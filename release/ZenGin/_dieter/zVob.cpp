/******************************************************************************** 
 
     $Workfile:: zVob.cpp             $                $Date:: 24.04.01 17:34   $
     $Revision:: 76                   $             $Modtime:: 23.04.01 17:30   $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zVob.cpp $
 * 
 * 76    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 75    15.03.01 2:17 Hildebrandt
 * 
 * 74    13.02.01 22:08 Hildebrandt
 * 
 * 73    13.02.01 18:32 Hildebrandt
 * 
 * 72    13.02.01 17:47 Hildebrandt
 * 
 * 71    13.02.01 1:08 Hildebrandt
 * 
 * 70    9.02.01 2:36 Hildebrandt
 * 
 * 69    8.02.01 14:53 Moos
 * 
 * 66    6.02.01 17:56 Moos
 * 
 * 65    6.02.01 9:51 Moos
 * 
 * 64    5.02.01 18:01 Moos
 * 
 * 63    2.02.01 13:04 Moos
 * 
 * 62    2.02.01 0:56 Hildebrandt
 * 
 * 61    1.02.01 19:58 Moos
 * 
 * 60    1.02.01 18:20 Hildebrandt
 * 
 * 59    1.02.01 2:52 Hildebrandt
 * 
 * 58    30.01.01 5:16 Hildebrandt
 * 
 * 57    25.01.01 12:14 Moos
 * 
 * 56    25.01.01 2:59 Hildebrandt
 * 
 * 55    23.01.01 21:01 Hildebrandt
 * 
 * 54    23.01.01 18:11 Hildebrandt
 * 
 * 53    16.01.01 3:31 Hildebrandt
 * 
 * 52    10.01.01 17:27 Hildebrandt
 * 
 * 51    9.01.01 17:10 Hildebrandt
 * 
 * 50    8.01.01 17:56 Hildebrandt
 * 
 * 49    20.12.00 3:03 Hildebrandt
 * 
 * 48    5.12.00 19:04 Hildebrandt
 * 
 * 47    22.11.00 20:06 Hildebrandt
 * 
 * 46    22.11.00 4:12 Hildebrandt
 * 
 * 45    20.11.00 18:47 Hildebrandt
 * 
 * 44    17.11.00 17:58 Hildebrandt
 * 
 * 43    17.11.00 1:28 Hildebrandt
 * 
 * 41    8.11.00 18:15 Hildebrandt
 * 
 * 40    7.11.00 18:24 Hildebrandt
 * 
 * 39    7.11.00 17:24 Hildebrandt
 * 
 * 38    3.11.00 19:05 Hildebrandt
 * 
 * 37    26.10.00 2:23 Hildebrandt
 * 
 * 36    25.10.00 15:06 Hildebrandt
 * 
 * 35    17.10.00 16:31 Hildebrandt
 * 
 * 34    13.10.00 15:04 Hildebrandt
 * 
 * 33    12.10.00 23:57 Hildebrandt
 * 
 * 32    12.10.00 20:28 Hildebrandt
 * 
 * 31    11.10.00 19:44 Hildebrandt
 * 
 * 30    22.09.00 23:27 Hildebrandt
 * 
 * 29    19.09.00 13:07 Hildebrandt
 * 
 * 28    7.09.00 19:39 Hildebrandt
 * 
 * 27    2.09.00 7:45 Hildebrandt
 *  
 * 26    1.09.00 18:01 Hildebrandt
 * 
 * 25    31.08.00 17:04 Hildebrandt
 * 
 * 24    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 23    23.08.00 19:22 Hildebrandt
 * 
 * 22    22.08.00 19:47 Hildebrandt
 * 
 * 21    21.08.00 17:18 Hildebrandt
 * 
 * 20    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 20    9.08.00 17:12 Admin
 * 
 * 19    1.08.00 12:35 Speckels
 * 
 * 18    21.07.00 19:55 Hildebrandt
 * 
 * 17    21.07.00 15:11 Hildebrandt
 * 
 * 16    21.07.00 14:28 Hildebrandt
 * 
 * 15    6.07.00 13:45 Hildebrandt
 * 
 * 9     10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 8     8.05.00 21:18 Hildebrandt
 * 
 * 7     8.05.00 18:17 Hildebrandt
 * zenGin 089g
 * 
 * 6     4.05.00 20:17 Hildebrandt
 * zenGin 089e
 * 
 * 5     3.05.00 23:57 Hildebrandt
 * zenGin 089d
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 26    22.03.00 21:07 Hildebrandt
 * 
 * 25    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 24    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 22    23.02.00 1:19 Hildebrandt
 * 
 * 21    22.02.00 23:38 Hildebrandt
 * 
 * 20    22.02.00 22:05 Hildebrandt
 * 
 * 19    22.02.00 19:53 Hildebrandt
 * 
 * 18    22.02.00 19:08 Hildebrandt
 * fixed RemoveVobSubtreeFromWorld() not deleting globalVobTreeNode when
 * there's no subtree
 * 
 * 17    22.02.00 2:02 Hildebrandt
 * zenGin 087d
 * 
 * 16    19.02.00 17:35 Hildebrandt
 * 
 * 15    18.02.00 3:05 Hildebrandt
 * zenGin 087b
 * 
 * 14    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 12    10.01.00 21:34 Hildebrandt
 * 
 * 11    10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 9     18.11.99 22:18 Hildebrandt
 * 
 * 8     18.11.99 0:28 Hildebrandt
 * 
 * 7     16.11.99 19:49 Hildebrandt
 * 
 * 6     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 76 $ ($Modtime: 23.04.01 17:30 $)

// ==================================================================================================================

#include <zCore.h>
#include <zVob.h>

#include <z3d.h>
#include <zWorld.h>
#include <zModel.h>
#include <zAI.h>
#include <zPhysics.h> 
#include <zRenderer.h>
#include <zBuffer.h> 
#include <zArchiver.h>
#include <zArchiverGeneric.h>
#include <zSky.h>
#include <zEventMan.h>
#include <zView.h>
#include <zMorphMesh.h>
#include <zVobMisc.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

#include <zAccount.h>

// ==================================================================================================================

// STL
#include <map>
using namespace std;


#ifdef DEBUG_HILDEBRANDT
//	#define zVOB_DEBUG_CD
//	#define zDEBUG_EVENT_MESSAGES
	#define zDEBUG_COLLECT_STATS
#endif


//#define	TEST_MORPH
 
#ifdef zVOB_DEBUG_CD 
	static inline void db_Print			(const zSTRING& s)											{ zerr.Message (s); };
	static inline void db_Line3D		(const zPOINT3& a, const zPOINT3& b, int color= GFX_YELLOW) { zlineCache.Line3D (a,b, color); };
	static inline void db_DrawBBox3D	(const zTBBox3D bbox, int color= GFX_YELLOW)				{ bbox.Draw (color); };
	static inline void db_DrawBSphere3D	(const zTBSphere3D bbox, int color= GFX_YELLOW)				{ bbox.Draw (color); };
	static inline void db_DrawWire		(zCPolygon *poly, int color= GFX_YELLOW)					{ poly->DrawWire (color); }; 
#else
	static inline void db_Print			(const zSTRING& s)											{ };
	static inline void db_Line3D		(const zPOINT3& a, const zPOINT3& b, int color= GFX_YELLOW) { };
	static inline void db_DrawBBox3D	(const zTBBox3D bbox, int color= GFX_YELLOW)				{ };
	static inline void db_DrawBSphere3D	(const zTBSphere3D bbox, int color= GFX_YELLOW)				{ };
	static inline void db_DrawWire		(zCPolygon *poly, int color= GFX_YELLOW)					{ }; 
#endif

//
zCLASS_DEFINITION				( zCEventMessage	, zCObject		,	0,	1)
	zCLASS_DEFINITION			( zCEventCore		, zCEventMessage,	0,	0)
zCLASS_DEFINITION				( zCVobLightPreset	, zCObject		,	0,	0)
								
// vob classes, that are explicitly known to the engine

	zCLASS_DEFINITION			( zCVob				, zCObject		,	0,	5)
	zCLASS_DEFINITION			( zCVobLevelCompo	, zCVob			,	0,	0)

// Visual
zCLASS_DEFINITION_ABSTRACT		( zCVisual			, zCObject		,	0)
	zCLASS_DEFINITION_ABSTRACT	( zCVisualAnimate	, zCVisual		,	0)



// ==================================================================================================================

/*
	Achtung:
	Bewegungen wie z.B. in Quake/Duke etc. sind immer eine Mischung aus Lokal und World...

	Move 
	SetPosition
	Translate
	SetTranslation
	Rotate
	SetRotation / SetOrientation
*/

///////////////////////////////////////////////////////////////////////////
//    VOB
///////////////////////////////////////////////////////////////////////////

// fuer Movement-Block / CD 
zBOOL						zCVob::s_vobAlreadyInMovement	= FALSE;
							
zCMesh*						zCVob::s_shadowMesh				= 0;
zTVobID						zCVob::s_nextFreeID				= 0;
zBOOL						zCVob::s_ignoreVisuals			= FALSE;
zBOOL						zCVob::s_renderVobs				= TRUE;
zBOOL						zCVob::s_showHelperVisuals		= FALSE;
zBOOL						zCVob::s_enableAnimations		= TRUE;

zCCollisionDetector*		zCVob::s_poCollisionDetector	= 0;


// aus Compile-Time-Performance-Gruenden ist diese map nicht static member von zCVob, sondern File-lokal.
typedef map<zCClassDef*,zCVisual*>		zTHelperVisualMap; 
typedef zTHelperVisualMap::value_type	zTHelperVisualMapVal;
typedef zTHelperVisualMap::iterator		zTHelperVisualMapIter;
static  zTHelperVisualMap				s_helperVisualMap;			// ordnet jeder Vob-Klasse ein Helper-Visual zu (= anklickbare Darstellung im Spacer)

// zero funcs for zEVENT_INTERFACE
void zCVob::OnTrigger			(zCVob* otherVob, zCVob *vobInstigator) {};
void zCVob::OnUntrigger			(zCVob* otherVob, zCVob *vobInstigator) {};
void zCVob::OnTouch				(zCVob* otherVob) {};
void zCVob::OnUntouch			(zCVob* otherVob) {};
void zCVob::OnTouchLevel		() {};
void zCVob::OnDamage			(zCVob*			otherVob, 
								 zCVob*			inflictorVob, 
								 zREAL			damage,  
								 int			damageType, 
								 const zVEC3&	hitLocation) {};
void zCVob::OnMessage			(zCEventMessage *eventMessage, zCVob* sourceVob) {};


zCVob::zCVob() : vobLeafList(4)
{
	type						= zVOB_TYPE_NORMAL;
	trafoObjToWorld             = Alg_Identity3D();
    trafo                       = NULL;
	globalVobTreeNode			= 0;
	homeWorld					= 0;
	visual						= 0;
	vobPresetName				= 0;
	lightColorStat				= lightColorDyn = zCOLOR(0,0,0,0);		// 0 wichtig! => markiert als noch nicht berechnet/dirty
	lightDirectionStat			= zVEC3(0);
	lightColorStatDirty			= TRUE;
	lightColorDynDirty			= TRUE;
	lastTimeDrawn				= -1;
	lastTimeCollected			= 0; 
	bbox3D.InitZero				();
	visualCamAlign				= zVISUAL_CAMALIGN_NONE;
	dontWriteIntoArchive		= FALSE;
								
	// Physik					
	sleepingMode				= zVOB_SLEEPING;
	rigidBody					= 0;
	physicsEnabled				= FALSE;						// MUSS hier stehen, Set..() prueft doch auf static..
	collButNoMove				= 0;
	isInMovementMode			= zVOB_MOVE_MODE_NOTINBLOCK;
	mbHintTrafoLocalConst		= FALSE;
	mbInsideEndMovementMethod	= FALSE;
	visualAlpha					= 1;							// 0..1
	visualAlphaEnabled			= FALSE;
	groundShadowSizePacked		= 0;
								
	//							
	eventManager				= 0;							// eventManager is created lazily
								
	//							
	m_poCollisionObject			= 0;
	m_poCollisionObjectClass	= zCCollObjectUndef::S_GetCollObjClass();
								
								
	// callbacks				
	callback_ai					= 0;
	// Set-Methoden immer am Ende
	//	vobID						= 0;
	ResetOnTimer				();
//	SetVobID					(GetNextFreeVobID());
	SetDrawBBox3D				(FALSE);
	SetShowVisual				(TRUE);		
	SetCollDetStat				(FALSE);
	SetCollDetDyn				(FALSE);
	SetPhysicsEnabled			(FALSE);
	SetStaticVob				(FALSE);
	SetCastDynShadow			(zDYN_SHADOW_TYPE_NONE);
	SetIgnoredByTraceRay		(FALSE);
	SetGroundPoly				(0);
	SetFarClipZScale			(1.0f);

#ifndef TEST_MORPH
	SetVisualAniMode			(zVISUAL_ANIMODE_NONE);
	SetVisualAniModeStrength	(0);
#else
	SetVisualAniMode			(zVISUAL_ANIMODE_WIND);
	SetVisualAniModeStrength	(1);
#endif
	SetZBias					(DEFAULT_VOB_ZBIAS);
	bsphere3D.radius	= FLT_MAX;
	this->bIsInWater	= FALSE;
	this->bIsAmbientVob = FALSE;

};

zCVob::~zCVob() 
{
	zERR_ASSERT (GetRefCtr()<=0);
	if (GetRefCtr()>0)
		zERR_FAULT ("D: tried to delete zCVob with refCtr>0 !");


#ifdef _DEBUG
    if (globalVobTreeNode || homeWorld){
        zCAccount::Sum(this);
    }
#endif

	// Vob IMMER ueber die zCWorld removen, nie direkt ueber this->RemoveWorldDependencies()
	RemoveVobFromWorld();

	// eine evtl. noch bestehenden globalVobTreeNode aufraeumen (sollte eigentlich nicht vorkommen)
	if (globalVobTreeNode)
	{
        if (globalVobTreeNode->GetParent())
            globalVobTreeNode->RemoveSubtree();                       // [Moos] baue den Baum richtig ab
        while (globalVobTreeNode->GetFirstChild())
            globalVobTreeNode->GetFirstChild()->RemoveSubtree();

		delete globalVobTreeNode; globalVobTreeNode=0;
	};

	// referenzierte Objekte releasen/deleten
	zRELEASE (visual);
	zRELEASE (callback_ai);
	zRELEASE (eventManager);
	delete vobPresetName;		vobPresetName		= 0;
	delete rigidBody;			rigidBody			= 0;
	delete m_poCollisionObject;	m_poCollisionObject	= 0;
	m_poCollisionObjectClass = 0;							// not owned

	// Vob aus World entfernen:
	// Vob aus BSP-Tree entfernen
	// Vob aus globalVobTree entfernen
	//   "     activeVobList "
	groundPoly				= 0;
	globalVobTreeNode		= 0;
	homeWorld				= 0;

	// FIXME: ?????
//	isInMovement		= FALSE;
};

void zCVob::InitVobSystem () 
{
	LoadGroundShadowMesh							();
	s_poCollisionDetector							= zNEW(zCCollisionDetector);
	zCCollObjectBase::S_RegisterCollisionTestFuncs	(S_GetCollisionDetector());
};

void zCVob::CleanupVobSystem () 
{
	DeleteGroundShadowMesh();

	// statische Helper-Visual Liste freigeben
	for (zTHelperVisualMapIter iter = s_helperVisualMap.begin(); iter!=s_helperVisualMap.end(); ++iter)
	{
		zCVisual *vis = iter->second;
		zRELEASE(vis);
	};

	//
	delete s_poCollisionDetector;	s_poCollisionDetector=0;
};

void zCVob::ResetIDCtr() 
{
	s_nextFreeID = 0;
};

zTVobID zCVob::GetNextFreeVobID() 
{
	return s_nextFreeID;
};

void zCVob::SetVobID (const zTVobID& id) 
{
//	vobID=id;
//	if (vobID>=s_nextFreeID) s_nextFreeID=vobID+1;		// FIXME
};

void zCVob::SetAI (zCAIBase* cbai)
{
	if (callback_ai==cbai) return;
	zRELEASE			(callback_ai);
	callback_ai			= cbai;
	if (cbai)
		cbai->AddRef	();
};

void zCVob::SetVobPresetName (const zSTRING& presetName)	
{ 
	// Der VobPresetName Mechanismus ist aus Effizienzgruenden nur im Spacer aktiv
	#ifdef COMPILING_SPACER
		if (!vobPresetName)	{
			vobPresetName	= zNEW(zSTRING(presetName));
		} else {
			(*vobPresetName)= presetName;	
		};
	#endif
};

const zSTRING& zCVob::GetVobPresetName () const 
{ 
	if (!vobPresetName)		return zSTR_EMPTY;
	else					return (*vobPresetName);
};

