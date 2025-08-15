/******************************************************************************** 
 
     $Workfile:: oInventory.cpp       $                $Date:: 24.04.01 17:33   $
     $Revision:: 186                  $             $Modtime:: 20.04.01 17:46   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oInventory.cpp $
 * 
 *********************************************************************************/


#include "zCore.h"
#include "zOption.h"
#include "zViewBase.h"
#include "zView.h"
#include "zWorld.h"
#include "zRenderer.h"
#include "zSound.h"
#include "zArchiver.h"
#include "zTexture.h"
#include "zParser.h"
#include "zEventMan.h"
#include "zSoundMan.h"
#include "zInput_Const.h"
#include "zInput_Win32.h"
#include "zFonts.h"
#include "zAccount.h"

#include "zIncDialogs.h"
#include "oItem.h"
#include "oViewDialogItem.h"
#include "oInventory.h"
#include "oViewDialogItemContainer.h"
#include "oViewDialogStealContainer.h"
#include "oViewDialogInventory.h"
#include "oInventory.h"
#include "oViewDialogTrade.h"

#include "oNpc.h"
#include "oItem.h"
#include "oGame.h"
#include "oWorld.h"
#include "oMobInter.h"
#include "oNpcMessages.h"
#include "oMagic.h"
#include "oAiShoot.h"


//////////////////////////////////////////////////////////////////////////////
// preprocessors

#define PACKED_INVENTORY	// enables stackable items

//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// general constants

const int INV_MAX_ITEMS		= 0x00000400;	// 1024, max number of items in inventory

//////////////////////////////////////////////////////////////////////////////
// layout constants (put in script vars?)

const int		INV_ALPHA			= 0xFF;						// 100%, opacity of active inventory
const int		INV_ALPHA_NOFOCUS	= 0x40;						// 25%, opacity of inactive inventory

const zCOLOR	INV_COLOR_LIGHT		(0x90, 0x90, 0x90, 0xFF);	// inactive title font color (light grey)
const zCOLOR	INV_COLOR_DEFAULT	(0xD0, 0xD0, 0xD0, 0xFF);	// default text color (grey)
const zCOLOR	INV_COLOR_BRIGHT	(0xFF, 0xFF, 0xFF, 0xFF);	// highlighted text color (white)
const zCOLOR	INV_COLOR_HOTKEY	(0xFF, 0x00, 0x00, 0xFF);	// hotkey font color (red)

const int		INV_SCALE_X			= 800; // 0x0280;	// 800, base width for scaling (pixel)	// [BENDLIN] 800x600, old = 640
const int		INV_SCALE_Y			= 600; // 0x01E0;	// 480, base height for scaling (pixel)	// [BENDLIN] 800x600, old = 480

//////////////////////////////////////////////////////////////////////////////
// font texture

const zSTRING FNT_INV_DEFAULT		= "FONT_DEFAULT.TGA";		// default texture for standard text
const zSTRING TEXT_FONT_INVENTORY	= "TEXT_FONT_INVENTORY";	// srcipt var which overrides default

//////////////////////////////////////////////////////////////////////////////
// layout textures and blend functions

const zSTRING				TEX_INV_BACK								= "INV_BACK.TGA";						// standard background (all)
const zTRnd_AlphaBlendFunc	TEX_INV_BACK_BLEND							= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_BACK_CONTAINER						= "INV_BACK_CONTAINER.TGA";				// background container (all)
const zTRnd_AlphaBlendFunc	TEX_INV_BACK_CONTAINER_BLEND				= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_BACK_PLUNDER						= "INV_BACK_PLUNDER.TGA";				// background plunder target (all)
const zTRnd_AlphaBlendFunc	TEX_INV_BACK_PLUNDER_BLEND					= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_BACK_STEAL							= "INV_BACK_STEAL.TGA";					// background steal target (all)
const zTRnd_AlphaBlendFunc	TEX_INV_BACK_STEAL_BLEND					= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_BACK_BUY							= "INV_BACK_BUY.TGA";					// background trade - trader (all)
const zTRnd_AlphaBlendFunc	TEX_INV_BACK_BUY_BLEND						= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_BACK_SELL							= "INV_BACK_SELL.TGA";					// background trade - player (all)
const zTRnd_AlphaBlendFunc	TEX_INV_BACK_SELL_BLEND						= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_TITLE								= "INV_TITLE.TGA";						// inventory title (border)
const zTRnd_AlphaBlendFunc	TEX_INV_TITLE_BLEND							= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_ITEM								= "INV_SLOT.TGA";						// normal slot (border)
const zTRnd_AlphaBlendFunc	TEX_INV_ITEM_BLEND							= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_ITEM_ACTIVATED						= "INV_SLOT_EQUIPPED.TGA";				// equipped slot (border)
const zTRnd_AlphaBlendFunc	TEX_INV_ITEM_ACTIVATED_BLEND				= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_ITEM_ACTIVATED_HIGHLIGHTED			= "INV_SLOT_EQUIPPED_HIGHLIGHTED.TGA";	// equipped and higlighted slot (border)
const zTRnd_AlphaBlendFunc	TEX_INV_ITEM_ACTIVATED_HIGHLIGHTED_BLEND	= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_ITEM_HIGHLIGHTED					= "INV_SLOT_HIGHLIGHTED.TGA";			// higlighted slot (border)
const zTRnd_AlphaBlendFunc	TEX_INV_ITEM_HIGHLIGHTED_BLEND				= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_ITEMINFO							= "INV_DESC.tga";						// item description (border)
const zTRnd_AlphaBlendFunc	TEX_INV_ITEMINFO_BLEND						= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_ARROW_TOP							= "O.TGA";								// up arrow
const zTRnd_AlphaBlendFunc	TEX_INV_ARROW_TOP_BLEND						= zRND_ALPHA_FUNC_BLEND;
const zSTRING				TEX_INV_ARROW_BOTTOM						= "U.TGA";								// down arrow
const zTRnd_AlphaBlendFunc	TEX_INV_ARROW_BOTTOM_BLEND					= zRND_ALPHA_FUNC_BLEND;

// Groesse fuer Iteminformationen
const int INV_INF_SIZEX				= 300; // Pixel (eigentlich 192)
const int INV_INF_SIZEY				= 32;  // Pixel
const int INV_INF_DX				= 10;  // Pixel

// Größe des gerenderten Items
const int INV_ITEM_SIZEX			= 70; // Pixel (eigentlich 100)
const int INV_ITEM_SIZEY			= 70; // Pixel (eigentlich 100)

// Offset und Rand fuer die Anzeige eines Items-Slots
const int INV_ITEM_WIDTH			= 70;
const int INV_ITEM_HEIGHT			= 70;

const int TEXT_INV_CATX				= 10;	// Pixel
const int TEXT_INV_CATY				= 7;	// Pixel

// Groesse fuer Iteminformationen
static int inv_inf_sizex;
static int inv_inf_sizey;
static int inv_inf_dx;

// Größe des gerenderten Items
static int inv_item_sizex;
static int inv_item_sizey;

// Offset und Rand fuer die Anzeige eines Items-Slots
static int inv_item_dx;
static int inv_item_dy;

static int inv_item_ofsy;
static int inv_item_ofsx;
static int inv_item_width;
static int inv_item_height;


// **********************************************************************************
// Einfacher Container
// **********************************************************************************

zBOOL	oCItemContainer::gfx_loaded			= FALSE;
zCGfx*	oCItemContainer::gfx_cat			= NULL;
zCGfx*	oCItemContainer::gfx_equip			= NULL;
zCGfx*	oCItemContainer::gfx_cursor			= NULL;
zCGfx*	oCItemContainer::gfx_cursor_equip	= NULL;
zCGfx*	oCItemContainer::gfx_arrow[4]		= { NULL, NULL, NULL, NULL };

zCList <oCItemContainer> oCItemContainer::contList;
zCList <oCItemContainer> s_openContainers;

// Static Functions

// SplitScreen-Modus ermitteln
zBOOL oCItemContainer::GetInvSplitScreen()
{
	static zINT invSplitScreen = -2;
	if (invSplitScreen == -2)
		invSplitScreen = zoptions->ReadBool(zOPT_SEC_GAME, "invSplitScreen", TRUE);
	return zBOOL(invSplitScreen);
}

// Maximale Spaltenanzahl ermitteln
zINT oCItemContainer::GetInvMaxColumns()
{
	static zINT invMaxColumns = 0;
	if (invMaxColumns == 0)
		invMaxColumns = zoptions->ReadInt(zOPT_SEC_GAME, "invMaxColumns", 5);
	if (invMaxColumns == 0)
		invMaxColumns = -1;
	if (invMaxColumns <= 0)
		return INV_MAX_ITEMS;
	else
		return invMaxColumns;
}

// Maximale Zeilenanzahl ermitteln
zINT oCItemContainer::GetInvMaxRows()
{
	static zINT invMaxRows = 0;
	if (invMaxRows == 0)
		invMaxRows = zoptions->ReadInt(zOPT_SEC_GAME, "invMaxRows", 0);
	if (invMaxRows == 0)
		invMaxRows = -1;
	if (invMaxRows <= 0)
		return INV_MAX_ITEMS;
	else
		return invMaxRows;
}

// Utility, map current tranfer count to transfer amount
zINT oCItemContainer::TransferCountToAmount(zINT count)
{
	if ( count >= 10000 )	return 10000;
	if ( count >= 1000 )	return 1000;
	if ( count >= 100 )		return 100;
	if ( count >= 10 )		return 10;
	return 1;
}

// Händler-Faktor
zREAL oCItemContainer::GetValueMultiplier()
{
	static zREAL valueMultiplier = 0.0f;
	if (valueMultiplier == 0.0f)
	{
		zCPar_Symbol* pSymbol = ::parser.GetSymbol(zSTRING("TRADE_VALUE_MULTIPLIER"));
		if (pSymbol)
			pSymbol->GetValue(valueMultiplier);
		if (valueMultiplier <= 0.0f)
			valueMultiplier = 0.3f;  // DEFAULT
	}
	return valueMultiplier;
}

// Instanzen-Name des Währungs-Items
zSTRING oCItemContainer::GetCurrencyInstanceName()
{
	static zSTRING CurrencyInstanceName = zSTRING("");
	if (CurrencyInstanceName.IsEmpty())
	{
		zCPar_Symbol* pSymbol = ::parser.GetSymbol(zSTRING("TRADE_CURRENCY_INSTANCE"));
		if (pSymbol)
			pSymbol->GetValue(CurrencyInstanceName);
		if (CurrencyInstanceName.IsEmpty())
			CurrencyInstanceName = zSTRING("ITMI_GOLD");
	}

	return CurrencyInstanceName;
}

// Instanzen-Name des Währungs-Items
int oCItemContainer::GetCurrencyInstance()
{
	static int CurrencyInstance = -1;
	if (CurrencyInstance == -1)
		CurrencyInstance = ::parser.GetIndex(GetCurrencyInstanceName());

	return CurrencyInstance;
}

// Erzeuge eine Instanz vom Währungs-Item
oCItem* oCItemContainer::CreateCurrencyItem(zINT amount)
{
	oCItem* Result = NULL;

	if (ogame && ogame->GetWorld())
	{
		Result = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, GetCurrencyInstanceName());
		if (Result)
			Result->SetAmount(amount);
	}
	
	return Result;
}

