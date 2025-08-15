/********************************************************************************
 
 Project : Menuitem Class 
 File    : zmenu_item.h
 Author  : Carsten Edenfeld 
 Version : 0.00
 Created : 22.12.98
  
*********************************************************************************
 TODO : 
*********************************************************************************
 BUGS : 
*********************************************************************************
 NOTE : 
*********************************************************************************/
#ifndef __ZMENU_MENU_ITEM_H__
#define __ZMENU_MENU_ITEM_H__

#include "zoption.h"
#include "zviews.h"
#include "zvob.h"
#include "zMathtools.h"

//#ifndef Lerp
//#define Lerp(t, a, b) ( a + t * (b - a) ) 
//#endif

const int MAX_ITEMS			= 150;
const int MAX_EVENTS		= 10;
const int MAX_SEL_ACTIONS	= 5;
const int MAX_USERVARS		= 4;
const int MAX_USERSTRINGS	= 10;

enum zTMenuItem {
	MENU_ITEM_UNDEF			= 0,
	MENU_ITEM_TEXT			= 1,
	MENU_ITEM_SLIDER		= 2,
	MENU_ITEM_INPUT			= 3,
	MENU_ITEM_CURSOR		= 4,
	MENU_ITEM_CHOICEBOX		= 5,
	MENU_ITEM_BUTTON		= 6,	
	MENU_ITEM_LISTBOX		= 7	
};

enum zTMenuItemFlags {
	IT_UNDEF			= 0,
	IT_CHROMAKEYED		= 1,
	IT_TRANSPARENT		= 2,
	IT_SELECTABLE		= 4,
	IT_MOVEABLE			= 8,
	IT_TXT_CENTER		= 16,
	IT_DISABLED			= 32,
	IT_FADE				= 64,	

	IT_EFFECTS_NEXT		= 128,	
	IT_ONLY_OUT_GAME	= 256,
	IT_ONLY_IN_GAME		= 512,
	IT_PERF_OPTION		= 1024,
	IT_MULTILINE		= 2048,
	IT_NEEDS_APPLY		= 4096,
	IT_NEEDS_RESTART	= 8192,
	IT_EXTENDED_MENU	= 16384
};

enum zTMenuItemEvent{
	MENU_EVENT_UNDEF	= 0,
	MENU_EVENT_EXECUTE	= 1,
	MENU_EVENT_CHANGED	= 2,
	MENU_EVENT_LEAVE	= 3,
	MENU_EVENT_TIMER	= 4,
	MENU_EVENT_CLOSE	= 5,
	MENU_EVENT_INIT		= 6,
	MENU_EVENT_SEL_PREV	= 7,
	MENU_EVENT_SEL_NEXT	= 8,
	MENU_EVENT_MAX		= 9
};
enum zTMenuItemSelAction {
	SEL_ACTION_UNDEF			= 0,
	SEL_ACTION_BACK				= 1,
	SEL_ACTION_STARTMENU		= 2,
	SEL_ACTION_STARTITEM		= 3,
	SEL_ACTION_CLOSE			= 4,
	SEL_ACTION_CONCOMMANDS		= 5,
	SEL_ACTION_PLAY_SOUND		= 6,
	SEL_ACTION_EXECCOMMANDS		= 7	
};

//////////////////////////////////////////////////////////////////////////
// MENUITEM-BASECLASS ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


class zCMenuItem : public zCView {


	friend class zCMenu;

public:

	zCMenuItem(const zSTRING &name);

	static		zCMenuItem*		GetByName(const zSTRING &name); 
	static		zCMenuItem*		Create	 (const zSTRING &name);

	void		AddRef()	{ 
								m_iRefCtr++;
							};

	void		Release()	{ 
								m_iRefCtr--;
								if (m_iRefCtr<=0 && !IsRegisteredCPP()) 
									delete this; 
							};

	int			GetRef()	{ 
								return m_iRefCtr;
							};

	void				SetByScript		(zSTRING &id);

	virtual	void		InitMenuItem	();

