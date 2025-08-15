/********************************************************************************
 
 Project : Gothic
 File    : cMath.h
 Author  : Carsten Edenfeld
 Version : 0.00
 Created : 12.05.98 06:00:04
 Last Mod: 12.05.98 06:00:04
 
*********************************************************************************
 TODO : 
*********************************************************************************
 BUGS : 
*********************************************************************************
 NOTE : 
*********************************************************************************/

#ifndef __ZMATHTOOLS_H__
#define __ZMATHTOOLS_H__

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

#ifndef __ZERROR_H__
#include "zError.h"
#endif

#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

#ifndef __ZTYPES3D_H__
#include <zTypes3D.h>
#endif

//#define Lerp(t, a, b) ( a + t * (b - a) ) 

/*template <class T>
class zCLerpHelp
{
	static T Lerp(const float t,const T &a,const T &b)
	{
		zERR_ASSERT(0<=t && t<=1);
		return static_cast<T>( a + t * (b - a) ); 
	};
};

#define Lerp zCLerpHelp::Lerp
*/

template <class T>
T Lerp(const float t,const T &a,const T &b) 
{
	// [Bendlin] Floatabweichung in die Abfrage einbeziehen
	// zERR_ASSERT(0<=t && t<=1);
	zERR_ASSERT( 0<=t && t<=1+FLT_EPSILON );
	return static_cast<T>( a + t * (b - a) ); 
}

zMAT4& GetPoseOfHeading(const zPOINT3 &origin, const zVEC3 &atVec);

inline  zMAT4 zInverseMatD	(const zMAT4 &matrix, const zSTRING &funcName)
{
    zMAT4 a(matrix),			// As a evolves from original mat into identity
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
			zERR_WARNING("C: cMath(InverseMatD): singular matrix; can't invert, called from function "+funcName);
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
	
};


inline zBOOL CheckMatrixConsistency( const zMAT4 &matrix, const zBOOL heavyCheck = FALSE ) 
{

	const float EPS_UNIT = 0.0001F;

	// check auf NAN, INF etc.
	for (int i=0; i<4; i++) 
	{
		for (int j=0; j<4; j++) {
			if (!_finite(matrix[i][j]) || _isnan (matrix[i][j])) 
			{
				return FALSE;
			}
		}
	}

	// check auf einheitslänge der UVN Vectoren, TODO: invertierbarkeit checken
	if (heavyCheck) 
	{
		if (zAbs(matrix.GetAtVector()	.Length()-1) > EPS_UNIT) return FALSE;
		if (zAbs(matrix.GetUpVector()	.Length()-1) > EPS_UNIT) return FALSE;
		if (zAbs(matrix.GetRightVector().Length()-1) > EPS_UNIT) return FALSE;
	}
	return TRUE;
};



class zCCircleArc3D 
{

public:
	float	radius;		// angle in radians
	float	angle;		// act angle;
	float	time;		// act time if rotating
	zPOINT3 center;		// center of circle in R³
	zVEC3	u,v;		// spanning vecs
	float	b0,b1;

	zCCircleArc3D(const zVEC3 u0, const zVEC3 v0, const zVEC3 m,const float _b0,const float _b1) { 
		u=u0; v=v0; center = m; b0=_b0; b1=_b1; };
	
	~zCCircleArc3D(){};

//	zPOINT3	Lerp ( const float t )  { return LerpRad( b0 + t*(b1-b0) ); };
//	inline zPOINT3	LerpRad		 ( const float b );
//	inline zPOINT3	Lerp1( const float rad );
//	inline void		Slerp( const float t, zMAT4 &pose ) ;
	inline void		Slerp( const float t, zPOINT3 &p );
};



const int MAX_SAMPLES_POS = 50;
const int MAX_SAMPLES_ROT = 100;

class zCPose {
private:
	static zMAT4	tmpMat;

	zCQuat	qRing[MAX_SAMPLES_ROT];
	zPOINT3 pRing[MAX_SAMPLES_POS];
	int		ringPosTrans;
	int		ringPosRot;

	zCQuat	actRotAbs;
	zPOINT3 actPosAbs;
	zCQuat	actRot;
	zPOINT3	actPos;
	zBOOL   oneTurn;

	int		numSamplesPos;
	int		numSamplesRot;

public:
	
	zCPose();
	~zCPose() {};

	void	SetPose		( zMAT4	&newMat )							{ SetRot(newMat);  SetPos(newMat.GetTranslation()); };
	void	SetPose		( zCQuat	&newRot, zMAT4 &newMat )		{ SetRot(newRot); SetPos(newMat.GetTranslation()); };
	void	SetRot		( zMAT4	&newMat );
	void	SetRot		( zCQuat	&newQuat);
	void	SetPos		( zMAT4	&newMat );
	void	SetPos		( zPOINT3 &newPos );
	void	UpdatePose	( zCQuat	&newRot, zPOINT3 &newPos ) ;
	void	UpdatePose	( zMAT4	&newMat );
	void	UpdateRot	( zMAT4	&newMat );
	void	UpdateRot	( zCQuat	&newQuat);
	void	UpdatePos	( zMAT4	&newMat )							{ UpdatePos(newMat.GetTranslation()); };
	void	UpdatePos	( zPOINT3 &newPos );

	zPOINT3	GetPos		() const									{ return actPos; };
	void	GetPose		(zMAT4 &mat);
	zMAT4&  GetPose		();
	void	GetPoseAbs	(zMAT4 &mat);
	void	GetPoseAbs	(zCQuat &rot, zPOINT3 &p) const				{ rot = actRotAbs; p = actPosAbs; };
	void	GetPose		(zCQuat &rot, zPOINT3 &p) const				{ rot = actRot; p = actPos; };
	zCQuat  GetRot		()  const									{ return actRot; };
	zCQuat  GetRotAbs	()  const									{ return actRotAbs; };
	zCQuat  GetRotQuatAbs() const									{ return actRotAbs; };
	zCQuat  GetRotQuat	()  const									{ return actRot; };
	zMAT4&	GetRotMatAbs();
	zMAT4&	GetRotMat	();
	void	SetInertia   ( float f )								{ SetInertiaPos(f); SetInertiaRot(f); };
	void	SetInertiaPos( float f );
	void	SetInertiaRot( float f );
	void	SetInertiaSamplesRot(const int numSamples);
	void	SetInertiaSamplesPos(const int numSamples);

private:
	void	CalcAvgRot	();

};

// enable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 

#endif