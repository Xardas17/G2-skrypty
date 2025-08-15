/******************************************************************************** 
 
     $Workfile:: Zmenu.cpp            $                $Date:: 15.03.01 14:01   $
     $Revision:: 91                   $             $Modtime:: 13.03.01 17:55   $
        Author:: Edenfeld
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   UI/GUI Menu class
   created: 25.5.2000

 * $Log: /current_work/ZenGin/_Carsten/Zmenu.cpp $
 * 
 * 91    15.03.01 14:01 Speckels
 * 
 * 90    17.02.01 19:12 Speckels
 * 
 * 89    16.02.01 21:19 Speckels
 * 
 * 88    6.02.01 11:43 Moos
 * 
 * 87    6.02.01 4:57 Speckels
 * 
 * 86    6.02.01 2:28 Speckels
 * 
 * 85    5.02.01 23:16 Speckels
 * 
 * 84    1.02.01 19:27 Speckels
 * 
 * 83    1.02.01 15:09 Speckels
 * 
 * 82    31.01.01 18:23 Speckels
 * 
 * [...]
 * 
 * 47    29.11.00 12:52 Speckels
 * 
 * 46    24.11.00 18:30 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Edenfeld
/// @version $Revisio: 2 $ ($Modtime: 13.03.01 17:55 $)

// =======================================================================================================================

#include "zcore.h"
#include "zWin32.h"
#include "zoption.h"

#include "zmenu.h"
#include "zparser.h"
#include "zmusic.h"
#include "zconsole.h"
#include "zfonts.h"

#ifdef PlaySound
#undef PlaySound
#include "zsound.h"
#endif


//
// static member
//

zCArray<zCMenu*> 		zCMenu::activeList;
zCArraySort<zCMenu*>	zCMenu::menuList;
zCParser*				zCMenu::menuParser 		= 0;	
zCWorld*				zCMenu::world  			= 0;
zCCamera*   			zCMenu::camera 			= 0;
zCTimer*				zCMenu::timer  			= 0;
zBOOL 					zCMenu::inGameMenu		= FALSE;

typedef void (*CallBack)();

CallBack				zCMenu::EnterCallback 	= 0;
CallBack				zCMenu::LeaveCallback 	= 0;
CallBack				zCMenu::FrameCallback 	= 0;

zCSoundFX*				zCMenu::browseSnd 		= 0;
zCSoundFX*				zCMenu::selectSnd 		= 0;
zCSoundFX*				zCMenu::escSnd			= 0;

zCVob*					zCMenu::soundSourceVob	= 0;

static zCSoundFX*	enterSound = 0;
static zCSoundFX*	startSound = 0;
static zBOOL		firstTime  = TRUE;


int zCMenu::CompareNames( const void *e1 ,const void *e2) 
{
	return strcmp( (*(zCMenu**)e2)->GetName().ToChar(),(*(zCMenu**)e1)->GetName().ToChar());
}

void zCMenu::CreateParser()
{
	zoptions->ChangeDir(DIR_SCRIPTS);
	if (!menuParser) menuParser = zNEW( zCParser );	
};

void zCMenu::Startup()
{
	zERR_MESSAGE(4,zERR_BEGIN,"C: MENU: Initializing menusystem");
		
	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "Menu");
	if (filename.IsEmpty())
		filename = "System\\Menu";
	zERR_MESSAGE(4, 0, "N: MENU: Loading file " + filename + ".src or .dat");

	#ifdef DEBUG_SPECKELS 
		zBOOL parsingEnabled = zCParser::GetEnableParsing();
		zCParser::SetEnableParsing(TRUE);
	#endif	

	menuParser->Parse		(filename + ".src");
	menuParser->CreatePCode	();

	#ifdef DEBUG_SPECKELS
		zCParser::SetEnableParsing(parsingEnabled);
	#endif

	menuList.SetCompare(CompareNames);
	if (zsound)
	{
		browseSnd 	= zsound->LoadSoundFXScript("MENU_BROWSE");
		selectSnd 	= zsound->LoadSoundFXScript("MENU_SELECT");
		escSnd		= zsound->LoadSoundFXScript("MENU_ESC");
		// soundSourceVob = zNEW(zCVob());
	}

	timer	= zNEW( zCTimer );

	zCMenuItem::Startup();

	zERR_MESSAGE(4,zERR_END,"");
};

void zCMenu::Shutdown()
{
    while (menuList.GetNum())
    {
        menuList[menuList.GetNum()-1]->m_listItems.DeleteList();
        delete menuList[menuList.GetNum()-1];    
    }

    zCMenuItem::Shutdown();

	// zRELEASE(soundSourceVob);
	zRELEASE(browseSnd);    
	zRELEASE(selectSnd);    
	zRELEASE(escSnd);
	    
    delete timer;		timer = 0;
};




//
// construct, initialize and destruct
//

zCMenu::zCMenu()  
{ 				
	InitValues	();
	SetName	("MENU_UNDEFINED");
};

zCMenu::zCMenu(const zSTRING &scriptName)  
{ 		
	InitValues	();
	SetName	(scriptName);
	RegisterCPP	();
	SetByScript	(scriptName);	
};

zCMenu::~zCMenu() 
{  	
	// Menueitems freigeben
	for (int i=0; i<m_listItems.GetNumInList(); i++) 
	{
		if (m_listItems[i]) 
		{ 
			m_listItems[i]->Release();
			m_listItems[i]=0; 			
		}
	};
	m_listItems.DeleteList();

	Unregister();
	delete m_musicTheme;m_musicTheme = 0;	
	
};


void zCMenu::InitValues()
{
	m_screenInitDone		= FALSE;
	m_pInnerWindow			= 0;
	m_pWindow				= 0;
	m_mainSel				= -1;
	m_pViewInfo				= 0;
	eventTimerUpdateMSec	= 0;
	updateTimer				= 0;
	fxTimer					= 0;
	m_exitState				= NONE;
	cursorEn				= TRUE;
	registeredCPP			= FALSE;
	forcedSelAction			= FALSE;
	noneSelectable			= FALSE;		
	defaultOutGame			= 0;
	defaultInGame			= 0;
	posx					= 0; 
	posy					= 0;
	dimx					= 8191;
	dimy					= 8191;	
	alpha					= 255;
	eventTimerUpdateMSec	= 1000;
	flags					= 0;
	forceSelAction			= SEL_ACTION_UNDEF;
	forceSelActionItem		= 0;	
	backPic					.Clear();
	backWorld				.Clear();	
	forceSelAction_S		.Clear();
	name					.Clear();
	musicThemeName			.Clear();
	m_musicTheme			= 0;	
	
	for (int i=0; i<MAX_ITEMS; i++)			itemID[i].Clear();
	for (int j=0; j<MENU_EVENT_MAX; j++)	eventOccured[j] = FALSE;

	ClearAllEvents			();
};


void zCMenu::Release()
{
	zBOOL result = IsRegisteredCPP();
	SetEnableHandleEvent(FALSE);
	if (!result) delete this;
};


void zCMenu::DefineExternal( zSTRING &s, zBOOL (*Proc)(), int type, int args... )
{
	zERR_ASSERT(menuParser);
	menuParser->DefineExternal(s,Proc,type,args);
};

zCMenu *zCMenu::Create(const zSTRING &name)
{
	zCMenu *menu = GetByName(name); // [Moos] Mal sehen, ob das geht. Bisher war es deaktiviert....
	if (!menu) 
	{
		menu = zNEW( zCMenu );
		menu->SetByScript(name);
	}
	return menu;
};

void zCMenu::Register()
{
    if (!menuList.IsInList(this)) // [Moos] doppelte Einträge sind tödlich
	    menuList.InsertSort(this);
};

void zCMenu::Unregister()
{
	menuList.RemoveOrder(this);
};

zBOOL zCMenu::IsRegistered()
{
	return (menuList.Search(this) != -1);
};

zCParser *zCMenu::GetParser()
{
	return menuParser;
};

zCMenu* zCMenu::GetByName(const zSTRING &name)
{
	zCMenu searchMenue;
	zSTRING id = name;
	searchMenue.SetName(id);
	int index = menuList.Search(&searchMenue);
	searchMenue.SetName("TMPITEM");
	
 	return (index>=0) ? menuList[index] : 0;
};

void zCMenu::SetByScript(const zSTRING &identifier)
{
	zBOOL extendedMenu = zoptions->ReadBool(zOPT_SEC_INTERNAL,"extendedMenu",FALSE);

	name = identifier;
	name.Upper();
	
	if (menuParser->GetSymbol(name)) 
	{	
		for (int i=0; i<MAX_ITEMS; i++) itemID[i].Clear();
		
		menuParser->CreateInstance(name, &backPic);

		// Menueitems
		m_mainSel = -1;
		for (i=0; i<MAX_ITEMS; i++) 
			if ( !itemID[i].IsEmpty() ) 
			{
				zCMenuItem* item = zCMenuItem::Create(itemID[i]);
				m_listItems.InsertEnd(item);	
				if (!extendedMenu && (item->GetMenuItemFlags() & IT_EXTENDED_MENU)) item->SetIsVisible(FALSE);				
				if  (m_mainSel!=-1 && item->GetIsSelectable()) m_mainSel = i;				
			};
			
		// Registrieren
		Register();		
	} 
	else 
	{
		zERR_WARNING("C: zmenu.cpp(zCMenu::SetByScript): Menu item unknown: " + name);
	}
};


void zCMenu::ClearAllEvents()
{
	for (int i=0; i<MENU_EVENT_MAX; i++) 
	{
		eventOccured[i] = FALSE;
	}
};

void zCMenu::PreviousOption()
{
	if (m_listItems.GetNumInList()<=0)	return;
	if (m_mainSel<0)					return;

	m_listItems[m_mainSel]->SetIsActive(FALSE);  // altes Item deaktivieren

	int anz = 0;	
	int opt = m_mainSel;
	while (anz++ < m_listItems.GetNumInList()) 
	{		
		if  (--opt < 0) opt = m_listItems.GetNumInList()-1;
		if  (m_listItems[opt]->GetIsSelectable()) break;
	};

	if (m_mainSel!=opt)
	{
		if (m_mainSel!=-1) HandleLeaveItem(m_listItems[m_mainSel]);
		m_mainSel = opt;
		if (m_mainSel!=-1) HandleEnterItem(m_listItems[m_mainSel]);
	}

	if (cursorEn) m_listItems[m_mainSel]->SetIsActive(TRUE);
}

void zCMenu::NextOption()
{	
	if (m_listItems.GetNumInList()<=0) 	return;
	if (m_mainSel<0)					return;

	m_listItems[m_mainSel]->SetIsActive(FALSE);  // altes Item deaktivieren

	int anz = 0;	
	int opt = m_mainSel;
	while ( anz++ <  m_listItems.GetNumInList() ) 
	{		
		if  (++opt >= m_listItems.GetNumInList()) opt = 0;
		if  (m_listItems[opt]->GetIsSelectable()) break;	
	};

	if (m_mainSel!=opt)
	{
		if (m_mainSel!=-1) HandleLeaveItem(m_listItems[m_mainSel]);
		m_mainSel = opt;
		if (m_mainSel!=-1) HandleEnterItem(m_listItems[m_mainSel]);
	}

	if (cursorEn) { m_listItems[m_mainSel]->SetIsActive(TRUE); }
}

void zCMenu::RestartMusicTheme()
{
	if (!IsInGame()) zmusic->PlayThemeByScript(musicThemeName);	
};

void zCMenu::Enter()
{
	if (EnterCallback) EnterCallback();

	if (!IsInGame()) 
	{
		zmusic->PlayThemeByScript(musicThemeName);	
		if (!enterSound) 
		{
			enterSound = zsound->LoadSoundFXScript("GAMESTART");

			if (enterSound) 
				enterSound->SetIsFixed(TRUE);			// darf nicht bei "NEW_GAME" gelöscht werden
		}
		if (firstTime) 
		{
			zsound->PlaySound(enterSound);
			firstTime = FALSE;
		}
	}

	ScreenInit();
	
	if (m_mainSel!=-1) HandleEnterItem(m_listItems[m_mainSel]);

	zinput->ClearKeyBuffer();
};

void zCMenu::Leave()
{
	if (m_mainSel!=-1) HandleLeaveItem(m_listItems[m_mainSel]);

	ScreenDone();

	if (LeaveCallback) LeaveCallback();

	zinput->ClearKeyBuffer();

	zRELEASE(enterSound);
	zRELEASE(startSound);
};

zBOOL zCMenu::Run()
{		
	m_exitState = NONE;		

	activeList.InsertEnd(this);
	Activate();	
	
	Enter();	

	if (m_exitState == NONE) 
	{
		do 
		{
			m_exitState=NONE;									
			do { HandleFrame(); } while (m_exitState==NONE);

		} while (!HandleAction());
	}
	
	Leave();

	activeList.RemoveOrder(this);

	return (m_exitState==GO);
};


const int __waitTime = 200;
int __lastSelection = 0;

zBOOL zCMenu::HandleEvent(int key)
{
	zBOOL leave = FALSE;

	zBOOL loopToggling = FALSE;
	zCMenuItem* effectMenuItem = 0;
	if (m_mainSel>=0)
	{
		effectMenuItem = m_listItems[m_mainSel];
		if (effectMenuItem->GetMenuItemFlags() & IT_EFFECTS_NEXT)
		{			
			if (m_mainSel + 1 != m_listItems.GetNumInList()) 			
				effectMenuItem = m_listItems[m_mainSel+1];
		};
	}

/*	// Logische Tasten (keybindings)
	switch (zinput->GetFirstBindedLogicalKey(key))
	{		
		case GAME_STRAFELEFT:	key=KEY_LEFT;						break;
		case GAME_STRAFERIGHT:	key=KEY_RIGHT;						break;
		case GAME_UP:			key=KEY_UP;							break;
		case GAME_DOWN:			key=KEY_DOWN;						break;		
	}; */

	// Map some keys
	switch (key)
	{
		case KEY_SPACE:			key=KEY_RIGHT;loopToggling=TRUE;	break;
		case KEY_TAB:			key=KEY_DOWN;						break;
		case MOUSE_BUTTONLEFT:	key=KEY_ENTER;						break;
		case MOUSE_BUTTONRIGHT:	key=KEY_ESC;						break;
		case MOUSE_WHEELDOWN:	key=KEY_DOWN;						break;
		case MOUSE_WHEELUP:		key=KEY_UP;							break;
	}


	//
	// Handle keys
	//
	

	switch (key)
	{
	case KEY_UP:
		{
			PreviousOption();
			if (browseSnd) zsound->PlaySound(browseSnd);
			eventOccured[MENU_EVENT_SEL_PREV]	= TRUE;
			leave = TRUE;
			__lastSelection = ztimer.GetTotalTime();
		}
		break;
	case KEY_DOWN:
		{
			NextOption();
			if (browseSnd) zsound->PlaySound(browseSnd);
			eventOccured[MENU_EVENT_SEL_NEXT]	= TRUE;
			leave = TRUE;
			__lastSelection = ztimer.GetTotalTime();
		}
		break;
	case KEY_LEFT:
		{   						
			if (effectMenuItem) effectMenuItem->ToggleValue(-1,loopToggling);
			leave = TRUE;
		}
		break;
	case KEY_RIGHT:		
		{
			if (effectMenuItem) effectMenuItem->ToggleValue(+1,loopToggling);
			leave = TRUE;
		}
		break;
	case KEY_ENTER: 
		if (m_mainSel>=0)
		{			
			if (selectSnd) zsound->PlaySound(selectSnd);
			HandleActivateItem(m_listItems[m_mainSel]);
			eventOccured[MENU_EVENT_EXECUTE]	= TRUE; // TODO: Run ueberschreiben
			m_exitState				= GO;
			leave = TRUE;
		}		
		break;
	case KEY_ESC:  
		{
			if (escSnd) zsound->PlaySound(escSnd);
			
			eventOccured[MENU_EVENT_LEAVE]	= TRUE;
			leave							= TRUE;
			m_exitState						= BACK;
		}
		break;
	}

	// TODO: Timer entfernen?
	updateTimer += GetTimer()->GetFrameTime();
	if (updateTimer > eventTimerUpdateMSec) 
	{
		updateTimer = 0;
		eventOccured[MENU_EVENT_TIMER] = TRUE;
	}
	return TRUE;	
};

