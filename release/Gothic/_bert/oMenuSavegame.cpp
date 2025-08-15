#include "zcore.h"
#include "omenusavegame.h"
#include "ztexture.h"

// [BENDLIN] 1.30
#include "zwin32.h"
extern int APP_VERSION_MAJOR;
extern int APP_VERSION_MINOR;
extern int APP_VERSION_POINT;
extern int APP_VERSION_INT;
extern char* APP_NAME;

static const zSTRING ITEM_THUMBPIC	= "MENUITEM_LOADSAVE_THUMBPIC";
static const zSTRING ITEM_DATETIME	= "MENUITEM_LOADSAVE_DATETIME_VALUE";
static const zSTRING ITEM_GAMETIME	= "MENUITEM_LOADSAVE_GAMETIME_VALUE";
static const zSTRING ITEM_WORLDNAME	= "MENUITEM_LOADSAVE_LEVELNAME_VALUE";
static const zSTRING ITEM_PLAYTIME	= "MENUITEM_LOADSAVE_PLAYTIME_VALUE";

oCMenuSavegame::oCMenuSavegame(const zSTRING& name, oTMenuSavegameMode _mode) : oCMenu_Main(name)
{
	savegameManager		= 0;
	mode				= _mode;
	m_selSlot			= -1;
	m_selSlotItemIndex	= -1;
	m_item_Thumbpic		= 0;
	m_item_Thumbpic2	= 0;
	m_item_DateTime		= 0;
	m_item_WorldName	= 0;
	m_item_GameTime		= 0;
	m_item_PlayTime		= 0;
	m_thumbPic			= 0;
};

oCMenuSavegame::~oCMenuSavegame	()
{
	m_item_Thumbpic		= 0;
	m_item_Thumbpic2	= 0;
	m_item_DateTime		= 0;
	m_item_WorldName	= 0;
	m_item_GameTime		= 0;
	m_item_PlayTime		= 0;
	zRELEASE(m_thumbPic);
};

void oCMenuSavegame::Activate()
{
	oCMenu_Main::Activate();
};

void oCMenuSavegame::HandleSlotChange(int oldSlot)
{
	oCSavegameInfo* info = savegameManager->GetSavegame(m_selSlot);
	zSTRING s;

	if (m_item_PlayTime)
	{
		int hours	= info->GetPlaytimeSeconds() / 3600;
		int minutes = (info->GetPlaytimeSeconds() / 60) - (hours*60);

		zSTRING s = zSTRING(hours)+"h "+zSTRING(minutes)+"min";
		m_item_PlayTime->SetText(s);
	};

	if (m_item_WorldName)		// Worldname
	{
		s.Clear();
		if (info && info->IsCompatible())
			s = info->GetWorldName();
		s.UpperFirstLowerRest();
		// [BENDLIN] 1.30
		if (info && info->IsCompatible() && !s.IsEmpty())
		{
			if ((info->GetVersionMajor() != APP_VERSION_MAJOR)	||
				(info->GetVersionMinor() != APP_VERSION_MINOR)	||
				(info->GetVersionPoint() != APP_VERSION_POINT)	||
				(info->GetVersionInt()	 != APP_VERSION_INT))
			{
				s += " ("+zSTRING(info->GetVersionMajor())+"."+zSTRING(info->GetVersionMinor());
				if (info->GetVersionPoint() >= 0)
				{
					s += "."+zSTRING(info->GetVersionPoint());
					if (info->GetVersionInt() >= 0)
						s += "."+zSTRING(info->GetVersionInt());
				}
				s += ")";
			}
		}
		m_item_WorldName->SetText(s, 0, TRUE);
	};			
	if (m_item_GameTime)		// Gametime
	{
		s.Clear();
		if (info && info->IsCompatible())
			s = info->GetGameTime();
		m_item_GameTime->SetText(s,0,TRUE);
	};
	if (m_item_DateTime)		// Savetime
	{
		s.Clear();
		if (info && info->IsCompatible())
			s = info->GetSaveTime();
		m_item_DateTime->SetText(s,0,TRUE);			
	}							
	if (m_item_Thumbpic)		// Screendump
	{
		zCTexture*	tex	= 0;// = m_thumbPic;
		if (info && info->IsCompatible())
			tex = info->GetThumbPic();
		
		if (!tex)
			info->ReloadResources();				// noch nicht geladen: dann jetzt aber laden
		
		if (info && info->IsCompatible())
			tex = info->GetThumbPic();

		if (tex)
		{			
			m_item_Thumbpic->InsertBack(tex);			// Screenshot anzeigen
		}
		else
		{
			m_item_Thumbpic->InsertBack(0);				// kein Screenshot
		};		
	};		
};

zBOOL oCMenuSavegame::HandleEvent(int key)
{
	zBOOL result = oCMenu_Main::HandleEvent(key);	
	
	//
	// Überprüfen ob HandleSlotChange aufgerufen werden muss
	//
	int oldSelSlot = m_selSlot;
	if (m_mainSel>=0 && m_mainSel<m_listItems.GetNumInList()) 
	{
		m_selSlotItemIndex	= m_mainSel;
		m_selSlot			= GetMenuItemSlotNr(m_listItems[m_mainSel]);
	}
	if (oldSelSlot!=m_selSlot) // Wechsel des Slots
	{
		HandleSlotChange(oldSelSlot);
	};

	return result;
};


