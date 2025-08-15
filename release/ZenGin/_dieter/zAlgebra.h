/******************************************************************************** 
 
     $Workfile:: zAlgebra.h           $                $Date:: 22.01.01 20:01   $
     $Revision:: 20                   $             $Modtime:: 22.01.01 13:46   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Vector and Matrix Algebra routines (floating point)
   created       : 19.11.96

 * $Log: /current_work/ZenGin/_Dieter/zAlgebra.h $
 * 
 * 20    22.01.01 20:01 Moos
 * 
 * 19    17.01.01 0:22 Hildebrandt
 * 
 * 18    4.12.00 17:18 Hildebrandt
 * 
 * 17    19.10.00 19:26 Hildebrandt
 * 
 * 16    4.10.00 16:38 Hildebrandt
 * 
 * 15    21.09.00 3:50 Rueve
 * 
 * 14    21.09.00 3:42 Rueve
 * 
 * 13    18.09.00 12:11 Rueve
 * Opt.
 * 
 * 12    21.08.00 17:18 Hildebrandt
 * 
 * 11    15.08.00 16:50 Hildebrandt
 * Alg_IsColinear() fix #2
 * 
 * 10    15.08.00 16:18 Hildebrandt
 * fixed potential div0 exception in Alg_IsColinear()
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 9     6.07.00 13:33 Hildebrandt
 * 
 * 5     9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 6     15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 4     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 20 $ ($Modtime: 22.01.01 13:46 $)

// =======================================================================================================================

#ifndef __ZALGEBRA_H__
#define __ZALGEBRA_H__

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#ifndef __ZCORE_H__
#include <zCore.h>
#endif

#ifndef __ZTRIGO_H__
#include <zTrigo.h>
#endif

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

// =======================================================================================================================

// this line defines a new type: pointer to a function which returns a
// zREAL and takes as argument a zREAL 
typedef zREAL (*V_FCT_PTR)(zREAL);

enum {VX, VY, VZ, VW};		    // axes
enum {VA, VB, VC, VD};          // coefficients for plane equotation
enum {PA, PB, PC, PD};		    // planes
enum {RED, GREEN, BLUE};	    // colors
enum {KA, KD, KS, ES};		    // phong coefficients

const zREAL zALG_EQUAL_EPSILON = zREAL (0.001);

// forward declarations
class zVEC2;
class zVEC3;
class zVEC4;
class zMAT3;
class zMAT4;

inline float Alg_SqrtInvApprox	(const float f);
inline float Alg_SqrtApprox		(const float f)	{ return f? f * Alg_SqrtInvApprox(f) : 0; };


/****************************************************************
*																*
*			    2D Vector										*
*																*
****************************************************************/

class zVEC2
{
public:

	zREAL n[2];

	// Constructors

	inline zVEC2() {};
	inline zVEC2(const zREAL x, const zREAL y);
	inline zVEC2(const zREAL d);
	inline zVEC2(const zVEC2& v);											// copy constructor
		   zVEC2(const zVEC3& v);											// cast v3 to v2
		   zVEC2(const zVEC3& v, int dropAxis);							// cast v3 to v2

	// Assignment operators

//	zVEC2& operator	= ( const zVEC2& v );							// assignment of a zVEC2
	zVEC2& operator += ( const zVEC2& v );							// incrementation by a zVEC2
	zVEC2& operator -= ( const zVEC2& v );							// decrementation by a zVEC2
	zVEC2& operator *= ( const zREAL d );							// multiplication by a constant
	zVEC2& operator /= ( const zREAL d );							// division by a constant
	zREAL& operator [] ( const int i)		{ return n[i]; };		// indexing
	zREAL  operator [] ( const int i) const { return n[i]; };		// read-only indexing

	// special functions

	zREAL  Length				();									// Length of a zVEC2
	zREAL  Length2				();									// squared Length of a zVEC2
	zVEC2& Normalize			();									// Normalize a zVEC2
	zVEC2& NormalizeApprox		();									// Normalize a zVEC3
	zVEC2& Apply				(V_FCT_PTR fct);					// Apply a func. to each component

	zBOOL IsEqualEps (const zVEC2& b) const {								// fuzzy compare with small epsilon
		return ((zAbs(zREAL(n[0]-b.n[0])) < zALG_EQUAL_EPSILON) &&
				(zAbs(zREAL(n[1]-b.n[1])) < zALG_EQUAL_EPSILON));
	};

	zSTRING GetDescription		() const;
	void	SetByDescription	(const zSTRING& desc);

	// friends

	friend zVEC2 operator - (const zVEC2& v);						// -v1
	friend zVEC2 operator + (const zVEC2& a, const zVEC2& b);	    // v1 + v2
	friend zVEC2 operator - (const zVEC2& a, const zVEC2& b);	    // v1 - v2
	friend zVEC2 operator * (const zVEC2& a, const zREAL d);	    // v1 * 3.0
	friend zVEC2 operator * (const zREAL d, const zVEC2& a);	    // 3.0 * v1
	friend zVEC2 operator * (const zMAT3& a, const zVEC2& v);	    // M . v
	friend zVEC2 operator * (const zVEC2& v, zMAT3& a);				// v . M
	friend zREAL operator * (const zVEC2& a, const zVEC2& b);		// dot product
	friend zVEC2 operator / (const zVEC2& a, const zREAL d);	    // v1 / 3.0
	friend zVEC3 operator ^ (const zVEC2& a, const zVEC2& b);	    // cross product
	friend int operator == (const zVEC2& a, const zVEC2& b);	    // v1 == v2 ?
	friend int operator != (const zVEC2& a, const zVEC2& b);	    // v1 != v2 ?
	friend ostream& operator << (ostream& s, zVEC2& v);			// output to stream
	friend istream& operator >> (istream& s, zVEC2& v);			// input from strm.
	friend void Alg_Swap(zVEC2& a, zVEC2& b);							// swap v1 & v2
	friend zVEC2 Alg_Min(const zVEC2& a, const zVEC2& b);				// min(v1, v2)
	friend zVEC2 Alg_Max(const zVEC2& a, const zVEC2& b);				// max(v1, v2)
	friend zVEC2 Alg_Prod(const zVEC2& a, const zVEC2& b);				// term by term *

	// necessary friend declarations

	friend class zVEC3;
};

// inlines
inline zVEC2::zVEC2(const zREAL x, const zREAL y)
{ n[VX] = x; n[VY] = y; }

inline zVEC2::zVEC2(const zREAL d)
{ n[VX] = n[VY] = d; }

inline zVEC2::zVEC2(const zVEC2& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; }

// Von Dieter hinzugefuegtes:

inline zVEC2& zVEC2::NormalizeApprox () // it is up to caller to avoid divide-by-zero
//{ *this /= Length(); return *this; }
{	
//	zREAL d_inv = zREAL(1.0) / LengthApprox();
	zREAL d_inv = Alg_SqrtInvApprox (n[VX]*n[VX] + n[VY]*n[VY]);
	n[VX] *= d_inv; n[VY] *= d_inv;
	return *this;
};



/****************************************************************
*																*
*			    3D Vector										*
*																*
****************************************************************/

class zVEC3
{
	public:

		zREAL n[3];

	// Constructors

	inline zVEC3() {};
	inline zVEC3(const zREAL x, const zREAL y, const zREAL z)	{ n[VX] = x; n[VY] = y; n[VZ] = z; };
	inline zVEC3(const zREAL d) 								{ n[VX] = n[VY] = n[VZ] = d; }

