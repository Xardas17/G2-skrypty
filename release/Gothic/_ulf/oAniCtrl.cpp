/******************************************************************************** 
 
     $Workfile:: oAniCtrl.cpp         $                $Date:: 17.02.01 16:24   $
     $Revision:: 167                  $             $Modtime:: 17.02.01 16:21   $
       $Author:: Wohlers              $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oAniCtrl.cpp $
 * 
 * 167   17.02.01 16:24 Wohlers
 * Bodystate Dead wird gesetzt, wenn NSCs in s_fallen oder s_fallenb
 * 
 * 166   16.02.01 19:35 Wohlers
 * Blutfix. zCAIPlayer hat nichts von Skriptbluttextur erfahren.
 * 
 * 165   10.02.01 23:45 Moos
 * Crashfix
 * 
 * 164   9.02.01 20:36 Wohlers
 * Bugfix CorrectAniStates
 * 
 * 163   8.02.01 18:10 Wohlers
 * 
 * 162   8.02.01 14:53 Moos
 * 
 * 161   7.02.01 21:15 Wohlers
 * 
 * 160   7.02.01 18:20 Moos
 * 
 * 159   6.02.01 12:40 Moos
 * 
 * 158   6.02.01 0:33 Wohlers
 * 
 * 157   30.01.01 19:11 Wohlers
 * 
 * 156   30.01.01 18:15 Wohlers
 * 
 * 155   29.01.01 22:34 Wohlers
 * 
 * 154   29.01.01 19:57 Keskenti
 * 
 * 153   29.01.01 16:19 Keskenti
 * 
 * 152   29.01.01 14:09 Moos
 * 
 * 151   28.01.01 20:16 Moos
 * 
 * 150   26.01.01 16:21 Moos
 * 
 * 149   23.01.01 16:22 Moos
 * 
 * 148   23.01.01 12:04 Moos
 * 
 * 147   22.01.01 20:01 Moos
 * 
 * 146   19.01.01 16:19 Keskenti
 * 
 * 145   18.01.01 16:52 Keskenti
 * 
 * 144   18.01.01 2:00 Wohlers
 * 
 * 143   17.01.01 0:04 Hildebrandt
 * methods inlined, autoRoll activated for diving
 * 
 * 142   16.01.01 19:12 Moos
 * 
 * 141   16.01.01 18:16 Moos
 * 
 * 140   16.01.01 10:56 Moos
 * 
 * 139   15.01.01 20:15 Moos
 * 
 * 138   12.01.01 18:19 Moos
 * 
 * 137   12.01.01 16:05 Moos
 * 
 * 136   12.01.01 12:38 Moos
 * 
 * 135   11.01.01 18:45 Moos
 * 
 * 134   11.01.01 16:30 Moos
 * 
 * 133   10.01.01 20:11 Moos
 * 
 * 132   10.01.01 19:53 Wohlers
 * 
 * 131   10.01.01 16:05 Wohlers
 * 
 * 130   10.01.01 15:57 Moos
 * 
 * 129   10.01.01 15:36 Moos
 * 
 * 128   10.01.01 15:37 Wohlers
 * 
 * 127   10.01.01 15:31 Moos
 * 
 * 126   10.01.01 9:00 Moos
 * 
 * 125   8.01.01 14:55 Wohlers
 * 
 * 124   20.12.00 17:13 Moos
 * 
 * 123   15.12.00 13:07 Moos
 * 
 * 122   14.12.00 20:45 Wohlers
 * 
 * 121   6.12.00 1:13 Speckels
 * (von Dieter auf Berts Rechner)
 * 
 * 120   29.11.00 12:52 Speckels
 * 
 * 119   28.11.00 11:39 Keskenti
 * 
 * 118   23.11.00 17:50 Wohlers
 * 
 * 117   21.11.00 19:16 Wohlers
 * 
 * 116   21.11.00 14:12 Wohlers
 * 
 * 115   17.11.00 16:52 Wohlers
 * 
 * 114   16.11.00 19:23 Wohlers
 * 
 * 113   10.11.00 17:34 Keskenti
 * 
 * 112   10.11.00 14:54 Wohlers
 * 
 * 111   9.11.00 12:04 Moos
 * 
 * 110   8.11.00 16:46 Wohlers
 * 
 * 109   3.11.00 15:20 Wohlers
 * 
 * 108   2.11.00 17:55 Keskenti
 * 
 * 107   1.11.00 16:13 Wohlers
 * 
 * 106   31.10.00 20:27 Keskenti
 * 
 * 105   27.10.00 20:02 Moos
 * 
 * 104   27.10.00 16:35 Wohlers
 * 
 * 103   26.10.00 15:48 Wohlers
 * 
 * 102   25.10.00 21:34 Wohlers
 * 
 * 101   20.10.00 16:41 Wohlers
 * 
 * 100   19.10.00 21:49 Wohlers
 * 
 * 99    11.10.00 22:56 Keskenti
 * 
 * 98    11.10.00 19:48 Wohlers
 * 
 * 97    11.10.00 17:42 Speckels
 * 
 * 96    11/10/00 17:37 Luesebrink
 * 
 * 95    11.10.00 17:08 Speckels
 * 
 * 94    10.10.00 13:39 Wohlers
 * 
 * 93    6.10.00 16:49 Wohlers
 * 
 * 92    6.10.00 15:51 Keskenti
 * 
 * 91    6.10.00 12:30 Wohlers
 * 
 * 90    5.10.00 19:03 Speckels
 * 
 * 89    5.10.00 14:49 Keskenti
 * 
 * 88    28/09/00 16:23 Luesebrink
 * 
 * 87    23.09.00 18:10 Wohlers
 * 
 * 86    23.09.00 17:55 Keskenti
 * 
 * 85    23.09.00 2:58 Edenfeld
 * 
 * 84    22.09.00 17:52 Keskenti
 * 
 * 83    21/09/00 19:06 Luesebrink
 * 
 * 82    21.09.00 17:15 Wohlers
 * 
 * 81    20.09.00 22:51 Wohlers
 * 
 * 80    20.09.00 16:51 Wohlers
 * 
 * 79    20/09/00 13:01 Luesebrink
 * 
 * 78    19.09.00 19:57 Keskenti
 * 
 * 77    19/09/00 19:52 Luesebrink
 * 
 * 76    15.09.00 16:04 Wohlers
 * 
 * 75    14.09.00 14:13 Keskenti
 * 
 * 74    12.09.00 22:43 Wohlers
 * 
 * 73    12.09.00 14:47 Wohlers
 * 
 * 72    11.09.00 19:25 Wohlers
 * 
 * 71    11.09.00 19:25 Wohlers
 * 
 * 70    11.09.00 19:23 Wohlers
 * 
 * 69    11.09.00 19:08 Speckels
 * 
 * 67    7.09.00 21:05 Wohlers
 * 
 * 66    6.09.00 14:48 Wohlers
 * 
 * 65    4.09.00 15:39 Keskenti
 * 
 * 64    2.09.00 14:55 Keskenti
 * 
 * 63    2/09/00 1:02 Luesebrink
 * 
 * 62    1/09/00 21:10 Luesebrink
 * 
 * 61    1.09.00 0:22 Rueve
 * 
 * 60    1.09.00 0:07 Wohlers
 * 
 * 59    30.08.00 19:59 Wohlers
 * 
 * 58    30.08.00 12:51 Wohlers
 * 
 * 57    29.08.00 21:24 Wohlers
 * 
 * 56    29.08.00 17:27 Wohlers
 * 
 * 55    29/08/00 17:10 Luesebrink
 * 
 * 54    29/08/00 16:06 Luesebrink
 * 
 * 53    29/08/00 15:38 Luesebrink
 * 
 * 52    29/08/00 15:32 Luesebrink
 * 
 * 51    29/08/00 11:58 Luesebrink
 * 
 * 50    28.08.00 21:38 Rueve
 * divetime init
 * 
 * 49    28/08/00 15:28 Luesebrink
 * 
 * 48    26/08/00 16:33 Luesebrink
 * 
 * 47    25/08/00 20:33 Luesebrink
 * 
 * 46    25/08/00 14:05 Luesebrink
 * 
 * 45    24/08/00 22:07 Luesebrink
 * 
 * 44    24/08/00 17:05 Luesebrink
 * 
 * 43    23/08/00 17:32 Luesebrink
 * 
 * 41    22.08.00 19:33 Wohlers
 * 
 * 40    17.08.00 16:56 Wohlers
 * 
 * 39    17.08.00 16:43 Rueve
 * constants.d aufräumen
 * 
 * 38    16.08.00 21:05 Keskenti
 * 
 * 37    16.08.00 15:10 Wohlers
 * 
 * 36    15.08.00 18:07 Wohlers
 * 
 * 35    15.08.00 13:29 Wohlers
 * 
 * 34    10.08.00 18:37 Wohlers
 * 
 * 33    10.08.00 12:37 Keskenti
 * 
 * 32    9.08.00 18:26 Keskenti
 * 
 * 31    9.08.00 18:21 Keskenti
 * 
 * 30    9.08.00 18:11 Keskenti
 * 
 * 29    4.08.00 18:03 Wohlers
 * 
 * 28    3.08.00 20:51 Wohlers
 * 
 * 27    3.08.00 17:41 Keskenti
 * 
 * 26    2/08/00 19:45 Luesebrink
 * 
 * 25    2.08.00 14:25 Wohlers
 * 
 * 24    31.07.00 22:04 Wohlers
 * 
 * 23    31.07.00 14:36 Wohlers
 * 
 * 22    27.07.00 15:03 Wohlers
 * 
 * 21    21.07.00 15:34 Wohlers
 * 
 * 20    20/07/00 19:05 Luesebrink
 * 
 * 19    20.07.00 18:33 Wohlers
 * 
 * 18    19.07.00 20:54 Wohlers
 * 
 * 17    19.07.00 20:05 Wohlers
 * 
 * 16    11.07.00 14:46 Wohlers
 * 
 * 15    5.07.00 12:20 Wohlers
 * 
 * 13    13.06.00 22:24 Edenfeld
 * 
 * 12    9.06.00 18:18 Wohlers
 * 
 * 11    9.06.00 12:58 Wohlers
 * Fixes
 * 
 * 10    5.06.00 22:34 Wohlers
 * uSrc 05.06.00
 * 
 * 9     25.05.00 14:50 Wohlers
 * Levelwechsel / Fernkampf
 * 
 * 8     24.05.00 20:28 Wohlers
 * Gothic 0.83
 * 
 * 7     22.05.00 18:41 Wohlers
 * Gothic 0.82
 * 
 * 14    12.05.00 5:45 Wohlers
 * 
 * 13    12.05.00 5:02 Wohlers
 * 
 * 12    12.05.00 3:37 Wohlers
 * 
 * 11    10.05.00 4:00 Wohlers
 * 
 * 10    9.05.00 20:20 Wohlers
 * Gothic 0.81
 * 
 * 9     8.05.00 23:07 Edenfeld
 * 
 * 6     8.05.00 21:14 Wohlers
 * Gothic 0.801
 * 
 * 5     8.05.00 19:31 Wohlers
 * Gothic 0.80 - Inventory
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 17    18.04.00 20:14 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 16    29.03.00 15:32 Wohlers
 * Various Bugfixes ( Waynet, Klettern )
 * 
 * 15    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 14    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 13    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 12    6.02.00 18:42 Wohlers
 * Various Fixes
 * 
 * 11    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 10    10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 9     20.12.99 20:39 Wohlers
 * ParticleControl angepasst
 * Ani-Probs (Jump/Climb) gefixed
 * 
 * 8     9.12.99 22:33 Wohlers
 * 
 * 7     7.12.99 22:08 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 6     24.11.99 23:39 Wohlers
 * Release Phoenix 069b
 * Mobsi-Erweiterungen 
 * 
 * 5     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

// auch in oAIHuman.cpp!!
//#define E3_NOWATERDIVE


#include "zCore.h"

#include "oAniCtrl.h"
#include "oNpc.h"
#include "oMobInter.h"
#include "oGame.h"
#include "oWorld.h"
#include "oMagic.h"
#include "oNpcMessages.h"
#include "oCollisionObjectMiscChar.h"
#include "oVisFX.h"

#include "zPhysics.h"
#include "zAICamera.h"
#include "zParticle.h"
#include "zParser.h"
#include "zSound.h"
#include "zSoundMan.h"
#include "zArchiver.h"
#include "zEventMan.h"
#include "zInput_Win32.h"
#include "zRenderLightContainer.h"

#include "zAccount.h"

#pragma warning ( disable:4244 )

// Logische Drehungen erlauben ?
zBOOL	ANI_ENABLE_TURN			= TRUE;
int		INTERPOLATE_MAX_TIME	= 1000 >> 1;

// Feintuning fürs Kampfsystem
int ANI_ADD_PARADE		= 0;
int ANI_ADD_STEPFORWARD	= 0;
int ANI_ADD_STEPBACK	= 0;
int ANI_ADD_HITSTEP		= 0;
int ANI_ADD_STUMBLE		= 0;
int ANI_ADD_FALLEN		= 0;

const zSTRING	ANI_EYEBLINK			= "R_EYESBLINK";

// Struktur zum Speichern der spezifischen Gildenwerte
struct oTGilValues 
{
	int				WATER_DEPTH_KNEE								[NPC_GIL_MAX];
	int				WATER_DEPTH_CHEST								[NPC_GIL_MAX];
//	int				JUMPUP_FORCE									[NPC_GIL_MAX];
	int				JUMPUP_HEIGHT									[NPC_GIL_MAX];	// DEFAULT = 200;
	int				SWIM_TIME										[NPC_GIL_MAX];
	int				DIVE_TIME										[NPC_GIL_MAX];
	int				STEP_HEIGHT										[NPC_GIL_MAX];
	int				JUMPLOW_HEIGHT									[NPC_GIL_MAX];
	int				JUMPMID_HEIGHT									[NPC_GIL_MAX];
	int				SLIDE_ANGLE1									[NPC_GIL_MAX];
	int				SLIDE_ANGLE2									[NPC_GIL_MAX];
	int				DISABLE_AUTOROLL								[NPC_GIL_MAX];	// 0 = Autoroll enabled ( default ) / 1 = Autoroll disabled
	int				SURFACE_ALIGN									[NPC_GIL_MAX];
	int				CLIMB_HEADING_ANGLE								[NPC_GIL_MAX];	// WallClimbUp - Winkel
	int				CLIMB_HORIZ_ANGLE								[NPC_GIL_MAX];
	int				CLIMB_GROUND_ANGLE								[NPC_GIL_MAX];
																					// Kampfdistanzen
	int				FIGHT_RANGE_BASE								[NPC_GIL_MAX];	
	int				FIGHT_RANGE_FIST								[NPC_GIL_MAX];	
	int				FIGHT_RANGE_G									[NPC_GIL_MAX];	
//	int				FIGHT_RANGE_DAG									[NPC_GIL_MAX];
	int				FIGHT_RANGE_1HS									[NPC_GIL_MAX];
	int				FIGHT_RANGE_1HA									[NPC_GIL_MAX];
	int				FIGHT_RANGE_2HS									[NPC_GIL_MAX];
	int				FIGHT_RANGE_2HA									[NPC_GIL_MAX];
//	int				FIGHT_RUN2WALK_LENGTH							[NPC_GIL_MAX];	// Übergangsbereich um den Angreifer vom Runmodus in den Walkmodus zu versetzen
	int				FALLDOWN_HEIGHT									[NPC_GIL_MAX];	// Wieviele Meter werden ohne Fallschaden überstanden ?
	int				FALLDOWN_DAMAGE_PERM							[NPC_GIL_MAX];
																					//	Blut
	int 			BLOOD_DISABLED									[NPC_GIL_MAX];	// DEFAULT = 0					; Blut ganz ausschalten (z.B. bei Sekletten) ? 
	int 			BLOOD_MAX_DISTANCE								[NPC_GIL_MAX];	// DEFAULT = 1000				; Wie weit spritzt das Blut (in cm) ?
	int				BLOOD_AMOUNT									[NPC_GIL_MAX];	// DEFAULT = 10					; Wie viel Blut ?
	int 			BLOOD_FLOW										[NPC_GIL_MAX];	// DEFAULT = 0					; Soll es sich langsam ausbreiten ?
	zSTRING			BLOOD_EMITTER									[NPC_GIL_MAX];	// DEFAULT = "PFX_BLOOD"		; Welcher Partikel-Emitter ?
	zSTRING			BLOOD_TEXTURE									[NPC_GIL_MAX];	// DEFAULT = "ZBLOODSPLAT2.TGA"	; Welche Textur ?
																					//	Drehgeschwindigkeit
	int				TURN_SPEED										[NPC_GIL_MAX];	// DEFAULT = NPC_TURNVELOCITY	= 150;
																					//	Schaden
//	oTDamageMode	DAMAGE_TYPE										[NPC_GIL_MAX];	// DEFAULT = oEDamageType_Blunt
//	int				DAMAGE					[ oEDamageIndex_MAX ]	[NPC_GIL_MAX];	// DEFAULT = oEDamageType_Blunt
/*	int 			DAMAGE_BARRIER									[NPC_GIL_MAX];  
	int 			DAMAGE_BLUNT									[NPC_GIL_MAX];  
	int 			DAMAGE_EDGE										[NPC_GIL_MAX];  
	int 			DAMAGE_FIRE										[NPC_GIL_MAX];  
	int 			DAMAGE_FLY										[NPC_GIL_MAX];  
	int 			DAMAGE_MAGIC									[NPC_GIL_MAX];  
	int 			DAMAGE_POINT									[NPC_GIL_MAX];  
	int 			DAMAGE_FALL										[NPC_GIL_MAX];  
*/
} TGilValues;

// InitAnis		= immer, wenn sich der Waffenmodus aendert -> setzt nicht den WalkMode !
// SetWalkMode	= immer, wenn sich der Walkmode aendert

oCAniCtrl_Human :: oCAniCtrl_Human ()
{
	npc					= NULL;
	targetVob			= NULL;			
	actionMode			= ANI_ACTION_STAND;
	wmode				= NPC_WEAPON_NONE;
	wmode_last			= NPC_WEAPON_NONE;
	wmode_selected		= NPC_WEAPON_NONE;
	changeweapon		= FALSE;	

	walkmode			= ANI_WALKMODE_RUN;
	nextwalkmode		= ANI_WALKMODE_RUN;		
	lastRunWalkSneak	= ANI_WALKMODE_RUN;
	always_walk			= FALSE;
	do_jump				= FALSE;
	defaultSurfaceAlign	= zMV_SURFACE_ALIGN_NONE;

	lookTargetx			= 0.5f;
	lookTargety			= 0.5f;

	distance			= 2;

	// KampfCombos
	comboNr				= 0;
	comboMax			= 0;
	canEnableNextCombo	= FALSE;
	canDoCollisionFX	= FALSE;
	endCombo			= FALSE;
	comboCanHit			= FALSE;
	hitPosUsed			= FALSE;
	hitAniID			= zMDL_ANI_ID_ILLEGAL;
	hitTarget			= NULL;;
	hitGraphical		= FALSE;
	lastHitAniFrame		= 0.0f;
	autoRollDirection	= 0.0f;

	memset(comboInfo,0,sizeof(comboInfo));

	paradeBeginFrame	= 0.0f;
	paradeEndFrame		= 0.0f;

	anioffset_lastper	= 0.0f;
	anioffset_thisper	= 0.0f;
	anioffset			= 0.0f;
	anioffset_ani		= zMDL_ANI_ID_ILLEGAL;

	for (int i=0; i<ANI_HITLIMB_MAX; i++) hitlimb[i] = NULL;

	// Clear all Anis
	dummyLastVar	= 0;
	int		amount	= (int)&dummyLastVar - (int)&s_dead1;
	memset (&s_dead1,0,amount);

	// autoRoll (0.003)
	SetAutoRollSpeed(0.01f);

//	SetDoOops (FALSE);
}

oCAniCtrl_Human :: ~oCAniCtrl_Human ()
{
	npc			= NULL;
	for (int i=0; i<ANI_HITLIMB_MAX; i++)	{ hitlimb[i] = NULL;					};	
	zRELEASE(targetVob);
}

void oCAniCtrl_Human :: Init (oCNpc *n)
{
	npc     		= n;  
	if (!n)			   return;
//	if (n->GetModel()) return;

    npc->AvoidShrink();                    // [Moos] sorge darür, dass das Visual wirklich existiert.
    		
    SetVob   (n);
    SetWorld (ogame->GetWorld());
	SetScriptValues();

	// Hier Overrides, da SetVob die Vars sonst fehlerhaft initialisiert
	// FIXME : Ist das nötig ?  [Moos] hoffentlich nicht, denn die AiPlayer-Umstellung verbietet das direkte Setzen der Welt.
	// GetWorld()			= ogame->GetGameWorld();
	
//	SetDoOops(FALSE);                           // zMV_DO_OOPS						= FALSE;
	SetConfigDoDetectWalkStopChasm(TRUE);       //  zMV_DO_DETECT_WALK_STOP_CHASM	= TRUE;

	InitAnimations();

 //   zERR_ASSERT_STRICT(GetModel());    
};

zBOOL oCAniCtrl_Human :: StartAni ( zTModelAniID aniID, zTModelAniID nextAniID )
{
    zERR_ASSERT(GetModel());

	// Ist Animation disabled
	zCModelAni* ani = GetModel()->GetAniFromAniID(aniID);
	if (!ani || ani->GetAniType()==zMDL_ANI_TYPE_DISABLED) return FALSE;

	if (nextAniID!=zMDL_ANI_ID_ILLEGAL) {
		// NextAni soll verändert / gesetzt werden
		// a) Erstmal gucken, obs eine AniBlend ist, muss besonders behandelt werden
		if (ani->GetAniType()==zMDL_ANI_TYPE_BLEND) {
			// * AniBlend * 
			zCModelAni* oldNextAni = ani->GetNextAni();
			ani		-> SetNextAni	(GetModel()->GetAniFromAniID(nextAniID));
			GetModel()	-> StartAni		(ani);
			ani		-> SetNextAni	(oldNextAni);
		
		} else {
			GetModel() -> StartAni (ani);
			zCModelAniActive* aniActive = GetModel()->GetActiveAni(ani);
			if (aniActive) {
				aniActive->SetNextAni(GetModel()->GetAniFromAniID(nextAniID));
			} else {
				zERR_WARNING("U: ANI: cannot set nextAni of "+ani->GetAniName());
				return FALSE;
			}
		}
	} else {
		GetModel()->StartAni(ani);
	}
	return TRUE;
}

void oCAniCtrl_Human :: SetNextAni( zTModelAniID ani, zTModelAniID nextAni )
{
    zERR_ASSERT(GetModel());
    
	zCModelAniActive* cAni = GetModel()->GetActiveAni(ani);
	if (cAni) {
		cAni->SetNextAni(GetModel()->GetAniFromAniID(nextAni));
	}
}

void oCAniCtrl_Human :: InitAnimations()
{
	if (!GetModel()) return;

	dummy1				= GetModel() -> GetAniIDFromAniName ("D1");
	dummy2				= GetModel() -> GetAniIDFromAniName ("D2");
	dummy3				= GetModel() -> GetAniIDFromAniName ("D3");
	dummy4				= GetModel() -> GetAniIDFromAniName ("D4");

	s_dead1				= GetModel() -> GetAniIDFromAniName ("S_DEAD");
	s_dead2				= GetModel() -> GetAniIDFromAniName ("S_DEADB");

	s_fall				= GetModel() -> GetAniIDFromAniName ("S_FALL");
	s_fallb				= GetModel() -> GetAniIDFromAniName ("S_FALLB");
	s_fallen			= GetModel() -> GetAniIDFromAniName ("S_FALLEN");
	s_fallenb			= GetModel() -> GetAniIDFromAniName ("S_FALLENB");

	s_hang				= GetModel() -> GetAniIDFromAniName ("S_HANG");
	t_hang_2_stand		= GetModel() -> GetAniIDFromAniName ("T_HANG_2_STAND");

	// ************************************************************************
	// ! Achtung ! OOPS - Ani wird im Base - Construktor definiert und benutzt
	// und alle anderen, die dort unten gebraucht werden.
	// ************************************************************************

	s_falldn			= GetModel() -> GetAniIDFromAniName ("S_FALLDN");
//	s_slide				= GetModel() -> GetAniIDFromAniName ("S_SLIDE");
//	s_slideb			= GetModel() -> GetAniIDFromAniName ("S_SLIDEB");
//	t_oops				= GetModel() -> GetAniIDFromAniName ("T_OOPS");
	
	help				= zMDL_ANI_ID_ILLEGAL;
	help1				= zMDL_ANI_ID_ILLEGAL;
	help2				= zMDL_ANI_ID_ILLEGAL;

	// *********************************************************
	// Weitere Interrupt - Anis ausser Oops
	// *********************************************************

	t_stumble			= GetModel() -> GetAniIDFromAniName ("T_STUMBLE");
	t_stumbleb			= GetModel() -> GetAniIDFromAniName ("T_STUMBLEB");
	t_fallen_2_stand	= GetModel() -> GetAniIDFromAniName ("T_FALLEN_2_STAND");
	t_fallenb_2_stand	= GetModel() -> GetAniIDFromAniName ("T_FALLENB_2_STAND");

	// *********************************************************
	// Animationen, die in allen Modi, den gleichen Namen haben
	// *********************************************************
	// Jumps
	t_stand_2_jumpstand	= GetModel() -> GetAniIDFromAniName ("T_STAND_2_JUMPSTAND");
	s_jumpstand			= GetModel() -> GetAniIDFromAniName ("S_JUMPSTAND");
	t_jumpstand_2_stand	= GetModel() -> GetAniIDFromAniName ("T_JUMPSTAND_2_STAND");
	
	_t_stand_2_jump			= GetModel() -> GetAniIDFromAniName ("T_STAND_2_JUMP");
	_s_jump					= GetModel() -> GetAniIDFromAniName ("S_JUMP");
	 t_jump_2_stand			= GetModel() -> GetAniIDFromAniName ("T_JUMP_2_STAND");
	_t_stand_2_jumpup		= GetModel() -> GetAniIDFromAniName ("T_STAND_2_JUMPUP");
	_s_jumpup				= GetModel() -> GetAniIDFromAniName ("S_JUMPUP");
	
	// Others
	_t_jumpup_2_falldn		= GetModel() -> GetAniIDFromAniName ("T_JUMPUP_2_FALLDN");
	_t_jump_2_falldn		= GetModel() -> GetAniIDFromAniName ("T_JUMP_2_FALLDN");

	for (int i=0; i<NPC_WEAPON_MAX; i++) 
		s_weapon[i] = GetModel()->GetAniIDFromAniName( "S_"+GetWeaponString(i) );

	_t_walk_2_aim		= zMDL_ANI_ID_ILLEGAL;
	_t_walkl_2_aim		= zMDL_ANI_ID_ILLEGAL;
	_t_walkr_2_aim		= zMDL_ANI_ID_ILLEGAL;
	_s_aim				= zMDL_ANI_ID_ILLEGAL;
	_t_aim_2_walk		= zMDL_ANI_ID_ILLEGAL;

	// **************
	// Items aufheben
	// **************
	// Item Manipulations
	t_stand_2_iaim		= GetModel() -> GetAniIDFromAniName ("T_STAND_2_IAIM");
	s_iaim				= GetModel() -> GetAniIDFromAniName ("S_IAIM");
	t_iaim_2_stand		= GetModel() -> GetAniIDFromAniName ("T_IAIM_2_STAND");
	// Item drop
	t_iaim_2_idrop		= GetModel() -> GetAniIDFromAniName ("T_IAIM_2_IDROP");
	s_idrop				= GetModel() -> GetAniIDFromAniName ("S_IDROP");
	t_idrop_2_stand		= GetModel() -> GetAniIDFromAniName ("T_IDROP_2_STAND");
	// Item take
	t_stand_2_iget		= GetModel() -> GetAniIDFromAniName ("T_STAND_2_IGET");
	s_iget				= GetModel() -> GetAniIDFromAniName ("S_IGET");
	s_oget				= GetModel() -> GetAniIDFromAniName ("S_OGET");	
	t_iget_2_stand		= GetModel() -> GetAniIDFromAniName ("T_IGET_2_STAND");
	// Item throw
	t_iaim_2_ithrow		= GetModel() -> GetAniIDFromAniName ("T_IAIM_2_ITHROW");
	s_ithrow			= GetModel() -> GetAniIDFromAniName ("S_ITHROW");
	t_ithrow_2_stand	= GetModel() -> GetAniIDFromAniName ("T_ITHROW_2_STAND");

	// **************
	// Specials
	// **************
	
	// Fackel - Kram
	_t_stand_2_torch	= GetModel() -> GetAniIDFromAniName ("T_STAND_2_TORCH");
	_s_torch			= GetModel() -> GetAniIDFromAniName ("S_TORCH");
	_t_torch_2_stand	= GetModel() -> GetAniIDFromAniName ("T_TORCH_2_STAND");

	InitAllAnis		();
	SearchStandAni  ();
}

