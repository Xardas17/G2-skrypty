/******************************************************************************** 
 
     $Workfile:: zMemory.h            $                $Date:: 6.12.00 23:07    $
     $Revision:: 12                   $             $Modtime:: 6.12.00 19:21    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ memory management wrapper
   created       : 11.7.2000

 * $Log: /current_work/zengin_work/_Dieter/zMemory.h $
 * 
 * 12    6.12.00 23:07 Hildebrandt
 * 
 * 11    4.12.00 16:49 Hildebrandt
 * 
 * 10    2.11.00 17:48 Hildebrandt
 * 
 * 9     2.09.00 1:41 Hildebrandt
 * 
 * 8     29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 2     9.08.00 17:12 Admin
 * 
 * 6     21.07.00 14:06 Hildebrandt
 * 
 * 5     19.07.00 16:45 Hildebrandt
 * 
 * 4     19.07.00 15:56 Hildebrandt
 * 
 * 3     18.07.00 18:12 Hildebrandt
 * 
 * 2     18.07.00 17:01 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 12 $ ($Modtime: 6.12.00 19:21 $)

// ===============================================================================================================

#ifndef __ZMEMORY_H__
#define __ZMEMORY_H__

// ===============================================================================================================

// map new/delete via define to global memory allocator 'zmalloc'
//#define ZMEMORY_USE_ZMALLOC
// log profiling infos (has mem/perf overhead) (ZMEMORY_USE_ZMALLOC must be defined)
//#define ZMEMORY_DO_PROFILE

// ===============================================================================================================

#ifndef __ZMEMORY_BASE_H__
#include <zMemory_Base.h>
#endif

// FIXME: dieses COMPILING_SPACER ist hier TMP, bis die korrekte Loesung kommt...
#ifdef COMPILING_SPACER

	// generic ANSI allocator
	#ifndef __ZMEMORY_GENERIC_H__
	#include <zMemory_Generic.h>
	#endif
	extern zCMallocGeneric zmalloc;

#else

	// FIXME: dieses #ifdef ist hier TMP, bis die korrekte Loesung kommt...
	#ifdef ZMEMORY_USE_ZMALLOC
		// Win32 Debug allocator
		#ifndef __ZMEMORY_WIN32_H__
		#include <zMemory_Win32.h>
		#endif
		extern zCMallocWin32Debug zmalloc;
	#else
		// generic ANSI allocator
		#ifndef __ZMEMORY_GENERIC_H__
		#include <zMemory_Generic.h>
		#endif
		extern zCMallocGeneric zmalloc;
	#endif

#endif

// ===============================================================================================================
 
// Funcs
#ifdef ZMEMORY_USE_ZMALLOC  
	void* operator new		(unsigned int size);
	void  operator delete	(void *ptr);
	void* operator new[]	(unsigned int size);
	void  operator delete[]	(void *ptr);
	void* operator new		(unsigned int size, const char *className, const char *file, int line);
	void  operator delete	(void *ptr,			const char *className, const char *file, int line);
	void* operator new[]	(unsigned int size, const char *className, const char *file, int line);
	void  operator delete[]	(void *ptr,			const char *className, const char *file, int line);
#else
	void* operator new		(unsigned int size);
	void  operator delete	(void *ptr);
	void* operator new[]	(unsigned int size);
	void  operator delete[]	(void *ptr);
	void* operator new		(unsigned int size, const char *className, const char *file, int line);
	void  operator delete	(void *ptr,			const char *className, const char *file, int line);
	void* operator new[]	(unsigned int size, const char *className, const char *file, int line);
	void  operator delete[]	(void *ptr,			const char *className, const char *file, int line);
#endif


#ifdef ZMEMORY_DO_PROFILE
	#define zNEW( className )					new(#className, __FILE__, __LINE__) className 
	#define zNEW_ARRAY( className, count )		new(#className, __FILE__, __LINE__) className [count]
#else
	#define zNEW( className )					new className 
	#define zNEW_ARRAY( className, count )		new className [count]
#endif

// ===============================================================================================================

#endif