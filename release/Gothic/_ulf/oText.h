/******************************************************************************** 
 
     $Workfile:: oText.h              $                $Date:: 22.05.00 18:43   $
     $Revision:: 4                    $             $Modtime:: 9.05.00 14:24    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oText.h $
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

#ifndef __O_TEXT__
#define __O_TEXT__

#include "zString.h"
#include "zview.h"
#include "zParser.h"

class oCText {
public :
	static zCView *output;

	static int  TXT_GUILD;				// Beginn Gildennamen
	static int  TXT_ATTRIBUTE;			// Beginn Attribute
	static int	TXT_FIGHT_TALENT;		// Beginn Talents
	static int	TXT_TALENT;				// Beginn Talents
	static int  TXT_DAYTIME;			// Beginn Tageszeiten
	static int  TXT_ATR[6];				// Beginn Klartext Attribute
	static int  TXT_ATR_HP;				// Klartext Strukturpunkte
	static int  TXT_SPELL;				// Beginn Zaubersprcuhnamen
	static int	TXT_ATTITUDE;			// Klartext Attitudes

	// Dialog 
	static int	TXT_PC_GREETING;		// Eröffnungssatz des Players
	static int  TXT_PC_FIRST_PHRASE;	// Ausfrage - Satz
	static int  TXT_PC_SECOND_PHRASE;	// Ausfrage - Satz 2
	static int  TXT_PC_TRADE_PHRASE;	// Handels-Satz
	static int  TXT_NPC_LAST_PHRASE;	// NSC Ausleitungssatz
	static int  TXT_PC_TRADE_THREAT;	//
	static int  TXT_NPC_TRADE_THREAT;	//
	static int  TXT_PC_INFO_THREAT;		//
	static int  TXT_NPC_INFO_THREAT;	//

	// News Texte	
	static int  TXT_NEWS_INTRO;			// Beginn News Einleitungssaetze
	static int  TXT_NEWS_STOLE;			// Beginn News "SC hat NSC bestohlen"
	static int	TXT_NEWS_STOLE_10;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_NEWS_STOLE_30;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_NEWS_STOLE_50;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_NEWS_STOLE_70;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_NEWS_STOLE_90;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_NEWS_STOLE_100;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int  TXT_NEWS_ATTACKED;		// Beginn News "SC hat wichtigen NSC angegriffen"
	static int  TXT_NEWS_KILLED;		// Beginn News "SC hat wichtigen NSC getoetet"

	// Ich-News Texte	
	static int  TXT_YNEWS_INTRO;		// Beginn News Einleitungssaetze
	static int  TXT_YNEWS_STOLE;		// Beginn News "SC hat NSC bestohlen"
	static int	TXT_YNEWS_STOLE_10;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_YNEWS_STOLE_30;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_YNEWS_STOLE_50;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_YNEWS_STOLE_70;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_YNEWS_STOLE_90;		// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int	TXT_YNEWS_STOLE_100;	// Beginn Meinungstexte "SC hat NSC bestohlen"
	static int  TXT_YNEWS_ATTACKED;		// Beginn News "SC hat wichtigen NSC angegriffen"
	static int  TXT_YNEWS_KILLED;		// Beginn News "SC hat wichtigen NSC getoetet"

	// Texte Einschüchterung
	static int  TXT_INTIMIDATION;		// Beginn Einschüchterungssätze der NSCs

	// Weitere Texte
	static int	TXT_INVCAT;				// Inventory-Kategorien
	static int  TXT_HELP;				// Texte fürs Hilfefenster

	static void InitText();
};

#endif 
