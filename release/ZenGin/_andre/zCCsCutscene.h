/****************************************************************
* Cutscene (Header)				     							*
* Datei         : zCCutscene.h									*
* Projekt       : Engine										*
* Autor         : Andre Schrieber								*
* Version       : 0.002											*
* last modified : 26.09.99										*
* erstellt      : 20.12.98										*
*****************************************************************
- bekannte Bugs:
*****************************************************************
- moegliche Optimierungen:
*****************************************************************
- neue Funktionalitaeten seit 
  
- neue Funktionalitaeten seit 
 
*****************************************************************
- noch fehlende Funktionalitaeten:
*****************************************************************
- Kommentare:
 
****************************************************************/

 
#ifndef _zCCutscene_H_
#define _zCCutscene_H_


#include "zDisk.h"
#include "zContainer.h"

#include "zArchiver.h"

#include "zCCSProps.h"
#include "zCSCamera.h"
#include "ztools.h"

class zCVob;
class zCEventManager;
class zCEventMessage;
class zCCSBlockPosition;
class zCCSManager;
class zCCSBlockBase;
class zCCSPlayer;


// damit wird die Zeit gemessen
typedef zREAL		zCSTIME;

extern const zSTRING CS_PLAYER_ROLENAME;
extern const zSTRING CS_MAIN_ROLENAME;

#define CS_NAME(prop)			((prop)?prop->GetName():"??")
#define CS_NAME_QUOTED(prop)	("\""+CS_NAME(prop)+"\"")

struct zTCSBlockPosition
{
	zCArray<zCCSBlockBase*> flatData;
	int						index;
	int						numInList;
};

class zCEvMsgCutscene : public zCEventMessage
{
zCLASS_DECLARATION	(zCEvMsgCutscene)
public:
	enum TCutsceneSubType {
		EV_CS_STARTPLAY	= 0,
		EV_CS_STOP,		
		EV_CS_INTERRUPT,
		EV_CS_RESUME,		
		EV_CS_MAX
	};
	
	zCEvMsgCutscene(TCutsceneSubType _subtype);
	virtual ~zCEvMsgCutscene();

	void	SetCutsceneName		(zSTRING _csName)	{ csName=_csName;csName.Upper();};
	void	SetIsOutputUnit		(zBOOL ou)			{ isOutputUnit = ou;			};
	void	SetIsGlobalCutscene	(zBOOL global)		{ isGlobalCutscene = global;	};
	void	SetIsMainRole		(zBOOL main)		{ isMainRole = main;			};

	zSTRING	GetCutsceneName	()						{ return csName;				};
	zBOOL	IsOutputUnit	()						{ return isOutputUnit;			};
	zBOOL	IsGlobalCutscene()						{ return isGlobalCutscene;		};
	zBOOL	IsMainRole		()						{ return isMainRole;			};

	virtual	zBOOL		IsHighPriority		()		{ return TRUE;					};
	
	virtual void		Delete				()		{ deleted = TRUE;				};
	virtual zBOOL		IsDeleted			()		{ return deleted;				};

	virtual int			MD_GetNumOfSubTypes	();
	virtual zSTRING		MD_GetSubTypeString	(int n);			
	
#ifdef COMPILING_SPACER
	virtual zSTRING		MD_GetInfo			();
	virtual void		MD_SetInfo			(const zSTRING & str);
#endif

protected:

	// Std-Con
	zCEvMsgCutscene() { };

	zSTRING csName;
	zBOOL	isOutputUnit;
	zBOOL	isGlobalCutscene;
	zBOOL	isMainRole;
	zBOOL	deleted;
};


class zCCSRole : public zCObject, public zSTRING
{
	zCLASS_DECLARATION	(zCCSRole)
public:
	zCCSRole			();
	zCCSRole			(zSTRING & name);		
	virtual ~zCCSRole	();
	
	void	SetRoleVob	(zCVob* rVob);
	zCVob*	GetRoleVob	();
	
	enum 			zTCSRoleFlag { CSRrequired, CSRdelayable, CSRnonrequired };	
	zBOOL 			mustBeAlive;
	zTCSRoleFlag 	rFlag;

protected:
	// Archiver-Methoden
	virtual void Archive	(zCArchiver &arc);
	virtual void Unarchive	(zCArchiver &arc);	
	
protected:
	zCVob* roleVob;
};

