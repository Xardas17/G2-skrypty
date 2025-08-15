#include <windows.h>

#include "zcore.h"
#include "zlocal.h"
#include "zzCarsten.h"
#include "zrenderer.h"
#include "zsound.h"
#include "zoption.h"
#include "zoption_const.h"
#include "zinput_win32.h"
#include "zview.h"
#include "zExceptionHandler.h"
#include "zCSCamera.h"
#include "zConsole.h"
#include "zworld.h"
#include "zmenu.h"
#include "zparser.h"
#include "zFFT.h"
#include "zParticle.h"
#include "zAIPlayer.h"


zBOOL zOpt_Sound_ChangeFXVol(zCOptionValue &newValue)
{
	zREAL volume = newValue.GetValueFloat();
	zClamp(volume, 0.0f, 1.0f);
	zsound->SetMasterVolume(volume);
	return TRUE;
};

zBOOL zOpt_Sound_ChangeMusicVol(zCOptionValue &newValue)
{
	zREAL volume = newValue.GetValueFloat();
	zClamp(volume, 0.0f, 1.0f);
	zmusic->SetVolume(volume);
	return TRUE;
};

/*	------------------------------------------------------------------
	zBOOL zOpt_Video_ChangeVidOptions(zCOptionValue &newValue)
	29.01.00	[HILDEBRANDT]	
				Umrechnung der Werte auf guenstige Bereiche entfernt und 
				in den Renderer verlegt.
	------------------------------------------------------------------ */

zBOOL zOpt_Video_ChangeVidOptions(zCOptionValue &newValue)
{
	float vidBrightness	= zoptions->ReadReal(zOPT_SEC_VIDEO,"zVidBrightness",0.5f);
	float vidContrast	= zoptions->ReadReal(zOPT_SEC_VIDEO,"zVidContrast"	,0.5f);
	float vidGamma		= zoptions->ReadReal(zOPT_SEC_VIDEO,"zVidGamma"		,0.5f);

	zClamp(vidBrightness,	0.0f,1.0f);
	zClamp(vidContrast,		0.0f,1.0f);
	zClamp(vidGamma,		0.0f,1.0f);
	zrenderer->Vid_SetGammaCorrection(vidGamma, vidContrast, vidBrightness);

	return TRUE;
};

/*
zBOOL zOpt_Video_ChangeResolution(zCOptionValue &newValue)
{
	int x	   = newValue.GetString().PickWord(1,"x","x").ToInt();
	int y	   = newValue.GetString().PickWord(2,"x","x").ToInt();
	int bpp	   = newValue.GetString().PickWord(3,"x","x").ToInt();
	
	zTRnd_VidModeInfo modeInfo;
	zrenderer->Vid_GetModeInfo(modeInfo,zrenderer->Vid_GetActiveModeNr());

	// nur Modus wechseln, falls anderer als aktueller gewählt
	if ( x!=modeInfo.xdim || y!=modeInfo.ydim || bpp!=modeInfo.bpp ) 
	{
		//zCView::SetMode(x,y,bpp);
	}

	return TRUE;
};
*/

zBOOL zOpt_ToggleJoy(zCOptionValue &newValue)
{
//	zinput->SetJoyEnabled(newValue.GetValueInt());
	return TRUE;
};




static zBOOL TestChangeFunc(zCOptionValue &newValue) {
	zerr.Message(zSTRING("C: Option ") + zSTRING(newValue.GetName()) + zSTRING(" changed ") );
	return TRUE;
}
static zBOOL LanguageChangedTest( zCOptionValue &v )
{
	zerr.Message("C: Options: Language set to" + v.GetValueString() );
	return FALSE;
};

