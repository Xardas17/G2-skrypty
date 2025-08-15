/********************************************************************************
 
 Project : Gothic
 File    : zCKBSplines.h
 // Kochanek-Bartels tension-continuity-bias spline interpolation for
 // positional data. orig. by dave eberly
 Version : 0.00
 Created : 31.07.98 
 Last Mod: 31.07.98 
 
*********************************************************************************
 TODO : 
*********************************************************************************
 BUGS : 
*********************************************************************************
 NOTE : 
*********************************************************************************/

#ifndef __KBSPLINES_H__
#define __KBSPLINES_H__

#ifndef __Z3D_H__
#include "z3d.h"
#endif

#ifndef __ZTYPES3D_H__
#include "zTypes3d.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zContainer.h"
#endif

#ifndef __ZWIEW_H__
#include "zview.h"
#endif

#ifndef __ZMATHTOOLS_H__
#include "zMathTools.h"
#endif


enum zTSplLerpMode {
	zTSPL_LERP_UNDEF = 0,
	zTSPL_LERP_PATH,
	zTSPL_LERP_PATH_IGNOREROLL,
	zTSPL_LERP_PATH_ROT_SAMPLES
};

class zCPositionKey {
public:
    // sample time
    zREAL		t;
    // sample position
    zPOINT3		p;
	// sample rotation
	zCQuat		rot;
    // sample parameters for affecting tangential behavior at control point
    zREAL		tension, continuity, bias;

	zCPositionKey() { 
		tension		= 0;
		continuity	= 0;
		bias		= 0;
		t			= 0;
	};

	~zCPositionKey() {};

	void	SetPosition	(const zPOINT3 &pos)		{ p=pos;			};
	zPOINT3&GetPosition ()							{ return p;			};
	void	SetRot		(const zCQuat &q)			{ rot = q;			};
	void	SetRot		(const zMAT4 &m)			{ rot.Matrix4ToQuat(m); };
	zCQuat&	GetQuat		()							{ return rot;		};
	zMAT4	GetMat		()							{ zMAT4 res = Alg_Identity3D(); rot.QuatToMatrix4(res); res.SetTranslation(p); return res; };
	void	SetMat		(const zMAT4 &m)			{ SetRot(m); m.GetTranslation(p); };
	void	SetTime		(const zREAL &time)			{ t = time;			};
	float	GetTime		()  const					{ return t;			};
	void	SetTension  (const zREAL &tens)			{ tension = tens;	};
	void	SetContinuity(const zREAL &c)			{ continuity = c;	};
	void	SetBias		(const zREAL &bs)			{ bias = bs;	};
	zREAL	GetTension  ()	const					{ return tension ;			};
	zREAL	GetContinuity()	const					{ return continuity;		};
	zREAL	GetBias		()	const					{ return bias;				};

};

// private structures to hide details of polynomials
class zCCubicPolynomial  {
public:
    // P(u) = C0 + u * C1 + u² * C2 + u³ * C3,  0 <= u <= 1
    zPOINT3 c0, c1, c2, c3;
    // sample time interval on which polynomial is valid, tmin <= t <= tmax
    zREAL tmin, tmax, trange;
//	zREAL length;

	zCCubicPolynomial() {};
	~zCCubicPolynomial(){};
	
	zREAL	Length(const zREAL u);
	zREAL   Speed (const zREAL u);

	inline  void	Interpolate0 (const zREAL u,zPOINT3 &p);
	inline  void	Interpolate1 (const zREAL u,zPOINT3 &p);
	inline  void	Interpolate2 (const zREAL u,zPOINT3 &p);	

};

class zCKBSpline {

private:
    zCCubicPolynomial* polynom;

    int		numPolynomials;
	zREAL*  length;  // tmp!
    zREAL	totalLength;
	int		lastKey;
	zCArray <zCPositionKey*> keyList;
    zBOOL   deleteKeysWhenDone;

