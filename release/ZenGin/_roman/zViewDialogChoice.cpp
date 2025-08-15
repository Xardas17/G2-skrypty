/******************************************************************************** 
 
     $Workfile:: zViewDialogChoice.cpp $                $Date:: 6.02.01 2:35     $
     $Revision:: 22                   $             $Modtime:: 6.02.01 2:34     $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewDialogChoice.cpp $
 * 
 * 22    6.02.01 2:35 Wohlers
 * 
 * 21    6.02.01 0:33 Wohlers
 * 
 * 20    24.01.01 17:52 Keskenti
 * 
 * 19    15.01.01 18:58 Keskenti
 * Added color for grayed text and set default colors to WHITE and GREY
 * respectively
 * 
 * 18    12.01.01 13:56 Keskenti
 * 
 * 17    9.01.01 13:21 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 16    13.12.00 14:16 Keskenti
 * 
 * 15    11.12.00 19:00 Keskenti
 * 
 * 14    28.11.00 12:37 Keskenti
 * 
 * 13    9.11.00 17:59 Keskenti
 * 
 * 12    8.11.00 12:45 Keskenti
 * 
 * 11    25.10.00 17:45 Keskenti
 * 
 * 10    21.10.00 1:14 Keskenti
 * 
 * 9     20.10.00 17:46 Keskenti
 * 
 * 8     20.10.00 15:35 Keskenti
 * 
 * 7     19.10.00 17:15 Keskenti
 * 
 * 6     19.10.00 14:01 Keskenti
 * 
 * 5     18.10.00 18:33 Keskenti
 * 
 * 4     18.10.00 17:15 Keskenti
 * 
 * 3     18.10.00 15:04 Keskenti
 * 
 * 2     18.10.00 2:15 Keskenti
 * 
 * 1     18.10.00 1:08 Keskenti
 * 
 * 2     18.10.00 0:49 Keskenti
 * 
 * 1     18.10.00 0:48 Keskenti
 * 
 *********************************************************************************/

#include <zIncViews.h>
#include <zViewDialog.h>
#include <zViewDialogChoice.h>
#include <zInput_Win32.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

