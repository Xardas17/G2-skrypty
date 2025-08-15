
#include "zcore.h"
#include "zSTRING.h"
#include "zERROR.h"
#include "z3d.h"
#include "zEventMan.h"
#include "zVob.h"
#include "zNetVobControl.h"
#include "zPlayerInfo.h"
#include "zworld.h"

#include "zCCSCutscene.h"
#include "zCCSPlayer.h"
#include "zCCSContext.h"
#include "zccsmanager.h"





zCLASS_DEFINITION_ABSTRACT(zCCSBlockBase,zCObject,0)

zCLASS_DEFINITION	(zCCSAtomicBlock,	zCCSBlockBase,	0,0)
zCLASS_DEFINITION	(zCCSBlock,			zCCSBlockBase,	0,0)
zCLASS_DEFINITION	(zCCSSyncBlock,		zCCSBlock,		0,0)
zCLASS_DEFINITION	(zCCutscene,		zCCSBlock,		0,3)
zCLASS_DEFINITION	(zCCSRole,			zCObject,		0,3)
zCLASS_DEFINITION	(zCEvMsgCutscene,	zCEventMessage,	0,0)


//
// Ultimativer Pointer :-) 
//
static zCEventMessage* CS_FINISHED_EVENTMSG = (zCEventMessage*)1;

//
// Konstanten für Rollen-Platzhalter 
//
const zSTRING CS_PLAYER_ROLENAME = "_PLAYER";
const zSTRING CS_MAIN_ROLENAME   = "_MAINROLE";

const int CS_BLOCK_CONTINUE	= 0;
const int CS_BLOCK_NEXT		= 1;
const int CS_BLOCK_STOP		= 2;


//
// Defines
//

#define _CALL_EV_MESSAGES_		// Soll Eventnachrichten an die Hauptrolle verschickt werden?



zCCSRole::zCCSRole() : 
	zCObject(), 
	rFlag(CSRrequired), 
	roleVob(0), 
	mustBeAlive(FALSE), 
	zSTRING() 
{
};

zCCSRole::zCCSRole(zSTRING & name) : 
	zCObject(), 
	rFlag(CSRrequired), 
	roleVob(0), 
	mustBeAlive(FALSE), 
	zSTRING(name) 
{
};
		
zCCSRole::~zCCSRole()
{ 
	if (roleVob)	zERR_MESSAGE(8,0,"B: CS: Destructing role: rolevob "+roleVob->GetVobName()+" (refCtr before is "+zSTRING(roleVob->GetRefCtr())+")");
	zRELEASE_OBJ(roleVob); 
};
	
void zCCSRole::SetRoleVob(zCVob* rVob)	
{ 
	if (rVob)		zERR_MESSAGE(8,0,"B: CS: Setting rolevob "+rVob->GetVobName()+" (refCtr before is "+zSTRING(rVob->GetRefCtr())+")");
	if (roleVob)	zERR_MESSAGE(8,0,"B: CS: Disposing rolevob "+roleVob->GetVobName()+" (refCtr before is "+zSTRING(roleVob->GetRefCtr())+")");
	assign(rVob->GetVobName());
	zADDREF_OBJ(rVob);
	zRELEASE_OBJ(roleVob);
	roleVob=rVob; 
}

zCVob* zCCSRole::GetRoleVob() 
{ 
	return roleVob; 
};

void zCCSRole::Archive(zCArchiver &arc)
{
	zCObject::Archive (arc);

	arc.WriteBool	("mustBeAlive",	mustBeAlive);
	arc.WriteString	("roleName", 	*this);
	arc.WriteEnum	("roleType",	"CSRrequired;CSRdelayable;CSRnonrequired",int(rFlag));
	if (!arc.InProperties())
	{
		arc.WriteObject("integratedVob",roleVob);	
	}
}
void zCCSRole::Unarchive(zCArchiver &arc)
{
	zCObject::Unarchive (arc);
	
	zSTRING lStr;
	int 	n		= 0;
	
	arc.ReadBool	("mustBeAlive",	mustBeAlive);
	arc.ReadString	("roleName",	lStr);		lStr.Upper();assign(lStr);	
	arc.ReadEnum	("roleType",	n);			rFlag = zTCSRoleFlag(n);
	if (!arc.InProperties())
	{
		zRELEASE_OBJ(roleVob);
		roleVob = dynamic_cast<zCVob*>(arc.ReadObject("integratedVob"));		
	}
}

	



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// EventMessage fuer Cutscenes
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



zCEvMsgCutscene::zCEvMsgCutscene(TCutsceneSubType _subtype)
{
	subType			= _subtype;
	csName			= "";	
	isOutputUnit	= FALSE;
	isGlobalCutscene= FALSE;
	isMainRole		= FALSE;
	deleted			= FALSE;	
};

zCEvMsgCutscene::~zCEvMsgCutscene() 
{	
};

int zCEvMsgCutscene::MD_GetNumOfSubTypes()
{
	return EV_CS_MAX;
};

zSTRING	zCEvMsgCutscene::MD_GetSubTypeString(int n)
{
	switch (n)
	{
	case EV_CS_STARTPLAY:	return "EV_CS_STARTPLAY";break;
	case EV_CS_STOP:		return "EV_CS_STOP";break;
	case EV_CS_INTERRUPT:	return "EV_CS_INTERRUPT";break;
	case EV_CS_RESUME:		return "EV_CS_RESUME";break;
	default: return "";
	};
};
	
#ifdef COMPILING_SPACER

	zSTRING	zCEvMsgCutscene::MD_GetInfo()
	{
		return "";
	};

	void zCEvMsgCutscene::MD_SetInfo(const zSTRING & str)
	{

	};

#endif






///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// BlockBase
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


zCCSBlockBase::zCCSBlockBase()	{ }
zCCSBlockBase::~zCCSBlockBase()	{ }

zCCSBlockBase*	zCCSBlockBase::GetChild(int n)				{ return 0; }
int				zCCSBlockBase::NewBlock(int id, int n)		{ return 0; }
int				zCCSBlockBase::GetNumOfChilds()				{ return 0; }
int				zCCSBlockBase::GetRoleNumOfChild(int pos)	{ return -1; }
void			zCCSBlockBase::BlockCorrection()			{ }
void			zCCSBlockBase::BlockAsFocus(int n)			{ }

zSTRING			zCCSBlockBase::GetRoleName()				{ return zSTRING(""); }
void			zCCSBlockBase::SetRoleName(zSTRING & name)	{ }
void			zCCSBlockBase::DeleteChild(int pos)			{ }

zCCSBlockPosition*	zCCSBlockBase::GetChildPos(int nr)		{ return 0; }

#ifdef COMPILING_SPACER

void			zCCSBlockBase::SetInfo(zSTRING & str)		{ }	
void			zCCSBlockBase::SetDBFlag(zBOOL f)			{ }
zBOOL			zCCSBlockBase::GetDBFlag()					{ return FALSE; }

#endif


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// AtomicBlock
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////




zCCSAtomicBlock::zCCSAtomicBlock() : zCCSBlockBase()
{
	commandRef		= 0;		
	command			= 0;
	roleVob			= 0;
	// synchronized	= TRUE;
	commandState	= EVCOM_NOTSTARTED;

	#ifdef COMPILING_SPACER
	dbflag = FALSE;
	#endif
}

zCCSAtomicBlock::~zCCSAtomicBlock()
{
	zRELEASE(command);
	zRELEASE(commandRef);
}

// override pure virtuals
void zCCSAtomicBlock::OrganizeRoles	(zTCSRoleVobList &roleVobs, zTCSRoleList &roleN)
{	
	commandState = EVCOM_NOTSTARTED;
	if (command)
	{
		zSTRING vobRefName = command->MD_GetVobRefName();
		if (!vobRefName.IsEmpty())
		{
			zBOOL found = FALSE;
			vobRefName.Upper();
			int z=0;
			while (	z<roleVobs.GetNumInList() && !found )
			{				
				found 	= (z<roleN.GetNumInList() 	&& roleN[z]==vobRefName)
						||(roleVobs[z] 			 	&& roleVobs[z]->GetVobName()==vobRefName);
				
				if (!found) z++;
			}
			
			if (found) roleVob = roleVobs[z];
			else 
			{ 
				commandState=EVCOM_FINISHED;
				#ifdef _CS_DEBUGINFO
				if (dbplayer) dbplayer->CSDB_Warning(this,zSTRING("No role found for vob ")+vobRefName);
				#endif
			};			
		}
	}
	else zERR_WARNING("B: CS: OrganizeRoles: command is NULL");
}

// override pure virtuals
void zCCSAtomicBlock::Play(const zTCSRoleEMList &aiman) 
{ 
	Play(aiman[0]); 
};

void zCCSAtomicBlock::Play(const zTCSRoleEMList &aiman, zCSTIME, zCSTIME) 
{ 
	Play(aiman[0]); 
};

