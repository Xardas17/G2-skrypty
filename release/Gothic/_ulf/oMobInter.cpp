/******************************************************************************** 
 
     $Workfile:: oMobInter.cpp        $                $Date:: 24.04.01 17:33   $
     $Revision:: 121                  $             $Modtime:: 19.04.01 15:22   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oMobInter.cpp $
 * 
 * 121   24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 119   13.03.01 18:36 Wohlers
 * Patches 1.07 1.Teil
 * 
 * 118   16.02.01 16:38 Speckels
 * 
 * 117   15.02.01 14:58 Wohlers
 * 
 * 116   13.02.01 19:18 Moos
 * Durch-Wände-Schlag-Fix
 * 
 * 115   10.02.01 20:48 Wohlers
 * 
 * 114   9.02.01 17:41 Wohlers
 * Ani "S_S0" not found-Meldung entschaerft.
 * 
 * 113   9.02.01 17:33 Wohlers
 * Fix fuer den FireVobtree-Fix
 * 
 * 112   9.02.01 16:51 Wohlers
 * Leak-Fix fuer FireVobtrees
 * 
 * 111   8.02.01 19:19 Wohlers
 * 
 * 110   8.02.01 18:38 Moos
 * 
 * 109   8.02.01 18:23 Moos
 * 
 * 108   7.02.01 20:55 Wohlers
 * 
 * 107   6.02.01 2:31 Wohlers
 * 
 * 106   30.01.01 13:48 Moos
 * 
 * 105   30.01.01 12:23 Moos
 * 
 * 104   29.01.01 20:19 Moos
 * 
 * 103   29.01.01 16:27 Wohlers
 * 
 * 102   28.01.01 19:08 Wohlers
 * 
 * 101   25.01.01 21:53 Wohlers
 * 
 * 100   25.01.01 15:46 Moos
 * 
 * 99    24.01.01 18:36 Speckels
 * 
 * 98    22.01.01 22:38 Wohlers
 * 
 * 97    22.01.01 18:25 Keskenti
 * 
 * 96    22.01.01 13:09 Moos
 * 
 * 95    19.01.01 16:17 Keskenti
 * 
 * 94    18.01.01 14:49 Moos
 * 
 * 93    18.01.01 0:39 Speckels
 * 
 * 92    16.01.01 17:22 Keskenti
 * 
 * 91    15.01.01 17:07 Keskenti
 * 
 * 90    12.01.01 15:24 Wohlers
 * 
 * 89    12.01.01 12:38 Moos
 * 
 * 88    10.01.01 15:23 Wohlers
 * 
 * 87    9.01.01 21:35 Wohlers
 * 
 * 86    4.01.01 14:07 Keskenti
 * 
 * 85    20.12.00 17:13 Moos
 * 
 * 84    19.12.00 16:41 Wohlers
 * 
 * 83    18.12.00 10:02 Keskenti
 * 
 * 82    12.12.00 14:55 Keskenti
 * 
 * 81    12.12.00 14:15 Keskenti
 * 
 * 80    29.11.00 12:52 Speckels
 * 
 * 79    21.11.00 19:16 Wohlers
 * 
 * 78    21.11.00 14:12 Wohlers
 * 
 * 77    16.11.00 19:23 Wohlers
 * 
 * 76    15.11.00 17:19 Wohlers
 * 
 * 75    9.11.00 17:10 Wohlers
 * 
 * 74    8.11.00 14:42 Wohlers
 * 
 * 73    6.11.00 18:45 Wohlers
 * 
 * 72    6.11.00 18:17 Wohlers
 * 
 * 71    31.10.00 20:27 Keskenti
 * 
 * 70    30.10.00 19:05 Moos
 * 
 * 69    27/10/00 16:53 Luesebrink
 * 
 * 68    26.10.00 14:16 Speckels
 * 
 * 67    26.10.00 14:10 Speckels
 * 
 * 66    25/10/00 15:48 Luesebrink
 * 
 * 65    25.10.00 15:24 Speckels
 * 
 * 64    25/10/00 13:06 Luesebrink
 * 
 * 63    21/10/00 16:26 Luesebrink
 * 
 * 62    18/10/00 15:17 Luesebrink
 * 
 * 61    17.10.00 16:37 Wohlers
 * 
 * 
 *********************************************************************************/

#include "zCore.h"

#include "zVob.h"
#include "zModel.h"
#include "zArchiver.h"
#include "zAICamera.h"
#include "zEventMan.h"
#include "zBuffer.h"
#include "zSoundMan.h"
#include "zPhysics.h"
#include "zPlayerInfo.h"
#include "zNetVobControl.h"
#include "zInput_Win32.h"
#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

#include "oMobInter.h"
#include "oNpc.h"
#include "oNpcMessages.h"
#include "oAIHuman.h"
#include "oAIShoot.h"
#include "oItem.h"
#include "oInventory.h"
#include "oGame.h"
#include "oWorld.h"

zCLASS_DEFINITION			( oCMOB,			oCVob			,		0, 2)
zCLASS_DEFINITION			( oCMobInter,		oCMOB			,		0, 3)
zCLASS_DEFINITION			( oCMobBed,			oCMobInter		,		0, 0)
zCLASS_DEFINITION			( oCMobSwitch,		oCMobInter		,		0, 0)
zCLASS_DEFINITION_ABSTRACT	( oCMobLockable,	oCMobInter		,		   0)
zCLASS_DEFINITION			( oCMobContainer,	oCMobLockable	,		0, 1)
																
zCLASS_DEFINITION			( oCMobWheel,		oCMobInter		,		0, 0)
zCLASS_DEFINITION			( oCMobLadder,		oCMobInter		,		0, 0)
zCLASS_DEFINITION			( oCMobDoor,		oCMobLockable	,		0, 1)
zCLASS_DEFINITION			( oCMobFire,		oCMobInter		,		0, 2)
zCLASS_DEFINITION			( oCMobItemSlot,	oCMobInter		,		0, 0)
																
zCLASS_DEFINITION			( oCDummyVobGenerator,	zCVob		,		0, 0)

// Temp
zCArray<zSTRING>	mobList;
zBOOL				mobNameConv = TRUE;
zBOOL				mobSaveConv	= FALSE;

// *********************************************************************************
// Statics
// *********************************************************************************

static zCPar_Symbol*	symState[4]		= { NULL, NULL, NULL, NULL };
static int				mobBodyState[4] = { BS_STAND, BS_STAND, BS_STAND, BS_STAND };

// *********************************************************************************
// Messages
// *********************************************************************************

zCLASS_DEFINITION			( oCMobMsg,			zCEventMessage,		0, 0)

oCMobMsg :: oCMobMsg (TMobMsgSubType subType, oCNpc* npc)
{
	this->subType	= subType;
	this->npc		= npc;
	from			= 0;
	to				= 0;
	playAni			= FALSE;
}

oCMobMsg :: oCMobMsg ()
{
	npc				= NULL;
	from			= 0;
	to				= 0;
	playAni			= FALSE;
};

oCMobMsg :: oCMobMsg (TMobMsgSubType subType, oCNpc* npc, zBOOL flag)
{
	this->subType	= subType;
	this->npc		= npc;
	from			= 0;
	to				= 0;
	playAni			= flag;
}

void oCMobMsg :: Pack	(zCBuffer& buffer, zCEventManager* evManContext)
{
	zCEventMessage::Pack (buffer, evManContext);

	zTVobID vobID	= 0;
	if (npc)  vobID = npc->GetVobID();
	buffer.Write (&vobID,	sizeof(vobID));

    int tmp;
    tmp = from;
   	buffer.Write (&tmp,	sizeof(tmp));

    tmp = to;
   	buffer.Write (&tmp,	sizeof(tmp));

    tmp = playAni;
   	buffer.Write (&tmp,	sizeof(tmp));

   	//buffer.Write (&from,	sizeof(from));
	//buffer.Write (&to,		sizeof(to));
	//buffer.Write (&playAni,	sizeof(playAni));
}

void oCMobMsg :: Unpack	(zCBuffer& buffer, zCEventManager* evManContext)
{
	zCEventMessage::Pack (buffer, evManContext);

	zTVobID vobID = 0;
	buffer.Read	(&vobID,	sizeof(vobID));
	npc = (oCNpc*) ogame->GetWorld()->SearchVobByID(vobID);

    int tmp;

	buffer.Read (&tmp,		sizeof(tmp));
    from = tmp;    

	buffer.Read (&tmp,		sizeof(tmp));
    to = tmp;    

	buffer.Read (&tmp,		sizeof(tmp));
    playAni = tmp;    

//	buffer.Read (&from,		sizeof(from));
//	buffer.Read (&to,		sizeof(to));
//	buffer.Read (&playAni,	sizeof(playAni));
}

int	oCMobMsg :: MD_GetNumOfSubTypes	()
{
	return 5;
}

zSTRING	oCMobMsg :: MD_GetSubTypeString	(int n)
{
	switch (n) {
	
		case EV_STARTINTERACTION	:	return "EV_STARTINTERACTION";
		case EV_STARTSTATECHANGE	:	return "EV_STARTSTATECHANGE";
		case EV_ENDINTERACTION		:	return "EV_ENDINTERACTION";
		case EV_UNLOCK				:	return "EV_UNLOCK";
		case EV_LOCK				:	return "EV_LOCK";	
		case EV_CALLSCRIPT			:	return "EV_CALLSCRIPT";
	}
	return "";
}

// *********************************************************************************
// Static : Konvertierung der alten Mobs ins neue Format
// *********************************************************************************
/*
void oCMOB :: ConvertOldMobsToNewMobs()
{
	oCMOB* newmob;

	// Durchsuche aktuelle Mob-Liste
	oCMob *oldmob = oCMob::MobList.wurzel;
	while (oldmob) {

		newmob = NULL;
		if (oldmob->HasFlag(OBJ_FLAG_SITDOWN)) {
			// Stuhl
			newmob	= new oCMobInter();
		} else if (oldmob->HasFlag(OBJ_FLAG_LIEDOWN)) {
			// Bett
			newmob	= new oCMobBed();
		}
		
		if (newmob) {
			// Was ist mit dem MeshNamen ?
			newmob -> SetVisual			(oldmob->GetVisual());
			newmob -> SetShowVisual		(TRUE);
			// Position setzen
			zMATRIX4 trafo				= oldmob -> trafoObjToWorld;
			zCWorld* wld				= oldmob -> GetHomeWorld();
			newmob -> SetCollDet		(FALSE);
			newmob -> SetPositionWorld	(0,0,0);	// Safety
			wld	   -> RemoveVob			(oldmob);
			wld	   -> AddVob			(newmob);
			newmob -> SetTrafoObjToWorld(trafo);
			// Attribute übernehmen
			newmob -> name				= oldmob -> name;
			newmob -> hitp				= oldmob -> hp_max;
			newmob -> moveable			= oldmob -> HasFlag(OBJ_FLAG_MOVEABLE);
			newmob -> takeable			= oldmob -> HasFlag(OBJ_FLAG_TAKEABLE);
			newmob -> sndMat			= (oTSndMaterial) oldmob -> GetSoundMaterial();
			newmob -> visualDestroyed	= oldmob -> destroyed_mesh;
			newmob -> SetOwner			( oldmob -> owner , oldmob -> owner_guild);
			newmob -> isDestroyed		= oldmob -> destroyed;
			newmob -> SetCollDetDyn		( oldmob -> GetCollDetDyn()  );
			newmob -> SetCollDetStat	( oldmob -> GetCollDetStat() );
		}
		oldmob = oldmob->next;
	}
}
*/
// *********************************************************************************
// Neuer oCMob
// *********************************************************************************

oCMOB :: oCMOB ()
{
	hitp			= 10;
	damage			= 0;
	moveable		= FALSE;
	takeable		= FALSE;
	focusOverride	= FALSE;
	sndMat			= SND_MAT_WOOD;
	owner			= -1;
	ownerGuild		= -1;
	focusNameIndex	= -1;
	isDestroyed		= FALSE;

	SetVobType		(zVOB_TYPE_MOB);
	SetShowVisual	(TRUE);
    SetCollisionClass (zCCollObjectComplex::S_GetCollObjClass());             // [Moos] 20.12.00 Anpassung an Vob-Änderung	
}

oCMOB :: ~oCMOB ()
{
	ignoreVobList.DeleteList();
}

void oCMOB :: SetVisual	(zCVisual* v)
{
	oCVob :: SetVisual(v);
    SetCollisionClass (zCCollObjectComplex::S_GetCollObjClass());             // [Moos] 20.12.00 Anpassung an Vob-Änderung	
};

void oCMOB :: SetName(const zSTRING& name)
{
	focusNameIndex = parser.GetIndex(name);
}

zSTRING oCMOB :: GetName()
{
	zSTRING focusName;
	zCPar_Symbol*	sym  = parser.GetSymbol	(focusNameIndex);
	if (sym)		sym -> GetValue			(focusName);
	return focusName;
};

zSTRING oCMOB :: GetScemeName()
{
	// Hier nur wichtig, wenn das Ding tragbar ist -> 
	// aus "HUMANS_CARRY" + Schemanamen ergibt dann das zu aktivierende Overlay-MDS
	zSTRING		vname;
	zCVisual*	v = GetVisual();
	if (v) {
		vname = v->GetVisualName();
		vname = vname.Copied("_",zSTR_BEFORE);
	}
	return vname;
};

void oCMOB :: OnDamage	(zCVob* otherVob, zCVob* inflictorVob, zREAL damage, int damageType, const zVEC3& hitLocation)
{
	Hit((int)damage);
}

void oCMOB :: OnMessage	(zCEventMessage *eventMessage, zCVob* sourceVob)
{
}

zCModel* oCMOB :: GetModel()
{
	return dynamic_cast<zCModel*>(GetVisual());
}

void oCMOB :: SetMoveable (zBOOL on)
{
	moveable = on;
}

zBOOL oCMOB :: IsMoveable()
{
	return moveable;
}

void oCMOB :: SetSoundMaterial(oTSndMaterial mat)
{
	sndMat = mat;
}

oTSndMaterial oCMOB :: GetSoundMaterial()
{
	return sndMat;
}

void oCMOB :: GetSoundMaterial_AM (zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2, int damage)
{
	med2	 = zCSoundManager :: zSND_MAN_MEDIUM_OBJECT;
	mat2	 = GetSoundMaterial();				
}

void oCMOB :: SetOwner (const zSTRING& o, const zSTRING &og)
{
	ownerStr			= o;
	ownerGuildStr		= og;
	int owner			= parser.GetIndex(o);
	zCPar_Symbol* sym	= parser.GetSymbol(og);
	int ownerg			= -1;
	if (sym) sym->GetValue(ownerg);
	SetOwner(owner,ownerg);
}

void oCMOB :: SetOwner (int o, int og)
{
	owner		= o;
	ownerGuild	= og;
}

zBOOL oCMOB :: IsOwnedByGuild(int guild)
{
	if		( ownerGuild  < 0	  ) return FALSE;
	else if ( ownerGuild == guild ) return TRUE;

	return FALSE;
}

zBOOL oCMOB :: IsOwnedByNpc( int instance )
{
	if		( owner  < 0		) return FALSE;
	else if ( owner == instance ) return TRUE;

	return FALSE;
}

zBOOL oCMOB :: IsOwner (oCNpc* npc)
{
	if		( IsOwnedByNpc	( npc->GetInstance () ) ) return TRUE;
	else if ( IsOwnedByGuild( npc->GetTrueGuild() ) ) return TRUE;

	return FALSE;
}