void zCMenu::ForceSelAction	(const zTMenuItemSelAction selAction,const zSTRING &selAction_S, zCMenuItem *item )
{
	switch (selAction) {  
	  case SEL_ACTION_BACK: 
	   m_exitState   = BACK;
	   break;
	  default: 
	   m_exitState   = GO;
	   break;
	 }

	forcedSelAction		= TRUE;
	forceSelAction		= selAction;
	forceSelAction_S	= selAction_S;
	forceSelActionItem	= item;
};

void zCMenu::Activate()
{
	if (m_pInnerWindow) 
	{
		SetEnableHandleEvent(TRUE);
		SetHandleEventTop();
	}

	for (int i=0; i<m_listItems.GetNumInList(); i++) 
	{
		if (!m_listItems[i]->m_parHideIfOptionSet.IsEmpty())  
		{
			// assert: items die auf optionen reagieren sind per default nicht disabled!
			if (zoptions->ReadInt(m_listItems[i]->m_parHideIfOptionSectionSet, m_listItems[i]->m_parHideIfOptionSet)==m_listItems[i]->m_parHideOnValue) 
			{
				m_listItems[i]->SetReallyDoNotRender(TRUE);
			}
			else 
			{
				m_listItems[i]->SetReallyDoNotRender(FALSE);
			};
		};
	}
};

