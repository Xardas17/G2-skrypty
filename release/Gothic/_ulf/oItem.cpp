/******************************************************************************** 
 
     $Workfile:: oItem.cpp            $                $Date:: 19.03.01 21:28   $
     $Revision:: 69                   $             $Modtime:: 19.03.01 21:19   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oItem.cpp $
 * 
 * 69    19.03.01 21:28 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 68    19.03.01 18:47 Edenfeld
 * Demo2 Crash Bugfix
 * 
 * 67    10.02.01 15:48 Moos
 * Visual-Lazy-Loading fix für die Fackel
 * 
 * 66    8.02.01 15:44 Wohlers
 * 
 * 65    7.02.01 20:55 Wohlers
 * 
 * 64    1.02.01 15:26 Wohlers
 * 
 * 63    31.01.01 20:46 Wohlers
 * 
 * 62    31.01.01 20:18 Wohlers
 * 
 * 61    30.01.01 15:35 Moos
 * 
 * 60    23.01.01 21:02 Wohlers
 * 
 * 59    22.01.01 22:38 Wohlers
 * 
 * 58    19.01.01 16:18 Keskenti
 * 
 * 57    19.01.01 1:05 Wohlers
 * 
 * 56    16.01.01 19:01 Wohlers
 * 
 * 55    15.01.01 17:27 Hildebrandt
 * 
 * 54    8.01.01 21:14 Speckels
 * 
 * 53    8.01.01 21:13 Speckels
 * 
 * 52    8.01.01 21:16 Wohlers
 * 
 * 51    8.01.01 16:20 Keskenti
 * 
 * 50    20.12.00 17:13 Moos
 * 
 * 49    17.11.00 16:52 Wohlers
 * 
 * 48    8.11.00 18:46 Keskenti
 * 
 * 47    2/11/00 16:39 Luesebrink
 * 
 * 46    31.10.00 20:27 Keskenti
 * 
 * 45    26.10.00 15:48 Wohlers
 * 
 * 44    26/10/00 14:27 Luesebrink
 * 
 * 43    25/10/00 13:06 Luesebrink
 * 
 * 42    23.10.00 19:57 Hildebrandt
 * 
 * 41    23.10.00 16:58 Moos
 * 
 * 40    23.10.00 13:10 Moos
 * 
 * 39    19.10.00 19:31 Keskenti
 * 
 * 38    9/10/00 19:18 Luesebrink
 * 
 * 37    5.10.00 18:05 Keskenti
 * 
 * 36    5.10.00 16:36 Speckels
 * 
 * 35    5.10.00 13:49 Speckels
 * 
 * 34    23.09.00 18:21 Keskenti
 * 
 * 33    23.09.00 18:14 Keskenti
 * 
 * 32    21.09.00 21:15 Wohlers
 * 
 * 31    19.09.00 19:00 Wohlers
 * 
 * 30    14.09.00 16:54 Wohlers
 * 
 * 29    7.09.00 14:28 Rueve
 * 
 * 28    31.08.00 19:19 Edenfeld
 * zCVob & zCParticleFX Memleak behoben
 * 
 * 27    30/08/00 12:33 Luesebrink
 * 
 * 26    25.08.00 14:21 Wohlers
 * 
 * 25    23.08.00 18:49 Wohlers
 * 
 * 24    22.08.00 14:42 Moos
 * 
 * 23    21.08.00 15:02 Moos
 * 
 * 22    21/08/00 14:45 Luesebrink
 * 
 * 21    18/08/00 16:53 Luesebrink
 * 
 * 20    17/08/00 13:55 Luesebrink
 * 
 * 19    15/08/00 17:49 Luesebrink
 * 
 * 18    14/08/00 15:37 Luesebrink
 * 
 * 17    9.08.00 12:53 Wohlers
 * 
 * 16    2.08.00 14:25 Wohlers
 * 
 * 15    31.07.00 22:28 Rueve
 * 
 * 14    28/07/00 17:17 Luesebrink
 * 
 * 13    27.07.00 15:29 Wohlers
 * 
 * 12    27.07.00 14:28 Wohlers
 * 
 * 11    21.07.00 15:34 Wohlers
 * 
 * 10    21.07.00 14:43 Wohlers
 * 
 * 9     5.07.00 12:21 Wohlers
 * 
 * 8     14.06.00 18:31 Wohlers
 * vobName = InstanzName
 * 
 * 7     13.06.00 22:24 Edenfeld
 * 
 * 6     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 10    11.05.00 2:41 Wohlers
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 5     8.05.00 19:31 Wohlers
 * Gothic 0.80 - Inventory
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 16    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 15    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 14    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 13    24.02.00 23:32 Wohlers
 * Fixes
 * 
 * 12    23.02.00 3:47 Wohlers
 * Fixes
 * 
 * 11    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 10    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 9     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 8     6.12.99 19:12 Wohlers
 * Waynet Erweiterungen I
 * 
 * 6     24.11.99 23:39 Wohlers
 * Release Phoenix 069b
 * Mobsi-Erweiterungen 
 * 
 * 5     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "zParser.h"
#include "zFile3d.h"
#include "z3D.h"
#include "zOption.h"
#include "zrenderer.h"
#include "zSky.h"
#include "zArchiver.h"
#include "zInput_Win32.h"
#include "zEventMan.h"
#include "zphysics.h"
#include "zprogmesh.h"
#include "zaccount.h"

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>


#include "oItem.h"
#include "oText.h"
#include "oWorld.h"
#include "ogame.h"
#include "oAIShoot.h"
#include "oVisFX.h"


//#pragma optimize( "", off )

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

// *************************************
// Inventory - Konstanten 
// Größe und Positionen ( in Pixel )
// *************************************

// Größe des Inventorys
const int INV_SIZEX					= 81;
const int INV_SIZEY					= 398;

// Größe des gerenderten Items
const int INV_RENDER_SIZEX			= 80;
const int INV_RENDER_SIZEY			= 66;

// Größe des aktiven Items
const int INV_RENDERACTIVE_SIZEX	= INV_RENDER_SIZEX;
const int INV_RENDERACTIVE_SIZEY	= INV_RENDER_SIZEY;

// Position der Kategorie
const int INV_CAT_POSX				= 7;
const int INV_CAT_POSY				= 8;

// Position des Item - Renderstartes
const int INV_RENDER_POSX			= 1;
const int INV_RENDER_POSY			= 65;

// Position des aktiven Item - Renderstartes
const int INV_RENDERACTIVE_POSX		= INV_RENDER_POSX;
const int INV_RENDERACTIVE_POSY		= INV_RENDER_POSY;

// Position der Pfeile
const int INV_UP_POSY				=  65;		// Y - Position Pfeil nach oben
const int INV_DOWN_POSY				= 370;		// Y - Position Pfeil nach unten

// Platz zwischen zwei Items
const int INV_RENDER_DELTAY			=   0;		// Abstand zwischen zwei Items

// !!! Konstanten muessen mit NPC_ATR übereinstimmen
const int HEAL_HIT	=	0;
const int HEAL_MANA =	2;
const int HEAL_MAD	=	4;

static zBOOL lightingSwell = TRUE;

static zCArray<int> gParserItemReferenceList(600);
static zBOOL		parserItemRefsDone = FALSE;

zREAL oCItem::s_fGlobalItemZBiasScale = 0;
zBOOL oCItem::s_bItemEffectEnabled	  = TRUE;

void oCItem :: SetLightingSwell(zBOOL lightingSwellon)
{	
	lightingSwell = lightingSwellon;
}

zBOOL oCItem :: GetLightingSwell()
{
	return lightingSwell;
};

oCItem :: oCItem()
{
	Init();
}

oCItem :: oCItem(zSTRING &s,int anz)
{
	Init();
	InitByScript (parser.GetIndex(s),anz);	
}

oCItem :: oCItem(int nr, int anz)
{
	Init();
	InitByScript(nr,anz);
}

oCItem :: ~oCItem ()
{
	// Moegliche Parser-Referenzen auf dieses Objetk aufloesen.
	RemoveEffect();
	parser.ResetWithVarReferenceList(gParserItemReferenceList,this);
	next = NULL;
}

void oCItem :: SetVisual	(zCVisual* v)
{
	oCVob :: SetVisual(v);
    SetCollisionClass (zCCollObjectPoint::S_GetCollObjClass()); // [Moos] 20.12.00 Anpassung an Vob-Änderung
};

void oCItem :: CreateVisual()
{
	if (!GetVisual()) {
		if (file.Search(".ZEN")<0) zCVob::SetVisual(file);
	}
};

void oCItem :: Init()
{
	// Clear Parser Vars
	memset (&idx, 0, (int)&amount- (int)&idx );
	
	instanz				= -1;
	mainflag			= -1;
	amount				= 1;								// Menge des Items
	c_manipulation		= 0;								// Counter für Manipulationen
	last_manipulation	= 0;				
	magic_value			= 0;								// zus. Magiewert des Items
	effectVob			= NULL;
	next				= NULL;
	description			= "";

	//	Clear Damages
	this->damageTypes = 0;
	this->damageTotal = 0;
	::memset( this->damage, 0, oEDamageIndex_MAX * sizeof( zUINT32) );

	//	Clear ItemInfo
	for( int nIndex = 0; nIndex < ITM_TEXT_MAX; nIndex++ )
	{
		text	[ nIndex ] = "";
		count	[ nIndex ] = 0;
	}
	
	disguiseGuild		= 0;

	SetVobType			(zVOB_TYPE_ITEM);
	//SetCollType			(zVOB_COLL_TYPE_SMALL_OBJECT);
    SetCollisionClass (zCCollObjectPoint::S_GetCollObjClass()); // [Moos] 20.12.00 Anpassung an Vob-Änderung

	inv_zbias			= 0;
	inv_rotx			= 0;
	inv_roty			= 0;
	inv_rotz			= 0;
	inv_animate			= 0;

	SetZBias(1);

	// *********************************************************************************
	// Parser Referenzen Tabelle aufbauen
	// *********************************************************************************

	if (!parserItemRefsDone) {
		parser.CreateVarReferenceList("C_ITEM",gParserItemReferenceList);
//		zERR_FAULT("U: ITM: Parser found "+zSTRING(gParserItemReferenceList.GetNumInList())+" C_ITEM Vars.");
		parserItemRefsDone = TRUE;
	}
};

static zBOOL s_LoadingGame=FALSE; // [Moos] Wird von Unarchive verwendet. Wenn jemandem etwas besseres einfällt, der virtuellen Funktion InitByScript diese Info zukommen zu lassen, bitte melden!

void oCItem :: InitByScript(int nr, int anz)
{
	// Check Class Size
	static int classindex = -1;
	if (classindex<0) {
		classindex = parser.GetIndex("C_ITEM");
		parser.CheckClassSize (classindex,(int)&amount - (int)&idx);
	}

	zSTRING f;

	instanz	= nr;
	
	parser.CreateInstance( nr, this );

	// OR flags, to add mainflag to flags-list
	flags  = flags | mainflag;
	amount = anz;

	//
	//	SET DAMAGES ACCORDING TO TYPES
	//
	if ( this->damage[0] != 0 ) 
	{
		zSTRING strMessage = zSTRING( "R: ITEM: item \""+this->name+"\" causes DAM_INDEX_BARRIER damage. Most likely it contains an assignment to DAMAGE instead of DAMAGETOTAL !!!" );
				
		zERR_WARNING( strMessage );
	}

	::ApplyDamages( this->damageTypes, this->damage, this->damageTotal );
	
	//
	// SET MESH
	//
	file.Upper();
	if (!file.IsEmpty()) {
		zSTRING visName = file;
		if (visName.Search(".ZEN")>0){
            // [Moos] In Savegames wird der komplette VobTree schon gespeichert. Also NICHT neu aufbauen!
            if (!s_LoadingGame){
      			// Kurz in Welt einfuegen
	    		SetVisual	(NULL);
		    	SetCollDet	(FALSE);
			    zoptions->ChangeDir(DIR_WORLD);
			    ogame->GetGameWorld() -> AddVob				(this);
    			this	  	-> SetPositionWorld				(0,0,0);
			    zCVob* vob  =  ogame->GetWorld()-> MergeVobSubtree(visName);
				if (vob)
				{
    				vob			-> SetCollDet					(FALSE);
    				vob			-> SetPositionWorld				(0,0,0);
    				this		-> SetTrafoObjToWorld			(vob->trafoObjToWorld);
					vob			-> AddRefVobSubtree				();
					ogame->GetWorld()-> zCWorld::RemoveVobSubtree	(vob);
					ogame->GetWorld()-> zCWorld::AddVobAsChild		(vob,this);			
					ogame->GetWorld()-> zCWorld::RemoveVobSubtree	(this);
				}
				else
				{
					zERR_WARNING("C: oCItem::InitByScript(): could not merge subtree for item " + name + " possible cause: visual " + visName + " does not exist or is corrupt!");
				}
            }
		} else {
			// [Wohlers] 07.02.01 - Das Visual noch nciht sofort verpassen, 
			// sondern erst beim Einfuegen in Welt (spart Speicher beim Inventory).
			// zCVob::SetVisual(visName); 
		}
	}
	SetVobType	(zVOB_TYPE_ITEM);

	int typ,ele;
	SetVobName	(parser.GetSymbolInfo(nr,typ,ele));

	//InsertEffect();

// [Moos] 29.1.2001 Mal sehen, was alles passiert, wenn das Item nicht sofort in die Welt gepackt wird. Eigentlich muss es da ja nicht rein....
//	ogame->GetGameWorld()->InsertVobInWorld(this);
}

zSTRING& oCItem::GetDescription()
{
	return this->description;
}

zSTRING& oCItem::GetText( int nIndex )
{
    static zSTRING empty("");
	if ( ( nIndex < 0 ) || ( nIndex >= ITM_TEXT_MAX ) ) return empty;
	return this->text[ nIndex ];
}

int oCItem::GetCount( int nIndex )
{
	if ( ( nIndex < 0 ) || ( nIndex >= ITM_TEXT_MAX ) ) return 0;
	return this->count[ nIndex ];
}

int oCItem :: GetHealMode( int &value )
{
	if (!HasFlag(ITM_CAT_FOOD)) return 10;

	if ((value = nutrition)>0) return HEAL_HIT;

	for (int i=0; i<3; i++) {
		if ((change_atr[i]==HEAL_HIT)	&& ((value = change_value[i])>0))	return HEAL_HIT;
		if ((change_atr[i]==HEAL_MANA)	&& ((value = change_value[i])>0))	return HEAL_MANA;
		if ((change_atr[i]==HEAL_MAD)	&& ((value = change_value[i])>0))	return HEAL_MAD;
	}
	return 10;
}	

int oCItem :: GetProtectionByIndex( oEDamageIndex nIndex )
{
	return protection[ nIndex ];
}

int oCItem :: GetProtectionByType( oEDamageType dwProtectionType )
{
	if ( ( dwProtectionType & oEDamageType_Barrier	) == oEDamageType_Barrier	) return this->GetProtectionByIndex( oEDamageIndex_Barrier	);
	if ( ( dwProtectionType & oEDamageType_Blunt	) == oEDamageType_Blunt		) return this->GetProtectionByIndex( oEDamageIndex_Blunt	);
	if ( ( dwProtectionType & oEDamageType_Edge		) == oEDamageType_Edge		) return this->GetProtectionByIndex( oEDamageIndex_Edge		);
	if ( ( dwProtectionType & oEDamageType_Fire		) == oEDamageType_Fire		) return this->GetProtectionByIndex( oEDamageIndex_Fire		);
	if ( ( dwProtectionType & oEDamageType_Fly		) == oEDamageType_Fly		) return this->GetProtectionByIndex( oEDamageIndex_Fly		);
	if ( ( dwProtectionType & oEDamageType_Magic	) == oEDamageType_Magic		) return this->GetProtectionByIndex( oEDamageIndex_Magic	);
	if ( ( dwProtectionType & oEDamageType_Point	) == oEDamageType_Point		) return this->GetProtectionByIndex( oEDamageIndex_Point	);
	if ( ( dwProtectionType & oEDamageType_Fall		) == oEDamageType_Fall		) return this->GetProtectionByIndex( oEDamageIndex_Fall		);

	return 0;
}

int oCItem :: GetProtectionByMode( oTDamageMode dwProtectionMode )
{
	int nProtectionTotal = 0;

	if ( ( dwProtectionMode & oEDamageType_Barrier	) == oEDamageType_Barrier	) nProtectionTotal +=  this->GetProtectionByIndex( oEDamageIndex_Barrier	);
	if ( ( dwProtectionMode & oEDamageType_Blunt	) == oEDamageType_Blunt		) nProtectionTotal +=  this->GetProtectionByIndex( oEDamageIndex_Blunt		);
	if ( ( dwProtectionMode & oEDamageType_Edge		) == oEDamageType_Edge		) nProtectionTotal +=  this->GetProtectionByIndex( oEDamageIndex_Edge		);
	if ( ( dwProtectionMode & oEDamageType_Fire		) == oEDamageType_Fire		) nProtectionTotal +=  this->GetProtectionByIndex( oEDamageIndex_Fire		);
	if ( ( dwProtectionMode & oEDamageType_Fly		) == oEDamageType_Fly		) nProtectionTotal +=  this->GetProtectionByIndex( oEDamageIndex_Fly		);
	if ( ( dwProtectionMode & oEDamageType_Magic	) == oEDamageType_Magic		) nProtectionTotal +=  this->GetProtectionByIndex( oEDamageIndex_Magic		);
	if ( ( dwProtectionMode & oEDamageType_Point	) == oEDamageType_Point		) nProtectionTotal +=  this->GetProtectionByIndex( oEDamageIndex_Point		);
	if ( ( dwProtectionMode & oEDamageType_Fall		) == oEDamageType_Fall		) nProtectionTotal +=  this->GetProtectionByIndex( oEDamageIndex_Fall		);

	return nProtectionTotal;
}

int oCItem :: GetFullProtection()
{
	int nProtectionTotal = 0;

	for ( zDWORD nIndex = 0; nIndex < oEDamageIndex_MAX; nIndex ++ ) 
		nProtectionTotal += this->GetProtectionByIndex( (oEDamageIndex) nIndex );

	return nProtectionTotal;
}

void oCItem :: CopyDamage( oCItem* pOther )
{
	if ( ! pOther ) return;

	pOther->damageTypes = this->damageTypes;
	pOther->damageTotal = this->damageTotal;

	::memcpy( pOther->damage, this->damage, sizeof( this->damage ) );
}

int oCItem :: GetDamageByIndex( oEDamageIndex nIndex )
{
	return damage[ nIndex ];
}

int oCItem :: GetDamageByType( oEDamageType dwDamageType )
{
	if ( ( dwDamageType & oEDamageType_Barrier	) == oEDamageType_Barrier	) return this->GetDamageByIndex( oEDamageIndex_Barrier	);
	if ( ( dwDamageType & oEDamageType_Blunt	) == oEDamageType_Blunt		) return this->GetDamageByIndex( oEDamageIndex_Blunt	);
	if ( ( dwDamageType & oEDamageType_Edge		) == oEDamageType_Edge		) return this->GetDamageByIndex( oEDamageIndex_Edge		);
	if ( ( dwDamageType & oEDamageType_Fire		) == oEDamageType_Fire		) return this->GetDamageByIndex( oEDamageIndex_Fire		);
	if ( ( dwDamageType & oEDamageType_Fly		) == oEDamageType_Fly		) return this->GetDamageByIndex( oEDamageIndex_Fly		);
	if ( ( dwDamageType & oEDamageType_Magic	) == oEDamageType_Magic		) return this->GetDamageByIndex( oEDamageIndex_Magic	);
	if ( ( dwDamageType & oEDamageType_Point	) == oEDamageType_Point		) return this->GetDamageByIndex( oEDamageIndex_Point	);
	if ( ( dwDamageType & oEDamageType_Fall		) == oEDamageType_Fall		) return this->GetDamageByIndex( oEDamageIndex_Fall		);

	return 0;
}

int oCItem :: GetDamageByMode( oTDamageMode dwDamageMode )
{
	int nDamageTotal = 0;

	if ( ( dwDamageMode & oEDamageType_Barrier	) == oEDamageType_Barrier	) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Barrier	);
	if ( ( dwDamageMode & oEDamageType_Blunt	) == oEDamageType_Blunt		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Blunt	);
	if ( ( dwDamageMode & oEDamageType_Edge		) == oEDamageType_Edge		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Edge	);
	if ( ( dwDamageMode & oEDamageType_Fire		) == oEDamageType_Fire		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Fire	);
	if ( ( dwDamageMode & oEDamageType_Fly		) == oEDamageType_Fly		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Fly		);
	if ( ( dwDamageMode & oEDamageType_Magic	) == oEDamageType_Magic		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Magic	);
	if ( ( dwDamageMode & oEDamageType_Point	) == oEDamageType_Point		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Point	);
	if ( ( dwDamageMode & oEDamageType_Fall		) == oEDamageType_Fall		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Fall	);

	return nDamageTotal; 
}

void oCItem :: GetDamages( zUINT32* aryDamages )
{
	if ( ! aryDamages ) return;

	::memcpy( aryDamages, this->damage, oEDamageIndex_MAX * sizeof(zUINT32) );
}

int oCItem :: GetFullDamage()
{
	int nDamageTotal = 0;

	for ( zDWORD nIndex = 0; nIndex < oEDamageIndex_MAX; nIndex ++ ) 
		nDamageTotal += this->GetDamageByIndex( (oEDamageIndex) nIndex );

	return	nDamageTotal;
}

oTDamageMode oCItem :: GetDamageTypes()
{
	return damageTypes;
}

zBOOL oCItem :: HasDamageType( oEDamageType dwDamageType )
{
	return ( ( this->damageTypes & dwDamageType ) == dwDamageType );
}

zBOOL oCItem :: IsDeadly()
{
	//
	//	EDGE und BLUNT sind nicht toedlich
	//
	if ( this->HasDamageType( oEDamageType_Blunt ) ) return FALSE;
	if ( this->HasDamageType( oEDamageType_Edge  ) ) return FALSE;

	return TRUE;
}

zBOOL oCItem :: IsOneHandWeapon()
{
	return (HasFlag(ITM_FLAG_AXE) || HasFlag(ITM_FLAG_SWD));
}

zBOOL oCItem :: MultiSlot ()
{
	return (
		HasFlag(ITM_FLAG_MULTI)	||
		HasFlag(ITM_CAT_MUN)	||
		HasFlag(ITM_CAT_FOOD)	||
		(SplitSlot() && !HasFlag(ITM_FLAG_ACTIVE))
	);
}

zBOOL oCItem :: SplitSlot ()
{
	// [BENDLIN] Addon - SplitSlot
	//
	// Hier stehen alle Kategorien, die zwar MultiSlot sind,
	// ABER bei EquipItem/UnequipItem getrennt/verbunden werden!
	//
	// Die Abfrage auf 'ACTIVE' bei MultiSlot() sorgt dafuer,
	// dass equipte Split-Items keine Multi-Items sind
	// (zu gut deutsch, weniger Aenderungen an der Engine)
	//
	// Um Split-Items zu deaktivieren muss diese Funktion
	// so geaendert werden, dass sie immer FALSE liefert.
	//
	if (HasFlag(ITM_FLAG_NSPLIT))
		return FALSE;

	return (
		HasFlag(ITM_CAT_NF) ||
		HasFlag(ITM_CAT_FF)	);
}

int oCItem :: GetValue ()
// Ermittle den Wert des Items
// Berücksichtigung von :
// a) Ausgangswert
// b) Magischer Wert
// c) Zustand
{
	// Ermittle Gesamtwert ( value + magic_value )
	float v = float(value + magic_value);
	// Zustand einbeziehen
	if (max_hitp>0) v *= ( hitp / max_hitp );
	// und liefern
	return ( zFloat2IntCeil(v) );
}

int oCItem :: GetWeight ()
{
	if (amount>1) 
		return (weight * amount);
	else
		return (weight);
}

zBOOL oCItem :: HasFlag(int nr)
// Check, if Item has appropriate flag set
{
	return ((flags & nr)==nr);
}

void oCItem :: ClearFlag (int nr)
{
	nr = 0xFFFFFFFF - nr; 
	flags = (flags & nr);
}

void oCItem :: SetFlag (int nr)
{
	flags = flags | nr;
}

zBOOL oCItem :: TwoHanded ()
// Waffe ein Zweihänder ?
{
	return ( (HasFlag(ITM_FLAG_2HD_AXE) || (HasFlag(ITM_FLAG_2HD_SWD))) );
}

zBOOL oCItem :: IsOwned (int instance, int guild)
{
	return (IsOwnedByNpc(instance) || IsOwnedByGuild(guild));	
}

zBOOL oCItem :: IsOwnedByNpc (int instance)
{
	return ((instance>0) && (instance==owner));
}

zBOOL oCItem :: IsOwnedByGuild (int guild)
{
	return ((guild>0) && (ownerGuild==guild));
}

int	  oCItem :: GetDisguiseGuild()
{
	return disguiseGuild;
}

int	 oCItem :: AddManipulation()	
{ 
	// Looki looki -> wann letzte Manipulation
	if (c_manipulation>0) {
		int deltaMin	= ogame -> GetWorldTimer() -> GetPassedTime(last_manipulation);
		if (deltaMin>60) {	
			// Ein Stunde ist vergangen -> Counter auf 0 
			c_manipulation = 0;
		}
	}
	last_manipulation = ogame -> GetWorldTimer() -> GetFullTime();
	c_manipulation++; 
	return c_manipulation; 
};

void oCItem :: GetSoundMaterial_AM (zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2, int damage)
{
	med2	 = zCSoundManager :: zSND_MAN_MEDIUM_ITEM;
	mat2	 = GetSoundMaterial();				
}

// *********************************************************************
// Benutze Item
// *********************************************************************

void oCItem :: Identify()
// Identify Item
{
//	flags = flags | ITM_FLAG_ID;
}

zSTRING oCItem :: GetName(zBOOL identified)
// Get Name of Item
{
//	if (identified && !nameID.IsEmpty()) 
//		return nameID;
//	else
		return name;
}

zSTRING oCItem :: GetStatus ()
{
	int nr;
	zSTRING s;
	int z = ( hitp * 100 / max_hitp ) - 1;

	if (z>=100) nr = 9; else
	if (z<=0)   nr = 0; else
				nr = z / 10;
	s = parser.GetText ( oCText :: TXT_ATR_HP, nr );
	return s;
}

void oCItem :: UseItem ()
{
	// Call Parserfunktion
/*	if (on_use>0) {
		parser.SetInstance	(zSTRING("ITEM"),this);
		parser.CallFunc		(on_use);
		// Ist es ein Schriftstueck, dann zeige es an
		// !!!! TO DO !!!!
	}*/
}