void oCMOB :: Hit (int dam)
{
//	if ((hitp>0) && (dam>hitp)) Destroy();
}

void oCMOB :: Destroy ()
{
	if (!IsDestroyed()) {
		// Destruction - Sound 
		zsndMan->StartDestructionSound (this,GetSoundMaterial());
		// Partikeleffect
		zCParticleFX	*partFX	= zNEW( zCParticleFX );
		zCVob			*vobFX	= zNEW( zCVob );
		vobFX	->SetCollDet				(FALSE);
		vobFX	->SetPositionWorld			(GetPositionWorld());  
		vobFX	->SetVisual					(partFX);
		vobFX	->SetDontWriteIntoArchive	(TRUE);
//		partFX	->SetEmitter				("PFX_MOBDESTROY_"+SndMaterialName[sndMat]);
		partFX	->SetEmitter				("PFX_MOBDESTROY");
		partFX  ->GetEmitter()->shpMesh_S	=	"OC_MOB_CHEST_LARGE.3DS";
//		if (GetVisual()) {
//			partFX -> emitter -> shpMesh_S = GetVisual()->GetVisualName();
//		}
		partFX  ->GetEmitter()->UpdateInternals	();
		partFX  ->CreateParticles			();
		GetHomeWorld()->AddVob				(vobFX);
		// und Mesh ersetzen
		isDestroyed = TRUE;
		if (!visualDestroyed.IsEmpty()) 
		{
			zCVob::SetVisual(visualDestroyed);	
			UpdateVisualDependencies();
		} 
		else if ( GetHomeWorld() ) 
		{
			GetHomeWorld()->RemoveVob(this);
//			delete this;
		}
	}
}

void oCMOB :: InsertInIgnoreList(zCVob* vob)
{
	if (!ignoreVobList.InList(vob)) {
		ignoreVobList.Insert(vob);
	}
};

void oCMOB :: RemoveFromIgnoreList(zCVob* vob)
{
	ignoreVobList.Remove(vob);
};

zBOOL oCMOB :: CanThisCollideWith	(zCVob* vob)				// gives derived vobs the possibility to exclude special other vobs from collDet and collResp
{
	return !ignoreVobList.InList(vob);
};
	
// *************************************
// Archive / Unarchive
// *************************************

void oCMOB :: Archive	(zCArchiver &arc)
{
	oCVob :: Archive	(arc);
	
	// Properties Spacer,

	arc.WriteGroupBegin	("MOB");
	arc.WriteString		("focusName"		,name);
	arc.WriteInt		("hitpoints"		,hitp);
	arc.WriteInt		("damage"			,damage);
	arc.WriteBool		("moveable"			,moveable);
	arc.WriteBool		("takeable"			,takeable);
	arc.WriteBool		("focusOverride"	,focusOverride);
	arc.WriteEnum		("soundMaterial"	,"WOOD;STONE;METAL;LEATHER;CLAY;GLAS",int(GetSoundMaterial()));
	arc.WriteString		("visualDestroyed"	,visualDestroyed);
	arc.WriteString		("owner"			,ownerStr);
	arc.WriteString		("ownerGuild"		,ownerGuildStr);
	arc.WriteGroupEnd	("MOB");
	
	// Internals
	if (!arc.InProperties()) {
		arc.WriteBool	("isDestroyed"		,isDestroyed);
	};

}

void oCMOB :: Unarchive	(zCArchiver &arc)
{
    int tmp;
	oCVob :: Unarchive	(arc);

	// Properties Spacer
	arc.ReadString		("focusName"		,name);
//	arc.ReadInt			("hitpoints"		,hitp);
	arc.ReadInt			("hitpoints"		,tmp);          hitp        = tmp;
//	arc.ReadInt			("damage"		    ,damage);
	arc.ReadInt			("damage"			,tmp);          damage      = tmp;
//	arc.ReadBool		("moveable"			,moveable);
	arc.ReadBool		("moveable"			,tmp);          moveable    = tmp;
//	arc.ReadBool		("takeable"			,takeable);
	arc.ReadBool		("takeable"			,tmp);          takeable    = tmp;
//	arc.ReadBool		("focusOverride"	,focusOverride);
	arc.ReadBool		("focusOverride"	,tmp);          focusOverride = tmp;
//	arc.ReadEnum		("soundMaterial"	,(int&)sndMat);
	arc.ReadEnum		("soundMaterial"	,tmp);          sndMat      = (oTSndMaterial)tmp;
	arc.ReadString		("visualDestroyed"	,visualDestroyed);
	arc.ReadString		("owner"			,ownerStr);
	arc.ReadString		("ownerGuild"		,ownerGuildStr);
	
	// Internals
	if (!arc.InProperties()) {
//		arc.ReadBool	("isDestroyed"		,isDestroyed);
		arc.ReadBool	("isDestroyed"		,tmp);          isDestroyed  = tmp;
		SetOwner		(ownerStr,ownerGuildStr);
	}

	if (!mobNameConv) SetName(name);

	// TMP
	if (mobNameConv && !name.IsEmpty()) {
		
		zSTRING mobID	= name;
		if (mobID.Search("MOBNAME_")<0) mobID = "MOBNAME_"+mobID;
		mobID.Upper();
		for (int i=0; i<mobID.Length(); i++) {
			if ((mobID[i]<=32) || (mobID[i]=='-')) mobID[i] = '_';
		}
		
		SetName(mobID);

		if (mobSaveConv) {
			// Erzeuge File mit entsprechenden Mobsi-Namen
			if (!mobList.IsInList(mobID)) {

				mobList.Insert(mobID);

				zoptions->ChangeDir(DIR_SCRIPTS);
				zFILE *f = zfactory->CreateZFile("MOBSI.D");
				if (!f->Exists()) {
					f->Create	();
				} else {
					f->Open		(TRUE);
					f->Append	();
				}
				f->Write ("CONST STRING "+mobID+" = \""+name+"\"\n");
				f->Close ();
				delete (f);
			}
		}
	}
}

zBOOL oCMOB::AllowDiscardingOfSubtree(){
    return TRUE;
}

// *********************************************************************************
// oCMob-Interactive Tagesablauf 
// *********************************************************************************

// [EDENFELD] 1.09 static removed for thread savety
//static int numMobsTriggered = 0;

int oCMobInter :: SetAllMobsToState (oCWorld* wld, const zSTRING& scheme, int stateNr)
{
	int numMobsTriggered = 0;
	// Alle Vobs dieser Welt durchlaufen
	TraverseMobs(&wld->globalVobTree,scheme,stateNr, &numMobsTriggered);
	return numMobsTriggered;
}

void oCMobInter :: TraverseMobs ( zCTree <zCVob> *node, const zSTRING& scheme, int stateNr, int *a_iCounter )
{
	if (node == NULL) return;

	oCMobInter* mob = zDYNAMIC_CAST<oCMobInter>(node->GetData());
	
	if (mob)
	{
		if (mob->GetScemeName()==scheme)
		{
			mob->SetTempState(stateNr);
			if (mob->IsTempStateChanged())
			{
				// [BENDLIN] 2002-05-18, Trigger all changed MOBs
				mob->SetStateToTempState();
				(*a_iCounter)++;
			}
		}
	}

	oCMobInter::TraverseMobs( node->GetFirstChild(), scheme, stateNr, a_iCounter);
	oCMobInter::TraverseMobs( node->GetNextChild(), scheme, stateNr, a_iCounter);
}

void oCMobInter :: TriggerAllMobsToTmpState (zCWorld* wld)
{
	TraverseTriggerMobs(&wld->globalVobTree);
};

void oCMobInter :: TraverseTriggerMobs(zCTree <zCVob>* node)
{
	if (!node) return;

	oCMobInter* mob = zDYNAMIC_CAST<oCMobInter>(node->GetData());
	
	if (mob /*&& mob->IsTempStateChanged()*/) mob->SetStateToTempState();
	
	TraverseTriggerMobs ( node->GetFirstChild()	);
	TraverseTriggerMobs ( node->GetNextChild()	);
};

// *********************************************************************************
// Neuer oCMob-Interactive
// *********************************************************************************

oCMobInter :: oCMobInter ()
{
	state			= 0;
	state_target	= state;
	state_num		= 1;
	mobStateAni		= zMDL_ANI_ID_ILLEGAL;
	npcStateAni		= zMDL_ANI_ID_ILLEGAL;
	aniCombHeight	= 0;
	// usedNpcNode		= -1;
	startPos		= zVEC3(0,0,0);
	rewind			= FALSE;
	npcsMax			= 0;
	npcsNeeded		= 0;
	npcsCurrent		= 0;
	
	inUseVob		= NULL;
	timerEnd		= 0.0f;

	// Patch 1.08
	tmpStateChanged	= FALSE;
	tmpState		= 0;

	onInterruptReturnToSlotPos = TRUE;

	SetDirection(MOBINTER_DIRECTION_NONE);
}

oCMobInter :: ~oCMobInter()
{
	inUseVob		= NULL;
   
    optimalPosList.DeleteListDatas(); // [Moos] Leakfix
}

void oCMobInter :: SetVisual (zCVisual *v)
{
	oCMOB :: SetVisual(v);
	if (v) {
		// Schnapp dir den Sceme Name
		zSTRING name = v->GetVisualName();
		sceme = name.Copied		("_",zSTR_BEFORE);
	  	//SetCollType				(zVOB_COLL_TYPE_BIG_OBJECT);
        SetCollisionClass		(zCCollObjectComplex::S_GetCollObjClass());             // [Moos] 20.12.00 Anpassung an Vob-Änderung
		SetIgnoredByTraceRay	(FALSE);
	}
};

// Patch 1.08
void oCMobInter :: SetTempState(int _tmpState)
{
	tmpStateChanged = ((_tmpState!=tmpState) || (_tmpState!=state));
	tmpState		= _tmpState;
};

zBOOL oCMobInter :: IsTempStateChanged()
{
	return tmpStateChanged;
};

void oCMobInter :: SetStateToTempState()
{
	if (tmpStateChanged) {
		
		if ((tmpState==1) && (GetState() == 0))
		{				
			GetEM()->OnTrigger		(this,this);	
		}
		else if ( (tmpState==0) && (GetState()>0) ) 
		{			
			GetEM()->OnUntrigger	(this,this);	
		}

		tmpStateChanged = FALSE;
	};
};

void oCMobInter :: SetMobBodyState(oCNpc* npc)
{
	if (!symState[0]) { symState[0] = parser.GetSymbol("MOB_NOTINTERRUPTABLE");		mobBodyState[0] = BS_MOBINTERACT;	};
	if (!symState[1]) { symState[1] = parser.GetSymbol("MOB_SIT");					mobBodyState[1] = BS_SIT;			};
	if (!symState[2]) { symState[2] = parser.GetSymbol("MOB_LIE");					mobBodyState[2] = BS_LIE;			};
	if (!symState[3]) { symState[3] = parser.GetSymbol("MOB_CLIMB");				mobBodyState[3] = BS_CLIMB;			};
	
	zSTRING schemeEnum;
	for (int i=0; i<4; i++) 
	{	
		if (symState[i]) 
		{
			symState[i]->GetValue(schemeEnum);

			int w = 1;
			do
			{
				zSTRING nextScheme = schemeEnum.PickWord(w++,",");
				if (nextScheme.IsEmpty()) break;
				if (GetScemeName().Search(nextScheme)>=0)
				{
					npc->SetBodyState(mobBodyState[i]);
					return;
				}
			}
			while (1==1);
		}
	}
	// Standard : Unterbrechbar
	npc->SetBodyState(BS_MOBINTERACT_INTERRUPT);
}

void oCMobInter :: OnDamage	(zCVob* otherVob, zCVob* inflictorVob, zREAL damage, int damageType, const zVEC3& hitLocation)
{
	oCMOB::OnDamage(otherVob, inflictorVob, damage, damageType, hitLocation);
}

void oCMobInter :: OnMessage (zCEventMessage* message, zCVob* sourceVob)
{
	if (dynamic_cast<oCMobMsg*>(message)) {
		//SetSleeping(FALSE);
		oCMobMsg* mobMsg = (oCMobMsg*)message;
		switch (mobMsg->GetSubType()) {
			case oCMobMsg::EV_STARTINTERACTION	:	StartInteraction(mobMsg->npc);								break;
			case oCMobMsg::EV_STARTSTATECHANGE	:	StartStateChange(mobMsg->npc,mobMsg->from, mobMsg->to);		break;
			case oCMobMsg::EV_ENDINTERACTION	:	StopInteraction	(mobMsg->npc);								break;
			case oCMobMsg::EV_CALLSCRIPT		:	CallOnStateFunc	(mobMsg->npc,mobMsg->to);								break;
		}
	}
}

void oCMobInter :: SetUseWithItem (const zSTRING& name)
{
	useWithItem = name;
}

int	oCMobInter :: GetUseWithItem ()
{
	if (useWithItem.IsEmpty()) return -1;
	return parser.GetIndex(useWithItem);
}

zBOOL oCMobInter :: HasUseWithItem(oCNpc* npc)
{
	int instance = GetUseWithItem();
	if (instance>0) {
		// ***********************************
		// Spieler muss das Item in der Hand 
		// oder InteractItem angemeldet haben
		// ***********************************
		if (npc->HasInHand(instance)) {
			// ***************************************
			// Erforderliches Item bereits in der Hand
			// ***************************************
			return TRUE;
		
		} else if (npc->GetInteractItem() && (npc->GetInteractItem()->GetInstance()==instance)) {
			// ***************************************
			// Erforderliches Item wurde vorher zur
			// Interaction angemeldet -> Start !
			// ***************************************
			return TRUE;
		
		} else if (npc->IsSelfPlayer() && npc->IsInInv(instance)) {
			
//			npc->SetInteractItem(npc->IsInInv(instance));
	
			// Patch 1.07
			oCItem* item = npc->RemoveFromInv(instance,1);
			npc->SetInteractItem(item);

			return TRUE;
		}

		return FALSE;
	}
	return TRUE;
}

zSTRING oCMobInter :: GetScemeName()
{
	return sceme;
}

void oCMobInter :: ScanIdealPositions ()
// Scan for ideal Positions
// Darf erst passieren, wenn Vob in Welt eingefügt ist.
{
	if (!GetHomeWorld()) return;
	if ((startPos==GetPositionWorld()) && (optimalPosList.GetNumInList()>0)) return;
	if (npcsCurrent>0) return;
	
	startPos = GetPositionWorld();
	optimalPosList.DeleteListDatas();

	if (GetModel()) {
		zCModelPrototype* m = GetModel()->GetModelProto();
		// zCArray<zCModelNode*> nodeList;					// linear nodeList => faster access, order important
		for (int i=0; i<m->GetNodeList().GetNumInList(); i++) {
			// Look For Slots "ZS_IDEALPOS"
			zCModelNode*	node		= m->GetNodeList()[i];
			zSTRING			nodeName	= node->GetName();
			// Sortierte Liste ?
			if (node && (nodeName.Search("ZS_POS")>=0)) {

				// Optimal Position
				TMobOptPos* optpos	= zNEW( TMobOptPos );
				optpos->trafo		= GetTrafoModelNodeToWorld(nodeName);
				optpos->distance	= FALSE;
				optpos->npc			= NULL;
				optpos->nodeName	= nodeName;
				
				// Nur Distance wichtig ?
				if (node->nodeName.Search("DIST")>=0) {
					// Nur Distance
					optpos->distance = TRUE;
				}

				if (node->nodeName.Search("NPC")>=0) {
					// MultiMob !
					npcsMax ++;
					npcsNeeded ++;
				}

				// In Liste einfügen
				optimalPosList.Insert(optpos);
			}
		}
	}
	if (npcsMax	== 0) {
		npcsMax		= 1;
		npcsNeeded	= 1;
	}
}