void oCAniCtrl_Human :: SearchStandAni(zBOOL forceStartAni)
{
    if (!GetModel())
        return;

	// Waterwalk / Swimming / Diving 
	CheckWaterLevel();
	if ((GetModel()->GetNumActiveAnis()<=0) || forceStartAni) {
		// Nach laden eines Spielstandes muessen entsprechende Anis wieder gestartet werden.
		if (GetActionMode()==ANI_ACTION_SWIM) {
			GetModel()	->StartAni			(s_swim);	
		} else if (GetActionMode()==ANI_ACTION_DIVE) {
			GetModel()	->StartAni			(s_dive);
			npc		->SetPhysicsEnabled	(FALSE);
		}
	}
	if ((GetActionMode()==ANI_ACTION_SWIM) || (GetActionMode()==ANI_ACTION_DIVE)) return;

	// a) RUN
	// b) WALK
	// c) SNEAK
	int fm = npc->GetWeaponMode();
	// RUN
	zCModelAni* aniRun	= GetModel()->GetAniFromAniID(s_run	[fm]);
	zCModelAni* aniWalk	= GetModel()->GetAniFromAniID(s_walk	[fm]);
	zCModelAni* aniSneak= GetModel()->GetAniFromAniID(s_sneak[fm]);
	if (aniRun && (aniRun->GetAniType()!=zMDL_ANI_TYPE_DISABLED)) {
		walkmode = ANI_WALKMODE_RUN;
		SetWalkMode (walkmode);
	} else if (aniWalk && (aniWalk->GetAniType()!=zMDL_ANI_TYPE_DISABLED)) {
		walkmode = ANI_WALKMODE_WALK;
		SetWalkMode (walkmode);
	} else if (aniSneak && (aniSneak->GetAniType()!=zMDL_ANI_TYPE_DISABLED)) {
		walkmode = ANI_WALKMODE_SNEAK;
		SetWalkMode (walkmode);
	} else {
		zERR_WARNING("U: ANI: No Stand-Ani for current Weaponmode found.");
	}

	// Waterwalk beachten -> erst jetzt aktivieren
	if (GetWaterLevel()==1) {
		SetWalkMode(ANI_ACTION_WATERWALK);
		GetModel()->StartAni(_s_walk);
	} else {
		// init with Stand-Ani
		GetModel() -> StartAni		( _s_walk );	
		SetInterruptFollowAni	( _s_walk );
	}

	// Und SelfDistance errechnen für exakte Kampfentfernung
	//zCModelPrototype* proto = GetModel()->GetModelProto();
//	zREAL selfDist = (npc->GetBBox3DWorld().maxs[VZ] - npc->GetBBox3DWorld().mins[VZ]) / 2;
//	zERR_WARNING("U:TEST: 2."+npc->GetInstanceName()+" SelfDist :"+zSTRING(int(selfDist)));
}

void oCAniCtrl_Human :: StartStandAni()
{
    zERR_ASSERT(GetModel());
	GetModel() -> StartAni(_s_walk);
}

void oCAniCtrl_Human :: Reset()
{
    zERR_ASSERT(GetModel());
	InitFightAnis	(npc->GetWeaponMode());
	SetWalkMode		(ANI_WALKMODE_RUN);
	GetModel()->StartAni	(_s_walk);
}

void oCAniCtrl_Human :: InitAngleValuesForConsole()
{
	angle_slide1	= Alg_Rad2Deg(config.zMV_MAX_GROUND_ANGLE_WALK);
	angle_slide2	= Alg_Rad2Deg(config.zMV_MAX_GROUND_ANGLE_SLIDE2);
	angle_heading	= Alg_Rad2Deg(config.zMV_DCUL_WALL_HEADING_ANGLE);
	angle_horiz		= Alg_Rad2Deg(config.zMV_DCUL_WALL_HORIZ_ANGLE);
	angle_ground	= Alg_Rad2Deg(config.zMV_DCUL_GROUND_ANGLE);
}

/* --------------------------------------------------------
	 oCAniCtrl_Human :: SetScriptValues()

	 16.08.2000   [Michael]
			Run2WalkLength beseitigt.

  --------------------------------------------------------- */
void oCAniCtrl_Human :: SetScriptValues()
// **** Überschreibe Monsterabhängige Konstanten mit Skriptwerten ****
{
	static int index = -1;

	int		v;
	int		g		= npc->GetTrueGuild();

	if (index<0) {
		memset(&TGilValues,0,sizeof(TGilValues));
		index = parser.GetIndex(zSTRING("GIL_VALUES"));
		parser.CreateInstance(index,&TGilValues);
	}

	// Wasser - Knie Tiefe
	v = TGilValues.WATER_DEPTH_KNEE	[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.WATER_DEPTH_KNEE[1];
	if (v!=0) config.zMV_WATER_DEPTH_KNEE = v;
	
	// Wasser - Brust Tiefe
	v = TGilValues.WATER_DEPTH_CHEST[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.WATER_DEPTH_CHEST[1];
	if (v!=0) config.zMV_WATER_DEPTH_CHEST = v;

	//
	//	CODECHANGE [ROMAN]
	//

	// Jumpup - Height
	v = TGilValues.JUMPUP_HEIGHT[g];
	if (((v==0)) && (g<NPC_GIL_HUMANS)) v = TGilValues.JUMPUP_HEIGHT[1];
	zCAIPlayer::SetJumpUpForceByHeight(v == 0.0f ? 200.0f : v );
	//
	//	CODECHANGE [ROMAN] END
	//
	
	// Swim Time
	int swimtime = 0;
	v = TGilValues.SWIM_TIME[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.SWIM_TIME[1];
	swimtime = v;

	// Dive Time
	int divetime = 0;
	v = TGilValues.DIVE_TIME[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.DIVE_TIME[1];
	divetime = v;

	npc->SetSwimDiveTime(swimtime,divetime);

	// Step Height
	v = TGilValues.STEP_HEIGHT[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.STEP_HEIGHT[1];
	if (v!=0) config.zMV_STEP_HEIGHT = v;

	// Jumpuplow
	v = TGilValues.JUMPLOW_HEIGHT[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.JUMPLOW_HEIGHT[1];
	if (v!=0) config.zMV_YMAX_JUMPLOW = v;

	// Jumpmid
	v = TGilValues.JUMPMID_HEIGHT[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.JUMPMID_HEIGHT[1];
	if (v!=0) config.zMV_YMAX_JUMPMID = v;

	// Autoroll
	v = TGilValues.DISABLE_AUTOROLL[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.DISABLE_AUTOROLL[1];
	SetAutoRollEnabled(!v);
	
	// Sliding
	v = TGilValues.SLIDE_ANGLE1[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.SLIDE_ANGLE1[1];
	if (v!=0) config.zMV_MAX_GROUND_ANGLE_WALK = Alg_Deg2Rad(v);

	// Sliding
	v = TGilValues.SLIDE_ANGLE2[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.SLIDE_ANGLE2[1];
	if (v!=0) config.zMV_MAX_GROUND_ANGLE_SLIDE2 = Alg_Deg2Rad(v);

	// Surface-Align
	v = TGilValues.SURFACE_ALIGN[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.SURFACE_ALIGN[1];
	SetConfigDoSurfaceAlign  (zCAIPlayer::zTSurfaceAlignMode(v));
	defaultSurfaceAlign		= v;

	// Climb - Winkel 1
	v = TGilValues.CLIMB_HEADING_ANGLE[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.CLIMB_HEADING_ANGLE[1];
	if  (v!=0) config.zMV_DCUL_WALL_HEADING_ANGLE = Alg_Deg2Rad(v);

	// Climb - Winkel 2
	v = TGilValues.CLIMB_HORIZ_ANGLE[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.CLIMB_HORIZ_ANGLE[1];
	if  (v!=0) config.zMV_DCUL_WALL_HORIZ_ANGLE = Alg_Deg2Rad(v);
	
	// Climb - Winkel 3
	v = TGilValues.CLIMB_GROUND_ANGLE[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.CLIMB_GROUND_ANGLE[1];
	if  (v!=0) config.zMV_DCUL_GROUND_ANGLE = Alg_Deg2Rad(v);

	// *** Fallhöhe ohne Schaden ***
	v = TGilValues.FALLDOWN_HEIGHT[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.FALLDOWN_HEIGHT[1];
	if  (v!=0) npc->SetFallDownHeight(v);
	// *** Fallschaden pro Meter ***
	v = TGilValues.FALLDOWN_DAMAGE_PERM[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.FALLDOWN_DAMAGE_PERM[1];
	if  (v!=0) npc->SetFallDownDamage(v);

	// Fight-Range-Base
	v = TGilValues.FIGHT_RANGE_BASE[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.FIGHT_RANGE_BASE[1];
	if  (v!=0) npc->SetFightRangeBase(v);

	// Fight-Range-G		(AI Distanz, die angibt wie weit ein NPC zusätzlich zu Base+Waffenreichweite
	// entfernt sein muss, damit eine Sprungattacke o.ä. gültig ist

	v = TGilValues.FIGHT_RANGE_G[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.FIGHT_RANGE_G[1];
	if  (v!=0) npc->SetFightRangeG(v);

 
	// Blut
/*
	// Blut
	int 	BLOOD_DISABLED			[NPC_GIL_MAX];	// DEFAULT = 0					; Blut ganz ausschalten (z.B. bei Sekletten) ? 
	int 	BLOOD_MAX_DISTANCE		[NPC_GIL_MAX];	// DEFAULT = 1000				; Wie weit spritzt das Blut (in cm) ?
	int		BLOOD_AMOUNT			[NPC_GIL_MAX];	// DEFAULT = 10					; Wie viel Blut ?
	int 	BLOOD_FLOW				[NPC_GIL_MAX];	// DEFAULT = 0					; Soll es sich langsam ausbreiten ?
	zSTRING BLOOD_EMITTER			[NPC_GIL_MAX];	// DEFAULT = "PFX_BLOOD"		; Welcher Partikel-Emitter ?
	zSTRING BLOOD_TEXTURE			[NPC_GIL_MAX];	// DEFAULT = "ZBLOODSPLAT2.TGA"	; Welche Textur ?
*/

	//
	//	CODECHANGE [ROMAN]
	//
	zSTRING s;

	//
	v = TGilValues.BLOOD_DISABLED[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.BLOOD_DISABLED[1];
	npc->EnableBlood(!v);

	v = TGilValues.BLOOD_MAX_DISTANCE[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.BLOOD_MAX_DISTANCE[1];
	npc->SetBloodDistance(v);

	v = TGilValues.BLOOD_AMOUNT[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.BLOOD_AMOUNT[1];
	npc->SetBloodAmount(v);

	v = TGilValues.BLOOD_FLOW[g];
	if ((v==0) && (g<NPC_GIL_HUMANS)) v = TGilValues.BLOOD_FLOW[1];
	npc->EnableBloodFlow(v);

	s = TGilValues.BLOOD_EMITTER[g];
	if ((s.IsEmpty()) && (g<NPC_GIL_HUMANS)) s = TGilValues.BLOOD_EMITTER[1];
	npc->SetBloodEmitter(s);

	s = TGilValues.BLOOD_TEXTURE[g];
	if ((s.IsEmpty()) && (g<NPC_GIL_HUMANS)) s = TGilValues.BLOOD_TEXTURE[1];
	npc->SetBloodTexture(s);
	if (!s.IsEmpty()) this->SetBloodDefaultTexture(s);

	//
	v = TGilValues.TURN_SPEED[g];
	if (((v==0)) && (g<NPC_GIL_HUMANS)) v = TGilValues.TURN_SPEED[1];
	npc->SetTurnSpeed(v);

	//

	//
	//	CODECHANGE [ROMAN] - Applied new combinable damage types
	//
/*	v = TGilValues.DAMAGE_TYPE[g];
	if (((v==0)) && (g<NPC_GIL_HUMANS)) v = TGilValues.DAMAGE_TYPE[1];
	npc->SetDefaultDamage( v == 0 ? oEDamageType_Blunt : v );

/*	int damages[ oEDamageIndex_MAX ];
	damages[ oEDamageIndex_Barrier	] = ( ( TGilValues.DAMAGE_BARRIER	[g] == 0 ) && (g<NPC_GIL_HUMANS) ) ? TGilValues.DAMAGE_BARRIER	[1] : TGilValues.DAMAGE_BARRIER	[g];	
	damages[ oEDamageIndex_Blunt	] = ( ( TGilValues.DAMAGE_BLUNT		[g] == 0 ) && (g<NPC_GIL_HUMANS) ) ? TGilValues.DAMAGE_BLUNT	[1] : TGilValues.DAMAGE_BLUNT	[g];	
	damages[ oEDamageIndex_Edge		] = ( ( TGilValues.DAMAGE_EDGE		[g] == 0 ) && (g<NPC_GIL_HUMANS) ) ? TGilValues.DAMAGE_EDGE		[1] : TGilValues.DAMAGE_EDGE	[g];	
	damages[ oEDamageIndex_Fire		] = ( ( TGilValues.DAMAGE_FIRE		[g] == 0 ) && (g<NPC_GIL_HUMANS) ) ? TGilValues.DAMAGE_FIRE		[1] : TGilValues.DAMAGE_FIRE	[g];	
	damages[ oEDamageIndex_Fly		] = ( ( TGilValues.DAMAGE_FLY		[g] == 0 ) && (g<NPC_GIL_HUMANS) ) ? TGilValues.DAMAGE_FLY		[1] : TGilValues.DAMAGE_FLY		[g];	
	damages[ oEDamageIndex_Magic	] = ( ( TGilValues.DAMAGE_MAGIC		[g] == 0 ) && (g<NPC_GIL_HUMANS) ) ? TGilValues.DAMAGE_MAGIC	[1] : TGilValues.DAMAGE_MAGIC	[g];	
	damages[ oEDamageIndex_Point	] = ( ( TGilValues.DAMAGE_POINT		[g] == 0 ) && (g<NPC_GIL_HUMANS) ) ? TGilValues.DAMAGE_POINT	[1] : TGilValues.DAMAGE_POINT	[g];	
	damages[ oEDamageIndex_Fall		] = ( ( TGilValues.DAMAGE_FALL		[g] == 0 ) && (g<NPC_GIL_HUMANS) ) ? TGilValues.DAMAGE_FALL		[1] : TGilValues.DAMAGE_FALL	[g];	

	npc->SetDamages( damages );
*/

	//
	//	CODECHANGE [ROMAN] - Applied new combinable damage types
	//

	//
	//	CODECHANGE [ROMAN] END
	//
}

//void oCAniCtrl_Human :: SetModel ( zCModel *m )
//{
//	GetModel() = m;
//}

void oCAniCtrl_Human :: SetInterruptFollowAni(zTModelAniID ani)
{
    if (!GetModel())
        return;

	SetNextAni(t_jumpstand_2_stand,ani);
	SetNextAni(t_jump_2_stand,ani );
	SetNextAni(t_hang_2_stand,ani );
	SetNextAni(t_jumpupmid_2_stand, ani );
	SetNextAni(t_jumpuplow_2_stand, ani );

	// Interrupt - Anis
	SetNextAni(t_stumble, ani );
	SetNextAni(t_stumbleb, ani );
	SetNextAni(t_fallen_2_stand, ani );
	SetNextAni(t_fallenb_2_stand, ani );
	SetNextAni(_t_torch_2_stand, ani );

	SetNextAni(_t_walkbr_2_walk, ani );
	SetNextAni(_t_walkbl_2_walk, ani );	
}

void oCAniCtrl_Human :: InitAllAnis ( )
// Initialisiert alle Anis fuer alle Modis
// und packt diese in die Ani-Arrays
{
	zSTRING w,s;

	_s_defend = zMDL_ANI_ID_ILLEGAL;

	for (int fm=NPC_WEAPON_NONE; fm<=NPC_WEAPON_MAG; fm++) {

		// Get Prefix
		switch (fm) {
			case NPC_WEAPON_NONE	:	w = "";		break;
			case NPC_WEAPON_FIST	:	w = "FIST";	break;
			case NPC_WEAPON_DAG		:	case NPC_WEAPON_1HS		:	
										w = "1H";	break;
			case NPC_WEAPON_2HS		:	w = "2H";	break;
			case NPC_WEAPON_BOW		:	w = "BOW";	break;
			case NPC_WEAPON_CBOW	:	w = "CBOW";	break;
			case NPC_WEAPON_MAG		:	w = "MAG";	break;
//			case NPC_WEAPON_PSI 	:	w = "PSI";	break;
			default					:	return;
		}
		// *** Bewegungsmodi ? ***
		// *** Default = RUN   *** 

		s = w+"RUN";
		// **********
		// RUN
		// **********
		s_run				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s);				// Standmode
		t_run_2_runl		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"_2_"+s+"L");
		t_runl_2_run		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"L_2_"+s);
		s_runl				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"L");
		t_runl_2_runr		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"L_2_"+s+"R");
		t_runr_2_runl		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"R_2_"+s+"L");
		s_runr				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"R");
		t_runr_2_run		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"R_2_"+s);
		// Run - Loop - rueckwaerts
		// Im Run-Mode gibt's kein Rückwärts-Cycle
		t_run_2_runbl		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"_2_"+s+"BL");
		t_runbl_2_run		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BL_2_"+s);
		s_runbl				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"BL");
		t_runbl_2_runbr		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BL_2_"+s+"BR");
		t_runbr_2_runbl		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BR_2_"+s+"BL");
		s_runbr				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"BR");
		t_runbr_2_run		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BR_2_"+s);
		
		t_jumpb				[fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"JUMPB");

		// Drehen
		t_runturnl			[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"TURNL");
		t_runturnr			[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"TURNR");

		t_runstrafel		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"STRAFEL");
		t_runstrafer		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"STRAFER");

		// ********************
		// WALK 
		// ********************

		s = w+"WALK";
		s_walk				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s);				// Standmode
		t_walk_2_walkl		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"_2_"+s+"L");
		t_walkl_2_walk		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"L_2_"+s);
		s_walkl				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"L");
		t_walkl_2_walkr		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"L_2_"+s+"R");
		t_walkr_2_walkl		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"R_2_"+s+"L");
		s_walkr				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"R");
		t_walkr_2_walk		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"R_2_"+s);
		// Walk - Loop - rueckwaerts
		t_walk_2_walkbl		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"_2_"+s+"BL");
		t_walkbl_2_walk		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BL_2_"+s);
		s_walkbl			[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"BL");
		t_walkbl_2_walkbr	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BL_2_"+s+"BR");
		t_walkbr_2_walkbl	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BR_2_"+s+"BL");
		s_walkbr			[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"BR");
		t_walkbr_2_walk		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BR_2_"+s);
	
		// Drehen
		t_walkturnl			[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"TURNL");
		t_walkturnr			[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"TURNR");

		t_walkstrafel		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"STRAFEL");
		t_walkstrafer		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"STRAFER");

		// ********************
		// SNEAK 
		// ********************

		// **** FIXME : Sonderfall : Gobbo ***
//		if (npc->GetTrueGuild()==NPC_GIL_GOBBO)
//			s = "SNEAK";
//		else
			s = w +"SNEAK";

		s_sneak				[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s);				// Standmode
		t_sneak_2_sneakl	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"_2_"+s+"L");
		t_sneakl_2_sneak	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"L_2_"+s);
		s_sneakl			[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"L");
		t_sneakl_2_sneakr	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"L_2_"+s+"R");
		t_sneakr_2_sneakl	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"R_2_"+s+"L");
		s_sneakr			[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"R");
		t_sneakr_2_sneak	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"R_2_"+s);
		// sneak - Loop - rueckwaerts
		t_sneak_2_sneakbl	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"_2_"+s+"BL");
		t_sneakbl_2_sneak	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BL_2_"+s);
		s_sneakbl			[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"BL");
		t_sneakbl_2_sneakbr	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BL_2_"+s+"BR");
		t_sneakbr_2_sneakbl	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BR_2_"+s+"BL");
		s_sneakbr			[fm] = GetModel() -> GetAniIDFromAniName ("S_"+s+"BR");
		t_sneakbr_2_sneak	[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"BR_2_"+s);
	
		// Drehen
		t_sneakturnl		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"TURNL");
		t_sneakturnr		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"TURNR");

		t_sneakstrafel		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"STRAFEL");
		t_sneakstrafer		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+s+"STRAFER");

		// Modi - Transitions
		t_run_2_walk		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"RUN_2_"	+w+"WALK");
		t_walk_2_run		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"WALK_2_"	+w+"RUN");
		t_run_2_sneak		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"RUN_2_"	+w+"SNEAK");
		t_sneak_2_run		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"SNEAK_2_"+w+"RUN");
		
		// ******************
		// Jump aus dem Lauf
		// ******************
		t_runl_2_jump		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"RUNL_2_JUMP");
		t_runr_2_jump		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"RUNR_2_JUMP");
		t_jump_2_runl		[fm] = GetModel() -> GetAniIDFromAniName ("T_JUMP_2_"+w+"RUNL");
	
		// Und die KampfAnis
		InitFightAnis (fm);
	}

	// ******************
	// Jump Low / Mid
	// ******************
	t_stand_2_jumpuplow		= GetModel()->GetAniIDFromAniName("T_STAND_2_JUMPUPLOW");
	s_jumpuplow				= GetModel()->GetAniIDFromAniName("S_JUMPUPLOW");
	t_jumpuplow_2_stand		= GetModel()->GetAniIDFromAniName("T_JUMPUPLOW_2_STAND");
	t_stand_2_jumpupmid		= GetModel()->GetAniIDFromAniName("T_STAND_2_JUMPUPMID");
	s_jumpupmid				= GetModel()->GetAniIDFromAniName("S_JUMPUPMID");
	t_jumpupmid_2_stand		= GetModel()->GetAniIDFromAniName("T_JUMPUPMID_2_STAND"); 

	// ... das Universum und der ganze Rest
	// ***************
	// Water Walk
	// ***************
	t_walk_2_walkwl		= GetModel() -> GetAniIDFromAniName("T_WALK_2_WALKWL"); 
	t_walkwl_2_walk		= GetModel() -> GetAniIDFromAniName("T_WALKWL_2_WALK");
	s_walkwl			= GetModel() -> GetAniIDFromAniName("S_WALKWL"); 
	t_walkwl_2_walkwr	= GetModel() -> GetAniIDFromAniName("T_WALKWL_2_WALKWR");
	t_walkwr_2_walkwl	= GetModel() -> GetAniIDFromAniName("T_WALKWR_2_WALKWL");
	s_walkwr			= GetModel() -> GetAniIDFromAniName("S_WALKWR"); 
	t_walkwr_2_walk		= GetModel() -> GetAniIDFromAniName("T_WALKWR_2_WALK");
	// Bbackward - Loop
	t_walk_2_walkwbl	= GetModel() -> GetAniIDFromAniName("T_WALK_2_WALKWBL");
	t_walkwbl_2_walk	= GetModel() -> GetAniIDFromAniName("T_WALKWBL_2_WALK");
	s_walkwbl			= GetModel() -> GetAniIDFromAniName("S_WALKWBL");
	t_walkwbl_2_walkwbr	= GetModel() -> GetAniIDFromAniName("T_WALKWBL_2_WALKWBR");
	t_walkwbr_2_walkwbl	= GetModel() -> GetAniIDFromAniName("T_WALKWBR_2_WALKWBL");
	s_walkwbr			= GetModel() -> GetAniIDFromAniName("S_WALKWBR"); 
	t_walkwbr_2_walk	= GetModel() -> GetAniIDFromAniName("T_WALKWBR_2_WALK");

	// ********************
	// Schwimmen / Tauchen
	// ********************
	t_swimturnl			= GetModel() -> GetAniIDFromAniName("T_SWIMTURNL");
	t_swimturnr			= GetModel() -> GetAniIDFromAniName("T_SWIMTURNR");
	t_walkwl_2_swimf	= GetModel() -> GetAniIDFromAniName("T_WALKWL_2_SWIMF");
	s_swimf				= GetModel() -> GetAniIDFromAniName("S_SWIMF");
	t_swimf_2_walkwl	= GetModel() -> GetAniIDFromAniName("T_SWIMF_2_WALKWL");
	t_walkwbl_2_swimb	= GetModel() -> GetAniIDFromAniName("T_WALKWBL_2_SWIMB");
	t_swimb_2_walkwbl	= GetModel() -> GetAniIDFromAniName("T_SWIMB_2_WALKWBL");
	t_swim_2_swimb		= GetModel() -> GetAniIDFromAniName("T_SWIM_2_SWIMB");
	t_swimb_2_swim		= GetModel() -> GetAniIDFromAniName("T_SWIMB_2_SWIM");
	s_swimb				= GetModel() -> GetAniIDFromAniName("S_SWIMB");
	t_swimf_2_swim		= GetModel() -> GetAniIDFromAniName("T_SWIMF_2_SWIM");
	s_swim				= GetModel() -> GetAniIDFromAniName("S_SWIM");
	t_swim_2_swimf		= GetModel() -> GetAniIDFromAniName("T_SWIM_2_SWIMF");
	t_swim_2_dive		= GetModel() -> GetAniIDFromAniName("T_SWIM_2_DIVE");
	s_dive				= GetModel() -> GetAniIDFromAniName("S_DIVE");
	t_divef_2_swim		= GetModel() -> GetAniIDFromAniName("T_DIVEF_2_SWIM");
	t_dive_2_divef		= GetModel() -> GetAniIDFromAniName("T_DIVE_2_DIVEF");
	s_divef				= GetModel() -> GetAniIDFromAniName("S_DIVEF");
	t_divef_2_dive		= GetModel() -> GetAniIDFromAniName("T_DIVEF_2_DIVE");
	t_diveturnl			= GetModel() -> GetAniIDFromAniName("T_DIVETURNL");
	t_diveturnr			= GetModel() -> GetAniIDFromAniName("T_DIVETURNR");	
	t_dive_2_drowned	= GetModel() -> GetAniIDFromAniName("T_DIVE_2_DROWNED");
	s_drowned			= GetModel() -> GetAniIDFromAniName("S_DROWNED");
	
	// ********************
	// Umsehen
	// ********************
	
	s_look				= GetModel() -> GetAniIDFromAniName("T_LOOK");
	s_point				= GetModel() -> GetAniIDFromAniName("T_POINT");

	// ********************
	// Drohen
	// ********************

	t_warn				= GetModel() -> GetAniIDFromAniName("T_WARN");
}

