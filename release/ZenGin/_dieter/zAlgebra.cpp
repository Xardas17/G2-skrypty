/******************************************************************************** 
 
     $Workfile:: zAlgebra.cpp         $                $Date:: 22.01.01 20:01   $
     $Revision:: 21                   $             $Modtime:: 22.01.01 14:28   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/ZenGin/_Dieter/zAlgebra.cpp $
 * 
 * 21    22.01.01 20:01 Moos
 * 
 * 20    17.01.01 0:22 Hildebrandt
 * 
 * 19    20.12.00 9:46 Moos
 * 
 * 18    4.12.00 17:18 Hildebrandt
 * 
 * 17    19.10.00 19:26 Hildebrandt
 * 
 * 16    4.10.00 16:38 Hildebrandt
 * 
 * 15    20.09.00 15:52 Rueve
 * 
 * 12    11.09.00 19:39 Speckels
 * 
 * 11    22.08.00 21:49 Hildebrandt
 * 
 * 10    15.08.00 23:54 Hildebrandt^
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 9     6.07.00 13:33 Hildebrandt
 * 
 * 5     9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 6     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 4     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 21 $ ($Modtime: 22.01.01 14:28 $)


/*																
*****************************************************************
* Original Author:												*
* Author: Jean-Francois DOUE									*
* Version 3.1 --- October 1993									*
* from: Graphic Gems IV											*
*																*
*****************************************************************
- bekannte Bugs:
*****************************************************************
- moegliche Optimierungen:	
	- linear Transform (vector3 * matrix4) kann noch für den 3d-Fall
	  optimiert werden (4. Zeile weg, Translation ohne Multipl.)
	- sin/cos aus den Tabellen nehmen (zTrigo.h)
*****************************************************************
- noch fehlende Funktionalitaeten:	
*****************************************************************
- Kommentare:
	- Coole Library. Jean hat ganze Arbeit geleistet.
	  Habe bereits einige Ergänzungen gemacht.
	- Ausmaß des "Klassen-Overheads" noch unbekannt.
	- Fehler landen auf dem Stream "cerr".
	- Stream I/O ist definiert ("<<",">>").
*/

#include <zAlgebra.h>
#include <zError.h>
#include <ctype.h>
#include <math.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 )

//#pragma optimize( "", off )

// for "GetDescription"
static const int MAX_FRAC = 8;
/*
// min-max macros
#define MIN(A,B) ((A) < (B) ? (A) : (B))
#define MAX(A,B) ((A) > (B) ? (A) : (B))
*/
/****************************************************************
*																*
*		    zVEC2 Member functions								*
*																*
****************************************************************/


/*
zREAL& zVEC2::operator [] ( int i) {
    if (i < VX || i > VY)
	zerr.Report (zERR_WARN,1000,"D: zAlgebra(zVEC2 [] operator): illegal access; index = " + zSTRING(i));
    return n[i];
}
*/


zVEC2& zVEC2::Apply(V_FCT_PTR fct)
{ n[VX] = (*fct)(n[VX]); n[VY] = (*fct)(n[VY]); return *this; }

zSTRING zVEC2::GetDescription() const {
	return zSTRING(zSTRING(n[0],MAX_FRAC) + " " + zSTRING(n[1],MAX_FRAC));
};

void zVEC2::SetByDescription (const zSTRING& desc) {
	n[0] = desc.PickWord_Old (1,"").ToFloat();
	n[1] = desc.PickWord_Old (2,"").ToFloat();
};

ostream& operator << (ostream& s, zVEC2& v)
{ return s << "| " << v.n[VX] << ' ' << v.n[VY] << " |"; }

istream& operator >> (istream& s, zVEC2& v) {
    zVEC2	v_tmp;
    char	c = ' ';
	
    while (isspace(c))
		s >> c;
    // The vectors can be formatted either as x y or | x y |
    if (c == '|') {
		s >> v_tmp[VX] >> v_tmp[VY];
		while (s >> c && isspace(c)) ;
//		if (c != '|')
//			 s.set(_bad)  ;
	}
    else {
		s.putback(c);
		s >> v_tmp[VX] >> v_tmp[VY];
	}
    if (s)
		v = v_tmp;
    return s;
};

void Alg_Swap(zVEC2& a, zVEC2& b)
{ zVEC2 tmp(a); a = b; b = tmp; }

zVEC2 Alg_Min(const zVEC2& a, const zVEC2& b)
{ return zVEC2(zMin(a.n[VX], b.n[VX]), zMin(a.n[VY], b.n[VY])); }

zVEC2 Alg_Max(const zVEC2& a, const zVEC2& b)
{ return zVEC2(zMax(a.n[VX], b.n[VX]), zMax(a.n[VY], b.n[VY])); }

zVEC2 Alg_Prod(const zVEC2& a, const zVEC2& b)
{ return zVEC2(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY]); }




/****************************************************************
*																*
*		    zVEC3 Member functions								*
*																*
****************************************************************/

// CONSTRUCTORS

zVEC3::zVEC3(const zVEC4& v, int dropAxis) {
    switch (dropAxis) {
	case VX: n[VX] = v.n[VY]; n[VY] = v.n[VZ]; n[VZ] = v.n[VW]; break;
	case VY: n[VX] = v.n[VX]; n[VY] = v.n[VZ]; n[VZ] = v.n[VW]; break;
	case VZ: n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VW]; break;
	default: n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; break;
    }
}

zVEC3& zVEC3::Apply(V_FCT_PTR fct)
{ n[VX] = (*fct)(n[VX]); n[VY] = (*fct)(n[VY]); n[VZ] = (*fct)(n[VZ]);
return *this; }

ostream& operator << (ostream& s, zVEC3& v)
{ return s << "| " << v.n[VX] << ' ' << v.n[VY] << ' ' << v.n[VZ] << " |"; }

istream& operator >> (istream& s, zVEC3& v) {
    zVEC3	v_tmp;
    char	c = ' ';
	
    while (isspace(c))
		s >> c;
    // The vectors can be formatted either as x y z or | x y z |
    if (c == '|') {
		s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ];
		while (s >> c && isspace(c)) ;
		//	if (c != '|')
		//	   s.set(_bad)  ;
	}
    else {
		s.putback(c);
		s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ];
	}
    if (s)
		v = v_tmp;
    return s;
}

void Alg_Swap(zVEC3& a, zVEC3& b)
{ zVEC3 tmp(a); a = b; b = tmp; }

zVEC3 Alg_Min(const zVEC3& a, const zVEC3& b)
{ return zVEC3(zMin(a.n[VX], b.n[VX]), zMin(a.n[VY], b.n[VY]), zMin(a.n[VZ],
  b.n[VZ])); }

zVEC3 Alg_Max(const zVEC3& a, const zVEC3& b)
{ return zVEC3(zMax(a.n[VX], b.n[VX]), zMax(a.n[VY], b.n[VY]), zMax(a.n[VZ],
  b.n[VZ])); }

zVEC3 Alg_Prod(const zVEC3& a, const zVEC3& b)
{ return zVEC3(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY], a.n[VZ] * b.n[VZ]); }


/****************************************************************
*																*
*		    zVEC4 Member functions								*
*																*
****************************************************************/


// SPECIAL FUNCTIONS

inline zREAL zVEC4::Length()
{ return sqrt(Length2()); }

inline zREAL zVEC4::Length2()
{ return n[VX]*n[VX] + n[VY]*n[VY] + n[VZ]*n[VZ] + n[VW]*n[VW]; }

zREAL zVEC4::LengthApprox() {
	// Quelle: Gems5, Ch2, Paeth, len4.c
	// overestimating, max-error: 16%
	zREAL a = zAbs(n[0]);
	zREAL b = zAbs(n[1]);
	zREAL c = zAbs(n[2]);
	zREAL d = zAbs(n[3]);
	zREAL t;
	
	/* everyone has a chance to play */
	/* (a,d) are big (winner, loser) */
	/* playoff for 2nd and 3rd slots */
	if ((t = a - b) < 0) {a -= t; b += t; };
	if ((t = c - d) < 0) {c -= t; d += t; };
	if ((t = a - c) < 0) {a -= t; c += t; };
	if ((t = b - d) < 0) {b -= t; d += t; };
	if ((t = b - c) < 0) {b -= t; c += t; };
    a += (25*b + 19*c + 16*d)/60;	/* compute 4D approximate length */
//	a += ( 5*b +  4*c +  3*d)/12;	/* .. only .1% worse; easy to eval  */
//	a += 1;							/* Roundoff -> underestimation   */
    return(a);						/* omit the above one bit jitter */
}

zVEC4& zVEC4::Normalize() // it is up to caller to avoid divide-by-zero
{ *this /= Length(); return *this; }

zVEC4& zVEC4::Apply(V_FCT_PTR fct)
{ n[VX] = (*fct)(n[VX]); n[VY] = (*fct)(n[VY]); n[VZ] = (*fct)(n[VZ]);
n[VW] = (*fct)(n[VW]); return *this; }

// FRIENDS


ostream& operator << (ostream& s, zVEC4& v)
{ return s << "| " << v.n[VX] << ' ' << v.n[VY] << ' ' << v.n[VZ] << ' '
  << v.n[VW] << " |"; }

