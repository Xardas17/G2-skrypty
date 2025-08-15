/******************************************************************************** 
 
     $Workfile:: zViewDialog.h        $                $Date:: 28.11.00 12:37   $
     $Revision:: 9                    $             $Modtime:: 28.11.00 12:32   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewDialog.h $
 * 
 * 9     28.11.00 12:37 Keskenti
 * 
 * 8     8.11.00 12:45 Keskenti
 * 
 * 7     25.10.00 17:45 Keskenti
 * 
 * 6     20.10.00 16:19 Keskenti
 * 
 * 5     20.10.00 15:35 Keskenti
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

#ifndef __ZVIEWDIALOG_H__
#define __ZVIEWDIALOG_H__

//
//	VIEW
//
class zCViewDialog : public zCViewPrint, public zCInputCallback
{
	zCLASS_DECLARATION	(zCViewDialog)
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zBOOL	IsDone		;
	zBOOL	IsActivated	;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	virtual zBOOL	zCCFASTCALL	IsActive		( void )				{ return this->IsActivated		; }
	virtual void 	zCCFASTCALL	Activate		( zBOOL bActive  )		{ this->IsActivated = bActive	; }

	virtual zBOOL	zCCFASTCALL	HasFinished		( void )				{ return this->IsDone			; }
	virtual void 	zCCFASTCALL	StartSelection	( void )				{ this->IsDone = FALSE			; }
	virtual void 	zCCFASTCALL	StopSelection	( void )				{ this->IsDone = TRUE			; }

	//
	//	CON-/DESTRUCTION
	//
public:
			 zCViewDialog();
	virtual ~zCViewDialog();
};

typedef zCViewDialog	*LPCViewDialog,	*LPCVIEWDIALOG;

#endif	//__ZVIEWDIALOG_H__