void oCAniCtrl_Human :: SetWalkMode(int wm)
{	
	int fm;
	if (wm==ANI_WALKMODE_RUN) {
		fm = npc->GetWeaponMode();
		_s_walk				=	s_run			[fm];
		_t_walk_2_walkl		=	t_run_2_runl	[fm];
		_t_walkl_2_walk		=	t_runl_2_run	[fm];
		_s_walkl			=	s_runl			[fm];
		_t_walkl_2_walkr	=	t_runl_2_runr	[fm];
		_t_walkr_2_walkl	=	t_runr_2_runl	[fm];
		_s_walkr			=	s_runr			[fm];
		_t_walkr_2_walk		=	t_runr_2_run	[fm];
		// Walk - Loop - rueckwaerts
		_t_walk_2_walkbl	=	t_run_2_runbl	[fm];
		_t_walkbl_2_walk	=	t_runbl_2_run	[fm];
		_s_walkbl			=	s_runbl			[fm];
		_t_walkbl_2_walkbr	=	t_runbl_2_runbr	[fm];
		_t_walkbr_2_walkbl	=	t_runbr_2_runbl	[fm];
		_s_walkbr			=	s_runbr			[fm];
		_t_walkbr_2_walk	=	t_runbr_2_run	[fm];
	
		_t_jumpb			=	t_jumpb			[fm];

		// Drehen
		_t_turnl			=	t_runturnl		[fm];
		_t_turnr			=	t_runturnr		[fm];

		_t_runl_2_jump		=	t_runl_2_jump	[fm];
		_t_runr_2_jump		=	t_runr_2_jump	[fm];
		_t_jump_2_runl		=	t_jump_2_runl	[fm];

		_t_strafel			=   t_runstrafel	[fm];
		_t_strafer			=   t_runstrafer	[fm];
		
		SetInterruptFollowAni(_s_walk);
		walkmode			=   wm;
		lastRunWalkSneak	=	walkmode;
		this->npc->SetBodyState( BS_RUN );

		if (npc->IsSelfPlayer()) npc->SetWalkStopChasm(FALSE);

	} else if (wm==ANI_WALKMODE_WALK) {
		fm = npc->GetWeaponMode();
		_s_walk				=	s_walk			[fm];
		_t_walk_2_walkl		=	t_walk_2_walkl	[fm];
		_t_walkl_2_walk		=	t_walkl_2_walk	[fm];
		_s_walkl			=	s_walkl			[fm];
		_t_walkl_2_walkr	=	t_walkl_2_walkr	[fm];
		_t_walkr_2_walkl	=	t_walkr_2_walkl	[fm];
		_s_walkr			=	s_walkr			[fm];
		_t_walkr_2_walk		=	t_walkr_2_walk	[fm];
		// Walk - Loop - rueckwaerts
		_t_walk_2_walkbl	=	t_walk_2_walkbl	[fm];
		_t_walkbl_2_walk	=	t_walkbl_2_walk	[fm];
		_s_walkbl			=	s_walkbl		[fm];
		_t_walkbl_2_walkbr	=	t_walkbl_2_walkbr[fm];
		_t_walkbr_2_walkbl	=	t_walkbr_2_walkbl[fm];
		_s_walkbr			=	s_walkbr		[fm];
		_t_walkbr_2_walk	=	t_walkbr_2_walk	[fm];
	
		_t_jumpb			=	zMDL_ANI_ID_ILLEGAL;

		// Drehen
		_t_turnl			=	t_walkturnl		[fm];
		_t_turnr			=	t_walkturnr		[fm];

		_t_strafel			=   t_walkstrafel	[fm];
		_t_strafer			=   t_walkstrafer	[fm];

		SetInterruptFollowAni(_s_walk);
		walkmode			=   wm;
		lastRunWalkSneak	=	walkmode;
		this->npc->SetBodyState( BS_WALK );

		if (npc->IsSelfPlayer()) npc->SetWalkStopChasm(TRUE);
//		SetDoOops(FALSE);

	} else if (wm==ANI_WALKMODE_SNEAK) {
		fm = npc->GetWeaponMode();
		_s_walk				=	s_sneak				[fm];
		_t_walk_2_walkl		=	t_sneak_2_sneakl	[fm];
		_t_walkl_2_walk		=	t_sneakl_2_sneak	[fm];
		_s_walkl			=	s_sneakl			[fm];
		_t_walkl_2_walkr	=	t_sneakl_2_sneakr	[fm];
		_t_walkr_2_walkl	=	t_sneakr_2_sneakl	[fm];
		_s_walkr			=	s_sneakr			[fm];
		_t_walkr_2_walk		=	t_sneakr_2_sneak	[fm];
		// Walk - Loop - rueckwaerts
		_t_walk_2_walkbl	=	t_sneak_2_sneakbl	[fm];
		_t_walkbl_2_walk	=	t_sneakbl_2_sneak	[fm];
		_s_walkbl			=	s_sneakbl			[fm];
		_t_walkbl_2_walkbr	=	t_sneakbl_2_sneakbr	[fm];
		_t_walkbr_2_walkbl	=	t_sneakbr_2_sneakbl	[fm];
		_s_walkbr			=	s_sneakbr			[fm];
		_t_walkbr_2_walk	=	t_sneakbr_2_sneak	[fm];
	
		_t_jumpb			=	zMDL_ANI_ID_ILLEGAL;

		// Drehen
		_t_turnl			=	t_sneakturnl		[fm];
		_t_turnr			=	t_sneakturnr		[fm];

		_t_strafel			=   t_sneakstrafel		[fm];
		_t_strafer			=   t_sneakstrafer		[fm];

		SetInterruptFollowAni(_s_walk);
		walkmode			=   wm;
		lastRunWalkSneak	=	walkmode;
		this->npc->SetBodyState( BS_SNEAK );
		
		if (npc->IsSelfPlayer()) npc->SetWalkStopChasm (TRUE);
		
//		zMV_DO_OOPS					= FALSE;

	} else if (wm == ANI_WALKMODE_WATER) {
		fm = npc->GetWeaponMode();

		_s_walk				=	s_walk[npc->GetWeaponMode()];
		_t_walk_2_walkl		=	t_walk_2_walkwl;
		_t_walkl_2_walk		=	t_walkwl_2_walk;
		_s_walkl			=	s_walkwl;
		_t_walkl_2_walkr	=	t_walkwl_2_walkwr;
		_t_walkr_2_walkl	=	t_walkwr_2_walkwl;
		_s_walkr			=	s_walkwr;
		_t_walkr_2_walk		=	t_walkwr_2_walk;
		
		// Walk - Loop - rueckwaerts
		_t_walk_2_walkbl	=	t_walk_2_walkwbl;
		_t_walkbl_2_walk	=	t_walkwbl_2_walk;
		_s_walkbl			=	s_walkwbl;
		_t_walkbl_2_walkbr	=	t_walkwbl_2_walkwbr;
		_t_walkbr_2_walkbl	=	t_walkwbr_2_walkwbl;
		_s_walkbr			=	s_walkwbr;
		_t_walkbr_2_walk	=	t_walkwbr_2_walk;

		_t_jumpb			=	zMDL_ANI_ID_ILLEGAL;
		
		// Drehen
		_t_turnl			=	GetModel()->GetAniIDFromAniName("T_WALKWTURNL");
		_t_turnr			=	GetModel()->GetAniIDFromAniName("T_WALKWTURNR");

		_t_strafel			=   GetModel()->GetAniIDFromAniName("T_WALKWSTRAFEL");
		_t_strafer			=   GetModel()->GetAniIDFromAniName("T_WALKWSTRAFER");

		SetInterruptFollowAni(_s_walk);

		walkmode = wm;
	
	} else if (wm == ANI_WALKMODE_SWIM) {
		t_stand_2_iaim	= zMDL_ANI_ID_ILLEGAL;
		walkmode		= wm;
		this->npc->SetBodyState( BS_SWIM );

	} else if (wm == ANI_WALKMODE_DIVE) {
		t_stand_2_iaim	= zMDL_ANI_ID_ILLEGAL;		
		walkmode		= wm;
		this->npc->SetBodyState( BS_DIVE );
	}

	// zMV_DO_DETECT_WALK_STOP_CHASM wieder auf FALSE, wenn NSC nicht der Spieler ist
	// if (!npc->IsAPlayer()) npc->SetConfigDoDetectWalkStopChasm(FALSE);
}

void oCAniCtrl_Human :: InitFightAnis (int fm)
// Erstelle KampfAnis ( neu fuer nur einen Mode ) entsprechend neuen Talent
{
	zSTRING w;

	switch (fm) {
		case NPC_WEAPON_FIST	:	w = "FIST";	break;
		case NPC_WEAPON_DAG		:	w = "DAG";	break;
		case NPC_WEAPON_1HS		:	w = "1HS";	break;
		case NPC_WEAPON_2HS		:	w = "2HS";	break;
		case NPC_WEAPON_BOW		:	w = "BOW";	break;
		case NPC_WEAPON_CBOW	:	w = "CBOW";	break;
		case NPC_WEAPON_MAG		:	w = "MAG";	break;
//		case NPC_WEAPON_PSI 	:	w = "PSI";	break;
		default					:	return;
	}
	
	zSTRING ws = GetWeaponString(fm);

	// Sonderfall T und W getrennt
	// Zustand AIM
	t_walk_2_aim				[fm] = GetModel() -> GetAniIDFromAniName("T_"+ws+"WALK_2_"+w+"AIM");
	t_walkl_2_aim				[fm] = GetModel() -> GetAniIDFromAniName("T_"+ws+"WALKL_2_"+w+"AIM");
	t_walkr_2_aim				[fm] = GetModel() -> GetAniIDFromAniName("T_"+ws+"WALKR_2_"+w+"AIM");
	
	s_aim						[fm] = GetModel() -> GetAniIDFromAniName("S_"+w+"AIM");
	t_aim_2_walk				[fm] = GetModel() -> GetAniIDFromAniName("T_"+w+"AIM_2_"+ws+"WALK");

	if (fm<=NPC_WEAPON_2HS) {
		// Drehschläge 360 Grad
		t_hitl					[fm] = GetModel() -> GetAniIDFromAniName("T_"+ws+"ATTACKL");
		t_hitr					[fm] = GetModel() -> GetAniIDFromAniName("T_"+ws+"ATTACKR");
		// Attacks - Schlagkombi aus dem Stand
		t_hitf					[fm] = GetModel() -> GetAniIDFromAniName("S_"+ws+"ATTACK");
		// Attacks - Schlag aus dem Lauf ( Overlay Ani ! )
		t_hitfrun				[fm] = GetModel() -> GetAniIDFromAniName("T_"+ws+"ATTACKMOVE");
		
		t_paradeL				[fm] = GetModel() -> GetAniIDFromAniName("T_"+ws+"PARADES");

	} else if ((fm==NPC_WEAPON_BOW) || (fm==NPC_WEAPON_CBOW)) {

		// **************
		// Bow / CrossBow
		// **************

		// Es gibt nur noch eine Reload und eine ShootAni, 
		// die Talente werden per OverlayMDS aktiviert.
		
		// _t_hitback[0] = Reload-Animation-Transition
		
		t_hitback	[fm] = GetModel()->GetAniIDFromAniName("T_"+w+"RELOAD");
		t_hitf		[fm] = GetModel()->GetAniIDFromAniName("T_"+w+"AIM_2_"+w+"SHOOT");
		s_hitf		[fm] = GetModel()->GetAniIDFromAniName("S_"+w+"SHOOT");

		/*
		if (npc->HasFightTalent(NPC_TAL_BOW_3)) 
			t_hitback[0] [fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"RELOAD3");
		else if (npc->HasFightTalent(NPC_TAL_BOW_2)) 
			t_hitback[0] [fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"RELOAD2");
		else if (npc->HasFightTalent(NPC_TAL_BOW_1)) 
			t_hitback[0] [fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"RELOAD1");
		else
			t_hitback[0] [fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"RELOAD");
													
		// _t_hitf[0] [fm] = T_BOWAIM_2_BOWSHOOT
		t_hitf[0]		[fm] = GetModel() -> GetAniIDFromAniName ("T_"+w+"AIM_2_"+w+"SHOOT");
		// _s_hitfs [fm] = S_BOWSHOOT
		s_hitf[0]		[fm] = GetModel() -> GetAniIDFromAniName ("S_"+w+"SHOOT");*/
	}
}

/* --------------------------------------------------------
	 oCAniCtrl_Human :: SetFightAnis( int fm )

	 16.08.2000   [Michael]
			WEAPON_DAG beseitigt.

  --------------------------------------------------------- */

void oCAniCtrl_Human :: SetFightAnis (int fm)
// Kopiere in die entsprechenden Kampfaliases die gewuenschten KampfAnidaten
{
	_t_walk_2_aim				 = t_walk_2_aim	[fm];
	_t_walkl_2_aim				 = t_walkl_2_aim[fm];
	_t_walkr_2_aim				 = t_walkr_2_aim[fm];
	_s_aim						 = s_aim		[fm];
	_t_aim_2_walk				 = t_aim_2_walk	[fm];

	if (fm<=NPC_WEAPON_2HS) {
		// Hits 
		_t_hitl					 = t_hitl		[fm];
		_t_hitr					 = t_hitr		[fm];
		// ***************
		// Multi Schläge
		// ***************
		// Schlag nach Vorne
		_t_hitf					 = t_hitf		[fm];
		_t_hitfrun				 = t_hitfrun	[fm];

		_t_paradeL				 = t_paradeL	[fm];

	} else if ((fm==NPC_WEAPON_BOW) || (fm==NPC_WEAPON_CBOW)) {

		// **************
		// Bow 
		// **************
						
		// _t_hitback[0] = Reload-Animation-Transition
		_t_hitback	= t_hitback	[fm];													
		// _t_hitf[0] [fm] = T_BOWAIM_2_BOWSHOOT
		_t_hitf		= t_hitf	[fm];
		// _s_hitfs [fm] = S_BOWSHOOT
		_s_hitf		= s_hitf	[fm];
	
	}

	// Intiialisiere Waffenreichweiten
	// Fight - Run2WalkLength
	int* adr = NULL;
	int	 v;
	int  g = npc->GetTrueGuild();
	switch (fm) {
		case NPC_WEAPON_FIST	:	adr = (int*)&TGilValues.FIGHT_RANGE_FIST;	break;
		case NPC_WEAPON_1HS		:	adr = (int*)&TGilValues.FIGHT_RANGE_1HS;	break;
//		case NPC_WEAPON_1HA		:	adr = (int*)&TGilValues.FIGHT_RANGE_1HA;	break;
		case NPC_WEAPON_2HS		:	adr = (int*)&TGilValues.FIGHT_RANGE_2HS;	break;
//		case NPC_WEAPON_2HA		:	adr = (int*)&TGilValues.FIGHT_RANGE_2HA;	break;
	}
	
	if (adr) {
		v = adr[g];
		if ((v==0) && (g<NPC_GIL_MAX)) v = adr[1];
		//changed[dennis]
		if( fm == NPC_WEAPON_FIST ) npc -> SetFightRangeFist(v);
	}
}

void oCAniCtrl_Human  :: StartAniWithOffset(zTModelAniID ani, zREAL offset)
// Offset wird zusätzlich zur normalen Bewegung aus der Ani auf die Ani addiert.
// Diese speziellen Anis werden dann jeweils in der DOAI durch den Aufruf von
// DoAniWithOffset um den entsprechenden Offset jeweils nach vorne / hinten versetzt 
// (linear) -> offset ist rel. Bewegung um cm.
// TEMP : Dies ist eine Testfunktion fürs Feintuning des Kampfsystems
{
/*	if (!anioffset_ani) {
		anioffset_lastper	= anioffset_thisper = 0.0f;
		anioffset_ani		= ani;
		anioffset			= offset;
		GetModel() -> StartAni(ani);
	}*/
}

void oCAniCtrl_Human :: DoAniWithOffset()
// Offset wird zusätzlich zur normalen Bewegung aus der Ani auf die Ani addiert.
// Diese speziellen Anis werden dann jeweils in der DOAI durch den Aufruf von
// DoAniWithOffset um den entsprechenden Offset jeweils nach vorne / hinten versetzt 
// (linear) -> offset ist rel. Bewegung um cm.
// TEMP : Dies ist eine Testfunktion fürs Feintuning des Kampfsystems
{
/*	if (anioffset_ani) {
		if (!GetModel()->IsAniActive(anioffset_ani)) {
			// Restlichen Offset draufaddieren
			anioffset_thisper	= 100;
			anioffset_ani		= zMDL_ANI_ID_ILLEGAL;
		} else {
			anioffset_thisper	= GetModel() -> GetProgressPercent(anioffset_ani) * 100;
			if (anioffset_thisper < anioffset_lastper) {
				anioffset_thisper = 100;
				anioffset_ani	  = zMDL_ANI_ID_ILLEGAL;
			}
		}
		zVEC3 dir	= npc->GetAtVectorWorld();
		zREAL mover	= (anioffset_thisper - anioffset_lastper) * anioffset / 100;
		npc -> Move ( dir * mover );
		anioffset_lastper = anioffset_thisper;
		if (anioffset_ani==zMDL_ANI_ID_ILLEGAL) anioffset_lastper = 0;
	}*/
}

void oCAniCtrl_Human :: CorrectFightPosition()
{

	const zREAL		moveSpeed			= 25.0f / 1000.0f; // 1/s
	const float		EPS_FIGHTPOSCORR	= 0.0001f;
	static zBOOL	s_bScalerInit		= FALSE; 
	static zREAL	s_fDistanceScale	= 0.75f;

	if (!s_bScalerInit)
	{
		s_bScalerInit = TRUE;
		zCPar_Symbol* pSymbol = ::parser.GetSymbol( "NPC_COLLISION_CORRECTION_SCALER" );
		if ( pSymbol ) pSymbol->GetValue( s_fDistanceScale );
	}
	zREAL distanceScale = s_fDistanceScale;

	
	// Ausnahmen: Dragon/Troll
	if (npc->GetGuild()==NPC_GIL_DRAGON || npc->GetGuild()==NPC_GIL_TROLL)
	{
		distanceScale = 0.5F;
	}

	zCVob* target = NULL;
	if (npc->IsSelfPlayer())	target  = npc->GetFocusVob();
	else						target	= npc->GetEnemy();

	if (target) 
	{
		zREAL dist		= npc->GetDistanceToVobApprox(*target);
		zREAL minDist	= npc->GetFightRange() * distanceScale;

		if (dist < minDist) 
		{
		
			//zVEC3 moveDir	= (npc->GetPositionWorld() - target->GetPositionWorld()).NormalizeApprox();
			
			zVEC3 moveDir	= (npc->GetPositionWorld() - target->GetPositionWorld());
			
			if ( ( zAbs(moveDir[VX])>EPS_FIGHTPOSCORR ) || ( zAbs(moveDir[VZ])>EPS_FIGHTPOSCORR ) )	// div by 0 abfangen
			{
				// [EDENFELD] Addon: Höhendifferenz nicht mit reinrechnen (Bloodfly-fliegt-am-Character-hoch-Bug)
				moveDir[VY]		= 0;
			};

			moveDir.NormalizeApprox();

			npc->Move(moveDir * moveSpeed * ztimer.GetFrameTimeF());
//			npc->Move(moveDir * dist);

            if (target->GetCollisionObject())
                static_cast<oCCollObjectCharacter *> (target->GetCollisionObject()) ->SetDontLetHimComeNearer(npc);

            if (dist < minDist * .8F && npc->GetCollisionObject())
            {
                static_cast<oCCollObjectCharacter *> (npc->GetCollisionObject()) ->SetDontLetHimComeNearer(target);
            }
		}
	}
}

zSTRING oCAniCtrl_Human :: GetWalkModeString()
{
	switch (walkmode) {
		case ANI_WALKMODE_WALK		: return "WALK";	
		case ANI_WALKMODE_RUN		: return "RUN";		
		case ANI_WALKMODE_SNEAK		: return "SNEAK";	
	}

	return "";
}

void oCAniCtrl_Human :: CorrectAniStates()
// In einigen Faellen muss der aktuelle Ani-Zustand korrigiert werden.
{
	if (!GetModel()) return;

	// Safety : Sicherheitsmechanismus um Ani-Haenger zu vermeiden.
	// Fixme  : jeden Frame ?????
	zCModel* model = GetModel();
	for (int i=NPC_WEAPON_NONE; i<NPC_WEAPON_MAX; i++) {
		if ((npc->GetWeaponMode()!=i) && (i!=NPC_WEAPON_DAG)) {
			if (model->IsAniActive(s_walk[i]))	{
				model->FadeOutAni(s_walk[i]);
			}
			if (model->IsAniActive(s_run[i]))	{
				model->FadeOutAni(s_run[i]);
			}
			if (model->IsAniActive(s_sneak[i]))	{
				model->FadeOutAni(s_sneak[i]);
			}
		}				
	}

	// Falls keine Ani mehr aktiv, suche eine passende StandAni
	// passiert bei Benutzung eines Overlay-Mds ( _wounded ) und 
	// dem Versuch die Waffe wegzustecken. 
	if ((GetModel()->GetNumActiveAnis()==0) || !GetLayerAni(1)) {
  		SearchStandAni();
	}
}

/* ----------------------------------------------------------------------
	
	oCAniCtrl_Human :: CheckWaterLevel()

	27.10.2000	[Moos]	
                exitcheck macht jetzt auch Test auf Bewustlosigkeit


   ---------------------------------------------------------------------- */

zBOOL oCAniCtrl_Human :: CheckWaterLevel()
// Prueft und schaltet Normal - / WalkWater / Swim und Dive-Modus um
// TRUE, wenn Swimmodus aktiviert wurde
{
	if (npc->IsDead()) return FALSE;
	if (npc->IsUnconscious()) {
		if (GetWaterLevel()>0) npc->DoDie();	
		return FALSE;
	}

	int am = GetActionMode();
	// Kein Wasser

	if (GetWaterLevel()==0) {
		if (am == ANI_ACTION_WATERWALK) {
			// ************************
			// *** Waten nach gehen ***
			// ************************
			zTModelAniID	nextAni = zMDL_ANI_ID_ILLEGAL;
			togglewalk				= zMDL_ANI_ID_ILLEGAL;
//			nextwalkmode			= ANI_WALKMODE_RUN;
			nextwalkmode			= lastRunWalkSneak;
			int nextAniNr			= 0;

			if (GetModel()->IsAniActive(_s_walk)) {
				togglewalk	= GetModel()->GetAniIDFromAniName("T_WALK_2_RUN");
				nextAniNr	= 0;	// s_walk
			} else if (GetModel()->IsAniActive(_s_walkl)) {
				togglewalk	= GetModel()->GetAniIDFromAniName("T_WALKWL_2_RUNL");
				nextAniNr	= 1;	// s_walkl
			} else if (GetModel()->IsAniActive(_s_walkbl)) {
				togglewalk  = GetModel()->GetAniIDFromAniName("T_WALKWBL_2_WALKBL");
				nextAniNr	= 2;	// s_walkbl
			} else {
				togglewalk	= GetModel()->GetAniIDFromAniName("T_WALK_2_RUN");
				nextAni		= _s_walk;
				nextAniNr	= 0;	// s_walk
			}

			if (togglewalk!=zMDL_ANI_ID_ILLEGAL) {
				// Walkmode setzen
				StopTurnAnis	();
        
                if (!GetModel()->GetIsFlying())  // [MOOS] 12.01.01 darf beim Sprung aus dem Wasser nicht ausgeführt werden
				    SetWalkMode		(nextwalkmode);

				// NextAni setzen
				if (nextAniNr==0) nextAni = _s_walk;	else 
				if (nextAniNr==1) nextAni = _s_walkl;	else
				if (nextAniNr==2) nextAni = _s_walkbl;	
				// Safety 
				if (nextAni==zMDL_ANI_ID_ILLEGAL) nextAni = _s_walk;

                if (!GetModel()->GetIsFlying())
                {
    				StartAni		(togglewalk,nextAni);
				    SetActionMode	(ANI_ACTION_STAND);
                }
			} else {
				zSTRING aniName;
				switch (nextAniNr) { 
					case 0 :  aniName = "T_WALK_2_RUN";			break;
					case 1 :  aniName = "T_WALKWL_2_RUNL";		break;
					case 2 :  aniName = "T_WALKWBL_2_WALKBL";	break;
					default:  aniName = "T_WALK_2_RUN";			break;
				}
				zERR_WARNING("U: NPC: Transition "+aniName+" not found."+npc->GetInstanceName());
			}
		
		} else if (am == ANI_ACTION_SWIM) {
			// ****************************
			// *** Schwimmen nach gehen ***
			// ****************************
			GetModel() -> StartAni	(_s_walk);
			SetActionMode		(ANI_ACTION_STAND);
		
		} else if (am == ANI_ACTION_DIVE) {
			// **************************
			// *** Tauchen nach gehen ***
			// **************************
			GetModel() -> StartAni	(_s_walk);
			SetActionMode		(ANI_ACTION_STAND);
		}

	} else if ((GetWaterLevel()==1) && (GetFeetY()<GetWaterY())) {
		// mittelhohes Wasser
		if (am == ANI_ACTION_WATERWALK) {
			// Do nothing
			// In Walkmodus schalten, falls noetig
			if (GetWalkMode()!=ANI_WALKMODE_WATER) {
				SetWalkMode	(ANI_WALKMODE_WATER);
				StartAni	(_s_walk);
			}

		} else if (am == ANI_ACTION_SWIM) {
			// ********************************
			// *** Schwimmen nach Waterwalk ***
			// ********************************
			SetWalkMode		(ANI_WALKMODE_WATER);
			SetActionMode	(ANI_ACTION_WATERWALK);

			if (GetModel()->IsAniActive		(s_swimf)) 
				GetModel()->StartAni			(t_swimf_2_walkwl);
//				GetModel()->StartAni			(s_walkwl);
			else if (GetModel()->IsAniActive	(s_swimb)) 
				GetModel()->StartAni			(t_swimb_2_walkwbl);
//				GetModel()->StartAni			(s_walkwbl);
			else if(GetModel()->IsAniActive(t_swim_2_swimb))
			{
				GetModel()->StartAni			(t_swimb_2_walkwbl);
			}
			else
				GetModel()->StartAni			(_s_walk);
			
			npc->Move		(npc->GetAtVectorWorld()*10);
		
		} else if (am == ANI_ACTION_DIVE) {
			// ******************************
			// *** Tauchen nach Waterwalk ***
			// ******************************
			// Do nothing
		
		} else {
			// ****************************
			// *** Gehen nach Waterwalk ***
			// ****************************
			zSTRING s			= GetWalkModeString();
			zTModelAniID ani	= zMDL_ANI_ID_ILLEGAL;

			if (GetModel()->IsStateActive(_s_walk)) {
				ani = GetModel()->GetAniIDFromAniName("T_"+s+"_2_WALK");

			} else if (GetModel()->IsStateActive(_s_walkl)) {
				ani = GetModel()->GetAniIDFromAniName("T_"+s+"L_2_WALKWL");
			
			} else if (GetModel()->IsStateActive(_s_walkbl)) {
				ani = GetModel()->GetAniIDFromAniName("T_"+s+"L_2_WALKWBL");
			}

			SetActionMode	(ANI_ACTION_WATERWALK);
			SetWalkMode		(ANI_WALKMODE_WATER);

			if (ani!=zMDL_ANI_ID_ILLEGAL) {
				GetModel()->StartAni(ani);
			
			} else {
				// Bestimmte Ani-Zustaende ausschliessen.	
//				if (!GetModel()->IsAniActive(s_falldn) && !GetModel()->IsAniActive(_s_jump)) {
				if (!GetModel()->GetIsFlying()) {
					GetModel()->StartAni(_s_walk);
				}
			}
		}
	
	}
	else if ((GetWaterLevel()==2) && (GetFeetY()<GetWaterY())) 
	{
		if (((npc->GetWeaponMode()!=NPC_WEAPON_NONE) || npc->HasTorch()) && !npc->IsMonster()) 
		{
			// **************************************************
			// Waffe sofort wegstecken und Normalmodus aktivieren
			// **************************************************
			oCMsgWeapon* msg = zNEW( oCMsgWeapon(oCMsgWeapon::EV_FORCEREMOVEWEAPON) );									
			msg->SetHighPriority(TRUE);
			npc->GetEM()->OnMessage(msg,npc);
			return FALSE;
		}
	
		if (am == ANI_ACTION_DIVE) {
			// Do nothing

		} else if (am == ANI_ACTION_SWIM) {
		
		} else if (am == ANI_ACTION_WATERWALK) {
		
			// *******************************
			// *** Waterwalk zum Schwimmen ***
			// *******************************
			if (GetModel()->IsAniActive(_s_walkl)) 
				
				//GetModel()->StartAni("T_WALKWL_2_SWIMF");
				GetModel()->StartAni("S_SWIMF");

			else if (GetModel()->IsAniActive(_s_walkbl)) 
				
				//GetModel()->StartAni("T_WALKWBL_2_SWIMB");
				GetModel()->StartAni("S_SWIMB");
			
			else 
				GetModel()->StartAni(s_swim);
		
			SetState		(zMV_STATE_SWIM);	
			SetActionMode	(ANI_ACTION_SWIM);
				
		} else {
			// **************************
			// *** Walk zum Schwimmen ***
			// **************************
			// Hier sollten die Fallzustände greifen, die dann den richtigen State togglen
			// siehe "CheckFallStates
			// Hier schon return, weil der Waffencheck hier noch nicht gemacht werden darf, 
			// weil der NSc sonst schon im Fallen über Wasser die Waffe "wegpoppt" :)
			return FALSE;
		}
	}
/*
	if (GetModel()->IsAniActive("T_WALKWL_2_SWIMF") || GetModel()->IsAniActive("T_WALKWBL_2_SWIMB") ||
		GetModel()->IsAniActive("T_SWIMF_2_WALKWL") || GetModel()->IsAniActive("T_SWIMB_2_WALKWBL")) {
		
		SetState(zMV_STATE_SWIM);
	
	}
*/
	return FALSE;
}

