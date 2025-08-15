/******************************************************************************** 
 
     $Workfile:: oMagic.cpp           $                $Date:: 18.03.01 18:48   $
     $Revision:: 82                   $             $Modtime:: 14.03.01 17:27   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Carsten/oMagic.cpp $
 * 
 * 82    18.03.01 18:48 Edenfeld
 * Nochn potentieller Magie Crash gefixt
 * 
 * 81    12.03.01 19:59 Edenfeld
 * Magie Crash Teil !
 * 
 * 80    15.02.01 19:46 Moos
 * Fix der Check-Routinen für den Transform-Spell
 * 
 * 79    15.02.01 13:20 Moos
 * Konsistenzchecks, Aufräumarbeiten und fixes für mysteriöse Bugs
 * 
 * 78    14.02.01 19:43 Moos
 * Verschwundende Magie-Runen wiedergefunden: Sie hatten einfach noch kein
 * Visual...
 * 
 * 77    14.02.01 19:15 Moos
 * 
 * 76    10.02.01 21:49 Moos
 * Crashfixes und Scroll-nichtverbrauch-fixes
 * 
 * 75    10.02.01 20:45 Moos
 * Monstermässige Magie-Leakfixes
 * 
 * 74    9.02.01 22:39 Edenfeld
 * VisualFX Memleaks work in progress
 * 
 * 73    8.02.01 14:53 Moos
 * 
 * 72    5.02.01 16:46 Edenfeld
 * 
 * 70    2.02.01 23:44 Edenfeld
 * 
 * 69    2.02.01 23:40 Edenfeld
 * 
 * 68    20.01.01 2:33 Edenfeld
 * 
 * 67    18.01.01 0:06 Edenfeld
 * 
 * 66    20.12.00 17:10 Moos
 * 
 * 65    20.12.00 14:15 Edenfeld
 * 
 * 64    30.11.00 15:03 Wohlers
 * 
 * 63    22.11.00 18:07 Edenfeld
 * 
 * 62    22.11.00 17:10 Edenfeld
 * 
 * 61    13.11.00 23:40 Edenfeld
 * 
 * 60    9.11.00 15:35 Moos
 * 
 * 59    8.11.00 18:22 Wohlers
 * 
 * 58    2.11.00 22:07 Edenfeld
 * 
 * 57    1.11.00 19:12 Moos
 * 
 * 56    1.11.00 17:58 Moos
 * 
 * 55    30/10/00 17:31 Luesebrink
 * 
 * 54    18.10.00 17:58 Moos
 * 
 * 53    17.10.00 20:06 Moos
 * 
 * 52    28.09.00 20:58 Wohlers
 * 
 * 51    21.09.00 16:02 Wohlers
 * 
 * 50    21.09.00 4:25 Edenfeld
 * 
 * 49    20.09.00 1:47 Rueve
 * 
 * 48    19.09.00 23:28 Edenfeld
 * 
 * 47    8/09/00 14:32 Luesebrink
 * 
 * 46    1.09.00 23:05 Moos
 * 
 * 45    1/09/00 17:35 Luesebrink
 * 
 * 44    31/08/00 14:29 Luesebrink
 * 
 * 43    31/08/00 13:47 Luesebrink
 * 
 * 42    30/08/00 12:33 Luesebrink
 * 
 * 41    25.08.00 15:05 Wohlers
 * 
 * 40    24.08.00 11:34 Moos
 * new durch zNEW ersetzt
 * 
 * 39    23.08.00 21:06 Wohlers
 * Items werden nach Gebrauch korrekt aus Inventory entfernt
 * 
 * 38    23/08/00 17:32 Luesebrink
 * 
 * 37    23.08.00 17:08 Wohlers
 * 
 * 36    23.08.00 16:14 Wohlers
 * 
 * 35    23.08.00 15:46 Wohlers
 * 
 * 34    23.08.00 15:38 Wohlers
 * 
 * 33    22.08.00 16:41 Edenfeld
 * 
 * 32    22/08/00 16:21 Luesebrink
 * 
 * 31    22/08/00 14:02 Luesebrink
 * 
 * 30    21/08/00 17:31 Luesebrink
 * 
 * 29    17.08.00 20:42 Edenfeld
 * 
 * 28    16.08.00 0:41 Edenfeld
 * 
 * 27    15.08.00 18:04 Wohlers
 * 
 * 26    15.08.00 17:50 Wohlers
 * 
 * 25    15.08.00 17:02 Wohlers
 * 
 * 24    14.08.00 21:27 Edenfeld
 * 
 * 23    11.08.00 15:43 Edenfeld
 * 
 * 22    11/08/00 14:21 Luesebrink
 * 
 * 21    10/08/00 15:46 Luesebrink
 * 
 * 20    9/08/00 18:47 Luesebrink
 * 
 * 19    9/08/00 18:28 Luesebrink
 * 
 * 18    8.08.00 15:16 Wohlers
 * 
 * 17    8/08/00 14:18 Luesebrink
 * 
 * 16    8.08.00 12:45 Wohlers
 * 
 * 15    8/08/00 12:35 Luesebrink
 * 
 * 14    7/08/00 12:48 Luesebrink
 * 
 * 13    4.08.00 17:09 Wohlers
 * 
 * 12    4/08/00 16:14 Luesebrink
 * 
 * 11    1.08.00 17:31 Edenfeld
 * 
 * 10    28.07.00 13:32 Edenfeld
 * 
 * 9     26.07.00 18:40 Edenfeld
 * 
 * 8     21.07.00 17:04 Edenfeld
 * 
 * 7     14.07.00 13:43 Edenfeld
 * 
 * 6     10.07.00 16:46 Wohlers
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
 * 5     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 4     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zcore.h"
#include "zview.h"
#include "zWorld.h"
#include "zEventMan.h"

#include "oText.h"
#include "oMagic.h"
#include "oSpell.h"
#include "oNpc.h"
#include "oNpcMessages.h"

#include "oGame.h"
#include "zAccount.h"


// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

// ************************************************************************
// Auswahlkranz
// ************************************************************************

static const zREAL	MAG_ANGLEYDIF	= 50.0F / 180.0F;	// 50 cm auf 180 Grad
static const zREAL  MAG_DISTANCE	=  90;
static const zREAL	MAG_OPEN_DELAY	= 2000;
static const zREAL	MAG_SELECT_TIME	= 250.0f;


static void S_CopyItemVisual(const oCItem *source, zCVob *destination){
    if (!source->GetVisual())
        ((oCItem *)source)->CreateVisual();

    if (source->GetVisual())
        destination->SetVisual(source->GetVisual());
}

oCMag_Book :: oCMag_Book ()
{

	zERR_MESSAGE(8,0,"C: MAG: constructed magbook");

	wld				= NULL;
	owner			= NULL;
	model			= NULL;
	spellnr			= 0;		// Selected Spell

	MAG_HEIGHT		= 90.0f;
	active			= FALSE;
	remove_all		= FALSE;
	in_movement		= FALSE;
	show_handsymbol	= FALSE;
	step			= 0.0f;
	action			= 0;
	fullangle		= 0;
	open			= FALSE;
	open_delay_timer= 0.0f;
	show_particles	= FALSE;

	targetdir		= 0.0f;
	t1				= 0.0f;
	targetpos		= zVEC3(0,0,0);
	startpos		= zVEC3(0,0,0);

	nextRegister	= 0;
	keys			= 0;
}

oCMag_Book :: ~oCMag_Book ()
{
	zERR_MESSAGE(8,0,"C: MAG: destructed magbook");
	
    int i;

	for (i=0; i<spells.GetNumInList(); i++) {
        spells[i]->Stop(); // [Moos]
		zRELEASE_ACCT(spells[i]);
	}
	spells.DeleteList();

	wld				= NULL;
	owner			= NULL;
	model			= NULL;
}


void oCMag_Book::CheckConsistency    (){
    zERR_ASSERT_STRICT(spells.GetNumInList() == spellitems.GetNumInList());

    int realKey=0;
    int i;
    zBOOL checkKey = TRUE;

    for (i = spells.GetNumInList()-1; i>=0; i--)
    {
        if (i == spellnr && !spells[i]){
            checkKey = FALSE;
            continue; // [Moos] Der aktuelle Spell muss nicht unbedingt eingetragen sein
        }

        zERR_ASSERT_STRICT(spells[i]->GetSpellID() == spellitems[i]->spell);
        realKey |= 1 << (spells[i]->keyNo -1);
    }

    if (checkKey)
        zERR_ASSERT_STRICT(keys == realKey);
}

void oCMag_Book :: SetOwner (zCVob *v)
{
   	owner	= v;
	wld		= owner -> GetHomeWorld();
	if (dynamic_cast<zCModel*>(owner->GetVisual()))	model = (zCModel*)owner->GetVisual();
	else 											model = NULL;

	// Magiekranzhöhe auf Kopfhöhe + 10 cm
	MAG_HEIGHT	= owner->GetBBox3DWorld().maxs[VY] - owner->GetPositionWorld()[VY] + 10;
}

void oCMag_Book :: SetWorld (zCWorld *w)
{
	wld = w;
}

zBOOL oCMag_Book :: Register (oCSpell* spell, zBOOL active)
{
	if (!spell) return FALSE;
	zADDREF_ACCT(spell);
	spells.Insert(spell);
	return TRUE;
}

//changed[dennis]
// [Moos] aufgeräumt
zBOOL oCMag_Book :: Register (oCItem* item, zBOOL active)
{
    if( spells.GetNumInList() >= 7 ) return FALSE;

	if( !nextRegister )
    {
		int i = 0;
		while(keys&(1<<i++));
		keys |= 1<<(i-1);
        nextRegister = i;
    }

    zERR_ASSERT(nextRegister > 0 && nextRegister < 10);

	if( Register( CreateNewSpell( item->spell ), TRUE ) ) spellitems.Insert(item);
	spells[spells.GetNumInList()-1]->keyNo = nextRegister;
	zRELEASE_ACCT_NONULL(spells[spells.GetNumInList()-1]);
	keys |= 1 << (nextRegister-1);
	nextRegister = 0;

#ifdef _DEBUG
    CheckConsistency();
#endif

	return TRUE;
}

/*--------------------------------------------------------------------------
	
	zBOOL oCMag_Book :: DeRegister(oCItem* item)

 

    17-Aug-00       [EDENFELD] Folge-Crash abgefangen

--------------------------------------------------------------------------*/