zBOOL oCMobInter :: GetFreePosition (oCNpc* npc, zVEC3& pos)
// Getting a free Position from this Object
{
	// Scan Positions
	ScanIdealPositions();
	// Look for a free one
	TMobOptPos* optPos = SearchFreePosition(npc);
	if (optPos) {
		pos = optPos->trafo.GetTranslation();
		return TRUE;
	} 
	return FALSE;
};

TMobOptPos* oCMobInter :: SearchFreePosition(oCNpc* npc, zREAL a_fMaxDist)
// Search List for a free Position
{
	// Okay, darf noch ein Slot vergeben werden
	if (npcsCurrent >= npcsMax) return NULL;

	// Now Search one
	zCList<TMobOptPos>* data	= optimalPosList.GetNextInList();;		// List of all Optimal Positions
	TMobOptPos*			optPos	= NULL;
	TMobOptPos*			found	= NULL;
	zREAL				minDist	= zREAL_MAX;	// Abstand zum naechsten Slot
	a_fMaxDist				   *= a_fMaxDist;	// max. erlaubter Abstand zum Slot ( nur für SCs )
	zREAL				dist;

	// [EDENFELD] 1.09
	zBOOL				tooFar		= FALSE;
	zBOOL				wrongSide	= FALSE;

	while (data) {
		optPos	= data -> GetData();
		data	= data -> GetNextInList();
		// Nur, wenn diese Position nicht schon durch anderen NSC belegt ist.
		if (optPos->npc==npc)	return optPos;
		if (optPos->npc)		continue;
		
		// Position und Entfernung checken
		dist = (npc->GetPositionWorld() - optPos->trafo.GetTranslation()).Length2();
		// Nah genug dran ?
		if (dist < minDist) {
			if (!optPos->distance) {
				if (!npc->FreeLineOfSight(optPos->trafo.GetTranslation())) 
				{
					wrongSide = TRUE;
					continue;
				}
			}

			// Falls es ein Spieler ist, 
			// jetzt auch noch die Entfernung zur maximal erlaubten Entfernung checken
			if (npc->IsSelfPlayer()) {
			// FIXME : Ist das ok so ?
			// Wenn keine AI-Befehle vorliegen, muss es der Speiler sein
			// if (npc->GetEM()->IsEmpty(TRUE)) {
				if (!optPos->distance) {
					// [EDENFELD] 1.09
					if (dist > a_fMaxDist) 
					{
						tooFar = TRUE;
						continue;
					}
				}
			}
			// Erst jetzt als gefunden markieren
			found	= optPos;
			minDist = dist;
		}
	}

	//[EDENFELD] 1.09: ScriptFn für "Zu weit weg" oder "Falsche Seite"
	if (!found && npc->IsSelfPlayer() )
	{
		if (tooFar)
		{
			npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, PLAYER_MOB_TOO_FAR_AWAY,-1),npc);
		}
		else if (wrongSide)
		{
			npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, PLAYER_MOB_WRONG_SIDE,-1),npc);
		}
	}
	return found;
}

void oCMobInter :: SetHeading (oCNpc* npc)
{
	zVEC3 pos;
	zREAL winkel,elev;
	// Winkel zwischen PlayerAtVector und anzusteuerndes Object
	npc -> GetAngles	(this, winkel, elev);
	// Winkelgeschwindigkeit 150 Grad/sec
	npc -> RotateWorld	(0,1,0,winkel);
}

void oCMobInter :: SetIdealPosition (oCNpc* npc)
// Set Npc to an Ideal Position
{
	TMobOptPos*	optPos = SearchFreePosition(npc);
	if (optPos) {

		zBOOL move = npc->GetInMovement();
		if (move) npc -> EndMovement();
		// Trafo oder Distance
		if (optPos -> distance) {
			zVEC3 posNpc	= npc -> GetPositionWorld();		posNpc[VY] = 0;
			zVEC3 posMob	= GetPositionWorld();				posMob[VY] = 0;
			zVEC3 posOpt	= optPos -> trafo.GetTranslation(); posOpt[VY] = 0;
			// einzunehmende Distanz
			zREAL dist		= (posOpt - posMob).Length();
//				zCView::StdPrintwin("Distance :"+zSTRING(dist)+"\n");
			// Einheits-Richtungsvektor 
			zVEC3 unit		= (posNpc - posMob).Normalize();

			npc -> SetCollDet(FALSE);
			// Zielposition an NSC-Höhe anpassen.
			posNpc		= GetPositionWorld();
			posNpc[VY]	= npc -> GetPositionWorld()[VY];
			npc	-> SetPositionWorld	(posNpc + unit * dist);
			npc -> SetHeadingYWorld	(this);
			npc -> SetCollDet		(TRUE);

		} else {
			// Hinpoppen
			zVEC3 pos	= optPos -> trafo.GetTranslation();
			pos[VY]		= npc	 -> GetPositionWorld()[VY];

			npc -> SetTrafoObjToWorld	(optPos->trafo);
			npc -> SetPositionWorld		(pos);
			// npc -> ResetXZRotations		();
			// npc->SetOnFloor(pos);
		
		}
		optPos -> npc = npc;	
		if (move) npc->BeginMovement();
	}
}

void oCMobInter :: Reset ()
// In Ausgangsstellung bringen
{
	if (!rewind) {
		
		//[KARK] check, ob es eine T_STAND_2_Sx (x=akt. State) vorhanden ist
		// wenn ja, dann im State verbleiben, wenn nicht, rückspulen auf State 0
		int newState = 0;

		oCNpc *user = dynamic_cast<oCNpc*>(inUseVob);
		if (user && (state > 0) )
		{
			zCModel *userModel = user->GetModel();
			if (userModel)
			{
				zSTRING			newStartAni		= "T_STAND_2_S" + zSTRING(state);
				zTModelAniID	newStartAniID	= userModel->GetAniIDFromAniName(newStartAni);

				// wenn es eine "Stand_2_currentState" Ani gibt, dann verbleibe in diesem State, ansonsten zurücksetzen
				if (newStartAniID != zMDL_ANI_ID_ILLEGAL)
				{
					newState = state;
				}
			}
		}

		zCModel *mobModel = GetModel();
		if (mobModel)
		{
			zSTRING			newMobAni	= "S_S"+zSTRING(newState);
			zTModelAniID	newMobAniID = mobModel->GetAniIDFromAniName(newMobAni);
			mobModel->StartAni(newMobAniID);
		}
		// [BENDLIN] reset state
		state = state_target = newState;
	}
	// [BENDLIN] reset direction
	if (state > 0)
		SetDirection(MOBINTER_DIRECTION_DOWN);
	else
		SetDirection(MOBINTER_DIRECTION_NONE);
}

void oCMobInter :: OnTick()
{
	if (rewind && (npcsCurrent<=0)) {
		
		// Rewind Objects
		npcStateAni = zMDL_ANI_ID_ILLEGAL;
		CheckStateChange(NULL);
		if ((state>0) && CanChangeState(NULL,state,state-1))  {
			SendStateChange(state,state-1);
		}
		if (IsInState(NULL,0)) SetSleeping(TRUE);
	}
}

// ***********************************************************************************
// Interactions-Schema
// ***********************************************************************************

void oCMobInter :: OnTrigger(zCVob *otherVob, zCVob* vobInstigator)
{
	if (otherVob)	zERR_MESSAGE(7,0,"B: MobInter Trigger from "+otherVob->GetVobName());
	else			zERR_MESSAGE(7,0,"B: MobInter Trigger");

	if (!otherVob && !vobInstigator) {
		// Von "aussen" manipuliert -> Mobsi - TA.
		if ((state == 0) && (this->npcsCurrent<=0)) {
			state = state_target = 1;
			if (GetModel()) GetModel()->StartAni("S_S1");
			
		}
	}

	if (triggerTarget.IsEmpty()) return;

	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) {
		
		zERR_MESSAGE(7,0,"B: MobInter Trigger Target "+targetVobList[i]->GetVobName());

		if (vobInstigator) {
			// TA schickt Message -> vobInstigator NSC (?) selbst
			targetVobList[i]->GetEM()->OnTrigger (this,vobInstigator); // erster Parameter ist this nicht othervob
		} else {
			// TA schickt Message -> vobInstigator Vob selbst
			targetVobList[i]->GetEM()->OnTrigger (this,this); // erster Parameter ist this nicht othervob
		}
	};
}

void oCMobInter :: OnUntrigger(zCVob *otherVob, zCVob* vobInstigator)
{
	if (otherVob)	zERR_MESSAGE(7,0,"B: MobInter Untrigger from "+otherVob->GetVobName());
	else			zERR_MESSAGE(7,0,"B: MobInter Untrigger");


	if (!otherVob && !vobInstigator) {
		// Von "aussen" manipuliert -> Mobsi - TA.
		if ((state == 1) && (this->npcsCurrent<=0)) {
			state = state_target = 0;
			if (GetModel()) GetModel()->StartAni("S_S0");
		}
	}

	if (triggerTarget.IsEmpty()) return;

	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) 
	{
		zERR_MESSAGE(7,0,"B: MobInter Untrigger Target "+targetVobList[i]->GetVobName());

		targetVobList[i]->GetEM()->OnUntrigger (this,vobInstigator); // erster Parameter ist this nicht othervob
	};
}

void oCMobInter :: SendStateChange(int from, int to)
{
	zBOOL send = FALSE;
	// Kann Nachricht verschickt werden ?
//	if (!IsKeyStateReady(from,to)) return;
	
	// Allen NSCs die Nachricht schicken.
	zCList<TMobOptPos>* data	= optimalPosList.GetNextInList();		
	zCPlayerInfo* playerInfo	= NULL;
	zCVob* owner				= NULL;
	if (GetEM()->GetNetVobControl(TRUE)) 
	{
		playerInfo = GetEM()->GetNetVobControl(TRUE)->GetCtrlPlayer();	
		if (playerInfo) owner = playerInfo->GetPlayerVob();
	}
	while (data) {
		TMobOptPos* optPos	= data->GetData();
		if (optPos->npc) {
			oCMobMsg* msg	= zNEW( oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE,optPos->npc) );
			msg->from = from; msg->to = to;
			GetEM()->OnMessage(msg,dynamic_cast<oCNpc*>(owner));								
			send = TRUE;
		}
		data = data->GetNextInList();
	}
	if (!send) {
		// Auch verschicken, falls kein NSC am Zustandswechsel beteiligt war
		oCMobMsg* msg	= zNEW( oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE,NULL) );
		msg->from = from; msg->to = to;
		GetEM()->OnMessage(msg,dynamic_cast<oCNpc*>(owner));									
	}
}