	inline zVEC3(const zVEC3& v)			{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; };	// copy constructor
	inline zVEC3(const zVEC2& v)			{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = 1.0; };		// cast v2 to v3
	inline zVEC3(const zVEC2& v, zREAL d)	{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = d; };	// cast v2 to v3
	inline zVEC3(const zVEC4& v);												// cast v4 to v3
	inline zVEC3(const zVEC4& v, int dropAxis);									// cast v4 to v3
																			
	// Assignment operators													
																			
//	zVEC3& operator	= ( const zVEC3& v );									// assignment of a zVEC3
	zVEC3& operator += ( const zVEC3& v );									// incrementation by a zVEC3
	zVEC3& operator -= ( const zVEC3& v );									// decrementation by a zVEC3
	zVEC3& operator *= ( const zREAL d );									// multiplication by a constant
	zVEC3& operator /= ( const zREAL d );									// division by a constant
	//zREAL& operator [] ( int i);											// indexing
	zREAL& operator [] ( const int i)		{ return n[i]; };				// indexing
	zREAL  operator [] ( const int i) const { return n[i]; };				// read-only indexing
	// special functions

	zREAL  Length			() const;										// Length of a zVEC3
	zREAL  Length2			() const;										// squared Length of a zVEC3
	zREAL  LengthApprox		() const;
	zVEC3& Normalize		();												// Normalize a zVEC3, caller needs to avoid zero-length vector
	zVEC3& NormalizeSafe	();												// Normalize a zVEC3, is safe against zero-length vector
	zVEC3& NormalizeApprox	();												// Normalize a zVEC3
	zVEC3& Apply			(V_FCT_PTR fct);								// Apply a func. to each component

	zBOOL IsEqualEps (const zVEC3& b) const {								// fuzzy compare with small epsilon
		return ((zAbs(zREAL(n[0]-b.n[0])) < zALG_EQUAL_EPSILON) &&
				(zAbs(zREAL(n[1]-b.n[1])) < zALG_EQUAL_EPSILON) &&
				(zAbs(zREAL(n[2]-b.n[2])) < zALG_EQUAL_EPSILON));
	};
	zVEC3 Abs		() const					{ return zVEC3 (zAbs(n[0]), zAbs(n[1]), zAbs(n[2])); };
	// return Vector = reflected 'this'-Vector against plane with 'normal'
	// assert: this & normal are normalized, this points away from plane, result will also
	zVEC3 Reflect	(const zVEC3& normal) const { return (2 * normal * (normal * (*this)) - (*this)); };
	zSTRING GetString () const { return zSTRING(" ("+zSTRING(n[0])+", "+zSTRING(n[1])+", "+zSTRING(n[2])+") "); };
	// friends
	// zVEC3 operator - ();						// -v1

	friend zVEC3 operator - (const zVEC3& v);							// -v1
	friend zVEC3 operator + (const zVEC3& a, const zVEC3& b);			// v1 + v2
	friend zVEC3 operator - (const zVEC3& a, const zVEC3& b);			// v1 - v2
	friend zVEC3 operator * (const zVEC3& a, const zREAL d);			// v1 * 3.0
	friend zVEC3 operator * (const zREAL d, const zVEC3& a);			// 3.0 * v1
	friend zVEC3 operator * (const zMAT4& a, const zVEC3& v);			// M . v
	friend zVEC3 operator * (const zVEC3& v, const zMAT4& a);			// v . M
	friend zREAL operator * (const zVEC3& a, const zVEC3& b);			// dot product
	friend zVEC3 operator / (const zVEC3& a, const zREAL d);			// v1 / 3.0
	friend zVEC3 operator ^ (const zVEC3& a, const zVEC3& b);			// cross product
	friend int operator == (const zVEC3& a, const zVEC3& b);			// v1 == v2 ?
	friend int operator != (const zVEC3& a, const zVEC3& b);			// v1 != v2 ?
	friend ostream& operator << (ostream& s, zVEC3& v);					// output to stream
	friend istream& operator >> (istream& s, zVEC3& v);					// input from strm.
	friend void Alg_Swap(zVEC3& a, zVEC3& b);							// swap v1 & v2
	friend zVEC3 Alg_Min(const zVEC3& a, const zVEC3& b);				// min(v1, v2)
	friend zVEC3 Alg_Max(const zVEC3& a, const zVEC3& b);				// max(v1, v2)
	friend zVEC3 Alg_Prod(const zVEC3& a, const zVEC3& b);				// term by term *

	// necessary friend declarations

	friend class zVEC2;
	friend class zVEC4;
	friend class zMAT3;
	friend zVEC2 operator * (const zMAT3& a, const zVEC2& v);			// linear transform
	friend zMAT3 operator * (const zMAT3& a, const zMAT3& b);			// matrix 3 product
};


/****************************************************************
*																*
*			    4D Vector										*
*																*
****************************************************************/

class zVEC4
{
public:
	zREAL n[4];

	// Constructors

	inline zVEC4() {};
	inline zVEC4(const zREAL x, const zREAL y, const zREAL z, const zREAL w) { n[VX] = x; n[VY] = y; n[VZ] = z; n[VW] = w; };
	inline zVEC4(const zREAL d)					{  n[VX] = n[VY] = n[VZ] = n[VW] = d; };
	inline zVEC4(const zVEC4& v)				{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; n[VW] = v.n[VW]; };	// copy constructor
	inline zVEC4(const zVEC3& v)				{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; n[VW] = 1.0; };		// cast zVEC3 to zVEC4
	inline zVEC4(const zVEC3& v, const zREAL d) { n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ];  n[VW] = d; };			// cast zVEC3 to zVEC4

	// Assignment operators

//	zVEC4& operator	= ( const zVEC4& v );	    // assignment of a zVEC4
	zVEC4& operator += ( const zVEC4& v );	    // incrementation by a zVEC4
	zVEC4& operator -= ( const zVEC4& v );	    // decrementation by a zVEC4
	zVEC4& operator *= ( const zREAL d );	    // multiplication by a constant
	zVEC4& operator /= ( const zREAL d );	    // division by a constant
	inline zREAL& operator [] (const int i);							// indexing
 	inline zREAL  operator [] (const int i) const	{ return n[i]; };	// read-only indexing

	// special functions

	zREAL  Length();					// Length of a zVEC4
	zREAL  Length2();					// squared Length of a zVEC4
	zREAL  LengthApprox();
	zVEC4& Normalize();					// Normalize a zVEC4
	zVEC4& Apply(V_FCT_PTR fct);		    // Apply a func. to each component

	// friends

	friend zVEC4 operator - (const zVEC4& v);						// -v1
	friend zVEC4 operator + (const zVEC4& a, const zVEC4& b);	    // v1 + v2
	friend zVEC4 operator - (const zVEC4& a, const zVEC4& b);	    // v1 - v2
	friend zVEC4 operator * (const zVEC4& a, const zREAL d);	    // v1 * 3.0
	friend zVEC4 operator * (const zREAL d, const zVEC4& a);	    // 3.0 * v1
	friend zVEC4 operator * (const zMAT4& a, const zVEC4& v);	    // M . v
	friend zVEC4 operator * (const zVEC4& v, zMAT4& a);				// v . M
	friend zREAL operator * (const zVEC4& a, const zVEC4& b);		// dot product
	friend zVEC4 operator / (const zVEC4& a, const zREAL d);	    // v1 / 3.0
	friend int operator == (const zVEC4& a, const zVEC4& b);	    // v1 == v2 ?
	friend int operator != (const zVEC4& a, const zVEC4& b);	    // v1 != v2 ?
	friend ostream& operator << (ostream& s, zVEC4& v);				// output to stream
	friend istream& operator >> (istream& s, zVEC4& v);				// input from strm.
	friend void Alg_Swap(zVEC4& a, zVEC4& b);						// swap v1 & v2
	friend zVEC4 Alg_Min(const zVEC4& a, const zVEC4& b);		    // min(v1, v2)
	friend zVEC4 Alg_Max(const zVEC4& a, const zVEC4& b);		    // max(v1, v2)
	friend zVEC4 Alg_Prod(const zVEC4& a, const zVEC4& b);		    // term by term *

	// necessary friend declarations

	friend class zVEC3;
	friend class zMAT4;
	friend zVEC3 operator * (const zMAT4& a, const zVEC3& v);	    // linear transform
	inline zENGINE_API friend zMAT4 operator * (const zMAT4& a, const zMAT4& b);					// matrix 4 product
};