zBOOL oCMag_Book :: DeRegister(oCItem* item)
{
	int i = 0;
	while( item != spellitems[i++] ) 
	{ 
		if (i >= GetNoOfSpells()) return FALSE;
	}
	DeRegister(i-1);
	return TRUE;
}

zBOOL oCMag_Book :: DeRegister(int no)
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	keys &= ~(1<<((spells[no]->keyNo-1)));
	spellitems.Remove(spellitems[no]);

    oCSpell *spell = spells[no];
	spells.RemoveIndex(no);
	zRELEASE_ACCT(spell); // [Moos] Leakfix

#ifdef _DEBUG
    CheckConsistency();
#endif

	return TRUE;
}
//

oCSpell* oCMag_Book :: CreateNewSpell (int id)
{
	zERR_MESSAGE(8,0,"C: MAG: CreateNewSpell");
	// Nicht doppelt einfügen.
	oCSpell*spell =  zNEW( oCSpell(id) );
	return spell;
}

zBOOL oCMag_Book :: Register (int snr, zBOOL active)
{
	zERR_MESSAGE(8,0,"C: MAG: Register");

	oCSpell* newspell = CreateNewSpell(snr);
	if (newspell) {
		//newspell->AddRef();
		spells.Insert(newspell);
		//zRELEASE(newspell);
	}
	
	return (newspell!=NULL);
}