void oCAniCtrl_Human :: SetAlwaysWalk(zBOOL pressed)
{
	static zBOOL caps_ok = TRUE;
	if ((caps_ok) && (pressed)) {
		always_walk = !always_walk;
		caps_ok		= FALSE;
		if (always_walk)	zCView::PrintDebug("<Always walk on.>\n");
		else				zCView::PrintDebug("<Always walk off.>\n");
	} else if (!pressed) {
		caps_ok		= TRUE;
	}
}

zBOOL oCAniCtrl_Human :: IsAlwaysWalk()
{
	return (always_walk && npc->IsAPlayer());
}

zBOOL oCAniCtrl_Human :: CanToggleWalkModeTo(int fm)
{	
	// Ist eine entsprechende Transition vorhanden ?
	togglewalk = zMDL_ANI_ID_ILLEGAL;
	zSTRING s,w;
	w = GetWeaponString(npc->GetWeaponMode());
	// Wohin hinschalten ?
	if (fm==ANI_WALKMODE_RUN) {
		// ****************
		// *** NACH RUN ***
		// ****************
		if (IsAlwaysWalk()) return FALSE;

		if (walkmode==ANI_WALKMODE_WALK) {
			if (IsStateAniActive(_s_walk))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"WALK_2_"+w+"RUN");	else
			if (IsStateAniActive(_s_walkl))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"WALKL_2_"+w+"RUNL");
		} else if (walkmode==ANI_WALKMODE_SNEAK) {
			if (IsStateAniActive(_s_walk))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"SNEAK_2_"+w+"RUN");	else
			if (IsStateAniActive(_s_walkl))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"SNEAKL_2_"+w+"RUNL");		
		}
		nextwalkmode = ANI_WALKMODE_RUN;
	} else

	if (fm==ANI_WALKMODE_WALK) {
		// *****************
		// *** NACH WALK ***
		// *****************
		if (walkmode==ANI_WALKMODE_RUN) {
			if (IsStateAniActive(_s_walk))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"RUN_2_"+w+"WALK");	else
			if (IsStateAniActive(_s_walkl))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"RUNL_2_"+w+"WALKL");
		} else if (walkmode==ANI_WALKMODE_SNEAK) {
			if (IsStateAniActive(_s_walk))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"SNEAK_2_"+w+"WALK");	else
			if (IsStateAniActive(_s_walkl))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"SNEAKL_2_"+w+"WALKL");		
		}
		nextwalkmode = ANI_WALKMODE_WALK;
	}
	
	if (fm==ANI_WALKMODE_SNEAK) {
		// *****************
		// *** NACH SNEAK ***
		// *****************
		if (!npc->HasTalent(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_SNEAK)) return FALSE;

		if (walkmode==ANI_WALKMODE_RUN) {
//			if (npc->GetTrueGuild()==NPC_GIL_GOBBO) {
//				if (IsStateAniActive(_s_walk))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUN_2_SNEAK");		else
//				if (IsStateAniActive(_s_walkl))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUNL_2_SNEAKL");		
//			} else {
				// *** Normal Case ***
				if (IsStateAniActive(_s_walk))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUN_2_"+w+"SNEAK");	else
				if (IsStateAniActive(_s_walkl))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUNL_2_"+w+"SNEAKL");		
//			}
		} else if (walkmode==ANI_WALKMODE_WALK) {
			// Es gibt keine Transitions von s_walk nach s_sneak
//			if (npc->GetTrueGuild()==NPC_GIL_GOBBO) {
//				if (IsStateAniActive(_s_walk)) togglewalk = s_sneak[0];
				//GetModel()->GetAniIDFromAniName("S_SNEAK");
//			} else {
				if (IsStateAniActive(_s_walk))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"WALK_2_"+w+"SNEAK");	else
				if (IsStateAniActive(_s_walkl))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"WALKL_2_"+w+"SNEAKL");		
				// if (GetModel()->IsStateActive(_s_walk)) togglewalk = s_sneak[npc->GetWeaponMode()];
				//GetModel()->GetAniIDFromAniName("S_"+w+"SNEAK");
//			}
		}
		nextwalkmode = ANI_WALKMODE_SNEAK;
	}

	zCModelAni* ani = GetModel()->GetAniFromAniID(togglewalk);
	return (ani && (ani->GetAniType()!=zMDL_ANI_TYPE_DISABLED));
}

zBOOL oCAniCtrl_Human :: CanToggleWalkMode()
{
	// Ist eine entsprechende Transition vorhanden ?
	togglewalk = zMDL_ANI_ID_ILLEGAL;
	zSTRING s,w;
	w = GetWeaponString(npc->GetWeaponMode());
	if (walkmode==ANI_WALKMODE_RUN) {
		
		if (npc->HasTalent(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_SNEAK)) {
			// *** FIX ME *** Special Case Gobbo
//			if (npc->GetTrueGuild()==NPC_GIL_GOBBO) {
//				if (IsStateAniActive(_s_walk))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUN_2_SNEAK");	else
//				if (IsStateAniActive(_s_walkl))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUNL_2_SNEAKL");		
//
//			} else {
			// *** Normal Case ***
				if (IsStateAniActive(_s_walk))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUN_2_"+w+"SNEAK");	else
				if (IsStateAniActive(_s_walkl))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUNL_2_"+w+"SNEAKL");		
//			}
			nextwalkmode=ANI_WALKMODE_SNEAK; 
		} else {
			if (IsStateAniActive(_s_walk))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUN_2_"+w+"WALK");	else
			if (IsStateAniActive(_s_walkl))	togglewalk = GetModel()->GetAniIDFromAniName("T_"+w+"RUNL_2_"+w+"WALKL");
			nextwalkmode=ANI_WALKMODE_WALK;
		}
	
	} else if (walkmode==ANI_WALKMODE_WALK) {

		if (IsAlwaysWalk()) return FALSE;
		
		if (IsStateAniActive(_s_walk))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"WALK_2_"+w+"RUN");	else
		if (IsStateAniActive(_s_walkl))	
			togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"WALKL_2_"+w+"RUNL");
		nextwalkmode=ANI_WALKMODE_RUN;

	} else if (walkmode==ANI_WALKMODE_SNEAK) {

		if (IsAlwaysWalk()) return FALSE;
		
		// *** FIX ME *** Special Case Gobbo
//		if (npc->GetTrueGuild()==NPC_GIL_GOBBO) {
//			if (IsStateAniActive(_s_walk))	togglewalk = GetModel() -> GetAniIDFromAniName("T_SNEAK_2_"+w+"RUN");	else
//			if (IsStateAniActive(_s_walkl))	togglewalk = GetModel() -> GetAniIDFromAniName("T_SNEAKL_2_"+w+"RUNL");
//		} else {
			if (IsStateAniActive(_s_walk))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"SNEAK_2_"+w+"RUN");	else
			if (IsStateAniActive(_s_walkl))	togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"SNEAKL_2_"+w+"RUNL");
//		}
		nextwalkmode=ANI_WALKMODE_RUN;
	
	} 
/*	else if ((walkmode==ANI_WALKMODE_WATER) && (GetWaterLevel()==0)) {
		if (GetModel()->IsStateActive(_s_walkl)) {
			togglewalk = GetModel() -> GetAniIDFromAniName("T_"+w+"WALKWL_2_"+w+"RUNL");
			nextwalkmode=ANI_WALKMODE_RUN;
		}
	}*/
	
	zCModelAni* ani = GetModel()->GetAniFromAniID(togglewalk);
	return (ani && (ani->GetAniType()!=zMDL_ANI_TYPE_DISABLED));
}

void oCAniCtrl_Human :: ToggleWalkMode(zTModelAniID nextAni)
{
	// Drehungen aus
	StopTurnAnis();
	StartAni	(togglewalk,nextAni);
	SetWalkMode	(nextwalkmode);
}

zBOOL oCAniCtrl_Human :: IsDead()
{
	// Regeltechnisch tot ?
	if (!npc->IsDead())			return FALSE;
	
	SetModel(npc->GetModel());

	// "Animatorisch" tot ?

	// bugfix hack, anscheinend gibts npcs die im s_fallen oder s_fallenb sind, aber trotzdem tot sind.
	// hier wird dann alles korrigiert

	if (GetModel()->IsAniActive(  s_fallen) || GetModel()->IsAniActive(s_fallenb) ||
	    GetModel()->IsAniActive(  s_dead1)  || GetModel()->IsAniActive(s_dead2)	  || GetModel()->IsAniActive(_s_jump))
	{
		// komplett tot - regeltechsnisch & Ani-Technisch
		npc->SetCollDetDyn	(FALSE);
		npc->SetCollDetStat	(TRUE);
		npc->SetBodyState	(BS_DEAD);
		//npc->SetSleeping	(TRUE);
		npc->GetEM()->Clear();
		this->SetConfigDoSurfaceAlign(zMV_SURFACE_ALIGN_NORMAL);


		if (GetModel()->IsAniActive( s_fallen) || GetModel()->IsAniActive(_s_jump))
		{
			GetModel()->StartAni(s_dead1);
		}
		else if (GetModel()->IsAniActive( s_fallenb))
		{
			GetModel()->StartAni(s_dead2);
		}

		//if (!npc->IsAIState(NPC_AISTATE_DEAD)) npc->DoDie();
		return TRUE;
	}
	// Ertrunken ?
	if ((GetModel()->IsAniActive(t_dive_2_drowned)) || (GetModel()->IsAniActive(s_drowned))) {
		SetState(oCAniCtrl_Human::zMV_STATE_DIVE);
		if (!npc->IsAIState(NPC_AISTATE_DEAD)) npc->DoDie();
		return TRUE;
	}

	// Falls die Teile laufen oder rumstehen, mal umkippen lassen.
	if ((!GetModel()->IsAniActive("T_DEADB")) && (!GetModel()->IsAniActive("T_DEAD")))
	if (IsStanding() || IsJumpStanding() || IsWalking()) {
		npc		-> DoDie();
		GetModel()	-> StartAni   ("T_DEADB");
		this->SetConfigDoSurfaceAlign(zMV_SURFACE_ALIGN_NORMAL);
		return TRUE;
	} else

	// Weitere kritische Anis
	if (GetModel()->IsAniActive(s_hang)) {
		// Haengen - fallen lassen
		// Kollision vermeiden
		zVEC3 at = npc->GetAtVectorWorld();
		npc	-> SetPhysicsEnabled(TRUE);
		npc -> Move		 (-at * 10);
		GetModel()->StartAni	 ("T_HANG_2_FALLDN");		
	}
	else if (GetModel()->IsAniActive("S_WOUNDED"))	GetModel()->StartAni("T_WOUNDED_2_DEAD");	
	else if (GetModel()->IsAniActive("S_WOUNDEDB"))	GetModel()->StartAni("T_WOUNDEDB_2_DEADB"); 

	return FALSE;
}

zBOOL oCAniCtrl_Human :: IsFallen()
{
	if (IsStateAniActive(s_fallen) || IsStateAniActive(s_fallenb)) {
		return TRUE;
	}
	return FALSE;
}

zBOOL oCAniCtrl_Human :: IsAiming()
{
	return GetModel() && (GetModel()->IsAniActive(_s_aim) || GetModel()->IsAniActive(_t_walk_2_aim));	
}

zBOOL oCAniCtrl_Human :: IsStateAniActive(zTModelAniID aniID)
{
	return IsStateAniActive(GetModel()->GetAniFromAniID(aniID));
};

zBOOL oCAniCtrl_Human :: IsStateAniActive(zCModelAni* ani)
// testet, ob die State-Ani auf Layer "1" aktiv ist, und keine anderen Anis auf Layer 1
// Weitere Animationen auf höheren Layern sind aber erlaubt : T_LOOK -> Layer 10
{
	zCModelAniActive*	curAni		= NULL;
	zBOOL				aniFound	= FALSE;

	for (int i=0; i<GetModel()->numActiveAnis; i++) {
		curAni = GetModel()->aniChannels[i];
		if (curAni->GetLayer()==1) {
			if (curAni->GetAni() != ani)	return FALSE;
			else							aniFound = TRUE;
		}
	}
	return aniFound;
}

zBOOL oCAniCtrl_Human :: IsStanding()
{
    if (!GetModel())
        return TRUE;

	// Correcting WalkMode
	int fm = npc->GetWeaponMode();

	if ((GetWalkMode()==ANI_WALKMODE_RUN) && (GetModel()->IsStateActive(s_walk[fm])))	 {
		GetModel()->StartAni(_s_walk);
	}
	
	if (IsStateAniActive(_s_walk)) {
		return TRUE;

	} else if ((GetModel()->IsAniActive(s_swim)) || (GetModel()->IsAniActive(s_dive))) {
		return TRUE;
	}
	return FALSE;
}

zBOOL oCAniCtrl_Human :: IsJumpStanding()
{
	return GetModel() && (GetModel()->IsStateActive(s_jumpstand));
}

zBOOL oCAniCtrl_Human :: IsWalking()
{
	return (!GetModel() || GetModel()->IsAniActive(_s_walkl) || GetModel()->IsAniActive(_s_walkr) || GetModel()->IsAniActive(_t_walk_2_walkl));
}


zBOOL oCAniCtrl_Human :: IsRunning()
{
	int fm = npc->GetWeaponMode();
	return (!GetModel()									|| 
			 GetModel()->IsAniActive(s_runl[fm])		|| 
			 GetModel()->IsAniActive(s_runr[fm])		|| 
			 GetModel()->IsAniActive(t_run_2_runl[fm])  || 
			 GetModel()->IsAniActive(t_runl_2_run[fm])	||
			 GetModel()->IsAniActive(t_runl_2_runr[fm])	||
			 GetModel()->IsAniActive(t_runr_2_runl[fm]) ||
			 GetModel()->IsAniActive(t_runr_2_run[fm]) );
}


zBOOL oCAniCtrl_Human :: IsWalkingBackward()
{
	return GetModel() && (GetModel()->IsAniActive(_s_walkbl) || GetModel()->IsAniActive(_s_walkbr) || GetModel()->IsAniActive(_t_walk_2_walkbl));
}

void oCAniCtrl_Human :: StopTurnAnis()
{
	GetModel() -> FadeOutAnisLayerRange(ANI_TURN_LAYER,ANI_TURN_LAYER);
//	GetModel() -> StopAnisLayerRange(ANI_TURN_LAYER,ANI_TURN_LAYER);
}


zREAL oCAniCtrl_Human :: Turn(zREAL dir, zBOOL playani)
// Hierüber sollen alle normalen Drehungen laufen
// Zumindest für den Spieler
// Berücksichtigt auch das Autoroll
// "dir" muss dabei +1 oder -1 sein ( Autoroll-Destination )
{
	zREAL deg			= 0.0f;
	autoRollDirection	= -dir;

	if (autoRollDirection<-1) autoRollDirection = -1; else
	if (autoRollDirection>+1) autoRollDirection = +1; 

	// Turn nicht erlaubt bei
//	if (!GetModel()->IsAniActive(_t_strafel))
//	if (!GetModel()->IsAniActive(_t_strafer))
	if (!GetModel()->IsAniActive(s_fallen))
	if (!GetModel()->IsAniActive(s_fallenb))
	if (!GetModel()->IsAniActive("S_WOUNDED"))
	if (!GetModel()->IsAniActive("S_WOUNDEDB"))
	if (!IsDead()) {
		zBOOL doLogicTurn = TRUE;
		// ****************
		// Rotation erlaubt
		// ****************
		if (playani) {
			zTModelAniID turnani = 0;
			if (GetModel()->IsAniActive(_s_walk)) {				
				if (dir<0)	turnani = _t_turnl;
				else		turnani = _t_turnr;		
			} else if (GetModel()->IsAniActive(s_dive)) {
				if (dir<0)	turnani = t_diveturnl;
				else		turnani = t_diveturnr;
			} else if (GetModel()->IsAniActive(s_swim)) {
				if (dir<0)	turnani = t_swimturnl;
				else		turnani = t_swimturnr;			
			} else {
				StopTurnAnis();
			}
			if (turnani) {
				GetModel() -> StartAni(turnani);
				doLogicTurn = !(GetModel()->GetAniFromAniID(turnani) && GetModel()->GetAniFromAniID(turnani)->FlagRotatesVob());
			}
		}
		
		// Rotation berechnen oder aus den Anis ?		
		if (ANI_ENABLE_TURN && doLogicTurn) 
		{

			//
			//	CODECHANGE [ROMAN]
			//

			deg = /*NPC_TURNVELOCITY_MSEC*/ npc->GetTurnSpeed() * (ztimer.GetFrameTimeF()/ztimer.GetMotionFactor()) * dir;
			//
			//	CODECHANGE [ROMAN] END
			//

			// Im Sprung Drehung verlangsamen
			if ( (GetModel()->IsAniActive(_t_runl_2_jump)) || (GetModel()->IsAniActive(_t_runr_2_jump)) || (GetModel()->IsAniActive(_t_stand_2_jump)) ){
				deg /= 3;
			}
			// Auch bei den Drehschlagen langsamer
			if (GetModel()->IsAniActive(_t_hitl) || GetModel()->IsAniActive(_t_hitr))
				deg /= 2;
			
			npc -> RotateWorld(0,1,0,deg);	
		}
	} 
	return deg;
}

/* --------------------------------------------------------
	 void oCAniCtrl_Human :: DoAutoRoll ()

	 16.1.2001	[HILDEBRANDT]
				AutoRoll fuer Dive aktiviert!
  --------------------------------------------------------- */

void oCAniCtrl_Human :: DoAutoRoll ()
{
	// Schwimmen -> sofort auf Null
	if (GetActionMode()==ANI_ACTION_SWIM) {
		if (GetAutoRollPosDest()!=0.0f) ResetAutoRoll();	

	// Tauchen -> AUTOROLL!
	} else if (GetActionMode()==ANI_ACTION_DIVE) {
		// Ausrichten
		SetAutoRollPosDest(autoRollDirection);
	
	} else if ((walkmode == ANI_WALKMODE_RUN) && (GetModel()->IsAniActive(_s_walkl))) {
		// Ausrichten
		SetAutoRollPosDest(autoRollDirection);
	
	} else {
		// normal wieder zurueck....
		SetAutoRollPosDest(0);
	}
};

void oCAniCtrl_Human :: TurnDegrees (zREAL deg, zBOOL startTurnAnis)
{
	//zBOOL isSheep = (npc->GetTrueGuild()==NPC_GIL_SHEEP) && (GetWalkMode()==ANI_WALKMODE_WALK);

	if (startTurnAnis /*|| isSheep*/) {
		if (GetModel()->IsAniActive(_s_walk)) {
			if (deg<0)	GetModel()->StartAni(_t_turnl);
			else		GetModel()->StartAni(_t_turnr);
		}
	} else {
		StopTurnAnis();		
	}

	npc -> RotateWorld(0,1,0,/*isSheep ? deg*0.5f : */deg);	
}

// Ulfis Little Helpers...
// World Tests

zBOOL oCAniCtrl_Human :: WallInFront(zREAL dist)
{
	// 2) Nische suchen, von oben nach unten
	zVEC3	ray			= GetVob()->GetAtVectorWorld() * dist;
    ray[VY]            += sin(config.zMV_MAX_GROUND_ANGLE_WALK) * dist;                               // [Moos] Ray leicht nach oben neigen, damit Boden-Schrägen nicht getroffen werden
	zVEC3	rayOrg		= GetCenterPos();
 
//	Line3D (rayOrg, rayOrg+ray, GFX_WHITE);
	return GetWorld()->TraceRayNearestHit (rayOrg, ray, GetVob(), zTRACERAY_VOB_IGNORE);
}

zSTRING oCAniCtrl_Human :: GetWeaponString(int wm)
{
	zSTRING s;

	switch (wm) 
	{
		case NPC_WEAPON_FIST	:	s = "FIST";		break;
		case NPC_WEAPON_DAG		:	s = "1H";		break;
		case NPC_WEAPON_1HS		:	s = "1H";		break;
		case NPC_WEAPON_2HS		:	s = "2H";		break;
		case NPC_WEAPON_BOW		:	s = "BOW";		break;
		case NPC_WEAPON_CBOW	:	s = "CBOW";		break;
		case NPC_WEAPON_MAG		:	s = "MAG";		break;
//		case NPC_WEAPON_PSI		:	s = "PSI";		break;
	}
	return s;
}

zSTRING oCAniCtrl_Human :: GetWeaponHitString(int wm)
{
	zSTRING w;
	switch (wm) {
		case NPC_WEAPON_FIST	:	w = "FIST";	break;
		case NPC_WEAPON_DAG		:	w = "DAG";	break;
		case NPC_WEAPON_1HS		:	w = "1HS";	break;
		case NPC_WEAPON_2HS		:	w = "2HS";	break;
		case NPC_WEAPON_BOW		:	w = "BOW";	break;
		case NPC_WEAPON_CBOW	:	w = "CBOW";	break;
		case NPC_WEAPON_MAG		:	w = "MAG";	break;
//		case NPC_WEAPON_PSI 	:	w = "PSI";	break;
	}
	return w;
}

zBOOL oCAniCtrl_Human :: IsDefending()
{
	return (GetModel()->IsStateActive(_s_defend));
}

void oCAniCtrl_Human :: GetFightLimbs()
{
	zBOOL found = FALSE;
	zCArray<zCModelAniEvent*> events;
	zCModelPrototype *proto = GetModel()->GetModelProto();
	
	for (int i=0; i<ANI_HITLIMB_MAX; i++) hitlimb[i] = NULL;
	GetModel()->GetOccuredAniEventList (events);
	int c = events.GetNumInList();
	for (i=0; i<c; i++) {
		zCModelAniEvent *ev = events[i];
		if (ev->aniEventType==zMDL_EVENT_TAG) {			
			if (ev->tagString=="DEF_HIT_LIMB") {
				// **************************************
				// An die Animation gebundene Kampflimbs 
				// **************************************
				for (int n=0; n<ANI_HITLIMB_MAX; n++) if (ev->string[n].Length()>0) {
					hitlimb[n] = GetModel()->SearchNode(ev->string[n]);	
					if (!hitlimb[n]) {
//						zerr.Report(zERR_WARN,-1,"U: (AniCtrl) Fightlimb "+ev->string[n]+" not found.");
					} else
						found = TRUE;
				} 
			} else if (ev->tagString=="DEF_OPT_FRAME") {
				// *****************************************
				// An die Animation gebundener Optimalframe 
				// *****************************************
				zSTRING n	= ev->string[0];
				int nr		= -1;
				do {
					nr++;
					comboInfo[nr].hitOptFrame = n.PickWord(nr+1," ").ToInt();
				} while ((comboInfo[nr].hitOptFrame>0) && (nr+1<ANI_MAX_HIT));
				comboMax	= nr;

				if (nr<=0) zERR_WARNING("U: ANI: No optimal Frames found."); 
			
			} else if (ev->tagString=="DEF_HIT_END") {
				// *****************************************
				// Die EndFrames der einzelnen Schläge
				// *****************************************
				zSTRING n	= ev->string[0];
				int nr		= -1;
				do {
					nr++;
					comboInfo[nr].hitEndFrame = n.PickWord(nr+1," ").ToInt();
				} while ((comboInfo[nr].hitOptFrame>0) && (nr+1<ANI_MAX_HIT));
				if (nr<=0) zERR_WARNING("U: ANI: No EndFrames found."); 

			} else if (ev->tagString=="DEF_WINDOW") {
				// *****************************************
				// Das ComboWindow für Tastendruck
				// *****************************************
				zSTRING n	= ev->string[0];
				int comboNr = 0;
				int nr		= 0;
				do {
					comboInfo[comboNr].comboStartFrame	= n.PickWord(nr+1," ").ToInt();
					comboInfo[comboNr].comboEndFrame	= n.PickWord(nr+2," ").ToInt();
					comboNr++;
					nr+=2;
				} while ((comboInfo[comboNr-1].comboStartFrame>0) && (comboNr<ANI_MAX_HIT));

				if (comboNr<=0) zERR_WARNING("U: ANI: No Combo-Window-Frames found."); 

			} else if (ev->tagString=="DEF_PAR_FRAME") {
				// *****************************************
				// Das Paradewindow
				// *****************************************
				zSTRING n			= ev->string[0];
				paradeBeginFrame	= (zREAL)n.PickWord(1," ").ToInt();
				paradeEndFrame		= (zREAL)n.PickWord(2," ").ToInt();

			} else if (ev->tagString=="DEF_DIR") {
				// *****************************************
				// Die Richtung des Schlages
				// *****************************************
				zSTRING n	= ev->string[0];
				int nr		= 0;
				do {
					comboInfo[nr].comboDir = (int)n[nr];
					nr++;
				} while ((nr < n.Length()) && (nr<ANI_MAX_HIT));
			}else if( ev->tagString=="DEF_DAM_MULTIPLY") {			
				zSTRING n = ev->string[0];
				float damageMultiplier = n.ToFloat();
				npc->SetDamageMultiplier( damageMultiplier );
			}
		}
	}

	if (found) return;

	proto->GetModelEventList(events);
	c = events.GetNumInList();
	for (i=0; i<c; i++) {
		zCModelAniEvent *ev = events[i];
		if ((ev->aniEventType==zMDL_EVENT_TAG) && (ev->tagString=="DEF_HIT_LIMB")) {
			for (int n=0; n<ANI_HITLIMB_MAX; n++) if (ev->string[n].Length()>0) {
				hitlimb[n] = GetModel()->SearchNode(ev->string[n]);	
				if (!hitlimb[n]) {
//					zerr.Report(zERR_WARN,-1,"U: (AniCtrl) Fightlimb "+ev->string[n]+" not found.");
					return;
				}
			}
		}
	}
}



/* ----------------------------------------------------------------------
	
    oCAniCtrl_Human :: DoSparks()	

	9.11.2000	[Moos]	
                Leakfix

   ---------------------------------------------------------------------- */


void oCAniCtrl_Human :: DoSparks(zVEC3 &pos, const zSTRING& strPFX ) 
{
	zCParticleFX	*partFX	= zNEW( zCParticleFX );
	zCVob			*vobFX	= zNEW( zCVob );
	vobFX	->SetCollDet			(FALSE);
	vobFX	->SetPositionWorld		(pos);  
	vobFX	->SetVisual				(partFX);
	vobFX	->SetDontWriteIntoArchive(TRUE);
	GetVob()		->GetHomeWorld()->AddVob(vobFX);
	
	partFX	->SetAndStartEmitter	( strPFX /*"PFX_METALSPARKS"*/ );

    zRELEASE(partFX); // [Moos] Leakfixes
    zRELEASE(vobFX);
}

zCModelAniActive* oCAniCtrl_Human :: GetLayerAni(int layer)
{
	for (int i=0; i<GetModel()->numActiveAnis; i++) {
		zCModelAniActive* ani = GetModel()->aniChannels[i];
		if (ani->GetLayer()==layer) return ani;
	}
	return NULL;
}

zTModelAniID oCAniCtrl_Human :: CheckLayerAni(int layer, const zSTRING &s)
// Show Debugging Info
{
	for (int i=0; i<GetModel()->numActiveAnis; i++) {
		zCModelAniActive* ani = GetModel()->aniChannels[i];
		if (ani->GetLayer()==layer) {
/*			zSTRING info;
			if (npc==oCNpc::player)	info += "SC: ";
			else						info += "NSC; ";
			info += s + ":" + ani->GetAni()->GetAniName() + " / " + zSTRING(ani->GetActFrame());
//			zerr.Message (info);
			//zCView :: stdoutput -> Printwin(info+"\n");*/
			// ******* FIX ME **********
			return zMDL_ANI_ID_ILLEGAL;
		}
	}
	return NULL;
}

zBOOL oCAniCtrl_Human :: CheckLimbHit(const zSTRING &nname, zCList<zCModelNodeInst> &hitModelNodeList)
// Prüft, ob angegebenes Limb getroffen wurde
{
	zCList<zCModelNodeInst> *node = hitModelNodeList.GetNextInList();
	while (node) {
		if (node->GetData()->GetProtoNode()->nodeName==nname) return TRUE;
		node = node->GetNextInList();
	}
	return FALSE;
}

