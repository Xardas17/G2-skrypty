/******************************************************************************** 
 
     $Workfile:: zParticle.h          $                $Date:: 4.12.00 17:29    $
     $Revision:: 16                   $             $Modtime:: 4.12.00 17:28    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Particle System (extends zCVisual)
   created       : 24.6.98

 * $Log: /current_work/zengin_work/_Dieter/zParticle.h $
 * 
 * 16    4.12.00 17:29 Hildebrandt
 * 
 * 15    26.10.00 2:23 Hildebrandt
 * 
 * 14    25.10.00 17:00 Hildebrandt
 * 
 * 13    11.10.00 16:17 Keskenti
 * 
 * 12    7.10.00 0:42 Hildebrandt
 * 
 * 11    6.10.00 1:05 Hildebrandt
 * 
 * 10    13.09.00 21:24 Hildebrandt
 * 
 * 9     29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 8     22.08.00 13:41 Hildebrandt
 * made 'zCParticleFX::CalcIsDead()' public
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 6     6.07.00 13:45 Hildebrandt
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 6     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 4     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     16.11.99 19:50 Hildebrandt
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 16 $ ($Modtime: 4.12.00 17:28 $)

// =======================================================================================================================

#ifndef __ZPARTICLE_H__
#define __ZPARTICLE_H__

#ifndef __ZVISUAL_H__
#include <zVisual.h>
#endif

#ifndef __ZRENDERER_H__
#include <zRenderer.h>
#endif

#ifndef __ZPROGMESH_H__
#include <zProgmesh.h>
#endif

#ifndef __ZMODEL_H__
#include <zmodel.h>
#endif



// declarations
class	zCParser;			// <zParser.h>
class	zCPolyStrip;
class	zCQuadMark;

// forward declarations
class	zCParticleFX;
class	zCParticleEmitter;

// =================================================================================

enum zTPFX_EmitterShape {
	zPFX_EMITTER_SHAPE_POINT,
	zPFX_EMITTER_SHAPE_LINE,
	zPFX_EMITTER_SHAPE_BOX,	
	zPFX_EMITTER_SHAPE_CIRCLE,
	zPFX_EMITTER_SHAPE_SPHERE,
	zPFX_EMITTER_SHAPE_MESH
};

enum zTPFX_EmitterFOR {
	zPFX_FOR_WORLD,
	zPFX_FOR_OBJECT,
	zPFX_FOR_OBJECT_EACH_FRAME
};

enum zTPFX_EmitterDirMode {
	zPFX_EMITTER_DIRMODE_NONE,
	zPFX_EMITTER_DIRMODE_DIR,
	zPFX_EMITTER_DIRMODE_TARGET,
	zPFX_EMITTER_DIRMODE_MESH
};

enum zTPFX_EmitterVisOrient {
	zPFX_EMITTER_VISORIENT_NONE,
	zPFX_EMITTER_VISORIENT_VELO_ALIGNED,
	zPFX_EMITTER_VISORIENT_VOB_XZPLANE,
	zPFX_EMITTER_VISORIENT_VELO_ALIGNED3D,
//	zPFX_EMITTER_VISORIENT_ROTATE
	// meshRot
	// texRot
};

enum zTPFX_DistribType {
	zPFX_EMITTER_DISTRIBTYPE_RAND,
	zPFX_EMITTER_DISTRIBTYPE_UNIFORM,
	zPFX_EMITTER_DISTRIBTYPE_WALK,
};

enum zTPFX_FlockMode
{
	zPFX_FLOCK_NONE,
	zPFX_FLOCK_WIND,
	zPFX_FLOCK_WIND_PLANTS,
};


typedef struct zSParticle {
	struct zSParticle*	next;
	zPOINT3				position;			// lokal or WS
	zPOINT3				positionWS;			// WS only
	zVEC3				vel;
	zREAL				lifeSpan;
	zREAL				alpha;
	zREAL				alphaVel;
	zVEC2				size;
	zVEC2				sizeVel;
	zVEC3				color;
	zVEC3				colorVel;
	//zREAL				texAniFrame;					// wird nicht mehr gebraucht, da pro partikel kein seperater frame erlaubt ist (material sortierung verhindert dies)
	//zREAL				flockFreeWillTime;				// wird nicht benutzt
	zCPolyStrip			*polyStrip;
} zTParticle;

// =======================================================================================================================

class zENGINE_API zCParticleEmitter {
public:
	// === D_SCRIPT =====================================================================================================
	// === D_SCRIPT =====================================================================================================
	// === D_SCRIPT =====================================================================================================

	// 1) Emitter: zeitliches  Austoss-Verhalten, particles-per-second
	float					ppsValue;
	zSTRING					ppsScaleKeys_S;
	int						ppsIsLooping;
	int						ppsIsSmooth;
	float					ppsFPS;
	zSTRING					ppsCreateEm_S;
	float					ppsCreateEmDelay;

	// 2) Emitter: raeumliches Austoss-Verhalten
	zSTRING					shpType_S;					//	"point, line, box, circle, sphere, mesh"
	zSTRING					shpFOR_S;					//	"object,world"
	zSTRING					shpOffsetVec_S;				//	(zVEC3 offset in objectSpace)
	zSTRING					shpDistribType_S;			//	"RAND, UNIFORM, WALK"
	float					shpDistribWalkSpeed;
//	int						shpIsUniformDistrib;		
	int						shpIsVolume;
	zSTRING					shpDim_S;					//	"10 20 30"	line: nur 1 Dimension !=0, circ/spher=radius
	zSTRING					shpMesh_S;					//	"cross.3ds"
	int						shpMeshRender_B;
	zSTRING					shpScaleKeys_S;				//	"[1.0] [0.8 0.9 0.2] [1.0]"
	int						shpScaleIsLooping;
	int						shpScaleIsSmooth;
	float					shpScaleFPS;

	// 3) Partikel: Start Richtung/Speed:
	zSTRING					dirMode_S;					//	"DIR, TARGET, MESH_POLY"
	zSTRING					dirFOR_S;					//	"OBJECT, WORLD"
	zSTRING					dirModeTargetFOR_S;
	zSTRING					dirModeTargetPos_S;			//	"30 23 67"
	float					dirAngleHead;
	float					dirAngleHeadVar;
	float					dirAngleElev;
	float					dirAngleElevVar;
	float					velAvg;
	float					velVar;

	// 4) Partikel: Lebensdauer
	float					lspPartAvg;
	float					lspPartVar;

	// 5) Partikel: Flugverhalten (gravity, nicht-linear?, mesh-selfRot?,..)
	// grav: a) nur Y, b) XYZ, c) auf Ziel zu steuern
	// zSTRING  flyMode_S;								//	"LINEAR, LIN_SINUS,.."
	// flyMeshSelfRotSpeedMin, flyMeshSelfRotSpeedMax
	zSTRING					flyGravity_S;
	int						flyCollDet_B;

	// 6) Partikel: Visualisierung
	zSTRING					visName_S;					//	"NAME_V0_A0.TGA/.3DS"	(Variation, Animation)
	zSTRING					visOrientation_S;
	int						visTexIsQuadPoly;			//	0=triMesh, 1=quadMesh
	float					visTexAniFPS;
	int						visTexAniIsLooping;			//	0=oneShot, 1=looping
	// color		(nur Tex, lifeSpan-Sync)			
	zSTRING					visTexColorStart_S;
	zSTRING					visTexColorEnd_S;
	// size-ani		(nur Tex, lifeSpan-Sync)
	zSTRING					visSizeStart_S;
	float					visSizeEndScale;
//	float					visSizeStartX;
//	float					visSizeStartY;
//	float					visSizeEndX;
//	float					visSizeEndY;
	// alpha		(lifeSpan-Sync)
	zSTRING					visAlphaFunc_S;
	float					visAlphaStart;
	float					visAlphaEnd;

	// 7) misc effects
	float					trlFadeSpeed;
	zSTRING					trlTexture_S;
	float					trlWidth;

	// marks
	float					mrkFadeSpeed;
	zSTRING					mrkTexture_S;
	float					mrkSize;

	// flocking fx
	zSTRING					m_flockMode_S;
	float					m_fFlockWeight;

	// master local bool
	zBOOL					m_bSlowLocalFOR;

	zSTRING					m_timeStartEnd_S;
	zBOOL					m_bIsAmbientPFX;

	// === SENTINEL ================================================================================================
	int						endOfDScriptPart;
	// === SENTINEL ================================================================================================

	// === C++ =====================================================================================================
	// === C++ =====================================================================================================
	// === C++ =====================================================================================================
	// 0) 
	zSTRING					particleFXName;				// = name of D-script instance

	// 1)
	zCArray<zREAL>			ppsScaleKeys;
	zCParticleEmitter		*ppsCreateEmitter;
	// 2)
	zTPFX_EmitterShape		shpType;					//	"point, line, box, circle, sphere, mesh"
	float					shpCircleSphereRadius;
	zVEC3					shpLineBoxDim;
	zVEC3*					shpMeshLastPolyNormal;
	zCMesh					*shpMesh;
	zCProgMeshProto			*shpProgMesh;
	zCModel					*shpModel;

	zTPFX_EmitterFOR		shpFOR;
	zTPFX_DistribType		shpDistribType;
	zVEC3					shpOffsetVec;
	zCArray<zREAL>			shpScaleKeys;				//	"[1.0] [0.8 0.9 0.2] [1.0]"
	// 3)
	zTPFX_EmitterDirMode	dirMode;					//	"DIR, TARGET, MESH_POLY"
	zTPFX_EmitterFOR		dirFOR;						//	"OBJECT, WORLD"
	zTPFX_EmitterFOR		dirModeTargetFOR;
	zPOINT3					dirModeTargetPos;			//	"30 23 67"
	zTBBox3D				dirAngleBox;
	zVEC3					dirAngleBoxDim;
	// 4)
	// 5)
	zVEC3					flyGravity;
	// 6)
	zCTexture				*visTexture;
	zTPFX_EmitterVisOrient	visOrientation;
	// size
	zVEC2					visSizeStart;
	// color
	zVEC3					visTexColorRGBAStart;
	zVEC3					visTexColorRGBAEnd;
//	zFIX					visTexColorRGBAStart[4];
//	zFIX					visTexColorRGBAEnd[4];
	// alpha
	zTRnd_AlphaBlendFunc	visAlphaFunc;

	// 7)
	zCTexture				*trlTexture;
	zCTexture				*mrkTexture;

	// 
	zBOOL					 isOneShotFX;
	zREAL					dirAngleHeadVarRad;
	zREAL					dirAngleElevVarRad;
	zTPFX_FlockMode			m_flockMode;
	zREAL					m_ooAlphaDist;
	zREAL					m_startTime;
	zREAL					m_endTime;
	
	// ==============================================================================================================

	// methods
	zCParticleEmitter	();
	~zCParticleEmitter	();

	//
	const zSTRING&			GetParticleFXName			() const { return particleFXName; };
	void					Reset						();
	void					ResetStrings				();
	void					UpdateInternals				();
	void					UpdateVelocity				();
	void					SetOutputDir				(const zVEC3& dir);
	zBOOL					IsOneShotFX					() const { return isOneShotFX; };

private:
	friend class zCParticleFX;

	static zVEC3			String2Vec3					(const zSTRING& s);
	static zVEC2			String2Vec2					(const zSTRING& s);
	void					ConvertAnglesIntoBox		();
	zVEC3	zCCFASTCALL		GetVelocity					(zTParticle* particle, zCParticleFX* partFX);
	zVEC3					GetPosition					();
	void					AddCompoundReferences		();	// adds ref to contained zCObject objects
};
 
class zCParticleEmitterVars {
public:
	// 1
	zREAL					ppsScaleKeysActFrame;
	zREAL					ppsNumParticlesFraction;
	zREAL					ppsTotalLifeTime;
	zBOOL					ppsDependentEmitterCreated;
	// 2
	zREAL					shpScaleKeysActFrame;
	zREAL					uniformValue;
	zREAL					uniformDelta;
	// 3
	// 4
	// 5
	// 6
	//
};

// =================================================================================

class zENGINE_API zCParticleFX : public zCVisual {
	zCLASS_DECLARATION	(zCParticleFX)
public:
	static zCParser		*s_pfxParser;

public:
	static zCArraySort<zCParticleEmitter*>	s_emitterPresetList;
	static zCParticleEmitter				s_emitterDummyDefault;

	static void					CleanupParticleFX		();
	static void					InitParticleFX			();
	static void					ParseParticleFXScript	();
	static zBOOL				S_GetAmbientPFXEnabled	()				 { return s_bAmbientPFXEnabled;	};
	static void					S_SetAmbientPFXEnabled	(const zBOOL m_b){ s_bAmbientPFXEnabled = m_b ; };

	static zCParticleEmitter*	SearchParticleEmitter	(const zSTRING& emitterName);
	static zVALUE				PartRand				();
	static void					SetShowDebugInfo		(const zBOOL b)	{ s_showDebugInfo = b;		};
	static zBOOL				GetShowDebugInfo		()				{ return s_showDebugInfo;	};
	static zBOOL				s_bAmbientPFXEnabled;
public:

	//												
	zCParticleFX();

	// zCVisual interface								
	virtual zBOOL		Render						(zTRenderContext& renderContext);	// TRUE=visible, FALSE=not visible
	zBOOL				IsBBox3DLocal				() { return FALSE; };				// OS / WS
	zTBBox3D			GetBBox3D					();
	zSTRING				GetVisualName				();
	zBOOL				GetVisualDied				()						{ return dead; };
	zBOOL				GetVisualNeverDies			()const					{ return m_bVisualNeverDies; };
	void				SetVisualNeverDies			(const zBOOL m_b)		{ m_bVisualNeverDies = m_b;  };

	void				SetVisualUsedBy				(zCVob* vob);
	zDWORD				GetRenderSortKey			() const				{ return zDWORD(emitter); };	// while rendering vobs they are sorted by their visuals sort-key
	void				HostVobRemovedFromWorld		(zCVob* hostVob, zCWorld* hostWorld);	// informs the visual, called BEFFORE the actual removal
	void				HostVobAddedToWorld			(zCVob* hostVob, zCWorld* hostWorld);	// informs the visual, called AFTER   the actual addition
													
	//												
	void				FreeParticles				();
	void				CreateParticles				();
													
	//												 
	static zCParticleFX* Load						(const zSTRING& partFXName);
	zBOOL				SetEmitter					(const zSTRING& emitterName , const zBOOL createCopy=FALSE);
	zBOOL				SetEmitter					(zCParticleEmitter* em		, const zBOOL createCopy=FALSE);
	zBOOL				SetAndStartEmitter			(const zSTRING& emitterName , const zBOOL createCopy=FALSE);
	zBOOL				SetAndStartEmitter			(zCParticleEmitter* em		, const zBOOL createCopy=FALSE);
	void				StopEmitterOutput			();
	void				RestoreEmitterOutput		();
	void				RemoveEmitter				();
	zCParticleEmitter*	GetEmitter					() const			{ return emitter;					};
	zTParticle*			GetFirstParticle			() const			{ return firstPart;					};
	zCVob*				GetConnectedVob				() const			{ return connectedVob;				};
	zBOOL				IsAmbientPFX				() const			{ return emitter->m_bIsAmbientPFX;	};

	//
	zUINT8				GetIsOneShotFX				() const			{ return this->isOneShotFX;			}
	void				SetIsOneShotFX				(zBOOL bIsOneShot)	{ this->isOneShotFX = bIsOneShot;	}

	//
	void				SetTimeScale				(const zREAL scale)	{ timeScale=scale;					};
	zREAL				GetTimeScale				() const			{ return timeScale;					};
	void				SetDontKillPFXWhenDone		(const zBOOL b)		{ dontKillPFXWhenDone=b;			};
	zBOOL				GetDontKillPFXWhenDone		()					{ return dontKillPFXWhenDone;		};
	zBOOL				GetRenderUnderwaterOnly		() const			{ return renderUnderWaterOnly;		};
	void				SetRenderUnderwaterOnly		(const zBOOL b)		{ renderUnderWaterOnly = b;			};
	void				SetForceEveryFrameUpdate	(const zBOOL b)		{ forceEveryFrameUpdate=b;			};
	zBOOL				GetForceEveryFrameUpdate	()	const			{ return forceEveryFrameUpdate;		};
	zBOOL				CalcIsDead					();

	//
	void				CheckDependentEmitter		();

protected:
	zTParticle			*firstPart;
	zCParticleEmitterVars emitterVars;
	zCParticleEmitter	*emitter;

	zTBBox3D			bbox3DWorld;
	zCVob				*connectedVob;
	int					bboxUpdateCtr;
	struct {
		zUINT8			emitterIsOwned			: 1;
		zUINT8			dontKillPFXWhenDone		: 1;
		zUINT8			dead					: 1;
		zUINT8			isOneShotFX				: 1;	// local, modifiable copy of zCParticleEmitter field
		zUINT8			forceEveryFrameUpdate	: 1;	// .. if not rendered/in frustum that frame
		zUINT8			renderUnderWaterOnly	: 1;
	};

	// 
	virtual	~zCParticleFX();						// use Release() instead!
	// zCVisual interface								
	const zSTRING*		GetFileExtension			(int i);
	zCVisual*			LoadVisualVirtual			(const zSTRING& visualName) const;

private:
	// explicity disable copy-contstructor and assignment-operator
	zCParticleFX		(const zCParticleFX&);
	zCParticleFX&		operator=(const zCParticleFX&);

	static int			s_globNumPart;
	static zTParticle	*s_globPartList;
	static zTParticle	*s_globFreePart;

	static zCMesh		*s_partMeshTri;
	static zCMesh		*s_partMeshQuad;
	static zBOOL		s_showDebugInfo;

	// updating not rendered pfx
	class zCStaticPfxList {
	public:
		zCStaticPfxList() { pfxListHead=pfxListTail=0; numInList=0; };
		zCParticleFX	*pfxListHead;
		zCParticleFX	*pfxListTail;
		int				numInList;

		void			InsertPfxHead	(zCParticleFX *pfx);
		void			RemovePfx		(zCParticleFX *pfx);
		void			TouchPfx		(zCParticleFX *pfx);
		void			ProcessList		();
	private:
		zBOOL			IsInList		(zCParticleFX *pfx) { return !((pfx->nextPfx==pfx->prevPfx) && (pfxListTail!=pfx) && (pfxListHead!=pfx)); };
	};
	static				zCStaticPfxList	s_pfxList;
	friend class		zCStaticPfxList;
	friend class		zCPFXPerFrameCallback;

	zCParticleFX		*nextPfx;
	zCParticleFX		*prevPfx;
	zREAL				privateTotalTime;	
	zREAL				lastTimeRendered;	// 'totalTime', related to timer of the world this visual resides in

	zREAL				timeScale;
	zREAL				localFrameTimeF;
	zCQuadMark			*quadMark;
	zTBBox3D			quadMarkBBox3DWorld;
	float				m_BboxYRangeInv;
	zBOOL				m_bVisualNeverDies;

	void				InitEmitterVars				();
	zREAL				GetShapeScaleThisFrame		();
	int					GetNumParticlesThisFrame	();
	void				UpdateParticleFX			();
	void				UpdateParticle				(zTParticle *particle);
	void				CreateParticlesUpdateDependencies();

};

#endif