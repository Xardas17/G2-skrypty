/******************************************************************************** 
 
     $Workfile:: zModelProto.cpp      $                $Date:: 24.04.01 17:33   $
     $Revision:: 39                   $             $Modtime:: 17.04.01 19:58   $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Animierte hierarchische 3D-Models (Prototypes & MAX-Importer, .MAN bin-Format)
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zModelProto.cpp $
 * 
 * 39    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 38    15.03.01 2:17 Hildebrandt
 * 
 * 37    5.02.01 19:13 Hildebrandt
 * 
 * 36    3.02.01 2:11 Hildebrandt
 * 
 * 35    1.02.01 19:58 Moos
 * 
 * 34    1.02.01 0:00 Hildebrandt
 * 
 * 33    31.01.01 6:03 Hildebrandt
 * 
 * 32    31.01.01 5:47 Hildebrandt
 * 
 * 31    26.01.01 0:02 Hildebrandt
 * 
 * 30    25.01.01 5:07 Hildebrandt
 * 
 * 29    17.01.01 19:20 Hildebrandt
 * 
 * 28    8.01.01 17:55 Hildebrandt
 * 
 * 27    15.12.00 3:44 Hildebrandt
 * 
 * 26    13.12.00 18:14 Hildebrandt
 * 
 * 25    13.12.00 0:28 Hildebrandt
 * 
 * 24    11.10.00 19:45 Hildebrandt
 * 
 * 23    28.09.00 19:20 Hildebrandt
 * 
 * 22    21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 * 
 * 21    13.09.00 21:24 Hildebrandt
 * 
 * 20    11.09.00 19:40 Speckels
 * 
 * 19    8.09.00 16:47 Moos
 * 
 * 18    31.08.00 17:04 Hildebrandt
 * 
 * 17    16.08.00 18:18 Hildebrandt
 * fixes for zCModelProtoType cleanups (Release() on 0-Ptr)
 * 
 * 16    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    9.08.00 17:12 Admin
 * 
 * 15    21.07.00 15:11 Hildebrandt
 * 
 * 14    21.07.00 14:28 Hildebrandt
 * 
 * 13    6.07.00 13:45 Hildebrandt
 * 
 * 8     10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 7     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 6     4.05.00 22:15 Hildebrandt
 * 
 * 5     4.05.00 20:17 Hildebrandt
 * zenGin 089e
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 17    22.03.00 21:07 Hildebrandt
 * 
 * 16    20.02.00 18:08 Hildebrandt
 * zenGin 087c
 * 
 * 15    18.02.00 19:47 Hildebrandt
 * fix for LoadModelASC() .mds/.asc problem
 * 
 * 14    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 12    13.01.00 17:35 Hildebrandt
 * .MDS loading: right .asc from "meshAndTree" is read
 * 
 * 11    11.01.00 20:59 Hildebrandt
 * zenGin 085b
 * 
 * 10    10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 9     10.12.99 17:48 Hildebrandt
 * fixed: wrong textures on models (illegal material sharing..)
 * 
 * 8     12/09/99 10:01p Hildebrandt
 * fixed LoadMDM/ApplyMeshLib problem
 * 
 * 7     13.11.99 1:10 Hildebrandt
 * 
 * 6     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 39 $ ($Modtime: 17.04.01 19:58 $)

#include <zCore.h>

#include <zModel.h>
#include "zoption.h"
#include <zFile3d.h>
#include <zSound.h>
#include <zParticle.h>

zCLASS_DEFINITION	(zCModelMeshLib	, zCObject	, zCLASS_FLAG_SHARED_OBJECTS, 0)

static const int	zMDL_ASC_FILE_VERS				= 104;
static const zVALUE zMDL_MAX_FPS					= 25; 
static const zREAL	zMDL_FLAG_INPLACE_MAXDIST		= zREAL(10.0F);		// eine Ani bekommt das Flag 'inPlace', wenn sie das Objekt nicht weiter als x cm fortbewegt
static const zREAL	zMDL_FLAG_STATICCYCLE_MAXDIST	= zREAL( 1.0F);		// eine Ani bekommt das Flag 'StaticCycle', wenn sie zyklisch ist und die Translation der RootNode das Objekt in einem kompletten Durchgang maximal x cm fortbewegt (epsilon)
static const char	zMDL_FILENAME_SEPARATOR			= '-';				// "HUMANS-S_RUN.MAN"

static const zREAL	zMDL_DEFAULT_RADIUS_EVENTSFXGRND= zREAL(1000.0F);
static const zREAL	zMDL_DEFAULT_RADIUS_EVENTSFX	= zREAL(2500.0F);
static const zREAL	zMDL_MAX_RADIUS_EVENTSFX		= zREAL(3500.0F);

static const zBOOL	READASC_SKIPMESH_BIP01			= TRUE;
static const zBOOL	READASC_SKIPMESH_ZSLOT			= TRUE;
static const zBOOL	READASC_SMOOTHMESH				= TRUE;

static const int	zMESH_DEFORM_MAX_LINKS_PARSED	= 16;
static const int	zMESH_DEFORM_MAX_LINKS			= 3;
static const zREAL	zMESH_DEFORM_MIN_WEIGHT			= zREAL(0.01F);		// 1%
static zBOOL s_bConvertNoLOD = FALSE;

#if 0
	inline static void Printm (const zSTRING s) { zerr.Message (s); };
#else
	inline static void Printm (const zSTRING s) { };
#endif

/*

*****************************************************************************************************

  .ASC Materialien:

	*MATERIAL_REF x						// x = nr des Materials (aus der globalMatList)
	*MESH_FACE_LIST {
		*MESH_MTLID y					// y = index des Submaterials eines Materials aus der globalMatList

	Falls ein Material SubMats hat, zaehlen nur die SubMats. Das �bergeordnete 'Multi-Material' hat
	keine Bedeutung

*****************************************************************************************************

  meshAndTree:
  - NodeTree mit Start trafo 
  - bbox

  - startMesh


	// Default im Script-Prototyp, erweitert/verfeinert in der Script-Instanz
	mdl_ResetRand	("state_ani");

	mdl_RandFreq	(0.8);
	mdl_AddRand		("state_ani", "rand_ani", prob);
	mdl_AddRand		("state_ani", "rand_ani", prob);


  aniDisable		("s_swim")
	ani				("s_stand"				1	"s_stand"		0.3	0.3	MI.	"stand.asc"			F	0	-1)

*****************************************************************************************************

	modelTag		("DEF_HIT_LIMB"	"ZS_RIGHTHAND")

	*eventTag		(0 "HIT_LIMB1"		"ZS_MOUTH")
	*eventTag		(0 "HIT_LIMB2"		"ZS_TAIL")
	*eventTag		(0 "SWAP_MESH"		"ZS_LONGSWORD" "ZS_RIGHTHAND")
	*eventTag		(0 "SFX"			"HUMAN_LIFT_OBJECT")
	*eventTag		(0 "SFX_GRND"		"HUMAN_RUN_LEFT")

	*eventSFX		(0 "HUMAN_LIFT_OBJECT")
	*eventSFXGrnd	(0 "HUMAN_RUN_LEFT")

  	*eventTag		(0 "HIT_LIMB2"		"BIP01 TAIL")
  	*eventTag		(0 "HIT_LIMB2"		"BIP01 TAIL")

	// stimmband, variation
	_voice_var

	- tag:
		- Ptr auf quellAni
		- frame-nr
		- tag-string
		- liste von arg-strings

	*eventSound		(frameNr "stepping.wav" prob)
	*eventSwapMesh	(0 "zs_LongSword" "zs_RightHand")


  Statistik (Nodes/Frames, bei denen die Translation animiert ist):
  - 7500 von 17000 (44%) Translationen sind verschieden=animiert
  - 500  von   763 (66%) Nodes haben eine animierte Translation

*****************************************************************************************************
  
Im currently writing an exporter that samples Character Studio transforms, for
a game engine.

I Use something like the following to get the nodes local TM.

parentTM = parent->GetNodeTM(t);
nodeTM = node->GetNodeTM(t);
localTM = nodeTM * Inverse(parentTM);

Ideally we want to convert the resultant matrix to just Rotations for our
animations and only store Position and Scale just once for each skeleton.

Unfortunately using decomp_affine() on the local matrices seems to produce a
scale axis that is varying throughout the animations. This is very slight but I then
cant just use the rotation output from decomp_affine() as I get slightly different
results from those in MAX. For example a run animation in MAX where the
knees are close, when exported the knees overlap! 

I have also tried using DecomposeMatrix()
but am unable to accurately reassemble the localTM from just rotations...

We really dont want to store the whole local matrix for each node, but at the
moment that seems the only way to exactly replicate Character Studio
animations.

Does anyone have any ideas how I can decompose my matrices into a more
compact form and still be able to accurately rebuild the matrix?

Or am I just missing something obvious?

Paul Douglas,
Confounding Factor

*********************************************************************************************

<< The problem is interpolating between keys. Sometimes two keys are very close, but the
interpolator insists on going "the long way around". Is this a bug in my interpolation code that
makes it choose the wrong arc over the 4D unit sphere, or is it an inherent problem? >> 

Have you studied Quat.cpp and its Slerp() implementation and compared it to yours? 

I searched in the MAX SDK help file and found..

Keyframe Interpolation in MAX

The function used for interpolation between keys depends on the type of controller. In
general, MAX uses cubic (polynomial of degree three) splines for interpolation. Rotations
are done using spherical linear interpolation (slerps). Registered developers who are
interested in the exact details of keyframe interpolation have the source code MAX uses
internally as part of the Debug SDK. The bezier interpolation code is available in
\MAXSDKDB\SDKSRC\INTERP.CPP and the TCB interpolation is in
\MAXSDKDB\SDKSRC\TCBINTRP.CPP. This code is not available for non-registered
developers. 

Several developers have tried to use the IKeyControl interface and then operate on the keys
to get and interpolate them in 'world space'. This is really an problematic thing to try do
because the keys are interdependent. For instance, consider scale keys. In world space
scale keys are dependent on the position and rotation of the controller as well as the parent
transformation. This is because first an object is scaled, then it is rotated, then its position is
applied, then the parent transformation is applied. So the scale is rotated. If you scale an
object along its X axis and then rotate it the scale becomes rotated. The scale is no longer
rotated about the world X axis, it's rotated about some other axis. This is normally what you
want, i.e. you don't want the object to rotate through the scaled spaced (this would cause it
to skew). So to talk about the scale in world space is a strange concept. 

Further, the interpolation of keys that are in world space is equally problematic. If keys are
put into world space, then interpolated in world space, the resulting animation will be very
different that what would be seen inside MAX. For example, consider an object that is
rotating 360 degrees about its local Z axis and is tilted at some arbitrary angle. If you
interpolate the way MAX does, all the interpolation is done in the local coordinate system.
Thus the object would rotate about its local Z axis (which is tilted). However if you were to
try to interpolate about in world space the rotation would occur about the world Z axis. The
object will still end up in the same place, but it will be a very different animation than what
MAX would have.

The bottom line is that developer need to understand the way MAX computes its node
transformation based on the keyframes and use the information to interpolate between keys
accordingly.

Jonas Ruikis
Developer Consulting Group
Kinetix

*********************************************************************************************

>I am creating an exporter for character studio for a game. I need to convert the data from
the right hand coordinate system of max to the left hand coordinate system...< 

Not too hard in most cases, just figure out which axes you need to negate, then do the same
thing on the vertices. You'll potentially have to reorder faces, too, to maintain the proper
vertex ordering so they'll get drawn.

>This I just can't get my head round for a hierarchical model such as a skeleton...< 

Easiest way would probably be to keep the "frames" all in 3DS format (i.e. right-handed)
until the instant that you export them. In my exporter I just load up my own data structures,
then on export export Vector(x, y, z) as Vector(3dsx, 3dsz, 3dsy). This is right, for our
engine, and as far as matrices go, it's just a matter of swapping the Y and Z rows, also.

tom! Eidetic, Inc. http://www.eidetic.com/ 

*********************************************************************************************
*/


static const zSTRING sep	= " \t";
static const zSTRING trenn	= " \t\r";
static const zSTRING skip	= " \t\r";


///////////////////////////////////////////////////////////////////////////
//     Model Node (Prototype)
///////////////////////////////////////////////////////////////////////////

zCModelNode::zCModelNode() {
	nodeName.Clear();
	parentNode		= 0;
	visual			= 0;
	trafo			= trafoObjToWorld = Alg_Identity3D();
	nodeTrafoList	= 0;
	lastInstNode	= 0;
	nodeRotAxis		= 0;
	nodeRotAngle	= 0;
	translation		= 0;
};

// copy constructor
zCModelNode::zCModelNode(const zCModelNode& src) 
{
	parentNode		= 0;
	nodeName		= src.nodeName;
	visual			= src.visual;		if (visual) visual->AddRef();
	trafo			= src.trafo;

	nodeRotAxis		= src.nodeRotAxis;
	nodeRotAngle	= src.nodeRotAngle;
	translation		= src.translation;
	trafoObjToWorld	= src.trafoObjToWorld;
	nodeTrafoList	= 0;
	lastInstNode	= 0;
};

zCModelNode::~zCModelNode() {
	zRELEASE (visual);
	parentNode			= 0;
	nodeTrafoList		= 0;
	lastInstNode		= 0;
};

void zCModelNode::SetNodeVisualS (zCVisual *vis) {
	if (vis==this->visual)	return;
	if (this->visual)		this->visual->Release();
	if (vis)				vis->AddRef();
	visual = vis;
};

///////////////////////////////////////////////////////////////////////////
//     Model Ani Sample
///////////////////////////////////////////////////////////////////////////

// Der ganze Aufwand mit 'samplePosRangeMin' und 'samplePosScaler' ist gemacht worden, damit
// die Animation die Daten mit groesst moeglichen Genauigkeit wieder entpacken kann. Das Packing
// der Positionsdaten ist somit pro Animation adaptiv.

zREAL	zTMdl_AniSample::samplePosRangeMin;
zREAL	zTMdl_AniSample::samplePosScaler;

// rotation
static const zREAL zMDL_SAMPLE_ROT_BITS			= zREAL(1<<16)-1.0F;
static const zREAL zMDL_SAMPLE_ROT_SCALER		= (zREAL(1.0F) / zMDL_SAMPLE_ROT_BITS) * zREAL(M_2PI);
static const zREAL zMDL_SAMPLE_QUAT_SCALER		= (zREAL(1.0F) / zMDL_SAMPLE_ROT_BITS) * zREAL(2.1);
static const zWORD zMDL_SAMPLE_QUAT_MIDDLE      = (1 << 15) - 1; 

// position
static const zREAL zMDL_SAMPLE_POS_BITS			= zREAL(1<<16)-1.0F;
static const zREAL zMDL_SAMPLE_POS_BITS_INV		= zREAL(1.0F) / zMDL_SAMPLE_POS_BITS;
/*
static const zREAL zMDL_SAMPLE_POS_RANGE_MIN	= -400.0F;				// Troll: -150 .. +850
static const zREAL zMDL_SAMPLE_POS_RANGE_MAX	= +800.0F;
static const zREAL zMDL_SAMPLE_POS_RANGE		= zMDL_SAMPLE_POS_RANGE_MAX-zMDL_SAMPLE_POS_RANGE_MIN;
static const zREAL zMDL_SAMPLE_POS_SCALER		= (zREAL(1.0F) / zMDL_SAMPLE_POS_BITS) * zMDL_SAMPLE_POS_RANGE;
*/

void zTMdl_AniSample::CalcSamplePosConstants (const zREAL transMin, const zREAL transRange) 
{
	samplePosRangeMin	= transMin;
	samplePosScaler		= zMDL_SAMPLE_POS_BITS_INV * transRange;
};

void zTMdl_AniSample::SetSamplePosConstants (const zREAL transMin, const zREAL transScaler) 
{
	samplePosRangeMin	= transMin;
	samplePosScaler		= transScaler;
};

void zTMdl_AniSample::Pack	(const zCQuat &quat, const zVEC3& trans) 
{
	PackQuat	(quat);
	PackTrans	(trans);
};

void zTMdl_AniSample::Unpack (zCQuat &quat, zVEC3& trans) const 
{
	UnpackQuat	(quat);
	UnpackTrans	(trans);
};

void zTMdl_AniSample::PackTrans	(const zVEC3& trans)
{
	const zREAL zMDL_SAMPLE_POS_RANGE_INV = zREAL(1.0F) / (samplePosScaler * zMDL_SAMPLE_POS_BITS);

	// position
	for (int i=0; i<3; i++) 
	{
		zREAL t		= trans[i];
//		zClamp		(t, zMDL_SAMPLE_POS_RANGE_MIN, zMDL_SAMPLE_POS_RANGE_MAX);

//		t			= (t + (-zMDL_SAMPLE_POS_RANGE_MIN)) / (zMDL_SAMPLE_POS_RANGE);	// 0..1
		t			= (t + (-samplePosRangeMin)) * (zMDL_SAMPLE_POS_RANGE_INV);	// 0..1
		position[i]	= zWORD(t*zMDL_SAMPLE_POS_BITS);
	};
};

void zTMdl_AniSample::UnpackTrans	(zVEC3& trans) const
{
	// position
	trans[0]	= float(position[0]) * samplePosScaler + samplePosRangeMin;
	trans[1]	= float(position[1]) * samplePosScaler + samplePosRangeMin;
	trans[2]	= float(position[2]) * samplePosScaler + samplePosRangeMin;
};

void zTMdl_AniSample::PackQuat	(const zCQuat &quat) 
{
	// rotation
    rotation[0] = zMDL_SAMPLE_QUAT_MIDDLE + int(quat.qx / zMDL_SAMPLE_QUAT_SCALER);
    rotation[1] = zMDL_SAMPLE_QUAT_MIDDLE + int(quat.qy / zMDL_SAMPLE_QUAT_SCALER);
    rotation[2] = zMDL_SAMPLE_QUAT_MIDDLE + int(quat.qz / zMDL_SAMPLE_QUAT_SCALER);

    if (quat.qw < 0)
        for(int i=2;i>=0;i--)
            rotation[i]=(zMDL_SAMPLE_QUAT_MIDDLE << 1) - rotation[i];
   
};

void zTMdl_AniSample::UnpackQuat (zCQuat &quat) const
{
	// rotation
    quat.qx = (int(rotation[0]) - zMDL_SAMPLE_QUAT_MIDDLE) * zMDL_SAMPLE_QUAT_SCALER;
    quat.qy = (int(rotation[1]) - zMDL_SAMPLE_QUAT_MIDDLE) * zMDL_SAMPLE_QUAT_SCALER;
    quat.qz = (int(rotation[2]) - zMDL_SAMPLE_QUAT_MIDDLE) * zMDL_SAMPLE_QUAT_SCALER;

    float len_q = quat.qx * quat.qx + quat.qy * quat.qy + quat.qz * quat.qz;

    if (len_q>1)
	{
		float l = float(1/sqrt(len_q));
//		float l = Alg_SqrtInvApprox(len_q);
        quat.qx *= l;
        quat.qy *= l;
        quat.qz *= l;
		quat.qw = 0;
		return;
    } else
	{
		quat.qw = float(sqrt(1-len_q));	
//		quat.qw = Alg_SqrtApprox (1-len_q);
		return;
	};
};

/*

// ALT: direkte Quat<=>Euler Konvertierung

void zTMdl_AniSample::PackQuat	(const zCQuat &quat) 
{
	// rotation
	zVEC3 euler;
	quat.QuatToEuler	(euler);
	for (int i=0; i<3; i++) {
		while (euler[i]<0)				euler[i] += zREAL(M_2PI);
		while (euler[i]>zREAL(M_2PI))	euler[i] -= zREAL(M_2PI);
		zClamp (euler[i], float(0), zREAL(M_2PI));

		euler[i]	/= zREAL(M_2PI);	// 0..1
		rotation[i]	= zWORD(euler[i]*zMDL_SAMPLE_ROT_BITS);
	};
};

void zTMdl_AniSample::UnpackQuat (zCQuat &quat) const
{
	// rotation
	zVEC3 euler;
	euler[0]	= float(rotation[0]) * zMDL_SAMPLE_ROT_SCALER;
	euler[1]	= float(rotation[1]) * zMDL_SAMPLE_ROT_SCALER;
	euler[2]	= float(rotation[2]) * zMDL_SAMPLE_ROT_SCALER;
	quat.EulerToQuat	(euler);
};
*/

///////////////////////////////////////////////////////////////////////////
//     Model Ani (Prototype)
///////////////////////////////////////////////////////////////////////////

zCModelAni::zCModelAni() 
{
	numFrames				= numNodes = 0;
	nodeList				= 0;
	aniSampleMatrix			= 0;
	numAniEvents			= 0;
	aniEvents				= 0;
	fpsRate					= 0;
	fpsRateSource			= 0;
	aniDir					= zMDL_ANIDIR_FORWARD;
	aniID					= 0;
	layer					= 0;
	blendInSpeed			= 0;
	blendOutSpeed			= 0;
							
	rootNodeIndex			=-1;
							
	nextAni					= 0;
	memset					(&aniFlags, 0, sizeof(aniFlags));
	aniBBox3DObjSpace.InitZero();

	//
	samplePosRangeMin		= 0;
	samplePosScaler			= 0;

	//
	SetAniType				(zMDL_ANI_TYPE_NORMAL);
	SetCollisionVolumeScale	(zREAL(1));
};

zCModelAni::~zCModelAni() 
{
	// Alias-Anis besitzen die Node/Ani-Daten nicht ! => kein Delete
	if (aniType!=zMDL_ANI_TYPE_ALIAS) {
		delete[] nodeList;			// nodes muss er nicht loeschen, nur die ptr drauf
		delete[] aniSampleMatrix;	
		delete[] aniEvents;			
	};
	nodeList		= 0;
	aniSampleMatrix = 0;
	aniEvents		= 0;

//	meshLib			= 0;
	nextAni			= 0;
};

/*
zBOOL zCModelAni::LoadResourceData()
{
	// zCResource Interface Method
	return TRUE;
};

zBOOL zCModelAni::ReleaseResourceData()
{
	// zCResource Interface Method
	return TRUE;
};

zDWORD zCModelAni::GetResSizeBytes()
{
	// zCResource Interface Method
	return sizeof(zTMdl_AniSample) * numFrames * numNodes;
};
*/

void zCModelAni::PrecacheAniEventData()
{
	// derzeit werden hier nur Sounds precached...
	for (int i=0; i<numAniEvents; i++)
	{
		const zTMdl_AniEventType aniEventType = aniEvents[i].aniEventType;
		if ((aniEventType==zMDL_EVENT_SOUND) || (aniEventType==zMDL_EVENT_SOUND_GRND))
		{
			const zCArray<zCSoundFX*>& soundList = aniEvents[i].soundList;
			for (int j=0; j<soundList.GetNum(); j++)
			{
				if (soundList[j])
					soundList[j]->CacheIn();
			};
			
		};
	};
};

zREAL zCModelAni::GetAniVelocity () const {
	// cm/msec
	const zREAL time	= GetAniTimeLength();
	if ((time==0) || (GetRootNodeIndex()<0))	return 0;
	const zREAL dist	= (GetTrans(numFrames-1, GetRootNodeIndex()) - GetTrans(0, GetRootNodeIndex())).Length();
	return (dist / time);
};

zVEC3 zCModelAni::GetAniTranslation	() const
{
	if (GetRootNodeIndex()<0)	return zVEC3(0);
	return GetTrans(numFrames-1, GetRootNodeIndex()) - GetTrans(0, GetRootNodeIndex());
};

static zREAL aniMaxFps	= -1;

void zCModelAni::AddTrafoMatrix (zMATRIX4 **intrafoMatrix) { 
	zREAL	step			= 1.0F;
	zREAL	srcNumFrames	= zREAL(numFrames);
	zREAL	actFrame;
	
	fpsRateSource=fpsRate;

//	if (srcNumFrames>1)
//	if (aniMaxFps!=-1)
//	if (fpsRate>aniMaxFps) 
	if ((srcNumFrames>1) && (aniMaxFps!=-1) && (fpsRate>aniMaxFps))
//	if (fpsRate>zMDL_MAX_FPS) 
	{
		step		= int(fpsRate) / aniMaxFps;
		fpsRate		= aniMaxFps;
//		numFrames	= int(zFloor (srcNumFrames * (zMDL_MAX_FPS / fpsRate)));
		numFrames	= 0;
		actFrame	= 0;
//		for (;actFrame<srcNumFrames; numFrames++, actFrame += step) {};
		while (actFrame<srcNumFrames) 
		{
			// FIXME: !!!!!!!!! MSVC++ ist ein krankes Stueck Scheisse !!!!!!
			if (actFrame>50000) zERR_WARNING("D: argel"); 
			numFrames++;
			actFrame += step;
		};
	};

	if ((numFrames*numNodes)<=0) {
		aniSampleMatrix=0;
		return;
	};
	
//	zREAL aniFpsScale	= zREAL(1.0F) / step;
	aniSampleMatrix		= zNEW(zTMdl_AniSample) [numFrames*numNodes];
	int trafoCtr;

	// minMax ermitteln (fuer Ani Packing)
	actFrame		= 0;
	trafoCtr		= 0;
	zREAL transMin	=+999999;
	zREAL transMax	=-999999;
	while (actFrame<srcNumFrames) 
	{
		int frame = int(zFloor(actFrame));
		for (int node=0; node<numNodes; node++) 
		{
			zVEC3	trans	= (intrafoMatrix[node][frame]).GetTranslation();
			for (int i=0; i<3; i++) 
			{
				transMin	= zMin (transMin, trans[i]);
				transMax	= zMax (transMax, trans[i]);
			};
			trafoCtr++;
		};
		actFrame += step;
	};
	if (transMin<=-999999)	{ 
		transMin	= 0.0F; transMax = +1.0F; 
	};
	zTMdl_AniSample::CalcSamplePosConstants (transMin, transMax-transMin);
	// diese Konstanten werden in der Ani persistent gespeichert !
	this->samplePosRangeMin	= zTMdl_AniSample::samplePosRangeMin;
	this->samplePosScaler	= zTMdl_AniSample::samplePosScaler;

	// Ani Daten packen
	actFrame		= 0;
	trafoCtr		= 0;
	while (actFrame<srcNumFrames) 
	{
		int frame = int(zFloor(actFrame));
		for (int node=0; node<numNodes; node++) 
		{
			zVEC3	trans		= (intrafoMatrix[node][frame]).GetTranslation();
			zCQuat	quat;
			quat.Matrix4ToQuat	(intrafoMatrix[node][frame]);
			quat.Unit			();
			aniSampleMatrix[trafoCtr].Pack		(quat, trans);

			trafoCtr++;
		};
		actFrame += step;
	};
//	zERR_MESSAGE		(5, 0, "frames: "+zSTRING(numFrames)+", nodes: "+zSTRING(numNodes)+", "+
//		zSTRING(numFrames*numNodes)+","+zSTRING(trafoCtr)+","+zSTRING(step)+","+zSTRING(aniFpsScale));
};

zCQuat zCModelAni::GetQuat (int frameNumber, int nodeNumber) const 
{ 
//	PrepareAniDataAccess();		// bisher fuer rotation nicht noetig
	zCQuat quat; 
	(aniSampleMatrix + (frameNumber*numNodes) + nodeNumber)->UnpackQuat  (quat);  
	return quat;  
};

zVEC3 zCModelAni::GetTrans (int frameNumber, int nodeNumber) const 
{ 
	PrepareAniDataAccess();
	zVEC3 trans; 
	(aniSampleMatrix + (frameNumber*numNodes) + nodeNumber)->UnpackTrans (trans); 
	return trans; 
};

void zCModelAni::SetTrans (int frameNumber, int nodeNumber, const zVEC3& trans) 
{ 
	PrepareAniDataAccess();
	(aniSampleMatrix + (frameNumber*numNodes) + nodeNumber)->PackTrans (trans); 
};

void zCModelAni::SetQuat (int frameNumber, int nodeNumber, const zCQuat& quat)
{ 
//	PrepareAniDataAccess();
	(aniSampleMatrix + (frameNumber*numNodes) + nodeNumber)->PackQuat (quat); 
};

void zCModelAni::AddNodeList (zCTree<zCModelNode> **mnodeList) {
	if (numNodes<=0) { nodeList=0; return; };
	nodeList = zNEW(zCModelNode*) [numNodes];
	for (int i=0; i<numNodes; i++) nodeList[i] = mnodeList[i]->GetData();
};

void zCModelAni::SetFlags (const zSTRING& s) {
	memset (&aniFlags, 0, sizeof(aniFlags));
	if (s.Search("M")!=-1) aniFlags.flagVobPos	= TRUE;
	if (s.Search("R")!=-1) aniFlags.flagVobRot	= TRUE;
	if (s.Search("E")!=-1) aniFlags.flagEndSync	= TRUE;
	if (s.Search("F")!=-1) aniFlags.flagFly		= TRUE;
	if (s.Search("I")!=-1) aniFlags.flagIdle	= aniFlags.flagInPlace = TRUE;
	if (s.Search("P")!=-1) aniFlags.flagInPlace	= TRUE;

};

