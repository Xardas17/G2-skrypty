/******************************************************************************** 
 
     $Workfile:: oGuilds.cpp          $                $Date:: 27.01.01 20:21   $
     $Revision:: 13                   $             $Modtime:: 27.01.01 20:19   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oGuilds.cpp $
 * 
 * 13    27.01.01 20:21 Wohlers
 * 
 * 12    26.01.01 14:18 Wohlers
 * 
 * 11    25.10.00 17:57 Wohlers
 * 
 * 10    5.09.00 21:09 Wohlers
 * 
 * 9     2.08.00 14:25 Wohlers
 * 
 * 8     21.07.00 15:34 Wohlers
 * 
 * 7     9.06.00 12:58 Wohlers
 * Fixes
 * 
 * 6     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 5     9.05.00 13:14 Edenfeld
 * 
 * 5     9.05.00 2:24 Wohlers
 * 
 * 4     8.05.00 19:31 Wohlers
 * Gothic 0.80 - Inventory
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 9     19.04.00 16:44 Wohlers
 * Bug-Fixes
 * 
 * 8     18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 7     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 5     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 4     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     6.12.99 19:13 Wohlers
 * Waynet Erweiterungen I
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "oGuilds.h"
#include "oNpc.h"

#include "zParser.h"

oCGuilds :: oCGuilds ()
{
	size		= NPC_GIL_MAX;
	attitude	= zNEW(zBYTE)[size*size];
	// Init : Alles auf FRIENDLY
	memset(attitude,zBYTE(NPC_ATT_FRIENDLY),size*size);
	// Und jetzt initialisieren
	InitGuildTable ("GIL_ATTITUDES");
}

oCGuilds :: ~oCGuilds ()
{
	delete[] attitude;	attitude = NULL;
}

int oCGuilds :: GetAttitude (int g1, int g2)
{
	if ((g1<NPC_GIL_MAX) && (g2<NPC_GIL_MAX)) 
		return (int) attitude[g2*size+g1];
	else {
		zERR_WARNING("U:GIL:Unknown Guild "+zSTRING(g1)+":"+zSTRING(g2));
		return NPC_ATT_NEUTRAL;
	}
};

void oCGuilds :: SetAttitude (int guild1, int guild2, zBYTE att)
{
	if ((guild1<NPC_GIL_MAX) && (guild2<NPC_GIL_MAX)) {
		
		attitude[guild2*size+guild1] = att;
	};
};

void oCGuilds :: InitGuildTable (const zSTRING& tableName)
{
	int index	= parser.GetIndex(tableName);
	if (index<0) {
		zerr.Warning("U:GUILDS:Guild-Attitudes not found :"+tableName);
	} else {
		// Size check
		zCPar_Symbol* sym = parser.GetSymbol(index);
		int number = sym -> ele;
		if (number != NPC_GIL_HUMANS * NPC_GIL_HUMANS) {
			zerr.Warning("U:GUILDS:Guild-attitude-table size mismatch : Size has to be "+zSTRING(NPC_GIL_MAX));
		}
		// Init Attitudes from Guild-Table in scripts
		int v, c = 0;
		for (int x=0; x<NPC_GIL_HUMANS; x++) {
			for (int y=0; y<NPC_GIL_HUMANS; y++) {
				sym -> GetValue( v, c );
				attitude[y*size+x] = (zBYTE) v;
				c++;
			}
		}
		zERR_MESSAGE(5,0,"U:GUILDS:Guild-attitude-table changed : "+tableName);
	}
};

zSTRING oCGuilds :: GetGuildName(int guild)
{
	zCPar_Symbol* sym = parser.GetSymbol("TXT_GUILDS");
	if (sym) {
		zSTRING npcName;
		sym->GetValue(npcName,guild);
		return npcName;
	}
	return zSTRING("Error : Missing guild-names !");
};

void oCGuilds :: SaveGuildTable(zCArchiver& arc)
{
	arc.WriteRaw("guildTable",attitude,size * size);
};

void oCGuilds :: LoadGuildTable(zCArchiver& arc)
{
	arc.ReadRaw("guildTable",attitude,size * size);
};
