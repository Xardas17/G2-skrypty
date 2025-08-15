/******************************************************************************** 
 
     $Workfile:: Zzbert.cpp           $                $Date:: 15.03.01 14:00   $
     $Revision:: 39                   $             $Modtime:: 14.03.01 20:12   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/Zzbert.cpp $
 * 
 * 39    15.03.01 14:00 Speckels
 * 
 * 38    14.03.01 20:04 Speckels
 * 
 * 37    13.03.01 18:57 Speckels
 * 
 * 36    12.03.01 20:17 Speckels
 * 
 * 35    1.02.01 19:40 Speckels
 * 
 * 34    28.01.01 19:08 Speckels
 * 
 * 33    28.01.01 18:47 Speckels
 * 
 * 32    26.01.01 16:13 Speckels
 * 
 * 31    21.11.00 17:35 Speckels
 * 
 * 30    20.11.00 15:17 Keskenti
 * 
 * 29    20.11.00 15:14 Keskenti
 * 
 * 28    14.11.00 20:56 Speckels
 * 
 * 27    7.11.00 17:47 Speckels
 * 
 * 26    20.10.00 21:15 Speckels
 * 
 * 25    20.10.00 20:57 Speckels
 * 
 * 24    7.10.00 19:51 Speckels
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 39 $ ($Modtime: 14.03.01 20:12 $)

#include "zcore.h"
#include <zzbert.h>
#include <new.h>
#include "zoption.h"
#include "zwin32.h"
#include "zconsole.h"
#include "zvob.h"
#include "zscandir.h"
#include "zccsplayer.h"
#include <direct.h>
#ifdef _VDFS
#include "zdisk_vdfs.h"
#endif

zERROR zerr;

void zInitOptions()
{
	///
	// Options-Instanz erzeugen
	///	

	if (zoptions)
		return;
	zoptions = zNEW(zCOption);
	zoptions ->Init(sysCommandLine);	

	//
	// INI-Datei bestimmen und laden
	//

	zoptions ->ChangeDir(DIR_SYSTEM);	
	zSTRING inivalue = zoptions->ParmValue("ini");
	if  (inivalue.IsEmpty())
		inivalue = "Gothic.ini";
	zoptions->Load(inivalue);
	
	// [BENDLIN] 1.30 INI-Patch weiter vorverlegt
	int patchversion = zoptions->ReadInt(zOPT_SEC_GAME, "PATCHVERSION", 0);
	if (patchversion < 0)
		patchversion = 0;
	switch (patchversion)
	{
	case 0:
		// Joystick/Gamepad deaktivieren
		zoptions->WriteBool(zOPT_SEC_GAME, "enableJoystick", FALSE);
		
	patchversion++;
	case 1:
		// Tastenkürzel (F1-F4) für Sichtweite
		zoptions->WriteReal(zOPT_SEC_GAME, "SHORTKEY1FARPLANEDIST", 0.8f);
		zoptions->WriteReal(zOPT_SEC_GAME, "SHORTKEY2FARPLANEDIST", 1.2f);
		zoptions->WriteReal(zOPT_SEC_GAME, "SHORTKEY3FARPLANEDIST", 2.0f);
		zoptions->WriteReal(zOPT_SEC_GAME, "SHORTKEY4FARPLANEDIST", 3.0f);
		// Auswirkungen des Radeon-Hack aus (nur noch 9700/9000/9500)
		zoptions->WriteBool("RENDERER_D3D", "zSyncAmbientCol", FALSE);
		// LogStatistics aus (veraltet)
		zoptions->WriteBool(zOPT_SEC_INTERNAL, "logStatistics", FALSE);
		// Erweitertes Menü deaktiviert
		zoptions->WriteBool(zOPT_SEC_INTERNAL, "extendedMenu", FALSE);
		// "gameAbnormalExit" wurde vorher nicht korrekt gesetzt (war immer true)!
		zoptions->WriteBool(zOPT_SEC_INTERNAL, "gameAbnormalExit", FALSE);
		// Abgeschnittene Items verhindern
		zoptions->WriteReal("ENGINE", "zInventoryItemsDistanceScale", 1.3f);

	patchversion++;
	case 2:
		// Radeon-Hack aus (neue ATI-Treiber installieren)
		zoptions->WriteBool("RENDERER_D3D", "radeonHackAmbientColBug", FALSE);

	patchversion++;
	case 3:
		// gameScript stand auf "gothic.dat" (deswegen ging -zreparse nicht ohne -parse)
		zoptions->WriteString(zOPT_SEC_INTERNAL, "gameScript", "");
		zoptions->WriteString(zOPT_SEC_INTERNAL, "playerInstanceName", "");
		// Alte Hacks aus (neuere Treiber)
//		zoptions->WriteBool("RENDERER_D3D",	"geforce3HackWBufferBug", FALSE);
//		zoptions->WriteBool("ENGINE",		"zSkyRenderFirst", FALSE);

	patchversion++;
	case 4:
		// Reaktiviert (Detonator FX 45.23)
		zoptions->WriteBool("RENDERER_D3D",	"geforce3HackWBufferBug",	TRUE);
		zoptions->WriteBool("ENGINE",		"zSkyRenderFirst",			TRUE);

	patchversion++;
//	case 5:
//
		break;
	}
	zoptions->WriteInt("GAME", "PATCHVERSION", patchversion);

	if (zoptions->ReadBool(zOPT_SEC_INTERNAL, "gameStartFailed", FALSE))
	{
		zERR_WARNING("B: GOTHIC: Start of gothic failed before.");
	};

#ifndef COMPILING_SPACER
	if (zoptions->ReadBool(zOPT_SEC_INTERNAL, "gameAbnormalExit", FALSE))
	{
		zERR_WARNING("B: GOTHIC: Abnormal exit of gothic detected.");
		// TODO: da hier daten zerschossen sein könnten (savegames, dmp datei etc.)
		// werden hier die default Werte wieder hergestellt
		// diese sollte allerdings nicht hier direkt gelöscht werden, sondern
		// erst beim nächsten gamestart, noch vor zCEngine::Init()
		// besser wäre dann hier ein universaler auto

#ifdef _VDFS
		// [BENDLIN] 1.30 - VDFS nach crash neu initialisieren
		// Ist hier OK, da zInitOptions() in zCEngine::Init()
		// noch vor der Initialisierung des Dateisystems erfolgt
		zERR_WARNING("N: Force Initializing VDFS after Crash.");
		if (zoptions->Parm("DEVMODE"))
			zERR_WARNING("N: Forced Initialization of VDFS canceled (-devmode)");
		else
		{
			TCHAR Filename[MAX_PATH] = { 0 };
			GetModuleFileName(NULL, Filename, MAX_PATH);
			LPTSTR Filebase = &Filename[lstrlen(Filename)-1];
			while ((Filebase >= Filename) && (Filebase[0] != '\\') && (Filebase[0] != '/'))
			{
				Filebase[0] = '\0';
				Filebase--;
			}
			if (Filebase > Filename)
			{
				Filebase[0] = '\0';
				Filebase--;
				while ((Filebase >= Filename) && (Filebase[0] != '\\') && (Filebase[0] != '/'))
				{
					Filebase[0] = '\0';
					Filebase--;
				}
				lstrcat(Filename, TEXT("VDFS.DMP"));

				DeleteFile(Filename);
			}
		}
#endif	// _VDFS
	}
	// Beim Beenden muss zDeinitOptions aufgerufen werden, sonst "abnormalExit"
	zoptions->WriteBool(zOPT_SEC_INTERNAL,"gameAbnormalExit",TRUE);
#endif	// !COMPILING_SPACER
	
	// Bis das Menue erscheint, gild der Start als nicht erfolgreich
	zoptions->WriteBool(zOPT_SEC_INTERNAL,"gameStartFailed",TRUE);

	//
	// Game-Counter
	//
	int count = zoptions->ReadInt(zOPT_SEC_INTERNAL,"gameStarts",0);
	zoptions->WriteInt(zOPT_SEC_INTERNAL,"gameStarts",(count+1) );


	//
	// Removing some (old) entries
	//
	zoptions->RemoveEntry(zOPT_SEC_INTERNAL,	"testmode");
	zoptions->RemoveEntry(zOPT_SEC_GAME,		"weatherEffects");
	zoptions->RemoveEntry(zOPT_SEC_INTERNAL,	"zFastUnsafeSaveGames");

	zoptions->Save(inivalue);

	// [BENDLIN] AddonMOD
	zSTRING gamevalue = zoptions->ParmValue("GAME");
	if (!gamevalue.IsEmpty())
	{
		zoptions ->ChangeDir(DIR_SYSTEM);
		zSTRING	gamefilename = gamevalue;
		zFILE* gamefile = zfactory->CreateZFile(gamefilename);
		if (!gamefile || !gamefile->Exists())
		{
			if (gamefile)
			{
				gamefile->Close();
				delete gamefile; gamefile = 0;
			}
			gamefilename += ".ini";
			gamefile = zfactory->CreateZFile(gamefilename);
		}
		if (gamefile)
		{
			if (gamefile->Exists())
			{
				zgameoptions = zNEW(zCOption);
				zgameoptions->Init("", FALSE);
				zgameoptions->Load(gamefilename);
				zSTRING gameparm = zgameoptions->ReadString(zOPT_SEC_OPTIONS, "force_Parameters");
				if (!gameparm.IsEmpty())
					zoptions->AddParameters(gameparm);
			}
			gamefile->Close();
			delete gamefile; gamefile = 0;
		}
	}
	// [BENDLIN] AddonMOD
	if (zoptions->Parm("VDFS") && !zoptions->ParmValue("VDFS").CompareTo("PHYSICALFIRST"))
	{
#ifdef _VDFS
		zFILE_VDFS::s_physical_first = true;
#endif
	};

	//
	// einige Commandozeilen-Parameter beruecksichtigen
	// in options-Datenbank schreiben: temporaer
	//

	zBOOL reset = TRUE;
	reset = zoptions->ReadBool(zOPT_SEC_PERFORMANCE,"recalc",TRUE);	
	
};

void zDeinitOptions()
{	
	///
	// INI-Datei bestimmen, speichern und Options-Instanz freigeben
	///

	// Beim Beenden von Gothic muss dieser Code ausgefuehrt werden, ansonsten "abnormalExit"
	if (zoptions)
	{
#ifndef COMPILING_SPACER
		zoptions->WriteBool(zOPT_SEC_INTERNAL, "gameAbnormalExit", FALSE);
#endif
		zoptions->ChangeDir(DIR_SYSTEM);
		zSTRING inivalue = zoptions->ParmValue("ini");
		if  (inivalue.IsEmpty())
			inivalue = "Gothic.ini";
		zoptions->Save(inivalue);
			
		delete zoptions; zoptions = 0;

		// [BENDLIN] AddonMOD
		if (zgameoptions)
		{
			delete zgameoptions; zgameoptions = 0;
		}
	}
};


////////////////////////////////////////////////////////////////////////////
//
// Example for a filecheck-callback
// Handles file of type .tga and .pcx
//
////////////////////////////////////////////////////////////////////////////

static zBOOL ConsoleEval (const zSTRING &s, zSTRING &msg) 
{	
	zSTRING w1 = s.PickWord(1," ");
	zSTRING w2 = s.PickWord(2," ");
	zSTRING w3 = s.PickWord(3," ");
	zSTRING w4 = s.PickWord(4," ");	
	if (w1=="ZERR")
	{
		if (w2=="AUTHORS")
		{
			zerr.SearchForSpy();
			zerr.SetFilterAuthors(w3);
			msg="logged authors are now: "+zerr.GetFilterAuthors();
			return TRUE;
		}
		else if (w2=="LEVEL")
		{
			zerr.SearchForSpy();
			zerr.SetFilterLevel(w3.ToInt());
			msg="max.level is now: "+zSTRING(zerr.GetFilterLevel());
			return TRUE;
		}
		else if (w2=="SEARCHSPY")
		{
			if (zerr.SearchForSpy()) msg="spy found"; else msg="spy not found";
			return TRUE;
		}
		else if (w2=="STATUS")
		{
			msg="max.level: "+zSTRING(zerr.GetFilterLevel());
			msg+="  (authors: "+zerr.GetFilterAuthors()+")\n";			
			msg+="flags: "+zerr.GetFilterFlagDescription()+"\n";
			msg+="targets: "+zerr.GetTargetDescription()+"\n";
			return TRUE;
		}
		else if (w2=="REM")
		{
			zerr.Separator();
			zERR_MESSAGE(5, 0, " Remark: "+w3);
			zerr.Separator();
			msg="added remark \""+w3+"\"";
			return TRUE;
		}
	}	
	
	return FALSE;
};

#include "zbuffer.h"

zBOOL BS_GPLUS = FALSE;

void zBert_StartUp()
{		
	zoptions->ChangeDir(DIR_SYSTEM);

	/*
	zerr.Separator();
	zERR_MESSAGE(1,0,"B: SearchFileTest");

	zSTRING filename="default_not_found.wav";
	zFILE* file = zfactory->CreateZFile("");
	for (int i=0;i<100;i++)
	{		
		zERROR_ID error = file->SearchFile(filename,zoptions->GetDirString(DIR_SOUND));		
	};
	delete file;file=0;

	zERR_MESSAGE(1,0,"B: SearchFileTest Finished");
	zerr.Separator();	
	*/

	_control87(_CW_DEFAULT,0xffff);

	///
	// Consolen-Kommandos registrieren
	/// 

	zcon.Register		("ZERR AUTHORS"		, "Set the author-filter for messages (as characters A-Z)");
	zcon.Register		("ZERR SEARCHSPY"	, "Search for existing zSpy if started later than game.");
	zcon.Register		("ZERR LEVEL"		, "Set the maximum priority-level for messages (from -1 to 10)");	
	zcon.Register		("ZERR STATUS"		, "Show error-status (current level, target ...)");
	zcon.Register		("ZERR REM"			, "Include a remark into the error-log.");
	zcon.Register		("ZERR ZVIEW"		, "just for internal tests");
	
	zcon.AddEvalFunc	(ConsoleEval);			
}

void zBert_ShutDown()
{				
	
}



