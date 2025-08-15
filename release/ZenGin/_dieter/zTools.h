/******************************************************************************** 
 
     $Workfile:: zTools.h             $                $Date:: 5.12.00 12:04    $
     $Revision:: 23                   $             $Modtime:: 5.12.00 10:02    $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Common Tool Classes, Functions and Macros
   created       : 23.7.97

 * $Log: /current_work/ZenGin/_dieter/zTools.h $
 * 
 * 23    5.12.00 12:04 Moos
 * 
 * 22    4.12.00 18:23 Hildebrandt
 * 
 * 21    4.12.00 18:08 Hildebrandt
 * 
 * 20    4.12.00 16:49 Hildebrandt
 * 
 * 19    8.11.00 22:01 Hildebrandt
 * 
 * 18    8.11.00 21:59 Hildebrandt
 * 
 * 17    2.11.00 2:25 Hildebrandt
 * 
 * 16    21.09.00 8:56 Moos
 * 
 * 15    20.09.00 22:56 Rueve
 * 
 * 14    20.09.00 15:52 Rueve
 * 
 * 13    20.09.00 15:16 Rueve
 * 
 * 12    20.09.00 1:48 Rueve
 * 
 * 11    31.08.00 16:46 Keskenti
 * 
 * 10    31.08.00 15:09 Keskenti
 * 
 * 9     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 8     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 5     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 4     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 23 $ ($Modtime: 5.12.00 10:02 $)

// Type definitions

#ifndef __ZTOOLS_H__
#define __ZTOOLS_H__

#include <assert.h>		// once for all... FIXME: TEMP
#include <math.h>
#include <stdlib.h>

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif



// ===========================================================================================================

class zFILE;		// zDisk.h
class zSTRING;		// zString.h

// ===========================================================================================================


/*--------------------------------------------------------------------------
    class zCTimer

    30-Aug-00       [Roman Keskenti]
                      Added motion-speed-factor
    05-Dec-00       [Moos]
                      Added possibility framerate limitation

--------------------------------------------------------------------------*/ 

class zCTimer {
public:
	zCTimer();
	// output: miliseconds
	zDWORD	GetFrameTime	() const { return frameTime;		};
	zDWORD	GetTotalTime	() const { return totalTime;		};
	zREAL	GetFrameTimeF	() const { return frameTimeFloat;	};
	zREAL	GetFrameTimeFSecs() const { return frameTimeFloatSecs;	};
	zREAL	GetTotalTimeF	() const { return totalTimeFloat;	};
	zREAL	GetTotalTimeFSecs() const { return totalTimeFloatSecs;	};
	zREAL	GetMotionFactor () const { return factorMotion;		};
	void	ResetTimer		();
	static void	FrameUpdate ();        // to be called every frame
	static void		S_SetMaxFPS	(const zDWORD a_iMaxFPS);
	static zDWORD	S_GetMaxFPS	();
    void    LimitFPS        (int fps); // limits the framerate to this value; fps=0 removes the limit.
	void	SetFrameTime	(const zREAL ftimeMSec);
	void	SetMotionFactor	(const zREAL fFactorMotion)				{ factorMotion = fFactorMotion; }
	void	SetMaxFPS		(const zDWORD a_iMaxFPS);
private:
	static zDWORD s_forcedMaxFrameTime;
	zREAL	factorMotion;
	zREAL	frameTimeFloat;
	zREAL	totalTimeFloat;
	zREAL	frameTimeFloatSecs;
	zREAL	totalTimeFloatSecs;
	zDWORD	lastTimer;
	zDWORD	frameTime;
	zDWORD	totalTime;
    zDWORD  minFrameTime;
	
	zDWORD	forcedMaxFrameTime;
};

extern zCTimer ztimer;

// ===========================================================================================================

class zCChecksum {
public:
	zCChecksum() { checksum=0; };
	void			BeginChecksum			();
	zDWORD			EndChecksum				();
	zDWORD			GetChecksum				() const	{ 	return checksum; };
					
	void			CalcBufferChecksum		(zBYTE	*buffer, zDWORD bufferSize);
	void			CalcFileChecksum		(zFILE	*file);
	void			CalcFileChecksum		(const	zSTRING& fileName);
	void			CalcDirectoryChecksum	();										// recursive

	static zDWORD	GetBufferCRC32			(zBYTE *buffer, zDWORD bufferSize, zDWORD crc=0);

protected:
	zDWORD			checksum;
};

// ===========================================================================================================

