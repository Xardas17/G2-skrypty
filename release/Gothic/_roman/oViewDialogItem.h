/******************************************************************************** 
 
     $Workfile:: oViewDialogItem.h   $                $Date:: 28.11.00 12:42   $
     $Revision:: 2                    $             $Modtime:: 28.11.00 12:41   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDialogItem.h $
 * 
 * 2     28.11.00 12:42 Keskenti
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

#ifndef __OVIEWDIALOGITEM_H__
#define __OVIEWDIALOGITEM_H__

//
//	VIEW
//
class oCViewDialogItem : public zCViewDialog
{
	zCLASS_DECLARATION( oCViewDialogItem )
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	oCItem*	Item;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	void			zCCFASTCALL	SetItem	( oCItem* pItem )	;
	oCItem*			zCCFASTCALL	GetItem	( void			)	{ return this->Item; }

protected:
	virtual void	zCCFASTCALL	Blit	( void )			;
	//
	//	CON-/DESTRUCTION
	//
public:
			 oCViewDialogItem();
	virtual ~oCViewDialogItem();
};

typedef oCViewDialogItem	*LPCViewDialogItem,	*LPCVIEWDIALOGITEM;

#endif	//__OVIEWDIALOGITEM_H__