zCRigidBody* zCVob::GetRigidBody () 
{ 
	// RigidBodys werden lazy erzeugt
	if (!rigidBody) rigidBody = zNEW(zCRigidBody);
	return rigidBody; 
};

// ======================================================================================================================
// ======================================================================================================================


// packingType==0 => verbose

#pragma pack (push, 1)
struct zSVobArcRawData
{
	zTBBox3D		bbox3DWS;
	zPOINT3			positionWS;
	zMAT3			trafoRotWS;

	struct zSBitField	// 17 Bit in use
	{
		zUINT8		showVisual			: 1;		
		zUINT8		visualCamAlign		: 2;
		zUINT8		cdStatic			: 1;
		zUINT8		cdDyn				: 1;
		zUINT8		staticVob			: 1;
		zUINT8		dynShadow			: 2;

		zUINT8		hasPresetName		: 1;
		zUINT8		hasVobName			: 1;
		zUINT8		hasVisualName		: 1;

		zUINT8		hasRelevantVisualObject	: 1;
		zUINT8		hasAIObject			: 1;
		zUINT8		hasEventManObject	: 1;		// saveGame only

		zUINT8		physicsEnabled		: 1;		// saveGame only
		zUINT8		visualAniMode		: 2;
		zUINT8		zbias				: 5;	
		zUINT8		bAmbient			: 1;
	} bitfield;
	zREAL			visualAniStrength;
	zREAL			fVobFarClipZ;

};
#pragma pack (pop)

/*
// ==============================================================

- read pack
- read raw
- raw => bits, sets, strings
- read strings

*/

/*
	O		presetName=string:
x			bbox3DWS=rawFloat:-2301.205322266 2957.390625000 -28832.857421875 -1397.107543945 3647.975097656 -27926.003906250 
x			trafoOSToWSRot=raw:1dde693f4acd95be79a990be0000000020d5313fa32638bfc93fd03ef63a283f4675223f
x			trafoOSToWSPos=vec3:-1851.079101563 3157.098388672 -28542.980468750
	O		vobName=string:MIN_LOB_STONE_V2_30
	O		visual=string:MIN_LOB_STONE_V2_30.3DS
x			showVisual=bool:1
x			visualCamAlign=enum:0
x			cdStatic=bool:0
x			cdDyn=bool:1
x			staticVob=bool:1
x			dynShadow=enum:0
	O		[visual zCProgMeshProto 0 156]
	O		[]
	O		[ai % 0 0]
	O		[]

*/
void zCCFASTCALL zCVob::ArchivePacked (zCArchiver &arc) 
{
	zSVobArcRawData rawData;

	// Pack ins Archive als 32bit DWord schreiben
	arc.WriteInt	("pack", 1);

	// cachen
	const zSTRING& visualName = (this->GetVisual()) ? this->GetVisual()->GetVisualName() : zSTR_EMPTY;

	// RawData ausfuellen und schreiben
	{
		// packBitfield ausfuellen
		{
			zERR_CASSERT (zVISUAL_CAMALIGN_COUNT==3);
			zERR_CASSERT (zDYN_SHADOW_TYPE_COUNT==2);

			memset (&rawData.bitfield, sizeof(rawData.bitfield), 0);	// zur Sicherheit loeschen, MUSS!
			//				
			rawData.bitfield.showVisual			= this->GetShowVisual();
			rawData.bitfield.visualCamAlign		= int(this->GetVisualCamAlign());
			rawData.bitfield.cdStatic			= this->GetCollDetStat();
			rawData.bitfield.cdDyn				= this->GetCollDetDyn();
			rawData.bitfield.staticVob			= this->GetStaticVob();
			rawData.bitfield.dynShadow			= int(this->GetCastDynShadow());
													
			rawData.bitfield.hasPresetName		= (this->GetVobPresetName().Length()>0);
			rawData.bitfield.hasVobName			= (this->GetVobName().Length()>0);
			rawData.bitfield.hasVisualName		= (visualName.Length()>0);				

			rawData.bitfield.hasRelevantVisualObject= (this->GetVisual()!=0);			// decal, vs. refCtr..
			rawData.bitfield.hasAIObject		= (this->GetAI()!=0);
			rawData.bitfield.hasEventManObject	= (this->GetEventManager(TRUE)!=0);		// fuer saveGame

			rawData.bitfield.physicsEnabled		= (this->GetPhysicsEnabled());			// fuer saveGame
			rawData.bitfield.visualAniMode		= int(this->GetVisualAniMode());
			rawData.bitfield.zbias				= GetZBias();
			rawData.bitfield.bAmbient			= GetIsAmbient();
		};											

		// restliches ausfuellen: bbox, pos, rot
		{	
			rawData.bbox3DWS					= this->GetBBox3DWorld();
			rawData.positionWS					= this->GetPositionWorld();
			rawData.trafoRotWS.SetRightVector	(this->trafoObjToWorld.GetRightVector	());
			rawData.trafoRotWS.SetUpVector		(this->trafoObjToWorld.GetUpVector		());
			rawData.trafoRotWS.SetAtVector		(this->trafoObjToWorld.GetAtVector		());
			rawData.visualAniStrength			= this->GetVisualAniModeStrength();
			rawData.fVobFarClipZ				= this->GetFarClipZScale();
		};

		// ins Archive schreiben
		arc.WriteRaw							("dataRaw", &rawData, sizeof(rawData));
	};

	// Namen
	if (rawData.bitfield.hasPresetName)			arc.WriteString		("presetName"	, GetVobPresetName());
	if (rawData.bitfield.hasVobName)			arc.WriteString		("vobName"		, GetVobName());
	if (rawData.bitfield.hasVisualName)			arc.WriteString		("visual"		, visualName);

	// Visual
	if (rawData.bitfield.hasRelevantVisualObject)arc.WriteObject	("visual"		, GetVisual	());

	// AI
	if (rawData.bitfield.hasAIObject)			arc.WriteObject		("ai"			, GetAI		());

	// SaveGame
	if (arc.InSaveGame()) 
	{
		if (rawData.bitfield.hasEventManObject)	arc.WriteObject		(GetEM(TRUE));	// TRUE: eventMan nicht erzeugen, wenn's ihn noch nicht geben sollte..
	};
};

void zCCFASTCALL zCVob::ArchiveVerbose (zCArchiver &arc) 
{
	// Internals
	arc.WriteGroupBegin	("Internals");
	arc.WriteInt		("pack"				, 0);			// "pack==0"	=> VERBOSE

	// ATT: vobID wird derzeit nicht genutzt, und deshalb vorerst auch nicht ins Archive aufgenommen!
	//	arc.WriteInt		("vobID"			, GetVobID());
	arc.WriteString		("presetName"		, GetVobPresetName());
	arc.WriteRawFloat	("bbox3DWS"			, &bbox3D	, sizeof(bbox3D));

	//
	zPOINT3		pos;
	zMAT3		mat3;
	pos					=trafoObjToWorld.GetTranslation	();
	mat3.SetRightVector	(trafoObjToWorld.GetRightVector	());
	mat3.SetUpVector	(trafoObjToWorld.GetUpVector	());
	mat3.SetAtVector	(trafoObjToWorld.GetAtVector	());
	arc.WriteRaw		("trafoOSToWSRot"	, &mat3	, sizeof(mat3));
	arc.WriteVec3		("trafoOSToWSPos"	, pos);
	arc.WriteGroupEnd	("Internals");

	// data
	arc.WriteGroupBegin	("Vob");
	arc.WriteString		("vobName"			, GetVobName());
	arc.WriteString		("visual"			, GetVisual() ? GetVisual()->GetVisualName() : zSTR_EMPTY);
	arc.WriteBool		("showVisual"		, GetShowVisual());
		
	arc.WriteEnum		("visualCamAlign"	, "NONE;YAW;FULL", int(GetVisualCamAlign()));
	arc.WriteEnum		("visualAniMode"	, "NONE;WIND;WIND2", int(GetVisualAniMode()));
	arc.WriteFloat		("visualAniModeStrength", GetVisualAniModeStrength());
	arc.WriteFloat		("vobFarClipZScale", this->GetFarClipZScale());

	arc.WriteBool		("cdStatic"			, GetCollDetStat());
	arc.WriteBool		("cdDyn"			, GetCollDetDyn());
	arc.WriteBool		("staticVob"		, GetStaticVob());
	arc.WriteEnum		("dynShadow"		, "DS_NONE;DS_BLOB", GetCastDynShadow());
	arc.WriteInt		("zbias"			, GetZBias());
	arc.WriteBool		("isAmbient"		, GetIsAmbient());

	arc.WriteGroupEnd	("Vob");
 
	//
	arc.WriteObject		("visual"			, GetVisual	());
	arc.WriteObject		("ai"				, GetAI		());

	// SaveGame
	if (arc.InSaveGame()) 
	{
		arc.WriteObject	(GetEM(TRUE));						// TRUE: eventMan nicht erzeugen, wenn's ihn noch nicht geben sollte..
		arc.WriteBool	("physicsEnabled"	,	GetPhysicsEnabled());
	};
};

void zCVob::Archive (zCArchiver &arc) 
{
	zCObject::Archive	(arc);

#ifdef COMPILING_SPACER
	if (zDYNAMIC_CAST<zCParticleFX>(GetVisual()))
	{
		zDYNAMIC_CAST<zCParticleFX>(GetVisual())->SetVisualNeverDies(TRUE);
	};
#endif

	// Kernteil des Archivs schreiben: entweder packed oder verbose
	{
		const zBOOL writePacked	= arc.InSaveGame() || arc.InBinaryMode();
		if (writePacked)	ArchivePacked		(arc);
		else				ArchiveVerbose		(arc);
	};

	// SaveGame
	if (arc.InSaveGame()) 
	{
		arc.WriteByte	("sleepMode"		,	GetSleepingMode());
		// nextOnTimer: ist absolut, muss aber relativ gespeichert werden
		const zREAL nextOnTimerRel = (nextOnTimer>=zREAL_MAX)	? nextOnTimer	: (nextOnTimer - ztimer.GetTotalTimeF());
		arc.WriteFloat	("nextOnTimer"		,	nextOnTimerRel);	
		//
		if (GetPhysicsEnabled()) {
			GetRigidBody()->Archive (arc);
		};
	};
};

// ======================================================================================================================

void zCCFASTCALL zCVob::UnarchivePacked (zCArchiver &arc, int pack)
{
	zERR_ASSERT (pack==1);

	// RawData aus Archive lesen
	zSVobArcRawData rawData;
	arc.ReadRaw		("dataRaw",	&rawData, sizeof(rawData));

	// bbox, pos, rot
	{
		this->bbox3D							= rawData.bbox3DWS; 
		this->trafoObjToWorld.SetTranslation	(rawData.positionWS);
		this->trafoObjToWorld.SetRightVector	(rawData.trafoRotWS.GetRightVector	());
		this->trafoObjToWorld.SetUpVector		(rawData.trafoRotWS.GetUpVector		());
		this->trafoObjToWorld.SetAtVector		(rawData.trafoRotWS.GetAtVector		());

		if (this->GetHomeWorld()==0 && trafo)
		{
			// nur beim Laden aus einem File/ nur wenn noch nicht in Welt eingefuegt
			*trafo = trafoObjToWorld;
		};
	};

	// Namen
	{
		if (rawData.bitfield.hasPresetName)
		{
			SetVobPresetName			(arc.ReadString		("presetName"));
		};
		if (rawData.bitfield.hasVobName)
		{
			SetVobName					(arc.ReadString		("vobName"));
		};
		if (rawData.bitfield.hasVisualName)
		{
			const zSTRING& visName		=arc.ReadString		("visual");
			if (visName.Length()>0)
			{
				// Material-Flags abhängig vom Vob-Typ setzen
				int oldUsage = zCMaterial::GetUsageDefault ();
				if (GetVobType()==zVOB_TYPE_LEVEL_COMPONENT) {
					zCMaterial::SetUsageDefault	(zCMaterial::zMAT_USAGE_LEVEL);
				};
				SetVisual(visName);

				zCMaterial::SetUsageDefault	(oldUsage);
				// FIX: damit alte Daten korrekt eingelesen werden, bei denen die BBoxWS defekt ist...
				if (GetVisual() && (zDYNAMIC_CAST<zCParticleFX>(GetVisual())))
				{
					bbox3D.mins = bbox3D.maxs = trafoObjToWorld.GetTranslation();
				};
			};
		};
	};

	// Flags: packBitfield auswerten
	{
		this->SetShowVisual			(rawData.bitfield.showVisual);
		this->SetVisualCamAlign		(zTVisualCamAlign(rawData.bitfield.visualCamAlign));
		this->SetVisualAniMode		(zTAnimationMode (rawData.bitfield.visualAniMode));
		this->SetFarClipZScale		(rawData.fVobFarClipZ);
		this->SetVisualAniModeStrength(rawData.visualAniStrength);
		this->SetCollDetStat		(rawData.bitfield.cdStatic);
		this->SetCollDetDyn			(rawData.bitfield.cdDyn);
		this->SetStaticVob			(rawData.bitfield.staticVob);
		this->SetCastDynShadow		(zTDynShadowType(rawData.bitfield.dynShadow));
		this->SetZBias				(rawData.bitfield.zbias);
		this->SetIsAmbient			(rawData.bitfield.bAmbient);
	};

	// Visual lesen?
	if (rawData.bitfield.hasRelevantVisualObject)
	{
//		int			oldVisRefCtr	= GetVisual() ? GetVisual()->GetRefCtr() : -1; 
		zCVisual	*newVis			= static_cast<zCVisual*>(arc.ReadObject	("visual", visual));

		// AI und Visual werden gesetzt und danach released. SetXXX() speichert eine Referenz, das
		// Release ist noetig, da dieser Kontext die Referenz auf die Objekte nicht mehr benoetigt.
		if (!visual)		
		{ 
			// es gab vorher kein Visual
			SetVisual	(newVis);	
			zRELEASE	(newVis);	
		} else
		{
			// es gab bereits ein Visual, das mit 'objectUseThis' gefuellt werden sollte
			// hir gibt es nichts weiter zu tun!
		};


		// ALT: Wenn ein Visual vorhanden ist und dessen RefCtr vor dem arc.ReadObject ungleich dem RefCtr danach ist,
		// so lag in dem Archive das Visual als Referenz vor. In diesem Fall ist allerdings der Visual RefCtr doppelt
		// hochgezaehlt waren, also ein mal zuviel (1x in SetVisual, beim sharen, 1x beim zCArchive::ReadObject().
	};

	// AI lesen?
	if (rawData.bitfield.hasAIObject)
	{
		// AI und Visual werden gesetzt und danach released. SetXXX() speichert eine Referenz, das
		// Release ist noetig, da dieser Kontext die Referenz auf die Objekte nicht mehr benoetigt.
		zCAIBase	*newAI	= static_cast<zCAIBase*>(arc.ReadObject	("ai", callback_ai));
		if (!callback_ai)	{ SetAI		(newAI);	zRELEASE(newAI);	};
	};

	if (GetVisual() && (zDYNAMIC_CAST<zCParticleFX>(GetVisual())))
	{
		zDYNAMIC_CAST<zCParticleFX>(GetVisual())->SetVisualNeverDies(TRUE);
	};


	// SaveGame
	if (arc.InSaveGame()) 
	{
		if (rawData.bitfield.hasEventManObject)
		{
			// Eventmanager unarchiven
			// ACHTUNG: Ein EM wird ueber factory passend zu diesem hostVob erzeugt, dann soll der Archiver diesen fuellen.
			//          Falls aber im Archive ein NullPtr steht wird der EM wieder geloescht.
			if (eventManager)
			{
				// reuse
				eventManager	= static_cast<zCEventManager*> (arc.ReadObject (eventManager));	// TRUE: eventMan nicht erzeugen, wenn's ihn noch nicht geben sollte..
			} else
			{
				// create, fill
				zCEventManager *em	= zfactory->CreateEventManager (this);
				eventManager		= static_cast<zCEventManager*> (arc.ReadObject (em));	// hier wird davon ausgegangen, dass sich im Archive an dieser Stelle KEINE Referenz auf einen EM befindet!
				if (!eventManager)	em->Release();
			};
		};
		this->SetPhysicsEnabled		(rawData.bitfield.physicsEnabled);
	};
};