/****************************************************************
*																*
*			   3x3 Matrix										*
*																*
****************************************************************/

class zMAT3
{
	static zMAT3 s_identity;
public:

	zVEC3 v[3];

	// Constructors

	inline zMAT3() {};
	zMAT3(const zVEC3& v0, const zVEC3& v1, const zVEC3& v2);
	zMAT3(const zREAL d);
	zMAT3(const zMAT3& m);

	// Assignment operators

	zMAT3& operator	= ( const zMAT3& m );							// assignment of a zMAT3
	zMAT3& operator += ( const zMAT3& m );							// incrementation by a zMAT3
	zMAT3& operator -= ( const zMAT3& m );							// decrementation by a zMAT3
	zMAT3& operator *= ( const zREAL d );							// multiplication by a constant
	zMAT3& operator /= ( const zREAL d );							// division by a constant
	zVEC3& operator [] ( const int i)		{ zERR_BOUNDS (i, VX, VZ);  return v[i]; };		// indexing
	zVEC3  operator [] ( const int i) const { return v[i]; };								// read-only indexing

	// special functions

	static const zMAT3& GetIdentity() { return s_identity; };
	void	MakeIdentity	() { *this = s_identity; };
	void	MakeZero		() { memset (this, 0, sizeof(*this)); };
	zMAT3	Transpose		() const;										// Transpose
	zMAT3	Inverse			(zREAL *det=NULL);								// Inverse
	zMAT3&	Apply			(V_FCT_PTR fct);									// Apply a func. to each element
	void	GetUpVector		( zVEC3& t) const {			t = (v[0][1], v[1][1], v[2][1]); };
	void	GetRightVector	( zVEC3& t) const {			t = (v[0][0], v[1][0], v[2][0]); };
	void	GetAtVector		( zVEC3& t) const {			t = (v[0][2], v[1][2], v[2][2]); };
	zVEC3	GetUpVector		()			const { return zVEC3(v[0][1], v[1][1], v[2][1]); };
	zVEC3	GetRightVector	()			const { return zVEC3(v[0][0], v[1][0], v[2][0]); };
	zVEC3	GetAtVector		()			const { return zVEC3(v[0][2], v[1][2], v[2][2]); };
	void SetAtVector (const zVEC3& a) {
		v[0][2] = a.n[VX];
		v[1][2] = a.n[VY];
		v[2][2] = a.n[VZ];
	};
	void SetUpVector (const zVEC3& a) {
		v[0][1] = a.n[VX];
		v[1][1] = a.n[VY];
		v[2][1] = a.n[VZ];
	};
	void SetRightVector (const zVEC3& a) {
		v[0][0] = a.n[VX];
		v[1][0] = a.n[VY];
		v[2][0] = a.n[VZ];
	};
	void MakeOrthonormal();

	// friends

	friend zMAT3 operator - (const zMAT3& a);						// -m1
	friend zMAT3 operator + (const zMAT3& a, const zMAT3& b);	    // m1 + m2
	friend zMAT3 operator - (const zMAT3& a, const zMAT3& b);	    // m1 - m2
	friend zMAT3 operator * (const zMAT3& a, const zMAT3& b);		// m1 * m2
	friend zMAT3 operator * (const zMAT3& a, const zREAL d);	    // m1 * 3.0
	friend zMAT3 operator * (const zREAL d, const zMAT3& a);	    // 3.0 * m1
	friend zMAT3 operator / (const zMAT3& a, const zREAL d);	    // m1 / 3.0
	friend int operator == (const zMAT3& a, const zMAT3& b);	    // m1 == m2 ?
	friend int operator != (const zMAT3& a, const zMAT3& b);	    // m1 != m2 ?
	friend ostream& operator << (ostream& s, zMAT3& m);				// output to stream
	friend istream& operator >> (istream& s, zMAT3& m);				// input from strm.
	friend void Alg_Swap(zMAT3& a, zMAT3& b);							// swap m1 & m2

	friend zMAT3 operator * (const zMAT4& a, const zMAT3& b);		// zMAT4 is used as a zMAT3 !
	friend zMAT3 operator * (const zMAT3& a, const zMAT4& b);

	// necessary friend declarations

	friend zVEC3 operator * (const zMAT3& a, const zVEC3& v);	    // linear transform
	friend zVEC2 operator * (const zMAT3& a, const zVEC2& v);	    // linear transform
};

/****************************************************************
*																*
*			   4x4 Matrix										*
*																*
****************************************************************/

class zENGINE_API zMAT4
{
	static zMAT4 s_identity;
public:
	
	zVEC4 v[4];
	
	// Constructors
	
	inline zMAT4() {};
	zMAT4(const zVEC4& v0, const zVEC4& v1, const zVEC4& v2, const zVEC4& v3);
	zMAT4(const zREAL d);
	//zMAT4(const zMAT4& m);
	
	// Assignment operators
	
	zMAT4& operator	 = ( const zMAT3& m );						// assignment of a zMAT3
	zMAT4& operator	 = ( const zMAT4& m );						// assignment of a zMAT4
	zMAT4& operator += ( const zMAT4& m );						// incrementation by a zMAT4
	zMAT4& operator -= ( const zMAT4& m );						// decrementation by a zMAT4
	zMAT4& operator *= ( const zREAL d );						// multiplication by a constant
	zMAT4& operator /= ( const zREAL d );						// division by a constant
	zVEC4& operator [] ( const int i)		{ zERR_BOUNDS (i, VX, VW); return v[i]; };	// indexing
	zVEC4  operator [] ( const int i) const { return v[i]; };	// read-only indexing
	
	// special functions
	