zSTRING oCItem :: GetVisualChange()
{
	zSTRING s = visual_change;
	s.Upper();
	int p = s.Search(".ASC");
	if (p>0) s.Delete(p,4);
	return(s);
}

zSTRING oCItem :: GetEffectName()
{
	return(effectName);
}


int oCItem :: GetStateEffectFunc(int stateNr)
{
	if ((stateNr>=0) && (stateNr<ITM_STATE_MAX) && (onState[stateNr]>0)) {
		return (onState[stateNr]);
	} 
	return -1;
}

oCItem* oCItem :: SplitItem (int removeAmount)
{
	if (removeAmount<GetAmount()) {
		oCItem* item = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,GetInstance());
		if (item) {
			item -> SetAmount(removeAmount);
			SetAmount (GetAmount() - removeAmount);
			return item;
		};
	} 
	return this;
};

// *********************************************************************
//							3D - Functions
// *********************************************************************


void oCItem :: RemoveEffect()
{
	if (effectVob) 
	{
		effectVob->Kill();
		zRELEASE_ACCT(effectVob);
	};
}

void oCItem :: InsertEffect()
{
	// Insert Particle Effect
	if (!oCItem::GetItemEffectsEnabled()) return;

	if ( !effectVob && !effectName.IsEmpty() ) 
	{	
		effectVob = oCVisualFX::CreateAndPlay(effectName, this);		
		if (!effectVob) zERR_WARNING("C: effect " + effectName + " could not be started for item " + this->GetName());
		else if (GetVisual()) effectVob->SetPFXShapeVisual(GetVisual());
	}	
}

