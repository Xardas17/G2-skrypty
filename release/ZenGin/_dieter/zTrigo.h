/******************************************************************************** 
 
     $Workfile:: zTrigo.h             $                $Date:: 4.12.00 16:49    $
     $Revision:: 6                    $             $Modtime:: 4.12.00 16:48    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Trigonometry Library
   created       : 16.12.96

 * $Log: /current_work/zengin_work/_Dieter/zTrigo.h $
 * 
 * 6     4.12.00 16:49 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 6 $ ($Modtime: 4.12.00 16:48 $)


#ifndef __ZTRIGO_H__
#define __ZTRIGO_H__

#ifndef __ZFIXPNT_H__
#include <zFixpnt.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

// ****************************************************************

typedef int		zANGLE;
//#define zANGLE int

#define M_PI			3.14159265358979323846
#define M_2PI			(2 * M_PI)
#define TRG_PI			3.14159265358979323846
#define TRG_2PI			(2 * TRG_PI)
#define TRG_MAXANGLE	2048
#define TRG_0			(0)
#define TRG_45			(zANGLE(TRG_MAXANGLE * 0.125))
#define TRG_90			(zANGLE(TRG_MAXANGLE * 0.25))
#define TRG_135			(zANGLE(TRG_MAXANGLE * 0.375))
#define TRG_180			(zANGLE(TRG_MAXANGLE * 0.5))
#define TRG_225			(zANGLE(TRG_MAXANGLE * 0.625))
#define TRG_270			(zANGLE(TRG_MAXANGLE * 0.75))
#define TRG_315			(zANGLE(TRG_MAXANGLE * 0.875))
#define TRG_360			(0)

// direct array-access
extern zREAL	trg_sin		[];
extern zREAL	trg_cos		[];
extern zFIX		trg_sinFix	[];
extern zFIX		trg_cosFix	[];

// Conversion: degree => intern ("zANGLE")
inline zANGLE	Trg_Deg2zAng ( const int   degree ) { return ((degree * TRG_MAXANGLE) / 360);}
inline zANGLE	Trg_Deg2zAng ( const zREAL degree ) { return (int((degree * TRG_MAXANGLE) / 360)); }

// Conversion: intern => degree
inline int		Trg_zAng2Deg ( const zANGLE angle ) { return ((angle * 360) / TRG_MAXANGLE );}

// computing functions, doing value clipping
inline zANGLE	Trg_AddAngle ( const zANGLE a, const zANGLE b ) { return ((a+b) & TRG_MAXANGLE-1); }
inline void		Trg_IncAngle ( zANGLE& a, const zANGLE b ) { a = ((a+b) & TRG_MAXANGLE-1); }
#define			Trg_ClipAngle(a) ((a) & (TRG_MAXANGLE-1))

// init Trig-Tables
extern void Trg_Init (void);

// ****************************************************************
// trg_sin [ trg_Deg2zAng (90) ]
#endif