class zCChecksum16 {
public:
	zCChecksum16() { checksum=0; };
	void			BeginChecksum			();
	zWORD			EndChecksum				();
	zWORD			GetChecksum				() const	{ 	return checksum; };
					
	void			CalcBufferChecksum		(zBYTE *buffer, zDWORD bufferSize);

	static zWORD	GetBufferCRC16			(zBYTE *buffer, zDWORD bufferSize, zWORD _crc=0);
protected:
	zWORD			checksum;
};

// ===========================================================================================================

// handy macros

// FIXME: remove-me!
// min-max macros
#define MIN(A,B) ((A) < (B) ? (A) : (B))
#define MAX(A,B) ((A) > (B) ? (A) : (B))

#define zSign(a)				(((a)<0) ? -1 : (a)>0 ? 1 : 0)
#define	zNotInRange(a,low,high)	(((a)<(low)) || ((a)>(high)))
#define	zInRange(a,low,high)	(((a)>=(low)) && ((a)<=(high)))

// ===========================================================================================================

// FPU Control-Word defaults
//	MSDEV Default				: double prec, round nearest, exceptions disabled
//	DirectX7					: single prec, round nearest, exceptions disabled

// Typecast float=>int rounding
//	C-Standard (int-typecast)	:	rounds to zero:		+3.2=>+3.0, +3.7=>+3.0, -3.2=>-3.0, -3.7=>-3.0, 
//	zFloat2Int					:	rounds to nearest:	+3.2=>+3.0, +3.7=>+4.0, -3.2=>-3.0, -3.7=>-4.0, 

// ===========================================================================================================

inline float zFloor	(const float a) { return float (floor(a)); }
inline float zCeil	(const float a) { return float (ceil(a)); }
inline float zAbsApprox	(const float a) {
	// src: sin dll-Source1.01
	// FIXME: ARGH, kann leider nicht als zAbs() benutzt werden, da sonst
	//        zCPoly::CalcNormal() (ruft .IsEqual()), IsColinear(), IsEqualEps() Probs macht, 
	//        aber warum nur ??
	// MR: dieser Kommentar ist echt antik (aus Mitte 99)...
	int tmp = * ( int * ) &a;
	tmp &= 0x7FFFFFFF;
	return * ( float * ) &tmp;
};

inline float zAbs(const float a)
{
	return fabs(a);
}

//inline __declspec(naked) float __fastcall zAbs (const float a)
//{
//	__asm {
//		fld		DWORD PTR [esp+4] 
//		fabs
//		ret 4
//	}
//}

inline int zAbs (const int a) {
	return abs(a);
}


// ===========================================================================================================

// quick type cast float => int, ROUNDING
inline int zFloat2Int (const float f)
{
	int i;
	__asm fld [f]
	__asm fistp [i]
	return i;
}

// quick type cast float => int, FLOOR
inline int zFloat2IntFloor (const float f)
{
/*	static float half=0.5F;		// FIXME: this faster ASM version sometimes gives wrong results!
	int i;
	__asm fld	[f]
	__asm fsub	[half]
	__asm fistp [i]
	return i;*/
	return zFloat2Int(zFloor(f));
}

// quick type cast float => int, CEILING
inline int zFloat2IntCeil (const float f)
{
/*	static float half=0.49999F;	// FIXME: this faster ASM version sometimes gives wrong results!
	int i;
	__asm fld	[f]
	__asm fadd	[half]
	__asm fistp [i]
	return i;*/
	return zFloat2Int(zCeil(f));
}

/*
// Quick Conversion float => int32 
// implicit rounding
// ATTENTION: gives incorrect results in single-precision FPU mode!!
inline zLONG zFloat2Int (float inval) {
	#define FIST_MAGIC ((((65536.0 * 65536.0 * 16)+(65536.0 * 0.5))* 65536.0))
	const double dtemp = FIST_MAGIC + inval;
	return ((*(zLONG *)&dtemp) - 0x80000000);
	#undef FIST_MAGIC
}

inline void zFloat2Int (int *i, const float f) {
	_asm	fld		f
	_asm	mov		edx,i
	_asm	fistp	[edx]
};

// This converts a floating point number to a 16.16 fixed point integer. 
// It is equivalent to 'i=(int)(f*65536.)'.

inline zLONG zFloat2Fix16 (float inval) {
	#define FIST_MAGIC2 ((((65536.0 * 16)+(0.5))* 65536.0))
	double dtemp = FIST_MAGIC2 + inval;
	return ((*(zLONG *)&dtemp) - 0x80000000);
	#undef FIST_MAGIC2
}
*/
// ===========================================================================================================

