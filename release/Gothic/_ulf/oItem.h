/******************************************************************************** 
 
     $Workfile:: oItem.h              $                $Date:: 8.02.01 15:44    $
     $Revision:: 31                   $             $Modtime:: 8.02.01 15:20    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oItem.h $
 * 
 * 31    8.02.01 15:44 Wohlers
 * 
 * 30    27.01.01 19:42 Moos
 * 
 * 29    22.01.01 22:38 Wohlers
 * 
 * 28    19.01.01 16:18 Keskenti
 * 
 * 27    16.01.01 19:01 Wohlers
 * 
 * 26    15.01.01 17:32 Hildebrandt
 * 
 * 25    15.01.01 17:27 Hildebrandt
 * 
 * 24    8.01.01 21:13 Speckels
 * 
 * 23    30.11.00 14:06 Keskenti
 * 
 * 22    8.11.00 18:46 Keskenti
 * 
 * 21    2/11/00 16:39 Luesebrink
 * 
 * 20    31.10.00 20:27 Keskenti
 * 
 * 19    26/10/00 14:27 Luesebrink
 * 
 * 18    25/10/00 13:06 Luesebrink
 * 
 * 17    24.10.00 16:53 Moos
 * 
 * 16    20.10.00 16:41 Wohlers
 * 
 * 15    19.10.00 19:31 Keskenti
 * 
 * 14    6.10.00 13:38 Keskenti
 * 
 * 13    30/08/00 12:33 Luesebrink
 * 
 * 12    26/08/00 16:33 Luesebrink
 * 
 * 11    25.08.00 14:21 Wohlers
 * 
 * 10    24.08.00 18:27 Wohlers
 * 
 * 9     16.08.00 21:05 Keskenti
 * 
 * 8     4/08/00 13:44 Luesebrink
 * 
 * 7     27.07.00 15:29 Wohlers
 * 
 * 6     27.07.00 14:13 Wohlers
 * 
 * 5     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 4     8.05.00 19:31 Wohlers
 * Gothic 0.80 - Inventory
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 13    18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 12    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 11    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 10    24.02.00 23:32 Wohlers
 * Fixes
 * 
 * 9     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 8     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 7     20.12.99 17:44 Wohlers
 * uSrc V0.70
 * AI_UseItem / AniComb TakeItem etc...
 * 
 * 6     6.12.99 19:12 Wohlers
 * Waynet Erweiterungen I
 * 
 * 4     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef _OITEM_H_
#define _OITEM_H_

#include "oVob.h"

#include "zParser.h"
#include "zSTRING.h"
#include "zList.h"
#include "z3D.h"
#include "zViewBase.h"
#include "oDamage.h"

class oCWorld;
class oCVisualFX;

// Kategorien (mainflag)
const int ITM_CAT_NONE			= 1<<0;		// Sonstiges
const int ITM_CAT_NF			= 1<<1;		// Alle Nahkampfwaffen
const int ITM_CAT_FF			= 1<<2;		// Alle Fernkampfwaffen
const int ITM_CAT_MUN			= 1<<3;		// Jede Art von Munition
const int ITM_CAT_ARMOR			= 1<<4;		// Rüstungen und Schilde
const int ITM_CAT_FOOD			= 1<<5;		// Alle Nahrungsmittel
const int ITM_CAT_DOCS			= 1<<6;		// Alle Dokumente
const int ITM_CAT_POTION		= 1<<7;		// Alle Schlüssel
const int ITM_CAT_LIGHT			= 1<<8;		// Alle Lichtquellen
const int ITM_CAT_RUNE			= 1<<9;
const int ITM_CAT_MAGIC			= 1<<31;
// Waffen (flag)
const int ITM_FLAG_DAG			= 1<<13;	// Waffe wird wie ein Dolch behandelt
const int ITM_FLAG_SWD			= 1<<14;	// Waffe wird wie ein Schwert behandelt
const int ITM_FLAG_AXE			= 1<<15;	// Waffe wird wie eine Axt behandelt
const int ITM_FLAG_2HD_SWD		= 1<<16;	// Waffe wird wie ein Zweihänder behandelt
const int ITM_FLAG_2HD_AXE		= 1<<17;	// Waffe wird wie eine Streitaxt behandelt
const int ITM_FLAG_SHIELD		= 1<<18;	// Waffe wird wie ein Schild behandelt
const int ITM_FLAG_BOW			= 1<<19;	// Waffe wird wie ein Bogen behandelt
const int ITM_FLAG_CROSSBOW		= 1<<20;	// Waffe wird wie eine Armbrust behandelt
// Magie (flag)
const int ITM_FLAG_RING			= 1<<11;	// Ring
const int ITM_FLAG_AMULET		= 1<<22;	// Amulett
const int ITM_FLAG_BELT			= 1<<24;	// Guertel
// Flags (flag)
const int ITM_FLAG_DROPPED		= 1<<10;	// (intern) Dropped
const int ITM_FLAG_MI			= 1<<12;	// Missionsgegenstand	
const int ITM_FLAG_MULTI		= 1<<21;	// Multi-Item-Slot
const int ITM_FLAG_NFOCUS		= 1<<23;	// (intern) Item im Focus ignorieren ?
const int ITM_FLAG_CREATEAMMO	= 1<<25;	// Waffe erzeugt benötigte Ammo selbst (magisch)
const int ITM_FLAG_NSPLIT		= 1<<26;	// SplitSlot deaktiviert (Waffe als Interact-Item)
const int ITM_FLAG_DRINK		= 1<<27;	// ein Trank
const int ITM_FLAG_TORCH		= 1<<28;	// Wie eine fackel behandeln
const int ITM_FLAG_THROW		= 1<<29;	// Kann Gegenstand geworfen werden ?
const int ITM_FLAG_ACTIVE		= 1<<30;	// Item in Inventory aktiviert


// Koerperstellen, wo Gegenstaende getragen werden koennen
enum {	ITM_WEAR_NO				= 0			};		// Kann nicht getragen werden
enum {	ITM_WEAR_TORSO			= 1			};		// Oberkoerper
enum {	ITM_WEAR_HEAD			= 2			};		// Kopf
enum {	ITM_WEAR_LIGHT			= 8			};		// Sonderslot Lichtquelle = 8  = NPC_SLOT_LIGHT

// Amount of States (Item-Interaction) that are possible
enum {	ITM_STATE_MAX			= 4			};

enum {	ITM_TEXT_MAX			= 6			};

/*
typedef
enum {
	ITM_DAM_EDGE	= 0,
	ITM_DAM_BLUNT	= 1,
	ITM_DAM_POINT	= 2,
	ITM_DAM_FIRE	= 3,
	ITM_DAM_MAGIC	= 4,
	ITM_DAM_FLY		= 5,
	ITM_DAM_BARRIER	= 6,
	ITM_DAM_MAX		
} zTITEMDAMAGE;
*/

