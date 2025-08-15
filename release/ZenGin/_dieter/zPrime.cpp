/******************************************************************************** 
 
     $Workfile:: zPrime.cpp     $                $Date:: 12.12.00 9:09    $
     $Revision:: 1                $             $Modtime:: 11.12.00 14:44   $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Tools for prime numbers
   created: 8.12.2000

 * $Log: /current_work/ZenGin/_dieter/zPrime.cpp $
 * 
 * 1     12.12.00 9:09 Moos
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 11.12.00 14:44 $)


#include "zPrime.h"
#include "zError.h"

// number of 16 bit primes (-1)
#define zSMALLPRIME_MAX_INDEX 6541
 

static zUINT16 SmallPrimes[zSMALLPRIME_MAX_INDEX+100];
static zUINT16 SmallPrime_Current_Index=0;

// give the prime table a start
inline void Startup(){
    if (SmallPrime_Current_Index==0){
        SmallPrime_Current_Index=1;
        SmallPrimes[0]=2;
    }
}

// square
inline zUINT32 Square(zUINT16 x){return x*x;}

zBOOL zCPrime::IsPrime(zUINT32 X){
    if (X<=1)
        return FALSE;

    // see if X is a multiple of any of the known primes smaller than sqrt(x):
    for (zUINT16 i=0;Square(PrimeNo(i)) <= X;i++)
        if (X % SmallPrimes[i] == 0) // it can be divided!
            return FALSE;

    // no divisor found. X is prime.
    return TRUE;
}


zUINT16 zCPrime::PrimeNo(zUINT16 index){
    zERR_ASSERT(index<=zSMALLPRIME_MAX_INDEX);

    if (index>=SmallPrime_Current_Index){
        // we need to calculate more primes!
        // TODO: better algorithm. Right now, we check every number separately.
        Startup();
        
        zUINT16 X=SmallPrimes[SmallPrime_Current_Index-1]+1; // check later if X is prime.
        while(index>=SmallPrime_Current_Index && X < (1<<16)){
            if (IsPrime(X)){ // found one. Add it to the array:
                SmallPrimes[SmallPrime_Current_Index]=(zUINT16)X;
                SmallPrime_Current_Index++;
            }
            X++; // look further.
        }
    }

    
    zERR_ASSERT(index<SmallPrime_Current_Index);

    return SmallPrimes[index];
}

zUINT32 zCPrime::NextPrime(zUINT32 min){
    // TODO: better algorithm!

    while(!IsPrime(min) && (min+1)!=0)
        min++;
    zERR_ASSERT(min+1 != 0);

    return min;
}