// Controling FPU Behaviour

class zCFPUControler {
public:
	//
	zCFPUControler();
	void		SaveCurrentControlWord	();
	void		RestoreSavedControlWord	();

	//
	void		RestoreDefaultControlWord();

	//
	zDWORD		GetCurrentControlWord	();
	void		SetControlWord			(const zDWORD cw);

	// precision
	void		SetPrecision_24			();
	void		SetPrecision_53			();
	void		SetPrecision_64			();

	// debug
	void		PrintStatus				();
private:
	zDWORD		savedControlWord;
	zDWORD		defaultControlWord;

	void		ComputeDefaultControlWord();
};

extern zCFPUControler zfpuControler;

// ===========================================================================================================

const int zRAND_MAX = RAND_MAX;

inline int zRand () {
	// [0, zRAND_MAX]
	return rand();
};

inline int zRand (int max) {
	return rand() % max;
};

inline zREAL zRandF () {	
	// returns float-random in range [0.0F, 1.0F]
	return zREAL(rand()) / zREAL(RAND_MAX);
};

inline zREAL zRandF (const zREAL max) {	
	// returns float-random in range [0.0F, 1.0F]
	return (zREAL(rand()) / zREAL(RAND_MAX)) * max;
};

inline zREAL zRandF2 () {
	// returns float-random in range [-1.0F, 1.0F]
	const zREAL RAND_HALVE		= (zREAL(zRAND_MAX) * zREAL(0.5F)); 
	const zREAL RAND_HALVEINV	= zREAL(1.0F) / RAND_HALVE; 
	return ((zREAL(zRand()) - RAND_HALVE) * RAND_HALVEINV);
};

// ===========================================================================================================

// fast scalar inverse
// source: nvidias "fastmath.cpp"
// out = 1/in

extern const float zfloatTwo;

#define zFloatInv(in,out)                  \
{										   \
    __asm { mov     eax,0x7F000000		}; \
    __asm { sub     eax,dword ptr [in]	}; \
    __asm { mov     dword ptr [out],eax }; \
    __asm { fld     dword ptr [in]		}; \
    __asm { fmul    dword ptr [out]     }; \
    __asm { fsubr   [zfloatTwo]			}; \
    __asm { fmul    dword ptr [out]     }; \
    __asm { fstp    dword ptr [out]     }; \
}
//#define zFloatInverse(in,out) { out = float(1) / in; }

// ===========================================================================================================

template <class T>
inline T zLerp (const float t, const T& a, const T& b) {
	return a + t*(b-a);
}

template <class T>
inline void zClamp (T& x, const T min, const T max) {
	if (x<min) x=min; else
 	if (x>max) x=max;	
}

//
// Fast 32-bit float evaluations. 
// Warning: likely not portable, and useful on Pentium class processors only.
//

inline zBOOL zIsSmallerPositive (const float f1,const float f2) {
	return ( (*(zDWORD*)&f1) < (*(zDWORD*)&f2));
}

inline zBOOL zIsGreaterPositive (const float f1,const float f2) {
	return ( (*(zDWORD*)&f1) > (*(zDWORD*)&f2));
}

inline float zMinPositive (const float f1, const float f2) {
	if ( (*(zDWORD*)&f1) < (*(zDWORD*)&f2))	return f1; 
	else									return f2;
}

inline float zMaxPositive (const float f1, const float f2) {
	if ( (*(zDWORD*)&f1) < (*(zDWORD*)&f2))	return f2; 
	else									return f1;
}

//
// Warning: 0 and -0 have different binary representations.
//

inline zBOOL zIsEqualPositive (const float f1, const float f2) {
	return ( *(zDWORD*)&f1 == *(zDWORD*)&f2 );
}

inline zBOOL zIsNegative (const float f1) {
	return ( (*(zDWORD*)&f1) >= (zDWORD)0x80000000 );	// Detects sign bit.
}

inline zBOOL zIsGreaterZero (const float f1) {
	return !((*(zDWORD*)&f1) & 0x80000000 );			// Detects sign bit.
}

//			if(!(*((uint32 *)&eDist) & 0x80000000))	//if edist > 0
//			if(*((uint32 *)&eDist) & 0x80000000)	//if edist < 0


// Clamp any float F0 between zero and positive float Range
inline void zClampFromZero (float& f, const float range)	{
	if ( (*(zDWORD*)&f) >=   (zDWORD)0x80000000)	f = 0.f;	else
	if ( (*(zDWORD*)&f) >  (*(zDWORD*)&range))		f = range;
}