zBOOL oCMag_Book :: IsIn (int id)
{
	for (int i=0; i<spells.GetNumInList(); i++) {
		if (spells[i]->GetSpellID()==id) return TRUE;
	}
	return FALSE;
}

void oCMag_Book :: Spell_Setup  (int snr, oCNpc* npc, zCVob *target)
{
	zERR_MESSAGE(8,0,"C: MAG: Spell_Setup");

	spells[snr] -> Setup(npc,target);
}

void oCMag_Book :: Spell_Setup  (oCNpc* npc, zCVob *target, const zBOOL a_bIgnoreCastState)
{
	zERR_MESSAGE(8,0,"C: MAG: Spell_Setup");

	GetSelectedSpell() -> Setup(npc,target,a_bIgnoreCastState);
}

void oCMag_Book :: Spell_Invest ()
{
	zERR_MESSAGE(8,0,"C: MAG: Spell_Invest");

	GetSelectedSpell()->Invest();
}

void oCMag_Book :: StartInvestEffect(zCVob* tgt, int level, int mana, int energyLeft)
{
	zERR_MESSAGE(8,0,"C: MAG: StartInvestEffect");
}

/* ----------------------------------------------------------------------
	
	oCMag_Book::Spell_Cast()

	23.08.2000	[Moos]	

				auf zNEW umgestellt

    18.10.2000 [Moos]
                
                probleme durch Leakfixes (spells werden jetzt korrekt [und damit leider zu früh] gelöscht) beseitigt

   ---------------------------------------------------------------------- */

void oCMag_Book :: Spell_Cast()
{
	zERR_MESSAGE(8,0,"C: MAG: Spell_Cast");

#ifdef _DEBUG
    CheckConsistency();
#endif

	oCSpell* spell	= GetSelectedSpell();

		// skript cast methode ausführen
	parser.SetInstance("SELF"	,spell->GetSpellCasterNPC());
	parser.SetInstance("OTHER"	,spell->GetSpellTargetNPC());

	int index = parser.GetIndex( zSTRING("SPELL_CAST_") + zSTRING(spell->GetObjectName()) );
	if (index > 0) parser.CallFunc(index, spell->GetLevel());

	zVEC3 pos		= spell -> GetVob() -> GetPositionWorld();
	int id			= spell -> GetSpellID();

	int		keyNo	= GetSelectedSpell()->keyNo;
	zBOOL	invested= GetSelectedSpell()->GetInvestedMana();

    spells[spellnr] = NULL; // [Moos] verhindert das löschen des spells 

	zBOOL canCastAnother = !(spellitems[spellnr]->MultiSlot() && invested && spellitems[spellnr]->GetAmount() <= 1);

	if (spell->Cast()) 
	{
//		if (spell->CanBeDeleted()) // [Moos] Leakfix: die Referenz wird jedenfalls freigegeben. Wenn der Spell noch gebraucht wird, ist er in der Liste des NPCs und wird hier nicht gelöscht.
        zRELEASE_ACCT(spell);		// spell kann gelöscht werden, wenn keine weiteren Referenzen darauf bestehen (Control/TRF/Light werden in oCNpc::activeSpellList weiterverwendet)

		// spell wurde gecasted, jetzt sofort neuen effekt bereitstellen

		// Neuen erstellen
	    spells[spellnr]  = CreateNewSpell(id);
	    spells[spellnr]->keyNo = keyNo;

		// Das Handsymbol kann innerhalb eines Zauberspruches wieder geschlossen werden,
		// (TRANSFORM / LIGHT / HUMANCTRL) Dann darf neuer Zauberspruch nicht eingefügt werden.
        // [Moos] probieren wir es mit der Logik unten...
//		if (!show_handsymbol) 
//		{
//			return;
//		}
		
        if (show_handsymbol && canCastAnother)
		{
            // And open new one
			Spell_Setup(spellnr, zDYNAMIC_CAST<oCNpc>(owner),NULL);
        }

        spell = NULL;
	}
    else spells[spellnr] = spell; // [Moos] restore old state

	//changed[dennis]

#ifdef _DEBUG
    CheckConsistency();
#endif

	if( spellitems[spellnr]->MultiSlot() && invested )
	{
		if( spellitems[spellnr]->GetAmount() > 0 )
            spellitems[spellnr]->ChangeAmount(-1);

		if( spellitems[spellnr]->GetAmount() == 0 )
		{
//                Spell_Stop(spellnr); //[Moos] Der aktuelle spell muss angehalten werden

			// DeRegister passiert automatisch beim RemoveFromInv
			oCItem* item =	((oCNpc*)owner)->RemoveFromInv(spellitems[spellnr],0);			
			wld->RemoveVob	(item);	
			if( spells.GetNumInList() == 0 ) {
				((oCNpc*)owner)->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),owner); 
				return;
			} else {
				spellnr = 0;
				Spell_Setup(spellnr, dynamic_cast<oCNpc*>(owner),NULL);
				return;
			}
		}
	}


