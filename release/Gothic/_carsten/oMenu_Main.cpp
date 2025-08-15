#include "zcore.h"
#include "omenu_main.h"
#include "zparser.h"
#include "zWin32.h"
#include "ooCarsten.h"
#include "zoption_const.h"


oCMenu_Main :: oCMenu_Main(const zSTRING &name) : zCMenu(name)
{

};

void oCMenu_Main::ScreenInit()
{
	zCMenu::ScreenInit();
}

void oCMenu_Main::ScreenDone()
{
	zCMenu::ScreenDone();
}

zBOOL oCMenu_Main::HandleEvent(int key) 
{	
	zBOOL leave = zCMenu::HandleEvent(key);	

	if (!leave)
	{
		switch (zinput->GetFirstBindedLogicalKey(key))
		{
			case GAME_STRAFELEFT:	key = KEY_LEFT;	break;
			case GAME_STRAFERIGHT:	key = KEY_RIGHT; break;
		};

		switch (key)
		{
		case KEY_UP:
		case KEY_DOWN:
		case MOUSE_WHEELUP:
		case MOUSE_WHEELDOWN:
			return zCMenu::HandleEvent(key);
			break;
		case KEY_LEFT:
		case KEY_RIGHT:
			leave = TRUE;
			break;
		case KEY_ENTER: 
		case MOUSE_BUTTONLEFT:
			{
				zsound->PlaySound(selectSnd);
				eventOccured[MENU_EVENT_EXECUTE] = TRUE;
				m_exitState					= GO;
				leave						= TRUE;
			}
			break;
		case KEY_ESC:   
		case MOUSE_BUTTONRIGHT:
			leave					  = TRUE;
			break;
		}
	}

	updateTimer += GetTimer()->GetFrameTime();
	if (updateTimer > eventTimerUpdateMSec) 
	{
		updateTimer = 0;
		eventOccured[MENU_EVENT_TIMER] = TRUE;
	}

	return leave;
};


//
// Menu_ChgKeys
//

oCMenu_ChgKeys :: oCMenu_ChgKeys(const zSTRING &name) : zCMenu(name)
{
};

/*

  Alte Version, Pre 1.08
zBOOL oCMenu_ChgKeys::HandleEvent(int key) 
{
	zBOOL result = zCMenu::HandleEvent(key);
	if (key==KEY_DEL) {
		
		if (m_listItems[m_mainSel]->m_parOnSelAction[0] == SEL_ACTION_EXECCOMMANDS ) {
			zSTRING word2 = m_listItems[m_mainSel]->m_parOnSelAction_S[0].PickWord(2, " ");
			if (!word2.IsEmpty()) {
				zCMenuItem *item = zCMenuItem::GetByName(word2);

				zCArray<zWORD>controlValueList;

				if (item->m_parOnChgSetOption == ZOPT_GAMEKEY_UP ||
					item->m_parOnChgSetOption == ZOPT_GAMEKEY_DOWN ||
					item->m_parOnChgSetOption == ZOPT_GAMEKEY_LEFT ||
					item->m_parOnChgSetOption == ZOPT_GAMEKEY_RIGHT)
				{
					if (item->m_parOnChgSetOption == ZOPT_GAMEKEY_UP) {
						controlValueList.Insert(KEY_UP);
					} else if (item->m_parOnChgSetOption == ZOPT_GAMEKEY_DOWN) {
						controlValueList.Insert(KEY_DOWN);
					} else if (item->m_parOnChgSetOption == ZOPT_GAMEKEY_LEFT) {
						controlValueList.Insert(KEY_LEFT);
					} else if (item->m_parOnChgSetOption == ZOPT_GAMEKEY_RIGHT) {
						controlValueList.Insert(KEY_RIGHT);
					}

					item->m_parUserString[0] = zinput->GetNameByControlValue(controlValueList[0]);
					item->m_parUserString[1].Clear();

					item->SetText(item->m_parUserString[0]);
					item->Draw();
					zoptions->WriteRaw(zOPT_SEC_KEYS,item->m_parOnChgSetOption,controlValueList.GetArray(),controlValueList.GetNumInList()<<1);
				} else {
					item->SetText("");
					item->Draw();
					item->m_parUserString[0].Clear();
					item->m_parUserString[1].Clear();
					// zoptions->RemoveEntry(zOPT_SEC_KEYS,item->m_parOnChgSetOption.ToChar());
					zoptions->WriteRaw(zOPT_SEC_KEYS,item->m_parOnChgSetOption,NULL,0);
				}

				zinput->BindKeys(0);
			}
			result = TRUE;
		}
	}
	return result;
};
*/