void zCCFASTCALL zCVob::UnarchiveVerbose (zCArchiver &arc) 
{
	// Internals
	// ATT: vobID wird derzeit nicht genutzt, und deshalb vorerst auch nicht ins Archive aufgenommen!
	//	zTVobID id = arc.ReadInt ("vobID");
	//	if (arc.InSaveGame()) vobID = id;
	SetVobPresetName				(arc.ReadString		("presetName"));
									 arc.ReadRawFloat	("bbox3DWS"		, &bbox3D, sizeof(bbox3D));

	// Trafo lesen (rot/pos im WS)
	zPOINT3		pos;
	zMAT3		mat3;
	arc.ReadRaw						("trafoOSToWSRot", &mat3, sizeof(mat3));
	arc.ReadVec3					("trafoOSToWSPos", pos);
	trafoObjToWorld.SetTranslation	(pos);
	trafoObjToWorld.SetRightVector	(mat3.GetRightVector	());
	trafoObjToWorld.SetUpVector		(mat3.GetUpVector		());
	trafoObjToWorld.SetAtVector		(mat3.GetAtVector		());

	//if (!arc.InProperties())
	if (this->GetHomeWorld()==0 && trafo)
	{
		// nur beim Laden aus einem File/ nur wenn noch nicht in Welt eingefuegt
		*trafo = trafoObjToWorld;
	};

	// data
	SetVobName					(arc.ReadString		("vobName"));
	const zSTRING& visName		=arc.ReadString		("visual");
	if (visName.Length()>0)
	{
		// Material-Flags abhängig vom Vob-Typ setzen
		int oldUsage = zCMaterial::GetUsageDefault ();
		if (GetVobType()==zVOB_TYPE_LEVEL_COMPONENT) {
			zCMaterial::SetUsageDefault	(zCMaterial::zMAT_USAGE_LEVEL);
		};
		SetVisual(visName);

		zCMaterial::SetUsageDefault	(oldUsage);

		// FIX: damit alte Daten korrekt eingelesen werden, bei denen die BBoxWS defekt ist...
		if (GetVisual() && (zDYNAMIC_CAST<zCParticleFX>(GetVisual())))
		{
			bbox3D.mins = bbox3D.maxs = trafoObjToWorld.GetTranslation();
		};
	};

	SetShowVisual				(arc.ReadBool		("showVisual"));
	SetVisualCamAlign			(zTVisualCamAlign	(arc.ReadEnum ("visualCamAlign")));

	SetVisualAniMode			(zTAnimationMode(arc.ReadEnum ("visualAniMode")));
	SetVisualAniModeStrength	(arc.ReadFloat		("visualAniModeStrength"));
	SetFarClipZScale			(arc.ReadFloat		("vobFarClipZScale"));

	SetCollDetStat				(arc.ReadBool		("cdStatic"));
	SetCollDetDyn				(arc.ReadBool		("cdDyn"));
	SetStaticVob				(arc.ReadBool		("staticVob"));
	SetCastDynShadow			(zTDynShadowType	(arc.ReadEnum		("dynShadow")));
	int _zbias = DEFAULT_VOB_ZBIAS;
	arc.ReadInt("zbias", _zbias);
	SetZBias					(_zbias);

	int _bIsAmbientVob = bIsAmbientVob;
	arc.ReadBool("isAmbient", _bIsAmbientVob);
	SetIsAmbient(_bIsAmbientVob);


	// Visual und AI lesen
	{
//		int			oldVisRefCtr	= GetVisual() ? GetVisual()->GetRefCtr() : -1; 
		zCVisual	*newVis;
		zCAIBase	*newAI;
		newVis		= static_cast<zCVisual*>(arc.ReadObject	("visual", visual));
		newAI		= static_cast<zCAIBase*>(arc.ReadObject	("ai", callback_ai));
		// AI und Visual werden gesetzt und danach release. SetXXX() speichert eine Referenz, das
		// Release ist noetig, da dieser Kontext die Referenz auf die Objekte nicht mehr benoetigt.
		if (!visual)		{ SetVisual	(newVis);	zRELEASE(newVis);	};
		if (!callback_ai)	{ SetAI		(newAI);	zRELEASE(newAI);	};
		// Wenn ein Visual vorhanden ist und dessen RefCtr vor dem arc.ReadObject ungleich dem RefCtr danach ist,
		// so lag in dem Archive das Visual als Referenz vor. In diesem Fall ist allerdings der Visual RefCtr doppelt
		// hochgezaehlt waren, also ein mal zuviel (1x in SetVisual, beim sharen, 1x beim zCArchive::ReadObject().
	};

	if (GetVisual() && (zDYNAMIC_CAST<zCParticleFX>(GetVisual())))
	{
		zDYNAMIC_CAST<zCParticleFX>(GetVisual())->SetVisualNeverDies(TRUE);
	};


	// SaveGame
	if (arc.InSaveGame()) 
	{
		// Eventmanager unarchiven
		{
			// ACHTUNG: Ein EM wird ueber factory passend zu diesem hostVob erzeugt, dann soll der Archiver diesen fuellen.
			//          Falls aber im Archive ein NullPtr steht wird der EM wieder geloescht.
			zCEventManager *em	= zfactory->CreateEventManager (this);
			eventManager		= static_cast<zCEventManager*> (arc.ReadObject (em));	// TRUE: eventMan nicht erzeugen, wenn's ihn noch nicht geben sollte..
			if (!eventManager)	em->Release();
		};
		SetPhysicsEnabled	(arc.ReadBool	("physicsEnabled"));
	};

};

void zCVob::Unarchive (zCArchiver &arc) 
{
	zCObject::Unarchive			(arc);

	// einen sauberen Zustand herstellen
	ResetOnTimer				();

	// Packing DWord Trailer lesen und auswerten
	{
		int	pack				= 0;	// 0 WICHTIG!
		arc.ReadInt				("pack"	, pack);
		if (pack==0)			this->UnarchiveVerbose	(arc);
		else					this->UnarchivePacked	(arc, pack);
	};

	// SaveGame
	if (arc.InSaveGame()) 
	{
		SetSleepingMode		(zTVobSleepingMode(arc.ReadByte	("sleepMode")));
		// nextOnTimer: ist absolut, muss aber relativ gespeichert werden
		zREAL nextOnTimerRel=nextOnTimer;
		arc.ReadFloat		("nextOnTimer"		,	nextOnTimerRel);	
		nextOnTimer			= (nextOnTimerRel>=zREAL_MAX) ? nextOnTimerRel : (ztimer.GetTotalTimeF() + nextOnTimerRel);
		if (GetPhysicsEnabled()) {
			GetRigidBody()->Unarchive (arc);
		};
	};

	// Konsistenz Korrekturen auf der trafo, falls dieser Vob in den Spacer geladen wird
	#ifdef COMPILING_SPACER
		if (!arc.InProperties())
		{
			RepairIllegalFloats (this->trafoObjToWorld);
			if (!this->trafoObjToWorld.IsUpper3x3Orthonormal())
				this->trafoObjToWorld.MakeOrthonormal();
			CorrectTrafo		();
		};
	#endif

	//
	UpdateVisualDependencies		();				// FIXME: schoen ist das nicht..

#ifdef COMPILING_SPACER
	// hier wird nun automatisch der ZBias Wert auf 0 gesetzt, falls das minExtend der BBox nicht kleiner als XXX ist
	// (zbiasing darf man anscheinend naturgemäss nur auf vobs einsetzen, die relativ flach sind, sonst gibt es innerhalb
	// der vobs sortierungsprobleme)
	const zREAL VOB_IGNORE_MIN_EXTEND = 10;
	zREAL minExtend = GetBBox3DWorld().GetMinExtent();
	if (minExtend>VOB_IGNORE_MIN_EXTEND) SetZBias(0);
#endif


#ifdef TEST_MORPH
		if (GetVisualAniMode()==zVISUAL_ANIMODE_NONE)
		{
			if (this->GetVisual() && this->GetVisual()->GetAlphaTestingEnabled())
			{
				SetVisualAniMode		(zVISUAL_ANIMODE_WIND);
				SetVisualAniModeStrength(1);
			}
		}
#endif


};


// ======================================================================================================================
// ======================================================================================================================

void zCVob::SetVobName (const zSTRING& n) 
{
	if (GetHomeWorld()) {
		GetHomeWorld()->RemoveVobHashTable(this);
	};
	SetObjectName (n);
	if (GetHomeWorld()) {
		GetHomeWorld()->InsertVobHashTable(this);
	};
};

zCEventManager* zCCFASTCALL zCVob::GetEM (const zBOOL dontCreate) 
{ 
 	if ((eventManager) || (dontCreate))	return eventManager;
	eventManager = zfactory->CreateEventManager(this);
	return eventManager;	
};

zBOOL zCVob::TraceRay		(	const zVEC3&		rayOrigin, 
								const zVEC3&		ray, 
								const int			traceFlags, 
								zTTraceRayReport	&report)
{
	// Input-Ray		: worldSpace
	// Output-Location	: worldSpace

	report.Clear();

	// Falls Helper-Visuals aktiviert sind und das Vob kein Visual besitzt, wird das HelperVis fuer den Test benutzt.
	zCVisual *testVisual = GetVisual();
	if ((!testVisual) && (traceFlags & zTRACERAY_VOB_TEST_HELPER_VISUALS))	testVisual	= this->GetClassHelperVisual();
	if (!testVisual)	return FALSE;

	// BBox-Test (worldSpace)
	{
		zBOOL hit;
		if (testVisual!=GetVisual())
		{
			// Helper-Visual
			zTBBox3D helpVisBoxWS;
			testVisual->GetBBox3D().Transform		(trafoObjToWorld, helpVisBoxWS);
			hit =	(helpVisBoxWS.TraceRay			(rayOrigin, ray, report.foundIntersection)) ||
					(helpVisBoxWS.IsTrivInLine		(rayOrigin, rayOrigin + ray));
		} else 
		{
			// regulaeres Visual
			hit =	(GetBBox3DWorld().TraceRay		(rayOrigin, ray, report.foundIntersection)) ||
					(GetBBox3DWorld().IsTrivInLine	(rayOrigin, rayOrigin + ray));
		};
		if (!hit) return FALSE;
	};
	
	// Vobs nur bis zur BBox testen ?
	// (falls per Flag so gewuenscht, oder das drunterliegende Visual keinen TraceRay Test beherrscht)
	if (((traceFlags & zTRACERAY_VOB_BBOX)!=0) || (!testVisual->CanTraceRay()))
	{
		report.foundVob			= this;
		report.foundPoly		= 0;
		return TRUE;
	};

	// FIXME: world-vob-visual
	//        in jeder Stufe wird bisher das Ergebnis der Berechnung an Ort und Stelle eine Ebene hoeher transformiert
	//        => evtl. die trafo hochreichen & oben transformieren.. ?

	// Ray in das Koordinatensystem des Vobs transformieren
	// (Normale/Ebenengleichung transformieren:	N'   = (M^-1)^T * N)
	const zVEC3&	xrayOrigin	= trafoObjToWorld.InverseLinTrafo() * rayOrigin;	// *)
//	const zVEC3&	xrayOrigin	= rayOrigin * trafoObjToWorld;						// !!geht nicht!! ATT: ist eine Optmimierung von *), die nur gilt, wenn die trafo ORTHONORMAL ist!
	const zVEC3&	xray		= ray		* trafoObjToWorld;
	const zBOOL		hit			= testVisual->TraceRay (xrayOrigin, xray, traceFlags, report);

	if (hit) 
	{
		// hier ggfs. hits nach worldSpace transformieren
		report.foundVob				= this;
		report.foundIntersection	= trafoObjToWorld * report.foundIntersection;		// intersection im worldSpace berechnen

		if (traceFlags & zTRACERAY_POLY_NORMAL) {
			report.foundPolyNormal	= trafoObjToWorld.Rotate (report.foundPolyNormal);	// normal im worldSpace
		};
	};

	return hit;
};

zCOLOR zCVob::CalcLightSampleAtOrigin () 
{
	zCOLOR res;
	if (GetHomeWorld()) 
	{
		res	= GetLightColorStat	();
		res.AddRGBApprox		(GetLightColorDyn());
	} else 
		res.SetRGBA				(0,0,0,255);

	return res;
};

zCOLOR zCVob::GetLightColorStat () 
{
	zERR_ASSERT (GetHomeWorld());
	// statisches Licht 
	if (lightColorStatDirty)
	{
		lightColorStatDirty		= FALSE;
		zVEC3	newColorSample;
		this->CalcStaticLight	(newColorSample);

		// erste Abfrage?
		if (lightColorStat.alpha!=0)
		{
			// color smoothing lerp
			const	zVEC3 oldColorSample	= lightColorStat.GetVEC3();
			const	zREAL distTotal			= (newColorSample - oldColorSample).LengthApprox();
			if (distTotal>0)
			{
				const	zREAL distCanLerp	= zREAL(0.2F) * ztimer.GetFrameTimeF();	// lerpVelocity
						zREAL t				= distCanLerp / distTotal;
				zClamp01					(t);
				newColorSample				= zLerp (t, oldColorSample, newColorSample);
			};
		};
		lightColorStat.SetRGB	(newColorSample);
		lightColorStat.alpha	= 255;
	};

	// Tageszeitbeleuchtung einrechnen (kann nicht gecacht werden)
	if ((groundPoly) && (groundPoly->GetLightmap())) 
	{
		// im Sektor (z.B. Haus)
		// ..
		return lightColorStat;
	} else 
	{
//		const int intensity		= lightColorStat.GetIntensityByte();
//		const zCOLOR colDayLight= GetHomeWorld()->GetActiveSkyControler()->GetDaylightColorFromIntensity (intensity);
//		return colDayLight;
		return GetHomeWorld()->GetActiveSkyControler()->GetDaylightColorFromIntensity (lightColorStat.GetIntensityByte());
	};
};


zCOLOR zCVob::GetLightColorStatGroundPoly() 
{
	if (lightColorStatDirty) GetLightColorStat();
	return lightColorStat;
}


zCOLOR zCVob::GetLightColorDyn() 
{
	// dynamisches Licht
	if (lightColorDynDirty)
	{
		lightColorDynDirty = FALSE;

		// Aus allen Leafs in denen der Vob Fragmente hat werden alle Lights geholt
		zCArray<zCVobLight*> vobLightList(vobLeafList.GetNumInList()); 
		for (int i=0; i<vobLeafList.GetNumInList(); i++) 
		{ 
			zCBspLeaf *leaf = vobLeafList[i];
			for (int j=leaf->lightVobList.GetNum()-1; j>=0; j--) 
			{
				// nur dyn lights einsammeln
				zCVobLight *light = leaf->lightVobList[j];
				if (light->GetIsStatic()) break;			// Lights sind sortiert: stat,dyn
				if (!vobLightList.IsInList(light)) 
					vobLightList.Insert (light);
			};
		};
		lightColorDyn	= zCVobLight::SumLightsAtPositionWS (vobLightList, GetPositionWorld());
	};
	return lightColorDyn;
};

