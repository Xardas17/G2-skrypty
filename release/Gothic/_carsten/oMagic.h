/******************************************************************************** 
 
     $Workfile:: oMagic.h             $                $Date:: 15.02.01 13:23   $
     $Revision:: 21                   $             $Modtime:: 15.02.01 11:28   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Carsten/oMagic.h $
 * 
 * 21    15.02.01 13:23 Moos
 * Aufräumarbeiten
 * 
 * 20    30.11.00 15:03 Wohlers
 * 
 * 19    13.11.00 23:40 Edenfeld
 * 
 * 18    21.09.00 4:25 Edenfeld
 * 
 * 17    30/08/00 12:33 Luesebrink
 * 
 * 16    22/08/00 14:02 Luesebrink
 * 
 * 15    21/08/00 17:31 Luesebrink
 * 
 * 14    14.08.00 21:27 Edenfeld
 * 
 * 13    10/08/00 15:46 Luesebrink
 * 
 * 12    9/08/00 18:47 Luesebrink
 * 
 * 11    9/08/00 18:28 Luesebrink
 * 
 * 10    8/08/00 14:18 Luesebrink
 * 
 * 9     8/08/00 12:35 Luesebrink
 * 
 * 8     4/08/00 16:14 Luesebrink
 * 
 * 7     26.07.00 18:40 Edenfeld
 * 
 * 6     10.07.00 16:47 Wohlers
 * CMag_Book -> oCMag_Book
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
 * 1     20.04.00 11:52 Admin
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 4     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __OMAGIC_H__
#define __OMAGIC_H__

#include <stdio.h>
#include "zParser.h"
#include "z3d.h"
#include "zModel.h"
#include "zContainer.h"
#include "oSpell.h"
#include "oItem.h"

class oCNpc;
class oCSpell;

// ************************************************************************
// Auswahlkranz
// ************************************************************************

class oCMag_Book {
public:
	oCMag_Book							();
	~oCMag_Book							();

	void			SetOwner			(zCVob* w);
	void			SetWorld			(zCWorld* w);
//changed[dennis]
	zBOOL			Register			(oCItem  *item,  zBOOL active = TRUE);
	zBOOL			Register			(int snr, zBOOL active = TRUE);

//changed[dennis]
	zBOOL			DeRegister			(oCItem  *item );
	zBOOL			DeRegister			(int no);

	void			Open				(zBOOL showMagicCircle = TRUE);	// Auswahlkranz "ausfahren"
	void			Close				(zBOOL removeall);				// Auswahlkranz "einfahren"
	zBOOL			IsOpen				() { return open; };
	zBOOL			IsActive			();
	zBOOL			IsIn				(int id);

	void			EnableSpell			(int snr, zBOOL flag = TRUE);

	zBOOL			IsInMovement		();				// Auswahlkranz in Bewegung ?
	
	void			SetFrontSpell		(int snr);		// Set to this Position
	void			Left				();				// Auswahlkranz eine Pos nach Links
	void			Right				();				// Auswahlkranz eine Pos nach Rechts
	
	oCSpell*		GetSelectedSpell	();			// Liefert den gewählten Spruch
	int				GetSelectedSpellNr	();

	void			DoPerFrame			();				 
	void			RemoveEffects		();				// z.B.Symbol auf Hand wieder entfernen

	void			SetShowHandSymbol	(zBOOL flag = TRUE);

	// Zum aktuellen Spell durchschleifen
	void			Spell_Setup			(oCNpc* npc, zCVob* target,const zBOOL a_bIgnoreCastState=FALSE);
	void			Spell_Invest		();
	void			Spell_Cast			();
	void			Spell_Setup			(int snr, oCNpc* npc, zCVob* target);
	void			Spell_Open			(int snr);
	void			Spell_Stop			(int snr);
	void			StopSelectedSpell	();
	void			KillSelectedSpell	();	

	zBOOL			Spell_InCast		();			// Wird Spell gerade benutzt ?

	// *** Called by messages ***
	void			StartInvestEffect	(zCVob* target, int level, int mana, int energyLeft);
	void			StartCastEffect		(zCVob* target, const zVEC3& targetPos);

	// Ease
	zREAL			Ease				(zREAL t, zREAL a, zREAL b);
	zVEC3			EasePos				(zREAL t, zVEC3 &a, zVEC3 &b);
	zVEC3			CalcPos				(zCVob* vob, zREAL angle);

	zREAL			GetAngle			(zCVob *to);
	zBOOL			DoTurn				();
	zBOOL			DoOpen				();
	zBOOL			DoClose				();
	void			ShowHandSymbol		();

	oCSpell*		CreateNewSpell		(int snr);

	oCSpell*		GetSpell			(oCItem *item, int &no);
	oCSpell*		GetSpell			(int no);
	oCSpell*		GetSpellByKey		(int no);

	oCItem*			GetSpellItem		(int no);
	oCItem*			GetSpellItemByKey	(int no);
	oCItem*			GetSpellItem		(oCSpell* spell);

	int				GetKeyByItem		(oCItem *item);

	//changed[dennis]
	int				GetNoOfSpells		( void );
	int				GetNoOfSpellByKey	( int key );

	void			NextRegisterAt		( int slot );

    void            CheckConsistency    ();
private:
	zBOOL			Register			(oCSpell *spell, zBOOL active = TRUE); // [Moos] Diese Funktion ist gefährlich, wenn sie von aussen aufgerufen wird.
	
	zCArray    <oCSpell*>	spells;
//changed[dennis]
	zCArray    <oCItem*>	spellitems;
	//zCArray    <zCVob*>		circleitems;
	zCWorld*	wld;
	zCVob*		owner;
	zCModel*	model;
	int			spellnr;		// Selected Spell
	zREAL		MAG_HEIGHT;
	zBOOL		active;
	zBOOL		remove_all;
	zBOOL		in_movement;
	zBOOL		show_handsymbol;
	zREAL		step;
	int			action;
	int			fullangle;
	zBOOL		open;
	zREAL		open_delay_timer;
	zBOOL		show_particles;

	zREAL		targetdir,t1;
	zVEC3		targetpos,startpos;

//changed[dennis]
	int			nextRegister;
	unsigned int keys;
};

#endif
