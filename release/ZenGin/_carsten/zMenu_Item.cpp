#include "zcore.h"
#include "zmenu.h"
#include "zmenu_item.h"
#include "zparser.h"
#include "zfonts.h"
#include "zoption.h"
#include "zoption_const.h"
#include "zMathTools.h"
#include "zWorld.h"
#include "zInput.h"
#include "zWin32.h"

unsigned char GetCharFromDIK(int dik1, int dik2, int dik3);

//
// Statische Elemente
//

zCArraySort<zCMenuItem*>	zCMenuItem::itemList;
zCMenuItem*					zCMenuItem::tmp;

int zCMenuItem::CompareNames( const void *e1 ,const void *e2) 
{
	return strcmp( (*(zCMenuItem**)e2)->GetName().ToChar(),(*(zCMenuItem**)e1)->GetName().ToChar());
}


void zCMenuItem::Startup()
{ 
	itemList.SetCompare(CompareNames);
	tmp = zNEW(zCMenuItem());
};

void zCMenuItem::Shutdown()
{ 		
	// auskommentiert: [Wohlers] hack, da sonst absturz    
	while (itemList.GetNumInList()>0)
	{ 
        itemList[0]->registeredCPP = FALSE; // [Moos] 6.12.00 Leakfix		
		itemList[0]->Unregister();
	}	

	if (tmp) tmp->Release();
	tmp=NULL;
};


zCMenuItem* zCMenuItem::GetByName(const zSTRING &n)
{
	zSTRING ID = n;
	ID.Upper();
	tmp->SetName(ID);
	int index = itemList.Search(tmp);		

	if (index != -1) 
	{
		zCMenuItem* item = itemList[index];
		if (item) item->AddRef();
		return item;
	}
	else return 0;
};

zCMenuItem* zCMenuItem::GetSelItem()
{
	int num = 0;
	zTMenuItemSelAction selAction;

	while ( (selAction = GetSelActionType(num)) != SEL_ACTION_UNDEF ) 
	{
		if (selAction == SEL_ACTION_STARTITEM) return zCMenuItem::GetByName(GetSelActionString(num));
		num++;
	};				
	return 0;
};


zCMenuItem* zCMenuItem::Create(const zSTRING &itemID)
{
	zSTRING ID = itemID;if (ID.IsEmpty()) return 0;
	
	ID.Upper();
	zCMenuItem *item = zCMenuItem::GetByName(ID);
	if (!item) 
	{
		if (zCMenu::GetParser()->GetSymbol(ID)) 
		{
			zCMenu::GetParser()->CreateInstance(ID, &tmp->m_parFontName);
			switch(tmp->GetType()) 
			{
				case MENU_ITEM_TEXT:			item = zNEW(zCMenuItemText(ID));break;					
				case MENU_ITEM_INPUT:			item = zNEW(zCMenuItemInput(ID));break;
				case MENU_ITEM_SLIDER:			item = zNEW(zCMenuItemSlider(ID));break;
				case MENU_ITEM_CHOICEBOX:		item = zNEW(zCMenuItemChoice(ID));break;
				case MENU_ITEM_LISTBOX:			item = zNEW(zCMenuItemList(ID));break;
				case MENU_ITEM_BUTTON:			item = zNEW(zCMenuItemButton(ID));break;					
				default:						zERR_FATAL("C: zmenu_item.cpp(zCMenuItem::Create): Illegal item type: " + zSTRING(tmp->GetType()));				
			}
		}
		else zERR_FATAL("C: zmenu_item.cpp(zCMenuItem::Create): MenuItem not known: " + zSTRING(ID));

		item -> InitView();
		item -> InitMenuItem();
	};	

	return item;
};

//
// Menueitem (Basisklasse fuer alle Menue-Items)
//

zCMenuItem::zCMenuItem(const zSTRING& itemID) : zCView()
{
	Init();
	id = itemID;
	id.Upper();
	SetByScript(id);
	RegisterCPP();
}

zCMenuItem::zCMenuItem()
{
	Init();
};

zCMenuItem::~zCMenuItem()
{	
	m_pFont			= 0;
	m_pFontHi		= 0;
	m_pFontSel		= 0;
	m_pFontDis		= 0;

	delete m_pInnerWindow;m_pInnerWindow=0;

	// Unregister();
}

void zCMenuItem::Init()
{
	for (int i=0; i<MENU_EVENT_MAX	; i++) m_parOnEventAction[i] = 0; 
	for (	 i=0; i<MAX_SEL_ACTIONS ; i++) 
	{
		m_parOnSelAction[i]	= SEL_ACTION_UNDEF;
		m_parOnSelAction_S[i].Clear();
	}
	inserted		= FALSE;
	changed			= TRUE;
	active			= FALSE;
	activeTimer		= 0;
	orgWin			= 0;
	open			= FALSE;
	close			= FALSE;
	opened			= FALSE;
	closed			= FALSE;	
	fxTimer			= 0;
	openDelayTimer	= 0;
	
	m_parAlpha			= 254;
	m_parType			= 0;
	m_parOpenDuration	= -1;
	m_parSizeStartScale  = 1;
	m_parItemFlags		= 0;
	m_parOpenDelayTime	= 0;
		
	m_parPosX			= 0;
	m_parPosY			= 0;
	//m_parTxtPosX		= 0;
	//m_parTxtPosY		= 0;
	m_parDimX			= -1;
	m_parDimY			= -1;
	m_parFrameSizeX		= 0;
	m_parFrameSizeY		= 0;

	disabled		= FALSE;	
	registeredCPP	= FALSE;	
	
	m_bVisible			= TRUE;
	m_bDontRender		= FALSE;
	m_bViewInitialized	= FALSE;
	m_iRefCtr		= 1;
	m_pInnerWindow	= 0;
	m_pFont			= 0;
	m_pFontHi		= 0;
	m_pFontSel		= 0;
	m_pFontDis		= 0;
	
	firstTimeInserted = TRUE;
	
	m_parFontName		.Clear();
	m_parBackPic		.Clear();
	m_parAlphaMode		.Clear();
	m_parOnChgSetOption	.Clear();
	id					.Clear();

	for (	i=0; i<MAX_USERSTRINGS; i++) m_parText[i].Clear();

	for (   i=0; i<MAX_USERVARS; i++) 
	{
		m_parUserFloat[i]= 0;
		m_parUserString[i].Clear();
	}
	m_parHideIfOptionSet.Clear();
	m_parHideIfOptionSectionSet.Clear();
	m_parHideOnValue=0;

};