zBOOL zCCFASTCALL zCVob::CalcStaticLight (zVEC3& color) const
{
	// berechnet den statischen Beleuchtungswert
	// a) falls vob statisch: SLOW
	//    beruehrte Stat-Lights an Objekt Center summieren & Visible-Rays casten
	// b) sonst:
	//	  Boden/Lightmap Sample ermitteln

	// beruecksichtigt nicht dynamischen Tag/Nacht Einfluss auf Beleuchtung

	//
	zERR_ASSERT (GetHomeWorld());

	zCPolygon	*groundPoly = GetGroundPoly();
	const zBOOL outdoor		= (GetHomeWorld()->GetBspTree()->GetBspTreeMode()==zBSP_MODE_OUTDOOR);
	const zBOOL hardLighting= ((GetStaticVob() || zDYNAMIC_CAST<zCMover>(this)) &&
							  ((!outdoor) || ((groundPoly) && (groundPoly->GetLightmap()))));

	if (hardLighting)
	{
		// Fall a)
		// Aus allen Leafs in denen der Vob Fragmente hat werden alle Lights geholt
		zCArray<zCVobLight*> vobLightList(vobLeafList.GetNumInList()); 
		for (int i=0; i<vobLeafList.GetNumInList(); i++) 
		{ 
			zCBspLeaf *leaf = vobLeafList[i];
			for (int j=0; j<leaf->lightVobList.GetNum(); j++) 
			{
				// nur stat lights einsammeln
				zCVobLight *light = leaf->lightVobList[j];
				if (!light->GetIsStatic()) break;				// Lights sind sortiert: stat, dyn
				if (!vobLightList.IsInList(light)) 
					vobLightList.Insert (light);
			};
		};
		const zPOINT3& samplePos = GetBBox3DWorld().GetCenter();
		color = zCVobLight::SumLightsAtPositionWS (vobLightList, samplePos, TRUE).GetVEC3();	// TRUE= occlusion testen
		//color *= 0.71F;		// Licht auf Vobs etwas daempfen, wirkt sonst gegenueber dem stat. Level zu hell
	} else
	{
		// Das GroundPoly ist hier dringend noetig. Nicht vorhanden? => early out 
		if (!groundPoly) { 
			color = zVEC3(160);		// irgendetwas 'neutrales'
			return FALSE;
		};

		// Die Beleuchtungsfarbe (und -intensitaet) wird aus dem Boden-Polygon genommen
		zVEC3		inters;
		zREAL		alpha;
		const zPOINT3&	rayStartPos = GetBBox3DWorld().GetCenter();
		zBOOL			res			= groundPoly->CheckRayPolyIntersection		(rayStartPos, zVEC3(0,-3000,0), inters, alpha);
		// Falls ab BBox-Center nichts gefunden wird, nochmal ab BBox-Center-Top probieren..
		if (!res) {
						res			= groundPoly->CheckRayPolyIntersection		(zVEC3(rayStartPos[VX],GetBBox3DWorld().maxs[VY],rayStartPos[VZ]), zVEC3(0,-3000,0), inters, alpha);
		};
		color						= groundPoly->GetLightStatAtPos				(inters);

		// Falls die Intensitaet des Bodypolys an diesem Ort zu gering ist, koennte es sein, dass ein statisches Objekt
		// direkt dadrueber steht, welches den Boden verdunkelt. In diesem Fall wird das Licht fuer den gerade zu beleuchtenden
		// Vob aus dem Vob direkt unter ihm genommen.
		zREAL colorIntensity	= ((0.299F)*color[0] + (0.587F)*color[1] + (0.114F)*color[2]);
		if (colorIntensity<30)	// ca. 11% Helligkeit
		{
			if (GetHomeWorld()->TraceRayNearestHit (rayStartPos, zVEC3(0,-3000,0), (zCVob*)this, zTRACERAY_STAT_IGNORE))	// zTRACERAY_VOB_BBOX reicht leider nicht
			{
//				zERR_ASSERT (GetHomeWorld()->traceRayReport.foundVob);
				if (GetHomeWorld()->traceRayReport.foundVob)
					color = GetHomeWorld()->traceRayReport.foundVob->GetLightColorStat().GetVEC3();
			};
		};

		// Die aus dem Poly ermittelte Beleuchtung anheben (ist sonst zu dunkel)
		// (=> ambiente Beleuchtung des Objektes, Poly-Beleuchtung unterschaetzt Beleuchtung des Objektes dadrueber wesentlich)
		// nur im Outdoor... 
		if (outdoor)
		{
			if (!groundPoly->GetSectorFlag())
			{
				color[0] = color[0] * 0.5F + 127.0F;	// +50% Helligkeit, in der Oberwelt
				color[1] = color[1] * 0.5F + 127.0F;	// +50% Helligkeit, in der Oberwelt
				color[2] = color[2] * 0.5F + 127.0F;	// +50% Helligkeit, in der Oberwelt
			} else 
			{
				color[0] = color[0] * 0.8F + 50.0F;		// +20% Helligkeit, in Sektoren (Wald..)
				color[1] = color[1] * 0.8F + 50.0F;		// +20% Helligkeit, in Sektoren (Wald..)
				color[2] = color[2] * 0.8F + 50.0F;		// +20% Helligkeit, in Sektoren (Wald..)
			};
		};
	};

	return TRUE;
};

const zSTRING* zCVob::GetSectorNameVobIsIn() const
{
	return GetHomeWorld()->GetBspTree()->GetSectorNameVobIsIn(this);
};


// ===================================================================================================================

void zCVob::LoadGroundShadowMesh () 
{
	// FIXME: per Hand erzeugen !

	s_shadowMesh	= zCMesh::Load ("_intern\\groundShadow.3ds");
	if (!s_shadowMesh) return;
	s_shadowMesh->Poly(0)->GetMaterial()->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_MUL);
	s_shadowMesh->SetStaticLight			(zCOLOR(255,255,255,255));
	s_shadowMesh->ResetLightDynToLightStat	();
};

void zCVob::DeleteGroundShadowMesh () {
	zRELEASE (s_shadowMesh);
};

enum { zVOB_GROUND_SHADOW_SIZE_SCALER = 8 };

void zCCFASTCALL zCVob::SetGroundShadowSize (const zVEC2& sizeXY)
{
	groundShadowSizePacked = (zFloat2Int(sizeXY[VX]*zVOB_GROUND_SHADOW_SIZE_SCALER)) | 
							 (zFloat2Int(sizeXY[VY]*zVOB_GROUND_SHADOW_SIZE_SCALER)<< 16);
};

zVEC2 zCCFASTCALL zCVob::GetGroundShadowSize () const
{
	return zVEC2 (zREAL(groundShadowSizePacked & (65535)) / zREAL(zVOB_GROUND_SHADOW_SIZE_SCALER),
				  zREAL(groundShadowSizePacked >> 16)     / zREAL(zVOB_GROUND_SHADOW_SIZE_SCALER));
};

void zCCFASTCALL zCVob::RenderGroundShadow (zTRenderContext& renderContext) 
{
	// FIXME: 
	// - optimieren (divs, cam->activate(), matrix, etc.)
	// - alle Schatten cachen & dann nach allen anderen vobs rendern (fog, 1 texture, etc.)

	if (!s_shadowMesh)
		return;
	// [BENDLIN] Addon - unter 70% Transparenz keine Schatten
	if (this->GetVisualAlphaEnabled() && (this->GetVisualAlpha() <= 0.7f))
		return;

	if (GetGroundPoly())
	{ 
		zCPolygon *floorPoly	= GetGroundPoly();

		// Boden-Hoehe finden
		// FIXME: diesen Wert irgendwie cachen/sharen.. (mit anderen Proggi-Parts)
		// zPOINT3 inters		= GetHomeWorld()->traceRayReport.foundIntersection; 
		// ax + by + cz - d		= 0;  by = (-ax - cz + d) / y
		zPOINT3	inters			= bbox3D.GetCenter();
		const zTPlane& plane	= floorPoly->polyPlane; 
		inters[VY]				= (-plane.normal[VX]*inters[VX] -plane.normal[VZ]*inters[VZ] + plane.distance) / plane.normal[VY];
		inters[VY]				+= 2.0F;						// zbuffer

		// Shadow-Mesh scalen
		zVALUE distFeetGround	= zAbsApprox (bbox3D.mins[VY] - inters[VY]);
		zREAL  maxYDist			= 1*(bbox3D.maxs[VY] - bbox3D.mins[VY]);
		if (distFeetGround>maxYDist) return;
		zVALUE heightFac		= 1- (distFeetGround / maxYDist);
			   heightFac		= zMin (0.9F, heightFac);

		// zVALUE modelXDim		= zMin (200.0F, zMax (10.0F, (bbox3D.maxs[VX] - bbox3D.mins[VX])*heightFac));
		// zVALUE modelZDim		= zMin (200.0F, zMax (10.0F, (bbox3D.maxs[VZ] - bbox3D.mins[VZ])*heightFac));

		zVEC2 newShadowSize		= zVEC2 (zMin (200.0F, zMax (10.0F, (bbox3D.maxs[VX] - bbox3D.mins[VX])*heightFac)),
										 zMin (200.0F, zMax (10.0F, (bbox3D.maxs[VZ] - bbox3D.mins[VZ])*heightFac)) );
		zREAL lerpFrac			= ztimer.GetFrameTimeF() * zREAL(0.001F);	//0.001
		zClamp01				(lerpFrac);	// 0.4F
		zVEC2 currentShadowSize	= (this->groundShadowSizePacked==0) ? newShadowSize : 
																	  zLerp (lerpFrac, GetGroundShadowSize(), newShadowSize);
		SetGroundShadowSize		(currentShadowSize);

		const zTBBox3D& shdBBox = s_shadowMesh->GetBBox3D(); 
		zVALUE shdXDim			= zAbsApprox (shdBBox.maxs[VX] - shdBBox.mins[VX]);
		zVALUE shdZDim			= zAbsApprox (shdBBox.maxs[VZ] - shdBBox.mins[VZ]);

		zVALUE xfac				= currentShadowSize[0] / shdXDim;
		zVALUE zfac				= currentShadowSize[1] / shdZDim;

		s_shadowMesh->ScaleXZ	(xfac, zfac); 

		// trafoWorld berechnen
		{
			zVEC3 at					= zVEC3	(0,0,1);
			zVEC3 up					= floorPoly->GetNormal();
	//		at							= (at + (-(at * up) * up)).NormalizeApprox();
			at							= (at + ((-up[VZ]) * up)).NormalizeApprox();
			zVEC3 right					= (up ^ at);

			zMATRIX4 trafoWorld;
			trafoWorld.MakeIdentity		();		// FIXME: ugly
			trafoWorld.SetAtVector		(at);
			trafoWorld.SetUpVector		(up);
			trafoWorld.SetRightVector	(right);
			trafoWorld.Translate		(inters);

			zCCamera::activeCam->SetTransform (zCAM_TRAFO_WORLD, trafoWorld);
		};

		// Shadow rendern
		renderContext.clipFlags		= -1;
		zrenderer->SetZBias(DEFAULT_LEVEL_ZBIAS);
		s_shadowMesh->Render		(renderContext);
	};
};

zCVisual* zCVob::GetClassHelperVisual () const
{
	zCVisual *helperVisual = 0;

	const zTHelperVisualMapIter pos = s_helperVisualMap.find (this->GetClassDef());
	if (pos!=s_helperVisualMap.end())
	{
		// gefunden, aus der map kramen
		helperVisual				= s_helperVisualMap[(*pos).first];
	} else 
	{
		// nicht gefunden, laden und in die map eintragen
		helperVisual				= zCVisual::LoadVisual (zSTRING("INVISIBLE_")+this->GetClassName_()+".3DS");
		if (!helperVisual)
			helperVisual			= zCVisual::LoadVisual (zSTRING("INVISIBLE_DEFAULT.3DS"));
		s_helperVisualMap.insert	(zTHelperVisualMapVal(this->GetClassDef(), helperVisual));
	};
	return helperVisual;
};

// ======================================================================

void zCVob::CalcRenderAlpha (const zREAL distVobToCam, zCVisual* &activeVisual, zREAL& alpha) 
{
	//zERR_ASSERT (GetHomeWorld());
	zERR_ASSERT (GetVisual());

	if (!GetHomeWorld())
	{
		alpha = 0; 
		return;
	};
	
	if (this->bIsInWater) 
	{
		alpha = 1;
		return;
	}
	
	// "Hack" damit sich das Vob-Fading dyn. an der globalen 'VobFarPlane' anpasst
	// FIXME: wie mans auch machen kann: Festlegung einer Referenz, die einem bestimmten 
	// Volumen eine absolute Range zuordnet. (klar, fuer jedes Vol existiert eine Distanz, ab
	// der das Rendern des Objektes kein Sinn mehr macht, da zu klein). Anhand des RefWertes von
	// anderen Vols auf Ranges umrechnen. Problematisch ist es nur, falls eine Erg-Range höher als
	// die VobFarPlaneZ ist. Dann: entweder clampen oder in der verfuegbaren Range 'sinnvoll' verteilen..

	// Hier werden zu einem Alpha verrechnet:
	// World::vobFarClipZ, Vob::GetBBox3DLocalVolume, user/visual::lodFar/NearDistance, zCVob::GetVisualAlpha()
	{
		const zREAL FADE_MAX				= zREAL(1000.0F);
		const zREAL FADE_VOL_MAX			= FADE_MAX*FADE_MAX*FADE_MAX;
		const zREAL FADE_MIN				= zREAL(  50.0F);
		const zREAL FADE_VOL_MIN			= FADE_MIN*FADE_MIN*FADE_MIN;
		const zREAL FADE_VOL_RANGE_INV		= zREAL(1.0F) / (FADE_VOL_MAX-FADE_VOL_MIN);

		zREAL scale;
		zREAL vol							= GetBBox3DLocal().GetVolume();
		if (vol>=FADE_VOL_MAX)	scale		= 1.0F; else
		if (vol<=FADE_VOL_MIN)	scale		= 0.0F; else
								scale		= (vol-FADE_VOL_MIN) * FADE_VOL_RANGE_INV;
		// zClamp (scale, 0.5F, 1.0F);
		// FIXME: ist sicher noch tunebar! bei hohen FarClipZ's werden kleine Vobs z.B. noch viel zu lange gerendert...
		scale								= scale * 0.5F + 0.5F;
		// GetVisual()->lodFarDistance			= GetHomeWorld()->GetVobFarClipZ()*scale;
		// GetVisual()->lodNearFadeOutDistance	= GetVisual()->lodFarDistance*0.9F;

		zERR_ASSERT(zCCamera::activeCam);
		const zREAL localLODFarDistance			= GetFarClipZScale()!=1 ? zMin(GetHomeWorld()->GetVobFarClipZ()*scale*GetFarClipZScale(), zCCamera::activeCam->GetFarClipZ()*scale) : zMin (GetVisual()->lodFarDistance		, zMin(GetHomeWorld()->GetVobFarClipZ()*scale, zCCamera::activeCam->GetFarClipZ()*scale) );
		const zREAL localLODNearFadeOutDistance	= GetFarClipZScale()!=1 ? localLODFarDistance*0.9F : zMin (GetVisual()->lodNearFadeOutDistance	, localLODFarDistance*0.9F);

		
//		const zREAL localLODFarDistance			= GetHomeWorld()->GetVobFarClipZ()*scale*GetFarClipZScale();
//		const zREAL localLODNearFadeOutDistance = localLODFarDistance*0.5F ;

		// ATT: die LOD-Visual Ketten sind erstmal disabled (werden eh von niemandem nicht benutzt)
		activeVisual						= GetVisual();
		alpha								= 0;
		if (distVobToCam<=localLODFarDistance) 
		{
			alpha = 1.0F;
			if (distVobToCam>localLODNearFadeOutDistance) 
			{
				alpha = ((localLODFarDistance - distVobToCam) / (localLODFarDistance - localLODNearFadeOutDistance));
			};
		};
	}

	// GetVisual()->GetLODVisualAndAlpha (distVobToCam, activeVisual, alpha);
	if (GetVisualAlphaEnabled()) 
	{
		alpha = zMin (alpha, GetVisualAlpha());
	};

	//if (alpha<1) zERR_WARNING("ALPHA:" + zSTRING(alpha));
};

zBOOL zCCFASTCALL zCVob::Render (zTRenderContext &renderContext) 
{
	// Assert: es gibt eine activeCam, dort sind die Matrizen & das Frustum korrekt gesetzt.

	// FIXME: Den ganzen Kram in die Visuals verlegen !!!
	//        Auch den Setup-Code (zCCamera::activeCam->camMatrix ....) !!!!
	// FIXME: sollen Lights visuelle Auswirkungen haben, bei ShowVisual..
#ifdef COMPILING_SPACER
	zBOOL dontDisplayLightSphere = FALSE;
	zCVobLight *vobLight = zDYNAMIC_CAST<zCVobLight>(this);
	if ( vobLight && vobLight->GetShowLightSphere() )
	{
		if (!zCVobLight::s_pLightSphereMesh)
		{
			zCVobLight::s_pLightSphereMesh = zCMesh::Load("SPHERE.3DS", TRUE);
			if (!zCVobLight::s_pLightSphereMesh) 
			{
				zERR_FAULT("sphere.3ds missing ??????????????????????????????? why the heck is this file not in the data base, re-put it there, as there has been in it since ages");
				dontDisplayLightSphere = TRUE;
			}
		}

		if (!dontDisplayLightSphere)
		{
			// Mesh entsprechend der lightrange skalieren
			zREAL actRadius = zCVobLight::s_pLightSphereMesh->GetBBox3D().GetSphere3D().radius;
			zREAL scaler	= vobLight->GetRange()/actRadius;
			zCVobLight::s_pLightSphereMesh->Scale(scaler,scaler,scaler);

			zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, trafoObjToWorld);
			zTCam_ClipType	meshClip			= zCCamera::activeCam->BBox3DInFrustum (zCVobLight::s_pLightSphereMesh->GetBBox3D(), renderContext.clipFlags);
			renderContext.distVobToCam			= zCCamera::activeCam->camMatrix.GetTranslation().LengthApprox();
			renderContext.hintLightingFullbright= TRUE;
			
			if ((meshClip!=zCAM_CLIP_TRIV_OUT) && (renderContext.distVobToCam<5000.0F))		// 50m
			{
				//zTRnd_AlphaBlendSource oldBlendSrc = zrenderer->GetAlphaBlendSource();
				//zTRnd_AlphaBlendFunc   oldBlendFunc= zrenderer->GetAlphaBlendFunc  ();
				zTRnd_PolyDrawMode	   oldDrawMode = zrenderer->GetPolyDrawMode	   ();
				//zREAL				   oldBlendFac = zrenderer->GetAlphaBlendFactor();

				zrenderer->SetPolyDrawMode	  (zRND_DRAW_WIRE			 );
				//zrenderer->SetAlphaBlendSource(zRND_ALPHA_SOURCE_CONSTANT);
				//zrenderer->SetAlphaBlendFunc  (zRND_ALPHA_FUNC_BLEND	 );
				//zrenderer->SetAlphaBlendFactor(0.5F						 );

				zCVobLight::s_pLightSphereMesh->Render			(renderContext);

				//zrenderer->SetAlphaBlendSource(oldBlendSrc);
				//zrenderer->SetAlphaBlendFunc  (oldBlendFunc);
				//zrenderer->SetAlphaBlendFactor(oldBlendFac);
				zrenderer->SetPolyDrawMode	  (oldDrawMode);

			};
		}
	}