void zCModelAni::SetBlendingSec (const zVALUE blendInSec, const zVALUE blendOutSec) {
	if (blendInSec==0)	blendInSpeed  = zMDL_ANI_BLEND_IN_ZERO;
	else				blendInSpeed  = 1 / blendInSec;
	if (blendOutSec==0)	blendOutSpeed = zMDL_ANI_BLEND_OUT_ZERO;
	else				blendOutSpeed =-1 / blendOutSec;
};

void zCModelAni::GetBlendingSec (zVALUE& blendInSec, zVALUE& blendOutSec) const {
	if (blendInSpeed==zMDL_ANI_BLEND_IN_ZERO)	blendInSec		= 0;
	else										blendInSec		= 1 / blendInSpeed;
	if (blendOutSpeed==zMDL_ANI_BLEND_OUT_ZERO)	blendOutSec		= 0;
	else										blendOutSec		=-1 / blendOutSpeed;
};

void zCModelAni::CorrectRootNodeIdleMovement () 
{
	// .. damit nicht Models beim 'Rumstehen' nach zwei Minuten neben ihrem eigentlichem Ort stehen
	if ((rootNodeIndex>=0) && (numFrames>0))
	{
		zREAL len = (GetTrans (0, rootNodeIndex) - GetTrans (numFrames-1, rootNodeIndex)).Length();
		if (len<zMDL_FLAG_STATICCYCLE_MAXDIST)
		{
			// FIXME: hier evtl. noch pruefen, ob die Ani cycled, d.h. nextAni==this ist (geht derzeit nicht, da die References erst spaeter aufgeloest werden)
			aniFlags.flagStaticCycle	= TRUE;
		};
	};

/*	
	// FIXME: das macht so doch gar keinen Sinn, oder ??
	zVEC3 trans(0,0,0);
	for (int i=0; i<numFrames; i++) {
		trans += GetTrans (i, rootNodeIndex);
	};
	if (aniFlags.flagIdle)	
	{
		// Der Fehler wird auf alle Frames gleichmaessig verteilt
		trans[VY]	= 0;

		trans		/= zREAL(numFrames);
		for (i=0; i<numFrames; i++) {
			SetTrans (i, rootNodeIndex, GetTrans (i, rootNodeIndex) - trans);
		};
	};*/
};

void zCModelAni::CalcInPlaceFlag ()
{
	// maximale Bewegung der Huefte in XZ-Plane < THRESH => flagInPlace setzen
	if (aniFlags.flagFly)	return;
	if (rootNodeIndex<0)	
	{
		// Anis ohne rootNodeIndex bewegen sich erst recht nicht => Flag setzen!
		aniFlags.flagInPlace = TRUE;
		return;
	};

	zREAL	maxDist	= 0;
	zVEC3	start	= GetTrans (0, rootNodeIndex); 
	start[VY]		= 0;
	for (int i=1; i<numFrames; i++) 
	{
		zVEC3 trans	= GetTrans (i, rootNodeIndex);
		trans[VY]	= 0;
		maxDist		= zMax (maxDist, (start-trans).Length());
	};
	if (maxDist<zMDL_FLAG_INPLACE_MAXDIST)
		aniFlags.flagInPlace = TRUE;
};

zBOOL zCModelAni::ResolveAlias (zCModelPrototype *hostModelProto) 
{
	if (GetAniType()!=zMDL_ANI_TYPE_ALIAS) return TRUE;
	if (aliasName.Length()>0) 
	{
		zCModelAni* alias = hostModelProto->SearchAni (aliasName);
		if (alias==0) 
		{
			zERR_WARNING ("D: zModel(zCModelAni::ResolveAlias): Could not resolve aliasAni: "+aliasName); 
			return FALSE;
		};
		if (alias->GetAniType()!=zMDL_ANI_TYPE_NORMAL) 
		{
			zERR_WARNING ("D: zModel(zCModelAni::ResolveAlias): aliasAni references ani of illegal type: "+GetAniName()+", "+aliasName); 
			return FALSE;
		};
		
		ascName				= alias->ascName;
		fpsRate				= fpsRateSource = alias->fpsRate;
		numFrames			= alias->numFrames; 
		numNodes			= alias->numNodes;
		nodeList			= alias->nodeList;
		nodeIndexList		= alias->nodeIndexList;
		aniSampleMatrix		= alias->aniSampleMatrix;
		rootNodeIndex		= alias->rootNodeIndex;
		numAniEvents		= alias->numAniEvents;		// aniEvents werden nun bei aniAlias geshared !
		aniEvents			= alias->aniEvents;
		samplePosRangeMin	= alias->samplePosRangeMin;
		samplePosScaler		= alias->samplePosScaler;
		aniBBox3DObjSpace	= alias->aniBBox3DObjSpace;

		// FIXME: wurde auch alles relevante kopiert ??

		// FIXME: flags ins .MAN speichern!
		aniFlags.flagInPlace	= alias->aniFlags.flagInPlace;
		aniFlags.flagStaticCycle= alias->aniFlags.flagStaticCycle;
	};
	return TRUE;
};

zBOOL zCModelAni::ResolveComb (zCModelPrototype *hostModelProto) 
{ 
	if (GetAniType()!=zMDL_ANI_TYPE_COMB) return TRUE;
	if (aliasName.Length()>0) 
	{
		int number	= zSTRING(aliasName[aliasName.Length()-1]).ToInt();
		aliasName.Delete (aliasName.Length()-1, 1); 

		numFrames=numNodes=0;
		zCModelAni	*combAni;
		zSTRING		combName;
		while (number>=1) 
		{
			combName	= aliasName + zSTRING(number);
			combAni		= hostModelProto->SearchAni (combName);
			if (combAni==0) 
			{
				zERR_FATAL ("D: zModel(zCModelAni::ResolveComb): Could not resolve combAni: "+combName); 
				return FALSE;
			};
			combAniList.InsertFront (combAni);
			if (numFrames>0)
			if (numFrames!=combAni->numFrames) 
			{
				zERR_WARNING ("D: zModel(zCModelAni::ResolveComb): combAnis have different frame-numbers: "+combName); 
				return FALSE;
			}
			if (numNodes>0)
			if (numNodes!=combAni->numNodes) 
			{
				zERR_FATAL ("D: zModel(zCModelAni::ResolveComb): combAnis have different numNodes, Ani: "+combName);
				return FALSE;
			};
			numFrames		= combAni->numFrames;
			numNodes		= combAni->numNodes;
			number--; 
		};

//		numFrames		= combAni->numFrames;
//		numNodes		= combAni->numNodes;
		aniDir			= combAni->aniDir;
		ascName			= combAni->ascName;
		fpsRate			= fpsRateSource = combAni->fpsRate;
		aniBBox3DObjSpace=combAni->aniBBox3DObjSpace;
		rootNodeIndex	= combAni->rootNodeIndex;
		nodeList		= zNEW(zCModelNode*)	[numNodes];
		nodeIndexList	= combAni->nodeIndexList;
		aniSampleMatrix	= zNEW(zTMdl_AniSample) [numFrames*numNodes];
		memcpy			(nodeList, combAni->nodeList, numNodes * sizeof(zCModelNode*));

		// Ani-Packing spezifisch
		zTMdl_AniSample::CalcSamplePosConstants (-800.0F, +1600.0F);		// FIXME: reicht diese Range ? irgendwie auch adaptiv machen ??
		// diese Konstanten werden in der Ani persistent gespeichert !
		samplePosRangeMin	= zTMdl_AniSample::samplePosRangeMin;
		samplePosScaler		= zTMdl_AniSample::samplePosScaler;

// FIXME: folgende Zeile ist nun sinnlos, da eine Ani nicht ohne weiteres das DatenFormat einer zweiten Ani verstehen kann..
//		memcpy (aniSampleMatrix	, combAni->aniSampleMatrix	, numNodes * numFrames *	sizeof(zTMdl_AniSample));
		zVEC3	trans;
		zCQuat	quat;
		for (int i=0; i<numFrames; i++) {
			for (int j=0; j<numNodes; j++) {
				trans	= combAni->GetTrans	(i, j);
				quat	= combAni->GetQuat	(i, j);
				SetTrans	(i, j, trans);
				SetQuat		(i, j, quat);
			};
		};

	};
	return TRUE;
};

// ****************************************************************************************************************


// File In/Out
/*
	- FCHUNK_MODELANI
		- FCHUNK_MAN_SOURCE
		- FCHUNK_MAN_HEADER
		- FCHUNK_MAN_ANIEVENTS
		- FCHUNK_MAN_NODELIST
		- FCHUNK_MAN_SAMPLES_ROT_MAT3
			- numFrames
			- Trafo-List (2D-Tabelle)
		- FCHUNK_MAN_SAMPLES_ROT_QUAT
		- FCHUNK_MAN_SAMPLES_POS
*/
enum
{
	zFCHUNK_MODELANI					= 0xA000,
		zFCHUNK_MAN_HEADER				= 0xA020,
									// - Ani-Name
									// - Layer
									// - numFrames
									// - numNodes
									// - fps-Rate
									// - nextAniName
		zFCHUNK_MAN_SOURCE				= 0xA010,
									// zWORD	Versions-Nummer
									// zDATE	Datum der Quelldatei
									// zSTRING	Quelldatei (.ASC)
		zFCHUNK_MAN_ANIEVENTS			= 0xA030,
									// - numAniEvents
									// - AniEvent-List
		zFCHUNK_MAN_RAWDATA				= 0xA090,
};

void zCModelAni::SaveMAN (zCModelPrototype *hostModelProto, const zSTRING& scriptDefLine) 
{
	CorrectRootNodeIdleMovement();

	int i;
	zSTRING fileName	= hostModelProto->GetModelProtoName() + zMDL_FILENAME_SEPARATOR + aniName+".man";
	zERR_MESSAGE (5, 0, "D: MDL: Saving Model-Ani: "+fileName);

	// Anis auf Layer 1 muessen immer eine gueltige RootNode referenzieren!
	// (sonst koennen sie z.B. nicht korrekt auf dem Boden aligned werden)
//	if ((this->rootNodeIndex<0) && (this->layer==1))
//		zERR_FAULT ("D: MDL: Ani on layer 1 must contain animated root-node!");

//	zoptions->ChangeDir		(DIR_COMPILED_ANIMS);
	zCFileBIN file;
	file.BinCreate		(zoptions->GetDirString(DIR_COMPILED_ANIMS) + fileName); 
	file.BinStartChunk	(zFCHUNK_MODELANI);

	// HEADER
	file.BinStartChunk	(zFCHUNK_MAN_HEADER);
	{
		file.BinWriteWord	(zMAN_VERS);
		file.BinWriteString (aniName);
		file.BinWriteInt	(layer);
		file.BinWriteInt	(numFrames);
		file.BinWriteInt	(numNodes);
		file.BinWriteFloat	(fpsRate);
		file.BinWriteFloat	(fpsRateSource);
		file.BinWriteFloat	(samplePosRangeMin);
		file.BinWriteFloat	(samplePosScaler);
		aniBBox3DObjSpace.SaveBIN (file);

/*		file.BinWriteFloat	(blendInSpeed);
		file.BinWriteFloat	(blendOutSpeed);
		file.BinWriteInt	(int(aniDir));*/
		// nextAni
		file.BinWriteString (nextAniName);
	}

	// SOURCE
	file.BinStartChunk	(zFCHUNK_MAN_SOURCE);
	{
		// Date & Name des Source-ASCs schreiben
//		zoptions->ChangeDir				(DIR_ANIMS);
		file.BinWriteSrcFileStats	(zoptions->GetDirString(DIR_ANIMS) + ascName);
		// Script Definitions-Zeile schreiben
		file.BinWriteString			(scriptDefLine);
	}

	// ANI-EVENTS
	if (numAniEvents>0) {
		file.BinStartChunk	(zFCHUNK_MAN_ANIEVENTS);
		{
			file.BinWriteInt (numAniEvents);
			for (i=0; i<numAniEvents; i++) aniEvents[i].Save(file);
		}
	};
 
	// RAWDATA
	file.BinStartChunk	(zFCHUNK_MAN_RAWDATA);
	{
		// NODELIST_CHECKSUM
		file.BinWrite (&hostModelProto->nodeListChecksum, sizeof(hostModelProto->nodeListChecksum));

		// NODELIST
		file.BinWrite (nodeIndexList.GetArray(), numNodes * sizeof(nodeIndexList[0]));
//		for (i=0; i<numNodes; i++) file.BinWriteString (nodeList[i]->nodeName);

		// SAMPLES
		file.BinWrite (aniSampleMatrix, sizeof(zTMdl_AniSample)*(numNodes*numFrames));
	}

	// cleanup
	file.BinClose (); 
};

zBOOL zCModelAni::LoadMAN (const zSTRING& filename, zCModelPrototype *hostModelProto, const zSTRING& scriptDefLine) 
{
	if (hostModelProto->GetIgnoreAnis()) return TRUE;	// ist ja kein Fehler !

	int i;
//	zoptions->ChangeDir (DIR_COMPILED_ANIMS); 
	zSTRING fileName = hostModelProto->GetModelProtoName() + zMDL_FILENAME_SEPARATOR + filename;

//	zERR_MESSAGE		(5, 0, "D: MDL: Loading Model-Ani: "+fileName);

	zCFileBIN file	(zoptions->GetDirString(DIR_COMPILED_ANIMS) + fileName);
	// noch nicht ins interne Format konvertiert ?
	if (!file.BinExists()) {
		file.BinClose ();
		return FALSE;
	};
	file.BinOpen	();

	zWORD	id;
	zLONG	len;
	int		tmpInt;
	while (!file.BinEof()) { 
		file.BinOpenChunk (id, len);
		switch (id) { 
		case zFCHUNK_MAN_HEADER:
			zWORD vers;
			file.BinReadWord	(vers);
			if (vers!=zMAN_VERS) goto convertASC;

			file.BinReadString	(aniName);
			file.BinReadInt		(layer);
			file.BinReadInt		(tmpInt);			numFrames	= tmpInt;
			file.BinReadInt		(tmpInt);			numNodes	= tmpInt;
			file.BinReadFloat	(fpsRate);
			file.BinReadFloat	(fpsRateSource);
			file.BinReadFloat	(samplePosRangeMin);
			file.BinReadFloat	(samplePosScaler);
			aniBBox3DObjSpace.LoadBIN (file);

			// nextAni
			file.BinReadString	(nextAniName);
			break;
		case zFCHUNK_MAN_SOURCE: {
			if (!zCModelPrototype::GetAutoConvertAnis()) {
				file.BinSkipChunk();
				break;
			};
//			zoptions->ChangeDir (DIR_ANIMS);		// dir ist bereits im String im File enthalten
			if (!file.BinReadCompareSrcFileStats ()) goto convertASC;

			// Script Definitions-Zeile lesen/vergleichen
			zSTRING line; 
			file.BinReadString (line);
			if (scriptDefLine.Length()>0) {
				if (line!=scriptDefLine) goto convertASC;
			};
			}
			break;
		case zFCHUNK_MAN_ANIEVENTS: 
			file.BinReadInt		(tmpInt);	numAniEvents = tmpInt;
			if (aniEvents)		delete[] aniEvents;
			aniEvents			= zNEW(zCModelAniEvent) [numAniEvents];
			for (i=0; i<numAniEvents; i++) aniEvents[i].Load(file);
			break;
		case zFCHUNK_MAN_RAWDATA: {
			// NodeList Checksum
			zDWORD checksum;
			file.BinRead (&checksum, sizeof(checksum));
			if (checksum!=hostModelProto->nodeListChecksum) {
				zERR_WARNING ("D: zModel(zCModelAni::LoadMAN): the file's node-hierarchy is incompatible to 'meshAndTree', converting ASC");
				goto convertASC;
			};

			// zFCHUNK_MAN_NODELIST
			assert (hostModelProto);
			

			// nodeIndexList laden (kann durchaus auch leer sein)
			nodeIndexList.DeleteList		();
			nodeIndexList.AllocAbs			(numNodes);
			nodeIndexList.MarkNumAllocUsed	();
			if (numNodes>0)
				file.BinRead				(nodeIndexList.GetArray(), sizeof(nodeIndexList[0])*numNodes);

			// nodeList erstellen
			delete[] nodeList;
			nodeList = zNEW(zCModelNode*) [numNodes];

			for (i=0; i<numNodes; i++) 
			{
				if (nodeIndexList[i]>=hostModelProto->nodeList.GetNum()) {
					zERR_WARNING ("D: zModel(zCModelAni::LoadMAN): .MAN-File: "+filename+", Ani is not compatible to Mesh/Tree; Node not found in Mesh/Tree");
					nodeList[i] = nodeList[i-1];
				} else
					nodeList[i] = hostModelProto->nodeList[nodeIndexList[i]];
				if (nodeList[i]->GetParentNode()==0) rootNodeIndex = i;		// rootNodeIndex bestimmen !
//				if (nodeList[i]->rootNode) rootNodeIndex = i;		// rootNodeIndex bestimmen !
			};

			// zFCHUNK_MAN_SAMPLES_ROT_MAT4
			delete[] aniSampleMatrix;
			int numSamples				= numNodes*numFrames;
			if (numSamples>0)
			{
				aniSampleMatrix			= zNEW(zTMdl_AniSample) [numSamples];
				file.BinRead			(aniSampleMatrix, sizeof(zTMdl_AniSample)*(numSamples));
			};

			};
			break;
		default:
			file.BinSkipChunk();
		};
	}

	// cleanup
	file.BinClose ();
	return 1;

convertASC:;
	file.BinClose ();
	return 0;
};

// ***************************************************************************************************************

zCModelAniEvent::zCModelAniEvent() : soundList(0), pfxEmitterList(0) {
	memset (this, 0, sizeof(*this));
};



/* ----------------------------------------------------------------------
	
    zCModelAniEvent::~zCModelAniEvent()	

	8.09.2000	[Moos]	
                echtes Aufr�umen der Listen


   ---------------------------------------------------------------------- */

zCModelAniEvent::~zCModelAniEvent(){
 int i;
 for(i=soundList.GetNum()-1;i>=0;i--)
    if (soundList[i]) soundList[i]->Release();

//    for(i=pfxEmitterList.GetNum()-1;i>=0;i--) // Die Emitter l�schen sich doch selbst, also ist das hier nicht n�tig
  //      delete pfxEmitterList[i];
        //        pfxEmitterList[i]->Release();
};

void zCModelAniEvent::Save (zCFileBIN& file) const {
	file.BinWrite		(&aniEventType, sizeof (aniEventType));
	file.BinWriteInt	(frameNr);
	file.BinWriteString	(tagString);
	for (int i=0; i<zMDL_ANIEVENT_MAXSTRING; i++)
		file.BinWriteString	(string[i]);
	file.BinWrite		(&value1, sizeof(value1));
	file.BinWrite		(&value2, sizeof(value2));
	file.BinWrite		(&value3, sizeof(value3));
	file.BinWrite		(&value4, sizeof(value4));

	// FIXME: prob ist obsolete!
	zREAL _prob;
	file.BinWrite		(&_prob  , sizeof(_prob));
};

void zCModelAniEvent::Load (zCFileBIN& file){
	file.BinRead		(&aniEventType, sizeof (aniEventType));
	file.BinReadInt		(frameNr);
	file.BinReadString	(tagString);
	for (int i=0; i<zMDL_ANIEVENT_MAXSTRING; i++)
		file.BinReadString	(string[i]);
	file.BinRead		(&value1, sizeof(value1));
	file.BinRead		(&value2, sizeof(value2));
	file.BinRead		(&value3, sizeof(value3));
	file.BinRead		(&value4, sizeof(value4));

	// FIXME: prob ist obsolete!
	zREAL _prob;
	file.BinRead		(&_prob  , sizeof(_prob));
};

// ***************************************************************************************************************

///////////////////////////////////////////////////////////////////////////
//     Model Prototype
///////////////////////////////////////////////////////////////////////////


// ***************************************************************************************************************

zBOOL				zCModelPrototype::s_ignoreAnis			= FALSE;
zBOOL				zCModelPrototype::s_autoConvertAnis		= TRUE;
zBOOL				zCModelPrototype::s_autoConvertMeshes	= FALSE;
zCModelPrototype*	zCModelPrototype::s_modelRoot			= 0;

static int CompareModelProtoAniNames ( const void *arg1, const void *arg2 ) {
	zCModelAni* ani1 = *((zCModelAni**)arg1);
	zCModelAni* ani2 = *((zCModelAni**)arg2);
	return ani1->GetAniName().CompareTo (ani2->GetAniName());
};

zCModelPrototype::zCModelPrototype () 
{
	//
	Init();							

	//
	refCtr					= 1;
	// insert into list		
	prev					= 0;
	next					= s_modelRoot;
	if (s_modelRoot)		
	s_modelRoot->prev		= this;
	s_modelRoot				= this;
};

void zCModelPrototype::Init () 
{
	protoAnis.SetCompare	(CompareModelProtoAniNames);
	bbox3D.InitZero			();
	bbox3DCollDet.InitZero	();
	nodeListChecksum		= 0;
	baseModelProto			= 0;
	fileSourceType			= zFROM_MDS;
	rootNodeTrans			= 0;

	//						
	modelProtoName			= zSTRING((int)this);		// safety
}

zCModelPrototype::~zCModelPrototype	() {
	// shared Object 
	refCtr--;
	if (refCtr!=0) 
		zERR_FATAL ("D:zModel(zCModelProto::Destructor): Reference-Ctr not zero !");

	// 
	Clear();

	// delete from list
	if (this==s_modelRoot) s_modelRoot= next; else
	if (prev) prev->next	= next;
	if (next) next->prev	= prev;
	prev = next = 0;

	//
	baseModelProto=0;
};

void zCModelPrototype::Clear () 
{
	// Alles an Daten ablegen, was dieses Objekt in sich traegt. Am Ende durch 
	// Init() einen 'frischen' Zustand herstellen.

	// SoftSkins
//	ReleaseMeshSoftSkinList();
	ReleaseMeshes();

	// delete meshTree
	// Achtung: die Knoten des Meshtrees (zCTree!) loeschen sich von selbst ...
	//			allerdings muss man das 'data' der Knoten per Hand loeschen.
	// FIXME/ACHTUNG: sorgt folgende Zeile manchmal fuer Abstuerze ???
	meshTree.DeleteDataSubtree	();
	meshTree.DeleteChilds		();

	// ProtoAnis l�schen
	// (NullPtr koennen in Liste enthalten sein, falls es sich um ein ModelProtoOverlay handelt (siehe ::Prepare..())
	for (int i=0; i<protoAnis.GetNum(); i++)
	{
		if (protoAnis[i])
			protoAnis[i]->Release();
	};
	protoAnis.DeleteList();

	// modelEvents
	for (i=0; i<modelEvents.GetNum(); i++)		delete modelEvents[i];
	modelEvents.DeleteList();

	// FIXME: Release() .. ?
	nodeList.DeleteList();
	hierarchySourceASC.Clear();
	sourceMeshSoftSkinList.DeleteList();
	baseModelProto=0;

	//
	Init();
};

void zCModelPrototype::ReleaseMeshSoftSkinList () 
{
	for (int i=0; i<meshSoftSkinList.GetNum(); i++)
	{
		if (meshSoftSkinList[i])
			meshSoftSkinList[i]->Release();
	}
	meshSoftSkinList.DeleteList();
};

void zCModelPrototype::ReleaseMeshes() 
{
	ReleaseMeshSoftSkinList();
	for (int i=0; i<nodeList.GetNum(); i++)
		nodeList[i]->SetNodeVisualS(0);
};

int zCModelPrototype::Release () {
	refCtr--;								
	int c = refCtr;
	if (c<=0) { refCtr++; delete this; };
	return c;
};

int zCModelPrototype::NumInList () {
	zCModelPrototype *proto = GetFirstInList();
	int num = 0;
	while (proto) {
		proto= proto->GetNextInList();
		num++;
	};
	return num;
};

const zSTRING& zCModelPrototype::GetModelProtoFileName() const
{
	return modelProtoFileName;
};

void zCModelPrototype::SetModelProtoName (const zSTRING& name)	
{ 
	modelProtoName		= name; modelProtoName.Upper();	
	modelProtoFileName	= GetModelProtoName() + ((fileSourceType==zFROM_ASC) ? ".ASC" : ".MDS");
};

void zCModelPrototype::SetFileSourceType (zTFileSourceType sourceType)	
{ 
	fileSourceType		= sourceType;				
	modelProtoFileName	= GetModelProtoName() + ((fileSourceType==zFROM_ASC) ? ".ASC" : ".MDS");
};

zCModelPrototype* zCModelPrototype::Load (const zSTRING& name, zCModelPrototype *baseModelProto) {
	// a) bereits im Speicher
	zPATH	modelPath (name);
	zSTRING modelName (modelPath.GetFile());
	modelName.Upper();

	zCModelPrototype *modelProto = zCModelPrototype::SearchName (modelName);
	if (modelProto) {
//		zERR_MESSAGE (5, 0, "D: MDL: Sharing ModelProto: "+zSTRING(modelName));
		return modelProto->AddRef();
	};

	//
	modelProto = zNEW(zCModelPrototype);

	// b) .MDL / .ASC laden ? (kombiniert .MDH und .MDM)
	if (name.Search(".ASC")!=-1)
	{
		if (!modelProto->LoadModelASC (name)) {
			modelProto->Release();
			modelProto = 0;
		}; 
	} else 
	{
		// c) als .mds auf HD (Script-Format + 3dsMax ASCII)
		if (!modelProto->LoadModelScript (name)) {
			modelProto->Release();
			modelProto = 0;
		}; 
	};

	//
	if (modelProto && baseModelProto)
	{
		modelProto->PrepareAsModelProtoOverlay (baseModelProto);
	};


	return modelProto;
};

zBOOL zCModelPrototype::PrepareAsModelProtoOverlay (zCModelPrototype *baseModelProto)
{
	// macht aus einem ModelProto, das als ein Overlay benutzt werden soll ein 
	// 'fettes' modelProto.
	if (!baseModelProto) return FALSE;
	if (baseModelProto->protoAnis.GetNum()<protoAnis.GetNum()) {
		zERR_FAULT ("D: ME: Loading overlay mds "+GetModelProtoName()+" for base-mds "+baseModelProto->GetModelProtoName()+" failed: overlay has more anis than base!");
		return FALSE;
	};

	//
	zCArraySort<zCModelAni*> newAniList(baseModelProto->protoAnis.GetNum());
	for (int i=0; i<baseModelProto->protoAnis.GetNum(); i++)
		newAniList.Insert (0);

	// overlay Anis in der 'fetten' Liste anordnen und deren neue aniID eintragen
	zBOOL errorOccured = FALSE;
	for (i=0; i<protoAnis.GetNum(); i++) {
		int index = baseModelProto->SearchAniIndex (protoAnis[i]->GetAniName());
		if (index<0) {
			zERR_FAULT ("D: ME: Loading overlay mds "+GetModelProtoName()+" for base-mds "+baseModelProto->GetModelProtoName()+" failed: ani in overlay not present in base: "+protoAnis[i]->GetAniName());
			errorOccured = TRUE;
			continue;
		};
		newAniList[index]			= protoAnis[i];
		newAniList[index]->aniID	= index;
	};

	if (errorOccured)
	{
		return FALSE;
	};

	//
	protoAnis = newAniList;
	protoAnis.SetCompare (CompareModelProtoAniNames);

	//
	this->baseModelProto	= baseModelProto;

	return TRUE;
};

void zCModelPrototype::CalcNodeListChecksum() {
	zCChecksum crc;
	crc.BeginChecksum();
	for (int i=0; i<nodeList.GetNum(); i++) 
		crc.CalcBufferChecksum ((zBYTE*)nodeList[i]->GetName().ToChar(), nodeList[i]->GetName().Length());
	crc.EndChecksum();
	nodeListChecksum = crc.GetChecksum();
};

void zCModelPrototype::CollectNodeMeshes (zCArray<zCModelNode*> &protoNodeList) {
	for (int i=0; i<nodeList.GetNum(); i++) {
		zCModelNode *mnode = nodeList[i];
		if (mnode)
		if (mnode->visual) 
		if (!mnode->IsSlot())	// keine Slot-Meshes speichern
		{
			protoNodeList.Insert (mnode);
		};
	};
};

zCModelPrototype* zCModelPrototype::SearchName (zSTRING name) {
	name.Upper();
	zCModelPrototype *model = s_modelRoot;
	while ((model) && (model->GetModelProtoFileName()!=name)) model = model->next;
	return model;
};

zCModelNode* zCModelPrototype::SearchNode (const zSTRING& nodeName) {
	for (int i=0; i<nodeList.GetNum(); i++)
		if (nodeList[i]->nodeName==nodeName) return nodeList[i];
	return 0;
};

