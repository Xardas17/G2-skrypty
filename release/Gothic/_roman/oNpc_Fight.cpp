/******************************************************************************** 
 
     $Workfile:: oNpc_Fight.cpp       $                $Date:: 13.04.01 18:27   $
     $Revision:: 30                   $             $Modtime:: 11.04.01 21:57   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oNpc_Fight.cpp $
 * 
 * 30    13.04.01 18:27 Edenfeld
 * 
 * 29    16.02.01 18:59 Wohlers
 * 
 * 28    15.02.01 18:38 Wohlers
 * 
 * 27    15.02.01 18:37 Wohlers
 * 
 * 26    15.02.01 2:21 Wohlers
 * 
 * 25    30.01.01 21:28 Wohlers
 * 
 * 24    29.01.01 17:42 Keskenti
 * 
 * 23    24.01.01 23:21 Wohlers
 * 
 * 22    24.01.01 15:05 Wohlers
 * 
 * 21    12.01.01 16:36 Wohlers
 * 
 * 20    9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 19    8.01.01 14:59 Wohlers
 * 
 * 18    18.12.00 14:37 Wohlers
 * 
 * 17    14.12.00 20:46 Wohlers
 * 
 * 16    12.12.00 13:31 Keskenti
 * 
 * 15    5.12.00 12:34 Keskenti
 * 
 * 14    20.11.00 22:18 Wohlers
 * 
 * 13    20.11.00 22:17 Wohlers
 * 
 * 12    17.11.00 16:53 Wohlers
 * 
 * 11    16.11.00 19:24 Wohlers
 * 
 * 10    2.11.00 21:04 Keskenti
 * 
 * 9     1.11.00 18:19 Wohlers
 * 
 * 8     1.11.00 16:13 Wohlers
 * 
 * 7     27.10.00 15:33 Moos
 * 
 * 6     26.10.00 21:07 Keskenti
 * 
 * 5     26.10.00 17:54 Keskenti
 * 
 * 4     26.10.00 17:03 Keskenti
 * 
 * 3     12.10.00 20:01 Wohlers
 * 
 * 2     12.10.00 19:18 Keskenti
 * 
 * 1     12.10.00 16:50 Keskenti
 * 
  *********************************************************************************/

#include <zCore.h>

#include <zModel.h>
#include <zContainer.h>
#include <zParser.h>
#include <zOption.h>
#include <zEventMan.h>

#include <oNpc.h>
#include <oAniCtrl.h>
#include <oAIHuman.h>
#include <oNpcMessages.h>
#include <oWaynet.h>
#include <oMagic.h>

#pragma warning( disable : 4244 ) // disable VC++ Warning: double to float conversion

	oCNpc::oEBloodMode oCNpc::modeBlood = oCNpc::oEBloodMode_Trails;

// **************************************************
// Instanznamen korrespondierend zur SituationsNummer
// **************************************************
// tmp
zSTRING oCNpc::FightAIInstances[oCNpc::FA_MAX_SITUATIONS];



static zSTRING FightAIInstances[oCNpc::FA_MAX_SITUATIONS] = {
	
	// Nahkampf
	"ENEMY_PREHIT",				// 0
	"ENEMY_STORMPREHIT",		// 1
	"ENEMY_TURNTOHIT_FOCUS",	// 2
	"MY_W_COMBO",				// 3
	"MY_W_RUNTO",				// 4
	"MY_W_STRAFE",				// 5
	"MY_W_FOCUS",				// 6
	"MY_W_NOFOCUS",				// 7
	"MY_G_COMBO",				// 8
	"MY_G_RUNTO",				// 9
	"MY_G_STRAFE",				// 10
	"MY_G_FOCUS",				// 11
	"MY_G_FK_NOFOCUS",			// 12
	"MY_FK_FOCUS",				// 13
	"MY_G_FK_NOFOCUS",			// 14
	// Fernkampf
	"MY_FK_FOCUS_FAR",			// 15
	"MY_FK_NOFOCUS_FAR",		// 16
	"MY_FK_FOCUS_MAG",			// 17
	"MY_FK_NOFOCUS_MAG"		// 18

};

// **************************************************
// Initialisiere FightAI
// **************************************************
static zCArray <oCNpc::oSFightAI*> fightAI; // [Moos] zCArrays von nicht-Pointern sind nicht empfehlenswert.

// Methode
void oCNpc::oSActionBlock::InitBlock(zCParser* par, int sitNr, int faiNr) 
{
	memset	(this,0,sizeof(*this));
	zSTRING	instanceName	=  "FA_" + ::FightAIInstances[sitNr] + zSTRING("_") + zSTRING(faiNr);

	par->CreateInstance	(instanceName,this);
	
	max = -1;
	// Count, how many valid Entrys...
	for (int i=0; i<FA_MAX_ENTRY; i++) {
		if (ownaction[i]==NPC_FIGHTMOVE_NOTINITIALISED) { max = i; break; }
	}
	if (max<0) max = FA_MAX_ENTRY;
}

int oCNpc::oSActionBlock::GetOwnAction(int quality) 
{
	int x = 0;
	if (max>0) x = zRand() % max;
	return ownaction[x];
};

void oCNpc::oSFightAI::Init(zCParser* par, int aiNumber) 
{
	for (int i=0; i<FA_MAX_SITUATIONS; i++) 
	{
		myactions[i].InitBlock(par,i,aiNumber);
	};
}

int oCNpc::oSFightAI::GetOwnAction (int situationNr) 
{
	return (myactions[situationNr].GetOwnAction(100));
};



void oCNpc :: InitFightAI ()
// Static
{
	zerr.Message("U:AI: Reading Script-fight-ai");
	
	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "FightAI");
	if (filename.IsEmpty())
		filename = "Content\\Fight";
	zERR_MESSAGE(4, 0, "N: NPC: Loading file " + filename + ".src or .dat");

	zoptions->ChangeDir(DIR_SCRIPTS);

	zCParser* p = zNEW( zCParser(100) );
	p -> Parse(filename + ".src");
	p -> CreatePCode();

	// Alle Fight-AIs initialisieren
	zCPar_Symbol* sym = p->GetSymbol("MAX_FIGHTAI");
	if (!sym) return;
	int amount;
	sym->GetValue(amount);
	for (int i=0; i<amount; i++) {
		fightAI.Insert	 ( zNEW( TFightAI ));		// ??? [Moos] Hoffentlich ist es so besser :D
		fightAI[i]->Init  ( p, i );
	}
	delete p;
	zerr.Message("U:AI: Reading Script-fight-ai finished");
}

/* ----------------------------------------------------------------------
	
    oCNpc :: ExitFightAI	

	26.08.2000	[Moos]	
                erzeugt, um die fightAIs zu löschen


   ---------------------------------------------------------------------- */
void oCNpc :: ExitFightAI ()
// Static
{
	for (int i=fightAI.GetNum()-1; i>=0; i--) {
        delete fightAI[i];
	}
    fightAI.DeleteList();
}

// **************************************************
// Fight Ranges
// **************************************************