// **************************************
// Insert / Remove-Methods
// **************************************

/*	------------------------------------------------------------------
	void oCItem :: ThisVobAddedToWorld		(zCWorld *homeWorld)

	23-Oct-00	[HILDEBRANDT]
				Reihenfolge von SetStaticVob() und SetPhysicsEnabled() geaendert
				(hatte sonst ein nicht-einschlafen von Items zur Folge)
	------------------------------------------------------------------ */

void oCItem :: ThisVobAddedToWorld		(zCWorld *homeWorld)
{
	// [Wohlers] - 07.02.01 - Erst jetzt dem Item das Visual verpassen [Moos] aber nicht für Fackeln und so...
	if (!GetVisual() && file.Search(".ZEN") < 0) 
	{
		zCVob::SetVisual(file);
	}

	oCVob::ThisVobAddedToWorld	(homeWorld);

	// called AFTER the actual addition

	// Flag - Init
	SetCollDetDyn		(TRUE);
	SetCollDetStat		(TRUE);
	// [EDENFELD] Test: Die zCWorld::activeVobList ist riesig in der newworld (>400 Vobs) dort sind alle Items verzeichnet
	// lege ich den Vob hier schlafen scheint alles zu funzen 
	// betrifft: items in der welt (pokale, etc.), Mobinter items, Objectinter Items. Keine Probs beobachtet
	// dadurch ist die activeVobList auf ein paar wenige geschrumpft (hauptsächlich NSCs in der Welt)
	SetSleeping			(TRUE);
	SetStaticVob		(FALSE);		// MUSS vor dem PhysicsEnablen [HILDEBRANDT]
	SetPhysicsEnabled	(FALSE);		// nur auf einem 'nicht-static' Vob laesst sich die Physik einschalten

	if (!homeWorld->GetIsInventoryWorld()) InsertEffect		();

	if (GetRigidBody()) GetRigidBody()->SetGravityEnabled(TRUE);
}