zCTree<zCModelNode>* zCModelPrototype::FindMeshTreeNode (const zSTRING& nodeName, zCTree<zCModelNode>* node) {
	if (node==0) node = &meshTree;

	// process Node	
	zCModelNode *mnode = node->GetData();
	if (mnode)
	if (mnode->nodeName==nodeName) return node;
	
	// recursive traversal
	zCTree<zCModelNode> *child = node->GetFirstChild(); 
	while (child) {
		zCTree<zCModelNode>* result = FindMeshTreeNode (nodeName, child);
		if (result) return result;
		child = child->GetNextChild();
	};
	return 0;
};

static int meshTreeNodeIndex;

int zCModelPrototype::FindMeshTreeNodeIndex (const zSTRING& nodeName, zCTree<zCModelNode>* node) {
	if (node==0) {
		node = &meshTree;
		meshTreeNodeIndex=0;
	}

	// process Node	
	zCModelNode *mnode = node->GetData();
	if (mnode)
	if (mnode->nodeName==nodeName) return meshTreeNodeIndex;
	meshTreeNodeIndex++;
	
	// recursive traversal
	zCTree<zCModelNode> *child = node->GetFirstChild(); 
	while (child) {
		int result = FindMeshTreeNodeIndex (nodeName, child);
		if (result>=0) return result;
		child = child->GetNextChild();
	};
	return -1;
};

int zCModelPrototype::FindNodeListIndex	(const zSTRING& nodeName) {
	for (int i=0; i<nodeList.GetNum(); i++)
		if (nodeList[i]->GetName()==nodeName) return i;
	return -1;
};

void zCModelPrototype::AddAni (zCModelAni *ani) {
/*	if (ani->aniName.Length()<=0) {
		zerr.Report (zERR_WARN, 1000, "D: Argh: ");
	};*/
	if (SearchAni (ani->aniName)!=0) {
		zERR_FATAL ("D: zModel(zCModelPrototype::AddAni): ani already defined: "+ani->aniName);
	};
	// eintragen
	protoAnis.InsertSort (ani);
};

int zCCFASTCALL zCModelPrototype::SearchAniIndex (const zSTRING& aniName) const {
	// durchsucht die Ani-Liste des Prototypes nach der angegeb. Ani

	// Binary Search	
	// return value= found index, -1=not found
	if (protoAnis.GetNumInList()<=0) return -1;
	int ind_low	= 0;
	int ind_high= protoAnis.GetNumInList()-1;
	int index	= ( ind_low + ind_high ) / 2; 
	int erg;

	do {
		erg = aniName.CompareTo (protoAnis[index]->GetAniName());
		if (ind_high <= ind_low) {
			if (erg==0) return index;
			return -1;
		}

		if (erg>0) 	ind_low	= index + 1; else
		if (erg<0)  ind_high= index - 1; else
		return index;

		index = ( ind_low + ind_high ) / 2;
	} while (1);
};

zCModelAni* zCModelPrototype::SearchAni (const zSTRING& aniName) const {
	int index = SearchAniIndex (aniName);
	if (index<0)	return 0;
	else			return protoAnis[index];
};

void zCModelPrototype::DescribeTree (zCTree<zCModelNode>* node, int indent) 
{
	if (node==0) node=&meshTree;

	zSTRING s = Spaces (indent*2) + "- ";
	zCModelNode *mnode = node->GetData();
	if (mnode)  {
		s += mnode->nodeName;
//		if (mnode->animated)	s += " (ani)";
		if (mnode->IsRootNode())s += " (root)";
	} else	
		s += "%";
	zERR_MESSAGE (5, 0, s+".");

	// recursive traversal
	zCTree<zCModelNode> *child = node->GetFirstChild(); 
	while (child) {
		DescribeTree (child, indent+1);
		child = child->GetNextChild();
	};
};

/*
zMAT4 zCModelPrototype::GetNodeTrafoObjToRoot (zCTree<zCModelNodeInst>* mnode) {
	zMAT4			mat		= Alg_Identity3D();
	zCModelNodeInst	*node;
	while (mnode) {
		node	= mnode->GetData();
		if (node) mat = node->mat;
		mnode	= mnode->GetParent();
	};
};
*/

// ***************************************************************************************************************

enum
{
	zMDH_VERS= (03),

	zFCHUNK_MODELHIERARCHY			= 0xD100,
		zFCHUNK_MDH_SOURCE			= 0xD110,
		zFCHUNK_MDH_END				= 0xD120,
};

zDWORD zCModelPrototype::GetMDHFileVersion ()  {
	// assert: vers nummern sind maximal 8BIT !!!
	return zDWORD(zMDH_VERS);
};

zBOOL zCModelPrototype::LoadMDH (const zSTRING& filename) 
{
//	zoptions->ChangeDir (DIR_COMPILED_ANIMS); 

	zERR_MESSAGE	(5, 0, "D: MDL: Loading Model-Hierarchy: "+filename);
	zCFileBIN file	(zoptions->GetDirString(DIR_COMPILED_ANIMS) + filename);
	// noch nicht ins interne Format konvertiert ?
	if (!file.BinExists()) {
//		file.BinClose ();
		return FALSE;
	};
	file.BinOpen		();
	zBOOL res = LoadMDH	(file);
	file.BinClose		();

	return res;
};

zBOOL zCModelPrototype::LoadMDH (zCFileBIN& file) 
{
	// Namen setzen (ohne Endung)
	SetModelProtoName (file.file->GetFilename());

	zWORD			id;
	zLONG			len;
	while (!file.BinEof()) { 
		file.BinOpenChunk (id, len);
		switch (id) { 
		case zFCHUNK_MODELHIERARCHY: {
			zDWORD	vers;
			file.BinReadDWord	(vers);
			if (vers!=GetMDHFileVersion()) goto convertASC;

			// Node-Hierarchy
			zWORD numNodes;
			file.BinReadWord		(numNodes);
			nodeList.EmptyList		();
			nodeList.AllocAbs		(numNodes);
			for (int i=0; i<numNodes; i++) 
			{
				zCModelNode			*mnode = zNEW(zCModelNode());
				zCModelNode			*pmnode= 0;
				zCTree<zCModelNode>	*pnode;
				zWORD				parentIndex;

				file.BinReadString	(mnode->nodeName); 
				file.BinReadWord		(parentIndex); 
				if (parentIndex!=0xFFFF)
				if (parentIndex<nodeList.GetNum()) pmnode = nodeList[parentIndex];

				if (!pmnode) {
					// rootNode
//					mnode->rootNode				= TRUE;
					meshTree.AddChild			(mnode);
				} else {
					pnode = FindMeshTreeNode	(pmnode->GetName());
					pnode->AddChild				(mnode);
					mnode->parentNode			= pmnode;
				};
				nodeList.InsertEnd	(mnode);
				file.BinRead		(&mnode->trafo, sizeof(mnode->trafo)); 
			};

			// misc data
			bbox3D.LoadBIN			(file);
			bbox3DCollDet.LoadBIN	(file);
			file.BinRead			(&rootNodeTrans, sizeof(rootNodeTrans));

			//
			file.BinRead			(&nodeListChecksum, sizeof(nodeListChecksum));
			};
			break;
		case zFCHUNK_MDH_SOURCE: {
			if (!zCModelPrototype::GetAutoConvertAnis()) {
				file.BinSkipChunk();
				break;
			};
//			zoptions->ChangeDir (DIR_ANIMS);
			if (!file.BinReadCompareSrcFileStats ()) 
				goto convertASC;
			};
			break;
		case zFCHUNK_MDH_END: 
			goto leaveParsing;
			break;
		default:
			file.BinSkipChunk();
		};
	};

leaveParsing:;
	// cleanup
	return 1;

convertASC:;
	return 0;
};

void zCModelPrototype::SaveMDH () 
{
	zSTRING fileName	= GetModelProtoName() + ".mdh";
	zERR_MESSAGE		(5, 0, "D: MDL: Saving Model-Hierarchy: "+fileName);
	zCFileBIN file;
	file.BinCreate		(zoptions->GetDirString(DIR_COMPILED_ANIMS) + fileName); 
	SaveMDH				(file);
	file.BinClose		();
};
	
void zCModelPrototype::SaveMDH (zCFileBIN &file) 
{
	int i;
	// HIERARCHY
	file.BinStartChunk			(zFCHUNK_MODELHIERARCHY);
	{
		file.BinWriteDWord		(GetMDHFileVersion());
		file.BinWriteWord		(zWORD(nodeList.GetNum())); 
		for (i=0; i<nodeList.GetNum(); i++) 
		{
			file.BinWriteString (nodeList[i]->GetName()); 
			if (nodeList[i]->GetParentNode())
			file.BinWriteWord	(zWORD(FindNodeListIndex(nodeList[i]->GetParentNode()->GetName()))); 
			else
			file.BinWriteWord	(zWORD(0xFFFF)); 
			file.BinWrite		(&nodeList[i]->trafo, sizeof(nodeList[i]->trafo)); 
		};
		bbox3D.SaveBIN			(file);
		bbox3DCollDet.SaveBIN	(file);
		file.BinWrite			(&rootNodeTrans		, sizeof(rootNodeTrans));
		file.BinWrite			(&nodeListChecksum	, sizeof(nodeListChecksum));
	};

	// SOURCE
	file.BinStartChunk			(zFCHUNK_MDH_SOURCE);
	{
		// Date & Name des Source-ASCs schreiben
//		zoptions->ChangeDir				(DIR_ANIMS);
		file.BinWriteSrcFileStats	(zoptions->GetDirString(DIR_ANIMS) + hierarchySourceASC);
	};

	file.BinStartChunk	(zFCHUNK_MDH_END);
};


// ***************************************************************************************************************
// .ASC - Importer
// ***************************************************************************************************************

// FIXME: ugly !?
struct zCModelPrototype::zTMatIDList {
	zCPolygon	*poly;
	int			matID;
};

//static TMatIDList						*matIDList;
static zCArray< zCArray<zCMaterial*> >	globalMatList;
static zCArray<zCMaterial*>				matList;

static const zBOOL						REV_VERT_ORDER = TRUE;
static zFILE							*file;
static zSTRING							line;
static int								numFramesInAni;
	
static int								maxImportFlags;
static zBOOL							readAni;
static zBOOL							readTree;
static zBOOL							readMesh;
static zBOOL							i_startFrame;
static zBOOL							i_lastFrame;
static zSTRING							ascFileName;
static zVEC3							nodeScale;

void zCModelPrototype::ConvertVec3 (zPOINT3& vec3) {
	zVALUE tmp;
	tmp		 = vec3[VY];
	vec3[VY] = vec3[VZ];
	vec3[VZ] =-tmp;
	vec3[VX] = -vec3[VX];
};

void zCModelPrototype::ConvertAngle (zVALUE& angle) {
//	angle = (float(2.0*M_PI) - angle);
};

static zSTRING GetString (const zSTRING& s) {
	zSTRING arg = line;
	arg.Delete ("\"", zSTR_TO);
	arg.Delete ("\"", zSTR_FROM);
	return arg;
};

static zSTRING GetArg (const zSTRING& s) {
	zSTRING arg = s;
	arg.Delete ("'", zSTR_TO);
	arg.Delete ("'", zSTR_FROM);
	return arg;
};

static void CutArg (zSTRING& s) {
	s.Delete ("'", zSTR_FROM); 
	s.Delete ("'", zSTR_FROM);
	// cut trailing spaces
	while (s[s.Length()-1]==' ') {
		s.Delete (s.Length()-1, 1);
	};
};

static void CutMarks (zSTRING& arg) {
	arg.Delete ("\"", zSTR_TO);
	arg.Delete ("\"", zSTR_FROM);
};

static zSTRING CutMarks2 (zSTRING& arg) {
	zSTRING n = arg;
	n.Delete ("\"", zSTR_TO);
	n.Delete ("\"", zSTR_FROM);
	return n;
};

void zCModelPrototype::SkipBlock () {
	int level = 1;
	while (!file->Eof()) {
		file->Read (line);
			 if (line.Search ("{")!=-1) level++; 
		else if (line.Search ("}")!=-1) level--; 
		if (level==0) return;
	};
};

void zCModelPrototype::SkipBlockCmt () {
	Printm ("D: MDL: Skipping Block: "+line);
	SkipBlock();
};

void zCModelPrototype::ReadComment () {
	//	zERR_MESSAGE (5, 0, "D: MDL: '"+GetString(line)+"'.");
};

void zCModelPrototype::ReadScene (zREAL &frameSpeed) {
/*	*SCENE_FILENAME "walk04.max"
	*SCENE_FIRSTFRAME 0
	*SCENE_LASTFRAME 60
	*SCENE_FRAMESPEED 25
	*SCENE_TICKSPERFRAME 192
	*SCENE_BACKGROUND_STATIC 0.0000	0.0000	0.0000
	*SCENE_AMBIENT_STATIC 0.0431	0.0431	0.0431 */
	int		firstFrame, lastFrame, ticksPerFrame;
	zSTRING num;
	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		num = line.PickWord_Old (3," \t");
			 if (line.Search ("*SCENE_FIRSTFRAME"	)!=-1) firstFrame		= num.ToInt();
		else if (line.Search ("*SCENE_LASTFRAME"	)!=-1) lastFrame		= num.ToInt();
		else if (line.Search ("*SCENE_FRAMESPEED"	)!=-1) frameSpeed		= num.ToFloat();
		else if (line.Search ("*SCENE_TICKSPERFRAME")!=-1) ticksPerFrame	= num.ToInt();
		else if (line.Search ("*SCENE_ENVMAP"		)!=-1) SkipBlock();
		else if (line.Search ("}"					)!=-1) break;
	};
	// falls bis zum letzten Frame gelesen werden soll: 
	// erstmal start+ende aus dem scene-header nehmen (wird spaeter durch TM_ANIM etc. korrigiert)
	if (i_lastFrame==999999) {
		i_lastFrame	= lastFrame;
	};
 
// FIXME: Hack !! 3dsMax scheint nicht zaehlen zu koennen !!!!!  (oder doch ???)
//if (firstFrame!=0) i_lastFrame--;								// ????????????????????

//if (firstFrame!=0) zERR_MESSAGE		(5, 0, "firstFrame: "+zSTRING(firstFrame));

	i_startFrame	-= firstFrame;
	i_lastFrame		-= firstFrame;
	numFramesInAni	 = i_lastFrame-i_startFrame+1;

//	zERR_MESSAGE (5, 0, "D: MDL: * Frames: "+zSTRING(i_startFrame)+" to "+zSTRING(i_lastFrame)+" , numFrame: "+zSTRING(numFramesInAni)+
//		((firstFrame!=0) ? " (segmented)" : ""));
	if ((i_startFrame<0) || (i_lastFrame<0))
		zERR_FATAL ("D: zModel(zCModelPrototype::ReadScene): illegal frame-range in MDS");
//	Printm ("D: MDL: * Frames: "+zSTRING(firstFrame)+"-"+zSTRING(lastFrame)+", FPS: "+zSTRING(frameSpeed)+
//		", ticks: "+zSTRING(ticksPerFrame));
};

zVEC3 zCModelPrototype::ReadTriple () 
{
	zVEC3 t;
	const zSTRING& trenn = " \t";
	const zSTRING& skip  = " \t";
//	t[VX] = zVALUE(line.PickWord_Old ( 4, sep).ToFloat());
//	t[VY] = zVALUE(line.PickWord_Old ( 6, sep).ToFloat());
//	t[VZ] = zVALUE(line.PickWord_Old ( 8, sep).ToFloat());
	t[VX] = zVALUE(line.PickWord ( 2, trenn, skip).ToFloat());
	t[VY] = zVALUE(line.PickWord ( 3, trenn, skip).ToFloat());
	t[VZ] = zVALUE(line.PickWord ( 4, trenn, skip).ToFloat()); 
//	zERR_MESSAGE (5, 0, zSTRING(t[0])+", "+zSTRING(t[1])+", "+zSTRING(t[2]));
	return t;
};

zMATRIX4 zCModelPrototype::ReadNodeTM (zCModelNode *mnode) 
{
/*		*TM_ROW0 0.0000	-0.4737	0.0000
		*TM_ROW1 0.4737	0.0000	0.0000
		*TM_ROW2 0.0000	0.0000	0.4737
		*TM_ROW3 0.0000	0.0000	97.3295
		*TM_POS 0.0000	0.0000	97.3295
		*TM_ROTAXIS 0.0000	0.0000	1.0000
		*TM_ROTANGLE 1.5708
		*TM_SCALE 0.4737	0.4737	0.4737
		*TM_SCALEAXIS 0.0000	0.0000	0.0000
		*TM_SCALEAXISANG 0.0000 */
	zMATRIX4	mat4 = Alg_Identity3D();
	zVEC3		row0, row1, row2, row3;
	zVEC3		rotax;
	zVALUE		rotangle;
	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
			 if (line.Search ("*TM_ROW0"		)!=-1) row0		= ReadTriple();
		else if (line.Search ("*TM_ROW1"		)!=-1) row1		= ReadTriple();
		else if (line.Search ("*TM_ROW2"		)!=-1) row2		= ReadTriple();
		else if (line.Search ("*TM_ROW3"		)!=-1) row3		= ReadTriple();
		else if (line.Search ("*TM_SCALEAXIS"	)!=-1) ;		
		else if (line.Search ("*TM_SCALEAXISANG")!=-1) ;
		else if (line.Search ("*TM_SCALE"		)!=-1) nodeScale= ReadTriple();
		else if (line.Search ("*TM_ROTAXIS"		)!=-1) rotax	= ReadTriple(); 
		else if (line.Search ("*TM_ROTANGLE"	)!=-1) rotangle	= zVALUE(line.PickWord_Old ( 2, " /t").ToFloat());
		else if (line.Search ("}"				)!=-1) break;
	};
	// Scale konvertieren
	ConvertVec3 (nodeScale);
//	if ((scale[VX]<0) || (scale[VY]<0) || (scale[VZ]<0)) zERR_MESSAGE (5, 0, "D: !! negativ scale !!");
	nodeScale[VX] /= float(fabs(nodeScale[VX]));
	nodeScale[VY] /= float(fabs(nodeScale[VY]));
	nodeScale[VZ] /= float(fabs(nodeScale[VZ]));
	//
/*	mat4[0] = zVEC3 (row0[0], row1[0], row2[0]);
	mat4[1] = zVEC3 (row0[1], row1[1], row2[1]);
	mat4[2] = zVEC3 (row0[2], row1[2], row2[2]);
	ConvertMat4 (mat4);*/
	//
	// Hack ... 
	if (rotax==zVEC3(0.0F,0.0F,0.0F))  {
		rotax	= zVEC3(1.0F,0.0F,0.0F);
		rotangle= 0.0F;
	};
	ConvertVec3  (rotax);
	ConvertAngle (rotangle);
	mat4		= Alg_Rotation3DRad (rotax, rotangle) * Alg_Scaling3D (nodeScale); 
//	mat4		= Alg_Rotation3DRad (rotax, rotangle); 
//	ConvertMat4 (mat4);
	//
	ConvertVec3			(row3);
	mat4.SetTranslation (row3);
	//
/*	zMATRIX4 Rot	= Alg_Rotation3D	(zVEC3(0.0,0.0,1.0), -1.5708 *180.0F / float(M_PI));
	zMATRIX4 Scale	= Alg_Scaling3D		(nodeScale);
	zMATRIX4 Trans	= Alg_Translation3D (row3);
	
	zMATRIX4 res;
	res	= Trans * Rot * Scale;
*/	
	// in Node eintragen
	mnode->trafoObjToWorld	= mat4;
	mnode->nodeRotAxis		= rotax;
	mnode->nodeRotAngle		= rotangle;
//	zERR_MESSAGE (5, 0, "D: ** nodeTM "+mnode->nodeName+", ROT: "+zSTRING(rotangle)+", "+zSTRING(rotax[0])+", "+zSTRING(rotax[1])+", "+zSTRING(rotax[2]));

	return mat4;
};
 
// ************************************************************************************

void zCModelPrototype::ReadVertexList (zCMesh *mesh, int _numVert) {
	mesh->AllocVerts (_numVert);

	zPOINT3 pos;
	for (int i=0; i<_numVert; i++) {
		file->Read (line);
		pos[VX] = zVALUE(line.PickWord_Old ( 7, sep).ToFloat());
		pos[VY] = zVALUE(line.PickWord_Old ( 9, sep).ToFloat());
		pos[VZ] = zVALUE(line.PickWord_Old (11, sep).ToFloat());
		ConvertVec3 (pos);
		mesh->AddVertex (pos);
	};
	file->SeekText ("}");
};

zCModelPrototype::zTMatIDList* zCModelPrototype::ReadFaceList (zCMesh *mesh, int _numPoly) { 
	mesh->AllocPolys (_numPoly);
	zTMatIDList* matIDList = zNEW(zTMatIDList) [_numPoly];

	int v1,v2,v3;
	for (int i=0; i<_numPoly; i++) {
		file->Read (line);
		v3 = line.PickWord_Old ( 6, ":").PickWord_Old (1,"B").ToInt();
		v2 = line.PickWord_Old ( 9, ":").PickWord_Old (1,"C").ToInt();
		v1 = line.PickWord_Old (12, ":").PickWord_Old (1,"A").ToInt();

		if (REV_VERT_ORDER) zSwap (v1, v3);
		zCPolygon *poly = mesh->AddPoly (mesh->ShareVertex(v1), mesh->ShareVertex(v2), mesh->ShareVertex(v3));

		// *MESH_MTLID
		matIDList[i].matID	= line.PickWord ( 18, " /t/r", " /t/r").ToInt(); 
		matIDList[i].poly	= poly;
//		zERR_MESSAGE (5, 0, "D: matID: "+zSTRING(matIDList[i].matID)+" "+line);
	};
	file->SeekText ("}");

	return matIDList;
};

zVEC2* zCModelPrototype::ReadTVertexList (int _numTVert) {
	zVEC2 *uvList = zNEW(zVEC2) [_numTVert];

	for (int i=0; i<_numTVert; i++) {
		file->Read (line);
		uvList[i].n[VX] =	   zVALUE(line.PickWord_Old ( 7, sep).ToFloat());
		uvList[i].n[VY] = 1.0F-zVALUE(line.PickWord_Old ( 9, sep).ToFloat());		// invert y/v Axis !
		//zERR_MESSAGE (5, 0, zSTRING(uvList[i].n[VX])+", "+zSTRING(uvList[i].n[VY]));
	};
	file->SeekText ("}");
	return uvList;
};

void zCModelPrototype::ReadTFaceList (zCMesh *mesh, zVEC2 *uvList, int _numTPoly) {
	int v1,v2,v3;
	for (int i=0; i<_numTPoly; i++) {
		file->Read (line);
		v1 = line.PickWord_Old ( 7, sep).ToInt();
		v2 = line.PickWord_Old ( 9, sep).ToInt();
		v3 = line.PickWord_Old (11, sep).ToInt();
		//zERR_MESSAGE (5, 0, zSTRING(v1)+", "+zSTRING(v2)+", "+zSTRING(v3));
//		if (REV_VERT_ORDER) zSwap (v1, v3);
		mesh->SharePoly(i)->SetMapping ( uvList[v1], uvList[v2], uvList[v3]);
	};
	file->SeekText ("}");
};

void zCModelPrototype::ReadSoftSkinVertList () 
{
	// Ein zCMesh sourceMesh wird in ein zCProgMeshProto/zCMeshSoftSkin umgewandelt und 
	// schliesslich die Vertex/Bone Weights zugeordnet.
	// ASSERT: alle nodes muessen hier bereits vorhanden sein !

/*
	- entgueltiger Set von Nodes muss in richtiger Reihenfolge vorliegen (sort ? breitensort ?)
	- exporter setzt VertWeights ans Ende (mit Node-Ref)
	- beim ersten SVert Block wird sortierte Liste der Nodes erstellt (wird spaeter von zCModel uebernommen)
*/

	struct zTControlerWeight {
		zCMeshSoftSkin::zTWeightEntry	weightEntry[zMESH_DEFORM_MAX_LINKS_PARSED];
		int								numNodes;
		zTControlerWeight() { numNodes=0; };
	};

	// Das Source zCMesh ermitteln, das bearbeitet werden soll
	// Node-Name
	zSTRING nodeName;
	file->Read		(nodeName);
	nodeName		= ascFileName + nodeName;
	nodeName.Upper	();
	zCMesh			*sourceMesh = 0;
	{
		for (int i=0; i<sourceMeshSoftSkinList.GetNum();i++)
			if (sourceMeshSoftSkinList[i]->GetMeshName()==nodeName) { 
				sourceMesh = sourceMeshSoftSkinList[i];
				sourceMeshSoftSkinList.RemoveIndex	(i);
				break;
			};
	}
	assert (sourceMesh);

	// num SVert
	file->Read (line); 
	int _numVert = line.ToInt();

	zTControlerWeight	*weightList	= zNEW(zTControlerWeight) [_numVert];
	int					maxLinks	= -1;
	int					_numNodesSum= 0;
	int					_numNodes;
	zVEC3				vertPosWorld;
	zSTRING				arg;

	for (int i=0; i<_numVert; i++) 
	{
		file->Read				(line);
		line.Upper				();

		_numNodes				= line.PickWord (1, "\t", "").ToInt();
		weightList[i].numNodes	= _numNodes;
		_numNodesSum			+= _numNodes;
		vertPosWorld			= sourceMesh->ShareVertex(i)->position;

		// *MESH_SVERT 2	"Bip01 Head"	0.2	"Bip01 Spine1"	0.3
		// 5 "bip01 r hand" 45
		//		if (sscanf( line, "%d \"%[^\"]\" %d", &index, name, &parent ) == 3)

		maxLinks				= zMax (maxLinks , _numNodes);
		_numNodes				= zMin (_numNodes, zMESH_DEFORM_MAX_LINKS_PARSED);
		line.Delete ("\"", zSTR_TO);
		for (int j=0; j<_numNodes; j++) 
		{
			weightList[i].weightEntry[j].weight	= line.PickWord (2, "\t", "\t").ToFloat();
			nodeName							= CutMarks2(line.PickWord (1, "\"", "\""));
			int index							= FindNodeListIndex		(nodeName);

			if (index==-1) {
				zERR_WARNING ("D: zModelProto(zCModelPrototype::ReadSoftSkinVertList): vertex is linked to non-existant node: "+nodeName);
				index =0;
			};
			if (index>255) 
				zERR_FATAL ("D: zModelProto(zCModelPrototype::ReadSoftSkinVertList): model has more than 256 nodes");
			zCModelNode *node							= nodeList[index];
			weightList[i].weightEntry[j].nodeIndex		= index;
			
			// die Vert-Pos wird in das lokale KS der jeweiligen Node transformiert
			if (node)
				weightList[i].weightEntry[j].vertPosOS	= node->trafoObjToWorld.Inverse() * vertPosWorld;
			line.Delete ("\"", zSTR_TO);
			line.Delete ("\"", zSTR_TO);
		};

		// Vertex/Bone Weight Listen bearbeiten 
		// ASSERT: Links liegen sortiert vor !
		if (1) {
			zBOOL normalize=FALSE;
			// geringe Weights rauswerfen
			for (int k=1;k<_numNodes; k++) {
				if (weightList[i].weightEntry[k].weight	<=zMESH_DEFORM_MIN_WEIGHT) {
					_numNodes = k+1;
					normalize = TRUE;
					break;
				};
			};
			// Mehr Links als erlaubt ?
			if (_numNodes>zMESH_DEFORM_MAX_LINKS) {
				_numNodes = zMESH_DEFORM_MAX_LINKS;
				normalize = TRUE;
			};

			// weights normalisieren
			if (normalize) {
				zREAL error=1;
				for (int k=0; k<_numNodes; k++) 
					error -= weightList[i].weightEntry[k].weight;
				if (error>0) {
					error /= zREAL(_numNodes);
					for (int k=0; k<_numNodes; k++) 
						weightList[i].weightEntry[k].weight += error;
				};
			};
			weightList[i].numNodes = _numNodes;
		};
/*
		_numNodes=1;
		weightList[i].weightEntry[0].weight	= 1;
		weightList[i].numNodes				= _numNodes;
*/
	};

	// zCMeshSoftSkin erzeugen
	zCProgMeshBuilder	*pmBuilder		= zNEW(zCProgMeshBuilder);
	zCMeshSoftSkin		*meshSoftSkin	= zNEW(zCMeshSoftSkin) ;
	zCArray<int>		posListRemap;

	if (!s_bConvertNoLOD)
	{
		pmBuilder->BuildProgMeshProto		(sourceMesh, 
											 meshSoftSkin, 
											 &posListRemap, 
											 zPM_BUILD_FLAG_FORCE_SMOOTH_NORMALS	| 
											 zPM_BUILD_FLAG_NO_TRIPLANES			| 
											 zPM_BUILD_FLAG_CREATE_SUBDIV_DATA);
	}
	else
	{
		pmBuilder->BuildProgMeshProto		(sourceMesh, 
											 meshSoftSkin, 
											 &posListRemap, 
											 zPM_BUILD_FLAG_FORCE_SMOOTH_NORMALS	| 
											 zPM_BUILD_FLAG_NO_TRIPLANES			| 
											 zPM_BUILD_FLAG_CREATE_SUBDIV_DATA		|
											 zPM_BUILD_FLAG_NO_LOD);
	}
	delete pmBuilder; pmBuilder=0;	
	zRELEASE (sourceMesh);
	meshSoftSkinList.Insert				(meshSoftSkin);

	// zCMeshSoftSkin erzeugen: LOD Params setzen
	zCProgMeshProto::zTLODParams lodParams;
	meshSoftSkin->GetLODParams	(lodParams);
	lodParams.morphPerc			= 0.03F;
	meshSoftSkin->SetLODParams	(lodParams);

	// Vert/Weight Stream erzeugen
	meshSoftSkin->AllocVertWeightStream (_numVert, _numNodesSum);
	for (i=0; i<_numVert; i++) 
	{
		zTControlerWeight *vertWeight = &weightList[posListRemap[i]];
		meshSoftSkin->AddNumWeightEntry (vertWeight->numNodes); 
		for (int j=0; j<vertWeight->numNodes; j++) 
		{
//			int index = vertWeight->weightEntry[j].nodeIndex;
			meshSoftSkin->AddWeightEntry		(vertWeight->weightEntry[j]);
		};
	};

	meshSoftSkin->BuildNodeIndexList();
	meshSoftSkin->BuildNodeOBBList	();

	// Normalen in Bone-Space transformieren
	// (sind im MeshSoftSkin noch im WorldSpace)
	for (i=0; i<_numVert; i++) 
	{
		zTControlerWeight *vertWeight	= &weightList[posListRemap[i]];
		int			nodeIndex			= vertWeight->weightEntry[0].nodeIndex;
//		zCModelNode *mnode				= nodeList[meshSoftSkin->nodeIndexList[nodeIndex]];
		zCModelNode *mnode				= nodeList[nodeIndex];
		meshSoftSkin->posNormalList[i]	= mnode->trafoObjToWorld.Inverse().Rotate(meshSoftSkin->posNormalList[i]);
	};

	// Normalen in Bone-Space transformieren
// .. erst einmal deakiviert ..
/*	meshSoftSkin->nodeWedgeNormalList.AllocAbs			(meshSoftSkin->wedgeList.GetNum());
	meshSoftSkin->nodeWedgeNormalList.MarkNumAllocUsed	();
	for (i=0; i<meshSoftSkin->wedgeList.GetNum(); i++)
	{
		int posIndex									= meshSoftSkin->wedgeList[i].position;
		int nodeIndex									= weightList[posListRemap[posIndex]].weightEntry[0].nodeIndex;
		meshSoftSkin->nodeWedgeNormalList[i].nodeIndex	= nodeIndex;
		meshSoftSkin->nodeWedgeNormalList[i].normal		= nodeList[nodeIndex]->trafoObjToWorld.Inverse().Rotate(meshSoftSkin->wedgeList[i].normal);
	};
*/
	
	// OBB's der Nodes vom WorldSpace in den ObjectSpace transformieren
	for (i=0; i<meshSoftSkin->nodeIndexList.GetNum(); i++) {
		zCModelNode *mnode = nodeList[meshSoftSkin->nodeIndexList[i]];
		meshSoftSkin->nodeOBBList[i]->Transform (mnode->trafoObjToWorld.Inverse());
	};

	zERR_MESSAGE (5, 0, "D: MDL: Parsed SoftSkin, maxLinks: "+zSTRING(maxLinks)+"("+zSTRING(zMESH_DEFORM_MAX_LINKS)+")");
	delete weightList;

	file->SeekText ("}");
};

