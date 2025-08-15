/******************************************************************************** 
 
     $Workfile:: Zzdieter.h           $                $Date:: 4.12.00 18:23    $
     $Revision:: 10                   $             $Modtime:: 4.12.00 17:22    $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Projekt-Mitglied bezogene Texte und Hinweise, StartUp/CleanUp-Code (Header)
   created: 8.1.97

 * $Log: /current_work/ZenGin/_dieter/Zzdieter.h $
 * 
 * 10    4.12.00 18:23 Moos
 * 
 * 9     28.09.00 19:18 Hildebrandt
 * 
 * 8     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 7     21.07.00 14:28 Hildebrandt
 * 
 * 6     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 10 $ ($Modtime: 4.12.00 17:22 $)


#ifndef __ZZDIETER_H__
#define __ZZDIETER_H__

// alle Includes des Autors, die auch exportiert werden sollen

#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

#ifndef __ZFIXPNT_H__
#include <zFixpnt.h>
#endif

#ifndef __ZERROR_H__
#include <zError.h>
#endif

#ifndef __ZTRIGO_H__
#include <zTrigo.h>
#endif

#ifndef __ZWORLD_H__
#include <zWorld.h>
#endif

#ifndef __Z3D_H__
#include <z3d.h>
#endif

#ifndef __ZVOB_H__
#include <zVob.h>
#endif

#ifndef __ZFILE3D_H__
#include <zFile3d.h>
#endif

#ifndef __ZMODEL_H__
#include <zModel.h>
#endif

#ifndef __ZSKY_H__
#include <zSky.h>
#endif

#ifndef __ZMORPHMESH_H__
#include <zMorphMesh.h>
#endif

#ifndef __ZRENDERER_H__
#include <zRenderer.h>
#endif

#ifndef __ZSOUND_H__
#include <zSound.h>
#endif

#ifndef __ZSNDMSS_H__
#include <zSndMSS.h>
#endif

#ifndef __ZSOUNDMAN_H__
#include <zSoundMan.h>
#endif

#ifndef __ZPHYSICS_H__
#include <zPhysics.h> 
#endif

#ifndef __ZPARTICLE_H__
#include <zParticle.h>
#endif

#ifndef __ZCONSOLE_H__
#include <zConsole.h>
#endif

extern void zDieter_StartUp	(zTSystemContextHandle* initContextHandle);
extern void zDieter_ShutDown();
extern void zDieter_ShutDown_Fast();

#endif