	zTMenuItem			GetType			();
	
	zTMenuItemFlags		GetMenuItemFlags()			{ return (zTMenuItemFlags)m_parItemFlags; };
	void				SetMenuItemFlags(int flags)	{ m_parItemFlags=flags; };

	zSTRING&			GetName			();
	void				SetName			(const zSTRING &name);
	void				GetCoords		(int &x0, int &y0, int &x1, int &y1);  // Absolute virtual screen coords
	void				SetName			(zSTRING &name);
	void				SetIsSelectable (zBOOL b);
	zBOOL				GetIsSelectable	();
	void				SetIsDisabled	(zBOOL b);
	zBOOL				GetIsDisabled	();
	void				SetIsVisible	(zBOOL b);
	zBOOL				GetIsVisible	();
	void				SetReallyDoNotRender(const zBOOL b) { m_bDontRender = b;	};
	zBOOL				GetReallyDoNotRender()const			{ return m_bDontRender;	};
	
	void				SetIsActive		(zBOOL b);
	
	int					GetEventFunc		(const zTMenuItemEvent evNr);
	zTMenuItemSelAction GetSelActionType	(const int num);
	zSTRING&			GetSelActionString	(const int num);
	zCMenuItem*			GetSelItem			();
	void				InitView			();

	virtual	zBOOL		ToggleValue		(int step, zBOOL loop=FALSE);

	virtual		zBOOL	Run				();
	
	virtual zSTRING		GetText			(const int num = 0);
	virtual void		SetText			(const zSTRING &txt, const int line = 0, zBOOL draw_now = FALSE);
	virtual void		SetText			(const zCArray <zSTRING> lines, zBOOL draw_now = FALSE);
	virtual	void		SetMinValue		(float min)			{};
	virtual	void		SetMaxValue		(float max)			{};
	virtual	void		Enter			();
	virtual	void		Leave			();	
	virtual	void		Draw			();
	virtual	void		DrawFront		();
	virtual zBOOL		Show			();
	virtual zBOOL		Hide			();	
	
	virtual zBOOL		HasBeenCanceled()	{ return FALSE; };

	/** PARSER ON *************************************************************************************/

	zSTRING m_parFontName;
	zSTRING m_parText			[MAX_USERSTRINGS];
	zSTRING m_parBackPic;
	zSTRING m_parAlphaMode;	
	int		m_parAlpha;
	int		m_parType;
	int		m_parOnSelAction	[MAX_SEL_ACTIONS]	 ;	
	zSTRING m_parOnSelAction_S	[MAX_SEL_ACTIONS];
	zSTRING m_parOnChgSetOption;
	zSTRING m_parOnChgSetOptionSection;	
	int		m_parOnEventAction	[MAX_EVENTS];
	int		m_parPosX;
	int		m_parPosY;
	int		m_parDimX;
	int		m_parDimY;	
	float	m_parSizeStartScale;
	int		m_parItemFlags;
	float	m_parOpenDelayTime;
	float	m_parOpenDuration;
	float   m_parUserFloat		[MAX_USERVARS];
	zSTRING m_parUserString		[MAX_USERVARS];
	int		m_parFrameSizeX;
	int		m_parFrameSizeY;
	zSTRING	m_parHideIfOptionSectionSet;
	zSTRING	m_parHideIfOptionSet;
	int	    m_parHideOnValue;
	
	/** PARSER OFF *************************************************************************************/	

	static int  CompareNames( const void *e1 ,const void *e2);
	static void Startup		();
	static void Shutdown    ();


protected:
	zCMenuItem();
	virtual ~zCMenuItem();

	int					GetDimX				(int _dimx);
	int					GetDimY				(int _dimy);
	
	virtual void		DrawItems			();
	void				Register			();
	void				Unregister			();

public:
	// FIXME: protected ??	
	void				RegisterByName	(const zSTRING &name)				{ Unregister(); id = name; id.Upper(); Register(); };

protected:

