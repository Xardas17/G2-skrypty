/****************************************************************
*																
* C++ abstrakte Effekt Visualisierungs Klasse
* File          : oVisFX.h ()								
* Author		: Carsten Edenfeld	
* Projekt       : Gothic
* Version       : 0.07
* last modified : 21.01.99
* erstellt      : 28.12.98
* Compiler OK   : 
*																
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations: this thing is a memory hog
						  chk abstraction level vs. memory usage,

Kopie des Emitters sparen, wenn keine Time oder Pos Keys vorhanden, oder ?

*****************************************************************
- missing features:  

*****************************************************************
- comments:
*****************************************************************/
 
#ifndef __OVISEFFECTS_H__
#define __OVISEFFECTS_H__

//#define _DUMMYVFX_

#include "z3d.h"
#include "zAI.h"
#include "zParticle.h"
#include "zParser.h"
#include "zKBSplines.h"
#include "zsound.h"
#include "zvobmisc.h"

class oCVisualFX; 
class oCVisualFXAI;

const int MAX_SPL_LEVEL		= 20;

enum zTVFXState {
	zVFXSTATE_UNDEF		= 0,
	zVFXSTATE_OPEN		= 1,
	zVFXSTATE_INIT		= 2,
	zVFXSTATE_INVESTNEXT= 3,
	zVFXSTATE_CAST		= 4,
	zVFXSTATE_STOP		= 5,
	zVFXSTATE_COLLIDE	= 6
};

enum TEmTrajectoryMode {
	EM_TRJ_UNDEF		= 0,
	EM_TRJ_FIXED		= 1,		// default, 4 keys, initkey, nextlevel_key, castkey, stop key
	EM_TRJ_TARGET		= 2,		// 
	EM_TRJ_LINE			= 4,
	EM_TRJ_SPLINE		= 8,
	EM_TRJ_RANDOM		= 16,
	EM_TRJ_CIRCLE		= 32,
	EM_TRJ_FOLLOW		= 64,
	EM_TRJ_MISSILE		= 128
};

enum TTrjLoopMode {
	TRJ_LOOP_NONE		= 0,
	TRJ_LOOP_RESTART	= 1,
	TRJ_LOOP_PINGPONG	= 2,
	TRJ_LOOP_HALT		= 3,
	TRJ_LOOP_PINGPONG_ONCE= 4
};


enum TEaseFunc {
	TEASEFUNC_LINEAR  = 0,
	TEASEFUNC_SINE	  = 1,
	TEASEFUNC_EXP	  = 2
};

enum TActionColl {
	TACTION_COLL_NONE	 = 0,
	TACTION_COLL_COLLIDE = 1,
	TACTION_COLL_BOUNCE  = 2,
	TACTION_COLL_CREATE  = 4,
	TACTION_COLL_CREATE_ONCE  = 8,
	TACTION_COLL_NORESP	 = 16,
	TACTION_COLL_CREATE_QUAD = 32
};

const int   VFX_MAX_POS_SAMPLES		= 10;
const int   VFX_NUM_USERSTRINGS		= 5;
const float VFX_LIFESPAN_FOREVER	= -1;

class oCTrajectory {
private:
	zCArray<zCPositionKey*>	keyList;

	zCKBSpline				*spl;
	int						mode;
	float					length;
	zMAT4 res;
	int	  lastKey;
public:
	
	oCTrajectory()
	{
		res		= Alg_Identity3D();
		spl		= 0;
		length  = 0;
		mode	= EM_TRJ_UNDEF;
		lastKey = 0;
	};
	~oCTrajectory()
	{
		if (spl){
			delete spl;
			spl = 0;
		}
		else for (int i=0; i<keyList.GetNumInList(); i++) delete keyList[i];
		keyList.DeleteList();
	};

	void	SetByScript	();
	void	InsertKey	(zMAT4 &trafo) 
	{
		zCPositionKey *k = zNEW(zCPositionKey);  // [Moos] auf zNEW umgestellt
		k->SetMat(trafo);
		keyList.Insert(k);
	}
	zMAT4  GetKey		(const int num) 
	{
		assert(keyList.GetNumInList() >= num);
		return keyList[num]->GetMat();
	}