void zCCSAtomicBlock::Play(zCEventManager* aiman)
{
	if (!aiman || IsFinished(aiman)) commandState = EVCOM_FINISHED;
	
	if (commandState==EVCOM_NOTSTARTED && command)
	{		
		#ifdef _CS_DEBUGINFO
			if (dbplayer) dbplayer->CSDB_BeginAtomBlock(this);
		#endif
				
		zRELEASE(commandRef);
		commandRef		= static_cast<zCEventMessage*>(command->CreateCopy());						
		commandRef		->AddRef		();
		commandRef		->MD_SetVobParam(roleVob);
		aiman			->OnMessage		(commandRef,NULL);
		commandState	= EVCOM_PLAYING;
	}
}

void zCCSAtomicBlock::Play(zCEventManager* aiman, zCSTIME b1, zCSTIME b2)
{

}

zCSTIME zCCSAtomicBlock::GetMinTime()
{
	return (command ? command->MD_GetMinTime() : 0);
}

zBOOL zCCSAtomicBlock::IsFinished(zCEventManager* aiman)
{	
	if (commandState==EVCOM_NOTSTARTED) return FALSE;
	if (commandState==EVCOM_FINISHED)	return TRUE;
	// if (!synchronized)					return TRUE;
	
	zERR_ASSERT(commandRef);

	zBOOL fin = 
		!aiman							|| 
		!aiman->IsRunning(commandRef)	|| 
		(commandRef->MD_GetTimeBehavior()==zCEventMessage::TBAssembled);

	if (fin) 
	{
		commandState=EVCOM_FINISHED;				

		#ifdef _CS_DEBUGINFO
			if (dbplayer) dbplayer->CSDB_EndAtomBlock(this);
		#endif

		zERR_MESSAGE(8,0,"B: CS: EVMsg "+commandRef->MD_GetSubTypeString(commandRef->GetSubType())+" finished");

		zRELEASE(commandRef);
	}
	return fin;
}

#ifdef COMPILING_SPACER

	zSTRING zCCSAtomicBlock::GetInfo()
	{
		if (command)
			return command->MD_GetInfo();
		else return zSTRING();
	}
	void zCCSAtomicBlock::SetInfo	(zSTRING & str)
	{
		if (command)
			command->MD_SetInfo(str);			
		else ;
	}

	zBOOL zCCSAtomicBlock::GetDBFlag() { return dbflag; }
	void zCCSAtomicBlock::SetDBFlag(zBOOL f) { dbflag=f; }

#endif

	
	
	



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// CSBlock
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



	
	
	
	
	
	
	

zCCSBlock::zCCSBlock() : zCCSBlockBase(), blocks(), roleName() { }
zCCSBlock::~zCCSBlock() 
{ 
	for (int z=0; z<blocks.GetNumInList(); z++)
	{
		if (blocks[z].block) zRELEASE(blocks[z].block);
	}
}

zCCSBlockBase *zCCSBlock::GetChild(int n)
{
	if (n>=0 && n<blocks.GetNumInList()) return blocks[n].block;
	else return 0;
}

zCCSBlockPosition *zCCSBlock::GetChildPos(int nr)
{
	if (nr>=0 && nr<blocks.GetNumInList()) return &blocks[nr];
	else return 0;
}

int	zCCSBlock::GetNumOfChilds()
{ return blocks.GetNumInList(); }

void zCCSBlock::DeleteChild(int pos)
{
	if (pos>=0 && pos<blocks.GetNumInList())
	{
		zRELEASE(blocks[pos].block); //sicherheitshalber
		blocks.RemoveOrderIndex(pos);
		BlockCorrection();
	}
}

// alle Subblöcke laufen potentiell zeitgleich
// in diesem Fall ist der Block Teil einer Spur, die explizit zu einer Rolle gehört
void zCCSBlock::Play(zCEventManager* aiman)
{
	for (int z=0; z<blocks.GetNumInList(); z++)
	{
		if (blocks[z].position==0) blocks[z].block->Play(aiman);
	}
}

void zCCSBlock::Play(zCEventManager* aiman, zCSTIME b1, zCSTIME b2)
{
	for (int z=0; z<blocks.GetNumInList(); z++)
	{
		// time
		zCSTIME lt = blocks[0].block->GetMinTime();		
		lt = blocks[z].position* ( (lt==0)?1:lt );

		// check time
		if (b1<lt && lt<=b2)	blocks[z].block->Play(aiman);
		if (b1>=lt)				blocks[z].block->Play(aiman,b1,b2);
	}
}

// in diesem Fall ist der Block eine Sync-Einheit, deren Subblöcke verschiedene Rollen sind
void zCCSBlock::Play(const zTCSRoleEMList &aiman)
{

	zERR_WARNING(zSTRING("zCCSBlock::Play(Array): not allowed!"));
}

void zCCSBlock::Play(const zTCSRoleEMList &aiman, zCSTIME b1, zCSTIME b2)
{

	zERR_WARNING(zSTRING("zCCSBlock::Play(Array): not allowed!"));
}

zCSTIME zCCSBlock::GetMinTime()
{
	if (blocks.GetNumInList()<=0) return 0;
	zCSTIME focusTime = blocks[0].block->GetMinTime();
	zCSTIME maxTime = focusTime;
	for (int z=1; z<blocks.GetNumInList(); z++)
	{
		zCSTIME blockTime = blocks[z].position*focusTime+blocks[z].block->GetMinTime();
		if (maxTime<blockTime) maxTime = blockTime;
	}
	return maxTime;
}

zBOOL zCCSBlock::IsFinished(zCEventManager* aiman)
{
	zBOOL fin = TRUE;

	// Mal schauen, ob alle enthaltenen Bloecke beendet sind.
	int z =0;
	while (z<blocks.GetNumInList() && fin)
	{
		fin = fin && blocks[z].block->IsFinished(aiman);
		z++;
	}
	return fin;
}

zBOOL zCCSBlock::IsFinished(const zTCSRoleEMList &aiman)
{
	zERR_WARNING(zSTRING("zCCSBlock::IsFinished(Array): not allowed!"));
	return TRUE;
}

void zCCSBlock::OrganizeRoles(zTCSRoleVobList &roles, zTCSRoleList &roleN)
{
	if (( blocks.GetNumInList()==0 ) ) return;

	// load ComplexData with roleData (depends on special implementation)
	for (int z=0; z<blocks.GetNumInList(); z++)
	{
		blocks[z].block->OrganizeRoles(roles,roleN);
	}
}

zSTRING zCCSBlock::GetRoleName()
{ 
	return roleName; 
}

void zCCSBlock::SetRoleName(zSTRING & name)
{ 
	roleName = name; 
}

#ifdef COMPILING_SPACER
	zSTRING zCCSBlock::GetInfo()
	{
		if (blocks[0].block) 
			return blocks[0].block->GetInfo();
		else return zSTRING("");
	}
#endif

void zCCSBlock::InsertBlock(zCCSBlockBase* bl, int n)
{
	blocks.Insert(zCCSBlockPosition());
	blocks[blocks.GetNumInList()-1].block=bl;
}

int zCCSBlock::NewBlock(int id, int n)
{
	zCCSAtomicBlock* lBlock = 0;
	blocks.Insert(zCCSBlockPosition());
	blocks[blocks.GetNumInList()-1].block=lBlock;
	return blocks.GetNumInList()-1;
}

void zCCSBlock::BlockAsFocus(int n)
{
	zCCSBlockBase* lBlock = blocks[0].block;
	zCSTIME lPos = blocks[0].position;
	blocks[0].block = blocks[n].block;
	blocks[0].position = blocks[n].position;
	blocks[n].block = lBlock;
	blocks[n].position = lPos;
}

void zCCSBlock::BlockCorrection()
{
	if (blocks.GetNumInList()<1) return;

	// der Block[0] muß immer position 0 haben, und alle andreren positiv
	if (blocks.GetNumInList()<1) 
	{
		blocks[0].position=0.0;
		return;
	}
	
	// alte Blockzeit modifiziert
	zCSTIME focus_alt = blocks[0].block->GetMinTime();
	if (focus_alt==0.0) focus_alt = 1.0;
	// neuer Block ??
	int minimalNum = 0;
	zCSTIME minPos = blocks[0].position;
	for (int z=1; z<blocks.GetNumInList(); z++)
		if (blocks[z].position<minPos)
		{
			minimalNum = z;
			minPos = blocks[z].position;
		}
	// ok, blocks[minimalNum] ist zukünftiger focus
	zCSTIME focus_neu = blocks[minimalNum].block->GetMinTime();
	if (focus_neu==0.0) focus_neu = 1.0;
	for (int z2=0; z2<blocks.GetNumInList(); z2++)
	{
		blocks[z2].position= (focus_alt * blocks[z2].position) / focus_neu;
	}
	// neuen focus setzen
	BlockAsFocus(minimalNum);
	// PosWerte rejustieren (block[0].position wieder 0)
	zCSTIME adjust = blocks[0].position;
	for (z2=0; z2<blocks.GetNumInList(); z2++)
	{
		blocks[z2].position = blocks[z2].position - adjust;
	}
}









