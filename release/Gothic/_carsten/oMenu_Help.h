
#ifndef __OMENU_HELP_H__
#define __OMENU_HELP_H__

#include "zMenu.h"


struct oSMenuKey {
	zSTRING name;
	zSTRING internalName;
	zSTRING desc;
	zWORD	key;
};

class oCMenu_Help : public zCMenu
{
public:
	oCMenu_Help(const zSTRING &name);

	zCArray <oSMenuKey>	  keys;

	void	SetKeys		(const zCArray<oSMenuKey>	&keys);

	zBOOL	HandleEvent(int key);
};


class oCHelpScreen {
public:
	oCHelpScreen();
	~oCHelpScreen();

	oCMenu_Help *help;

	void	SetKeys		(const zCArray<oSMenuKey>	&keys);

	void	Show();
};



#endif