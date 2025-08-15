/******************************************************************************** 
 
     $Workfile:: oNPC.h               $                $Date:: 13.02.01 19:11   $
     $Revision:: 154                  $             $Modtime:: 13.02.01 18:50   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oNPC.h $
 * 
 * 154   13.02.01 19:11 Wohlers
 * 
 * 153   8.02.01 18:24 Moos
 * 
 * 152   2.02.01 18:57 Moos
 * 
 * 151   1.02.01 19:49 Speckels
 * 
 * 150   1.02.01 18:14 Keskenti
 * 
 * 149   26.01.01 16:05 Moos
 * 
 * 148   24.01.01 22:14 Wohlers
 * 
 * 147   24.01.01 14:57 Moos
 * 
 * 146   23.01.01 19:12 Keskenti
 * 
 * 145   23.01.01 19:02 Wohlers
 * 
 * 144   22.01.01 22:38 Wohlers
 * 
 * 143   22.01.01 20:01 Moos
 * 
 * 142   22.01.01 13:09 Moos
 * 
 * 141   19.01.01 0:05 Speckels
 * 
 * 140   18.01.01 16:53 Keskenti
 * 
 * 139   18.01.01 14:49 Moos
 * 
 * 138   18.01.01 2:00 Wohlers
 * 
 * 137   18.01.01 0:06 Edenfeld
 * 
 * 136   17.01.01 17:43 Keskenti
 * 
 * 135   17.01.01 16:33 Wohlers
 * 
 * 134   16.01.01 15:24 Keskenti
 * 
 * 133   12.01.01 10:23 Keskenti
 * 
 * 132   8.01.01 14:55 Wohlers
 * 
 * 131   19.12.00 17:38 Wohlers
 * 
 * 130   19.12.00 13:40 Wohlers
 * 
 * 129   19.12.00 12:06 Keskenti
 * 
 * 128   15.12.00 16:00 Keskenti
 * 
 * 127   14.12.00 20:45 Wohlers
 * 
 * 126   7.12.00 18:06 Keskenti
 * 
 * 125   6.12.00 15:53 Keskenti
 * 
 * 124   5.12.00 18:35 Speckels
 * 
 * 123   29.11.00 21:57 Speckels
 * 
 * 122   29.11.00 17:20 Wohlers
 * 
 * 121   29.11.00 12:52 Speckels
 * 
 * 120   24.11.00 15:41 Wohlers
 * 
 * 119   21.11.00 19:39 Edenfeld
 * 
 * 
 *********************************************************************************/

#ifndef __ONPC_H__
#define __ONPC_H__

// NPC-Deklarations

// needs oAI.cpp

#include "zSTRING.h"
#include "zDisk.h"
#include "zList.h"
#include "z3D.h"
#include "zModel.h"
#include "zSoundMan.h"
#include "oItem.h"
#include "oVob.h"
#include "oNews.h"
#include "oNpcStates.h"
#include "oInventory.h"
#include "oCSPlayer.h"
#include "oMagFrontier.h"
#include "oAIHuman.h"

class oCWorld;
class zCPlayerGroup;
class zCModelAni;

// * Aktuelles Kapitel *
extern int Npc_chapter;

class oCAIHuman;
class oCMag_Book;
class oCSpell;
class oCDialog;
class oCInfo;
class oCAniCtrl_Human;
class oCMOB;
class oCMobInter;
class oCMobBed;
class oCRtn_Entry;
class oCAskBox;
class oCAI_NpcManager;
class zCAIManager;
class zCRoute;
class zCCSPlayerContext;
class oCMission;

// Event Messages
class oCNpcMessage;
class oCMsgDamage;
class oCMsgMovement;
class oCMsgWeapon;
class oCMsgAttack;
class oCMsgUseItem;
class oCMsgState;
class oCMsgVarious;
class oCMsgManipulate;
class oCMsgConversation;
class oCMsgMagic;
#if defined(SECUROM) && !defined(COMPILING_SPACER)
class oCMsgRequest;
#endif

class zCNetPacket;
class zCWaypoint;
class zCVobSpot;
class oCMagFrontier;

// Konstanten fuer Game_Modus
enum {	NPC_GAME_NORMAL,	NPC_GAME_PLUNDER,		NPC_GAME_STEAL };
enum {  BS_INT_OVERRIDE_NONE = 0, BS_INT_OVERRIDE_ALL = 1, BS_INT_OVERRIDE_STUMBLE_ONLY = 2 };

// ************************************
// Konstanten fuer NSCs
// ************************************

//	Face Anis
extern const zSTRING NPC_TALK_ANI;

// Constants Attributes
const int NPC_ATR_HITPOINTS				=  0;	// Lebenspunkte
const int NPC_ATR_HITPOINTSMAX			=  1;	// Max. Lbenspunkte
const int NPC_ATR_MANA					=  2;	// Mana Mana
const int NPC_ATR_MANAMAX				=  3;	// Mana Max

const int NPC_ATR_STRENGTH				=  4;	// Stärke
const int NPC_ATR_DEXTERITY				=  5;	// Geschick
const int NPC_ATR_REGENERATEHP			=  6;	// Regenerierung von HP alle x sekunden
const int NPC_ATR_REGENERATEMANA		=  7;   // Regenerierung von Mana alle x sekunden

const int NPC_ATR_MAX					=  8;

const int NPC_TAL_FIGHT_USED			=  0x00000FFF;
const int NPC_TAL_FIGHT_MAX				=  12;
const int NPC_TAL_USED					=  0x0000024D;
const int NPC_TAL_MAX					=  17;


const int NPC_HITCHANCE_1H				=  1;
const int NPC_HITCHANCE_2H				=  2;
const int NPC_HITCHANCE_BOW				=  3;
const int NPC_HITCHANCE_CROSSBOW		=  4;
const int NPC_HITCHANCE_MAX				=  5;


// ------------------------------------------------------------------------------
// [EDENFELD] 1.09
// Scriptfunktionen als T_DONTKNOW Ersatz

// a) Mob
const zSTRING	PLAYER_MOB_MISSING_KEY				=	"PLAYER_MOB_MISSING_KEY";
const zSTRING	PLAYER_MOB_MISSING_LOCKPICK			=	"PLAYER_MOB_MISSING_LOCKPICK";
const zSTRING	PLAYER_MOB_MISSING_KEY_OR_LOCKPICK	=	"PLAYER_MOB_MISSING_KEY_OR_LOCKPICK";
const zSTRING	PLAYER_MOB_NEVER_OPEN				=	"PLAYER_MOB_NEVER_OPEN";
const zSTRING	PLAYER_MOB_TOO_FAR_AWAY				=	"PLAYER_MOB_TOO_FAR_AWAY";
const zSTRING	PLAYER_MOB_WRONG_SIDE				=	"PLAYER_MOB_WRONG_SIDE";

const zSTRING	PLAYER_MOB_MISSING_ITEM				=	"PLAYER_MOB_MISSING_ITEM";
const zSTRING	PLAYER_MOB_ANOTHER_IS_USING			=	"PLAYER_MOB_ANOTHER_IS_USING";

// b) Leichen plündern
const zSTRING	PLAYER_PLUNDER_IS_EMPTY				=	"PLAYER_PLUNDER_IS_EMPTY";

// c) Munition alle
const zSTRING	PLAYER_RANGED_NO_AMMO				=	"PLAYER_RANGED_NO_AMMO";


class oCNpcTalent :  public zCObject
{
	zCLASS_DECLARATION	(oCNpcTalent)
public:
	enum oTEnumNpcTalent
	{
		NPC_TAL_UNKNOWN,
		// Skilled Talents
		NPC_TAL_1H,
		NPC_TAL_2H,
		NPC_TAL_BOW,
		NPC_TAL_CROSSBOW,
		NPC_TAL_PICKLOCK,
		NPC_TAL_PICKPOCKET,
		NPC_TAL_MAGE,
		// Special-Talents
		NPC_TAL_SNEAK,
		NPC_TAL_REGENERATE,
		NPC_TAL_FIREMASTER,
		NPC_TAL_ACROBAT,
		NPC_TALENT_PICKPOCKET,
		NPC_TAL_SMITH,
		NPC_TAL_RUNES,
		NPC_TAL_ALCHEMY	,
		NPC_TAL_TAKEANIMALTROPHY,
		NPC_TAL_A,
		NPC_TAL_B,
		NPC_TAL_C,
		NPC_TAL_D,
		NPC_TAL_E,
		NPC_TAL_MAX
	};

	static zBOOL				IsFightTalent	(int nr)	{ return (nr>oTEnumNpcTalent::NPC_TAL_UNKNOWN) && (nr<=oTEnumNpcTalent::NPC_TAL_CROSSBOW); };		
	
	static void					CreateTalentList(zCArray<oCNpcTalent*>* talentList);	
	
private:
	oTEnumNpcTalent	m_talent;
	int				m_skill;
	int				m_value;
	
public:
	oCNpcTalent();
	virtual ~oCNpcTalent();

	// *************************************
	// Archive / Unarchive
	// *************************************
	virtual void	Archive			(zCArchiver &arc);
	virtual void	Unarchive		(zCArchiver &arc);
			
	oTEnumNpcTalent	GetTalent		()						{ return m_talent;		};
	int				GetTalentValue	()						{ return m_value;	};
	int				GetTalentSkill	()						{ return m_skill;	};

	zBOOL			IsFightTalent	()						{ return IsFightTalent(m_talent);}	
		
	void			SetTalent		(oTEnumNpcTalent talent){ m_talent=talent;m_skill=0;m_value=0;};	
	void			SetTalentValue	(int value)				{ m_value=value;}
	void			SetTalentSkill	(int skill)				{ m_skill=skill;}
};

