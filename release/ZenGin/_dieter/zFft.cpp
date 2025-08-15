// FFT.cpp: Implementierung der Klasse zCFFT.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include "zFFT.h"
#include "zalgebra.h"

// disable VC++ Warning: zREAL to zREAL conversion
#pragma warning( disable : 4244 ) 



//////////////////////////////////////////////////////////////////////

#define MAKE_WAVE(m,n) (zVEC3( (2.0f * M_PI * (zREAL)m / (fftMapRes) ), 0.01f, (2.0f * M_PI * (zREAL)n / (fftMapRes)) ))
#define GetMap( map, x, z) &map[x&(fftMapRes-1)][z&(fftMapRes-1)]
#define	DDC_PI		   (3.14159265358979323846)

const zREAL EULER					= 2.71828f;
const zREAL SQRT2					= 1.414213562f;

const float TIMESCALE_FFT_SLOW		= 0.2f;
const float TIMESCALE_FFT_NORMAL	= 0.5f;
const float TIMESCALE_FFT_FAST		= 2.0f;


const unsigned int fftMapRes		= 32;

zCFFT zCFFT::s_fft;
zCFFT zCFFT::s_fftSlow;
zCFFT zCFFT::s_fftFast;

// statics 
zREAL zCFFT::S_CalcWave2D(const zREAL x, const zREAL z, const zREAL tileSize, const zTFFT fftType )
{
	const zREAL MAG_SCALE = 10000000.0f;
	switch (fftType)
	{
	case zTFFT_SLOW:
		{
			zComplex c = s_fftSlow.GetWaveHeight(x,z,tileSize);
			return zSinApprox ( c.Phase() +  (c.Mag() * MAG_SCALE) );
		}
	case zTFFT_NORMAL:
		{
			zComplex c = s_fft.GetWaveHeight(x,z,tileSize);
			return zSinApprox ( c.Phase() +  (c.Mag() * MAG_SCALE) );
		}
	case zTFFT_FAST:
		{
			zComplex c = s_fftFast.GetWaveHeight(x,z,tileSize);
			return zSinApprox ( c.Phase() +  (c.Mag() * MAG_SCALE) );
		}
	default:
		{
			zComplex c = s_fft.GetWaveHeight(x,z,tileSize);
			return zSinApprox ( c.Phase() +  (c.Mag() * MAG_SCALE) );
		}
	}
}

void zCFFT::S_Init		()
{
	zVEC3 flowVec(1.0f,0,0);

	s_fft    .SetSpeed(TIMESCALE_FFT_NORMAL);
	s_fftSlow.SetSpeed(TIMESCALE_FFT_SLOW  );
	s_fftFast.SetSpeed(TIMESCALE_FFT_FAST  );

	s_fft    .CreateWaveMap(1.0f, flowVec);
	s_fftSlow.CreateWaveMap(1.0f, flowVec);
	s_fftFast.CreateWaveMap(1.0f, flowVec);
};

void  zCFFT::S_SetFrameCtr(const zTFrameCtr a_iFCount)
{
	s_fft	 .SetFrameCtr(a_iFCount);
	s_fftSlow.SetFrameCtr(a_iFCount);
	s_fftFast.SetFrameCtr(a_iFCount);
};


void zCFFT::S_AnimateWaveMap(zREAL time)
{
	s_fftSlow.AnimateWaveMap( time * TIMESCALE_FFT_SLOW   );
	s_fft	 .AnimateWaveMap( time * TIMESCALE_FFT_NORMAL );
	s_fftFast.AnimateWaveMap( time * TIMESCALE_FFT_FAST	  );
}


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

zCFFT::zCFFT()
{
	m_h0Map				= NULL;
	
	m_WaveMap			= NULL;
	
	m_IWaveMap			= NULL;
	
	frameCtr			= 0;
	frameCtrLastUsed	= -1;
	fftSpeed			= 1.0f;

}

zCFFT::~zCFFT()
{
	FreeArray( m_h0Map );
	
	FreeArray( m_WaveMap );
	
	FreeArray( m_IWaveMap );

	
}

zREAL zCFFT::CalcWave2D(const zREAL x, const zREAL z, const zREAL tileSize )
{
	const zREAL MAG_SCALE = 10000000.0f;
	zComplex c = GetWaveHeight(x,z,tileSize);
	return zSinApprox ( c.Phase() +  (c.Mag() * MAG_SCALE) );
}