	void	ComputeArcLength();
	void	InvertIntegral  (const zREAL s, int &i, zREAL &u);
	void	ComputeIAndU	(const zREAL t, int &i, zREAL &u);

public:
	zCKBSpline(zCArray <zCPositionKey*> &key, zBOOL deleteKeys=TRUE) {
		InitVars  ();
		Initialize(key,deleteKeys);
	}
	zCKBSpline() 
	{ 
		InitVars();
	};

	~zCKBSpline()												{ Terminate(); };

	void	Initialize(zCArray <zCPositionKey*> &key, zBOOL deleteKeysWhenDone=TRUE);
	void	Changed	  ();
	void	Terminate ();
	void	Interpolate (zREAL t, zPOINT3 &p)					{ Interpolate0(t,p); };
	void	Interpolate0(zREAL t, zPOINT3 &p);  // F (t)
	void	Interpolate1(zREAL t, zPOINT3 &p);  // F'(t)
	void	Interpolate2(zREAL t, zPOINT3 &p);  // F"(t)
	void	InterpolateN(zREAL t, zMAT4 &mat,const zTSplLerpMode lerpMode= zTSPL_LERP_PATH) { Interpolate0( Lerp(t,GetMinTime(),GetMaxTime()),mat,lerpMode); };
	void	Interpolate (zREAL t, zMAT4 &mat,const zTSplLerpMode lerpMode= zTSPL_LERP_PATH) { Interpolate0(t,mat,lerpMode); };
	void	Interpolate0(zREAL t, zMAT4 &mat,const zTSplLerpMode lerpMode= zTSPL_LERP_PATH);  // F (t)
	void	Interpolate1(zREAL t, zMAT4 &mat,const zTSplLerpMode lerpMode= zTSPL_LERP_PATH);  // F'(t)

	// Interpolation funcs by arc length
	// Evaluate position and derivatives by specifying arc length s along the
	// curve.  If L is the total length of the curve, then 0 <= s <= L is
	// required.

	void	Interpolate_AL  (const zREAL s, zPOINT3 &p)			{ Interpolate0_AL(s,p); };
	void	Interpolate_ALN (const zREAL t, zPOINT3 &p)			{ Interpolate0_AL( Lerp( t, (float)0, Length() ),p); };
	void	Interpolate0_AL (const zREAL s, zPOINT3 &p);
	void	Interpolate1_AL (const zREAL s, zPOINT3 &p);
	void	Interpolate2_AL (const zREAL s, zPOINT3 &p);
	void	Interpolate_AL  (const zREAL s, zMAT4 &mat, const zTSplLerpMode lerpMode= zTSPL_LERP_PATH)	{ Interpolate0_AL(s,mat,lerpMode); };
	void	Interpolate_ALN (const zREAL t, zMAT4 &mat, const zTSplLerpMode lerpMode= zTSPL_LERP_PATH)	{ Interpolate0_AL( Lerp( t, (float)0, Length() ),mat,lerpMode); };
	void	Interpolate0_AL (const zREAL s, zMAT4 &mat, const zTSplLerpMode lerpMode= zTSPL_LERP_PATH);
	void	Interpolate1_AL (const zREAL s, zMAT4 &mat, const zTSplLerpMode lerpMode= zTSPL_LERP_PATH);

	zREAL	Length		() const								{ return totalLength; };
	zREAL	Length		( const zREAL t );

	void	DrawControlPolygon( const zCOLOR col );
	void	Draw			  ( const zCOLOR col, const float quality = 0 );

	zREAL	GetTime			  ( const zREAL length );
	zREAL	GetMinTime		  ()								{ return polynom[0].tmin; }; 
	zREAL	GetMaxTime		  ()								{ return polynom[numPolynomials-1].tmax; };

	zCPositionKey *GetKey	(const int num)						{ return keyList[num]; };
	int			  GetNumKeys()									{ return keyList.GetNumInList(); };
	int			  GetLastKey  () const							{ return lastKey; };

private:
	void	InitVars		  ()
	{
		totalLength		   = 0;
		numPolynomials	   = 0;
		polynom			   = 0;
		length			   = 0;
		lastKey			   = 0;
        deleteKeysWhenDone = TRUE;
	}
};


#endif
