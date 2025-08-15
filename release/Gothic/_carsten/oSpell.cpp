/******************************************************************************** 
 
     $Workfile:: oSpell.cpp           $                $Date:: 17.04.01 17:44   $
     $Revision:: 102                  $             $Modtime:: 17.04.01 17:44   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Carsten/oSpell.cpp $
 * 
 * 102   17.04.01 17:44 Edenfeld
 * Null Pointer Crash Patch 1.08 abgefangen
 * 
 * 101   18.02.01 22:04 Speckels
 * 
 * 100   18.02.01 12:17 Edenfeld
 * 
 * 99    16.02.01 18:04 Edenfeld
 * Telekinesis Fix Blablabla 
 * 
 * 98    16.02.01 12:42 Edenfeld
 * Telekinesis nicht levitier Prob behoben
 * 
 * 97    16.02.01 7:37 Edenfeld
 * Plotkiller Telekinesis Scroll Bugfix
 * 
 * 96    16.02.01 5:01 Edenfeld
 * Chainlightning Scroll-verschwindet-nicht-Bug gefixt
 * 
 * 95    16.02.01 2:19 Edenfeld
 * Telekinesis: Target fällt durchs Mesh FIX
 * 
 * 94    10.02.01 21:49 Moos
 * Crashfixes und Scroll-nichtverbrauch-fixes
 * 
 * 93    9.02.01 22:39 Edenfeld
 * VisualFX Memleaks work in progress
 * 
 * 92    6.02.01 17:07 Keskenti
 * 
 * 91    5.02.01 20:55 Edenfeld
 * 
 * 90    2.02.01 23:40 Edenfeld
 * 
 * 89    25.01.01 17:11 Edenfeld
 * 
 * 88    24.01.01 22:43 Edenfeld
 * 
 * 87    23.01.01 22:11 Edenfeld
 * 
 * 86    23.01.01 19:12 Keskenti
 * 
 * 85    23.01.01 18:58 Edenfeld
 * 
 * 84    18.01.01 0:06 Edenfeld
 * 
 * 83    17.01.01 17:28 Edenfeld
 * 
 * 82    17.01.01 11:26 Moos
 * 
 * 81    10.01.01 16:26 Wohlers
 * 
 * 80    8.01.01 17:47 Edenfeld
 * 
 * 79    20.12.00 17:10 Moos
 * 
 * 78    18.12.00 15:52 Keskenti
 * 
 * 77    18.12.00 15:51 Edenfeld
 * 
 * 76    18.12.00 15:37 Keskenti
 * 
 * 75    13.12.00 16:26 Edenfeld
 * 
 * 74    13.12.00 16:23 Keskenti
 * 
 * 73    13.12.00 16:15 Edenfeld
 * 
 * 72    30.11.00 15:03 Wohlers
 * 
 * 71    24.11.00 15:06 Edenfeld
 * 
 * 70    22.11.00 16:57 Edenfeld
 * 
 * 69    21.11.00 20:48 Edenfeld
 * 
 * 68    20.11.00 23:04 Edenfeld
 * 
 * 67    13.11.00 23:40 Edenfeld
 * 
 * 66    10.11.00 17:18 Moos
 * 
 * 65    9.11.00 18:30 Edenfeld
 * 
 * 64    8.11.00 17:35 Edenfeld
 * 
 * 63    8.11.00 15:32 Edenfeld
 * 
 * 62    7.11.00 21:07 Edenfeld
 * 
 * 61    2.11.00 22:07 Edenfeld
 * 
 * 60    1.11.00 17:58 Moos
 * 
 * 59    31.10.00 20:27 Keskenti
 * 
 * 58    31.10.00 13:08 Edenfeld
 * 
 * 57    26.10.00 16:49 Edenfeld
 * 
 * 56    23.10.00 13:21 Edenfeld
 * 
 * 55    21.10.00 18:13 Edenfeld
 * 
 * 54    18.10.00 19:17 Moos
 * 
 * 53    18.10.00 17:58 Moos
 * 
 * 52    10.10.00 19:06 Edenfeld
 * 
 * 51    5.10.00 15:33 Edenfeld
 * 
 * 50    4.10.00 17:47 Edenfeld
 * 
 * 49    23.09.00 2:58 Edenfeld
 * 
 * 48    22.09.00 19:57 Edenfeld
 * 
 * 47    21.09.00 20:33 Edenfeld
 * 
 * 46    21.09.00 19:35 Edenfeld
 * 
 * 45    21.09.00 4:25 Edenfeld
 * 
 * 44    19.09.00 23:28 Edenfeld
 * 
 * 43    15.09.00 16:33 Edenfeld
 * 
 * 42    15.09.00 0:36 Edenfeld
 * GetLevel
 * 
 * 41    7.09.00 21:07 Wohlers
 * RigidBody in GetRigidBody an Engine-Aenderungen von Dieter angepasst
 * 
 * 40    2.09.00 13:24 Wohlers
 * 
 * 39    2.09.00 7:48 Edenfeld
 * 
 * 38    31.08.00 17:54 Edenfeld
 * 
 * 37    31.08.00 17:49 Edenfeld
 * 
 * 36    31.08.00 17:43 Edenfeld
 * 
 * 34    31.08.00 16:56 Edenfeld
 * 
 * 33    31.08.00 13:51 Edenfeld
 * 
 * 32    30.08.00 23:38 Edenfeld
 * 
 * 31    29.08.00 14:16 Edenfeld
 * 
 * 30    24.08.00 11:34 Moos
 * new durch zNEW ersetzt
 * 
 * 29    23.08.00 3:31 Edenfeld
 * 
 * 28    22/08/00 14:02 Luesebrink
 * 
 * 27    22/08/00 10:23 Luesebrink
 * 
 * 26    21.08.00 18:38 Edenfeld
 * 
 * 25    21.08.00 13:34 Edenfeld
 * 
 * 24    18.08.00 2:06 Edenfeld
 * 
 * 23    17.08.00 20:54 Edenfeld
 * 
 * 22    17.08.00 20:42 Edenfeld
 * 
 * 21    15.08.00 17:50 Wohlers
 * 
 * 20    14.08.00 21:27 Edenfeld
 * 
 * 19    4.08.00 12:51 Wohlers
 * 
 * 18    2.08.00 14:25 Edenfeld
 * 
 * 17    2.08.00 12:19 Edenfeld
 * 
 * 16    1.08.00 17:31 Edenfeld
 * 
 * 15    31.07.00 16:25 Edenfeld
 * 
 * 14    28.07.00 13:32 Edenfeld
 * 
 * 13    21.07.00 17:04 Edenfeld
 * 
 * 12    14.07.00 13:43 Edenfeld
 * 
 * 11    5.07.00 12:22 Wohlers
 * 
 * 9     5.06.00 22:36 Wohlers
 * uSrc 05.06.00
 * 
 * 8     29.05.00 18:36 Wohlers
 * 
 * 7     24.05.00 20:29 Wohlers
 * Gothic 0.83
 * 
 * 6     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 5     11.05.00 0:31 Wohlers
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 5     8.05.00 19:32 Wohlers
 * Gothic 0.80 - Inventory
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 1     20.04.00 11:52 Admin
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 7     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 6     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 5     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 4     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zcore.h"
#include "zObject.h"
#include "z3d.h"

#include "zview.h"
#include "zPhysics.h"

#include "oSpell.h"
#include "oMagic.h"
#include "oNpc.h"
#include "oMobInter.h"
#include "oAIHuman.h"
#include "oAnictrl.h"
#include "zAICamera.h"
#include "oMagic.h"
#include "oWorld.h"
#include "oGame.h"

#include "oVisFX.h"
#include "oVisFX_MultiTarget.h"
//#include "oVisFX_Lightning.h"


#include "zWaynet.h"
#include "zEventMan.h"
#include "oNpcMessages.h"
#include "zInput_Win32.h"
#include "zAccount.h"

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 


oCSpell :: oCSpell ()
{
	InitValues(0);
}

oCSpell :: oCSpell (int _spellID)
{
	InitValues(_spellID);
}


oCSpell :: ~oCSpell ()
{
	// [changed] Ulf	:	Wenn ich das Stop ausführe, nibbelt das Game beim runterfahren ab 
	//						(Speicherüberschreiber!)
	// [changed] Carsten:	Speicherüberschreiber behoben, mal schauen obs geht
	// [changed] Roman	:	Stop & Release for Control Warn FX in case it is still active
	// [changed] Carsten:	Control Warn FX Kill statt Stop
	if (effect) 
	{
		effect->Kill();
		zRELEASE_ACCT(effect);
	};

	if ( controlWarnFX )
	{
		controlWarnFX->Kill();
		zRELEASE_ACCT(controlWarnFX);
	}

	spellCaster		= NULL;
	spellCasterNpc	= NULL;
	spellTarget		= NULL;
	spellTargetNpc	= NULL;
    zRELEASE_ACCT(saveNpc);  // [Moos]
};

void oCSpell :: InitValues(int _spellID)
{
	spellID			= _spellID;
	spellCaster		= NULL;
	spellCasterNpc	= NULL;
	spellTarget		= NULL;
	spellTargetNpc	= NULL;
	saveNpc			= NULL;
	effect			= NULL;

	manaTimer		= 0.0f;
	manaInvested	= 0;
	spellLevel		= 1;
	manaInvestTime	= 2000;
	damageType		= oEDamageType_Edge;
	damagePerLevel	= 0;
	spellStatus		= SPL_STATUS_CANINVEST;
	spellEnabled	= FALSE;
	spellInitDone	= FALSE;
	spellEnergy		= NPC_ATR_MANA;
	controlWarnFX	= 0;
	
	canBeDeleted	= TRUE;
	timerEffect		= 0.0f;
 
	up				= 0.0f;
	hoverY			= 0.0f;
	hoverOld		= 0.0f;
	hoverDir		= 1.0f;
	canChangeTargetDuringInvest = TRUE;
	canTurnDuringInvest=TRUE;
	isMultiEffect		= FALSE;			// Effect Class is oCVisFX_MultiTarget if set to 1
	targetCollectAlgo	= TARGET_COLLECT_FOCUS_FALLBACK_NONE;
	targetCollectType	= TARGET_FLAG_NPCS;
	targetCollectRange	= 10000;		// 10 m default
	targetCollectAzi	= 180;
	targetCollectElev	= 90;

	InitByScript ( GetSpellInstanceName( _spellID ) );

	keyNo = 32565;
};


zSTRING	oCSpell :: GetSpellInstanceName(const int _spellID) const
{
	zERR_BOUNDS(_spellID,0,SPL_MAX_SPELL);

	const zSTRING failString = zSTRING("default");
	zSTRING res;
	zCPar_Symbol *sym = parser.GetSymbol("spellFXInstanceNames");
	if (!sym) return failString;
	sym->GetValue(res,_spellID);
	return res;
};

oCVisualFX* oCSpell :: CreateEffect()
{
	zERR_MESSAGE(8,0,"C: SPL: CreateEffect");
	// VisualFX erzeugen
	if ( isMultiEffect )					effect = zNEW(oCVisFX_MultiTarget());
	else									effect = zNEW(oCVisualFX());

	effect -> SetSpellTargetTypes	(targetCollectType);
	effect -> SetDamage				( damagePerLevel );
	effect -> SetDamageType			( damageType );
	effect -> SetSpellType			( GetSpellID() );
	effect -> SetSpellCat			( GetCategory() );
	effect -> SetByScript			( "SPELLFX_"+GetSpellInstanceName(GetSpellID()) );

	return effect;
}

void oCSpell :: InitByScript(const zSTRING& name)
{

	zERR_MESSAGE(8,0,"C: SPL: InitByScript");
	// Skript-Logik-Daten 
	int index =		parser.GetIndex("SPELL_" + name);
	if (index>=0)	parser.CreateInstance(index,&manaInvestTime);
	else			zERR_WARNING("U: SPL: Spell-Instance "+name+" not found.");

	effect			= CreateEffect();

	// Decal erzeugen
	SetEnabled		(TRUE);
	SetObjectName	(name);

	manaTimer		= 0.0f;
	manaInvested	= 0;
	spellLevel		= 1;
}

void oCSpell :: SetEnabled(zBOOL enabled)
{
	zERR_MESSAGE(8,0,"C: SPL: SetEnabled");
	spellEnabled = enabled;

	zCVob* vob = GetVob();
	if (!vob) return;

	vob->SetShowVisual(enabled);	
}

zBOOL oCSpell :: GetEnabled()
{
	return spellEnabled;
}

void oCSpell :: Setup (zCVob* caster, zCVob* target, const zBOOL a_bIgnoreCastState) 
{
	// status unabhängige methode, wird sowohl in der init phase, als auch während der invest
	// phase aufgerufen

	zERR_MESSAGE(8,0,"C: SPL: Setup");
	if (!effect)											   return;
	if (spellStatus == SPL_STATUS_CAST && !a_bIgnoreCastState) return;

	// hat das target keine dyn collision, dann darf es auch nicht als target ans visualisierungs-
	// system weitergereicht werden (??? ist das gut so ???)
	if (target != NULL					 && 
		target->GetCollDetDyn() == FALSE && 
		!zDYNAMIC_CAST<oCNpc>(target)) 
	{
		target = 0;
	}

	if ( spellInitDone				&& 
		(spellTarget==target)		&& 
		(target != 0) )
	{
		return;
	}

	if (spellTarget) 
	{
		// Kein neues Target aussuchen, waehrend investiert wird.
		if (!canChangeTargetDuringInvest && (manaTimer>0.0f)) return;

		// Ziel hat sich geändert. Das alte Ziel "befreien"
		StopTargetEffects(spellTarget);
	}

	// Ziel übergeben
	spellTarget		= target;
	spellTargetNpc	= zDYNAMIC_CAST<oCNpc>(spellTarget);

	// Caster
	spellCaster		= caster;
	spellCasterNpc	= zDYNAMIC_CAST<oCNpc>(spellCaster);

	// Den Effect readien.

	if (effect)	
	{	
		zBOOL canBeInvested = TRUE;
		zCArray <zCVob*>	resVobList;

		if ( (GetSpellID() == SPL_LIGHT || GetSpellID() == SPL_PALLIGHT) &&
			  spellCasterNpc != NULL									 &&
			 (spellCasterNpc->IsSpellActive(SPL_LIGHT) || spellCasterNpc->IsSpellActive(SPL_PALLIGHT) ) )
		{
			canBeInvested = FALSE;
		}
		else if	(targetCollectAlgo ==  TARGET_COLLECT_NONE)						
		{
			effect->Init(caster,0	  ); 
		}
		else if (targetCollectAlgo ==  TARGET_COLLECT_CASTER)
		{
			effect->Init(caster,caster); 
		}
		else if (targetCollectAlgo ==  TARGET_COLLECT_FOCUS)
		{
			if (IsValidTarget(target)) 
			{
				effect->Init(caster,target); 
			}
			else canBeInvested = FALSE;
		}
		else if (targetCollectAlgo ==  TARGET_COLLECT_FOCUS_FALLBACK_NONE)		
		{
			if (IsValidTarget(target)) 
			{
				effect->Init(caster,target);
			}
			else effect->Init(caster,0	  ); 
		}
		else if (targetCollectAlgo ==  TARGET_COLLECT_FOCUS_FALLBACK_CASTER)	
		{
			if (IsValidTarget(target)) 
			{
				effect->Init(caster,target); 
			}
			else effect->Init(caster,caster); 
		}
		else if (targetCollectAlgo ==  TARGET_COLLECT_ALL				|| 
			     targetCollectAlgo ==  TARGET_COLLECT_ALL_FALLBACK_NONE || 
				 targetCollectAlgo ==  TARGET_COLLECT_ALL_FALLBACK_CASTER )
		{
			if ( spellInitDone )
			if ( !(ogame->GetWorld()->GetMasterFrameCtr() & 3)  ) return;		// nur alle drei frames die spell trajectory updaten
			// Packe alle Target in eine Liste.
			// 1. In Reichweite		( dist )
			// 2. Sichtbar			( Angle +- 60 )
			// 3. FreeLineOfSight	
			zTBBox3D box;
			zCArray <zCVob*>	targetvobs;
			// Erster Vob in ResultList muss der Spieler sein
			// Zweiter der FocusNsc
			resVobList.Insert(spellCaster);
			if (IsValidTarget(spellTarget)) resVobList.Insert(spellTarget);

			box.maxs = spellCaster->GetPositionWorld() + (targetCollectRange * zVEC3(1,1,1));
			box.mins = spellCaster->GetPositionWorld() - (targetCollectRange * zVEC3(1,1,1));

			if (spellCaster->GetHomeWorld()) spellCaster -> GetHomeWorld() -> CollectVobsInBBox3D(targetvobs, box);
			for (int i=0; i<targetvobs.GetNumInList(); i++) 
			{
				if ( dynamic_cast<oCNpc*>(targetvobs[i]) )
				{
					zCVob *v	= targetvobs[i];

					// Not the Caster himself
					if ( (spellTarget==v) || (spellCaster==v) ) continue;

					if ( IsValidTarget(v) ) resVobList.Insert(v);
				}
			}
			if (resVobList.GetNum()<2)
			{
				if		(targetCollectAlgo ==  TARGET_COLLECT_ALL_FALLBACK_CASTER)  resVobList.InsertEnd(spellCaster);
				else if (targetCollectAlgo !=  TARGET_COLLECT_ALL_FALLBACK_NONE)	canBeInvested = FALSE;
			}

			if (canBeInvested)
			{
				if	(isMultiEffect) 
				{
					effect->Init(resVobList);
				}
				else	
				{
					effect->Init(caster);
					effect->SetCollisionCandidates(resVobList);
				}
			}
		}

		if (!canBeInvested) 
		{
			spellStatus		= SPL_STATUS_DONTINVEST;
			spellTarget		= 0;
			spellTargetNpc	= 0;

			if (!spellInitDone) 
			{
				// spell konnte noch nicht mit einem Target initialisiert werden (target war ungültig)
				// zumindest muss aber einmal ein Init() aufgerufen werden, damit das visual sichtbar wird
				//
				if	(isMultiEffect) effect->Init(resVobList);
				else				effect->Init(spellCasterNpc);
			};

			spellInitDone	= FALSE;
		}
		else 
		{				
			spellStatus		= SPL_STATUS_CANINVEST;
			spellInitDone	= TRUE;
		};

	}
}

zBOOL oCSpell :: Invest ()
// Liefert True, falls naechster ManaPunkt investiert wurde.
{
	zERR_MESSAGE(8,0,"C: SPL: Invest");
	if (!effect) return FALSE;

	int manaLeft = 0;
	if (spellCasterNpc) manaLeft = spellCasterNpc->GetAttribute(spellEnergy);

	// InvestSpruch -> jederzeit ansprechbar zB. Telekinese
	if (manaLeft>0) 
	{	
		DoLogicInvestEffect();
	} 
	else 
	{
		// Mana Alle
		if (manaInvested>0) 
		{
			SetReleaseStatus();
			return TRUE;
		}
		return FALSE;
	}

	// erster manapunkt wird immer sofort investiert
	if (manaInvested == 0)	
	{
		spellCasterNpc -> CreatePassivePerception(NPC_PERC_ASSESSCASTER); // @@@ RICHTIG ?
		manaTimer += manaInvestTime;
	}
	else	
	{
		manaTimer += ztimer.GetFrameTimeF();
	}

	// Mana Investieren......
	if ( (manaTimer >= manaInvestTime) )
	{
		manaTimer -= manaInvestTime;

		// Zeit ist abgelaufen, naechster ManaPunkt wird investiert
		if (spellStatus == SPL_STATUS_CANINVEST || spellStatus == SPL_STATUS_CANINVEST_NO_MANADEC)
		{
			// Noch Mana übrig ?
			if (spellCasterNpc && manaLeft>0) 
			{
				// a) Skriptmethode aufrufen....

				CallScriptInvestedMana();

				if ( spellStatus == SPL_STATUS_CAST					|| 
					 spellStatus == SPL_STATUS_CANINVEST			|| 
					 spellStatus == SPL_STATUS_CANINVEST_NO_MANADEC ||	
					 spellStatus == SPL_STATUS_NEXTLEVEL )
				{
					// InvestCounter erhöhen	
					if ( manaInvested && (spellStatus == SPL_STATUS_CANINVEST) )
					{
						spellCasterNpc->ChangeAttribute(spellEnergy,-1);
					}
					manaInvested++;
				}
				else if (spellStatus & SPL_STATUS_FORCEINVEST)
				{
					manaInvested = spellStatus - SPL_STATUS_FORCEINVEST;
					spellCasterNpc->ChangeAttribute(spellEnergy,-manaInvested);
					spellStatus  = SPL_STATUS_CANINVEST;
				}
				
				// b) Aktion auslösen ? Spell casten.
				if (spellStatus == SPL_STATUS_CAST) {
					// Cast();
					return TRUE;
				} 
				// c) Aktion auslösen ? Spell beenden.
				if (spellStatus == SPL_STATUS_STOP) {
					// Stop();
					return TRUE;
				}

				// d) Aktion auslösen ? Nächster Level
				if (spellStatus == SPL_STATUS_NEXTLEVEL) 
				{
					spellStatus  = SPL_STATUS_CANINVEST;
					spellLevel ++;
					if (effect) effect->InvestNext();
					return TRUE;
				}

				return TRUE;
			}
		}
	}	
	return FALSE;
}

/* ----------------------------------------------------------------------
	
    oCSpell::Cast()	

	18.10.2000	[Moos]	
                deleteSpell hinzugefügt; spell löscht sich nun selbst bei Bedarf


   ---------------------------------------------------------------------- */


