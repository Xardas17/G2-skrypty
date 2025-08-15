/******************************************************************************** 
 
     $Workfile:: oInfo.h              $                $Date:: 18.01.01 19:33   $
     $Revision:: 14                   $             $Modtime:: 18.01.01 19:31   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oInfo.h $
 * 
 * 14    18.01.01 19:33 Keskenti
 * 
 * 13    8.01.01 19:26 Keskenti
 * 
 * 12    13.12.00 14:16 Keskenti
 * 
 * 11    8.12.00 18:13 Keskenti
 * 
 * 10    25.10.00 17:45 Keskenti
 * 
 * 9     21.10.00 1:14 Keskenti
 * 
 * 8     20.10.00 17:07 Keskenti
 * 
 * 7     19.10.00 14:00 Keskenti
 * 
 * 6     18.10.00 19:10 Keskenti
 * 
 * 5     4/10/00 15:28 Luesebrink
 * 
 * 4     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 7     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 6     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 5     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 4     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

// Informations

#ifndef __OINFO_H__
#define __OINFO_H__

#include "zString.h"
#include "zList.h"

// Forwards
class zCParser;

class oCNpc;
class oCInfo;

const int INF_ANSWER_MAX	= 6;

enum {	
		INF_ANSWER_DEFAULT	= 0, 
		INF_ANSWER_HERO		= 1, 
		INF_ANSWER_FIGHTER	= 2,
		INF_ANSWER_MAGE		= 3,
		INF_ANSWER_THIEF	= 4,
		INF_ANSWER_PSIONIC	= 5
};

class oCInfoChoice
{
public:
	zSTRING Text	;
	int		Function;

	oCInfoChoice( zSTRING& strText, int nFunc )
	{
		this->Text		= strText;
		this->Function	= nFunc	 ; 
	}

	~oCInfoChoice() {;}
};

class oCInfoManager;
typedef zCList< oCInfoChoice > zCListInfoChoices;

class oCInfo {
	friend class oCInfoManager;
public:
	oCInfo										();
	~oCInfo										();
												
	void				SetInstance				(int instance);
	int					GetInstance				();
												
	int					GetNpcID				();
	int					GetConditionFunc		();
	zBOOL				WasTold					();
	void				SetTold					(zBOOL f);
	zBOOL				IsImportant				()									{ return pd.important;	}
	zBOOL				IsTrade					()									{ return pd.trade	 ;	}
	zBOOL				IsPermanent				()									{ return pd.permanent;	}
												
	zBOOL				DoCheck					();		// Selfcheck (data) -> TRUE : ok
	int					GetDataSize				();
	void*				GetDataAdr				();
	zSTRING&			GetText					();
												
	zBOOL				InfoConditions			();
	void				Info					();
												
	void				AddChoice				( zSTRING strText, int nFunc )		;
	void				RemoveChoice			( zSTRING strText )					;
	void				RemoveAllChoices		()									;
	zCListInfoChoices&	GetChoices				()									{ return listChoices;					}
	int					GetChoiceCount			()									{ return listChoices.GetNumInList();	}

	oCInfo*				next;
	zSTRING				name		;

	virtual void		Archive					( zCArchiver &arc );
	virtual void		Unarchive				( zCArchiver &arc );
	virtual void		RestoreParserInstance	();
private:		
	#pragma pack(push,1)
	struct Tpd {							// Parserdata
		int				npc			;		// Npc - Instance 
		int				nr			;		// ID
		zBOOL			important	;		// Is it an important Info
		int				conditions	;		// Condition
		int				information	;		// function to be executed 
		zSTRING			description	;		// text that will be displaye by informationmanager
		zBOOL			trade		;		// Info will cause infomanmager to start trademanager
		zBOOL			permanent	;		// Indicates that info will not be deleted after being told
	} pd;
	#pragma pack(pop)

	zBOOL				told		;		// already told -> delete ?	
	int					instance	;		// InstanceNr of Info
//	zSTRING				name		;
	zCListInfoChoices	listChoices	;
};

typedef zCListSort< oCInfo > zCListInfos;

class oCInfoManager {
	
public:
	oCInfoManager								( zCParser* p );
	~oCInfoManager								( );
												
	// Get next matching Information			
	oCInfo*		GetInformation					( int infoInstance  );
	oCInfo*		GetInformation					( oCNpc* ask, oCNpc* npc, zBOOL important = FALSE );
	int			GetInfoCount					( oCNpc* pNpcAsker, oCNpc* pNpcAsked );
	int			GetInfoCountImportant			( oCNpc* pNpcAsker, oCNpc* pNpcAsked );
	int			GetInfoCountUnimportant			( oCNpc* pNpcAsker, oCNpc* pNpcAsked );
	oCInfo*		GetInfo							( oCNpc* pNpcAsker, oCNpc* pNpcAsked, int nInfo );
	oCInfo*		GetInfoImportant				( oCNpc* pNpcAsker, oCNpc* pNpcAsked, int nInfo );
	oCInfo*		GetInfoUnimportant				( oCNpc* pNpcAsker, oCNpc* pNpcAsked, int nInfo );
	zBOOL		InformationTold					( int infoInstance );
												
	virtual void		Archive					(zCArchiver &arc);
	virtual void		Unarchive				(zCArchiver &arc);
	virtual void		RestoreParserInstances	();
private:
	static int CompareInfos( oCInfo* pInfoLeft, oCInfo* pInfoRight )	{	if		( ( ! pInfoLeft )  || ( ! pInfoRight )	)	return  0;
																			if		( pInfoLeft->pd.nr  > pInfoRight->pd.nr )	return  1;
																			else if ( pInfoLeft->pd.nr == pInfoRight->pd.nr )	return  0;
																			else												return -1;	}
	// List of all (relevant) Infos
	zCListInfos infoList;	
	// Inits and handles all scripted Infos
	zCParser *p;
	// Statics
	static zBOOL size_checked;
};

#endif