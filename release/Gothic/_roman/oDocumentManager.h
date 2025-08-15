/******************************************************************************** 
 
     $Workfile:: oDocumentManager. $                $Date:: 24.01.01 16:21   $
     $Revision:: 7                    $             $Modtime:: 24.01.01 16:14   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oDocumentManager.h $
 * 
 * 7     24.01.01 16:21 Keskenti
 * 
 * 6     16.01.01 17:22 Keskenti
 * 
 * 5     17.11.00 17:44 Keskenti
 * 
 * 4     25.10.00 17:45 Keskenti
 * 
 * 3     24.10.00 20:54 Keskenti
 * 
 * 2     23.10.00 23:27 Keskenti
 * 
 * 1     23.10.00 18:00 Keskenti
 * 
 * 8     21.10.00 1:14 Keskenti
 * 
 * 7     20.10.00 22:57 Keskenti
 * 
 * 6     20.10.00 18:47 Keskenti
 * 
 * 5     20.10.00 16:40 Keskenti
 * 
 * 4     19.10.00 15:56 Keskenti
 * 
 * 3     18.10.00 18:33 Keskenti
 * 
 * 2     18.10.00 17:15 Keskenti
 * 
 *********************************************************************************/

#ifndef __ZDOCUMENTMANAGER_H__
#define __ZDOCUMENTMANAGER_H__


//
//	LIST
//
class	oCViewDocument;
typedef zCListSort< oCViewDocument > zCListDocuments;

//
//	DESCRIPTOR
//

//
//	MANAGER
//
class oCDocumentManager : public zCInputCallback
{
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zCListDocuments*	ListDocuments	;
	zCViewDialog*		DlgDocumentMain	;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	int				zCCFASTCALL	CreateDocument		( void																				);
	int				zCCFASTCALL	CreateMap			( void																				);
	void			zCCFASTCALL	SetPages			( int nDocID, int nPages															);
	void			zCCFASTCALL	SetPage				( int nDocID, int nPage , zSTRING&	strTexture, zBOOL bScale						);
	void			zCCFASTCALL	SetFont				( int nDocID, int nPage , zSTRING&	strTexture										);
	void			zCCFASTCALL	SetMargins			( int nDocID, int nPage , zPOS&		ptTopLeft , zPOS& ptBottomRight, zBOOL bPixels	);
	void			zCCFASTCALL	PrintLine			( int nDocID, int nPage , zSTRING&	strText											);
	void			zCCFASTCALL	PrintLines			( int nDocID, int nPage , zSTRING&	strText											);
	void			zCCFASTCALL	SetLevel			( int nDocID, const zSTRING& strTexture												);
	void			zCCFASTCALL	SetLevelCoords		( int nDocID, int nLeft, int nTop, int nRight, int nBottom							);
	void			zCCFASTCALL	Show				( int nDocID																		);
	void			zCCFASTCALL	UpdateMap			( int nDocID																		);

protected:
	int				zCCFASTCALL	GetNextAvailableID	( void																				);
	oCViewDocument*	zCCFASTCALL	GetDocumentView		( int nDocID																		);

	//
	//	EVENTS
	//
public:
	virtual zBOOL	HandleEvent	( int nKey	);		

	//
	//	CON-/DESTRUCTION
	//
public:
	static oCDocumentManager& GetDocumentManager( void );

protected:	 oCDocumentManager();
			 oCDocumentManager( const oCDocumentManager& mgrDocuments );
			 oCDocumentManager& operator = ( const oCDocumentManager& mgrDocuments );
public:		~oCDocumentManager();
};

#endif	//__ZDOCUMENTMANAGER_H__