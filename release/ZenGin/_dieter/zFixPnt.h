/******************************************************************************** 
 
     $Workfile:: zFixpnt.h            $                $Date:: 4.12.00 17:18    $
     $Revision:: 6                    $             $Modtime:: 4.12.00 16:37    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Fixpoint Library
   created       : 27.11.96

 * $Log: /current_work/zengin_work/_Dieter/zFixpnt.h $
 * 
 * 6     4.12.00 17:18 Hildebrandt
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
/// @version $Revision: 6 $ ($Modtime: 4.12.00 16:37 $)


#ifndef __ZFIXPOINT_H__
#define __ZFIXPOINT_H__

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

// noch zu implementierende Typen (ueber overloading):

typedef long		TFix18_14;
typedef long		TFix24_8;
typedef long		TFix28_4;
typedef short int	TFix8_8;

// for all fixpoint types

#define Fix_Add (a1, a2) ((a1) + (a2))
#define Fix_Sub (s1, s2) ((s1) - (s2))

//**********************************************
//
// fixpoint:       16_16
//

typedef long zFIX;
#define ZFIX_BASE	65536
#define ZFIX_SHL	16

#ifndef FIXBASE
#define FIXBASE		65536
#define FIXBASEHALF	32768
#define FIXSHL		16
#endif

//----------------------------------------------
//
// handy constants
//

#define FIX_16ZERO (zFIX)(0)
#define FIX_16ONE  (zFIX)(1 << FIXSHL)
#define FIX_16TWO  (zFIX)(2 << FIXSHL)
#define FIX_16HALF (zFIX)(1 << (FIXSHL-1))
#define FIX_16PI   (zFIX)(TRG_PI * FIXBASE)


//----------------------------------------------
//
// Conversion Funcs, to and from fixpoint
//

//#define fixInt2Fix  (x) ((x) << FIXSHL)
//#define fixArg2Fix  (x) ((zFIX)((x) * FIXBASE))
//#define fix2Int     (x) ((x) >> FIXSHL)
//#define fix2Double  (x) ((double)(x) / FIXBASE)

inline zFIX		Fix_Int2Fix		(const int a)    { return (zFIX)(a << FIXSHL); }
inline zFIX		Fix_Float2Fix	(const float a)  { return (zFIX)(a * FIXBASE); }
inline zFIX		Fix_Double2Fix	(const double a) { return (zFIX)(a * FIXBASE); }
inline int      Fix_2Int		(const zFIX a)   { return (int)(a >> FIXSHL); }
inline float    Fix_2Float		(const zFIX a)   { return ((float)a) / FIXBASE; }
inline double   Fix_2Double		(const zFIX a)   { return ((double)a) / FIXBASE; }
inline zFIX		Fix_Frac		(const zFIX a)   { return (zFIX)(a & (FIXBASE-1)); }
inline zFIX		Fix_Trunc		(const zFIX a)   { return (a & ((FIXBASE-1) << FIXSHL)); }
inline zFIX		Fix_Round		(const zFIX a)   { return ((a + (1 << (FIXSHL-1)) & ((FIXBASE-1) << FIXSHL))); }
inline int		Fix_Ceil2Int	(const zFIX a)	 { return ((a + FIXBASE) >> FIXSHL); };

//----------------------------------------------
//
// math-functions
//

inline zFIX Fix_Mul (const zFIX a , const zFIX b)
{
	register zFIX erg;
	_asm {
		MOV  eax, DWORD PTR [a]
		IMUL DWORD PTR [b]
		SHRD eax, edx, FIXSHL
		MOV  DWORD PTR [erg], eax
	}
	return erg;
}

inline zFIX Fix_Div (const zFIX a , const zFIX b)
{
	register zFIX erg;
	_asm {
       SUB  eax, eax
       MOV  edx, DWORD PTR [a]
       SHRD eax, edx, FIXSHL
       SAR  edx, FIXSHL
       IDIV DWORD PTR [b]
	   MOV  DWORD PTR [erg], eax
	}
	return erg;
}

// Division mit zusaetzlichem check auf (DIV0). In diesem Fall: erg=0.
inline zFIX Fix_Div0 (const zFIX a , const zFIX b)
{
	if (b==0) return 0;
	register zFIX erg;
	_asm {
       SUB  eax, eax
       MOV  edx, DWORD PTR [a]
       SHRD eax, edx, FIXSHL
       SAR  edx, FIXSHL
       IDIV DWORD PTR [b]
	   MOV  DWORD PTR [erg], eax
	}
	return erg;
}

inline zFIX Fix_Inv    (const zFIX a)   { return Fix_Div (1, a); }
/*inline zFIX Fix_DivSHL (const zFIX a, const zFIX b, const int anz)
{
	return 0;
}
*/

