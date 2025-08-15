#include <windows.h>
#include "zcore.h"
#include "zWin32.h"
#include "oVisFX.h"
#include "zConsole.h"
#include "zCPUSpecs.h"
#include "oVisFX.h"
#include "zCSCamera.h"
#include "zoption.h"
#include "zoption_const.h"
#include "zinput.h"
#include "zinput_win32.h"
#include "zExceptionHandler.h"
#include "zParser.h"
#include "ogame.h"
#include "onpc.h"
#include "oworld.h"
#include "zAICamera_Movement.h"
#include "zSky.h"
#include "ofocus.h"
 
const unsigned long MIN_REQ_FREQ = 330;
const unsigned long MIN_REQ_MEM  = 128;

zBOOL s_bCheckRoutines = FALSE;

extern HWND	winHandle;  

zBOOL freeLook = FALSE;

void Freelook () 
{
	// [HILDEBRANDT] Problem: vorher wurde die Windows API benutzt fuer die Maus-Abfrage, falls DInput aktiv ist,
	// ist dies allerdings nicht mehr moeglich. Loesung:
	// - bei DInput enabled wird die Mouse durch DInput abgefragt
	// - bei DInput disabled wird die Mouse durch die WinAPI abgefragt
	if (zinput->GetDeviceEnabled(zINPUT_MOUSE))
	{
		const float X_SCALE = 2;
		const float Y_SCALE = 2;

 		zREAL dx, dy, dz;
		zinput->GetMousePos (dx, dy, dz);

		if (dx) zCCamera::activeCam->GetVob()->RotateWorld		(0,1,0, float(dx)/X_SCALE);
		if (dy) zCCamera::activeCam->GetVob()->RotateLocalX		(float(dy)/Y_SCALE);
	} else
	{
		static zLONG lastX = 0, lastY = 0;
		
		const float X_SCALE = 10;
		const float Y_SCALE = 10;

		POINT   mPos;			// Mouse position
		GetCursorPos(&mPos);	// Get cursor position
		
		zLONG dx= mPos.x-lastX;
		zLONG dy= mPos.y-lastY;

		if (mPos.x < 10  ||  mPos.y < 10 ) {
			SetCursorPos(630,470);
			mPos.x = 630;
			mPos.y = 470;
		}
		else if (mPos.x > 635 ||  mPos.y > 475) {
			SetCursorPos(15,15);
			mPos.x = 15;
			mPos.y = 15;
		}
		
		lastX = mPos.x;
		lastY = mPos.y;
		if (dx) zCCamera::activeCam->GetVob()->RotateWorld		(0,1,0, float(dx)/X_SCALE);
	//	if (dx) zCCamera::activeCam->GetVob()->RotateLocalY     (float(dx)/X_SCALE);
		if (dy) zCCamera::activeCam->GetVob()->RotateLocalX		(float(dy)/Y_SCALE);
	};
};


void TestKeys_Carsten(int key)
{
};


