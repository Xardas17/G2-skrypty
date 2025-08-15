/******************************************************************************** 
 
     $Workfile:: oLogManager. $                $Date:: 6.02.01 4:40     $
     $Revision:: 9                    $             $Modtime:: 6.02.01 4:30     $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oLogManager.cpp $
 * 
 * 9     6.02.01 4:40 Speckels
 * 
 * 8     16.01.01 2:05 Keskenti
 * 
 * 7     16.01.01 1:38 Keskenti
 * 
 * 6     16.01.01 1:32 Keskenti
 * 
 * 5     15.01.01 17:07 Keskenti
 * 
 * 4     11.01.01 1:08 Keskenti
 * 
 * 3     9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 2     12.12.00 20:16 Keskenti
 * 
 * 1     12.12.00 16:29 Keskenti
 * 
 *********************************************************************************/

#include <zCore.h>
#include <zArchiver.h>
#include <oLogManager.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

	const char* oCLogTopic::ms_strSections	[]	= {	"zELogSection_Missions"		,
													"zELogSection_Notes"		,
													"zELogSection_All"			};

	const char* oCLogTopic::ms_strStati		[]	= {	"zELogTopicStatus_Free"		, 
													"zELogTopicStatus_Running"	, 
													"zELogTopicStatus_Success"	,
													"zELogTopicStatus_Failure"	,
													"zELogTopicStatus_Obsolete" };

//*********************************************************************************
//**														  Singleton Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCLogManager& oCLogManager::GetLogManager()
{
	static oCLogManager mgrLogs;
	return mgrLogs;
}

//*********************************************************************************
//**																  Copy Operator
//*********************************************************************************
//**
//*********************************************************************************
oCLogManager& oCLogManager::operator = ( const oCLogManager& mgrLogs )
{
	return (*this);
}

//*********************************************************************************
//**															   Copy Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCLogManager::oCLogManager( const oCLogManager& mgrLogs )
{
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCLogManager::oCLogManager()
{
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
oCLogManager::~oCLogManager()
{
	this->Clear();
}

//*********************************************************************************
//**																		  Clear
//*********************************************************************************
//**
//*********************************************************************************
void oCLogManager::Clear( void )
{
	this->m_lstTopics.DeleteListDatas();	
}

//*********************************************************************************
//**																		Archive
//*********************************************************************************
//**
//*********************************************************************************
void oCLogManager::Archive( zCArchiver& archiver )
{
	oCLogTopic*	pTopic	= NULL;
	int			nTopics = this->m_lstTopics.GetNumInList();

	archiver.WriteInt( "LOGMANAGERTOPICCOUNT", nTopics );

	while( (--nTopics) >= 0 )
	{
		pTopic = this->m_lstTopics[ nTopics ];

		if ( pTopic )
 			 pTopic->Archive( archiver );
	}
}

//*********************************************************************************
//**																	  Unarchive
//*********************************************************************************
//**
//*********************************************************************************
void oCLogManager::Unarchive( zCArchiver& archiver )
{
	oCLogTopic*	pTopic	= NULL;
	int			nTopics = archiver.ReadInt( "LOGMANAGERTOPICCOUNT" );

	for ( int nTopic = 0; nTopic < nTopics; nTopic++ )
	{
		pTopic = zNEW( oCLogTopic( "" ) );
		pTopic->Unarchive( archiver );
		this->m_lstTopics.Insert( pTopic );
	}
}

void oCLogTopic::AddEntry( const zSTRING& strEntry)
{ 
	oCLogEntry* pEntry = this->GetEntry( strEntry ); 
	if ( pEntry ) return; 

	// Letztes Element suchen
	zTLogEntryList* lastElement = &this->m_lstEntries;
	while (lastElement->next) lastElement = lastElement->next;

	// Einfuegen
	if (lastElement) 
	{
		// lastElement->Insert( zNEW( oCLogEntry )( strEntry ) );	
		zTLogEntryList *newItem	= zNEW(zTLogEntryList);
		newItem->data			= zNEW( oCLogEntry )( strEntry );
		lastElement->next		= newItem;		
	}
}

//*********************************************************************************
//**																		Archive
//*********************************************************************************
//**
//*********************************************************************************
void oCLogTopic::Archive( zCArchiver& archiver )
{
	archiver.WriteString( "TOPICDESCRIPTION"	,									m_strDescription			);
	archiver.WriteEnum	( "TOPICSECTION"		, (const char*) (ms_strSections	),	m_enuSection				);
	archiver.WriteEnum	( "TOPICSTATUS"			, (const char*) (ms_strStati	),	m_enuStatus					);
	archiver.WriteInt	( "LOGTOPICENTRYCOUNT"	,									m_lstEntries.GetNumInList()	);

	oCLogEntry*	pEntry	= NULL;
	int			nEntries = this->m_lstEntries.GetNumInList();

	archiver.WriteInt( "LOGMANAGERENTRYCOUNT", nEntries );

	while( (--nEntries) >= 0 )
	{
		pEntry = this->m_lstEntries[ nEntries ];

		if ( pEntry )
 			 pEntry->Archive( archiver );
	}
}

//*********************************************************************************
//**																	  Unarchive
//*********************************************************************************
//**
//*********************************************************************************
void oCLogTopic::Unarchive( zCArchiver& archiver )
{
	int nSection, nStatus;

	archiver.ReadString	( "TOPICDESCRIPTION", m_strDescription	);
	archiver.ReadEnum	( "TOPICSECTION"	, nSection 			);	m_enuSection	= (zELogSection		) (nSection);
	archiver.ReadEnum	( "TOPICSTATUS"		, nStatus			);	m_enuStatus		= (zELogTopicStatus	) (nStatus );
	
	oCLogEntry*	pEntry	 = NULL;
	int			nEntries = archiver.ReadInt( "LOGTOPICENTRYCOUNT" );

	for ( int nEntry = 0; nEntry < nEntries; nEntry++ )
	{
		pEntry = zNEW( oCLogEntry( "" ) );
		pEntry->Unarchive( archiver );
		this->m_lstEntries.Insert( pEntry );
	}
}

//*********************************************************************************
//**																		Archive
//*********************************************************************************
//**
//*********************************************************************************
void oCLogEntry::Archive( zCArchiver& archiver )
{
	archiver.WriteString( "ENTRYDESCRIPTION", m_strDescription	);
}

//*********************************************************************************
//**																	  Unarchive
//*********************************************************************************
//**
//*********************************************************************************
void oCLogEntry::Unarchive( zCArchiver& archiver )
{
	archiver.ReadString	( "ENTRYDESCRIPTION", m_strDescription	);
}
