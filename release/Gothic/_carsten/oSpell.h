/******************************************************************************** 
 
     $Work: oSpell.h             $                $Date:: 16.02.01 7:37    $
     $Revision:: 39                   $             $Modtime:: 16.02.01 7:17    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Carsten/oSpell.h $
 * 
 * 39    16.02.01 7:37 Edenfeld
 * Plotkiller Telekinesis Scroll Bugfix
 * 
 * 38    6.02.01 17:07 Keskenti
 * 
 * 37    2.02.01 23:40 Edenfeld
 * 
 * 36    13.12.00 16:15 Edenfeld
 * 
 * 35    30.11.00 15:03 Wohlers
 * 
 * 34    24.11.00 15:06 Edenfeld
 * 
 * 33    2.11.00 22:07 Edenfeld
 * 
 * 32    23.10.00 13:21 Edenfeld
 * 
 * 31    21.10.00 18:13 Edenfeld
 * 
 * 30    18.10.00 17:58 Moos
 * 
 * 29    10.10.00 14:31 Keskenti
 * 
 * 28    4.10.00 17:47 Edenfeld
 * 
 * 27    23.09.00 2:58 Edenfeld
 * 
 * 26    22.09.00 19:57 Edenfeld
 * 
 * 25    21.09.00 21:30 Herget
 * 
 * 24    21.09.00 20:30 Herget
 * 
 * 23    19.09.00 23:28 Edenfeld
 * 
 * 22    15.09.00 16:31 Edenfeld
 * 
 * 21    15.09.00 0:36 Edenfeld
 * GetLevel
 * 
 * 20    31.08.00 17:43 Edenfeld
 * 
 * 19    31.08.00 2:09 Herget
 * 
 * 18    23.08.00 17:37 Edenfeld
 * 
 * 17    22/08/00 14:02 Luesebrink
 * 
 * 16    22/08/00 10:23 Luesebrink
 * 
 * 15    18.08.00 2:06 Edenfeld
 * 
 * 14    17.08.00 19:31 Edenfeld
 * 
 * 13    14.08.00 21:27 Edenfeld
 * 
 * 12    10/08/00 15:46 Luesebrink
 * 
 * 11    2.08.00 12:19 Edenfeld
 * 
 * 10    1.08.00 17:31 Edenfeld
 * 
 * 9     14.07.00 13:43 Edenfeld
 * 
 * 8     5.07.00 12:22 Wohlers
 * 
 * 6     29.05.00 18:36 Wohlers
 * 
 * 5     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 4     8.05.00 19:32 Wohlers
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
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __SPELL_H__
#define __SPELL_H__


enum {	SPL_STATUS_DONTINVEST	= 0,	SPL_STATUS_CANINVEST	= 1, 
		SPL_STATUS_CAST			= 2,	SPL_STATUS_STOP			= 3,
		SPL_STATUS_NEXTLEVEL	= 4,	SPL_STATUS_CANINVEST_NO_MANADEC	= 8, SPL_STATUS_FORCEINVEST  = 1<<16 };

// **********************************
//  Constants for Spell Concept 1.33
// **********************************

// Paladin-Runen
const int SPL_PALLIGHT				= 0;                                                              
const int SPL_PALLIGHTHEAL			= 1;
const int SPL_PALHOLYBOLT			= 2;
const int SPL_PALMEDIUMHEAL			= 3;
const int SPL_PALREPELEVIL			= 4;
const int SPL_PALFULLHEAL			= 5;
const int SPL_PALDESTROYEVIL		= 6;
// Teleport-RUNEN
const int SPL_PALTELEPORTSECRET		= 7;
const int SPL_TELEPORTSEAPORT		= 8;
const int SPL_TELEPORTMONASTERY		= 9;
const int SPL_TELEPORTFARM			= 10;
const int SPL_TELEPORTXARDAS		= 11;
const int SPL_TELEPORTPASSNW		= 12;
const int SPL_TELEPORTPASSOW		= 13;
const int SPL_TELEPORTOC			= 14;
const int SPL_TELEPORT_1			= 15;
const int SPL_TELEPORT_2			= 16;
const int SPL_TELEPORT_3			= 17;
// Kreis 1
const int SPL_LIGHT					= 18;
const int SPL_FIREBOLT				= 19;
// Kreis 2
const int SPL_ICEBOLT				= 20;
// Kreis 1
const int SPL_LIGHTHEAL				= 21;
const int SPL_SUMMONGOBLINSKELETON	= 22;
// Kreis 2
const int SPL_INSTANTFIREBALL		= 23;
// Kreis 1
const int SPL_ZAP					= 24;
// Kreis 2
const int SPL_SUMMONWOLF			= 25;
const int SPL_WINDFIST				= 26;
const int SPL_SLEEP					= 27;
// Kreis 3
const int SPL_MEDIUMHEAL			= 28;
const int SPL_LIGHTNINGFLASH		= 29;  
const int SPL_CHARGEFIREBALL		= 30;
const int SPL_SUMMONSKELETON		= 31;
const int SPL_FEAR					= 32;
const int SPL_ICECUBE				= 33;
// Kreis 4
const int SPL_THUNDERBALL			= 34;
const int SPL_SUMMONGOLEM			= 35;
const int SPL_DESTROYUNDEAD			= 36;
const int SPL_PYROKINESIS			= 37;
// Kreis 5
const int SPL_FIRESTORM				= 38;
const int SPL_ICEWAVE				= 39;
const int SPL_SUMMONDEMON			= 40;
const int SPL_FULLHEAL				= 41;
// Kreis 6
const int SPL_FIRERAIN				= 42;
const int SPL_BREATHOFDEATH			= 43;
const int SPL_MASSDEATH				= 44;
const int SPL_ARMYOFDARKNESS		= 45;
const int SPL_SHRINK				= 46;
// Scrolls
const int SPL_TRFSHEEP				= 47;
const int SPL_TRFSCAVENGER			= 48;
const int SPL_TRFGIANTRAT			= 49;
const int SPL_TRFGIANTBUG			= 50;
const int SPL_TRFWOLF				= 51;
const int SPL_TRFWARAN				= 52;
const int SPL_TRFSNAPPER			= 53;
const int SPL_TRFWARG				= 54;
const int SPL_TRFFIREWARAN			= 55;
const int SPL_TRFLURKER				= 56;
const int SPL_TRFSHADOWBEAST		= 57;
const int SPL_TRFDRAGONSNAPPER		= 58;
const int SPL_CHARM					= 59;
// Kreis 5
const int SPL_MASTEROFDESASTER		= 60;	// SPL_RESERVED_1
// ???
const int SPL_DEATHBOLT				= 61;	// SPL_RESERVED_2
const int SPL_DEATHBALL				= 62;	// SPL_RESERVED_3
const int SPL_CONCUSSIONBOLT		= 63;	// SPL_RESERVED_4
const int SPL_RESERVED_64			= 64;	// SPL_RESERVED_5
const int SPL_RESERVED_65		    = 65;	// SPL_RESERVED_6
const int SPL_RESERVED_66	        = 66;	// SPL_RESERVED_7
const int SPL_RESERVED_67	        = 67;	// SPL_RESERVED_8
const int SPL_RESERVED_68	        = 68;
const int SPL_RESERVED_69		    = 69;
// Magick (Wasser)
const int SPL_THUNDERSTORM			= 70;	// 'Unwetter'		(derived from SPL_FIRERAIN)
const int SPL_WHIRLWIND				= 71;	// 'Windhose'		(derived from SPL_ICECUBE)
const int SPL_WATERFIST				= 72;	// 'Wasserfaust'	(derived from SPL_WINDFIST)
const int SPL_ICELANCE				= 73;	// 'Eislanze'		(derived from SPL_ICEBOLT)
const int SPL_INFLATE				= 74;	// 'Aufblähen'		(derived from SPL_SLEEP)
const int SPL_GEYSER				= 75;	// 'Geysir'			(derived from SPL_LIGHTNINGFLASH)
const int SPL_WATERWALL				= 76;	// 'Wasserwand'		(derived from SPL_FIRERAIN)
const int SPL_RESERVED_77	        = 77;
const int SPL_RESERVED_78	        = 78;
const int SPL_RESERVED_79	        = 79;
// Magick (Maya)
const int SPL_PLAGUE				= 80;	// 'Insektenplage'		(derived from SPL_FEAR)
const int SPL_SUMMONSWARM			= 81;	// 'Insektenschwarm'	(derived from SPL_SUMMONGOLEM)
const int SPL_GREENTENTACLE			= 82;	// 'Wurzelschlingen'	(derived from SPL_ICECUBE)
const int SPL_EARTHQUAKE			= 83;	// 'Erdbeben'			(derived from SPL_FIRERAIN)
const int SPL_SUMMONGUARDIAN		= 84;	// 'Wächter erschaffen'	(derived from SPL_SUMMONGOLEM)
const int SPL_BELIARSRAGE		    = 85;	// 'Beliars Zorn'		(derived from SPL_LIGHTNINGFLASH)
const int SPL_SUCKENERGY	        = 86;	// 'Energie stehlen'	(derived from SPL_WHIRLWIND)
const int SPL_SKULL			        = 87;	// 'Schrei der Toten'	(derived from SPL_WINDFIST)
const int SPL_SUMMONZOMBIE	        = 88;	// 'Zombie erschaffen'	(derived from SPL_SUMMONGOLEM)
const int SPL_RESERVED_89		    = 89;
// ...
const int SPL_RESERVED_90	        = 90;
const int SPL_RESERVED_91	        = 91;
const int SPL_RESERVED_92	        = 92;
const int SPL_RESERVED_93	        = 93;
const int SPL_RESERVED_94	        = 94;
const int SPL_RESERVED_95		    = 95;
const int SPL_RESERVED_96	        = 96;
const int SPL_RESERVED_97	        = 97;
const int SPL_RESERVED_98	        = 98;
const int SPL_RESERVED_99		    = 99;
 
const int SPL_MAX_SPELL				= 100;   // 59 (Gothic), 68 (Gothic2), 100 (G2Addon)


class oCNpc;
class oCVisualFX;

enum { 
	SPL_CAT_GOOD		= 0, 
	SPL_CAT_NEUTRAL		= 1, 
	SPL_CAT_BAD			= 2 
};

enum { 
	TARGET_COLLECT_NONE					= 0, 
	TARGET_COLLECT_CASTER				= 1, 
	TARGET_COLLECT_FOCUS				= 2, 
	TARGET_COLLECT_ALL					= 3, 
	TARGET_COLLECT_FOCUS_FALLBACK_NONE	= 4, 
	TARGET_COLLECT_FOCUS_FALLBACK_CASTER= 5, 
	TARGET_COLLECT_ALL_FALLBACK_NONE	= 6, 
	TARGET_COLLECT_ALL_FALLBACK_CASTER	= 7  
};

enum {
	TARGET_FLAG_NONE				= 0,	
	TARGET_FLAG_ALL					= 1,
	TARGET_FLAG_ITEMS				= 2,
	TARGET_FLAG_NPCS				= 4,
	TARGET_FLAG_ORCS				= 8,
	TARGET_FLAG_HUMANS				= 16,
	TARGET_FLAG_UNDEAD				= 32,
	TARGET_FLAG_LIVING				= 64
};

const int NUM_TARGET_TYPES			= 7;

class oCSpell : public zCObject
{
	zCLASS_DECLARATION (oCSpell)
public:
	static zBOOL		IsTargetTypeValid	(zCVob *v, int targetType);
	oCSpell									();
	oCSpell									(int spellID);

	void				Setup				(zCVob* caster, zCVob* target, const zBOOL a_bIgnoreCastState=FALSE);
	zBOOL				Invest				();
	zBOOL				Cast				();		
	int					Stop				();
	int					Kill				();
	void				Open				();
	void				Close				();
	void				Reset				();

	oCNpc*				GetSpellTargetNpc	()					{ return this->spellTargetNpc;		}
	int					GetSpellID			();
	void				SetSpellStatus		(int status)		{ spellStatus = status;				}
	int					GetSpellStatus		();
	int					GetEnergyType		();
	int					GetCategory			();
	oCVisualFX*			GetEffect			()					{ return effect;					}
	zCVob*				GetVob				();
	zSTRING				GetName				();
	zBOOL				GetEnabled			();
	zBOOL				IsValidTarget		(zCVob *v);
	void				SetEnabled			(zBOOL enable);
	void				SetReleaseStatus	();

	void				SetSpellInfo		(int infoValue);
	zBOOL				CastSpecificSpell	();

	void				DoTimedEffect		();
	void				EndTimedEffect		();
	zBOOL				CanBeDeleted		();
	zBOOL				CanChangeTarget		()									{ return canChangeTargetDuringInvest;	};
	zBOOL				CanTurnDuringInvest	()									{ return canTurnDuringInvest;			};
	zBOOL				DeleteCaster		();
	int					GetInvestedMana		()									{ return manaInvested;		}
	int					GetLevel			();
	zBOOL				IsInvestSpell		();
	void				SetInvestedMana		( int nManaInvested );
	oCNpc*				GetSpellCasterNPC	()					{ return spellCasterNpc;			};
	oCNpc*				GetSpellTargetNPC	()					{ return spellTargetNpc;			};

	int					keyNo;

private:
	virtual				~oCSpell			();

	oCVisualFX*			CreateEffect		();
	void				InitValues			(int _spellID);
	void				InitByScript		(const zSTRING& name);
	void				StopTargetEffects	(zCVob* vob);
	void				CallScriptInvestedMana();

	void				DoLogicInvestEffect	();

	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);

	zSTRING				GetSpellInstanceName(const int _spellID) const;

	// Data
	oCVisualFX*			effect;
	oCVisualFX*			controlWarnFX;
	zCVob*				spellCaster;
	oCNpc*				spellCasterNpc;
	zCVob*				spellTarget;
	oCNpc*				spellTargetNpc;
	oCNpc*				saveNpc;
	zREAL				manaTimer;
	int					manaInvested;
	int					spellLevel;
	int					spellStatus;
	int					spellID;
	int					spellInfo;
	zBOOL				spellEnabled;
	zBOOL				spellInitDone;

	zBOOL				timerEffect;		// Duration of Spell (Light / Invisibility) used in 
	zBOOL				canBeDeleted;

	zREAL				up;
	zREAL				hoverY;
	zREAL				hoverOld;
	zREAL				hoverDir;

	int					spellEnergy;
	
	// Parser
	struct {
		zREAL			manaInvestTime;			// Time for Investing one mana
		int				damagePerLevel;			// How much damage per Level.
		int				damageType;				// what kind of Damage
		int				spellType;				// Good, bad, neutral
		int				canTurnDuringInvest;
		int				canChangeTargetDuringInvest;
		int				isMultiEffect;			// Effect Class is oCVisFX_MultiTarget if set to 1
		int				targetCollectAlgo;
		int				targetCollectType;
		int				targetCollectRange;
		int				targetCollectAzi;
		int				targetCollectElev;
	};
};

#endif