void ExceptionInfoCallback(LPEXCEPTION_DESCR pExceptionDescr) 
{
	zSTRING			state;
	SYSTEM_INFO		systemInfo;
	MEMORYSTATUS	memInfo;
	char			userName[200];
	zDWORD			userNameSize	= sizeof(userName);
	zSTRING			nextLine;
	

	// add game related information to the exception struct

	nextLine = zSTRING(zSTRING(APP_NAME) + zSTRING(", Parser Version: ") + zSTRING(zCParser::GetVersion())).ToChar();

	pExceptionDescr->errDescr[pExceptionDescr->numErr] = (char*)malloc(strlen(nextLine.ToChar()));

	strcpy(pExceptionDescr->errDescr[pExceptionDescr->numErr++],nextLine.ToChar());

	if (!GetUserName(userName, &userNameSize)) lstrcpy(userName, "Unknown");
	GetSystemInfo(&systemInfo);

	memInfo.dwLength = sizeof(memInfo);
	GlobalMemoryStatus(&memInfo);
	nextLine = zSTRING("User:  " + zSTRING(userName) + ",  CPUType: " + zSTRING(systemInfo.dwProcessorType) + ",  Mem: " + zSTRING((memInfo.dwTotalPhys + ONEM - 1) / ONEM) + " MB total, " + zSTRING((memInfo.dwAvailPhys + ONEM - 1) / ONEM) + " MB free").ToChar();
	pExceptionDescr->errDescr[pExceptionDescr->numErr] = (char*)malloc(strlen(nextLine.ToChar()));
	strcpy(pExceptionDescr->errDescr[pExceptionDescr->numErr++],nextLine.ToChar());

	if ( zCCamera::activeCam && zCCamera::activeCam->GetVob() ) {

		zSTRING pos =  zSTRING("Pos(") + 
					   zSTRING(zCCamera::activeCam->GetVob()->GetPositionWorld()[VX]) + zSTRING("/") + 
					   zSTRING(zCCamera::activeCam->GetVob()->GetPositionWorld()[VY]) + zSTRING("/") +
					   zSTRING(zCCamera::activeCam->GetVob()->GetPositionWorld()[VZ]) + zSTRING(")");

		zSTRING at  =  zSTRING(", At(") + 
					   zSTRING(zCCamera::activeCam->GetVob()->GetAtVectorWorld()[VX]) + zSTRING("/") + 
					   zSTRING(zCCamera::activeCam->GetVob()->GetAtVectorWorld()[VY]) + zSTRING("/") +
					   zSTRING(zCCamera::activeCam->GetVob()->GetAtVectorWorld()[VZ]) + zSTRING(")");

		nextLine = zSTRING(zSTRING("Camera: ") + pos + at).ToChar();
		pExceptionDescr->errDescr[pExceptionDescr->numErr] = (char*)malloc(strlen(nextLine.ToChar()));
		strcpy(pExceptionDescr->errDescr[pExceptionDescr->numErr++],nextLine.ToChar());
	}

};

static zBOOL SpawnNpc(const zCVob* self, const zSTRING &instance, const float range, const int count)
{
	
	zCParser *p = zCParser::GetParser();

	int index = p -> GetIndex(instance);

	for (int i=0; i<count; i++)
	{
		// searching for a good position for the monster
		// TODO: make it better!

		oCNpc* npc = dynamic_cast<oCNpc*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_NSC,index));
		if (!npc) {
			zERR_WARNING("C: Wld_SpawnNpcRange(): Monster Instance not found");
			return FALSE;
		}

		zMAT4 newMat = self->trafoObjToWorld;
		newMat.PostRotateY(zRandF(360));
		newMat.SetTranslation(newMat.GetTranslation() + 150 * newMat.GetAtVector());
		npc->SetPositionWorld(newMat.GetTranslation());

		ogame->GetGameWorld()->AddVobRelease(npc);

		npc->BeginMovement();

		int tries = 10;		// zehn versuche den beknackten npc zu inserten
		while (--tries) 
		{
			zMAT4 newMat = self->trafoObjToWorld;
			newMat.PostRotateY(zRandF(360));
			newMat.SetTranslation(newMat.GetTranslation() + ((zRandF(range)+100) * newMat.GetAtVector()));
			zPOINT3 newPos = newMat.GetTranslation();
			if ( npc->SearchNpcPosition(newPos) ) npc->SetPositionWorld(newPos);
			else continue;

			if ( oCNpc::player->FreeLineOfSight(npc) ) break;
		}

		npc->EndMovement();

		if (!tries) npc->RemoveVobFromWorld();
	}
	
	return FALSE;
}