zBOOL oCSpell :: Cast()
// Returns TRUE, if casting was successful
{
	zERR_MESSAGE(8,0,"C: SPL: Cast");

    zBOOL deleteSpell = TRUE;

	StopTargetEffects(spellTarget);
	
	if (manaInvested>0) 
	{	
		if (effect)	
		{
			effect -> Cast();

			if ( (GetSpellID() != SPL_LIGHT) && (GetSpellID()!=SPL_PALLIGHT) ) 
			{
				zRELEASE_ACCT(effect); // [Moos] Leakfix; beim erzeugen des Effektes gab es ein AddRef. Wenn der Effekt gecastet ist, hat die Welt eine Referenz darauf.
			}
		}

		if (GetSpellStatus()==SPL_STATUS_CAST) deleteSpell = CastSpecificSpell ();
//        if (deleteSpell) delete this; // [Moos]

		return TRUE;
	} 

	spellStatus	= SPL_STATUS_CANINVEST;
	manaTimer	= 0.0f;

	return FALSE;
}

int oCSpell :: Stop()
{

	zERR_MESSAGE(8,0,"C: SPL: Stop");

	manaTimer		= 0.0f;
	manaInvested	= -1;
	spellLevel		= 1;
	spellStatus		= SPL_STATUS_CANINVEST;
	
	StopTargetEffects	(spellTarget);

	if (effect) 
	{
		effect -> Stop();
		zRELEASE_ACCT(effect);		
	}
	return keyNo;
}