void zCFFT::fft_float (unsigned NumSamples, int InverseTransform, zComplex *In, zComplex *Out)
{
	const    zREAL DCCF_PI	= zREAL(DDC_PI);
    unsigned NumBits;    /* Number of bits needed to store indices */
    unsigned i, j, k, n;
    unsigned BlockSize, BlockEnd;
	

    zREAL angle_numerator = 2.0f * zREAL(DCCF_PI);
    zREAL tr, ti;     /* temp real, temp imaginary */

    if ( !IsPowerOfTwo(NumSamples) )
    {
		return;
    }

    if ( InverseTransform )
        angle_numerator = -angle_numerator;

	if ( !In || !Out )
		return;

    NumBits = NumberOfBitsNeeded ( NumSamples );

    /*
    **   Do simultaneous data copy and bit-reversal ordering into outputs...
    */

    for ( i=0; i < NumSamples; i++ )
    {
        j = ReverseBits ( i, NumBits );
        Out[j].real = In[i].real;
        Out[j].img  = In[i].img;
    }

    /*
    **   Do the FFT itself...
    */

    BlockEnd = 1;
	zREAL sm1, sm2, cm1, cm2;
    for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
    {
        zREAL delta_angle = angle_numerator / (zREAL)BlockSize;

		zSinCos( -2 * delta_angle, sm2, cm2 );
		zSinCos( -delta_angle, sm1, cm1 );

        zREAL w = 2 * cm1;
        zREAL ar[3], ai[3];

        for ( i=0; i < NumSamples; i += BlockSize )
        {
            ar[2] = cm2;
            ar[1] = cm1;

            ai[2] = sm2;
            ai[1] = sm1;

            for ( j=i, n=0; n < BlockEnd; j++, n++ )
            {
                ar[0] = w*ar[1] - ar[2];
                ar[2] = ar[1];
                ar[1] = ar[0];

                ai[0] = w*ai[1] - ai[2];
                ai[2] = ai[1];
                ai[1] = ai[0];

                k = j + BlockEnd;
                tr = ar[0]*Out[k].real - ai[0]*Out[k].img;
                ti = ar[0]*Out[k].img + ai[0]*Out[k].real;

                Out[k].real = Out[j].real - (zREAL)tr;
                Out[k].img = Out[j].img - (zREAL)ti;

                Out[j].real += (zREAL)tr;
                Out[j].img += (zREAL)ti;
            }
        }

        BlockEnd = BlockSize;
    }

    /*
    **   Need to normalize if inverse transform...
    */

    if ( InverseTransform )
    {
        const zREAL denomInv = 1.0f/NumSamples;

        for ( i=0; i < NumSamples; i++ )
        {
            Out[i].real *= denomInv;
            Out[i].img  *= denomInv;
        }
    }
}


int zCFFT::IsPowerOfTwo ( unsigned x )
{
    if ( x < 2 )
        return FALSE;

    if ( x & (x-1) )        // Thanks to 'byang' for this cute trick!
        return FALSE;

    return TRUE;
}


unsigned zCFFT::NumberOfBitsNeeded ( unsigned PowerOfTwo )
{
    unsigned i;

    if ( PowerOfTwo < 2 )
    {
        fprintf (
            stderr,
            ">>> Error in fftmisc.c: argument %d to NumberOfBitsNeeded is too small.\n",
            PowerOfTwo );

        exit(1);
    }

    for ( i=0; ; i++ )
    {
        if ( PowerOfTwo & (1 << i) )
            return i;
    }
}



unsigned zCFFT::ReverseBits ( unsigned index, unsigned NumBits )
{
    unsigned i, rev;

    for ( i=rev=0; i < NumBits; i++ )
    {
        rev = (rev << 1) | (index & 1);
        index >>= 1;
    }

    return rev;
}


zREAL zCFFT::Index_to_frequency ( unsigned NumSamples, unsigned Index )
{
    if ( Index >= NumSamples )
        return 0.0;
    else if ( Index <= NumSamples/2 )
        return (zREAL)Index / (zREAL)NumSamples;

    return -(zREAL)(NumSamples-Index) / (zREAL)NumSamples;
}


void zCFFT::CreateWaveMap(zREAL a, zVEC3 &w)
{
	m_h0Map		= CreateArray();
	m_IWaveMap	= CreateArray();
	m_WaveMap	= CreateArray();

	FillH0Array( a, w );
}