zBOOL oCNpc :: IsNpcBetweenMeAndTarget (zCVob* target)
{
//	return FALSE;
	if (!target)	return FALSE;

	zCWorld* world = GetHomeWorld();
	if (!world)		return FALSE;

	zCArray <zCVob*> ignore;
	ignore.Insert(this);
	if (target) ignore.Insert(target);

	if (world->TraceRayNearestHit(GetPositionWorld(),target->GetPositionWorld() - GetPositionWorld(),&ignore,zTRACERAY_VOB_BBOX | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) {

		zCVob* obstacle = world->traceRayReport.foundVob;
		return (zDYNAMIC_CAST<oCNpc>(obstacle)!=NULL && obstacle->GetBBox3DWorld().GetSphere3D().IsIntersecting(this->GetBBox3DWorld().GetSphere3D()));

	}
	return FALSE;
};

zBOOL oCNpc :: IsInDoubleFightRange (zCVob* vob, zREAL &dist )
{
	if (!vob) return FALSE;

	zVEC3 inters,ray,rayD,res;
	zVEC3 org	= GetPositionWorld();
	rayD = ray	= vob->GetPositionWorld() - org;
	rayD[VY]	= 0;
	dist		= rayD.Length();
	
	// Diff von Gegner - BBox errechnen ( sofern relevant )
	zTBBox3D bboxVob = vob->GetBBox3DWorld();
	if (bboxVob.TraceRay(org-ray*2,ray*4,inters)) {
		// Länge schnappen ( Gegner - BBox )
		res		= (inters - vob->GetPositionWorld());
		res[VY] = 0;
		dist   -= res.Length();
	}

	return (dist <= (GetFightRangeBase() + GetFightRangeDynamic() * 2));
}

zBOOL oCNpc :: IsInFightRange (zCVob* vob, zREAL &dist )
{
	if (!vob)				return FALSE;

	zVEC3 inters,ray,rayD,res;
	zVEC3 org	= GetPositionWorld();
	rayD = ray	= vob->GetPositionWorld() - org;
	rayD[VY]	= 0; 
	dist		= rayD.Length();
	
	// Diff von Gegner - BBox errechnen ( sofern relevant )
	zTBBox3D bboxVob = vob->GetBBox3DWorld();
	oCNpc *bigNpc	 = zDYNAMIC_CAST<oCNpc>(vob);
	
	if (bigNpc && (bigNpc->GetGuild()==NPC_GIL_DRAGON || bigNpc->GetGuild()==NPC_GIL_TROLL))
	{
		bboxVob.Scale(zVEC3(0.5f,1,0.5f));
	}


	if (bboxVob.TraceRay(org-ray*2,ray*4,inters)) {
		// Länge schnappen ( Gegner - BBox )
		res		= (inters - vob->GetPositionWorld());
		res[VY] = 0;
		dist   -= res.Length();
	}

//	dist -= selfDist;

	// Gleiche Hoehe muss auch sein.
	if (!IsSameHeight(vob)) return FALSE;

	return (dist <= GetFightRange());
}

int oCNpc :: GetFightRange ()
{
	return GetFightRangeBase() + GetFightRangeDynamic();
};

void oCNpc :: SetFightRangeBase (int frBase)
{
	fightRangeBase = frBase;
};

int oCNpc :: GetFightRangeBase ()
{
	return fightRangeBase;
};

int oCNpc :: GetFightRangeDynamic ()
{
	oCItem* item = GetWeapon();
	if (item) return item->range;

	return GetFightRangeFist();
};

int oCNpc :: GetFightRangeFist ()
{
	return fightRangeFist;
};

int oCNpc :: GetFightRangeG()
{
	return fightRangeG;
};

void oCNpc :: SetFightRangeFist(int frf)
{
	fightRangeFist = frf;
};

void oCNpc :: SetFightRangeG(int frf)
{
	fightRangeG = frf;
};

// **************************************************
// Fight AI
// **************************************************

int oCNpc :: GetFightActionFromTable(int situationNr)
{
	return fightAI[fighttactic]->GetOwnAction(situationNr);
};

int oCNpc :: GetCurrentFightMove()
{
	// Eigene Aktionen im Kampf
	// NPC_FIGHTMOVE_NONE			-> nichts interessantes -> steht.
	// NPC_FIGHTMOVE_RUN			-> laufen
	// NPC_FIGHTMOVE_RUNBACK		-> zurücklaufen
	// NPC_FIGHTMOVE_TURN			-> drehen
	// NPC_FIGHTMOVE_STRAFE			-> strafen
	// NPC_FIGHTMOVE_JUMPBACK		-> zurückspringen
	// NPC_FIGHTMOVE_WAIT			-> warten (stehen ?)
	// NPC_FIGHTMOVE_STUMBLE		-> am Stumblen
	// NPC_FIGHTMOVE_ONGROUND		-> am Boden
	// NPC_FIGHTMOVE_PREHIT			-> normale Attacke / Vor optimalen Trefferframe
	// NPC_FIGHTMOVE_POSTHIT		-> normale Attacke / nach optimalen Trefferframe bis ComboFenster
	// NPC_FIGHTMOVE_COMBOZONE		-> normale Attacke / im ComboFenster
	// NPC_FIGHTMOVE_TURNTOHIT		-> Drehschlag
	// NPC_FIGHTMOVE_STORMPREHIT	-> Sturmattacke vor optimalen Trefferframe
	// NPC_FIGHTMOVE_PARADE			-> Parade machen
	
	zCModel* model			 = GetModel		();
	oCAniCtrl_Human* anictrl = GetAnictrl	();

	if (!model || !anictrl)							return NPC_FIGHTMOVE_WAIT;

	// NPC_FIGHTMOVE_TURN
	if (model->IsAniActive(anictrl->_t_turnl)  || model->IsAniActive(anictrl->_t_turnr)) return NPC_FIGHTMOVE_TURN;
	// NPC_FIGHTMOVE_RUN
	if (anictrl->IsWalking())						
	{
		if (model->IsAniActive(anictrl->_t_hitfrun))	return NPC_FIGHTMOVE_STORMPREHIT;
		else											return NPC_FIGHTMOVE_RUN;
	}
	// NPC_FIGHTMOVE_WAIT	
	if (anictrl->IsStanding())						return NPC_FIGHTMOVE_WAIT;
	// NPC_FIGHTMOVE_RUNBACK 
	if (model->IsAniActive(anictrl->_s_walkbl) || model->IsAniActive(anictrl->_t_walkbl_2_walk) || model->IsAniActive(anictrl->_t_walkbr_2_walk)) return NPC_FIGHTMOVE_RUNBACK;
	// NPC_FIGHTMOVE_STRAFE
	if (model->IsAniActive(anictrl->_t_strafel) || model->IsAniActive(anictrl->_t_strafer)) return NPC_FIGHTMOVE_STRAFE;
	// NPC_FIGHTMOVE_JUMPBACK
	if (model->IsAniActive(anictrl->_t_jumpb))		return NPC_FIGHTMOVE_JUMPBACK;
	// NPC_FIGHTMOVE_STUMBLE
	if (GetBodyState()==BS_STUMBLE)					return NPC_FIGHTMOVE_STUMBLE;
	// NPC_FIGHTMOVE_ONGROUND
	if (GetBodyState()==BS_LIE)						return NPC_FIGHTMOVE_ONGROUND;
	// NPC_FIGHTMOVE_TURNTOHIT

	// NPC_FIGHTMOVE_PREHIT / STORMPREHIT
	if (!anictrl->IsParadeRunning())
	{
		if (model->IsAniActive(anictrl->_t_hitl) || model->IsAniActive(anictrl->_t_hitr)) {
			// return NPC_FIGHTMOVE_TURNTOHIT;
			if (anictrl->IsInPreHit())	return NPC_FIGHTMOVE_PREHIT;
			else						return NPC_FIGHTMOVE_POSTHIT;
		};

		if (anictrl->IsInPreHit() )						
		{
			return NPC_FIGHTMOVE_PREHIT;
		}
		// NPC_FIGHTMOVE_PREHIT
		if (anictrl->IsInPostHit())						return NPC_FIGHTMOVE_POSTHIT;
		// NPC_FIGHTMOVE_COMBOZONE
		if (anictrl->IsInCombo())						return NPC_FIGHTMOVE_COMBOZONE;
	}
	else					return NPC_FIGHTMOVE_PARADE;
	
	return NPC_FIGHTMOVE_WAIT;
};

zSTRING GetFightMoveStringFromConstant(const int fightID)
{
	switch (fightID)
	{
	case	0		:				return "NOT INITIALISED";	break;
	case	1		:				return "RUN";			break;
	case	2		:				return "RUNBACK";		break;
	case	3		:				return "JUMPBACK";		break;
	case	4		:				return "TURN";			break;
	case	5		:				return "STRAFE";		break;
	
	case	6		:				return "ATTACK";		break;
	case	7		:				return "SIDEATTACK";	break;
	case	8		:				return "FRONTATTACK";	break;
	case	9		:				return "TRIPLEATTACK";	break;
	case	10		:				return "WHIRLATTACK";	break;
	case	11		:				return "MASTERATTACK";	break;

	case	12		:				return "PREHIT";		break;
	case	13		:				return "COMBO";			break;
	case	14		:				return "POSTHIT";		break;
	case	15		:				return "TURNTOHIT";		break;

	case	16		:				return "STORMPREHIT";	break;
	case	17		:				return "PARADE";		break;
	case	18		:				return "STANDUP";		break;

	case	19		:				return "WAIT";			break;
	case	20		:				return "ONGROUND";		break;
	case	21		:				return "STUMBLE";		break;
	default			:				return "UNKNOWN " + zSTRING(fightID);	break;
	};

};

zSTRING GetSituationStringFromConstant(const int fightID)
{
	switch (fightID)
	{
	case 0: return "[ENEMY_PREHIT]";
	case 1: return "[ENEMY_STORMPREHIT]";
	case 2: return "[Enemy_TurnToHit_focus]";
	case 3: return "[My_W_Combo]";
	case 4: return "[My_W_RunTo] ";
	case 5: return "[My_W_Strafe]";
	case 6: return "[My_W_Focus]";
	case 7: return "[My_W_noFocus]";
	case 8: return "[My_G_Combo]";
	case 9: return "[My_G_Runto]";
	case 10: return "[My_G_Strafe]";
	case 11: return "[My_G_Focus]";
	case 12: return "[My_G_FK_noFocus]";
	case 13: return "[My_FK_Focus]";
	case 14: return "[My_G_FK_noFocus] (2)";
	case 15: return "[MY_FK_FOCUS_FAR]";
	case 16: return "[MY_FK_NOFOCUS_FAR]";
	case 17: return "[MY_MAG_NOFOCUS_FAR]";
	case 18: return "[MY_MAG_NOFOCUS_FAR]";
	default: return "[UNKNOWN]" + zSTRING(fightID);
	}
}


int oCNpc :: FindNextFightAction()
// Konzept AI_Kampf 14.03.00
{
	// Der Feind sollte schon vorher per Skriptbefehl ermittelt werden. (Npc_GetNextEnemy())

//return NPC_FIGHTMOVE_PARADE;
	oCNpc* enemy = GetEnemy();
	if (!enemy)	return NPC_FIGHTMOVE_WAIT;;

	// FreeLine Of Sight ! (Ignore Characters) -> RUN wirft automatisch RobustTrace an.
	if (!FreeLineOfSight(enemy))
	{
		// [BENDLIN] 2002-11-02, 1.27
		// HACK: Nailed FAI (turn if no FLOS)
		if (fighttactic == 1)
			return NPC_FIGHTMOVE_TURN;

		return NPC_FIGHTMOVE_RUN;
	}

	// ***********************************************************
	// Fernkampf
	// ***********************************************************
	if (GetWeaponMode()==NPC_WEAPON_MAG)
	{
		if (lastAction==NPC_FIGHTMOVE_WAIT_EXT && fight_waitTime>0) return NPC_FIGHTMOVE_WAIT_EXT;
		// Im Magiekampf sind nur 2 Situationen moeglich.
		// Im Fokus oder nicht im Fokus
		int myMove;

		if (this->IsInFightFocus(enemy)) 
		{						// [ROMAN] Es muss hier getestet werden, ob ich den Gegner im Focus habe, NICHT umgekehrt.
			
			myMove = GetFightActionFromTable(17);				// 15 = "MY_MAG_FOCUS_FAR"	
		
		} else {
		
			myMove = GetFightActionFromTable(18);				// 16 = "MY_MAG_NOFOCUS_FAR"
		}
		
		return myMove;
	}
	else if (GetWeaponMode()>=NPC_WEAPON_BOW) 
	{
	
		if (lastAction==NPC_FIGHTMOVE_WAIT_EXT && fight_waitTime>0) return NPC_FIGHTMOVE_WAIT_EXT;

		// Im Fernkampf sind nur 2 Situationen moeglich.
		// Im Fokus oder nicht im Fokus
		int myMove;

		if (this->IsInFightFocus(enemy)) {						// [ROMAN] Es muss hier getestet werden, ob ich den Gegner im Focus habe, NICHT umgekehrt.
			
			myMove = GetFightActionFromTable(15);				// 15 = "MY_FK_FOCUS_FAR"	
		
		} else {
		
			myMove = GetFightActionFromTable(16);				// 16 = "MY_FK_NOFOCUS_FAR"

		}
		
		return myMove;
	}

	// ***********************************************************
	// Nahkampf
	// ***********************************************************

	int		situation			= 0;
	zREAL	dist				= 0.0f;
	zREAL azi,elev;

	zBOOL	iAmInFightRange		= enemy ? enemy->IsInFightRange		(this,dist)	: FALSE;
	zBOOL	iAmInFightFocus		= enemy ? enemy->IsInFightFocus		(this)		: FALSE;
	int		enemyMove			= enemy ? enemy->GetCurrentFightMove()			: NPC_FIGHTMOVE_WAIT;	
	
	zBOOL	enemyInFightRange	= IsInFightRange					(enemy,dist);
	// NEU: GetFightRangeG() ist nun auf Skriptebene aufgelagert
	zBOOL	enemyInWalkRange	= (dist < (GetFightRangeBase() + GetFightRangeDynamic() + GetFightRangeG()) );
	zBOOL	enemyInFarRange		= (dist < 3000);
	zBOOL	enemyInFightFocus	= IsInFightFocus					(enemy);
	GetAngles(enemy,azi,elev);
	zBOOL	enemyInFightAngles	= ((zAbs(azi)<90) && (zAbs(elev)<50));

	int		curMove				= GetCurrentFightMove				();
	int		myMove				= NPC_FIGHTMOVE_SKIP;		

	// ************************************************************
	// Verteilung der NSCs....
	// ************************************************************
	if (enemyInWalkRange && !enemyInFightRange && (myMove!=NPC_FIGHTMOVE_STRAFE)) {
		
		// Falls NSC zwischen mir und Ziel -> strafen...
		if (IsNpcBetweenMeAndTarget(enemy)) {
			
			// Strafen erforderlich.
			return NPC_FIGHTMOVE_STRAFE;			
		}
	}

	do {

		switch (situation) {

		// Situation 0 [ENEMY_PREHIT]
		case 0	: if (iAmInFightRange && iAmInFightFocus && enemyInFightAngles && (enemyMove==NPC_FIGHTMOVE_PREHIT))  myMove = GetFightActionFromTable(situation);	break;
		// Situation 1 [ENEMY_STORMPREHIT]
		case 1	: if (iAmInFightRange && iAmInFightFocus && enemyInFightAngles && (enemyMove==NPC_FIGHTMOVE_STORMPREHIT)) myMove = GetFightActionFromTable(situation);	break;
		// Situation 2 [Enemy_TurnToHit_focus] 
		case 2	: if (enemyInFightFocus && iAmInFightRange && (enemyMove==NPC_FIGHTMOVE_TURNTOHIT))					myMove = GetFightActionFromTable(situation);	break;
		
		// Situation 3 [My_W_Combo] 
		case 3	: if (enemyInFightRange && enemyInFightFocus && (curMove==NPC_FIGHTMOVE_COMBOZONE))	myMove = GetFightActionFromTable(situation);	break;
		// Situation 4 [My_W_RunTo] 
		case 4	: if (enemyInFightRange && enemyInFightFocus && (curMove==NPC_FIGHTMOVE_RUN))		myMove = GetFightActionFromTable(situation);	break;
		// Situation 5 [My_W_Strafe] 
		case 5	: if (enemyInFightRange && enemyInFightFocus && (curMove==NPC_FIGHTMOVE_STRAFE))	myMove = GetFightActionFromTable(situation);	break;
		// Situation 6 [My_W_Focus]
		case 6	: if (enemyInFightRange && enemyInFightFocus)										myMove = GetFightActionFromTable(situation);	break;
		// Situation 7 [My_W_noFocus]
		case 7	: if (enemyInFightRange)															myMove = GetFightActionFromTable(situation);	break;

		// Situation 8 [My_G_Combo]
		case 8	: if (enemyInWalkRange && enemyInFightFocus && (curMove==NPC_FIGHTMOVE_COMBOZONE))	myMove = GetFightActionFromTable(situation);	break;
		// Situation 9 [My_G_Runto]
		case 9	: if (enemyInWalkRange && enemyInFightFocus && (curMove==NPC_FIGHTMOVE_RUN))			myMove = GetFightActionFromTable(situation);	break;
		// Situation 10 [My_G_Strafe]
		case 10	: if (enemyInWalkRange && enemyInFightFocus && (curMove==NPC_FIGHTMOVE_STRAFE))		myMove = GetFightActionFromTable(situation);	break;
		// Situation 11 [My_G_Focus]
		case 11	: if (enemyInWalkRange && enemyInFightFocus)										myMove = GetFightActionFromTable(situation);	break;
		// Situation 12 [My_G_FK_noFocus]
		case 12	: if (enemyInWalkRange)																myMove = GetFightActionFromTable(situation);	break;
		
		// Situation 13 [My_FK_Focus]
		case 13	: if (enemyInFarRange && enemyInFightFocus)											myMove = GetFightActionFromTable(situation);	break;
		// Situation 14 [My_G_FK_noFocus]
		case 14	: if (enemyInFarRange)																myMove = GetFightActionFromTable(situation);	break;
		}

		situation++;
		// Noch in WarteStellung ?
		// Dann nur auf die ersten 3 Situationen reagieren
		if (situation>=3) {
			
			if (fight_waitForAniEnd!=zMDL_ANI_ID_ILLEGAL) {
				// Diese Animation soll beendet werden, 
				// vorher wird nur auf die ersten 3 Situationen reagiert.
				if (myMove!=NPC_FIGHTMOVE_SKIP) fight_waitForAniEnd = zMDL_ANI_ID_ILLEGAL;
				
				return myMove; 
				// Meist SKIP, wenn keine der ersten 3 Situationen greift.
				// Was heisst, dass ein _Stand ausgeführt wird (schadet nicht).
			} else if (fight_waitTime>0.0f) {
			
				if (myMove==NPC_FIGHTMOVE_SKIP) {
					// Keine Reaktion auf diese Situationen gestartet
					// also weiter warten
					return NPC_FIGHTMOVE_WAIT;
				}
			}
		}

		if (situation > 14)
		{
			situation = 0;
			// [BENDLIN] 2002-11-02, 1.27
			// HACK: Nailed FAI (turn if too far)
			if (fighttactic == 1)
				myMove = NPC_FIGHTMOVE_TURN;
			else
				myMove = NPC_FIGHTMOVE_RUN;
		}

	} while (myMove==NPC_FIGHTMOVE_SKIP);


#ifndef GOLDMASTER
	if (zoptions->Parm("DEBUGFIGHTAI"))
	{
		zSTRING s;

		zERR_MESSAGE(5,0,"C: FIGHT:                                 "); 
		
		s = GetFightMoveStringFromConstant(enemyMove);
		zERR_MESSAGE(5,0,"C: FIGHT: enemyMove:" + s);

		s = GetFightMoveStringFromConstant(curMove);
		zERR_MESSAGE(5,0,"C: FIGHT: curMove:" + s);

		s = GetSituationStringFromConstant(situation-1);
		zERR_MESSAGE(5,0,"C: FIGHT: Fight-Instance selected:" + s);

		s = GetFightMoveStringFromConstant(myMove);
		zERR_MESSAGE(5,0,"C: FIGHT: myMove:" + s);
		zERR_MESSAGE(5,0,"C: FIGHT: tactic:" + zSTRING(fighttactic));

		
	}
#endif

	return myMove;
}

/* ----------------------------------------------------------------------
	
	oCNpc ::ThinkNextFightAction()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */
int oCNpc :: ThinkNextFightAction()
{
	anictrl  = GetAnictrl();

//	anictrl -> zMV_DO_DETECT_WALK_STOP_CHASM = TRUE;
	
	// Beim Schwimmen/Tauchen, mal schnell vergessen
	if (anictrl->GetWaterLevel()>1) {
		oCNpc* enemy = GetEnemy();
		if (enemy) {
			rbt.stand				 = FALSE;
			rbt.standIfTargetReached = TRUE;
			rbt.targetReached		 = FALSE;
			rbt.maxTargetDist		 = 200 * 200;	// 2m
			RbtUpdate	(enemy->GetPositionWorld(),enemy);
			RobustTrace	();
		} else {
			anictrl->_Stand();
		}
		return 0;
	};

	// Warten aktiv ?
	if (fight_waitTime > 0.0f) {
		fight_waitTime -= ztimer.GetFrameTimeF();
		if (fight_waitTime <= 0.0f) fight_waitTime = 0.0f;
	}

	CheckRunningFightAnis();
	
	int myMove = FindNextFightAction();
	lastAction = (TFAction) myMove;
//	zERR_WARNING("U: NPC: myMove = "+zSTRING(myMove));

	// Nur weitermachen, wenn nicht auf das Ende einer Ani gewartet wird.
	if (fight_waitForAniEnd!=zMDL_ANI_ID_ILLEGAL) return 0;

	if (myMove == NPC_FIGHTMOVE_WAIT) {
	
		zREAL dist;
		if (IsInFightRange(enemy,dist)) {
			// Falls zu nah am Gegner jetzt entfernen.
			if (dist<GetFightRange()/4) {
				zVEC3 cdNormal;
				zREAL floorDist = GetFallDownHeight() + 100;
				// Mindestens 1m tief.
				if (!anictrl->DetectChasm(GetPositionWorld(),-GetAtVectorWorld()*100,floorDist,cdNormal)) {						
					anictrl->_Backward();
				}
			} else {
				anictrl->_Stand();
			}
		} else {
			anictrl -> _Stand();		
		}
		anictrl -> StopTurnAnis();
		// Warten und lauern....
		// Reaktionen auf Angriff sind aber noch an !
		// eigene Aktionen werden aber erst gestartet, wenn Wartezeit vorüber
		if (fight_waitTime<=0) fight_waitTime = 200;
		
	} else
	if (myMove == NPC_FIGHTMOVE_WAIT_LONG) 
	{
		zREAL dist;
		if (IsInFightRange(enemy,dist)) 
		{
			// Falls zu nah am Gegner jetzt entfernen.
			if (dist<GetFightRange()/4) {
				zVEC3 cdNormal;
				zREAL floorDist = GetFallDownHeight() + 100;
				// Mindestens 1m tief.
				if (!anictrl->DetectChasm(GetPositionWorld(),-GetAtVectorWorld()*100,floorDist,cdNormal)) {						
					anictrl->_Backward();
				}
			} else {
				anictrl->_Stand();
			}
		} 
		else 
		{
			anictrl -> _Stand();		
		}
		anictrl -> StopTurnAnis();
		// Warten und lauern....
		// Reaktionen auf Angriff sind aber noch an !
		// eigene Aktionen werden aber erst gestartet, wenn Wartezeit vorüber
		if (fight_waitTime<=0) fight_waitTime = 400;
		
	} else
	if (myMove == NPC_FIGHTMOVE_WAIT_EXT) 
	{
		zREAL dist;
		if (IsInFightRange(enemy,dist)) 
		{
			// Falls zu nah am Gegner jetzt entfernen.
			if (dist<GetFightRange()/4) {
				zVEC3 cdNormal;
				zREAL floorDist = GetFallDownHeight() + 100;
				// Mindestens 1m tief.
				if (!anictrl->DetectChasm(GetPositionWorld(),-GetAtVectorWorld()*100,floorDist,cdNormal)) {						
					anictrl->_Backward();
				}
			} else {
				anictrl->_Stand();
			}
		} 
		else 
		{
			anictrl -> _Stand();		
		}
		anictrl -> StopTurnAnis();
		// Warten und lauern....
		// Reaktionen auf Angriff sind aber noch an !
		// eigene Aktionen werden aber erst gestartet, wenn Wartezeit vorüber
		if (fight_waitTime<=0) fight_waitTime = 400;
		
	} else
	if (myMove == NPC_FIGHTMOVE_RUN)			GotoFightPosition();	else
	
	if (myMove == NPC_FIGHTMOVE_RUNBACK) {
		
		zVEC3 cdNormal;
		zREAL floorDist = GetFallDownHeight() + 100;
		// Mindestens 1m tief.
		if (!anictrl->DetectChasm(GetPositionWorld(),-GetAtVectorWorld()*100,floorDist,cdNormal)) {						
			anictrl->_Backward();
		}	
	
	} else if (myMove == NPC_FIGHTMOVE_TURN)			{
		
		zBOOL iAmMoving = GetModel()->IsAniActive(anictrl->_s_walkl);
		// Falls in Kampfreichweite -> stehenbleiben
		if (enemy) {
			// FightRange ist nur fuer den Nahkampf interessant.
			// Im Fernkampfmodus sollte er eh Abstand halten -> wie ? per Skript ?
			if (GetWeaponMode()<NPC_WEAPON_BOW) {
				zREAL dist;
				if (IsInFightRange(enemy,dist)) {
					// Falls zu nah am Gegner jetzt entfernen.
					if (dist<GetFightRange()/4) {
						zVEC3 cdNormal;
						zREAL floorDist = GetFallDownHeight() + 100;
						// Mindestens 1m tief.
						if (!anictrl->DetectChasm(GetPositionWorld(),-GetAtVectorWorld()*100,floorDist,cdNormal)) {						
							anictrl->_Backward();
							iAmMoving = FALSE;
						}
					} else {
						iAmMoving = FALSE;
						anictrl->_Stand(); // [Moos] 27.10. Das war eine klammer weiter unten und hat das Kampfgezumpel verursacht
					}
				}
			}
			// Zum Gegner ausrichten
			//Turn(enemy->GetPositionWorld());
			// [Ulf] : (AtHome2) Nur, wenn Drehung sich auch lohnt, 
			// sonst kommt unschoenes Zucken zustande -> kurzes Starten der Turn - Ani.
			zREAL azi, elev;
			GetAngles(enemy,azi,elev);
			if (abs((int)azi)>3) {
				SetBodyState(BS_STAND);
				GetEM()->OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_TURNTOVOB,enemy),this);
			}

			// RobustTrace weiter anmachen... Sonst haengen NSCs an Abgruende
			if (iAmMoving) {
				GotoFightPosition();
			}

		} else anictrl->_Stand();
	
	} else if (myMove == NPC_FIGHTMOVE_STRAFE) {
		
		zBOOL canStrafeLeft		= CanStrafe(TRUE ,anictrl->_t_strafel);
		zBOOL canStrafeRight	= CanStrafe(FALSE,anictrl->_t_strafer);
		if (canStrafeLeft && canStrafeRight) {
			if (zRand() & 1)	canStrafeRight	= FALSE;	// Nach links strafen
			else				canStrafeLeft	= FALSE;	// Nach rechts strafen
		}

		if (canStrafeRight) {
			
			fight_waitForAniEnd		= anictrl->_t_strafer;
			fight_lastStrafeFrame	= 0.0f;
			GetModel()->StartAni (fight_waitForAniEnd);
		
		} else if (canStrafeLeft) {
		
			fight_waitForAniEnd		= anictrl->_t_strafel;
			fight_lastStrafeFrame	= 0.0f;
			GetModel()->StartAni (fight_waitForAniEnd);
		}
	
	} else if (myMove == NPC_FIGHTMOVE_JUMPBACK)		{

		// **********************
		// Jump zurueck
		// **********************
		zTModelAniID aniID = GetModel()->GetAniIDFromAniName("T_"+anictrl->GetWeaponString(GetWeaponMode())+"PARADEJUMPB");
		if (CanJumpBack(aniID)) {		
			fight_waitForAniEnd = aniID;
			GetModel()->StartAni(fight_waitForAniEnd);
		}

	} else if (myMove == NPC_FIGHTMOVE_STANDUP)	{
	
		anictrl->_Stand();		
	
	} else if (myMove == NPC_FIGHTMOVE_PARADE) {

		GetEM()->OnMessage(zNEW(oCMsgAttack)		(oCMsgAttack :: EV_PARADE		,enemy),this);			
		
	} else {
		// **********************************************
		// FightMove / Attack
		// **********************************************

		zBOOL validAttack = (	(myMove == NPC_FIGHTMOVE_ATTACK)		|| 
								(myMove == NPC_FIGHTMOVE_SIDEATTACK)	|| 
								(myMove == NPC_FIGHTMOVE_FRONTATTACK)	|| 
								(myMove == NPC_FIGHTMOVE_TRIPLEATTACK)	|| 
								(myMove == NPC_FIGHTMOVE_WHIRLATTACK)	|| 
								(myMove == NPC_FIGHTMOVE_MASTERATTACK)	); 

		if (validAttack) {
			
			switch (GetWeaponMode()) {
			
				case NPC_WEAPON_FIST : 
				case NPC_WEAPON_DAG	 : 
				case NPC_WEAPON_1HS	 :
				case NPC_WEAPON_2HS  :	// Nahkampf
										FightAttackMelee(myMove);
										break;
				case NPC_WEAPON_BOW	 : 
				case NPC_WEAPON_CBOW :	// Fernkampf
										FightAttackBow();
										break;
				case NPC_WEAPON_MAG	 :	// Magie
										FightAttackMagic();
										break;
			
				default				 :	// Ouch, this should never happen.
										break;
			}

		} else {

			// Stehen bleiben
			anictrl->_Stand();
			
		}
	}
	return 0;
}