void oCItem :: ThisVobRemovedFromWorld	(zCWorld *homeWorld)
{
	if (!homeWorld->GetIsInventoryWorld()) RemoveEffect		();
	oCVob::ThisVobRemovedFromWorld	(homeWorld);
	SetAI(NULL);
}

void oCItem :: RotateForInventory (int dir)
// Dreht das Item, so das es korrekt im Inventory angezeigt wird.
// Einmal beim Start
{
	ResetRotationsLocal(); // [Moos] 20.12.00 Anpassung an Vob-Änderung
	
	const zBOOL userRotate = ( inv_rotx != 0|| inv_roty != 0|| inv_rotz != 0);

	if (userRotate)
	{
		RotateWorld(1,0,0, inv_rotx * dir);
		RotateWorld(0,1,0, inv_roty * dir);
		RotateWorld(0,0,1, inv_rotz * dir);
		return;
	}

	switch (mainflag) {
		case ITM_CAT_FF		:	RotateWorld(1,0,0, 90 * dir);
								RotateWorld(0,0,1, 45 * dir);
								break;
		case ITM_CAT_NF		:	if (HasFlag(ITM_FLAG_SHIELD)) {
									RotateWorld(1,0,0, -90 * dir);
									RotateWorld(0,0,1, -90 * dir);
									break;
								}
								RotateWorld(1,0,0,-90 * dir);
								if (HasFlag(ITM_FLAG_DAG)) {
									RotateWorld(0,0,1, -45 * dir);
								} else {
									RotateWorld(0,0,1, -135 * dir);
								}
								break;
		case ITM_CAT_ARMOR	:	RotateWorld(1,0,0,360 * dir);
								break;
		case ITM_CAT_MUN	:	RotateWorld(0,0,1,-135 * dir);
								break;
		case ITM_CAT_DOCS	:	RotateWorld(1,0,0,90 * dir);
								//Rotate(0,0,1,-90);
								break;
		case ITM_CAT_POTION	:	RotateWorld(0,1,0,90 * dir);
								break;
		case ITM_CAT_LIGHT	:	break;
		case ITM_CAT_FOOD	:	RotateWorld(0,1,0,-90 * dir);
								RotateWorld(1,0,0,-35 * dir);
								break;
		case ITM_CAT_MAGIC	:	RotateWorld(0,1,0,-90 * dir);
								RotateWorld(1,0,0,-35 * dir);
								break;
		case ITM_CAT_RUNE	:	RotateWorld(1,0,0,-90 * dir);
								break;
		case ITM_CAT_NONE	:	RotateWorld(1,0,0,-25 * dir);
								RotateWorld(0,0,1,-45 * dir);
								break;
	}
}