#endif

	if (!zCVob::GetRenderVobs())							   return FALSE;
	if (!GetHomeWorld())									   return FALSE;
	if ((!GetVisual()) && (!GetShowHelperVisuals()))		   return FALSE;
	if (!zCWorld::S_GetAmbientVobsEnabled() && GetIsAmbient()) return FALSE;

	//
	zBOOL		visible; 
	zCVisual	*activeVisual		= this->GetVisual();

	// RenderContext: einige Felder selbst ausfuellen
	renderContext.vob					= this;					// safety
	renderContext.visualCamAlign		= GetVisualCamAlign();

	// Helper Visual rendern? (i.d.R. nur fuer Editor wichtig)
	if ((!GetVisual()) && (GetShowHelperVisuals()))
	{
		zCVisual *helperVisual = GetClassHelperVisual();
		if (helperVisual)
		{
			// hier wird davon ausgegangen, dass das helperVisual ein bboxOS hat!
			zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, trafoObjToWorld);
			zTCam_ClipType	meshClip			= zCCamera::activeCam->BBox3DInFrustum (helperVisual->GetBBox3D(), renderContext.clipFlags);
			renderContext.distVobToCam			= zCCamera::activeCam->camMatrix.GetTranslation().LengthApprox();
			renderContext.hintLightingFullbright= TRUE;
			if ((meshClip!=zCAM_CLIP_TRIV_OUT) && (renderContext.distVobToCam<5000.0F))		// 50m
			{
				helperVisual->Render			(renderContext);
			};
		};
		return FALSE;
	};

	// CamAlign auswerten & WorldTrafo entsprechend setzen
	if (GetVisualCamAlign()==zVISUAL_CAMALIGN_YAW)
	{
		zVEC3 at							= (GetPositionWorld() - zCCamera::activeCam->GetVob()->GetPositionWorld()); 
		at[VY]								= 0;
		zMAT4 newTrafo						= trafoObjToWorld;
		newTrafo.SetAtVector				(at);
		newTrafo.SetUpVector				(zVEC3(0,1,0));
		newTrafo.MakeOrthonormal			(); 
		zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, newTrafo);
	} else
	if (GetVisualCamAlign()==zVISUAL_CAMALIGN_FULL) 
	{
/*		const zVEC3 pos = camTrafoWorldToCam * trafoObjToWorld.GetTranslation();
		zCCamera::activeCam->camMatrix.ResetRotation	();
		zCCamera::activeCam->camMatrix.SetTranslation	(pos);
		zCCamera::activeCam->camMatrixInv.ResetRotation	();
		zCCamera::activeCam->camMatrixInv.SetTranslation(-pos);*/
		zMAT4 newTrafo						= zMAT4::GetIdentity	();
		newTrafo.SetTranslation				(GetPositionWorld());
		zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, newTrafo);
	} else
	{
		zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, trafoObjToWorld);
	};

	// View-Frustum Culling im ObjectSpace (ist tighter)

	zrenderer->SetZBias(GetZBias());

	zBOOL isPfxTree = FALSE;
	if (zDYNAMIC_CAST<zCParticleFX>(GetVisual()) && this->HasParentVob())
	{
		isPfxTree = TRUE;
	};
	
	if (isPfxTree || zCCamera::activeCam->BBox3DInFrustum (GetBBox3DLocal(), renderContext.clipFlags)!=zCAM_CLIP_TRIV_OUT)  
	{
		renderContext.distVobToCam	= zCCamera::activeCam->camMatrix.GetTranslation().LengthApprox();
		if (zCVob::GetAnimationsEnabled())	
		{
			renderContext.m_AniMode				= GetVisualAniMode();
			renderContext.m_aniModeStrength		= GetVisualAniModeStrength();
		}
		else renderContext.m_AniMode				= zVISUAL_ANIMODE_NONE;

	//	CalcRenderAlpha				(renderContext.distVobToCam, activeVisual, visAlpha);
	//	if (!activeVisual)			{ visible = FALSE; goto leave; }; 

		// Bei Hardware TNL Clipping immer enablen (bzw. immer enabled lassen), bei
		// Software TNL Clipping je nach BBox/Frustum Test aktivieren/deaktivieren.
		if (zrenderer->HasCapability(zRND_CAP_TNL_HARDWARE))	zrenderer->SetRenderState (zRND_RENDERSTATE_CLIPPING, TRUE);
		else													zrenderer->SetRenderState (zRND_RENDERSTATE_CLIPPING, (renderContext.clipFlags>0));
		
		visible = activeVisual->Render	(renderContext);
	} else
		visible = FALSE;

	// Auch wenn das Visual nicht sichtbar sein sollte, muss trotzdem der Schatten gerendert werden !
	if (this->GetCastDynShadow()!=zDYN_SHADOW_TYPE_NONE)
	if (renderContext.distVobToCam<2500)
	{
		RenderGroundShadow(renderContext);
	};

	// ein Model?
	if ((GetVisual()!=0) && (GetVisual()->GetClassDef()==zCModel::GetStaticClassDef()))
	{ 
		// ACHTUNG: auch bei NICHT Aufruf der ::Render() muss SetIsVisible() aufgerufen werden...
		(static_cast<zCModel*>(visual))->SetIsVisible (visible);		// FIXME: ??????????????
	};

	return visible;
};

	// TestCode um Decals als LOD-Visuals zu testen
/*	if (activeVisual->prevLODVisual) 
	if (activeVisual->GetVisualType()==zVISUAL_DECAL) {
		zVEC3 at;
		at		= (GetPositionWorld() - zCCamera::activeCam->GetVob()->GetPositionWorld()); 
		at[VY]	= 0;

		zMAT4 newTrafo			= trafoObjToWorld;
		newTrafo.SetAtVector	(at);
		newTrafo.SetUpVector	(zVEC3(0,1,0));
		newTrafo.MakeOrthonormal(); 
//		SetTrafoObjToWorld		(newTrafo);

		zCVob *camVob = zCCamera::activeCam->GetVob();
//		zCCamera::activeCam->camMatrixInv = camVob->trafo;
//		zCCamera::activeCam->camMatrix    = camMatrixInv.InverseLinTrafo();

		zCCamera::activeCam->camMatrix    = camVob->trafo.InverseLinTrafo() * newTrafo;
		zCCamera::activeCam->camMatrixInv = zCCamera::activeCam->camMatrix.InverseLinTrafo(); 
		zCCamera::activeCam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );
		zCCamera::activeCam->SetUpFrustum(); 
	};
*/

zCOLOR zCVob::GetLightColorAtCenter () const 
{
	zCOLOR res;
	zCArray<zCVobLight*> vobLightList(vobLeafList.GetNumInList()); 
	if ((GetHomeWorld() && (!GetHomeWorld()->IsCompiled()))) {
		res.Reset();
	} else {
		for (int i=0; i<vobLeafList.GetNum(); i++) 
		{ 
			for (int j=0; j<vobLeafList[i]->lightVobList.GetNum(); j++) 
			{
				zCVobLight *light = vobLeafList[i]->lightVobList[j];
				if (!vobLightList.IsInList(light)) vobLightList.Insert (light);
			};
		};
		if (vobLightList.GetNumInList()>0) 
		{
			res = zCVobLight::SumLightsAtPositionWS (vobLightList, GetPositionWorld());
		} else {
			res.Reset();
		};
	};
	return res;
};

// =============================================================================================================

// "PUBLIC"

void zCVob::RemoveVobFromWorld () {
	if (GetHomeWorld())
		GetHomeWorld()->RemoveVob (this);
};

void zCVob::RemoveVobSubtreeFromWorld () {
	if (GetHomeWorld())
		GetHomeWorld()->RemoveVobSubtree (this);
};

void zCVob::ThisVobAddedToWorld (zCWorld *homeWorld)
{
	// called AFTER the actual addition
	// Visuals ggfs. benachrichtigen
	if (GetVisual())	GetVisual()->HostVobAddedToWorld (this, homeWorld);
};

void zCVob::ThisVobRemovedFromWorld (zCWorld *homeWorld)
{
	// called BEFFORE the actual removal
	// Visuals ggfs. benachrichtigen
	if (GetVisual())	GetVisual()->HostVobRemovedFromWorld (this, homeWorld);
};

// "PRIVATE"

void zCVob::AddRefVobSubtree (zCTree<zCVob>* node,const zBOOL a_bLightChildsCanMove)
{
	if (!node)	{
		node = globalVobTreeNode;
		if (!node) return;
	};

	// process node
	if (node->GetData()) 
	{	
		// fackel licht hint. FIXME: nicht hier!
		if (a_bLightChildsCanMove)
		if (zDYNAMIC_CAST<zCVobLight>(node->GetData()))
		{
			static_cast<zCVobLight*>(node->GetData())->SetCanMove(TRUE);
		}
		node->GetData()->AddRef ();
	};

	// recursive traversal
	zCTree<zCVob> *child = node->GetFirstChild(); 
	while (child) {
		AddRefVobSubtree (child);
		child = child->GetNextChild();
	};
};


void zCVob::ReleaseVobSubtree (zCTree<zCVob>* node)
{
	// depth first traversal
	if (!node)	{ 
		node = globalVobTreeNode;
		if (!node) return;
	};

	// recursive traversal
	zCTree<zCVob> *child = node->GetFirstChild(); 
	while (child) {
		zCTree<zCVob> *nextChild= child->GetNextChild(); // Ptr sichern, da er nach dem naechsten Aufruf nicht mehr zur Verfuegung stehen koennte
		ReleaseVobSubtree		(child);
		child					= nextChild;
	};

	// process node
	if (node->GetData()) {
		node->GetData()->Release();
	};
};

void zCVob::RemoveWorldDependencies (zBOOL removeFromGlobalVobTree) 
{
	// FIXME: die World-spezifischen Cleanups sollten in der zCWorld liegen..
	// inform the AI/visual of this event
	if (GetHomeWorld()) {
		if (GetAI())		GetAI()    ->HostVobRemovedFromWorld	(this, GetHomeWorld());
		if (GetVisual())	GetVisual()->HostVobRemovedFromWorld	(this, GetHomeWorld());
	};

	// aus touchVobList abarbeiten: 'OnUntouch' Messages verschicken
	for (int i=0; i<touchVobList.GetNum(); i++)	touchVobList[i]->touchVobList.Remove	(this);
	for (i=0; i<touchVobList.GetNum(); i++)		touchVobList[i]->GetEM()->OnUntouch		(this);
	touchVobList.EmptyList();

	//
	SetSleeping							(TRUE);		// aus active-Liste entfernen
	if (removeFromGlobalVobTree) {
		RemoveVobFromGlobalVobTree		();
	};
	RemoveVobFromBspTree				();

	//
	const zBOOL wasInHomeWorld = (GetHomeWorld()!=0);

	// Bei Vobs ohne einen ParentVob muss bei Verlassen der Welt die relative Trafo auf die absolute
	// gesetzt werden. Allein Child-Vobs, die durch das Entfernen des Root-Vobs automatisch mitentfernt werden,
	// haben an dfieser Stelle noch einen ParentVob. Hier ist das Zuruecksetzen der trafoOS auf die trafoWS nicht 
	// erlaubt, da der relative Zustand zum Parent im trafoOS erhalten bleiben muss.
	if (!this->HasParentVob() && trafo)
	{
        delete trafo;
        trafo = NULL;
        //trafo = trafoObjToWorld;
	};

	// Referenzen auf World-Objekte loeschen
	groundPoly			= 0;
	homeWorld			= 0;
	lastTimeDrawn		= -1;		// 'lastTimeX' bezieht sich immer nur auf die Welt/dessen FrameCtr, in der sich der Vob befindet,
	lastTimeCollected	= 0;		// zur Sicherheit werden beim Entfernen aus einer Welt diese Welt-abhaengigen Werte resettet

	// aus World loeschen: die World gibt ihre Referenz auf das Objekt frei!
	// Aber ACHTUNG: wenn diese Methode aus dem dtor aufgerufen wird, ist refCtr<=0, dann
	// darf Release nicht aufgerufen werden
	if (wasInHomeWorld) {
		// Referenz freigeben, wenn nicht aus Destruktor aufgerufen
		if (this->GetRefCtr()>=1)	zRELEASE_ACCT_NONULL(this);
		// ACHTUNG: this kann ab jetzt ungueltig sein!!!
	};
};

void zCVob::RemoveVobFromGlobalVobTree () 
{ 
	if (globalVobTreeNode) {
		// Falls Söhne dran hängen =>
		// Alle Söhne des zu löschenden Knotens werden Söhne des Parents des zu löschenden Knotens
		// Move globalVobTree-Nodes/Subtrees
		zCTree<zCVob> *vobNode = globalVobTreeNode->GetFirstChild();
		while (vobNode) {
			// aktualisiere Trafo
			zCVob* actVob = vobNode->GetData();
//			actVob->trafo = trafo * actVob->trafo; 
            actVob->DoneWithTrafoLocal();
			// move nodes
			vobNode->MoveSubtreeTo (globalVobTreeNode->GetParent());
//			vobNode->GetNextChild();
			vobNode = globalVobTreeNode->GetFirstChild();
		};
		delete globalVobTreeNode;
		globalVobTreeNode=0;
	};
};

void zCVob::RemoveVobFromBspTree () 
{ 
	if (GetHomeWorld()) {
		GetHomeWorld()->GetBspTree()->RemoveVob (this);
	};
};

// =============================================================================================================

zSTRING zCVob::GetVobInfo () 
{
	zCVob	*vob = this;
	zSTRING s;
	s	= vob->GetClassName_(); 
	s	+= ", id: "		+ zSTRING((int)vob->GetVobID()); 
	if (vob->GetVobName().Length()>0)	s += ", name: "+zSTRING(vob->GetVobName());
	if (vob->GetVisual())				s += ", visual: "+vob->GetVisual()->GetClassName_();
	if (vob->GetAI())					s += ", AI: "+vob->GetAI()->GetClassName_();
	s += ", leafs: "+zSTRING(vob->vobLeafList.GetNumInList());
	s += ", refCtr: "+zSTRING(vob->GetRefCtr());
	zCPolygon *poly = vob->GetGroundPoly();
	if (poly) {
		if (poly->GetMaterial()->GetBspSectorFront()) {
			s+=", sector: ";
//			s+=", sector: "+poly->GetMaterial()->GetBspSectorFront()->GetSectorName();
		};
	};
	return s;
};

void zCVob::SetVisual (zCVisual *newVisual) 
{
	//
	if (GetIgnoreVisuals()) return;

	// neues Visual gleich dem aktuellen ?
	if (visual==newVisual) return;

	// zunächst altes Visual wegwerfen: benachrichtigen
	if ((GetVisual()) && (GetHomeWorld()))	GetVisual()->HostVobRemovedFromWorld (this, GetHomeWorld());

	// zunächst altes Visual wegwerfen
	zRELEASE (visual);

	// neues Visual eintragen
	if (newVisual==0) {
		SetShowVisual  (FALSE);
		return;
	} else
	{
		//
		visual = (zCVisual*)newVisual->AddRef();
		visual->SetVisualUsedBy		(this);
		SetShowVisual				(TRUE);

		// Collision aus, damit beim Aendern des Visuals/der BBox keine Kollisionen mit anderen Vobs ausgeloest werden.
		// Kollision hier mit anderen Vobs wuerde die Anpassung der BBox an das neue Visual verhindern (wichtig fuer Spacer).
		const zBOOL collDyn			= GetCollDetDyn	();
		const zBOOL collStat		= GetCollDetStat();
		SetCollDet					(FALSE);

		// intern: Begin/EndMovement()!!!
		UpdateVisualDependencies	();

		//
		SetCollDetDyn				(collDyn);
		SetCollDetStat				(collStat);
		
		//
		SetCollTypeDefaultFromVisual();

		// neues Visual ueber deren World-Aufenthaltsort benachrichtigen
		if ((GetVisual()) && (GetHomeWorld()))	GetVisual()->HostVobAddedToWorld (this, GetHomeWorld());
	};
};