/*
// Kampftalente in 2 Stufen (Stufe 0 ist nur Platzhalter für "nicht erlernt")
const int NPC_TAL_1H_0				=	1<< 0;
const int NPC_TAL_1H_1				=	1<< 1;
const int NPC_TAL_1H_2				=	1<< 2;
const int NPC_TAL_2H_0				=	1<< 3;
const int NPC_TAL_2H_1				=	1<< 4;
const int NPC_TAL_2H_2				=	1<< 5;
const int NPC_TAL_BOW_0				=	1<< 6;
const int NPC_TAL_BOW_1				=	1<< 7;
const int NPC_TAL_BOW_2				=	1<< 8;
const int NPC_TAL_CROSSBOW_0		=	1<< 9;
const int NPC_TAL_CROSSBOW_1		=	1<<10;
const int NPC_TAL_CROSSBOW_2		=	1<<11;

const int NPC_TAL_SNEAK				=	1<< 0;
const int NPC_TAL_HIDE				=   1<< 1;
const int NPC_TAL_STEAL				=   1<< 2;
const int NPC_TAL_PICKLOCK			=   1<< 3;
const int NPC_TAL_TRAPS				=   1<< 4;
const int NPC_TAL_SEVENTHSENSE		=   1<< 5;
const int NPC_TAL_ACROBAT			=	1<< 6;
const int NPC_TAL_NIGHTSIGHT		=   1<< 7;
const int NPC_TAL_ASSASSIN			=   1<< 8;
const int NPC_TAL_IDENTIFY			=	1<< 9;
const int NPC_TAL_TAMEANIMALS		=   1<<10;
const int NPC_TAL_SPEAKORK			=   1<<11;
const int NPC_TAL_HEAL				=	1<<12;
const int NPC_TAL_MANA				=	1<<13;
const int NPC_TAL_IRONWILL			=   1<<14;

const int NPC_TAL_SWIM				=	1<<15;
const int NPC_TAL_CLIMB				=	1<<16;
*/
const int NPC_FLAG_NFOCUS			=	1<<18;

// ******************************************
// BodyStates / Overlays and Flags
// ******************************************
const int BS_STAND					=	0;
const int BS_WALK					=	1;
const int BS_SNEAK					=	2;
const int BS_RUN					=	3;
const int BS_SPRINT					=	4;
const int BS_SWIM					=	5;
const int BS_CRAWL					=	6;
const int BS_DIVE					=	7;
const int BS_JUMP					=	8;
const int BS_CLIMB					=	9;
const int BS_FALL					=  10;
const int BS_SIT					=  11;
const int BS_LIE					=  12;	
const int BS_INVENTORY				=  13;
const int BS_ITEMINTERACT			=  14;
const int BS_MOBINTERACT			=  15;
const int BS_MOBINTERACT_INTERRUPT	=  16;

const int BS_TAKEITEM				=  17;
const int BS_DROPITEM				=  18;
const int BS_THROWITEM				=  19;
const int BS_PICKPOCKET				=  20;

const int BS_STUMBLE				=  21;
const int BS_UNCONSCIOUS			=  22;
const int BS_DEAD					=  23;

const int BS_AIMNEAR				=  24;
const int BS_AIMFAR					=  25;
const int BS_HIT					=  26;
const int BS_PARADE					=  27;

// Magic
const int BS_CASTING				=  28;
const int BS_PETRIFIED				=  29;
const int BS_CONTROLLING			=  30;

const int BS_MAX					=  31;

// Modifier / Overlays
const int BS_MOD_HIDDEN				=    128;
const int BS_MOD_DRUNK				=	 256;
const int BS_MOD_NUTS				=	 512;
const int BS_MOD_BURNING			=   1024;
const int BS_MOD_CONTROLLED			=   2048;
const int BS_MOD_TRANSFORMED		=	4096;
const int BS_MOD_CONTROLLING		=   8192;

// Interruptable Flags
const int BS_FLAG_INTERRUPTABLE		=  32768;
const int BS_FLAG_FREEHANDS			=  65536;

// Useable Constants
const int BS_ONLY_STATE				=	BS_MOD_HIDDEN - 1;
const int BS_MOD_ACTIVE				=	BS_MOD_HIDDEN | BS_MOD_DRUNK | BS_MOD_NUTS | BS_MOD_BURNING | BS_MOD_CONTROLLED | BS_MOD_TRANSFORMED | BS_MOD_CONTROLLING;

extern const zSTRING BS_NAMES[BS_MAX];

extern const zSTRING BS_MOD_NAMES[6];

// Attitude ( je höher umso besser )
const int NPC_ATT_MAX		= 4;
enum { NPC_ATT_HOSTILE		= 0, NPC_ATT_ANGRY		= 1, NPC_ATT_NEUTRAL	= 2, NPC_ATT_FRIENDLY		= 3 };

// Anzahl Namen pro NSC-Slot
const int NPC_NAME_MAX				=  5;
const int NPC_MIS_MAX				=  5;

// NSC - Flags
const int NPC_FLAG_FRIENDS			=	1 << 0;   // 1    (not used)
const int NPC_FLAG_IMMORTAL			=	1 << 1;   // 2    unverwundbar
const int NPC_FLAG_GHOST			=	1 << 2;   // 4    transparent
const int NPC_FLAG_PROTECTED		=	1 << 10;  // 1024 COPY PROTECTION

// Waffenmodis
enum {	NPC_WEAPON_NONE =  0, 
		NPC_WEAPON_FIST =  1, NPC_WEAPON_DAG  = 2,
		NPC_WEAPON_1HS	=  3, NPC_WEAPON_2HS  = 4, 
		NPC_WEAPON_BOW	=  5, NPC_WEAPON_CBOW = 6,
		NPC_WEAPON_MAG	=  7,
		NPC_WEAPON_MAX  =  8 };

// AI - Senses - Flags
const int NPC_SENSE_SEE		= 1 << 0;
const int NPC_SENSE_HEAR	= 1 << 1;
const int NPC_SENSE_SMELL	= 1 << 2;

const zREAL NPC_TURNVELOCITY		= 150.0f;
//const zREAL NPC_TURNVELOCITY_MSEC	= 150.0f / 1000.0f;

extern const zSTRING NPC_NODE_RIGHTHAND;
extern const zSTRING NPC_NODE_LEFTHAND;
extern const zSTRING NPC_NODE_SWORD;
extern const zSTRING NPC_NODE_LONGSWORD;
extern const zSTRING NPC_NODE_BOW;
extern const zSTRING NPC_NODE_CROSSBOW;
extern const zSTRING NPC_NODE_SHIELD;
extern const zSTRING NPC_NODE_HELMET;
extern const zSTRING NPC_NODE_JAWS;
extern const zSTRING NPC_NODE_TORSO;						// Torso, kein wirkliches Slot

enum {	// * active Perception *
		NPC_PERC_ASSESSPLAYER			=	1,	NPC_PERC_ASSESSENEMY			=   2,	
		NPC_PERC_ASSESSFIGHTER			=   3,	NPC_PERC_ASSESSBODY				=   4,	
		NPC_PERC_ASSESSITEM				=   5,	
		// * passive perception *
		NPC_PERC_ASSESSMURDER			=	6,	NPC_PERC_ASSESSDEFEAT			=	7,
		NPC_PERC_ASSESSDAMAGE			=	8,	NPC_PERC_ASSESSOTHERSDAMAGE		=	9,
		NPC_PERC_ASSESSTHREAT			=  10,	NPC_PERC_ASSESSREMOVEWEAPON		=  11,
		NPC_PERC_OBSERVEINTRUDER		=  12,	NPC_PERC_ASSESSFIGHTSOUND		=  13,
		NPC_PERC_ASSESSQUIETSOUND		=  14,	NPC_PERC_ASSESSWARN				=  15,
		NPC_PERC_CATCHTHIEF				=  16,	NPC_PERC_ASSESSTHEFT			=  17,
		NPC_PERC_ASSESSCALL				=  18,	NPC_PERC_ASSESSTALK				=  19,
		NPC_PERC_ASSESSGIVENITEM		=  20,	NPC_PERC_ASSESSFAKEGUILD		=  21,	
		NPC_PERC_MOVEMOB				=  22,	NPC_PERC_MOVENPC				=  23,	
		NPC_PERC_DRAWWEAPON				=  24,	NPC_PERC_OBSERVESUSPECT			=  25,	
		NPC_PERC_NPCCOMMAND				=  26,	NPC_PERC_ASSESSMAGIC			=  27,  
		NPC_PERC_ASSESSSTOPMAGIC		=  28,	NPC_PERC_ASSESSCASTER			=  29,	
		NPC_PERC_ASSESSSURPRISE			=  30,	NPC_PERC_ASSESSENTERROOM		=  31,
		NPC_PERC_ASSESSUSEMOB			=  32,
		// * maximum *
		NPC_PERC_MAX					=  33
};

enum
{
	NPCTYPE_AMBIENT			= 0,	
	NPCTYPE_MAIN			= 1,
	NPCTYPE_GUARD			= 2,
	NPCTYPE_FRIEND			= 3,
	NPCTYPE_MINE_AMBIENT	= 4,
	NPCTYPE_MINE_GUARD		= 5,
	NPCTYPE_OW_AMBIENT		= 6,
	NPCTYPE_OW_GUARD		= 7
};

typedef struct TNpcSlot {

	TNpcSlot		() { vob=NULL; };

	zSTRING			name;
	zBOOL			inInventory;
	zBOOL			tmpLevel;
	zSTRING			itemName;

    oCVob *         Vob(){return vob;}

    void            SetVob(oCVob *vob);
    void            ClearVob();

	~TNpcSlot		() { ClearVob(); }
 private:
	oCVob*			vob;
    zBOOL           wasVobTreeWhenInserted:1;	
} TNpcSlot;

typedef struct TNpcPerc {
	
	int				percID;
	int				percFunc;

} TNpcPerc;

class oCNpc : public oCVob {
	zCLASS_DECLARATION	(oCNpc)

public:
	// PARSER ON
	struct {	

		int				idx												;			// Absolute ID des NSC
		zSTRING			name[5]											;			// Namen des NSCs
		zSTRING			slot											;				
		zSTRING			effect											;
		int				npcType											;			// Ambient / Main / Guard etc...
		int				variousFlags									;			// ??? Gedaechtnisflag (1 pro SC)
		int				attribute				[ NPC_ATR_MAX ]			;			// Attributes of NSC
		int				hitChance				[ NPC_HITCHANCE_MAX ]   ;
		int				protection				[ oEDamageIndex_MAX ]	;	
		int				damage					[ oEDamageIndex_MAX ]	;			// Damage per Type 
		int				damagetype										;			// Damage Type(s)
		int				guild											;			// Gildenmitglied ?
		int				level											;			// Gildenlevel ?
		int				mission					[ NPC_MIS_MAX ]			;			// Auftragsnummern		
		int				fighttactic										;			// Kampftactic ( Nummer des AI - Skriptfiles )
		int				fmode											;			// Waffe gezueckt ?
		int				voice											;			// Voice-Number
		int				voicePitch										;			// Voice-Pitch in Halftones
		int				mass											;			// Koerpermasse	
		int				daily_routine									;			// Tagesablauf
		int				startAIState									;			// Zustandsgesteuert
		zSTRING			spawnPoint										;			// Respawn at
		int				spawnDelay										;			// Respawn after time (seconds)
		int				senses											;						
		int				senses_range									;
		int				aiscriptvars			[100]					;			// Zur freien Benutzung im Skript
		zSTRING			wpname											;			// programm initialized for scripts				
						
