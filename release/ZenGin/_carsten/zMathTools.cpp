/********************************************************************************
 
 Project : Gothic
 File    : cMath.cpp
 Author  : Carsten Edenfeld
 Version : 0.00
 Created : 12.05.98 06:01:40
 Last Mod: 12.05.98 06:01:40
 
*********************************************************************************
 TODO : 
*********************************************************************************
 BUGS : 
*********************************************************************************
 NOTE : 
*********************************************************************************/

#include <math.h>
#include "zcore.h"
#include <zTrigo.h>
#include <zMathTools.h>
#include <zDbgTools.h>
#include <zGrafix.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 


zMAT4 zCPose :: tmpMat;


zMAT4& GetPoseOfHeading(const zPOINT3 & origin, const zVEC3 & at)
{
	static zMAT4 tmp;

	zERR_ASSERT(at.Length()>0);

	tmp				= Alg_Identity3D();
	zVEC3 up		= zPOINT3 (0.0F,1.0F,0.0F);

	up				= up - (((up * at)) * at);
	zREAL upLen		= up.Length();

	// Test, ob die Wahl des UpVectors(0,1,0) unguenstig war, d.h. up==newAtVector
	// (falls ja: alternatives up waehlen)
    // If this vector has near-zero length because the input specified a
    // bogus up vector, let's try a default up vector
    if (1e-6f>upLen)
    {
		up		= zVEC3(1,0,0) - at[VX] * at;
		upLen	= up.Length();
		
		// If we still have near-zero length, resort to a different axis.
		if (1e-6f>upLen)
		{
			up		= zVEC3(0,0,1) - at[VZ] * at;
			upLen	= up.Length();
		}
    }

	if (1e-6f<=upLen)
	{
		up				/= upLen;
		zVEC3 right		= (up ^ at).Normalize();

		tmp.SetAtVector		(at);
		tmp.SetUpVector		(up);
		tmp.SetRightVector	(right);
		tmp.SetTranslation  (origin);
	}
	else zERR_WARNING("C: GetPoseOfHeading: could not get up vector. at is:  X :" + zSTRING(at[VX]) + ", Y: " + zSTRING(at[VY]) + ", Z:" + zSTRING(at[VZ]));

	return tmp;

}


void	zCCircleArc3D:: Slerp( const float t, zPOINT3 &p ) 
{
	const float b =  b0 + t*(b1-b0) ;	
	float cosb, sinb;

	zSinCos(b, sinb, cosb);
	//						  ->  ->           ->            ->
	// Setup circle in Space. x = m + r*cos(b)*u0 + r*sin(b)*v0
	p = center + (radius * cosb) * u + (radius * sinb) * v;
};

void  zCPose	::	SetInertiaRot( float f )  
{
	numSamplesRot = Lerp( f, 1, MAX_SAMPLES_ROT );
	
	for (int i=0; i<numSamplesRot; i++) qRing[i]  = actRot;
	ringPosRot =0;
}	
void  zCPose	::	SetInertiaPos( float f ) 
{
	numSamplesPos = Lerp( f, 1, MAX_SAMPLES_POS );
	
	for (int i=0; i<numSamplesPos; i++) pRing[i]  = actPos;
	ringPosTrans =0;
}	
	
void  zCPose::SetInertiaSamplesRot(const int numSamples)
{
	numSamplesRot = numSamples;
	for (int i=0; i<numSamplesRot; i++) qRing[i]  = actRot;
	ringPosRot =0;
};

void  zCPose::SetInertiaSamplesPos(const int numSamples)
{
	numSamplesPos = numSamples;
	for (int i=0; i<numSamplesPos; i++) pRing[i]  = actPos;
	ringPosTrans =0;
};

void zCPose::CalcAvgRot()
{

	zCQuat avgRot;
	if ((oneTurn) && (numSamplesRot==4 || numSamplesRot==16 || numSamplesRot==64))
	{
		zCQuat	srcQuatList[MAX_SAMPLES_ROT];
		zCQuat	avgQuatList[MAX_SAMPLES_ROT];
		zCQuat* pSrcQuatList = &srcQuatList[0];
		zCQuat* pAvgQuatList = &avgQuatList[0];

		int next;
		if (ringPosRot == numSamplesRot-1) next = 0;
		else							   next = ringPosRot+1;

		for (int i=0; i<numSamplesRot; i++)
		{
			srcQuatList[i]=qRing[next++];
			if (next == numSamplesRot) next = 0;
		}

		int numSamplesSrc = numSamplesRot;

		int numAvg = 0;
		do
		{
			for (int i=0; i<numSamplesSrc; i+=4) 
			{
				numAvg = 0;
				zCQuat nextQuat;
				nextQuat.Squad(0.5F,pSrcQuatList[i],pSrcQuatList[i+1],pSrcQuatList[i+2],pSrcQuatList[i+3]);
				pAvgQuatList[i>>2]=nextQuat;
				numAvg++;
			}
			zSwap(pAvgQuatList,pSrcQuatList);
			numSamplesSrc = numAvg;
		}
		while (numAvg>=4);

		avgRot = pSrcQuatList[0];
	}
	else
	{
		//for (int i=1; i<numSamplesRot; i++) avgRot = avgRot + qRing[i];

		int next;
		if (ringPosRot==numSamplesRot-1)		 next = 0;
		else									 next = ringPosRot+1;

		avgRot = qRing[next];

		zCQuat nextQuat;
		for (int i=1; i<numSamplesRot; i++) 
		{
			if (++next==numSamplesRot-1) next = 0;
			nextQuat.Slerp(0.5F,avgRot,qRing[next]);
			avgRot = nextQuat;
		}
	}

	avgRot.Unit();
	actRot = avgRot;

};

