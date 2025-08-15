/******************************************************************************** 
 
     $Workfile:: zModel.h             $                $Date:: 15.03.01 2:17    $
     $Revision:: 32                   $             $Modtime:: 14.03.01 21:15   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ animated 3D-Models (mdl)
   created       : 28.10.97

 * $Log: /current_work/ZenGin/_Dieter/zModel.h $
 * 
 * 32    15.03.01 2:17 Hildebrandt
 * 
 * 31    5.02.01 19:13 Hildebrandt
 * 
 * 30    1.02.01 19:58 Moos
 * 
 * 29    31.01.01 5:47 Hildebrandt
 * 
 * 28    30.01.01 5:16 Hildebrandt
 * 
 * 27    17.01.01 18:01 Hildebrandt
 * 
 * 26    8.01.01 17:55 Hildebrandt
 * 
 * 25    15.12.00 13:07 Moos
 * 
 * 24    15.12.00 3:44 Hildebrandt
 * 
 * 23    13.12.00 18:14 Hildebrandt
 * 
 * 22    4.12.00 17:29 Hildebrandt
 * 
 * 21    17.11.00 1:29 Hildebrandt
 * 
 * 20    7.11.00 17:24 Hildebrandt
 * 
 * 19    21.09.00 21:20 Hildebrandt
 * zenGin 0.94
 * 
 * 18    13.09.00 21:24 Hildebrandt
 * 
 * 17    8.09.00 16:47 Moos
 * 
 * 16    5.09.00 21:45 Hildebrandt
 * 
 * 15    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 14    24.08.00 14:26 Hildebrandt
 * 
 * 13    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 12    21.07.00 14:28 Hildebrandt
 * 
 * 11    11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 10    6.07.00 13:45 Hildebrandt
 * 
 * 6     10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
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
 * 11    11.01.00 20:59 Hildebrandt
 * zenGin 085b
 * 
 * 10    10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 8     16.11.99 19:49 Hildebrandt
 * 
 * 7     9.11.99 16:55 Hildebrandt
 * ZenGin 083c
 * 
 * 6     22.10.99 21:58 Hildebrandt
 * test
 * 
 * 5     22.10.99 21:57 Hildebrandt
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 32 $ ($Modtime: 14.03.01 21:15 $)

// =======================================================================================================================

#ifndef __ZMODEL_H__
#define __ZMODEL_H__

#ifndef __ZVISUAL_H__
#include <zVisual.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

#ifndef __ZPROGMESH_H__
#include <zProgMesh.h>
#endif

#ifndef __ZRESOURCE_H__
#include <zResource.h>
#endif

#ifndef __ZSCANDIR_H__
#include <zScanDir.h>
#endif


#ifndef __ZSOUND_H__
#include <zSound.h>
#endif


// =======================================================================================================================

class zCFileBIN;			// zFile3d.h
class zCSoundFX;			// zSound.h
class zCParticleEmitter;	// zParticle.h
class zCBuffer;				// zBuffer.h

// forward declarations 

class zCModelPrototype;
class zCModelAni;

class zCModelNode;
class zCModelNodeInst;
class zCModelMesh;
class zCModel;
class zCModelAniActive;
class zCModelTexAniState;

// =======================================================================================================================

// name-conventions for model-nodes (biped)
extern const zSTRING	zMDL_NODE_NAME_BIP_PREFIX;
extern const zSTRING	zMDL_NODE_NAME_R_HAND;
extern const zSTRING	zMDL_NODE_NAME_L_HAND;
extern const zSTRING	zMDL_NODE_NAME_R_FOOT;
extern const zSTRING	zMDL_NODE_NAME_L_FOOT;
extern const zSTRING	zMDL_NODE_NAME_HEAD;
extern const zSTRING	zMDL_NODE_NAME_FOOTSTEPS;

typedef int zTModelAniID;

#define zMDL_ANI_ID_ILLEGAL	(-1)

// ************************************************************************************************************
//   Model - Prottypes (Ani, Node, Model)
// ************************************************************************************************************

// A ModelMeshLib is a collection of meshes that can be applied or removed from a model. 
// Several MeshLibs can be applied to one Model. Meshes of a MeshLib possibly overlay previously applied
// Meshlibs. Objects of class zCModelMeshLib are uniquely named and are shared objects.

class zENGINE_API zCModelMeshLib : public zCObject {
	zCLASS_DECLARATION (zCModelMeshLib)
public:
	typedef struct {			
		zCVisual				*visual;			// visual that sits in a model's node
		int						nodeIndex;			// index of the node in the model/modelProto's hierarchy (=>nodeList)
//		zCModelNodeInst			*node;
//		zCModelNode				*protoNode;
	} zTNodeMesh;

	void						AllocNumNodeVisuals	(int num);
	void						AddMeshSoftSkin		(zCMeshSoftSkin* meshSoftSkin);
	void						AddNodeVisual		(int nodeIndex, zCVisual *visual);
	void						ApplyToModel		(zCModel *model);
	void						ApplyToModel		(zCModelPrototype *modelProto);
	void						BuildFromModel		(zCModel *model);
	void						BuildFromModel		(zCModelPrototype *modelProto);
	void						RemoveFromModel		(zCModel *model);
	zCArray<zTNodeMesh>&		GetMeshNodeList		() { return meshNodeList;	};
								
	//							
	static zDWORD				GetMDMFileVersion	();
	static zBOOL				LoadMDM				(const zSTRING& filename, zCModelPrototype *destProto, zCModel *destModel, zCModelMeshLib **meshLib=0);
	static zBOOL				LoadMDM				(zCFileBIN&		file	, zCModelPrototype *destProto, zCModel *destModel, zCModelMeshLib **meshLib=0);
	void						SaveMDM				(zCModelPrototype *hostProto);
	void						SaveMDM				(zCFileBIN&		file, zCModelPrototype *hostProto);
	zCArray<zCMeshSoftSkin*>&	GetSoftSkins		()	{ return meshSoftSkinList;	};


protected:
	virtual ~zCModelMeshLib();			// use Release() instead !

private:						
	zCArray<zTNodeMesh>			meshNodeList;
	zCArray<zCMeshSoftSkin*>	meshSoftSkinList;

	void						ReleaseData			();
	static zBOOL				ConvertMDM			(const zSTRING& filename, zCModelPrototype *convertProto);
	static zBOOL				LoadMDM_Try			(const zSTRING&		filename, 
													 zCModelPrototype	*destProto, 
													 zCModel			*destModel, 
													 zCModelMeshLib		**resMeshLib);
	friend zCModelTexAniState;
};

// =====================================================================================

enum zTMdl_AniDir {
	zMDL_ANIDIR_FORWARD,
	zMDL_ANIDIR_REVERSE,
	zMDL_ANIDIR_ENDFASTEST
};	// ATT: keep in sync with bitfield!

enum zTMdl_AniEventType {
	zMDL_EVENT_TAG,
	zMDL_EVENT_SOUND,				//		(frameNr "stepping.wav" prob)
	zMDL_EVENT_SOUND_GRND,			//		(frameNr "stepping.wav" prob)
	zMDL_EVENT_ANIBATCH,
	zMDL_EVENT_SWAPMESH,			//		(frameNr "sourceNode"	"targetNode")
	zMDL_EVENT_HEADING,				//		(frameNr dAlpha			dBeta dGamma)
	zMDL_EVENT_PFX,
	zMDL_EVENT_PFX_GRND,
	zMDL_EVENT_PFX_STOP,
	zMDL_EVENT_SETMESH,
	zMDL_EVENT_MM_STARTANI,
	zMDL_EVENT_CAM_TREMOR,			//		(frameNr radiusCM	durationMSec	strengthXZPlane	strengthYHeight)
};


class zENGINE_API zCModelAniEvent {
public:
	zTMdl_AniEventType	aniEventType;

	enum { zMDL_ANIEVENT_MAXSTRING = 4 };
	int							frameNr;
	zSTRING						tagString;
	zSTRING						string[zMDL_ANIEVENT_MAXSTRING];
	zVALUE						value1;
	zVALUE						value2;
	zVALUE						value3;
	zVALUE						value4;
//	zVALUE						prob;				// obsolete ?
	zCArray<zCSoundFX*>			soundList;			// list => for different ground materials
	zCArray<zCParticleEmitter*>	pfxEmitterList;		// "

	zCModelAniEvent();
    ~zCModelAniEvent(); // [Moos] deletes the lists properly

	void Save (zCFileBIN& file) const;
	void Load (zCFileBIN& file);
};

// =====================================================================================

class zENGINE_API zCModelNode {
public:
	zCModelNode			*parentNode;
	zSTRING				nodeName;
	zCVisual			*visual;
	zMATRIX4			trafo;

	zVEC3				nodeRotAxis;		// tmp ?
	zVALUE				nodeRotAngle;		// tmp ?
	zPOINT3				translation;		// tmp ?
	zMATRIX4			trafoObjToWorld;	// tmp ?
	zMATRIX4			*nodeTrafoList;		// tmp ?
	zCModelNodeInst		*lastInstNode;
	
	zCModelNode();
	~zCModelNode();
	zCModelNode(const zCModelNode&);
	const zSTRING&		GetName			()	const	{ return nodeName;	};
	zCModelNode*		GetParentNode	()	const	{ return parentNode;};
	zBOOL				IsRootNode		()  const	{ return (GetParentNode()==0); };
	zCVisual*			GetNodeVisual	()	const	{ return visual;	};
	void				SetNodeVisualS	(zCVisual *visual);
	zBOOL				IsSlot			()	const	{ return (nodeName.Length()>=3) && (nodeName[0]=='Z') && (nodeName[1]=='S') && (nodeName[2]=='_'); };
};

// =====================================================================================

// Packed animation sample.

#pragma pack (push, 1)
typedef struct {
	static	zREAL			samplePosScaler;
	static  zREAL			samplePosRangeMin;
	static  void			CalcSamplePosConstants	(const zREAL transMin, const zREAL transRange);
	static  void			SetSamplePosConstants	(const zREAL transMin, const zREAL transScaler);

	zWORD	rotation[3];		// 16bit quantized euler angles
	zWORD	position[3];		// 16bit quantized zVEC3
	
	void	zCCFASTCALL		Pack					(const zCQuat &quat, const zVEC3& trans);
	void	zCCFASTCALL		Unpack					(zCQuat &quat, zVEC3& trans) const;
													
	void	zCCFASTCALL		PackTrans				(const zVEC3& trans);
	void	zCCFASTCALL		UnpackTrans				(zVEC3& trans) const;
													
	void	zCCFASTCALL		PackQuat				(const zCQuat &quat);
	void	zCCFASTCALL		UnpackQuat				(zCQuat &quat) const;
} zTMdl_AniSample;
#pragma pack (pop)

// =====================================================================================

enum zTMdl_AniType {	zMDL_ANI_TYPE_NORMAL, 
						zMDL_ANI_TYPE_BLEND, 
						zMDL_ANI_TYPE_SYNC, 
						zMDL_ANI_TYPE_ALIAS, 
						zMDL_ANI_TYPE_BATCH,
						zMDL_ANI_TYPE_COMB,
						zMDL_ANI_TYPE_DISABLED
					};	// ATT: keep in sync with bitfield

const zREAL zMDL_ANI_BLEND_IN_ZERO	= zREAL_MAX;
const zREAL zMDL_ANI_BLEND_OUT_ZERO =-zREAL_MAX;

//class zENGINE_API zCModelAni : public zCResource {
//	zCLASS_DECLARATION (zCModelAni)

class zENGINE_API zCModelAni : public zCObject {
	zCLASS_DECLARATION (zCModelAni)

	// ACHTUNG: Bei Neuzugaengen hier auch immer 'zCModelPrototype::ResolveReferences()' updaten !!!
	enum {	zMAN_VERS = (00*256 + 12 )	};
public:
	enum {	zMDL_ANI_FLAG_VOB_ROT	= 1, 
			zMDL_ANI_FLAG_VOB_POS	= 2,
			zMDL_ANI_FLAG_END_SYNC	= 4,
			zMDL_ANI_FLAG_FLY		= 8,
			zMDL_ANI_FLAG_IDLE		= 16 };

	// zCResource interface
	// Only override this methods if the derived class needs is a real resource and 
	// needs the zCResource/zCResourceManager services. zCClassDef zCLASS_FLAG_RESOURCE should be set for these classes.
//	zBOOL				LoadResourceData	();
//	zBOOL				ReleaseResourceData	();
//	zDWORD				GetResSizeBytes		();		// size of cachedIn resource, doesn't need to be exact but should calculate fast, for zCResourceManager cacheLimit calculations

	//
	zCModelAni();
	void				AddTrafoMatrix		(zMATRIX4 **intrafoMatrix);
	void				AddNodeList			(zCTree<zCModelNode> **mnodeList);
	void				SetAniName			(const zSTRING& name)	{ aniName = name; };
	const zSTRING&		GetAniName			() const				{ return aniName; };
	zTMdl_AniType		GetAniType			() const				{ return aniType; };
	void				SetAniType			(zTMdl_AniType type)	{ aniType=type; };
	void				SetFlags			(const zSTRING& s);
	void				SetBlendingSec		(const zVALUE blendInSec, const zVALUE blendOutSec);
	void				GetBlendingSec		(zVALUE& blendInSec, zVALUE& blendOutSec) const;
	zBOOL				ResolveAlias		(zCModelPrototype *hostModelProto);
	zBOOL				ResolveComb			(zCModelPrototype *hostModelProto);
	void				PrepareAniDataAccess()	const { zTMdl_AniSample::SetSamplePosConstants (samplePosRangeMin,samplePosScaler); };
	void				PrecacheAniEventData();
						
	zREAL				GetBlendInSpeed		() const	{ return blendInSpeed;	};
	zREAL				GetBlendOutSpeed	() const	{ return blendOutSpeed; };
	zCModelAni*			GetNextAni			() const				{ return nextAni;			};
	void				SetNextAni			(zCModelAni* nextAni)	{ this->nextAni = nextAni;	};
											
	zCQuat				GetQuat				(int frameNumber, int nodeNumber) const;
	zVEC3				GetTrans			(int frameNumber, int nodeNumber) const;
	void				SetTrans			(int frameNumber, int nodeNumber, const zVEC3& trans);
	void				SetQuat				(int frameNumber, int nodeNumber, const zCQuat& quat);
	void				CorrectRootNodeIdleMovement();
	void				CalcInPlaceFlag		();
	zBOOL				CorrectAniFreezer	();

	void				SetCollisionVolumeScale(const zREAL scale)	{ collisionVolumeScale = scale; };
	zREAL				GetCollisionVolumeScale() const				{ return collisionVolumeScale;	};
	
	zTModelAniID		GetAniID			() const				{ return aniID; };
	void				SetAniID			(const zTModelAniID id)	{ aniID = id;	};
											
	zREAL				GetAniTimeLength	() const			{ return (zREAL(numFrames) / zREAL(fpsRate) * zREAL(1000.0F)); };		// msec
	zREAL				GetAniVelocity		() const;			// cm/msec
	zVEC3				GetAniTranslation	() const;			// difference of translation of root node from first to last frame
	zREAL				GetFPSRate			() const			{ return fpsRate;		};
	int					GetLayer			() const			{ return layer;			};
											
	int					GetNumAniEvents		() const			{ return numAniEvents;	};
	zCModelAniEvent*	GetAniEventsPtr		() const			{ return aniEvents;		};

	int					GetNumFrames		() const			{ return numFrames;		};
	int					GetRootNodeIndex	() const			{ return rootNodeIndex; };
	
	//										
	zBOOL				FlagModifiesVob		() const			{ return (FlagRotatesVob() || FlagMovesVob()); };
	zBOOL				FlagRotatesVob		() const			{ return aniFlags.flagVobRot;		};
	zBOOL				FlagMovesVob		() const			{ return aniFlags.flagVobPos;		};
	zBOOL				FlagSyncWithEnd		() const			{ return aniFlags.flagEndSync;		};
	zBOOL				FlagFlying			() const			{ return aniFlags.flagFly;			};
	zBOOL				FlagIdle			() const			{ return aniFlags.flagIdle;			};
	zBOOL				FlagInPlace			() const			{ return aniFlags.flagInPlace;		};
	zBOOL				FlagStaticCycle		() const			{ return aniFlags.flagStaticCycle;	};
	
											
	// File In/Out							
	void				SaveMAN				(zCModelPrototype *hostModelProto, const zSTRING& scriptDefLine="");
	zBOOL				LoadMAN				(const zSTRING& filename, zCModelPrototype *hostModelProto, const zSTRING& scriptDefLine="");

protected:
	virtual ~zCModelAni();		// use Release() instead!

private:
	zSTRING				aniName;		
	zSTRING				ascName;
	zTModelAniID		aniID;

	zSTRING				aliasName;
	zCList<zCModelAni>	combAniList;

	int					layer;
	zREAL				blendInSpeed;				// Ani-blending
	zREAL				blendOutSpeed;
	zTBBox3D			aniBBox3DObjSpace;
	zREAL				collisionVolumeScale;
					
	zCModelAni			*nextAni;
	zSTRING				nextAniName;
	zCModelAniEvent		*aniEvents;

	zREAL				fpsRate;
	zREAL				fpsRateSource;
	int					rootNodeIndex;				// FIXME: ueberfluessig !!

	// jede Ani hat ein Zahl animierter Nodes, die auch kleiner sein kann, als die Zahl Nodes des Models.
	// 'nodeIndexList' mapt nun die Nodes der Ani auf die Nodes des Models
	zCArray<int>		nodeIndexList;				// entries = indicies into zCModel//zCModelProto's "nodeList"
	zCModelNode			**nodeList;
	zTMdl_AniSample		*aniSampleMatrix;
	zREAL				samplePosRangeMin;
	zREAL				samplePosScaler;

	struct {
		int				numFrames		: 16;		// table-y
		int				numNodes		: 16;		// table-x
		zTMdl_AniType	aniType			: 6;
		zTMdl_AniDir	aniDir			: 2;
		int				numAniEvents	: 6;		// maximum of 64 aniEvents
	};
	struct {
		zUINT8			flagVobRot		: 1;
		zUINT8			flagVobPos		: 1;
		zUINT8			flagEndSync		: 1;
		zUINT8			flagFly			: 1;
		zUINT8			flagIdle		: 1;			// ani is very subtle (is not played if model is far away from camera)
		zUINT8			flagInPlace		: 1;			// ani does not move the model very far from one spot
		zUINT8			flagStaticCycle	: 1;			// cycling repetitive ani, not moving the model from the spot, (special care is taken to keep the model EXACTLY on the same spot at frame 0) (note: flagInPlace => flagStaticCycle)
	} aniFlags;

	friend zCModel;
	friend zCModelPrototype;
	friend zCModelAniActive;
	friend zCModelNodeInst;
};

// =====================================================================================

enum zTModelProtoImportMAXFlags
{
	zMDL_MAX_IMPORT_ANI			= 1,	// import ani
	zMDL_MAX_IMPORT_MESH		= 2,	// import mesh
	zMDL_MAX_IMPORT_TREE		= 4,	// import tree
	zMDL_MAX_IMPORT_PASS_ZCMESH	= 8,	// instead of zCProgMeshProto
	zMDL_MAX_IMPORT_NO_LOD		= 16,	// don't generate LOD if zCProgMeshProto is imported
};

class zENGINE_API zCModelPrototype {
public:
	static	void				SetIgnoreAnis			(const zBOOL b)		{ s_ignoreAnis = b;				};
	static	zBOOL				GetIgnoreAnis			()					{ return s_ignoreAnis;			};
	static	void				SetAutoConvertAnis		(const zBOOL b)		{ s_autoConvertAnis= b;			};
	static	zBOOL				GetAutoConvertAnis		()					{ return s_autoConvertAnis;		};
	static	void				S_SetAutoConvertMeshes	(const zBOOL b)		{ s_autoConvertMeshes= b;		};
	static	zBOOL				S_GetAutoConvertMeshes	()					{ return s_autoConvertMeshes;	};
	//
	zCModelPrototype	();

	//
	void						SetModelProtoName	(const zSTRING& name);
	const zSTRING&				GetModelProtoName	() const				{ return modelProtoName;							};
	const zSTRING&				GetModelProtoFileName() const;
	enum zTFileSourceType		{ zFROM_MDS, zFROM_ASC };
	void						SetFileSourceType	(zTFileSourceType sourceType);
	zTFileSourceType			GetFileSourceType	() const				{ return fileSourceType;							};

	zBOOL						LoadModelScript		(const zSTRING& filename);
	zBOOL						LoadModelScriptMSB	(const zSTRING& filename); 
	zBOOL						LoadModelASC		(const zSTRING& filename);
	void						SaveMDL				(const zSTRING& filename);
	void						DescribeTree		(zCTree<zCModelNode>* node=0, int indent=0);
	void						Load3DSMAXAsc		(const zSTRING& filename, zBOOL rani=TRUE, zBOOL rmesh=TRUE, zBOOL tree=TRUE);
	void						Load3DSMAXAsc		(zCModelAni*	&aniPtrOut,
													const zSTRING&	filename, 
													const zSTRING&	aniName,
													int				startFrame,
													int				lastFrame,
													int				maxImportFlags,						// use 'zTModelProtoImportMAXFlags'
//													zBOOL			rani, zBOOL rmesh, zBOOL rtree,
													zREAL			maxFps=-1);
	zCTree<zCModelNode>*		GetMeshTree			()					{ return &meshTree;			};
	zVEC3						GetRootNodeTrans	() const			{ return rootNodeTrans;		};	// in neutral resting pose
	zTBBox3D					GetBBox3D			() const			{ return bbox3D;			};
	zTBBox3D					GetBBox3DCollDet	() const			{ return bbox3DCollDet;		};
	zCModelPrototype*			GetBaseModelProto	() const			{ return baseModelProto;	};	// if used as overlay ModelProto
	const zCArray<zCModelNode*>&	GetNodeList		() const			{ return nodeList;			};
	const zCArraySort<zCModelAni*>&	GetAniList		() const			{ return protoAnis;			};

	//							
	void						SetAni				(int nr);
	zCModelAni*					SearchAni			(const zSTRING& aniName) const;
	int zCCFASTCALL 			SearchAniIndex		(const zSTRING& aniName) const;
	zCModelNode*				SearchNode			(const zSTRING& nodeName);
	zCTree<zCModelNode>*		FindMeshTreeNode	(const zSTRING& nodeName, zCTree<zCModelNode>* node=0);
	int							FindMeshTreeNodeIndex(const zSTRING& nodeName, zCTree<zCModelNode>* node=0);
	int							FindNodeListIndex	(const zSTRING& nodeName);
	void						GetModelEventList	(zCArray<zCModelAniEvent*>& eventArray) const { eventArray=modelEvents; };

	// beim anlegen neuer ModelPrototypes werden bereits im Speicher befindliche, von anderen ModelProtos
	// bereits genutzte Meshes & Anis gesucht und geshared.

	static zCModelPrototype*	Load				(const zSTRING& name, zCModelPrototype *baseModelProto=0);
	static zCModelPrototype*	SearchName			(zSTRING name);
	// iterators									
	static int					NumInList			();						// count Textures
	static zCModelPrototype*	GetFirstInList		()			{ return s_modelRoot; };
	zCModelPrototype*			GetPrevInList		() const	{ return prev; };
	zCModelPrototype*			GetNextInList		() const	{ return next; };

	// Sharing Protos, Reference-Counter
	// new	 : ref=1,
	// delete: nur möglich wenn ref>=1; (macht selbst refCtr--);
	int							GetRefCtr			() const { return refCtr; };
	zCModelPrototype*			AddRef				() { ++refCtr; return this; };
	int							Release				();
								
	//								
	static zDWORD				GetMDHFileVersion	();
	zBOOL						LoadMDH				(const zSTRING	&filename);
	zBOOL						LoadMDH				(zCFileBIN		&file);
	void						SaveMDH				(zCFileBIN		&file);
	void						SaveMDH				();

	static zDWORD				GetMDSFileVersion	();

private:

	static zBOOL				s_ignoreAnis;
	static zBOOL				s_autoConvertAnis;
	static zBOOL				s_autoConvertMeshes;
	static zCModelPrototype		*s_modelRoot;					// linked by internal linked list, shared objects !
	zCModelPrototype			*next;
	zCModelPrototype			*prev;
	int							refCtr;

	//
	zSTRING						modelProtoName;				// e.g. "human" (human.mds), filename, without extension, no path
	zSTRING						modelProtoFileName;			// e.g. "human.mds"        , filename, with	   extension, no path
	zCTree<zCModelNode>			meshTree;					// Hierarchie & limb-meshes
	zCArraySort<zCModelAni*>	protoAnis;
	zCArray<zCModelAniEvent*>	modelEvents;
	zCArray<zCModelNode*>		nodeList;					// linear nodeList => faster access, order important
	zDWORD						nodeListChecksum;			// checksum on nodeListNames: to guard against incompatible data from files

	zCArray<zCMeshSoftSkin*>	meshSoftSkinList;
	zSTRING						hierarchySourceASC;

	zTBBox3D					bbox3D;						// static bbox3D in objectSpace, neutral standing pose
	zTBBox3D					bbox3DCollDet;				// static bbox3D in objectSpace, neutral standing pose
	zCModelPrototype			*baseModelProto;			// if used as overlay ModelProto
	zPOINT3						rootNodeTrans;				// for construction of bbox3
	zTFileSourceType			fileSourceType;

	zCArray<zCMesh*>			sourceMeshSoftSkinList;		// used while converting from MAX to internal format

	~zCModelPrototype();
	zCModelPrototype(const zCModelPrototype&);				// disable
	zCModelPrototype& operator=(const zCModelPrototype&);	// disable

	//
	void						Init						();
	void						Clear						();

	void						CalcNodeListChecksum		();
	zBOOL						PrepareAsModelProtoOverlay	(zCModelPrototype *baseModelProto);
	void						CopyNodeTreeFrom			(zCModelPrototype *baseModelProto);
	void						CopyNodeTreeFrom_R			(zCTree<zCModelNode> *srcNode, zCTree<zCModelNode> *destNode);
	void						ResolveReferences			();
	void						ReleaseMeshes				();
	void						ReleaseMeshSoftSkinList		();
	void						CalcAniBBox					(zCModelAni* ani);	// calcs one BBox3D for complete animation (preprocessing)

	///////////////////
	// .ASC PARSING
	///////////////////

	//
	struct zTMatIDList;

	void CollectNodeMeshes				(zCArray<zCModelNode*> &protoNodeList);
	void TraverseDelMeshTree			(zCTree<zCModelNode>* modelNode);
	//
	void SkipBlock						();
	void SkipBlockCmt					();
	void ReadComment					();
	void ReadScene						(zREAL &frameSpeed);
	void ReadMaterialList				();
	void ReadGeomobject					(zMATRIX4* &trafoList, zCTree<zCModelNode>* &newmnode);
		zCMaterial* ReadWireframeColor	();
		zCMaterial* ReadMaterial		();
			void ReadMapDiffuse			(zCMaterial *mat);
		zMATRIX4	ReadNodeTM			(zCModelNode *mnode);
			zVEC3 ReadTriple			();
		void		ReadMeshAnimation	(zCModelNode* mnode, int matRef);
		zCMesh*		ReadMesh			(zBOOL softSkin, zCModelNode *node, int matRef);
			void	ReadVertexList		(zCMesh *mesh, int _numVert);
			zTMatIDList* ReadFaceList	(zCMesh *mesh, int _numPoly);
			zVEC2*	ReadTVertexList		(int _numTVert);
			void	ReadTFaceList		(zCMesh *mesh, zVEC2 *uvList, int _numTPoly);
		void ReadTMAnimation			(zCModelNode *mnode, zMATRIX4* &trafoList);
			void ReadPosTrack			(zMATRIX4 *trafoList);
			void ReadRotTrack			(zMATRIX4 *trafoList);
	void ReadSoftSkinVertList			();

	void AssignMeshNodeMaterials		(zCMesh* mesh, zTMatIDList *matIDList, int matRef);
	void TransformNodeVisual			(zCModelNode* mnode, const zMAT4& trafo);
	void ProcessMeshNode				(zCModelNode* mnode, zCTree<zCModelNode> *parentNode, int matRef, zBOOL nodeMeshIsSoftSkin, zBOOL& deleteNode);
	void LocalizeTrafos					(zCTree<zCModelNode>* node, zCTree<zCModelNode>* parentNode);
	void ConvertMat4					(zMATRIX4& mat4);
	void ConvertVec3					(zPOINT3& vec3);
	void ConvertAngle					(zVALUE& angle);
	void AddAni							(zCModelAni *ani);
	// Load Model Script (MDS)
	void SkipBlockMDS					(int level=1);
	void	ReadModel					(zCFileBIN &file);
	zBOOL	ReadModelMSB				(zCFileBIN &file);
		void	ReadMeshEnum			();
		void	ReadMeshAndTree			(zBOOL &hasFlag_DONT_USE_MESH, zCFileBIN &file);
		zBOOL	ReadMeshAndTreeMSB		(zBOOL &hasFlag_DONT_USE_MESH, zCFileBIN &file);
		void RegisterMesh				(zCFileBIN &file);
//		void ReadStartMesh				();
		void	ReadAniEnum				(const zBOOL hasFlag_DONT_USE_MESH, zCFileBIN &file);
			void ReadAni				();
		zBOOL	ReadAniEnumMSB			(const zBOOL hasFlag_DONT_USE_MESH, zCFileBIN &file);

	friend zCModelAni;
	friend zCModelAniActive;
	friend zCModel;
	friend zCModelMeshLib;
};

// ************************************************************************************************************
//   Model - Instance (Ani, Node, Model)
// ************************************************************************************************************

struct zTAniAttachment;

enum { zMDL_MAX_ANIS_PARALLEL		= 6 };
enum { zMDL_MAX_MESHLIBS_PARALLEL	= 4 };

class zENGINE_API zCModelAniActive {
public:
	//
	zCModelAniActive();
	~zCModelAniActive();

	// methods
	void				SetDirection		(zTMdl_AniDir dir);
	zTMdl_AniDir		GetDirection		() const					{ return (advanceDir==-1) ? zMDL_ANIDIR_REVERSE : zMDL_ANIDIR_FORWARD; };
	zREAL				GetProgressPercent	() const;
	void				SetProgressPercent	(const zREAL percent);
	zREAL				GetActFrame			() const					{ return actFrame; };
	void				SetActFrame			(const zREAL newFrame);

	void				SetCombineAniXY		(zREAL xc, zREAL yc)		{ combAniX=xc; combAniY=yc; };
	void				GetCombineAniXY		(zREAL& xc, zREAL& yc) const{ xc=combAniX; yc=combAniY; };
	void				DoCombineAni		(zCModel *hostModel, int frame, int nextFrame=-1);
	void				SetNextAni			(zCModelAni* modelAni)		{ nextAni = modelAni;					};
	zREAL				GetBlendInSpeed		() const					{ return blendInOverride;				};
	zREAL				GetBlendOutSpeed	() const					{ return blendOutOverride;				};
	void				SetBlendInOverride	(const zVALUE blendIn )		{ blendInOverride  = blendIn;			};
	void				SetBlendOutOverride	(const zVALUE blendOut)		{ blendOutOverride = blendOut;			};
	
	zBOOL				IsUnused			() const					{ return protoAni==0;					};
	void				MarkUnused			()							{ protoAni=0;							};

	zBOOL				IsStateAni			() const					{ return protoAni->aniName[0]=='S';		};
	zBOOL				IsTransAni			() const					{ return protoAni->aniName[0]=='T';		};
	int					GetLayer			() const					{ return protoAni->layer;				};
	zBOOL				IsFadingOut			() const					{ return isFadingOut;					};

	zCModelAni*			GetAni				() const					{ return protoAni;						};

private:
	zCModelAni			*protoAni;
	zCModelAni			*nextAni;

	int					advanceDir;			// STATE
	zREAL				actFrame;			// STATE
	int					actAniEvent;		// STATE
	zREAL				combAniX, combAniY;

	zBOOL				isFadingOut;
	zBOOL				isFirstTime;
						
	zCModelAni			*nextAniOverride;	// STATE
	zVALUE				blendInOverride;
	zVALUE				blendOutOverride;
						
	// trans/rot of the root-node that affects the host-vob
	zPOINT3				lastPos;			// STATE for 'M' flag
	zPOINT3				thisPos;
	zCQuat				lastRotQuat;		// STATE for 'R' flag
	zCQuat				thisRotQuat;
	zCQuat				freezeRotQuat;		// rot at the first frame, later differences=>vob
	zBOOL				rotFirstTime;
	zVALUE				transWeight;		// weight for both trans/rot (blending of motion-root-mode, once per ani)

	// aniAttachments
	zTAniAttachment		*aniAttachment;
	zREAL				randAniTimer;

	friend zCModel;
	friend zCModelNodeInst;
};

// =====================================================================================

class zENGINE_API zCModelTexAniState {
public:
	zCModelTexAniState();
	~zCModelTexAniState();
	void				UpdateTexList			();
	void				DeleteTexList			();
	void				SetChannelVariation		(const int channel, const int varNr, zSTRING* texNamePart=0);

	// building texList
	void				BuildTexListFromMeshLib (zCModelMeshLib *meshLib);
	void				BuildTexListFromMesh	(zCMesh *mesh);
	void				BuildTexListFromProgMesh(zCProgMeshProto *pmesh);

	void				AddTexListFromMeshLib	(zCModelMeshLib *meshLib, zCArray<zCTexture*> &texList); 
	void				AddTexListFromMesh		(zCMesh			*mesh	, zCArray<zCTexture*> &texList);
	void				AddTexListFromProgMesh	(zCProgMeshProto*pmesh	, zCArray<zCTexture*> &texList);
	void				FinishTexList			(zCArray<zCTexture*> &texList);

protected:
	// Texture animation/combination for node-mesh
	enum				{ zMDL_MAX_ANI_CHANNELS = 2, zMDL_MAX_TEX = 4 };
	int					numNodeTex;
	zCTexture			**nodeTexList;
	int					actAniFrames[zMDL_MAX_ANI_CHANNELS][zMDL_MAX_TEX];
};

// =====================================================================================

#pragma pack (push, 1)
class zENGINE_API zCModelNodeInst {
public:
	// methods			
	zCModelNodeInst		();
	zCModelNodeInst		(zCModelNode *mnode); 
	~zCModelNodeInst	();
	void				InitByModelProtoNode(zCModelNode *mnode);

	// Ani-Blending
	void				AddNodeAni			(zCModelAniActive *modelAni);
	void				RemoveAllNodeAnis	();
	void				RemoveNodeAni		(zCModelAniActive *modelAni);
	void				FadeOutNodeAni		(zCModelAniActive *modelAni);
	int					GetNodeAniListIndex (const zCModelAniActive *modelAni) const;
	void				FindMasterAni		();
	void				CalcWeights			(zCModel *model);
	void				CalcBlending		(zCModel *model);

	// misc
	zCVisual*			GetNodeVisual		() const	{ return nodeVisual;	};
	void				SetNodeVisualS		(zCVisual *visual, zBOOL animated=FALSE);
	zTBBox3D			GetBBox3DNodeWorldS	() const	{ return bbox3D;		};
	zCModelNodeInst*	GetParentNode		() const	{ return parentNode;	};
	zBOOL				IsRootNode			() const	{ return (GetParentNode()==0);	};
	zCModelNode*		GetProtoNode		() const	{ return protoNode;				};
	zMATRIX4&			GetTrafoObjToCam	()			{ return trafoObjToCam;			};

private:
	zCModelNodeInst		*parentNode;
	zCModelNode			*protoNode;
	zCVisual			*nodeVisual;
	zMATRIX4			trafo;										// STATE (reprod), local=>parent 
	zMATRIX4			trafoObjToCam;								// STATE (reprod)
	zTBBox3D			bbox3D;										// STATE (reprod), worldSpace
//	zTFrameCtr			lastTimeBBox3DUpdated;

	// Texture animation/combination for node-mesh
	zCModelTexAniState	texAniState;

	// ani-blending
	enum				{ zMDL_BLEND_STATE_FADEIN, zMDL_BLEND_STATE_CONST, zMDL_BLEND_STATE_FADEOUT };
	struct zTNodeAni {
		zCModelAniActive*modelAni;									// STATE 
		zVALUE			weight;										// STATE 
		zVALUE			weightSpeed;								// STATE , percent per seconds (0.5 = 50%)
		int				blendState;									// STATE 
		zCQuat			quat;										// %
	};
	zTNodeAni			nodeAniList [zMDL_MAX_ANIS_PARALLEL];		// STATE 
	int					numNodeAnis;								// STATE 
	int					masterAni;									// STATE 
	zVALUE				masterAniSpeed;								// STATE 

	// ani-blending
	void				AddToNodeAniWeight	(const int i, const zVALUE delta);
	void				Init				();
	friend zCModel;
};
#pragma pack (pop)

// =====================================================================================

// Ani Attachments

// random anis
struct zTRandAni { 
	zTModelAniID			randAniProtoID;
	int						prob;
};

struct zTAniAttachment { 
	// attached to..
	zTModelAniID			aniID;

	// random anis
	zCArray<zTRandAni>		randAniList;
	zREAL					randAniFreq;
	int						randAniProbSum;

	// ..
};

class zENGINE_API zCModel : public zCVisualAnimate {
	zCLASS_DECLARATION (zCModel)
private:
	// childVob/modelNode Attachments
	typedef struct {
		zCVob				*vob;
		zCModelNodeInst		*mnode;
	} zTMdl_NodeVobAttachment;		
									
	typedef struct {				
		zCVob				*vob;
		zREAL				vobFXHandle;
	} zTMdl_StartedVobFX;			
									
	typedef struct {				
		zCModelAniActive	*ani;
		zCModelMeshLib		*meshLib;
	} zTAniMeshLibEntry;			
						
	// associates a zCModelMeshLib object resource with it's texture animation state
	typedef struct {				
		zCModelTexAniState	texAniState;
		zCModelMeshLib		*meshLib;
	} zTMeshLibEntry;

public:								


	static  zBOOL		S_GetSmoothRootNode		()					{ return s_bSmoothRootNode;		};
	static  void		S_SetSmoothRootNode		(const zBOOL b)		{ s_bSmoothRootNode = b;		};

	zCModel				() { Init(); };
	zCModel				(zCModelPrototype* baseModelProto);
	zCModel				(const zSTRING& modelFilename);

	// zCVisual interface
	zBOOL				Render					(zTRenderContext& renderContext);
	zBOOL				IsBBox3DLocal			() { return TRUE; };				// OS / WS
	zTBBox3D			GetBBox3D				();
	zSTRING				GetVisualName			();
	void				SetVisualUsedBy			(zCVob* vob);
//	void				GetLODVisualAndAlpha	(const zREAL distToCam, zCVisual* &vis, zREAL& alpha);
	zDWORD				GetRenderSortKey		() const;
	// traceRay, ray and report defined in objectSpace
	zBOOL				CanTraceRay				() const		{ return TRUE; };	// gives a call to TraceRay() useful infos/allowed?
	zBOOL				TraceRay				(	const zVEC3&		rayOrigin, 
													const zVEC3&		ray, 
													const int			traceFlags, 
													zTTraceRayReport	&report);
	void				HostVobRemovedFromWorld	(zCVob* hostVob, zCWorld* hostWorld);
//	void				HostVobAddedToWorld		(zCVob* hostVob, zCWorld* hostWorld);
						
	// zCVisualAnimate interface
	void				StartAnimation			(const zSTRING& aniName)	{ StartAni (aniName, zMDL_STARTANI_DEFAULT);};
	void				StopAnimation			(const zSTRING& aniName)	{ StopAni	(GetAniIDFromAniName(aniName));	};
	zBOOL				IsAnimationActive		(const zSTRING& aniName)	{ return IsAniActive (aniName);				};
	const zSTRING*		GetAnyAnimation			();
	const zCVob*		GetHomeVob				() const					{ return homeVob;							};
//	void				StartAnyAnimation		();

	// firstperson
	zBOOL				GetDrawHandVisualsOnly  () const					{ return m_bDrawHandVisualsOnly;			};
	void				SetDrawHandVisualsOnly	(const zBOOL b)				{ m_bDrawHandVisualsOnly = b;				};

	// lighting			
	enum				{ zMDL_DYNLIGHT_SCALEPRELIT=0, zMDL_DYNLIGHT_EXACT=1 };	// ATT: keep bitfield-size in sync!
	void				SetDynLightMode			(const int mode);
	int					GetDynLightMode			() const					{ return dynLightMode; };
												
	// Anis										
	void				AdvanceAnis				();
	void	zCCFASTCALL	AdvanceAni				(zCModelAniActive* ani, zBOOL& overflowed);
	zVEC3				GetLastPosDelta			() const						{ return vobTrans;	};
	zCQuat				GetLastRotDelta			() const						{ return vobRot;	};
	zBOOL				GetDoRotateVob			() const						{ return doVobRot;	};
	zVEC3				GetVelocity				() const						{ return modelVelocity; };
	zVEC3				GetVelocityRing			() const;
	void				ResetVelocity			();
	zPOINT3				GetRootPosLocal			() const						{ return rootPosLocal;	};
	void	zCCFASTCALL	RecalcRootPosLocal		(const zBOOL selectHighestY=TRUE);
	zPOINT3				GetRootNodeTrans		() const						{ return modelProtoList[0]->GetRootNodeTrans(); };	// in neutral resting pose
	void				GetOccuredAniEventList	(zCArray<zCModelAniEvent*>& aniEventArray) { aniEventArray=occuredAniEvents; };
	void				SetAniTransScale		(const zVEC3& s)				{ aniTransScale=s;			};
	zVEC3				GetAniTransScale		() const						{ return aniTransScale;		};
	zVEC3				GetAniTrans				(zCModelAni* protoAni, int frameNumber, int nodeNumber) const { return Alg_Prod(modelScale, protoAni->GetTrans(frameNumber, nodeNumber)); };
	zVEC3				GetAniTransLerp         (zCModelAni* protoAni, zREAL progress, int nodeNumber) const;
	zBOOL				GetSmoothRootNode		() const						{ return m_bSmoothRootNode;	};
	void				SetSmoothRootNode		(const zBOOL a_bSmoothRootNode) { m_bSmoothRootNode = a_bSmoothRootNode;	};
						
	enum				{ zMDL_STARTANI_DEFAULT, zMDL_STARTANI_ISNEXTANI, zMDL_STARTANI_FORCE };
	void				StartAni				(zTModelAniID	aniID	 , const int startMode=zMDL_STARTANI_DEFAULT);
	void				StartAni				(zCModelAni		*modelAni, const int startMode=zMDL_STARTANI_DEFAULT);
	void				StartAni				(const zSTRING& aniName  , const int startMode=zMDL_STARTANI_DEFAULT);
	void				StopAni					(zTModelAniID	aniID);
	void				StopAni					(zCModelAni		*modelAni);
	void				StopAni					(zCModelAniActive *activeAni);
	inline zBOOL		IsAniActive				(const zSTRING& aniName);
	inline zBOOL		IsAniActive				(zCModelAni		*modelAni);
	inline zBOOL		IsAniActive				(zTModelAniID	aniID);
	// gdw. dieser state der einzige aktive state ist & keine transition aktiv ist (alles im selben Layer)
	inline zBOOL		IsStateActive			(const zSTRING&		aniName) const;
	zBOOL				IsStateActive			(const zCModelAni*	modelAni) const;
	inline zBOOL		IsStateActive			(zTModelAniID		aniID) const;
						
	inline zCModelAni*	GetAniFromAniID			(const zTModelAniID aniID) const;
	inline zCModelAni*	GetAniFromAniName		(const zSTRING& aniName) const;
	inline zTModelAniID	GetAniIDFromAniName		(const zSTRING& aniName) const;

	inline zCModelAni*	GetNextAni				(zCModelAni* modelAni) const;
	zCModelAniActive*	GetActiveAni			(zTModelAniID aniID) const;
	zCModelAniActive*	GetActiveAni			(zCModelAni* modelAni) const;
						
	zCModelNodeInst*	SearchNode				(const zSTRING& nodeName);
	const zCArray<zCModelNodeInst*>& GetNodeList	() const						{ return nodeList;		};
	int					GetNumActiveAnis		() const						{ return numActiveAnis; };
												
	void				SetLerp					(const zBOOL lerp)				{ lerpSamples = lerp;	};
	zBOOL				GetLerp					() const						{ return lerpSamples;	};
	void				SetIsFlying				(const zBOOL fly)				{ isFlying = fly;		};
	zBOOL				GetIsFlying				() const						{ return isFlying;		};
	void				SetIsVisible			(const zBOOL visible)			{ isVisible = visible;	};
	zBOOL				GetIsVisible			() const						{ return isVisible;		};

	// Combine Textures/Meshes 
	// assert: names have to be UPCASE ! meshLib Names don't have file-extensions !
	zBOOL				ApplyMeshLib			(const zSTRING& meshLibName);
	zBOOL				RemoveMeshLib			(const zSTRING& meshLibName);
	void				RemoveMeshLibAll		();
	zBOOL				SetNodeMeshTexture		(const zSTRING& nodeName,	 const int channel, const int varNr, zSTRING* texNamePart=0);
	zBOOL				SetMeshLibTexture		(const zSTRING& meshLibName, const int channel, const int varNr, zSTRING* texNamePart=0);
						
	// misc				
	zCModelPrototype*	GetModelProto			() const { return modelProtoList[0]; };
	void				CalcNodeListBBoxWorld	();
	void				CalcModelBBox3DWorld	();
						
	void				CheckNodeCollision		(zCModel *model, zCModelNodeInst *weapNode, zMATRIX4& trafoThisToModel, zCList<zCModelNodeInst>& resNodeList);
	void				CheckNodeCollisionList	(const zCOBBox3D& obb, zMATRIX4& nodeCollisionMatrix);
	zMATRIX4			GetTrafoNodeToModel		(zCModelNodeInst* mnode);
//	zTBBox3D			GetBBox3DLocalFixed		() const { return modelProtoList[0]->bbox3D; };
	const zTBBox3D&		GetBBox3DLocalFixed		() const { return bbox3DLocalFixed; };
	const zTBBox3D&		GetBBox3DCollDet		() const { return bbox3DCollDet;	};
												
	// node access								
	zTBBox3D			GetBBox3DNodeWorld		(zCModelNodeInst* mnode);
	zPOINT3				GetNodePositionWorld	(zCModelNodeInst* mnode);
	void				SetNodeVisual			(zCModelNodeInst* mnode, zCVisual *visual, zBOOL animated=FALSE);

	// poly access
	void	zCCFASTCALL SetupLowestLOD			(zTRenderContext&			renderContext);
	int					GetLowestLODNumPolys	();
	zVEC3*				GetLowestLODPoly		(const int a_iPoly, zVEC3* &normal);
	zCMaterial*			GetMaterial				(const int a_iIndex);
	int					GetNumMaterials			() const;
												
	//											
	void				SetFatness				(const zREAL fatness)	{ this->fatness = fatness;	};	// units: cm, useful range -3..+3, default:0
	zREAL				GetFatness				() const				{ return fatness;				};
	void				SetModelScale			(const zVEC3& scale);
	zVEC3				GetModelScale			() const				{ return modelScale;			};
	void				SetTimeScale			(const zREAL scale)		{ timeScale=scale;				};
	zREAL				GetTimeScale			() const				{ return timeScale;				};

	// vob/node attachments
	// (Add calls AddRef() on childvob, Remove calls Release())
	void				AttachChildVobToNode	(zCVob* childVob, zCModelNodeInst* modelNode);
	void				RemoveChildVobFromNode	(zCVob* childVob);
	zCVob*				GetAttachedNodeVob		(zCModelNodeInst* modelNode);
	void				RemoveAllChildVobsFromNode();
	void				UpdateAttachedVobs		();
						
	//					
	void				FadeOutAnisLayerRange	(const int layerLow=2, const int layerHi=256);
	void				StopAnisLayerRange		(const int layerLow=2, const int layerHi=256);
	void				FadeOutAni				(zCModelAniActive	*modelAni);
	void				FadeOutAni				(zTModelAniID		aniID);
	void				FadeOutAni				(zCModelAni			*protoAni);
	zBOOL				ApplyModelProtoOverlay	(zCModelPrototype	*proto);
	zBOOL				ApplyModelProtoOverlay	(const zSTRING&		mdsFileName);
	zBOOL				HasAppliedModelProtoOverlay(zCModelPrototype *proto) const;
	zBOOL				HasAppliedModelProtoOverlay(const zSTRING&	mdsFileName) const;
	void				RemoveModelProtoOverlay (zCModelPrototype	*proto);
	void				RemoveModelProtoOverlay (const zSTRING&		mdsFileName);
						
	//					
	zREAL				GetProgressPercent		(const zSTRING& aniName) const;
	zREAL				GetProgressPercent		(zTModelAniID	aniID) const;
						
	void				SetCombineAniXY			(zTModelAniID aniID, zREAL  xc, zREAL  yc) const;
	zBOOL				GetCombineAniXY			(zTModelAniID aniID, zREAL& xc, zREAL& yc) const;

	// Ani Attachments (randAnis, ..)
	void				RemoveAniAttachment		(zTModelAniID aniID);
	void				RemoveAllAniAttachments	();
	void				RemoveAllVobFX			();


	zBOOL				CorrectAniFreezer		();

						
	// random-anis		
	void				SetRandAnisEnabled		(const zBOOL b);
	zBOOL				GetRandAnisEnabled		() const					{ return randAnisEnabled;	};
	void				DeleteRandAniList		(zTModelAniID aniID);
	void				InsertRandAni			(zTModelAniID aniID, zTModelAniID insertAniID, const int prob=int(1));
	zREAL				GetRandAniFreq			(zTModelAniID aniID) const;
	void				SetRandAniFreq			(zTModelAniID aniID, const zREAL freq);


	void				SetIsInMobinteraction	(const zBOOL b)				{ n_bIsInMobInteraction =b;	};
	zBOOL				GetIsInMobinteraction	() const					{ return n_bIsInMobInteraction;	};


	// znet, binary state packing/unpacking
	void				PackStateBinary			(zCBuffer& buffer);
	void				UnpackStateBinary		(zCBuffer& buffer);

#if 0
	// NodeShadow
	void				SetNodeShadowEnabled	(const zBOOL b) { nodeShadowEnabled=b; };
	zCArray<zREAL>		nodeShadowDim;			
	void				CalcNodeShadowDim		();
	void				RenderNodeShadow		();
#endif	
	
	// debug									
    void				ShowAniListAdd			(zCModelAni *ani);
    void				ShowAniList				(int x);
	void				PrintStatus				(int xpos=0, int ypos=6000);
	static void			SetDrawSkeleton			(const zBOOL b)					{ s_drawSkeleton = b;		};
	static zBOOL		GetDrawSkeleton			()								{ return s_drawSkeleton;	};
												
	int								numActiveAnis;								// STATE
	zCModelAniActive				*aniChannels	[zMDL_MAX_ANIS_PARALLEL];	// STATE
	zCModelAniActive				*activeAniList;								// STATE

protected:
	// zCVisual interface								
	const zSTRING*					GetFileExtension	(int i);
	zCVisual*						LoadVisualVirtual	(const zSTRING& visualName) const;

private:										
	static zBOOL					s_drawSkeleton;
	static zBOOL					s_bSmoothRootNode;
	static int						s_iNumSoftSkinPoly[20];
	zCArray<zTSoundHandle>			m_listOfVoiceHandles;	// list of sound-handles of voices
	//
	zCVob							*homeVob;
	zCArray<zCModelPrototype*>		modelProtoList;
	zCArray<zCModelNodeInst*>		nodeList;								// linear nodeList => faster access
	zCArray<zCMeshSoftSkin*>		meshSoftSkinList;
	zCArraySort<zTAniAttachment*>	aniAttachList;
	zCArray<zTMdl_NodeVobAttachment>attachedVobList;
	zCArray<zTMdl_StartedVobFX>		startedVobFX;
	zCArray<zTAniMeshLibEntry>		aniMeshLibList;
	zCArray<zTMeshLibEntry*>		meshLibList;
	zTFrameCtr						lastTimeBBox3DTreeUpdate;

	zCArray<zCModelAniEvent*>		occuredAniEvents;
									
	zTBBox3D						bbox3D;									// bbox3D in worldSpace
	zTBBox3D						bbox3DLocalFixed;						// bbox3D in objectSpace
	zTBBox3D						bbox3DCollDet;							// bbox3D in objectSpace
	zVALUE							modelDistanceToCam;
	zBOOL							n_bIsInMobInteraction;
									
	//								
	zREAL							fatness;
	zVEC3							modelScale;

	// update infos for Vob-Position
	zVEC3							aniTransScale;
	zPOINT3							rootPosLocal;
	zPOINT3							vobTrans;
	zPOINT3							vobTransRing;
	zBOOL							newAniStarted;
	zBOOL							m_bSmoothRootNode;
	zREAL							relaxWeight;

	// firstperson
	zBOOL							m_bDrawHandVisualsOnly;


	zCQuat							vobRot;
	zVEC3							modelVelocity;
	enum							{ zMDL_VELRING_SIZE = 8 };				// must be pow2
	int								actVelRingPos;
	zVEC3							modelVelRing[zMDL_VELRING_SIZE];
									
	struct {						
		zUINT8						isVisible				: 1;
		zUINT8						isFlying				: 1;
		zUINT8						randAnisEnabled			: 1;
		zUINT8						lerpSamples				: 1;
		zUINT8						modelScaleOn			: 1;
		zUINT8						doVobRot				: 1;
		zUINT8						nodeShadowEnabled		: 1;
		zUINT8						dynLightMode			: 1;
	};
	zREAL							timeScale;
						
	// debug			
    enum				{ MAX_ANIHISTORY = 16 };
    zCModelAni			**aniHistoryList;

	// methods
	virtual ~zCModel();			
	void				Init					();

	//					
	void				CopyProtoNodeList		();
	void				DoAniEvents				(zCModelAniActive *ani);
	void				AssertActiveAniListAlloced () { if (!activeAniList)	activeAniList = zNEW(zCModelAniActive) [zMDL_MAX_ANIS_PARALLEL]; };
	void	zCCFASTCALL	RenderNodeList			(zTRenderContext& renderContext, zCArray<zMAT4*> &nodeTrafoList, zCRenderLightContainer &renderLightCont, const zTPMLightingMode lightingMode);
	void				RemoveStartedVobFX		(zCVob* vobFX);

	// Ani-blending		
	void				CalcNodeListAniBlending ();
	void				GetAniMinMaxWeight		(zCModelAniActive *modelAni, zVALUE& min, zVALUE& max);
	void				CalcTransBlending		();
												
	// znet										
	void				psb_WriteAniBlock		(zCBuffer& b, const int aniNr, const int level) const;
	void				psb_ReadAniBlock		(zCBuffer& b, const int level, zCModelAniActive* ani);

	// meshLib
	void				AddAniMeshLib			(zCModelAniActive *ani, zCModelMeshLib *meshLib);
	void				RemoveAniMeshLib		(zCModelAniActive *ani);
	void				ApplyAniMeshLibList		();
	void				UpdateMeshLibTexAniState();

	// AniAttachments (randAnis..)
	static int			AniAttachmentCompare	(const void* ele1,const void* ele2);
	zTAniAttachment*	SearchAniAttachList		(zTModelAniID aniID) const;
	zTAniAttachment*	GetCreateAniAttachment	(zTModelAniID aniID);

	zCModel(const zCModel&);				// disable
	zCModel& operator=(const zCModel&);		// disable

	friend zCModelAniActive;
	friend zCModelMeshLib;
	friend zCModelPrototype;
};

// zCModel inlines 

inline zCModelAni* zCModel::GetAniFromAniID (const zTModelAniID aniID) const {
	if (aniID==zMDL_ANI_ID_ILLEGAL)	return 0;
	// walk overlays, start with last
	int i=modelProtoList.GetNum()-1;
	do {
		if (modelProtoList[i]->protoAnis[aniID])	
			return modelProtoList[i]->protoAnis[aniID];
	} while (i--);
	return 0;
};

inline zCModelAni* zCModel::GetAniFromAniName (const zSTRING& aniName) const {
	return GetAniFromAniID (GetAniIDFromAniName(aniName));
};

inline zTModelAniID zCModel::GetAniIDFromAniName (const zSTRING& aniName) const {
#ifdef _DEBUG
	if (modelProtoList.GetNumInList()==0) return zMDL_ANI_ID_ILLEGAL;
#endif
	zCModelAni *ani = modelProtoList[0]->SearchAni	(aniName);
	if (!ani)	return zMDL_ANI_ID_ILLEGAL;
	else		return ani->GetAniID();
};

inline zCModelAni* zCModel::GetNextAni (zCModelAni* modelAni) const {
	// Overlay..
	if (!modelAni->nextAni)	
	{
		// tatsaechlich keine NextAni angegeben?
		if (modelAni->GetAniName().Length()<=0) return 0;

		// Diese Ani hat in diesem ModelProto keine nextAni. Falls alerdings im .MDS explizit eine NextAni
		// angegeben wurde und dieses ModelProto als Overlay benutzt wurde, kann/sollte es sein, dass die nextAni 
		// ueber ein tiefer liegendes ModelProto aufgeloest werden kann.
		// In diesem Fall wird die im baseModelProto eingetragene nextAni genommen. Diese kann theoretisch von der im 
		// Overlay spezifizierten abweichen, sollte es aber nicht.
		const zTModelAniID aniID= modelAni->GetAniID();
		modelAni				= modelProtoList[0]->protoAnis[aniID];
		if (!modelAni->nextAni)	return 0;
	};

	return GetAniFromAniID (modelAni->nextAni->GetAniID());
};

inline zBOOL zCModel::IsAniActive (zCModelAni *ani) 
{
	if (ani) 
	{
		for (int i=0; i<numActiveAnis; i++)
		{
			if (aniChannels[i]->protoAni==ani)	return TRUE;
		};
	};
	return FALSE;
};

inline zBOOL zCModel::IsAniActive (zTModelAniID aniID)
{
	return IsAniActive (GetAniFromAniID (aniID));
};

inline zBOOL zCModel::IsAniActive (const zSTRING& aniName) {
	return IsAniActive (GetAniFromAniName(aniName));
};

inline zBOOL zCModel::IsStateActive (const zSTRING& aniName) const {
	return IsStateActive (GetAniFromAniName (aniName));
};

inline zBOOL zCModel::IsStateActive (zTModelAniID aniID) const
{
	return IsStateActive (GetAniFromAniID(aniID));
};

// =======================================================================================================================

// Callback class that converts model-engine source data into compiled data

class zCModelConvertFileHandler : public zCScanDirFileHandler
{
public:
	zCModelConvertFileHandler();

	virtual zBOOL HandleFile(const zSTRING& fname, const char* directory, _finddata_t fileinfo);	
};

// =======================================================================================================================

#endif