void zCFFT::FillH0Array(zREAL a, zVEC3 &wind)
{
	zREAL		w, l;

	// Prepare Gauss
	zRandom_Gauss *gauss = new zRandom_Gauss(0,100);

	w = wind.Length();

	l = (w * w) / 9.81f;

	for (int z=0; z < fftMapRes; z++)
	{
		for (int x=0; x < fftMapRes; x++)
		{
			zVEC3		vec3, wave;
			zREAL		eulerterm, dotprod, sPhK, k, k4, elim;
			int			kx, kz;
	
			
			kx			= x - (fftMapRes>>1);
			kz			= z - (fftMapRes>>1);

			
			wave		= MAKE_WAVE( kx, kz );

			k			= wave.Length();
			
			
			eulerterm	= pow( EULER, ( -1.0f / (k*l*k*l) ) );
			
			
			k4			= k * k * k * k;
			
			
			dotprod		= wave.Normalize() * wind.Normalize();
			dotprod		*= dotprod;

			elim		= pow( EULER, ( -(k*k)*(w*w) ) );
			
			sPhK		= sqrt( a * (eulerterm / k4) * dotprod * elim);			

			m_h0Map[z][x].real = 1.0f / SQRT2 * (zREAL)( gauss->GetGaussian() * sPhK);
			m_h0Map[z][x].img  = 0.0f;
		}
	}

	if (gauss)
		delete gauss;
}

void zCFFT::AnimateWaveMap(zREAL time)
{
	time *= fftSpeed;

	zVEC3			wave;
	zComplex		p, q, *r, *s;
	zREAL			k,
					wkt;
	int				kx, kz;

	for ( int z = 0; z < fftMapRes; z++)
	{
		for ( int x = 0; x < fftMapRes; x++)
		{

			kx = x - (fftMapRes>>1);
			kz = z - (fftMapRes>>1);

			wave	= MAKE_WAVE( kx, kz );

			k		= wave.LengthApprox();
			
			wkt		= (zREAL)Alg_SqrtApprox( 9.81f * k) * time;

			// ACHTUNG: Approx SinCos führt nach einiger Zeit zu Problemen (Ruckelndes Wasser etc.)
			zSinCos(wkt, p.img, p.real);
			zSinCos(-wkt, q.img, q.real);
			
			
			r		= GetMap( m_h0Map, x, z );
			s		= GetMap( m_h0Map, -x, -z);
			
			s->img	*= -1.0f;

			zComplex d	= (*r * p) + (*s * q);

			m_WaveMap[z][x].Set( d.real, d.img);
		}

		fft_float( fftMapRes, 1, m_WaveMap[z], m_IWaveMap[z] );
	
	}
}


void  zCFFT::SetFrameCtr(const zTFrameCtr a_iFCount)
{
	this->frameCtr = a_iFCount;
};

void  zCFFT::SetSpeed(const zREAL a_fSpeed)
{
	this->fftSpeed = a_fSpeed;
};


zComplex& zCFFT::GetWaveHeight( const int ix, const int iz ) 
{
	if (frameCtr != frameCtrLastUsed)
	{
		AnimateWaveMap(ztimer.GetTotalTimeF()/1000.0f);
		frameCtrLastUsed = frameCtr;
	}

	return (*GetMap( m_IWaveMap, ix, iz) );
}

zComplex& zCFFT::GetWaveHeight( const zREAL x, const zREAL z, const zREAL tileSize ) 
{
	static zREAL ooTileSize  = -1;
	static zREAL lastTileSize = -1;

	if (frameCtr != frameCtrLastUsed)
	{
		AnimateWaveMap(ztimer.GetTotalTimeF()/1000.0f);
		frameCtrLastUsed = frameCtr;
	}

	zERR_ASSERT(tileSize>0);

	if (tileSize != lastTileSize)
	{
		ooTileSize	= 1.0f/tileSize;
		lastTileSize= tileSize;
	}
	return(  *GetMap( m_IWaveMap, 
					 (int)((x * ooTileSize) + 0.5f) , 
					 (int)((z * ooTileSize) + 0.5f) )  );			

}

zComplex& zCFFT::GetWaveHeightSmooth( const zREAL x, const zREAL z, const zREAL tileSize ) 
{
	if (frameCtr != frameCtrLastUsed)
	{
		AnimateWaveMap(ztimer.GetTotalTimeF()/1000.0f);
		frameCtrLastUsed = frameCtr;
	}

	// slow bilinear interpolated
	static zComplex wave;

	zREAL rh = 1.0f / tileSize;

	zREAL u = (x + 0.5f * fftMapRes) * rh;
	zREAL v = (z + 0.5f * fftMapRes) * rh;

	int i = (int)(u);
	int j = (int)(v);

	zREAL a = u - i;
	zREAL b = v - j;
	zREAL ab = a*b;

	zComplex *m1,*m2,*m3,*m4;

	m1 = GetMap( m_IWaveMap,	i,		j);
	m2 = GetMap( m_IWaveMap,	i,		j+1);
	m3 = GetMap( m_IWaveMap,	i+1,	j);
	m4 = GetMap( m_IWaveMap,	i+1,	j+1);

	wave.real	= (1.0f-a-b+ab) * m1->real + (b-ab) * m2->real + (a-ab) * m3->real + ab * m4->real;
	wave.img	= (1.0f-a-b+ab) * m1->img + (b-ab) * m2->img + (a-ab) * m3->img + ab * m4->img;

	return (wave);
}


