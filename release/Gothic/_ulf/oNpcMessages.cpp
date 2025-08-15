/******************************************************************************** 
 
     $Workfile:: oNpcMessages.cpp     $                $Date:: 26.01.01 18:25   $
     $Revision:: 42                   $             $Modtime:: 26.01.01 18:21   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oNpcMessages.cpp $
 * 
 * 42    26.01.01 18:25 Edenfeld
 * 
 * 41    22.01.01 13:09 Moos
 * 
 * 40    20.01.01 2:35 Edenfeld
 * 
 * 39    18.01.01 0:04 Keskenti
 * 
 * 38    8.01.01 14:55 Wohlers
 * 
 * 37    20.12.00 0:03 Wohlers
 * 
 * 36    14.12.00 11:26 Keskenti
 * 
 * 35    5.12.00 21:57 Speckels
 * 
 * 34    24.11.00 15:41 Wohlers
 * 
 * 33    8.11.00 16:46 Wohlers
 * 
 * 32    3.11.00 16:17 Wohlers
 * 
 * 31    25.10.00 17:45 Keskenti
 * 
 * 30    20.10.00 16:41 Wohlers
 * 
 * 29    18.10.00 17:15 Keskenti
 * 
 * 28    11.10.00 19:53 Keskenti
 * 
 * 27    6.10.00 13:47 Wohlers
 * 
 * 26    6.10.00 13:38 Keskenti
 * 
 * 25    6.10.00 12:44 Keskenti
 * 
 * 24    5.10.00 18:56 Keskenti
 * 
 * 23    5.10.00 17:08 Speckels
 * 
 * 22    3.10.00 18:42 Keskenti
 * 
 * 21    2.10.00 14:29 Keskenti
 * 
 * 20    20.09.00 14:54 Keskenti
 * 
 * 19    12.09.00 12:34 Speckels
 * 
 * 18    12.09.00 12:25 Speckels
 * 
 * 17    7.09.00 21:07 Keskenti
 * 
 * 16    29.08.00 12:48 Keskenti
 * 
 * 15    28.08.00 20:56 Keskenti
 * 
 * 14    24.08.00 12:48 Keskenti
 * 
 * 13    17.08.00 13:52 Keskenti
 * 
 * 12    21.07.00 15:34 Wohlers
 * 
 * 11    20.07.00 20:15 Wohlers
 * 
 * 10    7.07.00 12:42 Wohlers
 * Gothic 0.87
 * 
 * 9     5.07.00 12:21 Wohlers
 * 
 * 8     5.06.00 22:35 Wohlers
 * uSrc 05.06.00
 * 
 * 7     29.05.00 18:35 Wohlers
 * 
 * 6     22.05.00 22:13 Wohlers
 * 
 * 5     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 5     3.05.00 19:18 Wohlers
 * Bugfixes
 * 
 * 4     1.05.00 19:19 Wohlers
 * EV_DropVob Bug gefixed
 * 
 * 3     1.05.00 16:05 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 24    19.04.00 16:44 Wohlers
 * Bug-Fixes
 * 
 * 23    7.04.00 17:57 Wohlers
 * Msg-Metadaten GOTOFP
 * 
 * 22    14.05.00 19:54 Wohlers
 * 0.77d - Fernkampf, GoRoute-MetadatenBug behoben
 * 
 * 21    5.04.00 15:22 Wohlers
 * EV_PLAYANI_NOOVERLAY 
 * 
 * 20    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 18    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 17    22.02.00 20:35 Wohlers
 * 
 * 16    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 14    11.01.00 22:59 Wohlers
 * CS-Fixes / NSC-Equip-Message
 * 
 * 13    10.01.00 16:39 Wohlers
 * Cutscene Fixes
 * 
 * 12    10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 11    22.12.99 17:37 Wohlers
 * Reihenfolge EV_SetWalkMode / EV_WhirlAround korrigiert
 * 
 * 10    20.12.99 17:43 Wohlers
 * 
 * 9     9.12.99 22:31 Wohlers
 * AI_WhirlAround 
 * 
 * 8     7.12.99 22:09 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 7     24.11.99 23:39 Wohlers
 * Release Phoenix 069b
 * Mobsi-Erweiterungen 
 * 
 * 6     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "oGame.h"
#include "oWorld.h"
#include "oNpc.h"
#include "oNpcMessages.h"

#include "zEventMan.h"
#include "zWaynet.h"
#include "zBuffer.h"
#include "zModel.h"
#include "zDisk.h"

#include <zCore.h>

#include <zTypes.h>
#include <zList.h>
#include <zParser.h>
#include <zview.h>
#include <z3D.h>
#include <zVob.h>
#include <zFile3D.h>
#include <zOption.h>
#include <zRenderer.h>
#include <zAlgebra.h>
#include <zModel.h>
#include <zMorphMesh.h>
#include <zParticle.h>
#include <zSound.h>
#include <zPhysics.h>
#include <zSoundMan.h>
#include <zMusic.h>
#include <zBuffer.h>
#include <zArchiver.h>
#include <zAICamera.h>
#include <zCCSPlayer.h>
#include <zInput_Win32.h>
#include <zEventMan.h>
#include <zWayNet.h>
#include <zFonts.h>

#include <oIncDialogs.h>
#include <oInfo.h>
#include <oGame.h>
#include <oInformationManager.h>

zCLASS_DEFINITION	(oCNpcMessage,		zCEventMessage, 0, 0)
zCLASS_DEFINITION	(oCMsgDamage,		oCNpcMessage,	0, 0)
zCLASS_DEFINITION	(oCMsgWeapon,		oCNpcMessage,	0, 0)
zCLASS_DEFINITION	(oCMsgMovement,		oCNpcMessage,	0, 0)
zCLASS_DEFINITION	(oCMsgAttack,		oCNpcMessage,	0, 0)
zCLASS_DEFINITION	(oCMsgUseItem,		oCNpcMessage,	0, 0)
zCLASS_DEFINITION	(oCMsgState,		oCNpcMessage,	0, 0)
zCLASS_DEFINITION	(oCMsgManipulate,	oCNpcMessage,	0, 1)
zCLASS_DEFINITION	(oCMsgConversation,	oCNpcMessage,	0, 0)
zCLASS_DEFINITION	(oCMsgMagic,		oCNpcMessage,	0, 1)
#if defined(SECUROM) && !defined(COMPILING_SPACER)
zCLASS_DEFINITION	(oCMsgRequest,		oCNpcMessage,	0, 0)
#endif

oCNpcMessage :: oCNpcMessage ()
{
	inUse			= FALSE;
	deleted			= FALSE;
	highPriority	= FALSE;
	SetCutsceneMode ( FALSE );
}

oCNpcMessage :: ~oCNpcMessage ()
{
}

// archive-methoden
void oCNpcMessage::Archive(zCArchiver& arc)
{
	zCEventMessage::Archive(arc);

	if (arc.InSaveGame()) {
		arc.WriteBool("highPriority",	highPriority);
		arc.WriteBool("inUse",			inUse);
		arc.WriteBool("deleted",		deleted);
	}
}

void oCNpcMessage::Unarchive(zCArchiver& arc)
{
	zCEventMessage::Unarchive(arc);

	if (arc.InSaveGame()) {
        zBOOL tmp;
//		arc.ReadBool("highPriority",	highPriority);
//		arc.ReadBool("inUse",			inUse);
//		arc.ReadBool("deleted",			deleted);
		arc.ReadBool("highPriority",	tmp);  highPriority = tmp;
		arc.ReadBool("inUse",			tmp);  inUse        = tmp;
		arc.ReadBool("deleted",			tmp);  deleted      = tmp;
	}
}

// ***************************************************************************************
// Damage
// ***************************************************************************************
oCMsgDamage :: oCMsgDamage ()
{
}

oCMsgDamage :: oCMsgDamage ( TDamageSubType enuSubType )
{
	this->subType = enuSubType;
}

oCMsgDamage :: oCMsgDamage ( TDamageSubType enuSubType, const oCNpc::oSDamageDescriptor& desc )
{
	this->subType	 = enuSubType;
	this->descDamage = desc		 ;
}


// [EDENFELD] Destruktor für oCMsgDamage hinzugefügt, damit auf Npcs abgespielte oCVisualFX Effekte 
// bei Levelchange / Loadgame korrekt dereferenziert werden
oCMsgDamage :: ~oCMsgDamage()
{	
	descDamage.Release();
};

int oCMsgDamage :: MD_GetNumOfSubTypes()
{ 
	return (int) EV_DAMAGE_MAX; 
}

zSTRING oCMsgDamage :: MD_GetSubTypeString( int nSubType )
{
	zSTRING result;
	switch ( nSubType ) 
	{
		case EV_DAMAGE_ONCE		: result = "EV_DAMAGE_ONCE"		;	break;
		case EV_DAMAGE_PER_FRAME: result = "EV_DAMAGE_PER_FRAME";	break;
	}
	return result;
}

void oCMsgDamage :: Pack( zCBuffer& buffer, zCEventManager* evManContext )
{	
	oCNpcMessage::Pack( buffer, evManContext );
}

void oCMsgDamage :: Unpack( zCBuffer& buffer, zCEventManager* evManContext )
{
	oCNpcMessage::Pack (buffer, evManContext);
}

void oCMsgDamage::Archive( zCArchiver& arc )
{
	oCNpcMessage::Archive( arc );

	arc.WriteRaw( "damage_descriptor", &(this->descDamage), sizeof( this->descDamage ) );
}

void oCMsgDamage::Unarchive( zCArchiver& arc )
{
	oCNpcMessage::Unarchive(arc);
	
	arc.ReadRaw( "damage_descriptor", &(this->descDamage), sizeof( this->descDamage ) );
}

// ***************************************************************************************
// Movement
// ***************************************************************************************

oCMsgMovement :: oCMsgMovement ()
{
	Init();
}

oCMsgMovement :: oCMsgMovement (TMovementSubType subType, const zSTRING&	target)
{
	Init();
	this->subType	= subType;
	targetName		= target;
}

oCMsgMovement :: oCMsgMovement (TMovementSubType subType, zCVob*		target)
{	
	Init();
	this->subType	= subType;
	targetVob		= target;
	if (target) targetPos = target->GetPositionWorld();
}

oCMsgMovement :: oCMsgMovement (TMovementSubType subType, const zVEC3&		target)
{
	Init();
	this->subType	= subType;
	targetPos		= target;
}

oCMsgMovement :: oCMsgMovement (TMovementSubType subType, zREAL		angle )
{
	Init();
	this->subType	= subType;
	this->angle		= angle;
}

oCMsgMovement :: oCMsgMovement (TMovementSubType subType, int target )
{
	Init();
	this->subType	= subType;
	this->angle		= 0.0f;
	targetMode		= target;
};

oCMsgMovement :: ~oCMsgMovement()
{
	delete (route);	route = NULL;
	targetVob		= NULL;
}

void oCMsgMovement :: Init()
{
	route			= NULL;
	targetVob		= NULL;
	targetPos		= zVEC3(0,0,0);
	angle			= 0.0f;
	targetMode		= 0;
	ani				= zMDL_ANI_ID_ILLEGAL;
}

void oCMsgMovement::Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);

	int st = GetSubType();

	// ist targetName und targetVobName vielleicht identisch???
	if ((st==EV_GOTOFP) || (st==EV_GOROUTE) || (st==EV_BEAMTO))							
		arc.WriteString	("targetName"	,targetName);
	if ((st==EV_GOTOVOB) || (st==EV_TURNTOVOB) || (st==EV_TURNAWAY) || (st==EV_WHIRLAROUND)) {
		if (!arc.InProperties()) arc.WriteObject	("targetVob"	,targetVob);
		arc.WriteString	("targetVobName",targetVobName);
	};
	if ((st==EV_GOTOPOS) || (st==EV_TURNTOPOS) || (st==EV_JUMP))	
		arc.WriteVec3	("targetPos"	,targetPos);
	if (st==EV_TURN)
		arc.WriteFloat	("angle"		,angle);
	if (st==EV_SETWALKMODE) 
		arc.WriteInt	("targetMode"	,targetMode);

}

void oCMsgMovement::Unarchive(zCArchiver& arc)
{
	route		= NULL;		// ??
	targetVob	= NULL;		// ??

	oCNpcMessage::Unarchive(arc);

	int st = GetSubType();

	if ((st==EV_GOTOFP) || (st==EV_GOROUTE) || (st==EV_BEAMTO))							
		arc.ReadString	("targetName"	,targetName);
	
	if ((st==EV_GOTOVOB) || (st==EV_TURNTOVOB) || (st==EV_TURNAWAY) || (st==EV_WHIRLAROUND)) {
		if (!arc.InProperties()) targetVob = static_cast<zCVob*>(arc.ReadObject("targetVob"));
		arc.ReadString	("targetVobName",targetVobName);
	}
	if ((st==EV_GOTOPOS) || (st==EV_TURNTOPOS) || (st==EV_JUMP))	
		arc.ReadVec3	("targetPos"	,targetPos);
	if (st==EV_TURN)
		arc.ReadFloat	("angle"		,angle);
	if (st==EV_SETWALKMODE) 
		arc.ReadInt		("targetMode"	,targetMode);

}

int oCMsgMovement :: MD_GetNumOfSubTypes()
{ return (int)EV_MOVE_MAX; }

zSTRING oCMsgMovement :: MD_GetSubTypeString(int n)
{
	zSTRING result;
	switch (n) {
		case EV_ROBUSTTRACE	: result = "EV_ROBUSTTRACE";	break;
		case EV_GOTOPOS		: result = "EV_GOTOPOS";		break;
		case EV_GOTOVOB		: result = "EV_GOTOVOB";		break;
		case EV_GOROUTE		: result = "EV_GOROUTE";		break;
		case EV_TURN		: result = "EV_TURN";			break;
		case EV_TURNTOPOS	: result = "EV_TURNTOPOS";		break;
		case EV_TURNTOVOB	: result = "EV_TURNTOVOB";		break;
		case EV_TURNAWAY	: result = "EV_TURNAWAY";		break;
		case EV_JUMP		: result = "EV_JUMP";			break;
		case EV_WHIRLAROUND	: result = "EV_WHIRLAROUND";	break;
		case EV_SETWALKMODE	: result = "EV_SETWALKMODE";	break;
		case EV_STANDUP		: result = "EV_STANDUP";		break;
		case EV_CANSEENPC	: result = "EV_CANSEENPC";		break;
		case EV_STRAFE		: result = "EV_STRAFE";			break;
		case EV_GOTOFP		: result = "EV_GOTOFP";			break;
		case EV_DODGE		: result = "EV_DODGE";			break;
		case EV_BEAMTO		: result = "EV_BEAMTO";			break;	
		case EV_ALIGNTOFP	: result = "EV_ALIGNTOFP";		break;
	}
	return result;
}

// - Parameter
zSTRING oCMsgMovement :: MD_GetVobRefName()
{ 
	if ((GetSubType()==EV_GOROUTE) || (GetSubType()==EV_GOTOFP) || (GetSubType()==EV_BEAMTO))	return zSTR_EMPTY;
	return targetVobName; 
}

void oCMsgMovement :: MD_SetVobRefName(const zSTRING & name)
{ 
	targetVobName = name; 
}

void oCMsgMovement :: MD_SetVobParam(zCVob* vob) 
{ 
	targetVob = vob; 
}

void oCMsgMovement :: Delete()				
{ 
	oCNpcMessage::Delete();
};

//	- TimeBehavior
zCEventMessage::zTTimeBehavior oCMsgMovement :: MD_GetTimeBehavior()
{ 
	switch (subType) {
	case EV_ROBUSTTRACE	:
	case EV_TURN		:
	case EV_TURNTOPOS	:
	case EV_TURNTOVOB	:
	case EV_TURNAWAY	:	
	case EV_SETWALKMODE	:	
	case EV_BEAMTO		:	return zCEventMessage::TBZero;
	
	case EV_GOTOPOS		:
	case EV_GOTOVOB		:
	case EV_GOROUTE		:	
	case EV_GOTOFP		:
	case EV_JUMP		:
	case EV_WHIRLAROUND	:	
	case EV_STANDUP		:	return zCEventMessage::TBUnknown;
	
	default				:	return zCEventMessage::TBZero;
	}
}

zREAL oCMsgMovement :: MD_GetMinTime()
{ return 3.0; }

// ***************************************************************************************
// Weapon 
// ***************************************************************************************

oCMsgWeapon :: oCMsgWeapon ()
{
	targetMode		= 0;
	ani				= zMDL_ANI_ID_ILLEGAL;
	duringRun		= FALSE;
	initDone		= FALSE;
	firstTime		= TRUE;
	useFist			= FALSE;
	showMagicCircle	= TRUE;
}

oCMsgWeapon :: oCMsgWeapon (TWeaponSubType subType, int tgtMode, zBOOL _useFist)
{
	ani				= zMDL_ANI_ID_ILLEGAL;
	duringRun		= FALSE;
	initDone		= FALSE;
	firstTime		= TRUE;
	useFist			= _useFist;
	this->subType	= subType;
	targetMode		= tgtMode;
	showMagicCircle	= TRUE;
}

void oCMsgWeapon::Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);

	arc.WriteInt	("targetMode"	,targetMode);

	if (!arc.InProperties()) {
		arc.WriteBool	("duringRun"	,duringRun);
		arc.WriteBool	("initDone"		,initDone);
		arc.WriteBool	("firstTime"	,firstTime);
	//  FIXME : Wie soll die ani gespeichert werden ?
	//	arc.WriteString ("aniName"		,aniName);
	};
}

void oCMsgWeapon::Unarchive(zCArchiver& arc)
{
	oCNpcMessage::Unarchive(arc);
	
	arc.ReadInt		("targetMode"	,targetMode);

	if (!arc.InProperties()) {
        int tmp;
//		arc.ReadBool	("duringRun"	,duringRun);
//		arc.ReadBool	("initDone"		,initDone);
//		arc.ReadBool	("firstTime"	,firstTime);
		arc.ReadBool	("duringRun"	,tmp);   duringRun = tmp;
		arc.ReadBool	("initDone"		,tmp);   initDone  = tmp;
		arc.ReadBool	("firstTime"	,tmp);   firstTime = tmp;
	}
}

int oCMsgWeapon :: MD_GetNumOfSubTypes()
{ return (int)EV_WEAPON_MAX; }

zSTRING oCMsgWeapon :: MD_GetSubTypeString(int n)
{
	zSTRING result;
	switch (n) {
	case EV_DRAWWEAPON			: result = "EV_DRAWWEAPON";			break;
	case EV_DRAWWEAPON1			: result = "EV_DRAWWEAPON1";		break;
	case EV_DRAWWEAPON2			: result = "EV_DRAWWEAPON2";		break;
	case EV_REMOVEWEAPON		: result = "EV_REMOVEWEAPON";		break;
	case EV_REMOVEWEAPON1		: result = "EV_REMOVEWEAPON1";		break;
	case EV_REMOVEWEAPON2		: result = "EV_REMOVEWEAPON2";		break;
	case EV_CHOOSEWEAPON		: result = "EV_CHOOSEWEAPON";		break;
	case EV_FORCEREMOVEWEAPON	: result = "EV_FORCEREMOVEWEAPON";	break;
	case EV_ATTACK				: result = "EV_ATTACK";				break;
	case EV_EQUIPBESTWEAPON		: result = "EV_EQUIPBESTWEAPON";	break;
	case EV_EQUIPBESTARMOR		: result = "EV_EQUIPBESTARMOR";		break;
	case EV_UNEQUIPWEAPONS		: result = "EV_UNEQUIPWEAPONS";		break;
	case EV_UNEQUIPARMOR		: result = "EV_UNEQUIPARMOR";		break;
	case EV_EQUIPARMOR			: result = "EV_EQUIPARMOR";			break;
	default: result = zSTRING("");
	}
	return result;
}

	//			- TimeBehavior
zCEventMessage::zTTimeBehavior oCMsgWeapon :: MD_GetTimeBehavior()
{ return zCEventMessage::TBZero; }
zREAL oCMsgWeapon :: MD_GetMinTime()
{ return 0.0F; }

// ***************************************************************************************
// Attacks
// ***************************************************************************************

oCMsgAttack :: oCMsgAttack()
{
	combo			= 0;
	target			= NULL;
	hitAni			= zMDL_ANI_ID_ILLEGAL;
	enableNextHit	= FALSE;
	reachedTarget 	= FALSE;
	startFrame		= 0.0f;
}

oCMsgAttack :: oCMsgAttack (TAttackSubType subType, zTModelAniID ani, int combo)
{
	reachedTarget 	= FALSE;
	enableNextHit	= FALSE;
	startFrame		= 0.0f;
	target			= NULL;

	this->subType	= subType;
	this->combo		= combo;
	hitAni			= ani;
}

oCMsgAttack	:: oCMsgAttack	(TAttackSubType	subType, zCVob* target, zREAL startFrame)
{
	combo			= 0;
	hitAni			= zMDL_ANI_ID_ILLEGAL;
	enableNextHit	= FALSE;
	reachedTarget 	= FALSE;

	this->subType	= subType;
	this->target	= target;
	this->startFrame= startFrame;
}

void oCMsgAttack::Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);

	arc.WriteInt		("combo"		,combo);
	if (!arc.InProperties()) {
		arc.WriteBool	("enableNextHit",enableNextHit);
	}
}

void oCMsgAttack::Unarchive(zCArchiver& arc)
{
	oCNpcMessage::Unarchive(arc);
	
	arc.ReadInt			("combo"		,combo);
	if (!arc.InProperties()) {
        int tmp;
//		arc.ReadBool	("enableNextHit",enableNextHit);
		arc.ReadBool	("enableNextHit",tmp); enableNextHit = tmp;
	}
}

// Pack / Unpack
void oCMsgAttack	:: Pack(zCBuffer& buffer, zCEventManager* evManContext)
{
	oCNpcMessage::Pack (buffer, evManContext);
	
	buffer.Write	(&combo, sizeof(combo));

    zBOOL tmp;
    tmp = enableNextHit;
	buffer.Write	(&tmp, sizeof(tmp));
//	buffer.Write	(&enableNextHit, sizeof(enableNextHit));

	buffer.Write	(&startFrame, sizeof(startFrame));
	
    // GetAniName From AniID	
	zSTRING aniName;
	oCNpc* npc = dynamic_cast<oCNpc*>(evManContext->GetHostVob());
	if (npc) {
		zCModel* model = npc->GetModel();
		if (model) {
			zCModelAni* ani		= model->GetAniFromAniID(hitAni);
			if (ani) aniName	= ani->GetAniName();
		}
	}
	buffer.WriteString (aniName);
};

void oCMsgAttack	:: Unpack(zCBuffer& buffer, zCEventManager* evManContext)
{
	oCNpcMessage::Unpack (buffer, evManContext);
	
	zSTRING aniName;
	buffer.Read (&combo, sizeof(combo));

    int tmp;

	buffer.Read (&tmp, sizeof(tmp));   enableNextHit = tmp;

//  buffer.Read (&enableNextHit, sizeof(enableNextHit));

	buffer.Read (&startFrame, sizeof(startFrame));	

	aniName = buffer.ReadString();

	oCNpc* npc = dynamic_cast<oCNpc*>(evManContext->GetHostVob());
	if (npc) hitAni = npc->GetModel()->GetAniIDFromAniName(aniName);
};

int oCMsgAttack :: MD_GetNumOfSubTypes()
{ return (int)EV_ATTACK_MAX; }
zSTRING oCMsgAttack :: MD_GetSubTypeString(int n)
{
	zSTRING result;
	switch (n) {
		case EV_ATTACKFORWARD	: result = "EV_ATTACKFORWARD";break;
		case EV_ATTACKLEFT		: result = "EV_ATTACKLEFT";break;
		case EV_ATTACKRIGHT		: result = "EV_ATTACKRIGHT";break;
		case EV_ATTACKRUN		: result = "EV_ATTACKRUN";break;
		case EV_ATTACKFINISH	: result = "EV_ATTACKFINISH";break;
		case EV_PARADE			: result = "EV_PARADE";break;
		case EV_AIMAT			: result = "EV_AIMAT";break;
		case EV_SHOOTAT			: result = "EV_SHOOTAT";break;
		case EV_STOPAIM			: result = "EV_STOPAIM";break;
		case EV_DEFEND			: result = "EV_DEFEND";break;
		default:				  result = zSTRING("");
	}
	return result;
}

// ***************************************************************************************
// UseItem
// ***************************************************************************************

oCMsgUseItem :: oCMsgUseItem ()
{
	vob		= NULL;
	ani		= zMDL_ANI_ID_ILLEGAL;
	state	= 0;
}

oCMsgUseItem :: oCMsgUseItem (TUseItemSubType subType, zCVob* vob)
{
	ani				= NULL;
	state			= 0;
	this->subType	= subType;
	this->vob		= vob;
}

oCMsgUseItem :: ~oCMsgUseItem ()
{
	vob = NULL;
};

	// Pack / Unpack
void oCMsgUseItem :: Pack	(zCBuffer& buffer, zCEventManager* evManContext)
{	
	oCNpcMessage::Pack (buffer, evManContext);

	zTVobID vobID	= 0;
	if (vob) vobID = vob->GetVobID();
	buffer.Write (&vobID, sizeof(vobID));
	buffer.Write (&state, sizeof(state));
};

void oCMsgUseItem :: Unpack	(zCBuffer& buffer, zCEventManager* evManContext)
{
	oCNpcMessage::Pack (buffer, evManContext);

	zTVobID vobID = 0;
	buffer.Read	(&vobID, sizeof(vobID));
	vob = (oCItem*)ogame->GetWorld()->SearchVobByID(vobID);
	buffer.Read (&state, sizeof(state));
};


void oCMsgUseItem::Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);

	arc.WriteObject("item",vob);
}

void oCMsgUseItem::Unarchive(zCArchiver& arc)
{
	oCNpcMessage::Unarchive(arc);
	
	vob = static_cast<zCVob*>(arc.ReadObject("item"));
}

// ***************************************************************************************
// States
// ***************************************************************************************

oCMsgState :: oCMsgState()
{
	function	= -1;
	minutes		= 0;
	instance	= -1;
	timer		= 0.0f;
	endOldState	= FALSE;
	other		= NULL;
	victim		= NULL;
	inRoutine	= FALSE;
}

oCMsgState :: oCMsgState (TStateSubType subType, zREAL time)
{
	function		= -1;
	minutes			= 0;
	instance		= -1;
	this->subType	= subType;
	timer			= time;
	endOldState		= FALSE;
	other			= NULL;
	victim			= NULL;
	inRoutine		= FALSE;
}

oCMsgState :: oCMsgState (TStateSubType subType, int func)
{
	minutes			= 0;
	instance		= -1;
	timer			= 0.0f;
	this->subType	= subType;
	function		= func;
	endOldState		= FALSE;
	other			= NULL;
	victim			= NULL;
	inRoutine		= FALSE;
}

oCMsgState :: oCMsgState (TStateSubType subType, int func, zBOOL param, const zSTRING& wp)
{
	this->subType	= subType;
	function		= func;
	endOldState		= param;
	this -> wp		= wp;
	instance		= -1;
	other			= NULL;
	victim			= NULL;
	inRoutine		= FALSE;
}

oCMsgState :: ~oCMsgState ()
{
	other			= NULL;
	victim			= NULL;
}

void oCMsgState :: Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);

	if ( (GetSubType()==EV_WAIT) || (GetSubType()==EV_APPLYTIMEDOVERLAY) )	arc.WriteFloat("time", timer);
	if (GetSubType()==EV_SETTIME)	{
		arc.WriteInt("hour",function);
		arc.WriteInt("minute",minutes);
	};
}

void oCMsgState :: Unarchive(zCArchiver& arc)
{
	oCNpcMessage::Unarchive(arc);
	
	if ( (GetSubType()==EV_WAIT) || (GetSubType()==EV_APPLYTIMEDOVERLAY) )	arc.ReadFloat("time", timer);
	if (GetSubType()==EV_SETTIME)	{
		arc.ReadInt("hour",function);
		arc.ReadInt("minute",minutes);
	};
}

int oCMsgState :: MD_GetNumOfSubTypes()
{ return (int)EV_STATE_MAX; }

zSTRING oCMsgState :: MD_GetSubTypeString(int n)
{
	zSTRING result;
	switch (n) {
		case EV_STARTSTATE			:	result = "EV_STARTSTATE";			break;
		case EV_WAIT				:	result = "EV_WAIT";					break;
		case EV_SETNPCSTOSTATE		:	result = "EV_SETNPCSTOSTATE";		break;
		case EV_SETTIME				:	result = "EV_SETTIME";				break;
		case EV_APPLYTIMEDOVERLAY	:	result = "EV_APPLYTIMEDOVERLAY";	break;
		default						:	result = "";	break;
	}
	return result;
}

zCEventMessage::zTTimeBehavior oCMsgState :: MD_GetTimeBehavior()
{ return zCEventMessage::TBFix; }

zREAL oCMsgState:: MD_GetMinTime()
{ 
	switch (GetSubType()) {
		case EV_STARTSTATE		: return 0.0f;
		case EV_SETNPCSTOSTATE	: return 0.0f;
		case EV_WAIT			: return timer/1000.0f;
		case EV_SETTIME			: return 0.0f;
		default					: return 3.0F; 
	}
}

// ***************************************************************************************
// World - Manipulations
// ***************************************************************************************

oCMsgManipulate	:: oCMsgManipulate ()
{
	subType			= 0;
	targetVob		= NULL;
	flag			= FALSE;
	aniCombY		= 0.5f;
	aniID			= zMDL_ANI_ID_ILLEGAL;
}

oCMsgManipulate :: oCMsgManipulate (TManipulateSubType subType)
{
	this->subType	= subType;
	this->targetVob	= NULL;
//	npcSlot			= NPC_NODE_NONE;
	flag			= FALSE;
	aniCombY		= 0.5f;
	aniID			= zMDL_ANI_ID_ILLEGAL;
}

oCMsgManipulate :: oCMsgManipulate (TManipulateSubType subType, zCVob* vob)
{
	this->subType	= subType;
	this->targetVob	= vob;
//	npcSlot			= NPC_NODE_NONE;
	flag			= FALSE;
	aniCombY		= 0.5f;
	aniID			= zMDL_ANI_ID_ILLEGAL;
}

oCMsgManipulate :: oCMsgManipulate (TManipulateSubType subType, int slot)
{
	this->subType	= subType;
	this->targetVob	= NULL;
	targetState		= slot;
	flag			= FALSE;
	aniCombY		= 0.5f;
}

oCMsgManipulate :: oCMsgManipulate (TManipulateSubType subType, const zSTRING& mobScheme, int target)
{
	this->subType	= subType;
	this->targetVob	= NULL;
	targetState		= target;
	name			= mobScheme;
	flag			= FALSE;
	aniCombY		= 0.5f;
}

oCMsgManipulate :: oCMsgManipulate (TManipulateSubType subType, zCVob* vob, int target)
{
	this->subType	= subType;
	this->targetVob	= vob;
	targetState		= target;
	flag			= FALSE;
	aniCombY		= 0.5f;
}

oCMsgManipulate	:: oCMsgManipulate (TManipulateSubType subType, const zSTRING& itemName, const zSTRING& slotName)
{
	this->subType	= subType;
	name			= itemName;
	slot			= slotName;
	targetVob		= NULL;
	targetState		= 0;
	flag			= FALSE;
	aniCombY		= 0.5f;
}

oCMsgManipulate	:: ~oCMsgManipulate ()
{
	targetVob		= NULL;
}

void oCMsgManipulate::Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);

	int st = GetSubType();

	if (st==EV_TAKEVOB) {
		arc.WriteString	("targetVobName",targetVobName);
	}
	if ((st==EV_DROPVOB) || (st==EV_USEMOB)	|| (st==EV_DROPMOB) || (st==EV_TAKEMOB) || (st==EV_USEITEM) || (st==EV_CALLSCRIPT) || (st==EV_EQUIPITEM) || (st==EV_USEITEMTOSTATE) ) {
		arc.WriteString ("schemeName"	,name);
	}
	if ((st==EV_USEMOB) || (st==EV_USEITEMTOSTATE)) {
		arc.WriteInt	("targetState"	,targetState);
	}
}

void oCMsgManipulate::Unarchive(zCArchiver& arc)
{
	oCNpcMessage::Unarchive(arc);
	
	int st = GetSubType();

	if ((st==EV_TAKEVOB)) {
		arc.ReadString	("targetVobName",targetVobName);
	}
	if ((st==EV_DROPVOB) || (st==EV_USEMOB)	|| (st==EV_DROPMOB) || (st==EV_TAKEMOB) || (st==EV_USEITEM)	|| (st==EV_CALLSCRIPT) || (st==EV_EQUIPITEM) || (st==EV_USEITEMTOSTATE) ) {
		arc.ReadString	("schemeName"	,name);
	}
	if ((st==EV_USEMOB) || (st==EV_USEITEMTOSTATE))	{
		arc.ReadInt		("targetState"	,targetState);
	}
}

void oCMsgManipulate::Pack	(zCBuffer& buffer, zCEventManager* evManContext)
{
	zCEventMessage::Pack (buffer, evManContext);

	buffer.Write (&subType,		sizeof(subType));
	buffer.WriteString(name);
	buffer.WriteString(slot);

	zTVobID vobID = 0;
	if (targetVob) vobID = targetVob->GetVobID();
	buffer.Write(&vobID,sizeof(vobID));

	buffer.Write(&targetState,sizeof(targetState));

	buffer.WriteBool(flag);
};

void oCMsgManipulate::Unpack(zCBuffer& buffer, zCEventManager* evManContext)
{
	zCEventMessage::Unpack (buffer, evManContext);

	buffer.Read (&subType,		sizeof(subType));
	name = buffer.ReadString();
	slot = buffer.ReadString();

	targetVob = 0;
	zTVobID vobID;
	buffer.Read(&vobID,sizeof(vobID));
	if (vobID>0) targetVob = ogame->GetWorld()->SearchVobByID(vobID);;
	
	buffer.Read(&targetState,sizeof(targetState));

	flag = buffer.ReadBool();
};

int oCMsgManipulate:: MD_GetNumOfSubTypes()
{ return (int)EV_MANIP_MAX; }

zSTRING oCMsgManipulate :: MD_GetSubTypeString(int n)
{
	zSTRING result;
	switch (n) {
	case EV_TAKEVOB				: result = "EV_TAKEVOB"				;	break;
	case EV_DROPVOB				: result = "EV_DROPVOB"				;	break;
	case EV_THROWVOB			: result = "EV_THROWVOB"			;	break;
	case EV_EXCHANGE			: result = "EV_EXCHANGE"			;	break;
	case EV_USEMOB				: result = "EV_USEMOB"				;	break;
	case EV_TAKEMOB				: result = "EV_TAKEMOB"				;	break;
	case EV_DROPMOB				: result = "EV_DROPMOB"				;	break;
	case EV_USEITEM				: result = "EV_USEITEM"				;	break;
	case EV_USEITEMTOSTATE		: result = "EV_USEITEMTOSTATE"		;	break;
	case EV_INSERTINTERACTITEM	: result = "EV_INSERTINTERACTITEM"	;	break;
	case EV_REMOVEINTERACTITEM	: result = "EV_REMOVEINTERACTITEM"	;	break;
	case EV_CREATEINTERACTITEM	: result = "EV_CREATEINTERACTITEM"	;	break;
	case EV_DESTROYINTERACTITEM	: result = "EV_DESTROYINTERACTITEM"	;	break;
	case EV_PLACEINTERACTITEM	: result = "EV_PLACEINTERACTITEM"	;	break;
	case EV_EXCHANGEINTERACTITEM: result = "EV_EXCHANGEINTERACTITEM";	break;
	case EV_USEMOBWITHITEM		: result = "EV_USEMOBWITHITEM"		;	break;
	case EV_CALLSCRIPT			: result = "EV_CALLSCRIPT"			;	break;
	case EV_EQUIPITEM			: result = "EV_EQUIPITEM"			;	break;
	default: result = "";
	}
	return result;
}

	//			- TimeBehavior
zCEventMessage::zTTimeBehavior oCMsgManipulate:: MD_GetTimeBehavior()
{ 
	switch (subType) {

	case EV_EQUIPITEM		:	
	case EV_CALLSCRIPT		:	return zCEventMessage::TBZero;
	
	case EV_TAKEVOB			:
	case EV_DROPVOB			:
	case EV_THROWVOB		:	
	case EV_USEMOB			:
	case EV_TAKEMOB			:
	case EV_DROPMOB			:
	case EV_USEITEM			:	
	case EV_USEITEMTOSTATE	:	return zCEventMessage::TBUnknown;
	
	default					:	return zCEventMessage::TBZero;
	}
}

zREAL oCMsgManipulate:: MD_GetMinTime()
{ 
	return 6.0F; 
}

// - Parameter
zSTRING oCMsgManipulate :: MD_GetVobRefName()
{ 
	if ((GetSubType()==EV_USEMOB) || (GetSubType()==EV_TAKEMOB) || (GetSubType()==EV_DROPMOB) || (GetSubType()==EV_DROPVOB) || (GetSubType()==EV_USEITEM) || (GetSubType()==EV_USEITEMTOSTATE) || (GetSubType()==EV_EQUIPITEM))	
		return "";
	else
		return targetVobName; 
}

void oCMsgManipulate :: MD_SetVobRefName(const zSTRING & name)
{ 
	targetVobName = name; 
}

void oCMsgManipulate :: MD_SetVobParam(zCVob* vob) 
{ 
	targetVob = vob; 
}

// ***************************************************************************************
// Conversation
// ***************************************************************************************

oCMsgConversation :: oCMsgConversation() 
{
	timer	= 0.0f;
	target	= NULL;
	ani		= zMDL_ANI_ID_ILLEGAL;
	cAni	= NULL;
	handle	= 0;
	number	= -1;
};

oCMsgConversation :: oCMsgConversation(TConversationSubType subType)
{
	this->subType	= subType;
	timer			= 0.0f;
	target			= NULL;
	handle			= 0;
	number			= -1;
	ani				= zMDL_ANI_ID_ILLEGAL;
	cAni			= NULL;
}

oCMsgConversation :: oCMsgConversation(TConversationSubType subType, const zSTRING& aniName)
{
	timer			= 0.0f;
	target			= NULL;
	handle			= 0;
	number			= -1;
	ani				= zMDL_ANI_ID_ILLEGAL;
	cAni			= NULL;
	this->subType	= subType;
	name			= aniName;
}

oCMsgConversation :: oCMsgConversation(TConversationSubType subType, const zSTRING& sndName, const zSTRING & _text)
{
	timer			= 0.0f;
	target			= NULL;
	handle			= 0;
	number			= -1;
	ani				= zMDL_ANI_ID_ILLEGAL;
	cAni			= NULL;
	this->subType	= subType;
	this->text		= _text;
	name			= sndName;
}

oCMsgConversation :: oCMsgConversation(TConversationSubType subType, zCVob* _target)
{
	timer			= 0.0f;
	target			= NULL;
	handle			= 0;
	number			= -1;
	ani				= zMDL_ANI_ID_ILLEGAL;
	cAni			= NULL;
	this->subType	= subType;
	target			= _target;
}	

oCMsgConversation :: oCMsgConversation(TConversationSubType subType, int number)
{
	timer			= 0.0f;
	target			= NULL;
	handle			= 0;
	number			= -1;
	ani				= zMDL_ANI_ID_ILLEGAL;
	cAni			= NULL;
	this->subType	= subType;
	this->number	= number;
}	

oCMsgConversation :: oCMsgConversation(TConversationSubType subType, int f_yes, int f_no, zREAL timer)
{
	number			= -1;
	target			= NULL;
	handle			= 0;
	ani				= zMDL_ANI_ID_ILLEGAL;
	cAni			= NULL;
	this->subType	= subType;
	this->f_yes		= f_yes;
	this->f_no		= f_no;
	this->timer		= timer;
}

oCMsgConversation :: ~oCMsgConversation()
{
	target			= NULL;
	cAni			= NULL;
}

void oCMsgConversation::Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);

	int st = GetSubType();
	if ((st == EV_PLAYSOUND)	|| (st == EV_CUTSCENE)		|| (st == EV_PLAYANISOUND))		
		arc.WriteString("text",text);
	if ((st == EV_PLAYANISOUND) || (st == EV_PLAYANI) || (st == EV_PLAYANI_FACE) || (st == EV_PLAYSOUND) || (st == EV_OUTPUTSVM) || (st == EV_CUTSCENE))
		arc.WriteString("name",name);
	if ((st == EV_LOOKAT)		|| (st == EV_POINTAT)		|| (st == EV_WAITTILLEND)	|| (st == EV_QUICKLOOK)) {
		arc.WriteString("targetVobName",targetVobName);
	}

	if (st == EV_OUTPUT)
		arc.WriteInt("number",number);


	// nicht nötig :
	// ani, handle
}

void oCMsgConversation::Unarchive(zCArchiver& arc)
{
    oCNpcMessage::Unarchive(arc);
    int st = GetSubType();
    
    if ((st == EV_PLAYANISOUND) || (st == EV_PLAYSOUND) || (st == EV_CUTSCENE))     
            arc.ReadString("text",text);
    if ((st == EV_PLAYANISOUND) || (st == EV_PLAYANI) || (st == EV_PLAYANI_FACE) || (st == EV_PLAYSOUND) || (st == EV_OUTPUTSVM) || (st == EV_CUTSCENE))
    {
            arc.ReadString("name",name);
            // Ani-SoundNamen immer schon uppern
            name.Upper();  //****
    }
    if ((st == EV_LOOKAT) || (st == EV_POINTAT) || (st == EV_WAITTILLEND) || (st == EV_QUICKLOOK)) {
            arc.ReadString  ("targetVobName",targetVobName);
			name = targetVobName;
    };
    if (st == EV_OUTPUT)
            arc.ReadInt("number",number);
}

int oCMsgConversation :: MD_GetNumOfSubTypes()
{ return (int)EV_CONV_MAX; }

void oCMsgConversation :: Delete()
{
	//
	//	DO NOT DELETE INFOMANAGER ULESS IT HAS FINISHED
	//
	static oCInformationManager& mgrInfos = oCInformationManager::GetInformationManager();
	
	if ( this->subType == EV_PROCESSINFOS )
	{
		if ( ! mgrInfos.HasFinished() )
		{
			zERR_MESSAGE( 1,0,"R: Deleting EV_PROCESSINFOS message [FAILED]" );

			return;
		}
		else
		{
			zERR_MESSAGE( 1,0,"R: Deleting EV_PROCESSINFOS message [OK]" );
		}
	}

	oCNpcMessage::Delete();
};

zBOOL oCMsgConversation :: IsOverlay()
{
	if (GetSubType()==EV_PLAYANI_NOOVERLAY) return FALSE;
	if (GetSubType()==EV_OUTPUTSVM_OVERLAY) return TRUE;
	if (GetSubType()==EV_SNDPLAY)			return FALSE;
	if (GetSubType()==EV_STOPPROCESSINFOS)	return FALSE;
	if (GetSubType()==EV_PRINTSCREEN)		return FALSE;
	if (GetSubType()==EV_STARTFX)			return FALSE;
	if (GetSubType()==EV_STOPFX)			return FALSE;
	return ((GetSubType()<=EV_LOOKAT) || (GetSubType()>=EV_POINTAT));	
};

zSTRING oCMsgConversation :: MD_GetSubTypeString(int n)
{
	switch (n) {
	case EV_PLAYANISOUND		: return zSTRING("EV_PLAYANISOUND");
	case EV_PLAYANI				: return zSTRING("EV_PLAYANI");
	case EV_PLAYSOUND			: return zSTRING("EV_PLAYSOUND");
	case EV_LOOKAT				: return zSTRING("EV_LOOKAT");
	case EV_OUTPUT				: return zSTRING("EV_OUTPUT");
	case EV_OUTPUTSVM			: return zSTRING("EV_OUTPUTSVM");
	case EV_CUTSCENE			: return zSTRING("EV_CUTSCENE");
	case EV_WAITTILLEND			: return zSTRING("EV_WAITTILLEND");
	case EV_ASK					: return zSTRING("EV_ASK");
	case EV_WAITFORQUESTION		: return zSTRING("EV_WAITFORQUESTION");
	case EV_STOPLOOKAT			: return zSTRING("EV_STOPLOOKAT");
	
	case EV_STOPPOINTAT			: return zSTRING("EV_STOPPOINTAT");
	case EV_POINTAT				: return zSTRING("EV_POINTAT");
	case EV_QUICKLOOK			: return zSTRING("EV_QUICKLOOK");

	case EV_PLAYANI_NOOVERLAY	: return zSTRING("EV_PLAYANI_NOOVERLAY");
	case EV_PLAYANI_FACE		: return zSTRING("EV_PLAYANI_FACE");
	
	case EV_PROCESSINFOS		: return zSTRING("EV_PROCESSINFOS");
	case EV_STOPPROCESSINFOS	: return zSTRING("EV_STOPPROCESSINFOS");
	case EV_OUTPUTSVM_OVERLAY	: return zSTRING("EV_OUTPUTSVM_OVERLAY");
	case EV_SNDPLAY				: return zSTRING("EV_SNDPLAY");
	default: return zSTRING("");
	}
}
	//			- Parameter
zSTRING oCMsgConversation :: MD_GetVobRefName()
{ return targetVobName; }
void oCMsgConversation :: MD_SetVobRefName(const zSTRING & name)
{ targetVobName = name; }
void oCMsgConversation :: MD_SetVobParam(zCVob* vob)
{ target = vob; }

		//			- TimeBehavior
zCEventMessage::zTTimeBehavior oCMsgConversation :: MD_GetTimeBehavior()
{ 
	switch (subType) {
	case EV_PLAYANISOUND:
	case EV_PLAYANI		:
	case EV_PLAYSOUND	: 
	case EV_QUICKLOOK	: return zCEventMessage::TBFix;

	case EV_STOPLOOKAT	: 
	case EV_STOPPOINTAT :
	case EV_POINTAT		: 
	case EV_LOOKAT		: return zCEventMessage::TBAssembled;
	
	case EV_OUTPUT		:	
	case EV_OUTPUTSVM	:
	case EV_CUTSCENE	: 
	case EV_WAITTILLEND	: 
	case EV_ASK			: 
	case EV_WAITFORQUESTION :	return zCEventMessage::TBUnknown;
	
	default				: return zCEventMessage::TBZero;
	}
}
zREAL oCMsgConversation :: MD_GetMinTime()
{ 
	switch (subType) {
	case EV_PLAYANI		:	if (cAni)	return cAni->GetAniTimeLength() / 1000;
							else		return 3.0f;
		
	case EV_SNDPLAY		:
	case EV_PLAYANISOUND: 
	case EV_PLAYSOUND	: {
							zREAL time = zsound->GetPlayingTimeMSEC(name)/1000;		
							if (time<=0.0f) time = 1.0f + zREAL(text.Length())/6.0f;
							return time;
						  };
	case EV_LOOKAT		:	return 1.0F;
	case EV_POINTAT		:	return 1.0F;
	
	case EV_OUTPUT		:	return 2.0F;
	case EV_OUTPUTSVM	:	return 2.0F;
	case EV_CUTSCENE	:	return 1.0F;
	
	case EV_STOPLOOKAT	:	return 0.0F;
	case EV_STOPPOINTAT	:	return 0.0F;


	default: return 0.0F;
	}
}

// ***************************************************************************************
// Magic
// ***************************************************************************************

oCMsgMagic :: oCMsgMagic()
{
	what				= 0;
	level				= 0;
	removeSymbol		= FALSE;
	target				= NULL;
	manaInvested		= 0;
	energyLeft			= 0;
	targetPos			= zVEC3(0,0,0);
}

oCMsgMagic :: oCMsgMagic(TConversationSubType subType)
{
	what				= 0;
	level				= 0;
	removeSymbol		= FALSE;
	target				= NULL;
	manaInvested		= 0;
	energyLeft			= 0;
	targetPos			= zVEC3(0,0,0);
	this->subType		= subType;
}

oCMsgMagic :: oCMsgMagic(TConversationSubType subType, int what, zBOOL removeSymbol)
{
	level				= 0;
	target				= NULL;
	manaInvested		= 0;
	energyLeft			= 0;
	targetPos			= zVEC3(0,0,0);
	this->subType		= subType;
	this->what			= what;
	this->removeSymbol	= removeSymbol;
}

oCMsgMagic :: ~oCMsgMagic()
{
	target				= NULL;
}

	// Pack / Unpack
void oCMsgMagic :: Pack	(zCBuffer& buffer, zCEventManager* evManContext)
{	
	oCNpcMessage::Pack (buffer, evManContext);

	buffer.Write (&subType,		sizeof(subType));
	buffer.Write (&what,		sizeof(what));
	buffer.Write (&removeSymbol,sizeof(removeSymbol));
	buffer.Write (&level,		sizeof(level));
	buffer.Write (&manaInvested,sizeof(manaInvested));
	buffer.Write (&energyLeft,	sizeof(energyLeft));
	buffer.Write (&activeSpell,	sizeof(activeSpell));

	zTVobID vobID	= 0;
	if (target) vobID = target->GetVobID();

	buffer.Write (&vobID, sizeof(vobID));
	buffer.Write (&targetPos, sizeof(targetPos));
};

void oCMsgMagic :: Unpack (zCBuffer& buffer, zCEventManager* evManContext)
{
	oCNpcMessage::Pack (buffer, evManContext);

	buffer.Read (&subType,		sizeof(subType));
	buffer.Read (&what,			sizeof(what));
	buffer.Read (&removeSymbol,	sizeof(removeSymbol));
	buffer.Read (&level,		sizeof(level));
	buffer.Read (&manaInvested,	sizeof(manaInvested));
	buffer.Read (&energyLeft,	sizeof(energyLeft));
	buffer.Read (&activeSpell,	sizeof(activeSpell));

	target = NULL;
	zTVobID vobID = 0;
	buffer.Read	(&vobID, sizeof(vobID));
	if (vobID!=0) target = ogame->GetWorld()->SearchVobByID(vobID);
	buffer.Read (&targetPos,	sizeof(targetPos));
};

int oCMsgMagic:: MD_GetNumOfSubTypes()
{ return (int)EV_MAGIC_MAX; }

zSTRING oCMsgMagic:: MD_GetSubTypeString(int n)
{
	switch (n)
	{
	case EV_OPEN:			return zSTRING("EV_OPEN");
	case EV_CLOSE:			return zSTRING("EV_CLOSE");
	case EV_MOVE:			return zSTRING("EV_MOVE");
	case EV_INVEST:			return zSTRING("EV_INVEST");
	case EV_CAST:			return zSTRING("EV_CAST");
	case EV_SETLEVEL:		return zSTRING("EV_SETLEVEL");
	case EV_SHOWSYMBOL:		return zSTRING("EV_SHOWSYMBOL");
	case EV_SETFRONTSPELL:	return zSTRING("EV_SETFRONTSPELL");
	case EV_CASTSPELL:		return zSTRING("EV_CASTSPELL"); 
	case EV_READY:			return zSTRING("EV_READY"); 
	case EV_UNREADY:		return zSTRING("EV_UNREADY"); 
	default:				return zSTRING("");
	}
}

void oCMsgMagic::Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);

	arc.WriteInt	("what",		what);
	arc.WriteInt	("level",		level);
	arc.WriteBool	("removeSymbol",removeSymbol);
}

void oCMsgMagic::Unarchive(zCArchiver& arc)
{
	oCNpcMessage::Unarchive(arc);

	arc.ReadInt		("what",		what);
	arc.ReadInt		("level",		level);
	arc.ReadBool	("removeSymbol",removeSymbol);
}

// ***************************************************************************************
// Request
// ***************************************************************************************

#if defined(SECUROM) && !defined(COMPILING_SPACER)
oCMsgRequest::oCMsgRequest()
{
	this->subType	= EV_REQUEST_0;
	this->delay		= 0.0f;
}

oCMsgRequest::oCMsgRequest(TRequestSubType subType, float delay)
{
	this->subType	= subType;
	this->delay		= delay;
}

oCMsgRequest::~oCMsgRequest()
{
	//
};

void oCMsgRequest::Pack(zCBuffer& buffer, zCEventManager* evManContext)
{	
	oCNpcMessage::Pack(buffer, evManContext);
	buffer.Write (&subType, sizeof(subType));
	buffer.Write (&delay, sizeof(delay));
};

void oCMsgRequest::Unpack(zCBuffer& buffer, zCEventManager* evManContext)
{
	oCNpcMessage::Pack(buffer, evManContext);
	buffer.Read	(&subType, sizeof(subType));
	buffer.Read (&delay, sizeof(delay));
};

void oCMsgRequest::Archive(zCArchiver& arc)
{
	oCNpcMessage::Archive(arc);
	arc.WriteInt("subType", int(subType));
	arc.WriteFloat("delay", delay);
}

void oCMsgRequest::Unarchive(zCArchiver& arc)
{
	oCNpcMessage::Unarchive(arc);
	int tmp = int(EV_REQUEST_0); arc.ReadInt("subType", tmp); subType = TRequestSubType(tmp);
	delay = 0.0f; arc.ReadFloat("delay", delay);
}
#endif
