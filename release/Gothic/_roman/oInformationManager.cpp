/******************************************************************************** 
 
     $Workfile:: oInformationManager. $                $Date:: 16.02.01 14:01   $
     $Revision:: 60                   $             $Modtime:: 16.02.01 13:54   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oInformationManager.cpp $
 * 
 * 60    16.02.01 14:01 Moos
 * Noch mehr Runterfahr-Crashfixes
 * 
 * 59    13.02.01 11:26 Speckels
 * 
 * 58    12.02.01 3:02 Speckels
 * 
 * 57    1.02.01 21:48 Speckels
 * 
 * 56    1.02.01 21:06 Speckels
 * 
 * 55    29.01.01 16:28 Keskenti
 * 
 * 54    26.01.01 15:57 Speckels
 * 
 * 53    18.01.01 0:10 Keskenti
 * 
 * 52    18.01.01 0:07 Keskenti
 *  
 * 51    17.01.01 16:58 Keskenti
 * 
 * 50    17.01.01 16:56 Keskenti
 * 
 * 49    17.01.01 16:17 Keskenti
 * 
 * 48    17.01.01 13:01 Keskenti
 * 
 * 47    16.01.01 1:20 Keskenti
 * 
 * 46    16.01.01 1:20 Keskenti
 * 
 * 45    15.01.01 23:48 Keskenti
 * 
 * 44    15.01.01 21:20 Keskenti
 * 
 * 43    15.01.01 18:57 Keskenti
 * 
 * 42    12.01.01 16:54 Edenfeld
 * 
 * 41    12.01.01 13:19 Keskenti
 * 
 * 40    11.01.01 0:45 Keskenti
 * 
 * 39    10.01.01 14:29 Keskenti
 * 
 * 38    9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 37    3.01.01 18:09 Keskenti
 * 
 * 36    3.01.01 18:07 Keskenti
 * 
 * 35    3.01.01 18:02 Keskenti
 * 
 * 34    20.12.00 20:59 Keskenti
 * 
 * 33    20.12.00 18:48 Keskenti
 * 
 * 32    20.12.00 15:49 Keskenti
 * 
 * 31    20.12.00 15:48 Keskenti
 * 
 * 30    20.12.00 14:08 Speckels
 * 
 * 29    18.12.00 19:35 Speckels
 * 
 * 28    15.12.00 16:12 Keskenti
 * 
 * 27    13.12.00 14:16 Keskenti
 * 
 * 26    12.12.00 16:02 Keskenti
 * 
 * 25    12.12.00 16:01 Keskenti
 * 
 * 24    8.12.00 18:13 Keskenti
 * 
 * 23    7.12.00 19:35 Keskenti
 * 
 * 22    7.12.00 18:05 Keskenti
 * 
 * 21    6.12.00 15:53 Keskenti
 * 
 * 20    30.11.00 17:57 Keskenti
 * 
 * 19    27.11.00 14:48 Keskenti
 * 
 * 18    14.11.00 13:07 Keskenti
 * 
 * 17    8.11.00 12:45 Keskenti
 * 
 * 16    26.10.00 21:07 Keskenti
 * 
 * 15    25.10.00 19:09 Keskenti
 * 
 * 14    25.10.00 17:45 Keskenti
 * 
 * 13    23.10.00 23:27 Keskenti
 * 
 * 12    21.10.00 1:14 Keskenti
 * 
 * 11    20.10.00 22:57 Keskenti
 * 
 * 10    20.10.00 18:47 Keskenti
 * 
 * 9     20.10.00 17:53 Keskenti
 * 
 * 8     20.10.00 16:40 Keskenti
 * 
 * 7     20.10.00 15:35 Keskenti
 * 
 * 6     19.10.00 17:15 Keskenti
 * 
 * 5     19.10.00 15:56 Keskenti
 * 
 * 4     18.10.00 19:10 Keskenti
 * 
 * 3     18.10.00 18:33 Keskenti
 * 
 * 2     18.10.00 17:15 Keskenti
 * 
 *********************************************************************************/

#include <zCore.h>

#include <zTypes.h>
#include <zList.h>
#include <zParser.h>
#include <zview.h>
#include <z3D.h>
#include <zVob.h>
#include <zFile3D.h>
#include <zOption.h>
#include <zRenderer.h>
#include <zAlgebra.h>
#include <zModel.h>
#include <zMorphMesh.h>
#include <zParticle.h>
#include <zSound.h>
#include <zPhysics.h>
#include <zSoundMan.h>
#include <zMusic.h>
#include <zBuffer.h>
#include <zArchiver.h>
#include <zAICamera.h>
#include <zCCSPlayer.h>
#include <zInput_Win32.h>
#include <zEventMan.h>
#include <zWayNet.h>
#include <zFonts.h>