///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// SyncBlock
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////








zCCSSyncBlock::zCCSSyncBlock()
 :	zCCSBlock()
{
}

zCCSSyncBlock::~zCCSSyncBlock() 
{
}

zBOOL zCCSSyncBlock::IsFinished(const zTCSRoleEMList &aiman)
{	
	// Mal schauen, ob alle enthaltenen Bloecke beendet sind.
	zBOOL fin = TRUE;
	int z =0;
	while (z<blocks.GetNumInList() && fin)
	{
		fin = fin && blocks[z].block->IsFinished(aiman[roleAss[z]]);
		z++;
	}
	//if (fin) zERR_MESSAGE(8,0,"B: CS: SyncBlock finished");
	return fin;
}

void zCCSSyncBlock::Play(zCEventManager* aiman)
{
	#ifdef _CS_DEBUGINFO
		if (dbplayer) dbplayer->CSDB_BeginSyncBlock(this);
	#endif
	for (int z=0; z<blocks.GetNumInList(); z++)
	{
		if (blocks[z].position==0) blocks[z].block->Play(aiman);
	}
}
// in diesem Fall ist der Block eine Sync-Einheit, deren Subblöcke verschiedene Rollen sind
void zCCSSyncBlock::Play(const zTCSRoleEMList &aiman)
{
	#ifdef _CS_DEBUGINFO
		if (dbplayer) dbplayer->CSDB_BeginSyncBlock(this);
	#endif
	if (aiman.GetNumInList()==1) { zCCSBlock::Play(aiman[0]); return; }

	for (int z=0; z<blocks.GetNumInList(); z++)
	{
		if (blocks[z].position==0) blocks[z].block->Play(aiman[roleAss[z]]);
	}
}

void zCCSSyncBlock::Play(const zTCSRoleEMList &aiman, zCSTIME b1, zCSTIME b2)
{
	if (aiman.GetNumInList()==1) { zCCSBlock::Play(aiman[0],b1,b2); return; }

	for (int z=0; z<blocks.GetNumInList(); z++)
	{
		// time
		zCSTIME lt = blocks[0].block->GetMinTime();		
		lt = blocks[z].position* ( (lt==0)?1:lt );
		// check time
		// if (!blocks[z].refBlock)
			if (b1<lt && lt<=b2) blocks[z].block->Play( aiman[roleAss[z]] );
		/*
			else
			if (blocks[z].block->IsFinished(aiman[roleAss[z]]))
				blocks[z].block->Play( aiman[roleAss[z]] );				
		*/
	}
}

int	zCCSSyncBlock::GetRoleNumOfChild(int pos)
{
	if (pos<roleAss.GetNumInList())
		return roleAss[pos];
	else return zCCSBlockBase::GetRoleNumOfChild(pos);
}

void zCCSSyncBlock::InsertBlock(zCCSBlockBase* bl, int n)
{
	roleAss.Insert(n);
	blocks.Insert(zCCSBlockPosition());
	assert(roleAss.GetNumInList()==blocks.GetNumInList());
	blocks[blocks.GetNumInList()-1].block=bl;
}

int zCCSSyncBlock::NewBlock(int id, int n)
{	
	zCCSAtomicBlock* lBlock = 0;
//	csplayer->AtomicBlockConstructor(id,lBlock);
	//lBlock->Init();
	roleAss.Insert(n);
	blocks.Insert(zCCSBlockPosition());
	blocks[blocks.GetNumInList()-1].block=lBlock;
	assert(roleAss.GetNumInList()==blocks.GetNumInList());
	return blocks.GetNumInList()-1;
}

void zCCSSyncBlock::BlockAsFocus(int n)
{
	zCCSBlock::BlockAsFocus(n);
	int tmp = roleAss[0];
	roleAss[0]=roleAss[n];
	roleAss[n]=tmp;
}

void zCCSSyncBlock::DeleteChild(int pos)
{
	roleAss.RemoveOrderIndex(pos);
	zCCSBlock::DeleteChild(pos);
}

void zCCSSyncBlock::AssignerCorrection(int n)
{
	for (int a=0; a<roleAss.GetNumInList(); a++)
	{
		if (roleAss[a]>n) roleAss[a]--;
	}
}







///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// zCCutscene
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////








zCCutscene::zCCutscene()
 :	zCCSBlock(), roleEvMList(), roleVobList(), roleList()
{	
	mainRoleVob		= 0;
	actualBlock		= 0;
	actualBlockNum	= 0;
	ownerPlayer		= 0;
	lastCheckResult	= CS_CHECK_UNKNOWN;
	properties		= zNEW(zCCSProps);	

	zERR_MESSAGE(8,0,"B: CS: Cutscene constructed.");
}

zCCutscene::~zCCutscene() 
{	
	Stop();	
	
	ClearCutscene();
	
	SetOwnerPlayer(0);

	zERR_MESSAGE(8,0,"B: CS: Cutscene destructed.");
}

void zCCutscene::SetOwnerPlayer(zCCSPlayer* player)
{
	zRELEASE(ownerPlayer);
	ownerPlayer = player;
	if (ownerPlayer) ownerPlayer->AddRef();
};

zBOOL zCCutscene::IsMember(zCVob* vob)
{
	int z=0;
	while (z<roleVobList.GetNumInList() && roleVobList[z]!=vob) z++;

	return z<roleVobList.GetNumInList();
}

void zCCutscene::SetRoleListForDebugging(zTCSRoleList & roleN)
{
	//roleList = roleN;
	for (int z=0; z<roleN.GetNumInList(); z++) // platz für diese einträge schaffen
	{
		roleVobList.Insert(0);
		roleEvMList.Insert(0);
		zCCSRole* lrole = zNEW(zCCSRole());
		*lrole = *(roleN[z]);
		lrole->rFlag = roleN[z]->rFlag;
		roleList.Insert(lrole);

		if (roleN[z]->GetRoleVob())
		{
			if (roleList[z]) roleList[z]->SetRoleVob(dynamic_cast<zCVob*>(roleN[z]->GetRoleVob()->CreateCopy()));
		}
	}
};
void zCCutscene::SaveRolesVobs(zCBuffer & buffer)
{
	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII, TRUE);	
	for (int z=0; z<roleList.GetNumInList(); z++)
	{
		if (roleList[z]->GetRoleVob()==0) // dann ist es ein Vob aus der Welt
		{
			zSTRING chunkName = zSTRING("roleName")+zSTRING(z);
			arch->WriteString(chunkName.ToChar(),roleList[z]);
			arch->WriteObject(roleVobList[z]);
		}
	}
	zCBuffer* lBuf = arch->GetBuffer();
	if (lBuf) buffer = (*lBuf); // buffer kopieren
	arch->Close();
	zRELEASE(arch);
}
void zCCutscene::RestoreRoleVobs(zCBuffer & buffer)
{
	zCArchiver* arch = zarcFactory.CreateArchiverRead(&buffer);	
	for (int z=0; z<roleList.GetNumInList(); z++)
	{
		if (roleList[z]->GetRoleVob()==0) // dann ist es ein Vob aus der Welt
		{
			zSTRING chunkName = zSTRING("roleName")+zSTRING(z);
			zSTRING test;
			arch->ReadString(chunkName.ToChar(),test);
			
			zRELEASE_OBJ(roleVobList[z]);			
			roleVobList[z] = dynamic_cast<zCVob*>(arch->ReadObject());
		}
	}
	arch->Close();
	zRELEASE(arch);
}