void zCMenu::UpdateWindowGeometry()
{
	m_use_dimx=dimx; m_use_dimy=dimy;
	m_use_posx=posx; m_use_posy=posy;	

	// Dimension nicht skalieren? Als Referenz gillt 640x480
	if (flags & MN_DONTSCALE_DIM)
	{
		float screenx = float(screen->nax(8192));
		float screeny = float(screen->nay(8192));
		float multx = 640.0f/screenx;
		float multy = 480.0f/screeny;
		m_use_dimx = int(dimx * multx);
		m_use_dimy = int(dimy * multy);
	};

	// Position neu berechnen?
	if (flags & MN_ALIGN_CENTER)
	{
		m_use_posx = (8192 / 2) - (m_use_dimx/2);
		m_use_posy = (8192 / 2) - (m_use_dimy/2);
	} 
	else 	
	// Position nicht skalieren?
	if (flags & MN_DONTSCALE_DIM)
	{
		float screenx = float(screen->nax(8192));
		float screeny = float(screen->nay(8192));
		float multx = 640.0f/screenx;
		float multy = 480.0f/screeny;
		m_use_posx = int(posx * multx);
		m_use_posy = int(posy * multy);
	};
};

void zCMenu::HandleFrame(zBOOL render)
{
	if (flags & MN_DONTSCALE_DIM)
	{
		if (m_pInnerWindow)
		{
			UpdateWindowGeometry();

			m_pInnerWindow->SetPos	( m_use_posx, m_use_posy );
			m_pInnerWindow->SetSize	( m_use_dimx, m_use_dimy );

			m_pInnerWindow->RecalcChildsSize();
			m_pInnerWindow->RecalcChildsPos();

			render=TRUE;
		}
	}

	sysEvent();			

	zCView::GetInput();

	if (render) Render();						
};