zCMesh* zCModelPrototype::ReadMesh (zBOOL softSkin, zCModelNode* node, int matRef) {
	// create Mesh
	int					_numVert;
	int					_numPoly;
	int					_numTVert;
	int					_numTPoly;
	zTMatIDList			*matIDList	=0;
	zVEC2				*uvList		=0;
	zCMesh				*mesh		=0;
	mesh = zNEW(zCMesh());
	mesh->SetMeshName (ascFileName + node->GetName());
	
// FIXME: Mesh muss einen Namen bekommen: "protoTypeName;nodeName"

	// parse mesh-contents
	zSTRING num;
	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		num = line.PickWord_Old (2," ");
		// Mesh
			 if (line.Search ("*MESH_NUMVERTEX"		)!=-1)		_numVert	= num.ToInt();
		else if (line.Search ("*MESH_NUMFACES"		)!=-1)		_numPoly	= num.ToInt();
		else if (line.Search ("*MESH_VERTEX_LIST"	)!=-1)		ReadVertexList	(mesh, _numVert);
		else if (line.Search ("*MESH_FACE_LIST"		)!=-1)		matIDList	= ReadFaceList	(mesh, _numPoly);
//		else if (line.Search ("*MESH_SOFTSKINVERTS"	)!=-1)		SkipBlock();
//		else if (line.Search ("*MESH_SOFTSKINVERTS"	)!=-1)		ReadSoftSkinVertList	((zCMeshSoftSkin*)mesh, _numVert);
		// Texture
		else if (line.Search ("*MESH_NUMTVERTEX"	)!=-1)		_numTVert	= num.ToInt();
		else if (line.Search ("*MESH_NUMTVFACES"	)!=-1)		_numTPoly	= num.ToInt();
		else if (line.Search ("*MESH_TVERTLIST"		)!=-1)		uvList		= ReadTVertexList (_numTVert);
		else if (line.Search ("*MESH_TFACELIST"		)!=-1)		ReadTFaceList (mesh, uvList, _numTPoly);
		else if (line.Search ("}"					)!=-1)		break;
	};

	AssignMeshNodeMaterials (mesh, matIDList, matRef);

	delete[] uvList;
	delete[] matIDList;

//	mesh->CalcBBox3D();
	mesh->ResetStaticLight();
	return mesh;
};

void zCModelPrototype::ReadMeshAnimation (zCModelNode* mnode, int matRef) {
	// falls evtl. irrtuemlich eine static definition eingelesen wurde => diese killen
	if (mnode->visual) mnode->visual->Release();
	mnode->visual = 0;

	int frameNr  = -1;
	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		if (line.Search ("}")!=-1) break;

		if (line.Search ("*MESH"	)!=-1) {
			//
			frameNr++;
			if ((frameNr<i_startFrame) || (frameNr>i_lastFrame)) {
				SkipBlock();
				continue;
			};
			//
			if (mnode->visual)	mnode->visual->AddEndLODVisual (ReadMesh (FALSE, mnode, matRef));
			else				mnode->visual				  = ReadMesh (FALSE, mnode, matRef);
		} 
	};
};


// ************************************************************************************

void zCModelPrototype::ReadPosTrack (zMATRIX4 *trafoList) {

	//	*CONTROL_POS_SAMPLE
	int actFrame = 0;
	int frameNr  = -1;
	while (!file->Eof()) {
		file->Read (line);
		if (line.Search ("}")!=-1) break;
		frameNr++;
		if ((frameNr<i_startFrame) || (frameNr>i_lastFrame)) continue;
		//
		zPOINT3 p;
		int		tick;
		tick  = int   (line.PickWord_Old ( 5, sep).ToInt());
		p[VX] = zVALUE(line.PickWord_Old ( 7, sep).ToFloat());
		p[VY] = zVALUE(line.PickWord_Old ( 9, sep).ToFloat());
		p[VZ] = zVALUE(line.PickWord_Old (11, sep).ToFloat());
//		zERR_MESSAGE (5, 0, zSTRING(tick)+", "+zSTRING(p[0])+", "+zSTRING(p[1])+", "+zSTRING(p[2]));
		ConvertVec3 (p);
		trafoList [actFrame].SetTranslation (p);
		actFrame++;
	};
};

void zCModelPrototype::ReadRotTrack (zMATRIX4 *trafoList) {
	//	*CONTROL_ROT_SAMPLE
	int actFrame = 0;
	int frameNr  = -1;
	while (!file->Eof()) {
		file->Read (line);
		if (line.Search ("}")!=-1) break;
		frameNr++;
		if ((frameNr<i_startFrame) || (frameNr>i_lastFrame)) continue;
		//
		int		tick;
		tick = int   (line.PickWord_Old ( 5, sep).ToInt());

		zPOINT3 d;
		zVALUE	ang;
		d[VX]= zVALUE(line.PickWord_Old ( 7, sep).ToFloat());
		d[VY]= zVALUE(line.PickWord_Old ( 9, sep).ToFloat());
		d[VZ]= zVALUE(line.PickWord_Old (11, sep).ToFloat());
		ang	 = zVALUE(line.PickWord_Old (13, sep).ToFloat());
		zPOINT3 oldPos = trafoList [actFrame].GetTranslation();

	if (d==zVEC3(0.0F,0.0F,0.0F))  {
		d= zVEC3(1.0F,0.0F,0.0F);
		ang= 0.0F;
	};

		ConvertAngle (ang);
		ConvertVec3  (d);
		trafoList [actFrame] = Alg_Rotation3DRad (d, ang); 
//		ConvertMat4 (trafoList [actFrame]);

		trafoList [actFrame].SetTranslation (oldPos);
		actFrame++;
	};
};

void zCModelPrototype::ReadTMAnimation (zCModelNode *mnode, zMATRIX4* &trafoList) { 
	Printm ("Enter: ReadAni");
	trafoList = zNEW(zMATRIX4) [numFramesInAni];
	zBOOL flag= 0;
	zBOOL rotFlag = FALSE;
	zBOOL posFlag = FALSE; 

	for (int i=0; i<numFramesInAni; i++) trafoList[i] = Alg_Identity3D();

	zSTRING num;
	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		num = line.PickWord_Old (2," ");
			 if (line.Search ("*CONTROL_POS_TRACK"	)!=-1) { ReadPosTrack (trafoList); flag++; posFlag = TRUE; }
		else if (line.Search ("*CONTROL_ROT_TRACK"	)!=-1) { ReadRotTrack (trafoList); flag++; rotFlag = TRUE; }
		// skip unsupported controllers
		else if (line.Search ("*CONTROL_"			)!=-1) { 
			line.Delete ("*", zSTR_TO); 
			zERR_WARNING("D: MDL: Skipped unsupported Controller: "+line);
			SkipBlock();
		}
		else if (line.Search ("{"					)!=-1) SkipBlockCmt();
		else if (line.Search ("}"					)!=-1) break;
	};

	// Fuer jeden Ani-Frame wird nun die korrekte, absolute Animations-Trafo berechnet, die
	// trans*rot*scale enthaelt. Diese befindet sich allerdings noch im WorldSpace. Aus:
	// 'POS_SAMPLE * ROT_SAMPLE * NODETM_SCALE'
	if ((flag) && (mnode)) {
		//zERR_MESSAGE (5, 0, "D: MDL: AniNode: "+mnode->nodeName+", POS: "+zSTRING(posFlag)+", ROT: "+zSTRING(rotFlag));
		zMATRIX4 trafoScale = Alg_Scaling3D		(nodeScale);  
		zMATRIX4 nodeRot	= Alg_Rotation3DRad (mnode->nodeRotAxis, mnode->nodeRotAngle);
		zMATRIX4 rot, trans;
		for (int i=0; i<numFramesInAni; i++) {
			// hier gibt es einen MAX 1.2/2.0 Unterschied
			if (posFlag)	trans = Alg_Translation3D (trafoList[i].GetTranslation());
			else			trans = Alg_Translation3D (mnode->trafoObjToWorld.GetTranslation());
			if (rotFlag)	rot   = trafoList[i]; 
			else			rot   = nodeRot;
			rot.SetTranslation (zVEC3(0,0,0));
			
			trafoList[i]	= trans * rot * trafoScale;		// objToWorld 
		};
	} else {
		if (trafoList) delete[] trafoList;
		trafoList = 0;
	};
	Printm ("Leave: ReadAni");
};

void zCModelPrototype::LocalizeTrafos (zCTree<zCModelNode>* node, zCTree<zCModelNode>* parentNode) 
{
	// Alle Ani-Trafos sind bisher noch als "objSpace => worldSpace" gespeichert.
	// Aus der nodeTrafo wird hier die localTrafo gemacht.
	// Alle Nodes werden rekursiv durchlaufen.

	// recursive traversal
	zCTree<zCModelNode> *child = node->GetFirstChild(); 
	while (child) {
		zCTree<zCModelNode> *nextChild = child->GetNextChild();
		// child koennte innerhalb der Rek. geloescht werden !
		LocalizeTrafos (child, node);
		child = nextChild;
	};
	
	// process Node	
	zCModelNode *mnode = node->GetData();
	zCModelNode *pnode;

	// MAX 1.2/2.0 Unterschied
	if (mnode)
	if (mnode->nodeTrafoList) {
		// alle Ani-Trafos sind noch objSpace => worldSpace
		// Aus der nodeTrafo die localTrafo machen
		if (parentNode)
		if (parentNode->GetData()) {
			pnode = parentNode->GetData();
			if (pnode->nodeTrafoList==0)
			{
				// Parent hat keine Ani, deshalb die NODE_TM des Parents benutzen...
				zMATRIX4	parentWorldToObj = pnode->trafoObjToWorld.Inverse();
				for (int i=0; i<numFramesInAni; i++) { 
					mnode->nodeTrafoList[i]	= parentWorldToObj * mnode->nodeTrafoList[i]; 		// local Trafo
				}
			} else
			{
				// Parent hat Ani, diese benutzen ...
				for (int i=0; i<numFramesInAni; i++) {
					mnode->nodeTrafoList[i]	= (pnode->nodeTrafoList[i].Inverse()) * mnode->nodeTrafoList[i]; 
//				zERR_MESSAGE (5, 0, "D: POS: "+zSTRING(pos[VX])+", "+zSTRING(pos[VY])+", "+zSTRING(pos[VZ])+", "+zSTRING(pos.Length())+
//								 ", SCALE:"+zSTRING(sc[VX])+", "+zSTRING(sc[VY])+", "+zSTRING(sc[VZ]));
				}
			};
			//
			// ** Scaling aus Ani-Matrix entfernen & in Mesh einrechnen (erst _nach_ dem localize !)
			//    Das Scaling ist waehrend der gesamten Ani konstant ! Naemlich gleich dem (WS) Node-Scaling.
			//    Zweck: beim rendern kann die Node-Inverse ueber ein einfaches Transpose berechnet werden !
			//
		};
		// wird ab jetzt nicht mehr gebraucht, koennte aber bei spaeteren Ani-Einlesungen stoeren,
		// deshalb vorsichtshalber loeschen.
		// FIXME: delete => darf nicht !!!!!!!!!
//		mnode->nodeTrafoList = 0;
//		delete mnode->nodeTrafoList;
		mnode->nodeTrafoList = 0;
	};
};

// ***************************************************************************************************************

/*
*MATERIAL_LIST {
	*MATERIAL_COUNT 10
	*MATERIAL 0 {

x		*MATERIAL_NAME "Flesh"
		*MATERIAL_CLASS "Standard"
.		*MATERIAL_AMBIENT 0.5373	0.1098	0.0549
x		*MATERIAL_DIFFUSE 0.9176	0.4667	0.4078
.		*MATERIAL_SPECULAR 0.9000	0.9000	0.9000
		*MATERIAL_SHINE 0.4000
		*MATERIAL_SHINESTRENGTH 0.8400
		*MATERIAL_TRANSPARENCY 0.0000
		*MATERIAL_WIRESIZE 1.0000
		*MATERIAL_SHADING Phong
		*MATERIAL_XP_FALLOFF 0.0000
		*MATERIAL_SELFILLUM 0.0000
		*MATERIAL_FALLOFF In
		*MATERIAL_SOFTEN
		*MATERIAL_XP_TYPE Filter
x		*MAP_DIFFUSE {
x			*MAP_NAME "Tex #15"
			*MAP_CLASS "Bitmap"
			*MAP_SUBNO 1
			*MAP_AMOUNT 1.0000
x			*BITMAP "D:\3DSMAX\Maps\INFERNO.tga"
			*MAP_TYPE Explicit
.			*UVW_U_OFFSET 0.0000
.			*UVW_V_OFFSET 0.0000
.			*UVW_U_TILING 1.0000
.			*UVW_V_TILING 1.0000
			*UVW_ANGLE 0.0000
			*UVW_BLUR 1.0000
			*UVW_BLUR_OFFSET 0.0000
			*UVW_NOUSE_AMT 1.0000
			*UVW_NOISE_SIZE 1.0000
			*UVW_NOISE_LEVEL 1
			*UVW_NOISE_PHASE 0.0000
			*BITMAP_FILTER Pyramidal
		}
		*MAP_BUMP {
			... wie "*MAP_DIFFUSE "
		*NUMSUBMTLS 4
		*SUBMATERIAL 0 {
			*MATERIAL_NAME "SKIN"
			...
// *MESH_MTLID 0

*/

void zCModelPrototype::ReadMapDiffuse (zCMaterial *mat) 
{
	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		     if (line.Search ("*BITMAP_FILTER")!=-1) {}
		else if (line.Search ("*BITMAP")!=-1) {
			zSTRING texName = GetString (line);
//zERR_MESSAGE (5, 0, "-Trying Model-Tex: "+texName); 
			zPATH path(texName);
			texName = path.GetFilename() + "." + path.GetExt();
			mat->SetTexture (texName);
		}
		else if (line.Search ("*MAP_REFLECT"	)!=-1) 
		{
			if (mat) 
			{
				zREAL envStr = line.PickWord(2,trenn,skip).ToFloat();

				if (envStr)
				{
					mat->SetEnvMapEnabled(TRUE);
					mat->SetEnvMapStrength(envStr);
				}
			}
		}
		else if (line.Search ("}")!=-1) break;
	};
};

zCMaterial* zCModelPrototype::ReadMaterial () {

	Printm ("Enter: ReadMaterial");
	zCMaterial	*mat = 0;
	zPOINT3		trip;
	
	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		if (line.Search ("*MATERIAL_NAME"		)!=-1) { 
			// Zur Sicherheit wird der ModelPrototypeName vorangestellt ... weil die bei PB so doof sind ...
			zERR_ASSERT (!ascFileName.IsEmpty());
			// den 'modelPrototypeName' zu nehmen ist leider nicht sicher genug..
			// absolut sicher & eindeutig ist allerdings der Name des ASCs, aus dem die Daten gelesen werden!
			zSTRING matName = ascFileName + zMDL_FILENAME_SEPARATOR + GetString (line);
			
			Printm ("  Mat: "+matName);
			mat = (zCMaterial*)(zCMaterial::GetStaticClassDef()->SearchObject (matName));
			if (mat) { 
				// mat gefunden ? => raus hier, rest ueberfluessig (auch SubMats werden geskippt !)
				SkipBlock();
				goto outaHere;
			} else {
				mat = zNEW(zCMaterial (matName));
				mat->SetAmbient		(0.0F);
				mat->SetDiffuse		(1.0F);
//				mat->SetPreAmbient	(0.4F);
//				mat->SetSpecular	(0.0F);
			};
		}
		else if (line.Search ("*MATERIAL_DIFFUSE"	)!=-1) trip = ReadTriple();
		else if (line.Search ("*MAP_DIFFUSE"		)!=-1) ReadMapDiffuse(mat);
		else if (line.Search ("*MAP_"				)!=-1) SkipBlock();
		else if (line.Search ("*NUMSUBMTLS"			)!=-1) {
			// es handelt sich um ein MultiMat => das �bergeordnete Material wird nicht gebraucht
			mat->Release();
			mat = 0;

			//
			int numMats = line.PickWord (2, trenn, skip).ToInt();
			matList.AllocAbs (numMats);
			// zERR_MESSAGE (5, 0, "D: NumSubMats: "+zSTRING(numMatsInList));
		}
		else if (line.Search ("*SUBMATERIAL"		)!=-1) {
//			int oldNum		= matList.GetNumInList();
			ReadMaterial();
		}
		else if (line.Search ("{"					)!=-1) SkipBlockCmt();
		else if (line.Search ("}"					)!=-1) break;
	};
	Printm ("end");
	if (mat) mat->SetColor (int(trip[0]*255), int(trip[1]*255), int(trip[2]*255));

outaHere:;

	if (mat) {
		if (mat->GetName().Length()<=0) 
			zERR_FATAL("D: zModel(): material without name !");
		// Standard-Material / kein Multimaterial => Material ist relevant und wird eingetragen
		matList.InsertEnd (mat);

		if (READASC_SMOOTHMESH)	mat->SetSmooth (TRUE);
	};
	Printm ("Leave: ReadMaterial");
	return mat;
};

zCMaterial* zCModelPrototype::ReadWireframeColor() {
	zCMaterial *mat = zNEW(zCMaterial);
//	mat->SubRef();
	zVEC3 t;
	mat->color.r = int(line.PickWord_Old ( 3, sep).ToFloat()*255);
	mat->color.g = int(line.PickWord_Old ( 5, sep).ToFloat()*255);
	mat->color.b = int(line.PickWord_Old ( 7, sep).ToFloat()*255);
	matList.Insert (mat);
	return mat; 
};

static void ReleaseMatsInList () {
	matList.DeleteList();
};

void zCModelPrototype::AssignMeshNodeMaterials (zCMesh *mesh, zTMatIDList *matIDList, int matRef) {
	// Materialien vergeben
	// Materialien bei den Polys eintragen (inkl. Submats)
	if (matIDList) {
		for (int i=0; i<mesh->numPoly; i++) {
			int nr = matIDList[i].matID;
			if (matList.GetNumInList()>0) {
				// MAX 1.2
				if (nr>=matList.GetNumInList()) nr = 0;
				matIDList[i].poly->SetMaterial ( matList.GetSafe (nr) ); 
			} else
			if ((matRef!=-1) && (globalMatList.GetNumInList()>0)) {
				// MAX 2.0
				if (nr>=globalMatList[matRef].GetNumInList()) nr = 0; 
				matIDList[i].poly->SetMaterial ( globalMatList[matRef].GetSafe (nr) ); 
			};
		};
		//			mat->SubRef();
		//			mnode->mesh->SetMaterial(mat);
	};
};

void zCModelPrototype::TransformNodeVisual (zCModelNode* mnode, const zMAT4& trafo) {
	// ACHTUNG: i.d.R.: ignore SoftSkins, transform mesh/meshAni
	zCMesh *mesh = zDYNAMIC_CAST<zCMesh>(mnode->visual);
	while (mesh) {
		// 
		mesh->TransformAllVerts	(trafo, TRUE);			// World => obj
		// normals
		if (READASC_SMOOTHMESH) mesh->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_SMOOTH);
		else					mesh->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_FACET); 
		//
		mesh = (zCMesh*)mesh->GetNextLODVisual();
	};
};

void zCModelPrototype::ProcessMeshNode (zCModelNode* mnode, zCTree<zCModelNode> *parentNode, int matRef, zBOOL nodeMeshIsSoftSkin, zBOOL& deleteNode) 
{
	// process Node	
	deleteNode			= FALSE;
	zCModelNode *pnode	= 0;
	if ((!mnode) || (!mnode->visual)) return;
	
	// Mesh aufbereiten
	// Materialien vergeben, transformieren: worldSpace => objSpace
	// bbox3D in worldSpace
	zCMesh *nodeMesh = zDYNAMIC_CAST<zCMesh>(mnode->visual);
	if ((nodeMesh->numPoly!=0) && (nodeMesh->numVert!=0)) {
		nodeMesh->CalcBBox3D			();
		bbox3D.CalcGreaterBBox3D		(mnode->visual->GetBBox3D()); 
	//	bbox3D.CalcGreaterBBox3D		(mnode->mesh->GetBBox3D()); 
	};

	// sanity 
	if (nodeMesh)
		nodeMesh->CheckForMaterials();

	// SoftSkin Meshes muessen weiterhin im Worldspace bleiben !
	// Die Meshes einer Mesh Animation sind als Visual LOD's gespeichert und muessen 
	// natuerlich _alle_ transformiert werden.
	// trafo: WS => OS
	if (!nodeMeshIsSoftSkin)
		TransformNodeVisual (mnode, mnode->trafoObjToWorld.Inverse());

	// Node Meshes in 'ZM_*' Knoten hochziehen und Node loeschen
	if (!nodeMeshIsSoftSkin)
	{  
		// Node Mesh
		if (parentNode)
		if (parentNode->GetData()) {
			pnode = parentNode->GetData();
			// reine Mesh-Knoten, ohne Ani und ohne Soehne, Vater ein "BIP*" ohne Mesh ? 
			// => Mesh hochziehen+transformieren & Knoten loeschen
			if (mnode->visual)
			if (pnode->visual==0)
			if (mnode->nodeTrafoList==0)
//			if (node ->GetNumChilds()==0)
			if (mnode->nodeName.Search ("ZS_")==-1)		// Slots sollen erhalten bleiben
			if (mnode->nodeName.Search ("ZM_")!=-1)		// nur ZM_Nodes ! damit Meshes nicht mehrfach 'hochrutschen'
			if (pnode->nodeName.Search (zMDL_NODE_NAME_BIP_PREFIX)!=-1)
			{
				TransformNodeVisual (mnode, mnode->trafo);
				deleteNode			= TRUE;
				pnode->visual		= mnode->visual;
			};
		};

		// Node-Meshes werden hier in ProgMeshes Konvertiert
		// einlesen/konstruieren: zCMesh, engine/Rendern: zCProgMeshProto
		zBOOL keepzCMesh = ((maxImportFlags& zMDL_MAX_IMPORT_PASS_ZCMESH)!=0);
	
		// in ProgMeshes konvertieren, auf Wunsch unterlassen
		if (!keepzCMesh)
		if (nodeMesh)
		{
			zCProgMeshProto *pmesh				= zNEW(zCProgMeshProto);
			// pmesh bekommt keinen Namen, da es nicht direkt geshared wird (sondern indirekt ueber die MeshLibs)
			if (!s_bConvertNoLOD)	zCProgMeshProto::BuildProgMeshProto	(nodeMesh, pmesh, 0, zPM_BUILD_FLAG_NO_POSNORMALS);		// zPM_BUILD_FLAG_NO_LOD
			else					zCProgMeshProto::BuildProgMeshProto	(nodeMesh, pmesh, 0, zPM_BUILD_FLAG_NO_POSNORMALS | zPM_BUILD_FLAG_NO_LOD);		// zPM_BUILD_FLAG_NO_LOD
			if (deleteNode)	pnode->visual		= pmesh;
			else			mnode->visual		= pmesh;
		};
	} else 
	{
		// SoftSkin Mesh
		if (mnode->visual)
		if (mnode->nodeTrafoList==0)
//		if (node ->GetNumChilds()==0)
		{
			deleteNode			= TRUE;
			zCMesh* mesh		= zDYNAMIC_CAST<zCMesh>(mnode->visual);
			sourceMeshSoftSkinList.Insert (mesh);
			assert				(mesh);
		};
	};

	//
	if (deleteNode) {
		mnode->visual = 0;
/*		delete node;	// zCTree
		node		= 0;
		delete mnode;	// zCModelNode
		mnode		= 0;*/
	};
};