zBOOL oCNpc :: FightAttackMelee(int myMove) 
{
	if (myMove == NPC_FIGHTMOVE_ATTACK) {
		
		if (anictrl->IsWalking() && (anictrl->t_hitfrun)) {
			// aus dem Lauf schlagen ?
			GetEM()->OnMessage(zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKRUN	,anictrl->_t_hitfrun),this);
		} else {
			// Single Attack ( Zufall links oder rechts )
			// Einzelschläge
			//		Left -----------------> z.b. singelattack
			//		Foward			
			if ((zRand()%2)==0)		GetEM()->OnMessage(zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKFORWARD,anictrl->_t_hitf),this);
			else					GetEM()->OnMessage(zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKLEFT	,anictrl->_t_hitl),this);

		}
		return TRUE;

	} else if (myMove == NPC_FIGHTMOVE_SIDEATTACK) {

		// Doublecombos
		// Left --> Right ---------------------> Sideattack
		oCMsgAttack* att = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKLEFT,anictrl->_t_hitl);
		att->combo		 = 1;	// Danach kommt noch eine !
		GetEM()->OnMessage(att,this);	
		att				= zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKRIGHT,anictrl->_t_hitr);
		GetEM()->OnMessage(att,this);	
		return TRUE;
	
	} else if (myMove == NPC_FIGHTMOVE_FRONTATTACK) {
		// Left --> Foward ------------------> Fronattack
		// Foward --> Right------------------>Frontattack_2
		if ((zRand()%2)==0) {
			oCMsgAttack* att = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKLEFT,anictrl->_t_hitl);
			att->combo		 = -1;	// Danach kommt noch eine !
			GetEM()->OnMessage(att,this);	
			att				= zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKFORWARD,anictrl->_t_hitf);
			GetEM()->OnMessage(att,this);	
		} else {
			oCMsgAttack* att = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKFORWARD,anictrl->_t_hitf);
			att->combo		 = -1;	// Danach kommt noch eine !
			GetEM()->OnMessage(att,this);	
			att				= zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKRIGHT,anictrl->_t_hitr);
			GetEM()->OnMessage(att,this);				
		}
		return TRUE;
	
	} else if (myMove == NPC_FIGHTMOVE_TRIPLEATTACK) {
		// Triplecombos
		// Foward --> Right -->Left  ------------------>Tripattack
		// Left --> Right --> Foward ------------------> Tripattack_2
		if ((zRand()%2)==0) {
			oCMsgAttack* att = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKFORWARD,anictrl->_t_hitf);
			att->combo		 = -1;	// Danach kommt noch eine !
			GetEM()->OnMessage(att,this);	

			att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKRIGHT,anictrl->_t_hitr);
			att->combo		 = -1;	// Danach kommt noch eine !
			GetEM()->OnMessage(att,this);	
			
			att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKLEFT,anictrl->_t_hitl);
			GetEM()->OnMessage(att,this);	
		} else {
			oCMsgAttack* att = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKLEFT,anictrl->_t_hitl);
			att->combo		 = -1;	// Danach kommt noch eine !
			GetEM()->OnMessage(att,this);	
			
			att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKRIGHT,anictrl->_t_hitr);
			att->combo		 = -1;	// Danach kommt noch eine !
			GetEM()->OnMessage(att,this);	

			att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKFORWARD,anictrl->_t_hitf);
			GetEM()->OnMessage(att,this);				
		}
		return TRUE;
	
	} else if (myMove == NPC_FIGHTMOVE_WHIRLATTACK) {
		
		// Left --> Right -->Left --> Right ------> Z.B. --Whirlattack
		oCMsgAttack* att = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKLEFT,anictrl->_t_hitl);
		att->combo		 = -1;	// Danach kommt noch eine !
		GetEM()->OnMessage(att,this);	
		
		att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKRIGHT,anictrl->_t_hitr);
		att->combo		 = -1;	// Danach kommt noch eine !
		GetEM()->OnMessage(att,this);	

		att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKLEFT,anictrl->_t_hitl);
		att->combo		 = -1;	// Danach kommt noch eine !
		GetEM()->OnMessage(att,this);				

		att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKRIGHT,anictrl->_t_hitr);
		GetEM()->OnMessage(att,this);				
		return TRUE;
	
	} else if (myMove == NPC_FIGHTMOVE_MASTERATTACK) {

		// Left --> Right --> Foward --> Foward --> Foward --> Foward--------------->Z.B. Masterattack
		oCMsgAttack* att = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKLEFT,anictrl->_t_hitl);
		att->combo		 = -1;	// Danach kommt noch eine !
		GetEM()->OnMessage(att,this);	
		
		att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKRIGHT,anictrl->_t_hitr);
		att->combo		 = -1;	// Danach kommt noch eine !
		GetEM()->OnMessage(att,this);	

		att				 = zNEW(oCMsgAttack)(oCMsgAttack :: EV_ATTACKFORWARD,anictrl->_t_hitf);
		att->combo		 = 4;	// Danach kommen noch vier !
		GetEM()->OnMessage(att,this);				
		return TRUE;
	}
	return FALSE;
}

