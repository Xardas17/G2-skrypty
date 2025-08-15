/******************************************************************************** 
 
     $Workfile:: zEngine.h            $                $Date:: 24.04.01 17:33   $
     $Revision:: 11                   $             $Modtime:: 22.04.01 22:37   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ zEngine Main-Header-File
   created       : 22.2.97

 * $Log: /current_work/ZenGin/_Dieter/zEngine.h $
 * 
 * 11    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 10    4.12.00 17:41 Hildebrandt
 * 
 * 9     11.10.00 19:45 Hildebrandt
 * 
 * 8     28.09.00 19:19 Hildebrandt
 * 
 * 7     29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 6     23.08.00 17:31 Hildebrandt
 * zengin 0.92i
 * 
 * 5     21.08.00 17:18 Hildebrandt
 * 
 * 4     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    9.08.00 17:12 Admin
 * 
 * 3     21.07.00 15:11 Hildebrandt
 * 
 * 2     11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 1     6.07.00 13:39 Hildebrandt
 * 
 * 17    6.07.00 13:35 Hildebrandt
 * 
 * 10    10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 9     9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 8     8.05.00 5:29 Hildebrandt
 * zenGin 089g
 * 
 * 7     6.05.00 17:56 Hildebrandt
 * zenGin 089f
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
 * 17    22.03.00 2:58 Hildebrandt
 * zenGin 088a
 * 
 * 16    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 14    22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 13    20.02.00 18:08 Hildebrandt
 * zenGin 087c
 * 
 * 12    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 10    14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 9     11.01.00 20:59 Hildebrandt
 * zenGin 085b
 * 
 * 8     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 6     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 11 $ ($Modtime: 22.04.01 22:37 $)

#ifndef __ZENGINE_H__
#define __ZENGINE_H__


#ifndef __ZCORE_H__
#include <zCore.h>
#endif

#ifndef __ZZBERT_H__
#include <zzBert.h>
#endif

#ifndef __ZZCARSTEN_H__
#include <zzCarsten.h>
#endif

#ifndef __ZZDIETER_H__
#include <zzDieter.h>
#endif

#ifndef __ZZULFI_H__
#include <zzUlfi.h>
#endif

#ifndef __ZOPTION_H__
#include <zoption.h>
#endif


#define zENGINE_VER			("v1.00")
#define zENGINE_VERMINOR	00
#define zENGINE_VERMAJOR	1
#define zENGINE_NAME		("*** ZenGin v1.00 - developed 1997-2001 Mad Scientists ")

class zENGINE_API zCEngine {
public:
	zCEngine();
	virtual ~zCEngine();

	//
	static zBOOL	Init		(zTSystemContextHandle* initContextHandle);
	static zBOOL	Shutdown	();
};

#endif