void oCMobInter :: SendEndInteraction(oCNpc* npc, int from, int to)
{
	// Nur an den betreffenden NSc schicken ?!.
	oCMobMsg* msg = zNEW( oCMobMsg(oCMobMsg::EV_ENDINTERACTION,npc) );
	msg->from = from; msg->to = to; msg->playAni = TRUE;
	GetEM()->OnMessage(msg,npc);								
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCMobInter::Interact
//
//	2002-05-11	[BENDLIN]
//
//				Interact-MOBs haben jetzt eine Benutzungs-Richtung.
//				Ueber diese wurde das Durchlaufen der einzelnen Stufen
//				soweit automatisiert, dass nur noch einmal ACTION
//				notwendig ist, um alle Stufen in einer Richtung zu
//				Durchlaufen.
//				Die Richtungstasten GAME_UP und GAME_DOWN erzwingen aber
//				weiterhin eine Richtung (UP wenn toggled).
//				Wenn ACTION nicht mehr aktiviert ist, dann wird beim
//				Erreichen der letzten Stufe auch die Interaktion mit
//				dem MOB beendet.
//
////////////////////////////////////////////////////////////////////////////////

void oCMobInter :: Interact (oCNpc* npc, zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right)
{
	CheckStateChange(npc);
	if (!IsInteractingWith(npc)) return;

	// [Kark]: 1.09 Sequel, Check um Spieler per AI_UseMob abmelden zu können
	// if (npc->IsMovLock()) return;
	if ( !npc->IsAPlayer() )
	{
		if ( npc->IsMovLock() )
		{
			return;
		}
	}

	
	// AniEvents ausführen -> InteractItem einfügen / entfernen etc.
	npc -> DoDoAniEvents();

	if ( (state >= 0) && (npcsCurrent >= npcsNeeded) )
	{
		// ACTION
		if ( action && !up && !down )
		{
			if ( GetDirection() == MOBINTER_DIRECTION_NONE )
			{
				if ( (state > 0) && (state < state_num) && CanChangeState(npc, state, state + 1) )
				{
					SendStateChange(state, state + 1);
					SetDirection(MOBINTER_DIRECTION_UP);
					return;
				}
			}
			if ( (state == state_num) && (GetDirection() == MOBINTER_DIRECTION_UP) && !CanChangeState(npc, state, -1) )
			{
				if ( CanChangeState(npc, state, state - 1) && zinput->GetToggled(GAME_ACTION) )
				{
					// goin' states back
					SendStateChange(state, state - 1);
					SetDirection(MOBINTER_DIRECTION_DOWN);
					return;
				}
			}
		}

		if ( !npc->inventory2.IsOpen() )
		{

			// UP/DOWN
			if ( up )
			{
				if ( (state == state_num) )
				{
					if ( CanChangeState(npc, state, -1) )
					{
						EndInteraction(npc, TRUE);
						return;
					}
					else if ( CanChangeState(npc, state, state - 1) )
					{
						// goin' states back
						SendStateChange(state, state - 1);
						SetDirection(MOBINTER_DIRECTION_DOWN);
						return;
					}
				}
				else if ( CanChangeState(npc, state, state + 1) && zinput->GetState(GAME_UP) && zinput->GetToggled(GAME_UP) )
				{
					SendStateChange(state, state + 1);
					SetDirection(MOBINTER_DIRECTION_UP);
					return;
				}
			}
			if ( down )
			{
				if ( (state == 0) && CanChangeState(npc, state, -1) )
				{
					EndInteraction(npc, TRUE);
				}
				else if ( CanChangeState(npc, state, state - 1) )
				{
					SendStateChange(state, state - 1);
					SetDirection(MOBINTER_DIRECTION_DOWN);
				}
				return;
			}

			// AUTO-STATE-CHANGE
			if ( GetDirection() == MOBINTER_DIRECTION_UP )
			{
				if ( (state == state_num) && CanChangeState(npc, state, -1) )
				{
						EndInteraction(npc, TRUE);
				}
				else if ( CanChangeState(npc, state, state + 1) )
				{
					SendStateChange(state, state + 1);
				}
				return;
			}
			else if ( GetDirection() == MOBINTER_DIRECTION_DOWN )
			{
				if ( (state == 0) && CanChangeState(npc, state, -1) )
				{
					EndInteraction(npc, TRUE);
				}
				else if ( CanChangeState(npc, state, state - 1) )
				{
					SendStateChange(state, state - 1);
				}
				return;
			}
		}
	}
}

void oCMobInter :: GetTransitionNames(int from, int to, zSTRING& mobAni, zSTRING& npcAni)
{
	if (to==-1) {
		mobAni	 = "";
		npcAni	 = "T_"+GetScemeName()+"_S"+zSTRING(from)+"_2_STAND";
		return;
	}
	mobAni	 = "T_S"+zSTRING(from)+"_2_";
	npcAni	 = "T_"+GetScemeName()+"_S"+zSTRING(from)+"_2_";
	mobAni  += "S"+zSTRING(to);
	npcAni  += "S"+zSTRING(to);
}

zBOOL oCMobInter :: IsInState (oCNpc* npc, int snr)
{
	zCModel *mobModel	 = GetModel();
	zCModel *npcModel	 = NULL;
	if (npc) npcModel	 = npc -> GetModel();
	else	 npcStateAni = zMDL_ANI_ID_ILLEGAL;

	// 1.Block Bedingungen
	// State == Target
	// Sofern State Anis vorhanden, müssen diese aktiv sein
	if ((state==snr) && (state_target==snr))
	if ((mobStateAni==zMDL_ANI_ID_ILLEGAL) || mobModel->IsAniActive(mobStateAni)) 
	if ((npcStateAni==zMDL_ANI_ID_ILLEGAL) || npcModel->IsAniActive(npcStateAni)) {
		return TRUE;
	}
	return FALSE;
};

zBOOL oCMobInter :: CanChangeState(oCNpc* npc, int from, int to)
{
	if (IsInState(npc, from)) {
		// Wechsel von 0 nach 1 nur mit entsprechenden InteractItem, sofern gefordert
		if (npc && npc->IsSelfPlayer() && (from==0) && (to>from) && !HasUseWithItem(npc)) return FALSE;			

		// 2.Block Bedingungen
		// Gibt es eine Transition in diesen Zustand ?
		zSTRING mobAni, npcAni;
		GetTransitionNames (from, to, mobAni, npcAni);
		// Wenn nur eine von beiden Anis da ist, dann ist der Zustand erlaubt
		zCModelAni* tAni = GetModel()->GetAniFromAniName(mobAni);
		if (tAni && tAni->GetAniType()!=zMDL_ANI_TYPE_DISABLED) return TRUE;
		tAni = NULL;
		if (npc) tAni = npc->GetModel()->GetAniFromAniName(npcAni);
		if (tAni && tAni->GetAniType()!=zMDL_ANI_TYPE_DISABLED) return TRUE;
		
/*		zTModelAniID mAni	= GetModel() -> GetAniIDFromAniName(mobAni);
		if (mAni!=zMDL_ANI_ID_ILLEGAL) return TRUE;
		zTModelAniID nAni	= zMDL_ANI_ID_ILLEGAL;
		if (npc) nAni		= npc -> GetModel() -> GetAniIDFromAniName(npcAni);
		if (nAni!=zMDL_ANI_ID_ILLEGAL) return TRUE;*/
	}
	return FALSE;	
}

void oCMobInter :: StartStateChange (oCNpc* npc, int from, int to)
// Die entsprechenden Anis starten
{
	// FIXME : Nur wenn entsprechende StateAni läuft starten...
	zTModelAniID tmp	= NULL;
	zCModel* mobModel	= GetModel();
	zCModel* npcModel	= NULL;
	if (npc) npcModel	= npc -> GetModel();
	zSTRING  mobAni, npcAni;

	GetTransitionNames (from,to,mobAni,npcAni);

	mobStateAni = zMDL_ANI_ID_ILLEGAL;
	if (mobModel) 
	{
		if (npc && npc->IsAPlayer()) mobModel->SetTimeScale(1.0f/ztimer.GetMotionFactor());

		tmp = mobModel -> GetAniIDFromAniName(mobAni);
		if ((tmp!=zMDL_ANI_ID_ILLEGAL) && !mobModel->IsAniActive(tmp)) {
			// mobStateAni = tmp->nextAni
			zCModelAni*  nextAni		= mobModel->GetNextAni(mobModel->GetAniFromAniID(tmp));
			if (nextAni) mobStateAni	= nextAni ->GetAniID();
			else		 mobStateAni	= zMDL_ANI_ID_ILLEGAL;
			mobModel -> StartAni (tmp);
			//zerr.Message("U:MI:Start MobAni "+mobAni);
		}
	};

	npcStateAni = NULL;
	if (npcModel) {
		StartTransitionAniNpc(npc,npcAni);
	};
	
	state_target = to;

	// [BENDLIN] Richtung anpassen
	SetDirection(MOBINTER_DIRECTION_NONE);
	if ((from >= 0) && (from <= state_num) && (to >= 0) && (to <= state_num) && (from != to))
	{
		if (from < to)
			SetDirection(MOBINTER_DIRECTION_UP);
		else
			SetDirection(MOBINTER_DIRECTION_DOWN);
	}

	OnBeginStateChange(npc,from,to);
}

void oCMobInter :: StartTransitionAniNpc(oCNpc* npc, const zSTRING& npcAni)
// Gekapselt, da hier AniCombs verwendet werden könnten....
{
	zCModel* npcModel	= npc -> GetModel();
	zTModelAniID tmp	= npcModel -> GetAniIDFromAniName(npcAni);
	zBOOL standAni		= (npcAni.Search("2_STAND")>0);

	if (tmp!=zMDL_ANI_ID_ILLEGAL) {
		zCModelAni*  nextAni		= npcModel->GetNextAni(npcModel->GetAniFromAniID(tmp));
		if (nextAni) npcStateAni	= nextAni ->GetAniID();
		else		 npcStateAni	= zMDL_ANI_ID_ILLEGAL;

		zCModelAni* ani = npcModel->GetAniFromAniID(tmp);
		if (ani->GetAniType()==zMDL_ANI_TYPE_COMB) {
			// ************
			// AniComb ???
			// ************
			
			// a) anvisierte Höhe des Slots schnappen
			zMAT4 trafo = GetTrafoModelNodeToWorld("BIP01 FIRE");
			zVEC3 pos	= trafo.GetTranslation();
			zREAL yk	= pos[VY] - npc->GetPositionWorld()[VY];
			// Now Scale
			yk = (yk + 100) / 200;
			if (yk < 0.0f) yk = 0.0f;
			if (yk > 1.0f) yk = 1.0f;
			
			aniCombHeight = yk;

			npcModel -> StartAni		(tmp);
			npcModel -> SetCombineAniXY	(tmp,0.5,yk);
			//zerr.Message("U:MI:Start NpcAniComb " + npcAni + " YK :"+zSTRING(yk));
		
		} else if (!npcModel->IsAniActive(tmp)) {
		
			npcModel -> StartAni (tmp);
			//zerr.Message("U:MI:Start NpcAni " + npcAni);
		}

		// StandAni (NachfolgeAni) automatisch setzen
		if (standAni) npc->GetAnictrl()->SetNextAni(tmp,npc->GetAnictrl()->_s_walk);

	};		
}

void oCMobInter :: CheckStateChange (oCNpc* npc)
{
	zCModel* mobModel	 = GetModel();
	zCModel* npcModel	 = NULL;
	if (npc) npcModel	 = npc -> GetModel();
	else	 npcStateAni = zMDL_ANI_ID_ILLEGAL;

	// Auf jeden Fall Mob-Interaktion beenden, wenn NSC wieder steht.
	// z.B. Nach S_TRY bei der Kiste
	if (npc && npc->GetAnictrl()->IsStanding()) {
		if (state!=state_target) {
			//zerr.Warning("U:MI:Npc leaves MobInteraction.");
			state = state_target;
		}
		// FALSE = keine EndAni mehr für den NSC spielen, da dieser bereits im StandMode
		EndInteraction(npc,FALSE);
		return;
	}

	/* Debug : Ani-Bug -> Ani laeuft nicht weiter. 
	zCModelAniActive* mobt = mobModel->GetActiveAni(mobModel->GetAniFromAniName("T_S1_2_S2"));
	if (mobt) {
		zerr.Message("U:MOB: Ani T_S1_2_S2 running : frame :"+zSTRING(mobt->GetActFrame()));
		zerr.Message("U:MOB: Ani T_S1_2_S2 running : dir :"+zSTRING(mobt->GetDirection()));
	}
	*/

	if (state!=state_target)
	if ((mobStateAni==zMDL_ANI_ID_ILLEGAL) || mobModel->IsAniActive(mobStateAni)) 
	if ((npcStateAni==zMDL_ANI_ID_ILLEGAL) || npcModel->IsAniActive(npcStateAni)) {
		
		// Hier auf AniCombine testen ?
		if (npcStateAni!=zMDL_ANI_ID_ILLEGAL) {
			zCModelAni* ani = npcModel->GetAniFromAniID(npcStateAni);
			if (ani->GetAniType()==zMDL_ANI_TYPE_COMB) {
				//npcModel -> StartAni		(npcStateAni);
				npcModel -> SetCombineAniXY	(npcStateAni,0.5,aniCombHeight);

				zerr.Message("U:MI:Start NpcAniComb " + ani->GetAniName() + " YK :"+zSTRING(aniCombHeight));
			}
		}
		zerr.Message ("U:MI:Set State to "+zSTRING(state_target));
		if(npc)
		{
			OnEndStateChange(npc,state,state_target);
		}
		else
		{
			zerr.Message("MK:MI: mob->npc = NULL from " + zSTRING(name) );
		}
		state = state_target;
	
	}
}

void oCMobInter :: CallOnStateFunc(oCNpc* npc, int state)
{
	int index = parser.GetIndex(onStateFuncName+"_S"+zSTRING(state));
	if (index>=0) {
		parser.SetInstance	("SELF",npc);
		parser.SetInstance	("ITEM",npc->GetInteractItem());
		parser.CallFunc		(index);
	};
}

void oCMobInter :: SendCallOnStateFunc(oCNpc* npc, int state)
{
	if (!onStateFuncName.IsEmpty()) {
		oCMobMsg* msg	= zNEW( oCMobMsg(oCMobMsg::EV_CALLSCRIPT,npc) );
		msg->to			= state;
		GetEM()->OnMessage(msg,this);
	}
}

void oCMobInter :: OnBeginStateChange(oCNpc* npc, int from, int to)
{
};

void oCMobInter :: OnEndStateChange(oCNpc* npc, int from, int to)
{
	if (to==1) {
		// Trigger it
		OnTrigger(this,npc);		
	} else if (to==0) {
		OnUntrigger(this,npc);
	}
	// Entsprechende Skriptfunktion starten (sofern vorhanden)
	// Nur beim Wechsel in höheren State
	if (from<to)				SendCallOnStateFunc(npc,to);	else
	if ((from==1) && (to==0))	SendCallOnStateFunc(npc,to);
};

void oCMobInter :: InterruptInteraction(oCNpc* npc)
{
	// Optimale Position wieder freigeben
	zCList<TMobOptPos>* data = optimalPosList.GetNextInList();;		
	zVEC3 slotPos		(1.0f,0.0f,0.0f);
	zVEC3 slotHeading	(1.0f,0.0f,0.0f);
	while (data) {
		TMobOptPos* optPos = data->GetData();
		if (optPos->npc == npc) {
			slotPos		= optPos->trafo.GetTranslation	();
			slotHeading	= optPos->trafo.GetAtVector		();
			optPos->npc = NULL;
			
		}
		data = data->GetNextInList();
	}

	// [BENDLIN] Random und Overlay-Anis aus, wenn diese aktiv sind (activeAnis > 1)
	if (npc->GetModel() && (npc->GetModel()->GetNumActiveAnis() > 1)) npc->GetModel()->StopAnisLayerRange();

	// Und freischalten
	// Patch 1.08 : Damit InteractItems nicht verloren gehen....
	if (npc->GetInteractItem()) {
		npc->PutInInv		(npc->GetInteractItem());
		npc->SetInteractItem(NULL);
	}
	npc->SetInteractMob		(NULL);
	
	// Auf Standardzustand bringen ?
	Reset();
	inUseVob = NULL;

	// Am Schluss wieder geradestehen, weil NSC durch OptimalSlot die Lage verändert haben kann.
	if (npc) {
		npc->ResetXZRotationsWorld();
		// VobFX stoppen
		if (npc->GetModel()) npc->GetModel()->RemoveAllVobFX();

		// Zur Slotposition beamen ?
		if (onInterruptReturnToSlotPos && npc->FreeLineOfSight(slotPos,this)) {
			// Genug Platz
//			npc->SetCollDet			(FALSE);                // [Moos] Kossision deaktivieren sollte nicht mehr nötig sein; das war der "Fliege durch Wand"-Bug
			if (npc->SearchNpcPosition	(slotPos)) {		// Setzt Höhe und checkt auf Platz.
				npc->SetPositionWorld	(slotPos);
			}
			// [TODO-BENDLIN]
			// npc->SetHeadingAtWorld	(-slotHeading);
			npc->SetCollDet			(TRUE);
//			npc->SetSleeping		(FALSE);
		}
		// [BENDLIN] TODO
		// npc->ResetXZRotationsWorld(); // [Moos] 20.12.00 Anpassung an Vob-Änderung
	}

	npcsCurrent--;
	if (npcsCurrent<=0) SetIgnoredByTraceRay(FALSE);  // [Moos] und Kollision wieder ein.
	
	if ((npcsCurrent<=0) && !rewind) SetSleeping(TRUE);
//	zerr.Message("U:MI:Interaction interrupted.");

	RemoveFromIgnoreList	(npc);
};

zBOOL oCMobInter :: IsMultiMob()
// More (N)SCs than 1 needed
{
	return (npcsNeeded>1);
}

zBOOL oCMobInter :: IsAvailable(oCNpc* npc)
// Time Check - jemand anderes schon angemeldet ?
{
	// Für den Spieler gibt es diesen Zeit-Check nicht.
	// nur wichtig, falls sich mehrere NSCs gleichzeitig im Skript anmelden.
	if (npc->IsSelfPlayer()) return TRUE;
	
	// FIXME : Hier muss noch was rein, falls es doch MultiUserMobs geben soll
	if (inUseVob && (inUseVob!=npc)) {
		// Zeit ok, oder hat sich da schon jemand angemeldet.
		zREAL nowTime = ztimer.GetTotalTimeF();
		if (nowTime < timerEnd) return FALSE;
	}	
	// Zeit abgelaufen
	inUseVob = NULL;
	return TRUE;
}

void oCMobInter :: MarkAsUsed(zREAL timeDelta, zCVob* vob)
{
	// ab diesen zeitpunkt wieder frei
	timerEnd	= ztimer.GetTotalTimeF() + timeDelta;
	inUseVob	= vob;
}

zBOOL oCMobInter :: CanInteractWith (oCNpc* npc)
{
	// Kann nur funktionieren, wenn Mob noch intakt ist
	if (IsDestroyed()) return FALSE;

	// [EDENFELD] 1.09: Nur 1 NSC pro MOBSI (HACK)
	if (npcsCurrent > 0)
	{
		if (npc->IsSelfPlayer()) 
		{
			npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, PLAYER_MOB_ANOTHER_IS_USING,-1),npc);
		}
		return FALSE;
	}

	// Kann nur dann funktionieren, wenn Mob im Ruhezustand -> Physik ist aus
	if (GetPhysicsEnabled()) return FALSE;

	// Skript - Startbedingung erfüllt ?