// [SPECKELS] Patch 2, (V1.08) Neue HandleEvent Funktion für oCMenu_ChgKeys
zBOOL oCMenu_ChgKeys::HandleEvent(int key) 
{
	zBOOL result = zCMenu::HandleEvent(key);
	if (key==KEY_DEL) 
	{		
		if (m_listItems[m_mainSel]->m_parOnSelAction[0] == SEL_ACTION_EXECCOMMANDS ) 
		{
			zSTRING word2 = m_listItems[m_mainSel]->m_parOnSelAction_S[0].PickWord(2, " ");
			if (!word2.IsEmpty()) 
			{
				zCMenuItem *item = zCMenuItem::GetByName(word2);

				zCArray<zWORD>controlValueList;
								
				item->SetText("");
				item->Draw();
				item->m_parUserString[0].Clear();
				item->m_parUserString[1].Clear();
				// [BENDLIN] Addon Patch2 - Empty Key Bindings
				zWORD buffer = 0x0000;
				zoptions->WriteRaw(zOPT_SEC_KEYS,item->m_parOnChgSetOption, &buffer, sizeof(buffer));

				zinput->BindKeys(0);
			}
			result = TRUE;
		}
	}
	return result;
};


/*
 alte Version, pre 1.08
zBOOL oCMenu_ChgKeys::ExecCommand(const zSTRING &s) 
{
	zSTRING word1 =  s.PickWord(1, " ");
	if ( word1 == "RUN" ) {
		zSTRING word2 = s.PickWord(2, " ");
		zCMenuItem *item = zCMenuItem::GetByName(word2); 
		item->SetIsActive(TRUE);
		zWORD key;

		do {
			sysEvent();
			zinput->ProcessInputEvents();
			zCMenu::GetActive()->Render();
			key=zinput->GetKey();

			// keys verbieten:
			switch (key)
			{
				case KEY_ENTER:
				case KEY_PAD_ENTER:
					key=0;
					break;
			}

		} while (key==0 || key&KEY_RELEASE);
		
		if (key!=KEY_ESC)
		{
			zSTRING value = zinput->GetNameByControlValue(key);
			zSTRING newKey= value;
			if (item->m_parUserString[0] != value && item->m_parUserString[1] != value &&
				(value != zinput->GetNameByControlValue(KEY_UP)) &&
				(value != zinput->GetNameByControlValue(KEY_DOWN)) &&
				(value != zinput->GetNameByControlValue(KEY_LEFT)) &&
				(value != zinput->GetNameByControlValue(KEY_RIGHT))) {
				if (item->m_parUserString[0].IsEmpty()) {
					item->m_parUserString[0] = newKey;
				} else {
					if (item->m_parUserString[1].IsEmpty()) {
						item->m_parUserString[1] = newKey;
					} else {
						if (item->m_parOnChgSetOption == ZOPT_GAMEKEY_UP ||
							item->m_parOnChgSetOption == ZOPT_GAMEKEY_DOWN ||
							item->m_parOnChgSetOption == ZOPT_GAMEKEY_LEFT ||
							item->m_parOnChgSetOption == ZOPT_GAMEKEY_RIGHT)
						{
							item->m_parUserString[1] = newKey;
						} else {
							item->m_parUserString[0] = item->m_parUserString[1];
							item->m_parUserString[1] = newKey;
						}
					}
				}
				newKey = item->m_parUserString[1].IsEmpty() ? item->m_parUserString[0] : item->m_parUserString[0] + ", " + item->m_parUserString[1];
				item->SetText(newKey);
				item->Draw();
				for (int i=0; i<m_listItems.GetNumInList(); i++) {
					if (m_listItems[i] == item) continue;
					if (m_listItems[i]->m_parUserString[0] == value || m_listItems[i]->m_parUserString[1] == value) {
						if (m_listItems[i]->m_parUserString[0] == value) {
							if (!m_listItems[i]->m_parUserString[1].IsEmpty()) {
								m_listItems[i]->m_parUserString[0] = m_listItems[i]->m_parUserString[1];
								m_listItems[i]->m_parUserString[1].Clear();
								newKey = m_listItems[i]->m_parUserString[1].IsEmpty() ? m_listItems[i]->m_parUserString[0] : m_listItems[i]->m_parUserString[0] + ", " + m_listItems[i]->m_parUserString[1];
							}
							else {
								m_listItems[i]->m_parUserString[0].Clear();
								m_listItems[i]->m_parUserString[1].Clear();
								newKey = "???";
							}
						}
						else {
							m_listItems[i]->m_parUserString[1].Clear();
							newKey = m_listItems[i]->m_parUserString[0];
						}
						m_listItems[i]->SetText(newKey);
						m_listItems[i]->Draw();
					}
				}

				zCArray<zWORD>controlValueList;
				controlValueList.Insert(zinput->GetControlValueByName(item->m_parUserString[0]));
				if(!item->m_parUserString[1].IsEmpty()) controlValueList.Insert(zinput->GetControlValueByName(item->m_parUserString[1]));
				zoptions->WriteRaw(zOPT_SEC_KEYS,item->m_parOnChgSetOption,controlValueList.GetArray(),controlValueList.GetNumInList()<<1);
				zinput->BindKeys(0);
			}
		}
		item->SetIsActive(FALSE);
	}
	else if ( word1 == "SETDEFAULT" ) {
		for (int i=0; i<m_listItems.GetNumInList(); i++) {
			if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) {
				zoptions->RemoveEntry(zOPT_SEC_KEYS,m_listItems[i]->m_parOnChgSetOption.ToChar());
			}
		}
		zinput->BindKeys(0);
		InitText();
		for (i=0; i<m_listItems.GetNumInList(); i++) {
			if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) m_listItems[i]->Draw();
		}
	}	
	else if ( word1 == "SETALTERNATIVE" ) {
		for (int i=0; i<m_listItems.GetNumInList(); i++) {
			if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) {
				zoptions->RemoveEntry(zOPT_SEC_KEYS,m_listItems[i]->m_parOnChgSetOption.ToChar());
			}
		}
		zinput->BindKeys(1);
		InitText();
		for (i=0; i<m_listItems.GetNumInList(); i++) 
		{
			if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) m_listItems[i]->Draw();
		}
	};
	
	return TRUE;
};
*/