//
// CheckMainRole(vob)
//
// Die Hauptrolle überprüfen.
//
int zCCutscene::CheckMainRole(zCVob* vob)
{
	if (!vob) return -1;

	zSTRING rName = vob->GetVobName();				
	
	zCPlayerInfo* playerInfo = zCPlayerInfo::GetActivePlayer();
	bool vobIsPlayer = playerInfo && (vob == playerInfo->GetPlayerVob());

	// Indizes
	int mainRoleIndex		=-1;	// Index der Hauptrolle in Rollenarray
	int playerRoleIndex		=-1;	// Index der Playerrolle in Rollenarray
	int roleIndex			=-1;	// Index des Vobs in Rollenarray	
	
	// Rollenindizes suchen
	for (int i=0;i<roleList.GetNumInList();i++)
	{		
		if (roleList[i]==CS_MAIN_ROLENAME)		mainRoleIndex	= i;	// a) MAINROLE-Variable?		
		if (roleList[i]==CS_PLAYER_ROLENAME)	playerRoleIndex	= i;	// b) PLAYER-Variable?		
		if (roleList[i]==rName)				roleIndex		= i;	// c) Vob als Rolle gefunden
	}
	
	// Rollenindizes auf Plausibilitaet checken	

	if (mainRoleIndex>=0) // Ist eine MAINROLE-Variable angegeben?
	{
		if (vobIsPlayer && playerRoleIndex>=0)	{ zERR_FAULT("B: CS "+CS_NAME_QUOTED(properties)+": Mainrole \""+rName+"\" is the player but "+CS_MAIN_ROLENAME+" and(!) "+CS_PLAYER_ROLENAME+" are defined as a role in the cutscene");return -1;}
		if (roleIndex>=0)						{ zERR_FAULT("B: CS "+CS_NAME_QUOTED(properties)+": Mainrole \""+rName+"\" found as a role of the cutscene but "+CS_MAIN_ROLENAME+" is defined as a role, too");return -1;}
		return mainRoleIndex;	// ansonsten alles ok
	}

	else if (vobIsPlayer) // Ist der Vob ein Spieler?
	{		
		if (playerRoleIndex<0)					{ zERR_FAULT("B: CS "+CS_NAME_QUOTED(properties)+": Mainrole \""+rName+"\" is the player but no "+CS_MAIN_ROLENAME+" or "+CS_PLAYER_ROLENAME+" is defined as a role in the cutscene");return -1;}
		if (roleIndex>=0)						{ zERR_FAULT("B: CS "+CS_NAME_QUOTED(properties)+": Mainrole \""+rName+"\" is _PLAYER but his rolename was found in the cutscene, too");return -1;}
		return playerRoleIndex;	// ansonsten alles ok
	}

	else
	{
		if (roleIndex<0)						{ zERR_FAULT("B: CS "+CS_NAME_QUOTED(properties)+": Mainrole \""+rName+"\" was not found in cutscenes");return -1; }
		return roleIndex;		// ansonsten alles ok
	};
	return -1;
}

zCVob* zCCutscene::GetStage()
{ 
	return 0; 
};


// PlayStatusValues
// 0 weitermachen
// 1 nächster Block begonnen
// 2 völlig Ende
int zCCutscene::CheckPlayState()
{	
	SolveEventManager(0); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)

	zBOOL blockFinished = (roleEvMList.GetNumInList()!=1) ? actualBlock->IsFinished(roleEvMList) : actualBlock->IsFinished(roleEvMList[0]);
	
	int retVal = (blockFinished) ? CS_BLOCK_NEXT : CS_BLOCK_CONTINUE;
	
	if (retVal==CS_BLOCK_NEXT)
	{
		actualBlockNum++;
		if (blocks.GetNumInList()<=actualBlockNum) 
		{
			if (csLoop())
			{
				actualBlock		= 0;
				actualBlockNum	= 0;				
			} 
			else 
			{
				retVal			= CS_BLOCK_STOP;
				Stop(); 
			}
		}
		
		if (blocks.GetNumInList()>actualBlockNum)
		{
			PrepareBlock();			
			if (roleEvMList.GetNumInList()!=1)	actualBlock->Play(roleEvMList); 
			else 								actualBlock->Play(roleEvMList[0]);
		}
	}
	return retVal;
}



void zCCutscene::PrepareBlock()
{
	actualBlock = blocks[actualBlockNum].block;
	for (int z=0; z<roleEvMList.GetNumInList(); z++)
	{
		SolveEventManager(z);

		if (roleEvMList[z] && !roleEvMList[z]->GetCutscene()) roleEvMList[z]->SetCutscene(this);		
	}
	
	actualBlock->OrganizeRoles(roleVobList,roleList);

}

void zCCutscene::AddRoleOU(zCVob* roleVob)
{		
	zERR_ASSERT(roleVobList.GetNumInList() == roleEvMList.GetNumInList());
	
	zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Adding vob \""+roleVob->GetVobName()+"\" (refCtr before is "+zSTRING(roleVob->GetRefCtr())+") to outputunit");

	if (roleVobList.GetNumInList()<=0) roleVobList.Insert(0);
	if (roleEvMList.GetNumInList()<=0) roleEvMList.Insert(0);

	// Rolle in Liste einfuegen
	roleVobList[0]=roleVob;
	zADDREF_OBJ(roleVob);
	// Eventmanager einfuegen
	roleEvMList[0] = roleVob?roleVob->GetEventManager():0;
	// ... und den Vob gleich auch noch als Hauptrolle merken
	zADDREF_OBJ(roleVob);
	zRELEASE_OBJ(mainRoleVob);
	mainRoleVob=roleVob;

	zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Added vob \""+roleVob->GetVobName()+"\" (refCtr after is "+zSTRING(roleVob->GetRefCtr())+") to outputunit");
}

zBOOL zCCutscene::AddMainRole(zCVob* roleVob)
{
	zERR_ASSERT(roleVobList.GetNumInList() == roleEvMList.GetNumInList());
	
	int what = CheckMainRole(roleVob);
	if (what>=0)
	{		
		zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Added vob \""+roleVob->GetVobName()+"\" (refCtr before is "+zSTRING(roleVob->GetRefCtr())+") to cutscene");

		// Rolle in Liste einfuegen
		zADDREF_OBJ(roleVob);
		zRELEASE_OBJ(roleVobList[what]);
		roleVobList[what]=roleVob;
		// Eventmanager der Rolle
		zCEventManager* aiman = roleVob?roleVob->GetEventManager():0;
		roleEvMList[what]=aiman;
		// ... und den Vob gleich auch noch als Hauptrolle merken	
		zADDREF_OBJ(roleVob);
		zRELEASE_OBJ(mainRoleVob);
		mainRoleVob = roleVob;		
		
		zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Added vob \""+roleVob->GetVobName()+"\" (refCtr after is "+zSTRING(roleVob->GetRefCtr())+") to cutscene");

		return TRUE;
	}
	return FALSE;
}