istream& operator >> (istream& s, zVEC4& v) {
    zVEC4	v_tmp;
    char	c = ' ';
	
    while (isspace(c))
		s >> c;
    // The vectors can be formatted either as x y z w or | x y z w |
    if (c == '|') {
		s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ] >> v_tmp[VW];
		while (s >> c && isspace(c)) ;
		//	if (c != '|')
		//	     s.set(_bad);
	}
    else {
		s.putback(c);
		s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ] >> v_tmp[VW];
	}
    if (s)
		v = v_tmp;
    return s;
}

void Alg_Swap(zVEC4& a, zVEC4& b)
{ zVEC4 tmp(a); a = b; b = tmp; }

zVEC4 Alg_Min(const zVEC4& a, const zVEC4& b)
{ return zVEC4(zMin(a.n[VX], b.n[VX]), zMin(a.n[VY], b.n[VY]), zMin(a.n[VZ],
  b.n[VZ]), zMin(a.n[VW], b.n[VW])); }

zVEC4 Alg_Max(const zVEC4& a, const zVEC4& b)
{ return zVEC4(zMax(a.n[VX], b.n[VX]), zMax(a.n[VY], b.n[VY]), zMax(a.n[VZ],
  b.n[VZ]), zMax(a.n[VW], b.n[VW])); }

zVEC4 Alg_Prod(const zVEC4& a, const zVEC4& b)
{ return zVEC4(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY], a.n[VZ] * b.n[VZ],
  a.n[VW] * b.n[VW]); }


/****************************************************************
*																*
*		    zMAT3 member functions								*
*																*
****************************************************************/

zMAT3 zMAT3::s_identity	= Alg_Identity2D();

// CONSTRUCTORS

zMAT3::zMAT3(const zVEC3& v0, const zVEC3& v1, const zVEC3& v2)
{ v[0] = v0; v[1] = v1; v[2] = v2; }

zMAT3::zMAT3(const zREAL d)
{ v[0] = v[1] = v[2] = zVEC3(d); }

zMAT3::zMAT3(const zMAT3& m)
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; }


// ASSIGNMENT OPERATORS

zMAT3& zMAT3::operator = ( const zMAT3& m )
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; return *this; }

zMAT3& zMAT3::operator += ( const zMAT3& m )
{ v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; return *this; }

zMAT3& zMAT3::operator -= ( const zMAT3& m )
{ v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; return *this; }

zMAT3& zMAT3::operator *= ( const zREAL d )
{ v[0] *= d; v[1] *= d; v[2] *= d; return *this; }

zMAT3& zMAT3::operator /= ( const zREAL d )
{ v[0] /= d; v[1] /= d; v[2] /= d; return *this; }


// SPECIAL FUNCTIONS

zMAT3 zMAT3::Transpose() const {
    return zMAT3(zVEC3(v[0][0], v[1][0], v[2][0]),
		zVEC3(v[0][1], v[1][1], v[2][1]),
		zVEC3(v[0][2], v[1][2], v[2][2]));
}

zMAT3 zMAT3::Inverse(zREAL *det)	    
{
	// Gauss-Jordan elimination with partial pivoting
/*
    zMAT3 a(*this),					// As a evolves from original mat into identity
		  b(Alg_Identity2D());		// b evolves from identity into Inverse(a)
    int	 i, j, i1;
	
    // Loop over cols of a from left to right, eliminating above and below diag
    for (j=0; j<3; j++) {   // Find largest pivot in column j among rows j..2
		i1 = j;					// Row with largest pivot candidate
		for (i=j+1; i<3; i++)
			if (fabs(a.v[i].n[j]) > fabs(a.v[i1].n[j]))
				i1 = i;
			
			// Swap rows i1 and j in a and b to put pivot on diagonal
			Alg_Swap(a.v[i1], a.v[j]);
			Alg_Swap(b.v[i1], b.v[j]);
			
			// Scale row j to have a unit diagonal
			if (a.v[j].n[j]==0.)
				zerr.Report (zERR_WARN,1000,"D: zAlgebra(zMAT3::Inverse): singular matrix; can't invert");
			b.v[j] /= a.v[j].n[j];
			a.v[j] /= a.v[j].n[j];
			
			// Eliminate off-diagonal elems in col j of a, doing identical ops to b
			for (i=0; i<3; i++)
				if (i!=j) {
					b.v[i] -= a.v[i].n[j]*b.v[j];
					a.v[i] -= a.v[i].n[j]*a.v[j];
				}
    }
    return b;
*/

	// Folgende direkte Berechnung ist schneller als die Gauss-Jordan Eliminierung
	{
		zVEC3 a (v[VY][VY] * v[VZ][VZ] - v[VY][VZ] * v[VZ][VY],
				 v[VY][VZ] * v[VZ][VX] - v[VY][VX] * v[VZ][VZ], 
				 v[VY][VX] * v[VZ][VY] - v[VY][VY] * v[VZ][VX]);
		zREAL d = v[VX] * a;

        if (det)
            *det = d;

#ifndef DEBUG_MOOS
		assert (d!=0);
#else
        if (d==0)
            d = 1;
#endif


		zREAL s = zREAL(1.0F) / d;
		return zMAT3(  zVEC3(a[VX] * s,
							 (v[VX][VZ] * v[VZ][VY] - v[VX][VY] * v[VZ][VZ]) * s,
							 (v[VX][VY] * v[VY][VZ] - v[VX][VZ] * v[VY][VY]) * s),
					   zVEC3(a[VY] * s,
							 (v[VX][VX] * v[VZ][VZ] - v[VX][VZ] * v[VZ][VX]) * s,
							 (v[VX][VZ] * v[VY][VX] - v[VX][VX] * v[VY][VZ]) * s),
					   zVEC3(a[VZ] * s,
							 (v[VX][VY] * v[VZ][VX] - v[VX][VX] * v[VZ][VY]) * s,
							 (v[VX][VX] * v[VY][VY] - v[VX][VY] * v[VY][VX]) * s));
	};
}

zMAT3& zMAT3::Apply(V_FCT_PTR fct) {
    v[VX].Apply(fct);
    v[VY].Apply(fct);
    v[VZ].Apply(fct);
    return *this;
}


// FRIENDS

zMAT3 operator - (const zMAT3& a)
{ return zMAT3(-(a.v[0]), -a.v[1], -a.v[2]); }

zMAT3 operator + (const zMAT3& a, const zMAT3& b)
{ return zMAT3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]); }

zMAT3 operator - (const zMAT3& a, const zMAT3& b)
{ return zMAT3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]); }

zMAT3 operator * (const zMAT3& a, const zMAT3& b) {
    #define ROWCOL(i, j) \
    a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + a.v[i].n[2]*b.v[2][j]
    return zMAT3(zVEC3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2)),
		zVEC3(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2)),
		zVEC3(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2)));
    #undef ROWCOL // (i, j)
}

zMAT3 operator * (const zMAT3& a, const zREAL d)
{ return zMAT3(a.v[0] * d, a.v[1] * d, a.v[2] * d); }

zMAT3 operator * (const zREAL d, const zMAT3& a)
{ return a*d; }

zMAT3 operator / (const zMAT3& a, const zREAL d)
{ return zMAT3(a.v[0] / d, a.v[1] / d, a.v[2] / d); }

int operator == (const zMAT3& a, const zMAT3& b)
{ return (a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]); }

int operator != (const zMAT3& a, const zMAT3& b)
{ return !(a == b); }

ostream& operator << (ostream& s, zMAT3& m)
{ return s << m.v[VX] << '\n' << m.v[VY] << '\n' << m.v[VZ]; }

istream& operator >> (istream& s, zMAT3& m) {
    zMAT3    m_tmp;

    s >> m_tmp[VX] >> m_tmp[VY] >> m_tmp[VZ];
    if (s)
	m = m_tmp;
    return s;
}

// Neu von mir dazu ...

void Alg_Swap(zMAT3& a, zMAT3& b)
{ zMAT3 tmp(a); a = b; b = tmp; }

zVEC3 operator * (const zMAT3& a, const zVEC3& v) {
	#define ROWCOL(i) a.v[i].n[0]*v.n[VX] + a.v[i].n[1]*v.n[VY] + a.v[i].n[2]*v.n[VZ]
    return zVEC3(ROWCOL(0), ROWCOL(1), ROWCOL(2));
	#undef ROWCOL // (i)
}

zMAT3 operator * (const zMAT4& a, const zMAT3& b) {
	// FIXME: mathematische Definition dieser Berechnung aufstellen ..
    #define ROWCOL(i, j) a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + a.v[i].n[2]*b.v[2][j]
    return zMAT3(zVEC3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2)),
				 zVEC3(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2)),
				 zVEC3(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2)));
    #undef ROWCOL // (i, j)
}

zMAT3 operator * (const zMAT3& a, const zMAT4& b) {
	// FIXME: mathematische Definition dieser Berechnung aufstellen ..
    #define ROWCOL(i, j) a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + a.v[i].n[2]*b.v[2][j]
    return zMAT3(zVEC3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2)),
				 zVEC3(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2)),
				 zVEC3(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2)));
    #undef ROWCOL // (i, j)
}

/****************************************************************
*																*
*		    zMAT4 member functions								*
*																*
****************************************************************/

zMAT4 zMAT4::s_identity	= Alg_Identity3D();

// CONSTRUCTORS

zMAT4::zMAT4(const zVEC4& v0, const zVEC4& v1, const zVEC4& v2, const zVEC4& v3)
{ v[0] = v0; v[1] = v1; v[2] = v2; v[3] = v3; }

zMAT4::zMAT4(const zREAL d)
{ v[0] = v[1] = v[2] = v[3] = zVEC4(d); }