	void   SetKey		(const int num, const zMAT4 matrix) 
	{
		keyList[num]->SetMat(matrix);
	}

	void  SetMode		(const int &m)													{ mode = m; };

	void  Calc			();
	void  Changed		();
	void  Clear			(); 		
	void  Draw			();
	float Length		()																{ return length; };
	zVEC3 RecalcByColl	(const zPOINT3 &org,const zVEC3 &inVec,const zVEC3& collisionNormal, const int alignCollNormal=FALSE);
	void  ApplyGrav		(const float &g);

	zMAT4 InterpolateN	(const float time);
	zMAT4 Interpolate	(const float dist);

	int	  VobCross		(const zCVob *vob);				// returns upper key, where the crossing occured, -1 if none
	void  SetByList		(zCArray<zCVob*>vobList);
	int	  GetNumKeys	()																{ return keyList.GetNumInList(); };

		
};


class oCEmitterKey {
public:
	// - D-Skript Parser Vars --------------------------------------------------------------
	// particle effect related key vars
	// vars which influence all particles all time

	zSTRING					visName_S;
	float					visSizeScale;
	float					scaleDuration;		// time to reach full scale at this key for relevant vars (size, alpha, etc.)

	float					pfx_ppsValue;
	int						pfx_ppsIsSmoothChg;
	int						pfx_ppsIsLoopingChg;

	float					pfx_scTime;
	zSTRING					pfx_flyGravity_S;

	// vars which influence particles at creation level only
	zSTRING					pfx_shpDim_S;
	int						pfx_shpIsVolumeChg;
	float					pfx_shpScaleFPS;
	float					pfx_shpDistribWalkSpeed;
	zSTRING					pfx_shpOffsetVec_S;
	zSTRING					pfx_shpDistribType_S;
	zSTRING					pfx_dirMode_S;
	zSTRING					pfx_dirFOR_S;
	zSTRING					pfx_dirModeTargetFOR_S;
	zSTRING					pfx_dirModeTargetPos_S;
	float					pfx_velAvg;
	float					pfx_lspPartAvg;
	float					pfx_visAlphaStart;

	zSTRING					lightPresetName;
	float					lightRange;
	zSTRING					sfxID;
	zBOOL					sfxIsAmbient;

	zSTRING					emCreateFXID;
	float					emFlyGravity;
	zSTRING					emSelfRotVel_S;
	zSTRING					emTrjMode_S;
	float					emTrjEaseVel;
	int						emCheckCollision;
	float					emFXLifeSpan;
	
	// cpp-Parser Vars ---------------------------------------------------------------------

	zBYTE					dScriptEnd;

	zVEC3					pfx_flyGravity;
	zVEC3					pfx_shpOffsetVec;
	zTPFX_DistribType		pfx_shpDistribType;
	zTPFX_EmitterDirMode	pfx_dirMode;
	zTPFX_EmitterFOR		pfx_dirFOR;
	zTPFX_EmitterFOR		pfx_dirModeTargetFOR;
	zPOINT3					pfx_dirModeTargetPos;

	zVEC3					emSelfRotVel;
	int						emTrjMode;
	// -------------------------------------------------------------------------------------

	zSTRING					name;

	zCVob					*vob;
	zPOINT3					targetPos;

	zCSoundFX				*sfx;
	zTSoundHandle			sfxHnd;

	static int		GetScriptClassSize() 
	{
		oCEmitterKey tmp;
		return int(&tmp.dScriptEnd)-int(&tmp.visName_S);
	}
	static  void	CreateNewScriptKey(const zSTRING &name);
	
	oCEmitterKey();
	~oCEmitterKey();

	void		   SetName			(const zSTRING &n)					{ name = n; };
	const zSTRING& GetName()											{ return name; };

	void	SetDefaultByFX			(oCVisualFX*fx);
	void	SetByScript				(const zSTRING &id);
	void	Edit					();
	void	ParseStrings			();



};