		zUINT32			experience_points								;			// Erfahrungspunkte
		zUINT32			experience_points_next_level					;			// Erfahrungspunkte die fuer die neachste Stufe benoetigt werden
		// zUINT32		magic_circle									;			// Spruch-Stufe
		zUINT32			learn_points									;			// Lern-Punkte
		int				bodyStateInterruptableOverride					;
		zBOOL			noFocus											;			// does not show name + health bar if set to true
		//zUINT32			chance_lockpick									;			// Chance fuer Versagen beim Schloss-knacken
		//zUINT32			chance_pickpocket								;			// Chance fuer Versagen beim Taschendiebstal
		//zUINT32			chance_acrobatics								;			// Modifikator fuer Fallschaden

		// PARSER OFF
		int		parserEnd;				
	};

	#include	"oNpc_Fight.h"
	#include	"oNpc_Damage.h"
	#include	"oNpc_Move.h"

public:

    // [Moos] In dieser Klasse sollen alle Daten abgelegt werden, die nur von frame zu frame gespeichert werden und vergessen werden können, wenn der NPC aus der Welt entfernt wird.
    class TActiveInfo{
    public:
        // flags:
        zBOOL       modified:1;                 // sagt, dass die Daten hier nach der Initialisierung modifiziert wurden. In diesem Fall düfen sie keinesfalls gelöscht werden.

        zBOOL       putTorchBackInHand:1;       // sagt, dass eine Fackel wieder aus dem Inventory angezündet werden soll, sobald wieder eine Hand frei ist.

        zBOOL       changeTorchAni    :1;       // sagt, dass die Fackelanimation bei Gelegenheit geändert werden soll
        zBOOL       changeTorchAniTo  :1;       // und zwar auf diesen Wert

//        oCNpc      *npc;

        TActiveInfo           (const oCNpc *npc);
        ~TActiveInfo          ();

        zBOOL       DontDelete()                 {return modified;}
    };

    friend class TActiveInfo;

    const TActiveInfo * GetActiveInfo()                const;
          TActiveInfo * GetActiveInfoWritable()        const;

	static oCStealContainer*	stealcontainer;

private:
          TActiveInfo * GetActiveInfoWritablePrivate() const{return (TActiveInfo *)GetActiveInfo();}

	static zBOOL				s_bEnabledDialogCamStop;
	static zBOOL				s_bTargetLocked;
	static zMATRIX4 			s_playerPositionMatrix;

protected:

	// Timed Overlays
    class oCNpcTimedOverlay {
	public:
					oCNpcTimedOverlay	(const zSTRING& mdsName, const zREAL time) { mdsOverlayName = mdsName; timer = time; };
					~oCNpcTimedOverlay	() {};
	
		zBOOL		Process				();		// return TRUE, if its done...
		zSTRING		GetMdsName			() { return mdsOverlayName; };
	private:

		zSTRING		mdsOverlayName;
		zREAL		timer;
	};

	zCList	<oCNpcTimedOverlay>			timedOverlays;
	zCArray	<oCNpcTalent*>				talents;

public :	
	static	void	EnableDialogCamStop			(zBOOL bEnable)	{ oCNpc::s_bEnabledDialogCamStop = bEnable; };

	static zBOOL	IsEnabledTalkBox		()							{ return oCNpc::isEnabledTalkBox;										};
	static void		EnableTalkBox			( zBOOL bEnable = TRUE )	{ oCNpc::isEnabledTalkBox = bEnable;		};
	static zBOOL	IsEnabledTalkBoxPlayer	()							{ return (oCNpc::isEnabledTalkBox && oCNpc::isEnabledTalkBoxPlayer);	};
	static void		EnableTalkBoxPlayer		( zBOOL bEnable = TRUE )	{ oCNpc::isEnabledTalkBoxPlayer = bEnable;	};
	static zBOOL	IsEnabledTalkBoxAmbient	()							{ return (oCNpc::isEnabledTalkBox && oCNpc::isEnabledTalkBoxAmbient);	};
	static void		EnableTalkBoxAmbient	( zBOOL bEnable = TRUE )	{ oCNpc::isEnabledTalkBoxAmbient = bEnable;	};
	static zBOOL	IsEnabledTalkBoxNoise	()							{ return (oCNpc::isEnabledTalkBox && oCNpc::isEnabledTalkBoxNoise);		};
	static void		EnableTalkBoxNoise		( zBOOL bEnable = TRUE )	{ oCNpc::isEnabledTalkBoxNoise = bEnable;	};
	static zBOOL	GetTargetLocked			()							{ return s_bTargetLocked;												};
	static void		SetTargetLocked			(const zBOOL a_bLockTarget)	{ s_bTargetLocked = a_bLockTarget;			};

	// * Get/Set Data *
	oCNpc			();

	virtual void	SetVisual					(zCVisual* v);

    void            Shrink                      ();        // deltes Model (and AI?)
    void            UnShrink                    ();
    void            AvoidShrink                 (int timeout = 1000);        // tells the NPC not to shrink for the next <timeout> frames (timeout not yet implemented...)

	void			CleanUp						();
    
	// Overlay wrappers
    zBOOL           ApplyOverlay                (const zSTRING &on);
    void            RemoveOverlay               (const zSTRING &on);

	// Timed Overlays
	zBOOL			ApplyTimedOverlayMds		(const zSTRING& mdsName, zREAL timer);

    // fatness/scale
    void            SetModelScale               (const zVEC3 &scale);
    void            SetFatness                  (zREAL fat);

	virtual void	InitByScript				(int nr,zBOOL reload = FALSE);
	int				GetInstance					()		{ return instanz; };
	zSTRING			GetInstanceName				();
	int				GetScriptID					()		{ return idx; };
	virtual zBOOL	GetScriptInstance			(zSTRING* &scriptInstanceName, int &scriptInstanceIndex);			// returns name/index, as available
	virtual zBOOL	SetByScriptInstance			(const zSTRING* scriptInstanceName, const int scriptInstanceIndex);	// use 'name' or 'index' exclusively, but not both

	zSTRING			GetName						(zBOOL mem = FALSE);
	zSTRING			GetGuildName				();
	int				GetVoice					() { return voice; };
	int				GetVoicePitch				() { return voicePitch; };
	zBOOL			IsVoiceActive				();
	void			SetMdsName					(const zSTRING &name) { mds_name = name; };
	const zSTRING  &GetMdsName					()                    { return mds_name; };
	zBOOL			GetOverlay					(zSTRING &name);
	zSTRING			GetVisualBody				();
	zSTRING			GetVisualHead				();
	zBOOL			GetCanBeFocused				()					  { return !noFocus; };
	void			SetHead						();

	void			SetAdditionalVisuals		(zSTRING &vBody, int bodyTexNr, int bodyColor, zSTRING &vHead, int headTexNr, int teethTexNr, int armorInstance=-1);
	void			InitModel					();
	zCModel*		GetModel					();
	void			CheckModelOverlays			();

	void			SetMovLock					(zBOOL f);
	zBOOL			IsMovLock					();

	oCAniCtrl_Human*GetAnictrl					();
	oCAIHuman*		GetHumanAI					()				{ return human_ai;		};
	void			DeleteHumanAI				();

	void			ClearEM						();

/*
	void			SetRoute					(zCRoute* rt);
	zCRoute*		GetRoute					( )				{ return route; };
*/

	// * Anis *
	zBOOL			StartStdFaceAni				(int attitude);
	zBOOL			StartFaceAni				(const zSTRING& name, zREAL intensity=zREAL(1.0F), zREAL holdtime=zREAL(-2));
	zBOOL			StopFaceAni					(const zSTRING& name);

	// * Get/Set Data virtuals *
	virtual zTVobCharClass GetCharacterClass	();
	// Disable Npc and remove from world
	virtual void	Disable						();
	// Enable Npc and set Position to current daily-routine-position
	virtual void	Enable						(zVEC3& pos);
	
	// * Attitude *
	void			SetKnowsPlayer				(int playerNumber);
	zBOOL			KnowsPlayer					(oCNpc* player);
	zBOOL			KnowsPlayer					(int playerNumber);
	
	zBOOL			IsFriendly					(oCNpc* other);
	zBOOL			IsNeutral					(oCNpc* other);
	zBOOL			IsAngry						(oCNpc* other);
	zBOOL			IsHostile					(oCNpc* other);

	int				GetAttitude					(oCNpc* other);
	void			SetAttitude					(int wert);
	int				GetPermAttitude				(oCNpc* other);
	void			SetTmpAttitude				(int wert);

	void			CheckAngryTime				();			// periodical

	// * Guilds *
	zBOOL			CanRecruitSC				();				
	void			SetGuild					(int guildID);
	int				GetGuild					();
	void			SetTrueGuild				(int guildID);
	int				GetTrueGuild				();
	int				GetCamp						();
	zBOOL			IsDisguised					();
	zBOOL			IsGuildFriendly				(int g);
	int				GetGuildAttitude			(int g);

	// * Attributes *
	int				GetAttribute				(int nr);
	int				GetHitChance				(int nr);
	void			SetHitChance				(int nr, int value);
	void			SetAttribute				(int nr, int value);
	void			ChangeAttribute				(int nr, int value);
	int				GetProtectionByIndex		( oEDamageIndex nIndex			 );										
	int				GetProtectionByType			( oEDamageType	dwProtectionType );										
	int				GetProtectionByMode			( oTDamageMode	dwProtectionMode );										
	int				GetFullProtection			();																		
	void			SetProtectionByIndex		( oEDamageIndex nIndex, int nValue );
	void			SetProtectionByType			( oEDamageType  nIndex, int nValue );
	int				GetDamageByIndex			( oEDamageIndex nIndex		 );											
	int				GetDamageByType				( oEDamageType	dwDamageType );											
	int				GetDamageByMode				( oTDamageMode  dwDamageMode );											
	void			SetDamages					( int* aryDamages );
	int				GetFullDamage				();																		
	int				GetLevel					()			{ return level; };
	void			SetLevel					(int lev)	{ level = lev;	};

	void			SetToDrunk					(zREAL ms);
	void			HealFromDrunk				();
	void			SetToMad					(zREAL ms);
	void			HealFromMad					();
	void			Regenerate					();
	void			CompleteHeal				();
	void			RefreshNpc					();
	

	// M:  weg damit void			SetRegenerationTime			(int atr, zREAL time);
	void			SetSwimDiveTime				(zREAL swimTimeSec, zREAL diveTimeSec);
	void			GetSwimDiveTime				(zREAL& _swimTime, zREAL& _diveTime, zREAL& _diveCtr);
	
	zBOOL			HasFlag						(int nr);
	void			SetFlag						(int nr);