// TODO: Komplettes Verstehen
zBOOL zCMenu::HandleAction()
{		
	if (m_exitState==NONE)		return FALSE; 	// TODO ??
	if (m_exitState==BACK)		return TRUE;	// Menue verlassen
	if (m_exitState==FINISHED)	return TRUE;	// Menue beenden

	zBOOL leave=FALSE;		

	// forced selection-action
	if (forcedSelAction) 
	{
		forcedSelAction = FALSE;
		leave = HandleSelAction(forceSelAction, forceSelAction_S, forceSelActionItem);
	}
	// Aktionen des Items
	else if (m_mainSel>=0)
	{
		if (!m_listItems.GetNumInList()) return FALSE;
		
		int num = 0;
		while ( m_listItems[m_mainSel]->GetSelActionType(num) != SEL_ACTION_UNDEF) 
		{			
			if (
				HandleSelAction
				(
					m_listItems[m_mainSel]->GetSelActionType(num),
					m_listItems[m_mainSel]->GetSelActionString(num)
				)
			) leave = TRUE;
			
			if (m_listItems[m_mainSel]->HasBeenCanceled())	break;

			HandleFrame(FALSE); // TODO: warum?			

			num++;			
			if (num == MAX_SEL_ACTIONS)						break;
		}
	}
		
	// Fuehre Events aus 
	if (!leave && m_mainSel>=0 && !m_listItems[m_mainSel]->HasBeenCanceled())
	{
		for (int flag=MENU_EVENT_EXECUTE;flag<MENU_EVENT_MAX;flag++)
		{
			if ( eventOccured[flag] && m_listItems[m_mainSel]->GetEventFunc((zTMenuItemEvent)flag) ) 
			{
				zBOOL *exit = (zBOOL*) menuParser->CallFunc( m_listItems[m_mainSel]->GetEventFunc((zTMenuItemEvent)flag) );
				if (*exit) leave=TRUE;
			}
			HandleFrame(FALSE); // FALSE = Don't render
			flag ++;
		};
	}

	ClearAllEvents();

	SetEnableHandleEvent(TRUE);
	
	return leave;
}

