// @HOME
// omenu_status.d
// otext.d

#include "zCore.h"
#include "zinput_win32.h"

#include "omission.h"
#include "oobert.h"
#include "oworld.h"
#include "ogame.h"
#include "onpc.h"
#include "omenu_status.h"
#include "onpcmessages.h"


extern void HandleResultString(zSTRING);

// Menues
const zSTRING MENU_STATUS						= "MENU_STATUS";
const zSTRING MENU_LOG							= "MENU_LOG";

// Globale Daten
const zSTRING MENU_ITEM_PLAYERNAME				= "MENU_ITEM_PLAYERNAME";
const zSTRING MENU_ITEM_PLAYERGUILD				= "MENU_ITEM_PLAYERGUILD";
const zSTRING MENU_ITEM_PLAYER_MAGICALGUILD		= "MENU_ITEM_PLAYER_MAGICALGUILD";

// Attribute und ihre Maximalwerte
const zSTRING MENU_ITEM_ATTRIBUTE_PREFIX   		= "MENU_ITEM_ATTRIBUTE";

// Level und Experience
const zSTRING MENU_ITEM_LEVEL					= "MENU_ITEM_LEVEL";
const zSTRING MENU_ITEM_LEVEL_NEXTEXP			= "MENU_ITEM_LEVEL_NEXT";
const zSTRING MENU_ITEM_EXP						= "MENU_ITEM_EXP";
const zSTRING MENU_ITEM_LEARN					= "MENU_ITEM_LEARN";

// Präfixe (Talente und Armor)
const zSTRING MENU_ITEM_TALENT_PREFIX			= "MENU_ITEM_TALENT";
const zSTRING MENU_ITEM_ARMOR_PREFIX			= "MENU_ITEM_ARMOR";

// Missionen und Logs
const zSTRING MENU_ITEM_LIST_MISACT				= "MENU_ITEM_LIST_MISSIONS_ACT";
const zSTRING MENU_ITEM_LIST_MISOLD				= "MENU_ITEM_LIST_MISSIONS_OLD";
const zSTRING MENU_ITEM_LIST_MISFAILED			= "MENU_ITEM_LIST_MISSIONS_FAILED";
const zSTRING MENU_ITEM_LIST_LOG				= "MENU_ITEM_LIST_LOG";
const zSTRING MENU_ITEM_CONTENT_VIEWER			= "MENU_ITEM_CONTENT_VIEWER";

// Daytime
const zSTRING MENU_ITEM_DAY						= "MENU_ITEM_DAY";
const zSTRING MENU_ITEM_TIME					= "MENU_ITEM_TIME";

//
// Log-Menue
//


oCMenu_Log::oCMenu_Log(const zSTRING &name) : zCMenu(name)
{
};

void oCMenu_Log::ScreenInit()
{	
	zCMenu::ScreenInit();

	listItemAct		= dynamic_cast<zCMenuItemList*>(zCMenuItem::GetByName(MENU_ITEM_LIST_MISACT));
	listItemOld		= dynamic_cast<zCMenuItemList*>(zCMenuItem::GetByName(MENU_ITEM_LIST_MISOLD));
	listItemFailed	= dynamic_cast<zCMenuItemList*>(zCMenuItem::GetByName(MENU_ITEM_LIST_MISFAILED));	
	listItemLog		= dynamic_cast<zCMenuItemList*>(zCMenuItem::GetByName(MENU_ITEM_LIST_LOG));	
	contentViewer	= dynamic_cast<zCMenuItemText*>(zCMenuItem::GetByName(MENU_ITEM_CONTENT_VIEWER));		

	if (listItemAct)	listItemAct->Hide();	else zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISACT+"\" missing for Log-Screen!");	
	if (listItemFailed) listItemFailed->Hide(); else zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISFAILED+"\" missing for Log-Screen!");	
	if (listItemOld)	listItemOld->Hide();	else zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISOLD+"\" missing for Log-Screen!");	
	if (listItemLog)	listItemLog->Hide();	else zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_LOG+"\" missing for Log-Screen!");			
	if (contentViewer)	contentViewer->Hide();	else zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_CONTENT_VIEWER+"\" missing for Log-Screen!");		
};