// Entferne eine Instanz eines Währungs-Items
void oCItemContainer::RemoveCurrencyItem(oCItem* item)
{
	if (ogame && ogame->GetWorld())
		ogame->GetGameWorld()->RemoveVob(item);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
///
///	Inventar - Sortierroutinen (static)
///

//////////////////////////////////////////////////////////////////////////////
//	default - sort by instance name
static int InventorySortDefault(oCItem *item1, oCItem *item2)
{
	return strcmp(item1->GetInstanceName().ToChar(), item2->GetInstanceName().ToChar());
}

//////////////////////////////////////////////////////////////////////////////
//	weapons
static int InventorySortCombat(oCItem *item1, oCItem *item2)
{
	int t1;
	int t2;
	if ( item1->GetMainFlag() == ITM_CAT_NF )	t1 = 0; else
	if ( item1->GetMainFlag() == ITM_CAT_FF )	t1 = 1; else
	if ( item1->GetMainFlag() == ITM_CAT_MUN )	t1 = 2; else
												t1 = 3;
	if ( item2->GetMainFlag() == ITM_CAT_NF )	t2 = 0; else
	if ( item2->GetMainFlag() == ITM_CAT_FF )	t2 = 1; else
	if ( item2->GetMainFlag() == ITM_CAT_MUN )	t2 = 2; else
												t2 = 3;
	// primary: category
	if ( t1 < t2 )
		return -1;
	if ( t1 > t2 )
		return 1;

	// secondary: damage
	if ( (t1 == 0) || (t1 == 1) )  // ITM_CAT_NF, ITM_CAT_FF
	{
		int d1 = item1->GetFullDamage();
		int d2 = item2->GetFullDamage();
		if ( d1 > d2 )
			return -1;
		if ( d1 < d2 )
			return 1;
	}
	
	// default
	return InventorySortDefault(item1, item2);
}

//////////////////////////////////////////////////////////////////////////////
//	potions

//////////////////////////////////////////////////////////////////////////////
//	food
static int InventorySortFood(oCItem *item1, oCItem *item2)
{	
	int v1 = 0;
	int v2 = 0;
	int d1 = item1->GetHealMode(v1);
	int d2 = item2->GetHealMode(v2);

	// primary: mode
	if ( d1 < d2 )
		return -1;
	if ( d1 > d2 )
		return 1;

	// secondary: value
	if ( v1 > v2) 
		return -1;
	if ( v1 < v2) 
		return 1;

	// default
	return InventorySortDefault(item1, item2);
}

//////////////////////////////////////////////////////////////////////////////
//	armor
static int InventorySortArmor(oCItem *item1, oCItem *item2)
{
	// primary: wear type
	int w1 = item1->GetWearType();
	int w2 = item2->GetWearType();
	if (w1 < w2)
		return -1;
	if (w1 > w2)
		return 1;
	
	// secondary: protection
	int p1 = item1->GetFullProtection();
	int p2 = item2->GetFullProtection();
	if ( p1 > p2)
		return -1;
	if ( p1 < p2)
		return 1;

	// default
	return InventorySortDefault(item1, item2);
}

//////////////////////////////////////////////////////////////////////////////
//	magic

static int InventorySortMagic(oCItem *item1, oCItem *item2)
{
	int t1;
	int t2;
	// primary: type
	if ( item1->HasFlag(ITM_FLAG_AMULET) )	t1 = 0; else
	if ( item1->HasFlag(ITM_FLAG_RING) )	t1 = 1; else
	if ( item1->HasFlag(ITM_FLAG_BELT) )	t1 = 2; else
											t1 = 3;
	if ( item2->HasFlag(ITM_FLAG_AMULET) )	t2 = 0; else
	if ( item2->HasFlag(ITM_FLAG_RING) )	t2 = 1; else
	if ( item2->HasFlag(ITM_FLAG_BELT) )	t2 = 2; else
											t2 = 3;
	if (t1 < t2)
		return -1;
	if (t1 > t2)
		return 1;
	
	// default
	return InventorySortDefault(item1, item2);
}

//////////////////////////////////////////////////////////////////////////////
//	rune

//////////////////////////////////////////////////////////////////////////////
//	other
static int InventorySortOther(oCItem *item1, oCItem *item2)
{
	int t1;
	int t2;

	if ( item1->GetInstanceName().CompareTo("ITLSTORCHBURNING") == 0 )	t1 = 0; else
	if ( item1->HasFlag(ITM_FLAG_MI) )									t1 = 1; else
																		t1 = 2;
	if ( item2->GetInstanceName().CompareTo("ITLSTORCHBURNING") == 0 )	t2 = 0; else
	if ( item2->HasFlag(ITM_FLAG_MI) )									t2 = 1;
																		t2 = 2;
	// primary: type
	if ( t1 < t2 ) 
		return -1;
	if ( t1 > t2 ) 
		return 1;

	// default
	return InventorySortDefault(item1, item2);
}

////////////////////////////////////////////////////////////////////////////////
//
//	Sort by Category
//
////////////////////////////////////////////////////////////////////////////////

static int InventorySort_CatOrder[INV_MAX] =
{
	//  0      1      2    3     4     5    6    7     8
	// "COMBAT,POTION,FOOD,ARMOR,MAGIC,RUNE,DOCS,OTHER,NONE"
	/* INV_NONE   */ 8,
	/* INV_COMBAT */ 0,
	/* INV_ARMOR  */ 3,
	/* INV_RUNE   */ 5,
	/* INV_MAGIC  */ 4,
	/* INV_FOOD   */ 2,
	/* INV_POTION */ 1,
	/* INV_DOCS   */ 6,
	/* INV_OTHER  */ 7,
};

static void ReadInvCatOrder(void)
{
	// read only ones
	static bool invCatOrderReaded = false;
	if (invCatOrderReaded) return;
	invCatOrderReaded = true;

	const zSTRING invCatNames[INV_MAX] =
	{"NONE","COMBAT","ARMOR","RUNE","MAGIC","FOOD","POTION","DOCS","OTHER"};

	// Get order string from INI file
	zSTRING invCatOrderStr = zoptions->ReadString(
		zOPT_SEC_GAME, "invCatOrder",
		"COMBAT,POTION,FOOD,ARMOR,MAGIC,RUNE,DOCS,OTHER,NONE");
	invCatOrderStr.TrimLeft();
	invCatOrderStr.TrimRight();
	if (invCatOrderStr.IsEmpty())
	{
		zERR_MESSAGE(5, 0, "N: ReadInvCatOrder: Empty inventory category order list (empty value)");
		return;
	}

	int i, j;
	int invCatOrder[INV_MAX];
	// Init list
	for (i=0; i<INV_MAX; i++)
		invCatOrder[i] = -1;

	// Read loop
	for (i=0; i<INV_MAX; i++)
	{
		// Pick word by index
		zSTRING invCatStr = invCatOrderStr.PickWord(i * 2 + 1, ",");
		invCatStr.TrimLeft();
		invCatStr.TrimRight();
		invCatStr = invCatStr.Upper();
		if (invCatStr.IsEmpty())
		{
			zERR_MESSAGE(5, 0, "N: ReadInvCatOrder: Invalid inventory category order list (empty word at pos " + zSTRING(i) + ")");
			return;
		}
		
		// Set index by word
		bool found = false;
		for (j=0; j<INV_MAX; j++)
		if (invCatStr.CompareTo(invCatNames[j]) == 0)
		{
			if (invCatOrder[j] != -1)
			{
				zERR_MESSAGE(5, 0, "N: ReadInvCatOrder: Invalid inventory category order list (doubled entry '" + invCatStr + "')");
				return;
			}
			invCatOrder[j] = i;
			found = true;
			break;
		}
		if (!found)
		{
			zERR_MESSAGE(5, 0, "N: ReadInvCatOrder: Invalid inventory category order list (unknown category name '" + invCatStr + "')");
			return;
		}
	}

	// Search for missing entries
	bool valid = true;
	for (i=0; i<INV_MAX; i++)
	if (invCatOrder[i] == -1)
	{
		zERR_MESSAGE(5, 0, "N: ReadInvCatOrder: Invalid inventory category order list (missing category '" + invCatNames[i] + "')");
		valid = false;
	}
	if (!valid) return;

	// Finally write the list
	for (i=0; i<INV_MAX; i++)
		InventorySort_CatOrder[i] = invCatOrder[i];
}

//////////////////////////////////////////////////////////////////////////////
//	map main flag to category
inline int Inventory_GetCategory(oCItem* item)
{
	if ( !item ) return (INV_NONE);
	
	switch ( item->GetMainFlag() )
	{
		case ITM_CAT_NF		: return (INV_COMBAT);
		case ITM_CAT_FF		: return (INV_COMBAT);
		case ITM_CAT_MUN	: return (INV_COMBAT);
		case ITM_CAT_ARMOR	: return (INV_ARMOR);
		case ITM_CAT_FOOD	: return (INV_FOOD);
		case ITM_CAT_DOCS	: return (INV_DOCS);
		case ITM_CAT_POTION	: return (INV_POTION);
//		case ITM_CAT_LIGHT	: return (INV_LIGHT);
		case ITM_CAT_RUNE	: return (INV_RUNE);
		case ITM_CAT_MAGIC	: return (INV_MAGIC);
		case ITM_CAT_NONE	: return (INV_OTHER);
	}
	return(INV_OTHER);
}

//////////////////////////////////////////////////////////////////////////////
//	sort all

static int InventorySort(oCItem *item1, oCItem *item2)
{
	// primary: category
	int t1 = InventorySort_CatOrder[Inventory_GetCategory(item1)];
	int t2 = InventorySort_CatOrder[Inventory_GetCategory(item2)];
	if ( t1 < t2 )
		return -1;
	if ( t1 > t2 )
		return 1;

	// secondary: depending on type
	switch ( Inventory_GetCategory(item1) )
	{
		case INV_COMBAT	: return InventorySortCombat	(item1, item2);
		case INV_ARMOR	: return InventorySortArmor		(item1, item2);
		case INV_FOOD	: return InventorySortFood		(item1, item2);
		case INV_MAGIC	: return InventorySortMagic		(item1, item2);
		case INV_OTHER	: return InventorySortOther		(item1, item2);
	}
	// default
	return InventorySortDefault(item1, item2);
}

//////////////////////////////////////////////////////////////////////////////


void oCItemContainer::Container_PrepareDraw ()
{
/*	zCList<oCItemContainer>* node = contList.GetNextInList();
	while (node) {
		node -> GetData() -> PrepareDraw();
		node = node -> GetNextInList();
	}*/
}

void oCItemContainer::Container_Draw ()
{
	zCList<oCItemContainer>* node = s_openContainers.GetNextInList(); // [Moos] Performance : früher stand hier contList. Da nur offene Container dargestellt werden, ist das OK.
	int count = 0;
	while (node) {
		node -> GetData() -> Draw();
		node = node -> GetNextInList();
		count++;
	}
}

oCItemContainer* oCItemContainer::GetNextContainerLeft(oCItemContainer* self)
{
	int x,y,x2,y2,minx;
	oCItemContainer *other, *found = NULL;

	if (!self) return NULL;
	self -> GetPosition (x,y);
	minx  = x;

	zCList<oCItemContainer>* node = s_openContainers.GetNextInList();  // [Moos] Performance : früher stand hier contList. Da nur offene Container untersucht werden, ist das OK.
	while (node) 
	{
		other = node->GetData();
		if ((other!=self) && !other->IsPassive() && other->IsOpen()) 
		{
			other->GetPosition(x2,y2);
			if (x2 < minx) 
			{
				found	= other;
				minx	= x2;
			}
		}
		node = node->GetNextInList();
	}
	return found;
}

oCItemContainer* oCItemContainer::GetNextContainerRight(oCItemContainer* self)
{
	int x,y,x2,y2,maxx;
	oCItemContainer *other, *found = NULL;

	if (!self) return NULL;
	self -> GetPosition (x,y);
	maxx  = x;

	zCList<oCItemContainer>* node = s_openContainers.GetNextInList(); // [Moos] Performance : früher stand hier contList. Da nur offene Container untersucht werden, ist das OK.
	while (node) {
		other = node->GetData();
		if ((other!=self) && !other->IsPassive() && other->IsOpen()) {
			other->GetPosition(x2,y2);
			if (x2 > maxx) {
				found	= other;
				maxx	= x2;
			}
		}
		node = node->GetNextInList();
	}
	return found;
}

// ************************************************************************************
// Container Base
// ************************************************************************************

/* ----------------------------------------------------------------------
	
	oCItemContainter :: oCItemContainer()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

oCItemContainer::oCItemContainer ()
{
	// vars
	contents		= NULL;					// List of all Items in Container
	npc				= NULL;					// Owner
	titleText		= "";					// inventory's name (display)
	invMode			= INV_MODE_DEFAULT;
	selectedItem	= 0;					// Current selected Item
	offset			= 0;					// Current offset in List
	
	// TODO
	marginTop		= 0;					// Space on top (screen)
	marginLeft		= 0;					// Space on left/right (screen)
	maxSlotsCol		= GetInvMaxColumns();	// INV_MAX_SLOTS_COL;	// Maximal Items to be drawn
	maxSlotsColScr	= 1;					// Maximal Items drawable on screen
	maxSlotsRow		= GetInvMaxRows();		// INV_MAX_SLOTS_ROW;	// Maximal Items to be drawn
	maxSlotsRowScr	= 1;					// Maximal Items drawable on screen
	maxSlots		= maxSlotsCol * maxSlotsRow;
	
	frame			= FALSE;				// Highlight Selected Item
	right			= FALSE;				// Left or Right ?
//	isOpen			= FALSE;				// Open or Closed ? ( only Visual ! )
	ownList			= TRUE;					// is it own list ?
	prepared		= FALSE;				// Item is prepared for drawing ?
	passive			= FALSE;				// passive = only used for display purposes

	viewTitle		= NULL;
	viewBack		= NULL;
	viewItem		= NULL;
	viewItemActive	= NULL;
	viewItemInfo	= NULL;
	viewItemInfoItem= NULL;
	textView		= NULL;
	rndWorld		= NULL;
	
	TransferCount = 1;
	
	m_bManipulateItemsDisabled		= FALSE;
	m_bCanTransferMoreThanOneItem	= TRUE;

	contents	= zNEW(zCListSort<oCItem>);
	// Sortierung setzen
	ReadInvCatOrder();
	contents->SetCompare(InventorySort);
	
	contList.Insert(this);

//	zERR_MESSAGE(5,0,"B: ItemContainer constructed");
};

oCItemContainer::~oCItemContainer ()
{		
	Close			();			// Zumachen
	DeleteContents	();			// Liste löschen (ownList)
	contList.Remove	(this);		// aus globaler Liste entfernen
	contents	= NULL;
	npc			= NULL;			

//	zERR_MESSAGE(5,0,"B: ItemContainer destructed");
};

/* ----------------------------------------------------------------------
	
	oCItemContainer :: LoadGrafix()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void oCItemContainer::LoadGrafix ()
{
	zoptions->ChangeDir	(DIR_TEX_DESKTOP);
	if (!gfx_loaded) 
	{
		// Load 
		gfx_cat			= zNEW(zCGfx)("invchest.tga");
		gfx_equip		= zNEW(zCGfx)("equip.tga");
		gfx_cursor		= zNEW(zCGfx)("cursor.tga");
		gfx_cursor_equip= zNEW(zCGfx)("cursor_equip.tga");

		// Load Arrows
		// 0 = left		1 = rechts		2 = hoch	3 = runter
		gfx_arrow[0]	= zNEW(zCGfx)("arroleft.tga");
		gfx_arrow[1]	= zNEW(zCGfx)("arrorite.tga");
		gfx_arrow[2]	= zNEW(zCGfx)("arroup.tga");
		gfx_arrow[3]	= zNEW(zCGfx)("arrodown.tga");
	
		gfx_loaded = TRUE;
	}
}

static void CalculateNormalized(zCView* view, int x, int y)
{	
	float xMult = (float)x / (float)INV_SCALE_X;
	float yMult = (float)y / (float)INV_SCALE_Y;

	// nur runterskalieren
	if (xMult>1) xMult=1;
	if (yMult>1) yMult=1;

	// Groesse fuer Iteminformationen
	inv_inf_sizex	= int(view->anx(INV_INF_SIZEX) * xMult);
	inv_inf_sizey	= int(view->any(INV_INF_SIZEY) * yMult);
	inv_inf_dx		= int(view->anx(INV_INF_DX) * xMult);

	// Größe des gerenderten Items
	inv_item_sizex	= int(view->anx(INV_ITEM_SIZEX) * xMult);
	inv_item_sizey	= int(view->any(INV_ITEM_SIZEY) * yMult);

	// Offset und Rand fuer die Anzeige eines Items-Slots
	inv_item_width	= int(view->anx(INV_ITEM_WIDTH) * xMult);
	inv_item_height = int(view->any(INV_ITEM_HEIGHT) * yMult);
};

static zBOOL s_bShowArrows = FALSE;

void oCItemContainer::Init(int x, int y, int mode)
{
	switch (mode)
	{
	case INV_MODE_CONTAINER:
	case INV_MODE_PLUNDER:
	case INV_MODE_STEAL:
	case INV_MODE_BUY:
	case INV_MODE_SELL:
		invMode = mode;
		break;
	default:
		invMode = INV_MODE_DEFAULT;
		break;
	}

	s_bShowArrows = zoptions->ReadBool(zOPT_SEC_GAME,"invShowArrows",TRUE);	

	// TODO
	marginTop		= 0;					// Space on top (screen)
	marginLeft		= 0;					// Space on left/right (screen)
	maxSlotsCol		= GetInvMaxColumns();	// Maximal Items to be drawn
	maxSlotsColScr	= 1;					// Maximal Items drawable on screen
	maxSlotsRow		= GetInvMaxRows();		// Maximal Items to be drawn
	maxSlotsRowScr	= 1;					// Maximal Items drawable on screen
	maxSlots		= maxSlotsCol * maxSlotsRow;
	
	// Sound on
    if (zsound)
	{
		zCSoundFX *snd = zsound->LoadSoundFXScript("INV_OPEN");
		if (snd)
		{
	//		snd->SetCanBeCachedOut(FALSE);
			zsound -> PlaySound(snd);
			zRELEASE(snd); // [Moos] Leakfix
		}
	}
}

void oCItemContainer::GetSize(int &x, int &y)
{
	x = maxSlotsCol * INV_ITEM_WIDTH;
	y = maxSlotsRow * INV_ITEM_HEIGHT;
}

void oCItemContainer::GetPosition(int &x,int &y)
{
	x = posx;
	y = posy;
}

zCListSort<oCItem>* oCItemContainer::JumpOffset (zBOOL& isAtTop, zBOOL& isAtBottom)
{
	isAtTop = TRUE;

	if (!contents)			return NULL;
	if  (selectedItem<0)	return contents->GetNextInList();
	
	// Calculate Offset
	if (selectedItem+1 > contents->GetNumInList()) 
	{
		selectedItem = contents->GetNumInList()-1;
		CheckSelectedItem();
	}
	
	if (selectedItem < offset) 
	{
		offset = offset - maxSlotsRow;
		if (offset<0) offset = 0;
	};
	
	// Jump Offset in List	
	zCListSort <oCItem>* node = contents->GetNextInList();		
	for (int i=0; i<offset; i++) 
	{
		if (node) node = node -> GetNextInList();
	}

	isAtTop	= (offset==0);
	return node;
}

void oCItemContainer::DrawCategory()
{
	if (IsPassive()) return;
	// TEMP
	if (titleText.IsEmpty()) return;

	// FIXME
	oCItemContainer* leftContainer = GetNextContainerLeft(this);
	if ( leftContainer )
	{
		switch ( leftContainer->GetMode() )
		{
			case INV_MODE_STEAL:
			case INV_MODE_PLUNDER:
				return;
		}
	}

	screen->InsertItem(viewTitle);
	{
		zSTRING text = titleText + "\n";
		
		int titlePosX = marginLeft - screen->anx(10);
		int titlePosY = titlePosX + inv_item_height / 2; // inv_item_height;
		int titleSizeX = zMax( inv_item_width * 2, screen->anx(TEXT_INV_CATX)*2 +  screen->zCView::FontSize(text) );
		int titleSizeY = inv_item_height / 2;
		if (right)
			titlePosX = 8192 - titlePosX - titleSizeX;

		// title background
		switch ( invMode )
		{
		case INV_MODE_CONTAINER:
			viewTitle->InsertBack		(TEX_INV_BACK_CONTAINER);
			viewTitle->SetAlphaBlendFunc(TEX_INV_BACK_CONTAINER_BLEND);
			break;
		case INV_MODE_PLUNDER:
			viewTitle->InsertBack		(TEX_INV_BACK_PLUNDER);
			viewTitle->SetAlphaBlendFunc(TEX_INV_BACK_PLUNDER_BLEND);
			break;
		case INV_MODE_STEAL:
			viewTitle->InsertBack		(TEX_INV_BACK_STEAL);
			viewTitle->SetAlphaBlendFunc(TEX_INV_BACK_STEAL_BLEND);
			break;
		case INV_MODE_BUY:
			viewTitle->InsertBack		(TEX_INV_BACK_BUY);
			viewTitle->SetAlphaBlendFunc(TEX_INV_BACK_BUY_BLEND);
			break;
		case INV_MODE_SELL:
			viewTitle->InsertBack		(TEX_INV_BACK_SELL);
			viewTitle->SetAlphaBlendFunc(TEX_INV_BACK_SELL_BLEND);
			break;
		default:
			viewTitle->InsertBack		(TEX_INV_BACK);
			viewTitle->SetAlphaBlendFunc(TEX_INV_BACK_BLEND);
			break;
		}
//		if ( this->GetEnableHandleEvent() )
		{
			viewTitle->SetFontColor		( INV_COLOR_BRIGHT );
			viewTitle->SetTransparency	( INV_ALPHA );
		}
//		else
//		{
//			viewTitle->SetFontColor		( INV_COLOR_LIGHT );
//			viewTitle->SetTransparency	( INV_ALPHA_NOFOCUS );
//		}
		viewTitle->SetPos			(titlePosX, titlePosY);
		viewTitle->SetSize			(titleSizeX, titleSizeY);
		viewTitle->ClrPrintwin		();
		viewTitle->Blit				();
		viewTitle->InsertBack		(TEX_INV_TITLE);
		viewTitle->SetAlphaBlendFunc(TEX_INV_TITLE_BLEND);
		viewTitle->PrintCXY			(text);
		viewTitle->Blit				();
	}
	screen->RemoveItem(viewTitle);
}

/* ----------------------------------------------------------------------
	
	oCItemContainer :: DrawItemInfo()

	08.11.2000	[Roman Keskenti]	
					Inital implementation

				[Speckels]
					Feste Groesse des Fensters, unabhaengig von der Aufloesung					

   ---------------------------------------------------------------------- */

void oCItemContainer::DrawItemInfo ( oCItem* pItem, zCWorld* pWorld )
{
	// [BENDLIN]
	if (!GetEnableHandleEvent()) return;

	screen->InsertItem(viewItemInfo);
	// TEMP
	switch ( invMode )
	{
		case INV_MODE_CONTAINER:
			viewItemInfo->InsertBack		(TEX_INV_BACK_CONTAINER);
			viewItemInfo->SetAlphaBlendFunc	(TEX_INV_BACK_CONTAINER_BLEND);
			break;
		case INV_MODE_PLUNDER:
			viewItemInfo->InsertBack		(TEX_INV_BACK_PLUNDER);
			viewItemInfo->SetAlphaBlendFunc	(TEX_INV_BACK_PLUNDER_BLEND);
			break;
		case INV_MODE_STEAL:
			viewItemInfo->InsertBack		(TEX_INV_BACK_STEAL);
			viewItemInfo->SetAlphaBlendFunc	(TEX_INV_BACK_STEAL_BLEND);
			break;
		case INV_MODE_BUY:
			viewItemInfo->InsertBack		(TEX_INV_BACK_BUY);
			viewItemInfo->SetAlphaBlendFunc	(TEX_INV_BACK_BUY_BLEND);
			break;
		case INV_MODE_SELL:
			viewItemInfo->InsertBack		(TEX_INV_BACK_SELL);
			viewItemInfo->SetAlphaBlendFunc	(TEX_INV_BACK_SELL_BLEND);
			break;
		default:
			viewItemInfo->InsertBack		(TEX_INV_BACK);
			viewItemInfo->SetAlphaBlendFunc	(TEX_INV_BACK_BLEND);
			break;
	}

	int x, y;
	this->GetSize( x, y );
	x = screen->anx( x );
	y = screen->any( y );

	zCFont* pFont				= this->viewItemInfo->GetFont();	
	if ( ! pFont ) return;

	int		nFontHeightScreen	= screen->any( pFont->GetFontY() );	
	int		nFontHeight			= viewItemInfo->any( pFont->GetFontY() );
	int		nFontHeightHalf		= nFontHeight >> 1;
	int		nMarginLeft			= 250;
	int		nMarginRight		= 250;
	int		nScreenHeight		= ( 6 + 2 + 1 ) * nFontHeightScreen;
	int vx	= inv_item_sizex * 10 + screen->anx(20);
	int vy	= nScreenHeight;
	int posx= int((8192-vx)/2);
	int posy= 8192-vy-screen->any(30);
	viewItemInfo->SetSize(vx,vy);
	viewItemInfo->SetPos(posx,posy);	
	// ---

	viewItemInfo->ClrPrintwin	();

	// [BENDLIN]
	viewItemInfo->SetFillZ		(TRUE);
	
	//
	//	RENDER ITEM
	//
	if ( pWorld )
	{
		viewItemInfo->InsertItem(viewItemInfoItem);

		int nSizeY = 8192;
		int nSizeX = viewItemInfo->anx(viewItemInfo->nay(nSizeY)); // breite = hoehe		
		int nPosX  = 6666-(nSizeX/2);	// nicht zentriert
		int nPosY  = 0;
		viewItemInfoItem->SetSize	( nSizeX, nSizeY );
		viewItemInfoItem->SetPos	( nPosX, nPosY );
		
		oCItem::SetLightingSwell (FALSE);
		pItem->RenderItem( pWorld, viewItemInfoItem, 0 );
		oCItem::SetLightingSwell (TRUE);	
		// ---
	}

	//
	//	PRINT ITEM'S INFOS
	//
	if ( pItem )
	{
		int		 nCount;
		zSTRING  strText;

		// [EDENFELD]: tmp: falls die Description des Items leer ist, wird der Item _Name_
		// genommen. Dies evtl. nur Übergangsweise, bis alle Descriptions gefüllt sind		
		strText = pItem->GetDescription();
		if (strText.IsEmpty()) strText = pItem->GetName();

		int posY;
		int posX;

		//
		//	DESCRIPTION
		//
				
		posY = nFontHeight - nFontHeightHalf;
		zCOLOR col = INV_COLOR_BRIGHT;
		this->viewItemInfo->PrintTimedCX( posY, strText, -2.0f, &col );
		
		//
		//	INFORMATIONS (je nach Item)
		//		
		for ( int nLine = 0; nLine < ITM_TEXT_MAX; nLine++ )
		{
			strText = pItem->GetText	( nLine );
			nCount	= pItem->GetCount	( nLine );	

			posY = (nLine+3) * nFontHeight - nFontHeightHalf;

			posX = nMarginLeft;
			col = INV_COLOR_DEFAULT;
			this->viewItemInfo->PrintTimed( posX, posY, strText, -2.0f, &col );
			if (nCount==0) continue;

			posX = 8192 - nMarginRight - viewItemInfo->FontSize(zSTRING(nCount));
			if (nLine < ITM_TEXT_MAX-1) 
				this->viewItemInfo->PrintTimed( posX, posY, zSTRING( nCount ), -2.0f, &col );
			else
			{
				int _value = pItem->GetValue();
				if (this->GetMode() == INV_MODE_SELL)
				{
					_value = zFloat2Int(zREAL(_value) * oCItemContainer::GetValueMultiplier());
					if ((pItem->GetValue() > 0) && (_value <= 0))
						_value = 1;
				}
				this->viewItemInfo->PrintTimed( posX, posY, zSTRING(_value), -2.0f, &col);
			}
		}
	}

	

	//
	//	BLIT ME
	//
	viewItemInfo->Blit();
	
	if ( pWorld )
	{
		viewItemInfo->RemoveItem(viewItemInfoItem);
	};

	screen->RemoveItem(viewItemInfo);								

	//
	// OLD INTERFACE
	//
	//if (right) x = posx - inv_inf_sizex; // - inv_inf_dx;
	//else x = posx + inv_item_width + inv_inf_dx;
}

/* ----------------------------------------------------------------------
	
	oCItemContainer :: Draw()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void oCItemContainer::Draw()
{
	if (!IsOpen()) return;
	
	zCPar_Symbol *sym = NULL;
	zSTRING fontName(FNT_INV_DEFAULT);
	sym = parser.GetSymbol(TEXT_FONT_INVENTORY);
	if (sym) sym->GetValue(fontName);

	CheckSelectedItem();
	
	// FIXME
	oCItemContainer* leftContainer = GetNextContainerLeft(this);
	if ( leftContainer )
	switch ( leftContainer->GetMode() )
	{
		case INV_MODE_STEAL:
		case INV_MODE_PLUNDER:
			return;
	}

	int nHeightItemInfoScreen = 0;
	zCFont* pFont = this->viewItemInfo->GetFont();
	if ( pFont )
		nHeightItemInfoScreen = (6 + 2 + 1) * screen->any(pFont->GetFontY());
	// Anzahl darstellbarer Items	

	// TODO
	maxSlotsColScr = (8192 - inv_item_width) / inv_item_width;
	marginLeft = (8192 - maxSlotsColScr * inv_item_width) / 2;
	marginTop = marginLeft;
	int _height = (8192 - marginLeft - inv_item_height - nHeightItemInfoScreen - screen->any(30));
	
	if (IsSplitScreen())
		maxSlotsColScr /= 2;

	if (maxSlotsColScr < 2)
		maxSlotsColScr = 2;

	maxSlotsCol = GetInvMaxColumns();
	if (maxSlotsCol > maxSlotsColScr)
		maxSlotsCol = maxSlotsColScr;

	maxSlotsRowScr = _height / inv_item_height;
	if (maxSlotsRowScr < 2)
		maxSlotsRowScr = 2;
	maxSlotsRow = GetInvMaxRows();
	if (maxSlotsRow > maxSlotsRowScr)
		maxSlotsRow = maxSlotsRowScr;

	maxSlots	= maxSlotsCol * maxSlotsRow;

	//
	// Category darstellen
	//
	this->DrawCategory();

	// TODO
	if ((!IsSplitScreen() && (maxSlotsCol > (maxSlotsColScr / 2))) && !GetEnableHandleEvent())
	{
		int x, y, sx, sy;
		screen->GetViewport( x, y, sx, sy);
		::zrenderer->SetViewport( x, y, sx, sy );
		return;
	}

	// TODO: Arrows
/*	if (s_bShowArrows)
	{
		if (i==0 && !isAtTop)
		{						
			screen->InsertItem(viewArrowAtTop);						
			viewArrowAtTop->SetPos(posx+screen->anx(16),y1);
			if (right)	viewArrowAtTop->SetPos(posx -  screen->anx(16), y1);
			else		viewArrowAtTop->SetPos(posx + inv_item_width, y1);
			viewArrowAtTop->Blit();
			screen->RemoveItem(viewArrowAtTop);
		}
		else if ((i+1==drawItemMaxY) && node && node->GetNextInList())
		{
			screen->InsertItem(viewArrowAtBottom);
			if (right)	viewArrowAtBottom->SetPos(posx -  screen->anx(16), y1+inv_item_height-screen->any(16));
			else		viewArrowAtBottom->SetPos(posx + inv_item_width, y1+inv_item_height-screen->any(16));
			viewArrowAtBottom->Blit();
			screen->RemoveItem(viewArrowAtBottom);
		}; 
	} */
	
	screen->InsertItem(viewBack);		
	switch ( invMode )
	{
	case INV_MODE_CONTAINER:
		viewBack->InsertBack		(TEX_INV_BACK_CONTAINER);
		viewBack->SetAlphaBlendFunc	(TEX_INV_BACK_CONTAINER_BLEND);
		break;
	case INV_MODE_PLUNDER:
		viewBack->InsertBack		(TEX_INV_BACK_PLUNDER);
		viewBack->SetAlphaBlendFunc	(TEX_INV_BACK_PLUNDER_BLEND);
		break;
	case INV_MODE_STEAL:
		viewBack->InsertBack		(TEX_INV_BACK_STEAL);
		viewBack->SetAlphaBlendFunc	(TEX_INV_BACK_STEAL_BLEND);
		break;
	case INV_MODE_BUY:
		viewBack->InsertBack		(TEX_INV_BACK_BUY);
		viewBack->SetAlphaBlendFunc	(TEX_INV_BACK_BUY_BLEND);
		break;
	case INV_MODE_SELL:
		viewBack->InsertBack		(TEX_INV_BACK_SELL);
		viewBack->SetAlphaBlendFunc	(TEX_INV_BACK_SELL_BLEND);
		break;
	default:
		viewBack->InsertBack		(TEX_INV_BACK);
		viewBack->SetAlphaBlendFunc	(TEX_INV_BACK_BLEND);
		break;
	}
	// viewBack->SetTransparency(INV_ALPHA);
	if (this->GetEnableHandleEvent())
		viewBack->SetTransparency(INV_ALPHA);
	else
		viewBack->SetTransparency(INV_ALPHA_NOFOCUS);

	if (right)
		viewBack->SetPos(8192 - marginLeft - maxSlotsCol * inv_item_width + screen->anx(10), (_height - maxSlotsRowScr * inv_item_height) / 2 + marginLeft + inv_item_height);
	else
		viewBack->SetPos(marginLeft - screen->anx(10), (_height - maxSlotsRowScr * inv_item_height) / 2 + marginLeft + inv_item_height);
	viewBack->SetSize			(inv_item_width * maxSlotsCol, inv_item_height * maxSlotsRow);

	// [BENDLIN]
	viewBack->SetFillZ(TRUE);

	viewBack->Blit();
	
	// Item ermitteln
	zBOOL isAtTop, isAtBottom;
	zCListSort<oCItem>*	node= JumpOffset(isAtTop, isAtBottom);

	oCItem*		item		= (node?node->GetData():0);				
	oCItem*		selItem		= GetSelectedItem();
	zCView*		itemView	= 0;		

	zBOOL		hasInvFocus	= frame;	
	zBOOL		isInvActive	= IsActive();
	
	int x1;	
	int y1;
	int x2;
	int y2;
	int i;
	for (i=0; i<maxSlots; i++) 
	{			
		x1 = (i % maxSlotsCol) * (8192 / maxSlotsCol);
		y1 = (i / maxSlotsCol) * (8192 / maxSlotsRow);
		x2 = (i % maxSlotsCol + 1) * (8192 / maxSlotsCol) - x1;
		y2 = (i / maxSlotsCol + 1) * (8192 / maxSlotsRow) - y1;
		
		if (node && node->GetData()) 
		{			 
			item = node->GetData();

			//
			// Itemzustand ermitteln
			//

			zBOOL isItemSelected	= (selItem==item);
			zBOOL isItemActive		= item->HasFlag(ITM_FLAG_ACTIVE);			

			if	( isItemSelected && isInvActive )	itemView = isItemActive ? this->viewItemActiveHighlighted		: viewItemHightlighted	;
			else									itemView = isItemActive ? this->viewItemActive					: viewItem				;
			if (hasInvFocus && isItemSelected && isInvActive) 
				this->DrawItemInfo( item, rndWorld );	
			
			//
			// Item-Viewport
			//						
			viewBack->InsertItem(itemView);

				if (this->GetEnableHandleEvent())
					itemView->SetTransparency(INV_ALPHA);
				else
					itemView->SetTransparency(INV_ALPHA_NOFOCUS);
				// itemView->SetTransparency(INV_ALPHA);
				itemView->SetPos			(x1, y1);
				itemView->SetSize			(x2, y2);
				itemView->Blit				();									

				oCItem::SetLightingSwell( isItemSelected );
				item->RenderItem(rndWorld,itemView,(float)(isItemSelected && isInvActive));
				oCItem::SetLightingSwell(TRUE);			

			viewBack->RemoveItem(itemView);

			// 
			// Texteinblendungen
			// 
			
			int posx,posy;
			itemView	->GetPos		(posx,posy);

			viewBack->InsertItem(textView);

				textView	->SetPos		(posx,posy);
				textView	->SetSize		(x2, y2);
				textView	->ClrPrintwin	();
  
				//
				// Multislot-Amount anzeigen
				//
				if (item->GetAmount()>1) 
				{
					zSTRING s	= zSTRING(item->GetAmount());
					int px		= 8192 - textView->FontSize(s);
					int py		= 8192 - textView->FontY();
					zCOLOR col	= INV_COLOR_BRIGHT; 
					if (!this->GetEnableHandleEvent())
						col = INV_COLOR_LIGHT;

					textView->SetFont		(fontName);
					textView->PrintTimed	(px-1000,py-800,s,-2,&col);
				};

				//
				// Hotkey anzeigen
				//
				zCOLOR col	= INV_COLOR_HOTKEY; 

				if(item->mainflag == ITM_CAT_RUNE)
				{
					if(oCNpc::player->HasMagic())
					{
						int keyNo = oCNpc::player->GetSpellBook()->GetKeyByItem(item);
						if( keyNo < 10 )
						{
							zSTRING s	= zSTRING(keyNo+3);
							int px		= textView->FontSize(s);
							int py		= textView->FontY();
							textView->SetFont	 (fontName);
							textView->PrintTimed (px+100,4100-(py/2),s,-2,&col);
						}
					}
				}

				if((item->mainflag==ITM_CAT_NF)&&(item->HasFlag(ITM_FLAG_ACTIVE)))
				{
					zSTRING s(1);
					int px		=  textView->FontSize(s);
					int py		=  textView->FontY();
					textView->SetFont(fontName);
					textView->PrintTimed (px+100,4100-(py/2),s,-2,&col);
				}

				if((item->mainflag==ITM_CAT_FF)&&(item->HasFlag(ITM_FLAG_ACTIVE)))
				{
					zSTRING s(2);
					int px		=  textView->FontSize(s);
					int py		=  textView->FontY();
					textView->SetFont(fontName);
					textView->PrintTimed (px+100,4100-(py/2),s,-2,&col);
				}

				textView->Blit();

			viewBack->RemoveItem(textView);

			//
			// Next Item
			//
			node = node->GetNextInList();
		}			
		else
		{
			//
			//	Empty slot
			//

			zCView* slotViewItem;
			if (this->GetEnableHandleEvent() && (i == 0) && (selectedItem <= 0) && (offset <= 0))
				 // empty inventory focused - first is empty but selected
				slotViewItem = this->viewItemHightlighted;
			else
				slotViewItem = this->viewItem;

			viewBack->InsertItem(slotViewItem);
				slotViewItem->SetTransparency	(INV_ALPHA);
				slotViewItem->SetPos			(x1, y1);
				slotViewItem->SetSize			(x2, y2);
				slotViewItem->Blit				();
			viewBack->RemoveItem(slotViewItem);
		}
	}

	screen->RemoveItem(viewBack);

	//
	//	VIEWPORT WIEDER AUF SCREEN SETZTEN
	//
	int x, y, sx, sy;
	screen->GetViewport( x, y, sx, sy);
	::zrenderer->SetViewport( x, y, sx, sy );
};