	// Talents	
	void			SetTalentValue				(int nr, int value);
	int				GetTalentValue				(int nr);
	void			SetTalentSkill				(int nr, int value);
	int				GetTalentSkill				(int nr);

	zBOOL			HasTalent					(int nr, int value=1);
	oCNpcTalent*	GetTalent					(int nr, zBOOL createIfNull=FALSE);
	
/*
	void			SetFallDownHeight			(zREAL fallHeight);
	zREAL			GetFallDownHeight			();
	void			SetFallDownDamage			(int fallDamage);
	void			CreateFallDamage			(zREAL dist);
*/

	void			IdentifyAllMushrooms		();					// Identify all
	oCItem*			IdentifyMushroom			(oCItem* item);		// Identify single

/*
	zREAL			GetJumpRange				();					// How far can he jump ?
	zREAL			GetClimbRange				();
	zBOOL			CanSwim						();					// He is a swimmer/diver ?
	zBOOL			CanDive						();
*/

	//
	//  CODECHANGED [SPECKELS]
	//

	void			StopAllVoices();	// Stops all sounds in listOfVoices

	//
	//	CODECHANGE [ROMAN]
	//

	// * Blut *
/*	void			EnableBlood					( int enabled	  )	{ bloodEnabled	= enabled			?			1		 : 0		; } 	
	int				IsBloodEnabled				( void )				{ return bloodEnabled; }
	void			EnableBloodFlow				( int flow		  )	{ bloodFlow		= flow				?			1		 : 0		; }
	int				IsBloodFlowEnabled			( void )			{ return bloodFlow; }
	void			SetBloodDistance			( int distance	  )	{ bloodDistance = (!distance)		?		 1000		 : distance	; }	
	int				GetBloodDistance			( void )			{ return bloodDistance; }
	void			SetBloodAmount				( int amount	  )	{ bloodAmount	= (!amount)			?		   10		 : amount	; }
	int				GetBloodAmount				( void )			{ return bloodAmount; }
	void			SetBloodEmitter				( zSTRING emitter ) { bloodEmitter	= emitter.IsEmpty() ? "PFX_BLOOD"		 : emitter	; }
	zSTRING			GetBloodEmitter				( void )			{ return bloodEmitter; }
	void			SetBloodTexture				( zSTRING texture ) { bloodTexture	= texture.IsEmpty() ? "ZBLOODSPLAT2.TGA" : texture	; }
	zSTRING			GetBloodTexture				( void )			{ return bloodTexture; }
*/
/*	// * Drehgeschwindigkeit * in Grad pro Sekunde  (DEG-winkel)
	zREAL			GetTurnSpeed				( void			  ) { return speedTurn; }
	void			SetTurnSpeed				( int speed		  ) { speedTurn		= speed				?  speed : NPC_TURNVELOCITY	    ; speedTurn *= 0.001f; }
*/

	// * Schadenstyp *
//	void			SetDefaultDamage			( zTITEMDAMAGE damageDefault ) { defaultDamage = damageDefault; }
//	zTITEMDAMAGE	GetDefaultDamage			( void ) { return defaultDamage; }

	//
	//	CODECHANGE [ROMAN] END
	//

	// * Magic *

	//
	//	CODECHANGE [ROMAN]
	//
	int				spellMana					;
	zBOOL			ReadySpell					( int nSpell, int nMana );
	zBOOL			UnreadySpell				( void );
	oCItem*			GetSpellItem				( int nSpell );
	//
	//	CODECHANGE [ROMAN] END
	//

//
	zBOOL			HasSpell					(int nr);
	void			LearnSpell					(int nr);
	void			DestroySpell				(int nr);
	void			CreateSpell					(int nr);

	int				GetActiveSpellNr			();
	int				GetActiveSpellCategory		();
	int				GetActiveSpellLevel			();
	int				GetActiveSpellIsScroll		();
	int				GetLastHitSpellID			()				{ return lastHitSpellID;	};
	void			SetLastHitSpellID			(const int id)	{ lastHitSpellID = id;		};
	int				GetLastHitSpellCat			()				{ return lastHitSpellCat;	};
	void			SetLastHitSpellCat			(const int cat)	{ lastHitSpellCat = cat;		};

	void			SetActiveSpellInfo			(int nr);

	void			InsertActiveSpell			(oCSpell* spell);
	void			RemoveActiveSpell			(oCSpell* spell);
	void			RemoveActiveSpell			(int nr);
	zBOOL			DoActiveSpells				();
	void			KillActiveSpells			();
	oCSpell*		IsSpellActive				(int nr);

	zBOOL			HasMagic					();
	int				GetNumberOfSpells			();
	void			OpenSpellBook				(zBOOL showMagicCircle = TRUE);
	void			CloseSpellBook				(zBOOL removeall);
	void			CopyTransformSpellInvariantValuesTo( oCNpc* pNpcOther );

	oCMag_Book*		GetSpellBook				();
	void			DoSpellBook					();
	void			SetTmpSpellBook				(oCMag_Book* mag);

	void			GetSpellInfo				(int nr, zSTRING& name, zSTRING& desc);
	void			GetTalentInfo				(int nr, zSTRING& name, zSTRING& desc, zSTRING& skills);
	void			GetAttribInfo				(int nr, zSTRING& name, zSTRING& desc);

//changed[dennis]
	void			MakeSpellBook				( void );
	void			DestroySpellBook			( void );

	// various effect things
	void			AddEffect					(const zSTRING& a_strNewFX, const zCVob* a_pTarget = 0);
	void			RemoveEffect				(const zSTRING& a_strFX);

	// * Dialog *
	void			SetCanTalk					(int timeSec);
	zBOOL			CanTalk						();
	void			SetTalkingWith				(oCNpc* other, zBOOL talking);
	oCNpc*			GetTalkingWith				();
	void			StartTalkingWith			(oCNpc* other);
	void			StopTalkingWith				();
	zCEventMessage* GetTalkingWithMessage		(oCNpc* other);
	zBOOL			ActivateDialogCam			(zREAL timems);
	zBOOL			DeactivateDialogCam			();
	zBOOL			CanBeTalkedTo				();		// Check for running OUs
	void			StopRunningOU				();

	void			CallNSC						(oCNpc *n);
	void			CheckSpecialSituations		();					// periodical
	zBOOL			IsWaitingForAnswer			();
	zBOOL			SetCurrentAnswer			(int status, zBOOL selected, oCNpc* other);
//	zBOOL			WaitsForAnswer				(zBOOL anserYes, oCNpc* npc);
	zTModelAniID	StartDialogAni				();

	// * News *
	oCNewsMemory*	GetNewsMemory				()	{ return &knownNews; };
	
	// * Missions/Infos *
	int				GetMission					(int nr) { if (nr<NPC_MIS_MAX) return mission[nr]; else return 0; };

	// * Perceptions NEW *
	void			ClearPerceptionLists		();
	void			ClearVobList				();
	void			CreateVobList				(zREAL distance);
	void			CreateVobList				(zCArray<zCVob*>& found, zREAL distance);
    void            InsertInVobList             (zCVob *vob);
    void            RemoveFromVobList           (zCVob *vob);
    
	void			SetNpcsToState				(int stateFunc, int radius);

	void			StopCutscenes				();

	void			CreatePassivePerception		(int percType, zCVob* other=NULL, zCVob* victim=NULL);
	static void		CreateSoundPerception		(int percType, zCVob* source, const zVEC3& position, zCVob* victimVob,zBOOL setVictim);
	void			PerceiveAll					();
	void			PerceptionCheck				();
	zBOOL			PercFilterNpc				(oCNpc* npc);
	zBOOL			PercFilterItem				(oCItem* item);
	void			ClearPerception				();
	void			EnablePerception			(int percType, int scriptFunc);
	void			DisablePerception			(int percType);
	zBOOL			HasPerception				(int percType);
	int				GetPerceptionFunc			(int percType);
	void			SetPerceptionTime			(zREAL time);

	// * AI *
	virtual void	InitHumanAI					();
	void			ResetToHumanAI				();
	void			PrintStateCallDebug			(const zSTRING &name, int callfunc, int callperc);

	int				GetAIState					();
	int				GetAIStateTime				();
	zBOOL			IsAIState					(int nr);
	void			ShowState					(int x, int y);
	int				GetOldScriptState			();

	void			ToggleFocusVob				(zBOOL left);
	void			SetFocusVob					(zCVob *vob);
	zCVob*			GetFocusVob					();
	oCNpc*			GetFocusNpc					();
	void			ClearFocusVob				();
	void			CollectFocusVob				(const zBOOL a_bForce = FALSE);
	zBOOL			FocusCheck					(const zCVob* vob, const int type, const int last_type, const zREAL low_azi, zREAL& azi);
	zBOOL			FocusCheckBBox				(const zCVob* vob, const int type, const int last_type, const zREAL low_azi, zREAL& azi);
	void			GetNearestVob				(zREAL maxDist);
	void			GetNearestValidVob			(zREAL max_dist);
	void			ForceVobDetection			(zCVob *v);
	zBOOL			HasVobDetected				(zCVob *v);
//	zCVob*			GetRbtObstacleVob			();
//	zVEC3			GetVecNormalFromBBox		(zCVob* vob, zVEC3& pos);

	void			StartFadeAway				();
	zBOOL			IsFadingAway				();
	zBOOL			FadeAway					();
//	zBOOL			BeamTo						(const zSTRING& targetVob);

	// * Perception *
	zBOOL			FreeLineOfSight				(zCVob* vob);
	zBOOL			FreeLineOfSight				(zVEC3& vec, zCVob *ignore = NULL);
	zBOOL			FreeLineOfSight_WP			(zVEC3& vec, zCVob *ignore = NULL);
	zBOOL			CanSee						(zCVob* vob, zBOOL ignoreAngles = FALSE);
	zBOOL			HasSenseSee					();
	zBOOL			HasSenseHear				();
	zBOOL			HasSenseSmell				();
	void			SetSenses					(int s);
	void			DetectWitnesses				(oCNpc *n, int type);
	virtual	zBOOL	IsMoreImportant				(zCVob* vob1, zCVob* vob2);

	zBOOL			CanSense					(zCVob *vob);

	void			AI_Alarm					( oCNpc *enemy );
	void			AI_ForceDetection			( );

	zBOOL			IsNear						(oCNpc* other);
	zBOOL			AreWeStronger				(oCNpc* enemy);
	oCNpc*			IsEnemyBehindFriend			(oCNpc* friend1);
	int				GetComrades					();

	void			ReactionWitness				(int nr, oCNpc *other, oCNpc *victim);
	