zBOOL zCMenu::HandleSelAction(const zTMenuItemSelAction selAction,const zSTRING &selAction_S, zCMenuItem *item)
{
	zBOOL leave = FALSE;
	zCMenuItem *selItem = item;
	if (!selItem) selItem = m_listItems[m_mainSel];

	switch ( selAction ) 
	{		

	//
	// Konsolen-Befehl
	//
	case  SEL_ACTION_CONCOMMANDS:
		{
			zSTRING command = selAction_S;
			zSTRING next;
			int cnr = 1;
			while ((next = command.PickWord(cnr++,"|","|")) != zSTRING("")) {
				next.Upper();
				zcon.Evaluate(next);
			}
		}
		break;
	
	//
	// Untermenue starten
	//
	case SEL_ACTION_STARTMENU:
		{
			zCMenu *subMenu = zCMenu::Create(selAction_S);
			zBOOL exclusive = subMenu->IsExclusive();
			
			if (exclusive) ScreenDone();
			
			leave = subMenu -> Run();	
			subMenu->Release();

			if (exclusive) ScreenInit();			
		}
		break;

	//
	// Ein Menueitem aktivieren
	//	
	case SEL_ACTION_STARTITEM:
		{
			zCMenuItem *subItem = zCMenuItem::Create(selAction_S);
			if (!subItem) break;

			if ( !subItem->IsInserted() ) // TODO: Konflikt mit Hide/Show?
			{ 
				subItem->InsertInWin(m_pInnerWindow);		
				leave = subItem -> Run();
				
				eventOccured[MENU_EVENT_CHANGED] = subItem->Changed() && !subItem->HasBeenCanceled();
				int flag = MENU_EVENT_EXECUTE;
				do 
				{
					if ( eventOccured[flag] ) 
					if ( m_listItems[m_mainSel]->GetEventFunc((zTMenuItemEvent) flag) != 0 ) {
						zBOOL *exit = (zBOOL*) menuParser->CallFunc( m_listItems[m_mainSel]->GetEventFunc((zTMenuItemEvent)flag) );
						if (*exit) leave=TRUE;
					}
					HandleFrame();
					flag ++;

				} while (flag != MENU_EVENT_MAX);
				subItem->RemoveFromWin();
			}
			else 
			{
				leave = subItem -> Run();
				eventOccured[MENU_EVENT_CHANGED] = subItem->Changed() && !subItem->HasBeenCanceled();
			}			

			subItem->Release();
		}
		break;

	//
	// Einen Sound spielen
	//	
	case SEL_ACTION_PLAY_SOUND:
		{
			// FIXME: Ein Soundhandler muss diese Sounds löschen!
			// 
			zCSoundFX *snd = zsound->LoadSoundFXScript(selAction_S);
			if (snd) zsound->PlaySound(snd);
			zRELEASE(snd);
		}
		break;

	//
	// Das gesamte Menue schliessen
	//	
	case SEL_ACTION_CLOSE:
		{
			zoptions->WriteString(zOPT_SEC_INTERNAL,zSTRING("menuAction"),selAction_S);
			// FIXME: Teufelswerk! Gothic 2 specific (wirklich übel) feel free to comment this piece of crap
			if (selAction_S=="NEW_GAME")
			{
				if (!IsInGame()) 
				{
					if (!startSound) 
					{
						startSound = zsound->LoadSoundFXScript("NEWGAME");
						if (startSound) startSound->SetIsFixed(TRUE);
					}
					zsound->PlaySound(startSound);
				}
			}
			leave = TRUE;
		}
		break;

	//
	// Zum vorherigen Menue zurueckkehren
	//	
	case SEL_ACTION_BACK:
		{
			leave	  = TRUE;
			m_exitState = BACK;
		}
		break;

	//
	// Einen speziellen Befehl ausfuehren
	//	
	case  SEL_ACTION_EXECCOMMANDS:
		{
			ExecCommand(selAction_S);
		}
		break;
	}
	return leave;
};

