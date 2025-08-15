/******************************************************************************** 
 
     $Workfile:: zAIPlayer.cpp        $                $Date:: 26.04.01 15:35   $
     $Revision:: 82                   $             $Modtime:: 26.04.01 15:32   $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/zengin/_Dieter/zAIPlayer.cpp $
 * 
 * 82    26.04.01 15:35 Edenfeld
 * Soundprovider Checks sicherer gemacht,
 * AIPlayer Sprunghänger Bug gefixt
 * 
 * 81    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 80    15.02.01 22:14 Moos
 * SurfaceAlign-Entzumpelung
 *  
 * 79    15.02.01 5:18 Hildebrandt
 * 
 * 78    13.02.01 17:05 Moos
 * Diego-Bewegt-Sich-Im-OC-keinen-Millimeter-wegen-Höhenangst-Fix
 * 
 * 77    12.02.01 18:40 Hildebrandt
 * 
 * 76    10.02.01 23:45 Moos
 * Slide vs. Falldown-Fix
 * 
 * 75    9.02.01 2:36 Hildebrandt
 * 
 * 74    3.02.01 2:19 Hildebrandt
 * 
 * 73    2.02.01 4:04 Hildebrandt
 * 
 * 72    31.01.01 17:47 Moos
 * 
 * 71    31.01.01 16:01 Moos
 * 
 * 70    29.01.01 0:50 Hildebrandt
 * 
 * 69    26.01.01 19:40 Hildebrandt
 * 
 * 68    24.01.01 23:41 Hildebrandt
 * 
 * 67    24.01.01 14:57 Moos
 * 
 * 66    23.01.01 19:19 Moos
 * 
 * 65    23.01.01 13:59 Keskenti
 * 
 * 64    23.01.01 12:04 Moos
 * 
 * 63    23.01.01 3:34 Hildebrandt
 * 
 * 62    22.01.01 20:01 Moos
 * 
 * 61    19.01.01 21:20 Moos
 * 
 * 60    19.01.01 16:38 Moos
 * 
 * 59    19.01.01 11:41 Moos
 * 
 * 58    18.01.01 17:17 Moos
 * 
 * 57    17.01.01 19:21 Hildebrandt
 * 
 * 56    17.01.01 18:01 Hildebrandt
 * 
 * 55    17.01.01 3:05 Hildebrandt
 * 
 * 54    17.01.01 1:57 Hildebrandt
 * 
 * 53    17.01.01 1:45 Hildebrandt
 * 
 * 52    16.01.01 20:18 Hildebrandt
 * 
 * 51    16.01.01 18:20 Hildebrandt
 * 
 * 50    16.01.01 17:27 Moos
 * 
 * 49    16.01.01 3:31 Hildebrandt
 * 
 * 48    15.01.01 19:08 Hildebrandt
 * 
 * 47    15.01.01 18:04 Moos
 * 
 * 46    15.01.01 3:55 Hildebrandt
 * 
 * 45    14.01.01 16:36 Hildebrandt
 * 
 * 44    12.01.01 15:48 Moos
 * 
 * 43    12.01.01 13:56 Moos
 * 
 * 42    12.01.01 12:38 Moos
 * 
 * 41    12.01.01 3:23 Hildebrandt
 * 
 * 40    11.01.01 20:08 Moos
 * 
 * 39    11.01.01 19:08 Moos
 * 
 * 38    11.01.01 18:46 Hildebrandt
 * 
 * 37    21.12.00 21:24 Moos
 * 
 * 36    21.12.00 18:27 Hildebrandt
 * 
 * 35    20.12.00 3:04 Hildebrandt
 * 
 * 34    5.12.00 19:04 Hildebrandt
 * 
 * 33    22.11.00 22:42 Hildebrandt
 * 
 * 32    22.11.00 16:37 Hildebrandt
 * 
 * 31    17.11.00 1:28 Hildebrandt
 * 
 * 30    26.10.00 21:42 Hildebrandt
 * 
 * 29    26.10.00 20:40 Hildebrandt
 * 
 * 28    26.10.00 2:23 Hildebrandt
 * 
 * 27    25.10.00 15:07 Hildebrandt
 * 
 * 26    11.10.00 19:45 Hildebrandt
 * 
 * 25    22.09.00 17:14 Moos
 * 
 * 24    21.09.00 20:58 Moos
 * 
 * 23    19.09.00 13:07 Hildebrandt
 *  
 * 22    15.09.00 16:44 Hildebrandt
 * 
 * 21    14.09.00 19:43 Hildebrandt
 * 
 * 20    11.09.00 17:34 Hildebrandt
 * 
 * 19    7.09.00 20:41 Hildebrandt
 * 
 * 18    31.08.00 20:30 Hildebrandt
 * 
 * 17    31.08.00 17:04 Hildebrandt
 * 
 * 16    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 15    21.08.00 17:18 Hildebrandt
 * 
 * 14    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 13    21.07.00 14:28 Hildebrandt
 * 
 * 12    6.07.00 13:33 Hildebrandt
 * 
 * 6     8.05.00 2:17 Hildebrandt
 * 
 * 5     4.05.00 20:16 Hildebrandt
 * zenGin 089e
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 17    22.03.00 2:58 Hildebrandt
 * zenGin 088a
 * 
 * 16    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 15    22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 14    20.02.00 18:08 Hildebrandt
 * zenGin 087c
 * 
 * 13    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 11    14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 10    10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 8     18.11.99 22:18 Hildebrandt
 * 
 * 7     13.11.99 1:10 Hildebrandt
 * 
 * 6     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 82 $ ($Modtime: 26.04.01 15:32 $)


/*

Für Wasser fehlt noch:
x Strömung
- leichter waterSplash Effekt bei jeder Bewegung im Wasser
- weitere Effekte ..(?)
- Unterwasser: Bubble PFX vom Player (Heretic2)
- Proz. Texturen (Unreal etc.)

*/

/*
  A)
  - Physik
  - ModelMove
  B)
  - AI:
	- Begin();
		- centerPos
		- feetY
		- headY
	- FindFloorCeiling();
		- floorY
		- ceilingY
		- aboveFloor
		- newCenter
	- CorrectFloorHeight ();
	- if (CollisionHandling()) goto leave;
	- BeginStateSwitch ();

  - Zustand A)	alter, korrekter Zustand
  - Zustand B)	Physik, Model-Movement ausgefuehrt
  - Zustand C)	AI: CorrectFloorHeight ausgef.
  - Zustand D)	AI: CollDetResp ausfg.

  - altePos		:	oldTrafoObjToWorld
  - neuePos		:	trafoObjToWorld		, GetPositionWorld()

  - floorY		:	altePos
  - ceilingY	:	altePos
  - feetY		:	altePos		(GetPosWorld(), aber noch vor CorrectFloorCeiling)
  - headY		:
  - aboveFloor	:	neu/alt		feetY-floorY

=====================================================================================================================

  Wasser-Effekt:
  - kleine aufsteigende Blaesschen (a la TombRaider): werden Wohl Decal-Vobs sein, wegen CollDet
    oder PartikelFX, dann aber tiefen-abh.
  x Wasserringe bei Bewegungen (TombRaider3)
  - Partikel-Spritzer, wenn Objekt in Wasser faellt
  - UnterWasser: 
	x blaues alpha-Poly für Färbung
	x Cam FOV-Ani							(wie Turok)
	- Vertex-Gouraud Animation				(TombRaider)
  - Wasseroberfläche:
	- Plasma-Texture ?						(Unreal)
	- animierte Vertices der WasserPolys	(Turok)
  - Heretic2:
	- Wasserringe
	x fetter Unterwasser-Nebel
	x kleine Partikel Unterwasser (keine CollDet, minimale Bewegung)

  
- Todo:
	x Models: Fake Boden Shadows
	- ME: bei n Anis muss die rootPosLocal richtig berechnet werden
	- Model-Collision: dyn. BBox-Verfahren ?, Anpassen der BBox an Swim/Dive, Normal
	* STABIL MACHEN (CD!)
	x zCVob, zCTexture: VIRTUALS !
	x TraceRay muss funktionieren (auch compiliert/uncomp.)  BSP-Compile-FIX !!!
	  (fehlt noch: BBox, Model)
	x TraceRay: spezieller Fall fuer SEHR flaches Wasser fehlt noch.
	- Physik/Gravity im Wasser ?
	- Vobs fallen ins Wasser
	x BSP-Compiler bug (pushboth)
	x AIPlayer: CorrectFloorHeight mit Ani-Y-Origin, nicht mit BBox !!

	* ME: aniAlias mit *aniEvents ausstatten (geht doch, oder?)
	* zTree.h Warnung in Libs ?
	* AI muss collision melden, falls ceiling<headPos !!
	* Zusammenspiel CD, AI
	x ME: Rotate-Flag
	x Mat-Groups in Mat-Scripte
	x bisection in CD
	x zCArray
	x CD muss Wasser ignorieren
	x DoAI-Position
	x IDEE: falls der Timer unter 10/15? FPS ist, diesen so faken, dass er nicht unter 10/15 gehen kann..
	        So kann mann einigen Probs aus dem Weg gehen, die sich bei extrem niedriger FPS-Rate ergeben

  - Moves:
	- CD beim Fallen (bbox unten genauer checken mit rays)
	- Wasser
	- Gehen:
		x gehen stoppt am Abgrund
		x gehen von Schraegen > 30° nicht moeglich
	- Sprung, Festhalten an Klippe
	x Rutschen F,B
	- Oszi-Verhalten beim WALKW im Becken (waterLevel 0/1), traceRay ??
*/

#include <zCore.h>
#include <zAIPlayer.h>
#include <zModel.h>
#include <zPhysics.h> 
#include <zParticle.h>
#include <zSoundMan.h>
#include <zArchiver.h>
#include <zEventMan.h>
#include <zPolyStrip.h>
#include <zInput_Win32.h>
#include <zView.h>
#include <zVobMisc.h>
#include <zSparseArray.h>
#include <zSky.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

zCLASS_DEFINITION (zCAIPlayer, zCAIBase, 0, 1)


zBOOL zCAIPlayer::s_bShowWeaponTrails = TRUE;

// ----------------------------------------------------------------------------------------------------


#ifdef DEBUG_HILDEBRANDT
//	#define zMV_DEBUG
#endif

		//////////////////
		// Konstanten	//
		//////////////////


//////////////////////////////
// von Model abhängig
//////////////////////////////

		// Referenz-Defaults, bezogen auf einen Human. Parameter anderer ModelProtos werden auf der Basis
		// dieser Werte skaliert.

		// Referenz-Konstante (Human Modelproto)
		static const zREAL	zMV_DEF_PROTO_VOLUME			= 280.0F;	// 655585, 612195, 446834, 551207

		static const zREAL	zMV_DEF_MIN_SPACE_MOVE_FORWARD	= 50;
		static const zREAL	zMV_DEF_DETECT_CHASM_SCAN_AT	= 50;

		static const zREAL	zMV_DEF_JUMP_UP_MIN_CEIL		= 50;
		static const zREAL	zMV_DEF_WATER_DEPTH_KNEE		= 50;
		static const zREAL	zMV_DEF_WATER_DEPTH_CHEST		= 151;

		static const zREAL	zMV_DEF_YMAX_SWIM_CLIMB_OUT		= 100;
		static const zREAL	zMV_DEF_FORCE_JUMP_UP			= 60000;

		static const zREAL	zMV_DEF_STEP_HEIGHT				= 75;		// sollte kleiner sein, als die beiden folgenden
		static const zREAL	zMV_DEF_YMAX_JUMPLOW			= 105;		// 105
		static const zREAL	zMV_DEF_YMAX_JUMPMID			= 205;		// 205
		
////////////////////////////////////////////////////////////////////////////
// interne Parameter, nur vom Programmierer zu ändern (fuer alle gleich)
////////////////////////////////////////////////////////////////////////////

//		static const zREAL	zMV_GROUND_OFFSET			= 0.5;
		static const zVEC3	zMV_UP						= zVEC3(0,+100000,0);
		static const zVEC3	zMV_DOWN					= zVEC3(0,-100000,0);

		static const zREAL	zMV_MAX_VEL_FALL_2_SWIM2	= zREAL((0.5F*1000)*(0.5F*1000)) ;	// falls drueber: FALL_2_DIVE

		// Detect ClumbUp Ledge
//		static const zREAL	zMV_DCUL_SCAN_HEIGHT		= (300+180);		// vom kopf an = Sprunghoehe
//		static const zREAL	zMV_DCUL_VERT_THRESH		=  30;

        // [Moos] andere Konstanten dafür
        static const zREAL zMV_DCUL_VERT_MAX_THRESH     = 40;
        static const zREAL zMV_DCUL_VERT_MIN_THRESH     = 10;
        static const zREAL zMV_DCUL_STEPBACK            = 20;
        static const zREAL zMV_DCUL_STEPFORWARD         = 3;

		static const zREAL	zMV_JUMP_GRAB_LEDGE_DIST	= 60;

	 
// ----------------------------------------------------------------------------------------------------

static const zREAL	D				= 120;
static const zREAL	MOV_MASS		=  80;		// Unser Player bringt 60kg auf die Waage
static		 zREAL	MOV_FORCE_Z		=  60+D;	// Kraft beim Vorwärts gehen	
static		 zREAL	MOV_FORCE_X		=  30+D;	// Kraft beim zur Seite gehen
static		 zREAL	MOV_FORCE_Y		=  30+D;	
static const zREAL	MOV_FRIC_MOV	= 0.2F;		// Reibungsfaktor

static const zREAL	MOV_FORCE_ROT	=	2;		// Rotationsbeschleunigung
static const zREAL	MOV_FRIC_ROT	= 0.3F;		// Reibungsfaktor Drehen
static const zREAL	MOV_TIME_CORR	= 64;		// Used in DIV


static zCModelAni *_s_run = 0;

static zCCache<const zCAIPlayer *, zCAIPlayer::zTLedgeInfo> s_ledgeCache(13);  // Hier werden die Informationen der aktuellen Kletterkante abgelegt


// Constructor
zCAIPlayer::zCAIPlayer ()
{
	//
	zBYTE	*firstByte		= (zBYTE*)(&this->vob);
	zBYTE	*lastByte		= (zBYTE*)(&this->dummyLastVar);
	memset					(firstByte	, 0,	lastByte-firstByte);
	memset					(&config	, 0,	sizeof(config));

	//
	zERR_CASSERT			((zMV_STATE_STAND==0));

	// Blood
	SetBleeding				(0.0F);
	bloodDefaultTexName		= zSTRING("ZBLOODSPLAT2.TGA");

	// autoRoll
	autoRollPos				= 0;
	autoRollPosDest			= 1;
	autoRollSpeed			= 0.003F;
	autoRollMaxAngle		= 10;
	SetAutoRollEnabled		(TRUE);
};

zCAIPlayer::~zCAIPlayer ()
{
	// 
	RemoveEffects			();
    ClearFoundLedge         ();

	// ptr auf 0 setzen
	vob						= 0;
	model					= 0;
	world					= 0;

    s_ledgeCache.Delete(this);
};

void zCAIPlayer::RemoveEffects ()
{
	// Die Effekt-Vobs werden aus der Welt entfernt und schliesslich Released.

	// 1) Watering
	if (waterRingVob) {
		waterRingVob->RemoveVobFromWorld	();
		waterRingVob->Release				();
		waterRingVob						= 0;
	};

	// 2) weaponTrail
	if (weaponTrailVob) {
		weaponTrailVob->RemoveVobFromWorld	();
		weaponTrailVob->Release				();
		weaponTrailVob						= 0;
	};

	// 3) blood
	for (int i=0; i<bloodVobList.GetNum(); i++)
	{
		bloodVobList[i].bloodVob->RemoveVobFromWorld();
		bloodVobList[i].bloodVob->Release			();
		bloodVobList[i].bloodVob					= 0;
	};
	bloodVobList.DeleteList();
};

void zCAIPlayer::HostVobRemovedFromWorld (zCVob* hostVob, zCWorld* hostWorld)
{
	RemoveEffects			();
//	interferenceReport.Clear();
};

zREAL zCAIPlayer::GetJumpUpHeight() 
{
	//zMV_FORCE_JUMP_UP= sqrt(2.0F * 400.0F * 981.0F) * vob->RigidBody()->GetMass();
	zERR_ASSERT (vob);
	return (config.zMV_FORCE_JUMP_UP * config.zMV_FORCE_JUMP_UP) / 
		   (2.0F * vob->GetRigidBody()->GetMass() * vob->GetRigidBody()->GetMass() * 981.0F);
};

void zCAIPlayer::SetJumpUpForceByHeight (const zREAL height) 
{
	zERR_ASSERT (vob);
	config.zMV_FORCE_JUMP_UP = sqrtf(2.0F * height * 981.0F) * vob->GetRigidBody()->GetMass();
};

void zCAIPlayer::SetVob (zCVob *inVob) 
{
	cdStatOriginal				= inVob->GetCollDetStat();
	vob							= inVob;
	world						= vob->GetHomeWorld();
	model						= (zCModel*)vob->GetVisual();
    if (model)
	    modelHeadNode		    = model->SearchNode (zMDL_NODE_NAME_HEAD);
    else
        modelHeadNode           = NULL;

	//
	vob->GetRigidBody()->SetMass (80);	// kg

	zREAL protoVol;
    if (model)
    {
    	const zTBBox3D& protoBox	= model->GetBBox3DLocalFixed();
    	protoVol					=	(protoBox.maxs.n[0]-protoBox.mins.n[0]) * 0.8F +  
									    (protoBox.maxs.n[1]-protoBox.mins.n[1]) * 1.0F + 
									    (protoBox.maxs.n[2]-protoBox.mins.n[2]) * 0.8F;
    }
    else
        protoVol = 1000;

	zREAL protoScale			= protoVol / zMV_DEF_PROTO_VOLUME; 

	// Konstanten berechnen, die von der Model-Groesse abhängig sind
	config.zMV_MIN_SPACE_MOVE_FORWARD	= zMV_DEF_MIN_SPACE_MOVE_FORWARD	* protoScale;
	config.zMV_DETECT_CHASM_SCAN_AT		= zMV_DEF_DETECT_CHASM_SCAN_AT		* protoScale;

	config.zMV_STEP_HEIGHT				= zMV_DEF_STEP_HEIGHT				* protoScale;
	config.zMV_JUMP_UP_MIN_CEIL			= zMV_DEF_JUMP_UP_MIN_CEIL			* protoScale;
	config.zMV_WATER_DEPTH_KNEE			= zMV_DEF_WATER_DEPTH_KNEE			* protoScale;
	config.zMV_WATER_DEPTH_CHEST		= zMV_DEF_WATER_DEPTH_CHEST			* protoScale;

	config.zMV_YMAX_SWIM_CLIMB_OUT		= zMV_DEF_YMAX_SWIM_CLIMB_OUT		* protoScale;
	config.zMV_FORCE_JUMP_UP			= zMV_DEF_FORCE_JUMP_UP				* protoScale;

	config.zMV_YMAX_JUMPLOW				= zMV_DEF_YMAX_JUMPLOW				* protoScale;
	config.zMV_YMAX_JUMPMID				= zMV_DEF_YMAX_JUMPMID				* protoScale;

	// Model abhängige Konstanten, nicht von Groesse abhängig.
	// Allerdings sollen diese Werte wohl evtl. per Script extern editierbar sein.
	config.zMV_MAX_GROUND_ANGLE_WALK	= Alg_Deg2Rad (50);		// 40, 50, 60
	config.zMV_MAX_GROUND_ANGLE_SLIDE	= Alg_Deg2Rad (60);		// (20,21,60);
	config.zMV_MAX_GROUND_ANGLE_SLIDE2	= Alg_Deg2Rad (70);

	#ifdef ZENGINE_AIPLAYER
	if (model){
//zMV_WATER_DEPTH_KNEE		= zMV_WATER_IGNORE_DEPTH;
//zMV_WATER_DEPTH_CHEST		= zMV_WATER_IGNORE_DEPTH;
		zCModelAni *walk, *run; 
		walk = model->GetAniFromAniName ("S_WALKL");
		run  = model->GetAniFromAniName ("S_RUNL");
		if (!walk) walk = model->GetAniFromAniName ("S_FISTWALKL");
		if (!run ) run  = model->GetAniFromAniName ("S_FISTRUNL");
		if ((!run) || (!walk)) return;
		zVEC3 s = model->GetModelScale();
		zREAL t = (s[0]+s[2]) * 0.5F;
		config.zMV_MIN_VELOCITY_WALK		= walk->GetAniVelocity() * zREAL(1000.0F) * zREAL(0.66F) * t;
		config.zMV_MIN_VELOCITY_RUN			= run ->GetAniVelocity() * zREAL(1000.0F) * zREAL(0.66F) * t;
		config.zMV_MIN_VELOCITY_RUN2		= config.zMV_MIN_VELOCITY_RUN  * config.zMV_MIN_VELOCITY_RUN;
		config.zMV_MIN_VELOCITY_WALK2		= config.zMV_MIN_VELOCITY_WALK * config.zMV_MIN_VELOCITY_WALK;
	//	zerr.Message ("-walk: "+zSTRING(zMV_MIN_VELOCITY_WALK));
	//	zerr.Message ("-run : "+zSTRING(zMV_MIN_VELOCITY_RUN));
	}
	#endif
 
	// defaults
#ifdef ZENGINE_AIPLAYER
	zMV_DO_SURFACE_ALIGN			= zMV_SURFACE_ALIGN_NONE;
//	zMV_DO_SURFACE_ALIGN			= zMV_SURFACE_ALIGN_NORMAL;
//	zMV_DO_SURFACE_ALIGN			= zMV_SURFACE_ALIGN_HIGH;
#else 
	zMV_DO_SURFACE_ALIGN			= zMV_SURFACE_ALIGN_NONE;
#endif
	zMV_DO_DETECT_WALK_STOP_CHASM	= TRUE;
	zMV_DO_WALL_SLIDING				= TRUE;
	zMV_DO_HEIGHT_CORRECTION		= TRUE;
//	zMV_DO_HEIGHT_CORRECTION		= FALSE;

	// 
	config.zMV_DCUL_WALL_HEADING_ANGLE		= Alg_Deg2Rad (45);
	config.zMV_DCUL_WALL_HORIZ_ANGLE		= Alg_Deg2Rad (45);
	config.zMV_DCUL_GROUND_ANGLE			= Alg_Deg2Rad (45);

	// Nach dem Aufruf dieser Methode koennen nach Belieben die hier gesetzten Werte z.B. per
	// Script überschrieben werden.
	// ..
};