void oCItemContainer::SetContents (zCListSort <oCItem> *list)
{
	// Die intern erzeugte Liste wird hier gelöscht, und es wird mit der von
	// aussen herangetragenen weitergearbeitet ist, die aber nicht von Container
	// mehr deleted wird
	
	DeleteContents();
	// Und Liste übernehmen
	ownList			= FALSE;
	contents		= list;
	if (!contents) return;
	// Sortierung setzen
	contents->SetCompare(InventorySort);
	zCListSort <oCItem>* node = contents->GetNextInList();
	while (node) {
		node -> GetData() -> RotateForInventory();
		node  = node -> GetNextInList();
	}
};

zCListSort <oCItem>* oCItemContainer::GetContents()
{
	return contents;
};

void oCItemContainer::Open(int x, int y, int mode)
{	
	zERR_MESSAGE(4,0,"B: Open Container");	
	
	// Passiv oeffnen
	OpenPassive(x, y, mode);
	
	// Aktivieren
	Activate();
	passive = FALSE;	

//	isOpen = TRUE;
    if (!IsOpen())
        s_openContainers.Insert(this);
}

/* ----------------------------------------------------------------------
	
	oCItemContainer :: OpenPassive()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void oCItemContainer::OpenPassive(int x, int y, int mode)
{
	CalculateNormalized(screen , zrenderer->vid_xdim,zrenderer->vid_ydim);
		
	zRELEASE(rndWorld);
	rndWorld = zNEW(zCWorld);	
	rndWorld->SetIsInventoryWorld(TRUE);

	if (x + inv_item_width > VIEW_VXMAX) 
		x = VIEW_VXMAX - inv_item_width;
	
	posx = x; posy = y;

	right= (posx>4095);				

	Init	(x, y, mode);
	
	// Views
	
	// Arrows
	viewArrowAtTop = zNEW(zCView)( 0,0,screen->anx(16),screen->any(16));
	screen->InsertItem									(viewArrowAtTop);		
	viewArrowAtTop->InsertBack							(TEX_INV_ARROW_TOP);
	viewArrowAtTop->SetAlphaBlendFunc					(zRND_ALPHA_FUNC_BLEND);
	viewArrowAtTop->SetTransparency						(96);
	screen->RemoveItem									(viewArrowAtTop);
		
	viewArrowAtBottom = zNEW(zCView)( 0,0,screen->anx(16),screen->any(16));
	screen->InsertItem									(viewArrowAtBottom);		
	viewArrowAtBottom->InsertBack						(TEX_INV_ARROW_BOTTOM);
	viewArrowAtBottom->SetAlphaBlendFunc				(zRND_ALPHA_FUNC_BLEND);		
	viewArrowAtBottom->SetTransparency					(96);
	screen->RemoveItem									(viewArrowAtBottom);

	// Title
	viewTitle											= zNEW(zCView)( 0,0,10,10);
	screen->InsertItem									(viewTitle);		
	viewTitle->InsertBack								(TEX_INV_TITLE);
	viewTitle->SetAlphaBlendFunc						(TEX_INV_TITLE_BLEND);
	screen->RemoveItem									(viewTitle);
														
	// Background
	viewBack											= zNEW(zCView)( 0,0,10,10);
	screen->InsertItem									(viewBack);		
	viewBack->InsertBack								(TEX_INV_BACK);
	viewBack->SetAlphaBlendFunc							(TEX_INV_BACK_BLEND);
	screen->RemoveItem									(viewBack);
														
	// Item												
	viewItem											=  zNEW(zCView)	( 0,0,inv_item_sizex, inv_item_sizey );
	screen->InsertItem									(viewItem);
	viewItem->InsertBack								(TEX_INV_ITEM);
	viewItem->SetAlphaBlendFunc							(TEX_INV_ITEM_BLEND);
	viewItem->SetTransparency							(INV_ALPHA);
	screen->RemoveItem									(viewItem);	
														
	// activated Item									
	viewItemActive										=  zNEW(zCView)( 0,0,inv_item_sizex, inv_item_sizey );
	screen->InsertItem									(viewItemActive);
	viewItemActive->SetTransparency						(INV_ALPHA);
	viewItemActive->InsertBack							(TEX_INV_ITEM_ACTIVATED);
	viewItemActive->SetAlphaBlendFunc					(TEX_INV_ITEM_ACTIVATED_BLEND);
	screen->RemoveItem									(viewItemActive);
														
	// highlighted Item									
	viewItemHightlighted								=  zNEW(zCView)( 0,0,inv_item_sizex, inv_item_sizey );
	screen->InsertItem									(viewItemHightlighted);
	viewItemHightlighted->SetTransparency				(INV_ALPHA);
	viewItemHightlighted->InsertBack					(TEX_INV_ITEM_HIGHLIGHTED);
	viewItemHightlighted->SetAlphaBlendFunc				(TEX_INV_ITEM_HIGHLIGHTED_BLEND);
	screen->RemoveItem									(viewItemHightlighted);
														
	// activated highlighted Item						
	viewItemActiveHighlighted							=  zNEW(zCView)( 0,0,inv_item_sizex, inv_item_sizey );
	screen->InsertItem									(viewItemActiveHighlighted);
	viewItemActiveHighlighted->SetTransparency			(INV_ALPHA);
	viewItemActiveHighlighted->InsertBack				(TEX_INV_ITEM_ACTIVATED_HIGHLIGHTED);
	viewItemActiveHighlighted->SetAlphaBlendFunc		(TEX_INV_ITEM_ACTIVATED_HIGHLIGHTED_BLEND);
	screen->RemoveItem									(viewItemActiveHighlighted);
														
	// Text Info
	textView = zNEW(zCView)								( 0,0,inv_item_sizex, inv_item_sizey );
	screen	-> InsertItem								(textView);
	textView-> SetTransparency							(INV_ALPHA);
	textView-> SetAlphaBlendFunc						(TEX_INV_ITEM_ACTIVATED_BLEND);
	screen	-> RemoveItem								(textView);
														
	// ItemInfo											
	viewItemInfo  =  zNEW(zCView)						( 0,0,inv_inf_sizex, inv_inf_sizey );
	screen->InsertItem									(viewItemInfo);
	viewItemInfo->SetTransparency						(INV_ALPHA);
	viewItemInfo->InsertBack							(TEX_INV_ITEMINFO);		
	viewItemInfo->SetAlphaBlendFunc						(TEX_INV_ITEMINFO_BLEND);
	screen->RemoveItem									(viewItemInfo);

	//	ItemInfoItem
	viewItemInfoItem  =  zNEW(zCView)					( 0,0,inv_inf_sizex, inv_inf_sizey );
	viewItemInfo->InsertItem							(viewItemInfoItem);
	viewItemInfoItem->SetTransparency					(INV_ALPHA);
	viewItemInfoItem->SetAlphaBlendFunc					(TEX_INV_ITEMINFO_BLEND);
	viewItemInfo->RemoveItem							(viewItemInfoItem);

//	isOpen	= TRUE;
    if (!IsOpen())
        s_openContainers.Insert(this);

	if (this->m_bManipulateItemsDisabled)
		this->CheckSelectedItem();

	passive = TRUE;		
}

zBOOL oCItemContainer::IsPassive()
{
	return passive;
}

void oCItemContainer::Close()
{
	if (IsOpen()) 
	{
		zERR_MESSAGE(4,0,"B: Close Container");
		delete viewTitle;					viewTitle					= NULL;	
		delete viewBack;					viewBack					= NULL;	
		delete viewItem;					viewItem					= NULL;	
		delete viewItemActive;				viewItemActive				= NULL;	
    	delete viewItemHightlighted;		viewItemHightlighted		= NULL;
    	delete viewItemActiveHighlighted;	viewItemActiveHighlighted	= NULL;   
		delete viewItemInfo;				viewItemInfo				= NULL;
		delete viewItemInfoItem;			viewItemInfoItem			= NULL;
		delete textView;					textView					= NULL;

		zRELEASE(rndWorld);

		// Sound on
        if (zsndMan){ // [Moos] Sicherheitstest; manchmal wird Close() aufgerufen, obwohl schon die halbe Engine abgebaut ist.
            zCSoundFX *snd=zsound->LoadSoundFXScript("INV_CLOSE");
		    zsound->PlaySound(snd);
//			snd->SetCanBeCachedOut(FALSE);
            zRELEASE(snd); // [Moos] Leakfix
        }
	}
	prepared	= FALSE;
//	isOpen		= FALSE;
    s_openContainers.Remove(this);
	Deactivate();
	// FIXME Close
	invMode = INV_MODE_DEFAULT;
}


zBOOL oCItemContainer::IsOpen(){
    return s_openContainers.IsInList(this);
}

void oCItemContainer::Activate()
{
	// Durchsuche alle anderen Container und lösche "frame" dort
	zCList<oCItemContainer>* node = contList.GetNextInList();
	while (node) {
		if (node->GetData()!=this) node->GetData()->Deactivate();
		node = node -> GetNextInList();
	}	
	// Alle Eingaben zuerst hierher
	SetEnableHandleEvent(TRUE);
	SetHandleEventTop	();
	// Rahmen an
	frame = TRUE;
	if (oCNpc::player) oCNpc::player -> SetMovLock(TRUE);
	// entsprechende Kategory anschmeissen
	// SetCategoryOnRightContainer();

	CheckSelectedItem();
}

/* void oCItemContainer::SetCategoryOnRightContainer()
{
}; */

