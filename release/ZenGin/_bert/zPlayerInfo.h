/******************************************************************************** 
 
     $Workfile:: zplayerinfo.h       $                 $Date:: 4.12.00 18:22    $
     $Revision:: 8                   $              $Modtime:: 4.12.00 18:04    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   basic informations about a/the player in the application
  
 * $Log: /current_work/ZenGin/_Bert/zplayerinfo.h $
 * 
 * 8     4.12.00 18:22 Moos
 * 
 * 7     28.08.00 15:15 Speckels
 * 
 * 16    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 14    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:47 Speckels
 * 
 * 13    9.08.00 17:12 Admin
 * 
 * 3     5.05.00 13:46 Speckels
 * 
 * 4     3.05.00 19:14 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 6     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 5     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 4     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 3     21.10.99 23:27 Speckels
 * new pingmethods (moved from
 * netCPlayerInfo)
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:04 $)


#ifndef __ZPLAYERINFO_H__
#define __ZPLAYERINFO_H__


#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef __ZBUFFER_H__
#include "zbuffer.h"
#endif

#ifndef __ZNET_WIN32_H__
#include "znet_win32.h"
#endif

#ifndef __ZGAMEINFO_H__
#include "zgameinfo.h"
#endif


class zCNetHost;
class zCVob;
class zCWorldInfo;

/*************************************************************/
/* zCPlayerInfo ***********************************************/
/*************************************************************/



class zCPlayerInfo
{
	friend class zCGameInfo;
public:		

	static	zCPlayerInfo* GetActivePlayer();
	void	SetActive();
	zBOOL	IsActive();

	zCPlayerInfo						();
	virtual ~zCPlayerInfo				();	

	virtual void	Init				(const zSTRING& _name=zSTR_EMPTY, const zSTRING& addr=zSTR_EMPTY);
	virtual void	Init				(const zSTRING& _name, zNET_HANDLE _handle);

	virtual void	SetName				(const zSTRING& _name)		{ name = _name; };
	virtual void	SetPlayerVob		(zCVob* _vob);
	
	virtual void	Reset();

	virtual void	Deactivate(zBOOL deactivate);
	virtual zBOOL	IsDeactivated()	const;	

	virtual void	SetReady		(const zBOOL _ready);
	virtual zBOOL	IsReady			()	const;	
	
	zDWORD			SetPingStart();
	zDWORD			SetPingEnd();
	zDWORD			GetLastPingTime() { return pingTime; };
	zDWORD			GetNumLostPings() { return pingLost; };
	
	void			SetWorldInfo	(zCWorldInfo* wi)		{ worldInfo = wi; };	
	zCWorldInfo*	GetWorldInfo	()						{ return worldInfo; };	

	zSTRING			GetName				() const	{ return name; };
	zCVob*			GetPlayerVob		() const	{ return hostVob; };
	zCNetHost*		GetNetHost			()			{ return netHost; };
	zBYTE			GetID				() const;	

	static zCPlayerInfo*	CreateFromBuffer(zCBuffer& buffer);
	void PackToBuffer(zCBuffer& buffer);	

	zCPlayerInfo*	CreateDistinctPlayer();

	
	void			StorePlayerVobAsScript();
	zCVob*			CreatePlayerVobFromScript();
	zCBuffer*		GetPlayerVobScript();
	void			SetPlayerVobScript(zCBuffer* buffer);

protected:

	virtual void	Pack				(zCBuffer& buffer);
	virtual void	Unpack				(zCBuffer& buffer);
	
	void			SetID(zBYTE _id)				{ id=_id; }	

private:

	static zCArray<int>		free_ids;
	static zBYTE			next_id;
	static zCPlayerInfo*	activePlayer;

	zCVob*			hostVob;
	zCNetHost*		netHost;	
	zCBuffer*		scriptBuffer;
	zCWorldInfo*	worldInfo;

	zSTRING			name;	

	zDWORD			pingTime;
	zDWORD			pingTimeStart;
	zDWORD			pingLost;

	struct
	{
		zBYTE		id						:  8;	// 8		
		zBOOL		ready					:  1;	// 9
		zBOOL		deactivated				:  1;	// 10

		zDWORD		reserved				: 22;	// 32!
	};
};

typedef zCPlayerInfo* zCPlayerInfoPtr;


#endif
