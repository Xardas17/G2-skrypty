/******************************************************************************** 
 
     $Workfile:: zMemory_Generic.cpp  $                $Date:: 6.12.00 19:47    $
     $Revision:: 12                   $             $Modtime:: 6.12.00 19:47    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ memory management wrapper
   created       : 11.7.2000

 * $Log: /current_work/zengin_work/_Dieter/zMemory_Generic.cpp $
 * 
 * 12    6.12.00 19:47 Hildebrandt
 * 
 * 11    2.11.00 16:04 Speckels
 * 
 * 10    1.09.00 22:24 Speckels
 * 
 * 9     1.09.00 21:15 Speckels
 * 
 * 8     1.09.00 17:29 Hoeller
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 2     9.08.00 17:12 Admin
 * 
 * 6     21.07.00 14:06 Hildebrandt
 * 
 * 5     20.07.00 19:48 Hildebrandt
 * 
 * 4     19.07.00 16:45 Hildebrandt
 * 
 * 3     19.07.00 15:56 Hildebrandt
 * 
 * 2     18.07.00 18:13 Hildebrandt
 * 
 * 1     18.07.00 17:21 Hildebrandt
 * 
 * 1     18.07.00 17:20 Hildebrandt
 * 
 * 2     18.07.00 17:01 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 12 $ ($Modtime: 6.12.00 19:47 $)

#include <zMemory_Generic.h>
#include <malloc.h>
#include <memory.h>

#ifndef COMPILING_SPACER
#include "smrtheap.h"
#include "smrtheap.hpp"
#endif

 
// ===============================================================================================================

void* zCMallocGeneric::Malloc (unsigned int size)
{
	return malloc(size);
};

void* zCMallocGeneric::Malloc (unsigned int size, const char *className, const char *file, int line)
{
	return malloc(size);
};

void* zCMallocGeneric::Realloc (void* ptr, unsigned int size)
{
	return realloc(ptr, size);
};

void zCMallocGeneric::Free (void* ptr)
{
	free(ptr);
};

zBOOL zCMallocGeneric::GetStats (zTMallocStats& mallocStats) 
{ 
	memset (&mallocStats, 0, sizeof(mallocStats)); 
	return FALSE; 
};

zBOOL zCMallocGeneric::Init(zBOOL activateProfiler) {
	return TRUE;
};

zBOOL zCMallocGeneric::Shutdown() {
	return TRUE;
};	

// ===============================================================================================================