static zBOOL zCarsten_EvalFunc(const zSTRING &in, zSTRING &msg)
{
	zSTRING s = in;
	s.Upper();
	if ( s.PickWord(1, " ") == "ZTOGGLE" ) 
	{
		if ( s.PickWord(2, " ") == "RENDERORDER" ) 
		{
			zCWorld::S_SetAlternateRenderOrder(!zCWorld::S_GetAlternateRenderOrder());
			if (zCWorld::S_GetAlternateRenderOrder()) msg = "alternate on";
			else									  msg = "alternate off";
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "ENVMAP" ) 
		{
			zCWorld::S_SetEnvMappingEnabled(!zCWorld::S_GetEnvMappingEnabled());
			if (zCWorld::S_GetEnvMappingEnabled())    msg = "env on";
			else									  msg = "env off";
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "AMBIENTVOBS" ) 
		{
			zCWorld::S_SetAmbientVobsEnabled(!zCWorld::S_GetAmbientVobsEnabled());
			if (zCWorld::S_GetAmbientVobsEnabled())    msg = "ambient vobs on";
			else									   msg = "ambient vobs off";
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "AMBIENTPFX" ) 
		{
			zCParticleFX::S_SetAmbientPFXEnabled(!zCParticleFX::S_GetAmbientPFXEnabled());
			if (zCParticleFX::S_GetAmbientPFXEnabled())    msg = "ambient pfx on";
			else										   msg = "ambient pfx off";
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "RENDERPORTALS" ) 
		{
			zCBspTree::S_SetRenderAllPortals(!zCBspTree::S_GetRenderAllPortals());
			if (zCBspTree::S_GetRenderAllPortals())		   msg = "render all portals on";
			else										   msg = "render all portals off";
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "FLUSHONAMBIENTCOL" ) 
		{
			zrenderer->SetSyncOnAmbientCol(!zrenderer->GetSyncOnAmbientCol());
			if (zrenderer->GetSyncOnAmbientCol())		   msg = "sync on";
			else										   msg = "sync off";
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "SHOWSPLINES" ) {
			zCCSCamera::SetDrawEnabled(!zCCSCamera::GetDrawEnabled());
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "TIMEDEMO" ) {
			int demoNum = s.PickWord(3, " ").ToInt();
			zSTRING cscamName = zSTRING("TIMEDEMO_");
			if (demoNum > 0) cscamName += zSTRING(demoNum);
			else cscamName += zSTRING("1");

			zCCSCamera::SetEvaluateAvgFPS(!zCCSCamera::GetEvaluateAvgFPS());
			if (zCCSCamera::GetEvaluateAvgFPS())
			{
				zCArray<zCVob*> cscamList;
				if ( zCCamera::activeCam && zCCamera::activeCam->GetVob() )	{
					zCCamera::activeCam->GetVob()->GetHomeWorld()->SearchVobListByClass(zCCSCamera::GetStaticClassDef(),cscamList);
				}
				
				zCCSCamera *cscam = 0;
				for (int i=0; i<cscamList.GetNumInList();i++) 
				{
					if (cscamList[i]->GetObjectName() == cscamName) 
					{
						cscam = static_cast<zCCSCamera*>(cscamList[i]);
						break;
					}
					else if (cscamList[i]->GetObjectName() == "TIMEDEMO") cscam = static_cast<zCCSCamera*>(cscamList[i]);
				}

				if (cscam) 
				{
					cscam->OnTrigger(cscam,cscam);
					msg = "timedemo camera triggered";
				}
				else msg = "no timedemo camera found";
				
			}
			return TRUE;
		}
	}
	else if (s.PickWord(1, " ") == "ZSET" )
	{
		if ( s.PickWord(2, " ") == "NEARCLIPZ" )
		{
			zVALUE nz = s.PickWord(3, " ").ToFloat();
			if (zCCamera::activeCam) zCCamera::activeCam->SetNearClipZ(nz);
			msg = "set new znear value";
			return TRUE;
		};
	}
	else if ( s.PickWord(1, " ") == "FORCECRASH" ) 
	{
		void *ptr = 0;
		*(int*) ptr =0;
	}
	return FALSE;
}