void oCAniCtrl_Human :: ShowWeaponTrail()
{
	if ((npc->GetWeaponMode()>=NPC_WEAPON_DAG) && (npc->GetWeaponMode()<=NPC_WEAPON_2HS)) 
	{
		// Schnapp dir den entsprechenden Slot
		// FIXME : Hier Pointer benutzen
		zCModelNodeInst *node = GetModel()->SearchNode (zSTRING("ZS_RIGHTHAND"));

		// nicht, wenn an der rechten hand ein oCVisualFX Effekt klebt (dann sieht der polystrip scheisse aus)
		if ( zDYNAMIC_CAST<oCVisualFX>(this->GetModel()->GetAttachedNodeVob(node)) ) return;

		if (node && node->GetNodeVisual() && node->GetNodeVisual()->GetOBBox3D()) 
		{
			zMATRIX4			trafoNodeToWorld	= GetVob()->trafoObjToWorld * GetModel()->GetTrafoNodeToModel(node);
			zCOBBox3D			*obb				= node->GetNodeVisual()->GetOBBox3D();
			zPOINT3				pos1				= obb->center + ((obb->axis[0]*obb->extent[0])*0.8F);
			zPOINT3				pos2				= obb->center - ((obb->axis[0]*obb->extent[0])*1.1f);
			pos1 = trafoNodeToWorld * pos1;
			pos2 = trafoNodeToWorld * pos2;
			AddWeaponTrailSegment (pos1, pos2);
		};	
	}
}


void oCAniCtrl_Human :: StartHitCombo (zTModelAniID aniID, zCVob* target)
{
	canEnableNextCombo		= TRUE;
	canDoCollisionFX		= TRUE;
	comboCanHit				= TRUE;
	endCombo				= TRUE;
	comboNr					= 0;
	hitAniID				= aniID;
	hitTarget				= target;
	hitPosUsed				= FALSE;
	hitGraphical			= FALSE;
	lastHitAniFrame			= 0.0f;
	paradeBeginFrame		= 0.0f;
	paradeEndFrame			= 0.0f;
	
	GetModel() -> StartAni		(aniID);
//	this->StartAni( aniID, _s_walk );
	GetModel() -> AdvanceAnis	();

	// FIXME: paradeBeginFrame und paradeEndFrame werden im folgenden Call manchmal nicht richtig initialisiert 
	// (Bug Kommunikation Modelengine <-> Game ?)
	GetFightLimbs			();
}

void oCAniCtrl_Human :: SetComboHitTarget		(const zCVob *a_pTarget)
{
	hitTarget = const_cast<zCVob*>(a_pTarget);
};

void oCAniCtrl_Human :: StartHitGraphical (zTModelAniID aniID, zCVob* _stopTurnNpc)
{
	canEnableNextCombo		= FALSE;
	comboCanHit				= FALSE;
	endCombo				= FALSE;
	comboNr					= 0;
	hitAniID				= aniID;
	hitTarget				= NULL;
	hitPosUsed				= FALSE;
	hitGraphical			= TRUE;
	lastHitAniFrame			= 0.0f;
	paradeBeginFrame		= 0.0f;
	paradeEndFrame			= 0.0f;

	GetModel() -> StartAni		(aniID);
	GetModel() -> AdvanceAnis	();
	GetFightLimbs			();

	stopTurnVob				= _stopTurnNpc;
	stopTurnVobSign			= GetStopTurnVobSign();
}

int oCAniCtrl_Human :: GetStopTurnVobSign()
{
	if (stopTurnVob) {
		zREAL azi,elev;
		npc->GetAngles(stopTurnVob,azi,elev);
		return zSign(azi);
	}
	return 0;
}

zBOOL oCAniCtrl_Human :: HitCombo (zBOOL enableNextCombo)
// Original Hit
{	
	zBOOL debugMe = FALSE;

	// WeaponTrail an
	ShowWeaponTrail();
	
	// Positionskorrektur
	//DoAniWithOffset();
	//changed[dennis]
	CorrectFightPosition();

	// Laufende Schlagani holen
	zCModelAniActive* hitAni = GetModel()->GetActiveAni(hitAniID);
	if (!hitAni) return FALSE;

	int hitAniFrame = hitAni->GetActFrame();

	// *********************************************
	// Animation im Combo Window ?
	// *********************************************
	// Kann die naechste Combo noch aktiviert werden, 
	// oder wurde bereits STRG + UP ausserhalb des Combo-Windows betaetigt ?

	//	zBOOL inWindow = IsInCombo();
	//	
//	if (inWindow) {
//		screen		->Print(0,0,"Hit");
//	}

	if (debugMe) {
		screen		->Print(0,200,"ComboCanHit:"+zSTRING(comboCanHit));
		screen		->Print(0,400,"CanEnableNextCombo:"+zSTRING(canEnableNextCombo));
		screen		->Print(0,600,"endCombo:"+zSTRING(endCombo));		
		screen		->Print(0,800,"comboNr:"+zSTRING(comboNr));		
	
	}

	if (enableNextCombo && canEnableNextCombo) {
		// Nur eine Chance....
		canEnableNextCombo = FALSE;
		// Gültiger Toggle innerhalb des Combo Fensters
		if ((comboInfo[comboNr].comboStartFrame<=hitAniFrame) && (hitAniFrame<=comboInfo[comboNr].comboEndFrame)) {
			// Geschafft, naechste Combo Ani darf aktiviert werden.
			endCombo = FALSE;
			hitAni->SetActFrame(comboInfo[comboNr].comboEndFrame-1);
			lastHitAniFrame = comboInfo[comboNr].comboEndFrame-1;
			//hitAniFrame = comboInfo[comboNr].comboEndFrame-1;
		}
	}

	// *********************************************
	// Animation im HitFrame ?
	// *********************************************
	if (comboCanHit) 
	{
		if (hitAniFrame < comboInfo[comboNr].hitOptFrame) 
		{
			// *******************************
			// auf graphischen Treffer checken
			// Setzt Position gür PartikelFX
			// *******************************
			CheckHitTarget();
			oCItem *weapon = zDYNAMIC_CAST<oCItem>(npc->GetRightHand());
			if (weapon && weapon->GetEffect()) weapon->GetEffect()->SetLevel(3,TRUE);
		}
		else
		{
			// *******************************
			// Logischen Treffer ausführen
			// *******************************
			comboCanHit = FALSE;
			zREAL dist	= 0.0f;
			if (npc->IsInFightRange(hitTarget,dist) && npc->IsInFightFocus(hitTarget) && npc->IsSameHeight(hitTarget)) {
				
				// ***********************************
				// Kein Treffer, wenn NSC pariert hat.
				// ***********************************
				oCNpc* hitNpc = zDYNAMIC_CAST<oCNpc>(hitTarget);
				if (npc->GetDamageByType( oEDamageType_Fly )==0)		// flugschaden kann nicht pariert werden
				if (hitNpc && hitNpc->GetAnictrl() && hitNpc->GetAnictrl()->CanParade(npc) ) 
				{
					StartParadeEffects(hitNpc);
					return FALSE;
				}

				CreateHit(hitTarget);
			};
		}
	}

	// *********************************************
	// Animation im EndFrame ?
	// *********************************************
	if (hitAniFrame>=comboInfo[comboNr].hitEndFrame || (hitAniFrame<lastHitAniFrame)) 
	{
		// Combo beenden oder weitermachen ?
		oCItem *weapon = zDYNAMIC_CAST<oCItem>(npc->GetRightHand());
		if (weapon && weapon->GetEffect()) weapon->GetEffect()->SetLevel(5,TRUE);

		if (endCombo) {
			// Bei dem Schlag aus dem Rennen weiterlaufen
			if (hitAni->GetAni()->GetAniName().Search("MOVE")>0) {
				GetModel()->StartAni(_s_walkl);
			} else {
				if( !npc->IsSelfPlayer() )GetModel()->StartAni(_s_walk);
				else if( !enableNextCombo )GetModel()->StartAni(_s_walk);
				else;
			}
			hitAniFrame			= 0.0f;

		} else {
			canEnableNextCombo	= TRUE;
			canDoCollisionFX	= TRUE;
			comboCanHit			= TRUE;
			endCombo			= TRUE;
			hitPosUsed			= FALSE;
			comboNr++;
			if (comboNr>=comboMax) {
				comboNr			= 0;
				hitAniFrame		= 0.0f;
			}
		}
	}
	lastHitAniFrame = hitAniFrame;

	if( !endCombo ) return TRUE;
	return FALSE;
};

zCVob* oCAniCtrl_Human :: CheckHitTarget()
// Vom StartFrame bis zum OptHitFrame auf graphischen Treffer checken
{
	// *****************************
	// Check auf grafischen Treffer
	// *****************************
	zCList<zCVob::zTModelLimbColl> resCollList;
	zCVob::zTModelLimbColl *limbinfo;
	zCVob* vob, *foundVob = NULL;
	zREAL dist = 0.0f;

	for (int i=0; i<ANI_HITLIMB_MAX; i++) if (hitlimb[i]) 
	{
		npc -> CheckModelLimbCollision (hitlimb[i], TRUE, resCollList);

		if (resCollList.GetNumInList()!=0) 
		{	
			limbinfo	= resCollList.GetNextInList()->GetData();
			vob			= limbinfo -> hitVob;
			hitpos		= limbinfo -> approxCollisionPos;

			// Graphischer Treffer erlaubt ?
			if (hitGraphical && npc->IsInFightRange(vob,dist)) 
			{
				foundVob	= vob;
				hitPosUsed	= TRUE;
				CreateHit(vob);
				break;
			
			} 
			else if (hitTarget == vob) 
			{
				// Nur dieses Objekt darf getroffen werden
				// Graphischen Treffer speichern
				foundVob	= vob;
				hitPosUsed	= TRUE;
				limbname	= hitlimb[i]->GetProtoNode()->nodeName;
				break;
			}
		}		
	}
	// Folgende Zeile ist unbedingt noetig, damit keine Mem-Leaks entstehen !!
	resCollList.DeleteListDatas();	
	
	return foundVob;
};

void oCAniCtrl_Human :: CreateHit (zCVob* vob)
{
	if (!vob) return;

	// Im Kampf dürfen NSC's nur das gesetzte Ziel verletzen
	if (!npc->IsAPlayer() && zDYNAMIC_CAST<oCNpc>(vob) && (npc->GetEnemy()!=vob)) return;

	oCItem *weapon = zDYNAMIC_CAST<oCItem>(npc->GetRightHand());
	if (weapon && weapon->GetEffect()) weapon->GetEffect()->SetLevel(4,TRUE);


	// *****************************
	// Treffer
	// *****************************

	// [EDENFELD] Bodystate BS_HIT auch setzen
	npc->SetBodyState(BS_HIT);

	zVEC3 pfxPos;
	if (hitPosUsed) pfxPos = hitpos;
	else			pfxPos = vob->GetPositionWorld();
	
	//
	//	CODECHANGE [ROMAN]
	//
	oCItem*				pWeapon		= npc->GetWeapon();
	oCNpc::oSDescDamage	descDamage;

	if ( this->npc->GetWeaponMode() == NPC_WEAPON_FIST	) 	descDamage.enuModeWeapon	 = oETypeWeapon_Fist	;	
	if ( this->npc->GetWeaponMode() == NPC_WEAPON_DAG	)	descDamage.enuModeWeapon	|= oETypeWeapon_Melee	;
	if ( this->npc->GetWeaponMode() == NPC_WEAPON_1HS	)	descDamage.enuModeWeapon	|= oETypeWeapon_Melee	;
	if ( this->npc->GetWeaponMode() == NPC_WEAPON_2HS	)	descDamage.enuModeWeapon	|= oETypeWeapon_Melee	;
	if ( this->npc->GetWeaponMode() == NPC_WEAPON_BOW	)	descDamage.enuModeWeapon	|= oETypeWeapon_Range	;
	if ( this->npc->GetWeaponMode() == NPC_WEAPON_CBOW	)	descDamage.enuModeWeapon	|= oETypeWeapon_Range	;
	if ( this->npc->GetWeaponMode() == NPC_WEAPON_MAG	)	descDamage.enuModeWeapon	|= oETypeWeapon_Magic	;

	descDamage.pItemWeapon			= pWeapon																	;
	descDamage.pVobHit				= pWeapon																	;
	descDamage.pVobAttacker			= this->npc																	;
	descDamage.pNpcAttacker			= this->npc																	;
	descDamage.fDamageMultiplier	= this->npc->GetDamageMultiplier()											;
	descDamage.fDamageTotal			= (pWeapon)		? pWeapon->GetFullDamage ()	: this->npc->GetFullDamage  ()	;	::memcpy( descDamage.aryDamage, this->npc->damage, sizeof( this->npc->damage ) );
	descDamage.enuModeDamage		= (pWeapon)		? pWeapon->GetDamageTypes()	: this->npc->GetDamageMode	()	;
	descDamage.vecLocationHit		= (hitPosUsed)	? hitpos : vob->GetPositionWorld()							;

	descDamage.dwFieldsValid		= oCNpc::oEDamageDescFlag_Damage			
									| oCNpc::oEDamageDescFlag_DamageType
									| oCNpc::oEDamageDescFlag_WeaponType
									| oCNpc::oEDamageDescFlag_Attacker
									| oCNpc::oEDamageDescFlag_Npc
									| oCNpc::oEDamageDescFlag_Inflictor
									| oCNpc::oEDamageDescFlag_Weapon
									;
	if ( pWeapon )
	{
		pWeapon->GetDamages( descDamage.aryDamage );
	}

	oCNpc* pNpcVictim = zDYNAMIC_CAST< oCNpc > (vob);
	if	( pNpcVictim )	pNpcVictim->/*GetEM()->*/OnDamage( descDamage );
	else			  
	{
		zREAL fAdd = 0;

		if		(   descDamage.enuModeWeapon						== oETypeWeapon_Fist  ) fAdd = (zREAL) npc->GetAttribute( NPC_ATR_STRENGTH  );
		else if ( ( descDamage.enuModeWeapon & oETypeWeapon_Melee ) == oETypeWeapon_Melee ) fAdd = (zREAL) npc->GetAttribute( NPC_ATR_STRENGTH  );
		else if ( ( descDamage.enuModeWeapon & oETypeWeapon_Range ) == oETypeWeapon_Range ) fAdd = (zREAL) npc->GetAttribute( NPC_ATR_DEXTERITY );

		vob->GetEM()->OnDamage( pWeapon															, 
								 this->npc														, 
								descDamage.fDamageTotal * descDamage.fDamageMultiplier + fAdd	,
								descDamage.enuModeDamage										,
								descDamage.vecLocationHit										);
	}

	//
	//	CODECHANGE [ROMAN] END
	//

	//changed[dennis]
/*	oCItem* weapon = npc->GetWeapon();
	if( weapon )
	{
		 if( weapon->mainflag == NPC_WEAPON_BOW || weapon->mainflag == NPC_WEAPON_CBOW ) 
			 vob->GetEM()->OnDamage( weapon, 
									 npc, 
									 npc->GetAttribute( NPC_ATR_DEXTERITY ) + weapon->GetFullDamage() * npc->GetDamageMultiplier(),
									 weapon->GetDamageTypes(),
									 pfxPos
								   );

		 else 
			 vob->GetEM()->OnDamage( weapon, 
									 npc, 
									 npc->GetAttribute( NPC_ATR_STRENGTH ) + weapon->GetFullDamage() * npc->GetDamageMultiplier(), weapon->GetDamageTypes(), pfxPos );
	}
	//else faust
	else vob->GetEM()->OnDamage(NULL, npc, npc->GetAttribute(NPC_ATR_STRENGTH),npc->GetDefaultDamage(),pfxPos);
*/

	// *****************************
	// Sound
	// *****************************
	oCVob* obj = zDYNAMIC_CAST<oCVob>(vob);
	if (obj) 
	{
		// hier wird nur (!) der collisionsound CS_IAM aufgerufen -> böse
		// soll: 	
		// CS_IAM_ME_FL  (Beißen, Klauen)
		// CS_IAM_FL_FL  (Boxen)
		// CS_IAM_ME_FL  (Schwerttreffer)
		// CS_IAM_WO_FL  (Holzprügeltreffer)

		oTSndMaterial mat1,mat2;
		zCSoundManager::zTSndManMedium med1,med2;
		npc		-> GetSoundMaterial_MA	(med1,mat1,limbname);
		obj		-> GetSoundMaterial_AM	(med2,mat2,1);			
		zsndMan	-> StartAttackSound		(npc,med1,med2,mat1,mat2);
	};

	// *****************************
	// Logischer Sound
	// *****************************
	oCNpc::AssessFightSound_S(npc,npc->GetPositionWorld(),vob);
}


zBOOL oCAniCtrl_Human :: CheckMeleeWeaponHitsLevel(oCItem *a_pWeapon)
{
	// egal in welchem weapon mode kann hier getestet werden, ob die attack coll limbs hier den
	// statischen level berühren
	// vorsicht: innerhalb einer combo darf nur einmal ein collisionseffekt gestartet werden
	if (!canDoCollisionFX)														return FALSE; 
	if (IsInPostHit() || IsInCombo())											return FALSE;
	if (npc->GetHomeWorld() && npc->GetHomeWorld()->GetMasterFrameCtr() & 2)	return FALSE;

	zCList<zCVob::zTModelLimbColl> resCollList;
	zCVob::zTModelLimbColl *limbinfo;

	for (int i=0; i<ANI_HITLIMB_MAX; i++) 
	{
		if (hitlimb[i]) 
		{
			zVEC3		approxCollPos;
			zCMaterial *foundCollMaterial;

			npc -> CheckModelLimbCollisionLevel(hitlimb[i], TRUE, resCollList);

			if (resCollList.GetNumInList()!=0) 
			{
				limbinfo		  = resCollList.GetNextInList()->GetData();
				approxCollPos	  = limbinfo -> approxCollisionPos;
				foundCollMaterial = limbinfo -> hitMaterial;

				// Folgende Zeile ist unbedingt noetig, damit keine Mem-Leaks entstehen !!
				resCollList.DeleteListDatas();	

				// coll effekte starten (pfx/sound)
				zCSoundManager::zTSndManMedium	med1, med2;
				oTSndMaterial					mat1, mat2;

				npc		-> GetSoundMaterial_MA	( med1, mat1, "FIST" );
				
				med2 = zCSoundManager::zSND_MAN_MEDIUM_LEVEL;

				if (!foundCollMaterial) mat2 = SND_MAT_METAL;
				else 
				{
					switch (foundCollMaterial->GetMatGroup())
					{
					case zMAT_GROUP_METAL: mat2 = SND_MAT_METAL; break;
					case zMAT_GROUP_STONE: mat2 = SND_MAT_STONE; break;
					case zMAT_GROUP_WOOD:  mat2 = SND_MAT_WOOD;  break;
					case zMAT_GROUP_SNOW:  mat2 = SND_MAT_LEATHER; break;
					case zMAT_GROUP_EARTH: mat2 = SND_MAT_CLAY;  break;
					case zMAT_GROUP_WATER: mat2 = SND_MAT_GLAS;  break;
					default:			   mat2 = SND_MAT_STONE; break;
					}
				}

				//
				//	CREATE PARTICLE FX
				//
				zCModelNodeInst *rightHand = GetModel()->SearchNode ("ZS_RIGHTHAND");
				if (rightHand) 
				{
					zMATRIX4 trafoHandToWorld	= npc->trafoObjToWorld * GetModel()->GetTrafoNodeToModel (rightHand);
					zPOINT3	 slotpos			= trafoHandToWorld.GetTranslation();
					zBOOL inMove = npc->GetInMovement();

					//
					//	CODECHANGE [ROMAN]
					//
					//if ( npc	->GetWeaponMode() != NPC_WEAPON_FIST ) 
					{
						//
						//	COMPOSE MATERIAL NAME FROM WEAPON MATERIALS
						//
						zSTRING strMaterial		;
						zSTRING strMaterialSrc	= SndMaterialName[ mat1 ];
						zSTRING strMaterialDst	= SndMaterialName[ mat2 ];

						// vorher: altes system: mat der waffe mit berücksichtigt
						/*strMaterial = strMaterialSrc;

						if		( strMaterialSrc != strMaterialDst )		
							if	( strMaterialSrc  < strMaterialDst )	strMaterial = strMaterialSrc + "_" + strMaterialDst;
							else										strMaterial = strMaterialDst + "_" + strMaterialSrc;*/
						
						// nachher: nur das level material wird berücksichtigt, und aus CPFX_IAI_ genommen
						strMaterial = strMaterialDst;

						//
						//	COMPOSE PFX NAME FROM MATERIAL NAMES
						//
						zSTRING strNameFX;

						strNameFX  = "CPFX_IAI_";
						strNameFX += strMaterial;

						//
						//	START PROPER PFX
						//
						if (inMove) npc -> EndMovement	();
									this-> DoSparks		( slotpos, strNameFX );  
						if (inMove) npc	-> BeginMovement();
					}
					//
				}

				// Sound	
				zsndMan -> StartHitSound( npc, med1, med2, mat1, mat2 ,0 );
				canDoCollisionFX = FALSE;
				return TRUE;
			}
		}
	}

	return FALSE;
}



void oCAniCtrl_Human :: HitInterrupt()
{
	canEnableNextCombo	= FALSE;
	canDoCollisionFX	= FALSE;
	comboCanHit			= FALSE;
	endCombo			= TRUE;
	hitPosUsed			= FALSE;
	hitGraphical		= FALSE;
	lastHitAniFrame		= 0.0f;

	GetModel()->StopAni		(hitAniID);
	hitAniID			= zMDL_ANI_ID_ILLEGAL;
}

zBOOL oCAniCtrl_Human :: HitGraphical()
// Graphischer Check auf Treffer eines anderen Objektes
{
	// WeaponTrail an
	ShowWeaponTrail();
	
	// Positionskorrektur
	CorrectFightPosition();
	
	// Laufende Schlagani holen
	zCModelAniActive* hitAni = GetModel()->GetActiveAni(hitAniID);
	if (!hitAni) return FALSE;
	
	// Turns unterdrücken, falls in stopTurnNSC - Winkelbereich
	if (stopTurnVob) {
		
		zREAL azi,elev;
		npc->GetAngles(stopTurnVob,azi,elev);

		if (abs(azi)<90.0f) {
		
			int newStopTurnVobSign = GetStopTurnVobSign();
			if (stopTurnVobSign != newStopTurnVobSign) {
				// Vorzeichenwechsel bedeutet vorbeigerauscht
				GetModel()->StopAni	(hitAni);
				GetModel()->StartAni	(_s_walk);
				npc->SetHeadingYWorld(stopTurnVob->GetPositionWorld()); // [Moos] 20.12.00 Anpassung an Vob-Änderung
				return TRUE;
			};
			stopTurnVobSign = newStopTurnVobSign;
		}
	};

	// Treffer ab ca. 20% 
	if (GetModel()->GetProgressPercent(hitAniID)<0.3f) return FALSE;

	// Und ? Was getroffen ?			
	return (CheckHitTarget()!=NULL);
}

zBOOL oCAniCtrl_Human :: IsInPreHit	 ()
{
	// Laufende Schlagani holen
	zCModelAniActive* hitAni = GetModel()->GetActiveAni(hitAniID);
	if (!hitAni)		return FALSE;
	// Bei Drehschlägen gibt's kein PreHit
	if (hitGraphical)	return FALSE; 

	int hitAniFrame = hitAni->GetActFrame();
	return (hitAniFrame < comboInfo[comboNr].comboStartFrame);		
};

zBOOL oCAniCtrl_Human :: IsInPostHit ()
{
	return (!IsInPreHit() && !IsInCombo());
}

zBOOL oCAniCtrl_Human :: IsInCombo	 ()
{
	// Laufende Schlagani holen
	zCModelAniActive* hitAni = GetModel()->GetActiveAni(hitAniID);
	if (!hitAni) return FALSE;
	int hitAniFrame = hitAni->GetActFrame();
	return ((comboInfo[comboNr].comboStartFrame<=hitAniFrame) && (hitAniFrame<=comboInfo[comboNr].comboEndFrame));
};


void oCAniCtrl_Human :: FirstPersonDrawWeapon()
{
}

// ********************
// Paraden
// ********************

zSTRING oCAniCtrl_Human :: GetHitDirection()
{
	zCModelAniActive* hitAni = GetModel()->GetActiveAni(hitAniID);
	if (!hitAni) return "0";

	if (comboInfo[comboNr].comboDir == 0) return "0";

	return "0";
	
	return zSTRING(char(comboInfo[comboNr].comboDir));
};

zCModelAniActive* oCAniCtrl_Human :: IsParadeRunning()
{
//	zCModelAniActive* ani = GetLayerAni(1);
//	if (ani && (ani->GetAni()->GetAniName().Search("PARADE")>0)) return ani;

	zCModelAniActive* ani;
	for (int i=0; i<GetModel()->numActiveAnis; i++) 
	{
		ani = GetModel()->aniChannels[i];
		if (ani && (ani->GetAni()->GetAniName().Search("PARADE")>0)) return ani;
	}

	return NULL;
}

zBOOL oCAniCtrl_Human :: CanParade(oCNpc* enemy)
// Konnte der einfallende Schlag pariert werden ?
{
	if (!enemy) 
	{
		return FALSE;
	}

	zCModelAniActive* ani = IsParadeRunning();
	if (ani) 
	{
		//  winkel check. über gewissen grenzen hinaus kann der SC doch getroffen werden
		zREAL azi, elev;
		npc	   -> GetAngles (enemy->GetPositionWorld(),azi,elev);
		if (zAbs(int(azi))>90) 
		{
			return FALSE;
		}

		// fist attacks können bei monstern nicht mit waffen pariert werden (ausser jumpback-parade)
		if ( npc->IsHuman()										&& 
			 !enemy->IsHuman()									&&
			 ani->GetAni()->GetAniName().Search("JUMP")==-1		&&
			 enemy->GetWeaponMode()==NPC_WEAPON_FIST		) 
		{
			return FALSE;
		}

		// Jumpback pariert NUR, wenn NSC eine Nahkampfwaffe in der Hand hat
		if ( (ani->GetAni()->GetAniName().Search("JUMP")!=-1) && (npc->GetWeaponMode()!=NPC_WEAPON_1HS && npc->GetWeaponMode()!=NPC_WEAPON_2HS) ) 
		{
			return FALSE;
		}

		return TRUE;

		// Zielausrichtung ermitteln
		// In der <Safe-Region> (optimales Trefferframe/-bereich)der 
		// Parade kann der Parierende nicht getroffen werden, auch nicht 
		// von anderen Attacken, die evtl. weitere Gegner anbringen.
		if ((paradeBeginFrame==0.0f) && (paradeEndFrame==0.0f)) 
		{
			return TRUE;
		}
		zREAL curFrame = ani->GetActFrame();
		
		/*if (!zInRange(curFrame,paradeBeginFrame,paradeEndFrame))
		{
			//zERR_WARNING("C: cannot parade: reason: frame out of parade window");
		}*/

		return (zInRange(curFrame,paradeBeginFrame,paradeEndFrame));
	}
/*	else
	{
		zERR_WARNING("C: Cannot parade: reason: no parade ani running");
	}*/
	return FALSE;
}