	zVEC3 Rotate (const zVEC3& vec) const {						// rotates given vec3, NO translation !!
		#define ROWCOL(i) v[i].n[0]*vec.n[VX] + v[i].n[1]*vec.n[VY] + v[i].n[2]*vec.n[VZ]
			return zVEC3(ROWCOL(0), ROWCOL(1), ROWCOL(2));
		#undef ROWCOL // (i)
	}
	static const zMAT4& GetIdentity() { return s_identity; };
	void	MakeIdentity		() { *this = s_identity; };
	void	MakeZero			() { memset (this, 0, sizeof(*this)); };
	zMAT4	Transpose			() const;						// Transpose
	zMAT4	TransposeLinTrafo	() const;						// Transpose Linear Transformation
	zMAT4	Inverse				() const;						// Inverse
	zMAT4	InverseLinTrafo		() const;						// Transpose
	zMAT4&	Apply(V_FCT_PTR fct);								// Apply a func. to each element
	zMAT4&	Translate( const zVEC3& t ) {						// translate relative
		v[0][3] += t.n[VX];
		v[1][3] += t.n[VY];
		v[2][3] += t.n[VZ];
		return *this;
	};
	zMAT4& SetTranslation( const zVEC3& t ) {					// translate absolute
		v[0][3] = t.n[VX];
		v[1][3] = t.n[VY];
		v[2][3] = t.n[VZ];
		return *this;
	};
	void GetTranslation( zVEC3& t) const {
		t.n[VX] = v[0][3];
		t.n[VY] = v[1][3];
		t.n[VZ] = v[2][3];
	};
	zVEC3	GetTranslation	()			const { return zVEC3(v[0][3], v[1][3], v[2][3]); };
	void	GetUpVector		( zVEC3& t) const {			t = (v[0][1], v[1][1], v[2][1]); };
	void	GetRightVector	( zVEC3& t) const {			t = (v[0][0], v[1][0], v[2][0]); };
	void	GetAtVector		( zVEC3& t) const {			t = (v[0][2], v[1][2], v[2][2]); };
	zVEC3	GetUpVector		()			const { return zVEC3(v[0][1], v[1][1], v[2][1]); };
	zVEC3	GetRightVector	()			const { return zVEC3(v[0][0], v[1][0], v[2][0]); };
	zVEC3	GetAtVector		()			const { return zVEC3(v[0][2], v[1][2], v[2][2]); };
	void SetAtVector (const zVEC3& a) {
		v[0][2] = a.n[VX];
		v[1][2] = a.n[VY];
		v[2][2] = a.n[VZ];
	};
	void SetUpVector (const zVEC3& a) {
		v[0][1] = a.n[VX];
		v[1][1] = a.n[VY];
		v[2][1] = a.n[VZ];
	};
	void SetRightVector (const zVEC3& a) {
		v[0][0] = a.n[VX];
		v[1][0] = a.n[VY];
		v[2][0] = a.n[VZ];
	};
	void ResetRotation () {
		SetRightVector	(zVEC3(1,0,0));
		SetUpVector		(zVEC3(0,1,0));
		SetAtVector		(zVEC3(0,0,1));
	};
	void	MakeOrthonormal		();
	zMAT3	ExtractRotation		();
	zVEC3	ExtractScaling		() const;
	void	PostRotateX			(const zREAL angleDeg);
	void	PostRotateY			(const zREAL angleDeg);
	void	PostRotateZ			(const zREAL angleDeg);
	
	void	PostScale			(const zVEC3& scale);
	void	PreScale			(const zVEC3& scale);
	
	zBOOL	IsUpper3x3Orthonormal() const;


	zVEC3	GetEulerAngles		() const;
	void	SetByEulerAngles	(const zVEC3 euler);
	
	zSTRING GetDescriptionRot	() const;
	zSTRING GetDescriptionPos	() const;
	void	SetByDescriptionRot (zSTRING& desc);
	void	SetByDescriptionPos (zSTRING& desc);
	
	
	// friends
	
	zENGINE_API friend zMAT4 operator - (const zMAT4& a);						// -m1
	zENGINE_API friend zMAT4 operator + (const zMAT4& a, const zMAT4& b);	    // m1 + m2
	zENGINE_API friend zMAT4 operator - (const zMAT4& a, const zMAT4& b);	    // m1 - m2
	inline zENGINE_API friend zMAT4 operator * (const zMAT4& a, const zMAT4& b);		// m1 * m2
	zENGINE_API friend zMAT4 operator * (const zMAT4& a, const zREAL d);	    // m1 * 4.0
	zENGINE_API friend zMAT4 operator * (const zREAL d, const zMAT4& a);	    // 4.0 * m1
	zENGINE_API friend zMAT4 operator / (const zMAT4& a, const zREAL d);	    // m1 / 3.0
	zENGINE_API friend int operator == (const zMAT4& a, const zMAT4& b);	    // m1 == m2 ?
	zENGINE_API friend int operator != (const zMAT4& a, const zMAT4& b);	    // m1 != m2 ?
	zENGINE_API friend ostream& operator << (ostream& s, zMAT4& m);			// output to stream
	zENGINE_API friend istream& operator >> (istream& s, zMAT4& m);			// input from strm.
	zENGINE_API friend void Alg_Swap(zMAT4& a, zMAT4& b);							// swap m1 & m2
	
	// necessary friend declarations
	
	friend zVEC4 operator * (const zMAT4& a, const zVEC4& v);	    // linear transform
	friend zVEC3 operator * (const zMAT4& a, const zVEC3& v);	    // linear transform
};

/****************************************************************
*																*
*	       2D functions and 3D functions						*
*																*
****************************************************************/

zENGINE_API zMAT3 Alg_Identity2D			();											// identity 2D
zENGINE_API zMAT3 Alg_Translation2D			(zVEC2& v);									// translation 2D
zENGINE_API zMAT3 Alg_Rotation2D			(zVEC2& Center, const zREAL angleDeg);	    // rotation 2D
zENGINE_API zMAT3 Alg_Scaling2D				(zVEC2& scaleVector);						// scaling 2D
								
zENGINE_API zMAT4 Alg_Identity3D			();											// identity 3D
zENGINE_API zMAT4 Alg_Translation3D			(const zVEC3& v);							// translation 3D
zENGINE_API zMAT4 Alg_Rotation3D			(const zVEC3& Axis, const zREAL angleDeg);		// rotation 3D
zENGINE_API zMAT4 Alg_Rotation3DN			(const zVEC3& Axis, const zREAL angleDeg);
zENGINE_API zMAT4 Alg_Rotation3DRad			(const zVEC3& Axis, const zREAL angleRad);
zENGINE_API zMAT4 Alg_Rotation3DNRad		(const zVEC3& Axis, const zREAL angleRad);
zENGINE_API zMAT4 Alg_Scaling3D				(const zVEC3& scaleVector);					// scaling 3D
zENGINE_API zMAT4 Alg_Perspective3D			(const zREAL d);							// perspective 3D

/****************************************************************
*																*
*			Added Special Functions								*
*																*
****************************************************************/

// Angle (radians) between 2 vectors

inline zREAL Alg_AngleRad ( zVEC4 const &Operand1, zVEC4 const &Operand2 ) {
	zVEC4 Unit1 = Operand1, Unit2 = Operand2;
	return (zREAL)acos( Unit1.Normalize() * Unit2.Normalize() );
}

inline zREAL Alg_AngleUnitRad ( zVEC4 const &Unit1, zVEC4 const &Unit2 )
{	return (zREAL)acos( Unit1 * Unit2 ); }

inline zREAL Alg_AngleRad (const zVEC3 &Operand1, const zVEC3 &Operand2 ) {
	zVEC3 Unit1 = Operand1, Unit2 = Operand2;
	return (zREAL)acos( Unit1.Normalize() * Unit2.Normalize() );
}

inline zREAL Alg_AngleUnitRad (const zVEC3 &Unit1, const zVEC3 &Unit2 ) {
	const zREAL dot = Unit1 * Unit2;
	if (dot>zREAL(+1)) return zREAL(0	); else
	if (dot<zREAL(-1)) return zREAL(M_PI); else
	return (zREAL)acos( dot ); 
}