void zCarsten_StartUp(zTSystemContextHandle* mainWindowContextHandle)
{	
	zoptions->InsertChangeHandler(zOPT_SEC_SOUND,ZOPT_SND_SFX_VOL.ToChar()		,zOpt_Sound_ChangeFXVol);
	zoptions->InsertChangeHandler(zOPT_SEC_SOUND,ZOPT_SND_MUSIC_VOL.ToChar()	,zOpt_Sound_ChangeMusicVol);	
	zoptions->InsertChangeHandler(zOPT_SEC_VIDEO,"zVidBrightness"	,	zOpt_Video_ChangeVidOptions);	
	zoptions->InsertChangeHandler(zOPT_SEC_VIDEO,"zVidContrast"		,	zOpt_Video_ChangeVidOptions);	
	zoptions->InsertChangeHandler(zOPT_SEC_VIDEO,"zVidGamma"			,	zOpt_Video_ChangeVidOptions);	
	//zoptions->InsertChangeHandler(zOPT_SEC_KEYS ,ZOPT_JOY_ENABLE.ToChar()		,zOpt_ToggleJoy);

	float f;
	f = zoptions->ReadReal(zOPT_SEC_SOUND,ZOPT_SND_SFX_VOL,1);
	zoptions->WriteReal(zOPT_SEC_SOUND,ZOPT_SND_SFX_VOL,f);		// Force calling of changed callback with possible default parameter

	f = zoptions->ReadReal(zOPT_SEC_SOUND, ZOPT_SND_MUSIC_VOL, 0.8f);
	zoptions->WriteReal(zOPT_SEC_SOUND,ZOPT_SND_MUSIC_VOL,f);

	delete zinput;
	zinput = zNEW (zCInput_Win32(mainWindowContextHandle) );

//	int i;
//	i = zoptions->ReadInt(zOPT_SEC_KEYS,ZOPT_JOY_ENABLE,FALSE);
//	zoptions->WriteInt(zOPT_SEC_KEYS,ZOPT_JOY_ENABLE,i);

//	if (zoptions->Parm("ZNOJOY")) zinput->SetJoyEnabled(FALSE);

#ifdef COMPILING_SPACER
	if (sysHandleExceptions()) zexhnd.SetIsActive(TRUE);
#endif

	zcon.Register( "ZTOGGLE SHOWSPLINES"	, "Toggles camera splines ");
	zcon.Register( "ZTOGGLE TIMEDEMO"		, "Toggles a time demo with avg FPS Rate");
	zcon.Register( "ZTOGGLE RENDERORDER"	, "Renders Sky last (possible better z buffer performance)");
	zcon.Register( "ZTOGGLE ENVMAP"			, "Toggled rendering of environmental fx");
	zcon.Register( "ZTOGGLE AMBIENTVOBS"	, "Toggles rendering of ambient vobs");
	zcon.Register( "ZTOGGLE AMBIENTPFX"		, "Toggles rendering of ambient pfx");
	zcon.Register( "ZTOGGLE RENDERPORTALS"	, "Toggles rendering of all portals (spacer only)");
	zcon.Register( "ZSET NEARCLIPZ"	,		  "sets the value for the near clipping plane");
	zcon.Register( "ZTOGGLE FLUSHONAMBIENTCOL"	,"toggles flushing the renderer on a ambientcol change");


	zcon.AddEvalFunc( zCarsten_EvalFunc );

	zCFFT	 ::S_Init					();
	zCPolygon::S_InitMorph				();
	zCTimer  ::S_SetMaxFPS				( zoptions->ReadDWord("ENGINE","zMaxFPS", zCTimer::S_GetMaxFPS()) );
	zCParticleFX::S_SetAmbientPFXEnabled( zoptions->ReadBool("ENGINE","zAmbientPFXEnabled", TRUE) );
	zCWorld::S_SetAmbientVobsEnabled	( zoptions->ReadBool("ENGINE","zAmbientVobsEnabled", TRUE) );
	zCWorld::S_SetEnvMappingEnabled		( zoptions->ReadBool("ENGINE","zEnvMappingEnabled", TRUE) );

#ifdef COMPILING_SPACER
	zCWorld::S_SetAlternateRenderOrder  ( FALSE );
#else
	zCWorld::S_SetAlternateRenderOrder  ( !zoptions->ReadBool("ENGINE","zSkyRenderFirst", TRUE ) );
#endif
	zCAIPlayer::S_SetShowWeaponTrails	( zoptions->ReadBool("GAME", "zShowWeaponTrails", TRUE) );

	ztimer.SetMaxFPS(zCTimer::S_GetMaxFPS());

	//zLocal_Startup();
}

void zCarsten_ShutDown()
{
	// [SPECKELS] Hack, da DirectMusic crasht, wenn man das MusicSystem loescht
	// if (zmusic) delete zmusic;
	zmusic = 0;

	zCMenu::Shutdown();

	delete zinput; 
	zinput = 0;

    zCAICamera::GlobalCleanUp(); // [Moos]

	//zLocal_Shutdown();
}

void zCarsten_ShutDown_Fast()
{
	delete zinput; 
	zinput = 0;
}