/*	if (!conditionFunc.IsEmpty()) {
		// Patch 1.07 : [Wohlers] : Codechange : 13.03.01
		// #4192 Winde lässt sich nicht benutzen 
		// altes Self merken.
		oCNpc* oldSelfNpc		= NULL;
		zCPar_Symbol* sym		= parser.GetSymbol("SELF");
		if (sym) oldSelfNpc		= zDYNAMIC_CAST<oCNpc>((zCVob*)sym->GetInstanceAdr());
		// Neues Self setzen.
		parser.SetInstance("SELF",npc);
		// ConditionFunc ausfuehren.
		zBOOL canUseThis = *(zBOOL*)parser.CallFunc(conditionFunc);
		// Self wieder herstellen.
		parser.SetInstance("SELF",oldSelfNpc);
		// und falls Bedingung nicht erfuellt, wieder raus.
		if (!canUseThis) return FALSE;
		//		[old] : if (!*(zBOOL*)parser.CallFunc(conditionFunc))) return FALSE;
		// Patch 1.07 : [Wohlers] CodeChange End
	}
*/
	// Anmeldung ok ? Kein weiterer hat sich für dieses Objekt entschieden ?
	if (!IsAvailable(npc)) return FALSE;

	zVEC3 pos;
	
	if (GetFreePosition(npc,pos)) {
		zBOOL useIt	 = TRUE;
		int instance = GetUseWithItem();
		
		if (instance>0) {
			useIt = FALSE;

			// ***************************************************
			// NSCs können Mob immer benutzen, 
			// die Schlingels erzeugen einfach das benötigte Item
			// ***************************************************
			zBOOL hasUse = FALSE;
			if (!npc->IsSelfPlayer())
			{
				// [EDENFELD] 1.27 Ein Item muss nicht neu erzeugt werden, wenn der NSC es bereits in der Hand hat.
				// Hier wurde vorher nicht darauf getestet.
				// Die SetInteractItem() Implementation in diesen Fall ist schon seltsam, ein neues InteractItem löscht ein etwaiges altes
				// aus dem Slot falls es die gleiche Instanz ist, OHNE danach das neue InteractItem wieder in den Slot zu packen.
				// vielleicht wäre der bessere Fix das neue auch in den Slot zu packen, aber aus Sicherheitsgründen wird hier statt dessen vermieden, das ein 
				// neues Item erstellt wird, falls bereits eins existiert. [AMEN] 
				// (genauer: Während Mobinteraktionen führte hier der alte Code dazu, das manchmal ein neues IteractItem gesetzt wurde, 
				// obwohl der NSC dieses bereits in der Hand hatte. (Das passierte skurrilerweise dann, wenn z.B. im ZS_PickOre() über ein Wld_IsMobAvailable()
				// alle Mobsis durchgegangen wurden und hier auf CanInteractWith() mit "self" getestet wurde. ARGH²(TM) )
				if (!HasUseWithItem(npc))
				{
					// ********************************
					// Muss Gegenstand erzeugt werden ?
					// ********************************
					zBOOL inMove = npc->GetInMovement();
					if (inMove)
						npc->EndMovement();
	//				oCItem* item = npc->IsInInv(instance);
					
					// Patch 1.07
					oCItem* item = npc->RemoveFromInv(instance, 1);
					if (item)
					{
						// Patch 1.07
						item->AddRef();
					}
					else
					{
						// Patch 1.07
						item = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,instance);

	//					oCItem *newitem = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,instance);
	//					item = npc->PutInInv(newitem);
	//                  newitem->Release();                                                         // [Moos] Leakfix
					}		
					npc->SetInteractItem(item);
					// Patch 1.07
					zRELEASE(item);
					if (inMove)
						npc->BeginMovement();
				}
				else
				{
					hasUse = TRUE;
					useIt  = TRUE;
				}
			}
	
			if (!hasUse) useIt = HasUseWithItem(npc);
		} 

		if (!useIt && npc->IsSelfPlayer()) {
			// Ne ne
			if( !npc->GetModel()->IsAniActive( "T_DONTKNOW" ) )
			// npc -> GetEM() -> OnMessage(zNEW( oCMsgConversation(oCMsgConversation::EV_PLAYANI,"T_DONTKNOW")),npc);

			// Meldung ausspucken: "Geht nich, Item fehlt."
			npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, PLAYER_MOB_MISSING_ITEM,-1),npc);
		}
	
		// Patch 1.08 - Die ConditionFunc erst ganz als letztes abfragen
		// Skript - Startbedingung erfüllt ?
		if (useIt && !conditionFunc.IsEmpty()) {
			// Patch 1.07 : [Wohlers] : Codechange : 13.03.01
			// #4192 Winde lässt sich nicht benutzen 
			// altes Self merken.
			oCNpc* oldSelfNpc		= NULL;
			zCPar_Symbol* sym		= parser.GetSymbol("SELF");
			if (sym) oldSelfNpc		= zDYNAMIC_CAST<oCNpc>((zCVob*)sym->GetInstanceAdr());
			// Neues Self setzen.
			parser.SetInstance("SELF",npc);
			// ConditionFunc ausfuehren.
			zBOOL canUseThis = *(zBOOL*)parser.CallFunc(conditionFunc);
			// Self wieder herstellen.
			parser.SetInstance("SELF",oldSelfNpc);
			// und falls Bedingung nicht erfuellt, wieder raus.
			if (!canUseThis) return FALSE;
			//		[old] : if (!*(zBOOL*)parser.CallFunc(conditionFunc))) return FALSE;
			// Patch 1.07 : [Wohlers] CodeChange End
		}		
		
		return useIt;
	
	} else if (npc->IsSelfPlayer()) {

		if( !npc->GetModel()->IsAniActive( "T_DONTKNOW" ) )
		{
			// npc -> GetEM() -> OnMessage(zNEW(oCMsgConversation(oCMsgConversation::EV_PLAYANI,"T_DONTKNOW")),npc);	
			// [TODO-BENDLIN] Hier Meldung ausspucken: "Da ist schon jemand anderes dran."
		}
	}
	return FALSE;
}

zBOOL oCMobInter :: IsInteractingWith (oCNpc* npc)
{
	// Slots nach entsprechenden NSC durchsuchen
	zCList<TMobOptPos>* data = optimalPosList.GetNextInList();;		
	while (data) {
		TMobOptPos* optPos = data->GetData();
		if (optPos->npc == npc) return TRUE;
		data = data->GetNextInList();
	}
	return FALSE;
}

void oCMobInter :: StartInteraction(oCNpc* npc)
// NPC from Stand zum aktuellen Zustand
{
		if (IsInteractingWith(npc)) return;

		mobStateAni		= zMDL_ANI_ID_ILLEGAL;
		npcStateAni		= zMDL_ANI_ID_ILLEGAL;

		// Und anmelden
		npc->SetInteractMob	(this);
		
		// Collision aus
		SetIgnoredByTraceRay(TRUE);
		//npc->SetCollDet(FALSE);
		//SetCollDet(FALSE);
		//InsertInIgnoreList(npc);
		
		// Turn Anis aus
		npc->GetAnictrl()->StopTurnAnis();

		// Positionieren
		ScanIdealPositions	();	
		SetIdealPosition	(npc);

		zCModel* n = npc -> GetModel();
		if (n) {
			// Aufwachen !
			n -> StartAni	("T_"+GetScemeName()+"_STAND_2_S"+zSTRING(state));
			npcStateAni		= n -> GetAniIDFromAniName("S_"+GetScemeName()+"_S"+zSTRING(state));
		}
		SetPhysicsEnabled	(FALSE);
		SetSleeping			(FALSE);
		
		// BodyState ermitteln
		SetMobBodyState		(npc);
		
		npcsCurrent++;

		// TEMP : test
		// npc->SetCollDet		(FALSE);

//		zerr.Message("U:MI:Interaction on.");

		// set direction depending on mob state
		if ( state == state_num )
		{
			SetDirection(MOBINTER_DIRECTION_DOWN);
		}
		else if ( state >= 0 ) 
		{
			SetDirection(MOBINTER_DIRECTION_UP);
		}
}

void oCMobInter :: EndInteraction(oCNpc* npc, zBOOL playEndAni)
{
	// Weg nach Stand von aktuellem State ?
	if (playEndAni) {
		zCModel* model = npc->GetModel();
		if (model && !model->IsAniActive(npc->GetAnictrl()->_s_walk)) {

			zSTRING npcAni = "T_"+GetScemeName()+"_S"+zSTRING(state)+"_2_STAND";
			StartTransitionAniNpc(npc,npcAni);
			inUseVob = NULL;
		}
	}
	else
	{
		// [TODO-BENDLIN] FIXME: ABMELDEN!!!
		SendEndInteraction(npc, state, -1);
	}
	// reset Direction flag
	SetDirection(MOBINTER_DIRECTION_NONE);
}

void oCMobInter :: StopInteraction (oCNpc* npc)
{
	if (!IsInteractingWith(npc)) return;

	if (!npc->GetAnictrl()->IsStanding()) {
		
		zSTRING npcAni = "T_"+GetScemeName()+"_S"+zSTRING(state)+"_2_STAND";
		StartTransitionAniNpc(npc,npcAni);
	}
		
	// Optimale Position wieder freigeben
	zCList<TMobOptPos>* data = optimalPosList.GetNextInList();;		
	while (data) {
		TMobOptPos* optPos = data->GetData();
		if (optPos->npc == npc) optPos->npc = NULL;
		data = data->GetNextInList();
	}

	// Am Schluss wieder geradestehen, weil NSC durch OptimalSlot die Lage verändert haben kann.
	if (npc)
	{
		npc->ResetXZRotationsWorld(); // [Moos] 20.12.00 Anpassung an Vob-Änderung
		if (npc->GetModel()) npc->GetModel()->RemoveAllVobFX();  // [EDENFELD] 1.09 beende alle PFX am Model
	}

	// Und freischalten
	if (!rewind) SetSleeping (TRUE);

	// Patch 1.08 : Damit InteractItems nicht verloren gehen....
	if (npc->GetInteractItem()) {
		npc->PutInInv		(npc->GetInteractItem());
		npc->SetInteractItem(NULL);
	}
	npc->SetInteractMob		(NULL);
	npc->SetFocusVob		(NULL); // [Ulf] : Verhindet bei Leitern das sofortige Wiederanmelden
    npc->CheckPutbackTorch  ();     // [Moos] nimm eine abgelegte Fackel wieder in die Hand

	npcsCurrent--;
	// Kollision wieder ein.
	if (npcsCurrent<=0) SetIgnoredByTraceRay(FALSE);
	
	RemoveFromIgnoreList	(npc);

	inUseVob = NULL;

//	zerr.Message("U:MI:Interaction off.");
};

// *************************************
// NSCs benutzen diese Funcs
// *************************************

zBOOL oCMobInter :: AI_UseMobToState(oCNpc* npc, int target)
{
	// Start
	if (!IsInteractingWith(npc) && CanInteractWith(npc)) {
		
		if ( (target>0) || ( (target==0) && (state>0) ) ) {					
			// Auch anmelden moeglich, wenn Mobsi wieder in Zustand 0 gebracht werden soll
			// zB.: Wachen schliessen das Tor per Wheel....
			oCMobMsg* msg = zNEW( oCMobMsg(oCMobMsg::EV_STARTINTERACTION,npc) );
			GetEM()->OnMessage(msg,npc);						
			return FALSE;
		}
	}

/*	// old implementation
	if ((target>0) && !IsInteractingWith(npc) && CanInteractWith(npc)) {
		oCMobMsg* msg = zNEW( oCMobMsg(oCMobMsg::EV_STARTINTERACTION,npc) );
		GetEM()->OnMessage(msg,npc);						
		return FALSE;
	}
*/	
	if (target>=state_num) target = state_num;
	
	// End Reached
	if (target==-1) {
		if (npc->GetAnictrl()->IsStanding()) {
			if ((state==0) || (state==state_num)) {
				// Be sure to end it
				// Jawoll und aktivieren
				oCMobMsg* msg = zNEW( oCMobMsg(oCMobMsg::EV_ENDINTERACTION,npc) );
				msg->from = state; msg->to = -1; msg->playAni = FALSE;
				GetEM()->OnMessage(msg,npc);						
				return TRUE;
			}
		}
		// Von diesem Zustand Wechsel nach Stand möglich ?
		if ((state>0) && IsInState(npc,state)) {
			if (CanChangeState(npc,state,-1)) {
				// Jawoll und aktivieren
				oCMobMsg* msg = zNEW( oCMobMsg(oCMobMsg::EV_ENDINTERACTION,npc) );
				msg->from = state; msg->to = -1; msg->playAni = TRUE;
				GetEM()->OnMessage(msg,npc);						
				return FALSE;
			}
		}
	}

	if (IsInteractingWith(npc)) {
		CheckStateChange(npc);
		if (IsInState(npc,target)) return TRUE;
		zBOOL action = !((state==0) && (target==-1));
		Interact(npc,action,(state<target),(state>target),FALSE,FALSE);

	} else if ((target==-1) && (state==target)) {
		return TRUE;
	}
	
	return FALSE;
}

// *************************************
// Archive / Unarchive
// *************************************

void oCMobInter :: Archive	(zCArchiver &arc)
{
	oCMOB :: Archive(arc);

	// Internals
	// if (npcsCurrent) { state = 0; state_target = 0; };
	
	if (!arc.InProperties()) {
//		arc.WriteInt		("state"		,state);
//		arc.WriteInt		("stateTarget"	,state_target);
		arc.WriteInt		("stateNum"		,state_num);
	};
	arc.WriteString			("triggerTarget",triggerTarget);
	arc.WriteString			("useWithItem"  ,useWithItem);
	arc.WriteString			("conditionFunc",conditionFunc);
	arc.WriteString			("onStateFunc"  ,onStateFuncName);
	arc.WriteBool			("rewind"		,rewind);
}

/*--------------------------------------------------------------------------

	void oCMobInter :: Unarchive(zCArchiver &arc)

 

    18-10-00       [Dennis]

					state = 0 standard

--------------------------------------------------------------------------*/
void oCMobInter :: Unarchive(zCArchiver &arc)
{
	oCMOB :: Unarchive(arc);
	
	if (!arc.InProperties()) {
		// Internals
//		arc.ReadInt	("state"		,state);
//		arc.ReadInt	("stateTarget"	,state_target);
		arc.ReadInt	("stateNum"		,state_num);
	};
	arc.ReadString	("triggerTarget",triggerTarget);
	arc.ReadString  ("useWithItem"  ,useWithItem);
	arc.ReadString	("conditionFunc",conditionFunc);
	arc.ReadString	("onStateFunc"  ,onStateFuncName);
	arc.ReadBool	("rewind"		,rewind);

	Reset();
}

// ************************************************************************************
// Feuriooooo
// ************************************************************************************

oCMobFire :: oCMobFire()
{
	mobStateAni		= zMDL_ANI_ID_ILLEGAL;
	npcStateAni		= zMDL_ANI_ID_ILLEGAL;

	fireVobtree		= NULL;
	
	fireSlot		= "BIP01 FIRE";
	fireVobtreeName	= "FIRETREE_LARGE.ZEN";
}

oCMobFire :: ~oCMobFire()
{
	DeleteEffects();
	// Habe hioer nur Referenz auf Base-Vob, nicht mehr auf ganzen Vobtree (siehe OnTrigger).
	zRELEASE(fireVobtree);
}