void oCAniCtrl_Human :: StartParadeEffects(oCNpc* enemy)
{
	//
	//	GET MATERIALS
	//
	zCSoundManager::zTSndManMedium	med1, med2;
	oTSndMaterial					mat1, mat2;

	npc		-> GetSoundMaterial_MA	( med1, mat1, "FIST" );
	enemy	-> GetSoundMaterial_MA	( med2, mat2, "FIST" );			

	//
	//	CREATE PARTICLE FX
	//
	zCModelNodeInst *rightHand = GetModel()->SearchNode ("ZS_RIGHTHAND");
	if (rightHand) 
	{
		zMATRIX4 trafoHandToWorld	= npc->trafoObjToWorld * GetModel()->GetTrafoNodeToModel (rightHand);
		zPOINT3	 slotpos			= trafoHandToWorld.GetTranslation();
		zBOOL inMove = npc->GetInMovement();

		//
		//	CODECHANGE [ROMAN]
		//
		if ( npc	->GetWeaponMode() != NPC_WEAPON_FIST ) 
		if ( enemy	->GetWeaponMode() != NPC_WEAPON_FIST ) 
		{
			//
			//	COMPOSE MATERIAL NAME FROM WEAPON MATERIALS
			//
			zSTRING strMaterial		;
			zSTRING strMaterialSrc	= SndMaterialName[ mat1 ];
			zSTRING strMaterialDst	= SndMaterialName[ mat2 ];

			strMaterial = strMaterialSrc;

			if		( strMaterialSrc != strMaterialDst )		
				if	( strMaterialSrc  < strMaterialDst )	strMaterial = strMaterialSrc + "_" + strMaterialDst;
				else										strMaterial = strMaterialDst + "_" + strMaterialSrc;

			//
			//	COMPOSE PFX NAME FROM MATERIAL NAMES
			//
			zSTRING strNameFX;

			strNameFX  = "CPFX_IAI_";
			strNameFX += strMaterial;

			//
			//	START PROPER PFX
			//
			if (inMove) npc -> EndMovement	();
						this-> DoSparks		( slotpos, strNameFX );  
			if (inMove) npc	-> BeginMovement();
		}
		//
		//	CODECHANGE [ROMAN]
		//
	}

	// Kollision Sounds (Model attacks Model)
	// stand jetzt:  CS_IAI_ME_ME
	// soll: 
	//  CS_IAI_ME_ME  (Gefecht mit Schwert)
	//	CS_IAI_ME_WO  (Gefecht mit Holzprügel)
	zsndMan -> StartAttackSound( npc, med1, med2, mat1, mat2 );
}

/*
void oCAniCtrl_Human :: Hit ()
// Original Hit
{	
	// WeaponTrail an
	ShowWeaponTrail();
	
	// Positionskorrektur
	DoAniWithOffset();

	if ((!inhit) || (!hitani)) return;
/*
	// ** Wirkt Parade des Gegners ? **
	if ((npc->enemy) && (npc->enemy->GetAnictrl()->HasParaded(npc))) {
		// Ani zurückholen
		if (hitani->GetActFrame()>=optframe) {
			// a) HitAnimation ausschalten
			// b) Schlag-Ani zurückholen
			// hitani	-> SetDirection ( zMDL_ANIDIR_REVERSE );
			// Frame Check
			// zCView :: stdoutput -> Printwin("Parade Hit :" + zSTRING(hitani->GetActFrame()) + "\n");
			// Partikel Effekt
			zCModelNodeInst *rightHand = GetModel()->SearchNode ("ZS_RIGHTHAND");
			if (rightHand) {
				zMATRIX4 trafoHandToWorld	= npc->trafoObjToWorld * GetModel()->GetTrafoNodeToModel (rightHand);
				zPOINT3	 slotpos			= trafoHandToWorld.GetTranslation();
				npc    -> EndMovement();
				DoSparks (slotpos);  
				npc	   -> BeginMovement();
			}
			// Sound
			zCSoundManager::zTSndManMedium med1,med2;
			int mat1,mat2;
			npc -> GetSoundMaterial_MA			(med1,mat1,"FIST");
			npc -> enemy -> GetSoundMaterial_AM (med2,mat2,1);			
			zsndMan -> StartAttackSound(npc,med1,med2,mat1,mat2);
			// Schlag beendet
			inhit	= FALSE;
			hitani	= NULL;
		}
		return;
	}
*/

	// Zustazcheck,,,
	// if (optframe<=0) zerr.Report(zERR_WARN,-1,"U: ANI: Wrong optimal Frame found : "+zSTRING(optframe)); 
	// ** Check auf logischen Treffer **
	// Optimalen Frame erreicht, dann Kollision abfahren...
/*	zCModelAniActive* hAni = GetModel()->GetActiveAni(GetModel()->GetAniFromAniID(hitani));
	
	if (can_hit && targetVob && (hAni->GetActFrame()>=hitOptFrame[comboNr])) {
		// Safety : nochmal Range-Check :
		zREAL dist;
		if (npc->IsInFightRange(targetVob,dist)) {
			// *****************************
			// Treffer auf NSC
			// *****************************
			// Logisch wurde auf jeden Fall getroffen...
			// sonst waere "canhit" nicht auf TRUE
			if (!gr_hit) hitpos = targetVob->GetPositionWorld();
			oCItem* weapon		= npc->GetWeapon();
			int		damageTypes	= 0;
			zREAL	damage		= 0.0f;
			if (weapon)	{
				damage		= weapon->GetDamage();
				damageTypes	= weapon->GetDamageTypes();
			} else {
				// Faustkampf !
				damage		= npc->GetAttribute(NPC_ATR_STRENGTH);
			}
			targetVob -> GetEM() -> OnDamage (npc->GetWeapon(),npc,damage,damageTypes,hitpos);

			// *****************************
			// Sound
			// *****************************
			oCVob* obj = dynamic_cast<oCVob*>(targetVob);
			if (obj) {
				oTSndMaterial mat1,mat2;
				zCSoundManager::zTSndManMedium med1,med2;
				npc		-> GetSoundMaterial_MA	(med1,mat1,limbname);
				obj		-> GetSoundMaterial_AM	(med2,mat2,1);			
				zsndMan	-> StartAttackSound		(npc,med1,med2,mat1,mat2);
			};

			// *****************************
			// Logischer Sound
			// *****************************
			oCNpc::AssessFightSound_S(npc,npc->GetPositionWorld());
		};
		// Schlag beenden
		inhit	= FALSE;
		hitani	= zMDL_ANI_ID_ILLEGAL;
		return;
	}
}
*/

void oCAniCtrl_Human :: StrafeLeft()
{
	if (GetActionMode()!=ANI_ACTION_SWIM) {
		StopTurnAnis		();
		GetModel()->StartAni		(_t_strafel);
		npc->SetBodyState	(BS_WALK);
	}
}

void oCAniCtrl_Human :: StrafeRight()
{
	if (GetActionMode()!=ANI_ACTION_SWIM) {
		StopTurnAnis		();
		GetModel()->StartAni		(_t_strafer);
		npc->SetBodyState	(BS_WALK);
	}
}

int oCAniCtrl_Human :: GetFootPos()
// Ermittelt ob linker oder rechter Fuß gerade vorne ist
// 0 - keiner 
// 1 - Links
// 2 - Rechts
{
	if (GetModel()->IsAniActive(_s_walkl)) {
		float per = GetModel()->GetProgressPercent(_s_walkl);
		if (npc->GetWeaponMode()==NPC_WEAPON_NONE) {
			// Genaue Fussberechnung im Normalmodus
			if ((per>0.85f) || (per<0.15f)) return 1;	else 
			if ((per>0.35f) && (per<0.65f)) return 2;	
		} else {
			// Im Kampfmodus immer und sofort stoppbar
			if ((per>0.75) && (per<0.25))	return 1;	else
			return 2;
			//if ((per>0.25) && (per<0.75))	return 2;	
		}

	} else if (GetModel()->IsAniActive(_s_walkbl)) {
		float per = GetModel()->GetProgressPercent(_s_walkbl);
		if ((per>0.90f) || (per<0.10f)) return 1;	else
		if ((per>0.40f) && (per<0.60f)) return 2;
	}
	return 0;
}

void oCAniCtrl_Human :: PC_GoForward()
{
	// Genug Platz nach vorne ?
	if ((IsStanding() && !CheckEnoughSpaceMoveForward()) || CheckForceModelHalt(NULL)) {
		_Stand();

	} else {
		this->SetConfigDoWallSliding(TRUE);
		_Forward();
	}
}

void oCAniCtrl_Human :: PC_GoBackward()
{
	// Genug Platz nach hinten ?
	if (!CheckEnoughSpaceMoveBackward() || CheckForceModelHalt(NULL)) {
		_Stand();

	} else {
		this->SetConfigDoWallSliding(TRUE);
		_Backward();
	}
}

void oCAniCtrl_Human :: PC_JumpForward()
{
	static const int MIN_JUMP_SPACE = 400;

	if ((GetModel()->IsAniActive(_s_walkl)) && (walkmode==ANI_WALKMODE_RUN)) {
		// Genug Platz ?
		if (WallInFront(MIN_JUMP_SPACE)) {
			do_jump = FALSE;
			return;
		}
		// Von welchem Fuß springen ?
		int side = GetFootPos();
		if ((side==1) && _t_runl_2_jump) {
			// Links
			GetModel()->StartAni (_t_runl_2_jump);
			SetConfigDoWallSliding(FALSE);
			do_jump = FALSE;
			npc -> SetBodyState	(BS_JUMP);
		
		} if ((side==2) && _t_runr_2_jump) {
			// Rechts
			GetModel()->StartAni (_t_runr_2_jump);
			SetConfigDoWallSliding(FALSE);
			do_jump = FALSE;
			npc -> SetBodyState	(BS_JUMP);
		}	
	
	} else if (GetModel()->IsAniActive(_s_walk)) {
		
		JumpForward();
		npc -> SetBodyState	(BS_JUMP);
		do_jump = FALSE;
	}
}

zBOOL oCAniCtrl_Human :: CanJump(int level)
// 0 - Keiner
// 1 - JumpUpLow
// 2 - JumpupMid
// 3 - JumpUp
{
	// Anis vorhanden ?
	switch (level) {
	
		case 0	:	return (_t_stand_2_jump		!= zMDL_ANI_ID_ILLEGAL);
		case 1	:	return (t_stand_2_jumpuplow	!= zMDL_ANI_ID_ILLEGAL);
		case 2	:	return (t_stand_2_jumpupmid	!= zMDL_ANI_ID_ILLEGAL);
		case 3	:	return (_t_stand_2_jumpup	!= zMDL_ANI_ID_ILLEGAL);

	}
	return FALSE;
};

int oCAniCtrl_Human :: CanJumpLedge()
// 0 - Keiner
// 1 - JumpUpLow
// 2 - JumpupMid
// 3 - JumpUp
{
    // [Moos] 10.1.01 : in diesen Fällen wollen wir keinen neuen Test machen
    if (// (GetFoundLedge() || GetVelocity()[VY] > -10) &&  // Diese Zeile wäre wichtig, wenn wir an-kanten-festhalten haben wollten
        (GetModel()->GetIsFlying() || GetModel()->IsStateActive(_s_jumpup) || GetModel()->IsAniActive(_t_stand_2_jumpup)
         || GetModel()->IsAniActive(s_jumpupmid) || GetModel()->IsAniActive(s_jumpuplow)))
        return 0;

	zVEC3 ledgePoint;
	DetectClimbUpLedge (ledgePoint, TRUE);

	// Pruefen, ob Decke zu flach ist, um vernuenftig springen zu koennen
	// Im tiefen Wasser nur Sprung nach oben erlaubt.
	if (GetFoundLedge()) {
		// Hier nach Ziel-Hoehe klassifizieren: hi/mid/low -Jump
		zREAL ledgeYDist = ledgePoint[VY]-GetFeetY();
		if (ledgeYDist>config.zMV_YMAX_JUMPMID)	{
			return 3;
		} else if (ledgeYDist>config.zMV_YMAX_JUMPLOW)	{
			return 2;
		} else if (ledgeYDist>config.zMV_STEP_HEIGHT) {
			return 1;
		};
	};
	return 0;
}

int oCAniCtrl_Human :: JumpForward()
// 0 - Keiner
// 1 - JumpUpLow
// 2 - JumpupMid
// 3 - JumpUp
// 4 - Jump
{
	SetConfigDoWallSliding(FALSE);

	//zVEC3 ledgePoint;
	//GetFoundLedge() = DetectClimbUpLedge (ledgePoint, TRUE);
    CanJumpLedge(); // [Moos] besser so

	npc->SetCollDetStat(TRUE);
	// Pruefen, ob Decke zu flach ist, um vernuenftig springen zu koennen
	// Im tiefen Wasser nur Sprung nach oben erlaubt.
	if (GetFoundLedge()) {
		// Hier nach Ziel-Hoehe klassifizieren: hi/mid/low -Jump
		zREAL ledgeYDist = GetLastLedgePoint()[VY]-GetFeetY();
		if (ledgeYDist>config.zMV_YMAX_JUMPMID)	{
			GetModel()->StartAni		(_t_stand_2_jumpup);	
			npc->SetBodyState	(BS_JUMP);
			return 3;
		} else if (ledgeYDist>config.zMV_YMAX_JUMPLOW)	{
			GetModel()->StartAni		(t_stand_2_jumpupmid);	
			npc->SetBodyState	(BS_JUMP);
			return 2;
		} else if (ledgeYDist>config.zMV_STEP_HEIGHT) {
			GetModel()->StartAni		(t_stand_2_jumpuplow); 
			npc->SetBodyState	(BS_JUMP);
			return 1;
		} else {
			GetModel()->StartAni		(_t_stand_2_jump);
			npc->SetBodyState	(BS_JUMP);
			ClearFoundLedge();
			return 4;
		}
	
	} else if ((WallInFront(150)) || (GetWaterLevel()==1)) {
		if ((GetCeilingY()-GetHeadY())<config.zMV_JUMP_UP_MIN_CEIL) return FALSE;
		GetModel()	-> StartAni		(_t_stand_2_jumpup);
		npc		-> SetBodyState	(BS_JUMP);
		return 3;
	} else {
		GetModel()	-> StartAni		(_t_stand_2_jump);
		npc		-> SetBodyState	(BS_JUMP);
		return 4;
	}

	return 0;	
}

/* --------------------------------------------------------
	 zBOOL oCAniCtrl_Human :: Swim_CanClimbLedge()

	 6.12.2000	[HILDEBRANDT]
				Offensichtlichen Bug beseitigt: statt der lokalen Variable 'ledgepoint'
				wurde der Member 'ledgePoint' verwendet.

  --------------------------------------------------------- */

zBOOL oCAniCtrl_Human :: Swim_CanClimbLedge()
{
	zVEC3 ledgePointLocal;
	return (DetectClimbUpLedge (ledgePointLocal)) && (zAbs(ledgePointLocal[VY]-GetHeadY())<config.zMV_YMAX_SWIM_CLIMB_OUT);
}

/* --------------------------------------------------------
	 void oCAniCtrl_Human :: Swim_ClimbLedge()

	 6.12.2000	[HILDEBRANDT]
				Offensichtlichen Bug beseitigt: statt der lokalen Variable 'ledgepoint'
				wurde der Member 'ledgePoint' verwendet.

  --------------------------------------------------------- */

void oCAniCtrl_Human :: Swim_ClimbLedge()
{
	// am Beckenrand hochziehen
	zVEC3 ledgePointLocal;
	if (DetectClimbUpLedge (ledgePointLocal)) {
		Print ("found ledge");
		// Rand in Armreichweite ?
		if (zAbs(ledgePointLocal[VY]-GetHeadY())<config.zMV_YMAX_SWIM_CLIMB_OUT) {
//			AlignModelToLedge ("S_HANG");
			AlignModelToLedge ("T_SWIM_2_HANG");	
			walkmode = ANI_WALKMODE_RUN;
			SetWalkMode		(walkmode);
			SetActionMode	(ANI_ACTION_STAND);
		}
	};
}

zBOOL oCAniCtrl_Human :: CanWalkOnPoly(const zVEC3& polyNormal)
{	
	zREAL slope = polyNormal[VY]; 
	zClamp (slope, zREAL(-1.0F), zREAL(+1.0F)); 
	slope = zREAL(acos(slope));
	
	if (slope<M_PI)							// scheint noetig..
	if (slope>config.zMV_MAX_GROUND_ANGLE_WALK) 
	{ 
		// Poly gefunden, dass zum drauf gehen zu steil ist.
		return FALSE;		
	}
	return TRUE;
};


/*
void oCAniCtrl_Human :: Hit( zTModelAniID ani )
{
	if (ani!=zMDL_ANI_ID_ILLEGAL) {
		comboNr			= 0;
		comboMax		= 0;
		inhit			= TRUE;
		hitani			= ani;

		// Auto-Positionskorrektur bei Schlägen der NSCs
		if (npc->IsAPlayer())	targetVob = npc->GetFocusVob();
		else					targetVob = npc->GetEnemy();

		zREAL dist		= 0.0f;
		zREAL add		= 0.0f;
		zBOOL inRange	= npc->IsInFightRange(targetVob,dist);

		if (targetVob)	{
			// Entfernung und Kampfdistanz ermitteln
			zREAL fr1	= npc -> GetFightRange();
			add			= dist - fr1;
			// Maximal 50 cm
			if (add<-50) add = -50;	else
			if (add> 50) add =  50;						
		}
		// Animation + Offset starten
		add = 0;
		StartAniWithOffset(ani,add);
		
		// Ist das eine Ani-Comb, na dann anpassen, da !
		zCModelAni* cAni = GetModel()->GetAniFromAniID(ani);
		if (cAni && cAni->GetAniType()==zMDL_ANI_TYPE_COMB) {
			zREAL yk = 0.5;
			if (targetVob) {			
				// Höhenunterschied schnappen !
				zREAL diffy = targetVob->GetPositionWorld()[VY] - npc->GetPositionWorld()[VY] - 15;
				// Maximale Höhe 
				zTBBox3D box	= npc->GetBBox3DWorld();
				zREAL maxheight = (box.maxs[VY] - box.mins[VY]);// * 0.7;
				// Unterschied berechnen
				zREAL val = (diffy / maxheight) + 0.5;
				// invers
				yk = 1.0 - val;
			}
			// YK : 0.0 - ganz oben
			// YK : 0.5 - mitte
			// YK : 1.0 - ganz unten 
			// zerr.Message("YK:"+zSTRING(yk));
			GetModel()-> SetCombineAniXY(ani,0.5,yk);		// x-Value wird ignoriert				
		}

		GetModel() -> StartAni		(hitani);
		GetModel() -> AdvanceAnis	();
		GetFightLimbs			();

		// logischer Check auf Treffer
		if (inRange && npc->IsSameHeight(targetVob)) {
			// Jap, in Kampfreichweite
			can_hit	= TRUE;
			gr_hit	= FALSE;
		} else {
			can_hit	= FALSE;
		}
	}
}

void oCAniCtrl_Human :: SetInHit ( zBOOL f )
{
	inhit = f;
}

int oCAniCtrl_Human :: GetOptimalFrame()
{
	if (inhit && hitani) {
		return hitOptFrame[comboNr];
	}
	return 0;
}

int oCAniCtrl_Human :: GetEndHitFrame()
{
	if (inhit && hitani) {
		return hitEndFrame[comboNr];
	}
	return 0;
}

zTModelAniID oCAniCtrl_Human :: GetHitAni()
{
	if (inhit)	return hitani;
	else		return zMDL_ANI_ID_ILLEGAL;
}
*/
// **************************************************************************************
// Waffe ziehen, Waffe auswählen, Waffe wegstecken
// **************************************************************************************

zBOOL oCAniCtrl_Human :: DrawWeapon1(int what, zBOOL ignoreFistCondition, zBOOL showMagicCircle)
// Die Hand greift an die Waffe
// a) S_RUN - T_RUN_2_FIST - S_FIST
// TRUE; wenn Aktion beendet
{
	// [EDENFELD] Patch 1: Skelettmagier ziehen ihre Waffe nicht (ANI PROB???)
	if (GetModel()->IsAniActive(_s_walk) || (npc->GetTrueGuild()==NPC_GIL_SKELETON_MAGE))
	{
		int next,start;
 		if (what<=0)	start = NPC_WEAPON_NONE;
		else			start = what - 1;

		next 				=  npc->GetNextWeaponMode		(start,+1,ignoreFistCondition);
		zSTRING w			=  GetWeaponString				(next);
		zTModelAniID ani	=  GetModel()->GetAniIDFromAniName	("T_RUN_2_"+w);
		
		if ((npc->GetWeaponMode()==NPC_WEAPON_NONE) && (next>=NPC_WEAPON_MAG)) {
			oCMsgMagic* magMsg	 = zNEW( oCMsgMagic(oCMsgMagic::EV_OPEN,next));
			magMsg->removeSymbol = showMagicCircle;
			npc->GetEM()->OnMessage(magMsg,npc);
		}

		if (ani == zMDL_ANI_ID_ILLEGAL) 
		{
			zERR_WARNING("C: draw weapon ani " + zSTRING("T_RUN_2_"+w) + " not found!");
			return TRUE;
		}
		else							GetModel() -> StartAni (ani); 

		SetActionMode	(ANI_ACTION_CHOOSEWEAPON);
 		wmode			= WMODE_CHOOSE;
		wmode_last		= NPC_WEAPON_NONE;
		wmode_selected	= next;
		changeweapon	= TRUE;

	};

	return (GetModel() -> IsAniActive(s_weapon[wmode_selected]));
}

zBOOL oCAniCtrl_Human :: ChooseNextWeapon2(int dir)
// last = 0 -> letzte Waffe aktivieren
// ansonsten direction +1 oder -1
{
	int current	= wmode_selected;
	if (GetModel()->IsAniActive(s_weapon[current])) {
		int next			= npc -> GetNextWeaponMode(current,dir);
		zSTRING w			= "T_" + GetWeaponString(current)+ "_2_" + GetWeaponString(next);
		zTModelAniID ani	= GetModel() -> GetAniIDFromAniName(w);
		if (ani == zMDL_ANI_ID_ILLEGAL) 
		{
			zERR_WARNING("U: ANI: Weaponchoose-Ani not found : T_" + GetWeaponString(current)+ "_2_" + GetWeaponString(next));
			return TRUE;
		}
		else							GetModel() -> StartAni (ani);		
		changeweapon		= TRUE;
		wmode				= WMODE_CHOOSE;
		wmode_last			= wmode_selected;
		wmode_selected		= next;
		if (next >= NPC_WEAPON_MAG) {
			npc->GetEM()->OnMessage(zNEW( oCMsgMagic(oCMsgMagic::EV_OPEN,next,TRUE)),npc);
		} 
		if (current >= NPC_WEAPON_MAG) {
			npc->GetEM()->OnMessage(zNEW( oCMsgMagic(oCMsgMagic::EV_CLOSE,current,TRUE)),npc);
		}
		return TRUE;

	}
	return FALSE;	
}

zBOOL oCAniCtrl_Human :: DrawWeapon2()
// a) S_FIST - T_FIST_2_FISTSTAND
{
	if (IsStateAniActive(s_weapon[wmode_selected])) {
		zSTRING w		= GetWeaponString(wmode_selected);
		zSTRING aniname = "T_"+w+"_2_"+w+"RUN";
		zTModelAniID ani = GetModel() -> GetAniIDFromAniName(aniname);
		if (ani == zMDL_ANI_ID_ILLEGAL) 
		{
			zERR_WARNING("C: draw weapon2 ani " + aniname + " not found!");
			return TRUE;
		}
		if (ani) 
		{
			w = "S_"+w;
			if (walkmode==ANI_WALKMODE_RUN)		w+="RUN";	else
			if (walkmode==ANI_WALKMODE_WALK)	w+="WALK";	else
			if (walkmode==ANI_WALKMODE_SNEAK)	w+="SNEAK";	
			zTModelAniID ani2 = GetModel() -> GetAniIDFromAniName(w);
			SetNextAni(ani,ani2);
			GetModel()		-> StartAni		(ani);
			SetActionMode (ANI_ACTION_STAND);
			wmode		=  WMODE_STAND;
			wmode_last	=  wmode_selected;
		
		}
	}
	return (IsStateAniActive(_s_walk));
}

zBOOL oCAniCtrl_Human :: RemoveWeapon1 ()
// S_FISTRUN - T_FISTRUN_FIST - S_FIST
{
	if (GetModel()->IsAniActive(_s_walk)) {
		zSTRING w			=  GetWeaponString			(npc->GetWeaponMode());
		zTModelAniID ani =  GetModel()->GetAniIDFromAniName			("T_"+w+"RUN_2_"+w);
		if (ani == zMDL_ANI_ID_ILLEGAL)
		{
			zERR_WARNING(zSTRING("C: draw weapon2 ani ") + zSTRING("T_") + w +zSTRING("RUN_2_") + w + zSTRING(" not found!"));
			return TRUE;
		};
		if (ani) 
		{
			GetModel() -> StartAni (ani);
			changeweapon	= FALSE;
			wmode			= WMODE_CHOOSE;
			SetActionMode	(ANI_ACTION_CHOOSEWEAPON);
			wmode_last		= npc->GetWeaponMode();
		}
	};
	return (GetModel() -> IsAniActive(s_weapon[wmode_last]));
}

zBOOL oCAniCtrl_Human :: RemoveWeapon2 ()
// S_FIST - T_FIST_2_RUN
{
	// FIXEM : Netzwerk : wmode_selected wird nicht übertragen
	zBOOL doTransition = FALSE;
	//if (npc->IsSelfPlayer())	doTransition = GetModel() -> IsStateActive	(s_weapon[wmode_last]);
	//else						doTransition = GetModel() -> IsAniActive		(s_weapon[wmode_last]);
	
	doTransition = IsStateAniActive(s_weapon[wmode_last]);

	if (doTransition) {
		zSTRING w = "T_"+GetWeaponString(wmode_last)+"_2_RUN";
		zTModelAniID ani = GetModel()->GetAniIDFromAniName			(w);
		changeweapon		= FALSE;

		w = "S_";
		if (walkmode==ANI_WALKMODE_RUN)		w+="RUN";	else
		if (walkmode==ANI_WALKMODE_WALK)	w+="WALK";	else
		if (walkmode==ANI_WALKMODE_SNEAK)	w+="SNEAK";	
		zTModelAniID ani2 =  GetModel()->GetAniIDFromAniName (w);

		if (ani != zMDL_ANI_ID_ILLEGAL)		// [EDENFELD] 1.24a else zweig wurde nie aufgerufen
		{
			//SetNextAni	(ani, ani2);
  			StartAni		(ani,ani2);
		} else {
  			StartAni		(ani2);
		}

		wmode				= WMODE_NONE;
		SetActionMode		(ANI_ACTION_STAND);
		wmode_selected		= NPC_WEAPON_NONE;
	}
	return (IsStateAniActive(_s_walk));
}

void oCAniCtrl_Human :: StartUp( zCVob *inVob )
{
	//**************************************************//
	// START											//
	//**************************************************//

	Begin (inVob);

	//**************************************************//
	// FLOOR / CEILING MESSEN							//
	//**************************************************//

//	FindFloorCeiling();

	//**************************************************//
	// BODENHOEHE - KORREKTUR							//
	//**************************************************//

//	CorrectFloorHeight ();
}


/* ----------------------------------------------------------------------
	
     oCAniCtrl_Human :: LerpFeetToTarget ()

     wenn im Moment die Animation <ani_n> abgespielt wird und die Bewegung <ani_f> darauf folgt
     und den Abschluss bildet, dann sorgt diese Routine (bei kontinuierlichem Aufruf während
     der ganzen Bewegung) dafür, dass am Ende von <ani_f> die Füsse der Figur an <targetPos> stehen.

	 9.1.2001	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */


void oCAniCtrl_Human :: LerpFeetToTarget (zTModelAniID ani_n, zTModelAniID ani_f, const zVEC3 &targetPos){

    zERR_ASSERT(GetModel()->IsAniActive(ani_n));

    if (GetVob()->GetPhysicsEnabled())
        SetPhysicsEnabled(FALSE);

    zCModelAni *ani_final = GetModel()->GetAniFromAniID  (ani_f);
    zCModelAni *ani_now   = GetModel()->GetAniFromAniID  (ani_n);

    if (!ani_final) ani_final = ani_now;

	if (ani_now) {
        zREAL progress = GetModel()->GetProgressPercent(ani_n);    // wie weit sind wir schon in der Sprung-Ani?

        // hole aus der Animation die Bewegung, die der Root-Node ohnehin schon macht      	
        zVEC3 pos_final		= GetModel()->GetAniTrans    (ani_final, ani_final->GetNumFrames()-1,ani_final->GetRootNodeIndex());
		zVEC3 pos_now		= GetModel()->GetAniTransLerp(ani_now  , progress                   ,ani_now  ->GetRootNodeIndex());
		zVEC3 aniDelta		= pos_final - pos_now;
		aniDelta			= GetVob()->trafoObjToWorld.Rotate (aniDelta);

        // das ist die Bewegung, die unsere Füsse insgesamt noch zu machen haben
//		zVEC3 realDelta		= (targetPos - zVEC3(GetCenterPos()[VX], GetFeetY(), GetCenterPos()[VZ]));
		zVEC3 realDelta		= (targetPos - zVEC3(GetCenterPos()[VX], GetCenterPos()[VY] + GetModel()->GetBBox3DCollDet().mins[VY] - 20, GetCenterPos()[VZ]));

        // somit müssen wir diese Bewegung insgesamt dazufaken:
		zVEC3 jumpMidDiff	= realDelta - aniDelta;

        // dafür haben wir die folgende Zeit:
		zREAL jumpMidtime	= ani_now->GetAniTimeLength()*(1-progress);
        if (ani_final != ani_now)
            jumpMidtime    += ani_final->GetAniTimeLength();

        // wenn wir noch mehr als einen Frame Zeit haben, lerpe die Bewegung zum Ziel; ansonsten springe es direkt an.        

        if (jumpMidtime > ztimer.GetFrameTimeF())
        	GetVob()->Move( jumpMidDiff * (ztimer.GetFrameTimeF() / jumpMidtime) );
        else
        {
            GetVob()->Move( jumpMidDiff );

            if (ani_final == ani_now){
                SetConfigDoWallSliding(TRUE);
                ClearFoundLedge();
            }
        }

        if (GetFoundLedge())
            GetVob()->SetHeadingAtWorld(GetLastLedgeNormal());

        GetVob()->ResetXZRotationsWorld();
	}
}