// clamps f between min and max, all positive assumed.
inline void zClampPositive (float& f, const float min, const float max) {
	if (*(zDWORD*)&f < *(zDWORD*)&min)	f=min;			else
	if (*(zDWORD*)&f > *(zDWORD*)&max)	f=max;
}	

// clamps f to [0..1]
inline void zClamp01 (float& f) {
	if ((*(zDWORD*)&f) >= (zDWORD)0x80000000)	f= 0.f; else
	if ((*(zDWORD*)&f) >  (zDWORD)0x3f800000)	f=1.0F;
/*
// Pentium2:
	cmp		[f],0
	cmovb	[f],0
	cmp		[f],3f800000
	cmova	[f],3f800000
*/
}	

// tests f to range [0..1]
inline zBOOL zIsInRange01 (const float f) {
	if (( (*(zDWORD*)&f) >= (zDWORD)0x80000000 ) || (*(zDWORD*)&f > 0x3f800000))	return FALSE;
	return TRUE;
}	

template <class T>
inline void zSwap (T& a, T& b) {
	const T tmp	= a;
	a			= b;
	b			= tmp;
}

/*
template <class T>
inline T zMin (const T& a, const T& b) {
	if (a<b) return a;
	else	 return b;
}

template <class T>
inline T zMax (const T& a, const T& b) {
	if (a>b) return a;
	else	 return b;
}
*/

inline float zMin (const float a, const float b) {
	if (a<b) return a;
	else	 return b;
}

inline float zMax (const float a, const float b) {
	if (a>b) return a;
	else	 return b;
}

inline int zMin (const int a, const int b) {
	if (a<b) return a;
	else	 return b;
}

inline int zMax (const int a, const int b) {
	if (a>b) return a;
	else	 return b;
}


template< class T > inline T zAlignPtr ( const T ptr, int alignment )
{
	return (T)(((zDWORD)ptr + alignment - 1) & ~(alignment-1));
}

inline int zGetHighestBit (int value) {
	int mask = 1 << (sizeof(int)*8-1);
	int bit = 31;

	while ( ((value & mask) == 0) && (bit>0))	{
		bit--;
		mask = mask >> 1;
	}
	
/* wenig effizient:
	// das höchstwertigste bit suchen
	int last,i;
	last = i = 0;
	do {
		if (value & 1) last = i;
		value = value >> 1;
		i++;
	} while (value!=0);

	if (bit != last)
		abort();*/

	return bit;
};

inline int zMakePowerOf2Lower (int value) {
	return 1<<zGetHighestBit (value);
};

inline int zMakePowerOf2Higher (int value) {
	// das höchstwertigste bit+1 suchen
	int i = zMakePowerOf2Lower (value);
	if (value>i) i = i << 1;
	
	return i;
};

// ===========================================================================================================
// FSinCos:  sin in ST(0), cos on ST(1)

/*inline __declspec(naked) float __fastcall zSin (const float a) {
	__asm {
		fld		DWORD PTR [esp+4] 
		fsin
		ret 4
	}
}

inline __declspec(naked) float __fastcall zCos (const float a) {
	__asm {
		fld		DWORD PTR [esp+4] 
		fcos
		ret 4
	}
}
*/


inline float zSin (const float a)
{
	return sinf(a);
};

inline float zCos(const float a)
{
	return cosf(a);
};

inline void zSinCos(const float a, float &sinval, float &cosval)
{
	sinval = sinf(a);
	cosval = cosf(a);
};

float zSinApprox	(const float a);
float zCosApprox	(const float a);
void  zSinCosApprox	(const float a, float &sinval, float &cosval);

// ===========================================================================================================

inline zREAL zSinusEase (const zREAL t) {
	// in/out: 0..1
	const zREAL _PI = 3.14159265358979323846F;
	return zREAL((zSinApprox (t*_PI- _PI/2)+1)/2);
};

inline zREAL zSinusSlowStart (const zREAL t) {
	// in/out: 0..1
	const zREAL _PI = 3.14159265358979323846F;
	return 1.0F - zREAL(zCosApprox(t*(_PI/2)));
};

inline zREAL zSinusSlowEnd (const zREAL t) {
	// in/out: 0..1
	const zREAL _PI = 3.14159265358979323846F;
	return zREAL(zSinApprox (t*(_PI/2)));
};

// ===========================================================================================================







#endif