zBOOL zCMenu::ExecCommand(const zSTRING &s)
{
	zSTRING command = s.PickWord(1," "," ");
	zSTRING parm1	= s.PickWord(2," "," ");
	return FALSE;
};


void zCMenu::RedrawItems()
{	
	for (int i=0; i<m_listItems.GetNumInList(); i++) 
	{	
		m_listItems[i]->DrawFront();
	}	
};

void zCMenu::PrintInformation(zSTRING s)
{
	if (!m_pViewInfo)				return;
	
//	zCPar_Symbol* sym;
	zCOLOR	color	= zCOLOR(255,255,255,255);
	m_pViewInfo->SetFontColor(color);
	m_pViewInfo->ClrPrintwin();
	m_pViewInfo->Printwin(s);

	m_pViewInfo->DrawItems();
};

/*--------------------------------------------------------------------------

    void zCMenu ::ScreenInit()

    22-Nov-00       [HILDEBRANDT]
					Compiler Warnings entfernt.
--------------------------------------------------------------------------*/ 

void zCMenu::ScreenInit()
{	
	if (m_screenInitDone) return;		
	m_screenInitDone = TRUE;

	zERR_MESSAGE(7,zERR_BEGIN,"C: MENU: Initializing menu-screen: "+GetName());		

	//
	// View mit Hintergrundbild erzeugen
	//
	
	UpdateWindowGeometry();

	if (!m_pWindow)
	{
		m_pWindow = zNEW( zCViewWindow(0,0,8192,8192) );
		screen->InsertItem(m_pWindow);			
	};
	if (!m_pInnerWindow)
	{
		m_pInnerWindow = zNEW( zCViewWindow(m_use_posx,m_use_posy,m_use_posx+m_use_dimx,m_use_posy+m_use_dimy) );
		m_pWindow->InsertItem(m_pInnerWindow);			
	}
	m_pInnerWindow->SetPos			( m_use_posx, m_use_posy );
	m_pInnerWindow->SetSize			( m_use_dimx, m_use_dimy );
	m_pInnerWindow->SetTransparency	( alpha );	

	if (!backPic.IsEmpty()) 
	{		
		zSTRING backTex = backPic;
		if (backTex.Search("|")>=0) backTex = backPic.PickWord( (inGameMenu) ? 2 : 1 ,"|","|");

		// zCView* backView = (inGameMenu) ? m_pInnerWindow : m_pWindow;
		zCView* backView = m_pInnerWindow;

		if (!backTex.IsEmpty())	backView->InsertBack(backTex); 
		else					backView->InsertBack(0);				
	}


	zERR_MESSAGE(7,0,"C: MENU: Opening menu-items");

		
	zCPar_Symbol* symX = menuParser->GetSymbol("MENU_INFO_X");
	zCPar_Symbol* symY = menuParser->GetSymbol("MENU_INFO_Y");
	int posX = 1000;
	int posY = 7500;
	if (symX && symY) { symX->GetValue(posX);symY->GetValue(posY); };

	if (flags & MN_SHOW_INFO)
	{		
		zSTRING fontName="font_default.tga";

		zCPar_Symbol* sym = menuParser->GetSymbol("MENU_FONT_INFO");
		if (sym) sym->GetValue(fontName);						
		
		m_pViewInfo = zNEW(zCView(0,0,100,100));
		m_pInnerWindow->InsertItem(m_pViewInfo);		
		m_pViewInfo->SetFont(fontName);
	
		m_pViewInfo->SetPos(posX,posY);
		m_pViewInfo->SetSize(8192-posX*2,8192-posY);
		m_pViewInfo->Setflags(VIEW_TXT_CENTER);

		// [BENDLIN] AddonMOD
		zBOOL menuShowVersion = zoptions->ReadBool(zOPT_SEC_INTERNAL, "menuShowVersion", TRUE);
		int menuVersionX = 6500;
		int menuVersionY = 7200;
		if (zgameoptions)
		{
			menuShowVersion = zgameoptions->ReadBool(zOPT_SEC_OPTIONS, "show_Version", menuShowVersion);
			menuVersionX = zgameoptions->ReadInt(zOPT_SEC_INFO, "show_VersionX", menuVersionX);
			menuVersionY = zgameoptions->ReadInt(zOPT_SEC_INFO, "show_VersionY", menuVersionY);
		}
		if (menuShowVersion)
			m_pInnerWindow->Print(menuVersionX, menuVersionY, APP_VERSION);
	}
		
	// [BENDLIN] AddonMOD
	if (zgameoptions)
	if (zgameoptions->ReadBool(zOPT_SEC_OPTIONS, "show_Info", FALSE))
	{
		int gameInfoX	= zgameoptions->ReadInt(zOPT_SEC_INFO, "show_InfoX", 800);
		int gameInfoY	= zgameoptions->ReadInt(zOPT_SEC_INFO, "show_InfoY", 7200);
		zSTRING gameTitle	= zgameoptions->ReadString(zOPT_SEC_INFO, "Title",			"Gothic II");
		zSTRING gameDesc	= zgameoptions->ReadString(zOPT_SEC_INFO, "Description",	"Original Game");
		zSTRING gameAuthors	= zgameoptions->ReadString(zOPT_SEC_INFO, "Authors",		"Piranha Bytes");
		zSTRING gameVersion	= zgameoptions->ReadString(zOPT_SEC_INFO, "Version",		APP_VERSION);
		zSTRING gameWebpage	= zgameoptions->ReadString(zOPT_SEC_INFO, "Webpage",		"http://www.gothic2.com");
		zSTRING gameIcon	= zgameoptions->ReadString(zOPT_SEC_INFO, "Icon",			"1");
		m_pInnerWindow->Print(gameInfoX, gameInfoY, gameTitle + " (" + gameVersion + ")");
	}

	//
	// Menuitems oeffnen und evtl. selektieren
	//	
	m_mainSel = (inGameMenu)?defaultInGame:defaultOutGame;	
	if (m_mainSel>=0 && !m_listItems[m_mainSel]->GetIsSelectable()) m_mainSel=-1;	

	for (int i=0; i<m_listItems.GetNumInList(); i++) 
	{
		m_listItems[i]->Open();
		m_listItems[i]->InsertInWin(m_pInnerWindow);		
		if (m_mainSel==-1 && m_listItems[i]->GetIsSelectable()) m_mainSel = i;		
	}		
	if (m_mainSel>=0 && m_mainSel<m_listItems.GetNumInList() && cursorEn) 
	{
		m_listItems[m_mainSel]->SetIsActive(TRUE);		
	}	
	
	SetEnableHandleEvent(TRUE);	
	SetHandleEventTop();		

	zERR_MESSAGE(7,zERR_END,"");	
};

