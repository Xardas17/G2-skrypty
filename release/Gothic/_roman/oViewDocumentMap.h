/******************************************************************************** 
 
     $Workfile:: oViewDocumentMap.h     $                $Date:: 16.01.01 17:22   $
     $Revision:: 5                    $             $Modtime:: 16.01.01 17:16   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDocumentMap.h $
 * 
 * 5     16.01.01 17:22 Keskenti
 * 
 * 4     24.11.00 13:47 Keskenti
 * 
 * 3     17.11.00 17:46 Keskenti
 * 
 * 2     25.10.00 17:45 Keskenti
 * 
 * 1     24.10.00 21:16 Keskenti
 * 
 * 6     24.10.00 20:54 Keskenti
 * 
 * 5     23.10.00 23:27 Keskenti
 * 
 * 4     21.10.00 1:14 Keskenti
 * 
 * 3     20.10.00 20:20 Keskenti
 * 
 * 2     20.10.00 17:54 Keskenti
 * 
 * 1     20.10.00 17:36 Keskenti
 * 
 * 1     20.10.00 16:27 Keskenti
 * 
 * 3     19.10.00 19:14 Keskenti
 * 
 * 2     19.10.00 17:15 Keskenti
 * 
 * 1     19.10.00 15:22 Keskenti
 * 
 * 1     19.10.00 15:19 Keskenti
 * 
 * 4     18.10.00 1:08 Keskenti
 * 
 * 3     18.10.00 0:58 Keskenti
 * 
 * 2     18.10.00 0:48 Keskenti
 * 
 * 1     18.10.00 0:47 Keskenti
 * 
 *********************************************************************************/

#ifndef __OVIEWDOCUMENTMAP_H__
#define __OVIEWDOCUMENTMAP_H__

//
//	VIEW
//
class oCViewDocumentMap : public oCViewDocument
{
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
private:
	typedef
	enum zEHeading
	{
		HEADING_NORTH		,
		HEADING_NORTHEAST	,	
		HEADING_EAST		,	
		HEADING_SOUTHEAST	,	
		HEADING_SOUTH		,	
		HEADING_SOUTHWEST	,	
		HEADING_WEST		,	
		HEADING_NORTHWEST
	}
	zTHeading;

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	oCViewDocument		ViewArrow	;
	oCViewDocument*		ViewPageMap	;
	zSTRING				Level		;
	zVEC4				LevelCoords	;  // VX=left, VY=top, VZ=right, VW=bottom

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	virtual oCViewDocument*	zCCFASTCALL	SetPage				( int nPage, zSTRING& strTexture, zBOOL bScale );
			void			zCCFASTCALL	SetLevel			( const zSTRING& strLevel );
			void			zCCFASTCALL	SetLevelCoords		( int left, int top, int right, int bottom );
			void			zCCFASTCALL	UpdatePosition		( void );

protected:											

	//
	//	CON-/DESTRUCTION
	//
public:
			 oCViewDocumentMap();
	virtual ~oCViewDocumentMap();
};

typedef oCViewDocumentMap	*LPCViewDialogtDocumentMap,	*LPCVIEWDIALOGDOCUMENTMAP;

#endif	//__OVIEWDOCUMENTMAP_H__