void oCItem :: RotateInInventory ()
// Laesst das Item korrekt im Inventory rotieren
{
	if (inv_animate)
	{
		zVEC3 rotateWorldVec(0,0,0);

		if (GetVisual() && GetVisual()->GetOBBox3D())
		{
			zCOBBox3D *obbox = GetVisual()->GetOBBox3D();
			rotateWorldVec = obbox->axis[0];
		}
		else
		{
			zVALUE max	= -1;
			int maxIndex= 0;
			for (int i=0; i<3; i++) 
			{
				zVALUE dim		= bbox3D.maxs[i] - bbox3D.mins[i];
				
				if (dim>max) 
				{
					max			= dim;
					maxIndex	= i;
				}
			};
			rotateWorldVec[maxIndex] = 1;
		}

		RotateLocal(rotateWorldVec[0],rotateWorldVec[1],rotateWorldVec[2],20 * ztimer.GetTotalTimeF()/1000);	
	}

}

void oCItem :: RenderItem ( int xp, int yp )
// Angabe in Pixels
{
	zCCamera i_cam;
	zCWorld* i_wld	= zNEW( zCWorld() );
	i_wld->SetIsInventoryWorld(TRUE);
	zCVob*	 i_vob	= zNEW( zCVob() );
	zREAL	 zdist;

	// Setup Camera
	i_cam.SetRenderTarget	(screen);
	i_cam.SetVob			(i_vob);
//	i_cam.SetFarClipZ		(zVALUE_MAX);
//	i_cam.drawMode  =		zCAM_DRAW_TEX_PER;
//	i_cam.shadeMode	=		zSHADE_GOURAUD;
	i_vob->SetPositionWorld	(0,0,0);
	
	SetPositionWorld		( 0,0,0 );
	RotateForInventory		();	

	i_wld->AddVob( i_vob );
	i_wld->AddVob( this  );

	zTBBox3D box3d	= GetBBox3DWorld();

	float x,y;
//	float z;
	x = (box3d.maxs[0] + box3d.mins[0]) / 2;
	y = (box3d.maxs[1] + box3d.mins[1]) / 2;
//	z = (box3d.maxs[2] + box3d.mins[2]) / 2;
	
//	zdist = zMax(x,y);
//	zdist = zMax(zdist,z);	
//	if (kbPressed(KEY_A)) zdist -= 1;
//	if (kbPressed(KEY_Z)) zdist += 1;

	// Distanz errechnen
	switch (mainflag) {
		case ITM_CAT_NF		:	if (HasFlag(ITM_FLAG_DAG))
									zdist = 25;
								else
									zdist = 65;
								break;
		case ITM_CAT_FF		:	zdist = 50;	break;
		case ITM_CAT_ARMOR	:	if (wear & ITM_WEAR_TORSO) zdist = 45; else
								if (wear & ITM_WEAR_HEAD)  zdist = 30; 
								break;
		case ITM_CAT_MUN	:	zdist = 50;	break;
		case ITM_CAT_FOOD	:	zdist = 25;	break;
//		case ITM_CAT_MONEY	:	zdist = 4;		break;
		case ITM_CAT_DOCS	:	zdist = 30;	break;
		case ITM_CAT_POTION	:	zdist = 20;	break;
		case ITM_CAT_LIGHT	:	zdist = 40;	break;
		case ITM_CAT_MAGIC	:	zdist = 25;	break;
		default				:	zdist = 25;	break;
	}
	// Sonderbehandlung fuer Shilder
	if (HasFlag(ITM_FLAG_SHIELD)) zdist = 50;
	zdist *= 7;

	// Weltposition ermitteln
	zVEC3 p;
	p[VZ] = zdist;
	i_cam.BackProject(xp,yp,p);
	
	p[VX] -= x; p[VY] -= y;
	SetPositionWorld (p);

	// Rotate
	zREAL azi,elev;
	Alg_CalcAziElev	(p,azi,elev);
	azi  = Alg_Rad2Deg(azi);
	elev = Alg_Rad2Deg(elev);
//	if (kbPressed(KEY_A)) Rotate(0,1,0,-azi);
//	if (kbPressed(KEY_Z)) Rotate(0,1,0,azi);
	//RotateLocal(1,0,0,-elev);

//	i_wld.CompileWorld		(zBSP_MODE_INDOOR,1.0,FALSE);
//	i_wld.Render			(i_cam);
	i_wld->RemoveVob		(i_vob);
	//changed[dennis]
	//i_wld->RemoveVob		(this);
	i_wld->RemoveVobSubtree	(this);
	zRELEASE				(i_wld);
	zRELEASE				(i_vob);
}

