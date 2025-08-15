#ifndef __OMENU_MAIN_H__
#define __OMENU_MAIN_H__

#include "zmenu.h"

const zSTRING NAME_MENU_ITEM_LOADGAME = zSTRING("MENU_ITEM_LISTBOX_LOADGAME");
const zSTRING NAME_MENU_ITEM_SAVEGAME = zSTRING("MENU_ITEM_LISTBOX_SAVEGAME");
const zSTRING MENU_CHG_KEYS			  = zSTRING("MENU_OPT_CONTROLS");
const zSTRING MENU_CHG_KEYS_EXT		  = zSTRING("MENU_OPT_CONTROLS_EXTKEYS");


// Diese C Funktionen können via Skript aufgerufen werden, und müssen
// bei der zCMenu Basis Klasse via zCMenu::AddExternal() registriert werden.


class oCMenu_ChgKeys : public zCMenu
{
public:
	oCMenu_ChgKeys(const zSTRING &name);

	zBOOL	ExecCommand(const zSTRING &s);
	zBOOL	HandleEvent(int key);
	void    ScreenInit ();
	void	Leave	   ();			// update key bindings
	void	InitText   ();

};

class oCMenu_Main : public zCMenu
{
public:
	oCMenu_Main(const zSTRING &name);
	
	zBOOL	HandleEvent(int key);
protected:
	virtual void ScreenInit();
	virtual void ScreenDone();	
};


#endif