void oCMenuSavegame::ScreenInit()
{	
	zERR_MESSAGE(5,zERR_BEGIN,"B: MSG: Initializing Savegame-Menu");
	zERR_ASSERT(savegameManager);	

	oCMenu_Main::ScreenInit();
		
	m_item_Thumbpic		= zCMenuItem::GetByName(ITEM_THUMBPIC);
	m_item_DateTime		= zCMenuItem::GetByName(ITEM_DATETIME);
	m_item_WorldName	= zCMenuItem::GetByName(ITEM_WORLDNAME);
	m_item_GameTime		= zCMenuItem::GetByName(ITEM_GAMETIME);
	m_item_PlayTime		= zCMenuItem::GetByName(ITEM_PLAYTIME);
	
	if (m_item_Thumbpic && m_thumbPic)
	{		
		int x1,y1,x2,y2;
		m_item_Thumbpic->GetCoords(x1,y1,x2,y2);
		m_item_Thumbpic2 = zNEW(zCView(x1,8000-y2+y1,x2,8000));
		m_item_Thumbpic2->InsertBack(m_thumbPic);
		screen->InsertItem(m_item_Thumbpic2);
		
	};	

	//
	// Bearbeite alle vorhandenen slot-items
	// Weise ihnen Informationen aus dem SavegameManager zu	

	for (int i=0; i<m_listItems.GetNumInList(); i++) 
	{
		zERR_MESSAGE(6,0,"B: MSG: Get "+m_listItems[i]->GetName());
		int slotNr = GetMenuItemSlotNr(m_listItems[i]);
		if ((slotNr >= SAVEGAME_SLOT_QUICK) && (slotNr <= SAVEGAME_SLOT_MAX))
		{						
			oCSavegameInfo* info = savegameManager->GetSavegame(slotNr);			
			if (info)
			{
				zERR_MESSAGE(5,0,"B: MSG: Savegame "+zSTRING(slotNr)+" found: "+info->GetName());
				zSTRING infoStr = info->IsCompatible() ? info->GetName() : "xxx";
				if (infoStr.IsEmpty()) infoStr="???";
				// infoStr += " ("+info->GetSaveTime()+")";
				if (slotNr != SAVEGAME_SLOT_QUICK)
					m_listItems[i]->SetText(infoStr,0,FALSE);				
			}
			else if (slotNr != SAVEGAME_SLOT_QUICK)
				m_listItems[i]->SetText("---", 0,FALSE);
			m_listItems[i]->SetIsDisabled( FALSE );
			m_listItems[i]->SetIsSelectable( (mode==SAVE) || (info!=0) );
		}
	}		

	m_selSlot = GetMenuItemSlotNr(m_listItems[m_mainSel]);
	//zERR_MESSAGE(1,0,"B: SelSlot "+zSTRING(m_selSlot));
	//zERR_MESSAGE(1,0,"B: SelItem "+zSTRING(m_mainSel));
	HandleSlotChange(-1);

	zERR_MESSAGE(5,zERR_END,"");
};


void oCMenuSavegame::ScreenDone()
{	
	// 
	// SavegameInfos aktualisieren
	//	
	
	zERR_MESSAGE(5,zERR_BEGIN,"B: MSG: Closing Savegame-Menu");
	for (int i=0; i<m_listItems.GetNumInList(); i++) 
	{
		zERR_MESSAGE(6,0,"B: MSG: Set "+m_listItems[i]->GetName());
		int slotNr = GetMenuItemSlotNr(m_listItems[i]);
		if (slotNr>=0)
		{						
			oCSavegameInfo* info = savegameManager->GetSavegame(slotNr);
			if (info)
			{				
				info->SetName(m_listItems[i]->GetText());
				zERR_MESSAGE(5,0,"B: MSG: Savegame "+zSTRING(slotNr)+": "+info->GetName());
			};
		}
	}		

	oCMenu_Main::ScreenDone();

	if (savegameManager) savegameManager->CleanResources();
	
	delete m_item_Thumbpic2;m_item_Thumbpic2=0;
	zRELEASE(m_item_Thumbpic);

	zinput->ClearKeyBuffer();

	zERR_MESSAGE(5,zERR_END,"");
};


int oCMenuSavegame::GetMenuItemSlotNr(zCMenuItem* item)
{
	if (!item)
		return -1;
	zSTRING name = item->GetName();
	if (name.Search("_SLOT") <= 0)
		return -1;
	name.Delete("_SLOT",zSTR_TO);
	int slotNr = name.ToInt();
	if ((slotNr<SAVEGAME_SLOT_QUICK) || (slotNr>SAVEGAME_SLOT_MAX)) slotNr=-1;
	return slotNr;
};

int oCMenuSavegame::GetSelectedSlot()
{
	return m_selSlot;
};

void oCMenuSavegame::SetScreenshot(zCTextureConvert* texCvt)
{
	zRELEASE(m_thumbPic);

	if (texCvt)
	{				
		// Screenshot konvertieren	
		zCTextureInfo texInfo = texCvt->GetTextureInfo();
		texInfo.texFormat	= zCTexture::CalcNextBestTexFormat(zRND_TEX_FORMAT_RGB_565);
		texInfo.numMipMap	= 1;			
		texInfo.sizeX		= 256;
		texInfo.sizeY		= 256;		
		texCvt->ConvertTextureFormat(texInfo);		

		m_thumbPic = zrenderer->CreateTexture();
		zCTextureExchange::CopyContents(texCvt,m_thumbPic);		
	}	

	if (m_thumbPic) m_thumbPic->AddRef();
};