void oCMenu_Log::ScreenDone()
{
	if (listItemAct)	listItemAct->Release();		listItemAct		=0;
	if (listItemFailed) listItemFailed->Release();	listItemFailed	=0;
	if (listItemOld)	listItemOld->Release();		listItemOld		=0;
	if (listItemLog)	listItemLog->Release();		listItemLog		=0;
	if (contentViewer)	contentViewer->Release();	contentViewer	=0;

	zCMenu::ScreenDone();	
};

//static zCList<oCLogEntry> entryList;

void oCMenu_Log::SetDayTime(const zSTRING &day, const zSTRING &time)
{
	zCMenuItem*	dayItem		= zCMenuItem::GetByName(MENU_ITEM_DAY) ;
	zCMenuItem*	timeItem	= zCMenuItem::GetByName(MENU_ITEM_TIME);

	if (dayItem)
	{
		dayItem->SetText(day);
		dayItem->Release();
	};

	if (timeItem)
	{
		timeItem->SetText(time);
		timeItem->Release();
	};
};

/* alt, pre 1.08
void oCMenu_Log::SetLogTopics(const zCList<oCLogTopic>& list)
{			
	zCMenuItemList*	listItemAct		= dynamic_cast<zCMenuItemList*>	(zCMenuItem::GetByName(MENU_ITEM_LIST_MISACT));
	zCMenuItemList*	listItemFailed	= dynamic_cast<zCMenuItemList*>	(zCMenuItem::GetByName(MENU_ITEM_LIST_MISFAILED));
	zCMenuItemList* listItemOld		= dynamic_cast<zCMenuItemList*>	(zCMenuItem::GetByName(MENU_ITEM_LIST_MISOLD));	
	zCMenuItemList* listItemLog		= dynamic_cast<zCMenuItemList*>	(zCMenuItem::GetByName(MENU_ITEM_LIST_LOG));	
	zCMenuItemText*	contentViewer	= dynamic_cast<zCMenuItemText*>	(zCMenuItem::GetByName(MENU_ITEM_CONTENT_VIEWER));

	if (!listItemAct)		zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISACT+"\" missing for Log-Screen!");		
	if (!listItemOld)		zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISOLD+"\" missing for Log-Screen!");	
	if (!listItemFailed)	zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISFAILED+"\" missing for Log-Screen!");			

	listItemAct->DeleteContent();
	listItemFailed->DeleteContent();
	listItemOld->DeleteContent();
	listItemLog->DeleteContent();

	zSTRING content;
	for (int i=0; i<list.GetNumInList(); i++) 
	{			
		zTMenuItemListElement element;				
		entryList		= list[i]->GetEntryList();
		content.Clear();
		for (int j=0;j<entryList.GetNumInList();j++)
		{
			if (!content.IsEmpty()) content = content + "\n---\n";
			content += entryList[j]->GetDescription(); 
		};
		if (content.IsEmpty()) content="---";
		element.content			= content;
		element.title			= list[i]->GetDescription();
		element.contentViewer	= contentViewer;
		
		switch (list[i]->GetSection())
		{
			case oCLogTopic::zELogSection::zELogSection_Missions:

				switch (list[i]->GetStatus())
				{
					case oCLogTopic::zELogTopicStatus::zELogTopicStatus_Running:
						if (listItemAct) listItemAct->InsertEnd(element);
						break;
					case oCLogTopic::zELogTopicStatus::zELogTopicStatus_Success:
						if (listItemOld) listItemOld->InsertEnd(element);
						break;
					case oCLogTopic::zELogTopicStatus::zELogTopicStatus_Failure:
						if (listItemFailed) listItemFailed->InsertEnd(element);
						break;
					case oCLogTopic::zELogTopicStatus::zELogTopicStatus_Obsolete:
						break;
				}
				break;

			case oCLogTopic::zELogSection::zELogSection_Notes:
				if (listItemLog) listItemLog->InsertEnd(element);
				break;
		};
	
	}

	if (contentViewer)	contentViewer->Release();
	if (listItemLog)	listItemLog->Release();
	if (listItemAct)	listItemAct->Release();
	if (listItemFailed) listItemFailed->Release();
	if (listItemOld)	listItemOld->Release();	
};
*/