void oCItemContainer::Deactivate()
{
	SetEnableHandleEvent(FALSE);
	// Rahmen an
	frame = FALSE;
	if (oCNpc::player && !passive) oCNpc::player -> SetMovLock(FALSE);
}

oCItem* oCItemContainer::GetSelectedItem()
{	
	if (!contents)		return NULL;	
	if (selectedItem<0)	return NULL;
	return contents->Get(selectedItem);
}

int oCItemContainer::GetSelectedItemCount()
{	
	if (!contents)						return 0;
	if (selectedItem<0)					return 0;
	if (!contents->Get(selectedItem))	return 0;
	return contents->Get(selectedItem)->GetAmount();
};

oCItem* oCItemContainer::Insert( oCItem* item )
{
	if (!item)		return item;
	if (!contents)	return item;

	if (item->MultiSlot())
	{
		zCListSort <oCItem> *ele = contents->GetNextInList();
		while (ele)
		{
			oCItem* i = ele->GetData();
			//
			// [BENDLIN] Addon - SplitSlot
			//
			// Es muessen beide Multi-Items sein!
			//
			if (i->MultiSlot())
			if (i->GetInstance() == item->GetInstance())
			{
				i->SetAmount(i->GetAmount() + item->GetAmount());
				zERR_ASSERT(item->GetRefCtr()>=2);
				ogame->GetGameWorld()->RemoveVob(item);
				return i;
			}
			ele = ele->GetNextInList();
		}
	}

	//
	//	EITHER MULTI ITEM AND NOT FOUND IN LIST OR NO MULTI ITEM AT ALL
	//
	contents->InsertSort(item);
	CheckSelectedItem();

    // [Moos] 30.1.2001 neue Logik: Items in Containern kriegen ein Addref und sind nicht in der Welt.
    zADDREF_ACCT(item);
	ogame->GetGameWorld()->RemoveVob(item);

	return item;
}

void oCItemContainer::Remove( oCItem* item )
{
	if (!contents) return;
	contents->Remove(item);	
	CheckSelectedItem();

    // [Moos] neue Logik: Items in Containern kriegen ein Addref und sind nicht in der Welt. Das wird hier rückgängig gemacht.
    ogame->GetGameWorld()->InsertVobInWorld(item);	
    zRELEASE_ACCT_NONULL(item);	
}

oCItem* oCItemContainer::RemoveByPtr (oCItem* item, int anz)
{
	return Remove(item,anz);
};

oCItem* oCItemContainer::Remove( oCItem* item, int anz )
{
	if ( ! item ) return item;

	oCItem* pItem = NULL;

	zCListSort <oCItem> *pElement = contents->GetNextInList();
	while( pElement )
	{
		pItem = pElement->GetData();

		if ( pItem == item )
		{
			// [BENDLIN] remove if requested amount is equal to OR GREATER than the current amount
			if		( pItem->GetAmount() <= anz ) 
			{
				// [BENDLIN] FIXME: generate requested amount?
				//if ( pItem->GetAmount() < anz )
				//	pItem->SetAmount( anz );

				this->Remove( item );

				return pItem;
			}
			else if ( pItem->GetAmount() > anz )
			{
				pItem->ChangeAmount( -anz );

				pItem = (oCItem*) ogame->GetGameWorld()->CreateVob( zVOB_TYPE_ITEM, pItem->GetInstance() );
				pItem->SetAmount( anz );
                ogame->GetGameWorld()->InsertVobInWorld(pItem); // [Moos] sicher ist sicher...
				zRELEASE_ACCT_NONULL(pItem);

				return pItem;
			}
			else
				return NULL;
		}
		pElement = pElement->GetNextInList();
	}

	return NULL;
}

/* ----------------------------------------------------------------------
	
    oCItemContainer::DeleteContents()	

	31.08.2000	[Moos]	
                Leakfix

   ---------------------------------------------------------------------- */


void oCItemContainer::DeleteContents( )
{
	// Nur eigene Listen dürfen gelöscht werden
	if (ownList && contents) 
	{
		contents -> DeleteListDatas();
		delete contents; // [Moos] Das muss immer gemacht werden.
		contents	= NULL;
	}
}