void zCVob::SetVisual (const zSTRING& visualFileName) 
{
	// hier wird lediglich ein visualName in ein zCVisual* umgewandelt
	if (visualFileName.IsEmpty())	return;
	if (GetIgnoreVisuals())			return;
 
	// 
	zSTRING s (visualFileName);
	s.Upper();

	// Visual Sharing
	// Falls das neue Visual denselben Namen hat, wie das bereits vorhandene, dann braucht dieses nicht neu gesetzt werden.
	// Sharing wird natuerlich auch bei Bedarf in den Visuals innerhalb zCVisual::LoadVisual() betrieben, aber diese Abfrage
	// ist hier z.B. fuer Faelle noetig, in denen es "Prototypes" gibt, damit nicht unnoetig eine neues Visual erzeugt wird.
	// (z.B. zCModel)
	if (GetVisual())
	if (GetVisual()->GetVisualName()==s)
		return;

	zCVisual *newVisual	= zCVisual::LoadVisual (s);

	if (!newVisual)
	{
		#ifndef DEBUG_HILDEBRANDT
			zERR_FAULT	("D: (zCVob::SetVisual): could not load visual '"+visualFileName+"' for vobName '"+GetVobName()+"' of class '"+GetClassName_()+"'");
		#else
			zERR_WARNING("D: (zCVob::SetVisual): could not load visual '"+visualFileName+"' for vobName '"+GetVobName()+"' of class '"+GetClassName_()+"'");
		#endif
	};

	// ein bereits vorhandenes Visual nicht loeschen, falls kein neues da ist
	if (newVisual) 
	{
		if (newVisual!=GetVisual())
		{
			SetVisual (newVisual);
		};
		newVisual->Release();
	};

};


//////////////////////////////////
//    Physik / AI				//
//////////////////////////////////

void zCVob::SetSleeping (zBOOL sleep) 
{
	if (sleep)	SetSleepingMode (zVOB_SLEEPING);
	else		SetSleepingMode (zVOB_AWAKE);
};

void zCVob::SetSleepingMode (const zTVobSleepingMode smode) 
{
	if (smode==sleepingMode) return;

	if (homeWorld) {
		if (smode==zVOB_SLEEPING) {
			homeWorld->RemoveActiveVob	(this); 
			ResetOnTimer				();				// einen evtl. laufenden Timer reseten
		} else {
			homeWorld->AddActiveVob		(this);
		};
	};
	sleepingMode = smode;
};

void zCVob::UpdateVisualDependencies  (const zBOOL a_bHintTrafoChanged) 
{
	// updated innerhalb des Vobs Daten, die von dem dranhaengenden Visual abhaengen (z.B. die BBox).
	if (GetVisual())
	{
		//if (GetHomeWorld())	
		const zBOOL local	= !GetInMovement();
		if (local)			BeginMovement();
		{
			if (GetVisual()->IsBBox3DLocal())	
			{
				// in diesem Fall ist kein direkter Update noetig.. (macht ja EndMovement)
				GetVisual()->GetBBox3D().Transform (trafoObjToWorld, bbox3D);
			} else
			{
				bbox3D			= GetVisual()->GetBBox3D();
				// if (GetHomeWorld())	
				TouchMovement	();
			};
		};
		//	if (GetHomeWorld())	
		// FIXME: der vob hat sich vermutlich nicht bewegt, daher müssen nicht alle Pfade in Endmovement beschritten
		// werden -> opti
		if (local)		EndMovement (a_bHintTrafoChanged);
		
	};
};

void zCVob::AddVobToWorld_CorrectParentDependencies() 
{
	// Situation:
	// Vob ist gerade frisch zu einem Parent gelinkt worden, befindet sich noch nicht 'richtig' in der World
	// und hatte in der Welt auch noch kein BeginMove/EndMove hinter sich. Hier werden seine internen Strukturen
	// auf den neuen ParentLink hin angepasst (also trafo, trafoObjToWorld, bboxOS, bboxWS).
	// Die trafoWS==trafoOS des eingehenden Vobs wird als WS-Koordinaten in der einzufuegenden Welt
	// interpretiert. Deshalb waere folgendes moeglich:
	//		vob->SetPosWorld (xyz); world->AddVob (vob); vob->GetPosWorld() == xyz;

	// Die bereits bestehende trafoObjToWorld des Vobs bleibt unangetastet! (egal, ob zu parent gelinkt, oder nicht)
	// Die trafoOS muss als abhaengige allerdings angepasst werden.

	// v1, eingehender Vob bleibt im WS konstant
	// bboxWS und bboxOS bleiben gleich!!!			(genauso wie die absolute WeltPos. und die Ausrichtung dort, unabh. davon, ob und wenn zu welchem Parent gelinkt wird) 
	// alte trafo = neue trafoObjToWorld
	// const zBOOL identityTrafo	= ((trafo[0][0]==trafo[1][1]) && (trafo[0][0]==trafo[2][2]));
	
	if (HasParentVob())
	{
		// Hier gibt es zwei moeglich Vorbedingungen, man gelangt hier her..
		// - 1) Vob ist Teil eines VobSubtrees, der zur Laufzeit in die Welt eingefuegt wird
		//      => trafo hat bereits korrekten Wert, relativ zum Parent
		// - 2) Vob wird aus einem Archive gelesen
		//		=> trafo ist gleich der trafoObjToWorld (galt nach/im Unarchive als voellig ungelinkt)
		// => in beiden Faellen ist die trafoObjToWorld die bestimmende und die trafo wird angepasst!

//		zCVob *parentVob		= globalVobTreeNode->GetParent()->GetData();
//		trafo					= parentVob->trafoObjToWorld.InverseLinTrafo() * trafoObjToWorld;

        CreateTrafoLocal(); // [Moos] das erledigt das jetzt alles
	} else 
	{
		// ASSERT: trafoObjToWorld==trafo;
//		trafoObjToWorld			= trafo;
	};
};

void zCVob::ResetOnTimer () 
{
	nextOnTimer = zREAL_MAX;
};

void zCVob::SetOnTimer (zREAL deltaTime) 
{
	nextOnTimer = ztimer.GetTotalTimeF() + deltaTime;
	// ein schlafender Vob muss erst wach gemacht werden, damit er auf OnTimer reagiert !
	// (allerdings muss er sich selbst wieder schlafen legen !)
	if (GetSleeping())
		SetSleepingMode (zVOB_AWAKE_DOAI_ONLY);
};

zBOOL zCVob::IsOnTimer () const 
{
	return (nextOnTimer<zREAL_MAX);
};

void zCVob::ProcessOnTimer () 
{
	if (ztimer.GetTotalTimeF()>=nextOnTimer) { 
		nextOnTimer	= zREAL_MAX;	// muss VOR dem OnTimer() Aufruf, damit innerhalb der Methode IsOnTimer() FALSE liefert
		OnTimer		(); 
	};
};


#ifdef DEBUG_MOOS
extern void ignore_addref_release(bool);
#endif

void zCVob::DoFrameActivity () 
{
	if (GetSleepingMode()==zVOB_SLEEPING) return;
	
	#ifdef DEBUG_HILDEBRANDT	
		zengineStats.numVobAI++;
	#endif

	// Dieser Kontext legt eine Referenz auf 'sich selber' an (Schutz vor illegales loeschen dieses Vobs in AI-Callback)

	zADDREF_NOACCT(this);


	zBOOL vobDeleted = FALSE; 
	if (GetSleepingMode()==zVOB_AWAKE_DOAI_ONLY) 
	{
		#ifdef DEBUG_HILDEBRANDT	
			zengineStats.numVobAI_only++;
		#endif
		
		//
		BeginMovement();							// noetig ! (AIPlayer z.B. braucht oldtrafoObjToWorld)

		//
		if (GetAI())	GetAI()->DoAI (this, vobDeleted);

		// Event-System (im Movement-Block!)
		if (!vobDeleted) {
			OnTick			();
			ProcessOnTimer	();
		};

		//
		EndMovement(FALSE);
	} else 
	{
		#ifdef DEBUG_HILDEBRANDT	
			zengineStats.numVobAI_full++;
		#endif
		BeginMovement();

		// *********************
		// ** PHYSIK	      ** 
		// *********************

		UpdatePhysics();


		// *********************
		// ** MODEL-MOVEMENT  **
		// *********************

		// FIXME: hieraus einen virtuellen zCVisual Call machen !!

		if (GetVisualClass()==zCModel::GetStaticClassDef())
		{
			zCModel	*model		= (zCModel*)GetVisual();
			model->AdvanceAnis	(); 

			// Translation
			const zPOINT3& m = model->GetLastPosDelta(); 
			if ( m!=zPOINT3(0,0,0) && ztimer.GetFrameTimeF()>0 ) {
				MoveLocal	(m);
			};

			// Rotation
			if (model->GetDoRotateVob()) 
			{
				zCQuat quat	= model->GetLastRotDelta();

				// Nur Rot um Y-Achse verwenden !
				quat.qx = quat.qz = 0;
				quat.Unit();

				zMAT4	aniRot		= Alg_Identity3D();				// FIXME: 4. Zeile & trans loeschen
				quat.QuatToMatrix4	(aniRot);

				this->SetNewTrafoObjToWorld(this->GetNewTrafoObjToWorld() * aniRot);	// bei startRot=0 perfekt
//				this->trafo			= this->trafo * aniRot;			// bei startRot=0 perfekt
			}  

			{
				if (visual->IsBBox3DLocal())	SetBBox3DLocal	(visual->GetBBox3D());
				else							SetBBox3DWorld	(visual->GetBBox3D());
			};
		};

		// *********************
		// ** AI-CALLBACK     ** 
		// *********************

		// FIXME: vor oder nach den anderen beiden ?? 
		// beachte: innerhalb des Movement-Blocks wird nur die trafo manip., d.h. GetPosWorld...
		// Problem, wenns hier ist:
		// - im letzten Frame koennte das Model nach illegal bewegt worden sein (Sprung durch Decke), aber erst
		//   hier wird es korrigiert
		// Prob, wenns in der Mitte ist:
		// - ClimpUpLedge: (wie unten) die Position wird nach der 'trafoObjToWorld' korigiert, diese ist allerdings
		//   durch die Physik noch nicht beeinfl., die trafo allerdings schon
		// Prob, wenns ganz unten ist:
		// - beachte: innerhalb des Movement-Blocks wird nur die trafo manip., d.h. GetPosWorld... ignoriert dann
		//   das Model-Ani-Movement

		// sinnvoll ist wohl, ganz unten, allerdings muessen dann wohl trafoObjToWorld & bbox3D aktuell sein !!!!!!!
		
		if (callback_ai) callback_ai->DoAI (this, vobDeleted);

		// ********************************************
		// ** COLLISION-DETECTION / UPDATING INTERNS ** 
		// ********************************************

		// Event-System (im Movement-Block!)
		if (!vobDeleted) {
			OnTick			();
			ProcessOnTimer	();
		};

		EndMovement();
	};

	// FIXME: Vob nicht hier loeschen, sondern erst, wenn der komplette Frame durch ist !!
	//        also in Liste speichern und diese am FrameEnde clearen
	if (vobDeleted) 
	{
		// 'vobDeleted' heisst hier 'aus Welt entfernen'
		this->RemoveVobFromWorld();
	};

	// Dieser Kontext gibt seine Referenz auf 'sich selber' frei (Schutz vor illegales loeschen dieses Vobs in AI-Callback)

    zCVob *rel = this;
	zRELEASE_NOACCT(rel);

};


// Checkt die Collision zw. der WeaponNode des 'This'-Vobs/Models gegen alle 
// Models, die die BBox3D der WeaponNode schneiden
// THIS = WEAPON
// TEST = Gegner-Model

// FIXME: ins zCModel verlegen !!

void zCVob::CheckModelLimbCollision (zCModelNodeInst			*weaponNode, 
									 const zBOOL				findApproxCollisionPos,
									 zCList<zTModelLimbColl>	&resCollList) 
{
	// Dieser Vob muss ein Model sein. Macht sonst keinen Sinn.
	if (!weaponNode)		return;
	if (!GetVisual())		return;
	if (!GetHomeWorld())	return;
	if (GetVisualClass()!=zCModel::GetStaticClassDef())	return;

	// ACHTUNG: es wird davon ausgegangen, dass diese Node-BBox3D die des Meshes
	// der Node ist, und nicht die Union des Node-Subtrees !
	zCModel *weaponModel = (zCModel*)GetVisual();
//		const zTBBox3D& weaponBBox = weaponNode->GetData()->GetBBox3DWorld();
	const zTBBox3D& weaponBBox = weaponModel->GetBBox3DNodeWorld(weaponNode);

	zCArray<zCVob*> resVobList;
	// FIXME: unnötiges FindRoot, besser: Kohärenz ausnutzen, von der bspTreeNode aus
	zCBspBase* bspNode = homeWorld->GetBspTree()->GetRoot();
	bspNode->CollectVobsInBBox3D (resVobList, weaponBBox);

	if (resVobList.GetNum()>0) 
	{
		// prüfen, ob mind. 1 Vob das CD-Flag gesetzt hat !
		zMATRIX4 trafoWorldToObj= trafoObjToWorld.InverseLinTrafo();
		for (int i=0; i<resVobList.GetNum(); i++) 
		{
			zCVob *vob = resVobList[i];
			if (vob!=this) 
			if (vob->GetVisual())
			if (vob->GetShowVisual())
			if (vob->GetCollDetDyn()) {
				if (vob->GetVisualClass()==zCModel::GetStaticClassDef())
				{ 
					// ein potent. Colliding-Pair gefunden ! Vob/Model <=> Limb
					// THIS	 = WEAPON
					// OTHER = TEST		= Gegner-Model
					zCModel		*testModel			= (zCModel*)(vob->GetVisual());
					zMATRIX4&	trafoTestToWeapon	= trafoWorldToObj * vob->trafoObjToWorld; 

					// neue Collision-Meldung bauen
					zTModelLimbColl *coll = zNEW(zTModelLimbColl);
					testModel->CheckNodeCollision (weaponModel, weaponNode, trafoTestToWeapon, coll->hitModelNodeList);

					int numCollNodes = coll->hitModelNodeList.GetNumInList();
					if (numCollNodes!=0) {
						// ok, weapon-Limb hat das Model des Test-Vobs irgendwo getroffen (=> nodeListe !)
						// genaueren Hit-Ort suchen ?
						if (findApproxCollisionPos) {
							zTBBox3D		bbox;
							zPOINT3			avgPos = zVEC3(0,0,0);
							for (int i=0; i<numCollNodes; i++) {
								bbox = weaponBBox;
//									bbox.ClipToBBox3D (coll->hitModelNodeList.Get(i)->GetBBox3DWorld());
								bbox.ClipToBBox3D (testModel->GetBBox3DNodeWorld(coll->hitModelNodeList.Get(i)));
								avgPos += bbox.GetCenter();
							};
							if (numCollNodes!=1)	coll->approxCollisionPos = avgPos / zVALUE(numCollNodes);
							else					coll->approxCollisionPos = avgPos;
						};
						coll->hitVob = vob;
						resCollList.Insert(coll);
					} else 
						delete coll;
				} else {
					// vob hat beliebiges visual: a) obb? b) bbox!
					zCOBBox3D	*vobOBB = vob->GetVisual()->GetOBBox3D();				// this
					if (vobOBB) {
						if (weaponNode->GetNodeVisual()) 
						{
							// obb/obb Test
							zCOBBox3D		*weapOBB		= (weaponNode->GetNodeVisual()->GetOBBox3D());
							zCModel			*weaponModel	= (zCModel*)GetVisual();
							zMATRIX4		trafoWeapToWorld= trafoObjToWorld * weaponModel->GetTrafoNodeToModel(weaponNode);
							const zMATRIX4& trafoVobToWeapon= trafoWeapToWorld.InverseLinTrafo () * vob->trafoObjToWorld;

							if (weapOBB)
							if (weapOBB->TestIntersectionTree (vobOBB, trafoVobToWeapon)) {
								zTModelLimbColl *coll = zNEW(zTModelLimbColl);
								if (findApproxCollisionPos) {
									zTBBox3D	bbox		= vob->GetBBox3DWorld();
									bbox.ClipToBBox3D		(weaponBBox);
									coll->approxCollisionPos= bbox.GetCenter();
								};
								coll->hitVob = vob;
								resCollList.Insert(coll);
							};
						};
					} else {
						// bbox/bbox Test
						if (vob->GetBBox3DWorld().IsIntersecting(weaponBBox)) {
							zTModelLimbColl *coll = zNEW(zTModelLimbColl);
							if (findApproxCollisionPos) {
								zTBBox3D	bbox		= vob->GetBBox3DWorld();
								bbox.ClipToBBox3D		(weaponBBox);
								coll->approxCollisionPos= bbox.GetCenter();
							};
							coll->hitVob = vob;
							resCollList.Insert(coll);
						};
					};
				
				};
			}; 
		};
	};
}; 