int oCSpell :: Kill()
// [Ulf] : Brauche keyNo als Return-Wert (wie bei Stop)
{
	int tmpKeyNr = keyNo;

	zERR_MESSAGE(8,0,"C: SPL: Kill");

	StopTargetEffects	(spellTarget);

	if (effect) 
	{
		effect -> Kill	 ();
		zRELEASE_ACCT	 (effect); // [Moos] Crashfix; war vorher delete...
	}

	zRELEASE_ACCT_NONULL(this); // [Moos] Crashfix; war vorher delete...
	
	return tmpKeyNr;
}

void oCSpell :: Open()
{
	zERR_MESSAGE(8,0,"C: SPL: Open");
	if (effect) effect->Open();
}

void oCSpell :: Close()
{
	zERR_MESSAGE(8,0,"C: SPL: Close");
	if (effect) 
	{
		effect->Stop();
		zRELEASE_ACCT(effect);
	}
}

void oCSpell :: Reset()
{
	zERR_MESSAGE(8,0,"C: SPL: Reset");
	if (effect && (effect->GetState() < zVFXSTATE_INIT) ) effect->Reset();
}


void oCSpell :: StopTargetEffects(zCVob* vob)
{
	zERR_MESSAGE(8,0,"C: SPL: StopTargetEffects");
	// Opfer aus dem Magiezustand rausnehmen.
	// Animationen stoppen

	/*
	if (GetSpellID()==SPL_TELEKINESIS || GetSpellID()==SPL_TELEKINESIS2) 
	{
		if (vob) 
		{
			if (!vob->GetHomeWorld()) return;
			zVEC3 groundVec = zVEC3(0,-(vob->GetPositionWorld()[VY]-vob->GetBBox3DWorld().mins[VY]),0);
			if (!vob->GetHomeWorld()->TraceRayNearestHit(vob->GetPositionWorld(), groundVec+zVEC3(0,-1,0),vob, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE_NO_CD_DYN))
			{
				vob->SetPhysicsEnabled(TRUE);
				vob->GetRigidBody()->SetGravityEnabled(TRUE);
				vob->SetSleeping(FALSE);
				vob->GetRigidBody()->SetVelocity(zVEC3(0,-100,0));
			}		
		}
	}
	else if (GetSpellID()==SPL_CONTROL)
	{
	};
	*/
};