void oCItemContainer::CheckSelectedItem()
{
	if (!GetSelectedItem() || (m_bManipulateItemsDisabled))
	{
		if ((!contents) || (contents->GetNumInList() <= 0) )
		{
			selectedItem = -1;
			offset		 = 0;
			// NextItem();
		}
		if (contents && (contents->GetNumInList() > 0) && (selectedItem < 0))
		{
			selectedItem = 0;
			offset		 = 0;
			// NextItem();
		}
		
		int i;
		for (i=0; i<10; i++)
			if (GetSelectedItem() && GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
				NextItem();
			else
				break;
		for (i=0; i<10; i++)
			if (GetSelectedItem() && GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
				PrevItem();
			else 
				break;
	};
};

void oCItemContainer::NextItem( )
{
	if (!contents) return;

	int oldSelection		= selectedItem;
	int oldOffset			= offset;
	
	if (GetSelectedItem()) GetSelectedItem()->RotateForInventory();

	zBOOL finished=FALSE;		

	// if (selectedItem<0) selectedItem=0;
	while (!finished)
	{
		if (selectedItem < contents->GetNumInList()-1) 
		{			
			if (IsSplitScreen() && ((selectedItem + 1) % maxSlotsCol == 0))
				finished = ActivateNextContainer(1);

			if (!finished)
			{
				selectedItem++;		
				if (selectedItem > offset + maxSlots - 1)
					offset += maxSlotsCol;

				if (!m_bManipulateItemsDisabled || !GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
				{										
					// SetCategoryOnRightContainer();
					finished=TRUE;
				}
			}
		}
		else
		{
			selectedItem= oldSelection;
			offset		= oldOffset;
			finished=TRUE;
		};
	}
	
	// Right Container
	if (IsSplitScreen() && (selectedItem == oldSelection) && (offset == oldOffset))
		ActivateNextContainer(1);

	if (selectedItem<0) return;

	if (m_bManipulateItemsDisabled && GetSelectedItem() && GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
	{
		selectedItem=-1;
		offset		= oldOffset;
	};
}

void oCItemContainer::NextItemLine( )
{
	if (!contents) return;

	int oldSelection		= selectedItem;
	int oldOffset			= offset;
	
	if (GetSelectedItem()) GetSelectedItem()->RotateForInventory();

	zBOOL finished=FALSE;		

	// if (selectedItem<0) selectedItem=0;
	while (!finished)
	{
		if (selectedItem < contents->GetNumInList()-1) 
		{			
			if (selectedItem < contents->GetNumInList()-maxSlotsCol) 
			{			
				selectedItem += maxSlotsCol;
				if (selectedItem >= contents->GetNumInList())
					selectedItem = contents->GetNumInList()-1;
				if (selectedItem > offset + maxSlots - 1)
					offset += maxSlotsCol;
			}
			else
			{
				selectedItem++;		
				if (selectedItem > offset + maxSlots - 1)
					offset += maxSlotsCol;
			}

			if (!m_bManipulateItemsDisabled || !GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
			{										
				// SetCategoryOnRightContainer();
				finished=TRUE;
			}
		}
		else
		{
			selectedItem= oldSelection;
			offset		= oldOffset;
			finished=TRUE;
		};
	}
	
	if (selectedItem<0) return;

	if (m_bManipulateItemsDisabled && GetSelectedItem() && GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
	{
		selectedItem=-1;
		offset		= oldOffset;
	};
}

void oCItemContainer::PrevItem()
{	
	if (!contents)		return;

	int oldSelection		= selectedItem;
	int oldOffset			= offset;
	
	if (GetSelectedItem()) GetSelectedItem()->RotateForInventory();

	zBOOL finished=FALSE;			

	while (!finished)
	{
		if (selectedItem > 0) 
		{			
			if (IsSplitScreen() && (selectedItem % maxSlotsCol == 0))
				finished = ActivateNextContainer(-1);

			if (!finished)
			{
				selectedItem--;		
				if (selectedItem < offset)
					offset -= maxSlotsCol;
				if (offset < 0)
					offset = 0;

				if (!m_bManipulateItemsDisabled || !GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
				{										
					// SetCategoryOnRightContainer();
					finished=TRUE;
				}
			}
		}
		else
		{
			selectedItem= oldSelection;
			offset		= oldOffset;
			finished=TRUE;
		};
	}		

	// Left Container
	if (IsSplitScreen() && (selectedItem == oldSelection) && (offset == oldOffset))
		ActivateNextContainer(-1);

	if (m_bManipulateItemsDisabled && GetSelectedItem() && GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
	{
		selectedItem=-1;
		offset		= oldOffset;
	};
}

void oCItemContainer::PrevItemLine()
{	
	if (!contents)		return;
	if (selectedItem<0) return;

	int oldSelection		= selectedItem;
	int oldOffset			= offset;
	
	if (GetSelectedItem()) GetSelectedItem()->RotateForInventory();

	zBOOL finished=FALSE;			

	while (!finished)
	{
		if (selectedItem > 0) 
		{			
			if (selectedItem >= maxSlotsCol) 
			{			
				selectedItem -= maxSlotsCol;
				if (selectedItem < 0)
					selectedItem = 0;
				if (selectedItem < offset)
					offset -= maxSlotsCol;
				if (offset < 0)
					offset = 0;
			}
			else
			{
				selectedItem--;		
				if (selectedItem < offset)
					offset -= maxSlotsCol;
				if (offset < 0)
					offset = 0;
			}

			if (!m_bManipulateItemsDisabled || !GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
			{										
				// SetCategoryOnRightContainer();
				finished=TRUE;
			}
		}
		else
		{
			selectedItem= oldSelection;
			offset		= oldOffset;
			finished=TRUE;
		};
	}		

	if (m_bManipulateItemsDisabled && GetSelectedItem() && GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE))
	{
		selectedItem=-1;
		offset		= oldOffset;
	};
}

zBOOL oCItemContainer::IsEmpty()
{
	return (!contents || (contents->GetNumInList()<=0));
}

zBOOL oCItemContainer::IsSplitScreen()
{
	switch (this->GetMode())
	{
	case INV_MODE_CONTAINER:
	case INV_MODE_BUY:
	case INV_MODE_SELL:
		if (GetInvSplitScreen())
			return TRUE;
		break;
	default:
		{
			oCItemContainer* leftContainer = GetNextContainerLeft(this);
			if (leftContainer)
			{
				switch (leftContainer->GetMode())
				{
				case INV_MODE_CONTAINER:
				case INV_MODE_BUY:
				case INV_MODE_SELL:
					if (GetInvSplitScreen())
						return TRUE;
					break;
				}
			}
		}
		break;
	}
	
	return FALSE;
}

zBOOL oCItemContainer::TransferItem(int dir, int maxAmount)
{
	if (m_bManipulateItemsDisabled && GetSelectedItem()->HasFlag(ITM_FLAG_ACTIVE)) 
	{
		return FALSE;
	}	

	oCItemContainer* cont = NULL;
	if (dir<0)	cont = GetNextContainerLeft (this);	
	else		cont = GetNextContainerRight(this);				
	if (cont) 
	{
		oCItem* item = GetSelectedItem();
		if (item)
		{
			int transferAmount=1;
			if (CanTransferMoreThanOneItem())
			{
				transferAmount = zMin(item->GetAmount(),maxAmount);
			}
			oCItem* insItem;
			
			// Patch 1.08 : Fix.
			item->AddRef();
			for (int i=0;i<transferAmount;i++)
			{		
				// Patch 1.08 : Fix : Argh !
				oCNpcContainer* cont2 = dynamic_cast<oCNpcContainer*>(this);
				if (cont2 && (item->GetAmount()==1)) {
					if (cont2->GetOwner() && !ownList) insItem = cont2->GetOwner()->inventory2.RemoveByPtr(item,1);
				}
				insItem = this->Remove(item, 1);
				if (insItem) {
					cont -> Insert(insItem);
				}
			}
			zRELEASE(item);
			return TRUE;
		}
	}
	return FALSE;
}

zBOOL oCItemContainer::ActivateNextContainer(int dir)
{
	oCItemContainer* cont = NULL;
	if (dir<0)	cont = GetNextContainerLeft (this);	
	else		cont = GetNextContainerRight(this);				
	if (cont)	cont ->Activate();
	return (cont!=NULL);
}

void oCItemContainer::Archive(zCArchiver &arc)
{
	if (!arc.InSaveGame())	return;
	// Nur im SaveGameMode ausführen

	int n = contents->GetNumInList();
	int c = 0;
	zSTRING s;
	// List aller Items speichern
	arc.WriteGroupBegin	("contents");	
	arc.WriteInt		("itemNr"	,n);
	zCListSort<oCItem> *node = contents->GetNextInList();
	while (node) 
	{
		s = "item"+zSTRING(c);
		arc.WriteObject(s.ToChar(),node->GetData());
		node = node -> GetNextInList();
		c++;
	}
	arc.WriteGroupEnd	("contents");
}

void oCItemContainer::Unarchive(zCArchiver &arc)
{
	if (!arc.InSaveGame())	return;
	// Nur im SaveGameMode ausführen

	oCItem* item;
	int n = 0;
	zSTRING s;
	arc.ReadInt	("itemNr" ,n);
	for (int i=0; i<n; i++) 
	{
		s = "item"+zSTRING(i);
		item = (oCItem*)arc.ReadObject1(s.ToChar());
		Insert(item);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCItemContainer::HandleEvent
//
//	2002-05-12	[BENDLIN]
//	
//				Inventory, Auto-Toggle entfernt
//				Inventory, RMT zum Schließen deaktiviert
//				Neues Interface: (in dieser Reihenfolge!)
//					GAME_ACTION / GAME_SMOVE	= Item transferieren	( + MOUSE_BUTTONLEFT	)
//					GAME_UP						= Auswahl nach oben		( + MOUSE_WHEELUP		)
//					GAME_DOWN					= Auswahl nach unten	( + MOUSE_WHEELDOWN		)
//					GAME_END / GAME_INVENTORY	= Abbruch				( + MOUSE_BUTTONRIGHT	)
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCItemContainer::HandleEvent( int key )
{
	if (!IsActive()) return FALSE;

	// Transfer-Anzahl initialisieren
	if ( zinput->IsBindedToggled(GAME_ACTION, key)
		|| ((key == MOUSE_BUTTONLEFT) && zinput->KeyToggled(MOUSE_BUTTONLEFT)) )
	{
		SetTransferCount(0);
	}
	
	zINT transferAmount = TransferCountToAmount(GetTransferCount());

	// DROP-Transfer
	if ( zinput->IsBinded(GAME_SMOVE, key) )
	{
		SetTransferCount(0);

		oCItem* selItem = GetSelectedItem();
		if ( selItem ) if ( transferAmount < selItem->GetAmount() ) transferAmount = selItem->GetAmount();
	}

	// ein nicht aktiver Container verfuegbar?
	zBOOL bNextContainer = FALSE;
	oCItemContainer* cont = GetNextContainerLeft(this);
	if (!cont)
		cont = GetNextContainerRight(this);
	if (cont)
		bNextContainer = cont->IsOpen() && !cont->IsPassive();
	// GAME_INVENTORY toggled
	zBOOL bInventoryToggled = zinput->IsBindedToggled(GAME_INVENTORY, key);

	// Schliessen mit GAME_END und GAME_INVENTORY (nur wenn kein anderes Inventory)
	if ( zinput->IsBindedToggled(GAME_END, key) ||
		(bInventoryToggled && (!bNextContainer || IsSplitScreen())) ||
		(key == MOUSE_BUTTONRIGHT && zinput->KeyToggled(MOUSE_BUTTONRIGHT)) )
	{
		Close();
		oCNpc::player->CloseInventory();
		// States zurück
		oCMobInter* mob = dynamic_cast<oCMobInter*>(oCNpc::player->GetInteractMob());
		if (mob)
		{
			oCMobMsg* msg = zNEW(oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE, oCNpc::player));
			msg->from = mob->GetState();
			msg->to = msg->from - 1;
			mob->GetEM()->OnMessage(msg, oCNpc::player);								
		}
		return TRUE;
	}
	// Actions
	else if ( zinput->IsBinded(GAME_ACTION, key) || zinput->IsBinded(GAME_SMOVE, key) || (key == MOUSE_BUTTONLEFT) )
	{
		oCItem* item = GetSelectedItem();
		if (item) 
		{

			if( oCNpc::player->CanCarry(item) )
			{
				oCItem* newItem = NULL;
				// wenn es das/die letzte(n) Item(s) ist/sind
				if ( transferAmount >= item->GetAmount() )
				{
					transferAmount = item->GetAmount();
					SetTransferCount(0);  // da letzte Aktion
				}
				else
				{
					// internen Zähler hochsetzen
					IncTransferCount(transferAmount);
				}
				// Transferieren
				newItem = this->RemoveByPtr(item, transferAmount);
				oCNpc::player->PutInInv(newItem/*, transferAmount*/);

				// Wenn Inventory leer -> schliessen
				if ( IsEmpty() )
				{
/*					Close();
					oCNpc::player->CloseInventory();
					// States zurück
					oCMobInter* mob = dynamic_cast<oCMobInter*>(oCNpc::player->GetInteractMob());
					if (mob)
					{
						oCMobMsg* msg = zNEW(oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE, oCNpc::player));
						msg->from = mob->GetState();
						msg->to = msg->from - 1;
						mob->GetEM()->OnMessage(msg, oCNpc::player);								
					} */
				}
			}
		}
		return TRUE;
	}
	// anderer Container rechts?
	else if ( bInventoryToggled && bNextContainer && !IsSplitScreen())
	{
		if ( !ActivateNextContainer(+1) )
			ActivateNextContainer(-1);
	}	
	// Scrollen (nach links)
	else if ( zinput->IsBinded(GAME_LEFT, key) || zinput->IsBinded(GAME_STRAFELEFT, key) )
	{
		PrevItem();
		return TRUE;
	} 
	// Scrollen (nach oben)
	else if ( zinput->IsBinded(GAME_UP, key) || (key == MOUSE_WHEELUP) )
	{
		PrevItemLine();
		return TRUE;
	} 
	// Scrollen (nach unten)
	else if ( zinput->IsBinded(GAME_DOWN, key) || (key == MOUSE_WHEELDOWN) )
	{
		NextItemLine();
		return TRUE;
	} 
	// Scrollen (nach rechts)
	else if ( zinput->IsBinded(GAME_RIGHT, key) || zinput->IsBinded(GAME_STRAFERIGHT, key) )
	{
		NextItem();
		return TRUE;
	} 
	
	return FALSE; 
}

// **********************************************************************************
// Stehlen
// **********************************************************************************

oCStealContainer::oCStealContainer()
{
	owner = NULL;
}


oCStealContainer::~oCStealContainer()
{
	// Liste löschen, aber nicht deren viewContent
	// safety : ownList == FALSE -> nicht löschen
	// Liste löschen, aber nicht deren viewContent -> 
	// dieser befindet sich im Inventory
	ownList		= FALSE;
	delete (contents);
	contents	= NULL;
	owner		= NULL;
}

void oCStealContainer::SetOwner (oCNpc* n)
{
	owner = n;
	CreateList();
}

oCNpc* oCStealContainer::GetOwner ()
{
	return owner;
}

void oCStealContainer::CreateList()
{
	// Aktuelle Liste loeschen
	//
	this->contents->DeleteList();

	// Das Inventory des Owners nach stehlbaren Items durchsuchen
	// und in die Liste einfügen
	ownList		= FALSE;

	int		itemNum	= 0;
	oCItem* ele		= NULL;
	
	itemNum = owner->inventory2.GetNumItemsInCategory();
	for (int i=0; i<itemNum; i++) {
	
		ele = owner->inventory2.GetItem(i);
		if (!ele) continue;
		
		// equippte Sachen dürfen nicht benutzt werden				
		int wert = ele->GetValue();
		if (ele->GetAmount()>1) wert *= ele->GetAmount();

		// [BENDLIN] Rüstungen können NICHT gekauft/gestohlen werden
		if (!ele->HasFlag(ITM_FLAG_ACTIVE) && !ele->HasFlag(ITM_CAT_ARMOR))
		{

			// Gegenstand gefunden, in Liste einfügen
			// nur über das Standard - Insert, 
			// da es sonst nochmal ins Inv eingefügt wird
			// -> einfach nur Insert(item)
			
			// [BENDLIN] HACK: Gold nicht mehr bei Händlern anzeigen
			if (!owner->GetTradeNpc() || !owner->GetTradeNpc()->IsSelfPlayer() ||
				(ele->GetInstanceName().CompareTo( oCItemContainer::GetCurrencyInstanceName() ) != 0))
			{
				oCItemContainer::Insert(ele);
			}
		} 
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCStealContainer::HandleEvent
//
//	2002-05-12	[BENDLIN]
//
//				Neues Interface: (in dieser Reihenfolge!)
//					GAME_ACTION / GAME_SMOVE	= Item stehlen			( + MOUSE_BUTTONLEFT	)
//					GAME_UP						= Auswahl nach oben		( + MOUSE_WHEELUP		)
//					GAME_DOWN					= Auswahl nach unten	( + MOUSE_WHEELDOWN		)
//					GAME_END / GAME_INVENTORY	= Abbruch				( + MOUSE_BUTTONRIGHT	)
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCStealContainer::HandleEvent( int key )
{
	if ( !IsActive() ) return FALSE;

	// Transfer-Anzahl initialisieren
	if (zinput->IsBindedToggled(GAME_ACTION, key)	||
		zinput->IsBinded(GAME_SMOVE, key)			||
		((key == MOUSE_BUTTONLEFT) && zinput->KeyToggled(MOUSE_BUTTONLEFT)) )
	{
		SetTransferCount(0);
	}
	
	zINT transferAmount = TransferCountToAmount(GetTransferCount());

	// Schliessen mit GAME_END und GAME_INVENTORY (toggle-checked)
	if ( zinput->IsBindedToggled(GAME_END, key) || zinput->IsBindedToggled(GAME_INVENTORY, key) || (key == MOUSE_BUTTONRIGHT && zinput->KeyToggled(MOUSE_BUTTONRIGHT)) )
	{
		owner->StopTheft(oCNpc::player, FALSE);
		return TRUE;
	}
	// Actions
	else if ( zinput->IsBinded(GAME_ACTION, key) || zinput->IsBinded(GAME_SMOVE, key) || (key == MOUSE_BUTTONLEFT) )
	{
		oCItem* item = GetSelectedItem();
		if ( item && owner )
		{
			// SC muß Item aufnehmen können
			if ( oCNpc::player->CanCarry(item) )
			{
				// Item darf nicht angelegt sein
				if ( !item->HasFlag(ITM_FLAG_ACTIVE) )
				{
					// Chance ist Möglichkeit des Versagens
					int nPercentage = ::zRand(100);
					if ( nPercentage < oCNpc::player->GetTalentValue(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_PICKPOCKET) )
					{
						oCItem* newItem = NULL;
						// wenn es das/die letzte(n) Item(s) ist/sind, dann beim Besitzer entfernen
						if ( transferAmount >= item->GetAmount() )
						{
							transferAmount = item->GetAmount();
							SetTransferCount(0);  // da letzte Aktion
							
							newItem = owner->inventory2.RemoveByPtr(item, transferAmount);
						}
						else
						{
							// internen Zähler hochsetzen
							IncTransferCount(transferAmount);
						}
						// Transferieren
						newItem = this->RemoveByPtr(item, transferAmount);
						oCNpc::player->PutInInv(newItem/*, transferAmount*/);

						// Wenn Inventory leer -> schliessen
						if ( IsEmpty() )
						{
							// [BENDLIN] 1.28
							// Tasten wegschmeißen, da das Inventar von alleine zugeht
							zinput->ClearKeyBuffer();
							owner->StopTheft(oCNpc::player, FALSE);
							return TRUE;
						}

					}
					else
					{
						// [BENDLIN] 1.28
						// Tasten wegschmeißen, da das Inventar von alleine zugeht
						zinput->ClearKeyBuffer();
						owner->StopTheft(oCNpc::player, TRUE);
					}
				}
				else if( !owner->IsUnconscious() && !owner->IsDead() )
				{
					// [BENDLIN] 1.28
					// Tasten wegschmeißen, da das Inventar von alleine zugeht
					zinput->ClearKeyBuffer();
					owner->StopTheft(oCNpc::player, TRUE);
				}
			}
		}
		return TRUE;
	}
	// Scrollen (nach links)
	else if ( zinput->IsBinded(GAME_LEFT, key) || zinput->IsBinded(GAME_STRAFELEFT, key) )
	{
		PrevItem();
		return TRUE;
	} 
	// Scrollen (nach oben)
	else if ( zinput->IsBinded(GAME_UP, key) || (key == MOUSE_WHEELUP) )
	{
		PrevItemLine();
		return TRUE;
	} 
	// Scrollen (nach unten)
	else if ( zinput->IsBinded(GAME_DOWN, key) || (key == MOUSE_WHEELDOWN) )
	{
		NextItemLine();
		return TRUE;
	} 
	// Scrollen (nach rechts)
	else if ( zinput->IsBinded(GAME_RIGHT, key) || zinput->IsBinded(GAME_STRAFERIGHT, key) )
	{
		NextItem();
		return TRUE;
	} 
	
	return FALSE; 
}

// **********************************************************************************
// Plündern
// **********************************************************************************

oCNpcContainer::oCNpcContainer()
{
}

oCNpcContainer::~oCNpcContainer()
{
}

void oCNpcContainer::CreateList()
{
	ownList	= FALSE;

	int		numItems	= 0;
	oCItem* ele			= NULL;

	numItems = owner->inventory2.GetNumItemsInCategory();
	for (int i=0; i<numItems; i++)
	{
		// Alles rein da.
		ele = owner->inventory2.GetItem(i);
		if (!ele)
			continue;
		
		// nur über das Standard - Insert, 
		// da es sonst nochmal ins Inv eingefügt wird
		// -> einfach nur Insert(item)
		if (!ele->HasFlag(ITM_CAT_ARMOR) && !ele->HasFlag(ITM_FLAG_ACTIVE))
		{
			oCItemContainer::Insert (ele);
		}
	}
//	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCNpcContainer::HandleEvent
//
//	2002-05-12	[BENDLIN]
//
//				Neues Interface: (in dieser Reihenfolge!)
//					GAME_ACTION / GAME_SMOVE	= Item plündern			( + MOUSE_BUTTONLEFT	)
//					GAME_UP						= Auswahl nach oben		( + MOUSE_WHEELUP		)
//					GAME_DOWN					= Auswahl nach unten	( + MOUSE_WHEELDOWN		)
//					GAME_END / GAME_INVENTORY	= Abbruch				( + MOUSE_BUTTONRIGHT	)
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCNpcContainer::HandleEvent( int key )
{
	if ( !IsActive() ) return FALSE;

	// Transfer-Anzahl initialisieren
	if ( zinput->IsBindedToggled(GAME_ACTION, key)
		|| ((key == MOUSE_BUTTONLEFT) && zinput->KeyToggled(MOUSE_BUTTONLEFT)) )
	{
		SetTransferCount(0);
	}
	
	zINT transferAmount = TransferCountToAmount(GetTransferCount());

	// DROP-Transfer

	if ( zinput->IsBinded(GAME_SMOVE, key) )
	{
		SetTransferCount(0);

		oCItem* selItem = GetSelectedItem();
		if ( selItem ) if ( transferAmount < selItem->GetAmount() ) transferAmount = selItem->GetAmount();
	}

	// Schliessen mit GAME_END und GAME_INVENTORY (toggle-checked)
	if ( zinput->IsBindedToggled(GAME_END, key) || zinput->IsBindedToggled(GAME_INVENTORY, key) || (key == MOUSE_BUTTONRIGHT && zinput->KeyToggled(MOUSE_BUTTONRIGHT)) )
	{
		Close();
		oCNpc::player->CloseDeadNpc();
		return TRUE;
	}
	// Actions
	else if ( zinput->IsBinded(GAME_ACTION, key) || zinput->IsBinded(GAME_SMOVE, key) || (key == MOUSE_BUTTONLEFT) )
	{
		oCItem* item = GetSelectedItem();
		if ( item )
		{
			// Angelegte Items ablegen lassen
			if (item->HasFlag(ITM_FLAG_ACTIVE))
				owner->UnequipItem(item);
	
			if ( oCNpc::player->CanCarry(item) )
			{

				oCItem* newItem = NULL;
				// wenn es das/die letzte(n) Item(s) ist/sind, dann beim Besitzer entfernen
				if ( transferAmount >= item->GetAmount() )
				{
					transferAmount = item->GetAmount();
					SetTransferCount(0);  // da letzte Aktion

					newItem = owner->inventory2.RemoveByPtr(item, transferAmount);
				}
				else
				{
					// internen Zähler hochsetzen
					IncTransferCount(transferAmount);
				}
				// Transferieren
				newItem = this->RemoveByPtr(item, transferAmount);
				oCNpc::player->PutInInv(newItem/*, transferAmount*/);

				// Wenn Inventory leer -> schliessen
				if ( IsEmpty() )
				{
					// [BENDLIN] 1.28
					// Tasten wegschmeißen, da das Inventar von alleine zugeht
					zinput->ClearKeyBuffer();
					oCNpc::player->CloseDeadNpc();
				}
			}
		}
		return TRUE;
	}
	// anderer Container rechts ? // !!! Es ist nicht mehr möglich beim Plündern Items zum Geplünderten zu Transferieren !!!
//	else if ( zinput->IsBinded(GAME_RIGHT, key) || zinput->IsBinded(GAME_STRAFERIGHT, key) )
//	{
//	 	ActivateNextContainer(+1);
//	} 
	// Scrollen (nach links)
	else if ( zinput->IsBinded(GAME_LEFT, key) || zinput->IsBinded(GAME_STRAFELEFT, key) )
	{
		PrevItem();
		return TRUE;
	} 
	// Scrollen (nach oben)
	else if ( zinput->IsBinded(GAME_UP, key) || (key == MOUSE_WHEELUP) )
	{
		PrevItemLine();
		return TRUE;
	} 
	// Scrollen (nach unten)
	else if ( zinput->IsBinded(GAME_DOWN, key) || (key == MOUSE_WHEELDOWN) )
	{
		NextItemLine();
		return TRUE;
	} 
	// Scrollen (nach rechts)
	else if ( zinput->IsBinded(GAME_RIGHT, key) || zinput->IsBinded(GAME_STRAFERIGHT, key) )
	{
		NextItem();
		return TRUE;
	} 

	return FALSE; 
}

oCItem* oCNpcContainer::Insert (oCItem* item)
{
	if (!item)
		return NULL;
	// 1. In diese Liste einfügen
	item = oCItemContainer::Insert (item);
	// 2. Dem Owner ins Inventory packen
	// Patch 2 : Verdoppelung beim pluendern
	if (owner && ownList)
		item = owner->PutInInv(item);
	return item;
}
	
void oCNpcContainer::Remove (oCItem* item)
{
	if (!item) return;
	// 1. Aus dieser Liste entfernen
	oCItemContainer::Remove (item);
	// 2. Dem Owner ins Inventory packen
	// Patch 2 : Verdoppelung beim pluendern
	if (owner && ownList)
		owner->RemoveFromInv(item, item->GetAmount());
}

// **********************************************************************************
// Npc - Inventory
// **********************************************************************************

zCGfx *oCNpcInventory::gfx_title = NULL;

/* ----------------------------------------------------------------------
	
    oCNpcInventory::oCNpcInventory()	

	 11.12.2000	[Moos]	
                Leakfix wieder aktiviert

   ---------------------------------------------------------------------- */


oCNpcInventory::oCNpcInventory ()
{
// [BENDLIN] Sortierung wurde in oCItemContainer verschoben
//	inventory.SetCompare(InventorySort);

	// Vars
	owner	= NULL;
	ownList = FALSE;

//	memset(_offset,0,sizeof(_offset));
//	memset(_itemnr,0,sizeof(_itemnr));

    delete contents;        // [Moos] Leakfix, Versuch Nr. 3. (11.12.00) Muss wirklich hier im Konstruktor stehen, da contents vom Konstruktor der Basisklasse erzeugt, dank ownList=FALSE aber nicht mehr gelöscht wird.
    contents=NULL;

//    SwitchToCategory(1);
	SetContents(&inventory);
//    invnr=-1;               // Damit die Items beim ersten betrachten des Inventorys richtig rotiert werden	

	// Pack Ability
#ifdef PACKED_INVENTORY
	SetPackAbility(TRUE);
#else
	SetPackAbility(FALSE);
#endif
}

oCNpcInventory::~oCNpcInventory()
{
	ClearInventory();
	owner = NULL;
}

void oCNpcInventory::ClearInventory()
{
	// Komplette Listen löschen
	zCListSort<oCItem> *node = NULL;

	node = inventory.GetNextInList();
	while (node)
	{
		// aus globalen Listen entfernen
		oCItem* item	= node->GetData();
		node			= node->GetNextInList();

#if 0  // [Moos] dieser ganze Klumbatsch wird nun hoffentlich nicht mehr gebraucht.
		assert(item->GetRefCtr() >= (item->GetHomeWorld() ? 2 : 1)); // [Moos] Wenn das Item nicht in der Welt ist, darf der Refcounter auch kleiner sein.
		if (ogame && ogame->GetWorld()) // [Moos] Test auf ogame dazu, da das Spiel schon weg sein kann
            ogame->GetWorld()->RemoveVob(item); 
/*		else{
            if (item->GetRefCtr()>1) item->Release(); // [Moos] Die Welt hat das Ding schamlos liegengelassen.
            if (item->GetRefCtr()>1) item->Release(); // sorge dafür, dass es weiter unten trotzdem verschwindet.
        }
*/ 
#endif

		zRELEASE_ACCT_NONULL(item);	// aus Inventory entfernt... 
	}
	inventory.DeleteList();

	// Und packStrings clearen.
	packString.Clear();
}
 
void oCNpcInventory::Open(int x, int y, int mode)
{
	UnpackAllItems();

	//changed[dennis]
	oCItem *item = dynamic_cast<oCItem*>(owner->GetRightHand());
	if( item )
	{
		if( item->HasFlag(ITM_FLAG_THROW) )
		{
			if((item->GetInstanceName() == zSTRING("ITLSTORCHBURNING")))
			{
				//put torch in inv
				owner->SetTorchAni(FALSE);
				oCItem* torch = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,"ITLSTORCH");
				owner->RemoveFromSlot(NPC_NODE_RIGHTHAND,FALSE);
				owner->PutInInv(torch);
				zRELEASE( item );
			}
			else
			{
				owner->RemoveFromSlot(NPC_NODE_RIGHTHAND,FALSE);
				owner->PutInInv(item);
			}
		}
	}
	item = dynamic_cast<oCItem*>(owner->GetLeftHand());
	if( item )
	{
		if( item->HasFlag(ITM_FLAG_THROW) )
		{
			if((item->GetInstanceName() == zSTRING("ITLSTORCHBURNING")))
			{
				//put torch in inv
/*				owner->SetTorchAni(FALSE);
				oCItem* torch = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,"ITLSTORCH");
				owner->RemoveFromSlot(NPC_NODE_LEFTHAND,FALSE);
				owner->PutInInv(torch);
				zRELEASE( item );*/ 
			}
			else
			{
				owner->RemoveFromSlot(NPC_NODE_LEFTHAND,FALSE);
				owner->PutInInv(item);
			}
		}
	}
	oCItemContainer::Open(x, y, mode);
	//changed[dennis]
//	if (IsEmpty())		SwitchToCategory(0);
//	else if (invnr<0)	SwitchToCategory(1);
	if (owner)
		owner->SetBodyState(BS_INVENTORY);

	// [BENDLIN] FLUSH KEYS!
	zinput->ClearKeyBuffer();
	zinput->ResetRepeatKey();
}

void oCNpcInventory::Close()
{
/*	oCItem *item = dynamic_cast<oCItem*>(owner->GetRightHand());
	if( item )
	{
		if( item->HasFlag(ITM_FLAG_TORCH) )
		{
			owner->RemoveFromInv( item );
		}
	}
	item = dynamic_cast<oCItem*>(owner->GetLeftHand());
	if( item )
	{
		if( item->HasFlag(ITM_FLAG_TORCH) )
		{
			owner->RemoveFromInv( item );
		}
	}*/ 
	oCItemContainer::Close();

	// [BENDLIN] FLUSH KEYS!
	// zinput->ClearKeyBuffer();
	zinput->ResetRepeatKey();
}

void oCNpcInventory::Draw()
{
//	if (inv_item_height==0) return;
//	if (invnr<0)			return;
	
//	FindNextCategory();
 	
	// falls Anzahl in der Liste kleiner ist ... 	
	/* ... auskommentiert da immer maximale Anzahl angezeigt werden soll.
	int numInList = inventory[invnr].GetNumInList();
	drawItemMax = zMin(numInList,drawItemMax);
	*/

	// falls maximale Anzahl entsprechend der Kategorie kleiner ist ...
/*	switch( invnr )
	{
		case INV_COMBAT:	drawItemMaxY = zMin(INV_COMBAT_MAX,drawItemMaxY);	break;
		case INV_ARMOR:		drawItemMaxY = zMin(INV_ARMOR_MAX,drawItemMaxY);	break;
		case INV_FOOD:		drawItemMaxY = zMin(INV_FOOD_MAX,drawItemMaxY);		break;
		case INV_DOCS:		drawItemMaxY = zMin(INV_DOCS_MAX,drawItemMaxY);		break;
		case INV_OTHER:		drawItemMaxY = zMin(INV_MISC_MAX,drawItemMaxY);		break;
		case INV_POTION:	drawItemMaxY = zMin(INV_POTION_MAX,drawItemMaxY);	break;
		case INV_RUNE:		drawItemMaxY = zMin(INV_RUNE_MAX,drawItemMaxY);		break;
		case INV_MAGIC:		drawItemMaxY = zMin(INV_MAGIC_MAX,drawItemMaxY);	break;
	} */
	oCItemContainer::Draw();
};

void oCNpcInventory::SetOwner(oCNpc* npc)
{
	owner = npc;
}

oCNpc* oCNpcInventory::GetOwner(void)
{
	return owner;
}

/* void oCNpcInventory::SetFirstCategory ()
{
	for (int i=0; i<INV_MAX; i++) {
		if (GetNumItemsInCategory(i)>0) {
			SwitchToCategory(i);
			return;
		}
	} 
	// Empty...
	SwitchToCategory(0);
} */

// int oCNpcInventory::GetNumItemsInCategory(int nCategory)
int oCNpcInventory::GetNumItemsInCategory()
{
//	if ((nCategory<INV_NONE) || (nCategory>=INV_MAX))				return 0;
//	return inventory[nCategory].GetNumInList() + GetNumItemsInPackString(nCategory);
	return inventory.GetNumInList() + GetNumItemsInPackString();
};

//
//	CODECHANGE [ROMAN]
//
oCItem* oCNpcInventory::GetItem(int nSlot)
{
	// [Ulf] : Out of Range Zugriffe abfangen...
	if ((nSlot<0) || (nSlot>=GetNumItemsInCategory()))		return NULL;

	// [Ulf] : Geht jetzt bei Null los (nSlot-1 entfernt)
	oCItem* item = inventory.Get(nSlot);
	if (!item && GetPackAbility())
	{
		zSTRING itemInstance;
		if (GetPackedItemBySlot(nSlot - inventory.GetNumInList(), itemInstance)) {
			item = CreateFromPackString(itemInstance);
		}
	}
	return item;
}
//
//	CODECHANGE [ROMAN] END
//

int oCNpcInventory::GetCategory(oCItem* item)
{
	return Inventory_GetCategory(item);
}

oCItem* oCNpcInventory :: Insert	(oCItem* item)
// virtual
{
	if (!item) return NULL;

    // [Moos] Entferne das Item aus der Welt; die muss ja nichts mehr davon wissen.
    if (item->GetHomeWorld())
        item->RemoveVobFromWorld();

    if (item->GetInstance() < 0 || item->GetName().Length() < 0)
    {
        zERR_WARNING("M: Invalid item (no name, no instance) put into inventory. Deleting it.");

        if (item->GetHomeWorld())
            item->RemoveVobFromWorld();

        return NULL;
    }

	if (item->MultiSlot())
	{
		zCListSort <oCItem> *ele = inventory.GetNextInList();
		while (ele)
		{
			oCItem* i = ele->GetData();
			//
			// [BENDLIN] Addon - SplitSlot
			//
			// Es muessen beide Multi-Items sein!
			//
			if (i->MultiSlot())
			if (i->GetInstance() == item->GetInstance())
			{
				i->SetAmount(i->GetAmount() + item->GetAmount());
				ogame->GetGameWorld()->RemoveVob(item);
				return i;
			}
			ele = ele->GetNextInList();
		}
	}

    if (inventory.InList(item))
        return item;

	// Ansonsten normal einfügen
	inventory.InsertSort(item);
	CheckSelectedItem();
	zADDREF_ACCT(item);		                // Im Inv, also AddRef drauf.	

    ogame->GetGameWorld()->RemoveVob(item); // Raus aus der Welt damit	

	return item;
}

int oCNpcInventory::GetAmount (int instance)
{
	if (instance<0) return 0;

	int amount	= 0;
	zCListSort <oCItem> *ele = inventory.GetNextInList();
	while (ele)
	{
		oCItem* i = ele -> GetData();
		if (i->GetInstance()==instance)
		{
			amount += i->GetAmount();
		}
		ele = ele->GetNextInList();
	}

	// Gimme Names
	if (GetPackAbility())
	{
		zCPar_Symbol* sym = parser.GetSymbol(instance);
		if (sym)
		{	
			oCItem* item = this->CreateFromPackString(sym->name);
			if (item)
				amount += item->GetAmount();
		}
	}	
	return amount;
}

oCItem* oCNpcInventory::IsIn	(oCItem* item, int anz)
{
	if (!item)
		return NULL;

	zCListSort <oCItem> *ele = inventory.GetNextInList();
	while (ele)
	{
		oCItem* i = ele -> GetData();
		if ((i==item) && (i->GetAmount()>=anz))
			return i;
		ele = ele->GetNextInList();
	}
	return NULL;
}

oCItem* oCNpcInventory::IsIn	(const zSTRING& name, int anz)
{
	return IsIn (parser.GetIndex(name),anz);
}

oCItem* oCNpcInventory::IsIn	(int instance, int anz)
{
	oCItem* item = NULL;

	zCListSort <oCItem> *ele = inventory.GetNextInList();
	while (ele)
	{
		item = ele -> GetData();
		if ((item->GetInstance()==instance) && (item->GetAmount()>=anz)) return item;
		ele = ele->GetNextInList();
	}

	// Gimme Names
	if (GetPackAbility())
	{
		zCPar_Symbol* sym = parser.GetSymbol(instance);
		if (sym)
		{	
			item = this->CreateFromPackString(sym->name);
			if (item && item->GetAmount()>=anz) return item;
		}
	}
	return NULL;
}

void oCNpcInventory::Remove (oCItem* item)
// Virtual
{
	if (!item)
		return;

	inventory.Remove(item);	
	CheckSelectedItem();

	zRELEASE_ACCT_NONULL(item);	// Aus Inventory entfernt....
}

oCItem* oCNpcInventory::RemoveByPtr (oCItem* item, int anz)
{
	if (!item)
		return 0;
	
	if (item->MultiSlot())
		return Remove(item,anz);

	zERR_ASSERT(anz==1);

	oCItem* tmpItem = NULL;
	zCListSort <oCItem> *ele = inventory.GetNextInList();
	while (ele) 
	{
		tmpItem = ele -> GetData();
		if (tmpItem == item) 
		{
			inventory.Remove(tmpItem);
			CheckSelectedItem();
            ogame->GetGameWorld()->InsertVobInWorld(tmpItem);
            zERR_ASSERTT_STRICT(tmpItem->GetRefCtr()>1,"Removing item with refcount <=1 from inventory will cause it to be deleted...");
			zRELEASE_ACCT_NONULL(tmpItem);	// Aus Inventory entfernt....
			return tmpItem;									
		}
		ele = ele->GetNextInList();
	};
	
	return NULL;
};

oCItem* oCNpcInventory::Remove (oCItem* item, int anz)
{
	if (!item) return 0;

	oCItem* tmpItem = NULL;
	if (!item->MultiSlot())
		tmpItem = RemoveByPtr(item, anz);
    if (tmpItem)
        return tmpItem;

    for (int avoidEquipped = 1; avoidEquipped >=0 ; avoidEquipped --) // [Moos] versuche zuerst, ein nichtequipptes Item zu nehmen
    {
	    zCListSort <oCItem> *ele = inventory.GetNextInList();
	    while (ele) 
	    {
		    tmpItem = ele -> GetData();
		    if (tmpItem->GetInstance()==item->GetInstance() && (!avoidEquipped || !tmpItem->HasFlag(ITM_FLAG_ACTIVE))) 
		    {
				// [BENDLIN] remove if requested amount is equal to OR GREATER than the current amount
			    if (tmpItem->GetAmount()<=anz) 
			    {
				    // a) passt genau / weniger -> zurückliefern

					// [BENDLIN] FIXME: generate requested amount?
					//if ( tmpItem->GetAmount() < anz )
					//	tmpItem->SetAmount( anz );

				    inventory.Remove(tmpItem);
				    CheckSelectedItem();

                    // [Moos] Füge das Item wieder in die Welt ein; sonst: Crash wegen dem Release unten, was das item sicher löscht...
                    ogame->GetGameWorld()->InsertVobInWorld(tmpItem);				
                    zERR_ASSERTT_STRICT(tmpItem->GetRefCtr()>1,"Removing item with refcount <=1 from inventory will cause it to be deleted...");
				    zRELEASE_ACCT_NONULL(tmpItem);	// Aus Inventory entfernt....
				    return tmpItem;
			    } 
			    else if (tmpItem->GetAmount()>anz) 
			    {
				    // b) mehr da als benötigt
				    //    Kopie des benötigten Items anlegen
				    tmpItem -> ChangeAmount( -anz );
				    tmpItem =  (oCItem*) ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,tmpItem->GetInstance());
				    tmpItem -> SetAmount ( anz );

                    ogame->GetGameWorld()->InsertVobInWorld(tmpItem);
				    // Hier ist das Item in den Listen vorhanden -> refCtr == 3
				    // hier muss ein zRELEASE drauf.
				    zERR_ASSERT(tmpItem->GetRefCtr()==3);
				    zRELEASE_ACCT_NONULL(tmpItem);
				    return tmpItem;
			    }					
		    }
		    ele = ele->GetNextInList();
	    }
    }
	return NULL;
}

oCItem* oCNpcInventory::Remove (int instance, int anz)
{
	oCItem* item = NULL;
	zCListSort <oCItem> *ele = inventory.GetNextInList();
	while (ele) 
	{
		item = ele -> GetData();
		if (item->GetInstance() == instance) return Remove(item,anz);
		ele = ele -> GetNextInList();
	}

	// Gimme Names
	if (GetPackAbility()) 
	{
		zCPar_Symbol* sym = parser.GetSymbol(instance);
		if (sym) 
		{
			item = this->CreateFromPackString(sym->name);
			if (item)
				Remove(item,anz);		
		}
	}
	return NULL;
}
	
oCItem* oCNpcInventory::Remove (const zSTRING& name, int anz)
{
	return Remove(parser.GetIndex(name), anz);
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCNpcInventory::IsEmpty
//
//	2002-05-12	[BENDLIN]
//
//				Armor kann ignoriert werden
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCNpcInventory::IsEmpty (zBOOL bIgnoreArmor, zBOOL bIgnoreActive)
{
	oCItem* item = NULL;
	// [BENDLIN] Addon Patch - Unpack for Checks!
	UnpackCategory();
	zCListSort <oCItem> *ele = inventory.GetNextInList();
	while (ele) 
	{
		item = ele -> GetData();
		if ( item )
		{
			if (bIgnoreArmor && (GetCategory(item) == INV_ARMOR) )
			{
				ele = ele -> GetNextInList();
				continue;
			}
			// [BENDLIN] Addon Patch - Added IgnoreActive
			if (bIgnoreActive && item->HasFlag(ITM_FLAG_ACTIVE))
			{
				ele = ele -> GetNextInList();
				continue;
			}
			return FALSE;
		}
		ele = ele -> GetNextInList();
	}
	return TRUE;
}

/* zBOOL oCNpcInventory::IsCatEmpty (int nr)
{
	oCItem* item = NULL;
	zCListSort <oCItem> *ele = inventory.GetNextInList();
	while (ele) 
	{
		item = ele -> GetData();
		if ( item )
		if ( GetCategory(item) == nr )
		{
			return FALSE;
		}
		ele = ele -> GetNextInList();
	}
	return TRUE;
} */

void oCNpcInventory::Archive(zCArchiver &arc)
{
#ifdef PACKED_INVENTORY
	PackAllItems();
	arc.WriteString("packed",packString);
	// Alle equippten Sachen werden jetzt noch mitgespeichert.
#endif 

	zSTRING s;
	int c	= 0;
	int num = inventory.GetNumInList();

	// List aller Items speichern
	arc.WriteGroupBegin	("contents");
	arc.WriteInt		("itemCount"	,num);
	zCListSort<oCItem> *node = NULL;

	node = inventory.GetNextInList();
	while (node)
	{
		s	 = "item"+zSTRING(c);
		arc.WriteObject(s.ToChar(),node->GetData());
		if( node->GetData()->mainflag == ITM_CAT_RUNE )
		{
			int keyNo = 0;
			if (owner && owner->GetSpellBook()) keyNo = owner->GetSpellBook()->GetKeyByItem(node->GetData());
			s = "shortKey"+zSTRING(c);
			arc.WriteInt(s.ToChar(),keyNo);
		}
		node = node -> GetNextInList();
		c++;
	}

	arc.WriteGroupEnd	("contents");
}

void oCNpcInventory::Unarchive(zCArchiver &arc)
{
	if (!arc.InSaveGame())	return;
	// Nur im SaveGameMode ausführen

#ifdef PACKED_INVENTORY
	arc.ReadString("packed",packString);
#endif 

	oCItem* item;
	int n = 0;
	zSTRING s;
	arc.ReadInt	("itemCount" ,n);
	for (int c=0; c<n; c++) 
	{
		s = "item"+zSTRING(c);
		item = (oCItem*)arc.ReadObject1(s.ToChar());

		if (!item)
		{
			zERR_WARNING("C: could not read inventory item");
			return;
		}

		int keyNo = -1;
		if(item->mainflag == ITM_CAT_RUNE )
		{
			s = "shortKey"+zSTRING(c);
			arc.ReadInt(s.ToChar(), keyNo);
			if (owner && owner->GetSpellBook()) owner->GetSpellBook()->NextRegisterAt(keyNo);
		}

		if( item->HasFlag( ITM_FLAG_ACTIVE ) )
		{
			item->ClearFlag( ITM_FLAG_ACTIVE );

			Insert(item);

			// Waffen nicht equippen, passiert durch die invSlots im Archive des NSCs.
			if ((GetCategory(item)!=INV_COMBAT)&&(GetCategory(item)!=INV_MAGIC)&&(GetCategory(item)!=INV_ARMOR)) 
			{
				owner->Equip (item);
			}
			else if(GetCategory(item)==INV_MAGIC)
			{
				item->SetFlag(ITM_FLAG_ACTIVE);
			}
		}
		else Insert(item);
        zRELEASE_ACCT(item); // [Moos] Leakfix
	}
}

// **********************************************************************************
// Inventory - Control
// **********************************************************************************

/* int oCNpcInventory::GetNextCategory ()
{
//changed[dennis]
	if(invnr == -1) return 0;
	if(invnr+1<INV_MAX)return invnr+1;
	else return invnr;
}

int oCNpcInventory::GetPrevCategory ()
{
//changed[dennis]
	if(invnr-1>0)return invnr-1;
	else return invnr;
}

zBOOL oCNpcInventory::SwitchToCategory( int nr )
{
	if ((nr < 0) || (nr > INV_MAX)) return FALSE;

	// Muss hier sein, weil invnr == -1 ???
	if ((invnr<0) || (invnr>=INV_MAX)) {
		invnr = 0;
	}

	int old = invnr;
	invnr	= nr;
	if (invnr!=old) {
		// Change Category - Save old Positions
		_offset[old] = offset;
		_itemnr[old] = selectedItem;
		// Load new Positions
		offset		 = _offset[invnr];
		selectedItem = _itemnr[invnr];
		// fixme
		SetContents  (&inventory[invnr]);
	}
	return (invnr!=old);
}

zBOOL oCNpcInventory::SwitchNextCategory()
{
	// [BENDLIN]
	return TRUE;

	int next = GetNextCategory();
	return SwitchToCategory(next);
}

zBOOL oCNpcInventory::SwitchPrevCategory()
{
	// [BENDLIN]
	return TRUE;

	int prev = GetPrevCategory();
	return SwitchToCategory(prev);
}

zBOOL oCNpcInventory::FindNextCategory()
{
	// In nächste nicht leere Kategorie wechseln,
	// falls die aktuelle leer ist
	//changed[dennis]
	return TRUE;
};
*/

// **********************************************************************************
// Draw
// **********************************************************************************

// Präfix für SelfPlayer
zSTRING _GetCategorySelfPlayerPrefix()
{
	static zSTRING CategoryPrefix = zSTRING("");
	if (CategoryPrefix.IsEmpty())
	{
		zCPar_Symbol* pSymbol = ::parser.GetSymbol(zSTRING("NAME_Currency"));
		if (pSymbol)
			pSymbol->GetValue(CategoryPrefix);
		if (CategoryPrefix.IsEmpty())
			CategoryPrefix = zSTRING("Gold: ");
	}
	return CategoryPrefix;
}

void oCNpcInventory::DrawCategory()
{	
	// [BENDLIN]
	// if (!GetEnableHandleEvent()) return;

	if (owner && owner->IsSelfPlayer())
	{
		zSTRING name = _GetCategorySelfPlayerPrefix() + zSTRING(this->GetAmount(GetCurrencyInstance()));
		this->SetName(name);
	}

	oCItemContainer::DrawCategory();
}

// **********************************************************************************
// Handeln - EventHandler
// **********************************************************************************
		
zBOOL oCNpcInventory::HandleTrade( int key )
{
	zERR_FATAL( "oCNpcInventory::HandleTrade() has been called although it is obsolete!" );

	oCNpc* other = owner->GetFocusNpc();

	if ((!other) || (zinput->IsBinded(GAME_RIGHT,key) || zinput->IsBinded(GAME_STRAFERIGHT,key))) {
		// **************************
		// Rechts - Handel abbrechen
		// **************************
		// Check, ob Angebot interessant ist
		if (other) other -> CloseTradeContainer();
		owner -> CloseTradeContainer();		
		return TRUE;
	
	} else if (zinput->IsBinded(GAME_LEFT,key) || zinput->IsBinded(GAME_STRAFELEFT,key)) {
		// ****************************
		// Links - Neues Item anbieten
		// ****************************
		// Falls ein NSC im Fokus ist, itemReactModule aktivieren
		owner -> OpenTradeContainer(GetSelectedItem(), other, owner->IsAPlayer() ? 1 : GetSelectedItem()->GetAmount() );
		// Passendes Gegenangebot suchen und anzeigen
		if (other && (other->GetPerceptionFunc (NPC_PERC_ASSESSGIVENITEM)>0)) {

			other -> OpenTradeOffer (owner);								
		}
		return TRUE;
		
	} else if (key & KEY_RELEASE) {

		key -= KEY_RELEASE;
		if (zinput->IsBinded(GAME_ACTION,key)) {
			// **********************************************
			// Action Taste losgelassen - Handel durchführen
			// **********************************************
			// Check, ob Angebot interessant ist
			other = owner -> GetFocusNpc();
			if (other && (other->GetPerceptionFunc (NPC_PERC_ASSESSGIVENITEM)>0)) {
				// AssessGivenItem aktivieren
				oCItem* trade  = owner->GetTradeItem();
				other -> AssessGivenItem(trade,owner);
			} else {
				owner -> CloseTradeContainer();
			}
		}
		return TRUE;
	}

	return TRUE;
};

// **********************************************************************************
// Inventory - EventHandler
// **********************************************************************************

// [Bendlin] alte Implementation

/*
zBOOL oCNpcInventory::HandleEvent( int key )
{
	if (!IsActive()) return FALSE;
	if (!owner->GetEM()->IsEmpty(TRUE)) return FALSE;
	
	// Nichts machen, wenn ItemInteraction läuft
	if (owner->GetInteractItemCurrentState() != -1) return FALSE;

	// Release Message ?
//	if (owner->trader && owner->trader->IsOpen()) {
//		// Trading
//		return HandleTrade( key );
//	}
		
	// Action nicht erlaubt, wenn in Mob-Interaction
	zBOOL actionOK	= (owner->GetInteractMob()==NULL);
	zBOOL leave		= FALSE;

	if (!m_bManipulateItemsDisabled)
	{
		if( (key >= KEY_4 && key <= KEY_9) || key == KEY_0 )
		{
			key = GetCharFromDIK(key,0);
			if( key == 0x30) key = 58;
			if( owner->GetSpellBook() ) 
			{
				int no;
				if( owner->GetSpellBook()->GetSpell(GetSelectedItem(), no) )
				{
					if( key-51 == owner->GetSpellBook()->GetSpell(GetSelectedItem(), no)->keyNo )
					{
						oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM,GetSelectedItem());
						owner->GetEM()->OnMessage(msg,GetSelectedItem());
					}
					else
					{
						if( !(invnr == INV_RUNE) ) return FALSE;
						// Equip Item
						if(owner->GetSpellBook()->GetSpellByKey(key-51))
						{
							owner->UnequipItem(owner->GetSpellBook()->GetSpellItemByKey(key-51));
							owner->GetSpellBook()->DeRegister(owner->GetSpellBook()->GetSpellItemByKey(key-51));
						}
						owner->UnequipItem(GetSelectedItem());
						owner->GetSpellBook()->DeRegister(GetSelectedItem());
						owner->GetSpellBook()->NextRegisterAt(key-51);
						oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM,GetSelectedItem());
						owner->GetEM()->OnMessage(msg,GetSelectedItem());
					}
				}
				else
				{
					// Equip Item
					if( owner->GetSpellBook()->GetSpellByKey(key-51) )
					{
						owner->UnequipItem(owner->GetSpellBook()->GetSpellItemByKey(key-51));
						owner->GetSpellBook()->DeRegister(owner->GetSpellBook()->GetSpellItemByKey(key-51));
					}
					if( !(invnr == INV_RUNE) ) return FALSE;
					owner->GetSpellBook()->NextRegisterAt(key-51);
					oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM,GetSelectedItem());
					owner->GetEM()->OnMessage(msg,GetSelectedItem());
				}
			}
		}	

		if (zinput->IsBinded(GAME_DOWN,key)) 
		{
			if (zinput->GetState(GAME_ACTION)) 
			{
				//changed [dennis]
				if (zinput->GetState(GAME_ACTION) && actionOK) {	
					oCItem* item = GetSelectedItem();
					if (item) {
						owner->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_DROPVOB,item),owner);
						FindNextCategory();
					};
				} else {	
					NextItem();
				}
				return TRUE;
			}
		}

	}

	if (zinput->IsBinded(GAME_LEFT,key) || zinput->IsBinded(GAME_STRAFELEFT,key)) 
	{
		if (zinput->GetState(GAME_ACTION)) 
		{
			oCItem* pItem = GetSelectedItem();
			if ( pItem )
			{
				if (GetNextContainerLeft(this)) 
				{
					oCStealContainer *cont = (dynamic_cast<oCStealContainer*>(GetNextContainerLeft(this)));
					if( pItem->HasFlag(ITM_FLAG_ACTIVE)) return FALSE;
					if( cont ) if( cont->GetOwner()->IsDead() ) return FALSE;
					// Falls links ein Container ist, Item transferieren
					
					//--------- PATCH2 - changed by Bert ------- TRansfer von 100 Items --------------------
					int amount=1;
					if (zinput->KeyPressed(KEY_LSHIFT) || zinput->KeyPressed(KEY_RSHIFT)) amount=100;
					else if (zinput->IsBinded(GAME_STRAFELEFT,key) || zinput->GetState(GAME_SMOVE)) amount=10;								
					TransferItem(-1,amount);
					//----------------------------------------------------------------------------------------

//										zBOOL transferMore = zinput->IsBinded(GAME_STRAFELEFT,key) || zinput->GetState(GAME_SMOVE);
//					TransferItem(-1,transferMore?10:1);
					FindNextCategory();
				}
				//
				//	CODECHANGE [ROMAN]	-	ITEMREACT-MODULE SIND PASSEE, DAS ERLEDIGT JETZT DER INFO-MANAGER
				//

//				else if (owner->GetFocusNpc()) 
//				{
//					// Falls ein NSC im Fokus ist, itemReactModule aktivieren
//					owner -> OpenTradeContainer(GetSelectedItem(), owner->GetFocusNpc(), owner->IsAPlayer() ? 1 : GetSelectedItem()->GetAmount() );
//					// Passendes Gegenangebot suchen und anzeigen
//					oCNpc* other = owner->GetFocusNpc ();
//					if (other) other -> OpenTradeOffer (owner);								
//				}

				//
				//	CODECHANGE [ROMAN]	-	END
				//
			}
		}
		else 
		{
			// 1. Versuche Kategory zu wechseln
			if (!SwitchPrevCategory()) 
				// 2. Wenn nicht, dann versuche Container zu wechseln
				ActivateNextContainer(-1);
		}
		return TRUE;
	
	} 
	else if (zinput->IsBinded(GAME_RIGHT,key) || zinput->IsBinded(GAME_STRAFERIGHT,key)) 
	{
		if (zinput->GetState(GAME_ACTION) && !m_bManipulateItemsDisabled) 
		{
			oCItem* item = GetSelectedItem();
			if( item ) if( item->HasFlag(ITM_FLAG_THROW ))
			{
                if( owner->HasTorch() ) 
				{
					owner->SetTorchAni( FALSE );
					owner->SetRightHand(owner->RemoveFromSlot(NPC_NODE_LEFTHAND,TRUE));
					return TRUE;
				}
				oCItem* newItem;
                zADDREF_ACCT(item);
				if(item->HasFlag(ITM_FLAG_TORCH) && (item->GetName() != zSTRING("ITLSTORCHBURNING")))
				{
					if (!owner->HasTorch()) 
					{
						newItem = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,"ITLSTORCHBURNING");
					
						// Und AI aktivieren
						oCAIVobMove* ai = newItem -> GetAIVobMove();
						if (ai) ai->Init(newItem,owner,newItem->GetPositionWorld());
						owner->RemoveFromInv(item->GetInstance(),1);
					}
					
				}
				else newItem = owner->RemoveFromInv(item->GetInstance(),1);
				
				// [Ulf] : Achtung, Item kann sich hier aendern und dann ist das Release falsch
				// darum temporaeres "newItem"
				owner->SetRightHand( newItem );
                
				zRELEASE_ACCT_NONULL(item);
				Close();
			}
		}
		else
		{	
			SwitchNextCategory();	
			return TRUE;
		}
		return FALSE;
	} 
	else if (zinput->IsBinded(GAME_UP,key) || (key==MOUSE_WHEELUP)) 
	{
		
		if (!m_bManipulateItemsDisabled && zinput->GetState(GAME_ACTION) && actionOK) 
		{	
			// Equip
			oCItem* item = GetSelectedItem();
			if (!item) return TRUE;
			
			// ****************************
			// 1) Check auf MobInteraction
			// ****************************
			oCMobInter*	mob	 = dynamic_cast<oCMobInter*>(owner->GetFocusVob());
			if (mob && (mob->GetUseWithItem()==item->GetInstance())) 
			{
				owner->SetInteractItem(item);
				leave = TRUE;
				goto _leaver;

			} 
			else if (!item->GetSchemeName().IsEmpty()) 
			{
				// ****************************
				// 2) Check auf ItemInteraction
				// ****************************
				oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_USEITEMTOSTATE,item,owner->GetInteractItemCurrentState()+1);
				owner->GetEM()->OnMessage(msg,item);
			
			} 
			else 
			{
				// ****************************
				// 3) Item anlegen
				// ****************************
				oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM,item);
				owner->GetEM()->OnMessage(msg,item);			
			}
			FindNextCategory();
		
		} 
		else 
		{
			PrevItem();
		}
		return TRUE;
	
	} 
	else if (zinput->IsBinded(GAME_DOWN,key) || (key==MOUSE_WHEELDOWN)) 
	{
		NextItem();
		return TRUE;

	}
	else if (zinput->IsBinded(GAME_WEAPON,key)) 
	{
		if (owner==oCNpc::player) owner->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON),owner);
		leave = TRUE;
	
	} 
	else if (zinput->IsBinded(GAME_END,key) || zinput->IsBinded(GAME_INVENTORY,key) || zinput->GetMouseButtonPressedRight()) 
	{
		leave = TRUE;
	}

_leaver:
	if (leave) {
		owner->CloseInventory();
		if (oCNpc::game_mode == NPC_GAME_PLUNDER)	owner->CloseDeadNpc();
		if (oCNpc::game_mode == NPC_GAME_STEAL)	owner->CloseSteal();
		// Möglichen Container links auch schliessen ( Truhe offen )
		if (GetNextContainerLeft(this)) GetNextContainerLeft(this)->Close();
		return TRUE;
	}

	return FALSE;
} 
*/

////////////////////////////////////////////////////////////////////////////////
//
//	oCNpcInventory::HandleEvent()
//
//	24.08.2000	[Moos]	
//
//				auf zNEW umgestellt
//
//	2002-05-12	[BENDLIN]
//	
//				Inventory, Auto-Toggle entfernt
//				Inventory, RMT zum Schließen deaktiviert
//				Neues Interface: (Aktionen in dieser Reihenfolge!)
//				* nur eigenes Inventory offen
//					GAME_ACTION					= Item Equip/Unequip	( + MOUSE_BUTTONLEFT	)
//					GAME_SMOVE					= Item ablegen			( + ???					)
//				* Tranfer-Modi (anderes Inventory links offen)
//					GAME_ACTION / GAME_SMOVE	= Transfer Item			( + MOUSE_BUTTONLEFT	)
//				* alle Modi
//					GAME_UP						= Auswahl nach oben		( + MOUSE_WHEELUP		)
//					GAME_DOWN					= Auswahl nach unten	( + MOUSE_WHEELDOWN		)
//					GAME_END / GAME_INVENTORY	= Abbruch				( + MOUSE_BUTTON_RIGHT	)
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCNpcInventory::HandleEvent( int key )
{
	if ( !IsActive() ) return FALSE;
	if ( !owner->GetEM()->IsEmpty(TRUE) ) return FALSE;
	
	// Nichts machen, wenn ItemInteraction läuft
	if ( owner->GetInteractItemCurrentState() != -1 ) return FALSE;

	zBOOL toggled = FALSE;
	// Transfer-Anzahl initialisieren
	if ( zinput->IsBindedToggled(GAME_ACTION, key) ||
		((key == MOUSE_BUTTONLEFT) && zinput->KeyToggled(MOUSE_BUTTONLEFT)) )
	{
		toggled = TRUE;
		SetTransferCount(0);
	}
	
	zINT transferAmount = TransferCountToAmount(GetTransferCount());

	// DROP-Transfer
	if ( zinput->IsBinded(GAME_SMOVE, key) )
	{
		toggled = zinput->GetToggled(GAME_SMOVE);
		SetTransferCount(0);

		oCItem* selItem = GetSelectedItem();
		if ( selItem ) if ( transferAmount < selItem->GetAmount() ) transferAmount = selItem->GetAmount();
	}
	
	// Action nicht erlaubt, wenn in Mob-Interaction
	zBOOL actionOK	= ( owner->GetInteractMob()==NULL );
	zBOOL leave		= FALSE;

	// Item-Manipulation möglich (nur eigenes Inventory offen)
	if (!m_bManipulateItemsDisabled)
	{
		// Tastenkürzel für Magie (4-0)
		if ( (key >= KEY_4 && key <= KEY_9) || key == KEY_0 )
		{
			// [BENDLIN] man sollte keine lokalen Varibalen ändern,
			// wenn sie später verwendet werden könnten... no comment
			int magkey = GetCharFromDIK((unsigned char)(key), 0, 0);
			if ( magkey == 0x30) magkey = 58;  // '0' -> ':' (one after '9')
			if ( owner->GetSpellBook() ) 
			{
				int no;
				if ( owner->GetSpellBook()->GetSpell(GetSelectedItem(), no) )
				{
					// magkey - "3"
					if ( magkey - 51 == owner->GetSpellBook()->GetSpell(GetSelectedItem(), no)->keyNo )
					{
						oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM, GetSelectedItem());
						owner->GetEM()->OnMessage(msg, GetSelectedItem());
					}
					else
					{
						if ( GetCategory(GetSelectedItem()) != INV_RUNE ) return FALSE;
						// Equip Item
						if ( owner->GetSpellBook()->GetSpellByKey(magkey - 51) )
						{
							owner->UnequipItem(owner->GetSpellBook()->GetSpellItemByKey(magkey - 51));
							owner->GetSpellBook()->DeRegister(owner->GetSpellBook()->GetSpellItemByKey(magkey - 51));
						}
						owner->UnequipItem(GetSelectedItem());
						owner->GetSpellBook()->DeRegister(GetSelectedItem());
						owner->GetSpellBook()->NextRegisterAt(magkey - 51);
						oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM, GetSelectedItem());
						owner->GetEM()->OnMessage(msg, GetSelectedItem());
					}
				}
				else
				{
					// Equip Item
					if( owner->GetSpellBook()->GetSpellByKey(magkey - 51) )
					{
						owner->UnequipItem(owner->GetSpellBook()->GetSpellItemByKey(magkey - 51));
						owner->GetSpellBook()->DeRegister(owner->GetSpellBook()->GetSpellItemByKey(magkey - 51));
					}
					if ( GetCategory(GetSelectedItem()) != INV_RUNE ) return FALSE;
					owner->GetSpellBook()->NextRegisterAt(magkey - 51);
					oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM, GetSelectedItem());
					owner->GetEM()->OnMessage(msg, GetSelectedItem());
				}
			}
		}	

		// DROP (immer einen kompletten Stapel !!!) [ganz abschaffen ?]
		if ( zinput->IsBinded(GAME_SMOVE, key) && !GetNextContainerLeft(this) ) // && toggled )
		{
			oCItem* item = GetSelectedItem();
			if (item)
			{ 
				// [BENDLIN] Addon - CrashFix SplitSlot-Drop
				if (item->HasFlag(ITM_FLAG_ACTIVE) && item->SplitSlot())
					owner->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM, item), owner);
				else
					owner->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_DROPVOB, item), owner);
			}
			return TRUE;
		}

	}

	// ein nicht aktiver Container verfuegbar?
	zBOOL bNextContainer = FALSE;
	oCItemContainer* cont = GetNextContainerLeft(this);
	if (!cont)
		cont = GetNextContainerRight(this);
	if (cont)
		bNextContainer = cont->IsOpen() && !cont->IsPassive();
	// GAME_INVENTORY toggled
	zBOOL bInventoryToggled = zinput->IsBindedToggled(GAME_INVENTORY, key);

	oCItem* item = GetSelectedItem();
	if ( item )
	{
		// ACTION //
		if ( zinput->IsBinded(GAME_ACTION, key) || zinput->IsBinded(GAME_SMOVE, key) || (key == MOUSE_BUTTONLEFT) )
		{
			////////////////////////////
			// ACTION - TRANSFER LEFT //
			////////////////////////////
			if ( GetNextContainerLeft(this) )
			{
				oCStealContainer *cont = (dynamic_cast<oCStealContainer*>(GetNextContainerLeft(this)));
				// aktive Items werden nicht transferiert!
				if ( item->HasFlag(ITM_FLAG_ACTIVE) ) return TRUE;
				// auch nicht an Tote =)
				if ( cont ) if ( cont->GetOwner()->IsDead() ) return TRUE;

				// wenn es das/die letzte(n) Item(s) ist/sind
				if ( transferAmount >= item->GetAmount() )
				{
					transferAmount = item->GetAmount();
					SetTransferCount(0);  // da letzte Aktion
				}
				else
				{
					// internen Zähler hochsetzen
					IncTransferCount(transferAmount);
				}
				// Transferieren
				TransferItem(-1, transferAmount);
//				FindNextCategory();
			}
			/////////////////////////////
			// ACTION - TRANSFER RIGHT // what for ?
			/////////////////////////////
			else if ( GetNextContainerRight(this) )
			{
				if ( !m_bManipulateItemsDisabled && item->HasFlag(ITM_FLAG_THROW) )
				{
					if( owner->HasTorch() ) 
					{
						owner->SetTorchAni(FALSE);
						owner->SetRightHand(owner->RemoveFromSlot(NPC_NODE_LEFTHAND, TRUE));
						return TRUE;
					}
					
					oCItem* newItem;
					zADDREF_ACCT(item);
					if( item->HasFlag(ITM_FLAG_TORCH) && (item->GetName() != zSTRING("ITLSTORCHBURNING")) )
					{
						if ( !owner->HasTorch() ) 
						{
							newItem = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, "ITLSTORCHBURNING");
							// Und AI aktivieren
							oCAIVobMove* ai = newItem->GetAIVobMove();
							if ( ai ) ai->Init(newItem, owner, newItem->GetPositionWorld());
							owner->RemoveFromInv(item->GetInstance(), 1);
						}
					}
					else newItem = owner->RemoveFromInv(item->GetInstance(), 1);
					// [Ulf] : Achtung, Item kann sich hier aendern und dann ist das Release falsch
					// darum temporaeres "newItem"
					owner->SetRightHand(newItem);
					zRELEASE_ACCT_NONULL(item);
					Close();
				}
			}
			////////////////////
			// ACTION - EQUIP //
			////////////////////
			else if ( !m_bManipulateItemsDisabled && actionOK && toggled )
			{	
				// 1) Check auf MobInteraction
				// [BENDLIN] Addon
				// Nur noch bei NPCs, sonst wird dem Spieler ein Interact-Item in die Hand gelogen,
				// wenn dieser mit offenem Inventar, mit Mobsi im Fokus das richtige Item anklickt.
				// (danach hat der Spieler nach Benutzung des Mobsis die doppelte Anzahl...)
				oCMobInter*	mob	 = dynamic_cast<oCMobInter*>(owner->GetFocusVob());
				if ( !owner->IsSelfPlayer() && mob && (mob->GetUseWithItem() == item->GetInstance()) )
				{
					owner->SetInteractItem(item);
					leave = TRUE;
					goto _leaver;
				}
				// 2) Check auf ItemInteraction
				else if ( !item->GetSchemeName().IsEmpty() )
				{
					oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_USEITEMTOSTATE, item, owner->GetInteractItemCurrentState() + 1);
					owner->GetEM()->OnMessage(msg, item);
				}
				// 3) Item anlegen
				else 
				{
					oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_EQUIPITEM, item);
					owner->GetEM()->OnMessage(msg, item);
				}
//				FindNextCategory();
			}
			// ACTION behandelt
			return TRUE;
		}
	}

	//Schliessen mit GAME_END und GAME_INVENTORY (nur wenn kein anderes Inventory)
	if ( zinput->IsBindedToggled(GAME_END, key) ||
		(bInventoryToggled && (!bNextContainer || IsSplitScreen())) ||
		(key == MOUSE_BUTTONRIGHT && zinput->KeyToggled(MOUSE_BUTTONRIGHT)) )
	{
		leave = TRUE;
	}
	// anderer Container rechts?
	else if ( bInventoryToggled && bNextContainer && !IsSplitScreen())
	{
		if (ActivateNextContainer(+1))
			return TRUE;
		return ActivateNextContainer(-1);
	}	
	// Scrollen (nach links)
	else if ( zinput->IsBinded(GAME_LEFT, key) || zinput->IsBinded(GAME_STRAFELEFT, key) )
	{
		PrevItem();
		return TRUE;
	} 
	// Scrollen (nach oben)
	else if ( zinput->IsBinded(GAME_UP, key) || (key == MOUSE_WHEELUP) )
	{
		PrevItemLine();
		return TRUE;
	} 
	// Scrollen (nach unten)
	else if ( zinput->IsBinded(GAME_DOWN, key) || (key == MOUSE_WHEELDOWN) )
	{
		NextItemLine();
		return TRUE;
	} 
	// Scrollen (nach rechts)
	else if ( zinput->IsBinded(GAME_RIGHT, key) || zinput->IsBinded(GAME_STRAFERIGHT, key) )
	{
		NextItem();
		return TRUE;
	} 
	// WEAPON (toggle-check)
	else if ( zinput->IsBindedToggled(GAME_WEAPON, key) ) 
	{
		if ( owner == oCNpc::player ) owner->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON), owner);
		leave = TRUE;
	} 