zBOOL oCNpc :: FightAttackBow()
{
	// ToDo : Munition vorhanden ?
	// ToDo : Andere Waffenauswahl ????

	oCNpc* enemy = GetEnemy();
	if (!enemy) return FALSE;
	if (!this->IsMunitionAvailable(GetWeapon())) return FALSE;

	oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_ATTACKBOW, enemy );
	pMsg->SetHighPriority(TRUE);
	pMsg->startFrame = 3000.0f;
	GetEM()->OnMessage( pMsg , enemy );
	return TRUE;
}

zBOOL oCNpc :: EV_AttackBow(oCMsgAttack* csg)
{
	//
	//	OVERLAY-AIM-MESAGES bereits vorhanden ?
	//
	// Das ist nicht so toll.
	// geht das nicht anders besser ?

	oCMsgAttack*	pMsgAttack	= NULL;
	zBOOL			found		= FALSE;

	for ( int nMessage = 0; nMessage < GetEM()->GetNumMessages(); nMessage++ ) {
		
		pMsgAttack = zDYNAMIC_CAST<oCMsgAttack> (GetEM()->GetEventMessage( nMessage ));
		if ( pMsgAttack && (pMsgAttack->GetSubType() == oCMsgAttack::EV_AIMAT )) {
			found = (pMsgAttack->target == enemy);
			if (!found) pMsgAttack->Delete();
			break;
		}
	}
	
	if (!found) {
		// Neue AIm-Message erzeugen, weil
		// a) noch nicht vorhanden.
		// b) oder Ziel sich geaendert hat.
		// Aim-Message generieren.
		oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_AIMAT, enemy );
		pMsg->SetHighPriority(TRUE);
		GetEM()->OnMessage( pMsg , enemy );
	}
	
	// Falls enemy gelocked, Schuss abfeuern.
	// Winkel ok ?
	zREAL azi,elev;
	GetAngles(enemy,azi,elev);
	if ((abs(int(azi))<5) && FreeLineOfSight(enemy)) {
		// [Ulf] : TurnAnis beenden vorm Schuss
		if (GetAnictrl()) GetAnictrl()->StopTurnAnis();
		// ToDo : NSCs sollten auch mal vorbeischiessen.
		// Zufaelligkeit in Azimuth-Winkel einbauen.
		oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_SHOOTAT, enemy );
		pMsg->SetHighPriority(TRUE);
		GetEM()->OnMessage( pMsg , enemy );
		return TRUE;	
	} else {
		Turn(enemy->GetPositionWorld());
	}
	
	// Timer....
	csg->startFrame -= ztimer.GetFrameTimeF();
	if (csg->startFrame<=0.0f) {
		// ToDo : NSCs sollten auch mal vorbeischiessen.
		// Zufaelligkeit in Azimuth-Winkel einbauen.
		oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_SHOOTAT, NULL );
		pMsg->SetHighPriority(TRUE);
		GetEM()->OnMessage( pMsg , enemy );
		return TRUE;		
	}
	
	return FALSE;
};

