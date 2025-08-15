/******************************************************************************** 
 
     $Workfile:: zPrime.h      $                $Date:: 12.12.00 9:09    $
     $Revision:: 1                $             $Modtime:: 8.12.00 14:32    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Tools for prime numbers
   created: 8.12.2000

 * $Log: /current_work/ZenGin/_dieter/zPrime.h $
 * 
 * 1     12.12.00 9:09 Moos
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 8.12.00 14:32 $)


#ifndef __ZPRIME_H__
#define __ZPRIME_H__

#ifndef __ZTYPES_H__
#include "zTypes.h"
#endif

// utility functions for small primes (for hash tables)
class zCPrime{
public:
    // first, we want a way to get ALL 16bit prime numbers by their index: (starting wirh Prime_No(0)=2)
    static zUINT16 PrimeNo(zUINT16 index); 

    // then, we want a prime check for every 32bit number:
    static zBOOL IsPrime(zUINT32 test);

    // and a way to get the next bigger prime for every 32bit number:
    static zUINT32 NextPrime(zUINT32 min);
};

#endif