void zCModelPrototype::ReadGeomobject (zMATRIX4* &trafoList, zCTree<zCModelNode>* &newmnode) {
	Printm ("Enter: ReadGeom");
	zSTRING				nodeName;
	zSTRING				parentName;
	zCModelNode			*mnode		= 0;
	zCTree<zCModelNode> *parentNode = 0;
						trafoList	= 0;
						newmnode	= 0;
	zBOOL				nodeMeshIsSoftSkin = FALSE;
	zBOOL				skipNode	= FALSE;
	zBOOL				skipMesh	= !readMesh; 
	zBOOL				skipAni		= !readAni;

	// Fuer Materials / Submaterials
	matList.DeleteList();
	int		matRef =-1;
	zSTRING arg;

	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		if (line.Search ("*NODE_NAME"		)!=-1) {
			// Namen
			nodeName		= GetString (line);
			Printm			("  Node: "+nodeName);
			arg = GetArg	(nodeName);
			CutArg			(nodeName);
			arg.Upper		();
			// Node bereits vorhanden ??
			zBOOL nodeHasBeenThere;
			newmnode		= FindMeshTreeNode (nodeName); 
			nodeHasBeenThere= (newmnode!=0);
			if (newmnode) {
				// Fehler, falls er den Node-Tree einlesen soll, und dabei einen schon vorhanden Knoten erzeugen will.
				if (readTree)
					zERR_FATAL ("D: zModelProto(zModelProto::ReadGeom): Same node-name used several times: "+nodeName);
				// da Node bereits vorhanden, ist auch dessen Parent bereits vorhanden
				if (newmnode->GetParent()->GetData()) {
					parentNode		= newmnode->GetParent();
					parentName		= parentNode->GetData()->GetName();
				};

			};
			mnode = 0;
			if (newmnode)	mnode = newmnode->GetData();
			if (mnode==0)	mnode = zNEW(zCModelNode);
			//
			mnode->nodeName = nodeName;
			//
			zBOOL legalPrefix = FALSE;
//			if (nodeName==zMDL_NODE_NAME_BIP_PREFIX) mnode->rootNode = TRUE;
			if (nodeName.Search (zMDL_NODE_NAME_BIP_PREFIX)!=-1) {
				if (nodeName.Search (zMDL_NODE_NAME_FOOTSTEPS	)!=-1) skipNode = TRUE;
				if (nodeName.Search ("SCHRITTE"					)!=-1) skipNode = TRUE;

				if (READASC_SKIPMESH_BIP01) skipMesh = TRUE;
				legalPrefix = TRUE;
			};
			// Mesh-Node ?
			if (nodeName.Search ("ZM_")!=-1) {
				if (arg[0]=='1') skipNode = TRUE;
				skipAni		= TRUE;
				legalPrefix = TRUE;
				if (skipMesh) skipNode = TRUE;
			};
			// Mesh-Slot ?
			if (nodeName.Search ("ZS_")!=-1) {
				if (READASC_SKIPMESH_ZSLOT) skipMesh = TRUE;
				legalPrefix = TRUE;
			};
			if (!legalPrefix) 
			{
				skipNode = TRUE;
				zerr.Warning ("D: zModelProto(zModelProto::ReadGeom): skipping node, illegal node-name prefix: "+nodeName);
			}
//if (nodeName.Search("ZM_UPPERARML")==-1) skipMesh = TRUE;
			//
			if ((!nodeHasBeenThere) && (!skipNode) && (!readTree) && (!readMesh)) {
				// Node noch nicht vorhanden und Tree soll gar nicht eingelesen werden: Fehler
				zerr.Warning ("D: zModelProto(zModelProto::ReadGeom): skipping node, node is contained here, but not in file 'meshAndTree': "+nodeName);
				skipNode = TRUE;
			};
			//
			if (skipNode) {
				SkipBlock();
				break;
			};
		}
		else if (line.Search ("*NODE_PARENT"	)!=-1) {
			parentName	= GetString (line); 
			CutArg(parentName);
			parentNode	= FindMeshTreeNode (parentName);
		}
		else if (line.Search ("*NODE_TM"		)!=-1) {
			if (!mnode) zERR_FATAL("D: MDL: no mnode !!!");
			// NodeTM: trafo node(obj)Space => worldSpace
			zBOOL rootNode = FALSE;
			if ((!parentNode) && (mnode)) rootNode = TRUE;
			ReadNodeTM (mnode);

			// Aus der nodeTrafo die localTrafo machen
			if (parentNode) mnode->trafo = parentNode->GetData()->trafoObjToWorld.Inverse() * mnode->trafoObjToWorld;	// local Trafo
			else			mnode->trafo = mnode->trafoObjToWorld;

			if (rootNode) {
//				rootNodeTrans = mnode->trafo.GetTranslation ();
				rootNodeTrans = mnode->trafoObjToWorld.GetTranslation ();
				mnode->trafo.SetTranslation (zVEC3(0,0,0));
			};
			mnode->translation = mnode->trafo.GetTranslation ();
		}
		else if (line.Search ("*MESH_ANIMATION"	)!=-1) {
			if (skipMesh)	SkipBlock(); 
			else			ReadMeshAnimation (mnode, matRef);
		}
		else if (line.Search ("*MESH_SOFTSKIN"	)!=-1) { 
			if (skipMesh)	SkipBlock(); 
			else			{ mnode->visual = ReadMesh (TRUE, mnode, matRef); nodeMeshIsSoftSkin=TRUE; };
		}
		else if (line.Search ("*MESH"			)!=-1) { 
			if (skipMesh)	SkipBlock(); 
			else			mnode->visual = ReadMesh (FALSE, mnode, matRef);
		}
		else if (line.Search ("*WIREFRAME_COLOR")!=-1) { if (matList.GetNumInList()==0) ReadWireframeColor(); }
		else if (line.Search ("*TM_ANIMATION"	)!=-1) { if (skipAni ) SkipBlock(); else ReadTMAnimation (mnode, trafoList); }
		else if (line.Search ("*MATERIAL_REF"	)!=-1) matRef =  line.PickWord (2, trenn, skip).ToInt();
//		else if (line.Search ("*MATERIAL"		)!=-1) { if (skipMesh) SkipBlock(); else ReadMaterial(); }	// MAX 1.2
		else if (line.Search ("*IK_JOINT"		)!=-1) SkipBlock();
		else if (line.Search ("{"				)!=-1) SkipBlockCmt();
		else if (line.Search ("}"				)!=-1) break;
	};
 
	// die RootNode hat als einzige keinen Parent!
//	if ((!parentNode) && (mnode)) mnode->rootNode = TRUE;

	if (!skipNode)
	if (!skipMesh)
		ProcessMeshNode (mnode, parentNode, matRef, nodeMeshIsSoftSkin, skipNode);

	if (!readTree) {
		ReleaseMatsInList();
		goto cleanUp;
	};

	// Node behalten ?
	if (skipNode) {
skipThisNode:;
		delete[]	trafoList;
		delete		mnode;
		ReleaseMatsInList();
		mnode		= 0;
		newmnode	= 0;
		trafoList	= 0;
		goto cleanUp;
	} else
	if (skipMesh) {
		ReleaseMatsInList	(); 
		zRELEASE			(mnode->visual);
	};

	// construct node, insert into tree
	if (parentNode) 
	{
		// zERR_MESSAGE (5, 0, "  Node: "+mnode->nodeName+", Parent: "+parentNode->GetData()->nodeName);
		newmnode			= parentNode->AddChild (mnode); 
		mnode->parentNode	= parentNode->GetData();
	} else 
	{
		if (!parentName.IsEmpty()) {
			zERR_WARNING ("D: zModel(zCModelProto::ReadGeomobj): skipping node, no parent found: "+mnode->GetName());
			goto skipThisNode;
		};
		newmnode			= meshTree.AddChild (mnode);
	};
	// ASSERT: eine Node wird erst *NACH* ihrem Parent eingefuegt !
	// rootNode und NICHT die erste in der List (=> es gab bereits eine RootNode..) => FEHLER 
	if ((mnode->GetParentNode()==0) && (nodeList.GetNum()>0)) {
		zERR_FATAL ("D: zModel(zCModelProto::ReadGeomobj): more than 1 'BIP01' rootNode in hierarchy: "+mnode->GetName());
	};
	nodeList.InsertEnd (mnode);

	if (!mnode->visual) {
		ReleaseMatsInList();
	};

cleanUp:;
	matList.DeleteList();
	Printm ("Leave: ReadGeom");
};


void zCModelPrototype::ReadMaterialList () {
	globalMatList.DeleteList();

	zSTRING num; 
	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		num = line.PickWord (2, trenn, skip); 
		{  } if (line.Search ("*MATERIAL_COUNT"	)!=-1) { globalMatList.AllocAbs (num.ToInt()); }
		else if (line.Search ("*MATERIAL"		)!=-1) {
			matList.DeleteList		();
			ReadMaterial			(); 
			globalMatList.InsertEnd (matList); 
			matList.DeleteList		();
		}
		else if (line.Search ("}"				)!=-1) break;
	};

	/*
	for (int i=0; i<globalMatList.GetNumInList(); i++) 
	{
		for (int j=0; j<globalMatList[i].GetNumInList(); j++) 
		{
			zERR_MESSAGE (5, 0, "D: _MAT: "+zSTRING(i)+", "+zSTRING(j)+": "+globalMatList[i].GetSafe(j)->GetName());
		};
	};
	*/
};

void zCModelPrototype::Load3DSMAXAsc (zCModelAni*	&aniPtrOut,
									  const			zSTRING& filename,  
									  const			zSTRING& aniName,
									  int			startFrame,
									  int			lastFrame,
									  int			_maxImportFlags,
									  zREAL			maxFps
									  ) 
{
	// x meshes parsen
	// x tree parsen
	// x ani parsen
//	zERR_MESSAGE (5, 0, "D: MDL: Loading 3DS-MAX ASCII '"+filename+"' ...");
	file = zfactory->CreateZFile (filename);

	if (!file->Exists()) 
	{
//		zoptions->ChangeDir (DIR_ANIMS);
		zPATH	ascPath;
		zPATH	path(filename);
		zSTRING fname = path.GetFilename()+"."+path.GetExt();
		if (ascPath.SearchFile(fname, zoptions->GetDirString (DIR_ANIMS))!=zERR_NONE) {
			zERR_FATAL ("D: MDL: zModel(zCModelProto::Load3DSMAXAsc): ASC not found: "+fname);
		};
		delete file;
		file = zfactory->CreateZFile (ascPath.GetPath());
	};

	

	zERROR_ID openState = file->Open();

	if ( (openState != zERR_NONE)  && (openState != zERR_NO) ) 
	{
		zERR_FATAL("C: could not open file " + filename);
	}

	//
/*	zMDL_MAX_IMPORT_ANI			= 1,
	zMDL_MAX_IMPORT_MESH		= 2,
	zMDL_MAX_IMPORT_TREE		= 4,
	zMDL_MAX_IMPORT_PASS_ZCMESH	= 8,
*/
	maxImportFlags	= _maxImportFlags;
	readAni			= ((_maxImportFlags& zMDL_MAX_IMPORT_ANI)!=0);
	readMesh		= ((_maxImportFlags& zMDL_MAX_IMPORT_MESH)!=0);
	readTree		= ((_maxImportFlags& zMDL_MAX_IMPORT_TREE)!=0);
	aniMaxFps		= maxFps;
	i_startFrame	= startFrame;
	i_lastFrame		= lastFrame;
	numFramesInAni	= lastFrame-startFrame+1;	// FIXME: was bei -1 ???
	if (i_lastFrame==-1) i_lastFrame = 999999;
	zPATH ascPath(filename);
	ascFileName		= ascPath.GetFilename();
	s_bConvertNoLOD = (ascPath.GetDir().Search("NOLOD")!=-1);

	if (readMesh)
	{
		ReleaseMeshSoftSkinList	();
		// BBox vorbereiten!
		bbox3D.Init				();
	};

	// Reading
	zREAL		fpsRate;
	int			actTrafoMatrix	= 0;
	int			actNode			= 0;
	int			sumNodes		= 0;
	zMATRIX4	**trafoMatrix;
	zMATRIX4	*trafoList;
	trafoMatrix	= zNEW(zMATRIX4*) [256];					// maximal 256 limbs !!
	zCTree<zCModelNode> *mnode; 
	zCTree<zCModelNode> **mnodeList = zNEW(zCTree<zCModelNode>*) [256];	// maximal 256 nodes

	while (!file->Eof()) {
		file->Read (line);
		line.Upper();
		if (line.Search ("*3DSMAX_ASCIIEXPORT"	)!=-1) {
			int vers = line.PickWord (2, trenn, skip).ToInt();
			if (vers==200) vers = 0;
			if (vers<zMDL_ASC_FILE_VERS)
				zERR_WARNING ("D: zModel(zCModelPrototype::Load3DSMAXAsc): .asc file exported with old exporter version, file: "+zSTRING(vers)+", engine: "+zSTRING(zMDL_ASC_FILE_VERS));
		}
		else if (line.Search ("*COMMENT"			)!=-1) ReadComment			();
		else if (line.Search ("*SCENE"				)!=-1) ReadScene			(fpsRate);
		else if (line.Search ("*MATERIAL_LIST"		)!=-1) ReadMaterialList		();
		else if (line.Search ("*MESH_SOFTSKINVERTS"	)!=-1) ReadSoftSkinVertList	();
		else if((line.Search ("*GEOMOBJECT"			)!=-1) || 
				(line.Search ("*HELPEROBJECT"		)!=-1))
		{ 
			ReadGeomobject(trafoList, mnode);
			sumNodes++;
			if ((trafoList) && (mnode)) {
				mnode->GetData()->nodeTrafoList	= trafoList;
				mnodeList  [actNode]			= mnode;
				trafoMatrix[actTrafoMatrix]		= trafoList;
				// error-checking: NodeName bereits in Ani enthalten
				for (int i=0; i<actNode; i++) {
					if (mnodeList[i]->GetData()->nodeName==mnode->GetData()->nodeName)
						zERR_FATAL ("D: zModelProto(zModelProto::Load3DSMAXAsc): Same node-name used several times: "+mnode->GetData()->nodeName);
				};
				actNode++;
				actTrafoMatrix++;
			};
		};
	};
//	zERR_MESSAGE (5, 0, "D: MDL: * NumAniNodes: "+zSTRING(actNode)+" ("+zSTRING(sumNodes)+"), NumFrames: "+zSTRING(numFramesInAni));

	// cleanUp
	globalMatList.DeleteList();

	//
	Printm ("Enter: Localize");
	LocalizeTrafos	(&meshTree, 0);
	Printm ("Leave: Localize");

	// trafoList in die aktuelle Ani einfuegen
	zCModelAni	*ani = 0;
	if (readAni) {
		ani					= zNEW(zCModelAni);
		ani->numFrames		= numFramesInAni;
		ani->fpsRate		= ani->fpsRateSource = fpsRate;
		ani->numNodes		= actTrafoMatrix;
		ani->AddTrafoMatrix (trafoMatrix);
		ani->AddNodeList	(mnodeList);
		ani->ascName		= ascPath.GetFilename()+"."+ascPath.GetExt(); 
		ani->SetAniName		(aniName);
		// Ani in Prototyp eintragen
		AddAni (ani);

		// rootNodeIndex bestimmen ! 
		for (int i=0; i<ani->numNodes; i++) 
			if (ani->nodeList[i]->IsRootNode()) { ani->rootNodeIndex = i; break; };

		// nodeIndexList der Ani berechnen
		ani->nodeIndexList.AllocAbs (ani->numNodes);
		for (i=0; i<ani->numNodes; i++) 
		{
			int index = FindNodeListIndex(ani->nodeList[i]->GetName());
			ani->nodeIndexList.InsertEnd (index);
			if (index<0)
				zerr.Warning ("D: shit: "+zSTRING(index)+", "+ani->nodeList[i]->GetName());
		};
	};
	aniPtrOut = ani;
	delete[] mnodeList; mnodeList=0;
	// Trafo-Matrix loeschen
	// die Liste von Ptr auf trafoListen, und auch die einzelnen Listen
	for (int i=0; i<actTrafoMatrix; i++) delete trafoMatrix[i];
	delete[] trafoMatrix; trafoMatrix=0;

//	RemoveSoftSkinsFromNodes();

	// solle ein Mesh eingelesen werden und damit auch eine BBox,
	// aber es kam kein Mesh an ? (z.B. bei einem Model, dass nur einen Slot enthaelt)
	// dann: BBox auf Neutral-Null setzen
	if (readMesh) {
		if (bbox3D.mins[0]>=zREAL_MAX)
			bbox3D.InitZero();
	};

	//
	if (readTree) {
		//
		CalcNodeListChecksum();

		//
		bbox3D.Translate (-rootNodeTrans);
		bbox3DCollDet = bbox3D;

		zVALUE S = 0.5F;
		bbox3DCollDet.mins[VX] *= S; 
		bbox3DCollDet.maxs[VX] *= S;
		bbox3DCollDet.mins[VZ] *= S;
		bbox3DCollDet.maxs[VZ] *= S;
		bbox3DCollDet.mins[VY] *= 0.7F;
		bbox3DCollDet.maxs[VY] *= 0.8F;
	};

	// Cleanup
	file->Close();
	delete file;
	file	= 0;
	s_bConvertNoLOD = FALSE;
//	zERR_MESSAGE (5, 0, "D: MDL: ... Finished.");
};

// ****************************************************************************************************************

void zCModelPrototype::CalcAniBBox (zCModelAni* ani)
{
	// Assert: das ModelProto besitzt Meshes..
	assert (ani);
	if (!ani) return;

	zBOOL		found = FALSE;
	zTBBox3D	bboxResult;
	bboxResult.Init				();
	ani->PrepareAniDataAccess	();

	// die ani-Trafos sichern (fuer z.B. die naechste Ani..)
	int i;
	zMAT4	*trafoSave	= zNEW(zMAT4) [nodeList.GetNum()];
	for (i=0; i<nodeList.GetNum(); i++)		trafoSave[i]= nodeList[i]->trafo;

	for (i=0; i<ani->numFrames; i++) 
	{
		for (int j=0; j<ani->numNodes; j++) 
		{
			zCModelNode *node	= ani->nodeList[j];
			zVEC3		trans	= ani->GetTrans		(i,j);
			zCQuat		quat	= ani->GetQuat		(i,j);
			node->trafo			= Alg_Identity3D	();
			node->trafo.SetTranslation				(trans);
			quat.QuatToMatrix4						(node->trafo);
		};
		for (j=0; j<nodeList.GetNum(); j++) 
		{
			zCModelNode *node	= nodeList[j];
			// damit die KoordSystem der rootNode und des hostVob direkt aufeinanderliegen muss die Translation
			// der rootNode auf 0 gesetzt werden (passiert sonst halt beim Abspielen der Ani, aus der Translation
			// wird dort das Mass der Fortbewegung errechnet)
			if (j==0) node->trafo.SetTranslation (zVEC3(0,0,0));
			if (node->parentNode)	node->trafoObjToWorld = node->parentNode->trafoObjToWorld * node->trafo;
			else					node->trafoObjToWorld = node->trafo;
		};
			
		// Softskins
		for (int k=0; k<meshSoftSkinList.GetNum(); k++) 
		{
			zCMeshSoftSkin *mesh = meshSoftSkinList[k];
			for (int l=0; l<mesh->nodeOBBList.GetNum(); l++) 
			{
				// FIXME: ist so ein wenig slow.. aus dem OBB erst eine BBox3D machen ..
				zCModelNode		*node		= nodeList [ mesh->nodeIndexList[l] ];
				if (mesh->nodeOBBList[l]->extent[0]<zREAL(0.01F)) continue;			// FIXME! "node without obb" rausfiltern
				zTBBox3D		box			= mesh->nodeOBBList	[l]->GetBBox3D();
				box.Transform				(node->trafoObjToWorld, box);
				bboxResult.CalcGreaterBBox3D(box);
				found = TRUE;
			};
		};

		// NodeMeshes
		for (k=0; k<nodeList.GetNum(); k++) 
		{
			zCModelNode		*node		= nodeList[k];
			zCVisual		*visual		= node->GetNodeVisual();		if (!visual) continue;
			zTBBox3D		box			= visual->GetBBox3D	();
			box.Transform				(node->trafoObjToWorld, box);
			bboxResult.CalcGreaterBBox3D(box);
			found = TRUE;
		};
	};

	//
	for (i=0; i<nodeList.GetNum(); i++)		nodeList[i]->trafo = trafoSave[i];
	delete[] trafoSave; trafoSave=0;

	if (!found) {
		// falls keine Meshes vorhanden oder die Animation keine (?) Frames hat: neutral-BBox nehmen
		if (!found)
		{
			if (ani->numFrames<=0) {
				zERR_FAULT ("D: MDL: ani has zero frames of animation, should be at least 1!");
			} else {
				zERR_FAULT ("D: MDL: in order to calculate ani-bbox, model should have a mesh at this stage, but has not..");
			};
		};
		bboxResult	= this->bbox3D;
	};
	ani->aniBBox3DObjSpace	= bboxResult;
};

void zCModelPrototype::ResolveReferences() 
{ 
// FIXME: InsertSort() scheint nicht richtig zu gehen...
protoAnis.QuickSort();
	zBOOL ok = TRUE;
	for (int i=0; i<protoAnis.GetNumInList(); i++) 
	{ 
		// aniID eintragen
		protoAnis[i]->aniID = i;

		// Next-Ani Referenzen aufloesen
		if (protoAnis[i]->nextAniName.Length()>0) {
			if (protoAnis[i]->nextAniName==protoAnis[i]->GetAniName()) {
				protoAnis[i]->nextAni = protoAnis[i];
			} else {
				protoAnis[i]->nextAni = SearchAni (protoAnis[i]->nextAniName);
			};
			if (protoAnis[i]->nextAni==0) {
				zERR_WARNING ("D: zModel(zCModelAni::ResolveReferences): Could not find nextAni: "+protoAnis[i]->nextAniName
				+", this:"+protoAnis[i]->aniName); 
			};
		};

		// Alias-Anis Referenzen aufloesen
		ok = protoAnis[i]->ResolveAlias(this) && ok;
		ok = protoAnis[i]->ResolveComb (this) && ok;
	};
	if (!ok)
		zerr.Fatal ("D: FATAL ! .. goodbye !!");
};
 
///////////////////////////////////////////////////////////////////////////
//     Model Prototype :: Load Model Script .MDS
///////////////////////////////////////////////////////////////////////////

static zFILE	*mfile;
//static zBOOL	treeMissing;
static zSTRING	ascPath;		// ???

//NOTE MDS LOAD
enum
{
	zMDS_VERS = (01),

	zFCHUNK_MODELSCRIPT							= 0xF000,
		zFCHUNK_MDS_SOURCE						= 0xF100,
		zFCHUNK_MDS_MODEL						= 0xF200,
			zFCHUNK_MDS_MESHANDTREE				= 0xF300,
			zFCHUNK_MDS_REGISTERMESH			= 0xF400,
			zFCHUNK_MDS_ANIENUM					= 0xF500,
				zFCHUNK_MDS_ANIMAXFPS			= 0xF510,
				zFCHUNK_MDS_ANI					= 0xF520,
				zFCHUNK_MDS_ANIALIAS			= 0xF530,
				zFCHUNK_MDS_ANIBLEND			= 0xF540,
				zFCHUNK_MDS_ANISYNC				= 0xF550,
				zFCHUNK_MDS_ANIBATCH			= 0xF560,
				zFCHUNK_MDS_ANICOMB				= 0xF570,
				zFCHUNK_MDS_ANIDISABLE			= 0xF580,
				zFCHUNK_MDS_MODELTAG			= 0xF590,
				zFCHUNK_MDS_ANIEVENTS			= 0xF5A0,
					zFCHUNK_MDS_EVENTSFX		= 0xF5A1,
					zFCHUNK_MDS_EVENTSFXGRND	= 0xF5A2,
					zFCHUNK_MDS_EVENTTAG		= 0xF5A3,
					zFCHUNK_MDS_EVENTPFX		= 0xF5A4,
					zFCHUNK_MDS_EVENTPFXSTOP	= 0xF5A5,
					zFCHUNK_MDS_EVENTPFXGRND	= 0xF5A6,
					zFCHUNK_MDS_EVENTSETMESH	= 0xF5A7,
					zFCHUNK_MDS_EVENTSWAPMESH	= 0xF5A8,
					zFCHUNK_MDS_EVENTMMSTARTANI	= 0xF5A9,
					zFCHUNK_MDS_EVENTCAMTREMOR	= 0xF5AA,
				zFCHUNK_MDS_ANIEVENTS_END		= 0xF5AF,
			zFCHUNK_MDS_ANIENUM_END				= 0xF5FF,
		zFCHUNK_MDS_MODEL_END					= 0xF2FF,
	zFCHUNK_MDS_END								= 0xFFFF,
};

zDWORD zCModelPrototype::GetMDSFileVersion()
{
	// assert: vers nummern sind maximal 8BIT
	return zDWORD(zMDS_VERS);
};

void zCModelPrototype::SkipBlockMDS (int level) 
{
//	int level = 1;
	while (!mfile->Eof()) {
		mfile->Read (line);
			 if (line.Search ("{")!=-1) level++; 
		else if (line.Search ("}")!=-1) level--; 
		if (level==0) return;
	};
};

zBOOL zCModelPrototype::ReadMeshAndTreeMSB (zBOOL& hasFlag_DONT_USE_MESH, zCFileBIN &file) 
{
	zBOOL		res			= TRUE;
	zCModelAni	*aniPtr		= 0;
	int			firstFrame	= 0;
	int			lastFrame	= 0;
	zBOOL		dontUseMesh;
	zSTRING		ascName; 

	// zFCHUNK_MDS_MESHANDTREE
	zDWORD _dontUseMesh;
	file.BinReadDWord(_dontUseMesh);
	dontUseMesh = zBOOL(_dontUseMesh);
	file.BinReadString(ascName);
	file.BinSkipChunk();

	hasFlag_DONT_USE_MESH = dontUseMesh;
	hierarchySourceASC = ascName + ".ASC";

	if ( LoadMDH(GetModelProtoName() + ".MDH") )
	{
		if ( !dontUseMesh )
		{
			res = zCModelMeshLib::LoadMDM(ascName + ".MDM", this, 0, 0);
		};
		return res;
	}
	else
	{
		zSTRING aniName;
		zERR_MESSAGE (5, 0, "D: MDL: Parsing Model Hierarchy \"" + hierarchySourceASC + "\"");

		Load3DSMAXAsc(aniPtr, hierarchySourceASC, aniName, firstFrame, lastFrame, zMDL_MAX_IMPORT_MESH | zMDL_MAX_IMPORT_TREE);

		// Model-Hierarchy speichern
//		zoptions->ChangeDir		(DIR_ANIMS);
		zPATH fpath;
		fpath.SearchFile(hierarchySourceASC, zoptions->GetDirString(DIR_ANIMS));
		hierarchySourceASC = fpath.GetPath();
		SaveMDH();

		// Model-Mesh speichern (default-mesh)
		if ( !dontUseMesh )
		{
			zCModelMeshLib *meshLib = zNEW(zCModelMeshLib);
			meshLib->BuildFromModel(this);
			meshLib->SaveMDM(this);
			meshLib->Release();
		}
	};
	return res;
};

void zCModelPrototype::ReadMeshAndTree (zBOOL& hasFlag_DONT_USE_MESH, zCFileBIN &file) 
{
	zCModelAni	*aniPtr		= 0;
	int			firstFrame	= 0;
	int			lastFrame	= 0;
	zSTRING		ascName		= line; 
	CutMarks				(ascName);
	ascName.Delete			(".", zSTR_FROM); 
	hierarchySourceASC		= ascName + ".ASC";

	zBOOL dontUseMesh		= (line.Search ("DONT_USE_MESH")!=-1);
	hasFlag_DONT_USE_MESH	= dontUseMesh;

	// zFCHUNK_MDS_MESHANDTREE
	file.BinStartChunk(zFCHUNK_MDS_MESHANDTREE);
	zDWORD _dontUseMesh = zDWORD(dontUseMesh);
	file.BinWriteDWord(_dontUseMesh);
	file.BinWriteString(ascName);
	file.BinEndChunk();

	if (LoadMDH (GetModelProtoName()+".mdh")) {
		if (!dontUseMesh) {
			// LoadMDM() konvertiert autom., falls noch nicht im internen Format
			// hier nicht den ModelProtoName verwenden...
//			zBOOL res= zCModelMeshLib::LoadMDM	(GetModelProtoName()+".mdm", this,0,0);
			zCModelMeshLib::LoadMDM	(ascName+".mdm", this,0,0);
		};
		return;
	} else {
		zSTRING aniName;
		zERR_MESSAGE		(5, 0, "D: MDL: Parsing Model Hierarchy \""+hierarchySourceASC+"\"");

		Load3DSMAXAsc		(aniPtr, hierarchySourceASC, aniName, firstFrame, lastFrame, zMDL_MAX_IMPORT_MESH | zMDL_MAX_IMPORT_TREE);	// ani, mesh, tree , %

		// Model-Hierarchy speichern
//		zoptions->ChangeDir		(DIR_ANIMS);
		zPATH fpath			;
		fpath.SearchFile	(hierarchySourceASC, zoptions->GetDirString(DIR_ANIMS));
		hierarchySourceASC	= fpath.GetPath();
		SaveMDH				();

		// Model-Mesh speichern (default-mesh)
		if (!dontUseMesh) {
			zCModelMeshLib *meshLib = zNEW(zCModelMeshLib);
			meshLib->BuildFromModel	(this);
			meshLib->SaveMDM		(this);
			meshLib->Release		();
		}
	};
};

static zCArray<zSTRING> s_registerMeshList;

void zCModelPrototype::RegisterMesh(zCFileBIN &file) 
{
	zSTRING	ascName = line;
	CutMarks(ascName);
	ascName.Delete(".", zSTR_FROM); 
	ascName += ".ASC";

	// zFCHUNK_MDS_REGISTERMESH
	file.BinStartChunk(zFCHUNK_MDS_REGISTERMESH);
	file.BinWriteString(ascName);
	file.BinEndChunk();

	if (zCModelPrototype::S_GetAutoConvertMeshes())
	{
		s_registerMeshList.Insert (ascName);
		// .. an Ort und Stelle konvertieren klappt nicht. Wird am Ende des Lesens des .MDS in einem Rutsch gemacht
	};
};

