/******************************************************************************** 
 
     $Workfile:: zCompilerVcWin $                $Date:: 7.11.00 17:23    $
     $Revision:: 5                    $             $Modtime:: 7.11.00 0:37     $
        Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Definitions specific to Visual C++ running under Win32.
   created       : 21.8.2000

 * $Log: /current_work/zengin_work/_Dieter/zCompilerVcWin32.h $
 * 
 * 5     7.11.00 17:23 Hildebrandt
 * 
 * 4     31.08.00 17:04 Hildebrandt
 * 
 * 3     23.08.00 17:31 Hildebrandt
 * zengin 0.92i
 * 
 * 2     21.08.00 17:18 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author  Author: Hildebrandt 
/// @version $Revision: 5 $ ($Modtime: 7.11.00 0:37 $)

#ifndef __ZCOMPILERVCWIN32_H__
#define __ZCOMPILERVCWIN32_H__

// ===============================================================================================================

// Calling conventions
#define zCCFASTCALL		__fastcall
#define zCCSTDCALL		__stdcall
#define zCCCDECL		__cdecl
#define zCCFORCEINLINE	__forceinline

// DLL and API import/export
#define zDLL_IMPORT	__declspec(dllimport)	/* Import function from DLL */
#define zDLL_EXPORT __declspec(dllexport)	/* Export function to DLL	*/

#ifdef ENGINE_EXPORTS
//	#define zENGINE_API	zDLL_EXPORT
	#define zENGINE_API	
#else
//	#define zENGINE_API	zDLL_IMPORT
	#define zENGINE_API	
#endif

// Unwanted VC++ level 4 warnings to disable.
#pragma warning(disable : 4251) /* needs to have dll-interface to be used by clients of class 'ULinker' */
#pragma warning(disable : 4275) /* non dll-interface class used as base for dll-interface class         */
#pragma warning(disable : 4701) /* local variable possibly used without initialisation					*/
#pragma warning(disable : 4100) /* unreferenced formal parameter										*/
#pragma warning(disable : 4511) /* copy constructor could not be generated                              */
#pragma warning(disable : 4127) /* Conditional expression is constant									*/
#pragma warning(disable : 4512) /* assignment operator could not be generated                           */

// Unwanted VC++ level 1 warnings to disable.
#pragma warning(disable : 4786) /* 'identifier' : identifier was truncated to 'number' characters in the debug information */ // when compiling STL..

// enable 
#pragma warning(1       : 4706)	/* assignment in conditional expression									*/
#pragma warning(1       : 4189) /* local variable inited but not referenced								*/

// ===============================================================================================================


#endif
