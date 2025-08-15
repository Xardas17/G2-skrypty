/******************************************************************************** 
 
     $Workfile:: zgameinfo.h             $             $Date:: 4.12.00 18:22    $
     $Revision:: 8                       $          $Modtime:: 4.12.00 18:15    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   class handling informations about the running application
 
 * $Log: /current_work/ZenGin/_Bert/zgameinfo.h $
 * 
 * 8     4.12.00 18:22 Moos
 * 
 * 7     28.08.00 15:15 Speckels
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
 * 5     30.03.00 14:23 Speckels
 * 
 * 4     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 3     25.09.99 18:11 Speckels
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:15 $)

#ifndef __ZGAMEINFO_H__
#define __ZGAMEINFO_H__


const int zMAX_PLAYER = 20;

#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef __ZBUFFER_H__
#include "zbuffer.h"
#endif

#ifndef __ZVOB_H__
#include "zvob.h"
#endif

#ifndef __ZNET_WIN32_H__
#include "znet_win32.h"
#endif

class zCPlayerInfo;
class zCPlayerGroup;

const int zPCK_GAMEINFO_INFO = 1;
const int zPCK_GAMEINFO_PLAYER = 2;
const int zPCK_GAMEINFO_ALL = 255;

class zCGameInfo
{	
	
public:

							zCGameInfo();
	virtual					~zCGameInfo();

	virtual void			Init	();

	virtual void			Reset	();
	
	virtual void			SetName	(const zSTRING& _name)	{ name=_name; };			
	virtual zSTRING			GetName	() const				{ return name; };
	
	int						GetNumPlayers();
	virtual	zBOOL			AddPlayer(zCPlayerInfo* player);	
	virtual	zBOOL			RemPlayer(zCPlayerInfo* player);	
	virtual	zCPlayerInfo*	GetPlayerByID(int num);
	virtual zCPlayerInfo*	GetPlayerByVobID(zTVobID vobID);
	virtual zCPlayerInfo*	GetPlayerByNetAddress(zTNetAddress& adr);
	
	void					PackToBuffer(zCBuffer& buffer, zBYTE flag = zPCK_GAMEINFO_ALL);
	static zCGameInfo*		CreateFromBuffer(zCBuffer& buffer);
	
protected:
	
	virtual void			Pack(zCBuffer& buffer, zBYTE flag);
	virtual void			Unpack(zCBuffer& buffer);

private:	

	zSTRING name;
	
	zCGameInfo(zCGameInfo&);
	zCGameInfo& operator=(zCGameInfo&);

};


#endif