void oCMobFire :: DeleteEffects ()
{
	// Particle - Effects löschen
	if (fireVobtree && fireVobtree->GetHomeWorld()) {
		fireVobtree->GetHomeWorld()->RemoveVobSubtree(fireVobtree);
		// FireVobtree bleibt im Speicher -> mit AddRef gecached...
		// darum kein "fireVobtree = NULL" Befehl.
	}
	zRELEASE(fireVobtree);
}

void oCMobFire :: OnDamage	(zCVob* otherVob, zCVob* inflictorVob, zREAL damage, int damageType, const zVEC3& hitLocation)
{
	zBOOL bDoesFireDamage  = ( ( damageType & oEDamageType_Fire ) == oEDamageType_Fire );
		  bDoesFireDamage &= ( damage > 0 );
		  
	if ( bDoesFireDamage )	GetEM()->OnTrigger(otherVob, inflictorVob);
}

void oCMobFire :: OnEndStateChange	(oCNpc* npc, int from, int to)
{
	oCMobInter::OnEndStateChange(npc,from,to);
	
	// Feuereffekt an/aus
	if (to == 1) OnTrigger	(npc,npc);	else
	if (to == 0) OnUntrigger(npc,npc);
}

void oCMobFire :: OnTrigger (zCVob* otherVob, zCVob* vobInstigator)
{
	if (state==0) {
		
		// Set to State 1
		state = 1; state_target = 1;

		if (GetHomeWorld()) {

			zBOOL inMovement	= FALSE;
			if (otherVob) {
				inMovement		= otherVob->GetInMovement();
				if (inMovement)	otherVob -> EndMovement	();
			}

			if (!fireVobtree) {
				// laden das Teil
				zoptions->ChangeDir(DIR_WORLD);
				if (fireVobtreeName.IsEmpty()) fireVobtreeName = "FIRETREE_SMALL.ZEN";
				fireVobtree	= GetHomeWorld() -> MergeVobSubtree (fireVobtreeName);
				// cachen den Kram
				if (fireVobtree) {
					fireVobtree-> AddRefVobSubtree(FALSE);			// the lights in the zen can't move -> optimize
					// entfernen...
					if (fireVobtree->GetHomeWorld()) {
						fireVobtree->GetHomeWorld()->RemoveVobSubtree(fireVobtree);
					}
				}
				// In Welt setzen und positionieren
				if (fireVobtree) {
					zVEC3 pos = GetTrafoModelNodeToWorld(fireSlot).GetTranslation();
					fireVobtree -> SetPositionWorld	(pos);
					if (!fireVobtree->GetHomeWorld()) {
						GetHomeWorld()->AddVobAsChild(fireVobtree,this);
					}
					// Jetzt nur ein AddRef auf BaseVob 
					fireVobtree -> AddRef();
					// hier den Tree wieder releasen -> ich behalte nur noch Ref auf BaseVob
					fireVobtree -> ReleaseVobSubtree();
				}			
			} else {
			
				// FireVobtree ist schon da....
				// In Welt setzen und positionieren
				zVEC3 pos = GetTrafoModelNodeToWorld(fireSlot).GetTranslation();
				if (!fireVobtree->GetHomeWorld()) {
					GetHomeWorld()->AddVobAsChild(fireVobtree,this);
				}
				fireVobtree -> SetPositionWorld	(pos);			
			}

			if (otherVob && inMovement) otherVob->BeginMovement();
		}
	}
}

void oCMobFire :: OnUntrigger(zCVob* otherVob, zCVob* vobInstigator)
{
	if (state==1) {
		DeleteEffects();
		state = 0; state_target = 0;
	}
}

void oCMobFire :: PreSave()
{
	// oCMobInter :: PreSave();

	// Falls Vobtree da, diesen kruzzeitig entfernen -> nicht mitspeichern
	if (GetState()==1) DeleteEffects();	
};

void oCMobFire :: Archive (zCArchiver &arc)
{	
	oCMobInter :: Archive (arc);

	arc.WriteGroupBegin	("Fire");
	arc.WriteString		("fireSlot"			,fireSlot);
	arc.WriteString		("fireVobtreeName"	,fireVobtreeName);
	arc.WriteGroupEnd	("Fire");

	if (!arc.InSaveGame()) return;
	// Diesen Teil nur im SaveGame ausführen
	// Save Contents
	// [...]
}

void oCMobFire :: PostSave()
{
	// oCMobInter :: PostSave();

	// und Vobtree hier wieder einfuegen
	if (GetState()==1) {
		state = 0;
		OnTrigger(this,this);
	}
};

void oCMobFire :: Unarchive (zCArchiver &arc)
{
	oCMobInter :: Unarchive (arc);

	arc.ReadString		("fireSlot"			,fireSlot);
	arc.ReadString		("fireVobtreeName"	,fireVobtreeName);
}

// ************************************************************************************
// Bed
// ************************************************************************************

oCMobBed :: oCMobBed ()
{
	sceme		= "BED";
	addName		= "FRONT";
	state_num	= 1;
};

oCMobBed :: ~oCMobBed ()
{
};

void oCMobBed :: StartInteraction(oCNpc* npc)
{
	oCMobInter :: StartInteraction(npc);
}

void oCMobBed :: OnBeginStateChange	(oCNpc* npc, int from, int to)
{
	oCMobInter::OnBeginStateChange(npc,from,to);
}

void oCMobBed :: OnEndStateChange		(oCNpc* npc, int from, int to)
{
	oCMobInter::OnEndStateChange(npc,from,to);
	if (to==0) {
		// Aufstehen => Aufwachen
		// FIXME : Hier noch Perception setzen ? 
		// Eigentlich -> sollte durch Skriptfunktion anschliessend 
		// wieder auf Default gesetzt werden 
		// z.B. Tagesablauf
	}
}

zSTRING oCMobBed :: GetScemeName()
{
	return sceme + "_" + addName;
}

TMobOptPos* oCMobBed :: SearchFreePosition(oCNpc *npc, zREAL maxDist)
{
	TMobOptPos* optPos = oCMobInter::SearchFreePosition(npc, maxDist);
	if (optPos) {
		if (optPos->nodeName.Search("FRONT")>0) addName = "FRONT";
		else									addName = "BACK";
	}
	return optPos;
}

// ************************************************************************************
// Schalter
// ************************************************************************************

oCMobSwitch :: oCMobSwitch ()
{
	sceme		= "LEVER";
	state_num	= 1;			// States 0 und 1
};

oCMobSwitch :: ~oCMobSwitch ()
{	
};

// *************************************
// Archive / Unarchive
// *************************************

void oCMobSwitch :: Archive	(zCArchiver &arc)
{
	oCMobInter :: Archive(arc);
}

void oCMobSwitch :: Unarchive(zCArchiver &arc)
{
	oCMobInter :: Unarchive(arc);
}

// ************************************************************************************
// Lockable
// ************************************************************************************

oCMobLockable :: oCMobLockable()
{
	locked		= FALSE;
	pickLockNr	= 0;
	autoOpen	= FALSE;
	keyInstance .Clear();
	pickLockStr	.Clear();
}

oCMobLockable :: ~oCMobLockable()
{
}

zBOOL oCMobLockable :: CanInteractWith(oCNpc* npc)
{
	if (oCMobInter::CanInteractWith(npc)) {
		// verschlossen ? Schlüssel oder Picklock ?
		return (CanOpen(npc));
	}
	return FALSE;
}

void oCMobLockable :: Interact (oCNpc* npc, zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right)
{
	int nFuncPickLock = ::parser.GetIndex( "G_PICKLOCK" );

	// Hier ist bereits angemeldet -> State ist "0"
	if (IsInState(npc,0)) {
		if (locked && !down) {
			// passender Schlüssel vorhanden ?
			if (!keyInstance.IsEmpty() && npc->IsInInv(keyInstance)) {
				locked = FALSE;
				oCMobMsg* msg = zNEW( oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE,npc) );
				msg->from = 0; msg->to = 1;
				GetEM()->OnMessage(msg,npc);
				return;
			} else if (left || right) {
				if (zinput->GetToggled(GAME_LEFT) || zinput->GetToggled(GAME_RIGHT) || zinput->GetToggled(GAME_STRAFELEFT) || zinput->GetToggled(GAME_STRAFERIGHT)) {			
					// Lockpicking....
					zBOOL success = FALSE;
					if		(left)	success = PickLock(npc,'L');
					else if (right)	success = PickLock(npc,'R');
					if (success) 
					{
						if ( pickLockNr >= pickLockStr.Length() )	// letztes char ? -> unlock
						{
							locked = FALSE;
							oCMobMsg* msg = zNEW( oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE,npc) );
							msg->from = 0; msg->to = 1;
							GetEM()->OnMessage(msg,npc);
						}
						else
						{
							::parser.SetInstance( "SELF", this );
							::parser.CallFunc	( nFuncPickLock, (int) TRUE, (int) FALSE );
						}

						return;
					}
					else
					{
						int nPercentage = ::zRand( 100 ) + 1;											// [1..100]

//						if  ( nPercentage <= npc->GetTalentValue( oCNpcTalent::NPC_TAL_PICKLOCK ) )
						// [EDENFELD] ab 1.09 wird die Chance aus dem Dexwert ermittelt
						if  ( nPercentage > npc->GetAttribute(::NPC_ATR_DEXTERITY) )
						{
							::parser.SetInstance( "SELF", this );
							::parser.CallFunc	( nFuncPickLock, (int) FALSE, (int) TRUE );

							oCItem* pItem = npc->IsInInv("ITKE_LOCKPICK",1);
							if ( pItem )
							{
								pItem = npc->RemoveFromInv("ITKE_LOCKPICK",1);
								::ogame->GetWorld()->RemoveVob( pItem );
							}
							// [BENDLIN] Sitzen bleiben solange picklocks vorhanden?
							pItem = npc->IsInInv("ITKE_LOCKPICK",1);
							if (!pItem) 
							{
								StopInteraction(npc);
							}
							pickLockNr = 0;
						}
						else
						{
							::parser.SetInstance( "SELF", this );
							::parser.CallFunc	( nFuncPickLock, (int) FALSE, (int) FALSE );
						}
					}
				}
			}
		}
	}

/*
	if ( (!keyInstance.IsEmpty() && npc->IsInInv(keyInstance) || !locked ) && action && up )
	{
		locked = FALSE;
		oCMobMsg* msg	= zNEW( oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE,npc) );
		msg->from = -1; msg->to = 1;
		GetEM()->OnMessage(msg,npc);
		return;
	}

	else if (!(npc->HasTalent(NPC_TAL_PICKLOCK) && npc->IsInInv("ITKELOCKPICK")) && action ) 
	{
		//start ani
		if (up) npc->GetModel()->StartAni("T_DONTKNOW");
		return;
	}
		
	if (action && IsInState(npc,0)) {
		if (left || right) {
			if (zinput->GetToggled(GAME_LEFT) || zinput->GetToggled(GAME_RIGHT)) {			
				if (locked) {
					GetEM()->OnMessage(zNEW( oCMobMsg(oCMobMsg::EV_UNLOCK,npc,left)), npc);			
					return;
				} else {
					GetEM()->OnMessage(zNEW( oCMobMsg(oCMobMsg::EV_LOCK,npc)), npc);
					return;
				}
			}
		} else if (!locked && autoOpen) {

			// Gerade ge"picklocked", dann automatisch öffnen
			oCMobMsg* msg = zNEW( oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE,npc) );
			msg->from = 0; msg->to = 1;
			GetEM()->OnMessage(msg,npc);								
			autoOpen = FALSE;
			return;			
		}
	
	} else if (IsInState(npc,1) && items && !items->IsOpen()) {
	
		// Falls Inventory nicht mehr sichtbar, Zustand nach 0 wechseln....
		oCMobMsg* msg	= zNEW( oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE,npc) );
		msg->from = 1; msg->to = 0;
		GetEM()->OnMessage(msg,npc);								
		return;			
	}*/

	oCMobInter :: Interact (npc, action, up, down, left, right);
}

zBOOL oCMobLockable :: CanChangeState(oCNpc* npc, int from, int to)
{
	// Standard Bedingung testen
	if (!oCMobInter::CanChangeState(npc,from,to)) return FALSE;
	// Spezielle Lockable Bedingung
	if ((from==0) && (to==1)) {
		return (!locked);
	}
	return TRUE;
}

void oCMobLockable :: OnEndStateChange(oCNpc* npc, int from, int to)
{
	// Standardtrigger
	oCMobInter :: OnEndStateChange(npc,from,to);

	if (to == 1) {
		Open(npc);
		zerr.Message("U:MI:Offen.");
	} else if (to==0) {
		Close(npc);
		zerr.Message("U:MI:Geschlossen.");
	}
};

zBOOL oCMobLockable :: CanOpen(oCNpc* npc)
{
	zBOOL	haveKey			= TRUE,
			haveLockPick	= TRUE;
	if (locked) 
	{
		// [KARK] 2002-05-11
		haveKey			= !keyInstance.IsEmpty() && npc->IsInInv(keyInstance);
		haveLockPick	= !pickLockStr.IsEmpty() && (npc->IsInInv("ITKE_LOCKPICK") != NULL);
		zBOOL canSteal  = npc->HasTalent(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_PICKLOCK);

		// Wenn Schlüssel oder Dietrich vorhanden dann kann mans mal versuchen
		if (haveKey || (haveLockPick && npc->HasTalent(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_PICKLOCK)))
		{
			return TRUE;
		}

		// 4 "Truhenfälle"
		/*
			1. Truhe hat einen Key UND eine picklock kombination
			2. Truhe hat einen Key UND KEINE picklock kombination
			3. Truhe hat keinen Key UND eine picklock kombination
			4. Truhe hat keinen Key UND keine picklock kombination

			Funcs:
				PLAYER_MOB_MISSING_KEY_OR_LOCKPICK
				PLAYER_MOB_MISSING_KEY
				PLAYER_MOB_MISSING_LOCKPICK
				PLAYER_MOB_NEVER_OPEN
		*/

		int refuseActionFunc = -1;


		if (!keyInstance.IsEmpty() && !pickLockStr.IsEmpty())
		{
			// ich brauche nen schlüssel oder dietrich
			if (haveLockPick && !canSteal)
			{
				refuseActionFunc = parser.GetIndex(PLAYER_MOB_MISSING_KEY);
			}
			else
			{
				refuseActionFunc = parser.GetIndex(PLAYER_MOB_MISSING_KEY_OR_LOCKPICK);
			};
		} 
		if (!keyInstance.IsEmpty() && pickLockStr.IsEmpty() )
		{
			// da brauch ich auf jeden fall den richtigen schlüssel
			refuseActionFunc = parser.GetIndex(PLAYER_MOB_MISSING_KEY);
		}
		if (keyInstance.IsEmpty() && !pickLockStr.IsEmpty() )
		{
			// gibt keinen Schlüssel, die MUSS ich knacken
			refuseActionFunc = parser.GetIndex(PLAYER_MOB_MISSING_LOCKPICK);
		}
		if (keyInstance.IsEmpty() && pickLockStr.IsEmpty() )
		{
			// die krieg ich nie auf
			refuseActionFunc = parser.GetIndex(PLAYER_MOB_NEVER_OPEN);
		}
		if (refuseActionFunc != -1)
		{
			npc->GetEM(TRUE)->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, refuseActionFunc),this);
		}
		else
		{
			npc -> GetEM() -> OnMessage(zNEW( oCMsgConversation(oCMsgConversation::EV_PLAYANI,"T_DONTKNOW")),npc);
		}
		return FALSE;
	}
	return TRUE;
}