#ifdef _DEBUG
    CheckConsistency();
#endif
}

void oCMag_Book :: StartCastEffect(zCVob* tgt, const zVEC3& tgtPos)
{
	zERR_MESSAGE(8,0,"C: MAG: StartCastEffect");
}

zBOOL oCMag_Book :: Spell_InCast()
{
	return FALSE;
}

void oCMag_Book :: Open(zBOOL showMagicCircle)
{
  	if (open)						return;
	if (spells.GetNumInList()==0)	return;

#ifdef _DEBUG
    CheckConsistency();
#endif

	zERR_MESSAGE(8,0,"C: MAG: Open");

    // [Moos] Visuals der SpellItems bei Bedarf erzeugen
    /*
     for (int i = spellitems.GetNumInList()-1; i>=0; i--)
        if (!spellitems[i]->GetVisual())
            spellitems[i]->CreateVisual();
    */ //[Moos] nicht mehr nötig

	// Safety...
	SetWorld (owner->GetHomeWorld());

	// Close active Effect
	if ((spellnr>=0) && (show_handsymbol)) 
		Spell_Stop(spellnr);

	int count	= spells.GetNumInList();

	if (showMagicCircle) 
	{
		// Magiekranz wird komplett angezeigt
		open = TRUE;

		// a) Inner Mitte aufbauen
		zCVob* mvob = NULL;

		step		= float(360 / count);
		// Baue Kranz auf
		startpos	= owner -> GetPositionWorld();
	
		for (int i=0; i<count; i++) 
		{		
			// Erschaffen und in Welt setzen
			mvob		=  spells[i]->GetVob();
			zERR_ASSERT(mvob);
			if (!mvob->RegisteredInWorld()) wld ->  AddVob	( mvob );
			
			spells[i]	-> Reset			();
			mvob		-> SetPositionWorld	(startpos);
			mvob		-> SetCollDet		(FALSE);
			S_CopyItemVisual(spellitems[i], mvob);
		};		

		t1				= 0;
		action			= 2;
		in_movement		= TRUE;
		show_particles	= FALSE;
		open_delay_timer= MAG_OPEN_DELAY;
		SetShowHandSymbol(FALSE);
	
	} 
	else 
	{
		for (int i=0; i<count; i++) spells[i]->Reset();		
			
		// springe zu dem aktuellen spell, ohne den kranz anzuzeigen
		oCSpell* selectedSpell = GetSelectedSpell();
		if (!selectedSpell) return;
		zCVob* mvob = selectedSpell->GetVob();
		zERR_ASSERT(mvob);
		//assert(mvob->RegisteredInWorld());
		if (!mvob) return;
		if (!mvob->RegisteredInWorld()) {
			// FIXME: tritt dieser Fall jemals ein ? Darf nicht! [Moos] Doch, darf er. Wenn man einen Spell per HotKey öffnet, ist er natürlich noch nicht in der Welt.
			wld ->  AddVob	( mvob );
		}
		selectedSpell	-> Reset();
		mvob			-> SetPositionWorld (owner->GetPositionWorld());
		S_CopyItemVisual(spellitems[spellnr], mvob);
        //mvob			-> SetVisual		(spellitems[spellnr]->GetVisual());			

		// Sofort aktiven Spell aktivieren.
		in_movement		= FALSE;
		show_particles	= FALSE;
		open_delay_timer= 0.0f;
		SetShowHandSymbol(TRUE);
	}

	// [Ulf] : Hier gab absturz, weil Spellnr==1 aber nur ein Objekt in Array (Index 0)
	// zCView::stdoutput->Printwin(spells[spellnr]->GetName()+"\n");
}

void oCMag_Book :: Close( zBOOL remall )
{	
	zERR_MESSAGE(8,0,"C: MAG: Close");

#ifdef _DEBUG
    CheckConsistency();
#endif

	if (IsOpen()) {
		in_movement = TRUE;
		action		= 3;
		t1			= 0;
		remove_all	= remall;

/*		if (!remove_all) 
		{
			GetSelectedSpell()->Reset();
			GetSelectedSpell()->Open ();
		}
*/
	} else {

		SetShowHandSymbol(!remall);

	}; 
}

zREAL oCMag_Book :: Ease(zREAL t, zREAL a, zREAL b)
{
 	const zREAL t1 = (zSin(t*TRG_PI-TRG_PI/2)+1.0F) / 2.0F;
	return a + t1 * ( b - a );
}

zVEC3 oCMag_Book :: EasePos(zREAL t, zVEC3 &a, zVEC3 &b)
{
	const zREAL t1 = (zSin(t*TRG_PI-TRG_PI/2)+1.0F) / 2.0F;
	return a + t1 * ( b - a );
}