void oCItem :: RenderItemPlaceCamera(zCCamera* cam, zREAL selected)
{       
//changed[dennis]
/*
		zTBBox3D box3d  = GetBBox3DWorld();     
        float dx = (box3d.maxs[0] - box3d.mins[0]);
        float dy = (box3d.maxs[1] - box3d.mins[1]);
        float dz = (box3d.maxs[2] - box3d.mins[2]);     
        float x = dx / 2.0;
        float y = dy / 2.0;
        float z = dz / 2.0;     
                
        zREAL zz=50;
        
        switch (GetCategory()) 
        {
                case ITM_CAT_NF         :       zz = HasFlag(ITM_FLAG_DAG)?25:70;break;
                case ITM_CAT_FF         :       zz = 100;       break;
                case ITM_CAT_ARMOR      :       if (wear == ITM_WEAR_TORSO) zz = 80; else
                                                                if (wear == ITM_WEAR_HEAD)  zz = 30; 
                                                                break;
                case ITM_CAT_MUN        :       zz = 50;        break;
                case ITM_CAT_FOOD       :       zz = 25;        break;
//                case ITM_CAT_MONEY      :       zz = 4;         break;
                case ITM_CAT_DOCS       :       zz = 30;        break;
                case ITM_CAT_KEYS       :       zz = 20;        break;
                case ITM_CAT_LIGHT      :       zz = 40;        break;
                default                         :       zz = 25;        break;
        }       
        // Sonderbehandlung fuer Schilder
        if (HasFlag(ITM_FLAG_SHIELD)) zz = 50;
        
        // cam->GetVob()->SetPositionWorld      (x,y,box3d.mins[2]-zAbs(zz));
        cam->GetVob()->SetPositionWorld (box3d.mins[0]+x,box3d.mins[1]+y,-zAbs(zz));*/

        // CODECHANGE Moos begin: UGLY hack for burning torch.
        zCVob *center = this;   // the REAL object we want to draw

        if (!GetVisual() && globalVobTreeNode && globalVobTreeNode->GetFirstChild()){
            zCVob *child = dynamic_cast<zCVob*> (globalVobTreeNode->GetFirstChild()->GetData());
            if (child)
                center = child;  // if no object would be drawn with center==this, try it with child.
                // (works right now for the burning torch....)
        }
        // CODECHANGE Moos end

        cam->SetFOV(45);
		zVEC3 tempL;
		zVEC3 tempW;
		zTBBox3D box3dl  = center->GetBBox3DLocal();     // CODECHANGE Moos : use the BB of center
		zTBBox3D box3dw  = center->GetBBox3DWorld();     // instead of this.
        tempL.n[0] = (box3dl.maxs[0] - box3dl.mins[0]) * 0.5f;
        tempL.n[1] = (box3dl.maxs[1] - box3dl.mins[1]) * 0.5f;
        tempL.n[2] = (box3dl.maxs[2] - box3dl.mins[2]) * 0.5f;

        tempW.n[0] = (box3dw.maxs[0] - box3dw.mins[0]) * 0.5f;
        tempW.n[1] = (box3dw.maxs[1] - box3dw.mins[1]) * 0.5f;
        tempW.n[2] = (box3dw.maxs[2] - box3dw.mins[2]) * 0.5f;
		
		if ( mainflag == ITM_CAT_MAGIC )
		{
			if ( HasFlag(ITM_FLAG_AMULET) )
			{
				tempL.n[1] -= 4.0f;
				tempW.n[1] -= 4.0f;
			}
			if ( HasFlag(ITM_FLAG_RING) )
			{
				tempL.n[1] -= 0.5f;
				tempW.n[1] -= 0.5f;
			}
			if ( HasFlag(ITM_FLAG_BELT) )
			{
				tempL.n[1] -= 2.0f;
				tempW.n[1] -= 2.0f;
			}
		}			

		float tempRad = tempL.Length();

		float beta  = cam->GetFOV() * 0.5f;
		float alpha = 90 - beta;
		float dist = (tempRad * sinf(alpha))/sinf(beta);

		if  (inv_zbias != 0) 
		{
			dist *= (float(inv_zbias)*0.01f);
		}
		else
		{
			switch (mainflag) 
			{
					case ITM_CAT_NF         : dist*=1.35f;	break;
					case ITM_CAT_FF         : dist*=1.35f;	break;
					case ITM_CAT_ARMOR      : dist;			break;
					case ITM_CAT_MUN        : dist*=1.35f;	break;
					case ITM_CAT_FOOD       : dist*=1.5f;	break;
					case ITM_CAT_DOCS       : dist*=1.35f;	break;
					case ITM_CAT_POTION     : dist*=1.45f;	break;
					case ITM_CAT_MAGIC      : if ( HasFlag(ITM_FLAG_RING) ) dist*=2.0f; break;
					case ITM_CAT_RUNE       : dist*=1.5f;	break;
					case ITM_CAT_NONE       : dist*=1.45f;	break;
					default: break;
			}  
		}
		
		
		if( selected ) dist*=0.8f;
        if (center != this)  // CODECHANGE Moos: step back to make the flame of the 
            dist *= 2.0f;    // burning torch visible

		if (s_fGlobalItemZBiasScale!=0) dist *= s_fGlobalItemZBiasScale;

		cam->GetVob()->SetPositionWorld (box3dw.mins[0]+tempW.n[0],box3dw.mins[1]+tempW.n[1],-zAbs(dist));
};