zBOOL oCNpc :: FightAttackMagic()
{
	// Kann Message generiert werden ?
	// [BENDLIN] spellMana == 0 führt zu Freeze, wurde persistent gemacht
	// if (spellMana<=0)				return FALSE;
	if (!HasMagic())					return FALSE;
	if (GetAttribute(NPC_ATR_MANA)<=0)	return FALSE;
	// jawoll....
	oCMsgMagic* pMsg = zNEW(oCMsgMagic)( oCMsgMagic::EV_CASTSPELL/*, GetEnemy()*/ );
	pMsg->SetHighPriority(TRUE);
	GetEM()->OnMessage	 (pMsg ,enemy);
	return FALSE;
};

zBOOL oCNpc :: EV_AttackMagic(oCMsgAttack* csg)
{
	return FALSE;
}

zBOOL oCNpc :: EV_CastSpell(oCMsgMagic* csg)
{
	oCAIHuman* ai = zDYNAMIC_CAST<oCAIHuman>(GetAI());
	if (!ai)
		return TRUE;
	oCMag_Book* sbook = GetSpellBook();
	if (!sbook)
		return TRUE;
	oCSpell* spell = sbook->GetSelectedSpell();
	if (!spell)
		return TRUE;

	zBOOL action = FALSE;
	// Weiter investieren....
	if (!csg->IsInUse()) {
		
		if (csg->target)	SetFocusVob(csg->target);
		else				SetFocusVob(GetEnemy());
		
		if (spell->GetInvestedMana() <= spellMana) {
				
			// Weiter investieren -> ACTION - Taste gedrückt simulieren.
			action = ai	-> MagicInvestSpell	( );

		} else {
			// Nicht mehr investieren, Taste loslassen.
			action = FALSE;
			// [EDENFELD] neu 1.21a es scheint so das folgende Zeile nötig ist, da ansonsten manchmal der Spell nicht beendet wird 
			// (hier wird dann sicherheitshalber nochmal der CAST State gesetzt damit unten die Message gelöscht wird)
			ai	-> MagicInvestSpell	( );
		};

		// Spellzustand checken. Falls STOP oder CAST als beenden deklarieren
		int spellState		= spell->GetSpellStatus();

		if ((spellState==SPL_STATUS_CAST) || (spellState==SPL_STATUS_STOP) || (spellState==SPL_STATUS_DONTINVEST)) {
			csg->SetInUse(TRUE);
			action = FALSE;
		};

		ai	-> MagicCheckSpellStates (action);


	} else {
		
		ai	-> MagicCheckSpellStates (FALSE);

	}

	// [BENDLIN] FIXME: wenn der Typ nicht steht gilt die Nachricht als bearbeitet!
	// [EDENFELD] scheint nur für skelett magier nötig
	// nope, auch für Orcshamanen, die sondt doof weiterennen
	// okay okay auch dieser Bug brauch seine Sonderbehandlung

	//	if (!action && csg->IsInUse() && GetAnictrl()->GetWalkMode()==ANI_WALKMODE_RUN)					return TRUE;

	// FIX für Weiterlaufen mit gezogenem Spell
	
	// FIX für Skelettmagier in S_MAGRUN ohne die Message zu beenden
	if ( GetTrueGuild()==NPC_GIL_SKELETON_MAGE ) 
	{
		if (GetModel()->IsAniActive("S_MAGRUN"))  return TRUE;
	}
	else if ( GetAnictrl()->IsRunning() || GetAnictrl()->IsWalking())
	{
		zERR_MESSAGE(5, 0, "N: EV_CastSpell - NPC is running or walking");
		return TRUE;
	}
	
	return (csg->IsInUse() && GetAnictrl()->IsStanding());
};