zCLASS_DEFINITION ( zCViewDialogChoice, zCViewDialog, 0 ,0 )

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewDialogChoice::zCViewDialogChoice()
{
	this->Choices		 =  0;
	this->ChoiceSelected = -1;
	this->LineStart		 =  0;
	this->ColorGrayed	 = zCOLOR( 0x9f, 0x9f, 0x9f, 0xff );
	this->ColorSelected	 = zCOLOR( 0xff, 0xff, 0xff, 0xff );

//	this->SetHandleEventTop();														// insert myself into the callback list
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewDialogChoice::~zCViewDialogChoice()
{
	this->RemoveAllChoices();
}

//
//---------------------------------------------------------------------------------
//********************************     CHOICE     *********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	HandleEvent
//*********************************************************************************
//**
//*********************************************************************************
zBOOL zCViewDialogChoice::HandleEvent( int nKey )
{
	//
	//	CHECK IF THIS VIEW IS ACTIVE
	//
	if ( ! this->IsActive() ) return FALSE;

	//
	//	HANDLE THE KEY
	//


	// [Ulf] - 05.01.01 - But use game-constants, not keys...
	if (zinput->IsBinded(GAME_UP, nKey) || (nKey == MOUSE_WHEELUP))
	{
		this->SelectPrevious();
		return TRUE;
	}
	else if (zinput->IsBinded(GAME_DOWN, nKey) || (nKey == MOUSE_WHEELDOWN))
	{
		this->SelectNext();
		return TRUE;
	}
	else if (zinput->IsBinded(GAME_ACTION, nKey) || (nKey == KEY_ENTER) || (nKey == MOUSE_BUTTONLEFT))
	{
		// [BENDLIN] Addon - FIXME: Dialogfreezer Versuch 65536
		// Hier wurde andauernd versucht den Dialog zu schliessen,
		// obwohl er eigentlich wieder geoeffnet werden sollte...
		if (this->IsClosed() || this->IsClosing())
		{
			int warnAgrl = 0;
		}
		else
		{
			this->CloseSafe		();
			this->IsActivated	= FALSE;
			this->IsDone		= TRUE;
		}
		return TRUE;
	
	}
	else if (zinput->IsBinded(GAME_INVENTORY, nKey) || zinput->IsBinded(GAME_WEAPON, nKey))
	{
		// forget it
		return TRUE;
	}
	else switch( nKey )
	{
		case KEY_0		:	this->Select		( 0 )	; return TRUE;
		case KEY_1		:	this->Select		( 1 )	; return TRUE;
		case KEY_2		:	this->Select		( 2 )	; return TRUE;
		case KEY_3		:	this->Select		( 3 )	; return TRUE;
		case KEY_4		:	this->Select		( 4 )	; return TRUE;
		case KEY_5		:	this->Select		( 5 )	; return TRUE;
		case KEY_6		:	this->Select		( 6 )	; return TRUE;
		case KEY_7		:	this->Select		( 7 )	; return TRUE;
		case KEY_8		:	this->Select		( 8 )	; return TRUE;
		case KEY_9		:	this->Select		( 9 )	; return TRUE;
	}

	return FALSE; 
}

//
//---------------------------------------------------------------------------------
//*****************************     INTERACTION     *******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																 StartSelection
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::StartSelection( void )
{
	this->HasClosed				= TRUE	;
	this->IsActivated			= TRUE	;	
	this->IsDone				= FALSE	;
	this->OpenSafe				();
	this->SetHandleEventTop		();														// put myself on top of the event list
	this->SetEnableHandleEvent	( TRUE );														
}

//*********************************************************************************
//**																  StopSelection
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::StopSelection( void )
{
	this->IsDone				= FALSE	;
	this->IsActivated 			= FALSE	;
	this->CloseSafe				();
	this->SetEnableHandleEvent	( FALSE );												
}

//
//---------------------------------------------------------------------------------
//********************************     RENDER     *********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	   BlitText
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::BlitText( void )
{
	zCViewText2*	pViewText	= NULL;
	int				nTextLines	= this->ListTextLines.GetNumInList();

	for ( int nChoice = this->LineStart; nChoice < nTextLines; nChoice++ )
	{
		pViewText = this->ListTextLines[ nChoice ];
		if ( pViewText ) 
		{
			//
			//	CHECK TIMER
			//
			if ( pViewText->IsTimed() )
			{
				zREAL fTime	 = pViewText->GetTimer	 ();
				fTime		-= ::ztimer.GetFrameTimeF()/ztimer.GetMotionFactor();
				if	( fTime <= 0.0f )	{ this->RemoveText( pViewText ); continue; }
				else					pViewText->SetTimer( fTime );
			}

			//
			//	BLIT IT
			//
			this->BlitTextLine( pViewText );
		}
	}
}

//
//---------------------------------------------------------------------------------
//********************************     CHOICE     *********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	   ScrollUp
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::ScrollUp( void )
{
	if ( this->LineStart > 0 ) 
	{
		//
		//	CALCULATE OFFSET TO BE USED FOR BLITTING TEXTS
		//	
		zCViewText2* pViewText = this->ListTextLines[ this->LineStart ];
		if ( pViewText )
		{
			zCFont* pFont = pViewText->GetViewFont().GetFont();
			if ( pFont )
				this->OffsetTextPixel.Y += pFont->GetFontY();
		}

		//
		//	DISADVANCE STARTING LINE 
		//
		this->LineStart--;
	}
}

//*********************************************************************************
//**																	 ScrollDown
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::ScrollDown( void )
{
	if ( this->LineStart < this->Choices ) 
	{
		//
		//	CALCULATE OFFSET TO BE USED FOR BLITTING TEXTS
		//	
		zCViewText2* pViewText = this->ListTextLines[ this->LineStart ];
		if ( pViewText )
		{
			zCFont* pFont = pViewText->GetViewFont().GetFont();
			if ( pFont )
				this->OffsetTextPixel.Y -= pFont->GetFontY();
		}

		//
		//	ADVANCE STARTING LINE
		//
		this->LineStart++;
	}
}

//*********************************************************************************
//**														 IsSelectedOutsideAbove
//*********************************************************************************
//**
//*********************************************************************************
zBOOL zCViewDialogChoice::IsSelectedOutsideAbove( void )
{
	return ( this->ChoiceSelected < this->LineStart );
}

//*********************************************************************************
//**														 IsSelectedOutsideBelow
//*********************************************************************************
//**
//*********************************************************************************
zBOOL zCViewDialogChoice::IsSelectedOutsideBelow( void )
{
	zPOS			ptTopLeft		, 
					ptBottomRight	;				this->GetPixelBorder( ptTopLeft, ptBottomRight );
	zPOS			ptSelected		= ptTopLeft	;

	zCViewText2*	pViewText		= NULL		;
	zCFont*			pFont			= NULL		;

	for ( int nChoice = this->LineStart; nChoice < this->Choices; nChoice++ )
	{
		pViewText = this->ListTextLines[ nChoice ];
		if ( pViewText )
		{
			//
			//	ADD THIS TEXT'S HEIGHT
			//
							pFont= pViewText->GetViewFont().GetFont();
			if ( ! pFont )	pFont= this->ViewFont.GetFont();

			if	( pFont )	ptSelected.Y += pFont->GetFontY();

			//
			//	IF THIS TEXT IS THE SELECTED -> RETURN
			//
			if ( nChoice == this->ChoiceSelected ) break;
		}
	}

	return ( ptSelected.Y > ptBottomRight.Y );
}

//*********************************************************************************
//**																  ShowSelection
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::ShowSelected( void )
{
	while ( this->IsSelectedOutsideAbove() )
	{
		this->ScrollUp();
	}
	while ( this->IsSelectedOutsideBelow() )
	{
		this->ScrollDown();
	}
}

//*********************************************************************************
//**																 SelectPrevious
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::SelectPrevious( void )
{
	if  ( this->Choices			== 0 )	return;
	if	( this->ChoiceSelected	 > 0 )	this->ChoiceSelected--;
	else								this->ChoiceSelected = this->Choices - 1;

	this->HighlightSelected();
}

//*********************************************************************************
//**																	 SelectNext
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::SelectNext( void )
{
	if  ( this->Choices			== 0					 )	return;
	if	( this->ChoiceSelected	 < ( this->Choices - 1 ) )	this->ChoiceSelected++;
	else													this->ChoiceSelected = 0;

	this->HighlightSelected();
}

//*********************************************************************************
//**																		 Select
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::Select( int nChoice )
{
	if  ( ( nChoice < 0 ) || ( nChoice > ( this->Choices - 1 ) ) ) return;
	this->ChoiceSelected = nChoice;

	this->HighlightSelected();
}

//*********************************************************************************
//**																		 Select
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2* zCViewDialogChoice::GetSelection( void )
{
	return this->ListTextLines[ this->ChoiceSelected ];
}

//*********************************************************************************
//**																		 Select
//*********************************************************************************
//**
//*********************************************************************************
zSTRING zCViewDialogChoice::GetSelectedText( void )
{
	zCViewText2* pViewText = this->GetSelection();
	if	( pViewText )	return pViewText->GetText();
	else				return zSTRING( "" );
}

//*********************************************************************************
//**															  HighlightSelected
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::HighlightSelected( void )
{
	zCViewText2* pViewText = NULL;

	for ( int nChoice = 0; nChoice < this->Choices; nChoice++ )
	{
		pViewText = this->ListTextLines[ nChoice ];

		if ( pViewText )
		{
			if ( nChoice == this->ChoiceSelected )	pViewText->SetColor( this->ColorSelected	);	// highlight selection
			else									pViewText->SetColor( this->ColorGrayed		);	// un-highlight all other choices
		}
	}

	this->ShowSelected();
}

//*********************************************************************************
//**																	  AddChoice
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::AddChoice( zSTRING& strChoice, zBOOL bEnumerate )
{
	zSTRING strChoiceEffective = "";

	if ( bEnumerate )
	{
		strChoiceEffective = zSTRING( (int) this->Choices );
		strChoiceEffective += ". ";
	}
		strChoiceEffective += strChoice;

	this->PrintLine( strChoiceEffective );
	this->Choices++;

	this->Select( 0 );
}

//*********************************************************************************
//**																   RemoveChoice
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::RemoveChoice( zSTRING& strChoice )
{
}

//*********************************************************************************
//**																   RemoveChoice
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::RemoveChoice( int nChoice )
{
}

//*********************************************************************************
//**															   RemoveAllChoices
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDialogChoice::RemoveAllChoices( void )
{
	this->Choices			=  0;
	this->ChoiceSelected	= -1;
	this->LineStart			=  0;
	this->OffsetTextPixel	= zPOS( 0, 0 );

	this->ClearText();
}

