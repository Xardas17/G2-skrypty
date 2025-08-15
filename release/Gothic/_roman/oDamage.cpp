/******************************************************************************** 
 
     $Workfile:: oDamage.cpp          $                $Date:: 9.01.01 13:20    $
     $Revision:: 4                    $             $Modtime:: 9.01.01 13:04    $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oDamage.cpp $
 * 
 * 4     9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 3     20.12.00 15:42 Speckels
 * 
 * 2     31.10.00 20:27 Keskenti
 * 
 * 1     31.10.00 18:44 Keskenti
 * 
 * 1     30.10.00 17:06 Keskenti
 * 
 *********************************************************************************/

#include <zCore.h>
#include <oDamage.h>

//
//	GLOBAL HELPER FUNCTIONS
//
void ApplyDamages( oTDamageMode damageTypes, int* damage, int &damageTotal ) 
{
	if (damageTypes == oEDamageType_Unknown) return;
	
	zBOOL bBarrier	= ( ( damageTypes & oEDamageType_Barrier ) == oEDamageType_Barrier	);
	zBOOL bBlunt	= ( ( damageTypes & oEDamageType_Blunt	 ) == oEDamageType_Blunt	);
	zBOOL bEdge		= ( ( damageTypes & oEDamageType_Edge	 ) == oEDamageType_Edge		);
	zBOOL bFire		= ( ( damageTypes & oEDamageType_Fire	 ) == oEDamageType_Fire		);
	zBOOL bFly		= ( ( damageTypes & oEDamageType_Fly	 ) == oEDamageType_Fly		);
	zBOOL bMagic	= ( ( damageTypes & oEDamageType_Magic	 ) == oEDamageType_Magic	);
	zBOOL bPoint	= ( ( damageTypes & oEDamageType_Point	 ) == oEDamageType_Point	);
	zBOOL bFall		= ( ( damageTypes & oEDamageType_Fall	 ) == oEDamageType_Fall		);

	zREAL fDivisor = 0.0f;
	if ( bBarrier	) fDivisor += 1.0f;
	if ( bBlunt		) fDivisor += 1.0f;
	if ( bEdge		) fDivisor += 1.0f;
	if ( bFire		) fDivisor += 1.0f;
	if ( bFly		) fDivisor += 1.0f;
	if ( bMagic		) fDivisor += 1.0f;
	if ( bPoint		) fDivisor += 1.0f;
	if ( bFall		) fDivisor += 1.0f;
	
	if (fDivisor<=0) 
	{
		zERR_FAULT("U: Dam: Invalid damage-type.");
	}
	else
	{
		zREAL	fDamageEven = ( (zREAL) damageTotal ) / fDivisor;
		int		nDamageEven	= (int)	( fDamageEven + 0.5f );

		if ( bBarrier	& ( damage[ oEDamageIndex_Barrier	] == 0 ) ) damage[ oEDamageIndex_Barrier ] = nDamageEven;
		if ( bBlunt		& ( damage[ oEDamageIndex_Blunt		] == 0 ) ) damage[ oEDamageIndex_Blunt	 ] = nDamageEven;
		if ( bEdge		& ( damage[ oEDamageIndex_Edge		] == 0 ) ) damage[ oEDamageIndex_Edge	 ] = nDamageEven;
		if ( bFire		& ( damage[ oEDamageIndex_Fire		] == 0 ) ) damage[ oEDamageIndex_Fire	 ] = nDamageEven;
		if ( bFly		& ( damage[ oEDamageIndex_Fly		] == 0 ) ) damage[ oEDamageIndex_Fly	 ] = nDamageEven;
		if ( bMagic		& ( damage[ oEDamageIndex_Magic		] == 0 ) ) damage[ oEDamageIndex_Magic	 ] = nDamageEven;
		if ( bPoint		& ( damage[ oEDamageIndex_Point		] == 0 ) ) damage[ oEDamageIndex_Point	 ] = nDamageEven;
		if ( bFall		& ( damage[ oEDamageIndex_Fall		] == 0 ) ) damage[ oEDamageIndex_Fall	 ] = nDamageEven;
	}
}