zBOOL oCMobLockable :: PickLock (oCNpc* npc, const char pickLockChar)
{
	zBOOL bDoesMatch = FALSE;
	// int nFuncPickLock = ::parser.GetIndex( "G_PICKLOCK" );

	if (pickLockStr.Length()>0) {
		if (pickLockNr<pickLockStr.Length()) {
			bDoesMatch = pickLockStr[pickLockNr]==pickLockChar;
			// Noch was zu knacken...	
			if ( bDoesMatch ) 
			{
				// Success....
				pickLockNr ++;

				// ::parser.SetInstance( "SELF", this );
				// ::parser.CallFunc	( nFuncPickLock, (int) TRUE, (int) FALSE );
			} else 
			{
				// Failure....
				pickLockNr = 0;

				// ::parser.SetInstance( "SELF", this );
				// ::parser.CallFunc	( nFuncPickLock, (int) FALSE, (int) FALSE );
			}	
			
			// Play Anis
			if (npc->GetModel()) {
				if (pickLockChar=='L')		npc	-> GetModel() -> StartAni ("T_"+GetScemeName()+"_S0_PICKLEFT");
				else						npc	-> GetModel() -> StartAni ("T_"+GetScemeName()+"_S0_PICKRIGHT");
			}
		}
	}
	return bDoesMatch;
}

void oCMobLockable :: Unlock (oCNpc* npc, zBOOL left)
{
	zBOOL success = FALSE;
	int nFuncPickLock = ::parser.GetIndex( "G_PICKLOCK" );

	if (locked) {
		zCModel* mobModel = GetModel();
		zCModel* npcModel = NULL;
		if (npc) npcModel = npc -> GetModel();
		
		// passender Schlüssel vorhanden ?
		if (!keyInstance.IsEmpty() && npc->IsInInv(keyInstance)) {
			success = TRUE;

		} 
		else if (npc->HasTalent(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_PICKLOCK) && npc->IsInInv("ITKE_LOCKPICK")) 
		{
			if		(left)	success = PickLock(npc,'L');
			else			success = PickLock(npc,'R');
			if (success) 
			{
				if ( pickLockNr >= pickLockStr.Length() )	// letztes char ? -> unlock
				{
					autoOpen = TRUE;

					::parser.SetInstance( "SELF", this );
					::parser.CallFunc	( nFuncPickLock, (int) TRUE, (int) TRUE );
				}
				else
				{
					::parser.SetInstance( "SELF", this );
					::parser.CallFunc	( nFuncPickLock, (int) TRUE, (int) FALSE );
				}

				return;
			}
			else
			{
				int nPercentage = ::zRand( 100 ) + 1;											// [1..100]

//				if  ( nPercentage <= npc->GetTalentSkill( oCNpcTalent::NPC_TAL_PICKLOCK ) )
				// [EDENFELD] neu 1.09 Unlock Success wird nun aus dem DEX Wert erwürfelt (ehemals über Picklock Talent Skill)

				if  ( nPercentage > npc->GetAttribute(::NPC_ATR_DEXTERITY) )			
				{
					::parser.SetInstance( "SELF", this );
					::parser.CallFunc	( nFuncPickLock, (int) FALSE, (int) TRUE );

					oCItem* pItem = npc->IsInInv("ITKE_LOCKPICK");
					if ( pItem )
					{
						npc->RemoveFromInv( pItem );
						::ogame->GetWorld()->RemoveVob( pItem );
					}
					StopInteraction(npc);
					pickLockNr = 0;
				}
				else
				{
					::parser.SetInstance( "SELF", this );
					::parser.CallFunc	( nFuncPickLock, (int) FALSE, (int) FALSE );
				}
			}
		} 
		else 
		{
			::parser.CallFunc( "G_NOKEY" );

			// Mach nicht auf - Try-Ani
			if (mobModel) {
				mobModel->StartAni("T_S0_TRY");
				//zERR_MESSAGE(5,0,"U: MOBI: T_S0_TRY");
			}
			if (npcModel) {
				zTModelAniID ani = npcModel->GetAniIDFromAniName("T_"+GetScemeName()+"_S0_TRY");
				// Diese Ani wechselt in den Stand -> Ende der MobInteraction
				if (ani!=zMDL_ANI_ID_ILLEGAL) {
					npcModel-> StartAni	 (ani);
					npc		-> GetAnictrl()->SetNextAni(ani,npc->GetAnictrl()->_s_walk);
				}
			}
		}

		if (success) {
			// Mach auf den Kram
			if (mobModel) {
				mobModel->StartAni("T_S0_UNLOCK");
				//zERR_MESSAGE(5,0,"U: MOBI: T_S0_UNLOCK");
			}
				
			if (npcModel) 
				npcModel->StartAni("T_"+GetScemeName()+"_S0_UNLOCK");
			locked = FALSE;		
		}
	}
}

void oCMobLockable :: Lock (oCNpc* npc)
{
	if (!locked) {
		// Nur mit passendem Schlüssel
		if (!keyInstance.IsEmpty() && npc->IsInInv(keyInstance)) {
			zCModel* mobModel = GetModel();
			zCModel* npcModel = npc->GetModel();
			if (mobModel) mobModel->StartAni("T_S0_LOCK");
			if (npcModel) npcModel->StartAni("T_"+GetScemeName()+"_S0_LOCK");
			locked = TRUE;
			//zERR_MESSAGE(5,0,"U: MOBI: T_S0_UNLOCK");
		}				
	}
}

void oCMobLockable :: Archive	(zCArchiver &arc)
{
	oCMobInter :: Archive(arc);

	arc.WriteGroupBegin	("Lockable");
	arc.WriteBool		("locked"		,locked);
	arc.WriteString		("keyInstance"	,keyInstance);
	arc.WriteString		("pickLockStr"	,pickLockStr);
	arc.WriteGroupEnd	("Lockable");
}

void oCMobLockable :: Unarchive(zCArchiver &arc)
{
	oCMobInter :: Unarchive(arc);

    zBOOL tmp;
//	arc.ReadBool	("locked"		,locked);
	arc.ReadBool	("locked"		,tmp);    locked = tmp;

	arc.ReadString	("keyInstance"	,keyInstance);
	arc.ReadString	("pickLockStr"	,pickLockStr);

	// scramle the pickLockStr (optional)
	if (!pickLockStr.IsEmpty() && ogame && ogame->IsInLoadSaveGame())
	{
		// read from INI
		static int picklockScramle = -1;
		if (picklockScramle == -1)
			picklockScramle = zoptions->ReadInt(zOPT_SEC_GAME, "pickLockScramble", 0);
		else if (picklockScramle <= 1)
			return;  // do nothing
		if (picklockScramle <= 1) // there is no need to scramble keys with 1 char :)
			picklockScramle = 0;
		
		// scramble if length is not greater than value
		int length = pickLockStr.Length();
		if ((length > 1) && (length <= picklockScramle))
		{
			zSTRING _pickLockStr = pickLockStr;
			pickLockStr.Clear();
			for (int i = length; i > 1; i--)
			{
				unsigned int pos = zRand(i);
				pickLockStr += _pickLockStr[pos];
				_pickLockStr.Delete(pos, 1);
			}
			pickLockStr += _pickLockStr;
		}
	}
}


// ************************************************************************************
// Chest
// ************************************************************************************

oCMobContainer :: oCMobContainer()
{
	sceme		= "CHEST";
	state_num	= 1;
	items		= NULL;
}

oCMobContainer :: ~oCMobContainer()
{
	// Komplett aus und aus den Listen entfernen !
	zCListSort<oCItem>*	itemNode = containList.GetNextInList();
	oCItem* item	= NULL;
	while (itemNode) {
		item		= itemNode->GetData();
		itemNode	= itemNode->GetNextInList();
		// aus Listen entfernen
		// Leider ist hier die Welt schon innen Arsch gegangen ?!
		//ogame->GetGameWorld()->RemoveFromLists(item);
		if (ogame && ogame->GetWorld())
            ogame->GetWorld()->RemoveVob(item);
/*        else{  
            if (item->GetRefCtr()>0) item->Release(); // [Moos] Leakfix, da die Welt nun beim Verlassen 
            if (item->GetRefCtr()>0) item->Release(); // tatsächlich schon weg ist und item nicht abgemeldet hat.
            } */  // [Moos] Das wird nun korrekter in ~oCWorld erledigt.
	}
	containList.DeleteListDatas();
};

void oCMobContainer :: OnMessage (zCEventMessage *eventMessage, zCVob* sourceVob)
{
	if (dynamic_cast<oCMobMsg*>(eventMessage)) {
		oCMobMsg* mobMsg = (oCMobMsg*)eventMessage;
		//npc = mobMsg->npc;
		switch (mobMsg->GetSubType()) {
			case oCMobMsg::EV_UNLOCK	:	Unlock	(mobMsg->npc,mobMsg->playAni);	break;
			case oCMobMsg::EV_LOCK		:	Lock	(mobMsg->npc);					break;
//			case oCMobMsg::EV_OPEN		:	Open(mobMsg->npc);		break;
		}
	}
	oCMobInter :: OnMessage (eventMessage, sourceVob);
}

void oCMobContainer :: Destroy()
{
	// NOTE : After Destroy the Object may be deleted
	oCMOB :: Destroy();

	// Inhalt fallenlassen.
	zVEC3 pos;
	oCItem* item = NULL;
	zCListSort<oCItem>* node = GetContainList();
	while (node) {
		item = node->GetData();
		node = node->GetNextInList();
		if (item) {
			// Search for lovely place.
			pos = GetPositionWorld();
			item	-> SetCollDet			(FALSE);
			item	-> SetPositionWorld		(pos);
			ogame	-> GetGameWorld()->EnableVob(item);
			if (item-> HasEnoughSpace	(pos)) {
				item-> SetPositionWorld	(pos);
				item-> SetCollDet		(TRUE);
				item-> SetPhysicsEnabled(TRUE);
				item-> SetSleeping		(FALSE);
				item-> GetRigidBody()->SetGravityEnabled(TRUE);
				item-> GetRigidBody()->SetVelocity(zVEC3(zREAL(zRand(300)),zREAL(zRand(300)),zREAL(zRand(300))));
			}
		}
	}
	containList.DeleteList();
}

void oCMobContainer :: Reset()
{
	// [KARK] Truhe wieder schliessen (Deckel zu)
	zCModel *mobModel = GetModel();
	if ((state == 1) && (mobModel))
	{
		zTModelAniID closeAniID = mobModel->GetAniIDFromAniName("T_S1_2_S0");	// "Schliessen"-Ani finden
		if (closeAniID != zMDL_ANI_ID_ILLEGAL)
		{
			if ( mobModel->GetNumActiveAnis() > 1)	// Random-Anis könnten durch AI_PlayAni() aktiv sein
			{
				mobModel->StopAnisLayerRange();
			}
			mobModel->StartAni(closeAniID);	// Deckel zu Ani abspielen
		}
	}

	state			= 0;
	state_target	= 0;

	// [BENDLIN] reset direction
	SetDirection(MOBINTER_DIRECTION_NONE);
}

void oCMobContainer :: Insert (oCItem* item)
{
	containList.Insert(item);

    // [Moos] 30.1.2001 neue Logik: Items in Containern kriegen ein Addref und sind nicht in der Welt.
    item->AddRef();
    ogame->GetGameWorld()->RemoveVobFromLists(item);
};

void oCMobContainer :: Remove (oCItem* item)
{
	containList.Remove(item);

    // [Moos] 30.1.2001 neue Logik: Items in Containern kriegen ein Addref und sind nicht in der Welt.
    ogame->GetGameWorld()->InsertVobInWorld(item);
    item->Release();
}

oCItem* oCMobContainer :: Remove (oCItem* item, int anz)
{
	containList.Remove(item);

	if ( ! item ) return item;

	oCItem* pItem = NULL;

	zCListSort <oCItem> *pElement = containList.GetNextInList();
	while( pElement )
	{
		pItem = pElement->GetData();

		if ( pItem == item )
		{
			// [BENDLIN] remove if requested amount is equal to OR GREATER than the current amount
			if ( pItem->GetAmount() <= anz ) 
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

                // [Moos] 30.1.2001 neue Logik: Items in Containern kriegen ein Addref und sind nicht in der Welt.
                ogame->GetGameWorld()->InsertVobInWorld(pItem);
				pItem->Release();

				return pItem;
			}
			else
				return NULL;
		}
		pElement = pElement->GetNextInList();
	}

	return NULL;
}

void oCMobContainer :: CreateContents (const zSTRING& s)
{
	zSTRING info;
	int wordnr = 1;
	// Get Instance Name
	do {
		info = s.PickWord(wordnr, ",");
		if (!info.IsEmpty()) {
			// Create these Objects
			zSTRING name	= info.PickWord(1,":");
			int num			= info.PickWord(3,":").ToInt();
			if (num<=0) num = 1;
			/*
			zCPar_Symbol* sym		= parser.GetSymbol(name);
			zCPar_Symbol* classSym	= sym?parser.GetSymbol(parser.GetBaseClass(sym)):0;
			if (classSym && (classSym->name == oCItem::GetStaticClassDef()->GetScriptClassName()) )
			*/
			int index = parser.GetIndex(name);
			if (index>=0 && parser.MatchClass(index,oCItem::GetStaticClassDef()->GetScriptClassName()))
			{
				oCItem* item	= zNEW( oCItem(name,num) );
				Insert	(item);
				zRELEASE(item); 
			}
			else
			{
				zERR_WARNING("B: MOBCONTAINER: Item-Instance not found: "+name);
			};
		}
		wordnr += 2;
	} while (!info.IsEmpty());
}

int oCMobContainer :: IsIn(int instance)
{
	int found = 0;
	zCListSort<oCItem> *itemNode = containList.GetNextInList();
	oCItem* item = NULL;
	while (itemNode) {
		item	 = itemNode->GetData();
		itemNode = itemNode->GetNextInList();
		if (item->GetInstance()==instance) found += item->GetAmount();
	}
	return found;
}

void oCMobContainer :: Open(oCNpc* npc)
{
	//oCMobLockable::Open( npc );

	// Do not Open, if its locked
	if (locked) return;

	// NSC können keine Kisten öffnen ?
	if (!npc->IsSelfPlayer()) return;

	// HACK: set body state interupptable
	npc->ModifyBodyState(BS_FLAG_INTERRUPTABLE, 0);

	if (!items) {
		items  = zNEW( oCItemContainer () );
		items -> SetName	(this->GetName());
		items -> SetContents(&containList);
		items -> Open		(0, 0, INV_MODE_CONTAINER);
	}
	// Open NSC inventory
	npc->OpenInventory(INV_MODE_DEFAULT);

	// Activate Container
	items->Activate();

	// FIXME
	// npc->inventory2.SetMode(INV_MODE_DEFAULT);
};

void oCMobContainer :: Close(oCNpc* npc)
{
	//oCMobLockable::Close( npc );

	npc -> SetMovLock(FALSE);
	npc -> CloseInventory();
	delete (items);
	items = NULL;
};

// *************************************
// Archive / Unarchive
// *************************************