//zMAT4::zMAT4(const zMAT4& m)
//{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; v[3] = m.v[3]; }


// ASSIGNMENT OPERATORS

zMAT4& zMAT4::operator = ( const zMAT3& m ) {
	v[0] = zVEC4 (m.v[0], 0);
	v[1] = zVEC4 (m.v[1], 0);
	v[2] = zVEC4 (m.v[2], 0);
	v[3] = zVEC4 (0,0,0,1);
	return *this;
};

zMAT4& zMAT4::operator = ( const zMAT4& m )
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; v[3] = m.v[3];
return *this; }

zMAT4& zMAT4::operator += ( const zMAT4& m )
{ v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; v[3] += m.v[3];
return *this; }

zMAT4& zMAT4::operator -= ( const zMAT4& m )
{ v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; v[3] -= m.v[3];
return *this; }

zMAT4& zMAT4::operator *= ( const zREAL d )
{ v[0] *= d; v[1] *= d; v[2] *= d; v[3] *= d; return *this; }

zMAT4& zMAT4::operator /= ( const zREAL d )
{ v[0] /= d; v[1] /= d; v[2] /= d; v[3] /= d; return *this; }

// SPECIAL FUNCTIONS

zMAT4 zMAT4::Transpose() const {
    return zMAT4(zVEC4(v[0][0], v[1][0], v[2][0], v[3][0]),
				 zVEC4(v[0][1], v[1][1], v[2][1], v[3][1]),
				 zVEC4(v[0][2], v[1][2], v[2][2], v[3][2]),
				 zVEC4(v[0][3], v[1][3], v[2][3], v[3][3]));
}
/*
zMAT4 zMAT4::TransposeLinTrafo() const {
    return zMAT4(zVEC4( v[0][0], v[1][0], v[2][0],-v[0][3]),
				 zVEC4( v[0][1], v[1][1], v[2][1],-v[1][3]),
				 zVEC4( v[0][2], v[1][2], v[2][2],-v[2][3]),
				 zVEC4( v[3][0], v[3][1], v[3][2], v[3][3]));
}*/

zMAT4 zMAT4::TransposeLinTrafo() const {
	// rot transpose, translation=0, persp.-row=const
    zMAT4 m     (zVEC4( v[0][0], v[1][0], v[2][0], 0),
				 zVEC4( v[0][1], v[1][1], v[2][1], 0),
				 zVEC4( v[0][2], v[1][2], v[2][2], 0),
				 zVEC4( v[3][0], v[3][1], v[3][2], v[3][3]));
	m.SetTranslation (m * -GetTranslation());
	return m;
}

zMAT4 zMAT4::InverseLinTrafo () const {
//	return Inverse();
	// rot transpose, translation=0, persp.-row=const
    zMAT4 m     (zVEC4( v[0][0], v[1][0], v[2][0], 0),
				 zVEC4( v[0][1], v[1][1], v[2][1], 0),
				 zVEC4( v[0][2], v[1][2], v[2][2], 0),
				 zVEC4( v[3][0], v[3][1], v[3][2], v[3][3]));
	m.SetTranslation (m * -GetTranslation());
	return m;
};

/*
void ddgMatrix4::invert()	LinTrafo!
{
	ddgMatrix4 b = *this;

	b.m[0].v[0] = m[0].v[0];
  	b.m[0].v[1] = m[1].v[0];
	b.m[0].v[2] = m[2].v[0];
	b.m[1].v[0] = m[0].v[1];
	b.m[1].v[1] = m[1].v[1];
	b.m[1].v[2] = m[2].v[1];
	b.m[2].v[0] = m[0].v[2];
	b.m[2].v[1] = m[1].v[2];
	b.m[2].v[2] = m[2].v[2];
  
	// el nuevo vector desplazamiento es:  d' = -(R^-1) * d 
	b.m[3].v[0] = -( m[3].v[0] * b.m[0].v[0] + m[3].v[1] * b.m[1].v[0] + m[3].v[2] * b.m[2].v[0] );
	b.m[3].v[1] = -( m[3].v[0] * b.m[0].v[1] + m[3].v[1] * b.m[1].v[1] + m[3].v[2] * b.m[2].v[1] );
	b.m[3].v[2] = -( m[3].v[0] * b.m[0].v[2] + m[3].v[1] * b.m[1].v[2] + m[3].v[2] * b.m[2].v[2] );
  
	// el resto queda igual 
	b.m[0].v[3] = b.m[1].v[3] = b.m[2].v[3] = 0.0f; 
	b.m[3].v[3] = 1.0f;

	*this = b;
}
*/
/*
inline float nMatrix4D::Det(void)
{
    return
	    (m11*m22 - m12*m21)*(m33*m44 - m34*m43)
	   -(m11*m23 - m13*m21)*(m32*m44 - m34*m42)
	   +(m11*m24 - m14*m21)*(m32*m43 - m33*m42)
	   +(m12*m23 - m13*m22)*(m31*m44 - m34*m41)
	   -(m12*m24 - m14*m22)*(m31*m43 - m33*m41)
	   +(m13*m24 - m14*m23)*(m31*m42 - m32*m41);
}
inline void nMatrix4D::Invert(void)
{
	float s = Det();	
    if (s == 0.0) return;	
    s = 1/s;
    Set(
        s*(m22*(m33*m44 - m34*m43) + m23*(m34*m42 - m32*m44) + m24*(m32*m43 - m33*m42)),
        s*(m32*(m13*m44 - m14*m43) + m33*(m14*m42 - m12*m44) + m34*(m12*m43 - m13*m42)),
        s*(m42*(m13*m24 - m14*m23) + m43*(m14*m22 - m12*m24) + m44*(m12*m23 - m13*m22)),
        s*(m12*(m24*m33 - m23*m34) + m13*(m22*m34 - m24*m32) + m14*(m23*m32 - m22*m33)),
        s*(m23*(m31*m44 - m34*m41) + m24*(m33*m41 - m31*m43) + m21*(m34*m43 - m33*m44)),
        s*(m33*(m11*m44 - m14*m41) + m34*(m13*m41 - m11*m43) + m31*(m14*m43 - m13*m44)),
        s*(m43*(m11*m24 - m14*m21) + m44*(m13*m21 - m11*m23) + m41*(m14*m23 - m13*m24)),
        s*(m13*(m24*m31 - m21*m34) + m14*(m21*m33 - m23*m31) + m11*(m23*m34 - m24*m33)),
        s*(m24*(m31*m42 - m32*m41) + m21*(m32*m44 - m34*m42) + m22*(m34*m41 - m31*m44)),
        s*(m34*(m11*m42 - m12*m41) + m31*(m12*m44 - m14*m42) + m32*(m14*m41 - m11*m44)),
        s*(m44*(m11*m22 - m12*m21) + m41*(m12*m24 - m14*m22) + m42*(m14*m21 - m11*m24)),
        s*(m14*(m22*m31 - m21*m32) + m11*(m24*m32 - m22*m34) + m12*(m21*m34 - m24*m31)),
        s*(m21*(m33*m42 - m32*m43) + m22*(m31*m43 - m33*m41) + m23*(m32*m41 - m31*m42)),
        s*(m31*(m13*m42 - m12*m43) + m32*(m11*m43 - m13*m41) + m33*(m12*m41 - m11*m42)),
        s*(m41*(m13*m22 - m12*m23) + m42*(m11*m23 - m13*m21) + m43*(m12*m21 - m11*m22)),
        s*(m11*(m22*m33 - m23*m32) + m12*(m23*m31 - m21*m33) + m13*(m21*m32 - m22*m31)));
}
*/

zMAT4 zMAT4::Inverse() const
// Gauss-Jordan elimination with partial pivoting
{
    zMAT4 a(*this),			// As a evolves from original mat into identity
	 b(Alg_Identity3D());	// b evolves from identity into Inverse(a)
    int i, j, i1;

    // Loop over cols of a from left to right, eliminating above and below diag
    for (j=0; j<4; j++) {		// Find largest pivot in column j among rows j..3
		i1 = j;					// Row with largest pivot candidate
		for (i=j+1; i<4; i++)
			if (fabs(a.v[i].n[j]) > fabs(a.v[i1].n[j])) i1 = i;

		// Swap rows i1 and j in a and b to put pivot on diagonal
		Alg_Swap(a.v[i1], a.v[j]);
		Alg_Swap(b.v[i1], b.v[j]);

		// Scale row j to have a unit diagonal
		if (a.v[j].n[j]==0.) {
			zERR_WARNING("D: zAlgebra(zMAT4::Inverse): singular matrix; can't invert");
			return b;
		};
		zREAL inv = zREAL(1) / a.v[j].n[j];
		b.v[j] *= inv;
		a.v[j] *= inv;

		// Eliminate off-diagonal elems in col j of a, doing identical ops to b
		for (i=0; i<4; i++)
		if (i!=j) {
			b.v[i] -= a.v[i].n[j]*b.v[j];
			a.v[i] -= a.v[i].n[j]*a.v[j];
		}
    }
    return b;
}

zMAT4& zMAT4::Apply(V_FCT_PTR fct)
{ v[VX].Apply(fct); v[VY].Apply(fct); v[VZ].Apply(fct); v[VW].Apply(fct); return *this; }