_leaver:
	if (leave) {
		owner->CloseInventory();
		if (oCNpc::game_mode == NPC_GAME_PLUNDER) owner->CloseDeadNpc();
		if (oCNpc::game_mode == NPC_GAME_STEAL)	owner->CloseSteal();
		// Möglichen Container links auch schliessen ( Truhe offen )
		if (GetNextContainerLeft(this))
		{
			GetNextContainerLeft(this)->Close();
			
			// MobInter-States zurück
			oCMobInter* mob = dynamic_cast<oCMobInter*>(owner->GetInteractMob());
			if (mob)
			{
				oCMobMsg* msg = zNEW(oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE, owner));
				msg->from = mob->GetState();
				msg->to = msg->from - 1;
				mob->GetEM()->OnMessage(msg, owner);								
			}
		}
		return TRUE;
	}

	return FALSE;
} 

// **********************************************************************************
// Special Functions
// **********************************************************************************

void oCNpcInventory::CheckForEquippedItems(zBOOL ignoreArmor)
{
	int cat;
	// Activate Equipped Item -> Put in Slots
	zCListSort<oCItem>* node = inventory.GetNextInList();
	oCItem* item = NULL;
	while (node)
	{
		item	= node->GetData			();
		node	= node->GetNextInList	();
		cat		= GetCategory			(item);

		if (item->HasFlag(ITM_FLAG_ACTIVE))
		{
			// Armors können hier ignoriert werden, 
			// weil Armors sind zu diesem Zeitpunkt bereits angelegt 
			// (Parameter von SetAdditionalVisuals). 
			if ((cat==INV_ARMOR) && ignoreArmor) continue;
			
			item->ClearFlag	(ITM_FLAG_ACTIVE);
			if (item->HasFlag(ITM_CAT_NF))	owner -> EquipWeapon	( item ); else
			if (item->HasFlag(ITM_CAT_FF))	owner -> EquipFarWeapon	( item ); else
			if (cat==INV_ARMOR)				owner -> EquipArmor		( item ); else
			if (cat==INV_RUNE)				owner -> Equip			( item );
				
		}
	}
}