void zCAIPlayer::DoAutoRoll() 
{
	zBOOL suppressAutoRoll	= vob->GetPhysicsEnabled();

	if (!GetAutoRollEnabled() || suppressAutoRoll) return;

	if (autoRollPos!=autoRollPosDest)
//	if ((autoRollPos!=autoRollPosDest) || (state=zMV_STATE_DIVE))
	{
		zREAL speedScale = (autoRollPosDest!=0) ? 0.5f : 1;
		if (autoRollPos<autoRollPosDest) {
			autoRollPos += autoRollSpeed * speedScale * ztimer.GetFrameTimeF(); 
			if (autoRollPos>autoRollPosDest) autoRollPos = autoRollPosDest;
		} else
		if (autoRollPos>autoRollPosDest) {
			autoRollPos -= autoRollSpeed * speedScale * ztimer.GetFrameTimeF(); 
			if (autoRollPos<autoRollPosDest) autoRollPos = autoRollPosDest;
		} else {
		};

		{
			zERR_ASSERT (vob);

			// aktuellen Roll-Winkel messen
			// FIXME: das acos() koennte mann sich sparen, wenn die vob::Rotates endlich auch bogenmass als params haetten..
//			zREAL dot		= zVEC3(0,1,0) * vob->GetRightVectorWorld();
//			zREAL dot		= vob->GetRightVectorWorld()[VY];
			zREAL dot		= vob->trafoObjToWorld.GetRightVector()[VY];
			zClamp (dot, zREAL(-1), zREAL(+1));
			zREAL actAngle	= 90 - Alg_Rad2Deg(acosf(dot));

			zREAL relAngle = (autoRollPos * autoRollMaxAngle) - actAngle; 

			if ( zAbs(actAngle+relAngle)<=autoRollMaxAngle)
			{
				vob->RotateLocalZ ( relAngle);
			}

		};
	};

	// Grund: Matrix clean halten, (verschluckte Collision-Rotates so bereinigen (ugly))
	if (autoRollPos==0) 
	if (oldState!=zMV_STATE_DIVE)
	{
//		if (oldPos!=autoRollPos) vob->ResetXZRotations();
//		else
		{
			zREAL dot = vob->trafoObjToWorld.GetRightVector()[VY];
			if (zAbsApprox(dot)>0.0001F) {
//				zerr.Message ("D: go: "+zSTRING(dot));
				vob->ResetXZRotationsWorld ();
			};
		};
	};
//	screen->Print (0,400, zSTRING(autoRollPos,4)+", "+zSTRING(autoRollPosDest,4));
};

void zCAIPlayer::ResetAutoRoll ()
{
	zERR_ASSERT (vob);
	if (!vob)					return;
	if (!vob->GetHomeWorld())	return;
	autoRollPosDest = autoRollPos = 0;
	vob->ResetXZRotationsWorld();
};

#ifdef ZENGINE_AIPLAYER
zBOOL zCAIPlayer::KeyPressed (int key)
{
	if (irgnoreKeyBoard)	return FALSE;
	else					return zinput->KeyPressed (key);
};
#endif

void zCAIPlayer::CalcModelAnisInPlace ()
{
	if (vob->GetPhysicsEnabled()) 
	{
		modelAnisInPlace = FALSE;
		return;
	};

	for (int i=0; i<model->GetNumActiveAnis(); i++)
		if (!model->aniChannels[i]->GetAni()->FlagInPlace()) { modelAnisInPlace= FALSE; return; };
	modelAnisInPlace = TRUE;
};

#ifdef ZENGINE_AIPLAYER
#endif

