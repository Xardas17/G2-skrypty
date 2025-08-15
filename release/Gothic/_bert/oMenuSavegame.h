/******************************************************************************** 
 
     $Workfile:: omenusavegame.h      $                $Date:: 15.03.01 14:00   $
     $Revision:: 6                    $             $Modtime:: 14.03.01 21:27   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/omenusavegame.h $
 * 
 * 6     15.03.01 14:00 Speckels
 * 
 * 5     31.10.00 11:14 Speckels
 * 
 * 4     10.10.00 18:43 Speckels
 * 
 * 3     10.10.00 14:48 Speckels
 * 
 * 2     9.10.00 20:53 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 6 $ ($Modtime: 14.03.01 21:27 $)

#ifndef __OMENU_SAVEGAME_H__
#define __OMENU_SAVEGAME_H__

#include "omenu_main.h"
#include "osavegame.h"

class oCMenuSavegame : public oCMenu_Main
{
public:		
	enum oTMenuSavegameMode { SAVE, LOAD } mode;

	oCMenuSavegame			(const zSTRING& name, oTMenuSavegameMode _mode);
	virtual ~oCMenuSavegame	();
	
	virtual void HandleSlotChange	(int oldSlot);

	zBOOL	HandleEvent		(int key);
	void	Activate		();

	virtual	int		GetSelectedSlot();

	virtual	void	ScreenInit();
	virtual	void	ScreenDone();

	void			SetSavegameManager(oCSavegameManager* man) { savegameManager=man; }; 
	void			SetScreenshot(zCTextureConvert* texCvt);

protected:			
	int				GetMenuItemSlotNr(zCMenuItem* item);

protected:
	oCSavegameManager*	savegameManager;	
	int					m_selSlot;
	int					m_selSlotItemIndex;

	zCTexture*			m_thumbPic;

	zCMenuItem*			m_item_PlayTime;
	zCMenuItem*			m_item_DateTime;
	zCMenuItem*			m_item_WorldName;
	zCMenuItem*			m_item_GameTime;
	zCMenuItem*			m_item_Thumbpic;	
	
	zCView*				m_item_Thumbpic2;
	
};

#endif