////////////////////////////////////////////////////////////////////////////////
//
//	oCMenu_ChgKeys::ExecCommand
//
//				[SPECKELS]
//
//				Patch 2 (V1.08), Neue Version von oCMenu_ChgKeys::ExecCommand()
//
//	2002-05-11	[BENDLIN]
//
//				filter unnamed keys
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCMenu_ChgKeys::ExecCommand(const zSTRING &s) 
{
	zSTRING word1 =  s.PickWord(1, " ");
	if ( word1 == "RUN" ) {
		zSTRING word2 = s.PickWord(2, " ");
		zCMenuItem *item = zCMenuItem::GetByName(word2); 
		item->SetIsActive(TRUE);
		zWORD key;

		do {
			sysEvent();
			zinput->ProcessInputEvents();
			zCMenu::GetActive()->Render();
			key=zinput->GetKey();

			// [BENDLIN] filter unnamed keys
			if ( zinput->GetNameByControlValue(key) == "" ) key = 0;

			// keys verbieten:
			switch (key)
			{
				case KEY_ENTER:
				// [EDENFELD] Version 1.09. folgende Zeile wegen Compiler Prob auskommentiert (beide werte sind '13')
//				case KEY_PAD_ENTER:
					key=0;
					break;
			}

		} while ((key==0) || (key&KEY_RELEASE));

		// [EDENFELD] 1.09
		zinput->ClearKeyBuffer();
		
		if (key!=KEY_ESC)
		{
			zSTRING value = zinput->GetNameByControlValue(key);
			zSTRING newKey= value;
			if (item->m_parUserString[0] != value && item->m_parUserString[1] != value)
			{
				if (item->m_parUserString[0].IsEmpty()) 
				{
					item->m_parUserString[0] = newKey;
				} 
				else 
				{
					if (item->m_parUserString[1].IsEmpty()) 
					{
						item->m_parUserString[1] = newKey;
					} 
					else 
					{
						item->m_parUserString[0] = item->m_parUserString[1];
						item->m_parUserString[1] = newKey;						
					}
				}

				// [BENDLIN] Addon Patch2 - Empty Key Bindings
				zWORD nokeys = 0x0000;

				newKey = item->m_parUserString[1].IsEmpty() ? item->m_parUserString[0] : item->m_parUserString[0] + ", " + item->m_parUserString[1];
				item->SetText(newKey);
				item->Draw();
				for (int i=0; i<m_listItems.GetNumInList(); i++) {
					if (m_listItems[i] == item) continue;
					if (m_listItems[i]->m_parUserString[0] == value || m_listItems[i]->m_parUserString[1] == value) {
						if (m_listItems[i]->m_parUserString[0] == value) {
							if (!m_listItems[i]->m_parUserString[1].IsEmpty()) {
								m_listItems[i]->m_parUserString[0] = m_listItems[i]->m_parUserString[1];
								m_listItems[i]->m_parUserString[1].Clear();
								newKey = m_listItems[i]->m_parUserString[0];
								// [BENDLIN] Addon Patch2 - Empty Key Bindings
								zCArray<zWORD>newCVL;
								newCVL.EmptyList();
								newCVL.Insert(zinput->GetControlValueByName(newKey));
								zoptions->WriteRaw(zOPT_SEC_KEYS, m_listItems[i]->m_parOnChgSetOption, newCVL.GetArray(), newCVL.GetNumInList()<<1);
							}
							else {
								m_listItems[i]->m_parUserString[0].Clear();
								m_listItems[i]->m_parUserString[1].Clear();
								newKey = "";
								// [BENDLIN] Addon Patch2 - Empty Key Bindings
								zoptions->WriteRaw(zOPT_SEC_KEYS, m_listItems[i]->m_parOnChgSetOption, &nokeys, sizeof(nokeys));
							}
						}
						else {
							m_listItems[i]->m_parUserString[1].Clear();
							newKey = m_listItems[i]->m_parUserString[0];
							// [BENDLIN] Addon Patch2 - Empty Key Bindings
							zCArray<zWORD>newCVL;
							newCVL.EmptyList();
							newCVL.Insert(zinput->GetControlValueByName(newKey));
							zoptions->WriteRaw(zOPT_SEC_KEYS, m_listItems[i]->m_parOnChgSetOption, newCVL.GetArray(), newCVL.GetNumInList()<<1);
						}
						m_listItems[i]->SetText(newKey);
						m_listItems[i]->Draw();
					}
				}

				zCArray<zWORD>controlValueList;
				// [BENDLIN] Addon Patch2 - Empty Key Bindings
				if (!item->m_parUserString[0].IsEmpty())
					controlValueList.Insert(zinput->GetControlValueByName(item->m_parUserString[0]));
				if (!item->m_parUserString[1].IsEmpty())
					controlValueList.Insert(zinput->GetControlValueByName(item->m_parUserString[1]));
				if (controlValueList.IsEmpty())
					zoptions->WriteRaw(zOPT_SEC_KEYS,item->m_parOnChgSetOption, &nokeys, sizeof(nokeys));
				else
					zoptions->WriteRaw(zOPT_SEC_KEYS,item->m_parOnChgSetOption,controlValueList.GetArray(),controlValueList.GetNumInList()<<1);
				zinput->BindKeys(0);
			}
		}
		item->SetIsActive(FALSE);
	}
	else if ( word1 == "SETDEFAULT" ) {
		for (int i=0; i<m_listItems.GetNumInList(); i++) {
			if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) {
				zoptions->RemoveEntry(zOPT_SEC_KEYS,m_listItems[i]->m_parOnChgSetOption.ToChar());
			}
		}
		zinput->BindKeys(0);
		InitText();
		for (i=0; i<m_listItems.GetNumInList(); i++) {
			if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) m_listItems[i]->Draw();
		}
	}	
	else if ( word1 == "SETALTERNATIVE" ) {
		for (int i=0; i<m_listItems.GetNumInList(); i++) {
			if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) {
				zoptions->RemoveEntry(zOPT_SEC_KEYS,m_listItems[i]->m_parOnChgSetOption.ToChar());
			}
		}
		zinput->BindKeys(1);
		InitText();
		for (i=0; i<m_listItems.GetNumInList(); i++) 
		{
			if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) m_listItems[i]->Draw();
		}
	};
	
	return TRUE;
};