void oCSpell :: CallScriptInvestedMana()
{
	zERR_MESSAGE(8,0,"C: SPL: CallScriptInvestedMana");

	// Spelleffekt + Logic
	parser.SetInstance("SELF"	,spellCasterNpc);
	parser.SetInstance("OTHER"	,spellTargetNpc);
	int index = parser.GetIndex("SPELL_PROCESSMANA");
	if (index>0) spellStatus = *(int*)parser.CallFunc(index,manaInvested);
	else zERR_FAULT("C: Skript Func SPELL_PROCESSMANA unknown!");

};


zBOOL oCSpell::IsTargetTypeValid(zCVob *v, int targetCollectType)
{
	if (targetCollectType == TARGET_FLAG_ALL) return TRUE;

	zBOOL	valid	= FALSE;
	
	for (int i=0; i < NUM_TARGET_TYPES; i++)
	{
		int traceBit = 1<<i;
		if (targetCollectType & traceBit)
		{
			if (traceBit == TARGET_FLAG_ITEMS)
			{
				if ( zDYNAMIC_CAST<oCItem>(v) ) { 
					valid = TRUE; break; 
				};
			}
			else if ( traceBit == TARGET_FLAG_NPCS )	
			{
				oCNpc *vNpc = zDYNAMIC_CAST<oCNpc>(v);
				if (vNpc  && !vNpc->IsDead() ) { valid = TRUE; break; };
			}
			else if ( traceBit == TARGET_FLAG_ORCS )
			{
				oCNpc *vNpc = zDYNAMIC_CAST<oCNpc>(v);
				if (vNpc && !vNpc->IsDead() && vNpc->GetTrueGuild()>NPC_GIL_ORCS) { valid = TRUE; break; };
			}
			else if ( traceBit == TARGET_FLAG_HUMANS )
			{
				oCNpc *vNpc = zDYNAMIC_CAST<oCNpc>(v);
				if (vNpc && !vNpc->IsDead() && vNpc->GetTrueGuild()<NPC_GIL_HUMANS) { valid = TRUE; break; };
			}
			else if ( traceBit == TARGET_FLAG_UNDEAD )
			{
				oCNpc *npc = dynamic_cast<oCNpc*>(v);
				if ( npc && !npc->IsDead() &&
					(npc ->GetTrueGuild()==NPC_GIL_SKELETON					||
					 npc ->GetTrueGuild()==NPC_GIL_ZOMBIE					||
					 npc ->GetTrueGuild()==NPC_GIL_GOBBO_SKELETON			||
					 npc ->GetTrueGuild()==NPC_GIL_SUMMONED_GOBBO_SKELETON	||
					 npc ->GetTrueGuild()==NPC_GIL_SUMMONED_SKELETON		||	
					 npc ->GetTrueGuild()==NPC_GIL_SUMMONED_SKELETON		||	
					 npc ->GetTrueGuild()==NPC_GIL_SHADOWBEAST_SKELETON 
					 ))
				{
					valid = TRUE; 
					break; 
				};
			}
		}
	}

	return valid;
};