//changed [dennis]
zBOOL oCNpcInventory::CanCarry(oCItem* item)
{
	return ( GetNumItemsInCategory() < INV_MAX_ITEMS );
}

// *************************************************************************************
// Inventory Packing Klamotten
// *************************************************************************************

void oCNpcInventory :: SetPackAbility(zBOOL packingOn)
{
	if (!packingOn) {
		// Zur Sicherheit alles entpacken.
		this->UnpackAllItems();
	}
	packAbility = packingOn;	
};

// void oCNpcInventory :: UnpackCategory(int nCategory)
void oCNpcInventory :: UnpackCategory()
{
	if (!GetPackAbility())
		return;

	UnpackItemsInCategory();
};

// int oCNpcInventory :: GetNumItemsInPackString(int cat)
int oCNpcInventory :: GetNumItemsInPackString()
{
	if (!GetPackAbility()) return 0;
	int num = 0;
	for (int i=0; i<packString.Length(); i++) if (packString[i]==':') num++;
	return num;
}

zBOOL oCNpcInventory :: GetPackedItemBySlot(int slotNr, zSTRING& itemInstance)
// Beginnend bei 0
{
	int	pos		= 0;
	int endPos	= 0;

	if (slotNr>0) pos	= packString.Search(0,",",slotNr-1) + 1;
	endPos				= packString.Search(pos,":",1);
	itemInstance		= packString.Copied(pos,endPos-pos);

	// Patch 1.08 : Cut preceding ","
	while (itemInstance[0]==',') {
		itemInstance.Delete(0,1);
	}

	return !itemInstance.IsEmpty();
}