zBOOL zMAT4::IsUpper3x3Orthonormal() const
{
	const zREAL DOT_THRESH	= 0.01F;
	const zREAL LEN_THRESH	= 0.01F;

	zREAL dot, len;
	dot = zAbs(GetAtVector() * GetRightVector());	if (dot>DOT_THRESH)	return FALSE;
	dot = zAbs(GetAtVector() * GetUpVector()	 );	if (dot>DOT_THRESH)	return FALSE;
	dot = zAbs(GetUpVector() * GetRightVector());	if (dot>DOT_THRESH)	return FALSE;

	len	= GetAtVector().Length();	 if ((len<(1-LEN_THRESH)) || (len>(1+LEN_THRESH))) return FALSE;
	len	= GetUpVector().Length();	 if ((len<(1-LEN_THRESH)) || (len>(1+LEN_THRESH))) return FALSE;
	len	= GetRightVector().Length(); if ((len<(1-LEN_THRESH)) || (len>(1+LEN_THRESH))) return FALSE;
	return TRUE;
};

zSTRING zMAT4::GetDescriptionRot () const {
	zSTRING res;
//	cout << *this << endl;
	for (int x=0; x<3; x++)
		for (int y=0; y<3; y++) {
			res = res + zSTRING(v[y][x],MAX_FRAC)+" ";
		};
	return res;
};

zSTRING zMAT4::GetDescriptionPos () const {
	zSTRING res;
	zVEC3 pos;
	GetTranslation (pos);
	for (int x=0; x<3; x++)
		res = res + zSTRING(pos[x],MAX_FRAC)+" ";
	return res;
};

void zMAT4::SetByDescriptionRot (zSTRING& desc) {
	int num=1;
	for (int x=0; x<3; x++)
		for (int y=0; y<3; y++) {
			v[y][x] = desc.PickWord_Old (num, " ").ToFloat();
			num++;
		};
};

void zMAT4::SetByDescriptionPos (zSTRING& desc) {
	zVEC3 pos;
	for (int x=0; x<3; x++)
		pos[x] = desc.PickWord_Old (x+1, " ").ToFloat();
	SetTranslation (pos);
};

/*
  euler => mat
 Thus, the final algorithm is as follows:

    -----------------------

    A       = cos(angle_x);
    B       = sin(angle_x);
    C       = cos(angle_y);
    D       = sin(angle_y);
    E       = cos(angle_z);
    F       = sin(angle_z);

    AD      =   A * D;
    BD      =   B * D;

    mat[0]  =   C * E;
    mat[1]  =  -C * F;
    mat[2]  =  -D;
    mat[4]  = -BD * E + A * F;
    mat[5]  =  BD * F + A * E;
    mat[6]  =  -B * C;
    mat[8]  =  AD * E + B * F;
    mat[9]  = -AD * F + B * E;
    mat[10] =   A * C;

    mat[3]  =  mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
    mat[15] =  1;


  mat => euler
 ***************

    angle_y = D = -asin( mat[2]);
    C           =  cos( angle_y );
    angle_y    *= RADIANS;

    if ( fabs( angle_y ) > 0.0005 )
      {
      trx      =  mat[10] / C;
      try      = -mat[6]  / C;

      angle_x  = atan2( try, trx ) * RADIANS;

      trx      =  mat[0] / C;
      try      = -mat[1] / C;

      angle_z  = atan2( try, trx ) * RADIANS;
      }
    else
      {
      angle_x  = 0;

      trx      = mat[5];
      try      = mat[4];

      angle_z  = atan2( try, trx ) * RADIANS;
      }

    angle_x = clamp( angle_x, 0, 360 );
    angle_y = clamp( angle_y, 0, 360 );
    angle_z = clamp( angle_z, 0, 360 );

*/

/*
///////////////////////////////////////////////////////////////////////////////
//
// @mfunc Extract three angles, which will reproduce the matrix
//        if applyed in the order:
//           Rotation about X,
//           Rotation about Y
//           Rotation about Z
//
//  Angles are given in degrees !!!!
void CMatrix::GetRotationXYZ(
                  double& dAngX,     // @parm Angle about X
                  double& dAngY,     // @parm Angle about Y
                  double& dAngZ      // @parm Angle about Z
                         ) const
{
  double dCosX, dSinX, dCosY, dSinY, dCosZ, dSinZ;

  dSinY = -XAxisZ;

  dCosY =  sqrt(1 - dSinY * dSinY);

  if (fabs(dCosY) > 0.000001) {
    dCosX =  ZAxisZ / dCosY;
    dSinX =  YAxisZ / dCosY;

    dCosZ =  XAxisX / dCosY;
    dSinZ =  XAxisY / dCosY;
  }
  else {
    if (dSinY > 0.0) {
      dCosZ = 0.0;
      dSinZ = 1.0;
    }
    else {
      dCosZ = 0.0;
      dSinZ = -1.0;
    }

    dCosX = -YAxisX / dSinY;
    dSinX =  ZAxisX / dSinY;
  }

  if( dCosX >=  0.999999 )
    dAngX = 0;
  else if( dCosX <= -0.999999 )
    dAngX = 180;
  else
    dAngX = acos(dCosX) * 180. / PI;
  if (dSinX < 0.)
    dAngX = 360 - dAngX;

  if( dCosY >=  0.999999 )
    dAngY = 0;
  else if( dCosY <= -0.999999 )
    dAngY = 180;
  else
    dAngY = acos(dCosY) * 180. / PI;
  if( dSinY < 0. )
    dAngY = 360 - dAngY;

  if( dCosZ >= 0.999999 )
    dAngZ = 0;
  else if( dCosZ <= -0.999999 )
    dAngZ = 180;
  else
    dAngZ = acos(dCosZ) * 180. / PI;
  if( dSinZ < 0. )
    dAngZ = 360 - dAngZ;
}
*/

zVEC3 zMAT4::GetEulerAngles () const {
	// FIXME: geht wohl auch direkter & schneller
	zVEC3 euler;
	zCQuat quat;
	quat.Matrix4ToQuat	(*this);
	quat.QuatToEuler	(euler);

	return euler;
};

void zMAT4::SetByEulerAngles (const zVEC3 euler) {
	zCQuat quat;
	quat.EulerToQuat	(euler); 
	quat.QuatToMatrix4	(*this);
};

/*

  Matrix/Euler Funcs 
  src: sin dll-source, q_shared.c


void VectorsToEulerAngles (vec3_t forward,vec3_t right,vec3_t up,vec3_t ang){
	double theta;
	double cp;
	double sp;

	sp = forward[ 2 ];

	// cap off our sin value so that we don't get any NANs
	if ( sp > 1.0 ){sp = 1.0;}
	if ( sp < -1.0 ){sp = -1.0;}

	theta = -asin( sp );
	cp = cos( theta );

	if ( cp > 8192 * FLT_EPSILON ) {
		ang[ 0 ] = theta * 180 / M_PI;
		ang[ 1 ] = atan2( forward[ 1 ], forward[ 0 ] ) * 180 / M_PI;
		ang[ 2 ] = atan2( -right[ 2 ], up[ 2 ] ) * 180 / M_PI;
	} else{
		ang[ 0 ] = theta * 180 / M_PI;
		ang[ 1 ] = -atan2( right[ 0 ], right[ 1 ] ) * 180 / M_PI;
		ang[ 2 ] = 0;
	}
}

void MatrixToEulerAngles (float mat[ 3 ][ 3 ],vec3_t ang) {
	double theta;
	double cp;
	double sp;

	sp = mat[ 0 ][ 2 ];

	// cap off our sin value so that we don't get any NANs
	if ( sp > 1.0 ) {	sp = 1.0;}
	if ( sp < -1.0 ){sp = -1.0;}

	theta = -asin( sp );
	cp = cos( theta );

	if ( cp > 8192 * FLT_EPSILON ) {
		ang[ 0 ] = theta * 180 / M_PI;
		ang[ 1 ] = atan2( mat[ 0 ][ 1 ], mat[ 0 ][ 0 ] ) * 180 / M_PI;
		ang[ 2 ] = atan2( mat[ 1 ][ 2 ], mat[ 2 ][ 2 ] ) * 180 / M_PI;
	} else {
		ang[ 0 ] = theta * 180 / M_PI;
		ang[ 1 ] = -atan2( mat[ 1 ][ 0 ], mat[ 1 ][ 1 ] ) * 180 / M_PI;
		ang[ 2 ] = 0;
		}
	}
*/

// FRIENDS

zMAT4 operator - (const zMAT4& a)
{ return zMAT4(-a.v[0], -a.v[1], -a.v[2], -a.v[3]); }

zMAT4 operator + (const zMAT4& a, const zMAT4& b)
{ return zMAT4(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2],
  a.v[3] + b.v[3]);
}

zMAT4 operator - (const zMAT4& a, const zMAT4& b)
{ return zMAT4(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2], a.v[3] - b.v[3]); }

zMAT4 operator * (const zMAT4& a, const zREAL d)
{ return zMAT4(a.v[0] * d, a.v[1] * d, a.v[2] * d, a.v[3] * d); }

zMAT4 operator * (const zREAL d, const zMAT4& a)
{ return a*d; }

zMAT4 operator / (const zMAT4& a, const zREAL d)
{ return zMAT4(a.v[0] / d, a.v[1] / d, a.v[2] / d, a.v[3] / d); }

int operator == (const zMAT4& a, const zMAT4& b)
{ return ((a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]) &&
  (a.v[3] == b.v[3])); }

int operator != (const zMAT4& a, const zMAT4& b)
{ return !(a == b); }