const int ITM_COND_MAX		= 3;

class oCItem : public oCVob {
	zCLASS_DECLARATION	(oCItem)

public:

	static	zBOOL	GetItemEffectsEnabled			()				{ return s_bItemEffectEnabled;	};
	static	void	SetItemEffectsEnabled			(const zBOOL b)	{ s_bItemEffectEnabled = b;		};
	static  zBOOL   s_bItemEffectEnabled;

	oCItem											();																		// Constructor Empty
	oCItem											(zSTRING &s,int anz = 1);												// Constructor
	oCItem											(int nr, int anz = 1);													// Constructor mit Parser Verweis auf Instanz

	virtual void			SetVisual				(zCVisual* v);
	void					CreateVisual			();

	void					Init					();																		
	void					InitByScript			(int nr, int anz = 1);													

	int						GetInstance				()																		{ return instanz; };
	zSTRING					GetInstanceName			();																		
	virtual zBOOL			GetScriptInstance		(zSTRING* &scriptInstanceName, int &scriptInstanceIndex);				// returns name/index, as available
	virtual zBOOL			SetByScriptInstance		(const zSTRING* scriptInstanceName, const int scriptInstanceIndex);		// use 'name' or 'index' exclusively, but not both

	// zCVob interface
	virtual zBOOL zCCFASTCALL  Render				(zTRenderContext &renderContext);		// TRUE=visible, FALSE=invisible	[HILDEBRANDT]
	