void zCCutscene::RemoveRole(zCVob* rolevob)
{
	// Rolle in Liste suchen
	int rc=0;
	while (rc<roleVobList.GetNumInList() && roleVobList[rc]!=rolevob) rc++;
	// ... und dann entfernen (Falls Hauptrolle gleich die gesamte Cutscene beenden)
	if (roleVobList[rc]==rolevob)
	{
		if (roleVobList[rc]==mainRoleVob)
		{			
			Stop();						// Cutscene beenden (Alle Rollen werden freigegeben)
		} 
		else 
		{			
			roleEvMList[rc]=0;				// EventManager
			zRELEASE_OBJ(roleVobList[rc]);		// Vob
		}
	}
}
//
// CSCheck(ref scr-result)
//
// Grosse Testmethode, die vor allem das Einsammeln der Rollen uebernimmt und 
// auch Zustaende der Rollen testet.
// In scr_result wird die gewuenschte Aktion zurueckgeliefert.
//
zBOOL zCCutscene::CSCheck	(int & scr_result)
{	
	lastCheckResult = CS_CHECK_OK;
	zBOOL	start	= TRUE;
	int		rc		= 0;
	
	//
	// (1) Einfache Checks
	//

	zCVob*		initVob = GetStage();
	zCWorld*	csworld = 0;

	// 1.a) Ist der InitVob (:TODO: was ist das?) vorhanden?
	if (!initVob) 
	{
		#ifdef _CS_DEBUGINFO
			if (dbplayer) dbplayer->CSDB_Error(NULL, zSTRING("Cutscene-Error: No stageVob found!"));
			zERR_MESSAGE(9,0,"B: CS "+CS_NAME_QUOTED(properties)+": No stageVob found");
		#endif
		lastCheckResult = CS_CHECK_NOSTAGE;
		start			= FALSE;
		goto cscheck_done;
	}	

	// 1.b) Ist der InitVob auch in der Welt eingefuegt?
	csworld = initVob->GetHomeWorld();
	if (!csworld) 
	{
		#ifdef _CS_DEBUGINFO
			if (dbplayer) dbplayer->CSDB_Error(NULL, zSTRING("Cutscene-Error: No World found!"));
		#endif
		lastCheckResult	= CS_CHECK_NOWORLD;
		start			= FALSE;
		goto cscheck_done;
	}	



	//
	// (2) Sammle alle Rollen ein
	//
	
	for (rc=0;rc<roleList.GetNumInList();rc++)
	{
		SolveEventManager(rc); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)

		//
		// Test, ob vorandene Rollen noch valid sind
		//
		if (roleEvMList[rc]!=0) 
		{
			if (properties && !properties->CheckRole(roleList[rc],roleVobList[rc]))
			{
				if (roleVobList[rc]==mainRoleVob)
				{
					Stop();					
				} 
				else 
				{
					roleEvMList[rc]=0;					
					zRELEASE_OBJ(roleVobList[rc]);
				}
				start = FALSE;				
			}
			continue; // weiter, diese Rolle ist ok bzw. wurde gerade entfernt
		}

		// 2.a) Integrierten Vob einfuegen		
		zCVob* localRoleVob = roleList[rc]->GetRoleVob();
		if (localRoleVob && !IsMember(localRoleVob))
		{											
			zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": ---> Role: "+zSTRING(roleList[rc])+ " (integrated, refCtr before is "+zSTRING(localRoleVob->GetRefCtr())+")");
			
			csworld			->AddVob			(localRoleVob);
			localRoleVob	->SetPhysicsEnabled	(FALSE);				// :TODO: Warum dies?
			localRoleVob	->SetSleepingMode	(zVOB_AWAKE_DOAI_ONLY);	// :TODO: Warum dies?				
			
			// localRoleVob	->AddRef(); // kein Addref, weil schon in AddVob vorgenommen (letztes RELEASE löscht Vob aus der Welt)
			roleVobList[rc]	= localRoleVob;			
			roleEvMList[rc]		= localRoleVob->GetEM();
			
			continue; // next role
		}

		// 2.b) Spieler einsammeln
		if (roleList[rc]==CS_PLAYER_ROLENAME)
		{	
			zCVob* playerVob = CatchPlayer();													
			if (playerVob && (!properties || properties->AcceptRole(roleList[rc],playerVob)) )
			{				
				if (!IsMember(playerVob))
				{
					zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": ---> Role: "+zSTRING(roleList[rc])+ " (PLAYER, refCtr before is "+zSTRING(playerVob->GetRefCtr())+")");

					zADDREF_OBJ(playerVob);
					zRELEASE_OBJ(roleVobList[rc]);
					roleVobList[rc]	= playerVob;					
					roleEvMList[rc]		= playerVob->GetEM();
				}
			}
			else // Spieler nicht gefunden oder bereits tot bzw. Member der Cutscene
			{					
				zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": ---> Role: "+zSTRING(roleList[rc])+ " (PLAYER not found)");

				start = FALSE;
				if (IsMember(playerVob))	lastCheckResult = CS_CHECK_PLAYER_ERROR;
				else						lastCheckResult = CS_CHECK_PLAYER_MISSING;				
				
				if (!playerVob) Stop();
			}
			continue; // next role
		}

		
		// 2.c) Wenn die Cutscene schon laeuft: "non required" Rollen nicht mehr einsammeln
		if ( (GetActualBlockNum()>0) && (roleList[rc]->rFlag!=zCCSRole::CSRnonrequired) )  continue;
		

		// 2.d) Allgemeine Rollen einsammeln (Alle passenden raussuchen und dann den naechstbesten nehmen)
		zTCSRoleVobList	resultList;			
		zCVob*			roleVob		= 0;			// gefundener Vob
		zREAL			resultDist	= zREAL_MAX;	// Distanz zwischen InitVob und gefundenem Vob (roleVob)

		csworld->SearchVobListByName(roleList[rc],resultList);
		if (resultList.GetNumInList()>0)
		{
			for (int count=0; count<resultList.GetNumInList(); count++)
			{
				zCVob* vob = resultList[count];
				if (IsMember(vob))												continue;
				if (properties && !properties->AcceptRole(roleList[rc],vob))	continue;				
				
				zVALUE dist = initVob->GetDistanceToVob(*vob);
				if ( (dist<resultDist) && CheckRange(dist) )  { roleVob=vob; resultDist=dist; }
			}
		}
		else // keinen passenden Vob gefunden: Mal schaun, ob er vielleicht gerade deaktiv ist (NSC ausserhalb des Sim.Radius')
		{
			roleVob		= csworld->SearchVobByName(roleList[rc]);								
			resultDist	= roleVob ? initVob->GetDistanceToVob(*roleVob) : 0;
		};

		// gefundenen Vob abchecken
		if (	
				!roleVob			||
				IsMember(roleVob)	||
				(properties && !properties->AcceptRole(roleList[rc],roleVob))
			) 
		{				
			roleVob=0;	// nicht ok
		}

		// Vob gefunden?
		if (roleVob) 
		{				
			zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": ---> Role: "+zSTRING(roleList[rc])+ " (found:"+zSTRING(int(resultDist/100))+"m, refCtr before is "+zSTRING(roleVob->GetRefCtr())+")");

			zADDREF_OBJ(roleVob);
			zRELEASE_OBJ(roleVobList[rc]);
			roleVobList[rc]	= roleVob;				
			roleEvMList[rc]		= roleVob->GetEM();										
		}
		else 
		{
			zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": Role: "+zSTRING(roleList[rc])+ " (not found)");
			#ifdef _CS_DEBUGINFO										
			if (dbplayer) dbplayer->CSDB_Error(NULL, zSTRING("Cutscene-Error: Role not found: ")+zSTRING(roleList[rc]));										
			#endif			
		}
		
		// Vob nicht da, aber required?
		if (!roleEvMList[rc] && (roleList[rc]->rFlag==zCCSRole::CSRrequired)) 
		{
			lastCheckResult = CS_CHECK_ROLE_MISSING;
			start			= FALSE; // Start nicht erlauben.
		}		
	
	} // for
	
	///
	// (3) Start-Bedingungen testen
	///

	start  = start && ( CheckRoles(scr_result));

cscheck_done:;
	
	if (!start && zerr.GetFilterLevel()>=7)
	{
		zSTRING reason;
		switch (lastCheckResult)
		{
			case CS_CHECK_ROLE_ERROR:		reason = "role error";break;
			case CS_CHECK_ROLE_MISSING:		reason = "role missing";break;
			case CS_CHECK_PLAYER_MISSING:	reason = "player missing";break;
			case CS_CHECK_PLAYER_ERROR:		reason = "player error";break;
			case CS_CHECK_ROLECHECK_FAILED: reason = "rolecheck failed";break;
			case CS_CHECK_NOSTAGE:			reason = "missing stage";break;
			case CS_CHECK_NOWORLD:			reason = "missing world";break;
			default:						reason = "unknown reason";
		};

		zERR_MESSAGE(zerr.GetFilterLevel(),0,"B: CS "+CS_NAME_QUOTED(properties)+": CSCheck ... Start disabled, because of "+reason);
	};

	return start;
}



//
// StartPlaying
//
// Wenn das Cutscene-System entschieden hat, dass die Cutscene gespielt werden kann,
// so wird diese Methode aufgerufen. Sie ist die letzte Instanz, die darueber entscheidet,
// ob sie nun wirklich spielen darf.
//
// Hier werden vor allem die Rollen abgecheckt (spielt eine Rolle z.B. gerade eine andere Cutscene?)
// Aber: Eine Globale Cutscene bricht die ambiente Cutscene einer Rolle ab:
//
// Eine abgeleitete Methode sollte diese hier erst aufrufen, wenn Sie damit einverstanden ist,
// dass die Cutscene spielen darf.
//
zBOOL zCCutscene::StartPlaying()
{	
	if (roleEvMList.GetNumInList()==0) return FALSE;

	zBOOL canPlay = TRUE;
	for (int i=0; i<roleEvMList.GetNumInList(); i++)
	{		
		SolveEventManager(i); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)

		// wenn die Rolle bereits an einer Cutscene teilnimmt ...
		if (roleEvMList[i] && roleEvMList[i]->GetCutscene())
		{
			zCCutscene* cs = roleEvMList[i]->GetCutscene();			
			if (IsGlobalCutscene() && !cs->IsGlobalCutscene())
			// andere Cutscene beenden:
			{
				zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": Stopping ambient cutscene of role: "+roleList[i]);
				cs->Stop();			
			}			
			else
			// nicht spielen:
			{
				canPlay = FALSE;
				// Meldung ausgeben:
				zSTRING roleNameStr = "role";								
				if (roleList.GetNumInList()>i)			roleNameStr="role \""+zSTRING(roleList[i])+"\"";
				else if (roleVobList.GetNumInList()>i)	roleNameStr="vob \""+roleVobList[i]->GetVobName()+"\"";				
				zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": Could not start playing: "+roleNameStr+" is playing another cutscene!");				
			};
		}
	}
		
	if (!canPlay) return FALSE;		

	
	//
	// Okidoki, von hier aus kann es losgehen ...
	// 

	#ifdef _CS_DEBUGINFO
	if (dbplayer) dbplayer->CSDB_StartPlaying(this);
	#endif
	
	Reset();

	//
	// Allen Rollen den Start der Cutscene mitteilen
	//

	#ifdef _CALL_EV_MESSAGES_
		for (int z=0; z<roleEvMList.GetNumInList(); z++)
		{		
			if (!roleVobList[z]) continue;
			zCEvMsgCutscene* evmsg = zNEW(zCEvMsgCutscene(zCEvMsgCutscene::EV_CS_STARTPLAY));
			evmsg->SetCutsceneName		(CS_NAME(properties));
			evmsg->SetIsOutputUnit		(!IsCutscene());
			evmsg->SetIsGlobalCutscene	(IsGlobalCutscene());
			evmsg->SetIsMainRole		(roleVobList[z]==mainRoleVob);
			roleVobList[z]->GetEM()->OnMessage(evmsg,NULL);
		}
	#endif

	//
	// Spielen ...
	//
		
	if (roleEvMList.GetNumInList()!=1) 	actualBlock->Play(roleEvMList); 
	else 								actualBlock->Play(roleEvMList[0]);
	
	return TRUE;
}

