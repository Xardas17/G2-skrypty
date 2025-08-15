/******************************************************************************** 
 
     $Workfile:: oplayerinfo.h        $                $Date:: 26.01.01 16:21   $
     $Revision:: 8                    $             $Modtime:: 26.01.01 16:17   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oplayerinfo.h $
 * 
 * 8     26.01.01 16:21 Moos
 * 
 * 7     20.09.00 21:32 Rueve
 * 
 * 6     28.08.00 14:31 Speckels
 * 
 * 17    23.08.00 21:46 Admin
 * 
 * 4     21.08.00 18:47 Speckels
 * 
 * 15    16.08.00 12:32 Admin
 * 
 * 3     10.08.00 21:46 Speckels
 * 
 * 14    9.08.00 17:11 Admin
 * 
 * 2     26.04.00 11:28 Admin
 * 
 * 2     19.04.00 18:36 Speckels
 * 
 * 3     30.03.00 14:23 Speckels
 * 
 * 8     7.02.00 17:58 Speckels
 * 
 * 7     2.12.99 22:52 Speckels
 * release-candidate stage object-interaction
 * 
 * 6     21.10.99 23:42 Speckels
 * Changes for item-interaction and error-handling
 * 
 * 5     27.09.99 16:29 Speckels
 * Aktualisierungen fuer SourceSafe
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 26.01.01 16:17 $)


#ifndef __OPLAYERINFO_H__
#define __OPLAYERINFO_H__


#include "zstring.h"
#include "zbuffer.h"
#include "zplayerinfo.h"


/*************************************************************/
/* Player-Instances ******************************************/
/*************************************************************/

const int MAX_PLAYER_INSTANCES = 5;

enum TPlayerInstance
{	
	PC_UNKNOWN,
	PC_HERO,
	PC_FIGHTER,
	PC_THIEF,
	PC_MAGE,
	PC_PSIONIC
};

extern const zSTRING PLAYER_INSTANCE[MAX_PLAYER_INSTANCES+1];

extern const zSTRING PLAYER_INSTANCE_NAME[MAX_PLAYER_INSTANCES+1];


/*************************************************************/
/* oCPlayerInfo ***********************************************/
/*************************************************************/

class oCPlayerInfo : public zCPlayerInfo
{
public:		

	oCPlayerInfo						();
	virtual ~oCPlayerInfo				();	

	virtual void	Init				(const zSTRING& _name=zSTR_EMPTY, const zSTRING& _addr=zSTR_EMPTY);
	virtual void	Reset();

	virtual void	SetInstance			(const TPlayerInstance _instance);
	virtual void	SetInstanceByName	(const zSTRING& _instanceName);

	TPlayerInstance GetInstance			() const;
	zSTRING			GetInstanceName		() const;

protected:

	virtual	void	Pack				(zCBuffer& buffer);
	virtual	void	Unpack				(zCBuffer& buffer);

private:

	TPlayerInstance	instance;
};

typedef oCPlayerInfo* CPlayerInfoPtr;

#endif