#ifdef ZENGINE_AIPLAYER
void zCAIPlayer::DoStateSwitch ()
{
	// ==================================================================================

	////////////////////////////
	//		S_FALL			  //
	////////////////////////////

	if (model->IsStateActive("S_FALLDN")) 
	{
		// Model faellt (macht nur Sinn mit eingeschalteter Physik)
		// Physik einschalten, falls dies noch nicht getan
//		if (!vob->GetPhysicsEnabled()) SetPhysicsEnabled (TRUE);

		// Auf Lande-Condition checken
		if (waterLevel==2) { 
			if (headY<GetWaterY()) {
//				SetPhysicsEnabled		(FALSE); 
				model->StartAni			("T_FALLDN_2_DIVE");		// T_FALL_2_DIVE
			} 
/*			else if (
//				(velocityLen2<zMV_MAX_VEL_FALL_2_SWIM2) && 
				(headY<GetWaterY()+30)) {
				model->StartAni			("S_SWIM");				// T_FALL_2_SWIM
			};*/
		} else
		if (aboveFloor<zMV_LAND_HEIGHT) { 
			// akzeptable Hoehendifferenz => Model-Hoehe stumpf korrigieren
			LandAndStartAni	("T_FALLDN_2_STAND");
		};
	}

	if (irgnoreKeyBoard) goto leave;

	if (model->IsStateActive("S_FALL")) {
		if (aboveFloor<zMV_LAND_HEIGHT) { 
			// akzeptable Hoehendifferenz => Model-Hoehe stumpf korrigieren
			LandAndStartAni	("T_FALL_2_FALLEN");
		};
	};
	/*	if (model->IsStateActive("S_FALLEN")) {
			if (force_z!=0) model->StartAni ("S_RUN");
		};
	*/

	/*******************************************************************************/
	/*		STAND / WALK / RUN / JUMP 											   */
	/*******************************************************************************/
	if (model->IsAniActive("S_1HWALK")) {
		if (KeyPressed(KEY_LCTRL))	model->StartAni ("T_1HWALK_2_1HSAIM");
		if (KeyPressed(KEY_LALT))	model->StartAni ("S_RUN");
	} else
	if (model->IsAniActive("S_1HSAIM")) {
		if (!KeyPressed(KEY_LCTRL)) model->StartAni ("T_1HSAIM_2_1HWALK");
	} else

	if (model->IsAniActive("S_FISTRUN")) {
		// cd-stat wieder anschalten nachdem climbUpLedge
		SetCDStat (TRUE);

		// Reset Rotationen, falls vorher getaucht wurde
		if (oldState==zMV_STATE_DIVE) {
			vob->ResetXZRotationsWorld();
		};

		if ((waterLevel==2) && (headY<GetWaterY())) {
			model->StartAni	("S_DIVE");							// T_STAND_2_DIVE
		} else

		if (force_z>0) {
			if (CheckEnoughSpaceMoveForward ()) {
				// Wasser ?
				if (waterLevel==0) {
					if (!KeyPressed(KEY_LSHIFT))	{ model->StartAni ("T_FISTRUN_2_FISTRUNL"); } 
					else							{ model->StartAni ("T_FISTWALK_2_FISTWALKL"); };
				} else
				if (waterLevel==1) model->StartAni ("T_WALKL_2_WALKWL"); else
				if (waterLevel==2) model->StartAni ("S_SWIMF");						// T_STAND_2_SWIMF
			};
		} else
		if (force_z<0) {
			// Wasser ?
			if (waterLevel==0) { if (CheckEnoughSpaceMoveBackward()) model->StartAni ("T_FISTWALK_2_FISTWALKBL"); } else
			if (waterLevel==1) { if (CheckEnoughSpaceMoveBackward()) model->StartAni ("T_FISTWALK_2_FISTWALKBL"); } else
			if (waterLevel==2) model->StartAni ("S_SWIMB");						// T_STAND_2_SWIMB
		} else {
			// nicht nach vorne/hinten
			// Wasser ?
			if (waterLevel==2) {
				// FIXME: evtl. hier Physik/S_FALL mit Übergang zu S_SWIM, wenn Kopf zu hoch über Wasser
//				SetPhysicsEnabled		(TRUE);
//				model->StartAni			("S_FALLDN"); 
				model->StartAni ("S_SWIM");							// T_STAND_2_SWIM 
				goto leaveS_STAND_;
			};
				 if ((KeyPressed(KEY_PAD_END))  && (CheckEnoughSpaceMoveLeft()))	model->StartAni ("T_FISTRUNSTRAFEL"); 
			else if ((KeyPressed(KEY_PAD_PGDN)) && (CheckEnoughSpaceMoveRight()))model->StartAni ("T_FISTRUNSTRAFER"); 
			else if (KeyPressed(KEY_LALT))		
			{	
				if (KeyPressed(KEY_LSHIFT)) {
					model->StartAni ("T_JUMPSTAND_2_JUMP"); 
				} else {
					// Jump up
					zPOINT3 ledgePoint;
					zBOOL	foundLedge = DetectClimbUpLedge (ledgePoint, TRUE);
					if (foundLedge)
					{
						// Hier nach Ziel-Hoehe klassifizieren: hi/mid/low -Jump
						zREAL ledgeYDist = ledgePoint[VY]-feetY;
						Print ("feetY: "+zSTRING(feetY)+", ledgeY: "+zSTRING(ledgePoint[VY]));
						if (ledgeYDist>config.zMV_YMAX_JUMPMID)	model->StartAni ("T_STAND_2_JUMPUP"		); else
						if (ledgeYDist>config.zMV_YMAX_JUMPLOW)	model->StartAni ("T_STAND_2_JUMPUPMID"	); else
						if (ledgeYDist>config.zMV_STEP_HEIGHT)		model->StartAni ("T_STAND_2_JUMPUPLOW"	); else
						{ 
							// Kante zu niedrig, also nur nach oben springen
							foundLedge=FALSE; 
							model->StartAni ("T_STAND_2_JUMPUP"); 
						};
					} else {
						// Pruefen, ob Decke zu flach ist, um vernuenftig springen zu koennen
//						if ((ceilingY-headY)>=zMV_JUMP_UP_MIN_CEIL) 
//							model->StartAni ("T_STAND_2_JUMPUP"); 
					};
				};
			} 
//			else if (KeyPressed(KEY_LEFT))	model->StartAni ("T_FISTRUNTURNL");
//			else if (KeyPressed(KEY_RIGHT))	model->StartAni ("T_FISTRUNTURNR");
			else if (KeyPressed(KEY_E)) {
				model->StartAni ("T_X_2_1H_STAND");
//				if (shield_equiped)
//				model->StartAni ("T_1H_SHIELD_READY");
			} 
leaveS_STAND_:;
		};
	} else
	if (model->IsAniActive("S_FISTRUNL")) {
		if (CheckForceModelHalt ("T_FISTRUNL_2_FISTRUN")) {} else

		if (force_z<=0) {
			zREAL perc = model->GetProgressPercent("S_FISTRUNL");
			if ((perc<0.10F) || (perc>0.90F))
				model->StartAni ("T_FISTRUNL_2_FISTRUN");
			else 
			if ((perc>0.40F) && (perc<0.60F))
				model->StartAni ("T_FISTRUNR_2_FISTRUN");
//			model->StartAni ("T_RUN_2_STAND");
		} else {
			// Wasser ?
			if (waterLevel==1)			model->StartAni ("T_FISTRUNL_2_FISTWALKWL"); else
			if (waterLevel==2)			{
				StartPhysicsWithVel		();
				StartFallDownAni		();
//				model->StartAni ("T_SWIM_2_DIVE"); // T_RUN_2_DIVE
			} else
			if (KeyPressed(KEY_LSHIFT))	model->StartAni ("T_FISTRUNL_2_FISTWALKL"); 
			if (KeyPressed(KEY_LALT))	model->StartAni ("T_FISTRUNL_2_JUMP");
		};
		if (KeyPressed(KEY_E)) model->StartAni ("T_X_2_1H_STAND");
	} else
	if (model->IsAniActive("S_FISTWALK")) {
		model->StartAni (_s_run);
	} else
	if (model->IsStateActive("S_FISTWALKBL")) {
		if (force_z>=0) model->StartAni ("T_FISTWALKBL_2_FISTWALK");
	} else

	if (model->IsAniActive("S_FISTWALKL")) {
		if (CheckForceModelHalt ("T_FISTWALKL_2_FISTWALK")) {} else
		if (force_z<=0) {
			model->StartAni ("T_FISTWALKL_2_FISTWALK");
		} else {
			// Wasser ?
			if (waterLevel==1) model->StartAni ("T_FISTWALK_2_FISTWALKW"); else
			if (waterLevel==2) { 
				StartPhysicsWithVel		();
				StartFallDownAni		();						// T_WALK_2_SWIMF
			} else
			if (!KeyPressed(KEY_LSHIFT))	model->StartAni ("T_FISTWALKL_2_FISTRUNL"); else
			if (KeyPressed(KEY_LALT))	model->StartAni ("T_FISTRUN_2_JUMP");
		};
		if (KeyPressed(KEY_E)) model->StartAni ("T_X_2_1H_STAND");
	} else


	//////////////////////////////
	//		S_SLIDE   etc.		//
	//////////////////////////////

	if ((model->IsAniActive("S_SLIDE")) ||
		(model->IsAniActive("S_SLIDEB")))
	{
		// Wasser ?
		if (waterLevel==0) {} else
		if (waterLevel==1) {
			model->StartAni					("S_WALK"); 
			SetPhysicsEnabled				(FALSE);
			vob->GetRigidBody()->SetMode	(zPHY_RBMODE_FLY);
			Print							("Slide STATE: end => S_WALK");
		} else
		if (waterLevel==2) {
			model->StartAni					("S_SWIM"); 
			SetPhysicsEnabled				(FALSE);
			vob->GetRigidBody()->SetMode	(zPHY_RBMODE_FLY);
			Print							("Slide STATE: end => S_SWIM");
		};
	} else
		 
	if (model->IsStateActive("S_JUMPSTAND")) {
		model->StartAni						(_s_run);
	} else

	if (model->IsStateActive("S_WALKBL")) { 
		if (CheckForceModelHalt ("T_WALKBL_2_WALK")) {} else
		if (force_z>=0) 
			model->StartAni					("T_WALKBL_2_WALK");
	} else

	//////////////////////////////
	//		S_JUMP_UP			//
	//////////////////////////////

	if (model->IsStateActive("S_JUMPUP")) { 
		// Zustand gerade gestartet => Physik anschmeissen
		if (!vob->GetPhysicsEnabled()) { 
			Print ("ph on");
//				SetCDStat						(FALSE);
			SetPhysicsEnabled					(TRUE);
			vob->GetRigidBody()->ApplyImpulse	(zVEC3(0,config.zMV_FORCE_JUMP_UP,0), vob->GetPositionWorld());		// FIXME: einheiten ?? [Moos] 1/100 Ns. :-)
//			vob->SetPositionWorld				(newCenter); 
			goto leaveJUMP_UP;													// muss, er darf nicht _sofot_ auf Landung pruefen
		}; 
		// Landung einleiten ?
		if ((feetY<=GetFloorY()) && (velocity[VY]<0)) {
			Print ("land ");
//			model->StartAni					("T_JUMPUP_2_STAND");
//			SetPhysicsEnabled				(FALSE); 
//			AlignToFloor					(GetFloorY());
//			LandAndStartAni ("T_JUMPUP_2_FALLDN");
			LandAndStartAni ("T_FALLDN_2_STAND");
			
			goto leaveJUMP_UP;
		};
		// im Sprung Decke gestossen ?
		if (velocity[VY]>0)
		if ((headY-GetCeilingY())>0) 
		{
			Print ("ceil");
			// abrupt halten, exakte Korrektur, dann wirkt aber wieder grav
			vob->GetRigidBody()->StopTranslation	();
			vob->MoveLocal							(0, -(headY-GetCeilingY()) -4,0);
		};
		// An Ledge haengen ?
		if (GetFoundLedge())
		{
			if (velocity[VY]>=0)
			if ((headY-GetLastLedgePoint()[VY])>0) {
				Print ("ledge2");
				AlignModelToLedge ("S_HANG");		// S_HANG
			};
		};
leaveJUMP_UP:;
	} else

	////////////////////////////
	//		S_STAND			  //
	////////////////////////////

	if (model->IsAniActive("S_RUN")) {
//	if ((model->IsStateActive("S_RUN")) || (model->IsAniActive("S_FISTRUN"))) {

		// cd-stat wieder anschalten nachdem climbUpLedge
		SetCDStat (TRUE);

		// Reset Rotationen, falls vorher getaucht wurde
		if (oldState==zMV_STATE_DIVE) {
 			vob->ResetXZRotationsWorld();
		};

		if ((waterLevel==2) && (headY<GetWaterY())) {
 			model->StartAni	("S_DIVE");							// T_STAND_2_DIVE
		} else

		if (force_z>0) {
			if (KeyPressed(KEY_LSHIFT))	
			{ 
				// SHIFT
				if (CheckEnoughSpaceMoveForward (FALSE))
				{
					if (waterLevel==0) model->StartAni ("T_WALK_2_WALKL");		else
					if (waterLevel==1) model->StartAni ("T_WALKL_2_WALKWL");	else
					if (waterLevel==2) model->StartAni ("S_SWIMF");						// T_STAND_2_SWIMF
				};
			} else 
			{
				// OHNE SHIFT
				if (CheckEnoughSpaceMoveForward (TRUE))		// TRUE= losrennen!
				{
					// Wasser ?
					if (waterLevel==0) model->StartAni ("T_RUN_2_RUNL");		else
					if (waterLevel==1) model->StartAni ("T_WALKL_2_WALKWL");	else
					if (waterLevel==2) model->StartAni ("S_SWIMF");						// T_STAND_2_SWIMF
				};
			};
		} else
		if (force_z<0) {
			// Wasser ?
			if (waterLevel==0) { if (CheckEnoughSpaceMoveBackward()) model->StartAni ("T_WALK_2_WALKBL"); } else
			if (waterLevel==1) { if (CheckEnoughSpaceMoveBackward()) model->StartAni ("T_WALK_2_WALKBL"); } else
			if (waterLevel==2) model->StartAni ("S_SWIMB");						// T_STAND_2_SWIMB
		} else {
			// nicht nach vorne/hinten
			// Wasser ?
			if (waterLevel==2) {
				// FIXME: evtl. hier Physik/S_FALL mit Übergang zu S_SWIM, wenn Kopf zu hoch über Wasser
//				SetPhysicsEnabled		(TRUE);
//				model->StartAni			("S_FALLDN"); 
				model->StartAni ("S_SWIM");							// T_STAND_2_SWIM 
				goto leaveS_STAND;
			};
				 if ((KeyPressed(KEY_PAD_END))  && (CheckEnoughSpaceMoveLeft()))	model->StartAni ("T_RUNSTRAFEL"); 
			else if ((KeyPressed(KEY_PAD_PGDN)) && (CheckEnoughSpaceMoveRight()))model->StartAni ("T_RUNSTRAFER");
			else if (KeyPressed(KEY_LALT))		{	
				if (KeyPressed(KEY_LSHIFT)) {
					model->StartAni ("T_JUMPSTAND_2_JUMP"); 
				} else {
					// Jump up
					zPOINT3 ledgePoint;
					zBOOL foundLedge = DetectClimbUpLedge (ledgePoint, TRUE);
					if (foundLedge)
					{
						// Hier nach Ziel-Hoehe klassifizieren: hi/mid/low -Jump
						zREAL ledgeYDist = GetLastLedgePoint()[VY]-feetY;
						Print ("feetY: "+zSTRING(feetY)+", ledgeY: "+zSTRING(GetLastLedgePoint()[VY]));
						if (ledgeYDist>config.zMV_YMAX_JUMPMID)	model->StartAni ("T_STAND_2_JUMPUP"			); else
						if (ledgeYDist>config.zMV_YMAX_JUMPLOW)	model->StartAni ("T_STAND_2_JUMPUPMID"	); else
						if (ledgeYDist>config.zMV_STEP_HEIGHT)	model->StartAni ("T_STAND_2_JUMPUPLOW"	); else
						{ 
							// Kante zu niedrig, also nur nach oben springen
							foundLedge=FALSE; 
							model->StartAni ("T_STAND_2_JUMPUP"); 
						};
					} else {
						// Pruefen, ob Decke zu flach ist, um vernuenftig springen zu koennen
//						if ((GetCeilingY()-headY)>=zMV_JUMP_UP_MIN_CEIL) 
//							model->StartAni ("T_STAND_2_JUMPUP"); 
					};
				};
			} 
			else if (KeyPressed(KEY_LEFT))	model->StartAni ("T_RUNTURNL");
			else if (KeyPressed(KEY_RIGHT))	model->StartAni ("T_RUNTURNR");
			else if (KeyPressed(KEY_E)) {
				model->StartAni ("T_X_2_1H_STAND");
//				if (shield_equiped)
//				model->StartAni ("T_1H_SHIELD_READY");
			} 
leaveS_STAND:;
		};
	}

	if (model->IsAniActive ("T_RUNTURNL")) {
		if (!KeyPressed(KEY_LEFT)) model->FadeOutAni (model->GetAniFromAniName(zSTRING("T_RUNTURNL")));
	} else
	if (model->IsAniActive ("T_RUNTURNR")) {
		if (!KeyPressed(KEY_RIGHT)) model->FadeOutAni (model->GetAniFromAniName(zSTRING("T_RUNTURNR")));
	};


	////////////////////////////////
	//		S_JUMPUPMID			  //
	////////////////////////////////
{	
	if (model->IsAniActive("T_STAND_2_JUMPUPMID")) {
		// ani0: Schwung holen, ani1: Flugphase, ani2: Kontakt mit Kante
		jumpLowMidPass	= 0;
		SetCDStat (FALSE);									// Dieses ist eine kritische Ani (Interrupt-Anis nicht erlaubt)
	} else
	if (model->IsAniActive("S_JUMPUPMID")) {
		if (jumpLowMidPass!=1) {

			// hier wird versucht die Y-Hoehe aus den Anis zu ermitteln, die der Sprung als Default überwindet
			zCModelAni *ani1= model->GetAniFromAniName("T_JUMPUPMID_2_STAND");
			zCModelAni *ani2= model->GetAniFromAniName("T_STAND_2_JUMPUPMID");
			if (ani1 && ani2) 
			{
				zVEC3 y1			= model->GetAniTrans(ani1, ani1->GetNumFrames()-1,ani1->GetRootNodeIndex());
				zVEC3 y2			= model->GetAniTrans(ani2, 0,ani2->GetRootNodeIndex());
				zVEC3 aniDelta		= y1-y2;
				aniDelta			= vob->trafoObjToWorld.Rotate (aniDelta);
				zVEC3 realDelta		= (GetLastLedgePoint()- zVEC3(centerPos[VX], GetFloorY(), centerPos[VZ]));
//				zVEC3 realDeltaNorm	= realDelta;	realDeltaNorm.NormalizeApprox();
//				realDeltaNorm[VY]	= 0;
//				zREAL offsetDist	= (this->model->GetBBox3DLocalFixed().maxs[VZ]-this->model->GetBBox3DLocalFixed().mins[VZ]) * zREAL(0.5F);
//				realDelta			= realDelta + realDeltaNorm * zREAL(35.0F);
				realDelta[VX]		*= zREAL(1.4F);
				realDelta[VZ]		*= zREAL(1.4F);
				zVEC3 jumpMidDiff	= aniDelta - realDelta;
				zREAL jumpMidtime	= model->GetAniFromAniName("S_JUMPUPMID")->GetAniTimeLength();
				jumpLowMidVel		= -(jumpMidDiff / jumpMidtime);
			};
			jumpLowMidPass		= 1;

		} 
		vob->Move (ztimer.GetFrameTimeF() * jumpLowMidVel);
	} else
	if (model->IsStateActive("T_JUMPUPMID_2_STAND")) { 
		if (jumpLowMidPass==1) {
//			vob->Move			(ledgePoint - GetHandPositionWorld());
//			vob->SetHeadingAt	(ledgeNormal);
			jumpLowMidPass=2;
		};
	};
 /*
   0cm .. 100cm		JUMPUPLOW
 100cm .. 200cm		JUMPUPMID
 200cm .. x			JUMPUP

Der Animationssatz fuer JumpUpLow (alos T_JUMPUPXXX_2_STANDT_STAND_2_JUMPUPXXX,S_JUMPUPXXX,T_JUMPUPXXX_2_STAND)
sollte auf 100cm geeicht sein. D.h. in MAX ueberwindet diese Animation komplett abgespielt 100cm. Die Engine passt
ueber Interpolation die Animation selbststaendig auf andere Höhenunterschiede an. Analog fuer JumpUpMid.
JUMPUPMID sollte auf 150cm geeicht sein (minimiert den Fehler, da der gueltige Bereich zw. 100cm und 200cm liegt.).


  T_STAND_2_JUMPUPXXX:
	Schwung holen, die Fuesse verlassen allerdings noch nicht den Boden.

  S_JUMPUPXXX
	Die Flugphase. Beim ersten Frame wird der Boden verlassen. Es allerdings wichtig, das diese Animation 
	aus mehreren Frames besteht (je mehr, desto optisch besser koennen verschiedene Höhenunterschiede durch die 
	Engine interpoliert ueberwunden werden)

  T_JUMPUPXXX_2_STAND
	Beim ersten Frame wird der Kontakt mit der Kante hergestellt. Der Rest der Ani richtet die Figur wieder in die 
	Standhaltung auf. Das Programm ermittelt aus dem ersten Frame der S_JUMPUPXXX Ani und dem ersten Frame dieser 
	Ani den durch die Ani ueberwundenen Hoehenunterschied. Beim ersten Frame wird die Figur in Orientierung und
	absoluter Hoehe an der Kante ausgerichtet. Bei JumpUpLow wird dabei die durchschnittliche Position der Fuesse
	genommen, bei JumpUpMid die durchschnittliche Position der Haende.

 */
	////////////////////////////////
	//		S_JUMPUPLOW			  //
	////////////////////////////////

	if (model->IsAniActive("T_STAND_2_JUMPUPLOW")) {
		jumpLowMidPass	= 0;
		SetCDStat (FALSE);									// Dieses ist eine kritische Ani (Interrupt-Anis nicht erlaubt)
	} else
	if (model->IsAniActive("S_JUMPUPLOW")) {
		if (jumpLowMidPass!=1) {
			// hier wird versucht die Y-Hoehe aus den Anis zu ermitteln, die der Sprung als Default überwindet
			zCModelAni *ani1= model->GetAniFromAniName("T_JUMPUPLOW_2_STAND");
			zCModelAni *ani2= model->GetAniFromAniName("T_STAND_2_JUMPUPLOW");
			if (ani1 && ani2) 
			{
				zVEC3 y1			= model->GetAniTrans(ani1, ani1->GetNumFrames()-1,ani1->GetRootNodeIndex());
				zVEC3 y2			= model->GetAniTrans(ani2, 0,ani2->GetRootNodeIndex());
				zVEC3 aniDelta		= y1-y2;
				aniDelta			= vob->trafoObjToWorld.Rotate (aniDelta);
				zVEC3 realDelta		= (GetLastLedgePoint()- zVEC3(centerPos[VX], GetFloorY(), centerPos[VZ]));
//				zVEC3 realDeltaNorm	= realDelta;	realDeltaNorm.NormalizeApprox();
//				realDeltaNorm[VY]	= 0;
//				realDelta			= realDelta + realDeltaNorm * zREAL(35.0F);
				realDelta[VX]		*= zREAL(1.4F);
				realDelta[VZ]		*= zREAL(1.4F);
				zVEC3 jumpMidDiff	= aniDelta - realDelta;
				zREAL jumpMidtime	= model->GetAniFromAniName("S_JUMPUPLOW")->GetAniTimeLength();
				jumpLowMidVel		= -(jumpMidDiff / jumpMidtime);
			};
			jumpLowMidPass		= 1;
		}
		vob->Move (ztimer.GetFrameTimeF() * jumpLowMidVel);
	} else
	if (model->IsStateActive("T_JUMPUPLOW_2_STAND")) {
		if (jumpLowMidPass==1) {
//			vob->Move			(ledgePoint - GetFeetPositionWorld());
//			vob->SetHeadingAt	(ledgeNormal);
			jumpLowMidPass=2;
		};
	};
};
	//////////////////////////////
	//		S_JUMP				//
	//////////////////////////////

	if (model->IsAniActive("S_JUMP")) {
		// Sprung nach vorne (letzter Loop-Frame)
		// Landung einleiten ?
		if ((waterLevel==2) && (feetY<=GetWaterY())) {
			// Landung auf Wasser
			StartPhysicsWithVel		();
			model->StartAni					("T_JUMP_2_FALLDN"); 
		} else
//		if ((aboveFloor<=0) && (velocity[VY]<0)) {  
		if ((aboveFloor<=0)) 
		{  
			// FIXME: Bedingung so ok ????
			// Landung auf Boden
			if (force_z>0)	LandAndStartAni	("T_JUMP_2_RUNL");	
			else			LandAndStartAni	("T_JUMP_2_STAND");
		} else {
			// wird gerade losgesprungen ? => Physik anschmeissen
			if (!vob->GetPhysicsEnabled()) {
				SetPhysicsEnabled					(TRUE);
				vob->GetRigidBody()->SetVelocity	(velocity*1.0);  
			};
		};
	} else

	//////////////////////////////
	//		T_STAND_2_JUMP		//
	//////////////////////////////

	if (model->IsAniActive("T_JUMPSTAND_2_JUMP")) {
		// Sprung nach vorne (Anlauf & Flugphase, bis zum Loop-Frame) 

		// Landung einleiten ?
		if ((waterLevel==2) && (feetY<=GetWaterY())) {
			// Landung auf Wasser
			StartPhysicsWithVel		();
			model->StartAni			("T_JUMP_2_FALL");
		} else { 
			zREAL perc = model->GetProgressPercent("T_JUMPSTAND_2_JUMP");
//			if ((aboveFloor<=0) && (velocity[VY]<0)) {
			if (aboveFloor<=0) {
				if (velocity[VY]<0) {
					if (perc>0.7) {
						LandAndStartAni	("T_JUMP_2_STAMD");
					};
				};
//				vob->SetPositionWorld  (newCenter);  
			};
		};
	} else

	////////////////////////////
	//		S_WALK			  //
	////////////////////////////
	if (model->IsAniActive("S_WALK")) {
		model->StartAni (_s_run);
	} else

	if (model->IsAniActive("S_WALKL")) {
		if (CheckForceModelHalt ("T_WALKL_2_WALK")) {} else
		if (force_z<=0) {
			model->StartAni ("T_WALKL_2_WALK");
		} else {
			// Wasser ?
			if (waterLevel==1) model->StartAni ("T_WALK_2_WALKWL"); else
			if (waterLevel==2) { 
				StartPhysicsWithVel		();
				StartFallDownAni		();						// T_WALK_2_SWIMF
			} else
			if (!KeyPressed(KEY_LSHIFT))	model->StartAni ("T_WALKL_2_RUNL"); else
			if (KeyPressed(KEY_LALT))	model->StartAni ("T_RUN_2_JUMP");
		};
		if (KeyPressed(KEY_E)) model->StartAni ("T_X_2_1H_STAND");
	} else

	////////////////////////////
	//		S_RUN			  //
	////////////////////////////

	if (model->IsAniActive("S_RUNL")) {
		if (CheckForceModelHalt ("T_RUNL_2_RUN")) {} else

		if (force_z<=0) {
			zREAL perc = model->GetProgressPercent("S_RUNL");
			if ((perc<0.10F) || (perc>0.90F))
				model->StartAni ("T_RUNL_2_RUN");
			else 
			if ((perc>0.40F) && (perc<0.60F))
				model->StartAni ("T_RUNR_2_RUN");
//			model->StartAni ("T_RUN_2_STAND");
		} else {
			// Wasser ?
			if ((waterLevel==1) && (GetFeetY()<GetWaterY()))		model->StartAni ("T_RUNL_2_WALKWL"); else
			if (waterLevel==2)			{
				StartPhysicsWithVel		();
				StartFallDownAni		();						// T_WALK_2_SWIMF
//				model->StartAni ("T_SWIM_2_DIVE"); // T_RUN_2_DIVE
			} else
			if (KeyPressed(KEY_LSHIFT))	model->StartAni ("T_RUNL_2_WALKL"); 
			if (KeyPressed(KEY_LALT))	model->StartAni ("T_RUNL_2_JUMP");
		};
		if (KeyPressed(KEY_E)) model->StartAni ("T_X_2_1H_STAND");
	} else

	//////////////////////////////
	//		S_HANG				//
	//////////////////////////////

	if (model->IsAniActive("S_HANG")) {
		model->StartAni ("T_HANG_2_STAND");
	} else



	/*******************************************************************************/
	/*		WALKWATER / SWIM / DIVE													*/
	/*******************************************************************************/

	{
		////////////////////////////
		//		S_WALKW			  //
		////////////////////////////

		if (model->IsAniActive("S_WALKWL")) {
			// waterLevel 1 (bis Brust)
			if (CheckForceModelHalt ("T_WALKWL_2_WALK")) {} else
			if (force_z<=0) {
				model->StartAni ("T_WALKWL_2_WALK");
			} else {
				// Wasser ?
				if (waterLevel==0) model->StartAni ("T_WALKWL_2_WALK"); else
				if (waterLevel==1) {} else
				if (waterLevel==2) 
					model->StartAni ("T_WALKWL_2_SWIMF"); 
			};
		} else

		if (model->IsStateActive("S_WALKWBL")) { 
			if (CheckForceModelHalt ("T_WALKWBL_2_WALK")) {} else
			if (force_z>=0) {
				model->StartAni ("T_WALKWBL_2_WALK");
			} else {
				// Wasser ?
				if (waterLevel==0) model->StartAni ("T_WALKWBL_2_WALK"); else
				if (waterLevel==1) {} else
				if (waterLevel==2) model->StartAni ("T_WALKWBL_2_SWIMB"); 
			};
		} else

		if (model->IsAniActive("S_WALKW")) { 
			// waterLevel 1 (bis Brust)
			if (force_z>=0) {
				model->StartAni ("T_WALKL_2_WALKWL");
			} else {
				// Wasser ?
	//			if (waterLevel==0) model->StartAni ("T_WALKWL_2_WALK"); else
	//			if (waterLevel==1) {} else
	//			if (waterLevel==2) model->StartAni ("T_WALKWL_2_SWIMF"); 
			};
		}
 // KEIN else
		////////////////////////////
		//		S_SWIM			  //
		////////////////////////////

		if (model->IsAniActive("S_SWIM")) {
			// waterLevel 2
			state = zMV_STATE_SWIM;
			
			// Reset Rotationen, falls vorher getaucht wurde
	//		if (model->IsStateActive("S_SWIM")) 
			if (oldState!=zMV_STATE_SWIM) {
				vob->ResetXZRotationsWorld();
			};

			// Wasser ?
			if (waterLevel==0) { model->StartAni (_s_run); goto leaveS_SWIM; } else
			if (waterLevel==1) { model->StartAni (_s_run); goto leaveS_SWIM; } else
			if (waterLevel==2) {};
			if (KeyPressed(KEY_UP  ))	{ if (CheckEnoughSpaceMoveForward())	model->StartAni ("T_SWIM_2_SWIMF"); } else
			if (KeyPressed(KEY_DOWN))	{ if (CheckEnoughSpaceMoveBackward())	model->StartAni ("T_SWIM_2_SWIMB"); } else
			if (KeyPressed(KEY_LCTRL)) {
				// am Beckenrand hochziehen
				zPOINT3 ledgePoint;
				if (DetectClimbUpLedge (ledgePoint))
				{
					Print ("found ledge");
					// Rand in Armreichweite ?
					if (zAbs(GetLastLedgePoint()[VY]-headY)<config.zMV_YMAX_SWIM_CLIMB_OUT) {
						AlignModelToLedge ("S_HANG");
						goto leaveS_SWIM;
					};
				};
				// Kein Hochziehen, sondern abtauchen
				model->StartAni ("T_SWIM_2_DIVE");
			};
	leaveS_SWIM:;
		} else

		////////////////////////////
		//		S_SWIMF			  //
		////////////////////////////

		if (model->IsAniActive("S_SWIMF")) {
			// waterLevel 2
			state = zMV_STATE_SWIM;

			if (CheckForceModelHalt ("T_SWIMF_2_SWIM")) {} else
			if (!KeyPressed(KEY_UP)) {
				model->StartAni ("T_SWIMF_2_SWIM");
			} else {
				// Wasser ?
				if (waterLevel==0) {
	//				model->StartAni ("S_WALK");  
					model->StartAni ("T_SWIMF_2_WALKWL"); 
				} else
				if (waterLevel==1) model->StartAni ("T_SWIMF_2_WALKWL"); else
				if (waterLevel==2) {};
			};
		};

		////////////////////////////
		//		S_SWIMB			  //
		////////////////////////////
 
		if (model->IsAniActive("S_SWIMB")) {
			// waterLevel 2 
			state = zMV_STATE_SWIM;

			if (CheckForceModelHalt ("T_SWIMB_2_SWIM")) {} else
			if (!KeyPressed(KEY_DOWN)) { 
				model->StartAni ("T_SWIMB_2_SWIM");
			} else {
				// Wasser ?
				if (waterLevel==0) model->StartAni ("T_SWIMB_2_WALKBL");	else
				if (waterLevel==1) model->StartAni ("T_SWIMB_2_WALKWBL"); else
				if (waterLevel==2) {};
			};
		};
	};

///////////
// DIVE
///////////


	////////////////////////////
	//		S_DIVE			  //
	////////////////////////////

	if (model->IsAniActive("S_DIVE")) {
		// waterLevel 2
		state = zMV_STATE_DIVE;

		if (vob->GetPhysicsEnabled()) {
			// Falls z.B. von ausserhalb in tiefes Wasser gesprungen wird (=Physik an), wird sie hier ausgestellt
			// IsStateActive() => sorgt fuer gewisse Verzoegerung, also solange bis nur noch S_DIVE aktiv ist
			if (model->IsStateActive("S_DIVE")) SetPhysicsEnabled		(FALSE); 
		};

		// Wasser ?
		if (waterLevel==0) {	model->StartAni (_s_run); goto leaveS_DIVE; } else		// T_DIVE_2_STAND
		if (waterLevel==1) {	model->StartAni (_s_run); goto leaveS_DIVE; } else		// T_DIVE_2_STAND
		if (waterLevel==2) {};
		// Auftauchen ?
//		if (headY>GetWaterY())		{ model->StartAni ("T_DIVEF_2_SWIM", zCModel::zMDL_STARTANI_FORCE);	} else
		if (headY>GetWaterY())		{ model->StartAni ("S_SWIM");	} else
		if (KeyPressed(KEY_LALT))	{ if (CheckEnoughSpaceMoveForward()) model->StartAni ("T_DIVE_2_DIVEF"); };
		
leaveS_DIVE:;
	} else

	////////////////////////////
	//		S_DIVEF			  //
	////////////////////////////

	if (model->IsAniActive("S_DIVEF")) {
		// waterLevel 2
		state = zMV_STATE_DIVE;

		if (CheckForceModelHalt ("T_DIVEF_2_DIVE")) {} else
		// Wasser ?
		if (waterLevel==0) {	model->StartAni (_s_run); goto leaveS_DIVEF; } else		// T_DIVEF_2_STAND
		if (waterLevel==1) {	model->StartAni (_s_run); goto leaveS_DIVEF; } else		// T_DIVEF_2_STAND
		if (waterLevel==2) {};
		// Auftauchen ?
//		if (headY>GetWaterY())		{ model->StartAni ("T_DIVEF_2_SWIM", zCModel::zMDL_STARTANI_FORCE);	} else
//		if (headY>GetWaterY())		{ model->StartAni ("S_SWIM", zCModel::zMDL_STARTANI_FORCE);	} else
		if (headY>GetWaterY())		{ model->StartAni ("S_SWIM");	} else
		if (!KeyPressed(KEY_LALT))	model->StartAni ("T_DIVEF_2_DIVE");

leaveS_DIVEF:;
	} else


/*******************************************************************************/
/*		1H - WEAPON															   */
/*******************************************************************************/

	////////////////////////////
	//		S_1H_STAND		  //
	////////////////////////////

	if (model->IsAniActive("S_1H_STAND")) {
		if (force_z>0) {
			// Walk
			model->StartAni ("T_1H_STAND_2_WALK_F");
		} else
		if (force_z<0) {
			model->StartAni ("T_1H_STAND_2_WALK_B");
		} else
		if (KeyPressed(KEY_E)) {
			model->StartAni ("T_1H_STAND_2_STAND");
//				if (shield_equiped)
//				model->StartAni ("T_1H_SHIELD_AWAY");
		}
		else
		if (KeyPressed(KEY_LCTRL)) model->StartAni ("T_1H_STAND_2_ACTION");
	} else

	////////////////////////////
	//		S_1H_WALK_F		  //
	////////////////////////////

	if (model->IsAniActive("S_1H_WALK_F")) {
		if (force_z<=0) {
			model->StartAni ("T_1H_WALK_F_2_STAND");
		} else
		if (KeyPressed(KEY_E)) model->StartAni ("T_1H_STAND_2_STAND");
		else
		if (KeyPressed(KEY_LCTRL)) model->StartAni ("T_1H_STAND_2_ACTION"); 
	} else

	////////////////////////////
	//		S_1H_WALK_B		  // 
	////////////////////////////

	if (model->IsAniActive("S_1H_WALK_B")) {
		if (force_z>=0) {
			model->StartAni ("T_1H_WALK_B_2_STAND");
		} else
		if (KeyPressed(KEY_E)) model->StartAni ("T_1H_STAND_2_STAND");
		else
		if (KeyPressed(KEY_LCTRL)) model->StartAni ("T_1H_STAND_2_ACTION");
	} else

	////////////////////////////
	//		S_1H_ACTION		  // 
	////////////////////////////

	if (model->IsAniActive("S_1H_ACTION")) {
		if (!KeyPressed(KEY_LCTRL)) model->StartAni ("T_1H_ACTION_2_STAND");
		else
		if (force_z>0) model->StartAni ("T_1H_SLASH1");
	} else
	{ }; // safe..

	goto leave;
leave:;

	  
	if (KeyPressed(KEY_LSHIFT)) 
	if (KeyPressed(KEY_LCTRL)) {
		model->StartAni ("S_1HWALK");  
	};
	if (model->IsAniActive("S_1HWALK")) {
		if (KeyPressed(KEY_LCTRL)) {
			model->StartAni ("T_1HWALK_2_1HSAIM");  
		};
	};
	if (model->IsAniActive("S_1HSAIM")) {
		if (!KeyPressed(KEY_LCTRL))	model->StartAni ("T_1HSAIM_2_1HWALK");
		if (KeyPressed(KEY_DOWN))	model->StartAni ("T_1HSAIM_2_1HSDEFEND");
	};
	if (model->IsAniActive("S_1HSDEFEND")) {
		if (!KeyPressed(KEY_DOWN))	model->StartAni ("T_1HSDEFEND_2_1HSAIM");
	};


	if (KeyPressed(KEY_F6)) 
		model->StartAni ("S_FOOD_S0"); 
	if (KeyPressed(KEY_F7)) 
		model->StartAni ("T_FOOD_RANDOM_1");
//	if (KeyPressed(KEY_O))		model->StartAni ("S_CIRCLE"); 
	if (KeyPressed(KEY_F8)) model->StartAni (_s_run); 

/*
	{
		static float xc = 0.5F;
		static float yc = 0.5F;

		zCModelAni* ani;
		ani = model->GetAniFromAniName ("S_BOWAIM");
//		ani = model->GetAniFromAniName ("S_BOWAIM");
//		ani = model->GetAniFromAniName ("S_LOOK");

//		if (KeyPressed(KEY_F6)) model->StartAni ("T_1HSAT1");
//		if (KeyPressed(KEY_F5)) model->StartAni ("BOW_SHOOT");
		if (KeyPressed(KEY_F6)) model->StartAni ("S_BOWAIM");
//		if (KeyPressed(KEY_F7)) {
//			zCMesh* mesh = zCMesh::Load ("arrow.3ds");
//			zCModelNodeInst *node = model->SearchNode ("ZS_RIGHTHAND");
//			node->SetNodeMesh (mesh);
//		};

		if (zinput->KeyPressed(KEY_R    )) xc = yc = 0.5F;
		if (zinput->KeyPressed(KEY_UP   )) yc -= 0.1F;
		if (zinput->KeyPressed(KEY_DOWN )) yc += 0.1F;
		if (zinput->KeyPressed(KEY_LEFT )) xc -= 0.1F;
		if (zinput->KeyPressed(KEY_RIGHT)) xc += 0.1F;
		if (xc<0) xc=0; else
		if (xc>1) xc=1;
		if (yc<0) yc=0; else
		if (yc>1) yc=1;
		screen->Print (0,4000, zSTRING(xc,4)+", "+zSTRING(yc,4));
		model->SetCombineAniXY ( ani->GetAniID(), xc , yc );
	};
*/
};
#endif