#ifndef _DUMMYVFX_

class zCEarthQuake;

struct zSVisualFXColl
{
	zCVob*	foundVob;
	zPOINT3 foundContactPoint;
	zVEC3	foundNormal;
};

class oCVisualFX : public zCEffect
{
	zCLASS_DECLARATION (oCVisualFX)
public:
	static	void	  PreSaveGameProcessing(const zBOOL destroyAllObjects);
	static  void	  PostSaveGameProcessing();
	static	void	  SetupAIForAllFXInWorld();

	// - D-Skript Parser Vars --------------------------------------------------------------
	zSTRING			  visName_S;
	zSTRING			  visSize_S;
	float			  visAlpha;
	zSTRING			  visAlphaBlendFunc_S;
	float			  visTexAniFPS;
	int				  visTexAniIsLooping;
	zSTRING			  emTrjMode_S;
	zSTRING			  emTrjOriginNode_S;
	zSTRING			  emTrjTargetNode_S;
	float			  emTrjTargetRange;
	float			  emTrjTargetAzi;
	float			  emTrjTargetElev;
	int				  emTrjNumKeys;
	int				  emTrjNumKeysVar;
	float			  emTrjAngleElevVar;
	float			  emTrjAngleHeadVar;
	float			  emTrjKeyDistVar;
	zSTRING			  emTrjLoopMode_S;
	zSTRING			  emTrjEaseFunc_S;
	float			  emTrjEaseVel;					// TODO: acceleration!
	float			  emTrjDynUpdateDelay;
	int				  emTrjDynUpdateTargetOnly;
	zSTRING			  emFXCreate_S;
	zSTRING			  emFXInvestOrigin_S;
	zSTRING			  emFXInvestTarget_S;
	float			  emFXTriggerDelay;
	int				  emFXCreatedOwnTrj;
	zSTRING			  emActionCollDyn_S;			// CREATE, BOUNCE, COLLIDE
	zSTRING			  emActionCollStat_S;			// CREATE, CREATEONCE, BOUNCE, COLLIDE, CREATEQUAD
	zSTRING			  emFXCollStat_S;
	zSTRING			  emFXCollDyn_S;
	zSTRING			  emFXCollDynPerc_S;
	zSTRING			  emFXCollStatAlign_S;			// TRAJECTORY, COLLISIONNORMAL
	zSTRING			  emFXCollDynAlign_S;
	float			  emFXLifeSpan;
	int				  emCheckCollision;
	int				  emAdjustShpToOrigin;
	float			  emInvestNextKeyDuration;
	float			  emFlyGravity;
	zSTRING			  emSelfRotVel_S;
	zSTRING			  userString[VFX_NUM_USERSTRINGS];

	zSTRING			  lightPresetName;
	zSTRING			  sfxID;
	zBOOL			  sfxIsAmbient;
	int				  sendAssessMagic;
	float			  secsPerDamage;

	// emTrjUpdateFPS n  (0: On next level, other: each n msec) // gravity immer anwenden 

	// collision: wie lange danach vis zeigen ?
	// humanctrl spruch, heal spruch, collision spruch, 

	zBYTE			  dScriptEnd;
	// cpp-Parser Vars ---------------------------------------------------------------------

	zVEC3			  visSize;
	int				  emTrjMode;
	int				  emActionCollDyn;
	int				  emActionCollStat;
	zVEC3			  emSelfRotVel;
	TEaseFunc		  emTrjEaseFunc;
	TTrjLoopMode	  emTrjLoopMode;
	zTVFXState		  fxState;

	// -------------------------------------------------------------------------------------

	static zCParser*		fxParser;
	static oCVisualFX*		actFX;

