/******************************************************************************** 
 
     $Workfile:: oDamage.h            $                $Date:: 31.10.00 20:27   $
     $Revision:: 2                    $             $Modtime:: 31.10.00 18:43   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oDamage.h $
 * 
 * 2     31.10.00 20:27 Keskenti
 * 
 * 1     30.10.00 17:06 Keskenti
 * 
 *********************************************************************************/

#ifndef __ODAMAGE_H__
#define __ODAMAGE_H__

//
//	DAMAGE/PROTECTION ARRAY INDICES
//
typedef
enum	oEIndexDamage
{
	oEDamageIndex_Barrier				= 0									,
	oEDamageIndex_Blunt					/*= oEDamageIndex_Barrier	+ 1	*/	,
	oEDamageIndex_Edge					/*= oEDamageIndex_Blunt		+ 1	*/	,
	oEDamageIndex_Fire					/*= oEDamageIndex_Edge		+ 1	*/	,
	oEDamageIndex_Fly					/*= oEDamageIndex_Fire		+ 1	*/	,
	oEDamageIndex_Magic					/*= oEDamageIndex_Fly		+ 1	*/	,
	oEDamageIndex_Point					/*= oEDamageIndex_Magic		+ 1	*/	,
	oEDamageIndex_Fall					/*= oEDamageIndex_Point		+ 1	*/	,
	oEDamageIndex_MAX					/*= oEDamageIndex_Fall		+ 1	*/	,
}
oEDamageIndex, oEProtectionIndex;

//
//	DAMAGE TYPES						( !!! oEDamageType = 1 << oEDamageIndex !!! )		 
//
typedef
enum	oETypeDamage
{
	oEDamageType_Unknown				= 0									,
	oEDamageType_Barrier				= 1									,
	oEDamageType_Blunt					= oEDamageType_Barrier	<< 1		,
	oEDamageType_Edge					= oEDamageType_Blunt	<< 1		,
	oEDamageType_Fire					= oEDamageType_Edge		<< 1		,
	oEDamageType_Fly					= oEDamageType_Fire		<< 1		,
	oEDamageType_Magic					= oEDamageType_Fly		<< 1		,
	oEDamageType_Point					= oEDamageType_Magic	<< 1		,
	oEDamageType_Fall					= oEDamageType_Point	<< 1		,
	oEDamageType_ForceDWORD				= 0xffffffff				
}										
oEDamageType;

//										
//	WEAPON TYPES						
//										
typedef									
enum	oETypeWeapon					
{										
	oETypeWeapon_Unknown				= 0									,
	oETypeWeapon_Fist					= 1									,
	oETypeWeapon_Melee					= oETypeWeapon_Fist		<< 1		,
	oETypeWeapon_Range					= oETypeWeapon_Melee	<< 1		,
	oETypeWeapon_Magic					= oETypeWeapon_Range	<< 1		,
	oETypeWeapon_Special				= oETypeWeapon_Magic	<< 1		,
	oETypeWeapon_ForceDWORD				= 0xffffffff				
}										
oEWeaponType;

//										
//	ACTUAL DAMAGE/WEAPON BITFIELDS 						
//										
typedef	zDWORD oTModeDamage, oTDamageMode;
typedef	zDWORD oTModeWeapon, oTWeaponMode;

//
//	GLOBAL HELPER FUNCTIONS
//
void ApplyDamages( oTDamageMode damageTypes, int* damage, int &damageTotal );

//										
#endif