// 20-Sep-2000  [Michael]
//		Funktionen durch identischen #define ersetzt
//
#define Alg_Rad2Deg(rad) (zREAL(zREAL(rad)*zREAL(180.0f)/zREAL(M_PI)))
/*inline zREAL Alg_Rad2Deg (const zREAL rad) {
	// deg = (180 * rad) / pi
	const zREAL C = (zREAL(180.0F) / zREAL(M_PI)); 
	return rad * C;
};*/

#define Alg_Deg2Rad(rad) (zREAL(zREAL(rad)*zREAL(M_PI)/zREAL(180.0f)))
/*inline zREAL Alg_Deg2Rad (const zREAL deg) {
	// rad = (deg * pi) / 180
	const zREAL C = (zREAL(M_PI) / zREAL(180.0F));
	return deg * C;
};*/

inline void Alg_CalcAziElev (const zVEC3& pos, zREAL& azi, zREAL& elev) {
	// src: news
	// returns pos's azi/elev relativ to (0,0,0)
	// azi = 0..90..180/-180..-90..0 (clockwise)
	// elev= 0..90..0..-90..0
	zREAL rInv,xx,yy,zz,sinElevInv;
	rInv		= pos.LengthApprox();
	if (rInv==0) rInv=0.00001F;
	rInv		= 1 / rInv;					// FIXME: use fast sqrInv
	xx			= pos[VX] * rInv;
	yy			= pos[VY] * rInv;
	zz			= pos[VZ] * rInv;
	elev		= acos(yy);
	sinElevInv	= zSin(elev);
	if (sinElevInv!=0)	sinElevInv	= 1 / sinElevInv; 
	else				sinElevInv	= 0.00001F;
	azi			= atan2 ((xx * sinElevInv) , (zz * sinElevInv));
	elev		= Alg_Deg2Rad(90) - elev;
};

inline void Alg_CalcAziElevUnit (const zVEC3& pos, zREAL& azi, zREAL& elev) {
	// src: news
	// returns pos's azi/elev relativ to (0,0,0)
	// azi = 0..90..180/-180..-90..0 (clockwise)
	// elev= 0..90..0..-90..0
	zREAL sinElevInv;
	elev		= acos(pos[VY]);
	sinElevInv	= zSin(elev);
	if (sinElevInv!=0)	sinElevInv	= 1 / sinElevInv;
	else				sinElevInv	= 0.00001F;
	azi			= atan2 ((pos[VX]* sinElevInv) , (pos[VZ]* sinElevInv));
	elev		= Alg_Deg2Rad(90) - elev;
};

inline zVEC4 Alg_FindPlaneCoeff ( const zVEC3& point1, const zVEC3& point2, const zVEC3& point3 ) {
	// Find coeffiecients (a,b,c,d) for the plane equotation
	// (a*x + b*y + c*z - d = 0)
	zVEC3 v1 = (point1 - point2) ^ (point3 - point2);  
	v1.Normalize();
	zVEC4 coeff(v1, zREAL(0));							// cross-product of v1 and v2

	coeff[VD] = (coeff[VA] * point2[VX] + 
				 coeff[VB] * point2[VY] + 
				 coeff[VC] * point2[VZ]);

	return coeff;
}

inline zVEC4 Alg_FindPlaneCoeffApprox ( const zVEC3& point1, const zVEC3& point2, const zVEC3& point3 ) {
	// Find coeffiecients (a,b,c,d) for the plane equotation
	// (a*x + b*y + c*z - d = 0)
	zVEC3 v1 = (point1 - point2) ^ (point3 - point2);  
	v1.NormalizeApprox();
	zVEC4 coeff(v1, zREAL(0));							// cross-product of v1 and v2

	coeff[VD] = (coeff[VA] * point2[VX] + 
				 coeff[VB] * point2[VY] + 
				 coeff[VC] * point2[VZ]);

	return coeff;
}


inline zBOOL Alg_IsColinear (const zVEC3& a, const zVEC3& b, const zVEC3& c) {
	// Achtung: Reihenfolge der Verts ist wichtig (Abs darf nicht!)
	// Duplicate inputs are treated as "colinear".
	zVEC3 u = (b-a);
	zVEC3 v = (c-b);
	zREAL len;
	len  = u.Length();		if (len==0)	return TRUE;	u	/= len;
	len  = v.Length();		if (len==0)	return TRUE;	v	/= len;
	return u.IsEqualEps(v) || u.IsEqualEps(-v);
};

inline zBOOL Alg_IsColinear (const zVEC3& vec1, const zVEC3& vec2) {
	// Duplicate inputs are treated as "colinear".
	zVEC3 u = vec1;
	zVEC3 v = vec2;
	zREAL len;
	len  = u.Length();		if (len==0)	return TRUE;	u	/= len;
	len  = v.Length();		if (len==0)	return TRUE;	v	/= len;
	return u.IsEqualEps(v) || u.IsEqualEps(-v);
};

void		 Alg_ClipAtZ0		(zVEC3& p1, zVEC3& p2);
	

/****************************************************************
*																*
*	       Quaternions											*
*																*
****************************************************************/

class zCQuat {
public:
	zREAL		qx,qy,qz,qw;

	zCQuat		() {};
	zCQuat		(const zREAL w) { qx=qy=qz=0; qw=w; };
	zCQuat		(const zREAL x, const zREAL y, const zREAL z, const zREAL w) { qx=x; qy=y; qz=z; qw=w; };
	
	// representation conversion
	// 3x3 Matrix 
	zMAT3		QuatToMatrix3	() const;
	void		QuatToMatrix3	(zMAT3& mat) const;
	void		Matrix3ToQuat	(const zMAT3& mat);

	// 4x4 Matrix 
	zMAT4		QuatToMatrix4	() const;
	void		QuatToMatrix4	(zMAT4& mat) const;
	void		Matrix4ToQuat	(const zMAT4& mat);

	// Euler Angles
	void		QuatToEuler		(zVEC3& euler) const;
	void		EulerToQuat		(const zVEC3& euler);

	// Axis/Angle
	void		QuatToAxisAngle	(zVEC3& axis, zREAL& angle) const;
	void		AxisAngleToQuat	(const zVEC3& axis, const zREAL& angle) {
		zREAL half = zREAL(0.5F) * angle;
		zREAL sinh = sin (half);
        qw = zCos(half);
		qx = axis[VX]*sinh; qy = axis[VY]*sinh; qz = axis[VZ]*sinh;
	};

	//
	void		Normalize		()			{ zREAL len = zREAL(1) / (qx*qx+qy*qy+qz*qz+qw*qw); qx*=len; qy*=len; qz*=len; qw*=len; };
	zCQuat		Inverse			() const	{ zREAL len = zREAL(1) / (qx*qx+qy*qy+qz*qz+qw*qw); return zCQuat(qx*-len, qy*-len, qz*-len, qw*len);  };
	zCQuat		InverseUnit		() const	{ return zCQuat ( -qx, -qy, -qz, qw ); };	// assert:  p is a unit quaternion
	zREAL		Dot				(const zCQuat& p) const			{ return p.qw*qw + p.qx*qx + p.qy*qy + p.qz*qz; };
	zREAL		Length			() const	{ return sqrt (Dot(*this)); };
	void		Unit			();
	void		Identity		()			{ qx=qy=qz=0; qw=1; };
	zBOOL		IsIdentity		() const	{ return ((qx==0) && (qy==0) && (qz==0) && (qw==1)); };