void oCNpc :: CheckRunningFightAnis()
// Hier wird die Funktionalitaet der Kampf-Move nachgebildet ohne den EM zu benutzen,
// weil sonst waehrend dieser Befehle keine Reaktion auf gefaehrlich SC-Moves
// möglich waere. ( Kein Abbruch von laufenden Befehlen )
// a) Strafen - Ausrichtung zum Gegner
{
	// Warten auf AniEnde aktiv ?
	if (fight_waitForAniEnd!=zMDL_ANI_ID_ILLEGAL) {
		if ((fight_waitForAniEnd == anictrl->_t_strafel) || (fight_waitForAniEnd == anictrl->_t_strafer)) {
			// Strafen, Ausrichtung zum Gegner
			if (enemy) Turn(enemy->GetPositionWorld());
			// Stoppen ?
			if (GetModel()->IsAniActive(fight_waitForAniEnd)) {
				if (fight_lastStrafeFrame > GetModel()->GetProgressPercent(fight_waitForAniEnd)) {
					GetModel()->StartAni(anictrl->_s_walk);
				} else {
					fight_lastStrafeFrame = GetModel()->GetProgressPercent(fight_waitForAniEnd);
				}
			}
		}
		if (!GetModel()->IsAniActive(fight_waitForAniEnd)) {
			// Und wieder freischalten
			fight_waitForAniEnd = zMDL_ANI_ID_ILLEGAL;
		}
	}
}

