/********************************************************************************
 
 Project : Gothic
 File    : zCKBSplines.cpp
 Version : 0.00
 Created : 31.07.98 
 Last Mod: 31.07.98 
 
*********************************************************************************
 TODO : Geschwindigkeitsoptimierung durch Nichtbenutzung von Tension/Bias/Continuity!
*********************************************************************************
 BUGS : weird: wenn nur über die Position interpoliert wird, ruckelt
		es manchmal, aber wenn parallel ein Draw() aufgerufen wird ist es smooth ??
*********************************************************************************
 NOTE : 
*********************************************************************************/
#include <math.h>
#include "zcore.h"
#include "zKBSplines.h"


/* ----------------------------------------------------------------------
	
    zCKBSpline::Initialize()	

	4.10.2000	[Moos]	
                Parameter deleteKeysWhenDone hinzugefügt; gibt an,
                ob in Terminate() die übergebenen Keys per delete gelöscht werden
                sollen. Muss FALSE sein, wenn die Keys auf dem Stack erzeugt wurden.


   ---------------------------------------------------------------------- */


void zCKBSpline::Initialize (zCArray <zCPositionKey*> &key, zBOOL deleteKeys)
{
    zERR_ASSERT(key.GetArray()); // [Moos] Sicherheit gegen Doppelverwendung von Keys; falls hier ein Fehler auftritt, bitte mich rufen!
    deleteKeysWhenDone = deleteKeys;

    int numKeys = key.GetNumInList();
	keyList = key;

	// if we have less than 4 keys given, we fake a little bit
	// (this is a feature to make life easier in the outside world of the zCKBSpline Class)
	if (numKeys == 3) {
		keyList.InsertEnd(key[key.GetNumInList()-1]);
		numKeys = 4;
	}
	else if (numKeys == 2) {
		keyList.InsertFront(key[0]);
		keyList.InsertEnd(key[key.GetNumInList()-1]);
		numKeys = 4;
	}

	zERR_ASSERTT_STRICT(numKeys>=4,"C: zKBSpline.cpp(zCKBSpline::Initialize): Kochanek Bartels Splines must have 4 keys minimum" );

    numPolynomials = numKeys-3;
    polynom = zNEW( zCCubicPolynomial[numPolynomials] );

    int i0 = 0, i1 = 1, i2 = 2, i3 = 3;
    for (/**/; i0 < numPolynomials; i0++, i1++, i2++, i3++)
    {
        // build P[i2]-P[i1];
        zPOINT3 dp = key[i2]->p - key[i1]->p;

        // build multipliers at point P[i1]
        zREAL omt0 = 1-key[i1]->tension;
        zREAL omc0 = 1-key[i1]->continuity;
        zREAL opc0 = 1+key[i1]->continuity;
        zREAL omb0 = 1-key[i1]->bias;
        zREAL opb0 = 1+key[i1]->bias;
        zREAL adj0 = 2*(key[i2]->t-key[i1]->t)/(key[i2]->t-key[i0]->t);
        zREAL out0 = 0.5F*adj0*omt0*opc0*opb0;
        zREAL out1 = 0.5F*adj0*omt0*omc0*omb0;

        // build outgoing tangent at P[i1]
        zPOINT3 Tout = out1*dp + out0 *(key[i1]->p - key[i0]->p);

        // build multipliers at point P[i2]
        zREAL omt1 = 1-key[i2]->tension;
        zREAL omc1 = 1-key[i2]->continuity;
        zREAL opc1 = 1+key[i2]->continuity;
        zREAL omb1 = 1-key[i2]->bias;
        zREAL opb1 = 1+key[i2]->bias;
        zREAL adj1 = 2*(key[i2]->t-key[i1]->t)/(key[i3]->t-key[i1]->t);
        zREAL in0 = 0.5F*adj1*omt1*omc1*opb1;
        zREAL in1 = 0.5F*adj1*omt1*opc1*omb1;

        // build incoming tangent at P[i2]
        zPOINT3 Tin = in1*(key[i3]->p - key[i2]->p)+in0*dp;

        polynom[i0].c0	= key[i1]->p;
        polynom[i0].c1	= Tout;
        polynom[i0].c2	= 3  * dp -2*Tout - Tin;
        polynom[i0].c3	= -2 * dp +  Tout + Tin;
        polynom[i0].tmin= key[i1]->t;
        polynom[i0].tmax= key[i2]->t;

        polynom[i0].trange = polynom[i0].tmax - polynom[i0].tmin;
    }

    ComputeArcLength();
    
    key.DeleteList(); // [Moos] Sicherheit, daß die Liste nicht noch für ein zweites Spline verwendet werden kann
}
//---------------------------------------------------------------------------
void zCKBSpline::Changed()
{
	// assume num keys stays constant. (!!)
    if (polynom) delete[] polynom;
    if (length)  delete[] length;
	Initialize(keyList);
}
//---------------------------------------------------------------------------
void zCKBSpline::Terminate ()
{
    if (polynom) {
		delete[] polynom;
		polynom = 0;
	}
    if (length) {
		delete[] length;
		length = 0;
	}

    if (deleteKeysWhenDone)
        for(int i=keyList.GetNum()-1;i>=0;i--) // [Moos] Leakfix, 2.Versuch
            delete keyList[i];  

	keyList.DeleteList();
}
//---------------------------------------------------------------------------
inline void zCCubicPolynomial::Interpolate0 (zREAL u,zPOINT3 &p)
{
	zClamp(u,zREAL(0),zREAL(1));
    p = c0 + u*(c1 + u*(c2 + u*c3));
}
//---------------------------------------------------------------------------
inline void zCCubicPolynomial::Interpolate1 (zREAL u, zPOINT3 &p)
{
	zClamp(u,zREAL(0),zREAL(1));
    p = c1+ u*(2*c2 + u*3*c3);
}
//---------------------------------------------------------------------------
inline void zCCubicPolynomial::Interpolate2 (zREAL u, zPOINT3 &p)
{
	zClamp(u,zREAL(0),zREAL(1));
    p = 2*c2 + u*6*c3;
}
//---------------------------------------------------------------------------
void zCKBSpline::ComputeIAndU (const zREAL t, int &i, zREAL &u)
{
    // clamp to [tmin,tmax]

    if ( polynom[0].tmin < t ) {

        if ( t < polynom[numPolynomials-1].tmax ) {
            for (i = 0; i < numPolynomials; i++)	{

                if ( t < polynom[i].tmax ) break;

            }
            u = (t-polynom[i].tmin)/polynom[i].trange;
        }
        else
        {
            i = numPolynomials-1;
            u = 1;
        }
    }
    else {
        i = 0;
        u = 0;
    }
}
//---------------------------------------------------------------------------
void zCKBSpline::Interpolate0 (const zREAL t, zPOINT3 &p)
{
    int i; zREAL u;
    ComputeIAndU(t,i,u);
	lastKey = int(i+(3*u));
    polynom[i].Interpolate0(u,p);
}
//---------------------------------------------------------------------------
void zCKBSpline::Interpolate0 (const zREAL t, zMAT4 &mat,const zTSplLerpMode lerpMode)
{
    int i; zREAL u; float tN,t1,t2;

	//assert(0<=t && t<=GetMaxTime());
	float tClamped = t;
	zClamp( tClamped,zREAL(0),zREAL(GetMaxTime()) );
	
    ComputeIAndU(tClamped,i,u);
	lastKey = int(i+(3*u));
	zPOINT3 origin;
    polynom[i].Interpolate0(u,origin);
	
	if (lerpMode == zTSPL_LERP_PATH_ROT_SAMPLES) {

		// find correct rot key to be interpolated
		zCQuat newRot;
		zBOOL directHit = FALSE;

		// FIXME (!): brute force

		int foundKey = -1;
		for (int i=0; i<keyList.GetNumInList(); i++) 
		{
			if (keyList[i]->GetTime() == t) { newRot = keyList[i]->GetQuat(); directHit = TRUE; break; };
			if (keyList[i]->GetTime() > t ) { foundKey = i-1; break; };
		}

		if (!directHit) 
		{
			t1 = keyList[foundKey]->GetTime();
			t2 = keyList[foundKey+1]->GetTime();
			tN = (t-t1)/(t2-t1);
			newRot.Slerp(tN,keyList[foundKey]->GetQuat(),keyList[foundKey+1]->GetQuat());
		}

		newRot.QuatToMatrix4(mat);
		mat.SetTranslation(origin);

		return;
	}
	else {
		zVEC3 at;
		polynom[i].Interpolate1(u,at);
		if (lerpMode == zTSPL_LERP_PATH_IGNOREROLL) 
		{
			// FIXME: wieso nur bei lerpMode == zTSPL_LERP_PATH_IGNOREROLL ?
			at[VY]=0;
			assert(!(at[VX]==0&&at[VY]==0&&at[VZ]==0));
			at.Normalize();
		}
		else if (at != zVEC3(0,0,0)) at.Normalize();
		
		mat = GetPoseOfHeading(origin,at);
	}

}
//---------------------------------------------------------------------------
void zCKBSpline::Interpolate1 (const zREAL t, zMAT4 &mat,const zTSplLerpMode lerpMode)
{
    int i; zREAL u;
    ComputeIAndU(t,i,u);
	zPOINT3 origin;
    polynom[i].Interpolate1(u,origin);

	if (lerpMode == zTSPL_LERP_PATH_ROT_SAMPLES) {
		// find correct rot key to be interpolated
		zCQuat newRot;
		zBOOL directHit = FALSE;

		// FIXME (!): brute force

		int foundKey = -1;
		for (int i=0; i<keyList.GetNumInList(); i++) 
		{
			if (keyList[i]->GetTime() == t) { newRot = keyList[i]->GetQuat(); directHit = TRUE; break; };
			if (keyList[i]->GetTime() > t ) { foundKey = i-1; break; };
		}

		if (!directHit) 
		{
			float t1 = keyList[foundKey]->GetTime();
			float t2 = keyList[foundKey+1]->GetTime();
			float tN = (t-t1)/(t2-t1);
			newRot.Slerp(tN,keyList[foundKey]->GetQuat(),keyList[foundKey+1]->GetQuat());
		}

		newRot.QuatToMatrix4(mat);
		mat.SetTranslation(origin);
		return;
	}
	else {
		zVEC3 at;
		polynom[i].Interpolate2(u,at);
		if (lerpMode == zTSPL_LERP_PATH_IGNOREROLL) {
			at[VY]=0;
			assert(!(at[VX]==0&&at[VY]==0&&at[VZ]==0));
			at.Normalize();
		}
		mat = GetPoseOfHeading(origin,at);
	}


}
//---------------------------------------------------------------------------
void zCKBSpline::Interpolate1 (const zREAL t, zPOINT3 &p)
{
    int i;zREAL u;
    ComputeIAndU(t,i,u);
	polynom[i].Interpolate1(u,p);
}
//---------------------------------------------------------------------------
void zCKBSpline::Interpolate2 (const zREAL t, zPOINT3 &p)
{
    int i;zREAL u;
    ComputeIAndU(t,i,u);
	polynom[i].Interpolate2(u,p);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// position and derivatives as functions of arc length
//---------------------------------------------------------------------------
zREAL zCCubicPolynomial::Speed (const zREAL u)
{
    zVEC3 vel;
    Interpolate1(u,vel);
	return vel.Length();
}
//---------------------------------------------------------------------------
zREAL zCCubicPolynomial::Length (const zREAL u)
{
    // Legendre polynomial information for Gaussian quadrature of speed
    // on domain [0,u], 0 <= u <= 1.
    const int degree = 5;
    static zREAL modRoot[degree] =
    {
        // Legendre roots mapped to (root+1)/2
        0.046910077F,
        0.230765345F,
        0.5F,
        0.769234655F,
        0.953089922F
    };
    static zREAL modCoeff[degree] =
    {
        // original coefficients divided by 2
        0.118463442F,
        0.239314335F,
        0.284444444F,
        0.239314335F,
        0.118463442F
    };

    // Need to transform domain [0,u] to [-1,1].  If 0 <= x <= u
    // and -1 <= t <= 1, then x = u*(t+1)/2.
    zREAL result = 0;
    for (int i = 0; i < degree; i++) result += modCoeff[i]*Speed(u*modRoot[i]);
    result *= u;

    return result;
}
//---------------------------------------------------------------------------
void zCKBSpline :: ComputeArcLength ()
{
    length = zNEW( zREAL[numPolynomials+1] );
    length[0] = 0;

	for (int i = 0; i < numPolynomials; i++)
    {
        // length of current polynomial
        zREAL currentLength = polynom[i].Length(1);
        // total length of curve between poly[0] and poly[i+1]
        length[i+1] = length[i] + currentLength;
    }

    totalLength = length[numPolynomials];
}
//---------------------------------------------------------------------------
void zCKBSpline::InvertIntegral (const zREAL s,int &i,zREAL &u)
{
    // clamp s to [0,L] so that t in [tmin,tmax]
    if ( s <= 0 ) {
        i = 0;
        u = 0;
        return;
    }
    if ( s >= totalLength ) {
        i = numPolynomials-1;
        u = 1;
        return;
    }

    // determine which polynomial corresponds to s
    zREAL dist;
    for (i = 0; i < numPolynomials; i++)
    {
        if ( s <= length[i+1] ) {
            // distance along segment
            dist = s - length[i];
            
            // initial guess for inverting the arc length integral
            u = dist/(length[i+1] - length[i]);
            break;
        }
    }

    // use Newton's method to invert the arc length integral
    const zREAL tolerance = 1e-06F;
    const int maxIters = 32;
    for (int iter = 0; iter < maxIters; iter++)
    {
        zREAL diff = polynom[i].Length(u) - dist;
        if ( fabs(diff) <= tolerance ) break;

        // assert(speed > 0);
        u -= diff/polynom[i].Speed(u);
    }

}
//---------------------------------------------------------------------------
void zCKBSpline :: Interpolate0_AL (const zREAL s, zPOINT3 &p)
{
    int i;
    zREAL u;
    InvertIntegral(s,i,u);
    polynom[i].Interpolate0(u,p);
}
//---------------------------------------------------------------------------
void zCKBSpline :: Interpolate0_AL (const zREAL s, zMAT4 &mat,const zTSplLerpMode lerpMode)
{
    int i;
    zREAL u;
    InvertIntegral(s,i,u);

	//zerr.Message("C: real interpolation time" + zSTRING(Lerp(u,polynom[i].tmin,polynom[i].tmax)));

	zPOINT3 origin;
    polynom[i].Interpolate0(u,origin);

	if (lerpMode == zTSPL_LERP_PATH_ROT_SAMPLES) {
		// find correct rot key to be interpolated
		// find correct rot key to be interpolated
		zCQuat newRot;
		zBOOL directHit = FALSE;

		// FIXME (!): brute force

		int foundKey = -1;

		float t = GetTime(s);

		for (int i=0; i<keyList.GetNumInList(); i++) 
		{
			if (keyList[i]->GetTime() == t) { newRot = keyList[i]->GetQuat(); directHit = TRUE; break; };
			if (keyList[i]->GetTime() > t ) { foundKey = i-1; break; };
		}

		if (!directHit) 
		{
			float t1 = keyList[foundKey]->GetTime();
			float t2 = keyList[foundKey+1]->GetTime();
			float tN = (t-t1)/(t2-t1);
			newRot.Slerp(tN,keyList[foundKey]->GetQuat(),keyList[foundKey+1]->GetQuat());
		}

		newRot.QuatToMatrix4(mat);
		mat.SetTranslation(origin);
		return;
	}
	else {
		zVEC3 at;
		polynom[i].Interpolate1(u,at);
		if (lerpMode == zTSPL_LERP_PATH_IGNOREROLL){
			at[VY]=0;
			assert(!(at[VX]==0&&at[VY]==0&&at[VZ]==0));
			at.Normalize();
		}
		mat = GetPoseOfHeading(origin,at);
	}

}
//---------------------------------------------------------------------------
void zCKBSpline :: Interpolate1_AL (const zREAL s, zMAT4 &mat,const zTSplLerpMode lerpMode)
{
    int i;
    zREAL u;
    InvertIntegral(s,i,u);
	zPOINT3 origin;
    polynom[i].Interpolate1(u,origin);

	if (lerpMode == zTSPL_LERP_PATH_ROT_SAMPLES) {
		// find correct rot key to be interpolated
		zCQuat newRot;
		zBOOL directHit = FALSE;

		// FIXME (!): brute force
		float t = GetTime(s);

		int foundKey = -1;
		for (int i=0; i<keyList.GetNumInList(); i++) 
		{
			if (keyList[i]->GetTime() == t) { newRot = keyList[i]->GetQuat(); directHit = TRUE; break; };
			if (keyList[i]->GetTime() > t ) { foundKey = i-1; break; };
		}

		if (!directHit) 
		{
			float t1 = keyList[foundKey]->GetTime();
			float t2 = keyList[foundKey+1]->GetTime();
			float tN = (t-t1)/(t2-t1);
			newRot.Slerp(tN,keyList[foundKey]->GetQuat(),keyList[foundKey+1]->GetQuat());
		}

		newRot.QuatToMatrix4(mat);
		mat.SetTranslation(origin);
		return;
	}
	else {
		zVEC3 at;
		polynom[i].Interpolate2(u,at);
		assert(!(at[VX]==0&&at[VY]==0&&at[VZ]==0));
		if (lerpMode == zTSPL_LERP_PATH_IGNOREROLL) {
			at[VY]=0;
			assert(!(at[VX]==0&&at[VY]==0&&at[VZ]==0));
			at.Normalize();
		}
		mat = GetPoseOfHeading(origin,at);
	}

}
//---------------------------------------------------------------------------
void zCKBSpline :: Interpolate1_AL (const zREAL s, zPOINT3 &p)
{
    int i; zREAL u;
    InvertIntegral(s,i,u);
    polynom[i].Interpolate1(u,p);
}
//---------------------------------------------------------------------------
void zCKBSpline :: Interpolate2_AL (const zREAL s, zPOINT3 &p)
{
    int i; zREAL u;
    InvertIntegral(s,i,u);
    polynom[i].Interpolate2(u,p);
}
//---------------------------------------------------------------------------
zREAL zCKBSpline ::Length (const zREAL t)
{
    int i; zREAL u;
	ComputeIAndU(t,i,u);

    return length[i] + polynom[i].Length(u);
}
//---------------------------------------------------------------------------

void zCKBSpline :: DrawControlPolygon( const zCOLOR col ) 
{
	zPOINT3 p0,p1;
	int x0,x1,y0,y1;
	if (numPolynomials == 0 || keyList.GetNumInList() < 4) return;
	p1 = zCCamera::activeCam -> Transform (keyList[0]->p);

	for (int i=1; i<keyList.GetNumInList(); i++) {
		p0 = p1;
		p1 = zCCamera::activeCam -> Transform (keyList[i]->p);
		Alg_ClipAtZ0(p0,p1);
		zCCamera::activeCam -> Project( &p0, x0, y0 );
		zCCamera::activeCam -> Project( &p1, x1, y1 );
		if (p0[VZ] >= 1 && p1[VZ] >= 1) 
		if (screen->ClipLine(x0,y0,x1,y1))  
			zrenderer->DrawLineZ( (float)x0,(float)y0, (float)1/p0[VZ], (float)x1,(float)y1,(float) 1/p1[VZ], col);
	}
};

void zCKBSpline :: Draw		( const zCOLOR col, const float quality) 
{
	if (numPolynomials == 0 || keyList.GetNumInList() < 4) return;
	const float MIN_QUAL = 0.05F;
	const float MAX_QUAL = 0.4F;
	float k = Lerp( quality, MIN_QUAL, MAX_QUAL );

	zPOINT3 p0,p1;
	int x0,y0,x1,y1; 

	float zNear		= 1;//zCCamera::activeCam->nearClipZ;
	float tMin		= GetMinTime(), tMax=GetMaxTime();
	float t			= tMin; 
	float timeOffset= (tMax-tMin)/((k*Length())+1);

	Interpolate0( tMin,  p0  );
	t += timeOffset;  if ( t > tMax ) t = tMax;
	Interpolate0( t, p1  );
	p0 = zCCamera::activeCam -> Transform( p0 );
	p1 = zCCamera::activeCam -> Transform( p1 );
	zCCamera::activeCam -> Project( &p0, x0, y0 );
	zCCamera::activeCam -> Project( &p1, x1, y1 );
	//clip to viewport edges
	if (p0[VZ] >= zNear && p1[VZ] >= zNear) 
	if (screen->ClipLine(x0,y0,x1,y1))  
		zrenderer->DrawLineZ( (float)x0,(float)y0, (float)1/p0[VZ], (float)x1,(float)y1, (float)1/p1[VZ], col);

	do {
		if (t<0) {
			#ifdef DEBUG_EDENFELD
			zERR_WARNING("C: zKBSplines.cpp(zCKBSpline :: Draw) t<0!!!");
			#endif
			return;
		}
		p0 = p1;
		t += timeOffset; if ( t > tMax ) t = tMax;
		Interpolate0( t, p1 );
		p1 = zCCamera::activeCam -> Transform( p1 );
		zCCamera::activeCam -> Project( &p0, x0, y0 );
		zCCamera::activeCam -> Project( &p1, x1, y1 );
		//clip to viewport edges
		if (p0[VZ] >= zNear && p1[VZ] >= zNear) 
		if (screen->ClipLine(x0,y0,x1,y1))  
			zrenderer->DrawLineZ( (float)x0,(float)y0, (float)1/p0[VZ], (float)x1,(float)y1, (float)1/p1[VZ], col);

	} while ( t<tMax );

};


zREAL zCKBSpline :: GetTime(const zREAL length) 
{
    int i;zREAL u;
    InvertIntegral(length,i,u);
	return Lerp(u,polynom[i].tmin,polynom[i].tmax);
}