	// operators
	friend int	  operator== (const zCQuat& p, const zCQuat& q)	{ return ((p.qx==q.qx) && (p.qy==q.qy) && (p.qz==q.qz) && (p.qw==q.qw)); };
	friend zCQuat operator+  (const zCQuat& p, const zCQuat& q) { return zCQuat ( p.qx+q.qx, p.qy+q.qy, p.qz+q.qz, p.qw+q.qw ); }
	friend zCQuat operator-  (const zCQuat& p, const zCQuat& q)	{ return zCQuat ( p.qx-q.qx, p.qy-q.qy, p.qz-q.qz, p.qw-q.qw ); }
	friend zCQuat operator-  (const zCQuat& p)					{ return zCQuat (-p.qx, -p.qy, -p.qz, -p.qw ); };
	friend zCQuat operator*  (const zREAL c	, const zCQuat& p)	{ return zCQuat ( c*p.qx, c*p.qy, c*p.qz, c*p.qw ); };
	friend zCQuat operator*  (const zCQuat& p, const zCQuat& q)	{ return zCQuat ( p.qw*q.qx + p.qx*q.qw + p.qy*q.qz - p.qz*q.qy,
																				  p.qw*q.qy + p.qy*q.qw + p.qz*q.qx - p.qx*q.qz,
																				  p.qw*q.qz + p.qz*q.qw + p.qx*q.qy - p.qy*q.qx,
																				  p.qw*q.qw - p.qx*q.qx - p.qy*q.qy - p.qz*q.qz ); };
	// Interpolation
	void		Slerp			(const zREAL t, const zCQuat& p, const zCQuat& q);
	void		Lerp			(const zREAL t, const zCQuat& p, const zCQuat& q);
	void		Squad			(const zREAL t, const zCQuat& q0, const zCQuat& q1, const zCQuat& q2, const zCQuat& q3);
	zVEC3		Rotate			(const zVEC3& v) const;
};


/****************************************************************
*																*
*	       Packed Normal										*
*																*
****************************************************************/

//  a normal packed into 16 bits (quantized)

class zCPackedNormal16 {
public:
	// ctors
    zCPackedNormal16()			: n(0)	{};
    zCPackedNormal16(zVEC3& v)			{ Pack(v); };

	#define zPACK_NORM_SCALE		zREAL(31.999f)
	#define zPACK_NORM_SCALE_INV	(zREAL(1.0F) / zPACK_NORM_SCALE)

    // pack each component into 5 bits (quantized)
    void Pack (const zVEC3& v) 
	{
        const unsigned int ix	= (unsigned int) (zPACK_NORM_SCALE * (v.n[VX]+1.0f)*0.5f);
        const unsigned int iy	= (unsigned int) (zPACK_NORM_SCALE * (v.n[VY]+1.0f)*0.5f);
        const unsigned int iz	= (unsigned int) (zPACK_NORM_SCALE * (v.n[VZ]+1.0f)*0.5f);
        n = ((ix&31)<<10) | ((iy&31)<<5) | (iz&31);
    };

    // unpack into vector3
    zVEC3 Unpack (void) const
	{
        const float ix	= float((n>>10) & 31);
        const float iy	= float((n>>5) & 31);
        const float iz	= float(n & 31);
        return zVEC3((((ix*zPACK_NORM_SCALE_INV)*2.0f)-1.0f),
					 (((iy*zPACK_NORM_SCALE_INV)*2.0f)-1.0f),
					 (((iz*zPACK_NORM_SCALE_INV)*2.0f)-1.0f));
    };

	#undef zPACK_NORM_SCALE
	#undef zPACK_NORM_SCALE_INV

    // get/set packed representation
    zWORD	GetPacked	(void)		const	{ return n;	};
    void	SetPacked	(zWORD _n)			{ n = _n;	};

private:
	zWORD n;
};


// fast arcustangens approximation.
// source: http://www.dspguru.com/comp.dsp/tricks/alg/fxdatan2.htm
inline zREAL Alg_ArcTan2Approx(const float y, const float x)
{
	#define _PI			3.14159265358979323846f
	zREAL coeff_1 = _PI/4.0f;
	zREAL coeff_2 = 3.0f*coeff_1;

	zREAL abs_y = zAbs(y)+1e-10;      // kludge to prevent 0/0 condition
	zREAL angle;

	if (x>=0)
	{
	  angle = coeff_1 - coeff_1 * ((x - abs_y) / (x + abs_y));
	}
	else
	{
	  angle = coeff_2 - coeff_1 * ((x + abs_y) / (abs_y - x));
	}

	if (y < 0)  return(-angle);     // negate if in quad III or IV
	else		   return(+angle);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// Komplexe Zahlen
//////////////////////////////////////////////////////////////////////////////////////////////////
struct zComplex
{
	zREAL real;
	zREAL img;
	float mag;
	float phase;

	zComplex() 	
	{
		real = 0.0f;
		img	 = 0.0f;
		EmptyCache();
	};

	zComplex(const float r, const float i)
	{
		real = r;
		img  = i;
		EmptyCache();
	};

	zComplex operator=(const zComplex c)
	{
		zComplex d;

		d.real = c.real;
		d.img  = c.img;
		d.mag  = c.mag;
		d.phase= c.phase;
		
		return (d);
	};

	zComplex operator+(const zComplex c)
	{
		zComplex d;

		d.real += c.real;
		d.img  += c.img;

		return (d);
	};

	zComplex operator*(const zComplex c)
	{
		zComplex d;
		
		d.real = this->real * c.real - this->img * c.img;
		d.img  = this->real * c.img  + this->img * c.real;

		return (d);
	};

	void Set(const float r, const float i)
	{
		real = r;
		img  = i;
		EmptyCache();
	};

	void Get(float &r, float &i)
	{
		r = real;
		i = img;
	}

	float Mag() 
	{
		if (mag == 0) mag   = ( (float)Alg_SqrtApprox( real*real + img*img) );
		return mag;
	}

	float Phase() 
	{
		if (phase==0) phase = ( (float)Alg_ArcTan2Approx( img, real) );
		return phase;
	}

	void  EmptyCache()
	{
		mag		= 0.0F;
		phase	= 0.0f;
	}
};



//////////////////////////////////////////////////////////////////
//																//
//		zVEC2 - IMPLEMENTATION									//
//																//
//////////////////////////////////////////////////////////////////

// CONSTRUCTORS

inline zVEC2::zVEC2(const zVEC3& v) // it is up to caller to avoid divide-by-zero
{ n[VX] = v.n[VX]/v.n[VZ]; n[VY] = v.n[VY]/v.n[VZ]; };

inline zVEC2::zVEC2(const zVEC3& v, int dropAxis) {
    switch (dropAxis) {
	case VX: n[VX] = v.n[VY]; n[VY] = v.n[VZ]; break;
	case VY: n[VX] = v.n[VX]; n[VY] = v.n[VZ]; break;
	default: n[VX] = v.n[VX]; n[VY] = v.n[VY]; break;
    }
}

// ASSIGNMENT OPERATORS

//inline zVEC2& zVEC2::operator = (const zVEC2& v)
//{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; return *this; }

inline zVEC2& zVEC2::operator += ( const zVEC2& v )
{ n[VX] += v.n[VX]; n[VY] += v.n[VY]; return *this; }

inline zVEC2& zVEC2::operator -= ( const zVEC2& v )
{ n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; return *this; }

inline zVEC2& zVEC2::operator *= ( const zREAL d )
{ n[VX] *= d; n[VY] *= d; return *this; }

inline zVEC2& zVEC2::operator /= ( const zREAL d )
{ zREAL d_inv = 1./d; n[VX] *= d_inv; n[VY] *= d_inv; return *this; }

// SPECIAL FUNCTIONS

inline zREAL zVEC2::Length()
{ return sqrt(Length2()); }

inline zREAL zVEC2::Length2()
{ return n[VX]*n[VX] + n[VY]*n[VY]; }

inline zVEC2& zVEC2::Normalize() // it is up to caller to avoid divide-by-zero
{ *this /= Length(); return *this; }

// FRIENDS

inline zVEC2 operator - (const zVEC2& a)
{ return zVEC2(-a.n[VX],-a.n[VY]); }

inline zVEC2 operator + (const zVEC2& a, const zVEC2& b)
{ return zVEC2(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY]); }