zREAL oCMag_Book :: GetAngle( zCVob *to )
{	
	zREAL azi,elev,azi2,elev2;
	// Blickrichtung des aktuellen NSCs
	Alg_CalcAziElev	(owner->GetAtVectorWorld(),azi,elev);
	// Position des Objektes
	owner->GetAziElev	(*to,azi2,elev2);
	azi		-= azi2;
	azi		=  Alg_Rad2Deg(azi);
	if (azi<-180)	azi  += 360; else
	if (azi> 180)	azi  -= 360;
	return abs(azi);
}

zBOOL oCMag_Book :: IsInMovement()
{
	return in_movement;
}

zBOOL oCMag_Book :: IsActive()
{
	return FALSE;
}

oCSpell* oCMag_Book :: GetSelectedSpell ()
{
	if( spells.GetNumInList() == 0 )	return NULL;
	if (spellnr >= spells.GetNum())		return NULL;
	if (spellnr < 0)					return NULL;
	if (!zDYNAMIC_CAST<oCSpell>(spells[spellnr])) return NULL;			// safety
	return spells[spellnr];
}

int oCMag_Book :: GetSelectedSpellNr()
{
	return spellnr;
}

void oCMag_Book :: Spell_Open (int nr)
{
	zERR_MESSAGE(8,0,"C: MAG: Spell_Open");
	// Disable Decal
	spells[nr] -> Open();
}

void oCMag_Book :: StopSelectedSpell ()
{   
	zERR_MESSAGE(8,0,"C: MAG: StopSelectedSpell");
	if (GetSelectedSpell()) Spell_Stop(spellnr);
}

void oCMag_Book :: KillSelectedSpell ()
//	[Ulf] : Bei Levelwechsel Spell sofort killen.
{   
	zERR_MESSAGE(8,0,"C: MAG: KillSelectedSpell");

	if (!wld) return; // ohne welt kein spell
	oCSpell *spell = GetSelectedSpell();
	if (!spell) return;
	
	zVEC3  pos;
	int id			= spell -> GetSpellID();
	zCVob* mvob		= spell ->GetVob();
	if (mvob) pos	= mvob->GetPositionWorld();

	int keyNo = spell -> Kill();
	// In einem Kill wird der Spell bereits geloescht !
	//   delete spells[spellnr];	// [Moos] Leakfix; Probleme (nicht zuendegeführte spells...) möglich...
	spells[spellnr]			= CreateNewSpell(id);
	spells[spellnr]->keyNo	= keyNo;

	// In Welt einsetzen
 	mvob	=  spells[spellnr]->GetVob();
	//mvob	-> SetVisual		(spellitems[spellnr]->GetVisual());
	S_CopyItemVisual(spellitems[spellnr], mvob);

    if (show_handsymbol || IsOpen()){
        mvob	-> SetPositionWorld	(pos);	
    	wld		-> AddVob			(mvob);
    }

	show_particles		= FALSE;
	open_delay_timer	= MAG_OPEN_DELAY;
}

void oCMag_Book :: Spell_Stop (int nr)
{
	zERR_MESSAGE(8,0,"C: MAG: Spell_Stop");

	if (!wld) return; // ohne welt kein spell
	if ( nr<0 )						  return;

	zVEC3  pos;
	int	   id;
	int	   keyNo;
	zCVob* mvob;

	if ( nr<=spells.GetNumInList()-1 ) 
	{
		id		= spells[nr] -> GetSpellID();
		// FIXME  Stop löscht den gesamten Spell !!! 
		mvob	= spells[nr]->GetVob();

		if (mvob) 
			pos = mvob->GetPositionWorld();

		keyNo	= spells[nr] -> Stop();
		zRELEASE_ACCT(spells[nr]); // [Moos] Leakfix; Probleme (nicht zuendegeführte spells...) möglich...
	}
	
	spells[nr]  = CreateNewSpell(id);
	spells[nr]->keyNo = keyNo;

	// In Welt einsetzen
 	mvob		= spells[nr]->GetVob();
//	mvob       -> SetVisual(spellitems[nr]->GetVisual());
	S_CopyItemVisual(spellitems[nr], mvob);

    if (show_handsymbol || IsOpen())
    {  // [Moos] aber nur, wenn der Spell auch angezeigt werden soll!
	    mvob	   -> SetPositionWorld(pos);	
	    wld->AddVob(mvob);
    	// 
    	show_particles		= FALSE;
	    open_delay_timer	= MAG_OPEN_DELAY;
    }
}

void oCMag_Book :: Left()
{
	if (!IsOpen()) return;
	if (IsInMovement()) return;
	if (spells.GetNumInList()==1) return;

#ifdef _DEBUG
    CheckConsistency();
#endif

	in_movement = TRUE;
	// Close old Effect
	Spell_Stop(spellnr);	// Complete Delete ? FIXME:  Muss das sein ???
	action		= 1;
	t1			= 0;
	targetdir	= -step;

	spellnr ++;
	if (spellnr>=spells.GetNumInList()) spellnr = 0;
}

void oCMag_Book :: Right()
{
	if (!IsOpen()) return;
	if (IsInMovement()) return;
	if (spells.GetNumInList()==1) return;

#ifdef _DEBUG
    CheckConsistency();
#endif

	in_movement = TRUE;
	// Close old Effect
	Spell_Stop(spellnr);		
	action		= 1;
	t1			= 0;
	targetdir	= step;

	spellnr --;
	if (spellnr<0) spellnr = spells.GetNumInList()-1;
}