ostream& operator << (ostream& s, zMAT4& m)
{ return s << m.v[VX] << '\n' << m.v[VY] << '\n' << m.v[VZ] << '\n' << m.v[VW]; }

istream& operator >> (istream& s, zMAT4& m)
{
    zMAT4    m_tmp;

    s >> m_tmp[VX] >> m_tmp[VY] >> m_tmp[VZ] >> m_tmp[VW];
    if (s)
	m = m_tmp;
    return s;
}

void Alg_Swap(zMAT4& a, zMAT4& b)
{ zMAT4 tmp(a); a = b; b = tmp; }

// Added

zVEC3 zMAT4::ExtractScaling() const
{
	//  aus algebraAux.h, von John Nagle
	//	Per Valerie Demers, Softimage.
	//	Transposed for mat4 matrices
	return(zVEC3(
	sqrt( v[ 0 ][ 0 ] * v[ 0 ][ 0 ] + v[ 1 ][ 0 ] * v[ 1 ][ 0 ] + v[ 2 ][ 0 ] * v[ 2 ][ 0 ] ),
	sqrt( v[ 0 ][ 1 ] * v[ 0 ][ 1 ] + v[ 1 ][ 1 ] * v[ 1 ][ 1 ] + v[ 2 ][ 1 ] * v[ 2 ][ 1 ] ),
	sqrt( v[ 0 ][ 2 ] * v[ 0 ][ 2 ] + v[ 1 ][ 2 ] * v[ 1 ][ 2 ] + v[ 2 ][ 2 ] * v[ 2 ][ 2 ] )));
}

zMAT3 zMAT4::ExtractRotation ()
{
	//  aus algebraAux.h, von John Nagle

	zVEC3 scale(ExtractScaling());	// get scaling
	//	Compute inverse of scaling
	zVEC3 invscale(1.0/scale[0],1.0/scale[1],1.0/scale[2]);
	//	Apply inverse of scaling as a transformation, to get unit scaling.
	zMAT4 unscaled((*this)*Alg_Scaling3D(invscale));// unscale pose
	//	Return pure rotation matrix
	return(zMAT3(						// drop last column and row
		zVEC3(unscaled[0],VW),
		zVEC3(unscaled[1],VW),
		zVEC3(unscaled[2],VW)));
}

void zMAT4::MakeOrthonormal () {
	//void Gram_Schmidt_Process( point *a, point *b, point *c ) {
	zVEC3 at,up,right;
	at		= GetAtVector().NormalizeSafe();
	up		= GetUpVector();
	up		= (up + (-(up* at) * at)).NormalizeSafe();
	right	= up ^ at;
	
	SetAtVector		(at);
	SetUpVector		(up);
	SetRightVector	(right);
};

void zMAT3::MakeOrthonormal () {
	//void Gram_Schmidt_Process( point *a, point *b, point *c ) {
	zVEC3 at,up,right;
	at		= GetAtVector().NormalizeSafe(); 
	up		= GetUpVector();
	up		= (up + (-(up* at) * at)).NormalizeSafe();
	right	= up ^ at;
	
	SetAtVector		(at);
	SetUpVector		(up);
	SetRightVector	(right);
};

/*--------------------------------------------------------------------------
    zMAT4::PostRotateX()

    19-Sep-00       [Michael]
                      Benutzung von zSinCos
--------------------------------------------------------------------------*/ 
void zMAT4::PostRotateX (const zREAL angleDeg) {
	// aus: Gems1, matrixpo.c 
	/*  	M4RotateX - Post-concatenate a x-axis rotation matrix.  */
	zREAL t;
	zREAL c,s;
	const zREAL angleRad	= Alg_Deg2Rad (-angleDeg);
	
	zSinCos(angleRad,s,c);
	
	for (int i = 0 ; i < 4 ; i++) {
		t		= v[i][1];
		v[i][1] = t*c - v[i][2]*s;
		v[i][2] = t*s + v[i][2]*c;
	}
};


/*--------------------------------------------------------------------------
    zMAT4::PostRotateY()

    19-Sep-00       [Michael]
                      Benutzung von zSinCos
--------------------------------------------------------------------------*/ 
void zMAT4::PostRotateY (const zREAL angleDeg) {
	// aus: Gems1, matrixpo.c 
	// M4RotateY - Post-concatenate a y-axis rotation matrix. 
	zREAL t;
	zREAL c,s;
	const zREAL angleRad  = Alg_Deg2Rad (-angleDeg);

	zSinCos(angleRad,s,c);
	
	for (int i = 0 ; i < 4 ; i++) {
		t		= v[i][0];
		v[i][0] = t*c + v[i][2]*s;
		v[i][2] = v[i][2]*c - t*s;
	}
};

/*--------------------------------------------------------------------------
    zMAT4::PostRotateZ()

    19-Sep-00       [Michael]
                      Benutzung von zSinCos
--------------------------------------------------------------------------*/ 
void zMAT4::PostRotateZ (const zREAL angleDeg) {
	// aus: Gems1, matrixpo.c 
	/*   	M4RotateZ - Post-concatenate a z-axis rotation matrix.   */
	zREAL t;
	zREAL c,s;
	const zREAL angleRad  = Alg_Deg2Rad (-angleDeg);
	
	zSinCos(angleRad,s,c);

	for (int i = 0 ; i < 4 ; i++) {
		t		= v[i][0];
		v[i][0] = t*c - v[i][1]*s;
		v[i][1] = t*s + v[i][1]*c;
	}
};

void zMAT4::PostScale (const zVEC3& scale) {
	v[0][0] *= scale.n[0];
	v[1][1] *= scale.n[1];
	v[2][2] *= scale.n[2];
};

void zMAT4::PreScale (const zVEC3& scale) {

/*	v[0][0]	*= scale.n[0];
	v[0][1]	*= scale.n[0];
	v[0][2]	*= scale.n[0];
	v[1][0]	*= scale.n[1];
	v[1][1]	*= scale.n[1];
	v[1][2]	*= scale.n[1];
	v[2][0]	*= scale.n[2];
	v[2][1]	*= scale.n[2];
	v[2][2]	*= scale.n[2];*/
	v[0][0]	*= scale.n[0];
	v[1][0]	*= scale.n[0];
	v[2][0]	*= scale.n[0];
	v[0][1]	*= scale.n[1];
	v[1][1]	*= scale.n[1];
	v[2][1]	*= scale.n[1];
	v[0][2]	*= scale.n[2];
	v[1][2]	*= scale.n[2];
	v[2][2]	*= scale.n[2];
//	*this = *this * Alg_Scaling3D(scale);
	// this = a, scale = b
/*	#define ROWCOL(i, j) a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + a.v[i].n[2]*b.v[2][j] + a.v[i].n[3]*b.v[3][j]
    return zMAT4(
    zVEC4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3)),
    zVEC4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3)),
    zVEC4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3)),
    zVEC4(ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL(3,3))
    );
	#undef ROWCOL
*/
}; 


/****************************************************************
*																*
*	       2D functions and 3D functions						*
*																*
****************************************************************/

// 2D

zMAT3 Alg_Identity2D()
{   return zMAT3(zVEC3(1.0, 0.0, 0.0),
		zVEC3(0.0, 1.0, 0.0),
		zVEC3(0.0, 0.0, 1.0)); }

zMAT3 Alg_Translation2D(zVEC2& v)
{   return zMAT3(zVEC3(1.0, 0.0, v[VX]),
		zVEC3(0.0, 1.0, v[VY]),
		zVEC3(0.0, 0.0, 1.0)); }
/*--------------------------------------------------------------------------
    zMAT3::Alg_Rotation2D()

    19-Sep-00       [Michael]
                      Benutzung von zSinCos
--------------------------------------------------------------------------*/ 
zMAT3 Alg_Rotation2D(zVEC2& Center, const zREAL angleDeg) {
    const zREAL  angleRad = angleDeg * M_PI / 180.0;
	zREAL  c,s;

	zSinCos(angleRad,s,c);
	
    return zMAT3(zVEC3(c, -s, Center[VX] * (1.0-c) + Center[VY] * s),
		zVEC3(s, c, Center[VY] * (1.0-c) - Center[VX] * s),
		zVEC3(0.0, 0.0, 1.0));
}

zMAT3 Alg_Scaling2D(zVEC2& scaleVector)
{   return zMAT3(zVEC3(scaleVector[VX], 0.0, 0.0),
		zVEC3(0.0, scaleVector[VY], 0.0),
		zVEC3(0.0, 0.0, 1.0)); }

//3D

zMAT4 Alg_Identity3D()
{   return zMAT4(zVEC4(1.0, 0.0, 0.0, 0.0),
		zVEC4(0.0, 1.0, 0.0, 0.0),
		zVEC4(0.0, 0.0, 1.0, 0.0),
		zVEC4(0.0, 0.0, 0.0, 1.0)); }

zMAT4 Alg_Translation3D(const zVEC3& v)
{   return zMAT4(zVEC4(1.0, 0.0, 0.0, v[VX]),
		zVEC4(0.0, 1.0, 0.0, v[VY]),
		zVEC4(0.0, 0.0, 1.0, v[VZ]),
		zVEC4(0.0, 0.0, 0.0, 1.0)); }

zMAT4 Alg_Rotation3D(const zVEC3& Axis, const zREAL angleDeg) {
    zVEC3 axisCopy = Axis;
	axisCopy.Normalize();
	return Alg_Rotation3DNRad (axisCopy, Alg_Deg2Rad(angleDeg));
}