void  zCPose ::	UpdatePose( zMAT4	&newMat ) 
{	

	zPOINT3 avgPos = zPOINT3(0,0,0);
	zCQuat  avgRot; 
	
	qRing[ringPosRot].Matrix4ToQuat(newMat);
	actRotAbs = qRing[ringPosRot++];
	if ( ringPosRot == numSamplesRot) ringPosRot = 0;
	pRing[ringPosTrans++]= newMat.GetTranslation();
	if ( ringPosTrans == numSamplesPos ) ringPosTrans = 0;

	avgPos = pRing[0];
	for (int i=1; i<numSamplesPos; i++) avgPos = avgPos + pRing[i];

	CalcAvgRot();

	avgPos/=numSamplesPos;
	actPos = avgPos;

	actPosAbs = newMat.GetTranslation();

};

void  zCPose ::	UpdatePose( zCQuat	&newRot, zPOINT3 &newPos ) 
{
	zPOINT3 avgPos = zPOINT3(0,0,0);
	zCQuat  avgRot; 

	qRing[ringPosRot++] = newRot ;
	if ( ringPosRot == numSamplesRot) ringPosRot = 0;
	pRing[ringPosTrans++]= newPos;
	if ( ringPosTrans == numSamplesPos) ringPosTrans = 0;

	avgPos = pRing[0];
	for (int i=1; i<numSamplesPos; i++) avgPos = avgPos + pRing[i];	
	avgPos.Normalize();

	CalcAvgRot();

	actPos = avgPos;
	actPosAbs = newPos;
	actRotAbs = newRot;

};

void zCPose::UpdateRot ( zMAT4	&newMat )
{
	qRing[ringPosRot].Matrix4ToQuat(newMat);
	actRotAbs = qRing[ringPosRot++];
	if ( ringPosRot == numSamplesRot ) 
	{
		oneTurn		= TRUE;
		ringPosRot	= 0;
	}

	CalcAvgRot();
};

void zCPose::UpdateRot ( zCQuat	&newQuat) 
{
	qRing[ringPosRot++] = newQuat;
	if ( ringPosRot == numSamplesRot) 
	{	
		oneTurn    = TRUE;
		ringPosRot = 0;
	}
	CalcAvgRot();
	actRotAbs = newQuat;
}

void zCPose::UpdatePos(zPOINT3 &newPos) 
{
	zPOINT3 avgPos = zPOINT3(0,0,0);
	
	pRing[ringPosTrans++]= newPos;
	if ( ringPosTrans == numSamplesPos ) ringPosTrans = 0;

	for (int i=0; i<numSamplesPos; i++) avgPos = avgPos + pRing[i];

	avgPos.Normalize();

	actPos = avgPos;
	actPosAbs = newPos;

}

zCPose::zCPose() 
{
	numSamplesPos = 1; 
	numSamplesRot = 1;
	ringPosRot    = 0;
	ringPosTrans  = 0;
	actPos		  = zVEC3(0,0,0);
	actRot.Identity();
	oneTurn		  = FALSE;
};

void zCPose::SetRot ( zMAT4	&newMat ) 
{	
	zCQuat newRot; 
	newRot.Matrix4ToQuat(newMat);
	for (int i=0; i<numSamplesRot; i++) qRing[i]=newRot;
	actRot = newRot;
};

void zCPose::SetRot ( zCQuat	&newQuat) 
{ 
	for (int i=0; i<numSamplesRot; i++) qRing[i]=newQuat;
	actRot = newQuat;
};

void zCPose::SetPos ( zMAT4	&newMat ) 
{
	for (int i=0; i<numSamplesPos; i++) pRing[i]=newMat.GetTranslation(); 
	actPos = newMat.GetTranslation();
};

void zCPose::SetPos ( zPOINT3 &newPos ) 
{
	for (int i=0; i<numSamplesPos; i++) pRing[i]=newPos; 
	actPos = newPos;
};

void zCPose::GetPose(zMAT4 &mat) 
{ 
	mat.MakeIdentity();
	actRot.QuatToMatrix4(mat);
	mat.SetTranslation(actPos);
};

zMAT4& zCPose::GetPose() 
{
	tmpMat.MakeIdentity();
	actRot.QuatToMatrix4(tmpMat);
	tmpMat.SetTranslation(actPos);
	return tmpMat;
}

void zCPose::GetPoseAbs(zMAT4 &mat) 
{
	mat.MakeIdentity();
	actRotAbs.QuatToMatrix4(mat);
	mat.SetTranslation(actPos);
}

zMAT4& zCPose::GetRotMatAbs() 
{ 
	tmpMat.MakeIdentity();
	actRotAbs.QuatToMatrix4(tmpMat);
	return tmpMat; 
};

zMAT4&	zCPose::GetRotMat () 
{ 
	tmpMat.MakeIdentity();
	actRot.QuatToMatrix4(tmpMat);
	return tmpMat; 
};
	

// enable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
