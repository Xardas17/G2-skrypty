
#ifndef __OMENU_STATUS_H__	// @HOME
#define __OMENU_STATUS_H__

#include "zMenu.h"
#include "ologmanager.h"

//
// Info-Structs
//

struct oSMenuInfoAttribute 
{
	enum oTMenuAttrib { ATTRIB_HP, ATTRIB_DEX, ATTRIB_MANA, ATTRIB_STR }; 
	
	zSTRING			name;
	zSTRING			descr;
	int				actValue;
	int				maxValue;
	oTMenuAttrib	type;
};

struct oSMenuInfoArmor
{
	enum oTMenuArmor { ATTRIB_1H, ATTRIB_2H, ATTRIB_BOW, ATTRIB_CROSSBOW }; 	
	int				actValue;	
};

struct oSMenuInfoTalent 
{
	zSTRING name;
	zSTRING desc;
	zSTRING skillEnum;
	int		value;
	int		skill;
};

class oCMenu_Status;
class oCMenu_Log;
class oCMenu_InfoBar;

//
// Menues
//

class oCMission;

class oCMenu_Log : public zCMenu
{	
	zCMenuItemList* listItemAct;
	zCMenuItemList* listItemOld;
	zCMenuItemList*	listItemFailed;
	zCMenuItemList* listItemLog;
	zCMenuItemText* contentViewer;

public:	
	oCMenu_Log				(const zSTRING &name);

	zBOOL	HandleEvent		(int key);

	void	SetLogTopics	(const zCList<oCLogTopic>& list);
	void	SetDayTime		(const zSTRING &day, const zSTRING &time);

	void	Activate		();

	void	SetInfo			(const zCMenuItem *it);

	virtual void ScreenInit();
	virtual void ScreenDone();

	virtual	zBOOL HandleEnterItem		(zCMenuItem* item);
	virtual	zBOOL HandleLeaveItem		(zCMenuItem* item);
	virtual	zBOOL HandleActivateItem	(zCMenuItem* item);

	virtual zBOOL	ExecCommand(const zSTRING &s);

	void	InitForDisplay	();
};


class oCMenu_Status : public zCMenu
{	
public:
	oCMenu_Status(const zSTRING &name);

	zCArray <oSMenuInfoAttribute>	m_listAttributes;	
	zCArray <oSMenuInfoTalent>		m_listTalents;
	zCArray <oSMenuInfoArmor>		m_listArmory;

	// Setting global parameters
	void	SetPlayerName	(const zSTRING &name);
	void	SetGuild		(const zSTRING &guild);
	void	SetMagicalGuild (const zSTRING &a_strMagicalGuild);

	//void	SetGuildLevel	(const zSTRING &guildLevel);	
	
	// Setting lists
	void	AddAttribute	(const oSMenuInfoAttribute& attrib);				
	void	AddTalent		(const oSMenuInfoTalent&	talent);
	void	AddArmor 		(const oSMenuInfoArmor&	armor);
	
	// Settings unique parameters	
	void	SetExperience	(zDWORD level, zDWORD exp, zDWORD nextLevel);		
	void	SetLearnPoints	(zDWORD points);

	zBOOL	HandleEvent		(int key);

	void	InitForDisplay	();

};

//
// Screens
//

class oCStatusScreen 
{
public:
	oCStatusScreen					();
	virtual ~oCStatusScreen			();		
	oCMenu_Status*	GetStatusMenu	() { return m_pStatusMenu; };
	void			Show			();		

protected:
	
	oCMenu_Status *m_pStatusMenu;
};

class oCLogScreen 
{
public:
	oCLogScreen				();
	virtual ~oCLogScreen	();		
	oCMenu_Log* GetLogMenu	()	{ return m_pLogMenu; };
	void		Show		();			
protected:
	
	oCMenu_Log* m_pLogMenu;
};


class oCMapScreen 
{	
public:
	oCMapScreen				();
	virtual ~oCMapScreen	();	
	void	Show			(int mapInst = 0);
};

#endif