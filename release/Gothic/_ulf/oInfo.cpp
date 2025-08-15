/******************************************************************************** 
 
     $Workfile:: oInfo.cpp            $                $Date:: 18.01.01 19:33   $
     $Revision:: 22                   $             $Modtime:: 18.01.01 19:33   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oInfo.cpp $
 * 
 * 22    18.01.01 19:33 Keskenti
 * 
 * 21    18.01.01 1:09 Speckels
 * 
 * 20    9.01.01 13:00 Keskenti
 * 
 * 19    8.01.01 19:26 Keskenti
 * 
 * 17    19.12.00 18:51 Keskenti
 * 
 * 16    13.12.00 14:16 Keskenti
 * 
 * 15    8.12.00 18:13 Keskenti
 * 
 * 14    26.10.00 14:04 Moos
 * 
 * 13    25.10.00 17:45 Keskenti
 * 
 * 12    21.10.00 1:14 Keskenti
 * 
 * 11    20.10.00 17:07 Keskenti
 * 
 * 10    19.10.00 14:00 Keskenti
 * 
 * 9     18.10.00 19:10 Keskenti
 * 
 * 8     11/10/00 15:28 Luesebrink
 * 
 * 7     4/10/00 15:28 Luesebrink
 * 
 * 6     2.08.00 14:25 Wohlers
 * 
 * 5     21.07.00 15:34 Wohlers
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
 * 8     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 7     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 6     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 5     11.01.00 22:59 Wohlers
 * CS-Fixes / NSC-Equip-Message
 * 
 * 4     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "oInfo.h"
#include "oNpc.h"

#include "zParser.h"

// **************************************************************************************
// All Informations
// **************************************************************************************

// Global
zSTRING infoClass ("C_INFO");

// Static 
zBOOL oCInfoManager :: size_checked = FALSE;

oCInfoManager :: oCInfoManager ( zCParser *parser )
{
	//
	//	SET LIST'S COMAPRE FUNCTION
	//
	infoList.SetCompare( oCInfoManager :: CompareInfos ); 

	p = parser;
	if (!p) return;
	
	// Getting the class Index
	int cindex = p->GetIndex(infoClass);
	if (cindex<0) return;
	// Create all Infos
	int	pos	= 0;
	while (pos>=0) {
		pos	= p->GetInstance(cindex,pos+1);
		if (pos>=0) {
			// Create Info
			oCInfo* info = zNEW( oCInfo() );
			// Check Size
			if (!size_checked) {
				p->CheckClassSize(infoClass,info->GetDataSize());
				size_checked = TRUE;				
			}
			p -> CreateInstance	(pos,info->GetDataAdr());
			info -> SetInstance	(pos);
			info -> DoCheck		();
			infoList.InsertSort	(info);
		}
	};
	// Debug
	zerr.Message("U: INF: "+zSTRING(infoList.GetNumInList())+" Infos found.");
};

oCInfoManager :: ~oCInfoManager ( )
{
	infoList.DeleteList();
	p = NULL;
};

oCInfo* oCInfoManager :: GetInformation ( oCNpc* ask, oCNpc* npc, zBOOL important )
// Durchsuche alle Infos nach einer passenden Info
// SC "ask" fragt NSC "npc"
{
	p->SetInstance("SELF",npc);
	p->SetInstance("OTHER",ask);

	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;
	int				nInstance	= npc -> GetInstance();

	while( pNext )
	{
		pInfo = pNext->GetData();
		if ( pInfo )											// VALID
		if ( pInfo->WasTold			()	== FALSE		)		// NOT YET TOLD
		if ( pInfo->GetNpcID		()	== nInstance	)		// RIGHT INSTANCE
		if ( pInfo->IsImportant		()	== important	)		// SAME IMPORTANCE
		if ( pInfo->InfoConditions	()	== TRUE			)		// CONDITION FULFILLED
		{
			return pInfo;
		}

		pNext = pNext->GetNextInList();
	}

	return NULL;
}

oCInfo* oCInfoManager :: GetInformation ( int infoInstance )
{
	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )											// VALID
		if ( pInfo->GetInstance		()	== infoInstance )		// RIGHT INSTANCE
		{
			return pInfo;
		}

		pNext = pNext->GetNextInList();
	}

	return NULL;
}

int oCInfoManager :: GetInfoCount ( oCNpc* pNpcAsker, oCNpc* pNpcAsked )
{
	this->p->SetInstance( "SELF" , pNpcAsked );
	this->p->SetInstance( "OTHER", pNpcAsker );

	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;
	int				nCount		= 0;
	int				nInstance	= pNpcAsked->GetInstance();

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )											// VALID
		if ( pInfo->WasTold			()	== FALSE		)		// NOT YET TOLD
		if ( pInfo->GetNpcID		()	== nInstance	)		// RIGHT INSTANCE
		if ( pInfo->InfoConditions	()	== TRUE			)		// CONDITION FULFILLED
		{
			nCount++;
		}

		pNext = pNext->GetNextInList();
	}

	return nCount;
}

int oCInfoManager :: GetInfoCountImportant ( oCNpc* pNpcAsker, oCNpc* pNpcAsked )
{
	this->p->SetInstance( "SELF" , pNpcAsked );
	this->p->SetInstance( "OTHER", pNpcAsker );

	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;
	int				nCount		= 0;
	int				nInstance	= pNpcAsked->GetInstance();

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )											// VALID
		if ( pInfo->IsImportant		()	== TRUE			)		// SAME IMPORTANCE
		if ( pInfo->WasTold			()	== FALSE		)		// NOT YET TOLD
		if ( pInfo->GetNpcID		()	== nInstance	)		// RIGHT INSTANCE
		if ( pInfo->InfoConditions	()	== TRUE			)		// CONDITION FULFILLED
		{
			nCount++;
		}

		pNext = pNext->GetNextInList();
	}

	return nCount;
}

int oCInfoManager :: GetInfoCountUnimportant ( oCNpc* pNpcAsker, oCNpc* pNpcAsked )
{
	this->p->SetInstance( "SELF" , pNpcAsked );
	this->p->SetInstance( "OTHER", pNpcAsker );

	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;
	int				nCount		= 0;
	int				nInstance	= pNpcAsked->GetInstance();

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )											// VALID
		if ( pInfo->IsImportant		()	== FALSE		)		// SAME IMPORTANCE
		if ( pInfo->WasTold			()	== FALSE		)		// NOT YET TOLD
		if ( pInfo->GetNpcID		()	== nInstance	)		// RIGHT INSTANCE
		if ( pInfo->InfoConditions	()	== TRUE			)		// CONDITION FULFILLED
		{
			nCount++;
		}

		pNext = pNext->GetNextInList();
	}

	return nCount;
}

oCInfo* oCInfoManager :: GetInfo ( oCNpc* pNpcAsker, oCNpc* pNpcAsked, int nInfo )
{ 
	this->p->SetInstance( "SELF" , pNpcAsked );
	this->p->SetInstance( "OTHER", pNpcAsker );

	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;
	int				nCount		= 0;
	int				nInstance	= pNpcAsked->GetInstance();

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )											// VALID
		if ( pInfo->WasTold			()	== FALSE		)		// NOT YET TOLD
		if ( pInfo->GetNpcID		()	== nInstance	)		// RIGHT INSTANCE
		if ( pInfo->InfoConditions	()	== TRUE			)		// CONDITION FULFILLED
		{
			if ( nCount == nInfo ) return pInfo;
			nCount++;
		}

		pNext = pNext->GetNextInList();
	}

	return NULL;
}

oCInfo* oCInfoManager :: GetInfoImportant ( oCNpc* pNpcAsker, oCNpc* pNpcAsked, int nInfo )
{ 
	this->p->SetInstance( "SELF" , pNpcAsked );
	this->p->SetInstance( "OTHER", pNpcAsker );

	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;
	int				nCount		= 0;
	int				nInstance	= pNpcAsked->GetInstance();

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )											// VALID
		if ( pInfo->IsImportant		()	== TRUE			)		// SAME IMPORTANCE
		if ( pInfo->WasTold			()	== FALSE		)		// NOT YET TOLD
		if ( pInfo->GetNpcID		()	== nInstance	)		// RIGHT INSTANCE
		if ( pInfo->InfoConditions	()	== TRUE			)		// CONDITION FULFILLED
		{
			if ( nCount == nInfo ) return pInfo;
			nCount++;
		}

		pNext = pNext->GetNextInList();
	}

	return NULL;
}

oCInfo* oCInfoManager :: GetInfoUnimportant ( oCNpc* pNpcAsker, oCNpc* pNpcAsked, int nInfo )
{ 
	this->p->SetInstance( "SELF" , pNpcAsked );
	this->p->SetInstance( "OTHER", pNpcAsker );

	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;
	int				nCount		= 0;
	int				nInstance	= pNpcAsked->GetInstance();

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )											// VALID
		if ( pInfo->IsImportant		()	== FALSE		)		// SAME IMPORTANCE
		if ( pInfo->WasTold			()	== FALSE		)		// NOT YET TOLD
		if ( pInfo->GetNpcID		()	== nInstance	)		// RIGHT INSTANCE
		if ( pInfo->InfoConditions	()	== TRUE			)		// CONDITION FULFILLED
		{
			if ( nCount == nInfo ) return pInfo;
			nCount++;
		}

		pNext = pNext->GetNextInList();
	}

	return NULL;
}

zBOOL oCInfoManager :: InformationTold ( int infoInstance )
{
	oCInfo* pInfo = this->GetInformation( infoInstance );

	if	( ! pInfo ) return FALSE;
	else			return pInfo->WasTold();
}

void oCInfoManager::Archive( zCArchiver &arc )
{
	if( !arc.InSaveGame() ) return;

	arc.WriteInt("NumOfEntries", infoList.GetNumInList());

	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )		
		{
			pInfo->Archive( arc );
		}

		pNext = pNext->GetNextInList();
	}
}

void oCInfoManager::Unarchive( zCArchiver &arc )
{
	if( !arc.InSaveGame() ) return;

	int NumOfEntries = 0;
	arc.ReadInt("NumOfEntries", NumOfEntries);
	infoList.DeleteList();
	for( int i = 0; i < NumOfEntries; i++ )
	{
		oCInfo *Entry = zNEW( oCInfo );
		Entry->Unarchive( arc );
		infoList.InsertSort( Entry );
	}
}

void oCInfoManager::RestoreParserInstances( void )
{
	zCListInfos*	pNext		= &this->infoList;
	oCInfo*			pInfo		= NULL;

	while( pNext )
	{
		pInfo = pNext->GetData();

		if ( pInfo )		
		{
			pInfo->RestoreParserInstance();
		}

		pNext = pNext->GetNextInList();
	}	
}

// **************************************************************************************
// Single Information
// **************************************************************************************

oCInfo :: oCInfo ()
{
	pd.npc			= -1;						// Npc - Instance 
	pd.nr			= -1;						// ID
	pd.important	= FALSE;					// Is it an important Info
	pd.conditions	= -1;						// Condition
	pd.information	= -1;				
	pd.trade		= FALSE;
	pd.permanent	= FALSE;
	told			= FALSE;					// already told -> delete ?	
	instance		= -1;						// InstanceNr of Info
	next			= NULL;
};

oCInfo :: ~oCInfo ()
{
	next			= NULL;
};

void oCInfo :: SetInstance(int inst)
{
	int typ,ele;
	instance = inst;
	name	 = parser.GetSymbolInfo(inst,typ,ele);
}

int oCInfo :: GetInstance()
{
	return instance;
}

zBOOL oCInfo :: DoCheck ()
{
	// All data correct Initialized
	if (pd.npc<=0) zERR_WARNING("U: INF: Skriptinfo:npc is not/wrong initialised:"+zSTRING(pd.information)+" "+zSTRING(pd.description));
	return TRUE;
}

int oCInfo :: GetNpcID ()
{
	return pd.npc;
}

int oCInfo :: GetConditionFunc()
{
	return pd.conditions;
}

zBOOL oCInfo :: WasTold()
{
	if ( pd.permanent ) return FALSE;
	return told;
}

void oCInfo :: SetTold(zBOOL f)
{
	told = f;
}

int oCInfo :: GetDataSize ()
{
	return sizeof(pd);
}

void* oCInfo :: GetDataAdr ()
{
	return &pd;
}

zSTRING& oCInfo :: GetText ()
{
	return this->pd.description;
}

zBOOL oCInfo :: InfoConditions()
{
	return *(zBOOL*)parser.CallFunc(pd.conditions);
}

void oCInfo :: Info()
{
	parser.CallFunc(pd.information);
	SetTold(TRUE);
}

void oCInfo::Archive( zCArchiver &arc )
{
	if( !arc.InSaveGame() ) return;

	arc.WriteBool( "Told", told );
	//arc.WriteInt( "InstNum", instance );
    
    // [Moos] vv
    arc.WriteString("InstName", name);
}

void oCInfo::Unarchive( zCArchiver &arc )
{
	if( !arc.InSaveGame() ) return;

	arc.ReadBool("Told", told );

//	arc.ReadInt("InstNum", instance );
//	SetInstance( instance );

    arc.ReadString("InstName", name);
    instance = parser.GetIndex(name);
    if (!parser.CreateInstance(instance, &pd))
        zERR_WARNING("Info instance not found.");

}

void oCInfo::RestoreParserInstance( void )
{
	::parser.SetInstance( this->instance, &this->pd );
}

/*
zSTRING oCInfo :: GetTransitionOU()
// Überleitung : Name der Output-Unit
// Kennung 1
{	
	if (pd.transition[0]=='$') return pd.transition;
	return ("I"+zSTRING(pd.nr)+"_"+zSTRING(pd.npc)+"_1");
}

zSTRING oCInfo :: GetTransition()
// Überleitung
{	
	return pd.transition;
}

zSTRING oCInfo :: GetAnswerOU(oCNpc* npc)
// SC-Antwort : Name der Output-Unit
// Kennung 2-7
{	
	zSTRING name = npc->GetInstanceName		();
	int nr		 = oCNpc::GetIDByInstance	(name);	
	if (pd.pc_answer[nr].IsEmpty()) nr = 0;
	if (pd.pc_answer[nr][0]=='$') return pd.pc_answer[nr];
	return ("I"+zSTRING(pd.nr)+"_"+zSTRING(pd.npc)+"_"+zSTRING(nr+2));
}

zSTRING oCInfo :: GetAnswer(oCNpc* npc)
{
	zSTRING name = npc->GetInstanceName		();
	int nr		 = oCNpc::GetIDByInstance	(name);
	if (pd.pc_answer[nr].IsEmpty()) nr = 0;
	return pd.pc_answer[nr];
}

zSTRING oCInfo :: GetInformationOU()
// SC-Antwort : Name der Output-Unit
// Kennung 8
{	
	if (pd.information[0]=='$') return pd.information;
	return ("I"+zSTRING(pd.nr)+"_"+zSTRING(pd.npc)+"_8");
}

zSTRING oCInfo :: GetInformation()
{
	return pd.information;
}
*/


void oCInfo::AddChoice( zSTRING strText, int nFunc )		
{
	oCInfoChoice* pChoice = zNEW( oCInfoChoice )( oCInfoChoice( strText, nFunc ) );
	listChoices.Insert( pChoice ); 
}

void oCInfo::RemoveChoice( zSTRING strText )
{
	int nChoices = GetChoiceCount(); 
	int nChoice  = 0;

	while( nChoice <= nChoices ) 
	{ 
		oCInfoChoice* pChoice = listChoices[ nChoice++ ];
		if ( pChoice ) 
		if ( pChoice->Text == strText ) 
		{
			listChoices.Remove( pChoice );
			delete pChoice; 
			return;
		}
	} 
}

void oCInfo::RemoveAllChoices()
{ 
	int nChoices = GetChoiceCount(); 
	int nChoice  = 0;

	while( nChoice <= nChoices ) 
	{ 
		oCInfoChoice* pChoice = listChoices[ nChoice++ ];
		if ( pChoice ) delete pChoice; 
	} 
	listChoices.DeleteList();
}
