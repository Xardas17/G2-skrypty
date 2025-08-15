/******************************************************************************** 
 
     $Workfile:: zCollisionObject.cpp $                $Date:: 20.12.00 3:03    $
     $Revision:: 4                    $             $Modtime:: 19.12.00 1:34    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Collection of zCCollsionObject subclasses.
   created       : 8.12.2000

 * $Log: /current_work/zengin_work/_Dieter/zCollisionObject.cpp $
 * 
 * 4     20.12.00 3:03 Hildebrandt
 * 
 * 3     15.12.00 3:55 Hildebrandt
 * 
 * 2     9.12.00 6:31 Hildebrandt
 * 
 * 1     8.12.00 21:29 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 4 $ ($Modtime: 19.12.00 1:34 $)

// ============================================================================================================

#include <zCore.h>
#include <zTypes3D.h>

#include <zBVolume.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>


// ============================================================================================================

zCOLLISION_OBJECT_DEFINITION (zCCollisionObject, TRUE)

// ============================================================================================================

zCArray<zCCollisionObjectDef*>* zCCollisionObjectDef::s_aoCollObjClassList	= 0;

zCCollisionObjectDef::zCCollisionObjectDef(const zBOOL isVolatile, zCCollisionObject* ( *_CreateNewInstance )())
{
	if (!s_aoCollObjClassList)
	{
		s_aoCollObjClassList	= zNEW(zCArray<zCCollisionObjectDef*>);
	};

	//
	m_bIsVolatile				= isVolatile;
	m_createNewInstance			= _CreateNewInstance;
	m_iIndex					= s_aoCollObjClassList->GetNum();
	s_aoCollObjClassList->Insert(this);
};

zCCollisionObjectDef::~zCCollisionObjectDef()
{
	if (s_aoCollObjClassList)
	{
		s_aoCollObjClassList->Remove	(this);
		if (s_aoCollObjClassList->IsEmpty())
		{
			delete s_aoCollObjClassList; s_aoCollObjClassList=0;
		};
	};
};

// ============================================================================================================

void zCCFASTCALL zCCollisionObject::CalcIntermediateTrafo (const zREAL time, zMAT4 &resultTrafo)
{
	zERR_ASSERT (time>=0);
	zERR_ASSERT (time<=1);

	if (time==0)
	{
		resultTrafo = GetTrafoOld();
	} else 
	if (time==1)
	{
		resultTrafo = GetTrafoNew();
	} else 
	{
		resultTrafo.SetTranslation	(zLerp (time, GetTrafoOld().GetTranslation(), GetTrafoNew().GetTranslation()));
		
		// FIXME: geht das schneller ? (glaube ja nicht ..)
		zCQuat quat0;
		zCQuat quat1;
		quat0.Matrix4ToQuat			(GetTrafoOld());
		quat1.Matrix4ToQuat			(GetTrafoNew());
		quat0.Lerp					(time, quat0, quat1);		// schnellerer lerp, statt slerp; duerfte keinen Unterschied machen
		quat0.QuatToMatrix4			(resultTrafo);
	};
};

void zCCFASTCALL zCCollisionObject::GetLargestBBox3DLocal (zTBBox3D &bbox3DLocalOut)
{ 
	// if collObject has several collision primitives, this is the local bbox of the union of the largest; is used to build the speedbox
	bbox3DLocalOut.mins = zVEC3(-0.1F);
	bbox3DLocalOut.maxs = zVEC3(+0.1F);
};	

// ============================================================================================================