void oCMenu_Log::SetLogTopics(const zCList<oCLogTopic>& list)
{			
	zCMenuItemList*	listItemAct		= dynamic_cast<zCMenuItemList*>	(zCMenuItem::GetByName(MENU_ITEM_LIST_MISACT));
	zCMenuItemList*	listItemFailed	= dynamic_cast<zCMenuItemList*>	(zCMenuItem::GetByName(MENU_ITEM_LIST_MISFAILED));
	zCMenuItemList* listItemOld		= dynamic_cast<zCMenuItemList*>	(zCMenuItem::GetByName(MENU_ITEM_LIST_MISOLD));	
	zCMenuItemList* listItemLog		= dynamic_cast<zCMenuItemList*>	(zCMenuItem::GetByName(MENU_ITEM_LIST_LOG));	
	zCMenuItemText*	contentViewer	= dynamic_cast<zCMenuItemText*>	(zCMenuItem::GetByName(MENU_ITEM_CONTENT_VIEWER));

	if (!listItemAct)		zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISACT+"\" missing for Log-Screen!");		
	if (!listItemOld)		zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISOLD+"\" missing for Log-Screen!");	
	if (!listItemFailed)	zERR_FAULT("B: MEN: Menuitem \""+MENU_ITEM_LIST_MISFAILED+"\" missing for Log-Screen!");			

	listItemAct->DeleteContent();
	listItemFailed->DeleteContent();
	listItemOld->DeleteContent();
	listItemLog->DeleteContent();

	zSTRING content;
	for (int i=0; i<list.GetNumInList(); i++) 
	{			
		zTMenuItemListElement element;				
//		entryList		= list[i]->GetEntryList();
		content.Clear();
//		for (int j=0;j<entryList->GetNumInList();j++)
		for (int j=0;j<list[i]->GetEntryList().GetNumInList();j++)
		{
			if (!content.IsEmpty()) content = content + "\n---\n";
//			content += entryList[j]->GetDescription(); 
			content += list[i]->GetEntryList()[j]->GetDescription(); 
		};
		if (content.IsEmpty()) content="---";
		element.content			= content;
		element.title			= list[i]->GetDescription();
		element.contentViewer	= contentViewer;
		
		switch (list[i]->GetSection())
		{
			case oCLogTopic::zELogSection::zELogSection_Missions:

				switch (list[i]->GetStatus())
				{
					case oCLogTopic::zELogTopicStatus::zELogTopicStatus_Running:
						if (listItemAct) listItemAct->InsertEnd(element);
						break;
					case oCLogTopic::zELogTopicStatus::zELogTopicStatus_Success:
						if (listItemOld) listItemOld->InsertEnd(element);
						break;
					case oCLogTopic::zELogTopicStatus::zELogTopicStatus_Failure:
						if (listItemFailed) listItemFailed->InsertEnd(element);
						break;
					case oCLogTopic::zELogTopicStatus::zELogTopicStatus_Obsolete:
						break;
				}
				break;

			case oCLogTopic::zELogSection::zELogSection_Notes:
				if (listItemLog) listItemLog->InsertEnd(element);
				break;
		};
	
	}

	if (contentViewer)	contentViewer->Release();
	if (listItemLog)	listItemLog->Release();
	if (listItemAct)	listItemAct->Release();
	if (listItemFailed) listItemFailed->Release();
	if (listItemOld)	listItemOld->Release();	
};


static	int waitTime		= 250;
static	int lastSelection	= 0;

void oCMenu_Log::SetInfo(const zCMenuItem *it) 
{	
	/*
	zCMenuItem *info;

	info = zCMenuItem::GetByName(MENU_ITEM_MISSION_NAME);

	info->ClrPrintwin();
	info->Setflags(VIEW_TXT_CENTER);
	info->SetText( ((zCMenuItem*)it)->GetText(0) );

	info = zCMenuItem::GetByName(MENU_ITEM_MISSION_INFO);	

	info->ClrPrintwin();
	info->ClrFlags(VIEW_TXT_CENTER);	
	info->SetText( it->m_parUserString[0]+zSTRING("\n") );
	*/
}


zBOOL oCMenu_Log::ExecCommand(const zSTRING &s)
{
	zSTRING itemID = s;
	zSTRING word1 =  itemID.PickWord(1, " ");	
	if (word1 == "EFFECTS") 
	{
		itemID.Delete("EFFECTS");
		itemID.TrimRight();itemID.TrimLeft();
		zCMenuItemList* listitem = dynamic_cast<zCMenuItemList*>(zCMenuItem::GetByName(itemID));
		if (listitem) 
		{
			listitem->Run();		
			listitem->Release();
		}
		return TRUE;
	}
	return FALSE;
};