/*--------------------------------------------------------------------------

    void zCMenu::ScreenDone()

    24-Nov-00       [HILDEBRANDT]
					Compiler Warnings entfernt.
--------------------------------------------------------------------------*/ 

void zCMenu::ScreenDone()
{		
	if (!m_screenInitDone) return;
	m_screenInitDone = FALSE;

	
	zERR_MESSAGE(7,0,"C: MENU: Deinitializing menu-screen: "+GetName());		

	for (int i=0; i<m_listItems.GetNumInList(); i++) m_listItems[i]->Close();

	SetEnableHandleEvent(FALSE);

	int numItems = m_listItems.GetNumInList();

	for (i=0; i<numItems; i++) m_listItems[i]->RemoveFromWin();		

	if (m_pViewInfo)
	{	
		m_pWindow -> RemoveItem(m_pViewInfo);
		delete m_pViewInfo;m_pViewInfo=0;
	}

	m_pWindow -> RemoveItem(m_pInnerWindow);		
	delete m_pInnerWindow;m_pInnerWindow=0;

	screen -> RemoveItem(m_pWindow);	
	delete m_pWindow;m_pWindow=0;

	zERR_MESSAGE(7,0,"C: MENU: Ready deinitializing menu");
}


void zCMenu::Render()
{	
	// test ob alle Items geschlossen, wenn ja - alle wieder öffnen
	
	zBOOL allClosed = TRUE;
	for (int i=0; i<m_listItems.GetNumInList(); i++) 
	{		
		allClosed = allClosed || !m_listItems[i]->DoesAutoClose() || m_listItems[i]->Closed(); 
		if (!allClosed) break;			
	}

	if (allClosed) 
		for (int i=0; i<m_listItems.GetNumInList(); i++) if (m_listItems[i]->DoesAutoClose()) m_listItems[i]->Open();

	if (!IsInGame()) Sleep(50);					// to avoid d3d queue lockups

	if (FrameCallback) 
	{
		FrameCallback();
	} 
	else 
	{		
		zrenderer	->	Vid_Clear(zCOLOR(0,0,0,0));
		zrenderer	->	BeginFrame();
		
		screen	->	Render();

		zrenderer	->	EndFrame();
		zrenderer	->	Vid_Blit();

		zsound	->	DoSoundUpdate();
	};	

	timer->ResetTimer();
}



