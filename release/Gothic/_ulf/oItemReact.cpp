/******************************************************************************** 
 
     $Workfile:: oItemReact.cpp       $                $Date:: 2.08.00 14:25    $
     $Revision:: 6                    $             $Modtime:: 2.08.00 13:14    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oItemReact.cpp $
 * 
 * 6     2.08.00 14:25 Wohlers
 * 
 * 5     21.07.00 15:34 Wohlers
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
 * 6     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 5     20.12.99 17:43 Wohlers
 * 
 * 4     6.12.99 19:13 Wohlers
 * Waynet Erweiterungen I
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "oItemReact.h"

#include "zParser.h"
#include "oNpc.h"
#include "oItem.h"

// ***********************************************************************************
// And again, the Manager for all Module
// ***********************************************************************************

// Global
zSTRING tradeClass ("C_ITEMREACT");

// Static 
zBOOL oCTradeManager :: size_checked = FALSE;

oCTradeManager :: oCTradeManager ( zCParser *parser )
{
	p = parser;
	if (!p) return;
	
	// Getting the class Index
	int cindex = p->GetIndex(tradeClass);
	if (cindex<0) return;
	// Create all Infos
	int	pos	= 0;
	while (pos>=0) {
		pos	= p->GetInstance(cindex,pos+1);
		if (pos>=0) {
			// Create Info
			oCItemReactModule* trade = zNEW( oCItemReactModule(pos) );
			// Check Size
			if (!size_checked) {
				p->CheckClassSize(tradeClass,trade->GetDataSize());
				size_checked = TRUE;				
			}
			trade -> Validate	();
			moduleList.Insert	(trade);
		}
	};
	// Debug
	zerr.Message("U:TRADE: "+zSTRING(moduleList.Count())+" ItemReactModules found.");
};

oCTradeManager :: ~oCTradeManager ( )
{
	moduleList.Clear();
	p = NULL;
};

oCItemReactModule* oCTradeManager :: GetModule ( oCNpc* ask, oCNpc* npc, oCItem* item )
// ask = Player
// npc = NPC
{
	oCItemReactModule* found = moduleList.wurzel;
	// Parser Setup.
	p->SetInstance("SELF"	,npc);
	p->SetInstance("OTHER"	,ask);
	p->SetInstance("ITEM"	,item);
	while (found) {
		// Check Conditions
		if ((found->GetNpcInstance()==npc->GetInstance()) && found->Conditions (item->GetInstance(),item->GetFlags())) return found;
		found = found -> next;
	}
	return NULL;
};

// ***********************************************************************************
// A single module 
// ***********************************************************************************

oCItemReactModule :: oCItemReactModule(int instance)
{
	next				= NULL;

	pd.trade_npc		= -1;
	pd.trade_instance	= -1;
	pd.trade_amount		= 0;
	pd.other_category	= 0;
	pd.other_instance	= -1;
	pd.other_amount		= 0;
	pd.reaction			= -1;

	parser.CreateInstance(instance,&pd);
	Validate();
};

oCItemReactModule :: ~oCItemReactModule()
{
	next = NULL;
};

void oCItemReactModule :: Validate()
{
//	zCPar_Symbol* sym = parser.GetSymbol(instance);
//	if (!sym) return;

	// All data initialised and okay ?
//	if (trade_npc>=0)		zerr.Warning("U:ITEMREACT:ItemReactModule: not used by a NPC ("+sym->name+")");
//	if (trade_instance>=0)	zerr.Warning("U:ITEMREACT:ItemReactModule: not used by ("+sym->name+")");
}

zBOOL oCItemReactModule :: Conditions (int activeInstance, int flags)
{
	if (pd.other_instance>=0) {
		// Es gibt Instance, also diese testen		
		return (activeInstance == pd.other_instance);
	
	} else {

		return ((flags & pd.other_category)>0);
	}
};

void oCItemReactModule :: GetOfferedInstance(int &instance, int &amount)
{
	instance	= pd.trade_instance;
	amount		= pd.trade_amount;
}

zBOOL oCItemReactModule :: StartReaction (int amount)
{
	pd.other_amount = amount;
	return *(zBOOL*) parser.CallFunc(pd.reaction);
};

int oCItemReactModule :: GetDataSize ()
{
	return sizeof(pd);
}

int oCItemReactModule :: GetNpcInstance()
{
	return pd.trade_npc;
}
