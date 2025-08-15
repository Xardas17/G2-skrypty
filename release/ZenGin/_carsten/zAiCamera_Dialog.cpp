#include "zcore.h"
#include "zTypes3d.h"
#include "zKBSplines.h"
#include "zoption.h"
#include "zarchiver.h"
#include "zCSCamera.h"
#include "zworld.h"
#include "zAICamera.h"
#include "zAICamera_Movement.h"
#include "zAICamera_Core.h"


zCVob *speaker	= 0;
zCVob *listener = 0;


void zCAICamera::StartupDialogCam()
{
	// jetzt die Presets saugen
	zerr.Message( zSTRING("C: reading dialog presets ...") );

	zoptions->ChangeDir(DIR_PRESETS);
	zCArchiver* arch = zarcFactory.CreateArchiverRead("DIALOGCAMS.ZEN");
	if (!arch)
	{
		zERR_FATAL("C: Dialogcam Preset File is not present!");
	}
		
	while(!arch->EndOfArchive()) 
	{			
		zCCSCamera *newCam = (zCCSCamera *)arch->ReadObject();
		if (newCam->GetObjectName() != "CAMERASTART") dialogCamList.InsertEnd(newCam);
		else zRELEASE(newCam);
	}
	
	arch->Close();
	zRELEASE(arch);

	if (zoptions->Parm("CONVERTDIALOGCAMS"))
	{
		zoptions->ChangeDir(DIR_PRESETS);
		zCArchiver* arch = zarcFactory.CreateArchiverWrite("DIALOGCAMS.ZEN",zARC_MODE_ASCII);
		if (!arch) return;

		for (int i=0; i<dialogCamList.GetNum(); i++)
		{
			arch->WriteObject("",dialogCamList[i]);
		}
		arch->Close();
		zRELEASE(arch);
	}

	// manuelles anheben der schulter camera (CR/CL Presets)
    for (int i=dialogCamList.GetNum()-1; i>=0; i--)
	{
		if (dialogCamList[i]->GetObjectName().Search("_C")!=-1)
		{
			for (int j=dialogCamList[i]->GetNumCamKeys()-1; j>=0; --j)
			{
				dialogCamList[i]->GetCamKey(j)->originalPose.SetTranslation(dialogCamList[i]->GetCamKey(j)->originalPose.GetTranslation()+zVEC3(0,25,0));
			}
		}
		else 
		{
			for (int j=dialogCamList[i]->GetNumCamKeys()-1; j>=0; --j)
			{
				dialogCamList[i]->GetCamKey(j)->originalPose.SetTranslation(dialogCamList[i]->GetCamKey(j)->originalPose.GetTranslation()+zVEC3(0,40,0));
			}
		};
	};

}

void zCAICamera::GlobalDialogCamCleanUp()
{
	// FIXME FIXME FIXME: Das ist so die einzige Möglichkeit 
	// Objekte vom Typ zCCSCamera/zCCamTrj_KeyFrame, die sich _nicht_ in der
	// Welt befinden, zu löschen. Prob: Die Klassen referezieren sich gegenseitig.
    for (int i=dialogCamList.GetNum()-1; i>=0; i--)
	{	
		for (int j=dialogCamList[i]->GetNumCamKeys()-1; j>=0; --j)
		{
			dialogCamList[i]->RemoveCamKey(dialogCamList[i]->GetCamKey(j));
		}
		for (	 j=dialogCamList[i]->GetNumTargetKeys()-1; j>=0; --j)
		{
			dialogCamList[i]->RemoveTargetKey(dialogCamList[i]->GetTargetKey(j));
		}
        zRELEASE(dialogCamList[i]);
	}
	dialogCamList.DeleteList();
};


void zCAICamera::InitDialogCam()
{
	dialogCamDuration		= 10;
	lastDialogCamSide		= 0;
	numOUsSpoken			= 0;
	numDialogCamTakes		= 0;
	lastNumDialogCamTakes	= 0;
	dialogCam				= NULL;
	firstSpeakerWasPC		= FALSE;
};

void zCAICamera :: SetDialogCamDuration(const float duration)	
{ 
	dialogCamDuration	  = duration;	
};