/*
;**************************************************************************
fixDivSHL PROC FAR
       ARG  z : DWORD,  n : DWORD, anz : BYTE
; Dividiert zwei Fixed-Point 32-Bit (16/16) Zahlen.
;**************************************************************************
;
; Ist Divisor=0 ? => nicht dividieren und Ergebnis auf 0
       CMP  n, 0
       JNE  yeah
       XOR  ax, ax
       XOR  dx, dx
       RET
yeah:                   ; (z / n)
       MOV   cl , anz
       ADD   cl , 16
       MOV   eax, z
       CDQ
       SHLD  edx, eax, cl
       SHL   eax, cl
       IDIV  n
       SHLD edx, eax, 16

       RET
fixDivSHL ENDP
;**************************************************************************
*/

// zCFIX24_8

// zCFIX: Standard 16.16 Fixpoint

class zCFIX {

public:
	
	// value
	int	n;

	// constructors
	zCFIX ()			{ };
	zCFIX (int    a)	{ n = a << FIXBASE; };
	zCFIX (float  a)	{ n = int(a * FIXBASE); };        
	zCFIX (double a)	{ n = int(a * FIXBASE); };
	
	// conversion
	float	ToFloat () { return float (this->n / FIXBASE); };
	double	ToDouble() { return double(this->n / FIXBASE); };
	int		ToInt   () { return int   (this->n >> FIXSHL); };
	zREAL	TozReal () { return zREAL (this->n / FIXBASE); };
	
	// numeric
	zCFIX	Frac	 () { return (this->n & (FIXBASE-1)); }
	zCFIX	Trunc	 () { return (this->n & ((FIXBASE-1) << FIXSHL)); }
	zCFIX	Round	 () { return (this->n + (1 << (FIXSHL-1)) & ((FIXBASE-1) << FIXSHL)); }
	zFIX	Inverse  () { return (int(FIXBASE) / this->n); }

	// arithmetic
	friend zCFIX operator + (const zCFIX a ,const zCFIX b);
	friend zCFIX operator - (const zCFIX a ,const zCFIX b);
	friend zCFIX operator * (const zCFIX a ,const zCFIX b);
	friend zCFIX operator / (const zCFIX a ,const zCFIX b);
	zCFIX operator += (const zCFIX a) { return (n += a.n); };
	zCFIX operator -= (const zCFIX a) { return (n -= a.n); };
	zCFIX operator *= (const zCFIX a) { return (*this = (*this * a)); };
	zCFIX operator /= (const zCFIX a) { return (*this = (*this / a)); };

	// comparison
	friend zBOOL operator == (const zCFIX a, const zCFIX b) { return (a.n==b.n); };
	friend zBOOL operator  < (const zCFIX a, const zCFIX b) { return (a.n <b.n); };
	friend zBOOL operator  > (const zCFIX a, const zCFIX b) { return (a.n >b.n); };
	friend zBOOL operator != (const zCFIX a, const zCFIX b) { return (a.n!=b.n); };
	friend zBOOL operator <= (const zCFIX a, const zCFIX b) { return (a.n<=b.n); };
	friend zBOOL operator >= (const zCFIX a, const zCFIX b) { return (a.n>=b.n); };
	// stream
	//friend ostream& operator<< (ostream& s, zCFIX& a);
};

// friend definitions
inline zCFIX operator + (const zCFIX a, const zCFIX b) 
{	return zCFIX( a.n + b.n );  };

inline zCFIX operator - (const zCFIX a,const zCFIX b) 
{	return zCFIX( a.n + b.n );  };

inline zCFIX operator * (const zCFIX a, const zCFIX b)
{
	register zCFIX erg;
	_asm {
		MOV  eax, DWORD PTR [a]
		IMUL DWORD PTR [b]
		SHRD eax, edx, FIXSHL
		MOV  DWORD PTR [erg], eax
	}
	return erg;
}

inline zCFIX operator / (const zCFIX a , const zCFIX b)
{
	register zCFIX erg;
	_asm {
       SUB  eax, eax
       MOV  edx, DWORD PTR [a]
       SHRD eax, edx, FIXSHL
       SAR  edx, FIXSHL
       IDIV DWORD PTR [b]
	   MOV  DWORD PTR [erg], eax
	}
	return erg;
}
/*
ostream& operator<< (ostream& s, zCFIX& a){
	//return a.ToDouble();
	return s << a.ToDouble();
	return s;
};
istream& operator>> (istream& s, zCFIX& a)	{
	s >> ta;
	return s;
};
*/

#endif