zMAT4 Alg_Rotation3DN (const zVEC3& Axis, const zREAL angleDeg) {
	return Alg_Rotation3DNRad (Axis, Alg_Deg2Rad(angleDeg));
};

zMAT4 Alg_Rotation3DRad (const zVEC3& Axis, const zREAL angleRad) {
    zVEC3 axisCopy = Axis;
	axisCopy.Normalize();
	return Alg_Rotation3DNRad (axisCopy, angleRad);
};

/*--------------------------------------------------------------------------
    zMAT4::Alg_Rotation3DNRad()

    19-Sep-00       [Michael]
                      Benutzung von zSinCos
--------------------------------------------------------------------------*/ 
zMAT4 Alg_Rotation3DNRad (const zVEC3& Axis, const zREAL angleRad) { 
    zREAL t,c,s;

	zSinCos(angleRad,s,c);
	t = 1.0 - c;

    return zMAT4(zVEC4(t * Axis[VX] * Axis[VX] + c,
		     t * Axis[VX] * Axis[VY] - s * Axis[VZ],
		     t * Axis[VX] * Axis[VZ] + s * Axis[VY],
		     0.0),
		zVEC4(t * Axis[VX] * Axis[VY] + s * Axis[VZ],
		     t * Axis[VY] * Axis[VY] + c,
		     t * Axis[VY] * Axis[VZ] - s * Axis[VX],
		     0.0),
		zVEC4(t * Axis[VX] * Axis[VZ] - s * Axis[VY],
		     t * Axis[VY] * Axis[VZ] + s * Axis[VX],
		     t * Axis[VZ] * Axis[VZ] + c,
		     0.0),
		zVEC4(0.0, 0.0, 0.0, 1.0));
}

/*
zMAT4 Alg_RotationY3D (const zREAL angleDeg) {
	const zREAL	FAK = float(M_PI * ((1.0) / 180.0));
    zREAL	angleRad= angleDeg * FAK,
			c		= zCos(angleRad),
			s		= zSin(angleRad),
			t		= 1.0 - c;

    return zMAT4(zVEC4(t * Axis[VX] * Axis[VX] + c,
		     t * Axis[VX] * Axis[VY] - s * Axis[VZ],
		     t * Axis[VX] * Axis[VZ] + s * Axis[VY],
		     0.0),
		zVEC4(t * Axis[VX] * Axis[VY] + s * Axis[VZ],
		     t * Axis[VY] * Axis[VY] + c,
		     t * Axis[VY] * Axis[VZ] - s * Axis[VX],
		     0.0),
		zVEC4(t * Axis[VX] * Axis[VZ] - s * Axis[VY],
		     t * Axis[VY] * Axis[VZ] + s * Axis[VX],
		     t * Axis[VZ] * Axis[VZ] + c,
		     0.0),
		zVEC4(0.0, 0.0, 0.0, 1.0));
}*/

zMAT4 Alg_Scaling3D(const zVEC3& scaleVector)
{   return zMAT4(zVEC4(scaleVector[VX], 0.0, 0.0, 0.0),
				 zVEC4(0.0, scaleVector[VY], 0.0, 0.0),
				 zVEC4(0.0, 0.0, scaleVector[VZ], 0.0),
				 zVEC4(0.0, 0.0, 0.0, 1.0)); }

zMAT4 Alg_Perspective3D(const zREAL d)
{   return zMAT4(zVEC4(1.0, 0.0, 0.0, 0.0),
				 zVEC4(0.0, 1.0, 0.0, 0.0),
				 zVEC4(0.0, 0.0, 1.0, 0.0),
				 zVEC4(0.0, 0.0, 1.0/d, 0.0)); }

void Alg_ClipAtZ0 (zVEC3& p1, zVEC3& p2) {
//	0 = z1 + t*(z2-z1);
	if ((p1[VZ]>=0) && (p2[VZ]>=0))	return;
	if ((p1[VZ]<=0) && (p2[VZ]<=0))	return;
	 
	zVEC3	p;
	zREAL	t;
	zVEC3	d = p2-p1;

	if (d[VZ]==0)					return;

	t		= -p1[VZ] / d[VZ];
//	if (t<0) return;

//	p[VX]	= ((p1[VZ] * d[VX]) / d[VZ]) - p1[VX];
//	p[VY]	= ((p1[VZ] * d[VY]) / d[VZ]) - p1[VY];
//	p[VX]	= -(p1[VX] + t*d[VX]);
//	p[VY]	= -(p1[VY] + t*d[VY]);
	p[VX]	= p1[VX] + t*d[VX];
	p[VY]	= p1[VY] + t*d[VY];
	p[VZ]	= 10.0F;

	if (p1[VZ]<0)	p1=p;
	else			p2=p;
};



/*
    { Sind Start- und Endpunkt hinter Betrachter ? => Exit }
    IF NOT drin [von] AND NOT drin [nach] THEN EXIT;
{    Printxy (30,(von*7), 'X');Line (0,180,319,180,32);}
    { Ist ein von zwei Punkten hinter Betrachter ? => 3D-Clipping }
    IF NOT drin [von] OR NOT  drin [nach] THEN BEGIN
{      Printxy (40,(von*7), 'c');}
      IF drin [von] THEN BEGIN
        n1:= von;  n2:= nach;
      END ELSE BEGIN
        n1:= nach; n2:= von;
      END;
      { 3D-Clipping der Kante an der X-Achse }
      v1 := poly.f [n1];
      v2 := poly.f [n2];
      xc := fixDiv ( fixMul (v1.z , v2.x - v1.x) , (v2.z- v1.z) ) - v1.x;
      yc := fixDiv ( fixMul (v1.z , v2.y - v1.y) , (v2.z- v1.z) ) - v1.y;
{      xc := (FLONG(v1.z).h * (FLONG(v2.x).h - FLONG(v1.x).h) DIV (FLONG(v2.z).h - FLONG(v1.z).h) - FLONG(v1.x).h);
       yc := (FLONG(v1.z).h * (FLONG(v2.y).h - FLONG(v1.y).h) DIV (FLONG(v2.z).h - FLONG(v1.z).h) - FLONG(v1.y).h);}
      { Projektion der geclippten Kante (z=-1) }
      ProjectL ( xc , yc , -1);
      xs [n2] := xp;
      ys [n2] := yp;
{      xs [n2] := ( (xc) * WINSCALE ) + WINXDIV2;
      ys [n2] := ( (yc) * WINSCALE ) + WINYDIV2;}
      IF ys[n2] >maxY THEN maxY:= yp;  {ys[n2];}
{     WITH poly.f [n1] DOLine (-poly.f [n1].y + 160, poly.f [n1].z + 180,Round(yc )           + 160,180, 45);}

*/

/****************************************************************
*																*
*	       Quaternions											*
*																*
****************************************************************/

/*
	Dieser Teil ist NICHT aus den Graphic Gems.
*/

/*
 Quaternion Quellen:

  - QSlim
  - Gems I
  - News
  - Clax
  - Magic-Src (Eberly)
  - V-Collide
  - GDMag Source-Code (Lander?)
*/

/*
Unreal
	UBOOL Normalize()
	{
		// 
		FLOAT SquareSum = (FLOAT)(X*X+Y*Y+Z*Z+W*W);
		if( SquareSum >= DELTA )
		{
			FLOAT Scale = 1.0f/(FLOAT)appSqrt(SquareSum);
			X *= Scale; 
			Y *= Scale; 
			Z *= Scale;
			W *= Scale;
			return true;
		}
		else 
		{	
			X = 0.0f;
			Y = 0.0f;
			Z = 0.1f;
			W = 0.0f;
			return false;
		}
	}
// Ensure quat1 points to same side of the hypersphere as quat2
inline void AlignFQuatWith(FQuat &quat1, const FQuat &quat2)
{
	FLOAT Minus  = Square(quat1.X-quat2.X) + Square(quat1.Y-quat2.Y) + Square(quat1.Z-quat2.Z) + Square(quat1.W-quat2.W);
	FLOAT Plus   = Square(quat1.X+quat2.X) + Square(quat1.Y+quat2.Y) + Square(quat1.Z+quat2.Z) + Square(quat1.W+quat2.W);

	if (Minus > Plus)
	{
		quat1.X = - quat1.X;
		quat1.Y = - quat1.Y;
		quat1.Z = - quat1.Z;
		quat1.W = - quat1.W;
	}
}
// No-frills spherical interpolation. Assumes aligned quaternions, and the output is not normalized.
inline FQuat SlerpQuat(const FQuat &quat1,const FQuat &quat2, float slerp)
{
	FQuat result;
	float omega,cosom,sininv,scale0,scale1;

	// Get cosine of angle betweel quats.
	cosom = quat1.X * quat2.X +
			quat1.Y * quat2.Y +
			quat1.Z * quat2.Z +
			quat1.W * quat2.W;

	if( cosom < 0.99999999f )
	{	
		omega = appAcos(cosom);
		sininv = 1.f/appSin(omega);
		scale0 = appSin((1.f - slerp) * omega) * sininv;
		scale1 = appSin(slerp * omega) * sininv;
		
		result.X = scale0 * quat1.X + scale1 * quat2.X;
		result.Y = scale0 * quat1.Y + scale1 * quat2.Y;
		result.Z = scale0 * quat1.Z + scale1 * quat2.Z;
		result.W = scale0 * quat1.W + scale1 * quat2.W;
		return result;
	}
	else
	{
		return quat1;
	}
	
}
*/