inline zVEC2 operator - (const zVEC2& a, const zVEC2& b)
{ return zVEC2(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY]); }

inline zVEC2 operator * (const zVEC2& a, const zREAL d)
{ return zVEC2(d*a.n[VX], d*a.n[VY]); }

inline zVEC2 operator * (const zREAL d, const zVEC2& a)
{ return a*d; }

inline zVEC2 operator * (const zMAT3& a, const zVEC2& v) {
    zVEC3 av;

    av.n[VX] = a.v[0].n[VX]*v.n[VX] + a.v[0].n[VY]*v.n[VY] + a.v[0].n[VZ];
    av.n[VY] = a.v[1].n[VX]*v.n[VX] + a.v[1].n[VY]*v.n[VY] + a.v[1].n[VZ];
    av.n[VZ] = a.v[2].n[VX]*v.n[VX] + a.v[2].n[VY]*v.n[VY] + a.v[2].n[VZ];
    return av;
}

inline zVEC2 operator * (const zVEC2& v, zMAT3& a)
{ return a.Transpose() * v; }

inline zREAL operator * (const zVEC2& a, const zVEC2& b)
{ return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY]); }

inline zVEC2 operator / (const zVEC2& a, const zREAL d)
{ zREAL d_inv = 1./d; return zVEC2(a.n[VX]*d_inv, a.n[VY]*d_inv); }

inline zVEC3 operator ^ (const zVEC2& a, const zVEC2& b)
{ return zVEC3(0.0, 0.0, a.n[VX] * b.n[VY] - b.n[VX] * a.n[VY]); }

inline int operator == (const zVEC2& a, const zVEC2& b)
{ return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]); }

inline int operator != (const zVEC2& a, const zVEC2& b)
{ return !(a == b); };


//////////////////////////////////////////////////////////////////
//																//
//		zVEC3 - IMPLEMENTATION									//
//																//
//////////////////////////////////////////////////////////////////

inline zVEC3::zVEC3(const zVEC4& v) // it is up to caller to avoid divide-by-zero
{ n[VX] = v.n[VX] / v.n[VW]; n[VY] = v.n[VY] / v.n[VW];
  n[VZ] = v.n[VZ] / v.n[VW]; }

// ASSIGNMENT OPERATORS

//inline zVEC3& zVEC3::operator = (const zVEC3& v)
//{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; return *this; }

inline zVEC3& zVEC3::operator += ( const zVEC3& v )
{ n[VX] += v.n[VX]; n[VY] += v.n[VY]; n[VZ] += v.n[VZ]; return *this; }

inline zVEC3& zVEC3::operator -= ( const zVEC3& v )
{ n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; n[VZ] -= v.n[VZ]; return *this; }

inline zVEC3& zVEC3::operator *= ( const zREAL d )
{ n[VX] *= d; n[VY] *= d; n[VZ] *= d; return *this; }

//#pragma optimize( "g", off )
inline zVEC3& zVEC3::operator /= ( const zREAL d )		// evil
{ zREAL d_inv = zREAL(1.0)/d; n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
  return *this; }

// SPECIAL FUNCTIONS

inline zREAL zVEC3::Length() const
{  return sqrt(Length2()); }

inline zREAL zVEC3::Length2() const
{  return n[VX]*n[VX] + n[VY]*n[VY] + n[VZ]*n[VZ]; }

inline zREAL zVEC3::LengthApprox () const {
	// Quelle: Gems4, dist_fast.c
	zREAL ix = (zAbs (zREAL(n[VX])));
	zREAL iy = (zAbs (zREAL(n[VY])));
	zREAL iz = (zAbs (zREAL(n[VZ])));
	
	// needs only two comparisons
	if (ix<iy) zSwap (ix, iy);
	if (ix<iz) zSwap (ix, iz);
	
	// now ix is the largest
	const zREAL t = iy + iz;
	return zREAL((ix - (ix*(1.0 / 16.0)) + (t*(1.0 / 4.0)) + (t*(1.0 / 8.0))));
}; 

//#pragma optimize( "g", off )
inline zVEC3& zVEC3::Normalize() 
//{ *this /= Length(); return *this; }
{	
	// it is up to caller to avoid divide-by-zero		
	const zREAL d_inv = zREAL(1.0) / Length();
	n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
	return *this;
};

inline zVEC3& zVEC3::NormalizeSafe () 
{	
	zREAL len = Length();				
	if (len==0) len=zREAL(0.000001F);
	const zREAL d_inv	= zREAL(1.0) / len;	
	n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
	return *this;
};

inline zVEC3& zVEC3::NormalizeApprox () // it is up to caller to avoid divide-by-zero
//{ *this /= Length(); return *this; }
{	
//	zREAL d_inv = zREAL(1.0) / LengthApprox();
	zREAL d_inv = Alg_SqrtInvApprox (n[VX]*n[VX] + n[VY]*n[VY] + n[VZ]*n[VZ]);
	n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
	return *this;
};

// FRIENDS

inline zVEC3 operator - (const zVEC3& a) {  return zVEC3(-a.n[VX],-a.n[VY],-a.n[VZ]); }

inline zVEC3 operator + (const zVEC3& a, const zVEC3& b)
{ return zVEC3(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY], a.n[VZ] + b.n[VZ]); }

inline zVEC3 operator - (const zVEC3& a, const zVEC3& b)
{ return zVEC3(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY], a.n[VZ]-b.n[VZ]); }

inline zVEC3 operator * (const zVEC3& a, const zREAL d)
{ return zVEC3(d*a.n[VX], d*a.n[VY], d*a.n[VZ]); }

inline zVEC3 operator * (const zREAL d, const zVEC3& a)
{ return a*d; }

inline zVEC3 operator * (const zMAT4& a, const zVEC3& v) {		// linear transform
    #define ROWCOL(i) a.v[i].n[0]*v.n[VX] + a.v[i].n[1]*v.n[VY] + \
	                  a.v[i].n[2]*v.n[VZ] + a.v[i].n[3]
    return zVEC3(ROWCOL(0), ROWCOL(1), ROWCOL(2));
    #undef ROWCOL // (i)
}

// return a * zVEC4(v); }

inline zVEC3 operator * (const zVEC3& v, const zMAT4& a)
{ return a.Transpose() * v; }

inline zREAL operator * (const zVEC3& a, const zVEC3& b)
{ return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY] + a.n[VZ]*b.n[VZ]); }

inline zVEC3 operator / (const zVEC3& a, const zREAL d)
{ zREAL d_inv = 1./d; return zVEC3(a.n[VX]*d_inv, a.n[VY]*d_inv,
  a.n[VZ]*d_inv); }