	oCVisualFX*				root;
	oCVisualFX*				parent;
	oCVisualFX*				fxInvestOrigin;
	oCVisualFX*				fxInvestTarget;
	oCVisualFXAI*			ai;
	zCArray <oCVisualFX *>	fxList;
	zCArray <oCVisualFX *>	childList; 
	zCArray <oCEmitterKey*> emKeyList;  // array of emitter keys, can be controled by timesamples or by the trajectory
	zCArray <zCVob*>		vobList;
	zCArray <zCVob*>		ignoreVobList;
	zCArray <zCVob*>		allowedCollisionVobList;
	zCArray <zCVob*>		collidedVobs;
	zCArray <zSVisualFXColl>queuedCollisions;
	oCTrajectory			trajectory;
	zCEarthquake*			earthQuake;
	zCVobScreenFX*			screenFX;
	float					screenFXTime;
	int						screenFXDir;
	
	zCModelNodeInst*		orgNode;
	zCModelNodeInst*		targetNode;

	zCVisual*				lastSetVisual;
	zCVob*					origin;
	zCVob*					inflictor;
	zCVob*					target;
	zCVobLight*				light;
	float					lightRange;
	zCSoundFX*				sfx;
	zTSoundHandle			sfxHnd;

	zSTRING					fxName;

	oCEmitterKey*			fxBackup;
	oCEmitterKey*			lastSetKey;
	oCEmitterKey*			actKey;
	float					frameTime;
	float					collisionTime;
	float					deleteTime;
	float					damageTime;

	zPOINT3					targetPos;
	zVEC3					lastTrjDir;
	zVEC3					keySize;
	zVEC3					actSize;
	zVEC3					castEndSize;

	float					nextLevelTime;
	float					easeTime;
	float					age;
	float					trjUpdateTime;
	float					emTrjDist;
	float					trjSign;
	float					levelTime;
	float					lifeSpanTimer;
	float					fxStartTime;
	float					oldFovX, oldFovY;

	zBOOL					collisionOccured			: 1;				// bleibt TRUE, bis keine Collision mehr stattfindet
	
	zBOOL					showVisual					: 1;
	zBOOL					isChild						: 1;
	zBOOL					isDeleted					: 1;
	zBOOL					initialized					: 1;
	zBOOL					shouldDelete				: 1;
	zBOOL					lightning					: 1;
	zBOOL					fxInvestOriginInitialized	: 1;
	zBOOL					fxInvestTargetInitialized	: 1;
	zBOOL					fxInvestStopped				: 1;
	zBOOL					timeScaled					: 1;
	int						fovMorph					: 2;
	int						level						: 5;
	int						collisionCtr				: 3;					// wird pro Frame auf 0 reseted
	int						queueSetLevel				: 5;

	static int GetScriptClassSize() 
	{
		oCVisualFX *tmp = new oCVisualFX;
		int size = int(&tmp->dScriptEnd)-int(&tmp->visName_S);
		zRELEASE(tmp);
		return size;
	}

	static void				InitParser();
	static void				ExitParser(); // [Moos]

	// static for spacer/editing	
	static zBOOL			FxConsole_EvalFunc		  (const zSTRING &s, zSTRING &msg);
	static zBOOL			EmConsole_EvalFunc		  (const zSTRING &s, zSTRING &msg);

	static void				FxConsole_ParameterChanged(const zSTRING &s);
	static void				EmConsole_ParameterChanged(const zSTRING &s);

	static oCVisualFX*	    GetActiveFX		  ()									{ return actFX;	 };
	static void			    CreateNewScriptFX (const zSTRING &name);
	static void			    GetTrajectoryVobs (zCArray <zCVob*>resVobList)	{
		if ( GetActiveFX() == 0 ) return;
		for (int i=0; i<GetActiveFX()->emKeyList.GetNumInList(); i++) resVobList.Insert(GetActiveFX()->emKeyList[i]->vob);
	};

	static oCVisualFX* CreateAndPlay	(const zSTRING &id,const zCVob *org,	  const zCVob *target=0, const int level = 1, const float damage = 0, const int damageType = 0, const zBOOL bIsProjectile = FALSE);
	static oCVisualFX* CreateAndPlay	(const zSTRING &id,const zPOINT3 &orgPos, const zCVob *target=0, const int level = 1, const float damage = 0, const int damageType = 0, const zBOOL bIsProjectile = FALSE);