void zCQuat::Unit () { 
	const zREAL len = zREAL(1) / sqrt(qx*qx+qy*qy+qz*qz+qw*qw); 
	qx*=len; qy*=len; qz*=len; qw*=len; 
};

// FIXME: Rechenzeitfresser!
void zCQuat::QuatToMatrix4 (zMAT4& mat) const 
{
	mat[0][0] = qw*qw + qx*qx - qy*qy - qz*qz;
	mat[0][1] = 2.0*(qx*qy + qw*qz);
	mat[0][2] = 2.0*(qx*qz - qw*qy);

	mat[1][0] = 2.0*(qx*qy - qw*qz);
	mat[1][1] = qw*qw - qx*qx + qy*qy - qz*qz;
	mat[1][2] = 2.0*(qy*qz + qw*qx);			//yz+wz
//	mat[1][2] = 2.0*(qy*qz + qw*qz);			//yz+wz

	mat[2][0] = 2.0*(qx*qz + qw*qy);
	mat[2][1] = 2.0*(qy*qz - qw*qx);			//yz-wz
//	mat[2][1] = 2.0*(qy*qz - qw*qz);			//yz-wz
	mat[2][2] = qw*qw - qx*qx - qy*qy + qz*qz;
};
/*
void zCQuat::Matrix4ToQuat (const zMAT4& mat) {
	const zREAL epsilon = 1e-06F;

	zREAL trace = mat[0][0]+mat[1][1]+mat[2][2];
	zREAL angle = acos(0.5*(trace-1.0f));

	qx = mat[1][2]-mat[2][1];
	qy = mat[2][0]-mat[0][2];
	qz = mat[0][1]-mat[1][0];
	zREAL length = sqrt(qx*qx + qy*qy + qz*qz);
	if ( length >= epsilon ) {
		zREAL lengthInv = zREAL(1) / length;
		qx *= lengthInv;
		qy *= lengthInv;
		qz *= lengthInv;

		zREAL halfAngle = 0.5*angle;
		zREAL cs = zCos(halfAngle);
		zREAL sn = zSin(halfAngle);
		qw  = cs;
		qx *= sn;
		qy *= sn;
		qz *= sn;
	} else {
		qw = 1.0;
		qx = 0.0;
		qy = 0.0;
		qz = 0.0;
	};
};
*/

void zCQuat::QuatToMatrix3	(zMAT3& mat) const 
{
	mat[0][0] = qw*qw + qx*qx - qy*qy - qz*qz;
	mat[0][1] = 2.0*(qx*qy + qw*qz);
	mat[0][2] = 2.0*(qx*qz - qw*qy);

	mat[1][0] = 2.0*(qx*qy - qw*qz);
	mat[1][1] = qw*qw - qx*qx + qy*qy - qz*qz;
	mat[1][2] = 2.0*(qy*qz + qw*qx);			

	mat[2][0] = 2.0*(qx*qz + qw*qy);
	mat[2][1] = 2.0*(qy*qz - qw*qx);			
	mat[2][2] = qw*qw - qx*qx - qy*qy + qz*qz;
};

void zCQuat::Matrix4ToQuat (const zMAT4& mat) 
{
	// Source: Bobic, GDM feb98
	zREAL	tr, s;
	zREAL	q[4];
	int		i, j, k;
	
	int nxt[3] = {1, 2, 0};
	tr = mat[0][0] + mat[1][1] + mat[2][2];

	// check the diagonal
	if (tr > 0.0) {
		s = sqrt (tr + 1.0);
		qw = s * 0.5;
		s = 0.5 / s;
		qx = (mat[1][2] - mat[2][1]) * s;
		qy = (mat[2][0] - mat[0][2]) * s;
		qz = (mat[0][1] - mat[1][0]) * s;
	} else {		
		// diagonal is negative
		i = 0;
		if (mat[1][1] > mat[0][0]) i = 1;
		if (mat[2][2] > mat[i][i]) i = 2;
		j	= nxt[i];
		k	= nxt[j];
		s	= sqrt ((mat[i][i] - (mat[j][j] + mat[k][k])) + 1.0); 
		q[i]= s * 0.5;
		if (s != 0.0) s = 0.5 / s;
		q[3] = (mat[j][k] - mat[k][j]) * s;
		q[j] = (mat[i][j] + mat[j][i]) * s;
		q[k] = (mat[i][k] + mat[k][i]) * s;
		
		qx = q[0];
		qy = q[1];
		qz = q[2];
		qw = q[3];
	}
}

void zCQuat::Matrix3ToQuat (const zMAT3& mat) 
{
	// Source: Bobic, GDM feb98
	zREAL	tr, s;
	zREAL	q[4];
	int		i, j, k;
	
	int nxt[3] = {1, 2, 0};
	tr = mat[0][0] + mat[1][1] + mat[2][2];

	// check the diagonal
	if (tr > 0.0) {
		s = sqrt (tr + 1.0);
		qw = s * 0.5;
		s = 0.5 / s;
		qx = (mat[1][2] - mat[2][1]) * s;
		qy = (mat[2][0] - mat[0][2]) * s;
		qz = (mat[0][1] - mat[1][0]) * s;
	} else {		
		// diagonal is negative
		i = 0;
		if (mat[1][1] > mat[0][0]) i = 1;
		if (mat[2][2] > mat[i][i]) i = 2;
		j	= nxt[i];
		k	= nxt[j];
		s	= sqrt ((mat[i][i] - (mat[j][j] + mat[k][k])) + 1.0); 
		q[i]= s * 0.5;
		if (s != 0.0) s = 0.5 / s;
		q[3] = (mat[j][k] - mat[k][j]) * s;
		q[j] = (mat[i][j] + mat[j][i]) * s;
		q[k] = (mat[i][k] + mat[k][i]) * s;
		
		qx = q[0];
		qy = q[1];
		qz = q[2];
		qw = q[3];
	}
}

void zCQuat::QuatToEuler (zVEC3& euler) const 
{
	// src: news.quaternions.txt
//	const zREAL EPSILON = (1.0e-05F);
	const zREAL EPSILON = 0.00001F;
		
	zREAL	sin_theta;      // sin of pitch
	zREAL	R00, R01, R02;  // rotation matrix elements
	zREAL		 R11, R12;
	zREAL		 R21, R22;  
	
	R02			= 2.0*(qx*qz - qw*qy);
	sin_theta	= -R02;
	
	if (zAbs(sin_theta) > (1.0 - EPSILON))
    {
		// very close to +- 90 degrees pitch, set heading to zero
		// and compute the roll angle
		euler[2] = 0.0;
		if (sin_theta > 0)	euler[1] = zREAL( M_PI/2.0);
		else				euler[1] = zREAL(-M_PI/2.0);
		R11			= 2.0*(qw*qw + qy*qy) - 1.0;
		R21			= 2.0*(qy*qz - qw*qx);
		euler[0]	= atan2(-R21, R11);
    }
	else
    {
		R00			= 2.0*(qw*qw + qx*qx) - 1.0;
		R01			= 2.0*(qx*qy + qw*qz);
		R12			= 2.0*(qy*qz + qw*qx);
		R22			= 2.0*(qw*qw + qz*qz) - 1.0;
		
		euler[0]	= atan2(R12, R22);		// roll
		euler[1]	= asin (sin_theta);		// pitch
		euler[2]	= atan2(R01, R00);		// heading
    }
};


/*
	(oben benutzt)
- roll	: x-Achse
- pitch	: y-Achse
- yaw	: z-Achse

  matrix-faq:
- pitch	: x-Achse
- yaw	: y-Achse
- roll	: z-Achse

*/
/*--------------------------------------------------------------------------
    zCQuat::EulerToQuat()

    19-Sep-00       [Michael]
                      Benutzung von zSinCos
--------------------------------------------------------------------------*/ 

void zCQuat::EulerToQuat (const zVEC3& euler) 
{
	zREAL cr, cp, cy, sr, sp, sy, cpcy, spsy;
	
	zSinCos(0.5f*euler[VX], sr, cr);  // roll
	zSinCos(0.5f*euler[VY], sp, cp);  // pitch
	zSinCos(0.5f*euler[VZ], sy, cy);  // yaw

	cpcy = cp * cy;
	spsy = sp * sy;
	
	qw = cr * cpcy    + sr * spsy;
	qx = sr * cpcy    - cr * spsy;
	qy = cr * sp * cy + sr * cp * sy;
	qz = cr * cp * sy - sr * sp * cy;
};

void zCQuat::QuatToAxisAngle (zVEC3& axis, zREAL& angle) const 
{
	const zREAL EPSILON = 1e-06F;
    zREAL len = qx*qx + qy*qy + qz*qz;
	
    if (len > EPSILON) {
		zREAL lenInv = 1.0f/len;
		
		axis[VX]= qx * (1.0f * lenInv);
		axis[VY]= qy * (1.0f * lenInv);
		axis[VZ]= qz * (1.0f * lenInv);
		angle	= (zREAL)(2.0 * acos(qw));
    } else {
		axis[VX]= 0.0;
		axis[VY]= 0.0;
		axis[VZ]= 1.0;
		angle	= 0.0;
    }
/*	zREAL halfAngle = zREAL(acos (qw));
	if (halfAngle>0.00001F)
	{
		zREAL oneOverSinAngle = 1.0f / (zREAL)zSin( halfAngle );
		axis[VX]		= qx * oneOverSinAngle;
		axis[VY]		= qy * oneOverSinAngle;
		axis[VZ]		= qz * oneOverSinAngle;
		angle			= 2.0f * halfAngle;
    } else {
		axis[VX]= 0.0;
		axis[VY]= 0.0;
		axis[VZ]= 1.0;
		angle	= 0.0;
    }
*/
};