zVEC3 oCMag_Book :: CalcPos(zCVob* vob, zREAL angle)
{
	zVEC3 targetpos = owner -> GetPositionWorld();
	zREAL y			= targetpos[VY];
	zMATRIX4 trafo	= Alg_Rotation3DN ( zVEC3(0,1,0), angle) * owner -> trafoObjToWorld; // [Moos] ex trafo
	targetpos		= targetpos + trafo.GetAtVector() * MAG_DISTANCE;	
	targetpos[VY]	= y + MAG_HEIGHT;	
	if (angle >  180) angle -= 360; else
	if (angle < -180) angle += 360;
	angle = abs(angle);
	targetpos[VY]  -= ( MAG_ANGLEYDIF * angle );
	// Setting the Alpha
	if (dynamic_cast<zCDecal*>(vob->GetVisual())) 
	{	
		// Set Decal Flags
		zCDecal *decal = (zCDecal *)vob->GetVisual();
		decal->decalMaterial->SetAlpha(255-angle);
	}
	return targetpos;
}

zBOOL oCMag_Book :: DoOpen()
{
	t1 += ztimer.GetFrameTimeF() / MAG_SELECT_TIME;
	if (t1>1) t1 = 1;

	startpos = owner -> GetPositionWorld();
	for (int i=0; i<spells.GetNumInList(); i++) 
	{
		// Calculating angle -> Valid : -180 <= angle <= 180
		//changed[dennis]
		zCVob* vob		= spells[i]->GetVob();
		//zCVob* vob		= circleitems[i];
		zREAL  angle	= (i-spellnr)*step;
		targetpos		= CalcPos(vob,angle);
		// Getting the Position...
		zVEC3 curpos	= EasePos(t1,startpos,targetpos);
		if (vob) vob -> SetPositionWorld( curpos );
	}
	return (t1>=1);
};


/* ----------------------------------------------------------------------
	
    oCMag_Book :: DoClose()	

	1.09.2000	[Moos]	
                Fix für den "Rune im Arsch"-Bug

   ---------------------------------------------------------------------- */


zBOOL oCMag_Book :: DoClose()
{
	if (!wld) return TRUE;
	t1 += ztimer.GetFrameTimeF() / MAG_SELECT_TIME;
	if (t1>1) t1 = 1;

	targetpos = owner -> GetPositionWorld();
	for (int i=0; i<spells.GetNumInList(); i++) 
	{
		// Calculating angle -> Valid : -180 <= angle <= 180
		//changed[dennis]
		zCVob* vob		= spells[i]->GetVob();
		zREAL  angle	= (i-spellnr)*step;
		startpos		= CalcPos(vob,angle);
		// Getting the Position...
		zVEC3 curpos	= EasePos(t1,startpos,targetpos);
		if (vob) vob -> SetPositionWorld( curpos );
	}

	if (t1>=1) 
	{
		// Ready, now Remove them all
		for (int i=0; i<spells.GetNumInList(); i++) 
		{
			zCVob* v =  spells[i]->GetVob();
			if (v && v->RegisteredInWorld())
			{
				zERR_MESSAGE(10,0," removing vob subtree: " + v->GetObjectName());
                v -> GetHomeWorld() -> RemoveVobSubtree(v); // [Moos] sicherer mit Subtree
			}
			//changed[dennis]

			//zCVob* v =  circleitems[i];

			if (i==spellnr) 
			{
				if (remove_all) 
				{
					// Stop active spell
					Spell_Stop(spellnr);
            
                    // [Moos]: Das Entfernen muss wiederholt werden, da
                    // Spell_Stop einen neuen Spell mit neuem Effekt in 
                    // die Welt einfügt.
			        zCVob* v =  spells[i]->GetVob();
			        if (v && v->RegisteredInWorld())
					{
						zERR_MESSAGE(10,0," removing vob subtree: " + spells[spellnr]->GetVob()->GetObjectName());
                        v -> GetHomeWorld() -> RemoveVobSubtree(v); // [Moos] sicherer mit Subtree
					}
				} 
				else continue;
			} 

			
		}
		//circleitems.DeleteList();
		action		= 0;
		in_movement = FALSE;
		open		= FALSE;

		// Activate Effekt, falls Delaytimer noch nicht am Ende
		show_particles = FALSE;
		open_delay_timer= 0.0f;
		
		// Remove HandSymbol ?
		SetShowHandSymbol(!remove_all);

		return TRUE;
	} 
	else return FALSE;

};

/* ----------------------------------------------------------------------
	
    oCMag_Book :: SetFrontSpell()	

	9.11.2000	[Moos]	
                Fix für die Hotkeys


   ---------------------------------------------------------------------- */

