/******************************************************************************** 
 
     $Workfile:: oGuilds.h            $                $Date:: 26.01.01 14:18   $
     $Revision:: 6                    $             $Modtime:: 26.01.01 13:48   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oGuilds.h $
 * 
 * 6     26.01.01 14:18 Wohlers
 * 
 * 5     25.10.00 17:57 Wohlers
 * 
 * 4     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 5     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 3     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __OGUILDS__
#define __OGUILDS__

#include "zTypes.h"
#include "zString.h"
#include "zArchiver.h"

class oCGuilds 
{
public:
	oCGuilds	();
	~oCGuilds	();

	int			GetAttitude		(int guild1, int guild2);
	void		SetAttitude		(int guild1, int guild2, zBYTE attitude);
	void		InitGuildTable	(const zSTRING& tableName);

	zSTRING		GetGuildName	(int guildNr);

	void		SaveGuildTable	(zCArchiver& arc);
	void		LoadGuildTable	(zCArchiver& arc);

private:
	int			size;
	zBYTE*		attitude;
};

#endif