void zCVob::CheckModelLimbCollisionLevel(zCModelNodeInst		*weaponNode, 
										const zBOOL				findApproxCollisionPos,
										zCList<zTModelLimbColl>	&resCollList) 
{
	// Dieser Vob muss ein Model sein. Macht sonst keinen Sinn.
	if (!weaponNode)		return;
	if (!GetVisual())		return;
	if (!GetHomeWorld())	return;
	if (GetVisualClass()!=zCModel::GetStaticClassDef())	return;

	// ACHTUNG: es wird davon ausgegangen, dass diese Node-BBox3D die des Meshes
	// der Node ist, und nicht die Union des Node-Subtrees !

	zTBBox3D weaponBox = weaponNode->GetBBox3DNodeWorldS();
	if (weaponBox.mins == weaponBox.maxs)
	{
		const zREAL MIN_BOX_SIZE = 20;
		weaponBox.mins[VX] -= MIN_BOX_SIZE;
		weaponBox.mins[VY] -= MIN_BOX_SIZE;
		weaponBox.mins[VZ] -= MIN_BOX_SIZE;
		weaponBox.maxs[VX] += MIN_BOX_SIZE;
		weaponBox.maxs[VY] += MIN_BOX_SIZE;
		weaponBox.maxs[VZ] += MIN_BOX_SIZE;
	}

	const zTBBox3D& weaponBBox = weaponBox;

	// strategie: 1. die Vobs mit zCProgMeshProto/zCMesh/zCMorphMesh Visuals einsammeln, und dann gegen dessen Polys testen
	// (Models werden ja schon weiter oben getestet. FIXME: was ist mit oCMobInter Klassen, diese haben ja teilweise auch zCModel Visuals, oder ?)

	zCArray<zCVob*> resVobList;
	zCPolygon **polyList = NULL;
	int foundPolyNum	 = 0;

	// FIXME: unnötiges FindRoot, besser: Kohärenz ausnutzen, von der bspTreeNode aus
	zCBspBase* bspNode = homeWorld->GetBspTree()->GetRoot();
	bspNode->CollectVobsInBBox3D (resVobList, weaponBBox);

	if (resVobList.GetNum()>0) 
	{
		// prüfen, ob mind. 1 Vob das CD-Flag gesetzt hat !
		zMATRIX4 trafoWorldToObj= trafoObjToWorld.InverseLinTrafo();
		for (int i=0; i<resVobList.GetNum(); i++) 
		{
			zCVob *vob = resVobList[i];
			if (vob!=this) 
			if (vob->GetVisual())
			if (vob->GetShowVisual())
			if (vob->GetCollDetDyn()) 
			if (vob->GetBBox3DWorld().GetMaxExtent()<300) 
			// vobs mit grösserer ausmasse als drei meter kollidieren nicht (vereinfachung, leider)
			// TODO: später kann evtl. ein genauerer Test mit den Polys der Vobs stattfinden.
			// allerdings wäre die derzeitige Implementation von CheckBBoxPolyIntersection dafür zu langsam
			{
				if (vob->GetVisualClass()==zCProgMeshProto::GetStaticClassDef() ) 
					//vob->GetVisualClass()==zCMesh::GetStaticClassDef()	)//		||
					//vob->GetVisualClass()==zCMorphMesh::GetStaticClassDef()	)
				{
					// vob hat beliebiges visual: a) obb? b) bbox!
					zCOBBox3D	*vobOBB = vob->GetVisual()->GetOBBox3D();				// this
					if (vobOBB) 
					{
						if (weaponNode->GetNodeVisual()) 
						{
							// obb/obb Test
							zCOBBox3D		*weapOBB		= (weaponNode->GetNodeVisual()->GetOBBox3D());
							zCModel			*weaponModel	= (zCModel*)GetVisual();
							zMATRIX4		trafoWeapToWorld= trafoObjToWorld * weaponModel->GetTrafoNodeToModel(weaponNode);
							const zMATRIX4& trafoVobToWeapon= trafoWeapToWorld.InverseLinTrafo () * vob->trafoObjToWorld;

							if (weapOBB)
							if (weapOBB->TestIntersectionTree (vobOBB, trafoVobToWeapon)) 
							{
								if (findApproxCollisionPos) 
								{
									// nun alle polys des visuals durchgehen, und die obb gegen die polys testen
									// nope, das ist nicht möglich, da es vobs mit sehr grossen bboxen gibt (bäume)
									// an denen das schwert dann viel zu früh kollidiert
									// deswegen wird nur kollidiert wenn die bbox eine gewisse grösse nicht
									// überschreitet
									if (vob->GetVisualClass()==zCProgMeshProto::GetStaticClassDef())
									{
										zCProgMeshProto* progMesh = static_cast<zCProgMeshProto*>(vob->GetVisual());
										// der einfachheit halber nehmen wir das erste material was ok ist 
										for (int i=0; i<progMesh->GetNumMaterial(); i++)
										{
											if (!progMesh->GetMaterialByIndex(i)->GetNoCollDet())
											{
												zTModelLimbColl *coll = zNEW(zTModelLimbColl);
												zTBBox3D	bbox		= vob->GetBBox3DWorld();
												bbox.ClipToBBox3D		(weaponBBox);
												coll->approxCollisionPos= bbox.GetCenter();
												coll->hitMaterial		= progMesh->GetMaterialByIndex(i);
												resCollList.Insert(coll);
												break;
											}
										}
									}
									else if (vob->GetVisualClass()==zCMesh::GetStaticClassDef())
									{
										zCMesh* mesh = static_cast<zCMesh*>(vob->GetVisual());
										CheckModelLimbCollisionPolys(weaponNode, findApproxCollisionPos, mesh->PolyList(), mesh->numPoly, resCollList);
										if (resCollList.GetNum()>0) return;
									}
								};
							};
						};
					}
					else 
					{
						// bbox/bbox Test
						if (vob->GetBBox3DWorld().IsIntersecting(weaponBBox)) 
						{
							if (findApproxCollisionPos) 
							{
								// nun alle polys des visuals durchgehen, und die obb gegen die polys testen
								if (vob->GetVisualClass()==zCProgMeshProto::GetStaticClassDef())
								{
									zCProgMeshProto* progMesh = static_cast<zCProgMeshProto*>(vob->GetVisual());
									// der einfachheit halber nehmen wir das erste material was ok ist 
									// FIXME: am besten wäre es, wenn man die polys eines progmesh einsammeln könnte

									for (int i=0; i<progMesh->GetNumMaterial(); i++)
									{
										if (!progMesh->GetMaterialByIndex(i)->GetNoCollDet())
										{
											zTModelLimbColl *coll = zNEW(zTModelLimbColl);
											zTBBox3D	bbox		= vob->GetBBox3DWorld();
											bbox.ClipToBBox3D		(weaponBBox);
											coll->approxCollisionPos= bbox.GetCenter();
											coll->hitMaterial		= progMesh->GetMaterialByIndex(i);
											resCollList.Insert(coll);
											break;
										}
									}
								}
								else if (vob->GetVisualClass()==zCMesh::GetStaticClassDef())
								{
									zCMesh* mesh = static_cast<zCMesh*>(vob->GetVisual());
									CheckModelLimbCollisionPolys(weaponNode, findApproxCollisionPos, mesh->PolyList(), mesh->numPoly, resCollList);
									if (resCollList.GetNum()>0) return;
								}
							};
						};
					};
				};
			};
		};
	};

	// nun alle level polys der weaponbbox einsammeln, und diese dann gegen die obb testen
	// FIXME: das könnte wirklich sehr langsam sein, man sollte das zumindest nur alle paar frames machen
	bspNode->CollectPolysInBBox3D(weaponBBox, polyList, foundPolyNum);

	if (foundPolyNum>0)
	{
		CheckModelLimbCollisionPolys(weaponNode, findApproxCollisionPos, polyList, foundPolyNum, resCollList);
	}

}; 

void zCVob::CheckModelLimbCollisionPolys(zCModelNodeInst		 *weaponNode, 
	 									 const zBOOL			 findApproxCollisionPos,
										 zCPolygon**			polyList,
										 const int&				 polyNum,
										 zCList<zTModelLimbColl> &resCollList)
{
	if (polyNum>0) 
	{
		zMATRIX4 trafoObjToWorld		= zCCamera::activeCam->camMatrixInv * weaponNode->GetTrafoObjToCam();
		const zMATRIX4 trafoWorldToObj	= trafoObjToWorld.InverseLinTrafo();

		// FIXME: doppelt!!!
		zTBBox3D weaponBox = weaponNode->GetBBox3DNodeWorldS();
		if (weaponBox.mins == weaponBox.maxs)
		{
			const zREAL MIN_BOX_SIZE = 20;
			weaponBox.mins[VX] -= MIN_BOX_SIZE;
			weaponBox.mins[VY] -= MIN_BOX_SIZE;
			weaponBox.mins[VZ] -= MIN_BOX_SIZE;
			weaponBox.maxs[VX] += MIN_BOX_SIZE;
			weaponBox.maxs[VY] += MIN_BOX_SIZE;
			weaponBox.maxs[VZ] += MIN_BOX_SIZE;
		}

		const zTBBox3D& weaponBBox = weaponBox;
		// prüfen, ob mind. 1 poly kollidieren darf
		for (int i=0; i<polyNum; i++) 
		{
			zCPolygon *poly = polyList[i];
			if (!poly->IsPortal())
			if (!poly->GetMaterial()->GetNoCollDet())
			//if (poly->GetMaterial()->GetMatGroup()!=zMAT_GROUP_WATER)
			if (poly != GetGroundPoly())
			{
				// jetzt wird krass: obb der weapon node besorgen, und dieses poly dagegen testen
				zCOBBox3D	*obbox= NULL;
				if (weaponNode->GetNodeVisual()) obbox = weaponNode->GetNodeVisual()->GetOBBox3D();

				if (obbox)
				{
					if ( obbox->CheckOBBPolyIntersection	(poly, trafoWorldToObj) )
					{
						// poly berührt die obb
						zTModelLimbColl *coll = zNEW(zTModelLimbColl);

						if ( findApproxCollisionPos ) 
						{
							zTBBox3D	bbox		= poly->GetBBox3D();
							bbox.ClipToBBox3D		(weaponBBox);
							coll->approxCollisionPos= bbox.GetCenter();
						};

						coll->hitMaterial = poly->GetMaterial();
						resCollList.Insert(coll);
						// der einfachheit halber brechen wir beim ersten poly ab
						return;
					};
				}
				else
				{
					if ( poly->CheckBBoxPolyIntersection(weaponBBox)) 
					{
						zTModelLimbColl *coll = zNEW(zTModelLimbColl);
						if (findApproxCollisionPos) 
						{
							zTBBox3D	bbox		= poly->GetBBox3D();
							bbox.ClipToBBox3D		(weaponBBox);
							coll->approxCollisionPos= bbox.GetCenter();
						};

						coll->hitMaterial= poly->GetMaterial();						
						resCollList.Insert(coll);
						// der einfachheit halber brechen wir beim ersten poly ab
						return;
					};
				};
			}; 
		};
	};
};

zMATRIX4 zCVob::GetTrafoModelNodeToWorld (const zSTRING& modelNodeName) 
{
	if (GetVisualClass()!=zCModel::GetStaticClassDef()) return trafoObjToWorld;
	zCModelNodeInst *modelNode= ((zCModel*)GetVisual())->SearchNode (modelNodeName);
	return GetTrafoModelNodeToWorld (modelNode);
};

zMATRIX4 zCVob::GetTrafoModelNodeToWorld (zCModelNodeInst *modelNode) 
{
	if (GetVisualClass()!=zCModel::GetStaticClassDef() || (!modelNode)) return trafoObjToWorld;
	return trafoObjToWorld * ((zCModel*)GetVisual())->GetTrafoNodeToModel (modelNode);
};

zTBBox2D zCVob::GetScreenBBox2D() 
{
	// assert: zCCamera::activeCam->camMatrix stimmt
	zERR_ASSERT (zCCamera::activeCam);

	zREAL			xc,yc,xr,yr;
	zTBBox2D		box2D; 

	zTBSphere3D		sphere;
	// kleinere optimierung: statische vobs cachen die bsphere in der klasse
	if (this->GetStaticVob()) 
	{
		if (bsphere3D.radius==FLT_MAX)
		{
			bsphere3D.center = GetBBox3DWorld().GetCenter();
			bsphere3D.radius = zREAL(0.5F) * (GetBBox3DWorld().maxs - GetBBox3DWorld().mins).LengthApprox();
		}
		sphere.center = bsphere3D.center;
		sphere.radius = bsphere3D.radius;
	}
	else
	{
		sphere.center	= GetBBox3DWorld().GetCenter	();
		sphere.radius	= zREAL(0.5F) * (GetBBox3DWorld().maxs - GetBBox3DWorld().mins).LengthApprox();
		// FIXME: ist so leider immer noch nicht ganz perfekt, die Sphere ist manchmal zu klein, besonders,
		// wenn das VobCenter nah an der Cam ist => liegt daran, dass SphereCenter=vobCenter...
	}

	sphere.center	= zCCamera::activeCam->Transform (sphere.center);
	zPOINT3 p2		= sphere.center + zVEC3(-sphere.radius, sphere.radius,0);
	
	// Prob: was, wenn das VobCenter hinter der Cam ist ? 
	if (sphere.center[VZ]<=2) {
		box2D.mins[VX] = box2D.mins[VY] = 0;
		box2D.maxs[VX] = box2D.maxs[VY] = zVALUE_MAX;
//		box2D.Draw();
		return box2D;
	};
	zVALUE zrecip	= (zVALUE(1)) / sphere.center[VZ];

	zCCamera::activeCam->Project (&(sphere.center)	, zrecip, xc, yc);
	zCCamera::activeCam->Project (&(p2)				, zrecip, xr, yr);

	box2D.mins[VX] = xr;
	box2D.mins[VY] = yr;
	box2D.maxs[VX] = xc+(xc-xr);
	box2D.maxs[VY] = yc+(yc-yr);
//	box2D.Draw();
	return box2D;
};

void zCVob::RepairIllegalFloats (zMAT4& matrix)
{
	zBOOL trafoDamaged = FALSE;
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			if ((_isnan (matrix[i][j])) || (!_finite(matrix[i][j])))
			{
				trafoDamaged = TRUE;
				// Rotations-Anteil
				if ((i<3) && (j<3))
				{
					matrix.SetAtVector		(zVEC3(0,0,1));
					matrix.SetUpVector		(zVEC3(0,1,0));
					matrix.SetRightVector	(zVEC3(1,0,0));
				} else
				// Translation
				if ((i<3) && (j==3))
				{
					matrix[i][j] = 0;
				} else
				// Homogener Teil
				if ((i==3) && (j<3))
				{
					matrix[i][j] = 1;
				} else
					matrix[i][j] = 0;
			};
		};
	};

	// Translation auf extreme hohe Werte testen, ggfs. auf 0 korrigieren
	{
		for (int i=0; i<3; i++)
		{
			if (zAbs(matrix[i][3])>1000000.0F)		// 10km
			{
				trafoDamaged = TRUE;
				matrix[i][3] = 0;
			};
		};
	};
	if (trafoDamaged) zERR_WARNING("C: Vob-Trafo has illegal floats and will be corrected (visual-artifacts or illegal vob position change may occur...)");
};

///////////////////////////////////////////////////////////////////////////
//    NETZWERK: Binary State Packing/Unpacking
///////////////////////////////////////////////////////////////////////////

void zCVob::PackStateBinary (zCBuffer& buffer) const 
{
	buffer.SetMode (WRITE);
	const zVEC3&	pos				= GetPositionWorld		();
	const zVEC3&	euler			= trafoObjToWorld.GetEulerAngles	();
	buffer.WriteFloat				(pos[0]);
	buffer.WriteFloat				(pos[1]);
	buffer.WriteFloat				(pos[2]);
	buffer.WriteFloat				(euler[0]);
	buffer.WriteFloat				(euler[1]);
	buffer.WriteFloat				(euler[2]);

	// FIXME: hier muss noch das ein/ausschalten der Physik gemeldet werden, evtl.
	//        muss auch der Zustand der Physik gemeldet werden.. (?)
};

void zCVob::UnpackStateBinary	(zCBuffer& buffer) 
{
	buffer.SetMode (READ);
	zVEC3	pos;
	zVEC3	euler;
	pos[0]	= buffer.ReadFloat		();
	pos[1]	= buffer.ReadFloat		();
	pos[2]	= buffer.ReadFloat		();
	euler[0]= buffer.ReadFloat		();
	euler[1]= buffer.ReadFloat		();
	euler[2]= buffer.ReadFloat		();
									
	// Neue Pos/Orient setzen		
	BeginMovement					();
	SetPositionWorld				(pos);
	trafoObjToWorld.SetByEulerAngles(euler);
	SetTrafoObjToWorld				(trafoObjToWorld); 
	EndMovement						();
};

