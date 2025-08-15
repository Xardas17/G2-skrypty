/******************************************************************************** 
 
     $Workfile:: oText.cpp            $                $Date:: 21.07.00 15:35   $
     $Revision:: 5                    $             $Modtime:: 21.07.00 15:13   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oText.cpp $
 * 
 * 5     21.07.00 15:35 Wohlers
 * 
 * 4     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "oText.h"

//#pragma optimize( "", off )

zCView * oCText :: output			= NULL;

int  oCText :: TXT_GUILD				= 0;	// Gildennamen
int  oCText :: TXT_ATTRIBUTE			= 0;	// Attributenamen
int	 oCText :: TXT_FIGHT_TALENT		= 0;	// Beginn Talents
int  oCText :: TXT_TALENT			= 0;	// Telentnamen
int  oCText :: TXT_DAYTIME			= 0;	// Tageszeiten
int  oCText :: TXT_ATR [6];					// Klartext Attribute
int  oCText :: TXT_ATR_HP			= 0;	// Klartext Strukturpunkte
int	 oCText :: TXT_ATTITUDE			= 0;	// Klartext Attitudes
int  oCText :: TXT_SPELL				= 0;	// Zauberspruchnamen

// Dialog
int	 oCText :: TXT_PC_GREETING		= 0;	// Eröffnungssatz des Players
int  oCText :: TXT_PC_FIRST_PHRASE	= 0;	// Ausfrage - Satz
int  oCText :: TXT_PC_SECOND_PHRASE	= 0;	// Ausfrage - Satz 2
int  oCText :: TXT_PC_TRADE_PHRASE	= 0;	// Handels-Satz
int  oCText :: TXT_NPC_LAST_PHRASE	= 0;	// NSC Ausleitungssatz
int  oCText :: TXT_PC_TRADE_THREAT	= 0;	//
int  oCText :: TXT_NPC_TRADE_THREAT	= 0;	//
int  oCText :: TXT_PC_INFO_THREAT	= 0;	//
int  oCText :: TXT_NPC_INFO_THREAT	= 0;	//
int  oCText :: TXT_INTIMIDATION		= 0;	// Beginn Einschüchterungssätze der NSCs

// News
int  oCText :: TXT_NEWS_INTRO		= 0;	// News - Einleitungssaetze
int  oCText :: TXT_NEWS_STOLE		= 0;	// Beginn News "SC hat NSC bestohlen"
int	 oCText :: TXT_NEWS_STOLE_10		= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_NEWS_STOLE_30		= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_NEWS_STOLE_50		= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_NEWS_STOLE_70		= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_NEWS_STOLE_90		= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_NEWS_STOLE_100	= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int  oCText :: TXT_NEWS_ATTACKED		= 0;	// Beginn News "SC hat wichtigen NSC angegriffen"
int  oCText :: TXT_NEWS_KILLED		= 0;	// Beginn News "SC hat wichtigen NSC getoetet"
// News - Du bezogen
int  oCText :: TXT_YNEWS_INTRO		= 0;
int  oCText :: TXT_YNEWS_STOLE		= 0;	// Beginn News "SC hat NSC bestohlen"
int	 oCText :: TXT_YNEWS_STOLE_10	= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_YNEWS_STOLE_30	= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_YNEWS_STOLE_50	= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_YNEWS_STOLE_70	= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_YNEWS_STOLE_90	= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int	 oCText :: TXT_YNEWS_STOLE_100	= 0;	// Beginn Meinungstexte "SC hat NSC bestohlen"
int  oCText :: TXT_YNEWS_ATTACKED	= 0;	// Beginn News "SC hat wichtigen NSC angegriffen"
int  oCText :: TXT_YNEWS_KILLED		= 0;	// Beginn News "SC hat wichtigen NSC getoetet"

int	 oCText :: TXT_INVCAT			= 0;	// Inventory-Kategorien

int  oCText :: TXT_HELP				= 0;	// Texte für das Hilfefenster

void oCText :: InitText ()
{
	// Tageszeiten
	TXT_DAYTIME		= parser.GetIndex(zSTRING("TXT_DAYTIMES"));
	// Gildennamen
	TXT_GUILD		= parser.GetIndex(zSTRING("TXT_GUILDS"));
	// Attribute
	TXT_ATTRIBUTE	= parser.GetIndex(zSTRING("TXT_ATTRIBUTES"));
	// Talentnamen
	TXT_FIGHT_TALENT= parser.GetIndex(zSTRING("TXT_FIGHT_TALENTS"));
	TXT_TALENT		= parser.GetIndex(zSTRING("TXT_TALENTS"));
	// Klartext fuer Strength
	TXT_ATR[0]		= parser.GetIndex(zSTRING("TXT_ATR_ST"));
	// Klartext fuer Strength
	TXT_ATR[1]		= parser.GetIndex(zSTRING("TXT_ATR_KO"));
	// Klartext fuer Strength
	TXT_ATR[2]		= parser.GetIndex(zSTRING("TXT_ATR_DK"));
	// Klartext fuer Strength
	TXT_ATR[3]		= parser.GetIndex(zSTRING("TXT_ATR_WK"));
	// Klartext fuer Strength
	TXT_ATR[4]		= parser.GetIndex(zSTRING("TXT_ATR_AG"));
	// Klartext fuer Strength
	TXT_ATR[5]		= parser.GetIndex(zSTRING("TXT_ATR_WI"));
	// Klartext Strukturpunkte
	TXT_ATR_HP		= parser.GetIndex(zSTRING("TXT_ATR_HP"));	
	// Klartext Attitudes
	TXT_ATTITUDE	= parser.GetIndex(zSTRING("TXT_ATTITUDE"));
	// Zauberspruchnamen
	TXT_SPELL		= parser.GetIndex(zSTRING("TXT_SPELLS"));
	
	// *** NEWS ***
	// Einleitungssaetze
	TXT_NEWS_INTRO		= parser.GetIndex(zSTRING("TXT_NEWS_INTRO"));
	
	// Newstext : SC hat wichtigen NSC bestohle
	TXT_NEWS_STOLE		= parser.GetIndex(zSTRING("TXT_NEWS_STOLE"));		// Beginn News "SC hat NSC bestohlen"
	TXT_NEWS_STOLE_10	= parser.GetIndex(zSTRING("TXT_NEWS_STOLE_10"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_NEWS_STOLE_30	= parser.GetIndex(zSTRING("TXT_NEWS_STOLE_30"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_NEWS_STOLE_50	= parser.GetIndex(zSTRING("TXT_NEWS_STOLE_50"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_NEWS_STOLE_70	= parser.GetIndex(zSTRING("TXT_NEWS_STOLE_70"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_NEWS_STOLE_90	= parser.GetIndex(zSTRING("TXT_NEWS_STOLE_90"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_NEWS_STOLE_100	= parser.GetIndex(zSTRING("TXT_NEWS_STOLE_100"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_NEWS_ATTACKED	= parser.GetIndex(zSTRING("TXT_NEWS_ATTACKED"));	// Beginn News "SC hat wichtigen NSC angegriffen"
	TXT_NEWS_KILLED		= parser.GetIndex(zSTRING("TXT_NEWS_KILLED"));

	// Einleitungssaetze Ich-News
	TXT_YNEWS_INTRO		= parser.GetIndex(zSTRING("TXT_YNEWS_INTRO"));
	
	// Ich-Newstext : SC hat wichtigen NSC bestohle
	TXT_YNEWS_STOLE		= parser.GetIndex(zSTRING("TXT_YNEWS_STOLE"));		// Beginn News "SC hat NSC bestohlen"
	TXT_YNEWS_STOLE_10	= parser.GetIndex(zSTRING("TXT_YNEWS_STOLE_10"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_YNEWS_STOLE_30	= parser.GetIndex(zSTRING("TXT_YNEWS_STOLE_30"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_YNEWS_STOLE_50	= parser.GetIndex(zSTRING("TXT_YNEWS_STOLE_50"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_YNEWS_STOLE_70	= parser.GetIndex(zSTRING("TXT_YNEWS_STOLE_70"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_YNEWS_STOLE_90	= parser.GetIndex(zSTRING("TXT_YNEWS_STOLE_90"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_YNEWS_STOLE_100	= parser.GetIndex(zSTRING("TXT_YNEWS_STOLE_100"));	// Beginn Meinungstexte "SC hat NSC bestohlen"
	TXT_YNEWS_ATTACKED	= parser.GetIndex(zSTRING("TXT_YNEWS_ATTACKED"));	// Beginn News "SC hat wichtigen NSC angegriffen"
	TXT_YNEWS_KILLED	= parser.GetIndex(zSTRING("TXT_YNEWS_KILLED"));

	// *** DIALOG - INTRO ***
	TXT_PC_GREETING 	= parser.GetIndex(zSTRING("TXT_PC_GREETING_PHRASE"));
	TXT_PC_FIRST_PHRASE = parser.GetIndex(zSTRING("TXT_PC_FIRST_PHRASE"));	
	TXT_PC_SECOND_PHRASE= parser.GetIndex(zSTRING("TXT_PC_SECOND_PHRASE"));	
	TXT_PC_TRADE_PHRASE = parser.GetIndex(zSTRING("TXT_PC_TRADE_PHRASE"));	
	TXT_NPC_LAST_PHRASE	= parser.GetIndex(zSTRING("TXT_NPC_LAST_PHRASE"));	// NSC Ausleitungssatz
	TXT_PC_TRADE_THREAT	= parser.GetIndex(zSTRING("TXT_PC_TRADE_THREAT"));	//
	TXT_NPC_TRADE_THREAT= parser.GetIndex(zSTRING("TXT_NPC_TRADE_THREAT"));	//
	TXT_PC_INFO_THREAT	= parser.GetIndex(zSTRING("TXT_PC_INFO_THREAT"));	//
	TXT_NPC_INFO_THREAT = parser.GetIndex(zSTRING("TXT_NPC_INFO_THREAT"));	//

	// *** NSC - Einschüchterungssätze ***
	TXT_INTIMIDATION	= parser.GetIndex(zSTRING("TXT_INTIMIDATION"));

	TXT_INVCAT			= parser.GetIndex(zSTRING("TXT_INVCAT"));			// Inventory-Kategorien
	TXT_HELP			= parser.GetIndex(zSTRING("TXT_HELP"));				// Texte fürs Hilfefenster
};
//#pragma optimize( "", on )