zBOOL oCSpell::IsValidTarget(zCVob *v)
{
	if (targetCollectAlgo == TARGET_COLLECT_CASTER)
	{
		if (v == spellCasterNpc) return TRUE;
		else if (v)				 return FALSE;
	};

	if (!v && (targetCollectAlgo != TARGET_COLLECT_NONE) )		   return FALSE;
	

	zSTRING objName = v ? v->GetObjectName() : "(none)";
	zERR_MESSAGE(9,0,"C: SPL: IsValidTarget: " + objName );

	// Check Angles
	zREAL azi, elev;
	if (!spellCasterNpc) return FALSE;
	spellCasterNpc->GetAngles(v,azi,elev);
	if ((zAbs(azi)>targetCollectAzi) || (zAbs(elev)>targetCollectElev))								return FALSE;
	if ((v->GetPositionWorld()-spellCasterNpc->GetPositionWorld()).Length2()>=targetCollectRange*targetCollectRange)	return FALSE;
	if (!spellCasterNpc->FreeLineOfSight(v))														return FALSE;

	/*if (GetSpellID() == SPL_TELEKINESIS)
	{
		if ( !dynamic_cast<oCItem*>(v) && !dynamic_cast<oCMOB*>(v) ||
			 (dynamic_cast<oCMOB*>(v)  && !static_cast<oCMOB*>(v)->IsMoveable())
		   )
		{
			spellStatus = SPL_STATUS_DONTINVEST;		   
			return FALSE;
		}
	}
	else if (GetSpellID() == SPL_TELEKINESIS2)
	{
		if ( !dynamic_cast<oCItem*>(v) && !dynamic_cast<oCMOB*>(v) ||
			 (dynamic_cast<oCMOB*>(v)  && !static_cast<oCMOB*>(v)->IsMoveable()) ||
			 !dynamic_cast<oCNpc*>(v)
		   ) 
		{
			spellStatus = SPL_STATUS_DONTINVEST;
			return FALSE;
		}
	}*/

	return oCSpell::IsTargetTypeValid(v,targetCollectType);
};

