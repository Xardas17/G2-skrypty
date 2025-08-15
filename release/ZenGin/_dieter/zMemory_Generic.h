/******************************************************************************** 
 
     $Workfile:: zMemory_Generic.h    $                $Date:: 6.12.00 19:47    $
     $Revision:: 9                    $             $Modtime:: 6.12.00 19:47    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ memory management wrapper
   created       : 11.7.2000

 * $Log: /current_work/zengin_work/_Dieter/zMemory_Generic.h $
 * 
 * 9     6.12.00 19:47 Hildebrandt
 * 
 * 8     6.12.00 19:33 Hildebrandt
 * 
 * 7     4.12.00 16:49 Hildebrandt
 * 
 * 6     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 2     9.08.00 17:12 Admin
 * 
 * 5     21.07.00 14:06 Hildebrandt
 * 
 * 4     20.07.00 19:48 Hildebrandt
 * 
 * 3     19.07.00 15:56 Hildebrandt
 * 
 * 2     18.07.00 18:13 Hildebrandt
 * 
 * 1     18.07.00 17:21 Hildebrandt
 * 
 * 2     18.07.00 17:01 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 9 $ ($Modtime: 6.12.00 19:47 $)

// ===============================================================================================================

#ifndef __ZMEMORY_GENERIC_H__
#define __ZMEMORY_GENERIC_H__

#ifndef __ZMEMORY_BASE_H__
#include <zMemory_Base.h>
#endif

// ===============================================================================================================

class zCMallocGeneric : public zCMalloc {
public:
	void*	Malloc			(unsigned int size);
	void*	Malloc			(unsigned int size, const char *className, const char *file, int line);
	void*	Realloc			(void* ptr, unsigned int size);
	void	Free			(void* ptr);

	zBOOL	GetStats		(zTMallocStats& mallocStats);

	zBOOL	Init			(zBOOL activateProfiler);
	zBOOL	Shutdown		();	
};

// ===============================================================================================================

#endif