// ***************************************************************************************
// Kampfbewegung
// ***************************************************************************************

/* ----------------------------------------------------------------------
	
	oCNpc :: GotoFightPosition()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void oCNpc :: GotoFightPosition()
{
	rbt.timer					= 500;
	rbt.targetVob				= enemy;
	if (enemy) rbt.targetPos	= enemy->GetPositionWorld();

	// Falls im Fernkampf, ca 10m Abstand halten
	if (GetWeaponMode()>=NPC_WEAPON_BOW) {
		
		rbt.standIfTargetReached= TRUE;
		rbt.exactPosition		= FALSE;
		rbt.maxTargetDist		= 1000 * 1000;
		RobustTrace();
	
	} else {

		rbt.maxTargetDist		= GetFightRange() * GetFightRange();
		RbtGotoFollowPosition();
	}

 
/*  //
	// Old - but working....
	// 
	rbt.timer					= 500;						// Never run out of time...
	rbt.targetVob				= enemy;
	if (enemy) rbt.targetPos	= enemy->GetPositionWorld();
	
	// Falls im Fernkampf, ca 10m Abstand halten
	if (GetWeaponMode()>=NPC_WEAPON_BOW) {
		rbt.maxTargetDist		= 1000 * 1000;
	} else {
		rbt.maxTargetDist		= GetFightRange() * GetFightRange();
	}
	rbt.standIfTargetReached	= TRUE;
	rbt.exactPosition			= FALSE;
	RobustTrace();*/
};