zSTRING&	zCMenu::GetBackWorld()
{
	return backWorld;
};


zSTRING DEF_DAT_FILE = zSTRING("intro.dat");

zSTRING&	zCMenu::GetBackDatFile ()
{
	return DEF_DAT_FILE;
};

zCMenu*	zCMenu::GetActive()
{
	if (activeList.GetNum() == 0) return 0;
	return activeList[activeList.GetNum()-1];
};

zCMenuItem*	zCMenu::GetActiveItem()
{
	return m_listItems[m_mainSel];
};

int	zCMenu::GetNumberOfActiveItem()
{
	if (m_mainSel<0) 								return -1;
	if ( !m_listItems[m_mainSel]->GetIsSelectable() )	return -1;
	int nr  = 0;
	int opt = 0;
	while (opt <= m_mainSel) 
	{
		if (m_listItems[opt++]->GetIsSelectable() ) nr++;
	};
	return nr;
};

zBOOL zCMenu::SetActiveItem(zCMenuItem *item)
{
	zERR_ASSERT(item);

	if (!item->GetIsSelectable()) return FALSE;

	// alle anderen items deaktivieren (es gibt nur ein aktives Item pro Menu)
	for (int i=0; i<m_listItems.GetNumInList(); i++) m_listItems[i]->SetIsActive(FALSE);

	item->SetIsActive(TRUE);

	m_mainSel = m_listItems.Search(item);
	
	zERR_ASSERTT_STRICT(m_mainSel != -1, "C: zCMenu::SetActiveItem : Item not in list");

	return TRUE;
};


zSTRING& zCMenu::GetName()
{
	return name;
};


void zCMenu::SetName(const zSTRING &id)
{
	name = id;
	name.Upper();
}

zBOOL zCMenu::HandleEnterItem(zCMenuItem* item)
{
	return TRUE;
};

zBOOL zCMenu::HandleLeaveItem(zCMenuItem* item)
{
	return TRUE;
};

zBOOL zCMenu::HandleActivateItem(zCMenuItem* item)
{
	return TRUE;
};