void zCMenuItem::SetByScript(zSTRING &identifier) 
{
	zSTRING ID = identifier;
	ID.Upper();
	id = ID;	

	if (zCMenu::GetParser()->GetSymbol(ID)) zCMenu::GetParser()->CreateInstance(ID, &m_parFontName);
	
	m_parBackPic.Upper();
	
	SetAlphaBlendFunc( zrenderer->AlphaBlendFuncStringToType(m_parAlphaMode)) ;
	
	// Fonts holen
	zSTRING fontName = m_parFontName;
	int		fontIndex= 0;	
	fontIndex = zfontman->Load(fontName);
	m_pFont = zfontman->GetFont(fontIndex);	

	if (fontName.Search("_hi")<0) fontName.Insert(fontName.Search("."),"_hi");	
	fontIndex = zfontman->Load(fontName);
	m_pFontHi = zfontman->GetFont(fontIndex);	

	m_pFontDis = m_pFont;
	m_pFontSel = m_pFontHi;	

	Register();

	int lastUsedUserString = -1;
	for (int i=0; i<MAX_USERSTRINGS; i++) if ( !m_parText[i].IsEmpty() ) lastUsedUserString = i;	
	for (i=0; i<=lastUsedUserString; i++) m_listLines.InsertEnd(m_parText[i]);
};

void zCMenuItem::InsertInWin(zCView *orgWindow)
{		
	if (GetOwner()) RemoveFromWin();

	if (!GetIsVisible()) return;

	//
	// Basis-View (Hintergrundbild)
	//

	orgWin = orgWindow;	
	orgWin->InsertItem(this);			
	this->SetPos			(m_parPosX,m_parPosY);	
	this->SetTransparency	(m_parAlpha);	
	this->SetFont			(m_parFontName);
	this->SetSize			(GetDimX(m_parDimX),GetDimY(m_parDimY));	// nach dem Setzen des Fonts!!

	if (m_parBackPic.Search(".TGA")>=0) 
	{		
		zSTRING backTex = m_parBackPic;
		if (backTex.Search("|")>=0) backTex = m_parBackPic.PickWord( (zCMenu::inGameMenu) ? 2 : 1 ,"|","|");
		if (!backTex.IsEmpty()) InsertBack(backTex); else InsertBack(0);
	}

	zCOLOR fontCol = this->GetFontColor();
	fontCol.SetAlphaByte(m_parAlpha);	

	//
	// InnerWindow (Text)
	//

	zERR_ASSERT(!m_pInnerWindow);
	m_pInnerWindow = zNEW(zCView(m_parFrameSizeX,m_parFrameSizeY,8192-m_parFrameSizeX,8192-m_parFrameSizeY));		

	InsertItem						(m_pInnerWindow);
	m_pInnerWindow->SetPos			(m_parFrameSizeX,m_parFrameSizeY);	
	m_pInnerWindow->SetSize			(8192-m_parFrameSizeX*2,8192-m_parFrameSizeY*2);
	m_pInnerWindow->SetFont			(m_parFontName);	
	m_pInnerWindow->SetFontColor	(fontCol);		
	m_pInnerWindow->SetAlphaBlendFunc(zrenderer->AlphaBlendFuncStringToType(m_parAlphaMode));			

	if (m_parItemFlags & IT_TXT_CENTER)	m_pInnerWindow->Setflags(VIEW_TXT_CENTER);
	else								m_pInnerWindow->ClrFlags(VIEW_TXT_CENTER);				

	inserted	= TRUE;

	//
	// Inhalt updaten
	//


	UpdateFX();
	UpdateSize();
	
	ClrPrintwin	();
	DrawFront	();
};

void zCMenuItem::RemoveFromWin()
{
	delete m_pInnerWindow;m_pInnerWindow=0;
	if (orgWin) orgWin->RemoveItem(this);	
	opened			= FALSE;
	open			= FALSE;
	close			= FALSE;
	closed			= FALSE;
	active			= FALSE;
	activeTimer		= 0;
	fxTimer			= 0;
	openDelayTimer	= 0;
};

// GetDimX/Y
//
// Berechnung der Groesse, entsprechend dem enthaltenen Text
int	zCMenuItem::GetDimX(int _m_parDimX)
{
	if (_m_parDimX>=0) return _m_parDimX;

	zCFont* font		= m_pInnerWindow ? m_pInnerWindow->GetFont() : GetFont();
	zCView* ownerWin	= GetOwner();
	if (!font || !ownerWin)	return 0;

	int frameX = nax(m_parFrameSizeX);
	return ownerWin->anx(font->GetFontX(GetText())+frameX);
};

int	zCMenuItem::GetDimY(int _m_parDimY)
{
	if (_m_parDimY>=0) return _m_parDimY;

	zCFont* font		= m_pInnerWindow ? m_pInnerWindow->GetFont() : GetFont();
	zCView* ownerWin	= GetOwner();
	if (!font || !ownerWin)	return 0;

	int frameY = nay(m_parFrameSizeY);
	return ownerWin->any(font->GetFontY()+frameY);
};

// InitMenuItem
//
// Virtuelle Methode, wird nach dem Erzeugen eines Menueitems aufgerufen
void zCMenuItem::InitMenuItem()
{			
	SetText(GetText());
};

void zCMenuItem::InitView()
{
	if (m_bViewInitialized) return;
		
	if (m_parDimX == -1 || m_parDimY == -1) zCView::Init(0,0,GetText(), VIEW_ITEM);
	else									zCView::Init(0,0,m_parDimX, m_parDimY, VIEW_ITEM);		
		
	SetPos(m_parPosX,m_parPosY);

	m_bViewInitialized = TRUE;
}



// Show / Hide
//
// Das Menueitem in die View-Hierarchie einfuegen/austragen
zBOOL zCMenuItem::Show()
{
	if (orgWin) 
	{
		orgWin->InsertItem	(this);
		this->InsertItem	(m_pInnerWindow);
	}
	return (orgWin!=0);
};

zBOOL zCMenuItem::Hide()
{
	if (orgWin) 
	{
		if (m_pInnerWindow) RemoveItem(m_pInnerWindow);
		orgWin->RemoveItem(this);		
		return TRUE;
	}
	return FALSE;
};

void zCMenuItem::Open()
{
	open			= TRUE;
	opened			= FALSE;
	close			= FALSE;
	closed			= FALSE;
	openDelayTimer	= 0;
};

void zCMenuItem::Close()
{
	close	= TRUE;
	closed  = FALSE;
};



//
// Virtuelle Methoden
//
zBOOL zCMenuItem::ToggleValue(int step, zBOOL loop) 
{ 	
	// Beeinflusst die Option die Performance-Settings, dann auf Custom umschalten
	if ((m_parItemFlags & IT_PERF_OPTION) && !(m_parItemFlags & IT_NEEDS_APPLY))		
	{
		zoptions->WriteInt(zOPT_SEC_INTERNAL,"perfQualityIndex",0); // Custom/Undef-Wert
	}
	
	return FALSE; 
};


//
// Einfache Methoden
//

zTMenuItem zCMenuItem::GetType()
{
	return (zTMenuItem)m_parType;
};


zSTRING zCMenuItem::GetText (const int num)
{
	if (num>=m_listLines.GetNumInList()) return zSTRING("");
	return m_listLines[num];
};


void zCMenuItem::SetName(const zSTRING &name)
{
	id = name;
};

zSTRING&  zCMenuItem::GetName()
{
	return id;
};

void zCMenuItem::GetCoords(int &x0, int &y0, int &x1, int &y1)
{
	GetScreenExtends(x0,y0,x1,y1);
};