/* ----------------------------------------------------------------------
	
     oCAniCtrl_Human :: RelaxHandToTarget ()

     analog zu LerpFeetToTarget; die Figur wird allerdings auch gedreht.
     Durch Erhöhen von <relax> kann man ausserdem den Eindruck, die Hände
     würden sich an targetPos festklammern, verstärken.

	 9.1.2001	[Moos]	
                erzeugt; muss noch implementiert werden
    10.1.2001   [Moos]
                implementiert

   ---------------------------------------------------------------------- */

void  oCAniCtrl_Human::RelaxHandToTarget  (const zVEC3 &tp, const zVEC3 &wa, zBOOL changeSpeed, zREAL relax){
//    return;
    //relax = 1;
    SetConfigDoWallSliding(FALSE);

    static zREAL putback = 5;
    zVEC3 targetPos = tp - GetVob()->GetAtVectorWorld() * putback;

    zVEC3 handPos   = GetHandPositionWorld();
    zVEC3 centerPos = GetVob()->GetPositionWorld();

    if (relax > 10)
        relax = 10;
    

    zREAL ft         = ztimer.GetFrameTimeF()*.001F * relax;

    if (ft > .2)
        ft = .2F;
        
    // der At-Vektor soll nicht "überhängen"
    zVEC3 wishAt = wa;
    if (wishAt[VY] > 0)
        wishAt[VY] = 0;
         
    zVEC3 centerToHandNorm = handPos - centerPos;
    centerToHandNorm.Normalize();

    zVEC3 centerToTargetNorm = targetPos - centerPos;
    zREAL centerToTargetLen = centerToTargetNorm.Length();
    centerToTargetNorm/=centerToTargetLen;
    
    if (centerToTargetLen > this->GetJumpUpHeight() * 1.5F)
        GetModel()->StartAni(_t_jumpup_2_falldn);


    zVEC3  rotateVec = (centerToHandNorm ^ centerToTargetNorm) + zVEC3(0, .3F * (GetVob()->GetAtVectorWorld() ^ wishAt)[VY], 0);
    //zVEC3  rotateVec = (centerToHandNorm ^ centerToTargetNorm) + .3F * (GetVob()->GetAtVectorWorld() ^ wishAt);
    //    rotateVec *= weight_new;

    /*
    zCQuat q (rotateVec[VX], rotateVec[VY], rotateVec[VZ], 1);
    q.Normalize();

    zMAT3 rot;
    q.QuatToMatrix3(rot);
    */

    zREAL ra = rotateVec.Length();

  
    if (ra > 0)
    {
        rotateVec *= 1/ra;
        GetVob()->RotateWorld(rotateVec, Alg_Rad2Deg(ra) * .5 * (1 - (1/ (1 + ft * 5))));
    }


//    GetVob()->SetHeadingAtWorld(wishAt);
    if (changeSpeed)
    {
        GetVob()->EndMovement();
        GetVob()->BeginMovement();

        handPos   = GetHandPositionWorld();
        //handPos = centerPos + (rot * (handPos - centerPos));

        if (!GetVob()->GetPhysicsEnabled())   
            SetPhysicsEnabled(TRUE);
    
    
        zCRigidBody *body = GetVob()->GetRigidBody();


        zVEC3 v = GetVob()->GetVelocity();
        v -= (v * centerToTargetNorm) * centerToTargetNorm;
        v /= 1+ft;
        body->SetVelocity(v);

/*
        relax *= 10;
        if (relax > 10)
            relax = 10;
*/

        zVEC3 ploepp    = targetPos - handPos;
        zVEC3 ploepPerp = (ploepp * centerToTargetNorm) * centerToTargetNorm;
        zVEC3 ploepPar  = ploepp - ploepPerp;

  //      if (ploepPar.Length2() > 25)
  //          ploepPar  = 0;
  //      else
        ploepPar *= (1 - 1/(1 + ft * ploepPar.Length2() *.1));

        ploepp = ploepPar + ploepPerp;

        GetVob()->Move(ploepp);
        centerPos += ploepp;

        zVEC3 a(0,0,0); //- relax * (2 * v + relax * (handPos - targetPos));

        zREAL gfak = 2;

        if (body->GetGravityEnabled())
            a += gfak * (zVEC3(0,981,0) * centerToTargetNorm) * centerToTargetNorm - zVEC3(0,(gfak - 1 )* 981,0);

        static const zREAL mindist = 40;
        if (GetWorld()->TraceRayNearestHit(centerPos, GetVob()->GetAtVectorWorld() * mindist, GetVob(), 0))
        {
            zREAL dist    = (GetWorld()->traceRayReport.foundIntersection - centerPos).Length();
            zVEC3 holdoff = (dist - mindist - 5) * GetVob()->GetAtVectorWorld();
            holdoff      -= (v * GetVob()->GetAtVectorWorld()) * GetVob()->GetAtVectorWorld()*.2F;
            holdoff      -= (holdoff * centerToTargetNorm) * centerToTargetNorm;
            a            += holdoff * relax * 10;
        }

        body->ApplyForce(a * body->GetMass(), handPos);
    }
}


/* ----------------------------------------------------------------------
	
     oCAniCtrl_Human :: CheckSpecialStates ()


	 9.1.2001	[Moos]	
                baumeln eingebaut und Sprünge verbessert

   ---------------------------------------------------------------------- */



void oCAniCtrl_Human :: CheckSpecialStates()
{
	//////////////////////////////
	//		S_JUMP_UP			//
	//////////////////////////////
	
//	if (GetModel()->IsStateActive("S_JUMPUP")) { 
	if (GetModel()->IsStateActive(_s_jumpup)) { 
		// Zustand gerade gestartet => Physik anschmeissen
		if (!GetVob()->GetPhysicsEnabled()) { 
			Print ("ph on");
//				SetCDStat						(FALSE);
			SetPhysicsEnabled				(TRUE);
            SetConfigDoWallSliding          (FALSE);

            zREAL jumpUpImp = config.zMV_FORCE_JUMP_UP;
            if (GetFoundLedge())
            { 
                jumpUpImp = sqrt( fabs(( GetLastLedgePoint()[VY] - GetCenterPos()[VY] ) * 981 * 2)) * GetVob()->GetRigidBody()->GetMass();
                if (jumpUpImp > config.zMV_FORCE_JUMP_UP)
                    jumpUpImp = config.zMV_FORCE_JUMP_UP;
            }

            zVEC3 jumpImp = zVEC3(0,config.zMV_FORCE_JUMP_UP,0);
            if (GetFoundLedge())
            {
                zVEC3 jumpDirNorm = GetLastLedgePoint() - GetCenterPos();
                jumpDirNorm.Normalize();

                jumpImp = jumpDirNorm * (jumpDirNorm * jumpImp);   // [Moos] 10.1.01 Springe immer in Richtung des Ziels
                jumpImp[VY] = jumpUpImp;

                // und richte dich an der Kante aus
                zVEC3 n = GetLastLedgeNormal();
                n[VY] = 0;
                zREAL len = n.Length();
                if (len > 0)
                    GetVob()->SetHeadingAtWorld(n/len);
            }

			GetVob()->GetRigidBody()->ApplyImpulseCM(jumpImp);      // [Moos] 11.1.01 Statt ApplyForce. Ist begriffsmässig besser. behandelt auch das [FIXME: einheiten ??]: es sind .01 Newton-Sekunden.
			//GetVob()->SetPositionWorld			(GetCenterPos()); 
			goto leaveJUMP_UP;											// muss, er darf nicht _sofot_ auf Landung pruefen
		}; 
		// Hoechster Punkt der Flugbahn erreicht ? -> T_JUMPUP_2_FALLDN
		if (GetVelocity()[VY]<0) {
			GetModel()->StartAni(_t_jumpup_2_falldn);
				//"T_JUMPUP_2_FALLDN");
		}

		// Landung einleiten ?
		if (((GetFeetY()<=GetFloorY()) && (GetVelocity()[VY]<0)) || GetFeetY() <= GetFloorY() - 20) {
			Print ("land ");
			GetModel()->StartAni					("T_JUMPUP_2_FALLDN");

			SetPhysicsEnabled				(FALSE);
            SetConfigDoWallSliding          (TRUE);

			AlignToFloor					(GetFloorY());
            GetVob()->ResetXZRotationsWorld(); // [Moos] 10.1.01 aufrichten, falls der npc (z.B. durch Kollisionen) umgeschubst wurde
			goto leaveJUMP_UP;
		};
		// im Sprung Decke gestossen ?
		if (GetVelocity()[VY]>0)
		if ((GetHeadY()-GetCeilingY())>0) {
			Print ("ceil");
			// abrupt halten, exakte Korrektur, dann wirkt aber wieder grav
			GetVob()->GetRigidBody()->StopTranslation	();
			GetVob()->MoveLocal						(0, -(GetHeadY()-GetCeilingY()) -4,0);
		};
		// An Ledge haengen ?
		if (GetFoundLedge()) {
            RelaxHandToTarget(GetLastLedgePoint(), GetLastLedgeNormal(), FALSE, .5F);
//			if (GetVelocity()[VY]>=0)
			if ((GetHeadY()-this->GetLastLedgePoint()[VY])>0) {
				Print ("ledge2");
				//AlignModelToLedge ("T_JUMPUP_2_HANG");

				GetModel()->StartAni("T_JUMPUP_2_HANG", zCModel::zMDL_STARTANI_FORCE);
                GetVob()->GetRigidBody()->SetVelocity(zVEC3(0,0,0));
                SetPhysicsEnabled(TRUE); // [Moos]
			};
		};
leaveJUMP_UP:;
	}

	//////////////////////////////
	//		S_STAND				//
	//////////////////////////////

	// in meiner Proc "Movement"


	//////////////////////////////
	//		S_HANG				//
	//////////////////////////////

    if (GetFoundLedge() && (GetModel()->IsAniActive(s_hang) || GetModel()->IsAniActive("T_JUMPUP_2_HANG")))
        RelaxHandToTarget(GetLastLedgePoint(), GetLastLedgeNormal(), TRUE, 4);    

	//////////////////////////////
	//		T_HANG_2_STAND  	//
	//////////////////////////////

	if (GetFoundLedge() && GetModel()->IsAniActive(t_hang_2_stand))
        LerpFeetToTarget(t_hang_2_stand, t_hang_2_stand, GetLastLedgePoint() + GetLastLedgeCont() * GetLastLedgeMaxMoveForward());

	//////////////////////////////
	//		T_STAND_2_JUMP		//
	//////////////////////////////

//	if (GetModel()->IsAniActive("T_STAND_2_JUMP")) {
	if ((GetModel()->IsAniActive(_t_stand_2_jump)) || (GetModel()->IsAniActive(_t_runr_2_jump)) || (GetModel()->IsAniActive(_t_runl_2_jump))) {
        zBOOL hitFloor = FALSE;

	    if (GetAboveFloor()<0){
            npc->SetPositionWorld(npc->GetNewTrafoObjToWorld().GetTranslation() - zVEC3(0, GetAboveFloor(), 0));
            hitFloor = TRUE;
        }

		// Sprung nach vorne (Anlauf & Flugphase, bis zum Loop-Frame)

		// Landung einleiten ?
		if ((GetWaterLevel()==2) && (GetFeetY()<=GetWaterY())) {
			// Landung auf Wasser
			StartPhysicsWithVel		();
			GetModel()->StartAni			("T_JUMP_2_FALLDN");
		} else
        {
			zTModelAniID ani= -1;
            if (GetModel()->IsAniActive(_t_stand_2_jump)) ani = _t_stand_2_jump;
//            if (GetModel()->IsAniActive(_t_runr_2_jump )) ani = _t_runr_2_jump;
//            if (GetModel()->IsAniActive(_t_runl_2_jump )) ani = _t_runl_2_jump;
     
            if (ani > 0)
            {
			    zREAL perc = GetModel()->GetProgressPercent(ani);
			    if (hitFloor)
                {
				    if (GetVelocity()[VY]<0)
                    {
					    if (perc>0.7)
                        {
						    LandAndStartAni	(GetModel()->GetAniFromAniID(t_jump_2_stand));
						    //"T_JUMP_2_STAMD");
						    //LandAndStartAni	("T_JUMP_2_STAMD");
					    };
				    };
				    GetVob()->SetPositionWorld  (GetCenterPos());  
			    };
            };
//			if (perc>0.7)
//			if ((GetAboveFloor()<=0) && (GetVelocity()[VY]<0)) {
//				LandAndStartAni	(t_jump_2_stand);
//			};
        
		};
	}


    ////////////////////////////////


	////////////////////////////////
	//		S_JUMPUPMID			  //
	////////////////////////////////

	if (GetModel()->IsAniActive(t_stand_2_jumpupmid)) {
//		jumpLowMidPass	= 0;
		SetCDStat (FALSE);									// Dieses ist eine kritische Ani (Interrupt-Anis nicht erlaubt)
	} else
	if (GetModel()->IsAniActive(s_jumpupmid)) {

    // BEGIN CODECHANGE [MOOS] 8.1.01
        if (GetFoundLedge())
            LerpFeetToTarget(s_jumpupmid, t_jumpupmid_2_stand, GetLastLedgePoint());

        /*

        // [Moos] Alte version

		if (jumpLowMidPass!=1) {

			// hier wird versucht die Y-Hoehe aus den Anis zu ermitteln, die der Sprung als Default überwindet
			zCModelAni *ani1= GetModel()->GetAniFromAniID(t_jumpupmid_2_stand);
			zCModelAni *ani2= GetModel()->GetAniFromAniID(t_stand_2_jumpupmid);
			if (ani1 && ani2) {
				zVEC3 y1			= GetModel()->GetAniTrans(ani1, ani1->GetNumFrames()-1,ani1->GetRootNodeIndex());
				zVEC3 y2			= GetModel()->GetAniTrans(ani2, 0,ani2->GetRootNodeIndex());
				zVEC3 aniDelta		= y1-y2;
				aniDelta			= GetVob()->trafo.Rotate (aniDelta);
				zVEC3 realDelta		= (this->GetLastLedgePoint()- zVEC3(GetCenterPos()[VX], GetFloorY(), GetCenterPos()[VZ]));
//				zVEC3 realDeltaNorm	= realDelta;	realDeltaNorm.NormalizeApprox();
//				realDeltaNorm[VY]	= 0;
//				zREAL offsetDist	= (this->GetModel()->GetBBox3DLocalFixed().maxs[VZ]-this->GetModel()->GetBBox3DLocalFixed().mins[VZ]) * zREAL(0.5F);
//				realDelta			= realDelta + realDeltaNorm * zREAL(35.0F);
				realDelta[VX]		*= zREAL(1.4F);
				realDelta[VZ]		*= zREAL(1.4F);
				zVEC3 jumpMidDiff	= aniDelta - realDelta;
				zREAL jumpMidtime	= GetModel()->GetAniFromAniName("S_JUMPUPMID")->GetAniTimeLength();
				jumpLowMidVel		= -(jumpMidDiff / jumpMidtime);
			};
			jumpLowMidPass		= 1;

		
		GetVob()->Move (jumpLowMidVel);
            */
    // END CODECHANGE [MOOS]

	} else
	if (GetModel()->IsStateActive(t_jumpupmid_2_stand)) { 

        if (GetFoundLedge())
            LerpFeetToTarget(t_jumpupmid_2_stand, t_jumpupmid_2_stand, GetLastLedgePoint() + GetLastLedgeCont() * GetLastLedgeMaxMoveForward());

//		if (jumpLowMidPass==1) {
//			GetVob()->Move (ledgePoint - GetHandPositionWorld());
//			GetVob()->SetHeadingAt	(ledgeNormal);
//			jumpLowMidPass=2;
//		};
		// NachfolgeAni setzen
		SetNextAni(t_jumpupmid_2_stand,_s_walk);
	};
 
	////////////////////////////////
	//		S_JUMPUPLOW			  //
	////////////////////////////////

	if (GetModel()->IsAniActive(t_stand_2_jumpuplow)) {
//		jumpLowMidPass	= 0;
		SetCDStat (FALSE);									// Dieses ist eine kritische Ani (Interrupt-Anis nicht erlaubt)
	} else



	if (GetModel()->IsAniActive(s_jumpuplow)) {
	//	if (jumpLowMidPass!=1) {
			// hier wird versucht die Y-Hoehe aus den Anis zu ermitteln, die der Sprung als Default überwindet
        
        if (GetFoundLedge())
            LerpFeetToTarget(s_jumpuplow, t_jumpuplow_2_stand, GetLastLedgePoint());

//#else
  /*
    // alte Version

		if (jumpLowMidPass!=1) {
			// hier wird versucht die Y-Hoehe aus den Anis zu ermitteln, die der Sprung als Default überwindet
			zCModelAni *ani1= GetModel()->GetAniFromAniID(t_jumpuplow_2_stand);
			zCModelAni *ani2= GetModel()->GetAniFromAniID(t_stand_2_jumpuplow);
			if (ani1 && ani2) {
				zVEC3 y1			= GetModel()->GetAniTrans(ani1, ani1->GetNumFrames()-1,ani1->GetRootNodeIndex());
				zVEC3 y2			= GetModel()->GetAniTrans(ani2, 0,ani2->GetRootNodeIndex());
				zVEC3 aniDelta		= y1-y2;
				aniDelta			= GetVob()->trafo.Rotate (aniDelta);
				zVEC3 realDelta		= (this->GetLastLedgePoint()- zVEC3(GetCenterPos()[VX], GetFloorY(), GetCenterPos()[VZ]));
//				zVEC3 realDeltaNorm	= realDelta;	realDeltaNorm.NormalizeApprox();
//				realDeltaNorm[VY]	= 0;
//				realDelta			= realDelta + realDeltaNorm * zREAL(35.0F);
				realDelta[VX]		*= zREAL(1.4F);
				realDelta[VZ]		*= zREAL(1.4F);
				zVEC3 jumpMidDiff	= aniDelta - realDelta;
				zREAL jumpMidtime	= GetModel()->GetAniFromAniName("S_JUMPUPLOW")->GetAniTimeLength();
				jumpLowMidVel		= -(jumpMidDiff / jumpMidtime);
			};
			jumpLowMidPass		= 1;
		}
		GetVob()->Move (ztimer.GetFrameTimeF() * jumpLowMidVel);
*/
//#endif

// END CODECHANGE [MOOS]

    } else

	if (GetModel()->IsStateActive(t_jumpuplow_2_stand)) {

        if (GetFoundLedge())
            LerpFeetToTarget(t_jumpuplow_2_stand, t_jumpuplow_2_stand, GetLastLedgePoint() + GetLastLedgeCont() * GetLastLedgeMaxMoveForward());

//		if (jumpLowMidPass==1) {
			//GetVob()->Move			(ledgePoint - GetFeetPositionWorld());
			//GetVob()->SetHeadingAt	(ledgeNormal);
//			jumpLowMidPass=2;
			//SetWalkMode(ANI_WALKMODE_RUN);
//		};
		// NachfolgeAni setzen
		SetNextAni(t_jumpupmid_2_stand,_s_walk);
	}

	// S_JUMP in Proc Movement, da dort auf Tasten reagiert werden muss
	// allerdings muss diese Funktion bei NSC durch den Aufruf von 
	// Checkjump erstetzt werden
	const zVALUE ANI_FALLDAMAGE_HEIGHT = 350.0f;

	if (GetModel()->IsAniActive(_s_jump) && GetModel()->GetIsFlying()) {
		//zCView::StdPrintwin("Dist:"+zSTRING(GetFallDownDistanceY())+"\n");
		if (GetFallDownDistanceY()>=ANI_FALLDAMAGE_HEIGHT) {
			GetModel()->StartAni(s_falldn);
		}
	}

	//////////////////////////////
	//	  CHECK_FALL_STATES		//
	//////////////////////////////
	
	else CheckFallStates();

	// situations abhängiges model smooth root node
	if (!npc->IsAniMessageRunning())
	{
		int bs = npc->GetBodyState();
		if ( bs==BS_ITEMINTERACT || bs==BS_MOBINTERACT || bs==BS_MOBINTERACT_INTERRUPT) 
			  GetModel()->SetSmoothRootNode(FALSE);
		else  GetModel()->SetSmoothRootNode(TRUE);
	}

}

void oCAniCtrl_Human :: CheckJump()
// S_JUMP in Proc Movement, da dort auf Tasten reagiert werden muss
// allerdings muss diese Funktion bei NSC durch den Aufruf von 
// Checkjump erstetzt werden
{
	if (GetModel()->IsAniActive(_s_jump)) {
		// Sprung nach vorne (letzter Loop-Frame)		// Landung einleiten ?
		if ((GetWaterLevel()==2) && (GetFeetY()<=GetWaterY())) {
			// Landung auf Wasser
			StartPhysicsWithVel		();
			GetModel()->StartAni("T_JUMP_2_FALLDN");
		} else if (GetAboveFloor()<=0) {
				LandAndStartAni (GetModel()->GetAniFromAniID(t_jump_2_stand));
				SetNextAni(t_jump_2_stand,_s_walk);

		} else {
			// wird gerade losgesprungen ? => Physik anschmeissen
			if (!GetVob()->GetPhysicsEnabled()) {
				GetVob()->SetPhysicsEnabled			(TRUE);
				GetVob()->GetRigidBody()->SetVelocity	(GetVelocity()*1.0);  
			};
		};
	} 
}

void oCAniCtrl_Human :: StartFallDownAni () 
{
	if (GetWaterLevel()==1) {
		if ((GetActionMode()==ANI_ACTION_SWIM) || (GetActionMode()==ANI_ACTION_WATERWALK)) return;
	}
	if (! ( npc	 ->IsUnconscious()
		 ||	GetModel()->IsAniActive	("T_FALLDN_2_STAND") 
		 || GetModel()->IsAniActive	("T_DEAD") 
		 || GetModel()->IsAniActive	("T_DEADB") 
		 || GetModel()->IsAniActive	("S_DEAD") 
		 || GetModel()->IsAniActive	("S_DEADB") ) ) 
		GetModel()->StartAni ("S_FALLDN");
};


void oCAniCtrl_Human :: HackNPCToSwim()
{	
	// folgende if abfrage fixt defect 109 "über wasser laufen" (Gothic 2) -> Hack
	if (GetWaterY()>GetFeetY() && GetHeadY()>GetWaterY() && 
		(GetModel()->IsAniActive(zSTRING("S_RUN")) || 
		 GetModel()->IsAniActive(zSTRING("S_RUNL"))||
		 GetModel()->IsAniActive(zSTRING("S_WALKL"))) )
	{
		npc->SetPositionWorld(npc->GetPositionWorld()+zVEC3(0,50,0));
	}
	
	if (npc->GetHomeWorld()->TraceRayNearestHit(npc->GetPositionWorld(), zVEC3(0,+100000,0), npc, zTRACERAY_POLY_TEST_WATER|zTRACERAY_STAT_POLY|zTRACERAY_VOB_IGNORE_NO_CD_DYN|zTRACERAY_VOB_IGNORE_CHARACTER))
	{
		zBOOL oldCollDyn = npc->GetCollDetDyn();
		zBOOL oldCollStat= npc->GetCollDetStat();
		npc->SetCollDet(FALSE);

		npc->SetPositionWorld(npc->GetHomeWorld()->traceRayReport.foundIntersection+zVEC3(0,5,0));
		GetModel()->StopAni (s_fall);
		GetModel()->StopAni (s_fallb);
		GetModel()->StopAni (s_fallen);
		GetModel()->StopAni (s_fallenb);
		GetModel()->StopAni (s_falldn);

		GetModel()->StartAni(t_divef_2_swim);	// T_FALL_2_DIVE

		npc->SetCollDetDyn (oldCollDyn );
		npc->SetCollDetStat(oldCollStat);

		SetWalkMode		(ANI_WALKMODE_SWIM);
		SetActionMode	(ANI_ACTION_SWIM);

	}
};

/* --------------------------------------------------------
	 oCAniCtrl_Human :: CheckFallStates()

	 19.08.2000   [DENNIS]
			Codeblock **1 neu

  --------------------------------------------------------- */
void oCAniCtrl_Human :: CheckFallStates()
// Fall-Stadien betrachten -> Anis wechseln -> Fallschaden betrachten
{
//	const zVALUE ANI_FALLDAMAGE_HEIGHT = 350.0f;

	// +3+ |U-0895| FallDn/Fall/FallB: Sobald eine Figur in "s_FallDn" wechselt sollte 
	// sofort getestet werden, ob der Sturz zu tief sein wird um auf den Füßen zu landen. 
	// Dann sollte von "s_FallDn" möglichst schnell nach "s_Fall" bzw. "s_FallB" 
	// gewechselt werden, und nicht erst nach Xm Falltiefe.

	if (!GetModel()->GetIsFlying()) {
		if ((GetWaterLevel()==2) && (GetActionMode()!=ANI_ACTION_SWIM) && (GetActionMode()!=ANI_ACTION_DIVE)) 
		{
			#ifdef E3_NOWATERDIVE
			HackNPCToSwim();
			return;
			#else
		
			// Codechange [Ulf] 17-01-01 : 
			// Hier fallen starten, wenn Model Fuesse unter Wasser hat und WaterLevel == 2 (ausser beim Fallen)
			npc->SetPhysicsEnabled(TRUE);
			if (npc->GetRigidBody()) npc->GetRigidBody()->SetGravityEnabled(TRUE);
			this->StartFallDownAni();
			#endif
		}
		return;
	}

	if (GetModel()->IsStateActive(s_falldn)) {
		
		npc -> SetBodyState(BS_FALL);	
		//npc -> SetTorchAni(FALSE);

		// Auf Lande-Condition checken
		if (GetWaterLevel()==2) {
			if (GetHeadY()<GetWaterY()) 
			{
				#ifdef E3_NOWATERDIVE
				HackNPCToSwim();
				#else
				SetPhysicsEnabled		(FALSE);
				GetModel()->StartAni			("T_FALLDN_2_DIVE");	// T_FALL_2_DIVE
				// Swim - Mode on
				SetWalkMode		(ANI_WALKMODE_DIVE);
				SetActionMode	(ANI_ACTION_DIVE);
				#endif
			}
/*//**1
		} else if (GetWaterLevel()==1) {
			if (GetHeadY()<GetWaterY()) {
				SetPhysicsEnabled		(FALSE);
				GetModel()->StartAni			("WALKWL");
			}
//**1		
*/ 		} else if (GetAboveFloor()<zMV_LAND_HEIGHT) { 
			// akzeptable Hoehendifferenz => Model-Hoehe stumpf korrigieren
			zTModelAniID nextAni	= zMDL_ANI_ID_ILLEGAL;
			zTModelAniID ani		= zMDL_ANI_ID_ILLEGAL; // = GetModel() -> GetAniIDFromAniName("T_FALLDN_2_STAND");
			if (GetWaterLevel()==1)	{
				SetWalkMode		(ANI_WALKMODE_WATER);
				SetActionMode	(ANI_ACTION_WATERWALK);
				ani		= GetModel() -> GetAniIDFromAniName("T_FALLDN_2_STAND");
				nextAni = _s_walk;
			} else if (GetWaterLevel()==0) {
				ani		= GetModel() -> GetAniIDFromAniName("T_FALLDN_2_STAND");
				nextAni = _s_walk;
			} else {
				ani		= GetModel() -> GetAniIDFromAniName("T_FALLDN_2_STAND");
				nextAni = _s_walk;
			}	
			LandAndStartAni	(GetModel()->GetAniFromAniID(ani));
			if (nextAni!=zMDL_ANI_ID_ILLEGAL) SetNextAni(ani, nextAni);
		
		} else {
			const zREAL ANI_FALL_GRABSPACE = 200.0f;
			if (GetFallDownDistanceY()>=ANI_FALL_GRABSPACE) {
				const zVEC3 down(0,-(npc->GetFallDownHeight()-ANI_FALL_GRABSPACE),0);
				zVEC3 pos = npc -> GetPositionWorld(); pos[VY] = GetFeetY();
				if (!GetWorld()->TraceRayNearestHit (pos, down, npc, zTRACERAY_VOB_IGNORE)) {
					// Kein Hit, dann andere States starten
					zVALUE dot = GetVob()->GetAtVectorWorld() * GetVelocity();
					zTModelAniID ani = zMDL_ANI_ID_ILLEGAL;
					if (dot>=0) ani = GetModel()->GetAniIDFromAniName("T_FALLDN_2_FALL");	//T_FALLDN_2_FALL");
					else		ani = GetModel()->GetAniIDFromAniName("T_FALLDN_2_FALLB");	//T_FALLDN_2_FALLB");				
					if (ani!=zMDL_ANI_ID_ILLEGAL) {
						zCModelAni* cAni = GetModel()->GetAniFromAniID(ani);
						if (cAni) cAni->SetFlags("MF");
						GetModel()->StartAni(cAni);
					}
				}
			}
		}
	
	} else if (GetModel()->IsStateActive(s_fall) || GetModel()->IsStateActive(s_fallb)) {

		if ((GetWaterLevel()==2) && (GetHeadY()<GetWaterY())) 
		{
			#ifdef E3_NOWATERDIVE
			HackNPCToSwim();
			#else
			SetPhysicsEnabled		(FALSE);
			if (GetModel()->IsAniActive	(s_fall))	GetModel()->StartAni	("T_FALL_2_DIVE");
			else								GetModel()->StartAni	("T_FALLB_2_DIVE");		// T_FALL_2_DIVE
			SetWalkMode		(ANI_WALKMODE_DIVE);
			SetActionMode	(ANI_ACTION_DIVE);
			#endif
		} 
		else 
		{
			if (GetAboveFloor()<zMV_LAND_HEIGHT) { 
				if (GetModel()->IsAniActive	(s_fall))	GetModel()->StartAni	("T_FALL_2_FALLEN");
				else								GetModel()->StartAni	("T_FALLB_2_FALLENB");
				npc -> SetBodyState(BS_LIE);
				npc -> CreateFallDamage	(GetFallDownDistanceY());
				
				// Physik wieder an / LandAndStartAni macht die naemlich aus.
				//npc -> SetPhysicsEnabled (TRUE);
				npc -> SetCollDet (TRUE);
				// What's the difference ?
		//				zVALUE dif = GetFallDownDistanceY() - ANI_FALLDAMAGE_HEIGHT;
		//				zCView :: stdoutput -> Printwin("< FallDif : " + zSTRING(dif) +">\n");
			}
		};
	} 
}