void zCAICamera :: ReleaseLastDialogCam()
{

	if (dialogCam) 
	{ 
		if (camVob->GetHomeWorld()) camVob->GetHomeWorld()->RemoveVob(dialogCam);

		for (int j=dialogCam->GetNumCamKeys()-1; j>=0; --j)
		{
			dialogCam->RemoveCamKey(dialogCam->GetCamKey(j));
		}
		for (	 j=dialogCam->GetNumTargetKeys()-1; j>=0; --j)
		{
			dialogCam->RemoveTargetKey(dialogCam->GetTargetKey(j));
		}
		zRELEASE(dialogCam);
	}
}

zCCSCamera *zCAICamera :: PickPreset(const zSTRING name, const zCArray<zCCSCamera*>&list)
{
	for (int i=0; i<list.GetNum(); i++) 
	{
		if (list[i]->GetObjectName()==name) return list[i];
	};
	return NULL;
};

void zCAICamera :: StartDialogCam(const zBOOL changedCamSys)
{
	// hier jetzt die targetVobList auseinandernehmen, und das korrekte zCCSCamera Objekt für eine
	// Dialog Kamerafahrt initialisieren
	// Zum Startpunkt der Camerafahrt müssen alle KF's eimal an der Line of Sight ausgerichtet werden
	// da die RefVobs sich danach aber noch drehen können, wird die Rotation der RefVobs danach ignoriert
	// (mit ignoreFORVobRot = TRUE)
	// dann werden alle KF's an die Distanz von Erzähler/Zuhörer angepasst
	// Abschliessend wird ein passendes Preset gewählt, ohne dabei die Seite der Line of Interest während des Dialogs zu wechseln
	
	zCZoneMusic::SetAutochange(FALSE);	// kein musik-themenwechsel während dialogen

	assert(targetVobList.GetNumInList()==2);

	if (changedCamSys)  { zERR_MESSAGE(9,0,"C: CAMAI: StartDialogCam started first time"); }
	else				zERR_MESSAGE(9,0,"C: CAMAI: StartDialogCam started");

	zCArray<zCCSCamera*>dialogPresets;
	
	speaker	 = targetVobList[0];
	listener = targetVobList[1];

	if (listener->GetPositionWorld() == speaker->GetPositionWorld()) 
	{
		zERR_WARNING("C: zCAICamera :: StartDialogCam(): listener and speaker have same position!");
		return;
	}

	numDialogCamTakes++;

	zBOOL criticalNSCs = (speaker ->GetBBox3DWorld().GetVolume()>(700*700*700)) || (listener->GetBBox3DWorld().GetVolume()>(700*700*700));

	// rolle[0] ist der sprecher, rolle[1] der zuhörer
	// vereinbarung: der zuhörer ist bis zum zweiten switch IMMER der Spieler
	// die Kamera switcht solange _nicht_

	if (changedCamSys) 
	{
		if (speaker->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_PC)
		{ 
			// beim ersten ansprechen wird bis zum wechseln der rollen immer auf den npc geschaut, 
			zSwap(speaker,listener);
			firstSpeakerWasPC = TRUE;
		}
	}
	else if (firstSpeakerWasPC)
	{
		// schauen, wie oft schon geswitcht wurde
		if (numDialogCamTakes <= 2) return;	// nichts bis zum ersten "echten" rollenwechsel machen
		else firstSpeakerWasPC = FALSE;
	}

	// dialogcamera liste aufbauen und diese mit den korrekten referenz vobs versehen
	// TODO: line of interest berücksichtigen & keyframes anpassen

	zMAT4 lineOfInterestTrafo   = GetPoseOfHeading(listener->GetPositionWorld(), (speaker ->GetPositionWorld()-listener->GetPositionWorld()).Normalize());
	zMAT4 lineOfInterestTrafoINV= GetPoseOfHeading(speaker ->GetPositionWorld() ,(listener->GetPositionWorld()-speaker->GetPositionWorld()).Normalize());

	for (int i =0; i<dialogCamList.GetNum(); i++)
	{
		zCCSCamera *newPreset = static_cast<zCCSCamera*>(dialogCamList[i]->CreateCopy());

		for (int pcount = 0; pcount<newPreset->GetNumCamKeys(); pcount++)
		{
			zCCamTrj_KeyFrame* key = newPreset->GetCamKey(pcount);
			zMAT4 trafoKeyToPreset = newPreset->trafoObjToWorld.InverseLinTrafo() * key->trafoObjToWorld;
			// neue Position und Orientierung entlang der Line of Interest (Spieler->NPC):
			zMAT4 trafoKeyToLine   =  lineOfInterestTrafo * trafoKeyToPreset;

			key->SetTrafo(trafoKeyToLine);
			//key->Changed();
		}

		for (int tcount = 0; tcount<newPreset->GetNumTargetKeys(); tcount++)
		{
			zCCamTrj_KeyFrame* key = newPreset->GetTargetKey(tcount);
			zMAT4 trafoKeyToPreset = newPreset->trafoObjToWorld.InverseLinTrafo() * key->trafoObjToWorld;
			// neue Position und Orientierung entlang der Line of Interest (NPC->Spieler):
			zMAT4 trafoKeyToLine   =  lineOfInterestTrafoINV * trafoKeyToPreset;

			key->SetTrafo(trafoKeyToLine);
			//key->Changed ();
		}

		zCCSCamera_EventMsgActivate* msg_c = zNEW( zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE) );
		zCCSCamera_EventMsgActivate* msg_t = zNEW( zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE) );

		if (newPreset->GetObjectName().Search("DIALOGCAM_A") != -1 || newPreset->GetObjectName().Search("DIALOGCAM_C") != -1)
		{
			msg_c->MD_SetVobParam(listener);
			msg_t->MD_SetVobParam(speaker );
		}
		else if (newPreset->GetObjectName().Search("DIALOGCAM_E") != -1 )
		{
			msg_c->MD_SetVobParam(speaker);
			msg_t->MD_SetVobParam(speaker);
		}
		else 
		{
			msg_c->MD_SetVobParam(listener);
			msg_t->MD_SetVobParam(listener);
		}

		newPreset->OnMessage(msg_c,NULL);
		newPreset->OnMessage(msg_t,NULL);

		dialogPresets.InsertEnd( newPreset );

        zRELEASE(msg_c); // [Moos] Leakfixes
        zRELEASE(msg_t);
	}

	// nun den korrekten camera preset rausfischen
	zBOOL presetFound  = FALSE;
	zCCSCamera *tryCam = NULL;

	if (changedCamSys)
	{
		// Preset AR default
		if ( zRandF()<0.3F ) 
		{
			// (30% Wahrscheinlichkeit Preset C oder M)
			if ( zRandF()<0.05F && (listener->GetPositionWorld() - speaker->GetPositionWorld()).LengthApprox() < 2000)
			{
				tryCam = PickPreset("DIALOGCAM_MR",dialogPresets);

				if ( !DialogPresetIsValid(tryCam) )
				{
					tryCam = PickPreset("DIALOGCAM_ML",dialogPresets);

					if ( DialogPresetIsValid(tryCam) ) presetFound = TRUE;

				} else presetFound = TRUE;
			}

			if (!criticalNSCs)
			if (!presetFound)
			{
				tryCam = PickPreset("DIALOGCAM_CR",dialogPresets);

				if ( !DialogPresetIsValid(tryCam) )
				{
					tryCam = PickPreset("DIALOGCAM_CL",dialogPresets);

					if ( DialogPresetIsValid(tryCam) ) presetFound = TRUE;

				} else presetFound = TRUE;
			}
		}

		if (!presetFound)
		{
			tryCam = PickPreset("DIALOGCAM_AR",dialogPresets);

			if ( !DialogPresetIsValid(tryCam) )
			{
				tryCam = PickPreset("DIALOGCAM_AL",dialogPresets);

				if ( DialogPresetIsValid(tryCam) ) presetFound = TRUE;

			} else presetFound = TRUE;
		}

		if (!presetFound) tryCam = PickPreset("DIALOGCAM_AR",dialogPresets);		// panic preset default

	}
	else 
	{	
		// rollen müssen getauscht worden sein, oder mehr als eine OU wurde nach dem dritten Take
		// von ein und denselben sprecher losgelassen

		// Preset A + letzte seite beachten
		// (30% Wahrscheinlichkeit Preset C oder M)
		
		// wenn letzter Preset A war, mit 30% Warscheinlichkeit auf E

		if ( (numOUsSpoken>1) && (!criticalNSCs) ) 
		{
			// hier muss die Seite gleich bleiben, da speaker<->listener nicht gewechselt hat
			zSTRING side = (lastDialogCamSide == 0) ? "R" : "L";

			if ( lastPresetName.Search("DIALOGCAM_A") != -1 || lastPresetName.Search("DIALOGCAM_C") != -1)
			{
				if (zRandF()<=0.3F)
				{
					if ( (speaker->GetPositionWorld()-listener->GetPositionWorld()).Length()>200 )
					if ( DialogPresetIsValid( PickPreset("DIALOGCAM_E" + side,dialogPresets)) )
					{
						tryCam = PickPreset("DIALOGCAM_E" + side,dialogPresets);
					}
				}
			}
		}
		else 
		{
			zSTRING side = (lastDialogCamSide == 0) ? "L" : "R";

			// Preset AR default
			if ( zRandF()<0.3F ) 
			{
				// (30% Wahrscheinlichkeit Preset C oder M)
				if ( zRandF()<0.05F )
				{
					tryCam  = PickPreset("DIALOGCAM_M" + side,dialogPresets);
					if ( DialogPresetIsValid(tryCam) ) presetFound = TRUE;
				}

				if (!criticalNSCs)
				if (!presetFound)
				{
					tryCam = PickPreset("DIALOGCAM_C" + side,dialogPresets);

					if ( DialogPresetIsValid(tryCam) ) presetFound = TRUE;
				}
			}

			if (!presetFound)
			{
				tryCam = PickPreset("DIALOGCAM_A" + side,dialogPresets);

				if ( DialogPresetIsValid(tryCam) ) presetFound = TRUE;
			}

			if (!presetFound) 
			{
				if ( (speaker->GetPositionWorld()-listener->GetPositionWorld()).Length()>200 )
				if ( DialogPresetIsValid( PickPreset("DIALOGCAM_E" + side,dialogPresets)) )
				{
					tryCam = PickPreset("DIALOGCAM_E" + side,dialogPresets);
					presetFound = TRUE;
				}
			}
			
			if (!presetFound) 
			{
				tryCam = PickPreset("DIALOGCAM_A" + side,dialogPresets);		// panic preset default
			}
		}
	}

	// alte dialog camera stoppen
	ReleaseLastDialogCam();

	// unnötige Elemente der aufgebauten Preset Liste löschen
	for (i=0; i<dialogPresets.GetNum(); i++)
	{
		zCCSCamera *preset = dialogPresets[i];

		if (preset != tryCam) 
		{ 
			for (int j=preset->GetNumCamKeys()-1; j>=0; --j)
			{
				preset->RemoveCamKey(preset->GetCamKey(j));
			}
			for (	 j=preset->GetNumTargetKeys()-1; j>=0; --j)
			{
				preset->RemoveTargetKey(preset->GetTargetKey(j));
			}
			zRELEASE(preset);
		}
	}
	dialogPresets.DeleteList();

	if (!tryCam) return; // [Moos] diese Zeile war vorher zwei Blöcke höher; das nichtreleasen der dialogPresets hat im Fall von return Leaks gemacht.

	dialogCam = tryCam;
	
	lastDialogCamSide =  (tryCam->GetObjectName()[tryCam->GetObjectName().Length()-1] == 'R') ? 0 : 1;


	#ifdef CHASE_DEBUG
	zERR_WARNING("C: DLG: choosen dialogcam: " + dialogCam->GetObjectName());
	zSTRING idString = speaker->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_PC ? "PC" : "NPC";
	zERR_WARNING("C: DLG: Speaker is " + idString);
	#endif

	dialogCam->ignoreFORVobRotCam		= TRUE;
	dialogCam->ignoreFORVobRotTarget	= TRUE;
	dialogCam->adaptToSurroundings		= TRUE;
	dialogCam->Refresh();

	camVob->GetHomeWorld()->AddVob(dialogCam);

	dialogCam->SetSleepingMode(zVOB_AWAKE_DOAI_ONLY);
	dialogCam->SetSleeping    (FALSE);

	zCCSCamera_EventMsg *msg = zNEW( zCCSCamera_EventMsg(zCCSCamera_EventMsg::EV_PLAY) );
	
	msg->time = GetDialogCamDuration()/1000;

	dialogCam->OnMessage(msg,NULL);

	lastPresetName = dialogCam->GetObjectName();

    zRELEASE(msg); // [Moos] Leakfix
};