typedef zCArray<zCCSRole*>			zTCSRoleList;
typedef zCArray<zCVob*>				zTCSRoleVobList;
typedef zCArray<zCEventManager*>	zTCSRoleEMList;

// Metadata struktures


class zCCSBlockBase : public zCObject {
zCLASS_DECLARATION	(zCCSBlockBase)
public:
	zCCSBlockBase				();
	
	virtual ~zCCSBlockBase		();
	
	virtual zCCSBlockBase *GetChild(int n);
	
	virtual void OrganizeRoles	(zCArray<zCVob*> &roles, zTCSRoleList &rolesN)=0;
	virtual zSTRING GetRoleName	();
	virtual void	SetRoleName	(zSTRING & name);

	virtual void Play			(const zTCSRoleEMList &)=0;
	virtual void Play			(const zTCSRoleEMList &, zCSTIME, zCSTIME)=0;
	virtual void Play			(zCEventManager*)=0;
	virtual void Play			(zCEventManager*, zCSTIME, zCSTIME)=0;

	virtual zCSTIME GetMinTime	()=0;
	virtual zBOOL IsFinished	(const zTCSRoleEMList &)=0;
	virtual zBOOL IsFinished	(zCEventManager*)=0;

protected:
	// Archiver-Methoden
	virtual void	Archive		(zCArchiver &arc);
	virtual void	Unarchive	(zCArchiver &arc);

public:
	virtual zCEventMessage*	GetCommand() { return NULL; };

	// für den Editor
#ifdef COMPILING_SPACER
	virtual zSTRING GetInfo		()=0;
	virtual	void	SetInfo		(zSTRING & str);
	virtual zBOOL	GetDBFlag	();
	virtual void	SetDBFlag	(zBOOL f);
#endif
	virtual int		NewBlock	(int id, int n=0);
	virtual void	InsertBlock	(zCCSBlockBase* bl, int n=0) {};
	virtual void	DeleteChild	(int pos);
	virtual int		GetNumOfChilds();
	virtual int		GetRoleNumOfChild(int pos);
	virtual void	BlockCorrection();
	virtual void	BlockAsFocus(int n);
	virtual zCCSBlockPosition*	GetChildPos	(int nr);
};

class zCCSAtomicBlock : public zCCSBlockBase {
zCLASS_DECLARATION	(zCCSAtomicBlock)
private:
	zCVob* roleVob;

protected:
	zCEventMessage* commandRef;
	zCEventMessage*	command;

	// zBOOL			synchronized;

	enum { EVCOM_NOTSTARTED, EVCOM_PLAYING, EVCOM_FINISHED } commandState;

	// Archiver-Methoden
	virtual void	Archive		(zCArchiver &arc);
	virtual void	Unarchive	(zCArchiver &arc);

public:
	zCCSAtomicBlock				();
	virtual ~zCCSAtomicBlock	();

	virtual void OrganizeRoles	(zCArray<zCVob*> &roles, zTCSRoleList &rolesN);

	virtual void Play			(const zTCSRoleEMList &aiman);
	virtual void Play			(const zTCSRoleEMList &aiman, zCSTIME, zCSTIME);
	virtual void Play			(zCEventManager* aiman);
	virtual void Play			(zCEventManager* aiman, zCSTIME b1, zCSTIME b2);
	
	virtual zCSTIME GetMinTime	();
	virtual zBOOL IsFinished	(const zTCSRoleEMList &aiman) { return TRUE; };
	virtual zBOOL IsFinished	(zCEventManager* aiman);	

	void	SetSynchronized		(zBOOL sync)		{ /*synchronized=sync;*/ };
	zBOOL	IsSynchronized		()					{ return TRUE;/*return synchronized;*/ };

	// für den Editor
#ifdef COMPILING_SPACER
	virtual zSTRING GetInfo		();
	virtual void	SetInfo		(zSTRING & str);
	zBOOL	dbflag;
	virtual zBOOL	GetDBFlag	();
	virtual void	SetDBFlag	(zBOOL f);	
#endif
	zCEventMessage*	GetCommand() { return command; };
	void			SetCommand(zCEventMessage* msg) { command=msg; };

};