	// * Worldchecks using the current vobList *
	oCItem*			DetectItem					( int flag, zBOOL best = FALSE );
	oCNpc*			DetectPlayer				( );
	oCMobInter*		FindMobInter				( const zSTRING& name );
	zCVobSpot*		FindSpot					( const zSTRING& name, zBOOL checkDistance ,zREAL collectDistance=700);
	oCNpc*			FindNpc						( int instance, int guild, int aiState, zBOOL nearest = TRUE);
	oCNpc*			FindNpcEx					( int instance, int guild, int aiState, zBOOL nearest = TRUE, zBOOL ignorePlayer = FALSE, zBOOL ignoreDead = FALSE );
	oCNpc*			FindNpcExAtt				( int instance, int guild, int aiState, zBOOL nearest = TRUE, zBOOL ignorePlayer = FALSE, zBOOL ignoreDead = FALSE, int att=0 );

	// * active perception *
	zBOOL			AssessPlayer_S				( oCNpc* player);
	zBOOL			AssessEnemy_S				( oCNpc* other );
	zBOOL			AssessFighter_S				( oCNpc* other );
	zBOOL			AssessBody_S				( oCNpc* other );
	zBOOL			AssessItem_S				( oCItem* item );

	// * passive perception *
	zBOOL			AssessMurder_S				( oCNpc* comitter );

	zBOOL			AssessThreat_S				( oCNpc* other );
	zBOOL			AssessDefeat_S				( oCNpc* comitter );
	zBOOL			AssessDamage_S				( oCNpc* comitter, int damage );
	zBOOL			AssessOthersDamage_S		( oCNpc* comitter, oCNpc* victim, int damage );
	
	zBOOL			AssessRemoveWeapon_S		( oCNpc* other );
	zBOOL			ObserveIntruder_S			( );
		
	static zBOOL	AssessFightSound_S			( zCVob* source, const zVEC3& pos, zCVob* victimVob );
	static zBOOL	AssessQuietSound_S			( zCVob* source, const zVEC3& pos );
	zBOOL			AssessWarn_S				( oCNpc* comitter  );
		
	zBOOL			CatchThief_S				( oCNpc* thief );
	zBOOL			AssessTheft_S				( oCNpc* thief );
	
	zBOOL			AssessCall_S				( oCNpc* other );
	zBOOL			AssessTalk_S				( oCNpc* other );

	zBOOL			AssessGivenItem_S			( oCNpc* other , oCItem* item    );
	
	zBOOL			AssessMagic_S				( oCNpc* other , int spellType	);
	zBOOL			AssessStopMagic_S			( oCNpc* other , int spellType  );
	zBOOL			AssessCaster_S				( oCSpell* spell );
	zBOOL			AssessFakeGuild_S			( );

	zBOOL			MoveMob_S					( oCMOB* mob   );
	zBOOL			MoveNpc_S					( oCNpc* other );
	zBOOL			AssessUseMob_S				( oCMobInter* mob );

	zBOOL			AssessEnterRoom_S			( );

	// andere Methoden für die Wahrnehmung
	
	zBOOL			AssessGivenItem				( oCItem* item, oCNpc* other );

	zBOOL			IsInFightMode_S				( int id );
	zBOOL			IsAiming_S					( oCNpc* target );

	// * MOB/ITEM Interaction *
	zCVob*			GetCarryVob					();
	void			SetCarryVob					(zCVob *v);
	void			SetInteractMob				(oCMobInter *mob);	
	oCMobInter*		GetInteractMob				();
	zBOOL			InMobInteraction			(const zSTRING& keyWord, int keyState);

	void			SetInteractItem				(oCItem* item);
	oCItem*			GetInteractItem				()						{ return interactItem; };
	int				GetInteractItemMaxState		(const zSTRING& sceme);
	int				GetInteractItemCurrentState	()						{ return interactItemCurrentState; };
	zCModelAni*		InteractItemGetAni			(const zSTRING& sceme, int from, int to);
	zBOOL			InteractItemIsInState		(const zSTRING& sceme, int state);

	zBOOL			CanUse						(oCItem *item);
	void            DisplayCannotUse            ();
    void            CheckAllCanUse              ();

	void			AddItemEffects				(oCItem *item);
	void			RemoveItemEffects			(oCItem *item);
	
	void			Equip						(oCItem *item);
	void			EquipItem					(oCItem *item);
	void			UnequipItem					(oCItem *item);
	void			EquipBestWeapon				(int weaponCategory);
	void			EquipBestArmor				();
	zBOOL			UseItem						(oCItem *item);
	void			Activate					(int cat, int nr);

	void			PreSaveGameProcessing		();
	void			PostSaveGameProcessing		();

	// * Interrupt Current NSC-Actions *
	zSTRING			GetInterruptPrefix			();
	void			Interrupt					(zBOOL checkBodyState = FALSE, zBOOL stopWeaponChoose = TRUE);
//	void			StandUp						(zBOOL walkingallowed = FALSE);

	// * Body States *
	void			SetBodyState				(int bs);
	int				GetBodyState				();
	int				GetFullBodyState			();
	zSTRING			GetBodyStateName			();
	zBOOL			HasBodyStateModifier		(int nr);
	void			SetBodyStateModifier		(int nr);
	void			ClrBodyStateModifier		(int nr);
	int				GetBodyStateInterruptableOverride() const		{ return bodyStateInterruptableOverride; };
	//
	//	CODECHANGE [ROMAN]
	//
	zSTRING			GetBodyStateModifierNames	();
	int				ModifyBodyState				(int add, int remove );
	//
	//	CODECHANGE [ROMAN] END
	//
	zBOOL			IsBodyStateInterruptable	();
	zBOOL			HasBodyStateFreeHands		();

/*	// * Weapons *
	int				GetNextWeaponMode			(int from, int dir);
	int				GetWeaponMode				();
	virtual void	SetWeaponMode				(int fm);
	virtual void	SetWeaponMode2				(int fm);
	void			SetWeaponMode2				(const zSTRING& mode);
	void			SetToFightMode				(oCItem *item, zBOOL startStandAni = TRUE);
	void			SetToFistMode				();
	void			EquipWeapon					(oCItem *item);
	void			EquipFarWeapon				(oCItem *item);
	void			EquipArmor					(oCItem *item);
	zBOOL			ShieldEquipped				();
	int				GetWeaponDamage				(oCItem* weapon);
	//changed[dennis]
	zREAL			GetDamageMultiplier			();
	void			SetDamageMultiplier			( zREAL dm );
	int				GetShieldValue				();
	int				GetWeaponDamage				();	
	int				GetBluntDamage				(oCItem* weapon);
	oCItem*			GetWeapon					();
	oCItem*			GetEquippedMeleeWeapon		();
	oCItem*			GetEquippedRangedWeapon		();
	oCItem*			GetEquippedArmor			();

	zBOOL			HasArrowInHand				();
	zBOOL			HasArrowInInv				();	
	zBOOL			HasBoltInHand				();
	zBOOL			HasBoltInInv				();
	
	zBOOL			IsMunitionAvailable			(oCItem* weapon);
	zBOOL			HasMunitionInHand			(oCItem* weapon);
	virtual	oCItem*	DoInsertMunition			(const zSTRING& slotName);
	virtual void	DoRemoveMunition			();

	// * Fight *
	void			SetEnemy					(oCNpc* npc);
	oCNpc*			GetEnemy					()					{ return enemy; };
	oCNpc*			GetNextEnemy				();
	zBOOL			IsInFightFocus				(zCVob* target);
	zBOOL			IsConditionValid			();
		
	void			SetFightRange				(int n);
	int				GetFightRange				();
	zBOOL			IsInFightRange				(zCVob* vob, zREAL &dist );
	zBOOL			IsSameHeight				(zCVob* other);
	oCNpc*			GetNearestFightNpcLeft		();
	oCNpc*			GetNearestFightNpcRight		();
	void			TurnToEnemy					();
	
	void			DropUnconscious				(zREAL azi, oCNpc* attacker = NULL);
	zBOOL			IsUnconscious				();
	zBOOL			IsDead						();
*/
	//
	//	CODECHANGE [ROMAN]
	//
//	void			Fleeing						();
	//
	//	CODECHANGE [ROMAN] END
	//
//	void			Fighting					();
	
	void			Follow						();
	zBOOL			EnterParty					();
//	void			CreateDynJump				(zVEC3 &p1, zVEC3 &p2);

	// * Spawning *
	void			SetSummoned					(zBOOL bSummoned) { this->isSummoned = bSummoned; }
	zBOOL			IsSummoned					(void)			  { return this->isSummoned;	  }

	zBOOL			SpawnInRangeAllowed			()						{ return spawnInRange; };
	void			SetSpawnInRangeAllowed		(zBOOL inRangeAllowed)	{ spawnInRange = inRangeAllowed; };
	void			SetCanRespawn				(zBOOL canRespawn)		{ respawnOn = canRespawn; };
	zBOOL			CanRespawn					()						{ return respawnOn; };	

	// * Event Messages *
	virtual void	OnTouch						(zCVob* otherVob);
//	virtual	void	OnDamage					(zCVob* otherVob, zCVob* inflictorVob, zREAL damage, int damageType, const zVEC3& hitLocation);
	virtual void	OnMessage					(zCEventMessage *eventMessage, zCVob* sourceVob);
//	virtual void	DoDie						(oCNpc* attacker = NULL);
	virtual zBOOL	DoDoAniEvents				();
//	virtual zBOOL	DoShootArrow				(zBOOL autoaim = FALSE);
	virtual zBOOL	DoModelSwapMesh				(const zSTRING &n1, const zSTRING &n2);
	virtual zBOOL	DoTakeVob					(zCVob *vob);
	virtual zBOOL	DoDropVob					(zCVob *vob);
	virtual zBOOL	DoRemoveFromInventory		(oCItem *item);
	virtual zBOOL	DoPutInInventory			(oCItem *item);
//	virtual zBOOL	DoSetToFightMode			(oCItem *item);
	virtual zBOOL	DoThrowVob					(zCVob *vob, zREAL dist);
	virtual zBOOL	DoExchangeTorch				();
	
	// * Owner *
	oCItem*			HasEquippedStolenItem		(oCNpc* npc);
	zBOOL			CheckForOwner				(zCVob *v);
	
	// * Torch *
	zBOOL			HasTorch					();
	void			ExchangeTorch				();
	void			SetTorchAni					(zBOOL f, zBOOL now=TRUE);
    void            CheckSetTorchAni            ();
    void            CheckPutbackTorch           ();

	// * Inventory *
	// *** Check Inventory ***
	oCItem*			GetFromInv					(int instance, int anz);