	zSTRING					GetName					(zBOOL identified = FALSE);												
	zSTRING					GetStatus				();																		
	zSTRING					GetVisualChange			();																		
	zSTRING					GetEffectName			();																		
	zSTRING					GetSchemeName			()																		{ return scemeName; };
	int						GetAmount				()																		{ return amount; };
	void					SetAmount				(int am)																{ amount = am; };
	void					ChangeAmount			(int delta)																{ amount += delta; };
																															
	oCItem*					SplitItem				(int amount);															
																															
	int						GetHealMode				(int &value);															
	int						GetValue				();																		
	int						GetWeight				();																		
																															
	int						GetFlags				()																		{ return flags; };
	zBOOL					HasFlag					(int nr);																
	void					ClearFlag				(int nr);																
	void					SetFlag					(int nr);																
	void					SetMainFlag				(int nr)																{ mainflag = nr; };
	int						GetMainFlag				()																		{ return mainflag; };
																															
	int						GetDisguiseGuild		();																		
																															
	zBOOL					MultiSlot				();																		
	zBOOL					SplitSlot				();																		
	void					Identify				();																		
	void					UseItem					();																		// Checke auf Parserfunktion
																															
	void					ShowItemInfo			(zBOOL right);															
			
	// Description
	zSTRING&				GetDescription			();
	zSTRING&				GetText					( int nIndex );
	int						GetCount				( int nIndex );

	// Weapons											
	void					CopyDamage				( oCItem* pOther			 );
	int						GetDamageByIndex		( oEDamageIndex nIndex		 );											
	int						GetDamageByType			( oEDamageType	dwDamageType );											
	int						GetDamageByMode			( oTDamageMode  dwDamageMode );											
	void					GetDamages				( zUINT32* aryDamages		 );
	int						GetFullDamage			();	
	oTDamageMode			GetDamageTypes			();																		
	zBOOL					HasDamageType			( oEDamageType  dwDamageType );											
	zBOOL					IsDeadly				();
	zBOOL					TwoHanded				();																		
	zBOOL					IsOneHandWeapon			();																		
																															
	// Protection																											
	int						GetProtectionByIndex	( oEDamageIndex nIndex			 );										
	int						GetProtectionByType		( oEDamageType	dwProtectionType );										
	int						GetProtectionByMode		( oTDamageMode	dwProtectionMode );										
	int						GetFullProtection		();																		
	int						GetWearType				()																		{ return wear; };
																															
	// Munitionskram																										
	int						GetMunitionInstance		()																		{ return munition; };
																															
	// Besitzer ?!																											
	zBOOL					IsOwned					(int instance, int guild);												
	zBOOL					IsOwnedByNpc			(int instance);															
	zBOOL					IsOwnedByGuild			(int guild);															
	int						AddManipulation			();																		
	void					SetManipulation			(int count)																{ c_manipulation = count; };
	int						GetStateEffectFunc		(int stateNr);															
																															
	virtual	oCAIVobMove*	GetAIVobMove			();																		
																															
	// Sound																												
	virtual oTSndMaterial	GetSoundMaterial		()																		{ return sndMat; };
	virtual void			GetSoundMaterial_AM		(zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2, int damage);
													
	// 3D - Funktions								
	void					RenderItem				(int xp, int yp );
	void					RenderItem				(zCWorld* i_wld, zCViewBase *viewport, zREAL addon = 0.0f );
	void					RotateForInventory		(int dir = 1 );
	void					RotateInInventory		();
	void					InsertEffect			();
	void					RemoveEffect			();
	oCVisualFX*				GetEffect				() const						{ return effectVob;	};
													
	// Archive / Unarchive							
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