zCVob* oCSpell :: GetVob()
{
	if (effect) return effect;
	else		return NULL;
}


int oCSpell :: GetSpellID()
{
	return spellID;
}

int oCSpell :: GetEnergyType()
{
	return spellEnergy;
}

int oCSpell :: GetCategory()
{
	return spellType; 
};

zSTRING oCSpell :: GetName()
{
	zSTRING spellName;
	zCPar_Symbol* sym = NULL;
	sym = parser.GetSymbol("TXT_SPELLS");
	if (sym) sym->GetValue(spellName,spellID);
	return spellName;
}

int oCSpell :: GetLevel()
{
	return this->spellLevel;
}

zBOOL oCSpell :: IsInvestSpell()
{
	// [BENDLIN] Addon - nix Investa
	return FALSE;
/** /
	switch (this->spellID)
	{
//	case SPL_PYROKINESIS:
	case SPL_LIGHTNINGFLASH:
	case SPL_GEYSER:
	case SPL_BELIARSRAGE:
		return TRUE;
	default:
		return FALSE;
	}
/**/
}

void oCSpell::SetInvestedMana( int nManaInvested )
{
	this->manaInvested = nManaInvested;
	if (nManaInvested == 0) this->manaTimer = 0;
};

int oCSpell :: GetSpellStatus()
{
	return spellStatus;
}


void oCSpell :: SetReleaseStatus()
{

	zERR_MESSAGE(8,0,"C: SPL: CallScript ProcessMana_Release");
	parser.SetInstance("SELF"	,spellCasterNpc);
	parser.SetInstance("OTHER"	,spellTargetNpc);
	int index = parser.GetIndex("SPELL_PROCESSMANA_RELEASE");
	if (index > 0) spellStatus = *(int*)parser.CallFunc(index,manaInvested);
	else zERR_FAULT("C: Skript Func SPELL_PROCESSMANA_RELEASE unknown!");

	if ((spellStatus!=SPL_STATUS_CAST) && (spellStatus!=SPL_STATUS_STOP)) 
	{
		zERR_WARNING("C: oCSpell :: SetReleaseStatus(): cant set status to other than STOP or CAST after Action Key has been released");
		spellStatus = SPL_STATUS_STOP;
	}
}

// **********************************************************************************
// cast Actions
// **********************************************************************************

void oCSpell :: SetSpellInfo(int infoValue)
// Für einige Spells haben diese Werte aus dem Skript eine Bedeutung
{
	spellInfo = infoValue;
}

void oCSpell :: DoLogicInvestEffect()
{
	/*zERR_MESSAGE(8,0,"C: SPL: DoLogicInvestEffect");
	if (!spellCasterNpc) return;

	if (GetSpellID()==SPL_TELEKINESIS || GetSpellID()==SPL_TELEKINESIS2) 
	{	
		// einmal zu beginn AssessTheft Wahrnehmung aussenden
		if (manaInvested == 0) 	spellCasterNpc->CheckForOwner(spellTarget);

		if (!spellCasterNpc->GetModel()->IsAniActive("S_TELSHOOT")) return;

		if ( dynamic_cast<oCItem*>(spellTarget) )
		{
			zREAL speed = 75.0f / 1000;		// 1 m pro sec
			zVEC3 move(0,0,0);

			zVEC3 add = spellTarget->GetPositionWorld() - spellCasterNpc->GetPositionWorld();	
			add[VY]   = 0; 
			add.NormalizeApprox();

			zVEC3 right	= zVEC3(0,1,0) ^ add; 
			//	zVEC3 right	= npc->GetRightVectorWorld();
	
			if (zinput->GetState(GAME_UP)) 
			{
				// nicht weiter als einen Meter an den NPC herankommen lassen
				if ( (spellTarget->GetPositionWorld()-spellCasterNpc->GetPositionWorld()).LengthApprox()>200 )
					move += -add;
			} 	
			if (zinput->GetState(GAME_LEFT)) {
				move += -right;
			} else if (zinput->GetState(GAME_RIGHT)) {
				move += right;
			}

			// Nicht höher als ein Meter steigen lassen
			zREAL fac = speed * ztimer.GetFrameTimeF();
			if (up<150.0f) {
				move += zVEC3(0,1,0);
				up   += fac;
			} 		
			
			zVEC3 pos	= spellTarget->GetPositionWorld();
			pos		   += move * fac;

			// Hovern...
			if (up>=150.0f) 
			{
				hoverY += hoverDir * ztimer.GetFrameTimeF() * speed/4;
				if ((hoverY<=-5.0f) || (hoverY>=5.0f)) hoverDir = -hoverDir;
				move[VY] += (hoverY - hoverOld);
				hoverOld = hoverY;
			}

			zVEC3 curPos			=  pos + move;

			zBOOL inMove =	spellCasterNpc -> GetInMovement	();
			if (inMove)		spellCasterNpc -> EndMovement	();
			spellTarget  ->	SetPositionWorld				(curPos);
			if (inMove)		spellCasterNpc -> BeginMovement	();
		}
	}*/
}