#include <oIncDialogs.h>
#include <oInfo.h>
#include <oGame.h>
#include <oInformationManager.h>
#include <oMobInter.h>

extern void NotifyInfoToSpy( char* pszMethod, char* pszOutput, char* pszStatus );

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//


oCInformationManager& oCInformationManager::GetInformationManager( void )
{
	static oCInformationManager mgrInfos;
	return mgrInfos;
}


/*********************************************************************************
 UpdateViewSettings

 01-Feb-01	[SPECKELS]	neu eingefuehrt
 *********************************************************************************/
void oCInformationManager::UpdateViewSettings()
{
	// [SPECKELS] zentrales Einstellen der FX-Modi
	
	int animateFade = zCViewFX::zEViewFX::VIEW_FX_FADE;
	int animateZoom = zCViewFX::zEViewFX::VIEW_FX_ZOOM;	
	int animateNone = zCViewFX::zEViewFX::VIEW_FX_NONE;	
	float durationFade = 1.0f;
	float durationZoom = 500.0f;
	float durationNone = 0.0f;
	if (!zoptions->ReadBool(zOPT_SEC_GAME,"animatedWindows",TRUE))
	{
		animateFade		= animateZoom	= animateNone;
		durationFade	= durationZoom	= durationNone;				
	};
	
	// Absolute Pixelgroesse
	zUINT32 width  = screen->anx(800);		// Fullwidth auf 800x600		// [BENDLIN] 800x600, old = 640
	zUINT32 height = screen->any(600)/4;	// Viertelhoehe bei 800x600		// [BENDLIN] 800x600, old = 480

	this->DlgStatus->SetDurationOpen	(durationFade);
	this->DlgStatus->SetDurationClose	(durationFade);
	this->DlgStatus->SetFXOpen			(animateFade);
	this->DlgStatus->SetFXClose			(animateFade);

	this->DlgChoice->SetDurationOpen	(durationZoom);
	this->DlgChoice->SetDurationClose	(durationZoom);
	this->DlgChoice->SetFXOpen			(animateZoom);
	this->DlgChoice->SetFXClose			(animateZoom);
	this->DlgChoice->SetSize			(zPOS(width,height));
	this->DlgChoice->SetPosition		(zPOS(4100-width/2,8192-height));

	this->DlgTrade->SetDurationOpen		(durationFade);
	this->DlgTrade->SetDurationClose	(durationFade);
	this->DlgTrade->SetFXOpen			(animateZoom);
	this->DlgTrade->SetFXClose			(animateZoom);	

	this->DlgTrade->UpdateViewSettings	();
};



/*********************************************************************************
 Constructor

 01-Feb-01	[SPECKELS]
			Setzen von FX-Einstellungen nach UpdateViewSettings ausgelager
 *********************************************************************************/