zBOOL oCMenu_Log::HandleEnterItem(zCMenuItem* item)
{		
	zBOOL result = zCMenu::HandleEnterItem(item);

	zSTRING itemID	= item->m_parOnSelAction_S[0];
	zSTRING word1	= itemID.PickWord(1, " ");	

	if (word1 == "EFFECTS") 
	{
		itemID.Delete("EFFECTS");itemID.TrimRight();itemID.TrimLeft();

		zCMenuItemList* listitem = dynamic_cast<zCMenuItemList*>(zCMenuItem::GetByName(itemID));
		if (listitem) 
		{
			listitem->Show();
			listitem->Release();
		}
	}

	return result;
};

zBOOL oCMenu_Log::HandleLeaveItem(zCMenuItem* item)
{
	zSTRING itemID	= item->m_parOnSelAction_S[0];
	zSTRING word1	= itemID.PickWord(1, " ");	

	if (word1 == "EFFECTS") 
	{
		itemID.Delete("EFFECTS");itemID.TrimRight();itemID.TrimLeft();

		zCMenuItemList* listitem = dynamic_cast<zCMenuItemList*>(zCMenuItem::GetByName(itemID));
		if (listitem) 
		{
			listitem->Hide();
			listitem->Release();
		}
	}

	return zCMenu::HandleLeaveItem(item);
};

zBOOL oCMenu_Log::HandleActivateItem(zCMenuItem* item)
{
	return zCMenu::HandleActivateItem(item);
};

zBOOL oCMenu_Log::HandleEvent(int key)
{
	zWORD logicalKey = zinput->GetFirstBindedLogicalKey(key);
	if (logicalKey == GAME_SCREEN_LOG)	key = KEY_ESC; // Abbruch	
	if (key == KEY_LEFT)				key = KEY_ENTER;
	if (key == KEY_RIGHT)				key = KEY_ENTER;

	return zCMenu::HandleEvent(key);	
};

void oCMenu_Log::Activate()
{
	zCMenu::Activate();
	// oCStatusScreen::SetInfo(zCMenu::GetActiveItem());
};

void oCMenu_Log::InitForDisplay()
{
	
};


//
// Status-Menue
//

static zSTRING resultStr;
zBOOL oCMenu_Status::HandleEvent(int key)
{	
	zWORD logicalKey = zinput->GetFirstBindedLogicalKey(key);
	
	if (logicalKey == GAME_SCREEN_STATUS)
		key = KEY_ESC;  // ESC bricht auch ab !!!
		
	if ((key != KEY_ESC) && (logicalKey != GAME_END))
	{
		unsigned char ch = GetCharFromDIK(key, 0, 0);
		if ((ch >= 32) && (ch <= 255))
			resultStr = resultStr + (char)(ch);
	}

	return zCMenu::HandleEvent(key);
};

void oCMenu_Status::SetPlayerName	(const zSTRING &name)
{
	zCMenuItem *it = zCMenuItem::GetByName(MENU_ITEM_PLAYERNAME);
	if (it) 
	{
		it->SetText(name,0,TRUE);
		it->Release();
	}
};

void oCMenu_Status::SetGuild		(const zSTRING &guild)
{
	zCMenuItem *it = zCMenuItem::GetByName(MENU_ITEM_PLAYERGUILD);
	if (it) 
	{
		it->SetText(guild.IsEmpty() ? it->GetText(1) : guild);	
		it->Release();
	}
};


void oCMenu_Status::SetMagicalGuild(const zSTRING &a_strMagicalGuild)
{
	zCMenuItem *it = zCMenuItem::GetByName(MENU_ITEM_PLAYER_MAGICALGUILD);
	if (it) 
	{
		it->SetText(a_strMagicalGuild.IsEmpty() ? it->GetText(1) : a_strMagicalGuild);	
		it->Release();
	}
};