zBOOL zCAICamera :: DialogPresetIsValid( zCCSCamera*preset )
{
	// hier wird geprüft, ob der Preset als Dialogcamera gültig ist
	// gecheckt wird: 
	// - LOS(player, PosKF)
	// - InWorld(PosKF)
	// besser wäre: Test auf Sichtbarkeit des Targets etc...
	if (!preset) return FALSE;

	for (int i=0; i<preset->GetNumCamKeys(); i++)
	{
		if ( !pathSearch->LineOfSight(preset->GetCamKey(i)->GetPositionWorld(),	speaker->GetPositionWorld()) ) return FALSE;
	}
	return TRUE;

};


	/*for (int i=0; i<dialogCamList.GetNumInList(); i++) 
	{
		dialogPresets.InsertEnd( static_cast<zCCSCamera*>(dialogCamList[i]->CreateCopy()) );

		zCArray<zCCamTrj_KeyFrame*>frontPosKFList;
		zCArray<float>			   frontPosDist;

		for (int pcount = 0; pcount<dialogPresets[i]->GetNumCamKeys(); pcount++)
		{
			zCCamTrj_KeyFrame* key = dialogPresets[i]->GetCamKey(pcount);
			zMAT4 trafoKeyToPreset = dialogPresets[i]->trafoObjToWorld.InverseLinTrafo() * key->trafoObjToWorld;
			// neue Position und Orientierung entlang der Line of Interest (Spieler->NPC):
			zMAT4 trafoKeyToLine   =  lineOfInterestTrafo * trafoKeyToPreset;
			// problem: falls sich Keyframes vor dem Spieler befinden, müssen diese an
			// die Entfernung zum Target Vob angepasst werden
			// ermittle die trafo relativ zum origin vob
			zMAT4 testTrafo		   =   roles[1]->trafoObjToWorld.InverseLinTrafo() * trafoKeyToLine;
			
			if (testTrafo.GetTranslation()[VZ]>0) 
			{	// keyframe befindet sich vor dem Spieler -> in Liste eintragen
				frontPosKFList.InsertEnd(key);
				frontPosDist  .InsertEnd(testTrafo.GetTranslation()[VZ]);
			}

			//key->SetTrafo(trafoKeyToLine);
			//key->Changed();
		}

		if (dialogPresets[i]->GetObjectName().Search("OU_ZOOM_") != -1) 
		{
			int brk=0;
		}

		float maxDist = -1;
		// Front Pos Keyframe ermitteln, der am weitesten vom origin entfernt ist
		for (	 pcount = 0; pcount<frontPosKFList.GetNumInList(); pcount++)
		{
			float dist = frontPosDist[pcount];
			if ( dist > maxDist ) maxDist = dist;
		}

		// FIXME: nicht exakt. Muss der Abstand des letzten KF's zum Target berücksichtigt werden
		float zScale = (roles[1]->GetPositionWorld()-roles[0]->GetPositionWorld()).Length()/maxDist;

		// alle Front Pos Keyframes an die Entfernung zum Target anpassen
	//	for (	 pcount = 0; pcount<frontPosKFList.GetNumInList(); pcount++)
	//	{
	//		zMAT4 testTrafo = roles[1]->trafoObjToWorld.InverseLinTrafo() * frontPosKFList[pcount]->trafoObjToWorld;
	//		testTrafo.SetTranslation(zVEC3(testTrafo.GetTranslation()[VX],testTrafo.GetTranslation()[VY],testTrafo.GetTranslation()[VZ]*zScale));
	//		testTrafo = roles[1]->trafoObjToWorld * testTrafo;
//
//			frontPosKFList[pcount]->SetTrafo( testTrafo );
//			frontPosKFList[pcount]->Changed ();
//		}

		for (int tcount = 0; tcount<dialogPresets[i]->GetNumTargetKeys(); tcount++)
		{
			zCCamTrj_KeyFrame* key = dialogPresets[i]->GetTargetKey(tcount);
			zMAT4 trafoKeyToPreset = dialogPresets[i]->trafoObjToWorld.InverseLinTrafo() * key->trafoObjToWorld;
			// neue Position und Orientierung entlang der Line of Interest (NPC->Spieler):
			zMAT4 trafoKeyToLine   =  lineOfInterestTrafoINV * trafoKeyToPreset;

			//key->SetTrafo(trafoKeyToLine);
			//key->Changed ();
		}

		zCCSCamera_EventMsgActivate* msg_c = zNEW( zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE) );
		msg_c->MD_SetVobParam(roles[1]);
		dialogPresets[i]->OnMessage(msg_c,NULL);

		zCCSCamera_EventMsgActivate* msg_t = zNEW( zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE) );
		msg_t->MD_SetVobParam(roles[0]);
		dialogPresets[i]->OnMessage(msg_t,NULL);

		dialogPresets[i]->ignoreFORVobRotCam	= TRUE;
		dialogPresets[i]->ignoreFORVobRotTarget = TRUE;
		dialogPresets[i]->adaptToSurroundings   = TRUE;
		//dialogPresets[i]->Refresh();

	}*/