inline zVEC3 operator ^ (const zVEC3& a, const zVEC3& b) {
    return zVEC3(a.n[VY]*b.n[VZ] - a.n[VZ]*b.n[VY], 
				 a.n[VZ]*b.n[VX] - a.n[VX]*b.n[VZ],
				 a.n[VX]*b.n[VY] - a.n[VY]*b.n[VX]);
}

inline int operator == (const zVEC3& a, const zVEC3& b)
{ return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]) && (a.n[VZ] == b.n[VZ]);
}

inline int operator != (const zVEC3& a, const zVEC3& b) { return !(a == b); }


//////////////////////////////////////////////////////////////////
//																//
//		zVEC4 - IMPLEMENTATION									//
//																//
//////////////////////////////////////////////////////////////////

// ASSIGNMENT OPERATORS

//inline zVEC4& zVEC4::operator = (const zVEC4& v)
//{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; n[VW] = v.n[VW];
//return *this; }

inline zVEC4& zVEC4::operator += ( const zVEC4& v )
{ n[VX] += v.n[VX]; n[VY] += v.n[VY]; n[VZ] += v.n[VZ]; n[VW] += v.n[VW];
return *this; }

inline zVEC4& zVEC4::operator -= ( const zVEC4& v )
{ n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; n[VZ] -= v.n[VZ]; n[VW] -= v.n[VW];
return *this; }

inline zVEC4& zVEC4::operator *= ( const zREAL d )
{ n[VX] *= d; n[VY] *= d; n[VZ] *= d; n[VW] *= d; return *this; }

inline zVEC4& zVEC4::operator /= ( const zREAL d )
{ zREAL d_inv = 1./d; n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
  n[VW] *= d_inv; return *this; }

inline zREAL& zVEC4::operator [] (const int i) {
	zERR_BOUNDS (i, VX, VW);
    return n[i];
}

// FRIENDS

inline zVEC4 operator - (const zVEC4& a)
{ return zVEC4(-a.n[VX],-a.n[VY],-a.n[VZ],-a.n[VW]); }

inline zVEC4 operator + (const zVEC4& a, const zVEC4& b)
{ return zVEC4(a.n[VX] + b.n[VX], a.n[VY] + b.n[VY], a.n[VZ] + b.n[VZ],
  a.n[VW] + b.n[VW]); }

inline zVEC4 operator - (const zVEC4& a, const zVEC4& b)
{  return zVEC4(a.n[VX] - b.n[VX], a.n[VY] - b.n[VY], a.n[VZ] - b.n[VZ],
   a.n[VW] - b.n[VW]); }

inline zVEC4 operator * (const zVEC4& a, const zREAL d)
{ return zVEC4(d*a.n[VX], d*a.n[VY], d*a.n[VZ], d*a.n[VW] ); }

inline zVEC4 operator * (const zREAL d, const zVEC4& a)
{ return a*d; }

inline zVEC4 operator * (const zMAT4& a, const zVEC4& v) {
    #define ROWCOL(i) a.v[i].n[0]*v.n[VX] + a.v[i].n[1]*v.n[VY] \
    + a.v[i].n[2]*v.n[VZ] + a.v[i].n[3]*v.n[VW]
    return zVEC4(ROWCOL(0), ROWCOL(1), ROWCOL(2), ROWCOL(3));
    #undef ROWCOL // (i)
}

inline zVEC4 operator * (const zVEC4& v, zMAT4& a)
{ return a.Transpose() * v; }

inline zREAL operator * (const zVEC4& a, const zVEC4& b)
{ return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY] + a.n[VZ]*b.n[VZ] +
  a.n[VW]*b.n[VW]); }

inline zVEC4 operator / (const zVEC4& a, const zREAL d)
{ zREAL d_inv = 1./d; return zVEC4(a.n[VX]*d_inv, a.n[VY]*d_inv, a.n[VZ]*d_inv,
  a.n[VW]*d_inv); }

inline int operator == (const zVEC4& a, const zVEC4& b)
{ return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]) && (a.n[VZ] == b.n[VZ])
  && (a.n[VW] == b.n[VW]); }

inline int operator != (const zVEC4& a, const zVEC4& b)
{ return !(a == b); }


//////////////////////////////////////////////////////////////////
//																//
//		zMAT4 - IMPLEMENTATION									//
//																//
//////////////////////////////////////////////////////////////////

zMAT4 operator * (const zMAT4& a, const zMAT4& b) {
    #define ROWCOL(i, j) a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + \
    a.v[i].n[2]*b.v[2][j] + a.v[i].n[3]*b.v[3][j]
    return zMAT4(
    zVEC4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3)),
    zVEC4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3)),
    zVEC4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3)),
    zVEC4(ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL(3,3))
    );
	#undef ROWCOL 
}


static const float ONE_HALF		= 0.5f;
static const float THREE_HALVES = 1.5f;
__declspec(naked) float Alg_SqrtInvApprox (const float f)
{
	__asm // 18 cycles
	{
		fld			dword ptr [esp + 4]
		// f
		fmul		dword ptr [ONE_HALF]
		// x2 = 0.5f*f
		mov			eax, [esp + 4]
		mov			ecx, 0x5f3759df
		shr			eax, 1
		sub			ecx, eax
		mov			[esp + 4], ecx
		fmul		dword ptr [esp + 4]
		// x2*y
		fld			dword ptr [esp + 4]
		// y
		// x2*y
		fmul		dword ptr [esp + 4]
		// y*y
		// x2*y
		fld			dword ptr [THREE_HALVES]
		// 1.5f
		// y*y
		// x2*y
		fmul		dword ptr [esp + 4]
		// 1.5f*y
		// y*y
		// x2*y
		fxch		st(2)
		// x2*y
		// y*y
		// 1.5f*y
		// ******** stall 1 clock ********
		fmulp		st(1), st
		// x2*y * y*y
		// 1.5f*y
		// ******** stall 2 clocks ********
		fsubp		st(1), st
		// y = 1.5f*y - (x2*y * y*y)
		ret
	}
}



const float AVERAGE_SMOOTH_FRAME_TIME = .025F;

class zCValueSmooth
{
public:
	zCValueSmooth();

	void	SetIsSmooth	(const zBOOL b)			{ bSmooth= b;			};
	zBOOL	GetIsSmooth	() const				{ return bSmooth;		};
	void	SetInertia	(const float i)			{ inertia= i;			};
	float	GetInertia	() const				{ return inertia;		};

	void	Set			(const float v)			{ fixedValue = smoothedValue =v; };

	float	GetFixed	() const				{ return fixedValue;	};
	float	GetSmoothed () const				{ return smoothedValue;	};

	void    Smooth		(float &v);

private:
	float	fixedValue;
	float	smoothedValue;
	float	inertia;
	zBOOL	bSmooth;
};


class zCVEC3Smooth
{
public:
	zCVEC3Smooth();

	void	SetIsSmooth	(const zBOOL b)			{ bSmooth= b;			};
	zBOOL	GetIsSmooth	() const				{ return bSmooth;		};
	void	SetInertia	(const float i)			{ inertia= i;			};
	float	GetInertia	() const				{ return inertia;		};

	void	Set			(const zVEC3 v)			{ fixedValue = smoothedValue =v; };

	zVEC3	GetFixed	() const				{ return fixedValue;	};
	zVEC3	GetSmoothed () const				{ return smoothedValue;	};

	void	Smooth		(zVEC3 &v);

private:
	zVEC3	fixedValue;
	zVEC3	smoothedValue;
	float	inertia;
	zBOOL	bSmooth;

};



// enable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 

#endif