void oCMag_Book :: SetFrontSpell(int snr)
{
	zERR_MESSAGE(8,0,"C: MAG: SetFrontSpell");

#ifdef _DEBUG
    CheckConsistency();
#endif

	oCNpc* ownerNpc = dynamic_cast<oCNpc*>(owner);

	if (ownerNpc && (ownerNpc->GetWeaponMode()!=NPC_WEAPON_MAG)) 
	{
		spellnr = snr;
		return;
	}

	zBOOL isInMovement = owner->GetInMovement();
	if (isInMovement) owner->EndMovement();

	// Close old Effect
	if (snr!=spellnr) 
	{
		Spell_Stop(spellnr);	

		if (!IsOpen()) 
		{
			// Diesen Spell aus Welt entfernen	
			zERR_MESSAGE(10,0," removing vob: " + spells[spellnr]->GetVob()->GetObjectName());
			if (wld) wld->RemoveVob(spells[spellnr]->GetVob());		
		}
	}

	// Springe zu diesem Spell ohne weiteres "Turnen" des Kranzes
	spellnr		= snr;
	in_movement = FALSE;
	action		= 0;

	if (IsOpen()) 
	{
		// Falls Zauberkranz auf, diesen neu positionieren.
		for (int i=0; i<spells.GetNumInList(); i++) {
			// Calculating angle -> Valid : -180 <= angle <= 180
			//changed[dennis]
			zCVob* vob		= spells[i]->GetVob();
			zREAL  angle	= (i-spellnr)*step;
			targetpos		= CalcPos(vob,angle);
			// Getting the Position...
			if (vob) vob -> SetPositionWorld( targetpos );
		}
	}
	else
	{
		// Spell auf der Hand initialisieren
		Spell_Setup(spellnr,dynamic_cast<oCNpc*>(owner),NULL);
	}

	if (isInMovement) owner->BeginMovement();

}

zBOOL oCMag_Book :: DoTurn()
{
	t1 += ztimer.GetFrameTimeF() / MAG_SELECT_TIME;
	if (t1>1) t1 = 1;
	
	zREAL	dir			= Ease (t1,0,targetdir);
	zREAL	subdir;
	if (targetdir > 0)	subdir =  1;	
	else				subdir = -1;
	
	for (int i=0; i<spells.GetNumInList(); i++) 
	{
		//changed[dennis]
		zCVob* vob		=  spells[i]->GetVob();
		zREAL angle		= (i-spellnr-subdir)*step + dir;
		zVEC3 pos		= CalcPos(vob,angle);		
		if( vob ) vob -> SetPositionWorld ( pos );
	}
	return (t1>=1);
}

void oCMag_Book :: ShowHandSymbol()
// Magie-Symbol am rechten Handslot ausrichten
{
	if ((spellnr>=0) && GetSelectedSpell()) 
	{
		zCVob* vob = GetSelectedSpell()->GetVob();
		if (vob) 
		{
            //zERR_ASSERT(vob->GetVisual());
			zMATRIX4 trafo = owner -> GetTrafoModelNodeToWorld("ZS_RIGHTHAND");
			vob -> SetPositionWorld(trafo.GetTranslation());
		}		
	}
}


// diese methode setzt fest, ob der aktuelle Spruch (Typ: oCSpell) angezeigt werden soll, oder nicht
// assert: ein open
void oCMag_Book :: SetShowHandSymbol (zBOOL flag)
{
 	if (!wld) return;
	// Remove ?
	// Nicht removen, wenn open==TRUE, weil dann kompletter Zauberkranz sichtbar ist
	if (!flag && !IsOpen() && show_handsymbol && (spellnr>=0)) 
	{
		if (GetSelectedSpell()) 
		{
			Spell_Stop(spellnr);
			zCVob* v = GetSelectedSpell()->GetVob();
			if (v && v->RegisteredInWorld()) 
			{
				zERR_MESSAGE(10,0," removing vob: " + v->GetObjectName());
				v -> GetHomeWorld() -> RemoveVob(v);			
			}
		}
	}
	show_handsymbol= flag;
	// Partikel anschmeissen ? Nur wenn Zauberkranz nicht offen ist (open!=TRUE)
	if (!IsOpen() && show_handsymbol) 
	{		
		// Position setzen !
		oCSpell *selectedSpell = GetSelectedSpell();
		if (!selectedSpell) return;
		zCVob* v = selectedSpell->GetVob();
		if (v && !v->RegisteredInWorld()) wld -> AddVob(v);			

		Spell_Setup		(spellnr, dynamic_cast<oCNpc*>(owner),NULL);
		ShowHandSymbol	();
	}
}