/* ----------------------------------------------------------------------
	
	oCSpell::CastSpecificSpell()

	24.08.2000	[Moos]	
				auf zNEW umgestellt
    18.10.2000  [Moos]
                Rückgabewert dazu: soll der Spell hinterher gelöscht werden?
    10.11.2000  [Moos]
                Crashfix für den Control-Spell

   ---------------------------------------------------------------------- */

zBOOL oCSpell :: CastSpecificSpell()
{
	if (!spellCasterNpc) return true;
	zERR_MESSAGE(8,0,"C: SPL: CastSpecificSpell");

	// Effekt ausführen
	if ( (GetSpellID()>=SPL_TRFSHEEP && GetSpellID()<=SPL_TRFDRAGONSNAPPER)) 
	{
		if (spellInfo >= 0) 
		{
			// Wird als Gilde interpretiert.
			saveNpc			= spellCasterNpc;
			zMAT4	trafo	= saveNpc -> trafoObjToWorld;
			zVEC3	pos		= saveNpc -> GetPositionWorld();

			if (spellCasterNpc->GetInstanceName().IsEmpty()){
				zERR_FAULT("oCSpell :: CastSpecificSpell(): (Transform) could not insert npc. given instance is invalid");
			}
			spellCasterNpc	= static_cast<oCNpc*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_NSC,spellInfo));
			spellCasterNpc -> SetAsPlayer();
			saveNpc		   -> Disable			();
 
			// voher referenzieren -> nicht löschen....
			zADDREF_ACCT(saveNpc);
			saveNpc -> CloseSpellBook	(TRUE);
 			saveNpc -> SetWeaponMode2	(NPC_WEAPON_NONE);
			saveNpc -> GetAnictrl  () -> SearchStandAni();

			spellCasterNpc -> SetTrafoObjToWorld(trafo);
			ogame->GetGameWorld()->AddVob		(spellCasterNpc);

			spellCasterNpc->SetCollDet(FALSE);

			if (!spellCasterNpc -> SearchNpcPosition	(pos))
			{
				oCVisualFX* transformFX = oCVisualFX::CreateAndPlay("TRANSFORM_NOPLACEFX",trafo.GetTranslation());
				zRELEASE(transformFX);
				// Codechange - [Ulf] 10.01.01 - Kollisionsflags beachten !

				spellCasterNpc->SetCollDet(TRUE);
				spellCasterNpc->RemoveVobFromWorld();
				saveNpc -> SetAsPlayer();
				spellCasterNpc->Disable();
				zRELEASE_ACCT(spellCasterNpc);
				// [EDENFELD] Patch 1.08 Avoid Null Ptr Crash
				zRELEASE_ACCT_NONULL(saveNpc);

				// ... sondern nur aus der Welt entfernen
				saveNpc -> Enable	  (trafo.GetTranslation());
				saveNpc -> SetSleeping(FALSE);

				canBeDeleted = FALSE;
				timerEffect  = 0;
				return FALSE;
			};

			// Ein paar Werte muessen uebernommen werden ...
			saveNpc		   -> CopyTransformSpellInvariantValuesTo( spellCasterNpc );

			// Jetzt den ueernommenen NPC aktivieren
			spellCasterNpc -> SetCollDet		(TRUE);
			spellCasterNpc -> Enable			(pos);
			spellCasterNpc -> GetAnictrl		() -> SearchStandAni();
			
            zRELEASE_ACCT_NONULL(spellCasterNpc); // [Moos] Leakfix. Die Welt kümmert sich um den neuen Npc.

			// Put Spell in Active-List for further Checks
			spellCasterNpc -> InsertActiveSpell   (this);
			spellCasterNpc -> SetBodyStateModifier(BS_MOD_TRANSFORMED);
			canBeDeleted	= FALSE;
			spellTargetNpc  = spellCasterNpc;
			
			// Wahrnehmung generieren
			spellCasterNpc -> AssessFakeGuild_S	();

			return false; // [Moos] der Spell ist beim Caster registriert, also nicht löschen
		}

	} 
	/*else if (GetSpellID()==SPL_CONTROL) 
	{		
		if (!spellTargetNpc) return TRUE;

        zRELEASE_ACCT(saveNpc);           // [Moos] Nur so zur Sicherheit
		saveNpc = spellCasterNpc;
		zADDREF_ACCT(saveNpc);           // [Moos] Crashfix     

		spellCasterNpc -> ModifyBodyState( BS_MOD_CONTROLLING, 0 );

		// Von den Skripten das OK bekommen.
		spellTargetNpc -> GetAnictrl () -> SearchStandAni();
		spellTargetNpc -> SetAsPlayer();
		spellTargetNpc -> SetBodyStateModifier(BS_MOD_CONTROLLED);

		spellCasterNpc -> GetEM() -> OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), spellCasterNpc);

		spellTargetNpc -> state.StartAIState("ZS_CONTROLLED",FALSE,0);

		// Put Spell in Active-List for further Checks
		spellTargetNpc -> InsertActiveSpell (this);
		canBeDeleted = FALSE;
	
        return false; // [Moos] der Spell ist beim Opfer registriert, also nicht löschen
	}*/
	else if ( GetSpellID() == SPL_LIGHT || GetSpellID()==SPL_PALLIGHT )
	{
		spellCasterNpc -> InsertActiveSpell (this);
		canBeDeleted = FALSE;
		return false;
	};

    return true;
}

