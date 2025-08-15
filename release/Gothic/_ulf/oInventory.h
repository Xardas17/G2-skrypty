/******************************************************************************** 

	$Workfile:: oInventory.h		$			$Date:: 22.07.02 00:00			$
	$Revision:: 1					$			$Modtime:: 22.07.02 00:00		$
	$Author:: Bendlin															$
	Subproject:: Gothic
	Copyright:: 1998-2002, Piranha Bytes Software GmbH
 
	Description: declarations for container/npc inventories

*	$Log: /current_work/Gothic/_Ulf/oInventory.h								$
*	
*********************************************************************************/

#ifndef __OINVENTORY__
#define __OINVENTORY__

class oCNpc;
class oCItem;
class zCGfx;
class zCView;
class zCTexture;

// max items inventory
extern	const int INV_MAX_ITEMS;

const int INV_MAX_SLOTS_COL	= 8;
const int INV_MAX_SLOTS_ROW	= 2;

#include "zString.h"
#include "zList.h"
#include "zViewBase.h"
#include "zView.h"
#include "zArchiver.h"

enum {	INV_NONE	= 0,	INV_COMBAT		= 1,	INV_ARMOR		= 2,	
		INV_RUNE	= 3,	INV_MAGIC		= 4,	INV_FOOD		= 5,
		INV_POTION	= 6,    INV_DOCS		= 7,	INV_OTHER		= 8,
		INV_MAX		= 9	};

enum {	INV_MODE_DEFAULT	= 0,
		INV_MODE_CONTAINER	= 1,
		INV_MODE_PLUNDER	= 2,
		INV_MODE_STEAL		= 3,
		INV_MODE_BUY		= 4,
		INV_MODE_SELL		= 5,
		INV_MODE_MAX		= 6 };

class oCItemContainer : public zCInputCallback {

public:

//	enum oTItemListMode { FULLSCREEN, HALFSCREEN, ONE };

	// Statics
	static	void		Container_PrepareDraw				();
	static	void		Container_Draw						();
															
	// Methodes												
	oCItemContainer											();
	virtual ~oCItemContainer								();
															
	virtual void				Open						(int x, int y, int mode);
	virtual void				OpenPassive					(int x, int y, int mode);

	virtual zSTRING				GetName						()				{ return titleText; };
	virtual void				SetName						(zSTRING& name)	{ if (!name.IsEmpty()) titleText = name; return; };
	virtual int					GetMode						()			{ return invMode; };
	virtual void				SetMode						(int mode)	{ if ((mode>=INV_MODE_DEFAULT)&&(mode<INV_MODE_MAX)) invMode = mode; return; };
	
	virtual void				Close						();
	virtual void				Activate					();
	virtual void				Deactivate					();
	virtual zBOOL				IsOpen						();
	virtual zBOOL				IsActive					()	{ return frame;  };
	virtual zBOOL				IsEmpty						();
	virtual zBOOL				IsSplitScreen				();
															
	virtual void				SetContents					(zCListSort<oCItem> *list);
	virtual zCListSort<oCItem>*	GetContents					();
															
	virtual oCItem*				Insert						(oCItem* item);
	virtual void				Remove						(oCItem* item);
	virtual oCItem*				Remove						(oCItem* item, int anz);
	virtual oCItem*				RemoveByPtr					(oCItem* item, int anz);
															
	virtual oCItem*				GetSelectedItem				();
	virtual int					GetSelectedItemCount		();
	virtual void				GetSize						(int &x, int &y);
															
	virtual void				DisableManipulateItems		(zBOOL dis=TRUE)		{ m_bManipulateItemsDisabled = dis;	};
	virtual zBOOL				CanManipulateItems			()						{ return !m_bManipulateItemsDisabled;	};

	virtual void				DisableTransferMoreThanOneItem(zBOOL dis=TRUE)		{ m_bCanTransferMoreThanOneItem = !dis;	};
	virtual zBOOL				CanTransferMoreThanOneItem	()						{ return m_bCanTransferMoreThanOneItem;	};

	virtual zBOOL				IsPassive					();
															
	static	zBOOL				GetInvSplitScreen			();
	static	zINT				GetInvMaxColumns			();
	static	zINT				GetInvMaxRows				();
	static	zINT				TransferCountToAmount		(zINT count);

	virtual zINT				GetTransferCount			()						{ return TransferCount; };
	virtual void				SetTransferCount			(const zINT cntAmount)	{ TransferCount = cntAmount; };
	virtual void				IncTransferCount			(const zINT cntAmount)	{ TransferCount += cntAmount; };
															
	// Archive												
	virtual void				Archive						(zCArchiver &arc);
	virtual void				Unarchive					(zCArchiver &arc);

	///////////////////////////////////////////////////////////
	//
	//	STATIC
	//
	///////////////////////////////////////////////////////////

