/******************************************************************************** 
 
     $Workfile:: zViewDialogChoice.h  $                $Date:: 15.01.01 18:58   $
     $Revision:: 13                   $             $Modtime:: 15.01.01 18:45   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewDialogChoice.h $
 * 
 * 13    15.01.01 18:58 Keskenti
 * Added color for grayed text and set default colors to WHITE and GREY
 * respectively
 * 
 * 12    13.12.00 14:16 Keskenti
 * 
 * 11    28.11.00 12:37 Keskenti
 * 
 * 10    25.10.00 17:45 Keskenti
 * 
 * 9     20.10.00 16:19 Keskenti
 * 
 * 8     20.10.00 15:35 Keskenti
 * 
 * 7     19.10.00 14:01 Keskenti
 * 
 * 6     18.10.00 17:15 Keskenti
 * 
 * 5     18.10.00 15:04 Keskenti
 * 
 * 4     18.10.00 2:15 Keskenti
 * 
 * 3     18.10.00 1:11 Keskenti
 * 
 * 2     18.10.00 1:09 Keskenti
 * 
 * 1     18.10.00 1:08 Keskenti
 * 
 * 3     18.10.00 0:58 Keskenti
 * 
 * 2     18.10.00 0:48 Keskenti
 * 
 * 1     18.10.00 0:47 Keskenti
 * 
 *********************************************************************************/

#ifndef __ZVIEWDIALOGCHOICE_H__
#define __ZVIEWDIALOGCHOICE_H__

//
//	VIEW
//
class zCViewDialogChoice : public zCViewDialog
{
	zCLASS_DECLARATION	(zCViewDialogChoice)
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zCOLOR	ColorSelected	;
	zCOLOR	ColorGrayed		;
	int		ChoiceSelected	;
	int		Choices			;
	int		LineStart		;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************

	//
	//	GET/SET
	//
public:
	void			zCCFASTCALL	SetColorActive			( zCOLOR& colActive )	{ this->ColorSelected	= colActive	; }
	void			zCCFASTCALL	SetColorGrayed			( zCOLOR& colGrayed )	{ this->ColorGrayed		= colGrayed	; }

	int				zCCFASTCALL	GetSelectedIndex		( void )				{ return this->ChoiceSelected		; }
	zSTRING			zCCFASTCALL	GetSelectedText			( void )				;

protected:																		
	zCViewText2*	zCCFASTCALL	GetSelection			( void )				;

	//
	//	ELEMENTS
	//
public:
	void			zCCFASTCALL	AddChoice				( zSTRING& strText, zBOOL bEnumerate = FALSE	)	;
	void			zCCFASTCALL	RemoveChoice			( zSTRING& strText								)	;
	void			zCCFASTCALL	RemoveChoice			( int nChoice									)	;
	void			zCCFASTCALL	RemoveAllChoices		( void											)	;
																				
	//
	//	INTERACTION
	//
public:
	virtual void 	zCCFASTCALL	StartSelection			( void );
	virtual void 	zCCFASTCALL	StopSelection			( void );

	//
	//	EVENTS
	//
public:
	virtual zBOOL				HandleEvent				( int nKey		);		
																		
	//																	
	//	SELECTION														
	//																	
protected:																
	void			zCCFASTCALL	SelectPrevious			( void			);
	void			zCCFASTCALL	SelectNext				( void			);
	void			zCCFASTCALL	Select					( int nCoice	);
																		
	void			zCCFASTCALL	HighlightSelected		( void			);
	void			zCCFASTCALL	ShowSelected			( void			);
	void			zCCFASTCALL	ScrollUp				( void			);
	void			zCCFASTCALL	ScrollDown				( void			);
	zBOOL			zCCFASTCALL	IsSelectedOutsideAbove	( void			);
	zBOOL			zCCFASTCALL	IsSelectedOutsideBelow	( void			);

	//
	//	RENDER
	//
	virtual void	zCCFASTCALL	BlitText				( void			);

	//
	//	CON-/DESTRUCTION
	//
public:
			 zCViewDialogChoice();
	virtual ~zCViewDialogChoice();
};

typedef zCViewDialogChoice	*LPCViewDialogChoice,	*LPCVIEWDIALOGCHOICE;

#endif	//__ZVIEWDIALOGCHOICE_H__