	zBOOL				IsRegistered		();
	void				RegisterCPP			()						{ registeredCPP = TRUE; };
	zBOOL				IsRegisteredCPP		()						{ return registeredCPP; };
	zBOOL				IsInserted			()						{ return inserted; };
	zBOOL				Changed				()						{ return changed;  };

	virtual void		Open				();
	void				Close				();
	zBOOL				Opened				()						{ return opened;	};
	zBOOL				Closed				()						{ return closed;	};
	zBOOL				DoesAutoClose		()						{ return (m_parOpenDuration != -1); };	

	// virtuals 	
	virtual		zBOOL	HandleEvent			(int key);	
	virtual		zBOOL	Input				(int len, zSTRING &ls);		

	virtual		void	InsertInWin			(zCView *orgWindow);
	virtual	    void	RemoveFromWin		();
	
	virtual     void	UpdateContent		();	
	virtual     void	UpdateFX			();	
				void	UpdateSize			();	

	int				m_iRefCtr;
	zCView*			m_pInnerWindow;	
	zCFont*			m_pFont;
	zCFont*			m_pFontHi;					
	zCFont*			m_pFontSel;
	zCFont*			m_pFontDis;					
	zBOOL			m_bViewInitialized;	
	zBOOL			m_bLeaveItem;
	zBOOL			m_bVisible;
	zBOOL			m_bDontRender;
	zCArray<zSTRING>m_listLines;

	zSTRING			id;
	zBOOL			inserted;
	zBOOL			changed;
	zBOOL			active;
	zBOOL			open;
	zBOOL			close;
	zBOOL			opened;
	zBOOL			closed;
	zBOOL			disabled;
	zCView*			orgWin;
	float			fxTimer;
	float			openDelayTimer;		

	static  zCArraySort <zCMenuItem*> itemList;

private:

	void	Init	();
	
	static  zCMenuItem	*tmp;
	float	activeTimer;
	zBOOL	registeredCPP;
	zBOOL	firstTimeInserted;

};

//////////////////////////////////////////////////////////////////////////
// MENUITEMS: InputBox ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


class zCMenuItemInput: public zCMenuItem
{	
public:
	zCMenuItemInput(const zSTRING& itemID);
	virtual ~zCMenuItemInput();

	virtual	void InitMenuItem();

	void	SetValue		(zSTRING _value);
	zSTRING GetValue		();
	
	virtual void Enter		()			{ zCMenuItem::Enter();canceled=FALSE; };
	virtual void Leave		()			{ zCMenuItem::Leave(); };

	zBOOL	HandleEvent		(int key)	{ return TRUE; };

	zBOOL	HasBeenCanceled	()			{ return canceled; };

	zBOOL	Run				();

protected:	

	virtual void InsertInWin(zCView *orgWindow);

protected:

	zSTRING	value;
	zWORD	curPos;
	zBOOL	canceled;
};


//////////////////////////////////////////////////////////////////////////
// TEXT //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
// Dieses Item zeigt entweder den angegebenen Text auf dem Bildschirm an
// oder einen Teil davon (Multi-Option-Text). Welcher Teil, entscheidet sich
// dann durch ein SetText(text) mit text = zSTRING(nummer_der_option)
//

class zCMenuItemText: public zCMenuItem
{
public:
	zCMenuItemText(const zSTRING& itemID);
	virtual ~zCMenuItemText();	

	virtual	void	InitMenuItem();

	virtual void	SetText		(const zSTRING &txt, const int line = 0, zBOOL draw_now = FALSE);
	virtual void	SetText		(const zCArray <zSTRING> lines, zBOOL draw_now = FALSE);	

	virtual	void	SetEnum		(const zSTRING& enumeration);	

	virtual	zBOOL	HandleEvent	(int key);	

	virtual void	DrawFront	();	

protected:	

	void	DrawMultiline();
	void	FormatMultiline();

protected:

	enum { MODE_SIMPLE, MODE_ENUM, MODE_MULTILINE } m_mode;

	zSTRING	m_fullText;		// string merken	
	int		m_numOptions;	// Anzahl der Möglichkeiten