void oCItem :: RenderItem ( zCWorld* i_wld, zCViewBase *viewitem, zREAL addon )
{
	zCCamera *oldcam = zCCamera::activeCam;

	zCCamera i_cam;
	zCVob*	 i_camvob	= zNEW( zCVob() );

	int lightRange = i_cam.GetCamLightRange();
	// Item der Welt hinzufügen
	SetPositionWorld ( 0,0,0 );
	
	// RotateInInventory();
	if (addon) RotateInInventory();	
		else RotateForInventory();	

	// SetDrawBBox3D(TRUE);
	SetGroundPoly	(NULL);

#ifdef DEBUG_MOOS
    ignore_addref_release(true);
#endif

	i_wld->AddVob	( this  );

#ifdef DEBUG_MOOS
    ignore_addref_release(false);
#endif

	// Kamera in die Welteinfuegen
	
	i_wld->AddVob	( i_camvob );	
	i_cam.SetVob	( i_camvob );


	i_cam.SetCamLightRange(5000);

	RenderItemPlaceCamera(&i_cam, addon);
	
	// Render vorbereiten
	i_cam.SetRenderTarget		(viewitem);		
	i_cam.SetFarClipZ			(zVALUE_MAX);	
	i_wld->SetDrawVobBBox3D		(FALSE);
	
	lastTimeDrawn = -1;
	i_wld->GetBspTree()->SetBspTreeMode(zBSP_MODE_INDOOR);
	zCSkyControler* sky = i_wld->GetActiveSkyControler();
	sky->SetFillBackground(FALSE);
	
	// Rendern
	zCEventManager::disableEventManagers = TRUE;	
	zrenderer->SetAlphaBlendFunc (zRND_ALPHA_FUNC_NONE);

	i_wld->Render(i_cam);	

	zCEventManager::disableEventManagers = FALSE;
	
	// Welt aufraeumen
	i_wld->RemoveVob		(i_camvob);

//changed[dennis]
//	i_wld->RemoveVob		(this);
#ifdef DEBUG_MOOS
    ignore_addref_release(true);
#endif
	i_wld->RemoveVobSubtree	(this);

	zRELEASE				(i_camvob);
#ifdef DEBUG_MOOS
    ignore_addref_release(false);
#endif

	zCCamera::activeCam = oldcam;

	i_cam.SetCamLightRange(lightRange);
}

// *********************************
//		Save / Load Functions
// *********************************

