#include "zCore.h"
#include "oMenu_Help.h"

const zSTRING MENU_ITEM_KEYNAME_TEMPLATE		= zSTRING("MENU_ITEM_KEYNAME_TEMPLATE");
const zSTRING MENU_ITEM_KEY_TEMPLATE			= zSTRING("MENU_ITEM_KEY_TEMPLATE");
const zSTRING MENU_HELP							= zSTRING("MENU_HELP_KEYS_1");
const zSTRING MENU_ITEM_KEY						= zSTRING("MENU_ITEM_KEY");


oCMenu_Help :: oCMenu_Help(const zSTRING &name) : zCMenu(name)
{
};

/*
oCMenu_Help :: ~oCMenu_Help()
{
	// alle cpp registrierten menu items löschen
	for ( int i=0; i<items.GetNumInList(); i++)
	{
		if ( items[i]->IsRegisteredCPP() ) delete items[i];
	}
};
*/

zBOOL oCMenu_Help::HandleEvent(int key)
{
	zBOOL leave = FALSE;

	zWORD logicalKey = zinput->GetFirstBindedLogicalKey(key);

	switch (logicalKey)
	{
		case GAME_UP:
		case GAME_DOWN:
		case GAME_LEFT:
		case GAME_RIGHT:
			leave = TRUE;
			break;
		case GAME_ACTION: 
		case GAME_ACTION2: 
		case GAME_END:
			{
				ForceSelAction(SEL_ACTION_CLOSE,"");
				eventOccured[MENU_EVENT_LEAVE]	= TRUE;
				leave							= TRUE;
				m_exitState						= BACK;
			}
			break;
	}

	if (!leave) 
	{
		switch (key)
		{
			case KEY_F1: 
			case KEY_ENTER: 
			case KEY_ESC:   
				{
					ForceSelAction(SEL_ACTION_CLOSE,"");
					eventOccured[MENU_EVENT_LEAVE]	= TRUE;
					leave							= TRUE;
					m_exitState						= BACK;
				}
				break;
			}
	}

	updateTimer += ztimer.GetFrameTime();
	if (updateTimer > eventTimerUpdateMSec) 
	{
		updateTimer = 0;
		eventOccured[MENU_EVENT_TIMER] = TRUE;
	}

	return leave;
};


void oCMenu_Help::SetKeys		(const zCArray<oSMenuKey>	&keys)
{
	
	// tmp, deactivated text for publisher release [Edenfeld]
	return;

	zCMenuItem *it;
	for (int i=0; i<keys.GetNumInList(); i++) 
	{
		it = zCMenuItem::GetByName(MENU_ITEM_KEY + "_" + zSTRING(i + 1));
		zERR_ASSERTT_STRICT(it,zSTRING("item " + MENU_ITEM_KEY + "_" + zSTRING(i + 1) +  " must be in menuinst_help.d").ToChar());
		it->SetText(keys[i].name);
	}
	this->keys = keys;
};


void oCHelpScreen :: SetKeys		(const zCArray<oSMenuKey>	&keys)
{
	if (help) help->SetKeys(keys);
};


oCHelpScreen::oCHelpScreen()
{
	help = zNEW( oCMenu_Help ("MENU_HELP") );
};

oCHelpScreen::~oCHelpScreen()
{
	delete help; help = 0;
};

void oCHelpScreen :: Show()
{	
	help->Run();
};