	int		m_topLine;
	int		m_viewLines;
	int		m_numLines;
	zBOOL	m_unformated;	
};

//////////////////////////////////////////////////////////////////////////
// SLIDER //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


class zCMenuItemSlider : public zCMenuItem
{
public:
	zCMenuItemSlider(const zSTRING& itemID);
	virtual ~zCMenuItemSlider();

	virtual	void	InitMenuItem	();

	zCViewWindow*	slider;
	int				slideStep;
	float			sliderValue;		// 0..1

	int				sliderDimX;

	virtual void	SetIsActive		(zBOOL b)			{ zCMenuItem::SetIsActive(b);SetEnableHandleEvent(b); };	

	void			SetValue		(float value);
	float			GetValue		();

	virtual zBOOL	HandleEvent		(int key)			{ return TRUE; };	
	virtual	zBOOL	ToggleValue		(int step, zBOOL loop=FALSE);	

protected:	

	virtual void	InsertInWin		(zCView *orgWindow);
	virtual void	RemoveFromWin	();	

	int sliderPos;				// [EDENFELD] Patch 1.09 aus ModSource
};

//////////////////////////////////////////////////////////////////////////
// BUTTON ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


class zCMenuItemButton : public zCMenuItem
{
public:
	zSTRING pic;
	zBOOL   active;

	zCMenuItemButton(const zSTRING& itemID);
	virtual ~zCMenuItemButton();

	virtual	void	InitMenuItem	();

	void			Toggle			();
	zBOOL			Run				();		

protected:	
	virtual void	InsertInWin		(zCView *orgWindow);
	virtual void	RemoveFromWin	();
};



//////////////////////////////////////////////////////////////////////////
// CHOIS ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


class zCMenuItemChoice : public zCMenuItem
{
public:
	zCMenuItemChoice(const zSTRING& itemID);
	virtual ~zCMenuItemChoice();

	virtual	void	InitMenuItem	();

	void			Clear			();
	//void  SetText		(const zSTRING &txt, zBOOL render = FALSE);
	virtual void	InsertInWin		(zCView *orgWindow);
	virtual void	RemoveFromWin	();
	virtual void	Draw			();
	virtual void	DrawFront		();		

	virtual zBOOL ToggleValue(int step, zBOOL loop=FALSE);


	zCView *winCursor;
	int		option;
	int		optionStart;
	int		curStep;
protected:

	int			SetOptionByString(zSTRING value);
	zSTRING		GetStringByOption();

private:
	int			GetNumOptions	();
	void		Resize			();
	zSTRING		GetText			(const int num);
	
};

struct zTMenuItemListElement
{
	zSTRING		title;	
	zSTRING		content;		
	zCMenuItem*	contentViewer;

	zTMenuItemListElement() { contentViewer=0; };
};

class zCMenuItemList : public zCMenuItem
{	
public:	

	zCMenuItemList(const zSTRING& itemID);
	virtual ~zCMenuItemList();

	virtual	void	InitMenuItem	();

	virtual zBOOL	Run			();
	virtual zBOOL	Show		();
	virtual zBOOL	Hide		();	
	virtual	void	DrawFront	();

	void	DeleteContent();
	void	InsertEnd	(zTMenuItemListElement& element);
	void	InsertFront	(zTMenuItemListElement& element);	
	
	void	ShowContent			();

	virtual	void	Enter		();
	virtual	void	Leave		();

protected:

	virtual void	UpdateContent();	

private:

	virtual void	InsertInWin		(zCView *orgWindow);
	virtual void	RemoveFromWin	();
	virtual	zBOOL	HandleEvent		(int key);	

	void	JumpToNextEntry		();
	void	JumpToPrevEntry		();
	void	JumpToTopEntry		();
	void	JumpToLastEntry		();

	zCArray<zTMenuItemListElement> m_list;

	int		m_cur_element;
	int		m_top_element;	
		
	zCView*	m_pInnerWindow2;
	zCView*	m_pViewArrowUp;
	zCView*	m_pViewArrowDn;	
};


#endif