static void GetMDSLineValue (const zSTRING& line, const zSTRING& key, zREAL &result) 
{
	int spos = line.Search(key);
	if (spos!=-1) {
		result = line.Deleted (0, spos+key.Length()).ToFloat();
	};
};

zBOOL zCModelPrototype::ReadAniEnumMSB (const zBOOL hasFlag_DONT_USE_MESH, zCFileBIN &file)
{
	zCModelAni		*aniPtr	= 0;
	int				numMAN	= 0;
	zREAL			maxFps;
	zREAL			resetMaxFps	= zMDL_MAX_FPS;
	zSTRING			aniName, ascName, nextAni, aniFlags, aniDir;
	int				firstFrame, lastFrame;
	int				layer;
	float			blendIn, blendOut;
	zREAL			lastRealSpeedFps;
	zBOOL			loadedMDMForAniConversion	= FALSE;
	zREAL			fps_min						= 999.0F;
	zREAL			fps_max						=-999.0F;
	zREAL			fps_avg						= 0;
	
	// zFCHUNK_MDS_ANIENUM
	zBOOL	res = FALSE;
	zWORD	id;
	zLONG	len;
	while (!file.BinEof())
	{ 
		maxFps = resetMaxFps;

		file.BinOpenChunk(id, len);
		switch (id)
		{ 
		case zFCHUNK_MDS_ANIMAXFPS:
			{
				file.BinReadFloat(resetMaxFps);
				file.BinSkipChunk();
			};
			break;
		case zFCHUNK_MDS_ANI:
			{
				if ( GetIgnoreAnis() )
				{
					aniPtr = 0;
					continue;
				};

				zREAL speed;
				zREAL collisionVolumeScale;
				
				file.BinReadString(aniName);
				file.BinReadInt(layer),
				file.BinReadString(nextAni);
				file.BinReadFloat(blendIn);
				file.BinReadFloat(blendOut);
				file.BinReadString(aniFlags);
				file.BinReadString(ascName);
				file.BinReadString(aniDir);
				file.BinReadInt(firstFrame);
				file.BinReadInt(lastFrame);
				file.BinReadFloat(maxFps);
				file.BinReadFloat(speed);
				file.BinReadFloat(collisionVolumeScale);
				file.BinSkipChunk();

				zBOOL loadOK		= FALSE;
				zBOOL justConverted = FALSE; 
				{
					aniPtr = zNEW(zCModelAni);
					aniPtr->SetAniType				(zMDL_ANI_TYPE_NORMAL);
					aniPtr->SetCollisionVolumeScale	(collisionVolumeScale);
					zSTRING scriptDefLine;
					loadOK = aniPtr->LoadMAN		(aniName + ".MAN", this, scriptDefLine);  // FIXME: , line); _MAN_SOURCE wird nicht mehr verglichen, Problem?
					numMAN++;
					if (loadOK) AddAni				(aniPtr); 
				};
				if (!loadOK) 
				{
					zERR_MESSAGE	(5, 0, "N: MSB: Parsing Ani \"" + aniName + "\" from \"" + ascName + "\"");
					Load3DSMAXAsc	(aniPtr, ascName, aniName, firstFrame, lastFrame, zMDL_MAX_IMPORT_ANI, maxFps); 
					justConverted	= TRUE;
					zERR_MESSAGE	(5, 0, "N: MSB: ... parsing finished.");
				};
				// Beachte: was wenn ASC-Ani dieselbe bleibt, aber die Params im MDS sich �ndern ?
				if (aniPtr) {
					aniPtr->SetAniName		(aniName);
					aniPtr->layer			= layer;
					aniPtr->nextAniName		= nextAni;
					aniPtr->SetBlendingSec	(blendIn, blendOut);
					aniPtr->SetFlags		(aniFlags); 
					aniPtr->aniDir			= (aniDir[0]=='R' ? zMDL_ANIDIR_REVERSE : zMDL_ANIDIR_FORWARD);
					lastRealSpeedFps		= aniPtr->fpsRate;

					if (justConverted) {
						// FIXME: 'SPD:x' macht hier Probleme, falls die Ani als .MAN eingelesen wird... => z.B. 'chest.mds', OPEN
						//        Warum nur ? ('justConverted' ist wahrscheinlich nur ein Hack..)
						if (speed!=0) {
							zREAL aniFpsScale	= speed / zREAL(aniPtr->fpsRateSource);
							aniPtr->fpsRate		= zREAL(((aniPtr->fpsRate) * aniFpsScale)); 
						};
					};

					// FIXME: flags ins .MAN speichern!
					aniPtr->CalcInPlaceFlag				();  // erst nach setFlags()
					aniPtr->CorrectRootNodeIdleMovement	();

					if (justConverted)
					{
						// muss fuer AniBBox-Berechnung ein Mesh noch eingeladen werden 
						// und ist dies noch nicht geschehen ?
						if (!loadedMDMForAniConversion)
						if (hasFlag_DONT_USE_MESH)
						{
							zSTRING mdmName				= hierarchySourceASC;
							mdmName.Delete				(".", zSTR_FROM); 
							zCModelMeshLib::LoadMDM		(mdmName + ".MDM", this, 0, 0);
							loadedMDMForAniConversion	= TRUE;
						};
						CalcAniBBox				(aniPtr);
						aniPtr->SaveMAN			(this, line);
					};
					fps_min = zMin (fps_min, aniPtr->GetFPSRate());
					fps_max = zMax (fps_max, aniPtr->GetFPSRate());
					fps_avg	+=aniPtr->GetFPSRate();
				};
			};
			break;
		case zFCHUNK_MDS_ANIALIAS:
			{
				if ( GetIgnoreAnis() ) continue;

				zSTRING aliasAni;

				file.BinReadString(aniName);
				file.BinReadInt(layer),
				file.BinReadString(nextAni);
				file.BinReadFloat(blendIn);
				file.BinReadFloat(blendOut);
				file.BinReadString(aniFlags);
				file.BinReadString(aliasAni);
				file.BinReadString(aniDir);
				file.BinSkipChunk();

				// neue Ani erzeugen
				aniPtr = zNEW(zCModelAni);
				aniPtr->SetAniType		(zMDL_ANI_TYPE_ALIAS);
				aniPtr->SetAniName		(aniName);
				aniPtr->layer			= layer;
				aniPtr->nextAniName		= nextAni;
				aniPtr->SetBlendingSec	(blendIn, blendOut);
				aniPtr->SetFlags		(aniFlags);
				aniPtr->aliasName		= aliasAni;
				aniPtr->aniDir			= (aniDir[0]=='R' ? zMDL_ANIDIR_REVERSE : zMDL_ANIDIR_FORWARD);
				AddAni (aniPtr);
			};
			break;
		case zFCHUNK_MDS_ANIBLEND:
			{
				if (GetIgnoreAnis()) continue;

				file.BinReadString(aniName);
//				file.BinReadInt(layer),
				file.BinReadString(nextAni);
				file.BinReadFloat(blendIn);
				file.BinReadFloat(blendOut);
				file.BinSkipChunk();
				
				// neue Ani erzeugen
				aniPtr = zNEW(zCModelAni);
				aniPtr->SetAniType		(zMDL_ANI_TYPE_BLEND);
				aniPtr->SetAniName		(aniName);
				aniPtr->SetBlendingSec	(blendIn, blendOut);
//				aniPtr->layer			= layer;
				aniPtr->nextAniName		= nextAni;
				AddAni(aniPtr);
				firstFrame = lastFrame = 0;  // fuer das aniEvent Parsing
			};
			break;
		case zFCHUNK_MDS_ANISYNC:
			{
				if (GetIgnoreAnis()) continue;

				file.BinReadString(aniName);
//				file.BinReadInt(layer),
				file.BinReadString(nextAni);
				file.BinSkipChunk();

				// neue Ani erzeugen
				aniPtr = zNEW(zCModelAni);
				aniPtr->SetAniType	(zMDL_ANI_TYPE_SYNC);
				aniPtr->SetAniName	(aniName);
//				aniPtr->layer		= layer;
				aniPtr->nextAniName = nextAni;
				AddAni (aniPtr);
				firstFrame = lastFrame = 0;  // fuer das aniEvent Parsing
			};
			break;
		case zFCHUNK_MDS_ANIBATCH:
			{
				// [BENDLIN] TODO: not implemented yet in MSB !!!
			};
			break;
		case zFCHUNK_MDS_ANICOMB:
			{
				if (GetIgnoreAnis()) continue;

				file.BinReadString	(aniName);
				file.BinReadInt		(layer),
				file.BinReadString	(nextAni);
				file.BinReadFloat	(blendIn);
				file.BinReadFloat	(blendOut);
				file.BinReadString	(aniFlags);
				file.BinReadString	(ascName);
				file.BinReadInt		(lastFrame);
				file.BinSkipChunk();

				// neue Ani erzeugen
				aniPtr = zNEW(zCModelAni);
				aniPtr->SetAniType		(zMDL_ANI_TYPE_COMB);
				aniPtr->SetAniName		(aniName);
				aniPtr->layer			= layer;
				aniPtr->nextAniName		= nextAni;
				aniPtr->SetBlendingSec	(blendIn, blendOut);
				aniPtr->SetFlags		(aniFlags);
				aniPtr->aliasName		= ascName+zSTRING(lastFrame);  // aliasName speichert den Namen der letzten Combi-Ani
				AddAni (aniPtr);
				firstFrame = lastFrame = 0;  // fuer das aniEvent Parsing
				// ani:		die FrameZahlen bei den *aniEvents werden ABSOLUT in bezug auf die Import-Frames angegeben (ani: 10-20, *aniEvent: 10-20);
				// aniComb:	die FrameZahlen bei den *aniEvents werden RELATIV in bezug auf die Import-Frames angegeben (ani: 10-20, *aniEvent:  0-10);
			};
			break;
		case zFCHUNK_MDS_ANIDISABLE:
			{
				file.BinReadString(aniName);
				file.BinSkipChunk();
				
				// neue Ani erzeugen
				aniPtr = zNEW(zCModelAni);
				aniPtr->SetAniType	(zMDL_ANI_TYPE_DISABLED);
				aniPtr->SetAniName	(aniName);
				AddAni(aniPtr);
				firstFrame = lastFrame = 0;  // fuer das aniEvent Parsing
			};
			break;
		case zFCHUNK_MDS_MODELTAG:
			{
				zCModelAniEvent *event = zNEW(zCModelAniEvent);

				event->aniEventType = zMDL_EVENT_TAG;
				file.BinReadString(event->tagString);
				for (int i=0; i<zCModelAniEvent::zMDL_ANIEVENT_MAXSTRING; i++)
					file.BinReadString(event->string[i]);
				file.BinSkipChunk();
				event->frameNr = 0;
				
				modelEvents.Insert(event);
				firstFrame = lastFrame = 0;  // fuer das aniEvent Parsing
			};
			break;
		case zFCHUNK_MDS_ANIEVENTS:
			{
				int numEvents;
				file.BinReadInt(numEvents);
				file.BinSkipChunk();
				if ( GetIgnoreAnis() ) continue;

				zCModelAniEvent *event		= zNEW(zCModelAniEvent)[numEvents];
				int				actEvent	= 0;
				int				frameNr;
				zREAL			aniFpsScale	= 1;
				if (aniPtr->fpsRateSource!=0)
					aniFpsScale = zREAL(lastRealSpeedFps) / zREAL(aniPtr->fpsRateSource);

				zBOOL	resEv = FALSE;
				zWORD	idEv;
				zLONG	lenEv;
				while (!file.BinEof())
				{ 
					if (actEvent > numEvents)
						zerr.Fatal("N: MSB: more effects in animation than specified in header!");

					if (actEvent < numEvents)
						event[actEvent].frameNr = 0;
					
					file.BinOpenChunk(idEv, lenEv);
					switch (idEv)
					{ 
					case zFCHUNK_MDS_EVENTSFX:
						{
							event[actEvent].aniEventType= zMDL_EVENT_SOUND;

							zSTRING sfxName;
							file.BinReadInt(frameNr);
							file.BinReadString(sfxName);
							file.BinReadFloat(event[actEvent].value1);
							file.BinReadFloat(event[actEvent].value2);
							file.BinSkipChunk();

							if (frameNr>0)
								event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
							event[actEvent].soundList.AllocAbs(1);
							event[actEvent].soundList.Insert(zsound->LoadSoundFXScript (sfxName));
							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTSFXGRND:
						{
							event[actEvent].aniEventType= zMDL_EVENT_SOUND_GRND;

							zSTRING sfxName;
							file.BinReadInt(frameNr);
							file.BinReadString(sfxName);
							file.BinReadFloat(event[actEvent].value1);
							file.BinReadFloat(event[actEvent].value2);
							file.BinSkipChunk();

							if (frameNr>0)
								event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));

							int errorLevel				= zerr.GetFilterLevel ();
							zerr.SetFilterLevel			(zERR_LV_NONE);
							event[actEvent].soundList.AllocAbs(zMAT_NUM_MAT_GROUP);
							for (int i=0; i<zMAT_NUM_MAT_GROUP; i++) {
								if (sfxName.Length()<=0)
									event[actEvent].soundList.InsertEnd (0);
								else
									event[actEvent].soundList.InsertEnd (zsound->LoadSoundFXScript (sfxName+"_"+zCMaterial::GetMatGroupString (zTMat_Group(i))));
							};
							zerr.SetFilterLevel			(errorLevel);

							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTTAG:
						{
							event[actEvent].aniEventType= zMDL_EVENT_TAG;

							file.BinReadInt(frameNr);
							file.BinReadString(event[actEvent].tagString);
							for (int i=0; i<zCModelAniEvent::zMDL_ANIEVENT_MAXSTRING; i++)
								file.BinReadString(event[actEvent].string[i]);
							file.BinSkipChunk();

							if (frameNr>0)
								event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTPFX:
						{
							event[actEvent].aniEventType= zMDL_EVENT_PFX;

							zSTRING emitterName;
							file.BinReadInt(frameNr);
							file.BinReadFloat(event[actEvent].value1);
							file.BinReadString(emitterName);
							file.BinReadString(event[actEvent].string[0]);
							file.BinReadFloat(event[actEvent].value2);
							file.BinSkipChunk();

							zCParticleEmitter* pfxEmitter = zCParticleFX::SearchParticleEmitter(emitterName);
							event[actEvent].pfxEmitterList.Insert(pfxEmitter);
							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTPFXSTOP:
						{
							event[actEvent].aniEventType= zMDL_EVENT_PFX_STOP;

							file.BinReadInt(frameNr);
							file.BinReadFloat(event[actEvent].value1);
							file.BinSkipChunk();

							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTPFXGRND:
						{
							event[actEvent].aniEventType= zMDL_EVENT_PFX_GRND;
							
							file.BinReadInt(frameNr);
							file.BinSkipChunk();

							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTSETMESH:
						{
							event[actEvent].aniEventType= zMDL_EVENT_SETMESH;

							file.BinReadInt(frameNr);
							file.BinReadString(event[actEvent].string[0]);
							file.BinSkipChunk();

							if (frameNr>0)
								event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTSWAPMESH:
						{
							event[actEvent].aniEventType= zMDL_EVENT_SWAPMESH;

							file.BinReadInt(frameNr);
							file.BinReadString(event[actEvent].string[0]);
							file.BinReadString(event[actEvent].string[1]);
							file.BinSkipChunk();

							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTMMSTARTANI:
						{
							event[actEvent].aniEventType= zMDL_EVENT_MM_STARTANI;

							file.BinReadInt(frameNr);
							file.BinReadString(event[actEvent].string[0]);
							file.BinReadString(event[actEvent].string[1]);
							file.BinReadFloat(event[actEvent].value1);
							file.BinReadFloat(event[actEvent].value2);
							file.BinSkipChunk();

							if (frameNr>0)
								event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
							actEvent++;
						};
						break;
					case zFCHUNK_MDS_EVENTCAMTREMOR:
						{
							event[actEvent].aniEventType= zMDL_EVENT_CAM_TREMOR;
							
							file.BinReadInt(frameNr);
							file.BinReadFloat(event[actEvent].value1);
							file.BinReadFloat(event[actEvent].value2);
							file.BinReadFloat(event[actEvent].value3);
							file.BinReadFloat(event[actEvent].value4);
							file.BinSkipChunk();

							if ( frameNr > 0 )
							  event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));

							actEvent++;
						};
						break;
					case zFCHUNK_MDS_ANIEVENTS_END:
						{
							file.BinSkipChunk();
							resEv = TRUE;
						};
						break;
					default:
						file.BinSkipChunk();
					};
					// FIXME: "fps:__"
					// check ist hier leider nur auf 'normalen' mit Ani-Data moeglich, da fuer die anderen die 
					// frame-Ranges noch nicht bekannt sind => dieses werden erst spaeter 'resolved'
					if ( !resEv )
					if (aniPtr->GetAniType()==zMDL_ANI_TYPE_NORMAL)
					if ( (event[actEvent-1].frameNr > aniPtr->numFrames - 1) || (event[actEvent-1].frameNr < 0) ) 
					{
						zERR_WARNING ("N: MSB: Frame-Number is out of bounds (AniEvents), ani: " + aniPtr->GetAniName());
						// zur Sicherheit auf legalen Bereich clampen
						zClamp(event[actEvent-1].frameNr, 0, aniPtr->numFrames - 1);
					};
					if ( resEv ) break;
				};
				if ( !resEv )
				{
					numEvents = 0;
					delete event; event = 0;
				};
				aniPtr->numAniEvents	= numEvents;
				aniPtr->aniEvents		= event;
			};
			break;
		case zFCHUNK_MDS_ANIENUM_END: 
			{
				file.BinSkipChunk();
				res = TRUE;
			}
			break;
		default:
			file.BinSkipChunk();
		};
		if ( res ) break;
	};

	// evtl. Meshes wieder rauswerfen, die fuer die Ani-BBox Berechnung noetig waren ?
	if (loadedMDMForAniConversion)
	if (hasFlag_DONT_USE_MESH)
	{
		ReleaseMeshes();
	};

	zERR_MESSAGE	(5, 0, "N: MSB: numAnis: " + zSTRING(protoAnis.GetNumInList()) + ", numMAN: " + zSTRING(numMAN)); 
	fps_avg			/= zREAL(numMAN);
	zERR_MESSAGE	(5, 0, "N: MSB: fpsRates min, max, avg: " + zSTRING(fps_min, 4) + ", " + zSTRING(fps_max, 4) + ", " + zSTRING(fps_avg, 4));

	return res;
};

void zCModelPrototype::ReadAniEnum (const zBOOL hasFlag_DONT_USE_MESH, zCFileBIN &file)
{
	zCModelAni		*aniPtr		= 0;
	int				numMAN		= 0;
	zREAL			maxFps;
	zREAL			resetMaxFps	= zMDL_MAX_FPS;
	zSTRING			line;
	zSTRING			aniName, ascName, nextAni, aniFlags, aniDir;
	zSTRING			arg;
	zSTRING			sfxName;
	int				firstFrame, lastFrame;
	int				layer;
	float			blendIn, blendOut;
	zREAL			lastRealSpeedFps;
	const int		MAX_ANI_EVENT				= 16;
	zSTRING			aniEventLines				[MAX_ANI_EVENT];
	zBOOL			loadedMDMForAniConversion	= FALSE;
	zREAL			fps_min						= 999.0F;
	zREAL			fps_max						=-999.0F;
	zREAL			fps_avg						= 0;

	zERR_MESSAGE	(5, 0, "D: MDL: Parsing 'aniEnum'...");

	// zFCHUNK_MDS_ANIENUM
	file.BinStartChunk(zFCHUNK_MDS_ANIENUM);
	file.BinEndChunk();

	while (!mfile->Eof()) { 
		mfile->Read (line); if (line.IsEmpty()) continue;
		if (line.Search ("//")!=-1) continue;
		line.Upper();

		//
		arg = line;
		arg.Delete ("(", zSTR_TO);
		arg.Delete (")", zSTR_FROM);

		maxFps		= resetMaxFps;

		if (line.Search ("ANIMAXFPS")!=-1)
		{
			resetMaxFps = arg.PickWord ( 1, trenn, skip).ToFloat();
			// zFCHUNK_MDS_ANIMAXFPS
			file.BinStartChunk(zFCHUNK_MDS_ANIMAXFPS);
			file.BinWriteFloat(resetMaxFps);
			file.BinEndChunk();
		}
		else
		if ((line.Search ("ANI ")!=-1) || (line.Search ("ANI\t")!=-1) || (line.Search ("ANI(")!=-1)) {
			if (GetIgnoreAnis()) {
				aniPtr = 0;
				continue;
			};

			// FIXME: Die String-Ops hier sind beschleunigbar.. (auch: 'GetToken()')

			// ani (1 "T_walk_end" "S_stand" 0.0 0.5 M.	"walk.asc" F 0 23 FPS:25 SPD:12)
			aniName		= arg.PickWord ( 1, trenn, skip);	CutMarks (aniName);
			layer		= arg.PickWord ( 2, trenn, skip).ToInt();
			nextAni		= arg.PickWord ( 3, trenn, skip);	CutMarks (nextAni);
			blendIn		= arg.PickWord ( 4, trenn, skip).ToFloat(); 
			blendOut	= arg.PickWord ( 5, trenn, skip).ToFloat();
			aniFlags	= arg.PickWord ( 6, trenn, skip);
			ascName		= arg.PickWord ( 7, trenn, skip);	CutMarks (ascName);
			aniDir		= arg.PickWord ( 8, trenn, skip);
			firstFrame	= arg.PickWord ( 9, trenn, skip).ToInt();
			lastFrame	= arg.PickWord (10, trenn, skip).ToInt();
			zREAL speed					= 0;
			zREAL collisionVolumeScale	= 1;
			{
//				zSTRING s	= arg.PickWord (11, trenn, skip);
				int		spos; 
				spos = arg.Search("FPS:");
				if (spos!=-1) {
					zSTRING tmp	(arg);
					tmp.Delete	("FPS:", zSTR_TO);
					maxFps		= tmp.ToFloat();
				};
				spos = arg.Search("SPD:");
				if (spos!=-1) {
					zSTRING tmp	(arg);
					tmp.Delete	("SPD:", zSTR_TO); 
					speed		= tmp.ToFloat();
				};
				spos = arg.Search("CVS:");
				if (spos!=-1) {
					zSTRING tmp	(arg);
					tmp.Delete	("CVS:", zSTR_TO); 
					collisionVolumeScale = tmp.ToFloat();
					zClamp (collisionVolumeScale, zREAL(0), zREAL(10));
				};
			};

			// zFCHUNK_MDS_ANI
			file.BinStartChunk(zFCHUNK_MDS_ANI);
			file.BinWriteString(aniName);
			file.BinWriteInt(layer),
			file.BinWriteString(nextAni);
			file.BinWriteFloat(blendIn);
			file.BinWriteFloat(blendOut);
			file.BinWriteString(aniFlags);
			file.BinWriteString(ascName);
			file.BinWriteString(aniDir);
			file.BinWriteInt(firstFrame);
			file.BinWriteInt(lastFrame);
			file.BinWriteFloat(maxFps);		// optional?
			file.BinWriteFloat(speed);
			file.BinWriteFloat(collisionVolumeScale);
			file.BinEndChunk();

			ascName = ascPath + ascName; 

			// firstFrame, lastFrame korrekt ?
			if ((lastFrame<firstFrame) && (lastFrame!=-1))
				zERR_FATAL ("D: MDL: lastFrame is less than firstFrame");

			// AddAni (aniName, ascName, startFrame, lastFrame);
//			Load3DSMAXAsc (ascName, aniName, firstFrame, lastFrame, TRUE, FALSE, treeMissing);
			zBOOL loadOK		= FALSE;
			zBOOL justConverted = FALSE; 

			{
				aniPtr = zNEW(zCModelAni);
				aniPtr->SetAniType				(zMDL_ANI_TYPE_NORMAL);
				aniPtr->SetCollisionVolumeScale	(collisionVolumeScale);
				loadOK = aniPtr->LoadMAN		(aniName+".man", this, line);
				numMAN++;
				if (loadOK) AddAni				(aniPtr); 
			};
			if (!loadOK) 
			{
				zERR_MESSAGE					(5, 0, "D: MDL: Parsing Ani \""+aniName+"\" from \""+ascName+"\"");
				Load3DSMAXAsc					(aniPtr, ascName, aniName, firstFrame, lastFrame, zMDL_MAX_IMPORT_ANI, maxFps); 
				justConverted					= TRUE;
				zERR_MESSAGE					(5, 0, "D: MDL: ... parsing finished.");
			};
			// Beachte: was wenn ASC-Ani dieselbe bleibt, aber die Params im MDS sich �ndern ?
			if (aniPtr) {
				aniPtr->SetAniName		(aniName);
				aniPtr->layer			= layer;
				aniPtr->nextAniName		= nextAni;
				aniPtr->SetBlendingSec	(blendIn, blendOut);
				aniPtr->SetFlags		(aniFlags); 
				aniPtr->aniDir			= (aniDir[0]=='R' ? zMDL_ANIDIR_REVERSE : zMDL_ANIDIR_FORWARD);
				lastRealSpeedFps		= aniPtr->fpsRate;

				if (justConverted) {
					// FIXME: 'SPD:x' macht hier Probleme, falls die Ani als .MAN eingelesen wird... => z.B. 'chest.mds', OPEN
					//        Warum nur ? ('justConverted' ist wahrscheinlich nur ein Hack..)
					if (speed!=0) {
						zREAL aniFpsScale	= speed / zREAL(aniPtr->fpsRateSource);
						aniPtr->fpsRate		= zREAL(((aniPtr->fpsRate) * aniFpsScale)); 
					};
				};

				// FIXME: flags ins .MAN speichern!
				aniPtr->CalcInPlaceFlag				();			// erst nach setFlags()
				aniPtr->CorrectRootNodeIdleMovement	();

				if (justConverted)
				{
					// muss fuer AniBBox-Berechnung ein Mesh noch eingeladen werden 
					// und ist dies noch nicht geschehen ?
					if (!loadedMDMForAniConversion)
					if (hasFlag_DONT_USE_MESH)
					{
						zSTRING mdmName				= hierarchySourceASC;
						mdmName.Delete				(".", zSTR_FROM); 
						zCModelMeshLib::LoadMDM		(mdmName+".mdm", this,0,0);
						loadedMDMForAniConversion	= TRUE;
					};
					CalcAniBBox				(aniPtr);

					aniPtr->SaveMAN			(this, line);
				};
				fps_min = zMin (fps_min, aniPtr->GetFPSRate());
				fps_max = zMax (fps_max, aniPtr->GetFPSRate());
				fps_avg	+=aniPtr->GetFPSRate();
			};
		} else
		if (line.Search ("ANIALIAS")!=-1) {
			if (GetIgnoreAnis()) continue;

			// aniAlias	("T_strafe_left"	1	"S_stand"	0.0	0.0	M.	"T_strafe_right"	R)
			zSTRING aliasAni;
			aniName		= arg.PickWord ( 1, trenn, skip);	CutMarks (aniName);
			layer		= arg.PickWord ( 2, trenn, skip).ToInt();
			nextAni		= arg.PickWord ( 3, trenn, skip);	CutMarks (nextAni);
			blendIn		= arg.PickWord ( 4, trenn, skip).ToFloat();
			blendOut	= arg.PickWord ( 5, trenn, skip).ToFloat();
			aniFlags	= arg.PickWord ( 6, trenn, skip);
			aliasAni	= arg.PickWord ( 7, trenn, skip);	CutMarks (aliasAni);
			aniDir		= arg.PickWord ( 8, trenn, skip);

			// zFCHUNK_MDS_ANIALIAS
			file.BinStartChunk(zFCHUNK_MDS_ANIALIAS);
			file.BinWriteString(aniName);
			file.BinWriteInt(layer),
			file.BinWriteString(nextAni);
			file.BinWriteFloat(blendIn);
			file.BinWriteFloat(blendOut);
			file.BinWriteString(aniFlags);
			file.BinWriteString(aliasAni);
			file.BinWriteString(aniDir);
			file.BinEndChunk();

			// neue Ani erzeugen
			aniPtr = zNEW(zCModelAni);
			aniPtr->SetAniType (zMDL_ANI_TYPE_ALIAS);
			aniPtr->SetAniName (aniName);
			aniPtr->layer			= layer;
			aniPtr->nextAniName		= nextAni;
			aniPtr->SetBlendingSec	(blendIn, blendOut);
			aniPtr->SetFlags		(aniFlags);
			aniPtr->aliasName		= aliasAni;
			aniPtr->aniDir			= (aniDir[0]=='R' ? zMDL_ANIDIR_REVERSE : zMDL_ANIDIR_FORWARD);
			AddAni (aniPtr);
		} else
		if (line.Search ("ANIBLEND")!=-1) { 
			if (GetIgnoreAnis()) continue;
			// aniBlend	("T_walk_to_run" "S_run" blendIn blendOut)
			aniName		= arg.PickWord ( 1, trenn, skip);	CutMarks (aniName);
//			layer		= arg.PickWord ( 2, trenn, skip).ToInt();
			nextAni		= arg.PickWord ( 2, trenn, skip);	CutMarks (nextAni);
			blendIn		= arg.PickWord ( 3, trenn, skip).ToFloat();
			blendOut	= arg.PickWord ( 4, trenn, skip).ToFloat();

			// zFCHUNK_MDS_ANIBLEND
			file.BinStartChunk(zFCHUNK_MDS_ANIBLEND);
			file.BinWriteString(aniName);
//			file.BinWriteInt(layer),
			file.BinWriteString(nextAni);
			file.BinWriteFloat(blendIn);
			file.BinWriteFloat(blendOut);
			file.BinEndChunk();
			
			// neue Ani erzeugen
			aniPtr = zNEW(zCModelAni);
			aniPtr->SetAniType		(zMDL_ANI_TYPE_BLEND);
			aniPtr->SetAniName		(aniName);
			aniPtr->SetBlendingSec	(blendIn, blendOut);
//			aniPtr->layer		= layer;
			aniPtr->nextAniName = nextAni;
			AddAni (aniPtr);
			firstFrame	= lastFrame	= 0;							// fuer das aniEvent Parsing
		} else
		if (line.Search ("ANISYNC")!=-1) {
			if (GetIgnoreAnis()) continue;
			// aniSync	("T_walk_to_run"	"S_run"		[0.0])
			aniName		= arg.PickWord ( 1, trenn, skip);	CutMarks (aniName);
//			layer		= arg.PickWord ( 2, trenn, skip).ToInt();
			nextAni		= arg.PickWord ( 2, trenn, skip);	CutMarks (nextAni);

			// zFCHUNK_MDS_ANISYNC
			file.BinStartChunk(zFCHUNK_MDS_ANISYNC);
			file.BinWriteString(aniName);
//			file.BinWriteInt(layer),
			file.BinWriteString(nextAni);
			file.BinEndChunk();

			// neue Ani erzeugen
			aniPtr = zNEW(zCModelAni);
			aniPtr->SetAniType (zMDL_ANI_TYPE_SYNC);
			aniPtr->SetAniName (aniName);
//			aniPtr->layer		= layer;
			aniPtr->nextAniName = nextAni;
			AddAni (aniPtr);
			firstFrame	= lastFrame	= 0;							// fuer das aniEvent Parsing
		} else
		if (line.Search ("ANIBATCH")!=-1) {
			if (GetIgnoreAnis()) { 
				SkipBlockMDS(0); 
				continue;
			};

			// [BENDLIN] TODO, not implemented yet in MSB !!!

			// aniBatch	("T_walk_start")
			// {
			//		*aniBatch	("T_1h_walk_start_top")
			//		*aniBatch	("T_1h_walk_start_bottom")
			// }
			aniName		= arg.PickWord ( 1, trenn, skip);	CutMarks (aniName);
			// neue Ani erzeugen
			aniPtr = zNEW(zCModelAni);
			aniPtr->SetAniType (zMDL_ANI_TYPE_BATCH);
			aniPtr->SetAniName (aniName);
			AddAni (aniPtr);

			// aniBatch als 1 aniEvent realisieren
			aniPtr->numAniEvents	= 1;
			aniPtr->aniEvents		= zNEW(zCModelAniEvent)[1];
			int actNr=0;
			while (!mfile->Eof()) { 
				mfile->Read (line);
				line.Upper();
				if (line.Search ("//"		)!=-1) continue;
				if (line.Search ("*ANIBATCH")!=-1) {
					line.Delete ("(", zSTR_TO);
					line.Delete (")", zSTR_FROM);
					line = line.PickWord ( 1, trenn, skip);	CutMarks (line);
					if (actNr>=zCModelAniEvent::zMDL_ANIEVENT_MAXSTRING)
						zERR_FATAL("D: zModel(zCModelPrototype::ReadAniEnum): more than 4 anis in aniBatch !");
					aniPtr->aniEvents[0].string[actNr] = line;
					actNr++;
				} else
				if (line.Search ("}"		)!=-1) break;
			};
			if (actNr==0) zERR_FATAL("D: zModel(zCModelPrototype::ReadAniEnum): aniBatch without anis !");
			aniPtr->aniEvents[0].frameNr = actNr;
			firstFrame	= lastFrame	= 0;							// fuer das aniEvent Parsing
		} else
		if (line.Search ("ANICOMB")!=-1) {
			if (GetIgnoreAnis()) continue;
			// aniComb	("s_bow_aim"	1	"s_bow_aim" 0.1	0.1	..	"c_bow_" 9)
			aniName		= arg.PickWord ( 1, trenn, skip);	CutMarks (aniName);
			layer		= arg.PickWord ( 2, trenn, skip).ToInt();
			nextAni		= arg.PickWord ( 3, trenn, skip);	CutMarks (nextAni);
			blendIn		= arg.PickWord ( 4, trenn, skip).ToFloat(); 
			blendOut	= arg.PickWord ( 5, trenn, skip).ToFloat();
			aniFlags	= arg.PickWord ( 6, trenn, skip);
			ascName		= arg.PickWord ( 7, trenn, skip);	CutMarks (ascName);
			lastFrame	= arg.PickWord ( 8, trenn, skip).ToInt();

			// zFCHUNK_MDS_ANICOMB
			file.BinStartChunk	(zFCHUNK_MDS_ANICOMB);
			file.BinWriteString	(aniName);
			file.BinWriteInt	(layer),
			file.BinWriteString	(nextAni);
			file.BinWriteFloat	(blendIn);
			file.BinWriteFloat	(blendOut);
			file.BinWriteString	(aniFlags);
			file.BinWriteString	(ascName);
			file.BinWriteInt	(lastFrame);
			file.BinEndChunk();

			// neue Ani erzeugen
			aniPtr = zNEW(zCModelAni);
			aniPtr->SetAniType		(zMDL_ANI_TYPE_COMB);
			aniPtr->SetAniName		(aniName);
			aniPtr->layer			= layer;
			aniPtr->nextAniName		= nextAni;
			aniPtr->SetBlendingSec	(blendIn, blendOut);
			aniPtr->SetFlags		(aniFlags);
			aniPtr->aliasName		= ascName+zSTRING(lastFrame);	// aliasName speichert den Namen der letzten Combi-Ani
			AddAni (aniPtr);
			firstFrame	= lastFrame	= 0;							// fuer das aniEvent Parsing
			// ani:			die FrameZahlen bei den *aniEvents werden absolut in bezug auf die Import-Frames angegeben (ani: 10-20, *aniEvent: 10-20);
			// aniComb:		die FrameZahlen bei den *aniEvents werden relativ in bezug auf die Import-Frames angegeben (ani: 10-20, *aniEvent:  0-10);
		} else
		if (line.Search ("ANIDISABLE")!=-1) {
			aniName		= arg.PickWord ( 1, trenn, skip);	CutMarks (aniName);

			// zFCHUNK_MDS_ANIDISABLE
			file.BinStartChunk	(zFCHUNK_MDS_ANIDISABLE);
			file.BinWriteString	(aniName);
			file.BinEndChunk();
			
			// neue Ani erzeugen
			aniPtr = zNEW(zCModelAni);
			aniPtr->SetAniType	(zMDL_ANI_TYPE_DISABLED);
			aniPtr->SetAniName	(aniName);
			AddAni(aniPtr);
			firstFrame = lastFrame = 0;  // fuer das aniEvent Parsing
		} else
		if (line.Search ("MODELTAG")!=-1) {
			zCModelAniEvent *event = zNEW(zCModelAniEvent);
			
			event->aniEventType = zMDL_EVENT_TAG;
			event->tagString	= CutMarks2(arg.PickWord (1, "\"", "\""));
			// zFCHUNK_MDS_MODELTAG
			file.BinStartChunk(zFCHUNK_MDS_MODELTAG);
			file.BinWriteString(event->tagString);
			for (int i=0; i<zCModelAniEvent::zMDL_ANIEVENT_MAXSTRING; i++)
			{
				event->string[i] = CutMarks2(arg.PickWord (3+(i*2), "\"", "\""));
				file.BinWriteString(event->string[i]);
			};
			file.BinEndChunk();
			event->frameNr = 0;
			
			modelEvents.Insert(event);
			firstFrame = lastFrame = 0;  // fuer das aniEvent Parsing
		} else

		//
		// Ani-Events
		//
		if ((line.Search ("{")!=-1) && (aniPtr)) {
			if (GetIgnoreAnis()) { 
				SkipBlockMDS(1); 
				continue;
			};

			// Events zaehlen
			int numEvents	= 0;
			while (!mfile->Eof()) {
				mfile->Read (line);
				line.Upper();
					 if (line.Search ("//"		)!=-1) continue;
					 if (line.Search ("*EVENT"	)!=-1) { aniEventLines[numEvents] = line; numEvents++; }
				else if (line.Search ("}"		)!=-1) break;
			};
 
			if (aniPtr->GetAniType()==zMDL_ANI_TYPE_ALIAS) {
				zERR_FAULT ("D: MDL: aniAlias are not allowed to have *aniEvents: "+zSTRING(aniPtr->GetAniName()));
				numEvents=0;
			};
			// Ani-Event-Block
			if (numEvents>0) {
				
				// zFCHUNK_MDS_ANIEVENTS
				file.BinStartChunk(zFCHUNK_MDS_ANIEVENTS);
				file.BinWriteInt(numEvents);
				file.BinEndChunk();

				zCModelAniEvent *event		= zNEW(zCModelAniEvent) [numEvents];
				int				actEvent	= 0;
				int				frameNr;
				zREAL			aniFpsScale	= 1;
				if (aniPtr->fpsRateSource!=0)	aniFpsScale	= zREAL(lastRealSpeedFps) / zREAL(aniPtr->fpsRateSource);
//				zREAL			aniFpsScale	= zREAL(aniPtr->fpsRate) / zREAL(aniPtr->fpsRateSource);
				zSTRING			arg;

				while (actEvent<numEvents) 
				{
					line	= aniEventLines[actEvent];
					arg		= line;
					arg.Delete ("(", zSTR_TO);
					arg.Delete (")", zSTR_FROM);

					//
					if (line.Search ("}"	 )!=-1)		break;
					if (line.Search ("//"	 )!=-1)		continue;
					if (line.Search ("*EVENT")==-1)		continue;

					if (actEvent>=numEvents) {
						zerr.Fatal ("D: !!! READ_ANI_ENUM !!!  Argh !!!");
					}

					//
					event[actEvent].frameNr = 0;

					if (line.Search ("*EVENTSFXGRND")!=-1) {				// muss VOR *eventSFX
						event[actEvent].aniEventType= zMDL_EVENT_SOUND_GRND;
						frameNr						=			arg.PickWord (1, trenn, skip).ToInt();
						sfxName						= CutMarks2(arg.PickWord (2, trenn, skip));
						zREAL range					= zMDL_DEFAULT_RADIUS_EVENTSFXGRND;
						GetMDSLineValue				(arg, "R:", range);
						event[actEvent].value1		= zMin (range, zMDL_MAX_RADIUS_EVENTSFX);
						event[actEvent].value2		= (arg.Search("EMPTY_")==-1) ? 1.0F : 0.0F;			// "EMPTY_SLOW"

						// zFCHUNK_MDS_EVENTSFXGRND
						file.BinStartChunk(zFCHUNK_MDS_EVENTSFXGRND);
						file.BinWriteInt(frameNr);
						file.BinWriteString(sfxName);
						file.BinWriteFloat(event[actEvent].value1);
						file.BinWriteFloat(event[actEvent].value2);
						file.BinEndChunk();

						if (frameNr>0)
							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));

						int errorLevel				= zerr.GetFilterLevel ();
						zerr.SetFilterLevel			(zERR_LV_NONE);
						event[actEvent].soundList.AllocAbs(zMAT_NUM_MAT_GROUP);
						for (int i=0; i<zMAT_NUM_MAT_GROUP; i++) {
							if (sfxName.Length()<=0)
								event[actEvent].soundList.InsertEnd (0);
							else
								event[actEvent].soundList.InsertEnd (zsound->LoadSoundFXScript (sfxName+"_"+zCMaterial::GetMatGroupString (zTMat_Group(i))));
						};
						zerr.SetFilterLevel			(errorLevel);

						actEvent++;
					} else
					if (line.Search ("*EVENTSFX"	)!=-1) {
						// *eventSFX		(frameNr [sfxHandle] "SOUND_NAME" )
						event[actEvent].aniEventType= zMDL_EVENT_SOUND;
						frameNr						=			arg.PickWord (1, trenn, skip).ToInt();
						sfxName						= CutMarks2(arg.PickWord (2, trenn, skip));
//						event[actEvent].prob		=			arg.PickWord (3, trenn, skip).ToFloat();
						zREAL range					= zMDL_DEFAULT_RADIUS_EVENTSFX;
						GetMDSLineValue				(arg, "R:", range);
						event[actEvent].value1		= zMin (range, zMDL_MAX_RADIUS_EVENTSFX);
						event[actEvent].value2		= (arg.Search("EMPTY_")==-1) ? 1.0F : 0.0F;			// "EMPTY_SLOW"
						
						// zFCHUNK_MDS_EVENTSFX
						file.BinStartChunk(zFCHUNK_MDS_EVENTSFX);
						file.BinWriteInt(frameNr);
						file.BinWriteString(sfxName);
						file.BinWriteFloat(event[actEvent].value1);
						file.BinWriteFloat(event[actEvent].value2);
						file.BinEndChunk();

						if (frameNr>0)
							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
						event[actEvent].soundList.AllocAbs(1);
						event[actEvent].soundList.Insert(zsound->LoadSoundFXScript (sfxName));
						actEvent++;
					} else
					if (line.Search ("*EVENTSWAPMESH")!=-1) {
						event[actEvent].aniEventType= zMDL_EVENT_SWAPMESH;
						frameNr						=			arg.PickWord (1, trenn, skip).ToInt();
						event[actEvent].string[0]	= CutMarks2(arg.PickWord (2, trenn, skip));
						event[actEvent].string[1]	= CutMarks2(arg.PickWord (3, trenn, skip));
						event[actEvent].frameNr		= int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));

						// zFCHUNK_MDS_EVENTSWAPMESH
						file.BinStartChunk(zFCHUNK_MDS_EVENTSWAPMESH);
						file.BinWriteInt(frameNr);
						file.BinWriteString(event[actEvent].string[0]);
						file.BinWriteString(event[actEvent].string[1]);
						file.BinEndChunk();

						actEvent++;
					} else
					if (line.Search ("*EVENTTAG")!=-1) {
//						ReadAniEventTag (arg, &event[actEvent]);
						event[actEvent].aniEventType= zMDL_EVENT_TAG;
						frameNr						=			arg.PickWord (1, trenn, skip).ToInt();
						event[actEvent].tagString	= CutMarks2(arg.PickWord (2, "\"", "\""));

						// zFCHUNK_MDS_EVENTTAG
						file.BinStartChunk(zFCHUNK_MDS_EVENTTAG);
						file.BinWriteInt(frameNr);
						file.BinWriteString(event[actEvent].tagString);
						for (int i=0; i<zCModelAniEvent::zMDL_ANIEVENT_MAXSTRING; i++)
						{
							event[actEvent].string[i] = CutMarks2(arg.PickWord (4+(i*2), "\"", "\""));
							file.BinWriteString(event[actEvent].string[i]);
						};
						file.BinEndChunk();

						if (frameNr>0)
							event[actEvent].frameNr		= int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
						actEvent++;
					} else
					if (line.Search ("*EVENTPFXSTOP")!=-1) {
						// *eventPFXStop	(frameNr "handleINT" )
						event[actEvent].aniEventType= zMDL_EVENT_PFX_STOP;
						frameNr					= arg.PickWord (1, trenn, skip).ToInt();
						event[actEvent].value1	= arg.PickWord (2, trenn, skip).ToFloat();	// handle

						// zFCHUNK_MDS_EVENTPFXSTOP
						file.BinStartChunk(zFCHUNK_MDS_EVENTPFXSTOP);
						file.BinWriteInt(frameNr);
						file.BinWriteFloat(event[actEvent].value1);
						file.BinEndChunk();

						event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
						actEvent++;
					} else
					if (line.Search ("*EVENTPFXGRND")!=-1) {
						// *eventPFX		(frameNr "handleINT" "pfxName" "nodeName")
						event[actEvent].aniEventType= zMDL_EVENT_PFX_GRND;
						frameNr = arg.PickWord (1, trenn, skip).ToInt();

						// zFCHUNK_MDS_EVENTPFXGRND
						file.BinStartChunk(zFCHUNK_MDS_EVENTPFXGRND);
						file.BinWriteInt(frameNr);
						file.BinEndChunk();

						event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
						actEvent++;
					} else
					if (line.Search ("*EVENTPFX")!=-1) {
						// *eventPFX		(frameNr [pfxHandle] "pfxName" "nodeName" [ATTACH])
						event[actEvent].aniEventType= zMDL_EVENT_PFX;
						frameNr						=			arg.PickWord (1, trenn, skip).ToInt();
						event[actEvent].value1		=			arg.PickWord (2, trenn, skip).ToFloat();	// handle
						zSTRING emitterName = arg.PickWord (2, "\"", "\"");
						zCParticleEmitter* pfxEmitter = zCParticleFX::SearchParticleEmitter(emitterName);
						event[actEvent].pfxEmitterList.Insert (pfxEmitter);
						event[actEvent].string[0]	=			(arg.PickWord (4, "\"", "\""));	// nodeName
						event[actEvent].frameNr		= int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
						event[actEvent].value2		= zREAL(arg.Search("ATTACH")!=-1);

						// zFCHUNK_MDS_EVENTPFX
						file.BinStartChunk(zFCHUNK_MDS_EVENTPFX);
						file.BinWriteInt(frameNr);
						file.BinWriteFloat(event[actEvent].value1);
						file.BinWriteString(emitterName);
						file.BinWriteString(event[actEvent].string[0]);
						file.BinWriteFloat(event[actEvent].value2);
						file.BinEndChunk();

						actEvent++;
					} else
					if (line.Search ("*EVENTSETMESH")!=-1) {
						// *eventSetMesh (frameNr "MAX_ASC_NAME")
						event[actEvent].aniEventType= zMDL_EVENT_SETMESH;
						frameNr						=			arg.PickWord (1, trenn, skip).ToInt();
						event[actEvent].string[0]	= CutMarks2(arg.PickWord (2, trenn, skip));

						// zFCHUNK_MDS_EVENTSETMESH
						file.BinStartChunk(zFCHUNK_MDS_EVENTSETMESH);
						file.BinWriteInt(frameNr);
						file.BinWriteString(event[actEvent].string[0]);
						file.BinEndChunk();

						if (frameNr>0)
							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
						actEvent++;
					} else
					if (line.Search ("*EVENTMMSTARTANI")!=-1) {
						// *eventMMStartAni (frameNr "aniName" ["nodeName"] [I:intensity] [H:holdTime])
						event[actEvent].aniEventType= zMDL_EVENT_MM_STARTANI;
						frameNr						=			arg.PickWord (1, trenn, skip).ToInt();
						event[actEvent].string[0]	= CutMarks2(arg.PickWord (2, trenn, skip));
						event[actEvent].string[1]	= CutMarks2(arg.PickWord (3, trenn, skip));	if ((event[actEvent].string[1])[1]==':') event[actEvent].string[1].Clear();
						event[actEvent].value1		=  1;	// default 
						event[actEvent].value2		= -2;	// default 
						GetMDSLineValue				(arg, "I:", event[actEvent].value1);
						GetMDSLineValue				(arg, "H:", event[actEvent].value2);

						// zFCHUNK_MDS_EVENTMMSTARTANI
						file.BinStartChunk(zFCHUNK_MDS_EVENTMMSTARTANI);
						file.BinWriteInt(frameNr);
						file.BinWriteString(event[actEvent].string[0]);
						file.BinWriteString(event[actEvent].string[1]);
						file.BinWriteFloat(event[actEvent].value1);
						file.BinWriteFloat(event[actEvent].value2);
						file.BinEndChunk();

						if (frameNr>0)
							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
						actEvent++;
					} else
					if (line.Search ("*EVENTCAMTREMOR")!=-1) {
						// *eventCamTremor	(frameNr radiusCM	durationMSec	strengthXZPlane	strengthYHeight)
						event[actEvent].aniEventType= zMDL_EVENT_CAM_TREMOR;
						frameNr						= arg.PickWord (1, trenn, skip).ToInt();
						event[actEvent].value1		= arg.PickWord (2, trenn, skip).ToFloat();
						event[actEvent].value1		*= event[actEvent].value1;		// aus radius radiusSquare machen
						event[actEvent].value2		= arg.PickWord (3, trenn, skip).ToFloat();
						event[actEvent].value3		= arg.PickWord (4, trenn, skip).ToFloat();
						event[actEvent].value4		= arg.PickWord (5, trenn, skip).ToFloat();

						// zFCHUNK_MDS_EVENTCAMTREMOR
						file.BinStartChunk(zFCHUNK_MDS_EVENTCAMTREMOR);
						file.BinWriteInt(frameNr);
						file.BinWriteFloat(event[actEvent].value1);
						file.BinWriteFloat(event[actEvent].value2);
						file.BinWriteFloat(event[actEvent].value3);
						file.BinWriteFloat(event[actEvent].value4);
						file.BinEndChunk();

						if (frameNr>0)
							event[actEvent].frameNr = int(aniFpsScale* zREAL(frameNr==-1 ? aniPtr->numFrames-1 : frameNr - firstFrame));
						actEvent++;
					};
					
					// FIXME: "fps:__"
					// check ist hier leider nur auf 'normalen' mit Ani-Data moeglich, da fuer die anderen die 
					// frame-Ranges noch nicht bekannt sind => dieses werden erst spaeter 'resolved'
					if (aniPtr->GetAniType()==zMDL_ANI_TYPE_NORMAL)
					{
						if ((event[actEvent-1].frameNr>aniPtr->numFrames-1) || (event[actEvent-1].frameNr<0)) 
						{
							zERR_WARNING ("D: MDL: Frame-Number is out of bounds, ani: "+aniPtr->GetAniName()+", line: " + line);

							// zur Sicherheit auf legalen Bereich clampen
							zClamp (event[actEvent-1].frameNr, 0, aniPtr->numFrames-1);
						};
					};
				};
				aniPtr->numAniEvents	= numEvents;
				aniPtr->aniEvents		= event;

				// zFCHUNK_MDS_ANIEVENTS_END
				file.BinStartChunk(zFCHUNK_MDS_ANIEVENTS_END);
				file.BinEndChunk();
			};
		}
		else if (line.Search ("}"			)!=-1) break;
		// ACHTUNG: wegen 'continue' oben darf hier nix relevantes mehr kommen !
	};
	
	// zFCHUNK_MDS_ANIENUM_END
	file.BinStartChunk(zFCHUNK_MDS_ANIENUM_END);
	file.BinEndChunk();

	// evtl. Meshes wieder rauswerfen, die fuer die Ani-BBox Berechnung noetig waren ?
	if (loadedMDMForAniConversion)
	if (hasFlag_DONT_USE_MESH) {
		ReleaseMeshes	();
	};

	//
	zERR_MESSAGE	(5, 0, "D: MDL: numAnis: "+zSTRING(protoAnis.GetNumInList())+", numMAN: "+zSTRING(numMAN)); 
	fps_avg			/= zREAL(numMAN);
	zERR_MESSAGE	(5, 0, "D: MDL: fpsRates min, max, avg: "+zSTRING(fps_min,4)+", "+zSTRING(fps_max,4)+", "+zSTRING(fps_avg,4));
};