static zBOOL oCarsten_EvalFunc(const zSTRING &in, zSTRING &msg)
{
	zSTRING s = in;
	s.Upper();

	static oCVisualFX *playedFX = 0;

	if (s.PickWord(1, " ") == "PLAY")
	{
		if (s.PickWord(2, " ") == "FX")
		{
			zSTRING fxname = s.PickWord(3, " ");
			playedFX  = oCVisualFX::CreateAndPlay(fxname, oCNpc::player, oCNpc::player->GetFocusVob());
			return TRUE;
		}
	}
	if (s.PickWord(1, " ") == "STOP")
	{
		if (s.PickWord(2, " ") == "FX")
		{
			if (playedFX) playedFX->Stop();
			zRELEASE(playedFX);
			return TRUE;
		}
	}
	else if (s.PickWord(1, " ") == "FIRSTPERSON")
	{
		if (zCAICamera::GetModeChangeEnabled())
		{
			zCAICamera::GetCurrent()->SetMode(CamModFirstPerson);
			zCAICamera::SetModeChangeEnabled(FALSE); 
		}
		else
		{
			zCAICamera::SetModeChangeEnabled(TRUE); 
		}
		return TRUE;
	}
	else
	if ( s.PickWord(1, " ") == "GOTO" ) 
	{
		if ( s.PickWord(2, " ") == "CAMERA" ) {
			if (zCCamera::activeCam && zCCamera::activeCam->GetVob())
			{
				if (ogame->GetSelfPlayerVob()) {
					zBOOL oldCollDyn = ogame->GetSelfPlayerVob()->GetCollDetDyn();
					zBOOL oldCollStat= ogame->GetSelfPlayerVob()->GetCollDetStat();
					ogame->GetSelfPlayerVob()->SetCollDet(FALSE);

					ogame->GetSelfPlayerVob()->SetPositionWorld(zCCamera::activeCam->GetVob()->GetPositionWorld()+zCCamera::activeCam->GetVob()->GetAtVectorWorld());

					ogame->GetSelfPlayerVob()->SetCollDetDyn (oldCollDyn );
					ogame->GetSelfPlayerVob()->SetCollDetStat(oldCollStat);
				}
				if (zCAICamera::GetCurrent()) zCAICamera::GetCurrent()->ReceiveMsg(zPLAYER_BEAMED);
			}
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "POS" ) {
			float x = s.PickWord(3, " ").ToFloat();
			float y = s.PickWord(4, " ").ToFloat();
			float z = s.PickWord(5, " ").ToFloat();

			zERR_MESSAGE(5,0,"C: beaming player to position X: " +zSTRING(x)+ " Y: " +zSTRING(y)+ " Z: " +zSTRING(z));

			if (zCCamera::activeCam && zCCamera::activeCam->GetVob())
			{
				if (ogame->GetSelfPlayerVob()) 
				{
					zBOOL oldCollDyn = ogame->GetSelfPlayerVob()->GetCollDetDyn();
					zBOOL oldCollStat= ogame->GetSelfPlayerVob()->GetCollDetStat();
					ogame->GetSelfPlayerVob()->SetCollDet(FALSE);

					ogame->GetSelfPlayerVob()->SetPositionWorld(zVEC3(x,y,z));

					ogame->GetSelfPlayerVob()->SetCollDetDyn (oldCollDyn );
					ogame->GetSelfPlayerVob()->SetCollDetStat(oldCollStat);

				}
				if (zCAICamera::GetCurrent()) zCAICamera::GetCurrent()->ReceiveMsg(zPLAYER_BEAMED);
			}
			return TRUE;
		}

	}
	else if ( s.PickWord(1, " ") == "REPARSE" ) 
	{
		// [BENDLIN] AddonMOD
		zSTRING parserfile;
		if (zgameoptions)
			parserfile = zgameoptions->ReadString(zOPT_SEC_FILES, "Game");
		else
			parserfile = zoptions->ReadString(zOPT_SEC_INTERNAL, "gameScript");
		if (parserfile.IsEmpty()) 
			parserfile = "Content\\Gothic";

		ogame->LoadParserFile(parserfile + ".src");
		return TRUE;
	}
	else if ( s.PickWord(1, " ") == "SPAWNMASS" ) 
	{
		int count;

		if ( s.PickWord(2, " ") == "GIGA" ) 
		{ 
			count =  s.PickWord(3, " ").ToInt();
			if (count == 0) count = 1;

			SpawnNpc(oCNpc::player, "DEMON"			, 2000, zRand(count)+1 );
			SpawnNpc(oCNpc::player, "TROLL"			, 2000, zRand(count)+1 );
			SpawnNpc(oCNpc::player, "ZOMBIE"		, 2000, zRand(count)+1 );
			SpawnNpc(oCNpc::player, "MINECRAWLER"	, 2000, zRand(count)+1 );
			SpawnNpc(oCNpc::player, "GOLEM"			, 2000, zRand(count)+1 );
			SpawnNpc(oCNpc::player, "ORC_WARRIOR"	, 2000, zRand(count)+1 );

		}
		count =  s.PickWord(2, " ").ToInt();
		if (count == 0) count = 1;

		SpawnNpc(oCNpc::player, "SKELETON", 2000, zRand(count)+1 );
		SpawnNpc(oCNpc::player, "WOLF"	  , 2000, zRand(count)+1 );
		SpawnNpc(oCNpc::player, "GOBBO"  ,2000,   zRand(count)+1 );
		SpawnNpc(oCNpc::player, "SNAPPER",2000,   zRand(count)+1 );
		SpawnNpc(oCNpc::player, "BLOODFLY",2000,  zRand(count)+1 );
		SpawnNpc(oCNpc::player, "MEATBUG",2000,  zRand(count)+2 );
		return TRUE;
	}

	else if ( s.PickWord(1, " ") == "DEBUG" ) 
	{
		if ( s.PickWord(2, " ") == "DAMAGE" )
		{
			int nValue = s.PickWord(3, " ").ToInt();

			if		( nValue == 0 ) { oCNpc::EnableDamageDebugOutput( FALSE );	return TRUE; }
			else if ( nValue == 1 ) { oCNpc::EnableDamageDebugOutput( TRUE  );	return TRUE; }
		}
	}

	return FALSE;
}