	// constructor -> load data, script instances, etc...
	oCVisualFX			();
	virtual ~oCVisualFX	() ;

	const zSTRING&	GetName						()	const								{ return fxName;					};
	int				GetNumKeys					()										{ return emKeyList.GetNumInList();	};
	oCEmitterKey*	GetKey						( const int num )						{ return emKeyList[num];			};
	oCEmitterKey*	GetActKey					()										{ return actKey;					};
	zCVob*		    GetActiveVob				()										{ return actKey->vob;				};
	int				FindKey						( const zSTRING &id );
	void			InsertKey					( oCEmitterKey *k )						{ emKeyList.Insert(k);				};
	void			ParseStrings				();
	void			Edit						();
	void			SetupEmitterKeysByVisual	();
	void			UpdateFXByEmitterKey		(oCEmitterKey *);
	zBOOL			GetIsChild					()										{ return isChild; };
	void			SetIsChild					(const zBOOL b)							{ isChild = b;	  };
	zBOOL			GetShowVisual				() const								{ return showVisual;};

	void			SetShowVisual				(const zBOOL b)						
	{ 
		if (showVisual != b)
		if (b) SetVisualByString(visName_S); else SetVisualByString("");
		for (int i=0; i<fxList.GetNumInList(); i++) fxList[i]->SetShowVisual(b);
		for (	 i=0; i<childList.GetNumInList(); i++) childList[i]->SetShowVisual(b);
		showVisual=b;	  
	};


	// requested virtuals of zCVob Class

	virtual void	OnTick			() ;

	// seperate virtual magic visual methods, common to all spells / magic visuals

	// init, inserts fx vobs into world, initializes AI Callbacks per frame etc.

	virtual void	Open			();											// fx if selected in spell book 
	virtual void    SetOrigin		( zCVob *orgVob,		const zBOOL recalcTrj = TRUE	) ;
	virtual void    SetTarget		( zCVob *targetVob,		const zBOOL recalcTrj = TRUE	) ;
	virtual void    SetInflictor	( zCVob *inflictorVob) ;
	virtual void    SetTarget		( zPOINT3 &targetPos,	const zBOOL recalcTrj = TRUE	) ;
	virtual zCVob*  GetOrigin		()														{ return origin;	};
	virtual zCVob*  GetTarget		()														{ return target;	};
	virtual zCVob*  GetInflictor	()														{ return inflictor; };
	virtual void	Init			( const zCVob *orgVob, const zPOINT3 &targetPos);	// easy init, can be called more than once
	virtual void	Init			( const zCVob *orgVob = 0, const zCVob *trgtVob = 0, const zCVob* inflictorVob = 0 );  // easy init, can be called more than once
	virtual void	Init			( const zCArray <zCVob *> &trajectoryVobs		);  // adv. init, can be called more than once
	virtual void	InvestNext		()										 ;  // as information for visual spell
	virtual void	SetLevel		( int level, zBOOL force=FALSE )							 ;  // as information for visual spell
	virtual int		GetLevel		()	const								 ;
	virtual void	Cast			( const zBOOL killAfterDone = TRUE );		// shoot
	virtual void	Stop			( const zBOOL killAfterDone = TRUE );		// stop or destroy / delete 
	virtual void	Kill			();
	virtual void	Play			( const float keyCycleTime = 0,const zMAT4 *orgTrafo = 0, const zMAT4 *targetTrafo=0 )	{};
	virtual zBOOL	CanBeDeleted	();
	virtual zBOOL	IsFinished		();
	virtual zBOOL	IsLooping		();
	virtual void	SetByScript		( const zSTRING &id );
	virtual void	SetDuration		( const float fSecDuration )				{ emFXLifeSpan = fSecDuration; };
	virtual void	Reset			();
	virtual void	ResetForEditing	();

