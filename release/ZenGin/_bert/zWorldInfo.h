/******************************************************************************** 
 
     $Workfile:: zworldinfo.h         $                $Date:: 4.12.00 18:23    $
     $Revision:: 8                    $             $Modtime:: 4.12.00 17:59    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log:: /current_work/ZenGin/_Bert/zworld $
 * 
 * 8     4.12.00 18:23 Moos
 * 
 * 7     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:48 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 3     5.05.00 13:46 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 6     17.04.00 17:13 Speckels
 * 
 * 4     27.03.00 21:46 Speckels
 * 
 * 1     7.02.00 18:00 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 4.12.00 17:59 $)


#ifndef __ZWORLDINFO_H__
#define __ZWORLDINFO_H__

#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zcontainer.h"
#endif

#ifndef __ZPLAYERINFO_H__
#include "zplayerinfo.h"
#endif

class zCWorld;
class zCPlayerGroup;

///
// network-informations about a level
///

class zCWorldInfo
{
public:
	zCWorldInfo(const zSTRING& _name);
	virtual ~zCWorldInfo();
	
	zSTRING			GetName();			/// get the name of the world (levelname)
	zCPlayerGroup*	GetPlayerGroup();	/// get the group of players in the world	
	zCPlayerInfo*	GetLevelMaster();	/// get the levelmaster
		
	void	EnterWorld(zCPlayerInfo* player);	// a player enters this world	
	void	LeaveWorld(zCPlayerInfo* player);	// a player leaves the world
	
	zBOOL	IsMember(zCPlayerInfo* levelMaster);	/// checking if the player is a member of the world	

	void	SetIsRunning(zBOOL running = TRUE)	{ isRunning = running; };
	zBOOL	IsRunning()							{ return isRunning; };

	void	ShowDebugInfo();

private:	

	zBOOL					isRunning;
	zSTRING					name;				/// name if the world (levelname)
	zCPlayerGroup*			playerGroup_Level;	/// group of all players in the world
	zCList<zCPlayerInfo>	historyList;		/// list of players, previously visited the world

};


#endif