zTMenuItemSelAction zCMenuItem::GetSelActionType	(const int num)
{
	return (zTMenuItemSelAction)m_parOnSelAction[num];
};

zSTRING& zCMenuItem::GetSelActionString	(const int num)
{
	return m_parOnSelAction_S[num];
};

void zCMenuItem::SetName(zSTRING &n)
{
	id = n;
	id.Upper();
}


void zCMenuItem::Register()
{
	if (!itemList.IsInList(this)) 
	{
		itemList.InsertSort(this);
		AddRef();
	}
};

void zCMenuItem::Unregister()
{	
	if (itemList.IsInList(this)) 
	{
		itemList.RemoveOrder(this);
		Release();
	}
};

zBOOL zCMenuItem::IsRegistered()
{
	return (itemList.Search(this) != -1);	
};


//
// Inhalt des Menueitems (Text)
//

const zSTRING TXT_FORMAT_LINE = "<hr>";

static void FormatText(zSTRING& s)
{
	int index;
	do { 
		index = s.Search("\\n");
		if (index>=0) { s.Delete("\\n");s.Insert(index,"\n"); }
	} while(index>=0);	
	do { 
		index = s.Search(TXT_FORMAT_LINE);
		if (index>=0) { s.Delete(TXT_FORMAT_LINE);s.Insert(index,"\n---\n"); }
	} while(index>=0);
};

void zCMenuItem::SetText (const zSTRING &txt, const int line, zBOOL draw_now)
{
	if (line<0) return;

	zERR_MESSAGE(7,0,"B: MenuItem "+GetName()+" text: "+zSTRING(txt)+" (line "+zSTRING(line)+")");
	
	int numLines = m_listLines.GetNumInList();
	if (line>=numLines)	
	{
		for (int i=numLines; i<=line; i++) m_listLines.InsertEnd("");
	}
	m_listLines[line] = txt;  
	FormatText(m_listLines[line]);		

	UpdateSize();
			
	DrawFront();
	if (draw_now) DrawItems();
};

void zCMenuItem::UpdateSize	()
{
	SetSize(GetDimX(m_parDimX),GetDimY(m_parDimY));
	if (m_pInnerWindow)
	{
		m_pInnerWindow->SetPos			(m_parFrameSizeX,m_parFrameSizeY);	
		m_pInnerWindow->SetSize			(8192-m_parFrameSizeX*2,8192-m_parFrameSizeY*2);
	}
};


void zCMenuItem::SetText (const zCArray <zSTRING> textLines, zBOOL draw_now)
{
	zERR_MESSAGE(7,0,"B: MenuItem "+GetName()+" text: textarray");

	m_listLines.DeleteList();
	for (int i=0; i<m_listLines.GetNumInList();  i++) 
	{
		m_listLines.InsertEnd(textLines[i]);
		FormatText(m_listLines[i]);		
	}

	DrawFront();
	if (draw_now) DrawItems();
};

//
// Aktivieren des Menueitems (eigene Aktivitaeten)
//

void zCMenuItem::Enter()
{		
};

void zCMenuItem::Leave()
{	
};

zBOOL zCMenuItem::HandleEvent(int key)
{
	switch (key)
	{
		case KEY_ESC:
		case MOUSE_BUTTONRIGHT:
			m_bLeaveItem = TRUE;
			break;	
	};

	if ( m_parOnEventAction[MENU_EVENT_INIT] ) 
	{
		zBOOL *exit = (zBOOL *)zCMenu::GetParser()->CallFunc(m_parOnEventAction[MENU_EVENT_INIT]);
		return (*exit);
	}

	return TRUE;
};

zBOOL zCMenuItem::Run()
{
	SetIsActive(TRUE)		;			
	SetEnableHandleEvent(TRUE);

	Enter();	
	
		m_bLeaveItem = FALSE;
		do 
		{			
			zCMenu::GetActive()->zCMenu::HandleFrame();
			
		} while(!m_bLeaveItem);
	
	Leave();

	SetEnableHandleEvent(FALSE);	
	SetIsActive(FALSE);	

	return FALSE;
};


zBOOL zCMenuItem::Input(int len, zSTRING &ls)
{
	zSTRING s		= ls;
	int		l		= ls.Length();	
	zBOOL	leave	= FALSE;
	int		key		= -1;
	
	SetText(s+"_");
		
	do 
	{
		/*
		sysEvent();
		zinput->ProcessInputEvents();

		zCMenu::GetActive()->Render();
		*/
		zCMenu::GetActive()->HandleFrame();
	
		key = zinput->GetKey();		
		switch (key)
		{
		case KEY_ESC:			
		case MOUSE_BUTTONRIGHT:
			leave = TRUE;			// Weiter bei KEY_ENTER ... (kein break)
		case KEY_ENTER:
		case MOUSE_BUTTONLEFT:
			leave = TRUE;
			ls = s;
			break;
		case KEY_BACKSPACE:
			if(l>0 ) 
			{ 
				s.Delete(s.Length()-1,1); 				
				SetText(s+"_");
				l--;
			} 
			break;
		case KEY_DEL:
			s.Clear();
			l=0;
			SetText(s+"_");
			break;
		default:
			key = GetCharFromDIK(key,
				((zinput->KeyPressed(KEY_RSHIFT) || zinput->KeyPressed(KEY_LSHIFT))	? DIK_LSHIFT : 0),
				(zinput->KeyPressed(KEY_RALT)										? DIK_RMENU  : 0));
			if ((l < len) && (key >= 32) && (key <= 255)) 
			{								
				s += (char*)(&key);											
				SetText(s + "_");
				l++;
			}
		};		

	} while(!leave);
	
	SetText(s);
	
	return (key==KEY_ENTER || key==MOUSE_BUTTONLEFT);
}


//
// Schreibe-Methoden
//

void zCMenuItem::Draw()
{
	if (GetReallyDoNotRender()) return;
	DrawFront	  ();
	DrawItems	  ();	
};

void zCMenuItem::DrawFront()
{	
	if (!GetOwner())	return;
	if (!m_pInnerWindow) return;			
	if (GetReallyDoNotRender()) return;


	zSTRING res = GetText();

	UpdateFX();	

	m_pInnerWindow->ClrPrintwin();
	if		(m_parItemFlags & IT_MULTILINE)		m_pInnerWindow->Printwin	(res+"\n");
	else if (m_parItemFlags & IT_TXT_CENTER)	m_pInnerWindow->PrintCXY	(res);
	else										m_pInnerWindow->Print		(0,0,	res);
};

void zCMenuItem::DrawItems()
{
	if (GetReallyDoNotRender()) return;

	zCView::DrawItems();

	if (m_pInnerWindow) UpdateContent();
}

void zCMenuItem::UpdateContent()
{		
	/*
	if (active || (GetMenuItemFlags() & IT_HILIGHT))
	{
		zTRnd_AlphaBlendFunc oldAlphaFunc = m_pInnerWindow->GetAlphaBlendFunc();	
		m_pInnerWindow->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);		
		m_pInnerWindow->Blit();
		m_pInnerWindow->SetAlphaBlendFunc	(oldAlphaFunc);
	}
	*/
};