// ***********************************************
// Helpers - Surrounding Checks
// ***********************************************

zREAL oCAniCtrl_Human :: CombineAniLerp (const zREAL curx, const zREAL targetx, const zREAL time, const zREAL maxTime)
{
	zREAL deltaMax	= time / maxTime;	// Maximale Auslenkung ( positiv )
	zREAL delta		= targetx - curx;

	// positiv
	if (delta>=0.0f)	return ( zMin(targetx , curx + deltaMax) );
	// negativ	
	else				return ( zMax(targetx , curx - deltaMax) ); 		
}

zBOOL oCAniCtrl_Human :: InterpolateCombineAni (const zREAL targetx, const zREAL targety, const zTModelAniID lookAni)
{
	// * dreh dich zu <Quelle> *
	// -> Kopf und Oberkörper (leicht) drehen in <Richtung>
	// CombAnis : T_LOOKAT		( Kopf und Oberkörper bewegen )
	//            T_QUICKLOOK	( nur Kopf bewegen )
	// Ani muss auf höheren Layer liegen -> Ist ein Overlay Befehl

	zREAL curx = 0.5f, cury = 0.5f;

	// Von derzeitiger Position Kopfbewegung zur Zielposition berechnen
	if (GetModel()->IsAniActive(lookAni)) GetModel() -> GetCombineAniXY	( lookAni, curx, cury );
	
	if ((curx!=targetx) || (cury!=targety)) {
	
		curx   = CombineAniLerp		( curx, targetx, ztimer.GetFrameTimeF(), INTERPOLATE_MAX_TIME /*1000*/ );
		cury   = CombineAniLerp		( cury, targety, ztimer.GetFrameTimeF(), INTERPOLATE_MAX_TIME /*1000*/ );

		// Und Ani setzen
		GetModel() -> StartAni			( lookAni );
		GetModel() -> SetCombineAniXY	( lookAni, curx, cury );
	
		// Falls Mittelpunkt wieder hergestellt, Ani beenden
		if ((curx==0.5f) && (cury==0.5f)) {
			GetModel() -> FadeOutAni( lookAni );
		}
		return FALSE;
	}
	return TRUE;
}

void oCAniCtrl_Human :: LookAtTarget()
{
	// Called per Frame to move Head in right Position
	InterpolateCombineAni ( lookTargetx, lookTargety, s_look );
};

void oCAniCtrl_Human :: SetLookAtTarget(zREAL targetx, zREAL targety)
{
	lookTargetx = targetx;
	lookTargety = targety;
	zRELEASE(targetVob);
};

void oCAniCtrl_Human :: SetLookAtTarget(zVEC3& pos)
{
	zREAL azi,elev;
	zREAL targetx,targety;

	// Zielausrichtung ermitteln
	npc	   -> GetAngles ((zVEC3)pos,azi,elev);
	if (abs(int(azi))<90) {
		targetx = (azi / 180) + 0.5;
		targety = 1 - ((elev / 120) + 0.5);

		zClamp(targetx,0.0f,1.0f);
		zClamp(targety,0.0f,1.0f);
	} else {
		targetx = 0.5;
		targety = 0.5;
	}

	SetLookAtTarget(targetx,targety);
};

void oCAniCtrl_Human :: SetLookAtTarget(zCVob* target)
{
	zRELEASE(targetVob);
	if (target) {
		zTBBox3D bbox = target->GetBBox3DWorld();
		zVEC3	 vecNeck	  = bbox.maxs;										// hinten oben rechts
				 vecNeck[VX] -= ( bbox.maxs[VX] - bbox.mins[VX] ) * 0.5f;		// hinten oben mitte
				 vecNeck[VZ] -= ( bbox.maxs[VZ] - bbox.mins[VZ] ) * 0.5f;		// mitte  oben mitte	-> Hals
		SetLookAtTarget(vecNeck);
		targetVob = target;
		targetVob->AddRef();
	}
}

void oCAniCtrl_Human :: StopLookAtTarget ()
{
	SetLookAtTarget(0.5f,0.5f);
	StopCombineAni (GetModel()->GetAniIDFromAniName("T_QLOOK"));
	StopCombineAni (GetModel()->GetAniIDFromAniName("S_TLOOK"));
	zRELEASE(targetVob);
};

// Combine Anis
void oCAniCtrl_Human :: StartCombineAni	(zVEC3& pos, zTModelAniID ani, const zREAL angleHeight, const zREAL angleWidth)
{
	zREAL azi,elev;
	zREAL targetx,targety;

	// Zielausrichtung ermitteln
	npc	   -> GetAngles ((zVEC3)pos,azi,elev);
	if (abs(int(azi))<=angleWidth)		targetx = (azi  / angleWidth) + 0.5;
	else								targetx = 0.5;
	if (abs(int(elev))<=angleHeight)	targety = 1 - ((elev / angleHeight) + 0.5);
	else								targety = 0.5;					

	zClamp (targetx,0.0f,1.0f);
	zClamp (targety,0.0f,1.0f);

	InterpolateCombineAni (	targetx, targety, ani );
};

void oCAniCtrl_Human :: StartCombineAni			(zCVob* target, zTModelAniID ani, const zREAL angleHeight, const zREAL angleWidth)
{
	if (target) StartCombineAni(target->GetPositionWorld(),ani,angleHeight,angleWidth);
};

void oCAniCtrl_Human :: StopCombineAni			(zTModelAniID ani)
{
	GetModel()->FadeOutAni(ani);
};

/*
void oCAniCtrl_Human :: LookAt (const zVEC3& pos, const zTModelAniID lookAni)
{
	// * dreh dich zu <Quelle> *
	// -> Kopf und Oberkörper (leicht) drehen in <Richtung>
	// CombAnis : T_LOOKAT ( Kopf und Oberkörper bewegen )
	// Ani muss auf höheren Layer liegen -> Ist ein Overlay Befehl

	// * Körperzustandsanalyse : Wo machen ? Hier ? *
	// Wenn du liegst, dann steh auf!
	// Mach den Oberkörper gerade (Ani! Markus)
	// Wenn du sitzt und <Quelle> nicht zu sehen, dann steh auf
	
	zREAL azi,elev;
	zREAL targetx,targety;
	zREAL curx = 0.5f,cury = 0.5f;

	// Zielausrichtung ermitteln
	npc	-> GetAngles((zVEC3)pos,azi,elev);
//	targetx = (azi  + 90) / ( 90 * 2);
//	targety = (elev + 45) / ( 45 * 2);
	targetx = (azi / 180) + 0.5;
	targety = (elev / 90) + 0.5;

	zClamp(targetx,0.0f,1.0f);
	zClamp(targety,0.0f,1.0f);

//	targety = 1 - targety;	// reverse coordinate
//	targetx = 1 - targetx;

	LookAt (targetx, targety, lookAni);
}

void oCAniCtrl_Human :: LookAt(const zCVob *v, const zTModelAniID lookAni)
{
	if (v) LookAt (v->GetPositionWorld(), lookAni);
}

void oCAniCtrl_Human :: StopLookAt (const zTModelAniID lookAni)
{
	GetModel()->SetCombineAniXY	(lookAni,0.5f,0.5f);
	GetModel()->FadeOutAni		(lookAni);
}

void oCAniCtrl_Human :: StopLookAt ()
{
	StopLookAt(s_look);
}
*/
zBOOL oCAniCtrl_Human :: DetectChasm(const zVEC3 &pos, const zVEC3 &dir, zREAL& floorDist, zVEC3 &cdNormal)
// IN / OUT : floorDist = Distance To Floor.
//      OUT : cdNormal
{
 	zVEC3 scanAt= dir; 
	scanAt[VY]	= 0;
	if (!npc->GetHomeWorld()->TraceRayFirstHit (pos, scanAt, npc, zTRACERAY_STAT_POLY)) 
	{
		const zVEC3 scanDown = zVEC3(0,-((pos[VY]-GetFeetY()) + floorDist), 0);
		//Line3D (GetCenterPos()+scanAt, GetCenterPos()+scanAt+scanDown, GFX_WHITE);
		if (npc->GetHomeWorld()->TraceRayNearestHit (pos+scanAt, scanDown, npc, zTRACERAY_STAT_POLY | zTRACERAY_POLY_NORMAL)) 
		{   
			floorDist	= GetFeetY() - npc->GetHomeWorld()->traceRayReport.foundIntersection[VY];
			cdNormal	= npc->GetHomeWorld()->traceRayReport.foundPolyNormal;
			if (!CanWalkOnPoly(cdNormal)) return TRUE;
		} 
//		return (floorDist>100);
		return (floorDist>50);				// Gothic 1: 100, nun 50 cm, damit NSCs auch von Tischen runterkommen
	};
	return FALSE;
}

zBOOL oCAniCtrl_Human :: IsInCriticalAni ()
// Bei diesen Anis keine Unterbrechunsanis abspielen
{
	return (// Klettern
			GetModel() -> IsAniActive(s_hang)			||
			GetModel() -> IsAniActive(t_hang_2_stand)	||
			GetModel() -> IsAniActive("T_STAND_2_HANG")	||
			// Am rumliegen
			GetModel() -> IsAniActive(s_fallen)			||
			GetModel() -> IsAniActive(s_fallenb)			||
			GetModel() -> IsAniActive(s_dead1)			||
			GetModel() -> IsAniActive(s_dead2)			||
			// Aufstehen / liegen / sitzen
			GetModel() -> IsAniActive("T_STAND_2_SITB")	||
			GetModel() -> IsAniActive("S_SITB")			||
			GetModel() -> IsAniActive("T_SITB_2_STAND")	||
			GetModel() -> IsAniActive("T_SITB_2_LIEB")	||
			GetModel() -> IsAniActive("S_LIEB")			||
			GetModel() -> IsAniActive("T_LIEB_2_SITB")	||

			GetModel() -> IsAniActive("T_STAND_2_SITF")	||
			GetModel() -> IsAniActive("S_SITF")			||
			GetModel() -> IsAniActive("T_SITF_2_STAND")	||
			GetModel() -> IsAniActive("T_SITF_2_LIEF")	||
			GetModel() -> IsAniActive("S_LIEF")			||
			GetModel() -> IsAniActive("T_LIEF_2_SITF")	
				
	);
}

// *************************************************************************************
// Archive
// *************************************************************************************

void oCAniCtrl_Human :: Archive(zCArchiver &arc)
{
	zCAIPlayer :: Archive(arc);

	if (!arc.InSaveGame())	return;

	arc.WriteObject	("aiNpc"		,npc);

	// Walk/Weapon
	arc.WriteInt	("walkMode"		,walkmode);
	arc.WriteInt	("weaponMode"	,wmode);
	arc.WriteInt	("wmodeLast"	,wmode_last);
	arc.WriteInt	("wmodeSelect"	,wmode_selected);
	arc.WriteBool	("changeWeapon"	,changeweapon);
	arc.WriteInt	("actionMode"	,actionMode);
//	arc.WriteInt	("waterLevel"	,GetWaterLevel());  // [Moos] Macht jetzt die AIPlayer
//	arc.WriteFloat	("waterY"		,GetWaterY());
//	arc.WriteFloat	("feetY"		,GetFeetY());
}

void oCAniCtrl_Human :: Unarchive(zCArchiver &arc)
{
	zCAIPlayer :: Unarchive(arc);

	if (!arc.InSaveGame())	return;
	
	// Nur im SaveGameMode ausführen

	npc = (oCNpc*)	arc.ReadObject1	("aiNpc");
	Init(npc);

	// Fixme : Oh hauahauaha
	if (npc) {
		assert(npc->GetRefCtr()>1);
		zRELEASE_ACCT_NONULL(npc);	
	}

	// Walk/Weapon
	walkmode		= ANI_WALKMODE_RUN; 
	actionMode		= ANI_ACTION_STAND;

	arc.ReadInt		("walkMode"		,walkmode);
	arc.ReadInt		("weaponMode"	,wmode);
	arc.ReadInt		("wmodeLast"	,wmode_last);
	arc.ReadInt		("wmodeSelect"	,wmode_selected);
	arc.ReadBool	("changeWeapon"	,changeweapon);
	arc.ReadInt		("actionMode"	,actionMode);
//	arc.ReadInt		("waterLevel"	,GetWaterLevel());
//	arc.ReadFloat	("waterY"		,GetWaterY());
//	arc.ReadFloat	("feetY"		,GetFeetY());

/*	if (npc) {
		SetActionMode	(_actionMode);
		SetWalkMode		(_walkmode);
	}*/
}

// *************************************************************************************
// Movement Routinen für NSCs und SCs !!!!
// *************************************************************************************

void oCAniCtrl_Human :: SetActionMode(int am)
{
	actionMode = am;
	if (am == ANI_ACTION_SWIM)	{
		npc->SetBodyState (BS_SWIM);
		SetConfigDoSurfaceAlign(zMV_SURFACE_ALIGN_NONE);
		npc->ResetXZRotationsWorld();                      // [Moos] 20.12.00 Anpassung an Vob-Änderung
		
	} else if (am == ANI_ACTION_DIVE)	{
		npc->SetBodyState (BS_DIVE);
		SetConfigDoWallSliding(TRUE);
		SetConfigDoSurfaceAlign(zMV_SURFACE_ALIGN_NONE);
		npc->ResetXZRotationsWorld();                      // [Moos] 20.12.00 Anpassung an Vob-Änderung

	} else {
		SetConfigDoWallSliding(FALSE);
		SetConfigDoSurfaceAlign(zCAIPlayer::zTSurfaceAlignMode(defaultSurfaceAlign));
	}
}

void oCAniCtrl_Human :: _Stand()
// AIM -> STAND
{
    if(!GetModel())
        return;

	// **** Wasserstandsprüfung ***
//	CheckWaterLevel();

	if (GetActionMode()==ANI_ACTION_DIVE) {
		
		SetState						(zMV_STATE_DIVE);
		npc->SetBodyState				(BS_DIVE);

		if (GetModel()->IsAniActive			(s_divef))	{
			GetModel()->StartAni				(t_divef_2_dive);
		} 

	} else if (GetActionMode()==ANI_ACTION_SWIM) {
	
		SetState						(zMV_STATE_SWIM);
		npc->SetBodyState				(BS_SWIM);

		if (GetModel()->IsAniActive			(s_swimf)) {
			GetModel()->StartAni				(t_swimf_2_swim);
		} else if (GetModel()->IsAniActive	(s_swimb)) {
			GetModel()->StartAni				(t_swimb_2_swim);
		}

	} else if (GetModel()->IsAniActive(_s_walkl)) {
		
		int side = GetFootPos();
		if (npc->GetWeaponMode()==NPC_WEAPON_NONE) {
			// Benutzen der Transitions
			if		(side == 1)	StartAni(_t_walkl_2_walk,_s_walk);
			else if (side == 2)	StartAni(_t_walkr_2_walk,_s_walk);
		} else {
			// IM Kampfmodus sofort stehenbleiben
			GetModel()->StartAni(_s_walk);
		}
		npc->SetBodyState (BS_STAND);

	} else if (GetModel()->IsAniActive(_t_walk_2_walkl)) {

		if (npc->GetWeaponMode()!=NPC_WEAPON_NONE) {
			// IM Kampfmodus sofort stehenbleiben
			GetModel()->StartAni(_s_walk);
			npc->SetBodyState (BS_STAND);
		}

	} else if (GetModel()->IsAniActive(_s_walkbl)) {
		int side = GetFootPos();
		if		(side == 1)	StartAni(_t_walkbl_2_walk,_s_walk);
		else if (side == 2)	StartAni(_t_walkbr_2_walk,_s_walk);
		npc->SetBodyState (BS_STAND);
	
	} else if (GetModel()->IsAniActive(_s_aim)) {
		StartAni			(_t_aim_2_walk,_s_walk);
		npc->SetBodyState	(BS_STAND);
	
	} else if (IsStateAniActive(_s_walk)) {
		// Safety
		npc->SetCollDet		(TRUE);
		npc->SetBodyState	(BS_STAND);		
		// Clear falldown height override
		this->npc->overrideFallDownHeight = FALSE;
	}

    if (!GetModel()->IsStateActive(_s_jumpup) || !GetModel()->IsStateActive(s_hang) )  // [Moos] im Sprung soll nicht von der Wand abgedreht werden
        SetConfigDoWallSliding(FALSE);
	//npc->SetCollDet(TRUE);
}

void oCAniCtrl_Human :: _Forward()
{
	// **** Wasserstandsprüfung ***
//	CheckWaterLevel();

	if (GetActionMode()==ANI_ACTION_DIVE) {

		SetState(zMV_STATE_DIVE);
		npc->SetBodyState(BS_DIVE);

		// Auftauchen ?
		if (!GetModel()->IsAniActive(t_swim_2_dive) && (GetHeadY() > GetWaterY())) {
			GetModel()	-> StartAni		(s_swim);
			npc		-> ResetXZRotationsWorld();                             // [Moos] 20.12.00 Anpassung an Vob-Änderung

			SetWalkMode				(ANI_WALKMODE_SWIM);
			SetActionMode			(ANI_ACTION_SWIM);
			return;
		}

		if (GetModel()->IsAniActive			(s_dive))	{
			GetModel()->StartAni				(t_dive_2_divef);
		} 

	} else if (GetActionMode()==ANI_ACTION_SWIM) {
		
		SetState(zMV_STATE_SWIM);
		npc->SetBodyState(BS_SWIM);

		if (GetModel()->IsAniActive			(s_swim))	{
			GetModel()->StartAni				(t_swim_2_swimf);
		} else if (GetModel()->IsAniActive	(s_swimb))	{
			GetModel()->StartAni				(t_swimb_2_swim);
		}

	} else {

		// Normalmode ?
		if (GetModel()->IsAniActive(_s_walk)) {
			GetModel()->StartAni(_t_walk_2_walkl);
			npc->SetCollDet(TRUE);
		
		} else if (GetModel()->IsAniActive(_s_walkbl)) {
			GetModel()->StartAni(_t_walkbl_2_walk);
		}

		if (!GetModel()->GetIsFlying()) {
			switch (GetWalkMode()) {
				case ANI_WALKMODE_WALK	:	 npc->SetBodyState (BS_WALK);	break;
				case ANI_WALKMODE_SNEAK	:	 npc->SetBodyState (BS_SNEAK);	break;
				case ANI_WALKMODE_RUN	:	 npc->SetBodyState (BS_RUN);	break;
			}
		}
	}

	StopTurnAnis();
}

void oCAniCtrl_Human :: _Backward()
{
	// **** Wasserstandsprüfung ***
//	CheckWaterLevel();

	if (GetActionMode()==ANI_ACTION_DIVE) {
		
		SetState						(zMV_STATE_DIVE);
		npc->SetBodyState				(BS_DIVE);

		if (GetModel()->IsAniActive			(s_divef))	{
			GetModel()->StartAni				(t_divef_2_dive);
		} 

	} else if (GetActionMode()==ANI_ACTION_SWIM) {

		SetState(zMV_STATE_SWIM);
		npc->SetBodyState(BS_SWIM);

		if (GetModel()->IsAniActive	(s_swim)) {
			GetModel()->StartAni		(t_swim_2_swimb);
		} else if (GetModel()->IsAniActive(s_swimf)) {
			GetModel()->StartAni		(t_swimf_2_swim);
		}

	}
	else 
	{
		// Normalmode ?
		if (GetModel()->IsAniActive	(_s_walk)) {
			npc->SetCollDet(TRUE);
			// Normal nach hinten gehen
			if (_t_walk_2_walkbl!=zMDL_ANI_ID_ILLEGAL) {
				StartAni (_t_walk_2_walkbl);
			}
			// Sprung nach hinten, im Run-Modus
			else GetModel()->StartAni	(_t_jumpb);
			
			switch (GetWalkMode()) {
				case ANI_WALKMODE_WALK	:	 npc->SetBodyState (BS_WALK);	break;
				case ANI_WALKMODE_SNEAK	:	 npc->SetBodyState (BS_SNEAK);	break;
				case ANI_WALKMODE_RUN	:	 npc->SetBodyState (BS_RUN);	break;
			}

		} else if (GetModel()->IsAniActive(_s_walkl)) 
		{
			_Stand();
		}
	}

	StopTurnAnis();
}

// *************************************************************************************
// MagieAnis
// *************************************************************************************

void oCAniCtrl_Human :: SetAnimations	(int spellMode, const zSTRING& scut)
{
	t_stand_2_cast	= zMDL_ANI_ID_ILLEGAL;
	s_cast			= zMDL_ANI_ID_ILLEGAL;
	t_cast_2_shoot	= zMDL_ANI_ID_ILLEGAL;
	s_shoot			= zMDL_ANI_ID_ILLEGAL;
	t_shoot_2_stand	= zMDL_ANI_ID_ILLEGAL;
	t_cast_2_stand	= zMDL_ANI_ID_ILLEGAL;

	zSTRING	type	= "MAG";

	t_stand_2_cast		=	GetModel()->GetAniIDFromAniName("T_"+type+"RUN_2_"+scut+"CAST");
	s_cast				=	GetModel()->GetAniIDFromAniName("S_"+scut+"CAST");
	t_cast_2_shoot		=	GetModel()->GetAniIDFromAniName("T_"+scut+"CAST_2_"+scut+"SHOOT");
	t_cast_2_stand		=	GetModel()->GetAniIDFromAniName("T_"+scut+"CAST_2_STAND");
	s_shoot				=	GetModel()->GetAniIDFromAniName("S_"+scut+"SHOOT");
	t_shoot_2_stand		=	GetModel()->GetAniIDFromAniName("T_"+scut+"SHOOT_2_STAND");

	// Cast Anis fehlen ?
	if (t_stand_2_cast == zMDL_ANI_ID_ILLEGAL) {
		t_stand_2_cast	= GetModel()->GetAniIDFromAniName("T_"+type+"RUN_2_"+scut+"SHOOT");
	}
}


zBOOL oCAniCtrl_Human :: TransitionToInvest()
{	
	if (GetModel()->IsAniActive(_s_walk)) {
		if (t_stand_2_cast!=zMDL_ANI_ID_ILLEGAL) GetModel()->StartAni(t_stand_2_cast);
	}
	else if (GetModel()->IsAniActive(t_shoot_2_stand))
	{
		GetModel()->FadeOutAni(t_shoot_2_stand);
	}
	return (GetModel()->IsAniActive(s_cast));
}

zBOOL oCAniCtrl_Human :: TransitionToCast()
{
	if (GetModel()->IsAniActive(s_cast)) {
		if (t_cast_2_shoot!=zMDL_ANI_ID_ILLEGAL) {
			StartAni(t_cast_2_shoot,s_shoot);
		}

	} else if (GetModel()->IsAniActive(s_shoot) && (t_shoot_2_stand!=zMDL_ANI_ID_ILLEGAL)) {
		SetNextAni		(s_shoot,t_shoot_2_stand);	// Safety.
		return TRUE;
	
	} else if (GetModel()->IsAniActive(t_shoot_2_stand)) {
		SetNextAni		(t_shoot_2_stand,_s_walk);	// Safety.			
	}
	return (GetModel()->IsAniActive(s_shoot));
}

zBOOL oCAniCtrl_Human :: TransitionToStand()
{
	if (GetModel()->IsAniActive(s_shoot)) {
		
		if (t_shoot_2_stand!=zMDL_ANI_ID_ILLEGAL) {
			StartAni			(t_shoot_2_stand,_s_walk);
		} else {
			GetModel() -> StartAni	(_s_walk);
		}
	
	} else if (GetModel()->IsAniActive(s_cast)) {
		
		if (t_cast_2_stand!=zMDL_ANI_ID_ILLEGAL) {
			StartAni	(t_cast_2_stand,_s_walk);
		} else {
			StartAni	(_s_walk);
		}
	}  else if (GetModel()->IsAniActive(t_stand_2_cast)) {
		StartAni(_s_walk);
	}

	return (GetModel()->IsAniActive(_s_walk));
}

zBOOL oCAniCtrl_Human :: IsInCastAni()
{
	return (GetModel()->IsAniActive(s_shoot) || GetModel()->IsAniActive(s_cast));
}

zBOOL oCAniCtrl_Human :: IsInWeaponChoose()
{
	if (GetModel()) {
		for (int i=0; i<NPC_WEAPON_MAX; i++) {
			if (GetModel()->IsAniActive(s_weapon[i])) return TRUE;
		}
	}
	return FALSE;
};

// *************************************************************************************
// HELPERS
// *************************************************************************************

//void oCAniCtrl_Human :: SetDoOops(zBOOL on)
//{
//	zMV_DO_OOPS = on;
//}

int	 oCAniCtrl_Human :: GetWaterLevel()
{
	if ((zCAIPlayer::GetWaterLevel()==1) && (GetFeetY()<GetWaterY())) return 1;
	if ((zCAIPlayer::GetWaterLevel()==2) && (GetFeetY()<GetWaterY())) return 2;
	return 0;
}

zBOOL oCAniCtrl_Human :: IsInWater()
{
	return (GetWaterLevel()>0);
}

//void oCAniCtrl_Human :: SetState( int st )
//{
//	state = st;
//}

//int  oCAniCtrl_Human :: GetOldState()
//{
//	return oldState;
//}

zCLASS_DEFINITION (oCAniCtrl_Human, zCAIPlayer, 0, 0)

#pragma warning ( default:4244 )