class zCCSBlockPosition {
public:
	zCSTIME			position;
	zCCSBlockBase*	block;	

	zCCSBlockPosition();
	zCCSBlockPosition( zCCSBlockBase* _bl );
	zCCSBlockPosition( zCSTIME _pos, zCCSBlockBase* _bl );
	virtual ~zCCSBlockPosition();

	zCCSBlockPosition& operator=(const zCCSBlockPosition& blp);
};


class zCCSBlock : public zCCSBlockBase 
{

	zCLASS_DECLARATION	(zCCSBlock)

	friend class zCCSCutsceneContext;

protected:

	zCArray<zCCSBlockPosition>	blocks;  // Definition blocks[0] ist FoKus und hat eine implementationstechnische Besonderheit
	zSTRING roleName;
	
	// Archiver-Methoden
	virtual void	Archive		(zCArchiver &arc);
	virtual void	Unarchive	(zCArchiver &arc);

public:

	zCCSBlock					();
	virtual ~zCCSBlock			();

	virtual zCCSBlockBase *GetChild(int n);

	virtual void OrganizeRoles	(zCArray<zCVob*> &roles, zTCSRoleList &rolesN);
	virtual zSTRING GetRoleName	();
	virtual void	SetRoleName	(zSTRING & name);

	virtual void Play			(const zTCSRoleEMList &aiman);
	virtual void Play			(const zTCSRoleEMList &aiman, zCSTIME b1, zCSTIME b2);
	virtual void Play			(zCEventManager* aiman);
	virtual void Play			(zCEventManager* aiman, zCSTIME b1, zCSTIME b2);

	virtual zCSTIME GetMinTime	();
	virtual zBOOL IsFinished	(const zTCSRoleEMList &aiman);
	virtual zBOOL IsFinished	(zCEventManager* aiman);
	
	// für den Editor
#ifdef COMPILING_SPACER
	virtual zSTRING	GetInfo		();
	virtual void	SetInfo(zSTRING & str);
#endif
	virtual zCCSBlockPosition* GetChildPos(int nr);
	virtual void	InsertBlock	(zCCSBlockBase* bl, int n=0);
	virtual int		NewBlock	(int id, int n=0);
	virtual int		GetNumOfChilds();
	virtual void	BlockCorrection();
	virtual void	BlockAsFocus(int n);
	virtual void	DeleteChild(int pos);

};

class zCCSSyncBlock : public zCCSBlock
{
zCLASS_DECLARATION	(zCCSSyncBlock)
private:
	zCArray<int> roleAss;

public:
	zCCSSyncBlock();
	virtual ~zCCSSyncBlock();

	virtual void Play			(zCEventManager* aiman);
	virtual void Play			(const zTCSRoleEMList &aiman);
	virtual void Play			(const zTCSRoleEMList &aiman, zCSTIME b1, zCSTIME b2);
	virtual zBOOL IsFinished	(const zTCSRoleEMList &aiman);

protected:
	// Archiver-Methoden
	virtual void	Archive		(zCArchiver &arc);
	virtual void	Unarchive	(zCArchiver &arc);

public:
	// für den Editor
	virtual int		GetRoleNumOfChild(int pos);
	virtual int		NewBlock	(int id, int n=0);
	virtual void	InsertBlock	(zCCSBlockBase* bl, int n=0);
	virtual void	BlockAsFocus(int n);
	virtual void	DeleteChild(int pos);

	void			AssignerCorrection(int n);
};




class zCCutscene : public zCCSBlock 
{
zCLASS_DECLARATION	(zCCutscene)
public:

	zCCutscene				();
	virtual ~zCCutscene		();

	enum zTCSCheckResult 
	{ 
		CS_CHECK_UNKNOWN,
		CS_CHECK_OK,
		CS_CHECK_ROLE_ERROR,
		CS_CHECK_ROLE_MISSING,
		CS_CHECK_PLAYER_MISSING,
		CS_CHECK_PLAYER_ERROR,
		CS_CHECK_ROLECHECK_FAILED,
		CS_CHECK_NOSTAGE,
		CS_CHECK_NOWORLD,
		CS_CHECk_MAX
	} 
	lastCheckResult;
		