zBOOL zCModelPrototype::ReadModelMSB(zCFileBIN &file)
{
	zBOOL hasFlag_DONT_USE_MESH = FALSE;
	s_registerMeshList.DeleteList();

	// zFCHUNK_MDS_MODEL
	zBOOL	res = FALSE;
	zWORD	id;
	zLONG	len;
	while (!file.BinEof())
	{ 
		file.BinOpenChunk(id, len);
		switch (id)
		{ 
		case zFCHUNK_MDS_ANIENUM:
			{
				file.BinSkipChunk();
				if ( !ReadAniEnumMSB(hasFlag_DONT_USE_MESH, file) ) goto leaveParsing;
			};
			break;
		case zFCHUNK_MDS_MESHANDTREE:
			{
				if ( !ReadMeshAndTreeMSB(hasFlag_DONT_USE_MESH, file) ) goto leaveParsing;
			}
			break;
		case zFCHUNK_MDS_REGISTERMESH:
			{
				zSTRING	ascName;
				file.BinReadString(ascName);
				file.BinSkipChunk();
				if ( zCModelPrototype::S_GetAutoConvertMeshes() )
				{
					s_registerMeshList.Insert(ascName);
					// ... an Ort und Stelle konvertieren klappt nicht.
					// Wird am Ende des Lesens des .MSB in einem Rutsch gemacht
				};
			};
			break;
//		case zFCHUNK_MDS_STARTMESH: 
//			ReadStartMesh();
//			break;
		case zFCHUNK_MDS_MODEL_END: 
			{
				file.BinSkipChunk();
				res = TRUE;
				goto leaveParsing;
			}
			break;
		default:
			file.BinSkipChunk();
		};
	};
	leaveParsing:;

	return res;
};

void zCModelPrototype::ReadModel(zCFileBIN &file) 
{
	zBOOL hasFlag_DONT_USE_MESH = FALSE;
	s_registerMeshList.DeleteList();

	// zFCHUNK_MDS_MODEL
	file.BinStartChunk(zFCHUNK_MDS_MODEL);
	file.BinEndChunk();

	while (!mfile->Eof()) {
		mfile->Read (line);
		line.Upper();
			 if (line.Search ("//"			)!=-1) continue;
		else if (line.Search ("ANIENUM"		)!=-1) ReadAniEnum		(hasFlag_DONT_USE_MESH, file);
		else if (line.Search ("MESHANDTREE"	)!=-1) ReadMeshAndTree	(hasFlag_DONT_USE_MESH, file);
		else if (line.Search ("REGISTERMESH")!=-1) RegisterMesh		(file);
//		else if (line.Search ("STARTMESH"	)!=-1) ReadStartMesh	();
		else if (line.Search ("{"			)!=-1) ;
		else if (line.Search ("}"			)!=-1) break;
	};

	// zFCHUNK_MDS_MODEL_END
	file.BinStartChunk(zFCHUNK_MDS_MODEL_END);
	file.BinEndChunk();
};

zBOOL zCModelPrototype::LoadModelScriptMSB(const zSTRING& filename) 
{
	fileSourceType = zFROM_MDS;

	// .MSB vorhanden ?
	zPATH path(filename);
	{
		zCFileBIN file (zoptions->GetDirString(DIR_COMPILED_ANIMS) + path.GetFilename() + ".MSB");
		// bereits im internen Format vorhanden ?
		if (file.BinExists()) 
		{
			// Model-Name setzen
			SetModelProtoName(path.GetFilename());

			zERR_MESSAGE (2, zERR_BEGIN, "N: MSB: Loading Model-Script (binary) '" + filename + "'");
			file.BinOpen();

			zBOOL	res = FALSE; 
			zWORD	id;
			zLONG	len;
			while (!file.BinEof())
			{ 
				file.BinOpenChunk(id, len);
				switch (id)
				{ 
				case zFCHUNK_MODELSCRIPT:
					{
						zDWORD	vers;
						file.BinReadDWord(vers);
						file.BinReadString(ascPath);
						file.BinSkipChunk();
						//goto compileMDS;
						if ( vers != GetMDSFileVersion() ) goto leaveParsing;
					};
					break;
				case zFCHUNK_MDS_SOURCE:
					{
						if ( !zCModelPrototype::GetAutoConvertAnis() )
						{
							file.BinSkipChunk();
							break;
						};
						// zoptions->ChangeDir (DIR_ANIMS);
						if ( !file.BinReadCompareSrcFileStats () ) goto leaveParsing;
						file.BinSkipChunk();
					};
					break;
				case zFCHUNK_MDS_MODEL:
					{
						file.BinSkipChunk();
						if ( !ReadModelMSB(file) ) goto leaveParsing;
					};
					break;
				case zFCHUNK_MDS_END: 
					{
						file.BinSkipChunk();
						res = TRUE;
						goto leaveParsing;
					};
					break;
				default:
					file.BinSkipChunk();
				};
			};
			leaveParsing:;

			file.BinClose();
			zERR_MESSAGE (2, zERR_END, "");
			if (res) return TRUE;
		};
		// Laden fehlgeschlagen: Objekt-Zustand wieder 'auffrischen'
		Clear();
		fileSourceType = zFROM_MDS;  // wurde durch Clear() wieder zurueckgesetzt
	};

	return FALSE;
};

