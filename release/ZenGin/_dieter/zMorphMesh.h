/******************************************************************************** 
 
     $Workfile:: zMorphMesh.h         $                $Date:: 31.01.01 5:47    $
     $Revision:: 15                   $             $Modtime:: 31.01.01 5:16    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
  C++ animated, layered morphing of 3D-Meshes
   created       : 1.3.99

 * $Log: /current_work/zengin_work/_Dieter/zMorphMesh.h $
 * 
 * 15    31.01.01 5:47 Hildebrandt
 * 
 * 14    4.12.00 18:41 Hildebrandt
 * 
 * 12    4.12.00 17:29 Hildebrandt
 * 
 * 11    17.11.00 1:29 Hildebrandt
 * 
 * 10    21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 * 
 * 9     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 8     6.07.00 13:45 Hildebrandt
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 5     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 4     16.11.99 19:49 Hildebrandt
 * 
 * 3     9.11.99 18:42 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 15 $ ($Modtime: 31.01.01 5:16 $)

// =======================================================================================================================

#ifndef __ZMORPHMESH_H__
#define __ZMORPHMESH_H__

#ifndef __Z3D_H__
#include <z3d.h>
#endif

#ifndef __ZPROGMESH_H__
#include <zProgMesh.h>
#endif

#ifndef __ZMODEL_H__
#include <zModel.h>
#endif

class zCMorphMeshProto;
class zCMorphMeshAni;
class zCMorphMesh;

// ============================================================================================

class zCMorphMeshAni {
public:
	zCMorphMeshAni();
	~zCMorphMeshAni();

	const zSTRING&			GetName			() const { return aniName;	};
	int						GetLayer		() const { return layer;	};
	void					SetBlending		(const zVALUE blendInSec, const zVALUE blendOutSec);
	void					SetFlagsByString(const zSTRING& flagString);

protected:
	zSTRING					aniName;
	zSTRING					ascName;
	zREAL					blendInSpeed;
	zREAL					blendOutSpeed;
	zREAL					holdTime;
	int						layer;
	zREAL					fpsRate;
	struct {
		zUINT8				discontinuity	: 1;
		zUINT8				looping			: 1;
		zUINT8				shape			: 1;
		zUINT8				refShape		: 1;
	} flags;

	int						numVert;
	int						*vertIndexList;
	int						numFrames;
	zPOINT3					*vertPosMatrix;		// x= verts, y= frames

	friend zCMorphMeshProto;
	friend zCMorphMesh;

private:
	zCMorphMeshAni(const zCMorphMeshAni&);					// disable
	zCMorphMeshAni& operator=(const zCMorphMeshAni&);		// disable

	void					Load			(zCFileBIN& file);
	void					Save			(zCFileBIN& file);
};	

// ============================================================================================

class zCMorphMeshProto {
public:
	static zCMorphMeshProto* Load			(const zSTRING& name);			// without file extension !
	static zCMorphMeshProto* SearchName		(const zSTRING& name);			// without file extension !
	static zBOOL			GetAutoConvertBinaryFiles ()				{ return autoConvertBinaryFile; };
	static void				SetAutoConvertBinaryFiles (const zBOOL b)	{ autoConvertBinaryFile = b;	};

	//
	zCMorphMeshProto();
	const zSTRING&			GetProtoName	() const					{ return morphProtoName;	};
	void					SetProtoName	(const zSTRING& name)		{ morphProtoName=name;		};
	zCMorphMeshAni*			SearchAni		(const zSTRING& aniName);

	// Sharing Protos, Reference-Counter
	int						GetRefCtr		() const { return refCtr; };
	zCMorphMeshProto*		AddRef			() { ++refCtr; return this; };
	int						Release			();

	//
	zBOOL					LoadMMB			(const zSTRING& fileName);
	void					SaveMMB			(const zSTRING& fileName);
	void					LoadMorphScript (const zSTRING& name);

protected:
	static zBOOL			autoConvertBinaryFile;
	static zCMorphMeshProto	*morphRoot;
	zCMorphMeshProto		*next;
	zCMorphMeshProto		*prev;
	int						refCtr;

	zSTRING					morphProtoName;			// e.g. "face" (face.mms), filename, without extension, no path
	zCProgMeshProto			*morphRefMesh;
	zPOINT3					*morphRefMeshVertPos;

//	zCMorphMeshAni			dummySearchAni;
	zCArraySort<zCMorphMeshAni*> aniList;

	//
	~zCMorphMeshProto();
	zCMesh*					Load3DSMAXAsc	(const zSTRING& ascName, zREAL &fpsRate, int firstFrame=0, int lastFrame=0);
	void					ReadMorphAni	(const zCArray<int> &posListRemap);
	void					ReadMorphRef	(zCArray<int>		&posListRemap);
	zCMorphMeshAni*			GenerateMorphAni(zCMesh *meshRoot, const zCArray<int> &posListRemap, zBOOL isRefShape);

private:
	zCMorphMeshProto(const zCMorphMeshProto&);					// disable
	zCMorphMeshProto& operator=(const zCMorphMeshProto&);		// disable
	zBOOL					m_bAlphaTestingEnabled;

	friend zCMorphMesh;
};

// ============================================================================================

class zCMorphMesh : public zCVisualAnimate {
	zCLASS_DECLARATION (zCMorphMesh)
public:
	struct zTMorphAniEntry {
		zCMorphMeshAni		*ani;
		zREAL				weight;
		zREAL				weightDest;
		zREAL				actFrame;
		int					actFrameInt;
		int					nextFrameInt;
		zREAL				frac;
		zREAL				blendInSpeed;
		zREAL				blendOutSpeed;
		zREAL				holdTime;
		int					blendState;
	};
public:
	// zCVisual interface
	zBOOL					Render				(zTRenderContext& renderContext);
	zBOOL					IsBBox3DLocal		() { return TRUE; };				// OS / WS
	zTBBox3D				GetBBox3D			();
	zCOBBox3D*				GetOBBox3D			() { return 0; };					// OS
	zSTRING					GetVisualName		();
	zDWORD					GetRenderSortKey	() const				{ return zDWORD(morphProto) | 0xD0000000; };	// while rendering vobs they are sorted by their visuals sort-key 

	// alpha testing
	virtual zBOOL			GetAlphaTestingEnabled()	const			{ return m_bUsesAlphaTesting;	};
	virtual void			SetAlphaTestingEnabled(const zBOOL a_btest)	{ m_bUsesAlphaTesting = a_btest; };

	// traceRay, ray and report defined in objectSpace
	zBOOL					CanTraceRay			() const				{ return TRUE; };	// gives a call to TraceRay() useful infos/allowed?
	zBOOL					TraceRay			(	const zVEC3&		rayOrigin, 
													const zVEC3&		ray, 
													const int			traceFlags, 
													zTTraceRayReport	&report);

	// zCVisualAnimate interface
	void					StartAnimation		(const zSTRING& aniName)	{ StartAni	(aniName); };
	void					StopAnimation		(const zSTRING& aniName)	{ StopAni	(aniName); };
	zBOOL					IsAnimationActive	(const zSTRING& aniName)	{ return IsAniActive (aniName); };
	const zSTRING*			GetAnyAnimation		();
	void					StartAnyAnimation	();			// useful if there is just one of them

	//
	static zCMorphMesh*		Load				(const zSTRING& name);
	zCMorphMesh				() { Init(); };
	zCMorphMesh				(zCMorphMeshProto* morphMeshProto);

	//
	zCMorphMeshAni*			SearchAni			(const zSTRING& aniName);
	void					StartAni			(zCMorphMeshAni	*ani	, zREAL intensity=zREAL(1.0F), zREAL holdTime=zREAL(-2));
	void					StartAni			(const zSTRING& aniName	, zREAL intensity=zREAL(1.0F), zREAL holdTime=zREAL(-2));
	void					StopAni				(zCMorphMeshAni	*ani);
	void					StopAni				(const zSTRING& aniName);
	void					FadeOutAni			(zCMorphMeshAni	*ani);
	void					FadeOutAni			(const zSTRING& aniName);
	zBOOL					IsAniActive			(zCMorphMeshAni	*ani);
	zBOOL					IsAniActive			(const zSTRING& aniName);

	//
	void					RemoveRandAni		(zCMorphMeshAni *ani);
	void					AddRandAni			(zCMorphMeshAni *ani, 
												 const zREAL timeMin, 
												 const zREAL timeMinVar, 
												 const zREAL timeMax, 
												 const zREAL timeMaxVar, 
												 const zREAL probMin);

	//
	zCProgMeshProto*		GetMorphMesh		() const	{ return morphMesh; };
	zBOOL					Render				(zTRenderContext&			renderContext, 
												 zCRenderLightContainer*	renderLightCont,
												 zREAL						fattness=0,
												 zREAL						scale=1);

	void					SetTextureVar		(const int channel, const int varNr, zSTRING* texNamePart=0);

	// debug
	void					PrintStatus			(int xpos=0, int ypos=6000);



protected:
	virtual ~zCMorphMesh	();					// use Release() instead!

	// zCVisual interface								
	const zSTRING*			GetFileExtension	(int i);
	zCVisual*				LoadVisualVirtual	(const zSTRING& visualName) const;

private:

	zCMorphMeshProto		*morphProto;
	zCProgMeshProto			*morphMesh;
//	zPOINT3					*morphMeshVertPos;
	zCMorphMeshAni			*refShapeAni;
	zCModelTexAniState		texAniState;
	enum {					zMORPH_BLEND_STATE_FADEIN,
							zMORPH_BLEND_STATE_CONST,
							zMORPH_BLEND_STATE_FADEOUT
	};

	zBOOL					m_bUsesAlphaTesting;

	zCArraySort<zTMorphAniEntry*>aniChannels;

	// random anis
	struct zTRandAni { 
		zREAL				randAniTimer;
		zCMorphMeshAni		*randAni;
		zREAL				randAniTimeMin;
		zREAL				randAniTimeMinVar;
		zREAL				randAniTimeMax;
		zREAL				randAniTimeMaxVar;
		zREAL				randAniProbMin;
	};
	zCArray<zTRandAni>		randAniList;

	//
	zCMorphMesh(const zCMorphMesh&);					// disable
	zCMorphMesh& operator=(const zCMorphMesh&);			// disable
	void					Init				();
	void					CalcVertPositions	();
	void					AdvanceAnis			();
	void					ProcessRandAnis		();
};

// =======================================================================================================================

// Callback class that converts model-engine source data into compiled data

class zCMorphMeshConvertFileHandler : public zCScanDirFileHandler
{
public:
	zCMorphMeshConvertFileHandler();

	virtual zBOOL HandleFile(const zSTRING& fname, const char* directory, _finddata_t fileinfo);	
};

// =======================================================================================================================

#endif