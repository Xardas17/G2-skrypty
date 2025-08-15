
/******************************************************************************** 
 
     $Workfile:: oPortals.h           $                $Date:: 6.02.01 21:00    $
     $Revision:: 5                    $             $Modtime:: 6.02.01 15:49    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   
 *********************************************************************************/

#ifndef __OPORTALS_H__
#define __OPORTALS_H__

#include "zTypes.h"
#include "zString.h"
#include "zContainer.h"

class oCNpc;

class oCPortalRoom {

public:
	oCPortalRoom							(const zSTRING& name);
	oCPortalRoom							();
	~oCPortalRoom							();

	zSTRING&	GetPortalName				();
	zBOOL		IsPortalMyRoom				(oCNpc* npc);
	oCNpc*		GetOwnerNpc					();
	void		SetOwnerNpc					(const zSTRING& npcInstance)	{ ownerNpc = npcInstance; };
	int			GetOwnerGuild				();				
	void		SetOwnerGuild				(int guildNr)					{ ownerGuild = guildNr; };

	void		SavePortalData				(zCArchiver& arc);
	void		LoadPortalData				(zCArchiver& arc);

private:

	zSTRING		portalName;
	zSTRING		ownerNpc;
	int			ownerGuild;

};

class oCPortalRoomManager {

public:

	oCPortalRoomManager								();
	~oCPortalRoomManager							();

	void			AssignPortalToNpc				(const zSTRING& portal, const zSTRING& npcInstance);
	void			AssignPortalToGuild				(const zSTRING& portal, int guildNr);
	
	zBOOL			IsPortalMyRoom					(const zSTRING& portal, oCNpc* npc);
	zBOOL			IsPlayerInRoom					()											{ return (curPlayerRoom!=NULL);	};				
	zBOOL			IsPlayerInMyRoom				(oCNpc* owner);
	zBOOL			IsNSCInPlayerRoom				(oCNpc* owner);
	zBOOL			WasPlayerInMyRoom				(oCNpc* owner);
	oCNpc*			GetCurPlayerPortalRoomOwner		();
	int				GetCurPlayerPortalRoomGuild		();
	oCNpc*			GetFormerPlayerPortalRoomOwner	();
	int				GetFormerPlayerPortalRoomGuild	();

	zBOOL			HasPlayerChangedPortalRoom		();

	oCNpc*			GetCurNpcPortalRoomOwner		(oCNpc* npc);
	int				GetCurNpcPortalRoomGuild		(oCNpc* npc);
	
	void			ShowPortalInfo					();

	void			ShowDebugInfo					();

	void			SavePortalData					(zCArchiver& arc);
	void			LoadPortalData					(zCArchiver& arc);
	void			CleanUp							();

	static int		SortPortals						(const void* ele1,const void* ele2);

private:

	int				GetPortalRoomIndex				(const zSTRING& name);

	zSTRING*		oldPlayerPortal;
	zSTRING*		curPlayerPortal;
	oCPortalRoom*	oldPlayerRoom;
	oCPortalRoom*	curPlayerRoom;

	zCArraySort <oCPortalRoom*> portals;

};

#endif