void oCMenu_ChgKeys::ScreenInit ()
{
	if (m_screenInitDone) return;

	InitText();
	zCMenu::ScreenInit();

};

void oCMenu_ChgKeys::Leave()
{	
	zCMenu::Leave();
	void*buffer=0;
	zDWORD bindSize;
	for (int i=0; i<m_listItems.GetNumInList(); i++) {
		if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) {
			bindSize = zoptions->ReadRaw(zOPT_SEC_KEYS,m_listItems[i]->m_parOnChgSetOption.ToChar(),buffer);
			if (bindSize == 0)
				zoptions->RemoveEntry(zOPT_SEC_KEYS,m_listItems[i]->m_parOnChgSetOption.ToChar());
		}
	}
	zinput->BindKeys(0);
};

void oCMenu_ChgKeys::InitText()
{
	void*buffer=0;
	zDWORD bindSize;
	for (int i=0; i<m_listItems.GetNumInList(); i++) {
		if (!m_listItems[i]->m_parOnChgSetOption.IsEmpty()) {
			bindSize = zoptions->ReadRaw(zOPT_SEC_KEYS,m_listItems[i]->m_parOnChgSetOption.ToChar(),buffer);
			// if (bindSize == 0) zERR_FATAL("C: oCMenu_ChgKeys::InitText(): could not read buffer for key: " + m_listItems[i]->m_parOnChgSetOption);

			m_listItems[i]->m_parUserString[0] = "";
			m_listItems[i]->m_parUserString[1] = "";

			for (int j=0; j<bindSize>>1; j++) {
				m_listItems[i]->m_parUserString[j] = zinput->GetNameByControlValue(((zWORD*)buffer)[j]);
			}
			m_listItems[i]->SetText(m_listItems[i]->m_parUserString[1].IsEmpty() ? m_listItems[i]->m_parUserString[0] : m_listItems[i]->m_parUserString[0] + ", " + m_listItems[i]->m_parUserString[1]);

			delete[] buffer;
		}
	}
};