	virtual void	ReportCollision			(const zCCollisionReport& collisionReport);
	virtual void	SetCollisionEnabled		(const zBOOL en);
	virtual void	SetCollisionCandidates	(zCArray <zCVob *> collisionVobs);
	virtual void	GetCollisionCandidates	(zCArray <zCVob *> &collisionVobs)	{ collisionVobs = allowedCollisionVobList;	 };
	virtual int		GetNumCollisionCandidates()									{ return allowedCollisionVobList.GetNum();	 };
	virtual zBOOL	GetCollidedCandidates	(zCArray <zCVob *> &collidedVobs);
	virtual zBOOL	CanThisCollideWith		(zCVob* vob);

	// Damage Types

	virtual	void	SetDamage		( const float dam     )						{ damage	 = dam;		};
	virtual	void	SetDamageType	( const int   damType )						{ damageType = damType;	};
	virtual float	GetDamage		() const									{ return damage;		};
	virtual int		GetDamageType	() const									{ return damageType;	};

	// spell types
	virtual	zBOOL	IsASpell		()											{ return sendAssessMagic; };
	virtual	void	SetSpellType	(const int _type)							{ spellType	= _type;		};
	virtual int		GetSpellType	()	const									{ return spellType;		};
	virtual	void	SetSpellCat		(const int cat)								{ spellCat	= cat;		};
	virtual int		GetSpellCat		()	const									{ return spellCat;		};
	virtual int		GetSpellTargetTypes() const									{ return spellTargetTypes;	};
	virtual void	SetSpellTargetTypes(const int types)						{ spellTargetTypes = types;	};
	virtual zBOOL	GetSendsAssessMagic();
	virtual void	SetSendsAssessMagic(const zBOOL a_bSendAssessMagic);

	// misc
	void			SetAllowMovement(const zBOOL b)								{ m_bAllowMovement = b;	};
	zBOOL			GetAllowMovement() const									{ return m_bAllowMovement ;};

	virtual void	Archive			(zCArchiver &);
	virtual void	Unarchive		(zCArchiver &);
	virtual zBOOL	GetIsProjectile ()											{ return bIsProjectile;	};
	virtual void 	SetIsProjectile (const zBOOL b)								{ bIsProjectile = b;	};

	void			SetPFXShapeVisual(zCVisual* a_pVisual, const zBOOL a_bForceChangeMesh=FALSE);

	
	zVEC3&			GetLastTrjDir	()											{ return lastTrjDir; };
	zTVFXState		GetState		()											{ return fxState;	 };

	zREAL			GetSleepTimer	()	const									{ return m_fSleepTimer;	};
	void			SetSleepTimer	(const zREAL f)								{ m_fSleepTimer = f;	};
	static void		RemoveInstancesOfClass  (zCClassDef &classDefinition,const zBOOL destroyAllObjects);

protected:

	virtual void	SetVisualByString( const zSTRING &visName );
	virtual void	CalcTrajectory	 ( const zBOOL &updateTargetOnly=FALSE );
	virtual void    Collide			 ( const zBOOL killAfterDone = TRUE		); // collision or destroy / delete 
	virtual void	CollisionResponse( const zVEC3& collisionNormal, zBOOL alignCollNormal );

	zBOOL			CheckDeletion	();
	void			DoMovements		();
	void			InitValues		();
	void			CreateBackup	();
	oCVisualFX*		CreateAndCastFX	(const zSTRING &id,const zCVob *org,	 const zCVob *inflictor = 0);
	oCVisualFX*		CreateAndCastFX	(const zSTRING &id,const zMAT4 &orgMat);

	void			InitEffect		();
	void			EndEffect		(const zBOOL killAfterDone = TRUE);
	void			CleanUpCriticalFX();


	float			damage;
	int				damageType;

private:
	

	int				spellType;
	int				spellCat;
	int				spellTargetTypes;
	float			savePpsValue;
	zVEC2			saveVisSizeStart;
	zPOINT3			transRing[VFX_MAX_POS_SAMPLES];
	int				ringPos;
	zBOOL			emTrjFollowHitLastCheck;
	zBOOL			bIsProjectile;
	zBOOL			bPfxMeshSetByVisualFX;
	zBOOL			m_bAllowMovement;
	zREAL			m_fSleepTimer;

