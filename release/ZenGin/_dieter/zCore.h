/******************************************************************************** 
 
     $Workfile:: zCore.h     $                $Date:: 4.12.00 17:18    $
     $Revision:: 6                    $             $Modtime:: 4.12.00 16:38    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Core public header file
   created       : 21.7.2000

 * $Log: /current_work/zengin_work/_Dieter/zCore.h $
 * 
 * 6     4.12.00 17:18 Hildebrandt
 * 
 * 5     28.09.00 19:20 Hildebrandt
 * 
 * 4     21.08.00 17:18 Hildebrandt
 * 
 * 3     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 2     9.08.00 17:12 Admin
 * 
 * 2     21.07.00 14:28 Hildebrandt
 * 
 * 1     21.07.00 13:59 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 6 $ ($Modtime: 4.12.00 16:38 $)

// ===============================================================================================================

#ifndef __ZCORE_H__
#define __ZCORE_H__

// ===================================================================================================================
//	Low level includes
// ===================================================================================================================

// Build options
//#include <zBuild.h>

// Compiler specific include
#if _MSC_VER
	#include "zCompilerVcWin32.h"
#else
	#error Unknown Compiler
#endif 


// OS specific include
//#include <zWin32.h>

// This handle is system/platform specific and is cast by the application (high-level)
// and by implementations of subsystems to the correct type (e.g. HWND).
#ifdef WIN32
	#include <windows.h>
	typedef HWND zTSystemContextHandle;
#else
	#error Unknown Environment
#endif

// Global constants
// ..

// ===================================================================================================================
//	Forward declarations
// ===================================================================================================================

// classes
class	zCObject;

// Structs
// ..

// Templates
// ..

// ===================================================================================================================
//	Abstract interfaces
// ===================================================================================================================

// ..

// ===================================================================================================================
//	Global variables
// ===================================================================================================================

// ..

// ===================================================================================================================
//	Global includes
// ===================================================================================================================

// Normal includes
#ifndef __ZLOCAL_H__
#include <zLocal.h>			// local/author specific include
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>			// basic types
#endif

#ifndef __ZMEMORY_H__
#include <zMemory.h>		// memory allocator
#endif

#ifndef __ZERROR_H__
#include <zError.h>			// basic error handling
#endif

#ifndef __ZTOOLS_H__
#include <zTools.h>			// basic low level tools
#endif

#ifndef __ZSTRING_H__
#include <zString.h>		// string class
#endif

#ifndef __ZOBJECT_H__
#include <zObject.h>		// base class
#endif

#ifndef __ZDISK_H__
#include <zDisk.h>
#endif

// ===================================================================================================================

#endif
