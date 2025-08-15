/********************************************************************************
 
 Project : Gothic - Game
 File    : zmenu.h
 Author  : Carsten Edenfeld (vorher: Bert Speckels,  übernommen 20.05.99) 
 Version : 0.00
 Created : 22.12.98
  
*********************************************************************************
 TODO : 
*********************************************************************************
 BUGS : 
*********************************************************************************
 NOTE : 
*********************************************************************************/

#ifndef __ZMENU_H__
#define __ZMENU_H__

#include "zviews.h"
#include "zmenu_item.h"
#include "zInput.h"

class zCCamera;
class zCWorld;
class zCMusicTheme;
class zCSoundFX;
class zCParser;
class zCTimer;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Viewitem - baseclass
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

enum zTMenuFlags {
	MN_UNDEF			= 0,
	MN_OVERTOP			= 1,
	MN_EXCLUSIVE		= 2,
	MN_NO_ANI			= 4,
	MN_DONTSCALE_DIM	= 8,
	MN_DONTSCALE_POS	= 16,
	MN_ALIGN_CENTER		= 32,
	MN_SHOW_INFO		= 64
};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// MENU - baseclass
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class zCMenu : public zCInputCallback
{	
	friend class zCMenuItem;
    friend class CGameManager; // [Moos] damit der Gamemanager sein Menu wieder loswerden kann..	

public:
	zCMenu(const zSTRING &name);		

	// for sorting
	static	int			CompareNames	( const void *e1 ,const void *e2);

	static	void		SetIsInGame		(zBOOL inGame)		{ inGameMenu = inGame; }; 
	static	zBOOL		IsInGame		()					{ return inGameMenu; };
	

	// menu manager
	static  zCMenu*		GetActive		();
	static  zCTimer*	GetTimer		()						{ return timer;						};
	static  void		CreateParser	();
	static  zCParser*	GetParser		();
	static  void		Startup			();
	static  void		Shutdown		();
	static  void		DefineExternal	( zSTRING &s, zBOOL (*Proc)(), int type, int args... );
	static  zCMenu*		Create			(const zSTRING &name);	
	static	zCMenu*	    GetByName		(const zSTRING &name); 
	
	static  zCCamera*	GetCamera		()						{ return camera;	};
	static  zCWorld *	GetWorld		()						{ return world;		};
	static  void		SetCamera		(zCCamera *cam)			{ camera = cam;		};
	static  void		SetWorld		(zCWorld  *wrld)		{ world  = wrld;	};

	static	void		RegisterFrameCB	( void (*FCB)() )		{ FrameCallback = FCB; };
	static	void		RegisterEnterCB	( void (*ECB)() )		{ EnterCallback = ECB; };
	static  void		RegisterLeaveCB ( void (*LCB)() )		{ LeaveCallback = LCB; };

	// Handling keyboard, mouse and other inputs.	
	virtual zBOOL HandleEvent(int key);	
	virtual zBOOL HandleEnterItem(zCMenuItem* item);
	virtual zBOOL HandleLeaveItem(zCMenuItem* item);
	virtual zBOOL HandleActivateItem(zCMenuItem* item);
	
	// Starting the Menu returns TRUE if previous menues should close 
	virtual zBOOL Run	();
	virtual	void  Enter	();
	virtual	void  Leave	();

	void		PrintInformation(zSTRING s);

	void		SetBackground	(zSTRING &file)		{ backPic = file;					};
	zBOOL		IsExclusive		()					{ return (flags & MN_EXCLUSIVE);	}; 

	void		RestartMusicTheme();

	zCMenuItem*	GetActiveItem	();
	zBOOL		SetActiveItem	(zCMenuItem *item);
	int			GetNumberOfActiveItem();// returns -1 if none active
	zSTRING&	GetBackWorld	();
	zSTRING&	GetBackDatFile	();
	zSTRING&	GetName			();

	void        ForceEvent		(zTMenuItemEvent ev,zSTRING &optionValue) {};
	void		ForceSelAction	(const zTMenuItemSelAction selAction, const zSTRING &selAction_S, zCMenuItem *item = 0);
	void		SetCursorEnabled(zBOOL b)			{ cursorEn = b; };
	void		Release			();

	
	// Redrawing the contents of the menu, including resizing if language changes, update fx for selection / opening, etc. 
	virtual void	Render		();
	virtual void	RedrawItems	();
	virtual void    HandleFrame (zBOOL render = TRUE);
	virtual void	Activate	();
	
	/** PARSER ON **************************************************************************/

	zSTRING backPic;
	zSTRING backWorld;
	int		posx,posy;
	int		dimx,dimy;	
	int		alpha;
	zSTRING	musicThemeName;
	int		eventTimerUpdateMSec;
	zSTRING itemID[MAX_ITEMS];
	int		flags;	
	int		defaultOutGame;
	int		defaultInGame;

	/** PARSER OFF *************************************************************************/

	zCViewWindow* m_pWindow;
	zCViewWindow* m_pInnerWindow;

protected:
	zCMenu();	
	virtual ~zCMenu();
	// initializing the screen: create windows 
	virtual void ScreenInit();

	// resetting the screen: remove windows 
	virtual void ScreenDone();
	
	// Handle selected actions  Returns TRUE if current menu should close
	virtual zBOOL HandleAction	 () ;
	virtual zBOOL HandleSelAction(const zTMenuItemSelAction selAction,const zSTRING &selAction_S, zCMenuItem *item = 0);
	
	virtual void  SetByScript(const zSTRING &id);

	void	UpdateWindowGeometry();

	zCMenuItem*				InsertItem		(zSTRING &name);	

	void	SetName			(const zSTRING &id);
	void	ClearAllEvents	();
	
	void	Register		();
	void	Unregister		();
	zBOOL	IsRegistered	();
	void	RegisterCPP		()										{ registeredCPP = TRUE;	};
	zBOOL	IsRegisteredCPP	()										{ return registeredCPP;	};

	void	PreviousOption	();
	void	NextOption		();

	// build in func 
	virtual zBOOL	ExecCommand(const zSTRING &s);

	/************************************************************************************************/

	static zCParser*	menuParser;
	static zCTimer*		timer;
	static zCArraySort <zCMenu*> menuList;
	static zCArray	   <zCMenu*> activeList;	

	static zCSoundFX	*browseSnd;
	static zCSoundFX	*selectSnd;
	static zCSoundFX	*escSnd;
	static zCVob		*soundSourceVob;

	enum { NONE, BACK, GO, FINISHED } m_exitState;

	zSTRING			name;

	zCMusicTheme*	m_musicTheme;
	int				m_mainSel;
	zBOOL			m_screenInitDone;

	int				m_use_dimx;
	int				m_use_dimy;
	int				m_use_posx;
	int				m_use_posy;	

	zCView*			m_pViewInfo;	
	zCVob*			cursorVob;	

	
	zBOOL			eventOccured[MENU_EVENT_MAX];
	zBOOL			cursorEn;
	zBOOL			noneSelectable;
	zBOOL			registeredCPP;	
	
	int				updateTimer;
	float			fxTimer;
	
	zTMenuItemSelAction forceSelAction;
	zSTRING				forceSelAction_S;
	zCMenuItem*			forceSelActionItem;
	zBOOL				forcedSelAction;	

	zCArray <zCMenuItem *> m_listItems;	

	static void (*FrameCallback)();
	static void (*EnterCallback)();
	static void (*LeaveCallback)();

private:
	void	InitValues		();

	static zCWorld*		world;
	static zCCamera*	camera;

	static zBOOL inGameMenu;
};


#endif