/* ----------------------------------------------------------------------
	
	oCNpc :: Fighting()

	24.08.2000	[Moos]	

				auf zNEW umgestellt (ja, hatte ich zuerst übersehen...)

   ---------------------------------------------------------------------- */

void oCNpc :: Fighting()
{
	// Patch 1.08  : Falls Pause Mode, sofort zurueck
	if (ztimer.GetFrameTimeF()<=0.0f) return;

	//
	// CODECHANGE [ROMAN]
	//

	anictrl = GetAnictrl();

	// Nicht beim Schwimmen oder Tauchen [Ulf]
	if ( anictrl->GetWaterLevel()<2 ) {
	
		if ( GetWeaponMode() == NPC_WEAPON_NONE )													// keine Waffe
		{
			GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON,anictrl->wmode_last),this);
			return;
		}
		else
		if	(												
			  ( ( GetWeaponMode() == NPC_WEAPON_BOW  ) || ( GetWeaponMode() == NPC_WEAPON_CBOW ) )	// Range Waffe
			 && ( ! ( IsMunitionAvailable( GetWeapon() ) /*HasArrowInInv() || HasArrowInHand()*/ ) )// aber keine Pfeile mehr
			)
		{
			GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),this);
			GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_EQUIPBESTWEAPON),this);
			return;
		}
	}
	
	//
	// CODECHANGE [ROMAN] END
	//

	// Abgruende immer detecten und runterfallen verhindern...
	rbt.useChasmChecks = TRUE;
	ThinkNextFightAction();
}

//
// CODECHANGE [ROMAN]
//

/* ----------------------------------------------------------------------
	
	oCNpc :: GetSpellItem()

	28.09.2000	[Roman Keskenti]	

					Initial implementation
	
	24.01.2001  [Ulf Wohlers]
					
					Anpassung an Inventory Aenderungen

   ---------------------------------------------------------------------- */

oCItem* oCNpc :: GetSpellItem( int nSpell )
{
	oCItem* pItem = NULL;

//	int numItems = inventory2.GetNumItemsInCategory(INV_RUNE);
	int numItems = inventory2.GetNumItemsInCategory();
	for (int i=0; i<numItems; i++) {
//		pItem = inventory2.GetItem(INV_RUNE, i);
		pItem = inventory2.GetItem(i);
		if (pItem && (inventory2.GetCategory(pItem)==INV_RUNE) && (pItem->spell == nSpell) ) {
			pItem->AddRef();		// protect from deletion
			return pItem;
			
		}
	}
	return NULL;

/*	old Implementation 
	zCListSort< oCItem >* pList = this->inventory2.GetFirstNode( INV_RUNE );
	while ( pList ) 
	{
		pItem = pList->GetData();
		if ( pItem )
		{
			if ( pItem->spell == nSpell )
			{
				pItem->AddRef();		// protect from deletion
				return pItem;
			}
		}

		pList = pList->GetNextInList();
	}
*/
}

/* ----------------------------------------------------------------------
	
	oCNpc :: ReadySpell()

	28.09.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */

zBOOL oCNpc :: ReadySpell( int nSpell, int nMana )
{
	//
	//	SPELLBOOK HOLEN
	//
	oCMag_Book* pBook = NULL;
	pBook = this->GetSpellBook();
	if ( ! pBook ) 	
	{
		this->spellMana = 0;

		return FALSE;
	}

	//
	//	HAB ICH SO EINEN SPRUCH ?
	//
	oCItem* pItemSpell = this->GetSpellItem( nSpell );

	if ( !  pItemSpell )	return FALSE;

	//
	//	SPRUCH GEGENSTAND IN DIE HAND NEHMEN
	//
	if ( ! pItemSpell->HasFlag( ITM_FLAG_ACTIVE ) )
	{
		this->EquipItem( pItemSpell );
		pBook->Register( pItemSpell, TRUE );
	}

	//
	//	SPRUCH POSITION IM ARRAY ERMITTELN
	//
	int nIndexSpell;
	oCSpell* pSpell = pBook->GetSpell( pItemSpell, nIndexSpell );
	if ( ! pSpell ) return FALSE;

	//
	//	GEGENSTAND WIRD AB HIER NICHT MEHR BENOETIGT
	//
	pItemSpell->Release();			// remove delete protection 

	//
	//	SPRUCH AKTIVIEREN
	//
	zBOOL bWasInMovement =	this->GetInMovement	();
	if ( bWasInMovement )	this->EndMovement	();

	pBook->SetFrontSpell( nIndexSpell );

	if ( bWasInMovement )	this->BeginMovement	();

	//
	//	MANA INVESTIEREN
	//
	this->spellMana = nMana;

	//
	//	"WAFFE" SPELL "ZIEHEN"
	//
	this->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON,NPC_WEAPON_MAG), this ); 

	//
	//	FETTISCH
	//
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	oCNpc :: UnreadySpell()

	28.09.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */

zBOOL oCNpc :: UnreadySpell( void )
{
	//
	//	"WAFFE" SPELL WEGSTECKEN
	//
	// [Ulf] - 12.01.01 - Haenger beim Waffewegstecken (passierte mal bei Magie) vermeiden.
	this->StandUp();
	this->GetEM()->OnMessage( zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), this ); 

	//
	//	FETTISCH
	//
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	oCNpc :: HasRangedWeaponAndAmmo()

	26.10.2000	[Roman Keskenti]	

					Initial implementation

	24.01.2001  [Ulf Wohlers]
					
					  Anpassung an Inv-Aenderungen

   ---------------------------------------------------------------------- */

zBOOL oCNpc :: HasRangedWeaponAndAmmo( void )
{
	//
	//	INVENTORY CHECKEN
	//
	oCItem* item = NULL;
//	int numItems = inventory2.GetNumItemsInCategory(INV_COMBAT);
	int numItems = inventory2.GetNumItemsInCategory();

//	inventory2.UnpackItemsInCategory(INV_COMBAT);
	inventory2.UnpackItemsInCategory();
	for (int i=0; i<numItems; i++) {
//		item = inventory2.GetItem(INV_COMBAT, i);
		item = inventory2.GetItem(i);
		// Kann Item benutzt werden
		if (CanUse(item) && item->HasFlag(ITM_CAT_FF) && IsMunitionAvailable(item)) {
			return TRUE;
		}
	}

	oCItem* pWeaponInHand = this->GetWeapon();

	//
	//	WAFFENHAND CHECKEN
	//
	if ( pWeaponInHand )
	{
		if ( CanUse( pWeaponInHand ) && pWeaponInHand->HasFlag( ITM_CAT_FF ) && IsMunitionAvailable( pWeaponInHand ))
		{
			return TRUE;
		}
	}

	return FALSE;
}

//
// CODECHANGE [ROMAN] END
//

zBOOL oCNpc :: CanDrawWeapon( )
// Darf NSC Waffe ziehen / wechseln / wegstecken....
// a) im Stehen
// b) im Laufen
// c) bei MobInteraktion
// d) beim Bogenkampf (ACHTUNG, kann Probs. machen, weiter beobachten!!!)
{
	if (GetAnictrl()) {
		return (	GetAnictrl()->IsStanding()	||
					GetAnictrl()->IsWalking()	||
					(GetInteractMob()!=NULL)	||
					(GetWeaponMode()==NPC_WEAPON_BOW) ||
					(GetWeaponMode()==NPC_WEAPON_CBOW)
					);
	}
	return FALSE;
}

//
// Skript - FAI wird nur dann angeschmissen, wenn....
// 

// a) FreeLine Of Sight zum Gegner....
// b) IsInFightRange (?)