void oCarsten_PerFrame()
{
	if (freeLook)
#ifndef COMPILING_SPACER
	if (zrenderer->Vid_GetScreenMode() == zRND_SCRMODE_FULLSCREEN && !zCCSCamera::GetIsPlaying()) Freelook();
#else 
	if (!zCCSCamera::GetIsPlaying()) Freelook();
#endif

}



void oCarsten_StartUp()
{
	oCVisualFX::InitParser();
    zcon.Register	( "EDIT FX"	, "edits a special effect");
    zcon.AddEvalFunc( oCVisualFX::FxConsole_EvalFunc );

	zinput->BindKeys(1);
	zinput->BindKeys(0);

	zexhnd.AddUnhandledExceptionInfoCallback(ExceptionInfoCallback); 

	zcon.Register( "FIRSTPERSON"	, "EXPERIMENTAL FIRST PERSON CAMERA");
	zcon.Register( "GOTO CAMERA"	, "SETS THE PLAYER POSITION TO THE CAMERA POSITION");
	zcon.Register( "GOTO POS"	,	  "SETS THE PLAYER POSITION TO THE GIVEN POSITION (X,Y,Z)");
	zcon.Register( "SPAWNMASS"	,	  "spawns max [num] random monsters around the player");
	zcon.Register( "SPAWNMASS GIGA"	, "spawns max [num] random giga monsters around the player");
	zcon.Register( "DEBUG DAMAGE"	, "enables/disabled (0/1) damage debug output");
	zcon.Register( "REPARSE"		, "reparses game scripts, warning: you have to know what you are doing (you are probably not)");
	zcon.Register( "PLAY FX"		, "plays a special fx");
	zcon.Register( "STOP FX"		, "stops the previously played fx");

	zcon.AddEvalFunc( oCarsten_EvalFunc );

	s_bCheckRoutines = zoptions->Parm("CHECKROUTINES");

	oCNpcFocus::SetHighlightMeleeFocus	 (zoptions->ReadInt ("GAME", "highlightMeleeFocus", 0));
	oCNpcFocus::SetHighlightInteractFocus(zoptions->ReadBool("GAME", "highlightInteractFocus", FALSE));
	oCGame::SetUseSpeechReverbLevel		 (zoptions->ReadReal("GAME", "useSpeechReverbLevel",1));
	//oCGame::SetUseOnlineHelp			 (zoptions->ReadBool("GAME", "useOnlineHelp",		TRUE));
	oCGame::SetUsePotions				 (zoptions->ReadBool("GAME", "usePotionKeys",		FALSE));
	oCGame::SetUseQuickSave				 (zoptions->ReadBool("GAME", "useQuickSaveKeys",	FALSE));
	oCItem::SetInventoryZBiasScale		 (zoptions->ReadReal("ENGINE", "zInventoryItemsDistanceScale", 1.3f));
	oCItem::SetItemEffectsEnabled		 (zoptions->ReadBool("GAME", "itemEffects", TRUE));
	if (zrenderer) zrenderer->SetRadialFog(zoptions->ReadBool ("RENDERER_D3D", "zFogRadial", TRUE));
}


void oCarsten_ShutDown()
{
	oCVisualFX::ExitParser();
}