zComplex** zCFFT::CreateArray()
{
	zComplex** array = NULL;

	array = new zComplex*[fftMapRes];
	if (array)
	{
		for (int i=0; i < fftMapRes; i++)
		{
			array[i] = new zComplex[fftMapRes];
			if (!array[i])
			{
				FreeArray(array);
				return (NULL);
			}
		}
	}
	return (array);
}

void zCFFT::FreeArray(zComplex** array)
{
	if (array)
	{
		for (int i=0; i < fftMapRes; i++)
		{
			if (array[i])
			{
				delete [] array[i];
				array[i] = NULL;
			}
		}
		delete [] array;
		array = NULL;
	}
}

/*
   This is the initialization routine for the random number generator.
   NOTE: The seed variables can have values between:    0 <= IJ <= 31328
                                                        0 <= KL <= 30081
   The random number sequences created by these two seeds are of sufficient
   length to complete an entire calculation with. For example, if sveral
   different groups are working on different parts of the same calculation,
   each group could be assigned its own IJ seed. This would leave each group
   with 30000 choices for the second seed. That is to say, this random
   number generator can create 900 million different subsequences -- with
   each subsequence having a length of approximately 10^30.
*/
zRandom_Gauss::zRandom_Gauss(int ij, int kl)
{
   u = new zREAL[97];

   zREAL s,t;
   int ii,i,j,k,l,jj,m;

   /*
	  Handle the seed range errors
		 First random number seed must be between 0 and 31328
		 Second seed must have a value between 0 and 30081
   */
   if (ij < 0 || ij > 31328 || kl < 0 || kl > 30081) {
		ij = 1802;
		kl = 9373;
   }

   i = (ij / 177) % 177 + 2;
   j = (ij % 177)       + 2;
   k = (kl / 169) % 178 + 1;
   l = (kl % 169);

   for (ii=0; ii<97; ii++) {
	  s = 0.0;
	  t = 0.5;
	  for (jj=0; jj<24; jj++) {
		 m = (((i * j) % 179) * k) % 179;
		 i = j;
		 j = k;
		 k = m;
		 l = (53 * l + 1) % 169;
		 if (((l * m % 64)) >= 32)
			s += t;
		 t *= 0.5;
	  }
	  u[ii] = s;
   }

   c    = 362436.0 / 16777216.0;
   cd   = 7654321.0 / 16777216.0;
   cm   = 16777213.0 / 16777216.0;
   i97  = 97;
   j97  = 33;

   m_gaussCall = 0;
}


zRandom_Gauss::~zRandom_Gauss()
{
	if (u)
	{
		delete u;
	}
}

/* 
   This is the random number generator proposed by George Marsaglia in
   Florida State University Report: FSU-SCRI-87-50
*/
zREAL zRandom_Gauss::RandomUniform()
{
   zREAL uni;

   uni = u[i97-1] - u[j97-1];
   if (uni <= 0.0)
      uni++;
   u[i97-1] = uni;
   i97--;
   if (i97 == 0)
      i97 = 97;
   j97--;
   if (j97 == 0)
      j97 = 97;
   c -= cd;
   if (c < 0.0)
      c += cm;
   uni -= c;
   if (uni < 0.0)
      uni++;

   return(uni);
}