	static	zREAL				GetValueMultiplier();
	static	zSTRING				GetCurrencyInstanceName();
	static	int					GetCurrencyInstance();
	static	oCItem*				CreateCurrencyItem(zINT amount = 1);
	static	void				RemoveCurrencyItem(oCItem* item);

protected:													
															
	virtual void				Init						(int x, int  y, int mode);
	virtual void				GetPosition					(int &x,int &y);
	virtual void				LoadGrafix					();
	virtual void				DeleteContents				();
															
	virtual zBOOL				HandleEvent					(int key);
															
	// Movement												
	virtual	void				NextItem					();
	virtual	void				NextItemLine				();
	virtual	void				PrevItem					();
	virtual	void				PrevItemLine				();
	virtual void				CheckSelectedItem			();
	virtual	zBOOL				TransferItem				(int dir, int maxAmount);
//	virtual void				SetCategoryOnRightContainer	();
	
	// Draw
	virtual void				Draw						();
	virtual void				DrawCategory				();
	virtual void				DrawItemInfo				( oCItem* pItem, zCWorld* pWorld );
															
	// Helpers												
	zCListSort<oCItem>*			JumpOffset					(zBOOL& isAtTop, zBOOL& isAtBottom);

	// Vars
	zCListSort<oCItem>*			contents;		// List of all Items in Container
	oCNpc*						npc;			// Owner
	zSTRING						titleText;		// inventory's name (display)
	int							invMode;		// inventory mode	
	int							selectedItem;	// Current selected Item
	int							offset;			// Current offset in List
	int							maxSlotsCol;	// Maximal Items to be drawn
	int							maxSlotsColScr;	// Maximal Items drawable on screen
	int							maxSlotsRow;	// Maximal Items to be drawn
	int							maxSlotsRowScr;	// Maximal Items drawable on screen
	int							maxSlots;		// Maximal Items to be drawn
	int							marginTop;		// Space on top (screen)
	int							marginLeft;		// Space on left/right (screen)
//	oTItemListMode				itemListMode;	// Maximal Items to be drawn
	zBOOL						frame;			// Highlight Selected Item
	zBOOL						right;			// Left or Right ?
//	zBOOL						isOpen;			// Open or Closed ? ( only Visual ! )  // [Moos] da nur sehr wenige Container offen sein können, machen wir das jetzt über eine Liste.
	zBOOL						ownList;		// is it own list ?
	zBOOL						prepared;		// Item is prepared for drawing ?

	zBOOL						passive;		// passive = only used for display purposes

	zINT						TransferCount;	// Number of Items currently transfered within one action

	// Views	
	zCView*						viewTitle;						// title
	zCView*						viewBack;						// slots
	zCView*						viewItem;						// items
	zCView*						viewItemActive;					// items - equipped
	zCView*						viewItemHightlighted;			// items - selected
	zCView*						viewItemActiveHighlighted;		// items - equipped + selected
	zCView*						viewItemInfo;					// infos
	zCView*						viewItemInfoItem;				// infos - item
	zCView*						textView;
	zCView*						viewArrowAtTop;
	zCView*						viewArrowAtBottom;
	zCWorld*					rndWorld;
	int							posx, posy;	

	zBOOL						m_bManipulateItemsDisabled;
	zBOOL						m_bCanTransferMoreThanOneItem;

	// Statics
	static	zCList<oCItemContainer>		contList;	// All Container
	static	zBOOL						gfx_loaded;
	static	zCGfx*						gfx_cat;
	static	zCGfx*						gfx_equip;
	static	zCGfx*						gfx_cursor;
	static	zCGfx*						gfx_cursor_equip;
	static	zCGfx*						gfx_arrow[4];	

	// New 
	static	zCTexture*					tex_back;
	static	zCTexture*					tex_cat;
	static	zCTexture*					tex_equip;
	static	zCTexture*					tex_cursor;
	static	zCTexture*					tex_cursor_equip;
	static	zCTexture*					tex_arrow[4];	

	oCItemContainer*					GetNextContainerLeft (oCItemContainer* self);
	oCItemContainer*					GetNextContainerRight(oCItemContainer* self);
	zBOOL								ActivateNextContainer(int dir);
};

class oCStealContainer : public oCItemContainer
{
public:
	// Con / Destructor
			oCStealContainer			();
	virtual	~oCStealContainer			();
	// Methods
	virtual zBOOL	HandleEvent			(int key);
	// New
	virtual void	SetOwner			(oCNpc* npc);
	virtual oCNpc*	GetOwner			();
	virtual void	CreateList			();
protected:
	oCNpc*	owner;
};

class oCNpcContainer : public oCStealContainer
{
public:
					oCNpcContainer		();
	virtual			~oCNpcContainer		();

	// Methods
	virtual zBOOL	HandleEvent			(int key);
	// New
	virtual void	CreateList			();