void zCCutscene::Reset()
{
	actualBlockNum = 0;
	PrepareBlock();

	zERR_MESSAGE(8,0,"B: CS: Cutscene resetted.");
}

void zCCutscene::ClearCutscene()
{
	for (int i=0; i<roleList.GetNumInList();	i++)	zRELEASE_OBJ(roleList[i]);
	for (int j=0; j<roleVobList.GetNumInList();	j++)	zRELEASE_OBJ(roleVobList[j]);	
	for (int k=0; k<roleEvMList.GetNumInList();	k++)	roleEvMList[k]=0;
	
	roleList.EmptyList();
	roleVobList.EmptyList();
	roleEvMList.EmptyList();

	zRELEASE_OBJ(mainRoleVob);
	zRELEASE_OBJ(properties);

	zERR_MESSAGE(8,0,"B: CS: Cutscene cleared.");
};

void zCCutscene::StopRole(zCVob* vob)
{
	if (!vob) return;
		
	zCCSCamera* camVob = dynamic_cast<zCCSCamera*>(vob);
	if (camVob)
	{
		zCCSCamera_EventMsg* evmsg = zNEW(zCCSCamera_EventMsg(zCCSCamera_EventMsg::EV_STOP));
		camVob->GetEM()->OnMessage(evmsg,NULL);
		zERR_MESSAGE(8,0,"B: CS: Stopping CSCamera");
	};
};

zCEventManager*	zCCutscene::SolveEventManager(int z)
{
	if (z<roleVobList.GetNumInList() && roleVobList[z])
	{
		return roleEvMList[z] = roleVobList[z]->GetEventManager(TRUE);
	}		
	return 0;
};

//
// Beenden einer Cutscene
//
void zCCutscene::Stop()
{	
	zERR_MESSAGE(8,0,"B: CS: Stopping cutscene ...");
	if (!mainRoleVob)
	{
		zERR_MESSAGE(8,0,"B: CS: Stopping cutscene failed ... mainrole is NULL");
		return;
	};

	zBOOL	cutsceneHasBeenPlayed = mainRoleVob && (mainRoleVob->GetEM()->GetCutscene() == this);
	
	//
	// Alle Rollen abmelden
	//	
	#ifdef _CALL_EV_MESSAGES_
	for (int z=0; z<roleEvMList.GetNumInList(); z++)
	{		
		SolveEventManager(z); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)

		if (roleEvMList[z] && roleEvMList[z]->GetCutsceneMode()) 
		{						
			if (roleEvMList[z]->GetCutscene()==this)	// wenn im Cutscenemode
			{
				zCVob* vob = roleVobList[z];				
				if (vob && cutsceneHasBeenPlayed)
				{
					zCEvMsgCutscene* evmsg = zNEW(zCEvMsgCutscene(zCEvMsgCutscene::EV_CS_STOP));
					evmsg->SetCutsceneName		(CS_NAME(properties));
					evmsg->SetIsOutputUnit		(!IsCutscene());
					evmsg->SetIsGlobalCutscene	(IsGlobalCutscene());
					evmsg->SetIsMainRole		(roleVobList[z]==mainRoleVob);
					vob->GetEM()->OnMessage(evmsg,NULL);
				};
			}			
		}
	}	
	#endif

	//
	// Alle Rollen wieder freigeben
	// Integrierte Rollen werden dabei (durch RefCouting) automatisch aus der Welt entfernt
	//
	for (z=0; z<roleEvMList.GetNumInList(); z++)
	{				
		SolveEventManager(z); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)

		if (roleEvMList[z] && roleEvMList[z]->GetCutsceneMode()) 
		{	
			if (roleEvMList[z]->GetCutscene()==this)	// wenn im Cutscenemode
			{				
				zERR_ASSERT(roleEvMList[z]->GetHostVob() == roleVobList[z]);
				
				zCVob* vob = roleVobList[z];
				zADDREF_OBJ(vob);
				roleEvMList[z]->Clear();				// CS-Events aus dem Eventmanager rausschmeissen ...
				roleEvMList[z]->SetCutscene(NULL);	// .. und dann (erst) die Cutscene abmelden
				StopRole(vob);					// Behandlung von speziellen Rollen												
				zRELEASE_OBJ(vob);
				zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Release \""+roleEvMList[z]->GetHostVob()->GetVobName()+"\" (refCtr before is "+zSTRING(roleEvMList[z]->GetHostVob()->GetRefCtr())+") from Cutscene.");
			}
			else 
			{
				zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Release of role \""+roleEvMList[z]->GetHostVob()->GetVobName()+"\" failed: Wrong cutscene.");
			}																		
		}		
		// Rolle freigeben (auch Integrierte!!!)
		roleEvMList[z]=0;
		zRELEASE_OBJ(roleVobList[z]);
	}	
	//
	// BlockNr auf das Ende setzen
	//	
	actualBlockNum = blocks.GetNumInList();	
	
	#ifdef _CS_DEBUGINFO
	if (dbplayer) dbplayer->CSDB_Stop(this);
	#endif	
	
	// Hauptrolle freigeben
	if (mainRoleVob) zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Release Mainrole \""+mainRoleVob->GetVobName()+"\" (refCtr before is "+zSTRING(mainRoleVob->GetRefCtr())+") from Cutscene.");
	zRELEASE_OBJ(mainRoleVob);

	zERR_MESSAGE(8,0,"B: CS: Cutscene stopped.");
}

void zCCutscene::Interrupt()
{		
	zBOOL cutsceneHasBeenPlayed = mainRoleVob && (mainRoleVob->GetEM()->GetCutscene() == this);
	
	#ifdef _CALL_EV_MESSAGES_
	for (int z=0; z<roleEvMList.GetNumInList(); z++)
	{		
		SolveEventManager(z); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)

		if (roleEvMList[z] && roleEvMList[z]->GetCutsceneMode()) 
		{						
			if (roleEvMList[z]->GetCutscene()==this)	// wenn im Cutscenemode
			{
				if (roleVobList[z] && cutsceneHasBeenPlayed)
				{
					zCEvMsgCutscene* evmsg = zNEW(zCEvMsgCutscene(zCEvMsgCutscene::EV_CS_INTERRUPT));
					evmsg->SetCutsceneName		(CS_NAME(properties));
					evmsg->SetIsOutputUnit		(!IsCutscene());
					evmsg->SetIsGlobalCutscene	(IsGlobalCutscene());
					evmsg->SetIsMainRole		(roleVobList[z]==mainRoleVob);
					roleVobList[z]->GetEM()->OnMessage(evmsg,NULL);		
				}
			}			
		}
	}	
	#endif
	//
	// Alle Rollen abmelden
	//	
	for (z=0; z<roleEvMList.GetNumInList(); z++)
	{		
		SolveEventManager(z); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)
		
		if (roleEvMList[z] && roleEvMList[z]->GetCutsceneMode()) 
		{						
			if (roleEvMList[z]->GetCutscene()==this)	// wenn im Cutscenemode
			{
				zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Release \""+roleEvMList[z]->GetHostVob()->GetVobName()+"\" from Cutscene (interrupt)");		
				zCVob* vob = roleVobList[z];
				zADDREF_OBJ(vob);
				roleEvMList[z]->Clear();				// CS-Events aus dem Eventmanager rausschmeissen ...
				roleEvMList[z]->SetCutscene(NULL);	// .. und dann (erst) die Cutscene abmelden
				StopRole(roleVobList[z]);			// Behandlung von speziellen Rollen
				zRELEASE_OBJ(vob);
			}
			else 
			{
				zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Release of role \""+roleEvMList[z]->GetHostVob()->GetVobName()+"\" failed: Wrong cutscene.  (interrupt)");
			}
		}		
	}
}

int zCCutscene::GetActualBlockNum()
{ 
	return actualBlockNum; 
}

