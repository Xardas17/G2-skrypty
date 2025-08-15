/******************************************************************************** 
 
     $Workfile:: zProgMesh.cpp        $                $Date:: 5.02.01 19:13    $
     $Revision:: 7                    $             $Modtime:: 2.02.01 1:03     $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Progressive Meshes
   created: 9.11.99

 * $Log: /current_work/zengin_work/_Dieter/zProgMesh.cpp $
 * 
 * 7     5.02.01 19:13 Hildebrandt
 * 
 * 6     31.08.00 17:04 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 3     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 2     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 7 $ ($Modtime: 2.02.01 1:03 $)
  
#if 0

#include <zCore.h>
#include <zProgMesh.h>

zCLASS_DEFINITION_ABSTRACT		( zCProgMesh		, zCVisual,	0)

const zSTRING* zCProgMesh::GetFileExtension	(int i)
{
	return 0;
};

zCVisual* zCProgMesh::LoadVisualVirtual	(const zSTRING& visualName) const
{
	return 0;
};

#endif