/******************************************************************************** 
 
     $Workfile:: oplayerinfo.cpp      $                $Date:: 26.01.01 16:21   $
     $Revision:: 8                    $             $Modtime:: 26.01.01 16:16   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oplayerinfo.cpp $
 * 
 * 8     26.01.01 16:21 Moos
 * 
 * 7     28.08.00 14:31 Speckels
 * 
 * 17    23.08.00 21:46 Admin
 * 
 * 5     21.08.00 18:47 Speckels
 * 
 * 15    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:46 Speckels
 * 
 * 14    9.08.00 17:11 Admin
 * 
 * 3     21.07.00 15:16 Speckels
 * 
 * 2     26.04.00 11:28 Admin
 * 
 * 2     19.04.00 18:36 Speckels
 * 
 * 3     30.03.00 14:23 Speckels
 * 
 * 4     7.02.00 17:58 Speckels
 * 
 * 3     21.10.99 23:42 Speckels
 * Changes for item-interaction and error-handling
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 26.01.01 16:16 $)



#include "zcore.h"
#include "zoption.h"

#include "oplayerinfo.h"
#include "onpc.h"


const zSTRING PLAYER_INSTANCE[MAX_PLAYER_INSTANCES+1] =
{
		"-",
		"PC_HERO",
		"PC_FIGHTER",
		"PC_THIEF",
		"PC_MAGE",
		"PC_PSIONIC"
};

const zSTRING PLAYER_INSTANCE_NAME[MAX_PLAYER_INSTANCES+1] =
{
		"-",
		"Hero",
		"Fighter",
		"Thief",
		"Mage",
		"Psionic"
};

///////////////////////////////////////////////////////////////////////
// PLAYER-Informations
///////////////////////////////////////////////////////////////////////

oCPlayerInfo::oCPlayerInfo()
{	
	instance = PC_HERO;	
};

void oCPlayerInfo::Init(const zSTRING& _name, const zSTRING& _addr)
{	
	zCPlayerInfo::Init(_name, _addr);
};

oCPlayerInfo::~oCPlayerInfo()
{	
};

void oCPlayerInfo::SetInstance(const TPlayerInstance _instance) 
{ 
	instance = _instance; 	
};

void oCPlayerInfo::SetInstanceByName(const zSTRING& _instanceName) 
{ 	
	for (int i=0;i<=MAX_PLAYER_INSTANCES;i++)
	{
		if (_instanceName == PLAYER_INSTANCE[i]) 
		{ 
			SetInstance((TPlayerInstance)i);
			return;
		};
	};
	zERR_WARNING("B: (oCPlayerInfo::SetInstanceByName) Could not find instance with name "+_instanceName);
	SetInstance(PC_UNKNOWN);
};

zSTRING oCPlayerInfo::GetInstanceName() const
{
	return PLAYER_INSTANCE[instance];
};

TPlayerInstance oCPlayerInfo::GetInstance() const	
{ 
	return instance; 
}	

void oCPlayerInfo::Pack(zCBuffer& buffer)
{
	zCPlayerInfo::Pack(buffer);
	buffer.Write(&instance,sizeof(instance));	
};

void oCPlayerInfo::Unpack(zCBuffer& buffer)
{
	zCPlayerInfo::Unpack(buffer);	
	buffer.Read(&instance,sizeof(instance));		
};

void oCPlayerInfo::Reset()
{
	zCPlayerInfo::Reset();
};