zBOOL zCCutscene::ResumeActBlock()
{
	zBOOL cutsceneHasBeenPlayed = mainRoleVob && (mainRoleVob->GetEM()->GetCutscene() == this);

	// Überprüfen, ob eine Rolle schon in einer anderen Cutscene spielt ...
	int z;
	for (z = 0;z<roleVobList.GetNumInList();z++)
	{
		roleEvMList[z] = roleVobList[z]->GetEM();
		if (roleEvMList[z]->GetCutscene() && roleEvMList[z]->GetCutscene()!=this) return FALSE;
	};
	
	#ifdef _CALL_EV_MESSAGES_
	for (z=0; z<roleEvMList.GetNumInList(); z++)
	{		
		SolveEventManager(z); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)

		if (roleEvMList[z] && roleEvMList[z]->GetCutsceneMode()) 
		{						
			if (roleEvMList[z]->GetCutscene()==this)	// wenn im Cutscenemode
			{
				if (roleVobList[z] && cutsceneHasBeenPlayed)
				{
					zCEvMsgCutscene* evmsg = zNEW(zCEvMsgCutscene(zCEvMsgCutscene::EV_CS_RESUME));
					evmsg->SetCutsceneName		(CS_NAME(properties));
					evmsg->SetIsOutputUnit		(!IsCutscene());
					evmsg->SetIsGlobalCutscene	(IsGlobalCutscene());
					evmsg->SetIsMainRole		(roleVobList[z]==mainRoleVob);
					roleVobList[z]->GetEM()->OnMessage(evmsg,NULL);		
				}
			}			
		}
	}	
	#endif
	
	// Cutscenemode der Rolle setzen
	for (z=0; z<roleEvMList.GetNumInList(); z++)
	{
		SolveEventManager(z); // EventManager holen, falls nicht da (sicherer nach Loadgame/Levelwechsel, macht aber Probs mit integr.Vobs!!!)
		
		if (roleEvMList[z]) roleEvMList[z]->SetCutscene(this);		
	}

	// gothic 1.26a: savegame-problem. zugriff ausserhalb arraygrösse abgefangen
	if (blocks.GetNumInList()>actualBlockNum)
	{
		PrepareBlock();
	}

	if (!actualBlock) return FALSE;
	
	if (roleEvMList.GetNumInList()!=1)	actualBlock->Play(roleEvMList); 
	else 								actualBlock->Play(roleEvMList[0]);
	
	return TRUE;
}

void zCCutscene::ResumeAtBlock(int nr)
{
	// wird bein Laden des Contextes aufgerufen...
	actualBlockNum = nr;
}

int zCCutscene::PlaySub(zCSTIME b1, zCSTIME b2)
{
	if (IsFinished()) return 0;

//	zBOOL blockFinished = FALSE;
//	if (roleEvMList.GetNumInList()!=1)
//		 blockFinished =actualBlock->IsFinished(roleEvMList);
//	else blockFinished =actualBlock->IsFinished(roleEvMList[0]);
	
	if (roleEvMList.GetNumInList()!=1)	actualBlock->Play(roleEvMList,b1,b2); 
	else 								actualBlock->Play(roleEvMList[0],b1,b2);
	
		
	return CheckPlayState(); // perform checkPlayState only ones;
}

BOOL zCCutscene::IsFinished()
{
	// are all blocks played?
	 return (blocks.GetNumInList()==actualBlockNum);
}

int zCCutscene::NewBlock(int id, int n)
{
	if (id==-1) {
		int retVal;
		zCCSSyncBlock* lBlock = zNEW(zCCSSyncBlock());
		if (n<blocks.GetNumInList())
		{
			blocks.InsertAtPos(zCCSBlockPosition(),n);
			retVal = n;
		} else {
			blocks.Insert(zCCSBlockPosition());
			retVal = blocks.GetNumInList()-1;
		}
		blocks[retVal].block=lBlock;
		return retVal;
	}
	else
		return zCCSBlock::NewBlock(id,n);
}

//
// Fuer den Spacer!!!
// 
void zCCutscene::NewCS(zCCSManager* man)
{
	zERR_ASSERT(man);

	NewRole(zSTRING("_MAINROLE"));	
	NewBlock(-1,0); // SyncBlock einfügen	
	zRELEASE_OBJ(properties);
	properties = man->CreateProperties();
}
void zCCutscene::NewRole(zSTRING & rName)
{
	roleList.Insert(zNEW(zCCSRole(rName)));
}

void zCCutscene::DeleteRole(int n)
{
	if (n<roleList.GetNumInList())
	{
		roleList.RemoveOrderIndex(n);
		
		for (int sc=0; sc<GetNumOfChilds(); sc++)
		{
			zCCSSyncBlock* lsB = dynamic_cast<zCCSSyncBlock*>(GetChild(sc));
			int ac=0;
			while (ac<lsB->GetNumOfChilds())
			{
				if(lsB->GetRoleNumOfChild(ac)==n)
					lsB->DeleteChild(ac);
				else ac++;
			}
			lsB->AssignerCorrection(n);
		}
	}
}

void zCCutscene::RegisterAdditionalVob(zCTree<zCVob> *node)
{
	roleVobList.Insert(node->GetData());
	if (node->GetData()) zADDREF_OBJ(node->GetData());	
		
	#ifdef _CS_DEBUGINFO
		node->GetData()->SetShowVisual(TRUE);
	#else
		node->GetData()->SetShowVisual(FALSE);
	#endif
	zCTree<zCVob>* tree = node->GetFirstChild();	
	while (tree)
	{		
		RegisterAdditionalVob(tree);
		tree = tree->GetNextChild();
	}
}

zCVob* zCCutscene::LoadStage()
{
	if (properties && !(properties->GetStageName().IsEmpty()) && GetStage())
	{
		zCWorld* lw = GetStage()->GetHomeWorld(); // alte stage/npc
		assert(lw!=0);
		zCVob* retVob =  lw->MergeVobSubtree(zSTRING("VOBTREES\\")+properties->GetStageName()+zSTRING(".zen"));
		//if (retVob) retVob->SetPositionWorld(GetStage()->GetPositionWorld()); // was ist mit der Richtung?
		// als ZielVobs mit aufnehmen
		if (retVob) RegisterAdditionalVob(retVob->globalVobTreeNode);
		#ifdef _CS_DEBUGINFO
			else
			{
				if (dbplayer) dbplayer->CSDB_Warning(NULL,zSTRING("Cutscene : Cant find stage"));		
			}
		#endif
		
		return retVob;
		
	} 
	else 
	{
		return 0;
	}
}
zCVob* zCCutscene::CatchPlayer(zCVob* initVob)
{
	if (!initVob) return NULL;

	zCNetVobControl* nvCtrl = initVob->GetEM()->GetNetVobControl(TRUE);
	if (nvCtrl) 
	{
		return nvCtrl->GetCtrlPlayer()->GetPlayerVob();
	}	
	else if (zCPlayerInfo::GetActivePlayer())
	{
		return zCPlayerInfo::GetActivePlayer()->GetPlayerVob();
	}
	else 
	{		
		return NULL;
	}
}


//* Block position class

zCCSBlockPosition::zCCSBlockPosition() : position(0.0), block(0) {}
zCCSBlockPosition::zCCSBlockPosition(zCCSBlockBase* _bl) : position(0.0), block(_bl) {}
zCCSBlockPosition::zCCSBlockPosition( zCSTIME _pos, zCCSBlockBase* _bl) : position(_pos), block(_bl) {}
zCCSBlockPosition::~zCCSBlockPosition() { /*zRELEASE_OBJ(refBlock);*/ }
zCCSBlockPosition& zCCSBlockPosition::operator=(const zCCSBlockPosition& blp)
{
	position	= blp.position;
	block		= blp.block;	
	return *this;
}




//
// Archiver-Methoden
//

// zCCSBlockBase

void zCCSBlockBase::Archive(zCArchiver &arc)
{
	zCObject::Archive (arc);
}
void zCCSBlockBase::Unarchive(zCArchiver &arc)
{
	zCObject::Unarchive (arc);
}

// zCCSAtomicBlock

void zCCSAtomicBlock::Archive(zCArchiver &arc)
{
	zCCSBlockBase::Archive (arc);
	arc.WriteObject	(command);	
	// arc.WriteBool	("synchronized",synchronized);
}
void zCCSAtomicBlock::Unarchive(zCArchiver &arc)
{
	zCCSBlockBase::Unarchive (arc);
	command = dynamic_cast<zCEventMessage*>(arc.ReadObject());	
	
	// synchronized=TRUE;
	// arc.ReadBool("synchronized",synchronized);
}

// zCCSBlock