	void			CreateHierachy			();
	void			DisposeHierachy			();

	void			CreateInvestFX			();
	void			InitInvestFX			();
	void			StopInvestFX			();
	void			DisposeInvestFX			();

	void			AdjustShapeToOrigin		();
	void			UpdateEffects			();
	void			UpdateActKey			();
	zBOOL			CheckDelayedTrigger		();
	zBOOL			ProcessQueuedCollisions	();
	zBOOL			ProcessCollision		(zSVisualFXColl &coll);
	void			CalcPFXMesh				();
	void			ReleasePFXMesh			();



};

// hoffentlich tmp, nur für Kollision
class oCVisualFXAI : public zCAIBase 
{
public:
	zCVob*		vob;
	zBOOL		delete_it;

	oCVisualFXAI() 
	{
		vob		  = 0;
		delete_it = FALSE;
	}

	virtual void	ReportCollisionToAI		(const zCCollisionReport& collisionReport) 
	{
		if (vob) static_cast<oCVisualFX*>(vob)->ReportCollision(collisionReport);
	}
	
	virtual void	HostVobAddedToWorld		(zCVob* hostVob, zCWorld* hostWorld) 
	{
		vob = hostVob;
	};	

	virtual void	DoAI					(zCVob*vob,zBOOL &vobDeleted);
	
	virtual	zBOOL	GetIsProjectile			()									{ return TRUE;	};

	void			RequestDeletion			()									{ delete_it = TRUE;			};
};

#else 


class oCVisualFX : public zCEffect
{
	zCLASS_DECLARATION (oCVisualFX)
public:

	oCVisualFX();
	virtual ~oCVisualFX();

	virtual void	OnTick			() ;

	// init, inserts fx vobs into world, initializes AI Callbacks per frame etc.
	virtual void	Open			();											// fx if selected in spell book 
	virtual void    SetOrigin		( zCVob *orgVob ) ;
	virtual void    SetTarget		( zCVob *targetVob ) ;
	virtual void    SetTarget		( zPOINT3 &targetPos );
	virtual void	Init			( zCVob *orgVob, zPOINT3 &targetPos		);	// easy init, can be called more than once
	virtual void	Init			( zCVob *orgVob = 0, zCVob *trgtVob = 0 );  // easy init, can be called more than once
	virtual void	Init			( zCArray <zCVob *> trajectoryVobs		);  // adv. init, can be called more than once
	virtual void	InvestNext		()										 ;  // as information for visual spell
	virtual void	SetLevel		( int level )							 ;  // as information for visual spell
	virtual int		GetLevel		()	const								 ;
	virtual void	Cast			( const zBOOL killAfterDone = TRUE );		// shoot
	virtual void	Stop			( const zBOOL killAfterDone = TRUE );		// stop or destroy / delete 
	virtual void	Kill			();
	virtual void	Play			( const float keyCycleTime = 0,const zMAT4 *orgTrafo = 0, const zMAT4 *targetTrafo=0 )	{};
	virtual zBOOL	IsFinished		();
	virtual zBOOL	IsLooping		();
	virtual void	SetByScript		( const zSTRING &id );
	virtual void    SetCollDetStat  ( const zBOOL b );

	virtual void	ReportCollision			(const zTVobCollisionReport& collisionReport);
	virtual void	SetCollisionEnabled		(const zBOOL en);
	virtual zBOOL	CanThisCollideWith		(zCVob* vob);

	// Damage Types

	virtual	void	SetDamage		( const float dam     );
	virtual	void	SetDamageType	( const int   damType );
	virtual float	GetDamage		() const;
	virtual int		GetDamageType	() const;

	virtual void	Archive			(zCArchiver &);
	virtual void	Unarchive		(zCArchiver &);

	static void		InitParser			();
	static zBOOL	FxConsole_EvalFunc  (const zSTRING &s, zSTRING &msg);

};

#endif

#endif