	oCItem*			IsInInv						(oCItem* item,				int num = 1);
	oCItem*			IsInInv						(int instance,				int num = 1);
	oCItem*			IsInInv						(const zSTRING& instance,	int num = 1);
	//changed [dennis]
	zBOOL			CanCarry					(oCItem* item);
	// *** Put In Inventory ***
	oCItem*			PutInInv					(oCItem* item);
	oCItem*			PutInInv					(int instance,				int num = 1);
	oCItem*			PutInInv					(const zSTRING& instance,	int num = 1);
	// *** Remove From Inventory ***
	oCItem*			RemoveFromInv				(oCItem* item,				int num = 1);
	oCItem*			RemoveFromInv				(int instance,				int num = 1);
	oCItem*			RemoveFromInv				(const zSTRING& instance,	int num = 1);
	void			DropInventory				();

	void			PutInSlot					(const zSTRING& slotName, oCVob* vob, zBOOL inInv = FALSE);
	void			PutInSlot					(TNpcSlot* slot, oCVob* vob, zBOOL inInv = FALSE);
	oCVob*			RemoveFromSlot				(const zSTRING& slotName, zBOOL dropIt = TRUE, zBOOL killEffect=TRUE);
	oCVob*			RemoveFromSlot				(TNpcSlot* slot, zBOOL dropIt = TRUE, zBOOL killEffect=TRUE);
    void            RemoveFromAllSlots          (zBOOL dropIt = TRUE);
	oCVob*			DropFromSlot				(const zSTRING& slotname);
	oCVob*			DropFromSlot				(TNpcSlot* slot);
	void			UpdateSlots					();		// Periodical
	
	// special effect handling
	void			SetItemEffectControledByModel(oCItem* a_pItem, zCModelNodeInst* a_pNode,  const zBOOL a_bModelControl, const zBOOL a_bForceInvisible = FALSE, const zBOOL a_bItemEffectCleanUp=FALSE);

	zBOOL			HasMissionItem				();

	void			SetToSlotPosition			(zCVob* vob, const zSTRING& slotName);
	TNpcSlot*		GetInvSlot					(const zSTRING& name);
	TNpcSlot*		GetInvSlot					(zCVob* vob);
	zBOOL			IsInvSlotAvailable			(const zSTRING& name);
	void			CreateInvSlot				(const zSTRING& name); 
	void			DeleteInvSlot				(const zSTRING& name);
	zBOOL			IsSlotFree					(const zSTRING& name);
	zBOOL			IsSlotFree					(TNpcSlot* slot);
	oCVob*			GetSlotVob					(const zSTRING& name);
	oCItem*			GetSlotItem					(const zSTRING& name);
	oCNpc*			GetSlotNpc					(const zSTRING& name);	
	//
	//	CODECHANGE [ROMAN]
	//
	oCItem*			GetItem						(int nCategory, int nSlot);
	//
	//	CODECHANGE [ROMAN] END
	//

	void			SetRightHand				(oCVob *vob);
	oCVob*			GetRightHand				();
	void			SetLeftHand					(oCVob *vob);
	oCVob*			GetLeftHand					();

	zBOOL			HasInHand					(int instance);
	zBOOL			HasInHand					(zCVob* what);
	void			RemoveFromHand				();
	void			DropAllInHand				();
	void			UpdateItemsInHand			();

	void			DropVob						(oCVob* vob, zVEC3 &pos); 

	void			CreateItems					(int instanz, int anz);

	void			OpenInventory				(int mode);
	void			CloseInventory				();
	zBOOL			OpenSteal					();
	void			CloseSteal					();	
	void			OpenDeadNpc					();
	void			CloseDeadNpc				();
	zBOOL		IsVictimAwareOfTheft		();
	void			StopTheft					( oCNpc* pNpcBurgler, zBOOL bVictimAware );

	// * Screens * 
	void			OpenScreen_Status			();
	void			OpenScreen_Help				();
	void			OpenScreen_Log				();
	void			OpenScreen_Map				(int mapInst = 0);

	// * Trading *
	void			OpenTradeContainer			(oCItem* item, oCNpc* tradingWithNpc, int amount);
	void			OpenTradeOffer				(oCNpc* player);
	oCNpc*			GetTradeNpc					(void);
	void			SetTradeNpc					(oCNpc* tradingWithNpc);
	void			CloseTradeContainer			();
	oCItem*			GetTradeItem				();
	zBOOL			CheckItemReactModule		(oCNpc* npc, oCItem* itemint);
	void			ExchangeTradeModules		(oCNpc* npc);

	// * Sounds *
	virtual void	GetSoundMaterial_MA			(zCSoundManager::zTSndManMedium &med1, oTSndMaterial &mat1, const zSTRING s = "");
	virtual void	GetSoundMaterial_AM			(zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2, int damage);
	virtual void	GetSoundMaterial_MH_HM		(zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2);

	// * Players *
	virtual zBOOL	IsAPlayer					();
	virtual zBOOL	IsSelfPlayer				();
	virtual void	SetAsPlayer					();
	virtual zBOOL	IsMonster					();
	virtual zBOOL	IsHuman						();
	virtual zBOOL	IsGoblin					();
	virtual zBOOL	IsOrc						();
	virtual zBOOL	IsSkeleton					();
	virtual int		GetPlayerNumber				();
	virtual zBOOL	IsAniMessageRunning			()										{ return m_bAniMessageRunning;	};

	// * Cutscenes *
	int				GetCutsceneDistance			();
	int				GetCutsceneReaction			();
	
	void			SetCSEnabled				(zBOOL enabled);	
	virtual int		GetCSStateFlags				();	
	zBOOL			IsInGlobalCutscene			();
	
	// * Sound *
	zREAL			GetDistToSound				();
	zCVob*			GetSoundSource				();
	void			SetSoundSource				(int soundType, zCVob* soundVob, zVEC3& soundPos);
	zVEC3			GetSoundPosition			() { return soundPosition; };

	// * Helpers *
	virtual void	ProcessNpc					();					// Called every Frame....
	void			RenderNpc					(zCView *v);
//	virtual	void	ResetPos					(zVEC3 &pos);
	zREAL			GetThrowSpeed				(const zREAL dist, const zREAL angle);
/*	zREAL			GetAngle					(zCVob*  to);
	void			GetAngles					(zCVob*  to, zREAL& azi, zREAL& elev);	
	void			GetAngles					(zVEC3& pos, zREAL& azi, zREAL& elev);
	zREAL			Turn						(zVEC3 &dir);
	zREAL			Turning						(zVEC3 &dir);
	int				CanGo						(zREAL len, zVEC3 &cdNormal);
	zREAL			GetDistanceToPos2			(zVEC3& pos, zBOOL dim2 = FALSE);
*/	
	// * Debug *
	virtual void	ShowDebugInfo				(zCCamera *camera);
	void			SetShowNews					(zBOOL on);

	// Special -> Spacer AI aktivieren
	void			UseStandAI					();

	// **********
	// * Vars	*
	// **********
	oCMagFrontier		magFrontier;
	oCNpc_States		state;							// AI - State
	oCNpcInventory		inventory2;
	oCItemContainer*	trader;
	oCNpc*				tradeNpc;
	
	// * Cutscenes *
	zREAL				rangeToPlayer;

	// **********
	// * Static *
	// **********
	// Init 
	static void			InitStatics				();
	static void			ReleaseStatics			();
	
	// * AI *
	static zBOOL		GetNpcAIDisabled		()				{ return ai_disabled;			};
	static void			SetNpcAIDisabled		(zBOOL off);

	static void			SetMessagesSkip			(zREAL timems)	{ ai_messagesSkip			= timems;
																  ai_messagesSkipTimer		= 0.0f;
																};
	static zREAL		GetMessagesSkip			()				{ return ai_messagesSkip;		};

	static void			SetScriptStateSkip		(zREAL timems)	{ ai_scriptStateSkip		= timems;	
																  ai_scriptStateSkipTimer	= 0.0f;
																};
	static zREAL		GetScriptStateSkip		()				{ return ai_scriptStateSkip;	};
	static zBOOL		IsScriptStateAIEnabled	();

	static void			SetBaseAIEnabled		(zBOOL enable)	{ ai_baseEnabled = enable;		};
	static zBOOL		GetBaseAIEnabled		()				{ return ai_baseEnabled;		};

	static void			ProcessAITimer			();

	static zBOOL		IsMessageAIEnabled		();
	static zBOOL		IsScripStateAIEnabled	();


	static zSTRING		GetInstanceByID			(int nr);
	static int			GetIDByInstance			(const zSTRING &name);

	static void			SetPerceptionRange		(int percID, zREAL	percDist);
	static zBOOL		IsInPerceptionRange		(int percID, zCVob* vob1, zCVob* vob2);
	static zBOOL		IsInPerceptionRange		(int percID, zREAL  distance);

	static oCNpc*		player;
	static zBOOL		godmode;
	static int			angle_near;			// Winkel fuer Auto-Heading im Nahkampf (+-)
	static int			angle_far_up;		// Hoehenwinkel fuer Auto-Heading Fernkampf (+-)
	static int			angle_far_side;		// Seitenwinkel fuer Auto-Heading Fernkampf (+-)
	static int			game_mode;

	static oCNpc*		dontArchiveThisNpc;		

protected :

	virtual				~oCNpc					();
	// ***********
	// * Methods *
	// ***********
	virtual void		ThisVobAddedToWorld		(zCWorld *homeWorld);		// called AFTER the actual addition
	virtual void		ThisVobRemovedFromWorld	(zCWorld *homeWorld);		// called BEFFORE the actual removal

	void				Burn					(int damage, zREAL timems);
	void				StopBurn				();

	//
	//  CODECHANGED [SPECKELS]
	//

	zCArray<zTSoundHandle>	listOfVoiceHandles;	// list of sound-handles of voices
	int						voiceIndex;			

	zCArray<oCVisualFX*>	effectList;

	zBOOL					UpdateNextVoice();	// returns TRUE if last voice was updated: next call will start at first

	// * Event Messages *