void zCCSBlock::Archive(zCArchiver &arc)
{
	zCCSBlockBase::Archive (arc);

	arc.WriteString	("blockName",roleName);
	
	arc.WriteInt	("numOfBlocks",blocks.GetNumInList());
	zSTRING chunckName;
	for (int c=0; c<blocks.GetNumInList(); c++)
	{
		chunckName = "subBlock"+zSTRING(c);
		arc.WriteFloat	(chunckName.ToChar(),blocks[c].position);						
		arc.WriteObject	(blocks[c].block);		
	}	
}
void zCCSBlock::Unarchive(zCArchiver &arc)
{
	zCCSBlockBase::Unarchive (arc);

	arc.ReadString("blockName",roleName);
	
	int count=0;arc.ReadInt("numOfBlocks",count);
	
	zSTRING chunckName;
	for (int c=0; c<count; c++)
	{
		blocks.Insert(zCCSBlockPosition());		

		chunckName = "subBlock"+zSTRING(c);		
		arc.ReadFloat(chunckName.ToChar(),blocks[c].position);
						
		blocks[c].block		= static_cast<zCCSBlock*>(arc.ReadObject());		
	}
}

// zCCSSyncBlock

void zCCSSyncBlock::Archive(zCArchiver &arc)
{
	zCCSBlock::Archive(arc);
	
	arc.WriteInt("numOfAss",roleAss.GetNumInList());
	
	zSTRING chunckName;
	zSTRING roleAssN("roleAss");
	for (int i=0; i<roleAss.GetNumInList(); i++)
	{
		chunckName = roleAssN+zSTRING(i);
		arc.WriteInt(chunckName.ToChar(),roleAss[i]);
	}
}
void zCCSSyncBlock::Unarchive(zCArchiver &arc)
{
	zCCSBlock::Unarchive(arc);
	
	int count=0;arc.ReadInt("numOfAss",count);
	
	zSTRING chunckName;
	zSTRING roleAssN("roleAss");
	int rInt=0;
	for (int i=0; i<count; i++)
	{
		chunckName = roleAssN+zSTRING(i);
		arc.ReadInt(chunckName.ToChar(),rInt);
		roleAss.InsertEnd(rInt);
	}
}

// zCCutscene

void zCCutscene::Archive(zCArchiver &arc)
{
	zCCSBlock::Archive(arc);
	
	// Properties
	arc.WriteObject(properties);

	// Rollenliste
	arc.WriteInt("numOfRoles", roleList.GetNumInList());
	for (int i=0; i<roleList.GetNumInList(); i++)
	{
		arc.WriteObject(roleList[i]);
	}
	
	// Vobliste
	arc.WriteInt("numOfRoleVobs", roleVobList.GetNumInList());
	for (int j=0; j<roleVobList.GetNumInList(); j++)
	{
		arc.WriteObject(roleVobList[j]);
	}
	
	// Hauptrolle nochmal extra
	arc.WriteObject	("mainRoleVob",			mainRoleVob);
}

void zCCutscene::Unarchive(zCArchiver &arc)
{		
	zCCSBlock::Unarchive(arc);	

	zERR_ASSERT(roleVobList.GetNumInList() == roleEvMList.GetNumInList());
	
	// Aufräumen	
	ClearCutscene();
	
	zERR_ASSERT(roleVobList.GetNumInList() == roleEvMList.GetNumInList());
		
	// Properties
	zRELEASE_OBJ(properties);
	properties = dynamic_cast<zCCSProps*>(arc.ReadObject());			
	if (properties) SetObjectName(properties->GetName());
	
	// Rollenliste
	int rc = arc.ReadInt("numOfRoles");
	while (rc>0)
	{
		zCCSRole* role = dynamic_cast<zCCSRole*>(arc.ReadObject());
		
		roleList	.InsertEnd(role);				
		rc--;
	}
	
	// Vobliste
	rc = arc.ReadInt("numOfRoleVobs");
	while (rc>0)
	{
		zCVob* roleVob = dynamic_cast<zCVob*>(arc.ReadObject());

		roleVobList.InsertEnd(roleVob);
		roleEvMList.InsertEnd(0);				// Reserve
		
		rc--;
	}

	// Hauptrolle
	zRELEASE_OBJ(mainRoleVob);
	mainRoleVob = dynamic_cast<zCVob*>(arc.ReadObject("mainRoleVob"));
					
	zERR_ASSERT(roleVobList.GetNumInList() == roleEvMList.GetNumInList());
}


zCVob* zCCutscene::FirstRoleUsed()
{
	int z=0;
	while (z<roleEvMList.GetNumInList())
	{
		if (roleEvMList[z]->GetCutsceneMode()) 
			return roleVobList[z];
	}

	return 0;
}

#ifdef COMPILING_SPACER
void zCCSBlock::SetInfo(zSTRING & str)
{
	if ((blocks.GetNumInList() > 0) && blocks[0].block)
	{
		blocks[0].block->SetInfo(str);
	};
};
#endif


zBOOL zCCutscene::CheckRoles(int& scr_result)
{
	zBOOL start = TRUE;
	scr_result = SCR_RESULT_NOTHING;
	if (!properties) return TRUE;

	int rc=0;
	while (rc<roleVobList.GetNumInList() && start)
	{			
		if (roleVobList[rc]) 
		{
			start = start && properties->CheckRole(roleList[rc],roleVobList[rc]);
			if (!start) scr_result = properties->GetCheckRoleResult();				
		}
		rc++;			
	}
		
	if (!start) lastCheckResult = CS_CHECK_ROLECHECK_FAILED;
	return start;
};


void zCCutscene::PrintDebugInfo(const zSTRING& parm)
{	
};

zCCutscene::zTCSCheckResult zCCutscene::GetLastCheckResult(zSTRING& result)
{
	switch (lastCheckResult)
	{
		case CS_CHECK_UNKNOWN:			 result="none";break;
		case CS_CHECK_OK:				 result="O.K.";break;
		case CS_CHECK_ROLE_ERROR:		 result="RoleErr";break;
		case CS_CHECK_ROLE_MISSING:		 result="RoleMiss";break;
		case CS_CHECK_PLAYER_MISSING:	 result="PlayerMiss";break;
		case CS_CHECK_PLAYER_ERROR:		 result="PlayerErr";break;
		case CS_CHECK_ROLECHECK_FAILED:	 result="RoleCheck";break;
		case CS_CHECK_NOSTAGE:			 result="NoStage";break;
		case CS_CHECK_NOWORLD:			 result="NoWorld";break;
		default:						 result="N/A";break;
	};
	return lastCheckResult;
};

zBOOL zCCutscene::TryToCancel()
{
	if
	(
		properties && 
		IsGlobalCutscene() && 
		(			
			GetActualBlockNum()>=properties->GetNumLockedBlocks()
		)
	)
		{
			Stop();
			return TRUE;
		}
		else
		{
			return FALSE;
		}	
};

/* -----------------------------------------------------------
  Iterieren einer serialisierten Form der Cutscnene
  (alle Bloecke in einem Array)
  Methoden zum iterieren der Messages und Blöcke.

  Beispiel:

  > zTCSBlockPosition pos;
  > pos = cutscene->GetFirstBlockPosition();
  > while (msg = cutscene->GetNextMessage(pos))
  > {
  > 	// do something
  > };
  ------------------------------------------------------------ */

zTCSBlockPosition zCCutscene::GetFirstBlockPosition()
{
	zTCSBlockPosition pos;
	SerializeCutscene(this,pos);
	pos.index = 0;	
	return pos;
};

zCEventMessage*	zCCutscene::GetNextMessage (zTCSBlockPosition& pos)
{
	zCCSBlockBase* block=0;
	do
	{		
		// Block holen, dabei gleich den Index erhoehen (danach!!)
		if (pos.index<pos.numInList) 
			block = pos.flatData.GetSafe( pos.index++ );	

		// Falls EventMessage vorhanden: zurueckgeben, sonst weitermachen
		if (block && block->GetCommand()) 
			return block->GetCommand();
	} 
	while (pos.index<pos.numInList); 

	return 0;	
};

zCCSBlockBase* zCCutscene::GetNextBlock (zTCSBlockPosition& pos)
{
	zCCSBlockBase* block=0;
	do
	{		
		// Block holen, dabei gleich den Index erhoehen (danach!!)
		if (pos.index<pos.numInList) 
			block = pos.flatData.GetSafe( pos.index++ );	
		
		if (block) return block;
	} 
	while (pos.index<pos.numInList); 

	return 0;	
};


void zCCutscene::SerializeCutscene(zCCutscene* cs, zTCSBlockPosition& posData)
{	
	posData.flatData.Insert(cs);
	int z=0;
	zCCSBlockBase* block = cs->GetChild(z);
	while (block) 
	{		
		SerializeBlock(block, posData);
		z++;
		block = cs->GetChild(z);
	}	

	posData.index		= 0;
	posData.numInList	= posData.flatData.GetNumInList();
}

void zCCutscene::SerializeBlock(zCCSBlockBase* bl, zTCSBlockPosition& posData)
{		
	posData.flatData.Insert(bl);
	int z=0;
	zCCSBlockBase* block = bl->GetChild(z);
	while (block) 
	{		
		SerializeBlock(block,posData);
		z++;
		block = bl->GetChild(z);
	}
}
