/******************************************************************************** 
 
     $Workfile:: zplayergroup.h      $                 $Date:: 4.12.00 18:22    $
     $Revision:: 9                   $              $Modtime:: 4.12.00 18:05    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   A player-group is representing a collection of null, one or more players
  
 * $Log: /current_work/ZenGin/_Bert/zplayergroup.h $
 * 
 * 9     4.12.00 18:22 Moos
 * 
 * 8     29.08.00 17:48 Moos
 * 
 * 7     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 4     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 3     21.10.99 23:29 Speckels
 * Work on error-handling and
 * item-interaction
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 9 $ ($Modtime: 4.12.00 18:05 $)


#ifndef __ZPLAYERGROUP_H__
#define __ZPLAYERGROUP_H__

#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif

#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zcontainer.h"
#endif

#ifndef __ZLIST_H__
#include "zlist.h"
#endif

class zCPlayerInfo;
class zCVob;

/** A player-group is representing a collection of null, one or more players (especially for a network-game)
  * Players can be added to any group. They will be included into an internal list. Methods will allow then to iterate through all members of the group or check if a special players is a member.
  * You can create new groups by simply creationg an object of zCPlayerGroup. It will automaticly inserted in the internal list of player-groups. The group will be removed from the list by deletion. There are also methods to iterate trough all existing groups. 
  *
  * @see zCPlayerInfo
  */

class zCPlayerGroup
{	
public:
	
	static zCPlayerGroup*	GetAllPlayerGroup()						{ return &allPlayerGroup;  };	

	//
	// construction and deconstruction
	//


	/// construction
	zCPlayerGroup(const zSTRING& _name);

	/// destruction
	virtual ~zCPlayerGroup();


	//
	// these methos manipulate and analyse the list of groups
	//

		
	/// search for a group with the given name
	static zCPlayerGroup* GetGroupByName(const zSTRING& _name);

	/// retrieve first group in list (last inserted)
	static zCPlayerGroup* GetFirstGroup(int& iter);

	/// retrieve next group in list
	zCPlayerGroup* GetNextGroup(int& iter);

	/// Remove all groups 
	static void ResetGroupList();
	
    // Cleanup and init [Moos]
    static void Init();
    static void Cleanup();


	//
	// handling players in the group
	//

	
	void ResetPlayerList();			/// Remove all player from the list
	
	zWORD GetNumPlayers()			/// getting number of hosts in this group
			{ return player_list.GetNumInList(); }	
		
	zBOOL AddPlayer(zCPlayerInfo* player);	/// Adding a palyer to this group
	zBOOL RemPlayer(zCPlayerInfo* player);	/// Removing a player from this group	

	zCPlayerInfo* GetFirstPlayer(int& iter);	/// Getting first player in this group	
	zCPlayerInfo* GetNextPlayer(int& iter);		/// Getting next player in this group
	zCPlayerInfo* GetPlayerByID(zBYTE id);		/// Getting player by its id

	zBOOL IsMember(zCPlayerInfo* player);	/// Asking if the player is in the group
		
	const zSTRING& GetName()				/// getting name of this group
			{ return name; }	

	void ShowDebugInfo();

	// check the distance of a player to the given vob and return the nearest one
	zCPlayerInfo* GetNearestPlayerToVob(zCVob* vob, zCPlayerInfo* excludedPlayer=0);
	
protected:		

	void AddGroupToList();

	void RemoveGroupFromList();	

private:	

	static zCPlayerGroup			allPlayerGroup;
	static zCList<zCPlayerGroup>	group_list;
	
	zSTRING						name;
	zCListSort<zCPlayerInfo>	player_list;	

	zCPlayerGroup();
	zCPlayerGroup(zCPlayerGroup&);
	zCPlayerGroup& operator=(zCPlayerGroup&);

};

typedef zCPlayerGroup* zCPlayerGroupPtr;


// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
// END OF znethost.h
// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////

#endif