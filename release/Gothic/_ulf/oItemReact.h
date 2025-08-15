/******************************************************************************** 
 
     $Workfile:: oItemReact.h         $                $Date:: 22.05.00 18:42   $
     $Revision:: 4                    $             $Modtime:: 9.05.00 14:23    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oItemReact.h $
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
 * 2     19.04.00 19:10 Wohlers
 * 
 * 4     6.12.99 19:13 Wohlers
 * Waynet Erweiterungen I
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef	__OITEMREACT__
#define __OITEMREACT__

#include "zTypes.h"
#include "zList.h"

class zCParser;
class oCItemReactModule;
class oCNpc;
class oCItem;

class oCTradeManager
{
public:
	oCTradeManager					( zCParser *parser );
	~oCTradeManager					();

	oCItemReactModule*	GetModule	( oCNpc* ask, oCNpc* npc, oCItem* item );

private:
	zCParser*	p;
	zList <oCItemReactModule> moduleList;
	
	// Statics
	static zBOOL size_checked;
};

class oCItemReactModule
{
public:
	oCItemReactModule			(int instance);
	~oCItemReactModule			();

	void	Validate			();
	zBOOL	Conditions			(int activeInstance, int flags);
	void	GetOfferedInstance	(int &instance, int &amount);
	zBOOL	StartReaction		(int amount);					// returns : Do Exchange
	int		GetDataSize			();
	int		GetNpcInstance		();

	oCItemReactModule*			next;

private:
	struct {
		// Parserdata
		int		trade_npc;				// Instance of NPC
		int		trade_instance;			// Item which NSC gives
		int		trade_amount;			// Amount of Items 
		int		other_category;			// Matching Category of SC-Item
		int		other_instance;			// Item from SC
		int		other_amount;			// Item amount
		// reactionCall
		int		reaction;				// ReactionFunc from script
	} pd;
};

#endif __OITEMREACT__