void oCSpell :: EndTimedEffect()
// Nur wenn dieser NSC bei einem anderen NSC aktiv
// SpellTargetNpc -> betroffener NSC
{
	zERR_MESSAGE(8,0,"C: SPL: EndTimedEffect");

	canBeDeleted = TRUE;

	if ((GetSpellID()>=SPL_TRFSHEEP && GetSpellID()<=SPL_TRFDRAGONSNAPPER))
	{
		// Zurückverwandeln
		if (saveNpc && spellTargetNpc) 
		{	

			zVEC3	pos = spellTargetNpc->GetPositionWorld();
			saveNpc -> SetTrafoObjToWorld		(spellTargetNpc -> trafoObjToWorld);
			ogame	-> GetGameWorld()->AddVob	(saveNpc);

			// Codechange - [Ulf] 10.01.01 - Kollisionsflags beachten !
			saveNpc -> SetCollDet(FALSE);
			if (!saveNpc -> SearchNpcPosition	(pos))
			{
				oCVisualFX* transformFX = oCVisualFX::CreateAndPlay("TRANSFORM_NOPLACEFX",spellTargetNpc->GetPositionWorld());
				zRELEASE_ACCT(transformFX);
				// Codechange - [Ulf] 10.01.01 - Kollisionsflags beachten !
				saveNpc->SetCollDet(TRUE);
				saveNpc->Disable();
				canBeDeleted = FALSE;
				timerEffect  = 0;
				return;
			}
			
			saveNpc -> Enable					(pos);
			saveNpc	-> ResetRotationsWorld		(); // [Moos] 20.12.00 Anpassung an Vob-Änderung
			saveNpc -> SetHeadingAtWorld 		(spellTargetNpc->GetAtVectorWorld());
			saveNpc -> ResetXZRotationsWorld	();
			// Codechange - [Ulf] 10.01.01 - Kollisionsflags beachten !
			saveNpc -> SetCollDet				(TRUE);

            if (!spellTargetNpc->GetInMovement())  // [Moos] Crashfix für Levelchange: man darf einem bewegten Vob nicht einfach so die Homeworld unterm Arsch wegreissen.
			    ogame	-> GetGameWorld	() -> RemoveVob(spellTargetNpc);

			// Ein paar Werte muessen uebernommen werden ...
			spellCasterNpc -> CopyTransformSpellInvariantValuesTo( saveNpc );

			// Original-NPC aktivieren
			saveNpc -> GetAnictrl () -> SearchStandAni();
			saveNpc -> SetAsPlayer				();
		
			// effect
			effect   = CreateEffect			();
			effect  -> Init					(saveNpc,NULL);
			effect  -> SetSpellTargetTypes	(targetCollectType);
			effect  -> Cast					();
            zRELEASE_ACCT(effect); // [Moos] Leakfix

			oCMsgConversation *pMsg = zNEW( oCMsgConversation( oCMsgConversation::EV_PLAYANI_NOOVERLAY, "T_TRFSHOOT_2_STAND") );
			pMsg->SetHighPriority(TRUE);
			saveNpc->GetEM()->OnMessage( pMsg, saveNpc);


			// Über DeleteCaster wird der ueberflüssige Vob jetzt entfernt.	
			// Und AssessSurprise aktivieren
			saveNpc -> CreatePassivePerception(NPC_PERC_ASSESSSURPRISE,saveNpc);	
		}
	} 
	/*else if (GetSpellID() == SPL_CONTROL) 
	{
		// Zurück in alten Körper
		if (saveNpc && spellTargetNpc) 
		{		
			saveNpc			-> SetAsPlayer();

			saveNpc			-> ModifyBodyState( 0, BS_MOD_CONTROLLING );

			spellTargetNpc	-> state.EndCurrentState();

			saveNpc			-> state.ClearAIState();

			saveNpc			-> StandUp();
			saveNpc			-> SetSleeping(FALSE);
			
			if (controlWarnFX) 
			{
				controlWarnFX->Stop();
				zRELEASE_ACCT(controlWarnFX);
			}

			// effect
			effect   = CreateEffect			();
			effect  -> Init					(saveNpc,NULL);
			effect	-> SetSpellTargetTypes	(targetCollectType);
			effect  -> Cast					();
			zRELEASE_ACCT(effect);
		}
	}*/
}

void oCSpell :: DoTimedEffect()
// Nur wenn dieser NSC bei einem anderen NSC aktiv
// SpellTargetNpc -> betroffener NSC
{
	if (timerEffect>0.0) 
	{
		timerEffect -= ztimer.GetFrameTimeF();
		if (timerEffect<=0) 
		{
			canBeDeleted = TRUE;	
			EndTimedEffect();
		}
	}
	
	// HumanControl : nur ca. 40m
	/*if (GetSpellID()==SPL_CONTROL) 
	{
		if (saveNpc && spellTargetNpc) 
		{
			if (spellTargetNpc->IsDead() || spellTargetNpc->GetDistanceToVob2(*saveNpc) >= 4000 * 4000) 
			{
				canBeDeleted = TRUE;
				EndTimedEffect();
			}
			else if (spellTargetNpc->GetDistanceToVob2(*saveNpc) >= 3500 * 3500)
			{
				if (!controlWarnFX) controlWarnFX = oCVisualFX::CreateAndPlay("CONTROL_LEAVERANGEFX",spellTargetNpc->GetPositionWorld());
			}
			else if (controlWarnFX) 
			{
				controlWarnFX->Stop();
				zRELEASE_ACCT(controlWarnFX);
			}
		}
	}
	else */
	if ( GetSpellID() == SPL_LIGHT || GetSpellID()==SPL_PALLIGHT )
	{
		if (effect->CanBeDeleted()) 
		{
			zRELEASE_ACCT(effect);
			canBeDeleted = TRUE;
		}
	};
}

zBOOL oCSpell :: CanBeDeleted()
// Nur wenn dieser NSC bei einem anderen NSC aktiv
// SpellTargetNpc -> betroffener NSC
{
	return canBeDeleted;
}

zBOOL oCSpell :: DeleteCaster()
// Nur wenn dieser NSC bei einem anderen NSC aktiv
// SpellTargetNpc -> betroffener NSC
{
	return ((GetSpellID()>=SPL_TRFSHEEP && GetSpellID()<=SPL_TRFDRAGONSNAPPER));
}

// **********************************************************************************
// Anis
// **********************************************************************************


void oCSpell :: Archive(zCArchiver& arc)
{

};

void oCSpell :: Unarchive(zCArchiver& arc)
{

};

zCLASS_DEFINITION			(oCSpell,		zCObject,	0,	0)

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
