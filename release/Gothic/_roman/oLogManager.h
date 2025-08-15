/******************************************************************************** 
 
     $Workfile:: oLogManager. $					$Date:: 6.02.01 4:41    $
     $Revision:: 10           $					$Modtime:: 6.02.01 4:18   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oLogManager.h $
 * 
 * 10    6.02.01 4:41 Speckels
 * 
 * 9     16.01.01 1:38 Keskenti
 * 
 * 8     15.01.01 17:07 Keskenti
 * 
 * 7     11.01.01 1:08 Keskenti
 * 
 * 6     13.12.00 12:58 Keskenti
 * 
 * 5     12.12.00 20:44 Keskenti
 * 
 * 4     12.12.00 20:16 Keskenti
 * 
 * 3     12.12.00 19:03 Keskenti
 * 
 * 2     12.12.00 16:27 Keskenti
 * 
 * 1     12.12.00 16:26 Keskenti
 * 
 *********************************************************************************/

#ifndef __OLOGMANAGER_H__
#define __OLOGMANAGER_H__

class oCLogEntry	;
class oCLogTopic	;
class oCLogManager	;

//

class oCLogEntry
{
	friend class oCLogTopic;

	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
protected:

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zSTRING	m_strDescription;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	const	zSTRING&	zCCFASTCALL	GetDescription	( void )	const						{ return this->m_strDescription; }
			void		zCCFASTCALL	SetDescription	( const zSTRING& strDescription )		{ this->m_strDescription = strDescription; }

	void				Archive						( zCArchiver& archiver );
	void				Unarchive					( zCArchiver& archiver );	

	//
	//	CON-/DESTRUCTION
	//
protected:	 oCLogEntry( const zSTRING& strDescription )	{ this->SetDescription( strDescription ); }
public:		~oCLogEntry()									{ ; }
};


class oCLogTopic
{
	friend class oCLogManager	;

	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
public:
	enum	zELogTopicStatus
	{
		zELogTopicStatus_Free		,		// DO NOT DISPLAY THIS ONE !!!
		zELogTopicStatus_Running	,
		zELogTopicStatus_Success	,
		zELogTopicStatus_Failure	,
		zELogTopicStatus_Obsolete	
	};

	enum	zELogSection
	{
		zELogSection_Missions		,
		zELogSection_Notes			,
		zELogSection_All					// ONLY USED INTERNALLY -> DO NOT SET THIS MODE !!!
	};

	typedef	zELogTopicStatus		zTLogTopicStatus;
	typedef zELogSection			zTLogSection	;
	typedef zCList< oCLogEntry >	zTLogEntryList	;

	const static char* ms_strSections	[];
	const static char* ms_strStati		[];

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zSTRING				m_strDescription;
	zTLogSection		m_enuSection	;
	zTLogTopicStatus	m_enuStatus		;
	zTLogEntryList		m_lstEntries	;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	const	zSTRING&			zCCFASTCALL	GetDescription	( void ) const									{ return this->m_strDescription	; }
	const	zTLogSection		zCCFASTCALL	GetSection		( void ) const									{ return this->m_enuSection		; }
	const	zTLogTopicStatus	zCCFASTCALL	GetStatus		( void ) const									{ return this->m_enuStatus		; }
	const	zTLogEntryList&		zCCFASTCALL GetEntryList	( void ) const									{ return this->m_lstEntries		; }
																							
			void				zCCFASTCALL	SetDescription	( const zSTRING&			strDescription	)	{ this->m_strDescription	= strDescription;	}
			void				zCCFASTCALL	SetSection		( const zTLogSection		enuSection		)	{ this->m_enuSection		= enuSection	;	}
			void				zCCFASTCALL	SetStatus		( const zTLogTopicStatus	enuStatus		)	{ this->m_enuStatus			= enuStatus		;	}
			void				zCCFASTCALL	AddEntry		( const zSTRING&			strEntry		);

			void				zCCFASTCALL	Archive			(		zCArchiver&			archiver		);
			void				zCCFASTCALL	Unarchive		(		zCArchiver&			archiver		);	
protected:
			oCLogEntry*			zCCFASTCALL	GetEntry		( const zSTRING&			strEntry		)		
			{
				zTLogEntryList* pNext	= &m_lstEntries;
				oCLogEntry*		pEntry	= NULL;

				while( pNext )
				{
					pEntry = pNext->GetData();

					if ( pEntry )
					if ( pEntry->GetDescription() == strEntry ) return pEntry;

					pNext = pNext->GetNextInList();

				}

				return NULL;
			}

	//
	//	CON-/DESTRUCTION
	//
protected:	  oCLogTopic(	const zSTRING&		strDescription, 
							zELogSection		enuSection		= zELogSection_Missions, 
							zELogTopicStatus	enuStatus		= zELogTopicStatus_Free )	{	this->SetDescription	( strDescription );
																								this->SetSection		( enuSection	 ); 
																								this->SetStatus			( enuStatus		 ); }
public:		 ~oCLogTopic()																	{	this->m_lstEntries.DeleteListDatas()	  ;	}
};

typedef oCLogTopic::zELogSection		zELogSection;
typedef	oCLogTopic::zELogTopicStatus	zELogTopicStatus;

class oCLogManager 
{
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
protected:
	typedef zCList< oCLogTopic >	zTLogTopicList;

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zTLogTopicList					m_lstTopics;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	const	zTLogTopicList&	zCCFASTCALL GetTopicList( void ) const														{ return this->m_lstTopics; }

			void			zCCFASTCALL	AddTopic	( const zSTRING&	strTopic, const zELogSection		enuSection	)	{ oCLogTopic* pTopic = this->GetTopic( strTopic	); if ( pTopic ) return; this->m_lstTopics.Insert( zNEW( oCLogTopic ) ( strTopic, enuSection ) );	}
			void			zCCFASTCALL	AddEntry	( const zSTRING&	strTopic, const zSTRING&			strEntry	)	{ oCLogTopic* pTopic = this->GetTopic( strTopic	); if ( pTopic ) pTopic->AddEntry	( strEntry  );													}
			void			zCCFASTCALL	SetStatus	( const zSTRING&	strTopic, const zELogTopicStatus	enuStatus	)	{ oCLogTopic* pTopic = this->GetTopic( strTopic	); if ( pTopic ) pTopic->SetStatus	( enuStatus );													}

			void			zCCFASTCALL	Clear		( void );
			void			zCCFASTCALL	Archive		(		zCArchiver&	archiver	);
			void			zCCFASTCALL	Unarchive	(		zCArchiver&	archiver	);	
protected:
			oCLogTopic*		zCCFASTCALL	GetTopic	( const zSTRING& strTopic, const zELogSection enuSection = oCLogTopic::zELogSection_All )
			{
				zTLogTopicList* pNext	= &m_lstTopics;
				oCLogTopic*		pTopic	= NULL;

				while( pNext )
				{
					pTopic = pNext->GetData();

					if ( pTopic )
					if ( pTopic->GetDescription() == strTopic ) 
					{
						if		( enuSection == oCLogTopic::zELogSection_All	)	return pTopic;
						else if	( enuSection == pTopic->GetSection()			)	return pTopic;
					}

					pNext = pNext->GetNextInList();
				}

				return NULL;
			}

	//
	//	CON-/DESTRUCTION
	//
public:
	static oCLogManager& GetLogManager( void );

protected:	 oCLogManager();
			 oCLogManager( const oCLogManager& mgrLogs );
			 oCLogManager& operator = ( const oCLogManager& mgrLogs );
public:		~oCLogManager();
};

#endif	//__OLOGMANAGER_H__