	virtual oCItem*	Insert				(oCItem* item);
	virtual void	Remove				(oCItem* item);
};

// ******************************************************************************
// NSC - Inventory
// ******************************************************************************

// changed [dennis]

class oCNpcInventory : public oCItemContainer {

public:
	oCNpcInventory								();
	virtual ~oCNpcInventory						();
												
	void			Open						(int x, int y, int mode);
	void			Close						();
	void			SetOwner					(oCNpc* npc);
	oCNpc*			GetOwner					(void);
												
	// **** Insert / Remove						
	int				GetCategory					(oCItem* item);
	virtual oCItem*	Insert						(oCItem* item);
	virtual void	Remove						(oCItem* item);
												
	virtual oCItem*	IsIn						(oCItem* item,			int anz = 1);
	virtual oCItem*	IsIn						(int instance,			int anz = 1);
	virtual oCItem*	IsIn						(const zSTRING& name,	int anz = 1);
	virtual oCItem*	Remove						(oCItem* item,			int anz);
	virtual oCItem*	RemoveByPtr					(oCItem* item,			int anz);
	virtual oCItem*	Remove						(int instance,			int anz = 1);
	virtual oCItem*	Remove						(const zSTRING& name,	int anz = 1);
												
	int				GetAmount					(int instance);
												
	// [BENDLIN] Addon Patch - Added IgnoreActive
	virtual zBOOL	IsEmpty						(zBOOL bIgnoreArmor = FALSE, zBOOL bIgnoreActive = FALSE);
//			zBOOL	IsCatEmpty					(int nr=-1);
//			int		GetNumItemsInCategory		(int nCategory);
			int		GetNumItemsInCategory		();
												
	// **** Control								
	virtual zBOOL	HandleEvent					(int key);
	zBOOL			HandleTrade					(int key);
//	int				GetNextCategory				();
//	int				GetCurrentCategory			()										{ return invnr; }
//	int				GetPrevCategory				();
//	zBOOL			SwitchToCategory			(int nr);
//	zBOOL			SwitchNextCategory			();
//	zBOOL			SwitchPrevCategory			();
//	zBOOL			FindNextCategory			();
//	void			SetFirstCategory			();

	//
	//	CODECHANGE [ROMAN]
	//
	// oCItem*			GetItem						( int nCategory, int nSlot );
	oCItem*			GetItem						(int nSlot );
	//
	//	CODECHANGE [ROMAN] END
	//

	// **** Specials
	void				CheckForEquippedItems	(zBOOL ignoreArmor = FALSE);
	void				ClearInventory			();

	// **** Archive
	void			Archive					(zCArchiver &arc);
	void			Unarchive				(zCArchiver &arc);

	// **** Check
	//changed [dennis]
	zBOOL			CanCarry				(oCItem* item);

	// Packing
	void			SetPackAbility			(zBOOL packingOn);
	zBOOL			GetPackAbility			()					{ return packAbility;		};
	
	void			PackAllItems			(zBOOL packEquipped = FALSE);
	void			UnpackAllItems			();

	// General Unpack uses automatically Category INV_NONE and parameter-Category
//	void			UnpackCategory			(int nCategory);
	void			UnpackCategory			();

//	void			PackItemsInCategory		(int nCategory, zBOOL packEquipped = FALSE);
	void			PackItemsInCategory		(zBOOL packEquipped = FALSE);
//	void			UnpackItemsInCategory	(int nCategory);
	void			UnpackItemsInCategory	();

protected:
	virtual void	Draw					();
	virtual void	DrawCategory			();

	oCItem*			CreateFromPackString	(const zSTRING &name);
	zBOOL			GetPackedItemInfo		(const zSTRING &name, zBOOL destroyEntry, int& amount, zBOOL &equipped);
	zBOOL			PackSingleItem			(oCItem* item);
	// int				GetNumItemsInPackString	(int cat);
	int				GetNumItemsInPackString	();
	// zBOOL			GetPackedItemBySlot		(int cat, int slotNr, zSTRING& itemInstance);
	zBOOL			GetPackedItemBySlot		(int slotNr, zSTRING& itemInstance);

private:
	oCNpc*			owner;
	
	zBOOL			packAbility;			// Item pack/unpack mechanism on/off

	// zCListSort<oCItem> inventory			[INV_MAX];	
	zCListSort<oCItem> inventory;	
	// zSTRING			packString				[INV_MAX];
	zSTRING			packString;
	
	// int				_offset					[INV_MAX];
	// int				_itemnr					[INV_MAX];
	// int				maxSlots				[INV_MAX];
	int				maxSlots;
	// int				invnr;					// Die aktuelle Inventory-Kategory

	// Statics
	// static	zCGfx*	gfx_cats				[INV_MAX];
	static			zCGfx*	gfx_title;
};

#endif