/*
  ALGORITHM 712, COLLECTED ALGORITHMS FROM ACM.
  THIS WORK PUBLISHED IN TRANSACTIONS ON MATHEMATICAL SOFTWARE,
  VOL. 18, NO. 4, DECEMBER, 1992, PP. 434-435.
  The function returns a normally distributed pseudo-random number
  with a given mean and standard devaiation.  Calls are made to a
  function subprogram which must return independent random
  numbers uniform in the interval (0,1).
  The algorithm uses the ratio of uniforms method of A.J. Kinderman
  and J.F. Monahan augmented with quadratic bounding curves.
*/
zREAL zRandom_Gauss::GetGaussian(zREAL mean,zREAL stddev)
{
   zREAL  q,u,v,x,y;

	/*  
		Generate P = (u,v) uniform in rect. enclosing acceptance region 
      Make sure that any random numbers <= 0 are rejected, since
      gaussian() requires uniforms > 0, but RandomUniform() delivers >= 0.
	*/
   do {
      u = RandomUniform();
      v = RandomUniform();
   	if (u <= 0.0 || v <= 0.0) {
       	u = 1.0;
       	v = 1.0;
   	}
      v = 1.7156 * (v - 0.5);

      /*  Evaluate the quadratic form */
      x = u - 0.449871;
   	  y = fabs(v) + 0.386595;
      q = x * x + y * (0.19600 * y - 0.25472 * x);

      /* Accept P if inside inner ellipse */
      if (q < 0.27597)
			break;

      /*  Reject P if outside outer ellipse, or outside acceptance region */
    } while ((q > 0.27846) || (v * v > -4.0 * log(u) * u * u));

	m_gaussCall++;

    /*  Return ratio of P's coordinates as the normal deviate */
    return (mean + stddev * v / u);
}

/*
   Return random integer within a range, lower -> upper INCLUSIVE
*/
int zRandom_Gauss::GetInt(int lower,int upper)
{
   return((int)(RandomUniform() * (upper - lower + 1)) + lower);
}

/*
   Return random zREAL within a range, lower -> upper
*/
zREAL zRandom_Gauss::GetFloat(zREAL lower,zREAL upper)
{
   return((upper - lower) * RandomUniform() + lower);
}


void zRandom_Gauss::StepForward(long forward)
{
   zREAL uni;

   while (forward--) {
       uni = u[i97-1] - u[j97-1];
       if (uni <= 0.0)
          uni++;
       u[i97-1] = uni;
       i97--;
       if (i97 == 0)
          i97 = 97;
       j97--;
       if (j97 == 0)
          j97 = 97;
       c -= cd;
       if (c < 0.0)
          c += cm;
   }
}

/* 
   BackupRandomUniform()
   Backup in the random sequence 'backup' times.   
   by Stan Reckard  
*/
zREAL zRandom_Gauss::UnRandomUniform() 
{
   zREAL uni, uniAlt, prev;
   zREAL cTmp;

   if (c >= cm)
      c -= cm;

   c += cd;

   if (j97 == 97)
      j97 = 0;
   j97++;

   if (i97 == 97)
      i97 = 0;
   i97++;

   uni = u[i97-1];
   uniAlt = uni - 1;

   prev = uni + u[j97-1];
   if ((prev > 0.0F) && (prev < 1.0F))
      u[i97-1] = prev;
   else {
      u[i97-1] = uniAlt + u[j97-1];
   }
   /* RandomUniform() has been completely undone at this point.  */

   /*
      Now get the random# that was last retrieved to 
		return without altering the random sequence.
      uni holds old value of u[i97-1]
   */
   cTmp = c;
   cTmp -= cd;
   if (cTmp < 0.0F)
      cTmp += cm;
   uni -= cTmp;
   if (uni < 0.0F)  uni++;

   return uni;  /* prev random# returned */
}

void zRandom_Gauss::StepBack(long backup) 
{
   zREAL uni, uniAlt, prev;

   while (backup--) {
      if (c >= cm)
          c -= cm;

      c += cd;

      if (j97 == 97)
         j97 = 0;
      j97++;

      if (i97 == 97)
         i97 = 0;
      i97++;

      uni = u[i97-1];
      uniAlt = uni - 1;

      prev = uni + u[j97-1];
      if ((prev > 0.0F) && (prev < 1.0F))
         u[i97-1] = prev;
      else
         u[i97-1] = uniAlt + u[j97-1];;
   }
}

/* rand24()    24-bit precision   */
unsigned int zRandom_Gauss::rand24() 
{ 
   return (unsigned int)(RandomUniform() * 4096 * 4096); 
}

/* unRand24()    24-bit precision   */
unsigned int zRandom_Gauss::unRand24() 
{ 
   return (unsigned int)(UnRandomUniform() * 4096 * 4096); 
}

zREAL zRandom_Gauss::GetGaussAt( long index)
{
	long diff = m_gaussCall - index;

	if ( diff > 0)
	{
		StepForward(diff);
	}
	else
	{
		StepBack( abs(diff) );
	}

	return ( GetGaussian() );
}



// enable VC++ Warning: zREAL to zREAL conversion
#pragma warning( default: 4244 ) 
