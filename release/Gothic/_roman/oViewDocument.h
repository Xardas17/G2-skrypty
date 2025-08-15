/******************************************************************************** 
 
     $Workfile:: oViewDocument.h     $                $Date:: 17.11.00 17:44   $
     $Revision:: 8                    $             $Modtime:: 17.11.00 14:53   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDocument.h $
 * 
 * 8     17.11.00 17:44 Keskenti
 * 
 * 7     25.10.00 17:45 Keskenti
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

#ifndef __OVIEWDOCUMENT_H__
#define __OVIEWDOCUMENT_H__

//
//	VIEW
//
class oCViewDocument : public zCViewDialog
{
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	int		Pages;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
			void			zCCFASTCALL	SetPages			( int nPages );
			void			zCCFASTCALL	SetMargins			( int nPage, zPOS& ptTopLeft, zPOS& ptBottomRight, zBOOL bPixels );
	virtual oCViewDocument*	zCCFASTCALL	SetPage				( int nPage, zSTRING& strTexture, zBOOL bScale );
			void			zCCFASTCALL	SetFont				( int nPage, zSTRING& strFont );
			void			zCCFASTCALL	PrintLine			( int nPage, zSTRING& strText );
			void			zCCFASTCALL	PrintLines			( int nPage, zSTRING& strText );
															
			int				zCCFASTCALL	GetPageCount		( void )															{ return this->Pages; }
															
			void			zCCFASTCALL	SetTexture			( zSTRING& strTexture, zBOOL bScale );

protected:											
			oCViewDocument*	zCCFASTCALL	GetPage				( int nPage );
															
			void			zCCFASTCALL	AlignPageToParent	( void );
			void			zCCFASTCALL	Center				( void );
			void			zCCFASTCALL	SizeToContent		( void );
			void			zCCFASTCALL	SizeToParent		( void );
			void			zCCFASTCALL	ScaleToParent		( void );

	//
	//	CON-/DESTRUCTION
	//
public:
			 oCViewDocument( zSTRING& strName );
			 oCViewDocument();
	virtual ~oCViewDocument();
};

typedef oCViewDocument	*LPCViewDialogtDocument,	*LPCVIEWDIALOGDOCUMENT;

#endif	//__OVIEWDOCUMENT_H__