oCInformationManager::oCInformationManager()
{
	this->LastMethod = "Constructor";

	//
	//	SETUP SCREEN
	//
	zCViewDraw& viewScreen = zCViewDraw::GetScreen();

	//
	//	CREATE DIALOGS
	//
	// [EDENFELD] 1.09: behebt angeblich Crash beim Intel Compiler. Vorher: ....= zNEW(zCViewDialogChoice)(zCViewDialogChoice());
	this->DlgStatus		= zNEW(zCViewDialogChoice);
	this->DlgChoice		= zNEW(zCViewDialogChoice);
	this->DlgTrade		= zNEW(oCViewDialogTrade );

	//
	//	SETUP PRINT VIEW
	//
	zUINT32 nQuartSize = 8192 >> 2;				

	this->DlgStatus->Init				( &viewScreen			, 
											FALSE				, 
											0,0,0,0,
											zSTRING( "DLG_CHOICE.TGA" )	
										);
	this->DlgStatus->SetPosition		( zPOS( 0				, 1 * nQuartSize	)	);
	this->DlgStatus->SetSize			( zPOS( 4 * nQuartSize	, 2 * nQuartSize	)	);

	//[EDENFELD] 1.09 : Fonts in Constants.d enthalten
	zCPar_Symbol *sym = NULL;
	zSTRING fontName("font_default.tga");
	sym = parser.GetSymbol("TEXT_FONT_DEFAULT");
	if (sym) sym->GetValue(fontName);
	this->DlgStatus->SetFont			( fontName										);

	this->DlgStatus->SetPixelMargins	( zPOS( 10, 10 ), zPOS( 20, 10 )				);
	this->DlgStatus->RemoveAllChoices	();

	//
	//	SETUP CHOICE DIALOG
	//
	this->DlgChoice->Init				( &viewScreen							, 
											FALSE								, 
											0,0,0,0,
											zSTRING( "DLG_CHOICE.TGA" )	
										);
	// [SPECKELS] Pos udn Size wird in UpdateViewSettings() gesetzt
	//this->DlgChoice->SetPosition		( zPOS( 0				, 3 * nQuartSize	)	);
	//this->DlgChoice->SetSize			( zPOS( 4 * nQuartSize	,	  nQuartSize	)	);
	this->DlgChoice->SetFont			( fontName										);
	this->DlgChoice->SetPixelMargins	( zPOS( 10, 10 ), zPOS( 20, 10 )				);
	this->DlgChoice->RemoveAllChoices	();

	//
	//	SETUP TRADE DIALOG
	//
	this->DlgTrade ->Init				( &viewScreen							, 
											FALSE								, 
											0,0,0,0,
											zSTRING( "DEFAULT.TGA" )	
										);
	this->DlgTrade ->SetPosition		( zPOS( 0				, 0					)	);
	this->DlgTrade ->SetSize			( zPOS( 4 * nQuartSize	, 4 *  nQuartSize	)	);
	this->DlgTrade ->SetFont			( fontName										);
	this->DlgTrade ->SetPixelMargins	( zPOS( 0, 0 ), zPOS( 0, 0 )					);

	//
	//	INIT VARS
	//
	this->Npc				= NULL						;
	this->Player			= NULL						;
	this->Info				= NULL						;
	this->IsDone			= TRUE						;
	this->MustOpen			= TRUE						;
	this->IndexBye			= -1						;
	this->Mode				= INFO_MGR_MODE_IMPORTANT	;

	UpdateViewSettings();
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
oCInformationManager::~oCInformationManager()
{
	this->LastMethod = "Destructor";

	zCViewDraw& viewScreen = zCViewDraw::GetScreen();
    if (&viewScreen)
    {
    	((zCViewObject*) &viewScreen)->RemoveChild( this->DlgChoice );
    	((zCViewObject*) &viewScreen)->RemoveChild( this->DlgTrade	);
	    ((zCViewObject*) &viewScreen)->RemoveChild( this->DlgStatus );
    }

	zRELEASE( this->DlgStatus );
	zRELEASE( this->DlgChoice );
	zRELEASE( this->DlgTrade  );
}

//
//---------------------------------------------------------------------------------
//*******************************     EXTERNALS     *******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																   ToggleStatus
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::ToggleStatus( void )
{
	static zBOOL bIsStatusEnabled = FALSE;

	bIsStatusEnabled = ! bIsStatusEnabled;

	if ( bIsStatusEnabled )	{ this->PrintStatus();	this->DlgStatus->StartSelection(); oCNpc::player->SetMovLock( TRUE  ); }
	else					{						this->DlgStatus->StopSelection (); oCNpc::player->SetMovLock( FALSE ); }
}

//*********************************************************************************
//**																    PrintStatus
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::PrintStatus( void )
{
	this->DlgStatus->RemoveAllChoices();

	zSTRING strStatus;

	//
	//	BOOLS
	//
						strStatus = zSTRING( "IsDone:                " ) + ( this->IsDone				 ? "TRUE" : "FALSE" );								this->DlgStatus->AddChoice( strStatus );
						strStatus = zSTRING( "IsWaitingForEnd:       " ) + ( this->IsWaitingForEnd		 ? "TRUE" : "FALSE" );								this->DlgStatus->AddChoice( strStatus );
						strStatus = zSTRING( "IsWaitingForScript:    " ) + ( this->IsWaitingForScript	 ? "TRUE" : "FALSE" );								this->DlgStatus->AddChoice( strStatus );
						strStatus = zSTRING( "IsWaitingForOpen:      " ) + ( this->IsWaitingForOpen		 ? "TRUE" : "FALSE" );								this->DlgStatus->AddChoice( strStatus );
						strStatus = zSTRING( "IsWaitingForClose:     " ) + ( this->IsWaitingForClose	 ? "TRUE" : "FALSE" );								this->DlgStatus->AddChoice( strStatus );
						strStatus = zSTRING( "IsWaitingForSelection: " ) + ( this->IsWaitingForSelection ? "TRUE" : "FALSE" );								this->DlgStatus->AddChoice( strStatus );
						strStatus = zSTRING( "MustOpen:              " ) + ( this->MustOpen				 ? "TRUE" : "FALSE" );								this->DlgStatus->AddChoice( strStatus );

	//
	//	ENUMS
	//
						strStatus = zSTRING( "Mode:                  " ) + ( this->Mode == INFO_MGR_MODE_IMPORTANT	? "INFO_MGR_MODE_IMPORTANT" 
																		   : this->Mode == INFO_MGR_MODE_INFO		? "INFO_MGR_MODE_INFO" 
																		   : this->Mode == INFO_MGR_MODE_CHOICE		? "INFO_MGR_MODE_CHOICE" 
																		   : this->Mode == INFO_MGR_MODE_TRADE		? "INFO_MGR_MODE_TRADE" 
																		   :										  "INVALID"						);		this->DlgStatus->AddChoice( strStatus );

	//
	//	INTS
	//
						strStatus = zSTRING( "IndexBye:              " ) + zSTRING( this->IndexBye			);												this->DlgStatus->AddChoice( strStatus );
						strStatus = zSTRING( "ImportantCurrent:      " ) + zSTRING( this->ImportantCurrent	);												this->DlgStatus->AddChoice( strStatus );
						strStatus = zSTRING( "ImportantMax:          " ) + zSTRING( this->ImportantMax		);												this->DlgStatus->AddChoice( strStatus );
																																							
	//																																						
	//	PLAYERS																																				
	//																																						
	if ( this->Npc	  )	strStatus = zSTRING( "Npc:					 " ) + this->Npc	->GetName();														this->DlgStatus->AddChoice( strStatus );
	if ( this->Player )	strStatus = zSTRING( "Player:				 " ) + this->Player	->GetName();														this->DlgStatus->AddChoice( strStatus );
																																							
	//																																						
	//	INFO																																				
	//																																						
	if ( this->Info )	strStatus = zSTRING( "Info:					 " ) + this->Info	->GetText();															this->DlgStatus->AddChoice( strStatus );

	//																																						
	//	METHOD																																				
	//																																						
						strStatus = zSTRING( "Last Method:			 " ) + this->LastMethod;															this->DlgStatus->AddChoice( strStatus );
}

//*********************************************************************************
//**																	HasFinished
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCInformationManager::HasFinished( void )
{
//	this->LastMethod = "HasFinished";

	return this->IsDone;
}

//*********************************************************************************
//**																  WaitingForEnd
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCInformationManager::WaitingForEnd( void )
{
//	this->LastMethod = "WaitingForEnd";

	return this->IsWaitingForEnd;
}

//*********************************************************************************
//**																		 SetNpc
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::SetNpc( oCNpc* pNpc )
{
	this->LastMethod = "SetNpc";

	//
	//	DO NOT START UNTIL WE HAVE STOPPED
	//
	if ( ! this->HasFinished() ) return;

	//
	//	RETRIEVE AND LOCK PLAYER
	//
	this->Npc		= pNpc;
	this->Player	= zDYNAMIC_CAST<oCNpc>  ( ::ogame->GetSelfPlayerVob() );
	this->Player->SetMovLock( TRUE );
	this->Player->CloseInventory();

	//
	//	RE- INIT VARS
	//
	this->Info					= NULL						;
	this->IsDone				= FALSE						;
	this->IsWaitingForEnd		= FALSE						;
	this->IsWaitingForScript	= FALSE						;
	this->IsWaitingForOpen		= FALSE						;
	this->IsWaitingForClose		= FALSE						;
	this->IsWaitingForSelection	= FALSE						;
	this->MustOpen				= FALSE						;
	this->IndexBye				= -1						;
	this->ImportantCurrent		= 0							;
	this->Mode					= INFO_MGR_MODE_IMPORTANT	;

	//
	//	DEACTIVATE CHOICE DIALOG'S INPUT HANDLER
	//
	this->DlgChoice->Activate( FALSE );

	//
	//	ACTIVATE DIALOG CAMERA
	//
	this->CameraStart();

	//
	//	DEACTIVATE PLAYER STATUS DISPLAY
	//
	::ogame->SetShowPlayerStatus( FALSE );

	//
	//	SET STARTING STATE
	//
	this->OnImportantBegin();
}

//*********************************************************************************
//**																		 Update
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::Update( void )
{
	this->LastMethod = "Update";

	//
	//	CHECK CONSTISTENCY
	//
	if ( ( ! this->Npc ) || ( ! this->Player )	) return;
	if (	 this->IsDone						) return;

	//
	//	KEEP PLAYER LOCKED
	//
	this->Player->SetMovLock( TRUE );

	//
	//	KEEP CAMERA WAITING
	//
	this->CameraRefresh();

	//
	//	WAIT FOR NPC TO COMPLETE ITS ACTIONS 
	//
	if ( this->IsWaitingForScript )
	{
		 this->InfoWaitForEnd();

		 return;
	}

	//
	//	WAIT FOR WINDOW TO CLOSE
	//
	if ( this->IsWaitingForClose )
	{
		switch( this->Mode )
		{
			case INFO_MGR_MODE_INFO		:	
			case INFO_MGR_MODE_CHOICE	:	this->IsWaitingForClose = ! this->DlgChoice->IsClosed(); break;
			case INFO_MGR_MODE_TRADE	:	this->IsWaitingForClose = ! this->DlgTrade ->IsClosed(); break;
		}

		return;
	}

	//
	//	OPEN IF NECCESSARY
	//
	if ( ! this->IsWaitingForEnd )		// !!! DO NOT OPEN ANY DIALOG WHEN WE HAVE RECEIVED A STOP MESSAGE !!!
	if (   this->MustOpen		 )
	{
		switch( this->Mode )
		{
			case INFO_MGR_MODE_INFO		:	
			case INFO_MGR_MODE_CHOICE	:	this->DlgChoice->StartSelection(); break;
			case INFO_MGR_MODE_TRADE	:	this->DlgTrade ->StartSelection(); break;
		}

		//
		//	MARK AS OPEN
		//
		this->MustOpen			= FALSE	;

		//
		//	WAIT FOR WINDOW TO CLOSE
		//
		this->IsWaitingForOpen	= TRUE	;

		return;
	}

	//
	//	WAIT FOR WINDOW TO OPEN
	//
	if ( this->IsWaitingForOpen )
	{
		//
		//	ACTIVATE CHOICE DIALOG'S INPUT HANDLER
		//
		this->DlgChoice->Activate( FALSE );

		//
		//	WAIT FOR PROPER DIALOG
		//
		switch( this->Mode )
		{
			case INFO_MGR_MODE_INFO		:	
			case INFO_MGR_MODE_CHOICE	:	this->IsWaitingForOpen = ! this->DlgChoice->IsOpen(); break;
			case INFO_MGR_MODE_TRADE	:	this->IsWaitingForOpen = FALSE;						  break;
		}

		if ( this->IsWaitingForOpen ) return;

		//
		//	ACTIVATE CHOICE DIALOG'S INPUT HANDLER
		//
		this->DlgChoice->Activate( TRUE );

		//
		//	WAIT FOR USER TO CHOOSE
		//
		this->IsWaitingForSelection = TRUE;

		return;
	}

	//
	//	WAIT FOR USER TO SELECT A CHOICE OR FINSH HIS TRADE
	//
	if ( ! this->IsWaitingForEnd		)	// !!! DO NOT AWAIT USER INPUT WHEN WE HAVE RECEIVED A STOP MESSAGE !!!
	if (   this->IsWaitingForSelection  )
	{
		switch( this->Mode )
		{
			case INFO_MGR_MODE_INFO		:								this->IsWaitingForSelection = ! this->DlgChoice->HasFinished();	break;	
			case INFO_MGR_MODE_CHOICE	:								this->IsWaitingForSelection = ! this->DlgChoice->HasFinished();	break;	
			case INFO_MGR_MODE_TRADE	:	this->DlgTrade->Update();	this->IsWaitingForSelection = ! this->DlgTrade ->HasFinished();	if ( ! this->IsWaitingForSelection ) this->OnTradeEnd(); break;	
		}

		if ( this->IsWaitingForSelection ) return;

		//
		//	DEACTIVATE CHOICE DIALOG'S INPUT HANDLER
		//
		this->DlgChoice->Activate( FALSE );

		//
		//	WAIT FOR THE WINDOW TO CLOSE
		//
		this->IsWaitingForClose = TRUE;

		return;
	}

	//
	//	PROCESS SELECTION - IF ANY 
	//
	if ( ! this->IsWaitingForEnd )		// !!! DO NOT HANDLE ANY DIALOG WHEN WE HAVE RECEIVED A STOP MESSAGE !!!
	{
		switch( this->Mode )
		{
			case INFO_MGR_MODE_IMPORTANT:	if ( this->ImportantCurrent > 0	)	this->ProcessNextImportant	();										
											else								this->ProcessImportant		();								break;
			case INFO_MGR_MODE_INFO		:	this->OnInfo	( this->DlgChoice->GetSelectedIndex() );										break;
			case INFO_MGR_MODE_CHOICE	:	this->OnChoice	( this->DlgChoice->GetSelectedIndex() );										break;
		}

		return;
	}

	//
	//	HAVE WE FINISHED ?
	//
	if (   this->IsWaitingForEnd	)
	if ( ! this->IsWaitingForClose	)
	if ( ! this->IsWaitingForScript	)
	{
		this->OnTermination();
	}
}

//*********************************************************************************
//**																		   Exit
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::Exit( void )
{
	this->LastMethod = "Exit";

	//
	//	CLOSE SELF
	//
	this->OnExit();
}

//
//---------------------------------------------------------------------------------
//********************************     PROCESS     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	CameraStart
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::CameraStart( void )
{
	//
	//	START DIALOG CAMERA
	//
	zCArray<zCVob*> aryPlayers;
	aryPlayers.Insert( this->Player );
	aryPlayers.Insert( this->Npc	);

	//::ogame->GetCameraAI()->SetTargetList		( aryPlayers	);
	::ogame->GetCameraAI()->SetDialogCamDuration( FLT_MAX		);
	::ogame->GetCameraAI()->SetMode				( CamModDialog,aryPlayers	);

	//
	//	STOP ALL AI_OUTPUTs FROM DISABLING THE DIALOG CAM
	//
	oCNpc::EnableDialogCamStop( FALSE );
}

//*********************************************************************************
//**																	 CameraStop
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::CameraStop( void )
{
	//
	//	STOP ALL AI_OUTPUTs FROM DISABLING THE DIALOG CAM
	//
	oCNpc::EnableDialogCamStop( TRUE );

	//
	//	STOP DIALOG CAMERA
	//
	::ogame->GetCameraAI()->SetMode( CamModNormal );
}

//*********************************************************************************
//**																  CameraRefresh
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::CameraRefresh( void )
{
	::ogame->GetCameraAI()->SetDialogCamDuration( FLT_MAX );
}

//*********************************************************************************
//**															   ProcessImportant
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::ProcessImportant( void )
{
	this->LastMethod			= "ProcessImportant";

	this->IsWaitingForScript	= FALSE;
	this->ImportantCurrent		= 0;
	this->ImportantMax			= ::ogame->GetInfoManager()->GetInfoCountImportant( this->Player, this->Npc );

	this->ProcessNextImportant();
}

//*********************************************************************************
//**														   ProcessNextImportant
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::ProcessNextImportant( void )
{
	this->LastMethod			= "ProcessNextImportant";

	//
	//	CHECK FOR END
	//
	if ( this->ImportantCurrent >= this->ImportantMax ) this->OnImportantEnd();

	//
	//	GET NEXT INFO
	//
	this->Info = ::ogame->GetInfoManager()->GetInfoImportant( this->Player, this->Npc, this->ImportantCurrent );
	this->ImportantCurrent ++;

	//
	//	PROCESS INFO
	//
	if ( this->Info ) this->OnInfo( this->Info );
}

//*********************************************************************************
//**															     InfoWaitForEnd
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::InfoWaitForEnd( void )
{
	this->LastMethod			= "InfoWaitForEnd";

	//
	//	WAIT FOR NPC AND PLAYER TO PROCESS ITS MESSAGES
	//
	if (	this->Npc		->GetEM()->	IsEmpty			( TRUE /*IGNORE OVERLAYS*/ ) )
	if (	this->Player	->GetEM()->	IsEmpty			( TRUE /*IGNORE OVERLAYS*/ ) )
	if ( !	this->Npc		->GetEM()->	GetCutsceneMode	()							 )
	if ( !	this->Player	->GetEM()->	GetCutsceneMode	()							 )

		this->IsWaitingForScript = FALSE;
}

//*********************************************************************************
//**																   CollectInfos
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::CollectInfos( void )
{
	this->LastMethod			= "CollectInfos";

	//
	//	CHECK NPC
	//
	if ( ! this->Npc ) return;
	
	//
	//	CLEAR CHOICES
	//
	this->DlgChoice->RemoveAllChoices();

	//
	//	GET NPC'S INFOS CONCERNING PLAYER
	//
	oCInfo* pInfo	= NULL;
	int		nInfos	= ::ogame->GetInfoManager()->GetInfoCountUnimportant( this->Player, this->Npc );

	//
	//	ADD INFOS TO CHOICE BOX
	//
	for ( int nInfo = 0; nInfo < nInfos; nInfo++ )
	{
		pInfo = ::ogame->GetInfoManager()->GetInfoUnimportant( this->Player, this->Npc, nInfo );
		if ( pInfo )
		{
			this->DlgChoice->AddChoice( pInfo->GetText() );
		}
	}

	//
	//	KEINE INFOS ? 
	//
	if ( nInfos == 0 ) 
	{
		//
		//	IMPORTANT INFOS ?
		//
		if ( this->ImportantMax > 0 )
		{
			this->OnExit();	
		}
		else
		{
#ifdef LANG_ENU
			zSTRING strChoice	= "END." ;	// END mit Punkt. Daran erkennt man, ob keine Skript-Infos vorhanden sind.
#else
			zSTRING strChoice	= "ENDE." ; // ENDE mit Punkt. Daran erkennt man, ob keine Skript-Infos vorhanden sind.
#endif
			this->IndexBye		= nInfos;
			this->DlgChoice->AddChoice( strChoice );
		}
	}

}

//*********************************************************************************
//**																 CollectChoices
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCInformationManager::CollectChoices( oCInfo* pInfo )
{
	this->LastMethod			= "CollectChoices";

	//
	//	CHECK INFO
	//
	if ( ! pInfo )																return FALSE;
	
	//
	//	GET INFO'S CHOICES - IF ANY
	//
	oCInfoChoice*	pChoice		= NULL;
	int				nChoices	= pInfo->GetChoiceCount();	if ( ! nChoices )	return FALSE;

	//
	//	CLEAR CHOICES
	//
	this->DlgChoice->RemoveAllChoices();

	//
	//	FILL CHOICES
	//
	for ( int nChoice = 0; nChoice < nChoices; nChoice++ )
	{
		pChoice = pInfo->GetChoices()[ nChoice ];
		this->DlgChoice->AddChoice( pChoice->Text );
	}

	return TRUE;
}

//
//---------------------------------------------------------------------------------
//********************************     EVENTS     *********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**															   OnImportantBegin
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnImportantBegin( void )
{
	this->LastMethod			= "OnImportantBegin";

	this->IsWaitingForScript	= TRUE	 				 ;
	this->Mode					= INFO_MGR_MODE_IMPORTANT;
}

//*********************************************************************************
//**																 OnImportantEnd
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnImportantEnd( void )
{
	this->LastMethod			= "OnImportantEnd";

	this->OnInfoBegin();
}

//*********************************************************************************
//**																    OnInfoBegin
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnInfoBegin( void )
{
	this->LastMethod			= "OnInfoBegin";

	this->Mode		= INFO_MGR_MODE_INFO;
	this->MustOpen	= TRUE				;

	this->CollectInfos();
}

//*********************************************************************************
//**																	     OnInfo
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnInfo( int nInfo )
{
	this->LastMethod			= "OnInfo";

	//
	//	BYE ?
	//
	if ( nInfo == this->IndexBye )	{ this->OnExit		( ); return; }

	//
	//	CONTINUE ...
	//
	oCInfo* pInfo = ::ogame->GetInfoManager()->GetInfoUnimportant( this->Player, this->Npc, nInfo );

	if ( pInfo )
	{
									this->OnInfo		( pInfo );
		if	( pInfo->IsTrade() )	this->OnTradeBegin	( );
	}	
}

//*********************************************************************************
//**																		 OnInfo
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnInfo( oCInfo* pInfo )
{
	this->LastMethod			= "OnInfo2";

	//
	//	CHECK INFO
	//
	if ( ! pInfo ) return;

	//
	//	SETUP SCRIPT INSTANCES
	//
	::parser.SetInstance( "SELF" , this->Npc	);
	::parser.SetInstance( "OTHER", this->Player );

	//
	//	CHECK INFO CONDITIONS
	//
	if ( pInfo->InfoConditions() )
	{
		//
		//	EXECUTE INFO
		//
        pInfo->Info();

		//
		//	WAIT FOR THIS INFO TO COMPLETE
		//
		this->IsWaitingForScript = TRUE;
	}

	//
	//	CHECK IMPORTANT INFOS FOR CHOICES
	//
	if ( pInfo->IsImportant() )
	{
		if ( pInfo->GetChoiceCount() ) { this->Info = pInfo; this->OnChoiceBegin();	}

		//
		//	DO NOT RECOLLECT IMPORTANT INFOS
		//
		return;
	}
	
	//
	//	CHECK FOR CHOICES
	//
	if ( pInfo->GetChoiceCount() ) { this->Info = pInfo; this->OnChoiceBegin();	}
	else												 this->OnInfoBegin	();
}

//*********************************************************************************
//**																  OnChoiceBegin
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnChoiceBegin( void )
{
	this->LastMethod			= "OnChoiceBegin";

	if ( ! this->CollectChoices( this->Info ) ) { this->OnChoiceEnd(); return; }

	this->Mode		= INFO_MGR_MODE_CHOICE	;
	this->MustOpen	= TRUE					;
}

//*********************************************************************************
//**																	   OnChoice
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnChoice( int nChoice )
{
	this->LastMethod			= "OnChoice";

	//
	//	CHECK INFO
	//	
	if ( ! this->Info ) return;

	//
	//	GET SELECTED CHOICE
	//
	oCInfoChoice* pChoice = this->Info->GetChoices()[ nChoice ];
	if ( pChoice ) 
	{
		this->OnChoice( pChoice );
	}

	//
	//	RESTART CHOICE SELECTION
	//
	this->OnChoiceBegin();
}

//*********************************************************************************
//**																	   OnChoice
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnChoice( oCInfoChoice* pChoice )
{
	this->LastMethod			= "OnChoice2";

	//
	//	CHECK CHOICE
	//
	if ( ! pChoice ) return;

	//
	//	SAVE FUNCTION
	//
	int nFunction = pChoice->Function;

	//
	//	REMOVE THIS CHOICE
	//
	this->Info->RemoveChoice( pChoice->Text );

	//
	//	EXECUTE CHOICE
	//
	::parser.SetInstance( "SELF" , this->Npc	);
	::parser.SetInstance( "OTHER", this->Player );
	::parser.CallFunc	( nFunction				);

	//
	//	WAIT FOR THIS INFO TO COMPLETE
	//
	this->IsWaitingForScript = TRUE;
}

//*********************************************************************************
//**																	OnChoiceEnd
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnChoiceEnd( void )
{
	this->LastMethod			= "OnChoiceEnd";

	this->OnInfoBegin();
}

//*********************************************************************************
//**																	  OnInfoEnd
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnInfoEnd( void )
{
	this->LastMethod			= "OnInfoEnd";

	this->Mode = INFO_MGR_MODE_TRADE;
	this->OnExit();
}

//*********************************************************************************
//**																   OnTradeBegin
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnTradeBegin( void )
{
	this->LastMethod			= "OnTradeBegin";

	//
	//	START TRADE
	//
	this->Mode					= INFO_MGR_MODE_TRADE	;
	this->MustOpen				= TRUE					;

	// [BENDLIN] Set trading NPCs
	if (this->Npc)
		this->Npc->SetTradeNpc(this->Player);
	if (this->Player)
		this->Player->SetTradeNpc(this->Npc);

	this->DlgTrade->SetNpcLeft	( this->Npc		);
	this->DlgTrade->SetNpcRight	( this->Player  );
}

//*********************************************************************************
//**																	 OnTradeEnd
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnTradeEnd( void )
{
	this->LastMethod			= "OnTradeEnd";

	// [BENDLIN] Set trading NPCs
	if (this->Npc)
		this->Npc->SetTradeNpc(NULL);
	if (this->Player)
		this->Player->SetTradeNpc(NULL);

	//
	//	START INFO SELECTION
	//
	this->OnInfoBegin();
}

//*********************************************************************************
//**																		 OnExit
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnExit( void )
{
	this->LastMethod			= "OnExit";

	//
	//	CLOSE DIALOGS
	//
	this->DlgChoice->StopSelection	();		
	this->DlgTrade ->StopSelection	();		

	//
	//	MARK AS FINISHED
	//
	this->IsWaitingForEnd	= TRUE	;
	this->MustOpen			= FALSE ;
}

//*********************************************************************************
//**																  OnTermination
//*********************************************************************************
//**
//*********************************************************************************
void oCInformationManager::OnTermination( void )
{
	this->LastMethod			= "OnTermination";

	//
	//	RE-ACTIVATE PLAYER STATUS DISPLAY
	//
	::ogame->SetShowPlayerStatus( TRUE );

	//
	//	RE-ACTIVATE DIALOG CAM
	//
	this->CameraStop();

	//
	//	UNLOCK PLAYER MOVEMENT
	//
	if ( this->Player )
	{
		this->Player->SetMovLock( FALSE );
		// [BENDLIN] 2002-05-17, MOB dialog states back
		oCMobInter* mob = dynamic_cast<oCMobInter*>(this->Player->GetInteractMob());
		if (mob)
		{
			oCMobMsg* msg = zNEW(oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE, this->Player));
			msg->from = mob->GetState();
			msg->to = msg->from - 1;
			mob->GetEM()->OnMessage(msg, this->Player);
		}
	}

	//
	//	RESET VARs
	//
	this->Player				= NULL	;
	this->Npc					= NULL	;
	this->IsWaitingForEnd		= FALSE	;
	this->IsDone				= TRUE	;
	this->ImportantCurrent		= 0		;
}