void zCMenuItem::UpdateFX()
{				
	if (!GetIsVisible()) return;

	zCOLOR newColor;
		
//	int		flags		= GetMenuItemFlags();
	
	// Zustaende
	zBOOL	isActive	= active;	
	zBOOL	isDisabled	= GetIsDisabled();		
	
	zCFont* useFont = m_pFont;

	// Zustand: Aktiviert

	if (isActive) 
	{				
		newColor.SetRGBA( 255,255,255,255);	// wird nochmal additiv geblittet
		useFont = m_pFontSel;
	}
	// Zustand: Disabled
	else if (isDisabled) 
	{			
		newColor.SetRGBA( 175,175,175,220);
		useFont = m_pFontDis;
	}		
	// Standard-Text
	else
	{
		newColor.SetRGBA( 255,255,255,255);
		useFont = m_pFont;
	}
		
	m_pInnerWindow->SetFont				(useFont);
	m_pInnerWindow->SetFontColor		(newColor);	
	m_pInnerWindow->SetTransparency		(m_parAlpha);	
		
	UpdateSize();
};









int	zCMenuItem::GetEventFunc(const zTMenuItemEvent evNr)
{
	return m_parOnEventAction[evNr];
}

void zCMenuItem::SetIsActive(zBOOL b)
{
	active = b;
	zCMenu* menu = zCMenu::GetActive();
	if (menu)
	{
		if (active)	menu->PrintInformation(m_parText[1]);	
		else		menu->PrintInformation("");	
	}
	DrawFront();
};

void zCMenuItem::SetIsSelectable (zBOOL b)
{
	if (b) m_parItemFlags |= IT_SELECTABLE; 
	else 
	{
		m_parItemFlags &= ~IT_SELECTABLE;
		if (active) zCMenu::GetActive()->NextOption();
	}
	DrawFront();
};

zBOOL zCMenuItem::GetIsSelectable	()
{
	if (GetIsDisabled())												return FALSE;
	if (GetReallyDoNotRender())												return FALSE;
	if ((m_parItemFlags & IT_ONLY_IN_GAME)	&& !zCMenu::IsInGame())		return FALSE;
	if ((m_parItemFlags & IT_ONLY_OUT_GAME) && zCMenu::IsInGame())		return FALSE;		

	return (m_parItemFlags & IT_SELECTABLE);
};

void zCMenuItem::SetIsDisabled(zBOOL b)
{
	m_parItemFlags &= IT_DISABLED;
	DrawFront();
};

zBOOL zCMenuItem::GetIsDisabled()
{
	if  (!GetIsVisible())												return TRUE;
	if	((m_parItemFlags & IT_ONLY_IN_GAME)	&& !zCMenu::IsInGame())		return TRUE;
	if	((m_parItemFlags & IT_ONLY_OUT_GAME) && zCMenu::IsInGame())		return TRUE;		

	return (m_parItemFlags & IT_DISABLED);
};

void zCMenuItem::SetIsVisible(zBOOL b)
{
	m_bVisible = b;		
};

zBOOL zCMenuItem::GetIsVisible()
{
	return m_bVisible;	
};




//
// zCMenuItemInput
//

static const zSTRING EMPTY_STRING_PLACEHOLDER = "---";

zCMenuItemInput::zCMenuItemInput(const zSTRING& itemID) : zCMenuItem(itemID)
{
	value.Clear();
	curPos		= 0;
	canceled	= FALSE;
};

zCMenuItemInput::~zCMenuItemInput()
{
	SetEnableHandleEvent(0);
};

void zCMenuItemInput::SetValue(zSTRING _value)
{ 
	SetText(value);
};

zSTRING zCMenuItemInput::GetValue()
{
	return GetText();
};