void oCMag_Book :: DoPerFrame()
{
	// Falls action noch laeuft diese vorher beenden
	if ((action==0) && !open && !show_handsymbol) return;
	
	zBOOL ready = TRUE;
	switch (action) {
		case 1		:	ready = DoTurn();	
						if (ready) zCView::stdoutput->Printwin(spells[spellnr]->GetName()+"\n");
						break;
		case 2		:	ready = DoOpen();
						break;
		case 3		:	ready = DoClose();
						break;
	}

 	if (ready) action = 0;
	in_movement = !ready;

	// Handsymbol anzeigen ?
	if (show_handsymbol) ShowHandSymbol();

	if( IsOpen() )
	{
		// Wenn offen, dann Zeit fürs öffnen des Partikeleffektes zählen
		if ((action==0) && (!show_particles)) 
		{
			if (GetSelectedSpell() && GetSelectedSpell()->GetVob()->RegisteredInWorld()) 
			{
				// Partikeleffekt noch nicht angezeigt
				open_delay_timer -= ztimer.GetFrameTimeF();
				if (open_delay_timer<=0) 
				{
//					GetSelectedSpell()->Reset();
					Spell_Open(spellnr);
					show_particles = TRUE;
				}
			}
		}

		for (int i=0; i<spells.GetNumInList(); i++) 
		{
			//changed[dennis]
			zCVob* vob		=  spells[i]->GetVob();
			if( vob )
			{
                zERR_ASSERT(vob->GetVisual());
    
				vob->ResetRotationsLocal();
				zMAT4 temp;
				temp.MakeIdentity();
				temp[0][0] = ((zCVob*)owner)->trafoObjToWorld[0][0];
				temp[0][1] = ((zCVob*)owner)->trafoObjToWorld[0][1];
				temp[0][2] = ((zCVob*)owner)->trafoObjToWorld[0][2];

				temp[1][0] = ((zCVob*)owner)->trafoObjToWorld[1][0];
				temp[1][1] = ((zCVob*)owner)->trafoObjToWorld[1][1];
				temp[1][2] = ((zCVob*)owner)->trafoObjToWorld[1][2];

				temp[2][0] = ((zCVob*)owner)->trafoObjToWorld[2][0];
				temp[2][1] = ((zCVob*)owner)->trafoObjToWorld[2][1];
				temp[2][2] = ((zCVob*)owner)->trafoObjToWorld[2][2];

				temp.PostRotateX(-90.0f);
				vob->trafoObjToWorld[0][0] =	temp[0][0];
				vob->trafoObjToWorld[0][1] =	temp[0][1]; 
				vob->trafoObjToWorld[0][2] =	temp[0][2]; 

				vob->trafoObjToWorld[1][0] =	temp[1][0]; 
				vob->trafoObjToWorld[1][1] =	temp[1][1]; 
				vob->trafoObjToWorld[1][2] =	temp[1][2]; 

				vob->trafoObjToWorld[2][0] =	temp[2][0]; 
				vob->trafoObjToWorld[2][1] =	temp[2][1]; 
				vob->trafoObjToWorld[2][2] =	temp[2][2]; 
				//vob->RotateLocalX(-90.0f);
				vob->UpdateVisualDependencies();
			}
		}

		//zCCamera::activeCam->Activate();
		for( int j = 0; j < spells.GetNum(); j++ )
		{
			//calc new pos here
			zPOINT3	  ProjPoint1	= zCCamera::activeCam->Transform( spells[j]->GetVob()->GetPositionWorld() /*circleitems[j]->GetPositionWorld()*/ );
			zPOINT2	  ProjPoint2;
			
			zCCamera::activeCam->Project (&ProjPoint1, ProjPoint2[VX], ProjPoint2[VY]);
			screen->Print(screen->anx(ProjPoint2[VX]-20),screen->any(ProjPoint2[VY]-20), (char)spells[j]->keyNo+3);
			//DELETE THIS LATER !!!!!!!!!!
			if( ogame->GetShowDebug() ) screen->Print(screen->anx(ProjPoint2[VX]),screen->any(ProjPoint2[VY]-50), spellitems[j]->GetName());
			if( spellitems[j]->MultiSlot() )
			{
				screen->Print(screen->anx(ProjPoint2[VX]+20),screen->any(ProjPoint2[VY]+20), (char)(spellitems[j]->GetAmount())+0);
			}
		}
	}
}

//changed[dennis]
int oCMag_Book::GetNoOfSpells( void )
{
	return spells.GetNumInList();
}

oCSpell* oCMag_Book::GetSpell(oCItem* item,int &no)
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	int i = 0;
	if( spells.GetNumInList() == 0 )
	{
		no = 32565;
		return NULL;
	}
	while( item != spellitems[i] && ++i < spells.GetNumInList());
	if ( i < spells.GetNumInList() )
	{
		no = i;
		return spells[i];
	}
	else
	{
		no = 32565;
		return NULL;
	}
}

oCSpell* oCMag_Book::GetSpell(int no)
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	if( spells.GetNumInList() == 0 ) return NULL;
	if( no <= spells.GetNumInList() ) return spells[no];
	else return NULL;
}

oCItem* oCMag_Book::GetSpellItem( int no )
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	if( no < spells.GetNumInList() ) return spellitems[no];
	else return NULL;
}

oCItem* oCMag_Book::GetSpellItem( oCSpell* spell )
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	int i = 0;
	while( spell != spells[i] && ++i < spells.GetNumInList());
	if ( i < spells.GetNumInList() ) return spellitems[i];
	else return NULL;
}

void oCMag_Book::NextRegisterAt( int slot )
{
#ifdef _DEBUG
    CheckConsistency();
#endif

    if (slot >= 0 && slot < 32000) // [Moos] Sanity-Fix für Dennis-Insanity
	    nextRegister = slot;
}

oCSpell* oCMag_Book::GetSpellByKey( int key )
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	for( int i = 0; i < spells.GetNumInList(); i++ )
	{
		if( spells[i]->keyNo == key ) return spells[i];
	}
	return NULL;
}

oCItem* oCMag_Book::GetSpellItemByKey( int key )
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	for( int i = 0; i < spells.GetNumInList(); i++ )
	{
		if( spells[i]->keyNo == key ) return spellitems[i];
	}
	return NULL;
}

int oCMag_Book::GetNoOfSpellByKey( int key )
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	if( keys & (1<<(key-1)))
	{
		int i = 0;
		while( spells[i]->keyNo != key && (i++ < spells.GetNumInList()-1) );
		return i+1;
	}
	else return 0;
}

int oCMag_Book::GetKeyByItem( oCItem *item )
{
#ifdef _DEBUG
    CheckConsistency();
#endif

	int no = 0;
	oCSpell *temp = GetSpell( item, no );
	if( temp ) return (temp->keyNo);
	return 32565;
}

#pragma warning( default: 4244 ) 