	// *** Positioning ***
/*	zBOOL				EV_RobustTrace		(oCMsgMovement* csg);
	zBOOL				EV_GotoPos			(oCMsgMovement* csg);
	zBOOL				EV_GotoVob			(oCMsgMovement* csg);
	zBOOL				EV_GoRoute			(oCMsgMovement* csg);
	zBOOL				EV_Turn				(oCMsgMovement* csg);
	zBOOL				EV_TurnToPos		(oCMsgMovement* csg);
	zBOOL				EV_TurnToVob		(oCMsgMovement* csg);
	zBOOL				EV_TurnAway			(oCMsgMovement* csg);
	zBOOL				EV_Jump				(oCMsgMovement* csg);
	zBOOL				EV_WhirlAround		(oCMsgMovement* csg);
	zBOOL				EV_SetWalkMode		(oCMsgMovement* csg);
	zBOOL				EV_StandUp			(oCMsgMovement* csg);
	zBOOL				EV_CanSeeNpc		(oCMsgMovement* csg);
	zBOOL				EV_Strafe			(oCMsgMovement* csg);
	zBOOL				EV_GotoFP			(oCMsgMovement* csg);
	zBOOL				EV_AlignToFP		(oCMsgMovement* csg);
	zBOOL				EV_Dodge			(oCMsgMovement* csg);
*/
	// *** Weapons ***
/*BOOL				EV_DrawWeapon		(oCMsgWeapon* csg);
	zBOOL				EV_DrawWeapon1		(oCMsgWeapon* csg);
	zBOOL				EV_DrawWeapon2		(oCMsgWeapon* csg);
	zBOOL				EV_RemoveWeapon		(oCMsgWeapon* csg);
	zBOOL				EV_RemoveWeapon1	(oCMsgWeapon* csg);
	zBOOL				EV_RemoveWeapon2	(oCMsgWeapon* csg);
	zBOOL				EV_ChooseWeapon		(oCMsgWeapon* csg);
	zBOOL				EV_ForceRemoveWeapon(oCMsgWeapon* csg);
	zBOOL				EV_EquipBestWeapon	(oCMsgWeapon* csg);
	zBOOL				EV_EquipBestArmor	(oCMsgWeapon* csg);
	zBOOL				EV_UnequipWeapons	(oCMsgWeapon* csg);
	zBOOL				EV_UnequipArmor		(oCMsgWeapon* csg);
	//
	//	CODECHANGE [ROMAN]
	//
	zBOOL				EV_EquipArmor		(oCMsgWeapon* csg);
	//
	//	CODECHANGE [ROMAN] END
	//

	// *** Attacks ***
	zBOOL				EV_AttackForward	(oCMsgAttack* csg);
	zBOOL				EV_AttackLeft		(oCMsgAttack* csg);
	zBOOL				EV_AttackRight		(oCMsgAttack* csg);
	zBOOL				EV_AttackRun		(oCMsgAttack* csg);
	zBOOL				EV_AttackFinish		(oCMsgAttack* csg);
	zBOOL				EV_Parade			(oCMsgAttack* csg);
	//
	//	CODECHANGE [ROMAN]
	//
	zBOOL				EV_AttackMagic		(oCMsgAttack* csg);
	zBOOL				EV_AttackBow		(oCMsgAttack* csg);

	// *** Aim ***
	zBOOL				EV_AimAt			(oCMsgAttack* csg);
	zBOOL				EV_StopAim			(oCMsgAttack* csg);
	zBOOL				EV_ShootAt			(oCMsgAttack* csg);

	zBOOL				InitAim				( oCMsgAttack* csg, oCNpc** pEnemy, zBOOL *pDrawn, zBOOL *pAmmo, zBOOL bKillFormerMsg );
	zBOOL				TransitionAim		( zTModelAniID idCurrentAni, zTModelAniID idTargetAni );
	zBOOL				InterpolateAim		( oCNpc* pEnemy );
	zBOOL				FinalizeAim			( zBOOL bStartMelee = FALSE, zBOOL bStandUp = FALSE );

	zBOOL				hasLockedEnemy	;
	zBOOL				didShoot		;
	zBOOL				didHit			;
	zBOOL				wasAiming		;

	// *** Defend ***
	zBOOL				EV_Defend			(oCMsgAttack* csg);

	zBOOL				isDefending		;
	zBOOL				didParade		;

	//
	//	CODECHANGE [ROMAN] END
	//
*/
	zBOOL				EV_CastSpell		(oCMsgMagic* csg);

	// *** UseItem ***
	zBOOL				EV_Drink			(oCMsgUseItem* csg);

	// *** States ***
	zBOOL				EV_Unconscious			(oCMsgState* csg);
	zBOOL				EV_DoState				(oCMsgState* csg);
	zBOOL				EV_Wait					(oCMsgState* csg);

	// *** World Manipulations ***
	zBOOL				EV_TakeVob				(oCMsgManipulate* csg);
	zBOOL				EV_DropVob				(oCMsgManipulate* csg);
	zBOOL				EV_ThrowVob				(oCMsgManipulate* csg);
	zBOOL				EV_Exchange				(oCMsgManipulate* csg);
	zBOOL				EV_UseMob				(oCMsgManipulate* csg);
	zBOOL				EV_TakeMob				(oCMsgManipulate* csg);
	zBOOL				EV_DropMob				(oCMsgManipulate* csg);
	zBOOL				EV_UseItemToState		(oCMsgManipulate* csg);
	zBOOL				EV_UseItem				(oCMsgManipulate* csg);
	zBOOL				EV_EquipItem			(oCMsgManipulate* csg);

	zBOOL				EV_InsertInteractItem	(oCMsgManipulate* csg);
	zBOOL				EV_RemoveInteractItem	(oCMsgManipulate* csg);
	zBOOL				EV_CreateInteractItem	(oCMsgManipulate* csg);
	zBOOL				EV_DestroyInteractItem	(oCMsgManipulate* csg);
	zBOOL				EV_PlaceInteractItem	(oCMsgManipulate* csg);
	zBOOL				EV_ExchangeInteractItem	(oCMsgManipulate* csg);
	zBOOL				EV_UseMobWithItem		(oCMsgManipulate* csg);

	void				CallScript				(const zSTRING& funcName);
	void				CallScript				(int funcIndex);

	zBOOL				EV_CallScript			(oCMsgManipulate* csg);

	// *** Conversation ***
	zBOOL				EV_PlayAniSound			(oCMsgConversation* csg);
	zBOOL				EV_PlayAni				(oCMsgConversation* csg);
	zBOOL				EV_PlayAniFace			(oCMsgConversation* csg);
	zBOOL				EV_PlaySound			(oCMsgConversation* csg);
	zBOOL				EV_LookAt				(oCMsgConversation* csg);
	zBOOL				EV_StopLookAt			(oCMsgConversation* csg);
	zBOOL				EV_PointAt				(oCMsgConversation* csg);
	zBOOL				EV_StopPointAt			(oCMsgConversation* csg);
	zBOOL				EV_QuickLook			(oCMsgConversation* csg);
	zBOOL				EV_Output				(oCMsgConversation* csg);
	zBOOL				EV_OutputSVM			(oCMsgConversation* csg);
	zBOOL				EV_OutputSVM_Overlay	(oCMsgConversation* csg);
	zBOOL				EV_Cutscene				(oCMsgConversation* csg);
	zBOOL				EV_WaitTillEnd			(oCMsgConversation* csg);
	zBOOL				EV_Ask					(oCMsgConversation* csg);
	zBOOL				EV_WaitForQuestion		(oCMsgConversation* csg);
	zBOOL				EV_ProcessInfos			(oCMsgConversation* csg);
	zBOOL				EV_StopProcessInfos		(oCMsgConversation* csg);
	// [EDENFELD] neu 1.09
	zBOOL				EV_SndPlay				(oCMsgConversation* csg);
	// [EDENFELD] neu 1.14d
	zBOOL				EV_PrintScreen			(oCMsgConversation* csg);
	zBOOL				EV_StartFX				(oCMsgConversation* csg);
	zBOOL				EV_StopFX				(oCMsgConversation* csg);

#if defined(SECUROM) && !defined(COMPILING_SPACER)
	// *** Request ***
	zBOOL				EV_Request				(oCMsgRequest* csg);
#endif


	// *** RobustTrace Movement ***
/*	zBOOL				RobustTrace				();
	zBOOL				RbtMoveToExactPosition	();
	zBOOL				RbtAvoidObstacles		();
	zBOOL				RbtInsertDirection		(zVEC3 direction);
	zBOOL				RbtCheckLastDirection	(zREAL dist);
	void				RbtInit					(zVEC3& tpos, zCVob* tvob);
	void				RbtUpdate				(zVEC3& tpos, zCVob* tvob);
	void				RbtReset				();
	zBOOL				RbtIsObjectObstacle		(zCVob* obstacle, const zVEC3& pos, const zVEC3& dir, zVEC3& cdNormal);
	zBOOL				RbtIsDirectionValid		(const zVEC3& direction);
	


public:
	zBOOL				RbtGetObstacle			(const zVEC3& pos, const zVEC3& dir, zCVob* &obstacle, zVEC3& cdNormal);
*/
protected:

	// *** FIGHT KI ***
/*	int					GetFightActionFromTable	(int situationNr);
	int					GetCurrentFightMove		();
	int					FindNextFightAction		();
	int					ThinkNextFightAction	();
	zBOOL				FightAttackMelee		(int myMove);
	zBOOL				FightAttackBow			();
	zBOOL				FightAttackMagic		();
*/
	//
	//	CODECHANGE [ROMAN]
	//
//	int					ThinkNextFleeAction		();
	//
	//	CODECHANGE [ROMAN] END
	//
//	void				GotoFightPosition		();
//	void				CheckRunningFightAnis	();

	// *************************************
	// Hilfsfunktionen ( Netzwerk relevant )
	// *************************************

	int					GetInvCategoryNum		()			{ return INV_MAX; };

	// *************************************
	// Pack / Unpack
	// *************************************	
	void				Pack					(zCBuffer& buffer);
	void				Unpack					(zCBuffer& buffer);

	// *************************************
	// Archive / Unarchive
	// *************************************
	virtual void		Archive					(zCArchiver &arc);
	virtual void		Unarchive				(zCArchiver &arc);
    virtual zBOOL       AllowDiscardingOfSubtree();


   // packed flags: put all booleans here

	// Debug
public:
	zBOOL				showaidebug        :1;
	zBOOL				showNews           :1;

	zBOOL				csAllowedAsRole    :1;
protected:
	zBOOL				isSummoned         :1;
	zBOOL				respawnOn          :1;
	zBOOL				movlock            :1;

	zBOOL				drunk              :1;							// Betrunken ?
	zBOOL				mad                :1;							// Verrückt ?
	zBOOL				overlay_wounded    :1;          				// Overlay active ?
	zBOOL				inOnDamage         :1;

	zBOOL				autoremoveweapon   :1;
	zBOOL				openinventory      :1;
	zBOOL				askroutine         :1;
	zBOOL				spawnInRange       :1;


    // packed ints; TODO: geht das noch kompakter?
	int					body_TexVarNr      :16;	    		// Body-Texture-Variation
	int					body_TexColorNr    :16;				// SkinColor
	int					head_TexVarNr      :16;				// Head-Texture-Variation	
	int					teeth_TexVarNr     :16; 			// Teeth-Texture-Variation
	int					guildTrue          :8;				// Originalgilde ( bei Verwandlung )