#ifdef ZENGINE_AIPLAYER
void zCAIPlayer::CheckWeaponCollisions()
{
	zCModelNodeInst *weaponNode = model->SearchNode ("ZS_RIGHTHAND");
	if ((weaponNode) && (weaponNode->GetNodeVisual()))
	{
		// Model-Limb Collision Test
		zCList<zCVob::zTModelLimbColl>	resCollList;
		vob->CheckModelLimbCollision (weaponNode, TRUE, resCollList);
		if (resCollList.GetNumInList()!=0) 
		{
			// Hier kann nun fuer jeden Vob eine Liste von Model-Limbs erfragt werden..
			// zerr.Message ("Num Vobs hit: "+zSTRING(resCollList.GetNumInList()));

			vob->EndMovement();		// !! NOETIG !!
			zSTRING s;
			if (resCollList.Get(0)->hitModelNodeList.Get(0)) {
				s = resCollList.Get(0)->hitModelNodeList.Get(0)->GetProtoNode()->nodeName;
			};
			zerr.Message ("D: hitVob: "+zSTRING(resCollList.Get(0)->hitVob->GetVobName())+", node: "+s);

			if (zCParticleFX::s_emitterPresetList.GetNum()>0) 
			{
				if (resCollList.Get(0)->hitVob->GetVisualClass()==zCModel::GetStaticClassDef())
				{
					// Particle-Effekt
					// Achtung: die hier erzeugten Vob/Visual loeschen sich bei Beendigung des Effekts selbststaendig !
					zCParticleFX	*partFX	= zNEW(zCParticleFX);
					zCVob			*vobFX	= zNEW(zCVob);

					// Partikel-Strom Hauprichtung errechnen
	//				zVEC3 weaponPos = weaponNode->GetData()->GetBBox3DWorld().GetCenter();
					zVEC3 weaponPos = model->GetNodePositionWorld(weaponNode);
					zVEC3 dir		= weaponPos - lastWeaponPos;
					lastWeaponPos	= weaponPos; 
					dir.NormalizeApprox(); 

					zVEC3 partDir	= vob->GetPositionWorld() - resCollList.Get(0)->hitVob->GetPositionWorld();
					partDir.NormalizeApprox();
					partDir			= partDir + dir;
					partDir			= partDir * 0.5F;

					vobFX	->SetDontWriteIntoArchive(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
					vobFX	->SetCollDet			(FALSE);
					vobFX	->SetPositionWorld		(resCollList.Get(0)->approxCollisionPos); 
					vobFX	->SetVisual				(partFX);
					partFX	->SetEmitter			("ZBLOOD1");
					partFX	->GetEmitter			()->SetOutputDir (partDir);
					partFX	->CreateParticles		();

					vob->GetHomeWorld()->AddVob		(vobFX);
					
					// "fire and forget" (selbstloeschend)
					zRELEASE (vobFX);
					zRELEASE (partFX);
				} else {
					zCParticleFX	*partFX	= zNEW(zCParticleFX);
					zCVob			*vobFX	= zNEW(zCVob);

					vobFX	->SetDontWriteIntoArchive(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
					vobFX	->SetCollDet			(FALSE);
					vobFX	->SetPositionWorld		(resCollList.Get(0)->approxCollisionPos); 
					vobFX	->SetVisual				(partFX);
					partFX	->SetEmitter			("ZMETALSPARKS");
					partFX	->CreateParticles		();

					vob->GetHomeWorld()->AddVob		(vobFX);

					// "fire and forget" (selbstloeschend)
					zRELEASE (vobFX);
					zRELEASE (partFX);
				};
			};
			// Folgende Zeile ist unbedingt noetig, damit keine Mem-Leaks entstehen !!
			resCollList.DeleteListDatas(); 
		};
	};
};
#endif

void zCAIPlayer::DoSurfaceAlignment ()
{
	// Surface-Align an unebenen Untergrund
	// (nicht im Flug, im Schwimmen/Tauchen)
	// ACHTUNG: dieser Teil braucht die Ergebnisse der Abstandshalter-Tests, um legale Boden-Stichproben nehmen zu koennen
	// FIXME: verbesserbar: falls eine Stichprobe nicht genommen werden kann (weil nichts per Ray getroffen wurde),
	// die andere aber schon, dann Schraeglagenlinie mit Punkt und VobCenter und der einen Probe herstellen.

	// ATT: ist leider schlecht mit 'modelAnisInPlace' koppelbar, da dieses Flag nicht die prozedurale Rotation auf der 
	//		Stelle beruecksichtigt.

	if ((zMV_DO_SURFACE_ALIGN!=zMV_SURFACE_ALIGN_NONE) &&
		(state==zMV_STATE_STAND)
//		&& (!modelAnisInPlace)
		)
	{
		// FIXME: es darf auch nicht jede surf-slope akzeptiert werden !
		// es werden nur Surfaces beruecksichtigt, die hoechstens Falltiefe' tief sind

		const	zPOINT3&	scanOrigin	= GetSurfaceAlignScanOrigin();
		zVEC3		        scanAt		= vob->GetNewTrafoObjToWorld().GetAtVector();
		const	zVEC3&		scanDown	= zVEC3(0,-((scanOrigin[VY]-feetY) + config.zMV_STEP_HEIGHT), 0);
		zBOOL	foundFront				= FALSE;
		zBOOL	foundBack				= FALSE;
		zVEC3	intersBack;
		zVEC3	intersFront;
		zVEC3	scanStart;
		zVEC3	scanDir;
 
        scanAt[VY] = 0;
        scanAt.NormalizeSafe();

		enum { rayFlags =	zTRACERAY_STAT_POLY				| zTRACERAY_POLY_NORMAL | 
							zTRACERAY_VOB_IGNORE_NO_CD_DYN	| zTRACERAY_VOB_IGNORE_CHARACTER };

		zREAL bodyLenFront;
		zREAL bodyLenBack;
		{
			const zTBBox3D& box		= model->GetBBox3D();				// im object Space des Models
			bodyLenFront			= zREAL(+0.6F) * box.maxs[VZ];
			bodyLenBack				= zREAL(-0.6F) * box.mins[VZ];
		};

		// back
		{
			scanDir	= (-bodyLenBack)*scanAt;
			if (world->TraceRayNearestHitCache (scanOrigin, scanDir, vob, rayFlags, &GetCollObject()->m_oBackRayCache)) 
					scanStart	= world->traceRayReport.foundIntersection - scanDir *.01F;
			else	scanStart	= scanOrigin + scanDir;

			if (world->TraceRayNearestHit (scanStart, scanDown, vob, rayFlags)) 
			{ 
				// hat Poly einen korrekten Winkel ?
				// (die Polys von Vobs NICHT testen)
				const zREAL slope	= (world->traceRayReport.foundVob) ? 0 : this->CalcFloorSlopeRad(world->traceRayReport.foundPolyNormal[VY]);
				if (slope<config.zMV_MAX_GROUND_ANGLE_SLIDE2)
				{
					intersBack		= world->traceRayReport.foundIntersection;
					foundBack		= TRUE;
					Line3D			(scanStart, intersBack, GFX_RED);
				};
			};
		};

		// front
		{
			scanDir	= (+bodyLenFront)*scanAt;
			if (world->TraceRayNearestHitCache (scanOrigin, scanDir, vob, rayFlags, &GetCollObject()->m_oFrontRayCache)) 
					scanStart	= world->traceRayReport.foundIntersection - scanDir * .01F; // [Moos] gehe von der Kollision noch ein stück zurück
			else	scanStart	= scanOrigin + scanDir;


			if (world->TraceRayNearestHit (scanStart, scanDown, vob, rayFlags)) 
			{
				// hat Poly einen korrekten Winkel ?
				// (die Polys von Vobs NICHT testen)
				const zREAL slope	= (world->traceRayReport.foundVob) ? 0 : this->CalcFloorSlopeRad(world->traceRayReport.foundPolyNormal[VY]);
				if (slope<config.zMV_MAX_GROUND_ANGLE_SLIDE2) 
				{
					intersFront		= world->traceRayReport.foundIntersection;
					foundFront		= TRUE;
					Line3D			(scanStart, intersFront, GFX_RED); 
				};
			};
		};

		// Korrektur
// FIXME: funzt leider derzeit nur bei (foundFront && foundBack)
//		if (foundFront && foundBack)
		{
			zVEC3 newAt;
            zVEC3 intersCenter = vob->trafoObjToWorld.GetTranslation();
            intersCenter[VY]   = GetFeetY();

			if (foundFront && foundBack)	newAt	= intersFront			 - intersBack;	    else
			if (foundFront)					newAt	= intersFront			 - intersCenter;	else
			if (foundBack)					newAt	= intersCenter           - intersBack;				
			else						   {newAt	= vob->trafoObjToWorld.GetAtVector(); newAt[VY] = 0;}

			newAt.Normalize			();

            zREAL frac = ztimer.GetFrameTimeF() * .02;
            newAt = (vob->trafoObjToWorld.GetAtVector() + newAt * frac)/(1+frac);

			newAt.Normalize			();
			vob->SetHeadingAtWorld	(newAt);
		};
	};
};

zBOOL zCAIPlayer::IsSliding () 
{
	return ((vob->GetPhysicsEnabled()) && (vob->GetRigidBody()->GetMode()==zPHY_RBMODE_SLIDE));
};

zBOOL zCAIPlayer::CheckFloorSliding () 
{
	// Result: TRUE= Reaktion ausgefuehrt, es bestand Handlungsbedarf

	// - startet Sliding, falls BodenNeigung entsprechend										(=> S_SLIDE*)
	// - stoppt  Sliding, falls Boden begehbar ist und Character bereits slidet					(=> S_RUN)
	// - Loest 'Physik-Bounce' aus, falls Schraege nach unten geht, und Neigung sehr steil ist

	// im Wasser darf nicht geslidet werden
	if (waterLevel>0)	
	{
		if (IsSliding()) 
		{
			// Sliden beenden
			Print							("Slide waterLevel>0: end => S_STAND");
			SetPhysicsEnabled				(FALSE);
			vob->GetRigidBody()->SetMode	(zPHY_RBMODE_FLY);
			StartStandAni					();
		};
		return FALSE;
	};

	// Natuerlich macht sliding im Swim/Dive keinen Sinn
	if ((state==zMV_STATE_SWIM) || (state==zMV_STATE_DIVE))		return FALSE;

	// (IsFlying==TRUE) => keine Bodenhaftung
	if (model->GetIsFlying())	return FALSE;

	// Result: TRUE= Reaktion ausgefuehrt, es bestand Handlungsbedarf
	zBOOL result = FALSE;

	// Welche Neigung hat der Boden ?
//	if (GetFloorPoly()) 
	{
		zVEC3	polyNormal;
		zREAL	slope		= 0;
		// Falls es kein FloorPoly gibt liegt, befindet sich unter dem Character ein Vob. Vobs als Untergrund
		// gelten derzeit als in jeder Neigung begehbar.
		if (GetFloorPoly())
		{
			polyNormal		= GetFloorPoly()->GetPlane().normal;
			slope			= CalcFloorSlopeRad (polyNormal[VY]);
			zERR_ASSERT		(slope<M_PI);
		};

		if (!(GetCollObject()->GetSpatialState().m_bFloorIsVob)	&&		// Auf Vobs wird Sliding vorerst nicht erlaubt
			(slope<M_PI)										&&		// scheint noetig..
			(slope>config.zMV_MAX_GROUND_ANGLE_WALK)            &&
            (aboveFloor<config.zMV_STEP_HEIGHT))                        // [Moos] nur sliden, wenn in Bodennähe...
		{ 
			// => Nicht Begehbar
			// Situation: Spieler befindet sich auf einem schraegen BodenPoly, das so steil ist, das er 
			// nicht drauf gehen kann. Nun muss ermittelt werden, ob mann die Schraege von oben oder unten betritt..

			zBOOL goingUp;
			if (model->GetIsFlying())	goingUp = FALSE;		// Model faellt von oben
			else
			if (IsSliding())			goingUp = FALSE;		// Model slidet bereits
			else {
				goingUp		= ((polyNormal*velocity)<0);
			}; 
			if (!goingUp) 
			{
				// Schraege abwaerts
	 			// Jetzt wird der Bodenwinkel klassifiziert
				if (slope<config.zMV_MAX_GROUND_ANGLE_SLIDE2) 
				{
					// Slide normal
					// Slide auf Hintern

					zBOOL startSliding;
					if (!IsSliding()) 
					{
						startSliding = TRUE;
					} else 
					{
						// Slide laeuft bereits, evtl. Richtung korrigieren (falls auf neuem Poly) ?
						if (slidePolyNormal.IsEqualEps(polyNormal))	startSliding = FALSE;
						else										startSliding = TRUE; 
					};

					if (startSliding) 
					{
						// Slide starten
						// FIXME: Model ausrichten ???
						Print							("Slide down: start");
						SetPhysicsEnabled				(TRUE);
						vob->GetRigidBody()->SetVelocity(velocity);		// was wenn vel fast 0 ???
						vob->GetRigidBody()->SetSliding	(polyNormal); 
						slidePolyNormal					= polyNormal;
						if ((vob->GetAtVectorWorld() * vob->GetRigidBody()->GetSlideDir())>0) 
						{
							// auf dem Hintern sliden ? (slide2) 
//							if (slope<zMV_MAX_GROUND_ANGLE_SLIDE2)
							model->StartAni				("S_SLIDE");
						} else 
						{
							model->StartAni				("S_SLIDEB");
						};
						result = TRUE;
					};
				} else 
				{
					// Bounce 
					// FIXME: evtl. hier immer auf eine 'Bounce-Ani' schalten
					if (IsSliding()) {
//						StartFallDownAni					();
					};										
					if ((!vob->GetPhysicsEnabled()) || (vob->GetRigidBody()->GetMode()!=zPHY_RBMODE_FLY))
					{
						SetPhysicsEnabled						(TRUE);
						vob->GetRigidBody()->ApplyImpulse		(polyNormal*30000, centerPos);
						vob->GetRigidBody()->SetMode			(zPHY_RBMODE_FLY);
						StartFallDownAni					();
						Print ("Bounce");
					};
					result = TRUE;							
				};

			};
		} else 
		{
			// => Begehbar
			if (/* IsSliding() || */
				(vob->GetRigidBody()->GetMode()==zPHY_RBMODE_SLIDE) ||
				(m_eCollObjectStateOld==zCCollObjectCharacter::zCONFIG_STATE_SLIDE)
			   )
			{
				// Sliden beenden
				// SLIDE => FLY
				if ((aboveFloor>config.zMV_STEP_HEIGHT) && (!GetCollObject()->GetSpatialState().m_bFloorIsStair) &&
					((waterLevel<=1) ||
					((waterLevel> 1) && (feetY>GetWaterY())) )
					)
				{  
					// Hoehen-Differenz  > 50cm => Model faellt runter 
					// (d.h. dass Stufen < 50cm sein muessen..)
					Print							("Slide: end => FLY : "+zSTRING(aboveFloor));
					SetPhysicsEnabled				(TRUE);
					StartFallDownAni				();
					vob->GetRigidBody()->SetVelocity(velocity*0.8F);
					vob->GetRigidBody()->SetMode	(zPHY_RBMODE_FLY);
				} else 
				// SLIDE => STAND
				{
					// Sliden beenden
					Print							("Slide: end => S_STAND");
					SetPhysicsEnabled				(FALSE);
					vob->GetRigidBody()->SetMode	(zPHY_RBMODE_FLY);
					StartStandAni					();
				};
			};
		};
	};
	return result;
};


void zCAIPlayer::CheckPhysics () 
{
	if (!model->GetIsFlying())
	{
		// Fall-Physik einschalten?
		if ((aboveFloor>config.zMV_STEP_HEIGHT) && (!GetCollObject()->GetSpatialState().m_bFloorIsStair))
		{  
			// Mann darf nur Fallen, wenn entweder nur begehbares Wasser unter einem ist, oder wenn tiefes Wasser unter
			// einem ist die Fuesse im Wasser sind (=> z.B. noetig fuer Übergang walkw(wlv1)=>swimF(wlv2)
			// Es gibt hier allerdings ein kleines Problem, wenn mann von level1 in level2 über eine 90° Kante sideSteped
			// oder rückwärts geht (=> während dieses T_-Anis wird der level-Wechsel (noch?) nicht abgefragt, so dass eine
			// Reaktion erst im naechsten S_ erfolgt. Lösung: Abfragen in T_-Anis (ähnlich S_STAND), oder..)
			if  ((!(vob->GetPhysicsEnabled() && vob->GetRigidBody()->GetMode() == zPHY_RBMODE_FLY) || !GetModel()->GetIsFlying())
				&& ((waterLevel<=1) ||
				   ((waterLevel> 1) && (feetY>GetWaterY()) 
//				   || ((waterLevel> 1) && (oldState!=zMV_STATE_SWIM))
				)))
			{
				// Hoehen-Differenz  > 50cm => Model faellt runter 
				// (d.h. dass Stufen < 50cm sein muessen..)
				Print							("fall: "+zSTRING(aboveFloor));
				SetPhysicsEnabled				(TRUE);
				StartFallDownAni				();
				vob->GetRigidBody()->SetVelocity(velocity*0.8F);
				vob->GetRigidBody()->SetMode	(zPHY_RBMODE_FLY);
			};
		} else 
		{
			// akzeptable Hoehendifferenz, d.h. Bodenkontakt
			if (!IsSliding()) {
				if (vob->GetPhysicsEnabled())	
				{
					SetPhysicsEnabled			(FALSE);
					Print						("landing");
				};
			};
	
			// ..snip..
//			CheckFloorSliding();
		};
	};

	// Physik unerlaubter Weise an?
	if ((vob->GetPhysicsEnabled()) && 
		(oldState==zMV_STATE_SWIM))
	{
		vob->SetPhysicsEnabled(FALSE);
	};

	// Kollision im Flug
	{
		// Line3D (vob->GetPositionWorld(), vob->GetPositionWorld() + vob->GetRigidBody()->GetVelocity()*0.5F);
        const zCCollObjectCharacter::zTInterferenceReport& interferenceReport=this->GetInterferenceReport();

		const zBOOL spacingRayHit	=	(interferenceReport.correction.spacingRayBack)	||
										(interferenceReport.correction.spacingRayFront)	||
										(interferenceReport.correction.spacingRayLeft)	||
										(interferenceReport.correction.spacingRayRight);
	// [HILDEBRANDT] habe aus dem 'GetModel()->GetIsFlying())' ein '!GetModel()->GetIsFlying())' gemacht. Machte
	//				 Aerger beim Leiterklettern
		if (interferenceReport.blocking.centerRayCollided || interferenceReport.blocking.lowCeiling || spacingRayHit )
        {
		    if (((vob->GetPhysicsEnabled())      && (vob->GetRigidBody()->GetMode()==zPHY_RBMODE_FLY)))// || 
                //((GetOldState() == zMV_STATE_STAND) && (!GetModel()->GetIsFlying()) && GetWaterLevel() == 0 ) )
		    {
                // [Moos] Extra: wenn wir ohne physik fliegen (anfang des Sprungs), schalte die Physik ein
			    zVEC3 &collNormal	    = (zVEC3 &)interferenceReport.collisionNormal;
			    const zVEC3 &velocity	= vob->GetRigidBody()->GetVelocity();

                /*
                if (!vob->GetPhysicsEnabled())
                {
                    vob->SetPhysicsEnabled			(TRUE);
                    vob->GetRigidBody()->SetMode	(zPHY_RBMODE_FLY);
                    vob->GetRigidBody()->SetVelocity(300 * collNormal);
                }
                */

                if (velocity.Length2() > 1000000) // [MOOS] really fast; change velocity randomly.
                {
                    vob->GetRigidBody()->SetVelocity(zVEC3(zRand(1000)-500, zRand(1000)-500, zRand(1000)-500));
                }

                if (collNormal.Length2() > 1)
                    collNormal.Normalize();

                if (velocity * collNormal < 5) // nur dann bewegen wir uns auf die Kollision zu
                    vob->GetRigidBody()->SetVelocity((velocity - 1.5F * (velocity * collNormal - 100) * collNormal)/(1 + ztimer.GetFrameTimeF() * .01F));

//                GetModel()->StartAni("S_FALL");
            /*
			    zVEC3 velocityNorm	    = velocity;
			    velocityNorm.Normalize();
			    if ((velocityNorm*collNormal)<-0.0F)
			    {

				    vob->GetRigidBody()->CollisionImpulseCenterStatic(collNormal, 0.2F);
	    //			vob->GetRigidBody()->ApplyImpulse		(polyNormal*30000, centerPos);
				    vob->GetRigidBody()->SetMode			(zPHY_RBMODE_FLY);
			    };
             */
		    }
        }
	};

/*	// Landen?
	if ((vob->GetPhysicsEnabled()) && (vob->GetRigidBody()->GetMode()==zPHY_RBMODE_FLY))
	{
		if (aboveFloor<zMV_LAND_HEIGHT) { 
			// akzeptable Hoehendifferenz => Model-Hoehe stumpf korrigieren
			LandAndStartAni	("T_FALLDN_2_STAND");
		};
	};
*/
	// Unter Wasser soll die Gravity gedaempft wirken
	if (vob->GetPhysicsEnabled()) 
	{
		if ((waterLevel==2) && (headY<GetWaterY())) {
			vob->GetRigidBody()->SetGravityScale	(0.7F);
			vob->GetRigidBody()->SetVelocity		(vob->GetRigidBody()->GetVelocity()*0.8F);
		} else {
			vob->GetRigidBody()->SetGravityScale	(1.0F);
		};
	};
};

void zCAIPlayer::PropagateCollObjectStates (const zTMovementState movementState) 
{
	// Daten an das CollObjectChar uebertragen
	zCCollObjectCharacter *collObjectChar = static_cast<zCCollObjectCharacter*>(vob->GetCollisionObject());
	if (collObjectChar)
	{
		collObjectChar->SetFeetYLocal						(feetY - centerPos[VY]);
		collObjectChar->SetHeadYLocal						(headY - centerPos[VY]);
		collObjectChar->GetConfig().m_fMaxGroundAngleWalk	= this->config.zMV_MAX_GROUND_ANGLE_WALK;
		collObjectChar->GetConfig().m_fStepHeight			= this->config.zMV_STEP_HEIGHT;
		collObjectChar->GetConfig().m_bTreatWaterAsSolid	= this->GetTreatsWaterAsSolid();
		collObjectChar->GetConfig().m_bDoWallSliding		= this->zMV_DO_WALL_SLIDING;

		// heightCorrection (nur beim PC smooth)
		collObjectChar->GetConfig().m_eDoHeightCorrection	= this->zMV_DO_HEIGHT_CORRECTION && (!model->GetIsFlying());
		collObjectChar->GetConfig().m_eDoHeightCorrectionSmooth	= this->vob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_PC;

		// MovementState
		{
			if (IsSliding())	
			{
				m_eCollObjectState	= zCCollObjectCharacter::zCONFIG_STATE_SLIDE; 
			} else 
			{
				switch (movementState)
				{
					case zMV_STATE_STAND:	m_eCollObjectState	= zCCollObjectCharacter::zCONFIG_STATE_STAND;break;
					case zMV_STATE_FLY:		m_eCollObjectState	= zCCollObjectCharacter::zCONFIG_STATE_FLY;	 break;
					case zMV_STATE_SWIM:	m_eCollObjectState	= zCCollObjectCharacter::zCONFIG_STATE_SWIM; break;
					case zMV_STATE_DIVE:	m_eCollObjectState	= zCCollObjectCharacter::zCONFIG_STATE_DIVE; break;
					default:				m_eCollObjectState	= zCCollObjectCharacter::zCONFIG_STATE_STAND; break;
				};
			};
			collObjectChar->GetConfig().m_eState	= m_eCollObjectState;
		};

		//
		collObjectChar->GetConfig().m_bUseSpacingRays				=!(this->modelAnisInPlace);
		collObjectChar->GetConfig().m_bLiftSpacingRayStart			= (this->zMV_DO_SURFACE_ALIGN==this->zMV_SURFACE_ALIGN_HIGH);
		collObjectChar->GetConfig().m_bFloorTooLowIsHardCollision	= (this->zMV_DO_DETECT_WALK_STOP_CHASM) && (movementState==zMV_STATE_STAND) && (waterLevel==0);
	};

};

void zCAIPlayer::CalcForceModelHalt () 
{
	zCCollObjectCharacter *collObjectChar = static_cast<zCCollObjectCharacter*>(vob->GetCollisionObject());
	if (collObjectChar)
	{
		// ForceModelHalt berechnen
		// => bei Kontakt mit Hindernis, der nicht durch WallSlide behandelt wurde.
		forceModelHalt	= FALSE;
		if (m_eCollObjectState==zCCollObjectCharacter::zCONFIG_STATE_STAND)
		{
			if ((!collObjectChar->GetInterferenceReport().blocking.blockingWallSlide) &&
				(!collObjectChar->GetInterferenceReport().correction.spacingRayWallSlide))
			{
				const zCCollObjectCharacter::zTInterferenceReport& interferenceReport = collObjectChar->GetInterferenceReport();
				const zDWORD bits	=	interferenceReport.correction.spacingRayBack	+ 
										interferenceReport.correction.spacingRayFront	+ 
										interferenceReport.correction.spacingRayLeft	+ 
										interferenceReport.correction.spacingRayRight	+ 
										interferenceReport.blocking.floorTooHigh		+
										interferenceReport.blocking.floorTooLow			+
										interferenceReport.blocking.floorTooSteepUp		+
										interferenceReport.blocking.floorTooSteepDown	+
										interferenceReport.blocking.lowCeiling;
				this->forceModelHalt= (bits!=0);

				#ifdef zMV_DEBUG
					if (forceModelHalt)	Print ("D: forceModelHalt: TRUE");
				#endif
			};
		};
	};
};

void zCAIPlayer::CalcStateVars () 
{
	//**************************************************//
	// Kollisionsobjekt initialisieren      			//
	//**************************************************//
    // [Moos] folgendes etwas hackiges codesegment sorgt dafür, dass der SpatialState
    // in eimem Aussagekräftigen Zustand ist.

    //zCCollObjectCharacter *co = (zCCollObjectCharacter *)vob->GetCollisionObject();
	zCCollObjectCharacter *co = (zCCollObjectCharacter *)(vob->GetCollisionObject());

    if (co && co->GetSpatialState().m_bIsUninited)
        co->MarkSpatialStateAsUninited(TRUE);

	//**************************************************//
	// VAR - INITS										//
	//**************************************************//
	
	//
	velocity				= vob->GetVelocity(); 
	velocityLen2			= velocity.Length2();
	centerPos				= vob->GetCollisionObject()->GetTrafoNew().GetTranslation();				/// NEEEEEEUUUUUUUUUUUUUUUU
							
	//						
	oldState				= state;
	state					= zMV_STATE_STAND;

	// 
	m_eCollObjectStateOld	= m_eCollObjectState;

	// HeadY, FeetY berechnen
	{
		if ((oldState==zMV_STATE_DIVE) && (modelHeadNode))	headY	= model->GetBBox3DNodeWorld(modelHeadNode).maxs[VY]; 
		else												headY	= vob  ->GetBBox3DWorld()				  .maxs[VY]; 

		// Bei Swim-Anis ist die Ani Y=0 Ebene nicht der Boden (=feetY), sondern der WasserLevel
		if ((model->GetIsFlying()) || (waterLevel==2))		feetY	= vob->GetBBox3DWorld().mins[VY];
		else												feetY	= GetModelFloorWorld ();			

		aboveFloor = (feetY - this->GetFloorY());
	};

	// Wasser spezifische Werte berechnen
	{
		oldWaterLevel			= waterLevel;
		waterLevel				= 0;			// 0=bis Knie, 1=bis Brust, 2=ueber Brust (zu tief zum Stehen)

		zREAL waterDepth		= GetWaterY() - GetFloorY();
		if (waterDepth<config.zMV_WATER_DEPTH_KNEE )
        	waterLevel = 0; 
        else if (waterDepth<config.zMV_WATER_DEPTH_CHEST)
            waterLevel = 1;
        else
		    waterLevel = 2;

		// Decke ist keine Wasser-Decke => waterVars richtig setzen
/*		if ((waterDepth==0) && (oldWaterLevel==2) && (oldState==zMV_STATE_DIVE)) 
		{
			// Unterwasser-Tunnel
			// Folgendes ist noetig, damit das Tauchen in Tunneln (ohne 'Wasser-Decke') moeglich ist
			// alter waterLevel==2 und beim Tauchen ? => force auf waterLevel2
			// in diesem Fall: waterY ungueltig (wichtig fuers Tauchen)
			waterLevel										= 2;
			aboveFloor										= 0;
			GetCollObject()->GetSpatialState().m_fWaterY	= GetCeilingY() + 1000000;
		};*/
	};

	CalcModelAnisInPlace	();

	// Daten an das CollObjectChar uebertragen		
	// SAFETY: diese Benachrichtigung muss eigentlich erst im End() stattfinden, falls allerdings im DoAI()/StateBlock
	//		   bereits eine EndMovement() auftritt, werden die Werte hier bereits auf die des letzten Frames gesetzt
	PropagateCollObjectStates(oldState);

	//
	CalcForceModelHalt		();					// NACH PropagateCollObjectStates()

	// Physik 
	CheckPhysics			();

	//
	CheckFloorSliding		();
};

void zCAIPlayer::DoProceduralMovement () 
{
	// AutoRoll
	DoAutoRoll				();

	// Wasser Stroemung (swim/dive)
	// UV Texture Ani des Wasserpolys als Bewegung auf das Model uebertragen
	{
		zCPolygon *waterPoly	= GetWaterPoly();
		if ((waterLevel==2)												&&
			((oldState==zMV_STATE_SWIM) || (oldState==zMV_STATE_DIVE))	&&
			(waterPoly))
		{
			// FIXME: uuuhh, ist das hier die richtige Stelle dafuer ... ?
			const zVEC3 currentDir = ztimer.GetFrameTimeF() * waterPoly->GetMaterial()->GetTexAniVector(waterPoly);
			vob->Move (currentDir);
			// 'modelAnisInPlace' kann nicht mehr gueltig sein, da Model extern bewegt wird
			modelAnisInPlace = FALSE;
		};
	};

	//
	DoSurfaceAlignment		();
};

	//**********************************************************************************************************//
	// BEGIN																									//
	//**********************************************************************************************************//

void zCAIPlayer::Begin (zCVob* inVob) 
{
	if (inVob->GetVisualClass()!=zCModel::GetStaticClassDef()) return;

	if (vob!=inVob) {
		SetVob (inVob);
	};

	// sicherstellen, dass es sich bei dem CollObject des Vobs um ein zCCollObjectCharacter handelt
	#ifdef _DEBUG
		zERR_ASSERT (dynamic_cast<zCCollObjectCharacter*>(vob->GetCollisionObject()));
	#endif

	#ifdef ZENGINE_AIPLAYER
		if ((model->GetNumActiveAnis()==0) || (!_s_run)) 
		{
			_s_run = model->GetAniFromAniName ("S_RUN");
			if (!_s_run)
			_s_run = model->GetAniFromAniName ("S_FISTRUN");
			model->StartAni (_s_run);
		};
	#endif

	//
	CalcStateVars			();

	//
	DoProceduralMovement	(); 

	//
	BeginStateSwitch		();

	//
	GetCollObject()->GetConfig().m_bUseSpacingRays	= (!this->modelAnisInPlace);
};

#ifdef ZENGINE_AIPLAYER
	void zCAIPlayer::PrintDebugInfos ()
	{
		#ifdef zMV_DEBUG
			int x	= 0;
			int y	= 5000;
			zSTRING stateName;
			if (m_eCollObjectState==zCCollObjectCharacter::zCONFIG_STATE_STAND	)	stateName = "STAND";	else
			if (m_eCollObjectState==zCCollObjectCharacter::zCONFIG_STATE_FLY	)	stateName = "FLY";		else
			if (m_eCollObjectState==zCCollObjectCharacter::zCONFIG_STATE_SLIDE	)	stateName = "SLIDE";	else
			if (m_eCollObjectState==zCCollObjectCharacter::zCONFIG_STATE_SWIM	)	stateName = "SWIM";		else
			if (m_eCollObjectState==zCCollObjectCharacter::zCONFIG_STATE_DIVE	)	stateName = "DIVE";

			screen->Print (x,y+(0*screen->FontY()), "state: "		+ stateName);
			screen->Print (x,y+(1*screen->FontY()), "flyFlag: "		+ zSTRING(model->GetIsFlying()));
			screen->Print (x,y+(2*screen->FontY()), "waterLevel: "	+ zSTRING(waterLevel));
			screen->Print (x,y+(3*screen->FontY()), "physics: "		+ zSTRING(vob->GetPhysicsEnabled()));

/*			zerr.Message ("D: state: "		+ stateName+
						   ", flyFlag: "	+ zSTRING(model->GetIsFlying())+
						   ", waterLevel: "	+ zSTRING(waterLevel)+
						   ", physics: "	+ zSTRING(vob->GetPhysicsEnabled())
						   );
*/
		#endif
	};
#endif

	//**********************************************************************************************************//
	// END																									//
	//**********************************************************************************************************//

void zCAIPlayer::End() 
{
	// ist hier und nicht in Begin() weil: ausserhalb koennte es auf TRUE gesetzt werden (=>Response)
	// und dann darf es in Begin() nicht ueberschrieben werden, andererseits muss es aber jeden Frame geloescht werden.
	forceModelHalt = FALSE;

	// Loest folgendes Problem (uuh..dirty):
	// im Wasser kann es vorkommen, dass zu einem Zeitpunkt nur Trans-Anis und keine State-Ani gespielt wird
	// => illegalerweise wechselt in dieser Zeit der state von SWIM/DIVE auf STAND
	if (waterLevel==2) 
	{
		if (state==zMV_STATE_STAND)	state = oldState;
/*		zBOOL hasState = FALSE;
		for (int i=0; i<model->numActiveAnis; i++) {
			hasState = hasState || model->aniChannels[i]->IsStateAni();
		};
		if (!hasState)	state	= oldState;*/
	};

	// Daten an das CollObjectChar uebertragen		
	// (wurde zur Sicherheit mit dem oldState auch schon in Begin() gemacht)
	PropagateCollObjectStates	(state);

	// Die 'rootPosLocal' des Models (= Ort der Bodenebene in der Animation) muss ggfs. neu berechnet werden.
	// Dies ist kritisch fuer die Uebergaenge STAND <=> SWIM. 
	// (In diesem Frame gestartete Anis wirken sich erst im naechsten auf die 'rootPosLocal' im Model aus..)
	if ((state==zMV_STATE_SWIM) || (oldState==zMV_STATE_SWIM))
	{
		const zBOOL selectHighestY	= (this->m_eCollObjectState != zCCollObjectCharacter::zCONFIG_STATE_SWIM);
		model->RecalcRootPosLocal	(selectHighestY);
	};

	//
	#ifdef ZENGINE_AIPLAYER
		PrintDebugInfos ();
	#endif

	//
	UpdateEffects();
};

void zCAIPlayer::DoAI (zCVob *inVob, zBOOL& vobDeleted)
{
#ifdef ZENGINE_AIPLAYER

	if (!irgnoreKeyBoard) 
	{
		if ((state==zMV_STATE_DIVE)) {
			// Bewegung in Z-Richtung ( Vorwärts / Rückwärts )
			force_z = 0;
			if ((KeyPressed(KEY_LALT)))										force_z += MOV_FORCE_Z; 

			// up/down
			if ((KeyPressed(KEY_PAD_UP))	|| (KeyPressed(KEY_UP)))		DiveRotateX (+5.0F);
			if ((KeyPressed(KEY_PAD_DOWN))	|| (KeyPressed(KEY_DOWN)))		DiveRotateX	(-5.0F); 
		} else {
			// Bewegung in Z-Richtung ( Vorwärts / Rückwärts )
			force_z = 0;
			if ((KeyPressed(KEY_PAD_UP))	|| (KeyPressed(KEY_UP)))		force_z += MOV_FORCE_Z;
			if ((KeyPressed(KEY_PAD_DOWN))	|| (KeyPressed(KEY_DOWN)))		force_z -= MOV_FORCE_Z;
		};

		if (KeyPressed(KEY_INS))											vob->MoveLocal (0,0,+10); 
		if (KeyPressed(KEY_DEL))											vob->MoveLocal (0,0,-10);
																			
		// Bewegung in X-Richtung ( Links / Rechts )
		force_x = 0;
		if (KeyPressed(KEY_PAD_PGDN))										force_x += MOV_FORCE_X;
		if (KeyPressed(KEY_PAD_END))										force_x -= MOV_FORCE_X;

		if (KeyPressed(KEY_HOME))											vob->RotateLocal (1,0,0, -10);
		if (KeyPressed(KEY_END))											vob->RotateLocal (1,0,0, 10);

		// Bewegung in Y-Richtung ( Hoch / Runter )
		force_y = 0;
		if (KeyPressed(KEY_A))												force_y += MOV_FORCE_Y;
		if (KeyPressed(KEY_Z))												force_y -= MOV_FORCE_Y;	// [BENDLIN] Addon - KeybFix

		// Rotation úm eigene Achse ( Links / Rechts drehen )
		force_rot = 0;
		if ((KeyPressed(KEY_PAD_LEFT)) || (KeyPressed(KEY_LEFT)))			force_rot -= MOV_FORCE_ROT;
		if ((KeyPressed(KEY_PAD_RIGHT)) || (KeyPressed(KEY_RIGHT)))			force_rot += MOV_FORCE_ROT;
	};

	if (KeyPressed(KEY_P)) {
		zVEC3 at = inVob->GetAtVectorWorld();
		at		+= zVEC3 (0,-1,0);
		at.Normalize();
		at		= at * 200.0F;
		AddBlood (inVob->GetPositionWorld(), at, 50, FALSE);

		SetBleeding (1.0F);
		if (KeyPressed(KEY_LSHIFT)) {
			SetBleeding (0.0F);
		};
	};

	// ********************************
	//  Geschw.-abh. Flags setzen
	// ********************************
	#ifdef ZENGINE_AIPLAYER
	{
		zMV_DO_WALL_SLIDING						= (velocityLen2>=config.zMV_MIN_VELOCITY_WALK2);
//		zMV_DO_DETECT_WALK_STOP_CHASM			= ((velocityLen2>(zMV_MIN_VELOCITY_WALK2/2)) && (velocityLen2<zMV_MIN_VELOCITY_RUN2));
		zMV_DO_DETECT_WALK_STOP_CHASM			= (velocityLen2<config.zMV_MIN_VELOCITY_RUN2);
		if (vob)
//		if (vob->RigidBody()->GetMode()==zPHY_RBMODE_FLY) {
		if (vob->GetPhysicsEnabled()) {
			zMV_DO_WALL_SLIDING	= FALSE;
		};
	}; 
	#endif

	// ***************
	//	AutoRoll
	// ***************
	// Ulf=> Beispiel fuer eine vereinfachte AutoRoll-Regel (Model muss mindestens Run-Speed haben)
	// (duerfte im Game komplexer & Ani-Zustands abhängig sein)
	if ((velocityLen2>config.zMV_MIN_VELOCITY_RUN2) || (state==zMV_STATE_DIVE))
	{
		if (force_rot>0)	SetAutoRollPosDest (-1); else
		if (force_rot<0)	SetAutoRollPosDest (+1); else
							SetAutoRollPosDest ( 0);
	} 
	else SetAutoRollPosDest(0);


	//**************************************************//
	// START											//
	//**************************************************//

	vobDeleted = FALSE;
	if (inVob->GetVisualClass()!=zCModel::GetStaticClassDef()) return;

	Begin				(inVob);

	{
		DoStateSwitch		();

		//**************************************************//
		// PROZEDURALE BEWEGUNG		(2)						//
		//**************************************************//

		if (!irgnoreKeyBoard) 
		{
			zREAL time_corr		= ztimer.GetFrameTimeF() / MOV_TIME_CORR;
			zREAL fric_corr		= MOV_FRIC_MOV * time_corr;
			xspeed				+= (force_x / MOV_MASS) * time_corr - fric_corr * xspeed; 
			yspeed				+= (force_y / MOV_MASS) * time_corr - fric_corr * yspeed; 
			zspeed				+= (force_z / MOV_MASS) * time_corr - fric_corr * zspeed; 
			rotspeed			+= force_rot * time_corr - MOV_FRIC_ROT * rotspeed * time_corr;

			zspeed				= 0;
			xspeed				= 0;
			vob->MoveLocal		(xspeed,yspeed,zspeed);
			vob->RotateWorldY	((rotspeed * time_corr)); 
		};
	};

	//**************************************************//
	// END												//
	//**************************************************//

	End					(); 

	// *********************
	//	 Waffen-Coll-Det
	// *********************

	CheckWeaponCollisions();

#endif
}

// =================================================================================================================

//*********************************************************************************
//**	zCAIPlayer													  UpdateEffects
//*********************************************************************************
//**	23-Jan-01	[Keskenti]	Disabled blood marks (see bug #3303)
//*********************************************************************************
void zCAIPlayer::UpdateEffects () 
{
	// im Spacer keine Effekte darstellen 
#ifdef COMPILING_SPACER
	return;
#endif

	// *******************************
	//		EFFECTS		
	// *******************************

	const zTBBox3D& protoBox	= model->GetBBox3DLocalFixed();
//	const zREAL scalar			= zMax (protoBox.maxs[VX], protoBox.maxs[VZ]);
	const zREAL scalar			= ((protoBox.maxs[VX]-protoBox.mins[VX]) + (protoBox.maxs[VZ]-protoBox.mins[VZ])) * 0.5F;
	const zREAL modelSizeScale	= scalar * (0.0225178);			// (1/44)

	if (zCParticleFX::s_emitterPresetList.GetNum()>0) 
	{

		zBOOL doWaterRing = FALSE;

		// Particle-Effekt beim Eintauchen ins Wasser
		if (vob->GetPhysicsEnabled())  
		if (waterLevel>0)
		if ((feetY<GetWaterY()) && (headY>GetWaterY()))
		{
	//		vob->EndMovement(); 

			// Particle-Effekt
			// Achtung: die hier erzeugten Vob/Visual loeschen sich bei Beendigung des Effekts selbststaendig !
			zCParticleFX	*partFX	= zNEW(zCParticleFX);
			zCVob			*vobFX	= zNEW(zCVob);
			vobFX	->SetDontWriteIntoArchive(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
			vobFX	->SetCollDet			(FALSE);
			vobFX	->BeginMovement			();
			vobFX	->SetPositionWorld		(zVEC3(centerPos[VX], GetWaterY(), centerPos[VZ]));  
			vobFX	->SetVisual				(partFX);
	//		partFX	->SetAndStartEmitter	("ZWATERSPLASH1");
			partFX	->SetAndStartEmitter	("PFX_WATERSPLASH");
			vob		->GetHomeWorld()->AddVob(vobFX);
			vobFX	->EndMovement			();

			// Sound Ausloesen (ModelHitsLevel)
			zsndMan ->StartHitSound			(vob,	zCSoundManager::zSND_MAN_MEDIUM_MODEL, 
													zCSoundManager::zSND_MAN_MEDIUM_LEVEL, 
													0,						// "flesh"
													zMAT_GROUP_WATER, 
													0);

			doWaterRing = TRUE;

			// "fire and forget" (selbstloeschend)
			zRELEASE (vobFX);
			zRELEASE (partFX);
		};

		if (startFXModelLandDust) 
		{
			startFXModelLandDust = FALSE;
			// FIXME: es gibt Probleme, wenn das EndMovement hier fehlt !!  => Das Model beamt lustig durch die Gegend
			// Warum ??? Es sollte aber gehen
	//		vob->EndMovement(); 
			zCParticleFX	*partFX	= zNEW(zCParticleFX);
			zCVob			*vobFX	= zNEW(zCVob);
			vobFX	->SetDontWriteIntoArchive(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
			vobFX	->SetCollDet			(FALSE);
			vobFX	->BeginMovement			();
			vobFX	->SetPositionWorld		(zVEC3(centerPos[VX], GetFloorY(), centerPos[VZ]));  
			vobFX	->SetVisual				(partFX);
			partFX	->SetEmitter			("PFX_DUST");	
			// Emitter-Groesse & Anzahl Partikel an BBox3D anpassen

			vob		->GetHomeWorld()->AddVob(vobFX);
			vobFX	->EndMovement			();

			zREAL xdim = zREAL(0.2F) * (vob->GetBBox3DWorld().maxs[VX] - vob->GetBBox3DWorld().mins[VX]);
			zREAL zdim = zREAL(0.2F) * (vob->GetBBox3DWorld().maxs[VZ] - vob->GetBBox3DWorld().mins[VZ]);
			partFX	->GetEmitter()->shpLineBoxDim[VX]	= xdim;
			partFX	->GetEmitter()->shpLineBoxDim[VZ]	= zdim;
			partFX	->GetEmitter()->ppsValue			= zMin (zREAL(64), zMax(zREAL(8), (xdim*zdim) * 0.04F));
			partFX	->CreateParticles		();	

			// "fire and forget" (selbstloeschend)
			zRELEASE (vobFX);
			zRELEASE (partFX);
		};

		// Wasserringe
		doWaterRing = doWaterRing ||
						((waterLevel>0)				&&
						(state!=zMV_STATE_DIVE)		&&
						(feetY<=GetWaterY())		&&
						(!vob->GetPhysicsEnabled()) );

		if (doWaterRing)
		{
			if (!waterRingVob) {
				zCParticleFX	*waterRingPFX;
				waterRingPFX	= zNEW(zCParticleFX);
				waterRingVob	= zNEW(zCVob);

				waterRingVob	->SetDontWriteIntoArchive(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
				waterRingVob	->SetCollDet			(FALSE);
				waterRingVob	->BeginMovement			();
				waterRingVob	->SetPositionWorld		(vob->GetPositionWorld());
				waterRingVob	->SetVisual				(waterRingPFX);
				waterRingPFX	->SetEmitter			("ZWATERRING");	
				waterRingPFX	->SetDontKillPFXWhenDone(TRUE);
//				waterRingPFX	->CreateParticles		();	

				vob				->GetHomeWorld()->AddVob(waterRingVob);
				waterRingVob	->EndMovement			();
				zRELEASE		(waterRingPFX);
			};

			if ((waterRingTimer<=0) || (velocityLen2>((30*30)*modelSizeScale)))
			{
//vob->EndMovement();	// FIXME:	ARGH !
				zCParticleFX	*waterRingPFX	= static_cast<zCParticleFX*>(waterRingVob->GetVisual());
				// neu Positionieren
				zPOINT3 newPos (vob->GetPositionWorld());
				newPos[VY] = GetWaterY() + zREAL(1.0F);
				
				if ((velocityLen2>((10*10)*modelSizeScale)) && 
					(state==zMV_STATE_SWIM))
				{
					zVEC3 velNorm	= velocity;
					velNorm.NormalizeApprox();
					newPos += checkWaterCollBodyLen * velNorm;
				};
				waterRingVob->SetPositionWorld (newPos);

				// hier evtl. noch: 
				// - vobUp an WaterPolyNormal ausrichten
				// - vobAt an vel ausrichten

				// schneller Vob Bewegung => 
				// - höhere Frequenz
				// - größer (Start & End)
				zREAL vel		= velocity.LengthApprox();
				zREAL sizeStart	=  1.0F + (vel * 0.08F);
				zREAL sizeEnd	= 50.0F + sizeStart*2;
				if (sizeEnd>100.0F)		sizeEnd = 100.0F;
				if (sizeEnd<sizeStart)	sizeEnd = sizeStart;
				sizeStart		*= modelSizeScale;
				sizeEnd			*= modelSizeScale;
				zREAL scale		= sizeEnd / sizeStart;
				waterRingPFX->GetEmitter()->visSizeStart	= sizeStart;
				waterRingPFX->GetEmitter()->visSizeEndScale	= scale;

				//
				waterRingPFX	->CreateParticles		();	
				waterRingTimer	= 500.0F - (vel * 0.1F) * modelSizeScale;

			};
			waterRingTimer -= ztimer.GetFrameTimeF();
		};
	};

	// Blood
	if ((GetBleeding()>0) && (waterLevel==0))
	{
		const zREAL xdiff = vob->GetPositionWorld()[VX]-bleedingLastPos[VX];
		const zREAL zdiff = vob->GetPositionWorld()[VZ]-bleedingLastPos[VZ];
		if ((xdiff*xdiff + zdiff*zdiff)>bleedingNextDist)
	//	if ((vob->GetPositionWorld()-bleedingLastPos).Length2()>bleedingNextDist)
		{
			zCQuadMark	*quadMark	= GetBloodQuadMark();
			if (quadMark)
			{
				// FIXME: von Modelgroesse abh. ! 
//				zREAL dim = (zRandF()*50 + 10) * (GetBleeding());
				zREAL dim	=  (zRandF()*40 + 7) * (zMax(0.6F, GetBleeding()));
				dim			*= modelSizeScale;

				zVEC2 size(dim,dim);
				quadMark->CreateQuadMark	(vob->GetPositionWorld(), zVEC3(0,-500,0), size);
				bleedingLastPos			= vob->GetPositionWorld();
				bleedingNextDist		= (30*30) + zRandF() * (200*200)*(1.0F-GetBleeding());
				bleedingNextDist		*= modelSizeScale*modelSizeScale;
			};
		};
	}
	/*else if (vob->GetGroundPoly()&& vob->GetGroundPoly()->GetMaterial()->GetMatGroup()==zMAT_GROUP_SNOW&&waterLevel==0)
	{
		zCQuadMark	*quadMark	= GetBloodQuadMark();
		if (quadMark)
		{
			zREAL dim	=  10;
			dim			*= modelSizeScale;

			zVEC2 size(dim,dim);
			
			quadMark->CreateQuadMark	(vob->GetGetPositionWorld(), zVEC3(0,-500,0), size);
			bleedingLastPos			= vob->GetPositionWorld();
			bleedingNextDist		= (30*30) + zRandF() * (200*200)*(1.0F-GetBleeding());
			bleedingNextDist		*= modelSizeScale*modelSizeScale;
		};
	}*/
	if (bloodVobList.GetNum()>3) 
	{
		const zDWORD	masterFrameCtr	= vob->GetHomeWorld()->GetMasterFrameCtr();
		for (int i=0; i<bloodVobList.GetNum()-3; i++) 
		{
			bloodVobList[i].alpha	-= ztimer.GetFrameTimeF() * 0.00001F;		// Patch1.08

			// vorerst NICHT faden, sondern einfach unbemerkt hinter dem Ruecken der Camera aus Welt entfernen
//			bloodVobList[i].bloodVob->SetVisualAlphaEnabled	(TRUE);
//			bloodVobList[i].bloodVob->SetVisualAlpha		(bloodVobList[i].alpha);

			// BloodVob aus World entfernen, wenn
			// ausgefadet & seit ein paar Frames nicht mehr gerendert
			if ((bloodVobList[i].alpha<0) && (bloodVobList[i].bloodVob->lastTimeDrawn+5<masterFrameCtr))
			{
				bloodVobList[i].bloodVob->RemoveVobFromWorld();					// ref von 2 => 1
				bloodVobList[i].bloodVob->Release();							// ref von 1 => 0, delete!
				bloodVobList.RemoveOrderIndex (i);
				i--;
			};
		};
	};

#ifdef ZENGINE_DEBUG
	// Weapon-Trail
	if (1) 
	{
//	vob->EndMovement();

		zCModelNodeInst *node			= model->SearchNode (zSTRING("ZS_RIGHTHAND"));
		if (node && node->GetNodeVisual() && node->GetNodeVisual()->GetOBBox3D()) {
			zMATRIX4			trafoNodeToWorld	= vob->trafoObjToWorld * model->GetTrafoNodeToModel(node);
			zCOBBox3D			*obb				= node->GetNodeVisual()->GetOBBox3D();
			zPOINT3				pos1				= obb->center + obb->axis[0]*obb->extent[0];
			zPOINT3				pos2				= obb->center - obb->axis[0]*obb->extent[0];
			pos1 = trafoNodeToWorld * pos1;
			pos2 = trafoNodeToWorld * pos2;
			AddWeaponTrailSegment (pos1, pos2);
		};
		
	};
#endif
};

// =================================================================================================================

zCQuadMark* zCAIPlayer::GetBloodQuadMark () 
{
	// Kein QuadMark moeglich, falls kein Vob oder dieser nicht in einer Welt registriert ist..
	// Das sollte eigentlich nicht passieren..
	if (!vob)					return 0;
	if (!vob->GetHomeWorld())	return 0;

	//
	zCVob* bloodVob = 0;
	if (bloodVobList.GetNum()>0)	bloodVob = bloodVobList[bloodVobList.GetNum()-1].bloodVob;

	if (bloodVob)
	if (bloodVob->GetBBox3DWorld().GetFloorArea()>(500*500)) {
		// neuen Blood-Vob anfangen
//		delete bloodVob;
		bloodVob=0;
	};

	if (!bloodVob) 
	{
		zCQuadMark	*quadMark;
		quadMark	= zNEW(zCQuadMark);
		bloodVob	= zNEW(zCVob);
		bloodVob	->SetDontWriteIntoArchive(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
		bloodVob	->SetCollDet			(FALSE);
		bloodVob	->BeginMovement			();
		bloodVob	->SetPositionWorld		(vob->GetPositionWorld());
		bloodVob	->SetVisual				(quadMark);

		vob			->GetHomeWorld()->AddVob(bloodVob);
		bloodVob	->EndMovement			();
		quadMark	->SetTexture			(bloodDefaultTexName);
//		quadMark	->GetDefaultMaterial	().SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);
		
		zRELEASE (quadMark);


		zTBloodVobTrack track;
		track.bloodVob	= bloodVob;
		track.alpha		= 1;
		bloodVobList.Insert	(track);
	};
	return (zCQuadMark*)bloodVob->GetVisual();
};

void zCAIPlayer::SetBloodDefaultTexture (const zSTRING& texName)
{
	bloodDefaultTexName = texName;
};

void zCAIPlayer::AddBlood (const zPOINT3& rayOrg, const zVEC3& ray, zREAL size, zBOOL scaleUp, zSTRING* texName) 
{
#ifdef COMPILING_SPACER
	// keine Effekte im Spacer
	return;
#endif
	zCQuadMark	*quadMark	= GetBloodQuadMark();
	if (!quadMark)			return;
	zCQuadMark::zTEffectParams *peffects=0;
	zCQuadMark::zTEffectParams effects;

	if (scaleUp) {
		peffects = &effects;
		effects.texAniType			= zCQuadMark::zTEXANI_SCALEUP_AUTO;
		effects.texAniSpeed			= 0.8F;
		effects.texAniScaleStart	= 0.5F;
	};

	if (texName)	quadMark->CreateQuadMark	(rayOrg, ray, zVEC2(size,size), *texName, peffects);
	else			quadMark->CreateQuadMark	(rayOrg, ray, zVEC2(size,size), peffects);
};

// =================================================================================================================


void zCAIPlayer::AddWeaponTrailSegment (const zPOINT3& posUp, const zPOINT3& posDown)
{
#ifdef COMPILING_SPACER
	// keine Effekte im Spacer
	return;
#endif

	if (!zCAIPlayer::S_GetShowWeaponTrails()) return;

	if (ztimer.GetFrameTimeF()<=0) return;

	if (!weaponTrailVob) 
	{
		zCPolyStrip	*polyStrip;
		polyStrip		= zNEW(zCPolyStrip);
		weaponTrailVob	= zNEW(zCVob);
		weaponTrailVob	->SetDontWriteIntoArchive(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
		weaponTrailVob	->SetCollDet			(FALSE);
		weaponTrailVob	->BeginMovement			();
		weaponTrailVob	->SetPositionWorld		(vob->GetPositionWorld());
		weaponTrailVob	->SetVisual				(polyStrip);

		vob				->GetHomeWorld()->AddVob(weaponTrailVob);
		weaponTrailVob	->EndMovement			();

		//
//		polyStrip->SetAlphaFadeSpeed	(0.1F);
		if (vob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_PC)
		{
			polyStrip->SetAlphaFadeSpeed	(0.6F);		// Gothic1: 1.3
		}
		else
		{
			polyStrip->SetAlphaFadeSpeed	(1.0F);		// Gothic1: 1.3
		}
		polyStrip->material->SetTexture	(zSTRING("ZWEAPONTRAIL.TGA"));
		polyStrip->AllocateResources	(256);
		zERR_ASSERT (polyStrip->material);
		//
		zRELEASE (polyStrip);
	};
	zCPolyStrip	*polyStrip = (zCPolyStrip*)(weaponTrailVob->GetVisual());

	static zCOLOR skyFogColor;
	if (zDYNAMIC_CAST<zCSkyControler_Outdoor>(zCSkyControler::GetActiveSkyControler()))
		skyFogColor = zrenderer->GetFogColor();
	else skyFogColor.SetRGBA(100,100,100,255);

	zREAL alphaScale = (skyFogColor.GetIntensityFloat()+100)/255.0F;
	if (alphaScale>1) alphaScale = 1;

	polyStrip->SetGlobalAlpha(255 * alphaScale);

	polyStrip->AddSegment(posUp, posDown);
	polyStrip->CalcBBox3D	();					// FIXME !!!!
};

// =================================================================================================================

#if 0
zBOOL zCAIPlayer::DetectWalkStopChasm()
{  
	// FIXME: nur alle 2 Frames ??

	// Hat das Model 'Walk-Speed' ?
	if (waterLevel	==0)
	if (oldState	==zMV_STATE_STAND) 
	if (velocityLen2>=(40*40))
	if (zMV_DO_DETECT_WALK_STOP_CHASM)
	if (!GetCollObject()->GetSpatialState().m_bFloorIsStair)
	{
		// Es muss in Richtung der Gehbewegung gescannt werden
 		zVEC3 scanAt= velocity; 
		scanAt[VY]	= 0;
		scanAt.NormalizeApprox();
		scanAt		= scanAt * config.zMV_DETECT_CHASM_SCAN_AT * 0.7F; 

		//
		const zPOINT3	scanOrigin	= GetSurfaceAlignScanOrigin();
		if (!world->TraceRayFirstHit (scanOrigin, scanAt, vob, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) 
		{
			const zVEC3 scanDown = zVEC3(0,-((scanOrigin[VY]-feetY) + config.zMV_STEP_HEIGHT), 0);
			Line3D (scanOrigin+scanAt, scanOrigin+scanAt+scanDown, GFX_WHITE);
			if (!world->TraceRayFirstHit (scanOrigin+scanAt, scanDown, vob, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) 
			{    
				Print ("chasm detected");

				// Zuruecksetzen (aber nur XZ, nicht Y)
/*				zVEC3 absMoveDist	= vob->trafoObjToWorld.GetTranslation() - vob->GetCollisionObject()->GetTrafoOld().GetTranslation();
				absMoveDist[VX]		= -absMoveDist[VX];
				absMoveDist[VZ]		= -absMoveDist[VZ];
				absMoveDist[VY]		= 0;
				vob->Move (absMoveDist);
*/
//				interferenceReport.blocking.walkStopChasm	= TRUE;

				return TRUE;
			};
//			Line3D (scanOrigin+scanAt, world->traceRayReport.foundIntersection, GFX_WHITE);
		};
	};
	return FALSE;
};
#endif
	//**********************************************************************************************************//
	//**********************************************************************************************************//


void                zCAIPlayer::CreateLedgeInfo                 (){
    s_ledgeCache[this];
}


zCAIPlayer::zTLedgeInfo  *zCAIPlayer::GetLedgeInfo              () const{
    if (s_ledgeCache.GetDataDangerous(this))
        return s_ledgeCache[this];
    else
        return NULL;
}

zBOOL           	zCAIPlayer::GetFoundLedge			        () const{
    return zBOOL(s_ledgeCache.GetDataDangerous(this));
}

void				zCAIPlayer::ClearFoundLedge           		(){
    s_ledgeCache.Delete(this);
}

#ifdef DEBUG_MOOS
#define s_extraFactor 2
#else
#define s_extraFactor 1
#endif

// static const int s_DetectLedgeRaycastFlags = zTRACERAY_STAT_POLY | zTRACERAY_POLY_NORMAL | zTRACERAY_VOB_IGNORE_NO_CD_DYN;

//static const  s_DetectLedgeRaycastFlags =    zTRACERAY_STAT_POLY				| zTRACERAY_POLY_NORMAL | 
//							                    zTRACERAY_VOB_IGNORE_NO_CD_DYN	| zTRACERAY_VOB_IGNORE_CHARACTER;

static enum { s_DetectLedgeRaycastFlags =       zTRACERAY_STAT_POLY				| zTRACERAY_POLY_NORMAL | 
        							            zTRACERAY_VOB_IGNORE_NO_CD_DYN	| zTRACERAY_VOB_IGNORE_CHARACTER };

// Block für rumgereichte Parameter
static zCAIPlayer *s_DetectLedgePlayer;
static zCVob      *s_DetectLedgeVob;
static zCWorld    *s_DetectLedgeWorld;
static zVEC3       s_DetectLedgeRayDir;
static zVEC3       s_DetectLedgeRayDirNormal;

static zREAL	   s_MV_DCUL_WALL_HEADING_ANGLE;
static zREAL	   s_MV_DCUL_WALL_HORIZ_ANGLE;
static zREAL	   s_MV_DCUL_GROUND_ANGLE;

// eine Klasse, die sich die waagerecht gecasteten Rays merkt:

class zCDetectLedgeReport{
public:
    zPOINT3 rayStart;   // Startpunkt des gecasteten Rays

    zBOOL      foundHit;   // gab es einen treffer?
    zCPolygon *hitPoly;    // getroffenes Polygon
    zCVob     *hitVob;    // getroffenes Polygon
    zVEC3      hitNormal;  // und seine Normale
    zPOINT3    hitPoint;   // getroffener Punkt

    zCDetectLedgeReport(const zPOINT3 &start)  // castet einen ray von start in Richtung s_DetectLedgeRayDir
    : foundHit(FALSE), rayStart(start), hitPoly(NULL), hitVob(NULL), hitNormal(0,0,0), hitPoint(0,0,0){
        if (s_DetectLedgeWorld->TraceRayNearestHit(start, s_DetectLedgeRayDir, s_DetectLedgeVob, s_DetectLedgeRaycastFlags))
        {
            foundHit        = TRUE;
            hitPoly         = s_DetectLedgeWorld->traceRayReport.foundPoly;
            hitVob          = s_DetectLedgeWorld->traceRayReport.foundVob;
            hitNormal       = s_DetectLedgeWorld->traceRayReport.foundPolyNormal;
            hitPoint        = s_DetectLedgeWorld->traceRayReport.foundIntersection;

            if ((hitPoint - rayStart).Length2() < zMV_DCUL_STEPBACK*zMV_DCUL_STEPBACK) // zu nah! mache einen Rückzieher.
                foundHit = FALSE;

            if (hitNormal.Length2() < .8) // kaputtige Normale!
                foundHit = FALSE;
        }           
    }
};

// die bisher beste gefundene Kante
static zPOINT3     s_DetectLedgePoint;
static zVEC3       s_DetectLedgeNormal;
static zVEC3       s_DetectLedgeCont;
static zREAL       s_DetectLedgeMaxMoveForward;
static zREAL       s_DetectLedgeValue;


/* ----------------------------------------------------------------------
	
    DetectClimbUpLedgeIdentifyAndRate()

    findet die Kante zwischen den beiden waagerechten RayCasts upper
    und lower, bewertet sie und merkt sie sich.

	 10.1.2001	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

static void DetectClimbUpLedgeIdentifyAndRate(const zCDetectLedgeReport &upper, const zCDetectLedgeReport &lower){

    zREAL value = 1;

    if (upper.foundHit && lower.hitNormal * (upper.hitPoint - lower.hitPoint) > 0) // dann ist die Kante konkav und garantiert nichts zum klettern
        return;


    // erste Konformitätstests: stimmt die Neigung des die Kante von unten begrenzenden Polygons?
    if (fabs(lower.hitNormal[VY]) > .99)
        return;  // nein! es ist fast flach.

	if (fabs(acos(lower.hitNormal[VY])) < s_MV_DCUL_GROUND_ANGLE / s_extraFactor) 
        return;  // nein! es zählt noch als Boden-Poly

    zVEC3 lowerHitNormalProj(-lower.hitNormal[VX], 0, -lower.hitNormal[VZ]);
    lowerHitNormalProj.Normalize();

    // Winkel zwischen Kante und Spieler OK?
    if (Alg_AngleUnitRad (lowerHitNormalProj, s_DetectLedgeVob->GetAtVectorWorld()) >= s_MV_DCUL_WALL_HEADING_ANGLE * s_extraFactor)
        return; //nein! Zu Steil.

    // Wandwinkel
	if (fabs(asin(lower.hitNormal[VY])) >= s_MV_DCUL_WALL_HORIZ_ANGLE * s_extraFactor) 
        return; // zu flach.


    // berechne den Vektor lowerToUpper so, dass er parallel zum von lower gefundenen Poly (dem underen Kletterkantenpoly) von
    // dem in lower gecasteten Ray zu dem in upper gecasteten führt.

    zVEC3 lowerToUpper = upper.rayStart - lower.rayStart;
    zREAL div          = s_DetectLedgeRayDirNormal * lower.hitNormal;
    if (div > -.01) // zu knapp
        return;

    lowerToUpper      -= s_DetectLedgeRayDirNormal * (lowerToUpper * lower.hitNormal) / div; // das macht ihn parallel zum Poly



    // gehe jetzt vom unteren gefundenen unteren Punkt etwas zurück (kein polytreffer möglich), dann richtung lowerToUpper (treffer->Abbruch) zum
    // oberen strahl, folge ihm etwas nach vorne (wieder kein treffer möglich) und gehe dann nach unten Richtung -lowerToUpper.
    // Der dabei hoffentlich getroffene Punkt ist der zweite, der für die Kletterkante wichtig ist.

    zPOINT3 rayStart = lower.hitPoint - s_DetectLedgeRayDirNormal * zMV_DCUL_STEPBACK;    // Schritt zurück

    if (s_DetectLedgeWorld->TraceRayNearestHit(rayStart, lowerToUpper, s_DetectLedgeVob, s_DetectLedgeRaycastFlags))
        return;                                                                          // Treffer beim Schritt nach oben

    rayStart += lowerToUpper +                                                           // mache den Schritt nach oben
                s_DetectLedgeRayDirNormal * (zMV_DCUL_STEPBACK + zMV_DCUL_STEPFORWARD);  // und gleich den nach vorne

    zPOINT3 upperHitPoint;
    zVEC3   upperHitNormal;

    if (!upper.foundHit || (rayStart - upper.hitPoint) * upper.hitNormal > 0)
    {
        // Dann hat der Schritt nach vorne kein Poly getroffen. Schritt nach unten muss ein Polygon treffen
        if (!s_DetectLedgeWorld->TraceRayNearestHit(rayStart, -lowerToUpper, s_DetectLedgeVob, s_DetectLedgeRaycastFlags))
            return;

        upperHitPoint  = s_DetectLedgeWorld->traceRayReport.foundIntersection;
        upperHitNormal = s_DetectLedgeWorld->traceRayReport.foundPolyNormal;
    }
    else
    {   // Schritt nach vorne hat das altbekannte Poly getroffen
        upperHitPoint  = upper.hitPoint;
        upperHitNormal = upper.hitNormal;
    }

    // damit sind die nötigen Infos aus der Welt gesammelt.

    // teste das oben angrenzende Polygon:
	if (upperHitNormal[VY] < cos(s_MV_DCUL_GROUND_ANGLE * s_extraFactor)) 
        return;  // es ist kein legitimes Boden-Poly. Pech.


    // nun wird es Zeit, die Kante gnau zu finden. Gehe dazu von lower.hitPoint soweit in Richtung lowerToUpper, bis die Ebene
    // des oberen Polygons erreicht ist.

    div = lowerToUpper * upperHitNormal;
    if (div < .01)
        return; // zu knapp

    zPOINT3 ledgePoint = lower.hitPoint + lowerToUpper * ((upperHitPoint - lower.hitPoint) * upperHitNormal) / div;


    // kann man die Kante von der Hüfte des Vob aus erreichen, ohne anzuecken?
    const zPOINT3& vobPos = s_DetectLedgeVob->GetPositionWorld();
    if (s_DetectLedgeWorld->TraceRayNearestHit(vobPos, (ledgePoint - vobPos) * .7F, s_DetectLedgeVob, s_DetectLedgeRaycastFlags))
        value *= .001f; // nein. aber besser als gar keine Kante...


    // wie geht es über der Kante weiter?
    zVEC3 cont    = s_DetectLedgeRayDir;
    cont         -= (cont * upperHitNormal) * upperHitNormal;
    cont            .NormalizeSafe();    

    // und wie weit kann man gehen?
    static const zREAL moveForward = 30;

    zREAL maxMoveForward = moveForward;
    if (s_DetectLedgeWorld->TraceRayNearestHit(ledgePoint + zVEC3(0,1,0), cont * (moveForward + 10), s_DetectLedgeVob, s_DetectLedgeRaycastFlags))
        maxMoveForward = (s_DetectLedgeWorld->traceRayReport.foundIntersection - ledgePoint).Length();

    maxMoveForward -=10;

    if (maxMoveForward < 10)
        value *= .001f;
   
    
    // prüfe den Platz. Direkt an der ausgewählten Stelle  [sowie 10 cm in mindestens zwei Richtungen, vielleicht später] sollte noch Platz sein.
    zVEC3 checkSpace = ledgePoint + maxMoveForward * cont * .5f + zVEC3(0, 1, 0);

    zCCollObjectCharacter *oc = s_DetectLedgePlayer->GetCollObject();

    zVEC3				                        transOut;
    zCCollObjectCharacter::zTSpatialState	    spatialStateOut;
    zVEC3				                        collisionNormalOut;

    if (oc->IsMoveInvalid(checkSpace, checkSpace + zVEC3(0, s_DetectLedgeVob->GetPositionWorld()[VY] - s_DetectLedgePlayer->GetFeetY(), 0), transOut, spatialStateOut, collisionNormalOut))
        return;

    // Bewerte die Kante nach ihrer Orientierung zum Spieler und der Entfernung. Zuerst die Entfernung:
    zREAL maxLen = s_DetectLedgePlayer->GetJumpUpHeight()*1.5;
    zREAL distValue  = 1 - (vobPos - ledgePoint).Length2() / (maxLen * maxLen);
    if (distValue < 0)
        distValue = 0;

    // dann die Orientierung:
    zREAL orValue = lowerHitNormalProj * s_DetectLedgeVob->GetAtVectorWorld();

    // und die "Spitzheit" der Kante
    zREAL edgeValue = .5F * (1 - lower.hitNormal * upperHitNormal);

    // natürlich der vorhandene Plazt
    zREAL spaceValue = maxMoveForward / moveForward;

    value *= distValue * orValue * edgeValue * spaceValue;

    // mal sehen, vielleicht fallen mir noch ein paar Kriterien ein.

    if (value > s_DetectLedgeValue) // die gefundene Kante ist besser als die bisherige. Mehre sie dir.
    {
        s_DetectLedgePoint          = ledgePoint;
        //s_DetectLedgeNormal       = lowerHitNormalProj;
        s_DetectLedgeNormal         = -lower.hitNormal;
        s_DetectLedgeCont           = cont;
        s_DetectLedgeMaxMoveForward = maxMoveForward;
        s_DetectLedgeValue          = value;
    }
}


/* ----------------------------------------------------------------------
	
    DetectClimbUpLedgeRecursive()

    findet eine geeignete Kletterkante zwischen den beiden RayCasts
    upper und lower

	 10.1.2001	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

static void DetectClimbUpLedgeRecursive(const zCDetectLedgeReport &upper, const zCDetectLedgeReport &lower){
    zVEC3 lowerToUpper = upper.rayStart - lower.rayStart;
    zREAL distance2    =lowerToUpper.Length2();

    // in diesem Fall kann zwischen den upper und lower keine Kante mehr liegen, die breiter als zMV_DCUL_VERT_MAX_THRESH cm ist. Brich die Suche ab.
    if ((lower.hitPoly == upper.hitPoly && !lower.hitVob) && (lower.foundHit || distance2 < zMV_DCUL_VERT_MAX_THRESH*zMV_DCUL_VERT_MAX_THRESH))
        return;

    // wenn upper und lower zu weit voneinander entfernt sind, suche noch genauer:
    if (distance2 > zMV_DCUL_VERT_MIN_THRESH * zMV_DCUL_VERT_MIN_THRESH)
    {
        zCDetectLedgeReport middle(lower.rayStart + .5F * lowerToUpper);
        DetectClimbUpLedgeRecursive(upper, middle);
        DetectClimbUpLedgeRecursive(middle, lower);
    }
    else if (lower.foundHit) // zwischen upper und lower sollte eine Kante liegen. Finde und bewerte sie.
        DetectClimbUpLedgeIdentifyAndRate(upper, lower);
}


/* ----------------------------------------------------------------------
	
    zCAIPlayer::DetectClimbUpLedge()

    findet eine Kletterkante.

	 10.1.2001	[Moos]	
                schnappt sich jetzt nicht mehr die erstbeste

   ---------------------------------------------------------------------- */


zBOOL zCAIPlayer::DetectClimbUpLedge (zPOINT3& resultLedgePoint, const zBOOL startYScanFromFeet) {
	
	// FIXME: das einzige was noch zu fehlen scheint:
	// Wenn der Boden relativ steil ist, koennte der geschaetzte 'ledgePoint' zu ungenau sein. Dieser zieht naemlich
	// nicht die Steigung des BodenPolys in Betracht. Die Folge: der ledgePoint ist zu etwas hoch. In manchen 
	// Situationen a) koennte er dadurch unerreichbar werden b) sieht es nicht gut aus.

	// 1) Wieviel Platz ist ueber dem Model ? => Ray schiessen
    // foundLedge = FALSE;

	zREAL	ceiling;
	zREAL	startY;
    zREAL   endY;
	//zREAL	scanHeight;

	if (world->TraceRayNearestHitCache (centerPos, zMV_UP, vob, zTRACERAY_VOB_IGNORE_NO_CD_DYN,&GetCollObject()->m_oUpRayCache))	ceiling = GetInters()[VY];
	else																					ceiling = zVALUE_MAX;
	// Zur Sicherheit wird die ScanHoehe ein wenig unterschaetzt (0.95F), damit keine Ledges hier als erreichbar 
	// gemeldet werden, die dann spaeter doch nicht erreicht werden.
	if (startYScanFromFeet)	{
		startY		= feetY;
//		scanHeight	= zMin (ceiling - startY, GetJumpUpHeight()*0.95F + (headY-feetY));
		endY    	= startY + zMin (ceiling - startY, GetJumpUpHeight()*0.95F + (headY-feetY));
	} else {
		startY		= headY;
//		scanHeight	= zMin (ceiling - startY, GetJumpUpHeight()*0.95F);
		endY    	= startY + zMin (ceiling - startY, GetJumpUpHeight()*0.95F);
	};

	if (world->TraceRayNearestHitCache (centerPos, zVEC3(0, startY - centerPos[VY], 0), vob, zTRACERAY_VOB_IGNORE_NO_CD_DYN,&GetCollObject()->m_oUpRayCache))	startY = GetInters()[VY] + 0.1F;

    // fülle die rumgereichten Daten:
    s_DetectLedgePlayer       = this;
    s_DetectLedgeVob          = vob; 
    s_DetectLedgeWorld        = world;
    s_DetectLedgeRayDirNormal = vob->GetAtVectorWorld();

    if (fabs(s_DetectLedgeRayDirNormal[VY]) < .9) // Mache die Scan-Richtung flach
    {
        s_DetectLedgeRayDirNormal[VY] = 0;
        s_DetectLedgeRayDirNormal.Normalize();
    }

    s_DetectLedgeRayDir       = s_DetectLedgeRayDirNormal * (zMV_DCUL_SCAN_DEPTH + zMV_DCUL_STEPBACK) * s_extraFactor;

    s_MV_DCUL_WALL_HEADING_ANGLE = config.zMV_DCUL_WALL_HEADING_ANGLE;
    s_MV_DCUL_WALL_HORIZ_ANGLE   = config.zMV_DCUL_WALL_HORIZ_ANGLE;
    s_MV_DCUL_GROUND_ANGLE       = config.zMV_DCUL_GROUND_ANGLE;

    s_DetectLedgeValue = -1;

	zVEC3			upperRayStart     = centerPos - s_DetectLedgeRayDirNormal * zMV_DCUL_STEPBACK;
                    upperRayStart[VY] = endY;
    zVEC3           lowerRayStart     = upperRayStart;
                    lowerRayStart[VY] = startY;

    DetectClimbUpLedgeRecursive(zCDetectLedgeReport(upperRayStart), zCDetectLedgeReport(lowerRayStart));

    if (s_DetectLedgeValue < 0){
        ClearFoundLedge();
        return FALSE;
    }

    CreateLedgeInfo();

    zTLedgeInfo *info       = GetLedgeInfo();
    info->point             = resultLedgePoint  = s_DetectLedgePoint;
    info->normal            = s_DetectLedgeNormal;
    info->cont              = s_DetectLedgeCont;
    info->maxMoveForward    = s_DetectLedgeMaxMoveForward;

	return TRUE;
};

void zCAIPlayer::AlignModelToLedge (const zSTRING& hangAniName) 
{
    zERR_ASSERT(GetFoundLedge());

	// Der erste Frame der Hang-Ani wird eingestellt, weil mit diesem gemessen wird !
	SetCDStat					(FALSE); 
	SetPhysicsEnabled			(FALSE);
	model->StartAni				(hangAniName, zCModel::zMDL_STARTANI_FORCE); 
	model->AdvanceAnis			();
	// align
	const zPOINT3& handPosWorld = GetHandPositionWorld();
	vob->Move				(GetLedgeInfo()->point - handPosWorld);
	vob->SetHeadingAtWorld	(GetLedgeInfo()->normal);
}; 

zVEC3 zCAIPlayer::GetHandPositionWorld () const 
{
	// FIXME: Vob-Methoden benutzen
	// nun Hände mit dem Ledge-Point alignen
	zCModelNodeInst *rightHand = model->SearchNode (zMDL_NODE_NAME_R_HAND);
	zCModelNodeInst *leftHand  = model->SearchNode (zMDL_NODE_NAME_L_HAND);
	if (!rightHand) return centerPos;
	if (!leftHand)	return centerPos;
	// FIXME: alleine die Pos wuerde schon reichen.. (?)
	zMATRIX4	trafoHandToWorld; 
	zPOINT3		handRPosWorld, handLPosWorld;
	trafoHandToWorld= vob->trafoObjToWorld * model->GetTrafoNodeToModel (rightHand);
	handRPosWorld	= trafoHandToWorld.GetTranslation();
	trafoHandToWorld= vob->trafoObjToWorld * model->GetTrafoNodeToModel (leftHand);
	handLPosWorld	= trafoHandToWorld.GetTranslation();

	return (handRPosWorld+handLPosWorld)*0.5;
};

void zCAIPlayer::AlignToFloor (const zREAL floorHeight) 
{
	zPOINT3 center		 = centerPos;
			center[VY]	-= (feetY-floorHeight);
	vob->SetPositionWorld (center);
};

zREAL zCAIPlayer::GetModelFloorWorld ()
{
	return (vob->GetPositionWorld()[VY] - model->GetRootPosLocal()[VY]);
};


	//**********************************************************************************************************//
	//**********************************************************************************************************//

zBOOL zCAIPlayer::CheckEnoughSpaceMoveDir (const zVEC3& unitDir, const zBOOL dontDetectWalkStopChasm)
{
	// Prueft, ob Model an aktueller Position in angegebene Richtung bewegt werden sollte (!).
	// a) ist die Luftlinie vom VobCenter nach unitDir auf x cm frei ?
	// b) ist der Boden in Richtung unitDir vor dem Model eine begehbare Schraege ?
	// c) wird der Raum zwischen Boden & Decke auch nicht zu eng ?? 
	// d) ist ein Abgrund (mindestens Falltiefe) vor dem Model ?

	// FIXME:
	// - ray-Tests zusammenlegen (z.B. nur 1 Ray fuer alle Rays in Richtung unitDir)
	// - Ray Laengen beschraenken (z.B. zMV_DOWN)

	const zBOOL		inWater		= ((state==zMV_STATE_DIVE) || (state==zMV_STATE_SWIM));
	const zPOINT3	scanOrigin	= GetSurfaceAlignScanOrigin();	// ein evtl. etwas nach oben versetzter centerPos
	int commonRayFlags			= zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE_NO_CD_DYN;

	// Falls Wasser (als solches) unberuecksichtigt bleiben soll, soll es als normales solid Poly behandelt werden und
	// auch von TraceRay zurueckgeliefert werden.
	if (GetTreatsWaterAsSolid())
		commonRayFlags	|=zTRACERAY_POLY_TEST_WATER;

	// a) ist die Luftlinie vom VobCenter nach unitDir auf x cm frei?
	{
		zREAL checkLen;
		//	if (inWater)	checkLen = zMax (checkWaterCollBodyLen, zMV_MIN_SPACE_MOVE_FORWARD * 1.3);
		//	else			checkLen = zMV_MIN_SPACE_MOVE_FORWARD;
		checkLen = zMax (checkWaterCollBodyLen, config.zMV_MIN_SPACE_MOVE_FORWARD * 1.3);
		if (world->TraceRayFirstHit (scanOrigin, unitDir*checkLen, vob, commonRayFlags)) return FALSE;
	};

	// Beim Schwimmen/Tauchen sind die Tests hier zuende..
	if (!inWater) 
	{
		// b) ist der Boden in Richtung unitDir vor dem Model eine begehbare Schraege ? 
		//    (im Wasser sind alle Schraegen begehbar) 
		//	  (Vobs bleiben unberuecksichtigt)
		//    ACHTUNG: diese Stelle ist sehr sensibel fuer Slide/Water
		//	  FIXME: Hier gibt es noch ein Problem: wenn Vobs unberuecksichtigt bleiben, kann man auf Vob-Bruecken einmal
		//           stehengeblieben nicht mehr weiterlaufen. Falls Vobs beruecksichtigt werden, wuerde man auch an/auf kleinen
		//           Vobs haengen bleiben (kleine Steine). (Kriterium Vob-BBox-Size?)
		zREAL			downHitY	= -99999999.0F;			// wird fuer Test c) benoetigt, wird pre-inited, falls hier gleich kein realer Werte gefunden werden kann
		const zVEC3&	scanStart	= scanOrigin + unitDir * (config.zMV_MIN_SPACE_MOVE_FORWARD * 0.5); 
		// ==0, no transpPoly
		if (world->TraceRayNearestHit (scanStart, zMV_DOWN, vob, commonRayFlags | zTRACERAY_STAT_POLY | zTRACERAY_POLY_NORMAL | zTRACERAY_VOB_IGNORE))	// zTRACERAY_POLY_IGNORE_TRANSP 
		{
			downHitY				= world->traceRayReport.foundIntersection[VY];
			if (waterLevel==0) 
			{
				{
					const zVEC3& polyNormal = world->traceRayReport.foundPolyNormal;
					zREAL	slope			= this->CalcFloorSlopeRad (polyNormal[VY]);

					if (slope<M_PI)							// scheint noetig..
					if (slope>config.zMV_MAX_GROUND_ANGLE_WALK) 
					{ 
						// Falls ein statisches Poly mit entspr. Steigung gefunden wurde, wird noch geschaut, ob zwischen Model
						// und diesem Poly sich vielleicht ein Vob befindet, dass ein Gehen auf demselben zulassen wuerde.
						const zVEC3 rayDir = world->traceRayReport.foundIntersection - scanStart;
						if (!world->TraceRayNearestHit (scanStart, rayDir, vob, commonRayFlags | zTRACERAY_STAT_IGNORE)) 
						{
							// Poly gefunden, dass zum drauf gehen zu steil ist, nur .. geht es auf oder abwaerts ?
							// Nun muss ermittelt werden, ob mann die Schraege von oben oder unten betritt..
							// FIXME: hat zMV_GROUND_OFFSET Auswirkung ??
							if (GetFloorY()<world->traceRayReport.foundIntersection[VY]) {
								// Schraege aufwaerts
								return FALSE;
							} else {
								// Schraege abwaerts
								return FALSE;
							};
						};
					};
				};
			};
		};

		// c) Wird der Raum zwischen Boden & Decke auch nicht zu eng ?? (ist von Test a. anhängig)
		if (world->TraceRayNearestHit (scanStart, zMV_UP, vob, commonRayFlags)) 
		{
			zREAL upHitY = world->traceRayReport.foundIntersection[VY];
			if ((upHitY-downHitY)<GetProtoYHeight() && (upHitY - downHitY) <= (GetCeilingY() - GetFloorY())) return FALSE;   // [Moos] 11.1.01 : zweite Bedingung: Erlabe jedenfalls die Bewegung, wenn sich der verfügbare Platz vergrössert
		};

		// d) ist ein Abgrund (mindestens Falltiefe) vor dem Model ?
		//    (natuerlich nur checken, wenn nicht mit Wasser in Kontakt)
		if ((zMV_DO_DETECT_WALK_STOP_CHASM)							&&
			(!GetCollObject()->GetSpatialState().m_bFloorIsStair)	&&
			(waterLevel==0)											&&
			(!dontDetectWalkStopChasm))
		{
			// Es muss in Richtung der Gehbewegung gescannt werden (nicht at!)
 			const zVEC3 scanAt= unitDir * config.zMV_DETECT_CHASM_SCAN_AT; 
			if (!world->TraceRayNearestHit (scanOrigin, scanAt, vob, commonRayFlags)) 
			{
				const zVEC3 scanDown = zVEC3(0,-((scanOrigin[VY]-feetY) + config.zMV_STEP_HEIGHT), 0);
				Line3D (scanOrigin+scanAt, scanOrigin+scanAt+scanDown, GFX_WHITE);
				if (!world->TraceRayNearestHit (scanOrigin+scanAt, scanDown, vob, commonRayFlags)) 
				{    
					Print ("chasm detected (check enoughSpaceDir)");
					return FALSE; 
				};
			};
		};
	};

	return TRUE;
};

zBOOL zCAIPlayer::CheckEnoughSpaceMoveForward (const zBOOL dontDetectWalkStopChasm) {
	return CheckEnoughSpaceMoveDir (vob->GetAtVectorWorld(), dontDetectWalkStopChasm);
};

zBOOL zCAIPlayer::CheckEnoughSpaceMoveBackward (const zBOOL dontDetectWalkStopChasm) {
	return CheckEnoughSpaceMoveDir (-vob->GetAtVectorWorld(), dontDetectWalkStopChasm);
};

zBOOL zCAIPlayer::CheckEnoughSpaceMoveRight (const zBOOL dontDetectWalkStopChasm) {
	return CheckEnoughSpaceMoveDir (vob->GetRightVectorWorld(), dontDetectWalkStopChasm);
};

zBOOL zCAIPlayer::CheckEnoughSpaceMoveLeft (const zBOOL dontDetectWalkStopChasm) {
	return CheckEnoughSpaceMoveDir (-vob->GetRightVectorWorld(), dontDetectWalkStopChasm);
};

zREAL zCAIPlayer::GetProtoYHeight () 
{
	// FIXME: diesen Wert cachen ! (ACHTUNG: was bei modelProto-Wechsel !)
	const zTBBox3D& protoBBox3D = model->GetBBox3DLocalFixed();
	return protoBBox3D.maxs[VY] - protoBBox3D.mins[VY];
};

zPOINT3 zCAIPlayer::GetSurfaceAlignScanOrigin()
{
	// basierend auf 'centerPos', noetig um den Einfluss des zMV_DO_SURFACE_ALIGN Flags
	// geltend zu machen. Ergebnis ist ggfs. etwas in Rictung UpVector geoffsetet.

	if (zMV_DO_SURFACE_ALIGN==zMV_SURFACE_ALIGN_HIGH)
	{
		const zREAL scanOriginYOffset = GetProtoYHeight() * zREAL(0.65F);
		if (scanOriginYOffset!=0) 
		{

			enum { rayFlags =	zTRACERAY_STAT_POLY				| zTRACERAY_POLY_NORMAL | 
								zTRACERAY_VOB_IGNORE_NO_CD_DYN	| zTRACERAY_VOB_IGNORE_CHARACTER };

			const zVEC3& offs = scanOriginYOffset * zVEC3(0, 1, 0); //vob->GetUpVectorWorld(); //[Moos] verhindere Gezumpel und gehe direkt nach oben.
			if (world->TraceRayNearestHitCache (centerPos, offs, vob, rayFlags, &GetCollObject()->m_oUpRayCache)) 
			{
				return centerPos + zREAL(0.8F) * (world->traceRayReport.foundIntersection - centerPos);
			} else
				return centerPos + offs;
		};
	};

	return centerPos;
};

void zCAIPlayer::DiveRotateX (const zREAL& angle)
{
//	const zREAL zMV_DIVE_MAX_DOT_X = 0.2F;
//	const zREAL zMV_DIVE_MAX_ROT_X = Alg_Rad2Deg(acos(zMV_DIVE_MAX_DOT_X)); 
	const zREAL zMV_DIVE_MAX_ROT_X = 80.0F;

	//	zVEC3 at	= (vob->GetRightVectorWorld() ^ zVEC3(0,1,0));	
	//	zREAL dot	= at * vob->GetAtVectorWorld();
	zVEC3 at		= vob->GetRightVectorWorld();
		  at		= zVEC3(-at[VZ], 0, at[VX]);
	zREAL dot		= (at[VX]*vob->GetAtVectorWorld()[VX] + at[VZ]*vob->GetAtVectorWorld()[VZ]); 
	zClamp			(dot, zREAL(-1), zREAL(+1));

	zREAL actAngle	= Alg_Rad2Deg(acosf(dot));
	zREAL doAngle;
	if (vob->GetAtVectorWorld()[VY]>0)	doAngle	= -(zMin (zMV_DIVE_MAX_ROT_X, actAngle - (angle)) - actAngle); 
	else								doAngle	=   zMin (zMV_DIVE_MAX_ROT_X, actAngle + (angle)) - actAngle; 

	vob->RotateLocalX (doAngle);
}

void zCAIPlayer::SetCDStat (const zBOOL b) 
{
	if (cdStatOriginal)	cdStat = b; 
	else				cdStat = FALSE;
	vob->SetCollDetStat (cdStat);
};

void zCAIPlayer::LandAndStartAni (const zSTRING& aniName) 
{
	LandAndStartAni (model->GetAniFromAniName (aniName));
};

void zCAIPlayer::LandAndStartAni (zCModelAni *modelAni) 
{
	if (!CheckFloorSliding()) 
	{
		if (ShouldCorrectFloorHeight()) 
		{ 
			model->StartAni			   (modelAni);
			SetPhysicsEnabled		   (FALSE);
            vob->ResetXZRotationsWorld ();            // [Moos] Sicherheit, falls der NPC in der Luft gedreht wurde (z.B. vom an der Kante baumeln...)
//			vob->SetPositionWorld	(newCenter);  

			// Particle-Effekt
			if (waterLevel==0)	startFXModelLandDust = TRUE;
		};
	};
};

zBOOL zCAIPlayer::CheckForceModelHalt (const zSTRING& aniName) 
{
	if (forceModelHalt) {
		model->StartAni (aniName);
		forceModelHalt = FALSE;
		return TRUE;
	} else
		return FALSE;
};

zBOOL zCAIPlayer::CheckForceModelHalt (zCModelAni *modelAni) 
{
	if (forceModelHalt) {
		model->StartAni (modelAni);
		forceModelHalt = FALSE;
		return TRUE;
	} else
		return FALSE;
};


zBOOL zCAIPlayer::ShouldCorrectFloorHeight () 
{
	return (aboveFloor<=config.zMV_STEP_HEIGHT);
};


	//**********************************************************************************************************//
	// BEGIN STATE SWITCH																						//
	//**********************************************************************************************************//

void zCAIPlayer::BeginStateSwitch() 
{
	// werden beide in den jeweiligen States evtl. durch SWIM/DIVE ueberschrieben..
	if ((vob->GetPhysicsEnabled()) || (model->GetIsFlying()))	state = zMV_STATE_FLY;

	// Falls das Model faellt muss dessen Falltiefe getrackt werden
	{
		if (oldState!=zMV_STATE_FLY) 
		{
			fallDownStartY		= centerPos[VY];
			// Patch 1.08a {Wohlers] : fallDownDistanceY resetten.
			fallDownDistanceY	= 0;
		};

		// Model im physikalischen Fall?
		if ((vob->GetPhysicsEnabled()) && (vob->GetRigidBody()->GetMode()!=zPHY_RBMODE_SLIDE)) 
		{
			fallDownDistanceY	= fallDownStartY - centerPos[VY]; 
		};
	};
};

	//**********************************************************************************************************//

void zCAIPlayer::SetPhysicsEnabled (zBOOL b) 
{ 
	vob->SetPhysicsEnabled(b); 
};

void zCAIPlayer::StartPhysicsWithVel () 
{ 
	// Physik wird angeschmissen und dabei auch gleich die Bewegung aus der Animation auf die Physik
	// übertragen
	SetPhysicsEnabled					(TRUE); 
	vob->GetRigidBody()->SetVelocity	(velocity); 
};

void zCAIPlayer::StartStandAni () 
{
	model->StartAni (_s_run);
}; 

void zCAIPlayer::StartFallDownAni () 
{
	model->StartAni ("S_FALLDN");
};

void zCAIPlayer::Archive (zCArchiver& arc) 
{
	zCAIBase::Archive (arc);

	// FIXME: evtl. hier nicht Daten des CollObjects speichern, sondern das CollObject das selber erledigen lassen!
	if (arc.InSaveGame())
	{
//		zERR_ASSERT (vob);
		if ((vob) && GetCollObject())
		{
			arc.WriteInt	("waterLevel"	, waterLevel);
			arc.WriteFloat	("floorY"		, GetCollObject()->GetSpatialState().m_fFloorY);
			arc.WriteFloat	("waterY"		, GetCollObject()->GetSpatialState().m_fWaterY);
			arc.WriteFloat	("ceilY"		, GetCollObject()->GetSpatialState().m_fCeilingY);
			arc.WriteFloat	("feetY"		, feetY);
			arc.WriteFloat	("headY"		, headY);
			arc.WriteFloat	("fallDistY"	, fallDownDistanceY);
			arc.WriteFloat	("fallStartY"	, fallDownStartY);
		};
	};
};
 
void zCAIPlayer::Unarchive (zCArchiver& arc) 
{	
	zCAIBase::Unarchive (arc);

	//
	if (arc.InSaveGame())
	{
		// Das Parent Object im Archive muesste der Vob sein, dem diese AI gehoert
		zCObject	*parentObject	= arc.GetParentObject();
		zCVob		*parentVob		= zDYNAMIC_CAST<zCVob>(parentObject);

		if (parentVob)
		{
			// gefundenen parentVob kurzzeitig an die 'offizielle' Stelle setzen, damit der sein CollObject erzeugen kann etc.
			zSwap			(parentVob, this->vob);
			{
				if (!GetCollObject())	vob->CreateCollisionObject();
				arc.ReadInt	    ("waterLevel"	, waterLevel);
				arc.ReadFloat	("floorY"		, GetCollObject()->GetSpatialState().m_fFloorY);
				arc.ReadFloat	("waterY"		, GetCollObject()->GetSpatialState().m_fWaterY);
				arc.ReadFloat	("ceilY"		, GetCollObject()->GetSpatialState().m_fCeilingY);
				arc.ReadFloat	("feetY"		, feetY);
				arc.ReadFloat	("headY"		, headY);
				arc.ReadFloat	("fallDistY"	, fallDownDistanceY);
				arc.ReadFloat	("fallStartY"	, fallDownStartY);
			};
			// .. und wieder zuruecktauschen
			zSwap			(parentVob, this->vob);
		};
	};
};

#ifdef zMV_DEBUG
	void zCAIPlayer::Print		(const zSTRING& s) const						{ zerr.Message ("D: AI_CHAR: "+s); };
	void zCAIPlayer::Line3D		(const zVEC3& a, const zVEC3& b, int col) const	{ zlineCache.Line3D (a,b,col); };
	void zCAIPlayer::PrintScreen(int xscr, int yscr, zSTRING s) const			{ 
		zrenderer->Vid_BeginLfbAccess	();
		screen->Print					(xscr, yscr, s); 
		zrenderer->Vid_EndLfbAccess		();
	};
#else
	void zCAIPlayer::Print		(const zSTRING& s) const						{ };
	void zCAIPlayer::Line3D		(const zVEC3& a, const zVEC3& b, int col) const	{ };
	void zCAIPlayer::PrintScreen(int xscr, int yscr, zSTRING s) const	{ };
#endif

	//**********************************************************************************************************//
	//**********************************************************************************************************//
	//**********************************************************************************************************//

/*

  Wasser:
  *******

  gefixt:
  - Die RootNode von 'S_SWIM' muss animiert sein: => sonst klappt S_SWIM/S_SWIMB Wechsel nicht
  - Die Ani "T_DIVEF_2_SWIM" muss 0 Laenge haben => das Auftauchen ist abrupt (Ani-Wechsel & ResetRot)
	- => if (headY>GetWaterY())	{ model->StartAni ("S_SWIM");	} else
	- Beim Übergang gleich "S_SWIM" starten & ResetRotationsXZ() ausfuehren ?
  - S_WalkWL => S_SWIMF
	waehrend beide Anis laufen (langer ani-blend) ist der State=STAND. Deshalb wird waehrend des
	Blends die falsche Hoehe fuer das Model genommen. 
	- lerp beider Hoehen => dann muss aber der State=SWIM/STAND erkannt werden..
	- Anis im .MDS mit deren State kennzeichnen ? oder autom. über Namen ? (Dive,swim)
	- OOPS: passiert sogar bei Transition "T_SWIM_2_SWIMF" und umgekehrt ..
	x schnellerer Blend? 
	x => derzeitige Loesung: falls wl=2 und state==stand then state=oldstate

  noch offen:
  x Uebergang: swim (waterLevel2) => walk (wl0)		"step too high"
  x Uebgerang: wl1 => wl2 (falldn)					"fall down"


  Bemerkungen:
  x TraceRay-Polys / Vobs / Winkelabfragen
    (was: Bei der Auswertung von PolyNormals wird oft nicht geprueft, ob die Polys von Vobs sind... )
    Problem: manche Vob-Meshes sind sehr klein und koennen voellig frei orientierte Polys enthalten. Dabei
	wuerden einige Routinen die auf Winkel checken reagieren und ungewuenschte Ergebnisse liefern. (z.B. das
	sliden auf dem Stein einer Feuerstelle ..).
	Allerdings kann man sich auch sehr grosse Vob-Meshes vorstellen, bei denen definitiv alle Winkel Checks 
	erwuenscht sind (slide etc.).
	derzeitige Loesung	:		Vob-Polys werden aus !!BODEN!!-Winkel Checks rausgehalten
	Endloesung			:		Vob-Polys nur hineinnehmen, wenn groesse des Vobs einen THRESH überschreitet (oder Collision-Type => gross/klein)
	betroffene Routinen	: CheckEnoughSpaceMoveDir(), CheckFloorSliding()


  Collision-Probs: 
  x Bei der Auswertung von PolyNormals wird oft nicht geprueft, ob die Polys von Vobs sind...
	=> z.B. walk ueber Stein im OC, "bounce"
	=> vielleicht gleich bei Checks dieser Art Winkel Checks auf Vob-Polys unterlassen ??
	   gehen über einen Eimer... (vielleicht auch vom CollType abh. machen)
*/

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
 
  