zBOOL oCItem :: GetScriptInstance	(zSTRING* &scriptInstanceName, int &scriptInstanceIndex)
{
	// returns name/index, as available
	// Achtung : dynamisches Objekt !
	zCPar_Symbol* sym = parser.GetSymbol(instanz);
	if (sym) scriptInstanceName = &sym->name;
	else	 scriptInstanceName = NULL;
	scriptInstanceIndex			= instanz;
	return TRUE;
}
	
zBOOL oCItem ::	SetByScriptInstance	(const zSTRING* scriptInstanceName, const int scriptInstanceIndex)
{
	// use 'name' or 'index' exclusively, but not both
	if (scriptInstanceName) {
		InitByScript(parser.GetIndex(*scriptInstanceName));
	} else {
		InitByScript(scriptInstanceIndex);
	}
	return TRUE;
}

zSTRING oCItem :: GetInstanceName ()
{
	int typ,ele;
	return parser.GetSymbolInfo(instanz,typ,ele);
}

// *************************************
// Archive / Unarchive
// *************************************

void oCItem :: Archive (zCArchiver &arc)
{
    // speichere das Visual zwischen (nur falls es kein .ZEN ist)
	// Es muss nicht gespeichert werden, wird aus den Skripten eh neu initialisiert.
	zBOOL dontSaveVisual = (file.Search(".ZEN")<0);
	zCVisual* visual = NULL;
	if (dontSaveVisual) {
		visual = GetVisual();
		if (visual) visual->AddRef();
		SetVisual(NULL);
	}
	
	oCVob :: Archive(arc);

	// Item wird komplett über Instanznamen initialisiert
	// extra gespeichert werden nur die veränderlichen Werte :
	// amount
	arc.WriteString	("itemInstance"	,GetInstanceName());

    if (dontSaveVisual) {
		SetVisual(visual);	//  restauriere das alte Visual
		zRELEASE (visual);
	}

	if (!arc.InSaveGame()) return;

	arc.WriteInt	("amount"		,GetAmount());
	arc.WriteInt	("flags"		,flags);
};

void oCItem :: Unarchive (zCArchiver &arc)
{
	zCVob :: Unarchive(arc);

	// Get Instance Name
	arc.ReadString	("itemInstance"	,name);
	int	index		= parser.GetIndex (name);
	if (index >= 0) {
        zBOOL LoadingGame = s_LoadingGame;
        s_LoadingGame = TRUE;

		InitByScript	(index);

        s_LoadingGame = LoadingGame;
	} else {
		// zerr.Warning("U:ITEM:Load:Instance not found : " + name);
		//zERR_FAULT("U:ITEM:Load:Instance not found : Vobname :" + GetVobName() + "/ Scriptinstance:" + name +". Correct instancename or remove item !");
	};

	if (!arc.InSaveGame()) return;
	// GetAmount
	arc.ReadInt		("amount"		,amount);
	arc.ReadInt		("flags"		,flags);
};

oCAIVobMove* oCItem :: GetAIVobMove ()
{
	if (HasFlag(ITM_FLAG_TORCH)) {
		oCAIVobMoveTorch* ai = dynamic_cast<oCAIVobMoveTorch*>(GetAI());
		if (!ai) {
			// neue AI bauen
            // CODECHANGE Moos: SetAI handles reference counting
    		// GetAI()->Release();
			SetAI (ai = zNEW( oCAIVobMoveTorch()) );
            ai -> Release();
		}	
		//SetShowDebug(TRUE);
		return ai;
	} else {

		return oCVob :: GetAIVobMove ();
	}
}

/*	------------------------------------------------------------------
	oCItem::Render ()
	15.01.2001	[HILDEBRANDT]	
				hintLightingSwell im RenderContext gesetzt. Items sind
				damit besser unter anderen Objekten identifzierbar.
	26.07.2002  [EDENFELD]	
				Glanz Effekt für Items mit Glas oder Metall Eigenschaft
				hinzugefügt
	------------------------------------------------------------------ */


struct zSEnvValues
{
	zBOOL envEn;
	float envWeight;
};

zBOOL zCCFASTCALL  oCItem::Render (zTRenderContext &renderContext)
{

	// Falls Item nicht in Focus kommen darf, dann auch nicht blinken (zB. ItemInteraktion)
	if (HasFlag(ITM_FLAG_NFOCUS))	renderContext.hintLightingSwell = FALSE;
	else							renderContext.hintLightingSwell	= GetLightingSwell();

	// glanz effekt für materialien glas und metal (ausser für waffen, diese werden über einen anderen mechanismus gehandelt)
	if ((GetSoundMaterial()==SND_MAT_METAL || GetSoundMaterial()==SND_MAT_GLAS)  && 
		zDYNAMIC_CAST<zCProgMeshProto>(GetVisual())								 && 
		this->GetMainFlag()!=ITM_CAT_NF
		)
	{
		static zCArray<zSEnvValues>savedEnvValues;

		zCProgMeshProto* mesh = static_cast<zCProgMeshProto*>(GetVisual());
		for (int i=0; i<mesh->GetNumMaterial(); i++)
		{
			static zSEnvValues savedEnvValue;
			float  envScaler = 1.0f;
			
			zCMaterial *mat = mesh->GetMaterialByIndex(i);
			if (mat->GetMatGroup()==zMAT_GROUP_WOOD)  envScaler = 0.2f;	else
			if (mat->GetMatGroup()==zMAT_GROUP_EARTH) envScaler = 0.5f; else
			if (mat->GetMatGroup()==zMAT_GROUP_STONE) envScaler = 0.6f; 

			// alte Materialeigenschaften speichern
			savedEnvValue.envEn		= mat->GetEnvMapEnabled();
			savedEnvValue.envWeight	= mat->GetEnvMapStrength();
			savedEnvValues.Insert(savedEnvValue);

			// env anschalten
			mat->SetEnvMapEnabled (TRUE);
			if (GetSoundMaterial()==SND_MAT_GLAS) mat->SetEnvMapStrength(0.4f * envScaler);
			else								  mat->SetEnvMapStrength(0.8f * envScaler);
		};

		// rendern (mit env-fx)
		zBOOL res = oCVob::Render (renderContext);


		// alte env werte wiederherstellen
		for (i=0; i<mesh->GetNumMaterial(); i++)
		{	
			zCMaterial *mat = mesh->GetMaterialByIndex(i);
			mat->SetEnvMapEnabled (savedEnvValues[i].envEn);
			mat->SetEnvMapStrength(savedEnvValues[i].envWeight);
		}
		// liste leeren
		savedEnvValues.EmptyList();

		return res;
	}

	return oCVob::Render (renderContext);
};

zCLASS_DEFINITION_SCRIPTED ( oCItem , oCVob	, 0, 0, C_ITEM)

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