// ========================================================================================================


///////////////////////////////////////////////////////////////////////////
//    zCVobLevelCompo:	Level-Komponenten
///////////////////////////////////////////////////////////////////////////

zBOOL zCVobLevelCompo::unarcIgnoreVisuals=FALSE;
 
zCVobLevelCompo::zCVobLevelCompo() 
{ 
	SetVobType	(zVOB_TYPE_LEVEL_COMPONENT);
	SetCollDet	(FALSE);
};

zBOOL zCVobLevelCompo::HasIdentityTrafo () const 
{
	if (trafoObjToWorld.GetTranslation().Length2()>zREAL(0.001F)) return FALSE;
	for (int i=0; i<3; i++)
		if ((trafoObjToWorld[i][i]>zREAL(1.001F)) /* || trafo[i][i]<zREAL(0.999F)) */ ) return FALSE;
	return TRUE;
};

void zCVobLevelCompo::Archive (zCArchiver &arc) 
{
	// LevelCompos duerfen keine rot/trans haben !
	if (!HasIdentityTrafo())
		SetTrafo		(Alg_Identity3D());

	//
	zCVob::Archive		(arc);
};

void zCVobLevelCompo::Unarchive (zCArchiver &arc) 
{
	// soll das Visual der LevelKomponente geladen werden ?
	// (wird von zCWorld angesteuert)
	zBOOL flag			= GetIgnoreVisuals ();
	SetIgnoreVisuals	(unarcIgnoreVisuals);
	
	// Basisklasse laden
	zCVob::Unarchive	(arc);

	//
	SetIgnoreVisuals	(flag);
	if (GetIgnoreVisuals()) {
		SetVisual		(0);		// visual releasen, falls doch eins gesetzt wurde...
	};

	// LevelCompos duerfen keine rot/trans haben !
	if (!HasIdentityTrafo())
		SetTrafo		(Alg_Identity3D());
};

void zCVobLevelCompo::SetVisual (zCVisual *v) 
{
	// fuer Visuals muss hier die 'Material-Usage' richtig eingestellt werden
	const zBYTE oldUsage = zCMaterial::GetUsageDefault ();
	zCMaterial::SetUsageDefault	(zCMaterial::zMAT_USAGE_LEVEL);
	
	//
	zCVob::SetVisual			(v);

	//
	SetCollDet					(FALSE);
	zCMaterial::SetUsageDefault	(oldUsage);
};

void zCVobLevelCompo::SetVisual (const zSTRING& visualFileName) 
{
	// fuer Visuals muss hier die 'Material-Usage' richtig eingestellt werden
	const zBYTE oldUsage = zCMaterial::GetUsageDefault ();
	zCMaterial::SetUsageDefault	(zCMaterial::zMAT_USAGE_LEVEL);
	
	//
	zCVob::SetVisual			(visualFileName);

	//
	SetCollDet					(FALSE);
	zCMaterial::SetUsageDefault	(oldUsage);
};


///////////////////////////////////////////////////////////////////////////
//    zCEventMessage
///////////////////////////////////////////////////////////////////////////


zCEventMessage::zCEventMessage (const zTSubType subType) 
{
	this->subType = subType;
};

zTEventMessageID zCEventMessage::GetMessageID () const 
{
	return zTEventMessageID ( zDWORD(GetClassDef()->GetClassID()) + (zDWORD(subType) << 16));
};

void zCEventMessage::AnalyzeMessageID (const zTEventMessageID id, zTClassID& outClassID, zTSubType& outSubType) 
{
	outClassID	= zTClassID(zDWORD(id) & 65535);
	outSubType	= zTSubType(zDWORD(id) >> 16  );
};

zCEventMessage*	zCEventMessage::CreateFromID(zTEventMessageID id) 
{
	zTClassID		classID;
	zCEventMessage* eventMessage;
	zTSubType		subType;
	AnalyzeMessageID (id, classID, subType);
	eventMessage	= (zCEventMessage*)zCClassDef::CreateNewInstanceID (classID);
	eventMessage->subType = subType;
	return eventMessage;
};

void zCEventMessage::PackToBuffer (zCBuffer& buffer, zCEventManager* evManContext) 
{
	zTEventMessageID	eventID	= GetMessageID();
	buffer.Write		(&eventID, sizeof(zTEventMessageID));
	Pack				(buffer, evManContext);
}; 	

zCEventMessage*	zCEventMessage::CreateFromBuffer (zCBuffer& buffer, zCEventManager* evManContext) 
{
	zTEventMessageID	eventID;
	zCEventMessage		*eventMessage;
	buffer.Read			(&eventID, sizeof(zTEventMessageID));
	eventMessage		= CreateFromID	(eventID);
	eventMessage->Unpack (buffer, evManContext);
	return eventMessage;
};	

void zCEventMessage::Archive (zCArchiver& arc) 
{
	zCObject::Archive(arc);

	//
	if (arc.InProperties()) {
		zSTRING choices;
		for (int i=0; i<MD_GetNumOfSubTypes(); i++)
			choices += (zSTRING(";")+MD_GetSubTypeString(i));
		arc.WriteEnum ("subType", choices.ToChar(),subType);
	} else {
		arc.WriteEnum ("subType", "",subType);
	};
};

void zCEventMessage::Unarchive (zCArchiver& arc)
{
    zCObject::Unarchive(arc);

	//
    subType	= arc.ReadEnum ("subType");
};

static void TestClassIntegrity_Callback (zCObject *object, int currentCtr, zCClassDef *classDef, int& numLoops)
{
	if (classDef) {
		zCObject *object	= classDef->CreateNewInstance();
		zCEventMessage *em	= dynamic_cast<zCEventMessage*>(object);
		numLoops			= (em) ? em->MD_GetNumOfSubTypes() : 0;
		object->Release		();
	} else {
		zCEventMessage *em	= dynamic_cast<zCEventMessage*>(object);
		assert (em);
		em->subType			= currentCtr;
	};
};

void zCEventMessage::TestClassIntegrity	()
{
	zerr.Message ("D: Testing zCEventMessage derived classes...");
	// das kann nur der zCArchiverGeneric..
	zCArchiverGeneric::TestClassIntegrity ((zCArchiver::zTTestClassCallback*)(&TestClassIntegrity_Callback));

	// Die Buffer Pack/Unpack Methoden der Messages testen!
	zCVob *dummyVob = zNEW(zCVob);
	zCClassDef *classDef;
	for (int i=0; i<zCClassDef::GetNum(); i++) 
	{
		classDef			= zCClassDef::GetClassDefByIndex(i);
		if (classDef->IsAbstractClass()) continue;
		if (!zCObject::CheckInheritance	(zCEventMessage::GetStaticClassDef(), classDef)) continue;

		//

		zCObject *object	= classDef->CreateNewInstance();
		zCEventMessage *em	= dynamic_cast<zCEventMessage*>(object);
		if (em->MD_GetNumOfSubTypes()>0)
			zerr.Message ("D: EM: >>> Testing Pack()/Unpack() zCEventMessage: "+classDef->GetClassName_()+" (numSubTypes:" +zSTRING(em->MD_GetNumOfSubTypes())+")");

		for (int j=0; j<em->MD_GetNumOfSubTypes(); j++)
		{
			zCEventMessage *em			= dynamic_cast<zCEventMessage*>(classDef->CreateNewInstance());
			zCEventManager *eventManager= zfactory->CreateEventManager(dummyVob);
			em->subType					= j;
			zCBuffer buffer				(65536);
			buffer.SetMode				(WRITE);
			em->Pack					(buffer, eventManager);
			int size = buffer.GetSize	();
			buffer.SetMode				(READ);
			buffer.SetPosBegin			();
			em->Unpack					(buffer, eventManager);
			if (buffer.GetPos()!=size)
				zERR_WARNING ("D: EM: pack/unpack size mismatch, written: "+zSTRING(size)+", read: "+zSTRING(buffer.GetPos()));
			if (size==0)
				zERR_WARNING ("D: EM: suspicious: message has 0 databytes, causes: a) intentionally, b) pack/unpack missing ?");
			eventManager->Release		();
			em->Release					();
		};
		em->Release	();
	};
	dummyVob->Release();
};

///////////////////////////////////////////////////////////////////////////
//    zCEventCore
///////////////////////////////////////////////////////////////////////////

void zCEventCore::Clear () 
{
	otherVob		= 0;
	vobInstigator	= 0;

	// damage
	inflictorVob	= 0;
	damage			= 0;
	damageType		= 0;
	hitLocation		= zVEC3(0,0,0);
};

zCEventCore::~zCEventCore()
{
	otherVob		= 0;
	vobInstigator	= 0;
	inflictorVob	= 0;
};

void zCEventCore::Pack (zCBuffer& buffer, zCEventManager* evManContext) 
{
	zCEventMessage::Pack (buffer, evManContext);

	//
	zTVobID vobID			= otherVob ? otherVob->GetVobID() : zVOB_ID_NULL;
	buffer.Write			(&vobID, sizeof(vobID));

	switch (subType) {
	case zEVENT_TRIGGER:
	case zEVENT_UNTRIGGER:
		{
			zTVobID vobID	= vobInstigator ? vobInstigator->GetVobID() : zVOB_ID_NULL;
			buffer.Write	 (&vobID, sizeof(vobID));
		};
		break;
	case zEVENT_DAMAGE:
		zTVobID vobID		= inflictorVob ? inflictorVob->GetVobID() : zVOB_ID_NULL;
		buffer.Write		(&vobID, sizeof(vobID));
		buffer.WriteFloat	(damage);
		buffer.WriteByte	(damageType);							// FIXME: bitpack
		buffer.Write		(&hitLocation, sizeof(hitLocation));	// FIXME: quantize!
		break;
	};
};

void zCEventCore::Unpack (zCBuffer& buffer, zCEventManager* evManContext) 
{
	zCEventMessage::Unpack (buffer, evManContext);

	//
	Clear();

	//
	zCWorld *homeWorld = evManContext->GetHostVob()->GetHomeWorld();
	zTVobID		vobID;
	buffer.Read (&vobID, sizeof(vobID));
	otherVob	= homeWorld ? homeWorld->SearchVobByID (vobID) : 0;

	switch (subType) {
	case zEVENT_TRIGGER:
	case zEVENT_UNTRIGGER:
		{
			buffer.Read (&vobID, sizeof(vobID));
			vobInstigator= homeWorld ? homeWorld->SearchVobByID (vobID) : 0;
		};
		break;
	case zEVENT_DAMAGE:
		buffer.Read		(&vobID, sizeof(vobID));
		inflictorVob	= homeWorld ? homeWorld->SearchVobByID (vobID) : 0;
		damage			= buffer.ReadFloat	();
		damageType		= buffer.ReadByte	();
		buffer.Read		(&hitLocation, sizeof(hitLocation));
		break;
	};
};

zSTRING zCEventCore::MD_GetSubTypeString	(int n) 
{
	switch (n) {
		case zEVENT_TRIGGER:	return zSTRING("TRIGGER");
		case zEVENT_UNTRIGGER:	return zSTRING("UNTRIGGER");
		case zEVENT_TOUCH:		return zSTRING("TOUCH");
		case zEVENT_UNTOUCH:	return zSTRING("UNTOUCH");
		case zEVENT_TOUCHLEVEL:	return zSTRING("TOUCHLEVEL");
		case zEVENT_DAMAGE:		return zSTRING("DAMAGE");
	};
	return zSTR_EMPTY;
};

void zCEventCore::Archive (zCArchiver& arc) 
{
	zCEventMessage::Archive (arc);
	
//	zSTRING otherVobName;
//	if (otherVob) otherVobName = otherVob->GetVobName();
//	arc.WriteString			("otherVob"		, otherVobName);
	arc.WriteGroupBegin		("DAMAGE");
	arc.WriteFloat			("damage"		, damage);
	arc.WriteByte			("damageType"	, damageType);
	if (!arc.InProperties()) {
		arc.WriteVec3		("hitLocation"	, hitLocation);
	//	arc.WriteString		("inflictorVob"	, otherVobName);
	};

	arc.WriteGroupEnd		("DAMAGE");
};

void zCEventCore::Unarchive (zCArchiver& arc) 
{
	zCEventMessage::Unarchive (arc);

	// 
	Clear();

	//
//	arc.ReadString	("otherVob"		, otherVobName);
	arc.ReadFloat		("damage"		, damage);
	damageType			= arc.ReadByte		("damageType");
	if (!arc.InProperties()) {
		arc.ReadVec3		("hitLocation"	, hitLocation);
	};
};


///////////////////////////////////////////////////////////////////////////
//    Visual
///////////////////////////////////////////////////////////////////////////

zCArray<zCVisual*>	zCVisual::s_visualClassList;

zCVisual::zCVisual() 
{
	nextLODVisual			= prevLODVisual				= 0; 

	// Folgende Wert duerfen hier per Default ruhig sehr hoch angesetzt werden. Das sind Defaults fuer die
	// User-einstellbaren Werte. Runtime wirkt sich automatisch auch die Screen-Space Groesse des Objektes und
	// die eingestellte FarClipPlane aus.
	lodFarDistance			= 50000.0F;		
	lodNearFadeOutDistance	= 49000.0F;
};

zCVisual::~zCVisual() {
	nextLODVisual			= prevLODVisual				= 0; 
};

void zCVisual::AddNextLODVisual (zCVisual *nextVis) 
{
	if (!nextVis) return;
	if (nextLODVisual)	
	nextLODVisual->prevLODVisual= nextVis;

	nextVis->nextLODVisual		= nextLODVisual;
	nextVis->prevLODVisual		= this;

	nextLODVisual				= nextVis;
};

void zCVisual::AddEndLODVisual (zCVisual *endVis) 
{
	if (!endVis) return;
	zCVisual *vis = this;
	while (vis->nextLODVisual) vis = vis->nextLODVisual;

	vis->nextLODVisual			= endVis;
	endVis->nextLODVisual		= 0;
	endVis->prevLODVisual		= vis;
};

void zCVisual::GetLODVisualAndAlpha(const zREAL distToCam, zCVisual* &vis, zREAL& alpha) 
{
	vis = this;
	do {
		if (distToCam<=vis->lodFarDistance) { 
			alpha = 1.0F;
			if (distToCam>vis->lodNearFadeOutDistance) {
				alpha = ((vis->lodFarDistance - distToCam) / (vis->lodFarDistance - vis->lodNearFadeOutDistance));
			};
			return;
		};
		vis = vis->nextLODVisual;
	} while (vis);
	alpha	= 0;
};

zBOOL zCVisual::TraceRay	(	const zVEC3&		rayOrigin, 
								const zVEC3&		ray, 
								const int			traceFlags, 
								zTTraceRayReport	&report)
{
	// MUSS hier TRUE liefern, falls das Visual keinen eigenen Test implementiert
	// => Assert: ein vorausgegangener Ray/BBox Test hat einen Treffer ergeben
	return TRUE;
};

void zCVisual::InitVisualSystem	()
{
	// alle nicht abstrakte, von zCVisual abgeleitete Klassen einsammeln und davon dummy-Objekte erstellen
	zCClassDef* classDef;
	zCClassDef* classDefBase	= zCVisual::GetStaticClassDef ();
	for (int i=0; i<zCClassDef::GetNum(); i++) 
	{
		classDef = zCClassDef::GetClassDefByIndex (i);
		if (zCObject::CheckInheritance (classDefBase, classDef))
		if (!classDef->IsAbstractClass())
		{
			zCVisual *visual = static_cast<zCVisual*>(classDef->CreateNewInstance ());
			// nur visual Klassen mit FileExtensions eintragen
			if (visual->GetFileExtension(0))	s_visualClassList.Insert (visual);
			else								visual->Release();
		};
	};
};

void zCVisual::CleanupVisualSystem	()
{
	for (int i=0; i<s_visualClassList.GetNum(); i++)
	{
		zRELEASE (s_visualClassList[i]);
	};
};

zCVisual* zCVisual::LoadVisual (const zSTRING& visualName)
{
	const zSTRING *fileExt=0;
	for (int i=0; i<s_visualClassList.GetNum(); i++)
	{
		int j=0;
		fileExt = s_visualClassList[i]->GetFileExtension(j);
		while (fileExt)
		{
			if (visualName.Search(*fileExt)!=-1)
			{
				// class found
				zCVisual *newVisual	= s_visualClassList[i]->LoadVisualVirtual (visualName);
				return newVisual;
			};
			j++;
			fileExt = s_visualClassList[i]->GetFileExtension(j);
		};
	};
	zERR_WARNING ("D: unknown visual class, unknown extension: "+visualName);
	return 0;
};


zBOOL	zCVob::	GetIsProjectile	() const
{ 
	return (GetAI() ? GetAI()->GetIsProjectile() : FALSE); 
};