	int					drunk_heal         :8;				// Betrunken-Zähler  // FIXME: werden die zwei überhaupt noch verwendet?
	int					mad_heal           :8;  			// Verrückt-Zähler

	int					spells             :8;

	int					bodyState          :19;

	int					m_bAniMessageRunning:1;

	int					instanz;

	// **********
	// * Vars	*
	// **********

	//

	// * Visual *
	zSTRING				mds_name;
	zSTRING				body_visualName;
	zSTRING				head_visualName;

    zVEC3               model_scale;
    zREAL               model_fatness;

	// * Ex. Data *
	int					namenr;							// Aktuelle Namensnummer
	zREAL				hpHeal;							// Counter natürliche Heilung HP
	zREAL				manaHeal;						// Counter natürliche Heilung MANA
	zREAL				swimtime,	divetime;
	zREAL				divectr;
	zCVob*				fireVob;
	int					fireDamage;
	zREAL				fireDamageTimer;

	// * Attitudes *
	int					attitude;						// Attitude des NSC gegenueber dem SC (1 pro SC)
	int					tmp_attitude;						
	zREAL				attTimer;
	int					knowsPlayer;

	// * Perceptions NEW *
	TNpcPerc			percList		[NPC_PERC_MAX];
	int					percActive;
	zREAL				percActiveTime;
	zREAL				percActiveDelta;

	// * Talents *
public:
	zBOOL				overrideFallDownHeight;			// nach FLAY-DAMAGE soll die falldown height nicht beruecksichtigt werden
protected:
	zREAL				fallDownHeight;					// Height without Damage
	int					fallDownDamage;					// Damage per meter
		
	// * Spells *
	oCMag_Book*			mag_book;
	zCList<oCSpell>		activeSpells;
	int					lastHitSpellID;
	int					lastHitSpellCat;

    // * Overlays *
	zCArray<zSTRING>	activeOverlays;

	// * Dialog *
	oCAskBox*			askbox;							// current AskBox
	int					askYes,askNo;					// and Scriptfunction-Markers for Answer
	zREAL				canTalk;	
	oCNpc*				talkOther;

	oCInfo*				info;							// Last saved info
	oCNews*				news;							// Last given news
	oCMission*			curMission;

	// * News *
	oCNewsMemory		knownNews;						// all known News

	// * Mob/Item Interaction *
	zCVob*				carry_vob;	
	oCMobInter*			interactMob;
	oCItem*				interactItem;
	int					interactItemCurrentState;
	int					interactItemTargetState;
	
	// * AI *
	int					script_aiprio;					// aktuelle Skriptprioritaet ( nicht detect/process Prioritaet )
	int					old_script_state;
	oCAIHuman*			human_ai;
	oCAniCtrl_Human*	anictrl;
	zCRoute*			route;							// current Route;

	//changed[dennis]
	zREAL				damageMul;

	// * Event Messages *
	oCNpcMessage*		csg;							// Fixme : Name nochmal ändern
	oCNpcMessage*		lastLookMsg;
	oCNpcMessage*		lastPointMsg;
	
	// * Focus *
	zCArray<zCVob*>		vobList;
	zREAL				vobcheck_time;
	zREAL				pickvobdelay;
//	oCNpc*				enemy;
	zCVob*				focus_vob;
	
	// * Inventory *
	zCArray<TNpcSlot*>	invSlot;
	zCArray<TNpcSlot*>  tmpSlotList;

	// * Trading *

	// * FadeAway / Respawn *
	zREAL				fadeAwayTime;
	zREAL				respawnTime;

	// * Kampf *
	zREAL				selfDist;
	int					fightRangeBase;				// BasisReichweite
	int					fightRangeFist;				// Nahkampfreichweite (nur Faustkampf)
	int					fightRangeG;
	
	zREAL				fight_waitTime;
	zTModelAniID		fight_waitForAniEnd;
	zREAL				fight_lastStrafeFrame;

	// * logical Sound *
	int					soundType;
	zCVob*				soundVob;
	zVEC3				soundPosition;

	// * Network *
	zCPlayerGroup*		playerGroup;
	
	// RobustTracing
/*	struct oTRobustTrace {
		struct {
			zUINT8			stand				: 1;		
			zUINT8			dirChoosed			: 1;
			zUINT8			exactPosition		: 1;
			zUINT8			targetReached		: 1;
			zUINT8			standIfTargetReached: 1;
			zUINT8			waiting				: 1;
		};
		zVEC3			targetPos;
		zCVob*			targetVob;
		zCVob*			obstVob;
		zREAL			targetDist;
		zREAL			lastTargetDist;
		zREAL			maxTargetDist;
		zREAL			dirTurn;
		zREAL			timer;			
		zVEC3			dirFirst;
		zREAL			dirLastAngle;
		zCList<zVEC3>	lastDirs;
		int				frameCtr;
	};
	oTRobustTrace		rbt;
*/	
	//
	//	CODECHANGE [ROMAN]
	//

	//	*** Blood
/*	int 	bloodEnabled ;	
	int 	bloodDistance;	
	int		bloodAmount	 ;	
	int 	bloodFlow	 ;	
	zSTRING bloodEmitter ;	
	zSTRING bloodTexture ;	
*/
	//	*** Turn
//	zREAL	speedTurn	 ;

	//	*** Damage Type
//	zTITEMDAMAGE	defaultDamage;

	//	*** Flee
/*	zCList< zCWaypoint >	listFleePoints;
	zCWaypoint*				waypointFlee;
	zBOOL					foundFleePoint;
	zBOOL					reachedFleePoint;
//	oCNpc					npcFlee;
	zVEC3					vecFlee;
	zVEC3					posFlee;
*/
	//
	//	CODECHANGE [ROMAN] END
	//

	// ***********
	// * Statics *
	// ***********
 
//	static void			InitFightAI				();
//	static void			ExitFightAI				(); // Moos
	static void			InitBodyStates			();
		
	static int			bodyStateList[BS_MAX];
	static zBOOL		ai_disabled;

	static zREAL		ai_messagesSkip;
	static zREAL		ai_messagesSkipTimer;
	static zREAL		ai_scriptStateSkip;
	static zREAL		ai_scriptStateSkipTimer;
	static zBOOL		ai_baseEnabled;

	static zBOOL		isEnabledTalkBox;			// Subtitles on/off for all NPCs
	static zBOOL		isEnabledTalkBoxPlayer;		// Subtitles on/off for the PC			(off if not isEnabledTalkBox)
	static zBOOL		isEnabledTalkBoxAmbient;	// Subtitles on/off for ambient talk	(off if not isEnabledTalkBox)
	static zBOOL		isEnabledTalkBoxNoise;		// Subtitles on/off if without target	(off if not isEnabledTalkBox)
};

// ******************************************************************************************
// Gilden - Beziehungen 
// ******************************************************************************************



// Einzelgaenger
const int NPC_GIL_NONE						=  0;

const int NPC_GIL_PALADIN					=  1;
const int NPC_GIL_MILIZ						=  2;
const int NPC_GIL_VOLK						=  3;
const int NPC_GIL_FEUERKREIS				=  4;
const int NPC_GIL_NOVIZE					=  5;
const int NPC_GIL_DRACHENJAEGER				=  6;
const int NPC_GIL_SOELDNER					=  7;
const int NPC_GIL_BAUERN					=  8;
const int NPC_GIL_BANDIT					=  9;
const int NPC_GIL_PRISONER					= 10;
const int NPC_GIL_DEMENTOR					= 11;
const int NPC_GIL_OUTLANDER					= 12;
const int NPC_GIL_PIRAT						= 13;
const int NPC_GIL_WASSERKREIS				= 14;

const int NPC_GIL_PUBLIC					= 15;  // for Portal Rooms

const int NPC_GIL_HUMANS					= 16;  // human separator

// Monster / Unterirdische
const int NPC_GIL_MEATBUG					= 17;
const int NPC_GIL_SHEEP						= 18;
const int NPC_GIL_GOBBO						= 19;
const int NPC_GIL_GOBBO_SKELETON			= 20;
const int NPC_GIL_SUMMONED_GOBBO_SKELETON	= 21;
const int NPC_GIL_SCAVANGER					= 22;
const int NPC_GIL_GIANT_RAT					= 23;
const int NPC_GIL_GIANT_BUG					= 24;
const int NPC_GIL_BLOODFLY					= 25;
const int NPC_GIL_WARAN						= 26;
const int NPC_GIL_WOLF						= 27;
const int NPC_GIL_SUMMONED_WOLF				= 28;
const int NPC_GIL_MINECRAWLER				= 29;
const int NPC_GIL_LURKER					= 30;
const int NPC_GIL_SKELETON					= 31;
const int NPC_GIL_SUMMONED_SKELETON			= 32;
const int NPC_GIL_SKELETON_MAGE				= 33;
const int NPC_GIL_ZOMBIE					= 34;
const int NPC_GIL_SNAPPER					= 35;
const int NPC_GIL_SHADOWBEAST				= 36;
const int NPC_GIL_SHADOWBEAST_SKELETON		= 37;
const int NPC_GIL_HARPY						= 38;
const int NPC_GIL_STONEGOLEM				= 39;
const int NPC_GIL_FIREGOLEM					= 40;
const int NPC_GIL_ICEGOLEM					= 41;
const int NPC_GIL_SUMMONED_GOLEM			= 42;
const int NPC_GIL_DEMON						= 43;
const int NPC_GIL_SUMMONED_DEMON			= 44;
const int NPC_GIL_TROLL						= 45;
const int NPC_GIL_SWAMPSHARK				= 46;
const int NPC_GIL_DRAGON					= 47;
const int NPC_GIL_MOLERAT					= 48;
const int NPC_GIL_ALLIGATOR					= 49;
const int NPC_GIL_SWAMPGOLEM				= 50;
const int NPC_GIL_STONEGUARDIAN				= 51;
const int NPC_GIL_GARGOYLE					= 52;
const int NPC_GIL_EMPTY_A					= 53;
const int NPC_GIL_SUMMONED_GUARDIAN			= 54;
const int NPC_GIL_SUMMONED_ZOMBIE			= 55;
const int NPC_GIL_EMPTY_B					= 56;
const int NPC_GIL_EMPTY_C					= 57;

const int NPC_GIL_ORCS						= 58;  // orc separator

const int NPC_GIL_ORC						= 59;
const int NPC_GIL_FRIENDLYORC				= 60;
const int NPC_GIL_UNDEADORC					= 61;
const int NPC_GIL_DRACONIAN					= 62;
const int NPC_GIL_EMPTYORC1					= 63;
const int NPC_GIL_EMPTYORC2					= 64;
const int NPC_GIL_EMPTYORC3					= 65;

const int NPC_GIL_MAX						= 66;

#endif