	// Statics
	static void				SetLightingSwell		(zBOOL lightingSwellon);
	static zBOOL			GetLightingSwell		();
	static void				SetInventoryZBiasScale  (const zREAL a_fSc)														{ s_fGlobalItemZBiasScale = a_fSc;	};
	static zREAL			GetInventoryZBiasScale  ()																		{ return s_fGlobalItemZBiasScale;	};

protected:
	virtual void			ThisVobAddedToWorld		(zCWorld *homeWorld);													// called AFTER the actual addition
	virtual void			ThisVobRemovedFromWorld	(zCWorld *homeWorld);													// called BEFFORE the actual removal

	void					RenderItemPlaceCamera	(zCCamera* cam, zREAL selected);
	virtual					~oCItem					();
	
public:

	// PARSER ON
	struct { 
		//
		//	Für alle Items
		//
		int				idx;									//	Eindeutige ID
		zSTRING			name,nameID;							//	Name des Items		
		int				hitp,max_hitp;							//	Strukturpunkte
		int				mainflag,flags;								
		int				weight;									//	Gewicht
		int				value;									//	Wert des Items		
																	
		//															
		//	Für Waffen												
		//															
		oTDamageMode	damageTypes;							//	What Types of Damage
		int				damageTotal;							//	How much Damage alltogether		| these two are mutual exclusive
		int				damage			[ oEDamageIndex_MAX ];	//	How much Damage for each Type	| these two are mutual exclusive
																	
		//															
		//	Für Rüstungen											
		//															
		int				wear;									//	Gegenstand kann wo getragen werden ?
		int				protection		[ oEDamageIndex_MAX ];	//	
																	
		//															
		//	Für Nahrung												
		//															
		int				nutrition;								//	Heilwert der Nahrung
																	
		//															
		//	Bedingungen, damit Item benutzt werden kann				
		//															
		int				cond_atr		[ ITM_COND_MAX ];		//			
		int				cond_value		[ ITM_COND_MAX ];		//	
																	
		//															
		//	Veränderungen der Attribute, wenn Item benutzt wird		
		//															
		int				change_atr		[ ITM_COND_MAX ];		//	
		int				change_value	[ ITM_COND_MAX ];		//	
																	
		//															
		//	Parserfunktionen											
		//															
		int				magic;									//	Funktion zum "Magie-Header"
		int				on_equip;								//	
		int				on_unequip;								//	
		int				onState			[ ITM_STATE_MAX ];		//	StateEffect !
		int				owner;									//	Skriptinstanz
		int				ownerGuild;								//	gesamte Gilde
		int				disguiseGuild;							//	Zur Schau getragene Gilde durch Verkleidung
		zSTRING			file;									//	Die Grafikdatei
		zSTRING			visual_change;							//	
		zSTRING			effectName;
		int				visual_skin;							//	
		zSTRING			scemeName;								//	
		oTSndMaterial	sndMat;									//	
		int				munition;								//	MunitionInstance
																	
		//															
		//	Magie													
		//															
		int				spell;									//	type of spell
		int				range;									//	range of weapon
		int				mag_circle;								//	magic circle

		//
		//	Beschreibung
		//
		zSTRING			description		;
		zSTRING			text			[ ITM_TEXT_MAX ];
		int				count			[ ITM_TEXT_MAX ];

		// positionierung & orientierung im inventory
		int				inv_zbias;
		int				inv_rotx;
		int				inv_roty;
		int				inv_rotz;
		int				inv_animate;
	};															
	// PARSER OFF	

private:
	static zREAL		s_fGlobalItemZBiasScale;

	int					amount;									// Menge des Items
	int					instanz;								
	int					c_manipulation;							// Counter für Manipulationen
	zREAL				last_manipulation;						
	int					magic_value;							// zus. Magiewert des Items	
																
	oCVisualFX*			effectVob;									
																
	// Vars														
	oCItem*				next;									// next in list

	oCItem(const oCItem&);		    		// disable
	oCItem& operator=(const oCItem&);		// disable

};																

#endif