oCItem* oCNpcInventory :: CreateFromPackString(const zSTRING &name)
{	
	if (!GetPackAbility()) return NULL;
	
	int		amount;
	zBOOL	equipped;
	
	oCItem* item	= NULL;
	oCItem* tmpItem = NULL;
	if (GetPackedItemInfo(name,TRUE,amount,equipped))
	{
		tmpItem = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob( zVOB_TYPE_ITEM, name ));
		if (tmpItem)
		{
			tmpItem->SetAmount(amount);
			if (equipped)
			{
				//
				// [BENDLIN] Addon - SplitSlot FIXME
				//
				// ... keiner wusste hier weiter ...
				//
//				tmpItem->SetFlag(ITM_FLAG_ACTIVE);
			}
			// In Liste einfuegen....
			item = Insert(tmpItem);
		}
		zRELEASE(tmpItem);
	}
	return item;
}

zBOOL oCNpcInventory :: GetPackedItemInfo(const zSTRING &name, zBOOL destroyEntry, int& amount, zBOOL &equipped)
// IN	: Item Instance Name
// OUT	: Amount of Item.
// OUT  : Is item equipped.
// RET  : Item found.
{
	if (!GetPackAbility()) return FALSE;
	
	int posFound	= -1;
	int	posEnd		= -1;
	amount			= 0;
	equipped		= FALSE;

	zSTRING amountStr;

	// [BENDLIN] 2002-12-05 (1.29)
	if (!name.IsEmpty())
	{
		posFound = packString.Search(name + ":");
		
		// [BENDLIN] Addon
		// Diese Sicherheitsabfrage sorgte dafuer,
		// dass FOO in FOOBAR:1 gefunden wurde ...
		// Das endete mit einem neuen Item FOO:0 !
		// Deswegen wird die Abfrage jetzt genauer
		// und die Standardanzahl ist nun mind. 1.
/*
		// [BENDLIN] 1.30a - missing amount specifier prevents item to be found
		if (posFound < 0)
		  posFound = packString.Search(name);
*/
		// ... suche nach "FOO,"
		if (posFound < 0)
		  posFound = packString.Search(name + ",");
		// ... suche nach "FOO" am Ende
		if (posFound < 0)
		{
			posFound = packString.SearchRev(",");
			if (posFound >= 0)
				posFound = packString.Search(posFound + 1, name);
		}
		// ... oder einziger Eintrag
		if (posFound < 0)
		if (0 == packString.CompareTo(name))
			posFound = 0;
		
		if (posFound >= 0)
		{
			if ((packString[posFound-1] == ',')	||
				(posFound == 0)					||
				(posFound+name.Length() >= packString.Length()))
			{
				// Position des naechsten items suchen
				posEnd = packString.Search(posFound, ",", 1);
				if (posEnd<0)
					posEnd = packString.Length();
				// Okay, Item gefunden....	
				amountStr = packString.Copied(posFound + name.Length() + 1, posEnd - (posFound + name.Length() + 1));
				amount = amountStr.ToInt();
				// [BENDLIN] Addon
				// die Anzahl kann nicht kleiner oder gleich 0 sein!
				if (amount <= 0)
					amount = 1;
				equipped = amountStr.Search("E");
				// Eintrag zerstoeren
				if (destroyEntry)
				{
					// [BENDLIN] item am ende wird entfernt
					if ((posEnd == packString.Length())	&&
						(posFound > 0)					&&
						(packString[posFound - 1] == ','))
					{
						posFound--;
					}
					packString.Delete(posFound, posEnd - posFound + 1);
				}
				return TRUE;
			}
		}
	}
	return FALSE;
};

zBOOL oCNpcInventory :: PackSingleItem(oCItem* item)
// Packt uebergebenes Item in PackString
{
	if (!GetPackAbility())	return FALSE;
	if (!item)				return FALSE;

	int		amount		= 0;
	zBOOL	equipped	= FALSE;
	// Multi-Item noch im unsortierten String ?
	if (item->MultiSlot())
	{
		if (GetPackedItemInfo(item->GetInstanceName(),TRUE,amount,equipped))
			item->SetAmount(item->GetAmount()+amount);					
	}
	// Aus Inventory entfernen
	item = RemoveByPtr(item,item->GetAmount());
	// Und In entsprechende Kategorie packen
	// Item - InstanceName
	if ( !packString.IsEmpty() )
		packString += ",";
	packString += item->GetInstanceName()+":";
	// item - Amount
	packString += zSTRING(item->GetAmount());
	// item - Equipped ( only savegame )
	if (item->HasFlag(ITM_FLAG_ACTIVE)) {
		packString += "E";
	}
	// und aus Welt entfernen und zerstoeren
	ogame->GetWorld()->RemoveVob(item);
	return TRUE;
};

void oCNpcInventory :: PackAllItems(zBOOL packEquipped)
{
	PackItemsInCategory(packEquipped);
};

void oCNpcInventory :: UnpackAllItems()
{
	UnpackItemsInCategory();
};

// void oCNpcInventory :: PackItemsInCategory (int nCategory, zBOOL packEquipped)
void oCNpcInventory :: PackItemsInCategory (zBOOL packEquipped)
// FIXME : koennte noch effektiver gemacht werden.
{
	if (!GetPackAbility()) return;

	zSTRING newPackString;
	oCItem* item			= NULL;
			
	zCListSort<oCItem>* node = inventory.GetNextInList();
	while (node)
	{
		item = node->GetData();
		node = node->GetNextInList();

		if ( !item )
		{
			zERR_WARNING("N: PackItemsInCategory: invalid item (null) - npc:"+owner->GetInstanceName()+", packstring:"+packString);
		}
		else
		if (item) {
			
			// Equippte Items nicht entfernen.
			if (item->HasFlag(ITM_FLAG_ACTIVE)) {
				
				if (!packEquipped)
				{
					if ( !node && (newPackString.GetLastChar() == ',')  )
						newPackString.DeleteRight(1);
					continue;
				}
			}

			if ( item->GetInstanceName().IsEmpty() )
			{
				zERR_WARNING("N: PackItemsInCategory: empty item string - npc:"+owner->GetInstanceName()+", packstring:"+packString);
			}
			// Item - InstanceName
			newPackString += item->GetInstanceName()+":";
			
			// item - Amount
			if ( item->GetAmount() <= 0 )
			{
				zERR_WARNING("N: PackItemsInCategory: invalid item count - npc:"+owner->GetInstanceName()+", item:"+item->GetInstanceName()+", amount:"+item->GetAmount());
			}
			newPackString += zSTRING(item->GetAmount());
			
			// item - Equipped ( only savegame )
			if (item->HasFlag(ITM_FLAG_ACTIVE)) {
				newPackString += "E";
			}

			// Kommt da noch was ?
			if ( newPackString.GetLastChar() == ',' )
			{
				zERR_WARNING("N: PackItemsInCategory: invalid new packstring - npc:"+owner->GetInstanceName()+", packstring:"+newPackString);
			}
			else
			if (node) newPackString += ",";
			
			// Item aus Liste/Inventory entfernen		
			item = RemoveByPtr(item,item->GetAmount());
			// Item aus Welt entfernen (+zerstoeren)
			ogame->GetWorld()->RemoveVob(item);
		}
	}
	
	while ( packString.GetLastChar() == ',' )
	{
		zERR_WARNING("N: PackItemsInCategory: invalid pack string - npc:"+owner->GetInstanceName()+", packstring:"+packString);
		packString.DeleteRight(1);
	}
	if (!packString.IsEmpty() && !newPackString.IsEmpty()) packString += ",";
	packString += newPackString;
	// [BENDLIN] FIXME: endet schon mit ','
	if ( packString.Search(",,") >= 0 )
	{
		zERR_WARNING("N: PackItemsInCategory: invalid pack string - npc:"+owner->GetInstanceName()+", packstring:"+packString);
	}
	
//	zERR_MESSAGE(5,0,"U: INV: Packed category : "+packString[nCategory]);	
}

void oCNpcInventory :: UnpackItemsInCategory ()
{
	if (!GetPackAbility()) return;

	// Alles auspacken
	zSTRING itemName;
	zSTRING itemAmountStr;
	zBOOL	itemEquipped;
	int		itemAmount;
	int		posKomma;
	zSTRING curPackString	= packString;
	oCItem*	item			= NULL;
	
	while (!curPackString.IsEmpty()) {
		
		itemName		= curPackString.PickWord(1,":");
		itemAmountStr	= curPackString.PickWord(2,":,",":,");
		itemAmount		= itemAmountStr.ToInt();
		itemEquipped	= (itemAmountStr.Search("E")>=0);

		// [BENDLIN] FIXME: Itemname beginnt mit ','
		while ( itemName.Search(",") == 0 )
		{
			zERR_WARNING("N: UnpackItemsInCategory: invalid item instance name - npc:"+owner->GetName()+", name="+itemName);
			itemName.Delete(0, 1);
		};
		// [BENDLIN] FIXME: Itemname leer
		if ( itemName.IsEmpty() )
		{
			zERR_WARNING("N: UnpackItemsInCategory: empty item instance name - npc:"+owner->GetName());
		};

		// item erzeugen
		item			= static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob( zVOB_TYPE_ITEM, itemName ));
		if (item) {
			item	-> SetAmount(itemAmount);
			owner	-> PutInInv	(item);
			if (itemEquipped) owner->Equip(item);
		}
		zRELEASE(item);

		// und raus damit.
		posKomma = curPackString.Search(",");
		if (posKomma>=0)	curPackString.Delete(0,posKomma+1);
		else				curPackString.Clear();
	}

	packString.Clear();
}