	zTCSRoleList				roleList;		// List of roles		
	zTCSRoleEMList				roleEvMList;	
	zTCSRoleVobList				roleVobList;
	zCVob*						mainRoleVob;
	
	zCCSProps*		properties;	// StartConditions

	zTCSCheckResult GetLastCheckResult(zSTRING& result);
	
	void			SetRoleListForDebugging(zTCSRoleList & roleN);	
	void			SaveRolesVobs	(zCBuffer & buffer);
	void			RestoreRoleVobs	(zCBuffer & buffer);	
	
	virtual zBOOL	AddMainRole		(zCVob* roleVob);
	virtual void	AddRoleOU		(zCVob* roleVob);
	virtual void	RemoveRole		(zCVob* rolevob);

	void			SetProperties	(zCCSProps* props)	{ properties = props; };
	zCCSProps*		GetProperties	()					{ return properties; };

	virtual	void	SetOwnerPlayer	(zCCSPlayer* player); 

	virtual void	Reset			();
	
	virtual void	ClearCutscene	();
	
	virtual zBOOL	StartPlaying	();	
	virtual void	Stop			();
	virtual void	StopRole		(zCVob* vob);
	virtual void	Interrupt		();
	virtual zBOOL	ResumeActBlock	();  // resumes the cs at actual block	

	zBOOL			csLoop			() { return properties?properties->Loop():FALSE; };

	// 0=nix 1=neuer block 2=ganz ende
	virtual int		PlaySub			(zCSTIME b1, zCSTIME b2); // ist true, wenn dabei ein neuer block gestartet wurde
	
	// für den Editor
	virtual void	NewCS			(zCCSManager* man);
	virtual int		NewBlock		(int id, int n=0);

	int				GetNumOfRoles	()		{ return roleList.GetNumInList(); };
	zSTRING			GetRoleName		(int n) { return roleList[n]; };
	zCVob*			GetMainRole		()		{ return mainRoleVob; };	

	int				GetActualBlockNum();

	zBOOL			IsGlobalCutscene()	{ return properties?properties->IsGlobalCutscene():FALSE; };
	virtual zBOOL	IsCutscene		()	{ return TRUE; };
	virtual zBOOL	IsFinished		();
	zBOOL			HasToBeTriggered()	{ return properties?properties->HasToBeTriggered():FALSE; };	
	zBOOL			TryToCancel		();

	void			NewRole			(zSTRING & rName);
	void			DeleteRole		(int n);	

	zBOOL			IsMember		(zCVob* vob);

	zCVob*			FirstRoleUsed	();

	virtual void	PrintDebugInfo	(const zSTRING& parm="");
	
	zTCSBlockPosition	GetFirstBlockPosition	();
	zCEventMessage*		GetNextMessage			(zTCSBlockPosition& pos);
	zCCSBlockBase*		GetNextBlock			(zTCSBlockPosition& pos);

	void			SerializeCutscene(zCCutscene* cs, zTCSBlockPosition& posData);

protected:
	
	zCEventManager*	SolveEventManager(int z);

	void			SerializeBlock(zCCSBlockBase* bl, zTCSBlockPosition& posData);

	void			RegisterAdditionalVob	(zCTree<zCVob> *node);
	int				CheckMainRole			(zCVob* vob);		
	virtual zBOOL	CheckRoles				(int& scr_result);

	virtual zBOOL	CSCheck				(int & scr_result);
	zBOOL			CheckDistance		(zREAL distance) { return (properties ? properties->CheckDistance(distance) : TRUE); };
	zBOOL			CheckRange			(zREAL range)    { return (properties ? properties->CheckRange(range) : TRUE); };
	int				CheckPlayState		(); // return an integer describing the Status
 
	virtual zCVob*	GetStage			();
	virtual zCVob*	LoadStage			();
	virtual zCVob*	CatchPlayer			(zCVob* initVob=0);	
			
	virtual void	PrepareBlock		(); // overrideable is called, when a block is readied to Play
	void			ResumeAtBlock		(int nr);  // resumes the cs at that block	

	// Archiver-Methoden
	virtual void	Archive				(zCArchiver &arc);
	virtual void	Unarchive			(zCArchiver &arc);

	zCCSPlayer* ownerPlayer;	

private:		
	int				actualBlockNum;
	zCCSBlockBase*	actualBlock;
	
};

#endif