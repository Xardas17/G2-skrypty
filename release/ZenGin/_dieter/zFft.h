// zFFT.h: Schnittstelle für die Klasse zCFFT.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZFFT_H__
#define __ZFFT_H__



#ifndef __ZALGEBRA_H__
#include "zAlgebra.h"
#endif

enum zTFFT
{
	zTFFT_NONE,
	zTFFT_SLOW,
	zTFFT_NORMAL,
	zTFFT_FAST
};



class zRandom_Gauss
{

protected:
	zREAL	*u,c,cd,cm;
	int		i97,j97;
	int		m_gaussCall;
	
	zREAL	RandomUniform			();
	zREAL	UnRandomUniform			();

public:
	zRandom_Gauss(int ij,int kl);
	~zRandom_Gauss();

	int		GetInt					(int lower=0,int upper=100);
	zREAL	GetFloat				(zREAL lower=0.0,zREAL upper=1.0);
	zREAL	GetGaussian				(zREAL mean=0.0,zREAL stddev=1.0);
	zREAL	GetGaussAt				( long index = 0);

	unsigned int rand24				();
	
	unsigned int unRand24			();

	
	void	StepForward				(long forward=1);
	void	StepBack				(long backup=1);
};


class zCFFT  
{
public:
	zCFFT();
	virtual ~zCFFT();

	static zCFFT s_fft;
	static zCFFT s_fftSlow;
	static zCFFT s_fftFast;

	static void		S_Init				();
	static zREAL	S_CalcWave2D		(const zREAL x, const zREAL z, const zREAL tileSize, const zTFFT fftType ) ;
	static void		S_AnimateWaveMap	(zREAL time);
	static void		S_SetFrameCtr		(const zTFrameCtr a_iFCount);
	static zCFFT&	GetMain				()			{ return s_fft;	};

	zBOOL			PerformFFT			(int bInv = 1, int type = 0);
	void			SetFrameCtr			(const zTFrameCtr a_iFCount);
	void			SetSpeed			(const zREAL a_fSpeed);
	void			CreateWaveMap		(zREAL a, zVEC3 &v);
	zREAL			CalcWave2D			(const zREAL x, const zREAL z, const zREAL tileSize);
	zComplex&		GetWaveHeightSmooth	(const zREAL x, const zREAL z, const zREAL tileSize) ;
	zComplex&		GetWaveHeight		(const zREAL x, const zREAL z, const zREAL tileSize) ;
	zComplex&		GetWaveHeight		(const int ix, const int iz) ;
	void			AnimateWaveMap		(zREAL time);


protected:
	
	zComplex		**m_h0Map;
	zComplex		**m_WaveMap;
	zComplex		**m_IWaveMap;
	zREAL			fftSpeed;
	zTFrameCtr		frameCtr;
	zTFrameCtr		frameCtrLastUsed;

	inline void	fft_float				(unsigned NumSamples, int InverseTransform, zComplex *In, zComplex *Out);

	zREAL		Index_to_frequency		(unsigned NumSamples, unsigned Index);
	int			IsPowerOfTwo			(unsigned x) ;
	unsigned	NumberOfBitsNeeded		(unsigned PowerOfTwo);
	unsigned	ReverseBits				(unsigned index, unsigned NumBits);

	
	void		FillH0Array				(zREAL a, zVEC3 &wind);
	
	zComplex**	CreateArray				();
	void		FreeArray				(zComplex** array);
};

#endif