void oCMenu_Status::SetExperience	(zDWORD level, zDWORD exp, zDWORD nextLevel)
{	
	zCMenuItem *it;
	it = zCMenuItem::GetByName(MENU_ITEM_LEVEL);
	if (it) { it->SetText(zSTRING(level),0,TRUE);it->Release();}
	else	zERR_FAULT("B: STAT: Menuitem "+MENU_ITEM_LEVEL+" not found");

	it = zCMenuItem::GetByName(MENU_ITEM_EXP);
	if (it) { it->SetText(zSTRING(exp),0,TRUE);it->Release();}
	else	zERR_FAULT("B: STAT: Menuitem "+MENU_ITEM_EXP+" not found");

	it = zCMenuItem::GetByName(MENU_ITEM_LEVEL_NEXTEXP);
	if (it) { it->SetText(zSTRING(nextLevel),0,TRUE);it->Release();}
	else	zERR_FAULT("B: STAT: Menuitem "+MENU_ITEM_LEVEL_NEXTEXP+" not found");
};

void oCMenu_Status::SetLearnPoints(zDWORD points)
{
	zCMenuItem *it;
	it = zCMenuItem::GetByName(MENU_ITEM_LEARN);
	if (it) { it->SetText(zSTRING(points),0,TRUE);it->Release();}
}


/*
void oCMenu_Status::SetGuildLevel	(const zSTRING &guildLevel)
{
	zCMenuItem *it = zCMenuItem::GetByName(MENU_ITEM_GUILDLEVEL);
	if (it) 
	{
		it->SetText(guildLevel);
		it->Release();
	}
};
*/

oCMenu_Status::oCMenu_Status(const zSTRING &name) : zCMenu(name)
{
};

void oCMenu_Status::AddArmor(const oSMenuInfoArmor& armor)
{
	m_listArmory.InsertEnd(armor);
}

void oCMenu_Status::AddAttribute(const oSMenuInfoAttribute& attrib)
{
	m_listAttributes.InsertEnd(attrib);
}

void oCMenu_Status::AddTalent		(const oSMenuInfoTalent& talent)
{	
	m_listTalents.InsertEnd(talent);
};





#pragma warning ( disable: 4706 )

void oCMenu_Status::InitForDisplay()
{
	zCMenuItem	*it1,*it2;
	int			i;

	//
	// Attributes
	//	
	for (i=0; i<m_listAttributes.GetNumInList(); i++) 
	{
		it1 = zCMenuItem::GetByName(MENU_ITEM_ATTRIBUTE_PREFIX+"_"+zSTRING(i+1)+"_TITLE");
		it2 = zCMenuItem::GetByName(MENU_ITEM_ATTRIBUTE_PREFIX+"_"+zSTRING(i+1));
		zERR_ASSERTT(it1 && it2,"menuitem for attributes missing");
		
		if (it1) { it1->m_parUserString[0] = m_listAttributes[i].descr;	it1->Release();it1=0; }
		if (it2) { it2->SetText(zSTRING(m_listAttributes[i].actValue)+"/"+zSTRING(m_listAttributes[i].maxValue));it2->Release();it2=0; }
	}

	//
	// Armor
	//

	zSTRING			itemName;
	oSMenuInfoArmor armor;
	for (i=0;i<m_listArmory.GetNumInList();i++)
	{
		itemName = MENU_ITEM_ARMOR_PREFIX + "_" + zSTRING(i+1);
		it1 = zCMenuItem::GetByName(itemName);
		if (it1)
		{
			armor = m_listArmory.GetSafe(i);
			it1->SetText(zSTRING(armor.actValue));
			it1->Release();it1=0;
		};
	};

	//
	// Talente
	//
	zCMenuItemText*	it_text;	
	int count = 1;
	for (i=0; i<m_listTalents.GetNumInList(); i++) 
	{				
		itemName = MENU_ITEM_TALENT_PREFIX + "_" + zSTRING(count);				

		// Soll das Talent überhaupt angezeigt werden, wenn der Skill <=0 ist?
		if (m_listTalents[i].skill<=0)
		{			
			if (m_listTalents[i].skillEnum=="|") continue;
		}

		count++;

		// Talentname		
		it1 = zCMenuItem::GetByName(itemName + "_TITLE");
		if (!it1) continue;
		it1->SetText(m_listTalents[i].name);
		it1->Release();it1=0;
		
		// Talentskill (als Text)			
		it_text = dynamic_cast<zCMenuItemText*>(zCMenuItem::GetByName(itemName + "_SKILL"));		
		if (it_text) 
		{
			it_text->SetEnum(m_listTalents[i].skillEnum);
			if (m_listTalents[i].value>=0) it_text->SetText( zSTRING(m_listTalents[i].skill) ); else it_text->SetText("");
			it_text->Release();it_text=0;
		}

		// Talentwert
		if (m_listTalents[i].value>=0)
		{
			it1 = zCMenuItem::GetByName(itemName);
			if (it1) 
			{
				it1->SetText(zSTRING(m_listTalents[i].value)+"%");
				it1->Release();it1=0;
			}
		}		
	}

};