void zCMenuItemInput::InitMenuItem()
{	
	zCMenuItem::InitMenuItem();

	// Optionswert auslesen, setzen und wieder zurueckschreiben
	if ( !m_parOnChgSetOption.IsEmpty() && zoptions->EntryExists(m_parOnChgSetOptionSection,m_parOnChgSetOption.ToChar()) ) 
	{
		zSTRING s;
		s = zoptions->ReadString(m_parOnChgSetOptionSection,m_parOnChgSetOption);
		SetText(s,0,FALSE);
		zoptions->WriteString(m_parOnChgSetOptionSection,m_parOnChgSetOption,s,(m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);
	};
};

void zCMenuItemInput::InsertInWin(zCView *orgWindow)
{	
	zCMenuItem::InsertInWin(orgWindow);

	if (!GetIsVisible()) return;

	Draw();
};


zBOOL zCMenuItemInput::Run()	
{
	canceled = FALSE;

	SetIsActive(TRUE)		;			
	SetEnableHandleEvent(TRUE);

	Enter();	

		//Eingabe
		zSTRING inpText = GetText();		
		zSTRING oldText = inpText;
		
		zBOOL emptyStringPlaceholderFound = (inpText == EMPTY_STRING_PLACEHOLDER);		
		if (emptyStringPlaceholderFound) inpText.Clear();

		canceled = !Input(80,inpText);
		zERR_MESSAGE(5,0,"B: InputItem canceled = "+zSTRING(canceled));
		
		if (emptyStringPlaceholderFound && inpText.IsEmpty()) inpText=EMPTY_STRING_PLACEHOLDER;

		// Hat sich der Wert ge�ndert -> Optionswert schreiben
		if (inpText != oldText) 
		{
			if ( !m_parOnChgSetOption.IsEmpty() ) 
				zoptions->WriteString(m_parOnChgSetOptionSection,m_parOnChgSetOption,inpText, (m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);			
		}
		SetText(inpText);
	
	Leave();

	SetEnableHandleEvent(FALSE);	
	SetIsActive(FALSE);	
	
	return FALSE;
};

//
// Text
//

zCMenuItemText::zCMenuItemText(const zSTRING& itemID) : zCMenuItem(itemID)
{	
	m_mode			= MODE_SIMPLE;
	m_numOptions	= 0;
	m_topLine		= 1;
	m_viewLines		= -1;
	m_numLines		= -1;
	m_unformated	= TRUE;
	ClrFlags(VIEW_TXT_CENTER);	
};

zCMenuItemText::~zCMenuItemText() 
{	
};


void zCMenuItemText::DrawFront()
{
	if (!GetOwner())	return;
	if (!m_pInnerWindow)	return;

	UpdateFX();	

	switch (m_mode)
	{
		case MODE_SIMPLE:
		case MODE_ENUM:
				zCMenuItem::DrawFront();
				break;

		case MODE_MULTILINE:
				DrawMultiline();
				break;
	};
};

void zCMenuItemText::FormatMultiline()
{			
	zSTRING s = m_fullText;
	zSTRING line;

	m_listLines.DeleteList();

	zSTRING symbols(" \n\t");	
	int		restX = 8100;			// Restanzahl logischer Koordinaten	einer Zeile
	int		wortSize=0;				// Breite in log.Koordinaten des jeweiligen Wortes	
	zSTRING wort;					// String fuer aktuelle Zeile und Wort	
	
	while (!s.IsEmpty())
	{		
		wort		= s.PickWord(1,symbols,"");		
		wortSize	= m_pInnerWindow->FontSize(wort);		
		s.Delete(0,wort.Length());
		
		if (wort=="\t") wort=" ";
		if (wort=="\n") wort.Clear();
		
		if (wort.IsEmpty() || wortSize>=restX)	
		{									
			restX		=  8100;
			line.TrimLeft();
			m_listLines.InsertEnd(line);
			line.Clear();
		} 
		
		line	+= wort;
		restX	-= wortSize;		
	}	
	line.TrimLeft();
	m_listLines.InsertEnd(line);

	m_viewLines		= 8100 / m_pInnerWindow->FontY();
	m_numLines		= m_listLines.GetNumInList();
	m_topLine		= zMax(1,m_numLines-m_viewLines+1);	
	m_unformated	= FALSE;
};

void zCMenuItemText::DrawMultiline()
{
	ClrPrintwin();
	m_pInnerWindow->ClrPrintwin();	

	if (m_unformated) FormatMultiline();

	m_viewLines = 8100 / m_pInnerWindow->FontY();	
	
	int index		= m_topLine-1;
	int y			= 0;
	int	y_step		= m_pInnerWindow->FontY();
	
	while (index<m_listLines.GetNumInList() && (y+y_step<8100))
	{				
		if (m_parItemFlags & IT_TXT_CENTER)	m_pInnerWindow->PrintCX	(  y,m_listLines[index]);
		else								m_pInnerWindow->Print	(0,y,m_listLines[index]);			
		y += y_step;															
		index++;
	}	
	// Positionsanzeige
	if (m_numLines>1 && (m_numLines>m_viewLines))
	{
		int		pageCount	= (int)zCeil(float(m_numLines)	/ float(m_viewLines));
		int		page		= (int)zCeil(float(m_topLine)	/ float(m_viewLines));
		int		percent		= (100 * (m_topLine-1)) / (m_numLines-1);
		float	y = float(8192 - m_parFrameSizeY);
		PrintCX((int)y,zSTRING(page) + "/" + zSTRING(pageCount)+"  ("+zSTRING(percent) + "%)");
	}; 
};

void zCMenuItemText::InitMenuItem()
{
	zCMenuItem::InitMenuItem();

	m_fullText = GetText();	

	// Optionswert auslesen
	if ( !m_parOnChgSetOption.IsEmpty() && zoptions->EntryExists(m_parOnChgSetOptionSection,m_parOnChgSetOption.ToChar()) )
	{
		m_fullText = zoptions->ReadString(m_parOnChgSetOptionSection,m_parOnChgSetOption);		
	};

	m_mode = MODE_SIMPLE;
	if (m_parItemFlags & IT_MULTILINE) 
	{
		m_mode		= MODE_MULTILINE;				
	}
	else if (m_fullText.Search("|")>=0) 
	{
		m_mode = MODE_ENUM;		
		SetEnum(m_fullText);
	}
};

void zCMenuItemText::SetEnum(const zSTRING& enumeration)
{
	m_fullText = enumeration;		
	int count=0;
	while (m_fullText.Search("|",++count)>=0);
	m_numOptions = count;		
	if (count>1) m_mode = MODE_ENUM;
	SetText(GetText()); 					
};

/*

  Alte Version: Pre 1.08
zBOOL zCMenuItemText::HandleEvent(int key)
{
	if (m_viewLines<0) return FALSE;
	
	int oldTopLine	= m_topLine;
	int topMax		= (m_viewLines<m_numLines)?zMax(1,m_numLines):1;
	// if (key==KEY_ENTER) key = KEY_ESC;	
	
	switch (key)
	{		
		case MOUSE_WHEELUP:		m_topLine = zMax(m_topLine-2, 1);			break;		
		case MOUSE_WHEELDOWN:	m_topLine = zMin(m_topLine+2, topMax);		break;

		case KEY_PGUP:	m_topLine = zMax(m_topLine-m_viewLines, 1);			break;
		case KEY_PGDN:	m_topLine = zMin(m_topLine+m_viewLines, topMax);	break;

		case KEY_HOME:	m_topLine = 1;										break;
		case KEY_END:	m_topLine = topMax;									break;

		default:		return zCMenuItem::HandleEvent(key);
	};

	key = zinput->GetFirstBindedLogicalKey(key);	

	switch (key)
	{
		case GAME_UP:	m_topLine = zMax(m_topLine-1, 1);					break;
		case GAME_DOWN:	m_topLine = zMin(m_topLine+1, topMax);				break;		
	}

	if (oldTopLine!=m_topLine) DrawFront();	

	return TRUE;
};
*/

// [SPECKELS] Patch 2 (V1.08): Neue HandleEvent Funktion
zBOOL zCMenuItemText::HandleEvent(int key)
{
	if (m_viewLines<0) return zCMenuItem::HandleEvent(key);
	
	int oldTopLine	= m_topLine;
	int topMax		= (m_viewLines<m_numLines)?zMax(1,m_numLines):1;
	// if (key==KEY_ENTER) key = KEY_ESC;	
		
	int logKey = zinput->GetFirstBindedLogicalKey(key);	

	switch (logKey)
	{
		case GAME_UP:	key=KEY_UP;		break;
		case GAME_DOWN:	key=KEY_DOWN;	break;
	}

	switch (key)
	{		
		case MOUSE_WHEELUP:		m_topLine = zMax(m_topLine-2, 1);			break;		
		case MOUSE_WHEELDOWN:	m_topLine = zMin(m_topLine+2, topMax);		break;

		case KEY_PGUP:	m_topLine = zMax(m_topLine-m_viewLines, 1);			break;
		case KEY_PGDN:	m_topLine = zMin(m_topLine+m_viewLines, topMax);	break;

		case KEY_HOME:	m_topLine = 1;										break;
		case KEY_END:	m_topLine = topMax;									break;		

		case KEY_UP:	m_topLine = zMax(m_topLine-1, 1);					break;
		case KEY_DOWN:	m_topLine = zMin(m_topLine+1, topMax);				break;

		default:		return zCMenuItem::HandleEvent(key);
	};

	if (oldTopLine!=m_topLine) DrawFront();	
	
	return TRUE;		
};




void zCMenuItemText::SetText(const zSTRING &txt, const int line, zBOOL draw_now)
{		
	m_topLine		= 1;
	m_viewLines		= -1;
	m_numLines		= -1;
	m_unformated= TRUE;

	if (m_mode != MODE_ENUM)
	{		
		zCMenuItem::SetText(txt,line,draw_now);		
		m_fullText=GetText();				
	}
	else
	{
		zSTRING newText=txt;	

		int num = newText.ToInt();
		if (num>=m_numOptions)	num = m_numOptions-1;
		if (num<0)				num=0;
		newText = m_fullText.PickWord(num+1,"|","|");
		zCMenuItem::SetText(newText,line,draw_now);	
	}
};

void zCMenuItemText::SetText(const zCArray <zSTRING> lines, zBOOL draw_now)
{
	SetText(lines[0],0,draw_now);
};

//
// Slider
//

const int SLIDER_FRAME = 100; //Patch3(Bert)

zCMenuItemSlider::zCMenuItemSlider(const zSTRING& itemID) : zCMenuItem(itemID)
{	
	Setflags(VIEW_TXT_CENTER);
	slider		= 0;
	slideStep	= 0;
	sliderValue = 0.75F;
	sliderDimX	= 0;
	sliderPos	= 0;
};

zCMenuItemSlider::~zCMenuItemSlider() 
{	
};

zBOOL zCMenuItemSlider::ToggleValue(int step, zBOOL loop)
{
	zCMenuItem::ToggleValue(step,loop);

	if (!slider) { zERR_WARNING("B: MENU: No slider defined");return FALSE; }
	
	float oldSliderValue = sliderValue;

	int x0,y0,x1,y1;
	slider->GetExtends(x0,y0,x1,y1);

	/*	
	int sliderPos = x0 + slideStep*step;
	if (sliderPos>8191-sliderDimX)	sliderPos = 8191-sliderDimX;
	if (sliderPos<0)				sliderPos = 0;
	slider->SetPos(sliderPos,y0);
	slider->GetExtends(x0,y0,x1,y1);
	sliderValue = float(x0)/float(8191-sliderDimX);
	*/	

	//Patch3(Bert)
	sliderPos+=step;
	if (sliderPos>m_parUserFloat[0])	sliderPos = (int) m_parUserFloat[0];
	if (sliderPos<0)					sliderPos = 0;
	slider->SetPos(SLIDER_FRAME+sliderPos*slideStep-(x1-x0)/2,y0);
	sliderValue = sliderPos / m_parUserFloat[0];	

	zERR_MESSAGE(8,0,"C: zCMenuItemSlider::SlideRight(): value: " + zSTRING(sliderValue));
	
	// Optionswert schreiben, wenn sich dieser geaendert hat
	if (sliderValue!=oldSliderValue) 
	{
		if (!m_parOnChgSetOption.IsEmpty() ) 
		{
			zoptions->WriteReal(m_parOnChgSetOptionSection,m_parOnChgSetOption,sliderValue,(m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);			
		}		
	}

	return TRUE;
};

void zCMenuItemSlider::InitMenuItem()
{
	zCMenuItem::InitMenuItem();

	// Optionswert auslesen und wieder zurueckschreiben (wieso eigentlich?)
	if (!m_parOnChgSetOption.IsEmpty()) 
	{
		float f;
		f = zoptions->ReadReal(m_parOnChgSetOptionSection,m_parOnChgSetOption,sliderValue);
		sliderValue = f;
		zoptions->WriteReal(m_parOnChgSetOptionSection,m_parOnChgSetOption,sliderValue, (m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);
	};

	//Patch3(Bert)
	slideStep  = (m_parUserFloat[0]>1) ? int((8191-SLIDER_FRAME*2)/(m_parUserFloat[0])) : 8192-SLIDER_FRAME*2;
	sliderPos = int(sliderValue * (m_parUserFloat[0]));
};

void zCMenuItemSlider::InsertInWin(zCView *orgWindow)
{
	// Optionwert (Index) aufl�sen	
	sliderValue = zoptions->ReadReal(m_parOnChgSetOptionSection,m_parOnChgSetOption,0);
	zoptions->WriteReal(m_parOnChgSetOptionSection,m_parOnChgSetOption,sliderValue,(m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);

	zCMenuItem::InsertInWin(orgWindow);

	if (!GetIsVisible()) return;

	sliderDimX = m_pInnerWindow->anx(16);
	int sliderDimY = m_pInnerWindow->any(16);

	int sliderPosY = (8192 - sliderDimY) / 2;
	/*
	if (m_parUserFloat[1] != 0) 	sliderDimX = (int)m_parUserFloat[1];
	else sliderDimX = 8191/20;
	*/

	slider = zNEW(zCViewWindow(0,sliderPosY, sliderDimX, sliderPosY+sliderDimY));

	m_pInnerWindow->InsertItem(slider);			

	slider->ClrFlags(VIEW_TXT_CENTER);

	zoptions->ChangeDir(DIR_TEX_DESKTOP);
	if (!m_parUserString[0].IsEmpty())	slider->InsertBack(m_parUserString[0]);

	//slider->SetTransparency		(254);	
	//slider->SetAlphaBlendFunc	( zRND_ALPHA_FUNC_ADD );

	SetValue(sliderValue);	
};

void zCMenuItemSlider::RemoveFromWin()
{
	if (slider) this->RemoveItem(slider);
	delete slider;slider = 0;
	zCMenuItem::RemoveFromWin();
};

void  zCMenuItemSlider::SetValue(float value)
{
	sliderValue = value;
	sliderPos = int (sliderValue * (m_parUserFloat[0]));
	int x0,y0,x1,y1;
	slider->GetExtends(x0,y0,x1,y1);
	slider->SetPos(SLIDER_FRAME+sliderPos*slideStep-(x1-x0)/2,y0);
};

float zCMenuItemSlider::GetValue()
{
	return sliderValue;
};

zCMenuItemChoice::zCMenuItemChoice(const zSTRING& itemID) : zCMenuItem(itemID)
{
	winCursor = 0;
	option    = 0;
	curStep   = 0;
	optionStart = 0;
};

zCMenuItemChoice::~zCMenuItemChoice()
{
};

zBOOL zCMenuItemChoice::ToggleValue(int step, zBOOL loop)
{
	zCMenuItem::ToggleValue(step,loop);

	option += step;
	
	if (loop)
	{
		// Durchlaufend
		if (option < optionStart)		option = GetNumOptions()-1;	
		if (option >= GetNumOptions())	option = optionStart;
	}
	else
	{
		// An Anfang und Ende stoppend
		if (option < optionStart)		option = optionStart;	
		if (option >= GetNumOptions())	option = GetNumOptions()-1;
	}

	// Optionswert schreiben	
	zoptions->WriteInt(m_parOnChgSetOptionSection,m_parOnChgSetOption,option, (m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);
		
	zERR_MESSAGE(6,0,"B: MEN: Value of Choice: "+zSTRING(option));

	DrawFront();
	return TRUE;
};

int zCMenuItemChoice::SetOptionByString(zSTRING value)
{
	// Optionwert (Index) aufl�sen	
	zERR_MESSAGE(7,0,"B: MEN: Searching current choicebox-setting \""+value+"\" in \""+m_listLines[0]+"\"");
	int i=0;
	zSTRING result;
	do 
	{
		result = m_listLines[0].PickWord(++i,"|#","|#");		
	} while (result != value && !result.IsEmpty());

	option = 0;
	if (result==value) 
	{	
		zERR_MESSAGE(7,0,"B: MEN: Found option at position "+zSTRING(i));
		option=i-1;
	}
	if (option < 0)					option = GetNumOptions()-1;
	if (option >= GetNumOptions())	option = optionStart;		
	return option;
};

zSTRING zCMenuItemChoice::GetStringByOption()
{
	zSTRING result = m_listLines[0].PickWord(option+1,"|#","|#");
	return result;
};

void zCMenuItemChoice::InsertInWin(zCView *orgWindow)
{	
	// Optionwert (Index) aufl�sen	
	option = zoptions->ReadInt(m_parOnChgSetOptionSection,m_parOnChgSetOption,0);
	if (option < 0)					option = GetNumOptions()-1;
	if (option >= GetNumOptions())	option = optionStart;		
	zoptions->WriteInt(m_parOnChgSetOptionSection,m_parOnChgSetOption,option,(m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);

	// Item ins das Fenster einfuegen
	zCMenuItem::InsertInWin(orgWindow);
	
	if (!GetIsVisible()) return;

	// Item initialisieren
	winCursor = zNEW(zCViewWindow(0,0,8191,m_pInnerWindow->FontY()));	
	m_pInnerWindow->InsertItem(winCursor);			

	winCursor -> ClrFlags			(VIEW_TXT_CENTER);
	winCursor -> SetTransparency	(100);	
	winCursor -> SetAlphaBlendFunc	( zRND_ALPHA_FUNC_ADD ) ;
	if (!m_parUserString[0].IsEmpty()) winCursor -> InsertBack(m_parUserString[0]);

	if ( GetEventFunc((zTMenuItemEvent) MENU_EVENT_INIT) != 0 ) {
		zCMenu::GetParser()->CallFunc( GetEventFunc((zTMenuItemEvent)MENU_EVENT_INIT) );
	}

	winCursor->SetPos(0,option * m_pInnerWindow->FontY());

	DrawFront();

	zCMenu* actMenu = zCMenu::GetActive();
	if (actMenu) actMenu->Render();		
};

void zCMenuItemChoice::RemoveFromWin()
{
	if (winCursor) this->RemoveItem(winCursor);
	delete winCursor;
	winCursor = 0;
	zCMenuItem::RemoveFromWin();
};


void zCMenuItemChoice::Resize()
{
	// FontY() muss schon die Gr�sse des Views kennen, da die Gr�sse aber
	// in Abh�ngigkeit von FontY() ermittelt werden soll:
	// tempor�r dem Vater den aktuellen Font geben
	
	UpdateSize();
}


void zCMenuItemChoice::Draw()
{
	zCMenuItem::Draw();	
};


void zCMenuItemChoice::DrawFront()
{
	if (!GetOwner())	return;
	if (!m_pInnerWindow) return;

	zSTRING enumIn = zCMenuItem::GetText();
	
	zSTRING res = enumIn.PickWord(option+1,"#|","#|");			

	m_pInnerWindow->ClrPrintwin();

	UpdateFX();	

	if		(m_parItemFlags & IT_MULTILINE)	 m_pInnerWindow->Printwin	(res+"\n");
	else if (m_parItemFlags & IT_TXT_CENTER) m_pInnerWindow->PrintCXY	(res		);
	else									 m_pInnerWindow->Print		(m_pInnerWindow->anx(20), 0,res);
	
};


/*--------------------------------------------------------------------------
    int zCMenuItemChoice::GetNumOptions()

    22-Nov-00       [HILDEBRANDT]
					Compiler Warnings entfernt.
--------------------------------------------------------------------------*/ 

int zCMenuItemChoice::GetNumOptions()
{	
	zSTRING enumIn	= zCMenuItem::GetText();
	zWORD   wordNr	= 1;

	zSTRING word;	
	do
	{
		word = enumIn.PickWord(wordNr,"#|","#|");
		wordNr++;
	} while (!word.IsEmpty());

	return wordNr-2;
}


zSTRING zCMenuItemChoice::GetText(const int num)
{
	const zSTRING enumIn	= zCMenuItem::GetText();
	
	if (num>=1) return enumIn.PickWord(num,"#|","#|");
	else		return enumIn;
}

void zCMenuItemChoice::InitMenuItem()
{
	zCMenuItem::InitMenuItem();
	if (!m_parOnChgSetOption.IsEmpty()) 
	{	
		zSTRING enumIn	= zCMenuItem::GetText();
		int pos = enumIn.Search("#",1);
		if (pos>=0) optionStart=1; else optionStart=0;

		option = zoptions->ReadInt(m_parOnChgSetOptionSection,m_parOnChgSetOption,0);
		/*
		if (option < 0)					option = GetNumOptions()-1;
		if (option >= GetNumOptions())	option = optionStart;		
		zoptions->WriteInt(m_parOnChgSetOptionSection,m_parOnChgSetOption,option,(m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);
		*/
	};	
};

zCMenuItemButton::zCMenuItemButton(const zSTRING& itemID) : zCMenuItem(itemID)
{
	pic.Clear();
	active = TRUE;
};

zCMenuItemButton::~zCMenuItemButton()
{
	SetEnableHandleEvent(FALSE);
};

void zCMenuItemButton::InitMenuItem()
{
	zCMenuItem::InitMenuItem();

	if (!m_parOnChgSetOption.IsEmpty()) 
	{
		active=zoptions->ReadInt(m_parOnChgSetOptionSection,m_parOnChgSetOption,TRUE);		
		zoptions->WriteInt(m_parOnChgSetOptionSection,m_parOnChgSetOption,active);
	};
	if (active) pic = m_parBackPic;
	else pic = m_parUserString[0];
};

void zCMenuItemButton::Toggle			()
{	
	active = !active;
	if (!active) pic = m_parUserString[0]; else pic = m_parBackPic;

	zoptions->WriteInt(m_parOnChgSetOptionSection,m_parOnChgSetOption,active,(m_parItemFlags & IT_NEEDS_APPLY) == IT_NEEDS_APPLY);
	zoptions->ChangeDir(DIR_TEX_DESKTOP);
		
	InsertBack(pic);
	Draw();
};

zBOOL zCMenuItemButton::Run				()
{
	Enter();
		Toggle();
	Leave();
	return FALSE;
};

void zCMenuItemButton::InsertInWin		(zCView *orgWindow)
{
	zCMenuItem::InsertInWin(orgWindow);

	if (!GetIsVisible()) return;

	zoptions->ChangeDir(DIR_TEX_DESKTOP);
	InsertBack(pic);
};

void zCMenuItemButton::RemoveFromWin	()
{
	zCMenuItem::RemoveFromWin();
};


//
// Listbox
//

const int		LB_PIC_ARROW_DX		= 16;
const int		LB_PIC_ARROW_DY		= 16;

const zSTRING	LB_PIC_ARROW_UP		= "o.tga";
const zSTRING	LB_PIC_ARROW_DN		= "u.tga";

zCMenuItemList::zCMenuItemList(const zSTRING& itemID) : zCMenuItem(itemID)
{	
	m_cur_element	= -1;
	m_top_element	= -1;
	m_pInnerWindow2	= 0;
	m_pViewArrowUp	= 0;
	m_pViewArrowDn	= 0;
};

zCMenuItemList::~zCMenuItemList()
{
	m_pViewArrowUp	= 0;
	m_pViewArrowDn	= 0;
	m_pInnerWindow2	= 0;	
};

zBOOL zCMenuItemList::Run()
{
	if (m_list.GetNumInList()<=0) return FALSE;
	m_cur_element = zMax(m_cur_element,0);
	m_cur_element = zMin(m_cur_element,m_list.GetNumInList()-1);	

	zCMenuItem::Run();

	return FALSE;
};

void zCMenuItemList::InitMenuItem()
{
	
};

zBOOL zCMenuItemList::Show()
{	
	zBOOL result = zCMenuItem::Show();
	if (result) DrawFront();
	return result;
};

zBOOL zCMenuItemList::Hide()
{
	return zCMenuItem::Hide();
};


void zCMenuItemList::DeleteContent()
{
	m_list.DeleteList();
}

void zCMenuItemList::InsertEnd(zTMenuItemListElement& element)
{		
	m_list.InsertEnd(element);	
};

void zCMenuItemList::InsertFront(zTMenuItemListElement& element)
{
	m_list.InsertFront(element);	
};

void zCMenuItemList::InsertInWin(zCView *orgWindow)
{
	zCMenuItem::InsertInWin(orgWindow);

	if (!GetIsVisible()) return;

	/*
	if (!m_pInnerWindow2)
	{		
		m_pInnerWindow2 = zNEW(zCView(0,0,8192,8192));
		m_pInnerWindow->InsertItem(m_pInnerWindow2);
		m_pInnerWindow2->SetFont				(m_pInnerWindow->GetFont());
		m_pInnerWindow2->SetFontColor		(m_pInnerWindow->GetFontColor());
		m_pInnerWindow2->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
		m_pInnerWindow2->SetPos				(0,0);
		m_pInnerWindow2->SetSize				(8192,8192);

	}
	*/

	int dx	= anx(LB_PIC_ARROW_DX);
	int dy	= any(LB_PIC_ARROW_DY);
	
	if (!m_pViewArrowUp) m_pViewArrowUp	= zNEW(zCView(8192-dx,m_parFrameSizeY,8192,m_parFrameSizeY+dy));	
	if (!m_pViewArrowDn) m_pViewArrowDn	= zNEW(zCView(8192-dx,8192-m_parFrameSizeY-dy,8192,8192-m_parFrameSizeY));

	m_pViewArrowUp->InsertBack(LB_PIC_ARROW_UP);
	m_pViewArrowDn->InsertBack(LB_PIC_ARROW_DN);
	InsertItem(m_pViewArrowUp);
	InsertItem(m_pViewArrowDn);
};

void zCMenuItemList::RemoveFromWin()
{
	delete m_pViewArrowUp;	m_pViewArrowUp	= 0;
	delete m_pViewArrowDn;	m_pViewArrowDn	= 0;
	delete m_pInnerWindow2;	m_pInnerWindow2	= 0;		

	zCMenuItem::RemoveFromWin();	
};

void zCMenuItemList::Enter	()
{
	zCMenuItem::Enter();
};

void zCMenuItemList::Leave	()
{
	zCMenuItem::Leave();
};


void zCMenuItemList::UpdateContent()
{
	// nichts machen: Aktion (zusaetzliches Blit) der Basisklasse unterbinden!
};

void zCMenuItemList::DrawFront()
{
	if (!GetOwner())		return;
	if (!m_pInnerWindow)	return;		
	m_pInnerWindow->ClrPrintwin();

	// if (!m_pInnerWindow2)	return;
	// m_pInnerWindow2->ClrPrintwin();

	m_top_element = zMax(m_top_element,0);
	m_cur_element = zMax(m_cur_element,0);
		
	int y				= 0;
	int y_step			= m_pInnerWindow->FontY();
	int max_elements	= int( (8192-y_step) / y_step);	

	if (m_top_element>m_cur_element)				m_top_element = m_cur_element;
	if (m_top_element+max_elements<m_cur_element)	m_top_element = m_cur_element-max_elements;

	zTMenuItemListElement element;
	int	nr = m_top_element;	
	if (nr>=0)
	{	
		while (nr<m_list.GetNumInList() && y<8192-y_step)
		{			
			element = m_list.GetSafe(nr);
			
			if (active && (nr == m_cur_element))	m_pInnerWindow->SetFont(m_pFontHi);
			else									m_pInnerWindow->SetFont(m_pFont);
			m_pInnerWindow->Print(0,y,element.title);
			// if (active && (nr == m_cur_element)) m_pInnerWindow2->Print(0,y,element.title);

			y+=y_step;
 			nr++;	
		}
	}	
	if (m_pViewArrowUp) if (m_top_element==0)			RemoveItem(m_pViewArrowUp); else InsertItem(m_pViewArrowUp);	
	if (m_pViewArrowDn) if (nr>=m_list.GetNumInList())	RemoveItem(m_pViewArrowDn); else InsertItem(m_pViewArrowDn);		
};

zBOOL zCMenuItemList::HandleEvent(int key)
{
	switch (zinput->GetFirstBindedLogicalKey(key))
	{
		case GAME_STRAFELEFT:	key = KEY_LEFT;	break;
		case GAME_STRAFERIGHT:	key = KEY_RIGHT; break;
	};

	switch (key)
	{
		case KEY_LEFT:
		case KEY_RIGHT:
			key = KEY_ESC;
			break;
	}

	switch (key)
	{		
		case MOUSE_WHEELUP:
			JumpToPrevEntry();
			break;
		case MOUSE_WHEELDOWN:
			JumpToNextEntry();
			break;
		case KEY_HOME:
			JumpToTopEntry();
			break;
		case KEY_END:
			JumpToLastEntry();
			break;
		case KEY_ESC:
		case MOUSE_BUTTONRIGHT:
			m_bLeaveItem = TRUE;
			break;
		case KEY_ENTER:
		case MOUSE_BUTTONLEFT:
			ShowContent();
			break;
	};

	key = zinput->GetFirstBindedLogicalKey(key);	

	switch (key)
	{
		case GAME_UP:	
			JumpToPrevEntry();
			break;
		case GAME_DOWN:
			JumpToNextEntry();
			break;		
	};

	return TRUE;
};

void zCMenuItemList::ShowContent()
{	
	zTMenuItemListElement element = m_list.GetSafe(m_cur_element);
	if (element.contentViewer)
	{		
		// element.contentViewer->Setflags(VIEW_STAYONTOP);		
		element.contentViewer->SetText(element.content);
		element.contentViewer->Show();		
		element.contentViewer->Run();
		element.contentViewer->Hide();

	};	
};

void zCMenuItemList::JumpToNextEntry()
{
	if (m_cur_element+1<m_list.GetNumInList()) 
	{ 
		m_cur_element++;
		DrawFront(); 		
	};	
};

void zCMenuItemList::JumpToPrevEntry()
{
	if (m_cur_element>0) 
	{
		m_cur_element--;
		DrawFront();		
	}

};

void zCMenuItemList::JumpToTopEntry()
{
	if (m_cur_element!=0)
	{
		m_cur_element=0;
		DrawFront();		
	}
};

void zCMenuItemList::JumpToLastEntry()
{
	if (m_cur_element!=m_list.GetNumInList()-1)
	{
		m_cur_element=m_list.GetNumInList()-1;
		DrawFront();		
	}
};