void oCMobContainer :: Archive	(zCArchiver &arc)
{
	oCMobLockable :: Archive(arc);

	arc.WriteGroupBegin	("Container");
	arc.WriteString		("contains"		,contains);
	arc.WriteGroupEnd	("Container");

	if (!arc.InSaveGame()) return;
	// Diesen Teil nur im SaveGame ausführen
	// Save Contents
	arc.WriteInt("NumOfEntries", containList.GetNumInList());
	for( int i = 0; i < containList.GetNumInList(); i++ )
	{
//		containList[i]->Archive(arc);
		arc.WriteObject(containList[i]);
	}
}

void oCMobContainer :: Unarchive(zCArchiver &arc)
{
	oCMobLockable :: Unarchive(arc);

	arc.ReadString	("contains"		,contains);

	pickLockStr.Upper();

	if (!arc.InSaveGame()) {
		// Diesen Teil nur beim Startup ausführen
		CreateContents (contains);
		return;
	}
	containList.DeleteListDatas();
	int NumOfEntries = 0;
	arc.ReadInt("NumOfEntries", NumOfEntries);
	oCItem *Entry = NULL;
	for( int i = 0; i < NumOfEntries; i++ )
	{
/*		Entry = zNEW( oCItem );
		Entry->Unarchive( arc );
		containList.Insert( Entry );*/		
		Entry = NULL;
		Entry = dynamic_cast<oCItem*>(arc.ReadObject());
		if( Entry ){
            containList.Insert( Entry );
            Entry->AddRef();
        }
		else ;//error

        // [Moos] in die Welt einfügen
		if (ogame && dynamic_cast<oCWorld*>(ogame->GetWorld()))
            (dynamic_cast<oCWorld*>(ogame->GetWorld()))->InsertVobInWorld(Entry);

        zRELEASE(Entry); // [Moos] Leakfix
	}
}

// *******************************************************************************
// Türen
// *******************************************************************************

oCMobDoor :: oCMobDoor()
{
	addName		= "FRONT";
	sceme		= "DOOR";
	state_num	= 1;
}

oCMobDoor :: ~oCMobDoor()
{
}

zSTRING oCMobDoor :: GetScemeName()
{
	return sceme + "_" + addName;
}

TMobOptPos* oCMobDoor :: SearchFreePosition(oCNpc* npc, zREAL a_fMaxDist)
{
	TMobOptPos* optPos = oCMobInter::SearchFreePosition(npc,a_fMaxDist);
	if (optPos) {
		if (optPos->nodeName.Search("FRONT")>0) addName = "FRONT";
		else									addName = "BACK";
	}
	return optPos;
}

// *******************************************************************************
// Mobs with more than two states
// *******************************************************************************

oCMobWheel :: oCMobWheel()
{
	sceme						= "WHEEL";
	state_num					= 16;
	onInterruptReturnToSlotPos	= FALSE;
};

void oCMobWheel :: OnTrigger (zCVob *otherVob, zCVob *vobInstigator)
{
	oCMobInter::OnTrigger(otherVob,vobInstigator);
	if (this->npcsCurrent<=0) {
		state = state_target = 1;
		if (GetModel()) GetModel()->StartAni("S_S1");
	}
};

void oCMobWheel :: OnUntrigger (zCVob *otherVob, zCVob *vobInstigator)
{
	oCMobInter::OnUntrigger(otherVob,vobInstigator);
	if (this->npcsCurrent<=0) {
		state = state_target = 0;
		if (GetModel()) GetModel()->StartAni("S_S0");
	}
};

////////////////////////////////////////////////////////////////////////////////
//
//	oCMobWheel::Interact
//
//	2002-05-11	[BENDLIN]
//
//				Spezial-Behandlung komplett entfernt.
//				Ist wieder multi-stage -fähig (siehe Basisklasse)
//
////////////////////////////////////////////////////////////////////////////////

void oCMobWheel ::Interact (oCNpc* npc, zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right)
{
	oCMobInter::Interact(npc, action, up, down, left, right);
};

oCMobWheel :: ~oCMobWheel()
{
};

// *******************************************************************************
// Leiter
// *******************************************************************************

oCMobLadder :: oCMobLadder()
{
	sceme						= "LADDER";
	state_num					= 0;
	onInterruptReturnToSlotPos	= FALSE;

	Interacting = FALSE;
	PrevAction = FALSE;
};

oCMobLadder :: ~oCMobLadder()
{
};

void oCMobLadder :: StartInteraction(oCNpc* npc)
{
	// Anzahl der States sind im Namen kodiert
	zCVisual* v	 = GetVisual();	
	if (v) {
		// Schnapp dir den Sceme Name
		zSTRING statesCode = v->GetVisualName();
		statesCode	= statesCode.Copied("_",zSTR_AFTER);
		state_num	= statesCode.ToInt() - 1;
	}

	if (state_num <= 0) {
		// Anzahl der Zustände aus Höhe der Leiter berechnen
		zTBBox3D box = GetBBox3DLocal();
		zREAL height = box.maxs[VY] - box.mins[VY];
		state_num	 = int(height/100) - 1;
	}
	
	oCMobInter :: StartInteraction(npc);		
	
	if ( !Interacting )
	{
		Interacting = TRUE;
		PrevAction = TRUE;
		SetDirection(MOBINTER_DIRECTION_NONE);
	}
//	zerr.Message("U:MI: Ladder States :"+zSTRING(state_num));
}

zBOOL oCMobLadder :: CanChangeState(oCNpc* npc, int from, int to)
{
	if (oCMobInter::CanChangeState(npc,from,to)) {
		// Falls Zielzustand == -1, der darf nur erreicht werden, 
		// wenn aktueller State == 0 oder "state_num"
		if (to==-1) 
			return ((state==0) || (state==state_num));
		else
			return TRUE;
	}
	return FALSE;
}

zBOOL oCMobLadder :: CanInteractWith(oCNpc* npc)
{
	// Leitern kann wirklkich nur einer benutzen
	return (oCMobInter::CanInteractWith(npc));
}

TMobOptPos* oCMobLadder :: SearchFreePosition(oCNpc* npc, zREAL a_fMaxDist)
{
	TMobOptPos* optPos = oCMobInter::SearchFreePosition(npc, a_fMaxDist);
	// Oben oder unten ?
	if (optPos) {
		zVEC3 center = GetBBox3DWorld().GetCenter();
		if (optPos->trafo.GetTranslation()[VY] < center[VY]) {
			// Unten
			state = 0;
		} else {
			// Oben
			state = state_num;
		}
		state_target = state;
	}	
	return optPos;
}

///////////////////////////////////////////////////////////////
//
//	oCMobLadder::Interact
//
//	2002-05-11	[BENDLIN]
//
//				ACTION		= start/end interaction
//				UP/DOWN		= begin movement / change direction
//				LEFT/RIGHT	= on last stage only -> leave
//
///////////////////////////////////////////////////////////////

void oCMobLadder :: Interact (oCNpc* npc, zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right)
{
	// detect new actions
	zBOOL NewAction = FALSE;
	if ((PrevAction != action) || (action && (!Interacting)))
	{
		PrevAction = action;
		NewAction = action;
	}
		
	// jump off
	if ((Interacting) && (NewAction) && (state >= 0) && (state <= state_num))
	{
		// try "normal" way
		if (CanChangeState(npc, state, -1))
		{
			SendStateChange(state, -1);
			EndInteraction(npc, TRUE);
		}
		else
		{					
			// let the (N)PC falling down...
			// (FIXME : Das ist nicht wirklich schön, oder ? - Springen von Stufe 0 beim "Greifen"!)
			npc->Interrupt();
			npc->SetPhysicsEnabled(TRUE);
			npc->GetAnictrl()->SetFallDownStartY(npc->GetAnictrl()->GetCenterPos()[VY]);
			npc->GetRigidBody()->SetGravityEnabled(TRUE);
			npc->GetRigidBody()->SetVelocity(-npc->GetAtVectorWorld());
			npc->GetModel()->SetIsFlying(FALSE);
			npc->GetModel()->StartAni("S_FALLDN");

			EndInteraction(npc, FALSE);
		}
		
		return;	
	}

	CheckStateChange(npc);
	if (!IsInteractingWith(npc)) return;

	if (npc->IsMovLock()) return;

	// AniEvents - insert/remove InteractItem, etc.
	npc->DoDoAniEvents();

	// handle interaction
	if ((state >= 0)) 
	{
		if (NewAction && (npcsCurrent >= npcsNeeded) && !Interacting)
		{
			Interacting = TRUE;
		}

		if (Interacting)
		{
			if (up)
			{
				if ((state < state_num) && CanChangeState(npc, state, state + 1))
				{
					// one stage up
					SetDirection(MOBINTER_DIRECTION_UP);
					SendStateChange(state, state + 1);
				}
				else if ((state == state_num) && CanChangeState(npc, state, -1))
				{	
					// last stage (upward)
					SendStateChange(state, -1);
					EndInteraction(npc, TRUE);
				}
			}
			else if (down)
			{
				if ((state > 0))
				{
					if (CanChangeState(npc, state, state - 1))
					{
						// one stage down
						SetDirection(MOBINTER_DIRECTION_DOWN);
						SendStateChange(state, state - 1);
					}
				}
				else if ((state == 0) && CanChangeState(npc, state, -1) && (!action))
				{	// last stage (downward), ACTION not pressed
					SendStateChange(state, -1);
					EndInteraction(npc, TRUE);
				}
			}
			else if ((left || right) && CanChangeState(npc, state, -1))
			{
				SendStateChange(state, -1);
				EndInteraction(npc, TRUE);
			}
			else if ((GetDirection() == MOBINTER_DIRECTION_UP) && (state == state_num) && CanChangeState(npc, state, -1))
			{
				// auto-leave last stage (upward)
				SendStateChange(state, -1);
				EndInteraction(npc, TRUE);
			}
			else if ((GetDirection() == MOBINTER_DIRECTION_DOWN) && (state == 0) && CanChangeState(npc, state, -1) && (!action))
			{
				// auto-leave last stage (downward), ACTION not pressed
				SendStateChange(state, -1);
				EndInteraction(npc, TRUE);
			}
		}
	}
}

///////////////////////////////////////////////////////////////
//
//	oCMobLadder::EndInteraction
//
//	2002-05-11	[BENDLIN]
//
//				Reset internal vars
//
///////////////////////////////////////////////////////////////

void oCMobLadder::EndInteraction (oCNpc* npc,zBOOL playEndAni)
{
	Interacting = FALSE;
	PrevAction = FALSE;
	oCMobInter::EndInteraction(npc, playEndAni);
}

// ************************************************************************************
// MobInter Slot - Place an Item in the Slot
// ************************************************************************************

oCMobItemSlot :: oCMobItemSlot ()
{
	insertedItem = NULL;
	removeable	 = FALSE;
}

oCMobItemSlot :: ~oCMobItemSlot()
{
//	delete (GetInsertedItem());
	insertedItem = NULL;
}

int	oCMobItemSlot :: GetUseWithItem	()
// Keine weiteren Items benötigt, wenn ItemSlot bereits belegt
// d.h. in diesem Fall wird die Interaktion erlaubt
{
	if (GetInsertedItem()) return -1;
	return oCMobInter :: GetUseWithItem();
}

zBOOL oCMobItemSlot :: CanInteractWith	(oCNpc* npc)
{
	// if (GetInsertedItem()) return FALSE;
	
	if (oCMobInter::CanInteractWith(npc)) {
		// Falls ein neuer NSC sich anmelden möchte, und dies gelingt, 
		// so springt der Zustand des Mobs wieder auf Null 
		// ( sonst wuerde dieser auf 1 bleiben ( nachdem ein Item eingefügt wurde ) 
		// und keine weiteren Anmeldungen waeren erfolgreich
		// SetCollDet(FALSE);
		// state = state_target = 0;
		return TRUE;
	}
	return FALSE;
}

oCItem* oCMobItemSlot :: GetInsertedItem()
{
	return insertedItem;
}

zBOOL oCMobItemSlot :: PlaceItem (oCItem* item)
{
	if (!item)				return FALSE;
	if (GetInsertedItem())	return FALSE;
	
	if (GetUseWithItem() == item->GetInstance()) {
		// Durchsuche nach Item-Slot : ZS_SLOT
		zCModelPrototype* m = GetModel()->GetModelProto();
		for (int i=0; i<m->GetNodeList().GetNumInList(); i++) {
			zCModelNode*	node		= m->GetNodeList()[i];
			zSTRING			nodeName	= node->GetName();
			// Found ?
			if (node && (nodeName.Search("ZS_SLOT")>=0)) {				
				
				//SetCollDet(FALSE);

				item -> SetCollDet(FALSE);

				if (item->GetHomeWorld()) item->GetHomeWorld()->RemoveVob(item);
				item -> SetPositionWorld	(0,0,0);
				GetHomeWorld()->AddVob		(item);
				
				zMATRIX4 trafo	= GetTrafoModelNodeToWorld(nodeName);
				item -> SetCollDet			( FALSE );
				item -> SetTrafoObjToWorld	( trafo );
				item -> SetPhysicsEnabled	(FALSE);
				item -> SetIgnoredByTraceRay(TRUE);
				item -> SetSleeping			(TRUE);
				insertedItem = item;
				return TRUE;
			}
		}
		zerr.Warning("U:MOBSI:No Slot ZS_SLOT found."+GetInstanceName());
		return FALSE;
	}
	return FALSE;
}

oCItem* oCMobItemSlot :: RemoveItem()
{
	// FIXME : Remove From Slot
	oCItem* item = GetInsertedItem();
	insertedItem = NULL;
	if (item && item->GetHomeWorld()) {
		item -> GetHomeWorld() -> RemoveVob (item);
	}
	return item;
}

zBOOL oCMobItemSlot :: IsIn (int instance)
{
	oCItem* item = GetInsertedItem();
	return (item && item->GetInstance()==instance);
}

void oCMobItemSlot :: Archive	(zCArchiver &arc)
{
	oCMobInter :: Archive(arc);
	
	arc.WriteBool("itemRemoveable",removeable);
	if (!arc.InProperties()) arc.WriteObject("insertedItem",insertedItem);
};

void oCMobItemSlot :: Unarchive	(zCArchiver &arc)
{
	oCMobInter :: Unarchive(arc);
	arc.ReadBool("itemRemoveable",removeable);
	if (!arc.InProperties()) insertedItem = (oCItem*) arc.ReadObject("insertedItem");
};

// ************************************************************************************
// Dummy Item Generator
// ************************************************************************************

oCDummyVobGenerator :: oCDummyVobGenerator()
{
	SetShowVisual	(FALSE);
	SetCollDet		(FALSE);
	SetSleeping		(FALSE);
}

void oCDummyVobGenerator :: OnTrigger(zCVob* otherVob, zCVob* vobInstigator)
{
	// Pfeil erzeugen
	oCItem* arrow		= zNEW( oCItem(zSTRING("Arrow")) );

	// AI dranhängen
	oCAIArrow *aiArrow = zNEW( oCAIArrow );
	arrow	-> SetAICallback	(aiArrow);
	arrow	-> SetSleeping		(FALSE);
	arrow	-> SetVobName		("Pfeil von Dummy-Generator");
	// Arrow einfügen
	GetHomeWorld() -> AddVob	(arrow);
	zMATRIX4 trafo  = trafoObjToWorld;
	trafo.PostRotateY			(90);
//	aiArrow	-> SetupAIVob		(arrow, NULL, trafo);
}