/*
void zCQuat::Slerp (const zREAL t, const zCQuat& p, const zCQuat& q) {
    // assert:  Dot(p,q) >= 0 (obtained by preprocessing input)
	const zREAL EPSILON = 1e-06F;

    zREAL cs = p.Dot(q);
    zREAL sn = sqrt(fabs(1-cs*cs));
    if ( fabs(sn) < EPSILON ) { *this = p; return; };

    int notFlipped = 1;
    if ( cs < 0.0 ) {
        cs = -cs;
        notFlipped = 0;
    }

    zREAL angle = atan2(sn,cs);
    zREAL invSn = 1.0/sn;
    zREAL c0	= zSin((1-t)*angle)*invSn;
    zREAL c1	= zSin(t*angle)*invSn;

    if (notFlipped) { *this = c0*p + c1*q; } 
	else			{ *this = c0*p - c1*q; };
}
*/

#if 1
void zCQuat::Slerp (const zREAL t, const zCQuat& p, const zCQuat& q) 
{
	// Quelle: Eberly
    // assert:  p.Dot(q) >= 0 (guaranteed in NiRotKey::Interpolate methods)
    zREAL dCos = p.Dot(q);

	int notFlipped = 1;
	if (dCos<0) {
		dCos		= -dCos;
		notFlipped	= 0;
		if (dCos<-1.0F)	dCos = -1.0F;
	} else {
		if (dCos>+1.0F)	dCos = +1.0F;
	};

    // numerical round-off error could create problems in call to acos
    const zREAL dAngle= acos(dCos);
    const zREAL dSin	= zSin(dAngle);  // fSin >= 0 since fCos >= 0

    if (dSin<1e-03) {
        *this=p;
    } else
	{
        const zREAL dInvSin = 1.0f/dSin;
        const zREAL dCoeff0 = zSin((1.0-t)*dAngle)*dInvSin;
        const zREAL dCoeff1 = zSin(t*dAngle)*dInvSin;

//		*this= dCoeff0*p + dCoeff1*q;

		if (notFlipped) { *this = dCoeff0*p + dCoeff1*q; } 
		else			{ *this = dCoeff0*p - dCoeff1*q; };
    }
};

#else

void zCQuat::Slerp (const zREAL t, const zCQuat& q0, const zCQuat& q1) 
{
	// Quelle: Genesis
//void geQuaternion_SlerpNotShortest(

	// spherical interpolation between q0 and q1.   0<=t<=1 
	// resulting quaternion is 'between' q0 and q1
	// with t==0 being all q0, and t==1 being all q1.
	zREAL omega,cosom,sinom,Scale0,Scale1;

	const zREAL EPSILON = (0.00001F);

    cosom = q0.Dot(q1);
	if ( (1.0f + cosom) > EPSILON )
	{
		if ( (1.0f - cosom) > EPSILON )
		{
			omega  = (zREAL) acos( cosom );
			sinom  = (zREAL) zSin( omega );
			// has numerical difficulties around cosom == nPI/2
			// in this case everything is up for grabs... 
			//  ...degenerate to linear interpolation
			if (sinom < EPSILON)
			{
				Scale0 = 1.0f - t;
				Scale1 = t;	
			}
			else
			{
				Scale0 = (zREAL) zSin( (1.0f-t) * omega) / sinom;
				Scale1 = (zREAL) zSin( t*omega) / sinom;
			}
		}
		else
		{
			// has numerical difficulties around cosom == 0
			// in this case degenerate to linear interpolation
			Scale0 = 1.0f - t;
			Scale1 = t;
		}
		*this = Scale0 * q0 + Scale1*q1;
		// Unit, normalize
	}
	else
	{
		const zREAL QUATERNION_PI = ((zREAL)3.14159265358979323846f);
		this->qx= -q0.qy; 
		this->qy=  q0.qx;
		this->qz= -q0.qw;
		this->qw=  q0.qz;
		Scale0	= (zREAL) zSin( (1.0f - t) * (QUATERNION_PI*0.5) );
		Scale1	= (zREAL) zSin( t * (QUATERNION_PI*0.5) );
		*this	= Scale0 * q0 + Scale1*q1;
	}
};
#endif

void zCQuat::Lerp (const zREAL t, const zCQuat& p, const zCQuat& q) {
	// Source: Bobic, GDM feb98
	// Action: Linearly interpolates between two quaternion positions
	//		   fast but not as nearly as smooth as Slerp
/*	zREAL to1[4];
	zREAL cosom;
	zREAL scale0, scale1;
	
	// calc cosine
	cosom = p.qx * q.qx + p.qy * q.qy + p.qz * q.qz + p.qw * q.qw;
	
	// adjust signs (if necessary)
	if ( cosom < 0.0 ) {
		to1[0] =-q.qx;
		to1[1] =-q.qy;
		to1[2] =-q.qz;
		to1[3] =-q.qw;
	} else  {
		to1[0] = q.qx;
		to1[1] = q.qy;
		to1[2] = q.qz;
		to1[3] = q.qw;
	}
	// interpolate linearly
	scale0 = 1.0 - t;
	scale1 = t;
	
	// calculate final values
	qx = scale0 * p.qx + scale1 * to1[0];
	qy = scale0 * p.qy + scale1 * to1[1];
	qz = scale0 * p.qz + scale1 * to1[2];
	qw = scale0 * p.qw + scale1 * to1[3];*/

    if (p.Dot(q)<0.0)	{ *this = (1.0-t)*p - t*q; } 
	else				{ *this = (1.0-t)*p + t*q; };  
}

// [EDENFELD] 1.09 Slerp Argumente korrigiert 
void zCQuat::Squad (const zREAL t,	const zCQuat& q0, 
									const zCQuat& q1, 
									const zCQuat& q2, 
									const zCQuat& q3) 
{
	zCQuat quat0,quat1;
//	quat0.Slerp (t, q0, q3);
//	quat1.Slerp (t, q1, q2);
//	Slerp (2*t*(1-t), quat0, quat1);
	quat0.Slerp		(t, q0, q3);
	quat0.Normalize	();
	quat0.Unit		();
	quat1.Slerp		(t, q1, q2);
	quat1.Normalize	();
	quat1.Unit		();
	Slerp (2.0F*t*(1-t), quat0, quat1);
};

/*
	- inverse eines Quats ?
	- wann ist ein Quat normalized ?    q^2 = 1 ? Sqrt oder nicht ?
	- wann muss ein Quat normlized sein ?
	- entspr. nur ein normalized Quat einer Rotation ?
*/
/*
// Gary Tarolli's clever inverse square root technique
float fsqrt_inv(float f)
{
	long i;
	float x2, y;

	x2 = 0.5f*f;
	i = *(long *)&f;
	i = 0x5f3759df - (i>>1);
	y = *(float *)&i;

	// repeat this iteration for more accuracy
	y = 1.5f*y - (x2*y * y*y);

	return y;
}
*/
/*
Hack to override default _ftol lib behaviour. did not speed up engine!
#define ANSI_FTOL 1

extern "C" 
{ 
    __declspec(naked) void _ftol() {
        __asm    {
#if ANSI_FTOL
            fnstcw   WORD PTR [esp-2]
            mov      ax, WORD PTR [esp-2]
			
            OR AX,	 0C00h
			
            mov      WORD PTR [esp-4], ax
            fldcw    WORD PTR [esp-4]
            fistp    QWORD PTR [esp-12]
            fldcw    WORD PTR [esp-2]
            mov      eax, DWORD PTR [esp-12]
            mov      edx, DWORD PTR [esp-8]
#else
            fistp    DWORD PTR [esp-12]
            mov		 eax, DWORD PTR [esp-12]
            mov		 ecx, DWORD PTR [esp-8]
#endif
            ret
        }
    }
}
*/

const static zREAL averageFrameTime = .025F; // 40 fps


zCValueSmooth::zCValueSmooth()
{
	fixedValue		= 0;
	smoothedValue	= 0;
	inertia			= 2;
	bSmooth			= TRUE;
};


void zCValueSmooth::Smooth(float& v)
{
	fixedValue = v;
	if (!bSmooth) return;

    zREAL dist2 = (v - smoothedValue);
	dist2 *= dist2;

    zREAL frac = ztimer.GetFrameTimeFSecs() / (inertia * averageFrameTime);
    frac      *= (1 + 4 * dist2) / (1 + dist2);

    smoothedValue += v * frac;
    smoothedValue /= (1 + frac);
	v   = smoothedValue;
}


zCVEC3Smooth::zCVEC3Smooth()
{
	fixedValue		= 0;
	smoothedValue	= 0;
	inertia			= 2;
	bSmooth			= TRUE;
};

void zCVEC3Smooth::Smooth(zVEC3& v)
{
	fixedValue = v;
	if (!bSmooth) return;

    zREAL dist2 = (v - smoothedValue).Length2();

    zREAL frac = ztimer.GetFrameTimeFSecs() / (inertia * averageFrameTime);
    frac      *= (1 + 4 * dist2) / (1 + dist2);

    smoothedValue += v * frac;
    smoothedValue /= (1 + frac);
	v   = smoothedValue;
}




// enable VC++ Warning: double to float conversion
#pragma warning( default : 4244 )

//#pragma optimize( "", on)