#pragma warning ( default: 4706 )


//
// Status-Screen
//


oCStatusScreen::oCStatusScreen()
{
	zERR_MESSAGE(6,zERR_BEGIN,"B: STAT: Init Status-Screen ...");		

	m_pStatusMenu = zNEW( oCMenu_Status ("MENU_STATUS") );		

	resultStr.Clear();

	zERR_MESSAGE(6,zERR_END,"");
};

oCStatusScreen::~oCStatusScreen()
{
	zERR_MESSAGE(6,zERR_BEGIN,"B: STAT: Deinit Status-Screen ...");	
		
	zRELEASE(m_pStatusMenu);
	
	HandleResultString(resultStr);

	zERR_MESSAGE(6,zERR_END,"");
};

void oCStatusScreen::Show()
{	
	zERR_MESSAGE(3,zERR_BEGIN,"B: STAT: Entering Status-Screen ...");
	
	zinput->ResetRepeatKey(); // [SPECKELS] Hack, um toggle zu vermeiden

	zBOOL doPause = TRUE;
	
	if (m_pStatusMenu)	
	{
		if (doPause && ogame) ogame->Pause();
		m_pStatusMenu->InitForDisplay();
		m_pStatusMenu->Run();	
		if (doPause && ogame) ogame->Unpause();
	}

	zinput->ResetRepeatKey(); // [SPECKELS] Hack, um toggle zu vermeiden
	
	zERR_MESSAGE(3,zERR_END,"");
};



//
// Log-Screen (Missions and more)
//

oCLogScreen::oCLogScreen()
{
	zERR_MESSAGE(6,zERR_BEGIN,"B: STAT: Init Log-Screen ...");		
		
	m_pLogMenu = zNEW( oCMenu_Log ("MENU_LOG") );		

	zERR_MESSAGE(6,zERR_END,"");
};

oCLogScreen::~oCLogScreen()
{
	zERR_MESSAGE(6,zERR_BEGIN,"B: STAT: Deinit Log-Screen ...");	
		
	zRELEASE(m_pLogMenu);

	zERR_MESSAGE(6,zERR_END,"");
};

void oCLogScreen::Show()
{	
	zERR_MESSAGE(3,zERR_BEGIN,"B: STAT: Entering Log-Screen ...");
	
	zinput->ResetRepeatKey(); // [SPECKELS] Hack, um toggle zu vermeiden
	
	zBOOL doPause = TRUE;

	if (m_pLogMenu)	
	{
		if (doPause && ogame) ogame->Pause();
		m_pLogMenu->InitForDisplay();
		m_pLogMenu->Run();	
		if (doPause && ogame) ogame->Unpause();
	}
	zinput->ResetRepeatKey(); // [SPECKELS] Hack, um toggle zu vermeiden
	
	zERR_MESSAGE(3,zERR_END,"");
};





//
// Map-Screen
//

oCMapScreen::oCMapScreen()
{
	zERR_MESSAGE(6,zERR_BEGIN,"B: STAT: Init Map-Screen ...");

	zERR_MESSAGE(6,zERR_END,"");
};

oCMapScreen::~oCMapScreen()
{
	zERR_MESSAGE(6,zERR_BEGIN,"B: STAT: Deinit Map-Screen ...");

	zERR_MESSAGE(6,zERR_END,"");
};

void oCMapScreen::Show(int mapInst)
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: STAT: Entering Map-Screen ...");

	oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
	if (ogame && world && oCNpc::player) 
	{					
		zSTRING wldName = zSTRING("ITWR_MAP_") + world->GetWorldName();
		oCItem* mapItem = NULL;
		if (mapInst > 0)
			mapItem = oCNpc::player->IsInInv(mapInst);
		if (mapItem == NULL)
			mapItem = oCNpc::player->IsInInv(wldName);
		if (mapItem)
		{
			zSTRING mapName = mapItem->GetInstanceName();
			oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_USEITEM, mapName, -1);
			oCNpc::player->GetEM()->OnMessage(msg, oCNpc::player);
		}
	};

	zERR_MESSAGE(3,zERR_END,"");
};

