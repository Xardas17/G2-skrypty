/******************************************************************************** 
 
     $Workfile:: zTypes.h             $                $Date:: 4.12.00 16:49    $
     $Revision:: 7                    $             $Modtime:: 4.12.00 16:48    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Common Types
   created       : 16.12.96

 * $Log: /current_work/zengin_work/_Dieter/zTypes.h $
 * 
 * 7     4.12.00 16:49 Hildebrandt
 * 
 * 6     21.08.00 17:18 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 5     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 3     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 7 $ ($Modtime: 4.12.00 16:48 $)

#ifndef __ZTYPES_H__
#define __ZTYPES_H__

#include <float.h>


// Type definitions

//////////////////
// Common Things 
//////////////////

// floating-point numeric-type for Engine
typedef float				zREAL;
//typedef double			zREAL;
#define zREAL_MAX			zREAL(+FLT_MAX)
#define zREAL_MIN			zREAL(-FLT_MAX)

typedef int zTFrameCtr;
							
//							
typedef int					 BOOL;
typedef int					zBOOL;
typedef char				zBOOL8;
typedef short int			zBOOL16;
typedef int					zBOOL32;
#define TRUE				1
#define FALSE				0

// common things
typedef char				 zINT8;
typedef char				zSINT8;
typedef unsigned char		zUINT8;
typedef short				 zINT16;
typedef short				zSINT16;
typedef unsigned short		zUINT16;
typedef long				 zINT32;
typedef long				zSINT32;
typedef unsigned long		zUINT32;

typedef unsigned __int64	zQWORD;			// 64-bit unsigned.
typedef unsigned __int64	zUQWORD;		// 64-bit unsigned.
typedef signed	 __int64	zSQWORD;		// 64-bit signed.

typedef unsigned long       zDWORD;
typedef unsigned long  int	zUDWORD;
typedef signed   long  int	zSDWORD;
typedef signed   long       zLONG;

typedef unsigned short int	zWORD;
typedef unsigned short int	zUWORD;
typedef signed   short int	zSWORD;
typedef signed   short int	zINT;

typedef unsigned char		zBYTE;
typedef unsigned char		zUBYTE;
typedef signed   char		zSBYTE;

#endif
