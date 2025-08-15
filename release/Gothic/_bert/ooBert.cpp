/******************************************************************************** 
 
     $Workfile:: oobert.cpp           $                $Date:: 24.04.01 17:33   $
     $Revision:: 73                   $             $Modtime:: 17.04.01 18:38   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oobert.cpp $
 * 
 * 73    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 71    19.03.01 21:29 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 70    18.03.01 19:00 Edenfeld
 * Demo Geschichten
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 73 $ ($Modtime: 17.04.01 18:38 $)



#include "zcore.h"
#include "zconsole.h"
#include "zoption.h"
#include "znettypes.h"
#include "zccspool.h"
#include <z3d.h>
#include <zWorld.h>
#include "zsky.h"
#include "zinput.h"
#include "zdisk.h"

#include "oobert.h"
#include "ogame.h"
#include "oworld.h"
#include "ocsplayer.h"
#include "ocsmanager.h"
#include "onpc.h"
#include "onpcmessages.h"
#include "ogamemanager.h"

static zBOOL ConsoleEval (const zSTRING &s, zSTRING &msg) 
{
	zSTRING w1 = s.PickWord(1," ");
	zSTRING w2 = s.PickWord(2," ");
	zSTRING w3 = s.PickWord(3," ");
	zSTRING w4 = s.PickWord(4," ");
	
	msg = "ok";
	if (w1 == "SET") 
	{
		if (w2=="CLIPPINGFACTOR")
		{
			float factor = w3.ToFloat();
			if (factor<0.05f)	factor=0.05f;
			if (factor>10.0f)	factor=10.0f;
			if (ogame->GetWorld()->GetActiveSkyControler())
				ogame->GetWorld()->GetActiveSkyControler()->SetFarZScalability(factor);
		};
	} 
	else if (w1=="LIST")
	{	
		if (w2=="CS")
		{			
			ogame->GetWorld()->GetCutscenePlayer()->PrintListOfCutscenes(w3);
			msg="toggled cutscene-debuginfos";
			return TRUE;			
		};
	}	
	else if (w1=="HERO")
	{
		if (w2=="EXPORT" && oCNpc::player)
		{

			if (w3.IsEmpty()) w3="hero_export.zen";
			if (w3.Search(".zen")<0) w3+=".zen";
	
			zFILE_FILE file(zoptions->GetDirString(DIR_SAVEGAMES)+w3);
			if (file.Exists()) 
			{
				file.FileDelete();
			}

			if (file.Create()==zERR_NONE)
			{				
				zCArchiver* arc = zarcFactory.CreateArchiverWrite
						(
							&file,						
							zARC_MODE_ASCII,
							TRUE			
						);
				arc->WriteObject(oCNpc::player);
				arc->Close();

				msg = "Exported your hero to file \""+file.GetFullPath()+"\".";
				return TRUE;
			}
			else
			{
				msg = "\""+file.GetFullPath()+"\" could not be created.";
				return FALSE;
			}
		}
		else if (w2=="IMPORT" && oCNpc::player)
		{
			if (w3.IsEmpty()) w3="hero_export.zen";
			if (w3.Search(".zen")<0) w3+=".zen";

			zFILE_FILE file(zoptions->GetDirString(DIR_SAVEGAMES)+w3);
			if (file.Exists() && file.Open()==zERR_NONE)
			{				
				zCArchiver* arc = zarcFactory.CreateArchiverRead(&file);
				oCNpc* npc = dynamic_cast<oCNpc*>(arc->ReadObject());
				arc->Close();
				if (npc && ogame) 
				{
					zPOINT3 p = oCNpc::player->GetPositionWorld();
					zPOINT3	v = oCNpc::player->GetAtVectorWorld();
					oCNpc::player->RemoveVobFromWorld();
					npc->SetPositionWorld(p);
					npc->SetHeadingAtWorld(v);
					ogame->GetWorld()->AddVob(npc);					
					npc->SetAsPlayer();
					msg = "Imported your hero from file \""+file.GetFullPath()+"\".";
				}
				return TRUE;
			}
			else 
			{
				msg = "\""+file.GetFullPath()+"\" does not exist.";
				return TRUE;
			}
		}
		else return FALSE;
	}
	else if  (w1=="TOGGLE")
	{			
		if (w2=="CS")
		{
			if (w3=="LIST")
			{
				ogame->GetWorld()->GetCutscenePlayer()->ToggleDebugInfo();
				msg="toggled cutscene-debuginfos";					
				return TRUE;
			}					
		}		
		else if (w2=="CUTSCENES")
		{
			if (w3=="ENABLED")
			{
				zCCSCutsceneContext::DisablePlayCutscenes(!zCCSCutsceneContext::playDisabled);
				if (zCCSCutsceneContext::playDisabled)	
				{
					msg="Cutscene-System disabled ";
					ogame->GetWorld()->GetCutscenePlayer()->StopAllCutscenes();
				}
				else 
				{
					msg="Cutscene-System enabled";
				}
				return TRUE;
			};			
		}		
	}
	else if (w1=="SHOW")
	{
		if (w2=="CS")
		{	
			zERR_MESSAGE(1,zERR_BEGIN,"B: CS: Informations about cutscene \""+w3+"\"");

			int num = ogame->GetCutsceneManager()->PoolNumPlayed(w3);
			if (num<0)  // -1 means: has'nt been started
			{				
				zERR_MESSAGE(1,0,"B: CS: CSPool: It wasn't played yet.");
			}
			else
			{
				zERR_MESSAGE(1,0,"B: CS: CSPool: Has been started.");				
				zERR_MESSAGE(1,0,"B: CS: CSPool: Has been played "+zSTRING(num)+" times");				
			};

			zCCSCutsceneContext* cs = ogame->GetWorld()->GetCutscenePlayer()->GetStartedCutscene(w3);
			if (cs)
			{
				if (cs->IsPlaying()) zERR_MESSAGE(1,0,"B: CS: CSPlayer: Cutscenes is playing right now.");
				else zERR_MESSAGE(1,0,"B: CS: CSPlayer: Cutscenes is sleeping.");
			};

			zERR_MESSAGE(1,zERR_END,"");
			return TRUE;
		};
	}
	else if (w1=="PLAY")
	{
		if (w2=="CS")
		{
			zSTRING csName = w3;			
			oCNpc* npc = oCNpc::player;
			if (oCNpc::player->GetFocusNpc()) npc = oCNpc::player->GetFocusNpc();
			
			if (npc)
			{				
				npc		->GetEM()
						->OnMessage(new oCMsgConversation
										(
											oCMsgConversation::EV_CUTSCENE,
											csName,
											npc->GetVobName()
										)
										,
										npc
									);
				msg="Started playing cutscene for npc \""+npc->GetVobName()+"\"";
				return TRUE;
			}				
		}
		else if (w2=="VIDEO")
		{
			zSTRING filename = w3;			
			gameMan->PlayVideo(filename);
		};

	};

	return FALSE;
}

static void InitOptions()
{	
	zSTRING scriptName		= zoptions->Parm("PARSE")	? zoptions->ParmValue("PARSE")	: "";
	zSTRING worldName		= zoptions->Parm("3D")		? zoptions->ParmValue("3D")		: "";
	zSTRING playerInstance	= zoptions->Parm("PLAYER")	? zoptions->ParmValue("PLAYER")	: "";

	// [BENDLIN] AddonMOD
	if (!scriptName.IsEmpty())
	{
		zFILE* file = zfactory->CreateZFile(scriptName);
		if (file)
		{
			zSTRING scriptNameExt = file->GetExt(); scriptNameExt.Upper();
			if (!scriptNameExt.CompareTo("SRC"))
				scriptName.DeleteRight(4);

			if (!scriptName.IsEmpty())
			if (zgameoptions)
				zgameoptions->WriteString(zOPT_SEC_FILES, "Game", scriptName, TRUE);
			else
				zoptions->WriteString(zOPT_SEC_INTERNAL, "gameScript", scriptName, TRUE);

			file->Close(); delete file; file = 0;
		}
	}
	if (!worldName.IsEmpty())
	{
		if (zgameoptions)
			zgameoptions->WriteString(zOPT_SEC_SETTINGS, "World", worldName, TRUE);
		else
			zoptions->WriteString(zOPT_SEC_INTERNAL, "gamePath", worldName, TRUE);
	}
	if (!playerInstance.IsEmpty())
	{
		if (zgameoptions)
			zgameoptions->WriteString(zOPT_SEC_SETTINGS, "Player", playerInstance, TRUE);
		else
			zoptions->WriteString(zOPT_SEC_INTERNAL, "playerInstanceName", playerInstance, TRUE);
	}

#ifndef COMPILING_SPACER
	gLogStatistics = (int) zoptions->ReadBool(zOPT_SEC_INTERNAL, "logStatistics", FALSE);
#else
	gLogStatistics = FALSE;
#endif
};

void oBert_StartUp()
{		
	zcon.Register		("SET CLIPPINGFACTOR","Setting the clipping-factor. Default is 1. Usually check 0.1 ... 2.0");

	zcon.Register		("LIST CS"			, "List running cutscenes.");
	zcon.Register		("LIST CS STATES"	, "List running cutscenes including their current status.");
	zcon.Register		("LIST CS PROPS"	, "List running cutscenes including status and properties.");
	zcon.Register		("LIST CS HISTORY"	, "List all cutscenes in the history-pool.");
	
	zcon.Register		("SHOW CS"	, "Show information of a cutscene (add cutscene-name including extension)");

	zcon.Register		("PLAY CS"	, "Play a cutscene (add cutscene-name including extension)");	
	zcon.Register		("PLAY VIDEO"	, "Playing a videofile");

	zcon.Register		("TOGGLE CS LIST"	, "Toggle list of running cutscenes on screen");
	zcon.Register		("TOGGLE CUTSCENES ENABLED", "Enable or disable cutscene-system");			

	zcon.Register		("HERO EXPORT"	, "Exports your hero to the given file.");
	zcon.Register		("HERO IMPORT"  , "Imports your hero from the given file.");			

	zcon.AddEvalFunc(ConsoleEval);	
	InitOptions();


}

static int GetCode(const zSTRING& str)
{
	int code = 0;
	for (int i=0;i<str.Length();i++)
	{
		code = code + (i*11)*int(str[i]);
	};
	return code;
};


void oBert_ShutDown()
{				
}

void ShowMoreInfos(oCNpc* npc, oCNpc* other)
{
	if (!npc) return;

	zCView* view = zNEW( zCView(0,0,8192,8192) );
	screen->InsertItem(view);
	
	view->InsertBack("menu_ingame.tga");

		int dx = screen->anx(800);	// [BENDLIN] 800x600, old = 640
		int dy = screen->any(600);	// [BENDLIN] 800x600, old = 480

		view->SetPos((8192-dx)/2,(8192-dy)/2);
		view->SetSize(dx,dy);					
		view->DefPrintwin(1500,1500,6692,6692);
		view->ClrFlags(VIEW_TXT_CENTER);

		zSTRING s = "Statistics for ["+npc->GetName()+"]\n";
		s+="\n";
		s+="Guild: "+npc->GetGuildName()+"\n";
		s+="\n";
		s+="Hitpoints: "+zSTRING(npc->GetAttribute(NPC_ATR_HITPOINTS))+"/"+zSTRING(npc->GetAttribute(NPC_ATR_HITPOINTSMAX))+"\n";
		s+="Mana: "+zSTRING(npc->GetAttribute(NPC_ATR_MANA))+"/"+zSTRING(npc->GetAttribute(NPC_ATR_MANAMAX))+"\n";
		s+="\n";
		s+="Strength: "+zSTRING(npc->GetAttribute(NPC_ATR_STRENGTH))+"\n";
		s+="Dexterity: "+zSTRING(npc->GetAttribute(NPC_ATR_DEXTERITY))+"\n";
		s+="\n";
		if (other)
		{			
			zSTRING attitude;
			if (npc->IsNeutral(other))			attitude = "neutral";
			else if (npc->IsHostile(other))		attitude = "hostile";
			else if (npc->IsAngry(other))		attitude = "angry";
			else if (npc->IsFriendly(other))	attitude = "friendly";

			s+="Attitude to me: "+attitude+"\n";
		}					
		
		view->Printwin(s);

		view->Blit();
		zrenderer->Vid_Blit();

		zBOOL	finished=FALSE;
		while (!finished) 
		{			
			zinput->ProcessInputEvents();			
			finished = finished || zinput->KeyPressed(KEY_ESC);
			finished = finished || zinput->GetState(GAME_END)>0;
		}

	screen->RemoveItem(view);	

	delete view;view=0;
	
	zinput->ClearKeyBuffer();
	zinput->ResetRepeatKey();


};

//static zSTRING draculaAddString("");

// ----------------------------------------------------------------------
//	[EDENFELD] 17.04.01	
//
// ----------------------------------------------------------------------

void HandleResultString(zSTRING resultStr)
{	
	//
	// Ausfuehrung diverser Test	
	//

	zCView* view	= ::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN );
	oCNpc*	focus	=  dynamic_cast<oCNpc*>(oCNpc::player->GetFocusNpc());
	zSTRING focusName = focus?focus->GetName():"";
	
	resultStr.Upper();
	int code = GetCode(resultStr);	

// #ifdef DEBUG_SPECKELS
#if 1
	zERR_MESSAGE(3,0,"B: TEST: Result: "+resultStr+" ("+zSTRING(code)+")");		
#endif

	// Game-Figuren

	if (code==22374) // God-Mode (GUARDIAN)
	{
		oCNpc::godmode = !oCNpc::godmode;
		if (view)
			if (oCNpc::godmode)	
			{
				view->PrintTimed(100, 300,"GUARDIAN-MODE", 3000);

				view->PrintTimed(100, 600,"Ja, ich weiß, woher ich stamme!"	, 4500);
				view->PrintTimed(100, 800,"Ungesättigt gleich der Flamme"	, 5000);
				view->PrintTimed(100,1000,"glühe und verzehr' ich mich."	, 5500);

				view->PrintTimed(100,1400,"Licht wird alles, was ich fasse"	, 6000);
				view->PrintTimed(100,1600,"Kohle alles, was ich lasse, "	, 6500);
				view->PrintTimed(100,1900,"Flamme bin ich sicherlich!"		, 7000);
			}
			else	view->PrintTimed(100,300,"GUARDIAN-MODE off", 3000);
	}
	else if (code==4774) // Full (TAKI)
	{				
		oCNpc::player->SetAttribute(NPC_ATR_HITPOINTS,oCNpc::player->GetAttribute(NPC_ATR_HITPOINTSMAX));
		oCNpc::player->SetAttribute(NPC_ATR_MANA,oCNpc::player->GetAttribute(NPC_ATR_MANAMAX));
		if (view) view->PrintTimed(100,300,"TAKI makes you feal fine", 3000);		
	}
	else if (code==8360 || code==18425)	// Erz (HESSE|GARRETT)
		
	{		
		oCNpc::player->PutInInv("ITMI_NUGGET", 1);
		if (view) view->PrintTimed(100,300,"some more ore ...", 3000);
	}

	// [BENDLIN] Addon Patch2
	else if (code == 8448)	// Ornamentbruchstück von Vatras (LARES)
		
	{		
		if (ogame && ogame->GetWorld()) 
		{ 
			zCVob* vob = ogame->GetWorld()->SearchVobByName("VLK_449_LARES");
			if (vob)
			{
				oCNpc* Lares = dynamic_cast<oCNpc*>(vob);
				if (Lares && Lares->IsInInv	("ITMI_ORNAMENT_ADDON_VATRAS"))
				{ 
					Lares->RemoveFromInv	("ITMI_ORNAMENT_ADDON_VATRAS");
					oCNpc::player->PutInInv	("ITMI_ORNAMENT_ADDON_VATRAS");
					if (view)
						view->PrintTimed(100, 300,"Ornament von Lares erhalten", 5000);
				}
			}
		} 
	}
	
	// Film/Literatur-Figuren (Monster)

	else if (code==23122) // Shrink (KINGKONG)
	{
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		if (world)
		{
			oTVobListNpcs* npcList = world->GetVobListNpcs();
			int count = npcList->GetNumInList();
			for (int i=0;i<count;i++)
			{
				oCNpc* npc = static_cast<oCNpc*>(npcList->Get(i));				
				if (npc!=oCNpc::player) npc->GetModel()->SetModelScale(zVEC3(0.4f,0.4f,0.4f));		
			};
		};
		if (view) view->PrintTimed(100,300,"KINGKONG-POINT-OF-VIEW", 3000);		
	}	

	else if (code==22748) // Huge-ness (GODZILLA)
	{
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		if (world)
		{
			oTVobListNpcs* npcList = world->GetVobListNpcs();
			int count = npcList->GetNumInList();
			for (int i=0;i<count;i++)
			{
				oCNpc* npc = static_cast<oCNpc*>(npcList->Get(i));				
				if (npc!=oCNpc::player) npc->GetModel()->SetModelScale(zVEC3(5.0f,5.0f,5.0f));		
			};
		};
		if (view) view->PrintTimed(100,300,"GODZILLA MUTATION", 3000);
		if (view) view->PrintTimed(100,600,"Kampf der Saurier Mutanten!", 6000);
	}	

	else if (code==18128) // Flat NPC (GROMMIT)
	{
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		if (world)
		{
			oTVobListNpcs* npcList = world->GetVobListNpcs();
			int count = npcList->GetNumInList();
			for (int i=0;i<count;i++)
			{
				oCNpc* npc = static_cast<oCNpc*>(npcList->Get(i));				
				if (npc!=oCNpc::player) npc->GetModel()->SetModelScale(zVEC3(0.2f,1.3f,1.3f));		
			};
		};			
		if (view) view->PrintTimed(100,300,"GROMMIT-AFTER-CAR-ACCIDENT-MODE", 3000);		
	}	
	else if (code==12100) // Thin-ness (SHRIKE)
	{
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		if (world)
		{
			oTVobListNpcs* npcList = world->GetVobListNpcs();
			int count = npcList->GetNumInList();
			for (int i=0;i<count;i++)
			{
				oCNpc* npc = static_cast<oCNpc*>(npcList->Get(i));				
				if (npc!=oCNpc::player) npc->GetModel()->SetFatness(-6.0f);
			};
			if (view) 
			{	
				view->PrintTimed(100, 600,"Deep in the shady sadness ofa vale"	, 4500);
				view->PrintTimed(100, 800,"Far sunken from the healthy breath of morn,"	, 5000);
				view->PrintTimed(100,1000,"Far from the fiery noon, and eve s  one star,"	, 5500);
				view->PrintTimed(100,1200,"Sat gray-hair d  Saturn, quiet as a stone,"	, 6000);
				view->PrintTimed(100,1400,"Still as the silence round about his lair;"	, 6500);
				view->PrintTimed(100,1600,"Forest on forest hung above his head"	, 7000);
				view->PrintTimed(100,1800,"like cloud on cloud ..."		, 7500);
				view->PrintTimed(100,2000,"-John Keats-"		, 8000);
			}		

		};					
	}
	else if (code==22088) // Fatness (GARFIELD)
	{
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		if (world)
		{
			oTVobListNpcs* npcList = world->GetVobListNpcs();
			int count = npcList->GetNumInList();
			for (int i=0;i<count;i++)
			{
				oCNpc* npc = static_cast<oCNpc*>(npcList->Get(i));				
				if (npc!=oCNpc::player) npc->GetModel()->SetFatness(6.0f);
			};
		};					
		if (view) view->PrintTimed(100,300,"GARFIELD-MODE", 3000);		
	}			


	// Filme

	else if (code==30283) // Fast (SOUTHPARK)
	{ 
		::ztimer.SetMotionFactor( 3.0f );
		if (view) view->PrintTimed(100,300,"SOUTHPARK", 3000);
	}	
	else if (code==12925) // Slow (CLERKS)
	{ 
		::ztimer.SetMotionFactor( 0.4f );
		if (view) view->PrintTimed(100,300,"CLERKS", 3000);
	}	
	else if (code==9152) // Slow NPC (EOWYN)
	{ 
		if (focus)
		{			
			focus->GetModel()->SetTimeScale(0.4f);
			if (view) 
			{	
				view->PrintTimed(100, 600,"Kalt sei Hand, Herz und Gebein,"	, 4500);
				view->PrintTimed(100, 800,"Kalt der Schlaf unterm Stein:,"	, 5000);
				view->PrintTimed(100,1000,"Nimmer steh vom Bette auf,"	, 5500);
				view->PrintTimed(100,1200,"Eh nicht endet der Sonn und des Mondes Lauf,"	, 6000);
				view->PrintTimed(100,1400,"Die Sterne zersplittern im schwarzen Wind,"	, 6500);
				view->PrintTimed(100,1600,"Und fallen herab und liegen hier blind,"	, 7000);
				view->PrintTimed(100,1800,"Bis der dunkle Herrscher hebt seine Hand"		, 7500);
				view->PrintTimed(100,2000,"Über tote See und verdorrtes Land."		, 8000);
				view->PrintTimed(100,2000,"- J.R.R.Tolkien -"		, 8500);
			}		

		}
	}	
	else if (code==36234) // Fast NPC (HIGHLANDER)
	{ 
		if (focus)
		{			
			focus->GetModel()->SetTimeScale(3.0f);
			if (view) view->PrintTimed(100,300,"HIGHLANDER", 3000);
		}
	}	

	// Autoren von Klassikern

	else if (code==22990) // Rain (MELVILLE = MOBY DICK)
	{
		zCSkyControler_Outdoor *skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(ogame->GetWorld()->GetActiveSkyControler());
		if (skyCtrl) skyCtrl->SetRainFXWeight(0, 0.1F);			
		if (view) view->PrintTimed(100,300,"MOBY DICKS ELEMENT", 3000);
	}
	else if (code==8173) // Next Npc (VERNE)
	{
		if (ogame) 
		{
			ogame->SwitchCamToNextNpc();
			if (view) view->PrintTimed(100,300,"FROM EARTH TO NEXT NPC", 3000);
		}
	}
	else if (code==7942) // Takeover (DEFOE)
	{
		if (focus) 
		{
			focus->SetAsPlayer();
			if (view) view->PrintTimed(100,300,"YOU ARE NOW "+focusName, 3000);
		}
	}
	
	// Hhgttg

	else if	(code==550)	// Reset to default (42)
	{ 				
		::ztimer.SetMotionFactor	( 1.0f );
		oCNpc::player->GetModel()->SetTimeScale(1.0f);

		oCNpc::player->SetAsPlayer();
		
		if (zrenderer)		zrenderer->SetPolyDrawMode	(zRND_DRAW_MATERIAL);			
		Game_ToggleTestMode(FALSE);
		oCNpc::godmode = FALSE;

		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		if (world)
		{
			oTVobListNpcs* npcList = world->GetVobListNpcs();
			int count = npcList->GetNumInList();
			for (int i=0;i<count;i++)
			{
				oCNpc* npc = static_cast<oCNpc*>(npcList->Get(i));				
				npc->GetModel()->SetFatness(1.0f);
				npc->GetModel()->SetModelScale(zVEC3(1.0f,1.0f,1.0f));		
			};
		};					
		if (view) view->PrintTimed(100,300,"WHAT WAS THE QUESTION?", 3000);

		//
		ogame->SetShowFramerate		(FALSE);
		ogame->SetShowTime			(FALSE);
	}
		
	else if (code==12859) // Testmode (MARVIN)
	{
		Game_ToggleTestMode(TRUE);
		if (view) view->PrintTimed(100,300,"MARVIN-MODE", 3000);
	}

	// Cocktails

	else if (code==36278) // Flat (CAIPIRINHA)
	{ 
		zrenderer->SetPolyDrawMode (zRND_DRAW_FLAT);
		if (view) view->PrintTimed(100,300,"CAIPI-Mode", 3000);
	}
	else if (code==11968) // Wire (MAITAI)
	{ 
		zrenderer->SetPolyDrawMode (zRND_DRAW_WIRE); 
		if (view) view->PrintTimed(100,300,"MAITAI-Mode", 3000);}	

	// Sonstiges

	else if (code==71852) // Mud beschwören: THEQUEENISDEAD
	{ 
		if (!oCNpc::player->IsInInv("ITSC_SUMMONMUD"))
		{ 
			oCNpc::player->PutInInv("ITSC_SUMMONMUD");
			if (view) view->PrintTimed(10,300,"THE QUEEN IS DEAD", 3000); 
		} 
	}	

	else if (code==8085) // Clock (CLOCK)
	{
		zBOOL clockVisible = !::ogame->GetShowTime();
		::ogame->SetShowTime( clockVisible );
		if (view) 
		{
			if (clockVisible)	view->PrintTimed(10,300,"CLOCK TICK TOCK", 3000); 
			else				view->PrintTimed(10,300,"CLOCK OFF", 3000); 
		}
	}
	else if (code==22803) // Show RealPlayTimer (REALTIME)
	{
		gameMan->ShowRealPlayTime();
	}
	else if (code==2838) // More Infos (SPY)
	{
		ShowMoreInfos(focus, oCNpc::player);
	} 
	else if (code==8140) // Show Framerate/triangle Ctr (FRATE)
	{
		ogame->SetShowFramerate	(!ogame->GetShowFramerate());
	};
};

//
// Statistics-Logfile (Patch 2)
//

static zCArray<zSTRING> logEntries;

zBOOL gLogStatistics = FALSE;

void ClearLogStatistics()
{
	logEntries.EmptyList();	
	zERR_MESSAGE(5,0,"B: LogStatistics: Cleared.");
}

bool LogStatistics(oCNpc* player)
{
	static int lastHour=0;
	
	if (!ogame)  return false;
	if (!player) return false;			// [EDENFELD] Crash im Spacer 1.33 behoben. player konnte NULL sein

	int day,hour,min;
	ogame->GetTime(day,hour,min);	

	if (lastHour==hour) return false;

	zREAL minutes = (zREAL) ((day*24+hour)*60+min - 480);  // 480 = 8 Uhr morgens
	lastHour = hour;

	zSTRING s;
	
	// gespielte Zeit in Minuten
	s+= zSTRING( minutes ); 
	s+="\t";
	
	// Spielzeit
	s += zSTRING( day	); 
	s+="\t";
	s+= zSTRING( hour	);
	s+="\t";
	s+= zSTRING( min	);	
	s+="\t";

	// Level
	s+= zSTRING(player->GetLevel());
	s+="\t";
	s+= zSTRING(player->experience_points);
	s+="\t";
	s+= zSTRING(player->learn_points);
	s+="\t";	

	// Gilde
	s+= zSTRING(player->GetGuildName());
	s+="\t";
	
	// Attribute
	s+= zSTRING(player->GetAttribute(NPC_ATR_STRENGTH));
	s+="\t";
	s+= zSTRING(player->GetAttribute(NPC_ATR_DEXTERITY));
	s+="\t";	
	s+= zSTRING(player->GetAttribute(NPC_ATR_HITPOINTSMAX));
	s+="\t";
	s+= zSTRING(player->GetAttribute(NPC_ATR_MANAMAX));
	s+="\t";	
	// Talente
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_1H));
	s+="\t";
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_2H));
	s+="\t";
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_BOW));
	s+="\t";
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_CROSSBOW));
	s+="\t";
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_MAGE));
	s+="\t";
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_PICKLOCK));
	s+="\t";
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_PICKPOCKET));
	s+="\t";	
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_SNEAK));
	s+="\t";
	s+= zSTRING(player->GetTalentSkill(oCNpcTalent::NPC_TAL_ACROBAT));
	s+="\t";
	
	logEntries.InsertEnd(s+"\n");
	zERR_MESSAGE(5,0,"B: LogStatistics: New Entry ("+zSTRING(minutes)+" minutes)");

	return false;
}

bool LogStatisticsWrite(const zSTRING& path)
{
	zFILE_FILE file(path+"log.sav");
	if (file.Create()==zERR_NONE)
	{
		zSTRING header="minutes\tday\thour\tminute\tlevel\texperience\tlearnpoints\tguild\tstrength\tdexterity\tmax.hitpoints\tmax.mana\t1handed\t2handed\tbow\tcrossbow\tcircle\tpicklock\tpickpocket\tsneak\tacrobatic\t\n";
		file.Write(header);
		
		zSTRING line;
		for (int i=0;i<logEntries.GetNumInList();i++)
		{			
			file.Write(logEntries[i]);
		};
		file.Close();
		return true;
	};
	return false;
}

bool LogStatisticsRead(const zSTRING& path)
{
	zFILE_FILE file(path+"log.sav");
	ClearLogStatistics();
	if (file.Open()==zERR_NONE)
	{
		zSTRING line;
		file.Read(line); // header
		while (!file.Eof())
		{
			file.Read(line);
			if (!line.IsEmpty()) logEntries.InsertEnd(line+"\n");
		};
		file.Close();
		return true;
	};
	return false;
}