// NOTE MDS parser is here
zBOOL zCModelPrototype::LoadModelScript (const zSTRING& filename) 
{
	// Source-Format	: .MDS	(model script)
	// Compiled-Format	: .MSB	(model script binary)

	if ( !LoadModelScriptMSB(filename) )

	{
		fileSourceType = zFROM_MDS;

		// Ort suchen, an dem sich das MDS befindet..
		zPATH mdsPath;
		zSTRING fname (filename);
		fname.Upper();
		if (mdsPath.SearchFile(fname, zoptions->GetDirString(DIR_ANIMS)) != zERR_NONE)
		{
			// MDS nicht gefunden
			zERR_FAULT ("D: zModel(zCModelProto::LoadModelScript): MDS not found: " + fname);
			return FALSE;
		};

		zCFileBIN file;
		file.BinCreate(zoptions->GetDirString(DIR_COMPILED_ANIMS) + mdsPath.GetFilename() + ".MSB");
		
		// zFCHUNK_MODELSCRIPT
		file.BinStartChunk(zFCHUNK_MODELSCRIPT);
		file.BinWriteDWord(GetMDSFileVersion());
		file.BinWriteString(mdsPath.GetDirectoryPath()); // FIXME: STATIC ascPath!!!
		file.BinEndChunk();

		// zFCHUNK_MDS_SOURCE
		file.BinStartChunk(zFCHUNK_MDS_SOURCE);
		zoptions->ChangeDir(DIR_ANIMS);  // sonst wird Datei nicht gefunden - n�tig?
		file.BinWriteSrcFileStats(mdsPath.GetPath());
		file.BinEndChunk();

		// Hier wird implizit der aktuelle Pfad gesetzt, nachfolgende Routinen suchen ihre
		// Files in diesem aktuellem Pfad.
		zERR_MESSAGE (2, zERR_BEGIN, "D: MDS: Loading Model-Script '" + mdsPath.GetPath() + "' ...");	

		ascPath = mdsPath.GetDirectoryPath();
		mfile = zfactory->CreateZFile(mdsPath.GetPath());
		mfile->Open();
			
		// Model-Name setzen
		SetModelProtoName (mdsPath.GetFilename());

		while (!mfile->Eof()) { 
			mfile->Read (line);
			line.Upper();
			if (line.Search ("//"		)!=-1) continue;
			if (line.Search ("MODEL"	)!=-1) ReadModel(file);
		};

		zERR_MESSAGE (2, zERR_END, "");

		// zFCHUNK_MDS_END
		file.BinStartChunk(zFCHUNK_MDS_END);
		file.BinEndChunk();

		// Cleanup
		mfile->Close();
		delete mfile; mfile=0;
		file.BinClose();
	};

	// last inits
	ResolveReferences();

	// Registered Meshes nachtraeglich konvertieren?
	{
		if (zCModelPrototype::S_GetAutoConvertMeshes())
		{
			for (int i=0; i<s_registerMeshList.GetNum(); i++)
			{
				zCModel *model			= zNEW(zCModel(this));	
				// FIXME: sollte eigentlich NICHT noetig sein!! 
				//        Problem: zNEW(zCModel(this)) erhoeht nicht den proto-RefCtr, model->Release() hingegen dekrementiert ihn!!
				this->AddRef			();							
				model->ApplyMeshLib		(s_registerMeshList[i]);
				model->RemoveMeshLib	(s_registerMeshList[i]);
				model->Release			();
			};
			s_registerMeshList.DeleteList();
		};
	};

	return TRUE;
};

zBOOL zCModelPrototype::LoadModelASC (const zSTRING& filename) 
{
	// Source-Format	: .ASC
	// Compiled-Format	: .MDL

	//
	fileSourceType		= zFROM_ASC;

	// .MDL vorhanden ?
	zPATH path(filename);
	{
//		zoptions->ChangeDir	(DIR_COMPILED_ANIMS);
		zCFileBIN file	(zoptions->GetDirString(DIR_COMPILED_ANIMS) + path.GetFilename()+".MDL");
		// bereits im internen Format vorhanden ?
		if (file.BinExists()) 
		{
			zERR_MESSAGE							(5, 0, "D: MDL: Loading Model-MDL '"+filename+"'");
			file.BinOpen							();
			zBOOL	res = LoadMDH					(file);
			if (res)res = zCModelMeshLib::LoadMDM	(file, this, 0); 
			file.BinClose							();
			if (res)	return TRUE;
		};

		// Laden fehlgeschlagen: Objekt-Zustand wieder 'auffrischen'
		Clear();
		fileSourceType		= zFROM_ASC;		// wurde durch Clear() wieder zurueckgesetzt
	};

	// Model-Name setzen
	SetModelProtoName		(path.GetFilename());

	// neu konvertien, .ASC vorhanden ?

	// Ort suchen, an dem sich das ASC befindet..
	zPATH	mdsPath;
	zSTRING fname	(filename);
	fname.Upper		();
//	zoptions->ChangeDir	(DIR_ANIMS);
	if (mdsPath.SearchFile(fname, zoptions->GetDirString(DIR_ANIMS))!=zERR_NONE) {
		// ASC nicht gefunden
		zERR_FAULT ("D: zModel(zCModelProto::LoadModelASC): ASC not found: "+fname);
		return FALSE;
	};

	//
	zERR_MESSAGE			(2, zERR_BEGIN, "D: MDL: Loading Model-ASC '"+filename+"' ...");	

	zCModelAni* aniPtr=0;
	Load3DSMAXAsc			(aniPtr, mdsPath.GetPath(), "", 0, 0, zMDL_MAX_IMPORT_MESH | zMDL_MAX_IMPORT_TREE);
	zRELEASE (aniPtr);
//	zoptions->ChangeDir			(DIR_COMPILED_ANIMS);
	zCFileBIN file;
	file.BinCreate			(zoptions->GetDirString(DIR_COMPILED_ANIMS) + path.GetFilename()+".MDL");
	SaveMDH					(file);
	zCModelMeshLib *meshLib	= zNEW(zCModelMeshLib);
	meshLib->BuildFromModel	(this);
	meshLib->SaveMDM		(file, this);
	meshLib->Release		();
	file.BinClose			(); 
	
	// Model-Name setzen
	SetModelProtoName		(mdsPath.GetFilename());

	zERR_MESSAGE			(2, zERR_END, "");
	return TRUE;
};

///////////////////////////////////////////////////////////////////////////
//     Model Mesh-Lib	(Prototype)
///////////////////////////////////////////////////////////////////////////

// Wenn es Meshes aquiriert oder freigibt ruft es AddRef / Release auf

zCModelMeshLib::~zCModelMeshLib() 
{
	ReleaseData();
};

void zCModelMeshLib::ReleaseData () {
	for (int i=0; i<meshNodeList.GetNumInList(); i++) { 
		meshNodeList[i].visual->Release();
	};
	meshNodeList.EmptyList();
	for (i=0; i<meshSoftSkinList.GetNum(); i++) {
		meshSoftSkinList[i]->Release();
	};
	meshSoftSkinList.EmptyList();
};

void zCModelMeshLib::AllocNumNodeVisuals(int num) {
	meshNodeList.AllocAbs (num);
};

void zCModelMeshLib::AddMeshSoftSkin (zCMeshSoftSkin* meshSoftSkin)
{
	meshSoftSkinList.InsertEnd ((zCMeshSoftSkin*)meshSoftSkin->AddRef());
};

void zCModelMeshLib::AddNodeVisual (int nodeIndex, zCVisual *visual) {
	zERR_ASSERT (nodeIndex>=0);
	if (nodeIndex<0)	nodeIndex=0;
	if (visual==0)		return;
	visual->AddRef		();
	zTNodeMesh nodeVis;
	nodeVis.nodeIndex	= nodeIndex;
	nodeVis.visual		= visual;
	meshNodeList.Insert (nodeVis); 
};

void zCModelMeshLib::ApplyToModel (zCModel *model) {
	for (int i=0; i<meshNodeList.GetNum(); i++) { 
		zCModelNodeInst *node = model->GetNodeList()[meshNodeList[i].nodeIndex];
		if (node)
			node->SetNodeVisualS (meshNodeList[i].visual, FALSE);	// FALSE => texture ist nicht ueber Node, sondern ueber MeshLib ANIMATED !!
	};
	for (i=0; i<meshSoftSkinList.GetNum(); i++) {
		model->meshSoftSkinList.Insert ((zCMeshSoftSkin*)meshSoftSkinList[i]->AddRef());
	};
};

void zCModelMeshLib::ApplyToModel (zCModelPrototype *modelProto) {
	for (int i=0; i<meshNodeList.GetNum(); i++) { 
		zCModelNode *node = modelProto->nodeList[meshNodeList[i].nodeIndex];
		if (node)
			node->SetNodeVisualS (meshNodeList[i].visual);
	};
	for (i=0; i<meshSoftSkinList.GetNum(); i++) {
		modelProto->meshSoftSkinList.Insert ((zCMeshSoftSkin*)meshSoftSkinList[i]->AddRef());
	};
};

void zCModelMeshLib::RemoveFromModel (zCModel *model) 
{
	// nodeMeshes rauswerfen
	for (int i=0; i<meshNodeList.GetNum(); i++) { 
		zCModelNodeInst *node = model->GetNodeList()[meshNodeList[i].nodeIndex];
		if (node) {
			if (node->GetNodeVisual()==meshNodeList[i].visual)
				node->SetNodeVisualS (0);
		};
	};

	// softSkins rauswerfen
	for (i=0; i<meshSoftSkinList.GetNum(); i++) {
		if (model->meshSoftSkinList.IsInList (meshSoftSkinList[i])) {
			model->meshSoftSkinList.Remove (meshSoftSkinList[i]);
			meshSoftSkinList[i]->Release();
		};
	};
};

void zCModelMeshLib::BuildFromModel (zCModelPrototype *modelProto)
{
	ReleaseData();
	this->SetObjectName (modelProto->GetModelProtoName());

	meshNodeList.EmptyList();
	for (int i=0; i<modelProto->GetNodeList().GetNum(); i++) 
	{
		if (modelProto->GetNodeList()[i]->IsSlot()) continue;
		AddNodeVisual (i, modelProto->GetNodeList()[i]->GetNodeVisual());
//		AddNodeVisual (modelProto->GetNodeList()[i], modelProto->GetNodeList()[i]->GetNodeVisual());
	};

	//
	meshSoftSkinList.EmptyList();
	meshSoftSkinList.AllocAbs (modelProto->meshSoftSkinList.GetNum());
	for (i=0; i<modelProto->meshSoftSkinList.GetNum(); i++) {
		AddMeshSoftSkin (modelProto->meshSoftSkinList[i]);
	};
};

void zCModelMeshLib::BuildFromModel	(zCModel *model) 
{
	ReleaseData();
	this->SetObjectName (model->GetModelProto()->GetModelProtoName());

	meshNodeList.EmptyList();
	for (int i=0; i<model->GetNodeList().GetNum(); i++) 
	{
		if (model->GetNodeList()[i]->GetProtoNode()->IsSlot()) continue;
		AddNodeVisual (i, model->GetNodeList()[i]->GetNodeVisual());
//		AddNodeVisual (model->nodeList[i], model->nodeList[i]->GetNodeVisual());
	};

	//
	meshSoftSkinList.EmptyList();
	meshSoftSkinList.AllocAbs (model->meshSoftSkinList.GetNum());
	for (i=0; i<meshSoftSkinList.GetNum(); i++) {
		AddMeshSoftSkin (model->meshSoftSkinList[i]);
	};
};

// ================================================================================================================

const zDWORD zMDM_VERS = (06);

static const zWORD zFCHUNK_MODELMESH				= 0xD000;
static const zWORD		zFCHUNK_MDM_SOURCE			= 0xD010;
static const zWORD		zFCHUNK_MDM_NODEMESHES		= 0xD020;
static const zWORD		zFCHUNK_MDM_SOFSKINLIST		= 0xD030;
static const zWORD		zFCHUNK_MDM_END				= 0xD040;

zDWORD zCModelMeshLib::GetMDMFileVersion ()  {
	// assert: vers nummern sind maximal 16BIT !!!
	return	zDWORD(zMDM_VERS) +											// 8bit
			(zDWORD(zCProgMeshProto	::GetFileVersion()) << 8 ) +		// 16bit
			(zDWORD(zCMeshSoftSkin	::GetFileVersion()) << 24)	
			;
};

void zCModelMeshLib::SaveMDM (zCModelPrototype *hostModelProto) 
{
	// .MDM immer speichern, selbst wenn kein Mesh drin ist !!
//	zCArray<zCModelNode*> protoNodeList;
//	CollectNodeMeshes	(protoNodeList);
//	if ((protoNodeList.GetNum()<=0) && (meshSoftSkinList.GetNum()<=0))	return;
//	if ((meshNodeList.GetNum()<=0) && (meshSoftSkinList.GetNum()<=0))	return;

//	const zSTRING& fileName	= GetModelProtoName() + ".mdm";
//		  zSTRING  ascName	= GetModelProtoName() + ".asc";
	const zSTRING& fileName	= GetObjectName() + ".mdm";
	zERR_MESSAGE			(5, 0, "D: MDL: Saving Model-Mesh: "+fileName);
	
	zCFileBIN file;
	file.BinCreate			(zoptions->GetDirString(DIR_COMPILED_ANIMS) + fileName); 
	SaveMDM					(file, hostModelProto);
	file.BinClose			();
};


void zCModelMeshLib::SaveMDM (zCFileBIN &file, zCModelPrototype *hostModelProto) 
{
	int		 i;
	zSTRING  ascName		(GetObjectName() + ".ASC");
	file.BinStartChunk		(zFCHUNK_MODELMESH);
	file.BinWriteDWord		(GetMDMFileVersion());
							
	// SOURCE				
	file.BinStartChunk		(zFCHUNK_MDM_SOURCE);
	{
		// Date & Name des Source-ASCs schreiben
//		zoptions->ChangeDir				(DIR_ANIMS);
		file.BinWriteSrcFileStats	(zoptions->GetDirString(DIR_ANIMS) + ascName);
	}

	if (meshNodeList.GetNum()>0) {
		// NODE_MESHES, NODELIST
		file.BinStartChunk	(zFCHUNK_MDM_NODEMESHES);
		{
			file.BinWriteWord	(meshNodeList.GetNumInList());
			for (i=0; i<meshNodeList.GetNum(); i++) {
//				zCModelNode *protoNode	= (meshNodeList[i].node) ? meshNodeList[i].node->GetProtoNode() : meshNodeList[i].protoNode;
				zCModelNode *protoNode  = hostModelProto->GetNodeList()[meshNodeList[i].nodeIndex];
				file.BinWriteString		(protoNode->nodeName);
			};

			for (i=0; i<meshNodeList.GetNumInList(); i++) {
				zCModelNode *protoNode		= hostModelProto->GetNodeList()[meshNodeList[i].nodeIndex];
				zCProgMeshProto *pmesh		= zDYNAMIC_CAST<zCProgMeshProto>(protoNode->visual);
				zERR_ASSERT (pmesh);
				if (pmesh)
				{
					pmesh->Save				(file);
				};
			};
		};
	};

	// SOFTSKINLIST
	if (meshSoftSkinList.GetNum()>0) {
		file.BinStartChunk	(zFCHUNK_MDM_SOFSKINLIST);
		{
			// NODELIST_CHECKSUM => wichtig, da das SS-mesh implizit Referenzen auf Nodes hat
			file.BinWrite		(&hostModelProto->nodeListChecksum, sizeof(hostModelProto->nodeListChecksum));
			file.BinWriteWord	(meshSoftSkinList.GetNum());
			for (i=0; i<meshSoftSkinList.GetNum(); i++) {
				meshSoftSkinList[i]->Save	(file);
			};
		};
	};
	file.BinStartChunk	(zFCHUNK_MDM_END);
};

zBOOL zCModelMeshLib::LoadMDM (const zSTRING&		filename, 
								 zCModelPrototype	*destProto, 
								 zCModel			*destModel, 
								 zCModelMeshLib		**resMeshLib)
{
	// FileName:	"barrel.mdm"	(der name wird direkt benutzt, wie er reinkommt)

	// Semantik:
	// - Diese Routine konvertiert autom., falls bin-File nicht vorhanden oder Vers-Mismatch
	// - MeshLibs existieren immer in bezug auf Model/ModelProto.
	// - Es immer entweder ein Model oder ein ModelProto anzugeben (entweder a) zum Referenzen aufloesen, oder b)
	//   um dort die Meshes abzulegen).
	// - a) Falls eine MeshLib angegeben wird ('resMeshLib'), werden die Daten in dieser MeshLib abgelegt. In diesem
	//   Fall ist trotzdem entweder ein 'destProto' oder ein 'destModel' anzugeben, damit gewisse Referenzen (auf
	//   Nodes) aufgeloest werden koennen.
	// - b) Falls keine MeshLib angegeben wird, werden die Daten in dem Model oder der dem ModelProto abgelegt.
	// - In beiden Faellen koennen die Daten entweder direkt von der Platte kommen, oder, falls die gewuenschte 
	//   Datei bereits einmal als MeshLib mit dem Parameter 'resMeshLib!=0' geladen wurde, aus einer bereits im Speicher
	//   stehenden Meshlib.

	if ((!destProto) && (!destModel)) return FALSE;

	zERR_ASSERT_STRICT (!((destProto) && (destModel)));

	zPATH	path		(filename);
	zSTRING	meshLibName	(path.GetFilename());

	// bereits im Speicher ?
	zCModelMeshLib *modelMeshLib = (zCModelMeshLib*)zCModelMeshLib::GetStaticClassDef()->SearchObject (meshLibName);
	if (modelMeshLib) {
		modelMeshLib->AddRef();
		if (resMeshLib)
		{
			// Fall a)
			*resMeshLib = modelMeshLib;
		} else 
		{
			// Fall b)
			if (destModel)		modelMeshLib->ApplyToModel	(destModel); else
			if (destProto)		modelMeshLib->ApplyToModel	(destProto); 
		};
		return TRUE;
	};

	//
	zERR_MESSAGE (3, zERR_BEGIN, "D: MDL: Loading Model-Mesh: "+filename);

	//
	zCModelPrototype* convertProto = destProto ? destProto : (destModel ? destModel->GetModelProto() : 0);
	zBOOL res	= LoadMDM_Try	(filename, destProto, destModel, resMeshLib);
	if (!res) {
		res		= ConvertMDM	(filename, convertProto);
		if (res)
		res		= LoadMDM_Try	(filename, destProto, destModel, resMeshLib);
	};

	zERR_MESSAGE (3, zERR_END, "");

	return res;
};

zBOOL zCModelMeshLib::LoadMDM_Try (const zSTRING&	filename, 
								 zCModelPrototype	*destProto, 
								 zCModel			*destModel, 
								 zCModelMeshLib		**resMeshLib)
{
//	zoptions->ChangeDir			(DIR_COMPILED_ANIMS); 
	zCFileBIN file			(zoptions->GetDirString(DIR_COMPILED_ANIMS) + filename);
	// noch nicht ins interne Format konvertiert ?
	if (!file.BinExists())	
	{
		file.BinClose		();
		return FALSE;
	};
	file.BinOpen			();
	zBOOL res = LoadMDM		(file, destProto, destModel, resMeshLib);
	file.BinClose			();
	return res;
};

zBOOL zCModelMeshLib::LoadMDM (zCFileBIN			&file,
							   zCModelPrototype		*destProto, 
							   zCModel				*destModel, 
							   zCModelMeshLib		**resMeshLib)
{
	// Semantik: siehe andere Methode 'LoadMDM'

	zBOOL meshLibCreated = FALSE;
	if (resMeshLib) {
		*resMeshLib = zNEW(zCModelMeshLib);
		(*resMeshLib)->SetObjectName (file.file->GetFilename());
		meshLibCreated = TRUE;
	};

	zCModelMeshLib *meshLib = resMeshLib ? *resMeshLib : 0;
	zCArray<zCModelNodeInst*>	nodeList;
	zCArray<zCModelNode*>		nodeProtoList;

	zWORD						num;
	zWORD						id;
	zLONG						len;
	while (!file.BinEof()) { 
		file.BinOpenChunk (id, len);
		switch (id) { 
		case zFCHUNK_MODELMESH: {
			zDWORD	vers;
			file.BinReadDWord	(vers);
//goto convertASC;
			if (vers!=GetMDMFileVersion()) goto convertASC;
			};
			break;
		case zFCHUNK_MDM_SOURCE: {
			if (!zCModelPrototype::GetAutoConvertAnis()) {
				file.BinSkipChunk();
				break;
			};
//			zoptions->ChangeDir (DIR_ANIMS);
			if (!file.BinReadCompareSrcFileStats ()) goto convertASC;
			};
			break;
		case zFCHUNK_MDM_NODEMESHES: {
			file.BinReadWord		(num);
			nodeList.AllocAbs		(num);
			nodeProtoList.AllocAbs	(num);
			zSTRING nodeName;
			zBOOL	ok;
			for (int i=0; i<num; i++) {
				file.BinReadString (nodeName);
				if (destModel) {
					zCModelNodeInst *node = destModel->SearchNode (nodeName);
					nodeList.InsertEnd (node);
					ok = (node!=0);
				} else {
					zCModelNode		*node = destProto->SearchNode (nodeName);
					nodeProtoList.InsertEnd (node);
					ok = (node!=0);
				};
				if (!ok) {
					zERR_FAULT ("D: MDL: zModelProto(zCModelProto::LoadMDM): Mesh-ASC applied to wrong model: "+file.file->GetFilename()+", node in mesh but not in model: "+nodeName);
				};
			}; 

			if (meshLib) meshLib->AllocNumNodeVisuals(num);
			for (i=0; i<num; i++) {
				zCProgMeshProto *pmesh = zNEW(zCProgMeshProto);
				if (!pmesh->Load (file)) goto convertASC;
				pmesh->PackStaticVertexBuffers();				// FIXME: ist wahrscheinlich nicht der richtige Ort dafuer!!
				if (destModel) {
					if (nodeList[i]) {
						int nodeIndex	= destModel->GetNodeList().Search (nodeList[i]);
//						if (meshLib)	meshLib->AddNodeVisual		(nodeList[i], mesh);
						if (meshLib)	meshLib->AddNodeVisual		(nodeIndex, pmesh);
						else			nodeList[i]->SetNodeVisualS	(pmesh, TRUE);
					};
				} else {
					if (nodeProtoList[i]) {
						nodeProtoList[i]->SetNodeVisualS	(pmesh);
					};
				};
				// Dieser Kontext benoetigt das Mesh nicht mehr
				pmesh->Release();
			};
			};
			break;
		case zFCHUNK_MDM_SOFSKINLIST: {
			// NodeList Checksum
			zDWORD checksum;
			file.BinRead (&checksum, sizeof(checksum));
			if (destModel)
			if (checksum!=destModel->GetModelProto()->nodeListChecksum) {
				zerr.Fault (zSTRING("D: zModel(zCModelAni::LoadMDM): the file's node-hierarchy is incompatible to 'meshAndTree';")+
					zSTRING("applied mesh and mds-'meshAndTree' entry need to have exactly the same hierachy => adjust them"));
				file.BinSkipChunk();
				break;
//				goto convertASC;
			};

			// man will SoftSkins hinzufuegen !
			zWORD num;
			file.BinReadWord						(num);
			for (int i=0; i<num; i++) {
				zCMeshSoftSkin *mesh = zNEW(zCMeshSoftSkin());
				zBOOL res = mesh->Load	(file);
				// ist Laden fehlgeschlagen ?
				if (!res) goto convertASC;
				mesh->SetObjectName		(file.file->GetFilename());
				if (meshLib) {
					meshLib->AddMeshSoftSkin	(mesh);		// inkl. AddRef
					// Dieser Kontext benoetigt das Mesh nicht mehr
					zRELEASE					(mesh);
				} else {
					// FIXME: dieses sollten 'Add' Methoden des Models/Protos sein, die intern das AddRef (Release()) machen..
					if (destModel)		destModel->meshSoftSkinList.InsertEnd (mesh);
					else				destProto->meshSoftSkinList.InsertEnd (mesh);
				};
				// Dieser Kontext benoetigt das Mesh nicht mehr
//				zRELEASE					(mesh);		// s.o.
			};
			};
			break;
		case zFCHUNK_MDM_END: 
			goto leaveParsing;
			break;
		default:
			file.BinSkipChunk();
		};
	}

leaveParsing:;
	return TRUE;

convertASC:;
	if (meshLibCreated)	meshLib->Release();

	return FALSE;
};

zBOOL zCModelMeshLib::ConvertMDM (const zSTRING& filename, zCModelPrototype	*convertProto)
{

	//
	assert (convertProto);
	if (!convertProto) return FALSE;

	//
	zSTRING ascName;
	zPATH	path(filename);
	ascName	= path.GetFilename();
	ascName.Upper();

	zERR_MESSAGE			(5, 0, "D: MDL: Converting Mesh-ASC into .MDM: \""+ascName+"\"");

	// neu konvertieren
	zCModelAni *aniPtr		= 0;
	zSTRING		aniName;
	int			firstFrame, lastFrame;
	firstFrame = lastFrame	= 0;

/*
	// "A"
	// legt neues modelProto an, kopiert nodeTree => klappt leider nicht, da der softSkin Reader die Trafos der Nodes in
	// gewissen Zustaenden erwartet....
	zCModelPrototype *modelProto	= zNEW(zCModelPrototype); 
	modelProto->SetModelProtoName	(ascName);
	modelProto->CopyNodeTreeFrom	(GetModelProto());		// der neue ModelProto muss denselben NodeTree haben, wie das baseModelProto
	modelProto->Load3DSMAXAsc		(aniPtr, ascName+".asc", aniName, firstFrame, lastFrame, FALSE, TRUE, FALSE);	// ani, mesh, tree
	meshLib							= zNEW(zCModelMeshLib);
	meshLib->SetObjectName			(ascName);
	meshLib->BuildFromModel			(modelProto);
	meshLib->SaveMDM				(this->GetModelProto());
	modelProto->Release				();
	delete aniPtr;
*/
	// "B"
	// Das baseModelProto wird fuer das Laden der neuen MeshLib benutzt... FIXME: bleiben unerwuemschte Reste im modelProto zurueck ??
	zCModelPrototype *modelProto	= convertProto; 
	modelProto->ReleaseMeshes		();						// modelproto von Meshes saeubern..
	modelProto->Load3DSMAXAsc		(aniPtr, ascName+".asc", aniName, firstFrame, lastFrame, zMDL_MAX_IMPORT_MESH);	// ani, mesh, tree
	zCModelMeshLib *meshLib			= zNEW(zCModelMeshLib);
	meshLib->BuildFromModel			(modelProto);
	meshLib->SetObjectName			(ascName);
	meshLib->SaveMDM				(modelProto);
	zRELEASE (aniPtr);
	meshLib->Release				();
	
	// .mdm hier neu laden, da sich die internen Referenzen der obigen meshLib auf ein modelProto beziehen, es aber
	// unten auf ein Model angewandt werden soll.
//	zCModelMeshLib::LoadMDM (ascName+".mdm", 0, this, &meshLib);
	return TRUE;		// FIXME....
};

// zCModelMeshLib* meshLib = (zCModelMeshLib*)zCModelMeshLib::GetStaticClassDef()->SearchObject (s);

// ================================================================================================================

zCModelConvertFileHandler::zCModelConvertFileHandler() 
{
	RegisterFileType("mds");
	RegisterFileType("asc");
};

zBOOL zCModelConvertFileHandler::HandleFile (const zSTRING& fname, const char* directory, _finddata_t fileinfo)
{
	zBOOL touched = FALSE;

	// Kompletten Dateinamen bauen
	zSTRING filename = zSTRING(directory) + DIR_SEPARATOR + fname;
	filename.Upper();		

	//
	if (fname.Search(".MDS")>=0) 
	{				
		{
			zCModelPrototype::S_SetAutoConvertMeshes (TRUE);
			zCModelPrototype *proto = zCModelPrototype::Load (fname);
			if (proto)
			{
				proto->Release();
				touched		= TRUE;
			};
			zCModelPrototype::S_SetAutoConvertMeshes (FALSE);
		};
	}
	else 
	if (fname.Search(".ASC")>=0) 
	{				
		// nur einfache Mesh-ASCs konvertieren (Pfad in .ini Datei?)
		if (filename.Search ("ANIMS\\ASC_MOBSI\\MESHES")>=0)
		{
			// .ASC => .MDL
			zCVisual *visual = zCVisual::LoadVisual (fname);
			if (visual)
			{
				visual->Release();
				touched		= TRUE;
			};
		} 
	} 
	else
	{
		zERR_WARNING("D: MDL: Convert: Unknown filetype: "+fname);
	}

	return touched;
};

// ================================================================================================================
