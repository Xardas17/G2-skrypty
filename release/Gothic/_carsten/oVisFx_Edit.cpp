

#include "zcore.h"
#include "oVisFX.h"
#include "zconsole.h"


	// game files. nicht alle bzw. gar keine nötig, muss man noch sehen...
	#include "oGame.h"
	#include "oWorld.h"
	#include "oNpc.h"


static zCVob	    *editVob			= 0;
static zCConsole	*fxCon				= 0;		// fx console
static zCConsole	*emCon				= 0;		// emitter console

zBOOL		drawBBox			= FALSE;
zBOOL		drawTrj				= FALSE;
zBOOL		showTarget			= FALSE;
float		playTime			= 5;
zVEC3		lastTrjPos;

#ifndef _DUMMYVFX_

oCVisualFX *	oCVisualFX::actFX		= 0;	

static zCVob *GetNearVob()
{
	if (!editVob) return 0;

	zTBBox3D box;
	box.maxs = editVob->GetPositionWorld() + zVEC3(2000,2000,2000);
	box.mins = editVob->GetPositionWorld() - zVEC3(2000,2000,2000);
	zCArray<zCVob*>resVobList;
	ogame->GetWorld()->CollectVobsInBBox3D(resVobList,box);

	for (int i=0; i<resVobList.GetNumInList(); i++){
		if (resVobList[i]->GetVobType() == zVOB_TYPE_NSC && resVobList[i]!=oCNpc::player) return resVobList[i];
	}
	return 0;
}

static void SetEditVob()
{
	if (editVob && (editVob!=oCNpc::player)) 
	{
		editVob->RemoveVobFromWorld();
		zRELEASE(editVob);
	}

	editVob = oCNpc::player;		// FIXME: einzige Bedingung für game Klasse?

	if (editVob == 0) 
	{
		editVob = zNEW(zCVob);
		zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVob(editVob);
		editVob->SetVobName			("help fx edit vob");
		editVob->SetVisual			("invisible_zCVob.3ds");  
		editVob->SetShowVisual		(TRUE);
		editVob->SetCollDet			(FALSE);
		editVob->SetSleeping		(FALSE);
		editVob->SetPhysicsEnabled	(FALSE);
		editVob->SetPositionWorld(zCCamera::activeCam->GetVob()->GetPositionWorld() + 150 * zCCamera::activeCam->GetVob()->GetAtVectorWorld());
	}
}

void oCVisualFX :: Edit()
{
	zcon.Hide();
	
	if (fxCon) delete fxCon;
	fxCon = zNEW(zCConsole());
	fxCon -> SetPos  (0,0);
	fxCon -> SetParser (fxParser);
	fxCon -> SetChangedFunc ( oCVisualFX::FxConsole_ParameterChanged );  
	fxCon -> AddEvalFunc	( oCVisualFX::FxConsole_EvalFunc ); 
	fxCon -> AddEvalFunc	( oCVisualFX::EmConsole_EvalFunc ); 
	zcon.Register		( "VFX_REPARSE"		, "reparses the vfx scripts");

	fxCon -> Register  ( "EDIT FX"	, "edits a special effect");
	fxCon -> Register  ( "VFX_RESETKEY"	, "resets act emitter key to the given base fx in magic editor");
	fxCon -> Register  ( "VFX_RESETALL"	, "resets all emitter keys to the given base fx in magic editor");
	fxCon -> Register  ( "VFX_REPARSE"	, "reparses magic scripts" );
	fxCon -> Register  ( "VFX_RESETKEY"	, "resets act emitter key to the given base fx in magic editor");
	fxCon -> Register  ( "VFX_SETDRAWBBOX" , "shows all bboxes of all oCVisualFX objects");
	fxCon -> Register  ( "VFX_SETDRAWTRJ"  , "shows the trajectorys of all oCVisualFX objects");
	fxCon -> Register  ( "VFX_SHOWTARGET"  , "shows the targets of the oCVisualFX objects");

	fxCon->EditInstance(GetName(), (zBYTE*)&visName_S);
	zSTRING key; 
	// open first emitter key if available
	if (emKeyList.GetNumInList() >= 1) {
		emKeyList[0]->Edit();
		actKey = emKeyList[0];
	}
	fxCon->SetFocus();
};

void oCVisualFX::CreateNewScriptFX(const zSTRING &name)
{
	zSTRING ID(name);
	ID.Upper();
	zoptions->ChangeDir(DIR_SCRIPTS);
	zFILE* file = zfactory->CreateZFile("System\\VisualFx\\VisualFxInst.d");
	file->Open		(true);
	file->Append	();
	file->Write	(zSTRING("\nINSTANCE "+ID+"(CFx_Base)\n"));
	file->Write	(zSTRING("{\n"));
	file->Write	(zSTRING("};\n"));
	file->Close	();
	delete file;
	InitParser();
};



void oCEmitterKey:: Edit()
{
	if (emCon) delete emCon;
	emCon = zNEW(zCConsole());

	emCon -> SetPos			(4100,0);
	emCon -> SetParser		( oCVisualFX::fxParser );
	emCon -> SetChangedFunc ( oCVisualFX::EmConsole_ParameterChanged );  
	emCon -> AddEvalFunc	( oCVisualFX::FxConsole_EvalFunc ); 
	emCon -> AddEvalFunc	( oCVisualFX::EmConsole_EvalFunc ); 
	emCon -> Register		( "EDIT FX"	, "edits a special effect");
	emCon -> Register		( "VFX_RESETKEY"	, "resets act emitter key to the given base fx in magic editor");
	emCon -> Register		( "VFX_RESETALL"	, "resets all emitter keys to the given base fx in magic editor");
	emCon -> Register		( "VFX_SETDRAWBBOX" , "shows all bboxes of all oCVisualFX objects");
	emCon -> Register		( "VFX_SETDRAWTRJ"  , "shows the trajectorys of all oCVisualFX objects");
	emCon -> Register		( "VFX_SHOWTARGET"  , "shows the targets of the oCVisualFX objects");
	emCon -> Register		( "VFX_REPARSE"		, "reparses the vfx scripts");

	// open first emitter key if available
	emCon->EditInstance(GetName(),this);
	emCon->SetFocus();
};

void oCEmitterKey::CreateNewScriptKey(const zSTRING &n)
{
	zSTRING ID(n);
	ID.Upper();
	zoptions->ChangeDir(DIR_SCRIPTS);

	zFILE* file = zfactory->CreateZFile("System\\VisualFx\\VisualFxInst.d");
	file->Open	(true);
	file->Append();
	file->Write	(zSTRING("\nINSTANCE "+ID+"(C_ParticleFXEmitKey)\n"));
	file->Write	(zSTRING("{\n"));
	file->Write	(zSTRING("};\n"));
	file->Close	();
	delete file;
	oCVisualFX::InitParser();
};

// -------------------------------------------------------------------------------------------------------
// FX Base Class related
// -------------------------------------------------------------------------------------------------------
void  oCVisualFX::FxConsole_ParameterChanged(const zSTRING &in) 
{
	zSTRING s(in);
	s.Upper();

	if ( s == "EMTRJNUMKEYS" ) 
	{
		int num = actFX->emTrjNumKeys;
		int actNum = actFX->emKeyList.GetNumInList();
		if ( actNum == 0) 
		{
			if (num>0) 
			{
				for (int i=0; i<num; i++) 
				{
					oCEmitterKey *newKey = zNEW(oCEmitterKey);

					newKey -> SetDefaultByFX(actFX);
					newKey -> SetName( actFX->GetName()+"_KEY"+zSTRING(num) );

					actFX->emKeyList.Insert(newKey);
				}
				InitParser();
			}
		}
		else if (actNum>num) 
		{
			for (int i=num; i<actNum; i++) delete actFX->emKeyList[i];
		} 
		else 
		{
			for (int i=actNum; i<num; i++) 
			{
				oCEmitterKey *newKey = zNEW(oCEmitterKey);

				newKey -> SetDefaultByFX(actFX);
				newKey -> SetName( actFX->GetName()+"_KEY"+zSTRING(num) );

				actFX->emKeyList.Insert(newKey);
			}
			oCVisualFX::InitParser();
		}
	}
	else if ( s == "VISNAME" ) 
	{
		if ( !actFX->GetVisual() ) actFX->SetupEmitterKeysByVisual();
		actFX -> visName_S.Upper();
		actFX -> SetVisualByString(actFX->visName_S);
	}
	else if ( s == "LIGHTPRESETNAME" ) 
	{
		if (actFX->light && actFX->GetHomeWorld()) 
		{
			actFX->GetHomeWorld()->RemoveVob(actFX->light);			
		}
		zRELEASE(actFX->light); 
		if (actFX->lightPresetName != "")
		{
			actFX -> lightPresetName.Upper();
		    actFX -> light= zNEW(zCVobLight); 
			actFX -> light-> SetByPreset( actFX->lightPresetName );
			actFX -> light->SetCanMove(TRUE);

			actFX->light->SetPositionWorld(actFX->GetPositionWorld());
			actFX->GetHomeWorld()->AddVobAsChild(actFX->light,actFX);
		}
	}
	else if ( s == "SFXID" ) 
	{
		if (actFX->sfx) 
		{
			actFX->sfx->Release(); 
			actFX->sfxHnd = 0;
		}
		if (actFX->sfxID != "") 
		{
			actFX->sfx	  = zsound -> LoadSoundFXScript(actFX->sfxID);
			actFX->sfxHnd = zsound -> PlaySound3D      (actFX->sfx,actFX);
		}
	}
	else if ( s == "EMCHECKCOLLISION" ) 
	{
		actFX->SetCollisionEnabled(actFX->emCheckCollision);
	}
	else if ( s == "EMTRJMODE_S" ) 
	{
		SetEditVob();
	}
	else if ( s == "VFX_REPARSE" )
	{
		oCVisualFX::InitParser();
		if (emCon) emCon -> SetParser		( oCVisualFX::fxParser );
		if (fxCon) fxCon -> SetParser		( oCVisualFX::fxParser );

	}

	actFX->ParseStrings();

	SetEditVob();
	actFX->target = GetNearVob();

	if (!actFX->target) actFX->targetPos = editVob->GetPositionWorld()+400*editVob->GetAtVectorWorld();

	actFX->CalcTrajectory();

};

void  oCVisualFX::EmConsole_ParameterChanged(const zSTRING &in) 
{
	zSTRING s(in);
	s.Upper();

	if ( s == "SFXID" )
	{
		if (actFX->GetActKey()->sfx) 
		{
			actFX->GetActKey()->sfx->Release(); 
			actFX->GetActKey()->sfx	   = 0;
			actFX->GetActKey()->sfxHnd = 0;
		}
		if (actFX->GetActKey()->sfxID != "") 
		{
			actFX->GetActKey()->sfx = zsound -> LoadSoundFXScript(actFX->GetActKey()->sfxID);
		}
	}

	SetEditVob();

	actFX -> GetActKey()->ParseStrings();
	actFX -> UpdateFXByEmitterKey(actFX->GetActKey());
	actFX -> target = GetNearVob();

	if (!actFX->target) actFX->targetPos = editVob->GetPositionWorld()+400*editVob->GetAtVectorWorld();

	actFX->CalcTrajectory();

};

zBOOL oCVisualFX::FxConsole_EvalFunc (const zSTRING &in, zSTRING &msg)
{

	zSTRING s = in;
	s.Upper();
	if ( s.PickWord(1, " ") == "EDIT" ) 
	{
		if ( s.PickWord(2, " ") == "FX" ) 
		{
			oCVisualFX::InitParser();
		//	emCon -> SetParser		( oCVisualFX::fxParser );
		
			zSTRING id = s.PickWord(3, " ");
			if (id == "") 
			{
				msg == "fx id invalid";
				return TRUE;
			}
			if ( actFX ) 
			{
				if ( id == actFX->GetName() ) 
				{
					actFX->Edit();
					return TRUE;
				}
				else 
				{
					oCVisualFX::actFX->RemoveVobFromWorld();
					zRELEASE(oCVisualFX::actFX); 

					actFX = zNEW(oCVisualFX());

					if (fxParser->GetSymbol(id)) 
					{
						actFX ->SetByScript(id);
						msg = "deleted old fx";
					}
					else 
					{
						msg = "unknown fx identifier: " + id + " creating new";
						actFX -> fxName = id;
						CreateNewScriptFX(id);
						InitParser();
					}

					SetEditVob();
					zCVob *nearVob = GetNearVob();

					if (nearVob) actFX -> Init(editVob,nearVob); 
					else		 actFX -> Init(editVob,editVob->GetPositionWorld()+400*editVob->GetAtVectorWorld());

					actFX -> Edit();

					return TRUE;
				};
			}
			else if (fxParser->GetSymbol(id)) 
			{
				actFX = zNEW(oCVisualFX());
				actFX -> SetByScript(id);
				SetEditVob();
				zCVob *nearVob = GetNearVob();

				actFX->Open();

				if (nearVob) actFX -> Init(editVob,nearVob); 
				else		 actFX -> Init(editVob,editVob->GetPositionWorld()+400*editVob->GetAtVectorWorld());

				actFX -> Edit();

				return TRUE;
			}
			else
			{ 
				msg = "unknown fx identifier: " + id + " creating new";

				actFX = zNEW(oCVisualFX());

				actFX -> fxName = id;
				CreateNewScriptFX(id);
				InitParser();
				actFX -> SetByScript(id);

				SetEditVob();
				zCVob *nearVob = GetNearVob();

				actFX->Open();
				
				if (nearVob) actFX -> Init(editVob,nearVob); 
				else		 actFX -> Init(editVob,editVob->GetPositionWorld()+400*editVob->GetAtVectorWorld());

				actFX -> Edit();

				return TRUE;
			}
		} 
	}
	else if (s.Search("VFX_SETDRAWBBOX")!=-1) 
	{
		drawBBox = !drawBBox;
		if (drawBBox) msg = "enabled drawing fx bounding boxes";
		else		  msg = "disabled drawing fx bounding boxes";
		return TRUE;
	}
	else if ( s.Search("VFX_SETDRAWTRJ")!=-1 ) 
	{
		drawTrj = !drawTrj;
		if (drawTrj) msg = "enabled drawing fx trajectory";
		else		 msg = "disabled drawing fx trajectory";
		return TRUE;
	}
	else if ( s.Search( "VFX_SHOWTARGET")!=-1 ) 
	{
		showTarget = !showTarget;
		if (showTarget) msg = "bbox for vfx target activated";
		else		 msg = "bbox for vfx target deactivated";
		return TRUE;
	}
	else if (s.Search("VFX_RESETKEY")!=-1) 
	{
		actFX->actKey->SetDefaultByFX(actFX);
		msg = "act key reseted";
		return TRUE;
	}
	else if (s.Search("VFX_RESETALL")!=-1) 
	{
		msg = "all keys reseted";
		actFX->SetupEmitterKeysByVisual();
		return TRUE;
	}
	else if ( s.Search("VFX_STOP")!=-1 ) 
	{
		if (actFX) 
		{
			actFX->RemoveVobFromWorld();
			zRELEASE(actFX);
		}
		msg = "deleted";
		return TRUE;
	}
	else if ( s.Search("VFX_REPARSE")!=-1 )
	{
		oCVisualFX::InitParser();
		if (emCon) emCon -> SetParser		( oCVisualFX::fxParser );
		if (fxCon) fxCon -> SetParser		( oCVisualFX::fxParser );
		return TRUE;
	}


	return FALSE;
}
zBOOL oCVisualFX::EmConsole_EvalFunc (const zSTRING &in, zSTRING &msg)
{
	zSTRING s(in);
	s.Upper();

	if ( s.PickWord(1, " ") == "KEY" ) 
	{
		if (actFX == 0) 
		{ 
			msg = "no act fx!"; 
			return TRUE; 
		};

		zSTRING word = s.PickWord(2, " ");

		// bei jedem "key xxx" wird der aktuelle effekt neu gestartet
		actFX->ResetForEditing();
		
		SetEditVob();
		zCVob *nearVob = GetNearVob();

		actFX->Open();
		
		if (nearVob) actFX -> Init(editVob,nearVob); 
		else		 actFX -> Init(editVob,editVob->GetPositionWorld()+400*editVob->GetAtVectorWorld());


		if (word == "OPEN") 
		{
			oCEmitterKey *actEmKey;
			int index = actFX -> FindKey("OPEN");

			if (index == -1) 
			{
				actEmKey = zNEW(oCEmitterKey);
				actEmKey->SetName( actFX->GetName() + "_KEY_OPEN" );
				actFX -> InsertKey(actEmKey);

			} else actEmKey = actFX->GetKey(index);

			if (!fxParser->GetSymbol(actEmKey->GetName())) 
			{
				msg = "key not found... creating";
				oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
				actEmKey->SetDefaultByFX(actFX);
				InitParser();
			};

			actFX->actKey = actEmKey;
			actFX->UpdateFXByEmitterKey(actEmKey);
			actEmKey->Edit();
			return TRUE;
		}
		else if (word == "INIT") 
		{
			oCEmitterKey *actEmKey;
			int index = actFX -> FindKey("INIT");

			if (index == -1) 
			{
				actEmKey = zNEW(oCEmitterKey);
				actEmKey->SetName( actFX->GetName() + "_KEY_INIT" );
				actFX -> InsertKey(actEmKey);

			} else actEmKey = actFX->GetKey(index);

			if (!fxParser->GetSymbol(actEmKey->GetName())) 
			{
				msg = "key not found... creating";
				oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
				actEmKey->SetDefaultByFX(actFX);
				InitParser();
			} 
			
			actFX->actKey = actEmKey;
			actFX->UpdateFXByEmitterKey(actEmKey);
			actEmKey->Edit();
			return TRUE;

		} 
		else if (word == "INVEST") 
		{
			oCEmitterKey *actEmKey;

			int index = actFX -> FindKey("INVEST_" + zSTRING(s.PickWord(3, " ").ToInt()));
			if (index == -1) 
			{
				actEmKey = zNEW(oCEmitterKey);
				actEmKey->SetName( actFX->GetName() + "_KEY_INVEST_" + zSTRING(s.PickWord(3, " ").ToInt()));
				actFX -> InsertKey(actEmKey);

			} else actEmKey = actFX->GetKey(index);

			if (!fxParser->GetSymbol(actEmKey->GetName())) 
			{
				msg = "key not found... creating";
				oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
				actEmKey->SetDefaultByFX(actFX);
				oCVisualFX::InitParser();
			};

			actFX->actKey = actEmKey;
			actFX->UpdateFXByEmitterKey(actEmKey);

			actEmKey->Edit();
			return TRUE;
		} 
		else if (word == "CAST") 
		{
			oCEmitterKey *actEmKey;
			int index = actFX -> FindKey("CAST");

			if (index == -1) 
			{
				actEmKey = zNEW(oCEmitterKey);
				actEmKey->SetName( actFX->GetName() + "_KEY_CAST" );
				actFX -> InsertKey(actEmKey);

			} else actEmKey = actFX->GetKey(index);

			if ( !fxParser->GetSymbol(actEmKey->GetName()) ) 
			{
				msg = "key not found... creating";
				oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
				actEmKey->SetDefaultByFX(actFX);
				InitParser();
			};

			actFX->actKey = actEmKey;
			actFX->UpdateFXByEmitterKey(actEmKey);

			actEmKey->Edit();
			return TRUE;
		} 
		else if (word == "STOP") 
		{
			oCEmitterKey *actEmKey;
			int index = actFX -> FindKey("STOP");

			if (index == -1) 
			{
				actEmKey = zNEW(oCEmitterKey);
				actEmKey->SetName( actFX->GetName() + "_KEY_STOP" );
				actFX -> InsertKey(actEmKey);

			} else actEmKey = actFX->GetKey(index);

			if (!fxParser->GetSymbol(actEmKey->GetName())) 
			{
				msg = "key not found... creating";
				oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
				actEmKey->SetDefaultByFX(actFX);
				oCVisualFX::InitParser();
			};

			actFX->actKey = actEmKey;
			actFX->UpdateFXByEmitterKey(actEmKey);
			actEmKey->Edit();
			return TRUE;
		} 
		else if (word == "COLLIDE") 
		{
			oCEmitterKey *actEmKey;
			int index = actFX -> FindKey("COLLIDE");

			if (index == -1) 
			{
				actEmKey = zNEW(oCEmitterKey);
				actEmKey->SetName( actFX->GetName() + "_KEY_COLLIDE" );
				actFX -> InsertKey(actEmKey);

			} else actEmKey = actFX->GetKey(index);

			if (!fxParser->GetSymbol(actEmKey->GetName())) 
			{
				msg = "key not found... creating";
				oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
				actEmKey->SetDefaultByFX(actFX);
				oCVisualFX::InitParser();
			};

			actFX->actKey = actEmKey;
			actFX->UpdateFXByEmitterKey(actEmKey);
			actEmKey->Edit();
			return TRUE;
		} 
		else 
		{
			int reqKey = word.ToInt();
			if ( reqKey < actFX->emKeyList.GetNumInList() && reqKey >= 0 ) 
			{
				oCEmitterKey *actEmKey = actFX->emKeyList[reqKey];
				if (!fxParser->GetSymbol(actEmKey->GetName())) 
				{
					msg = "key not found... creating";
					actEmKey->SetName(actFX->GetName() + "_KEY" + zSTRING(reqKey));
					oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
					actEmKey->SetDefaultByFX(actFX);
					InitParser();
				} ;
				actFX->actKey = actEmKey;
				actFX->UpdateFXByEmitterKey(actEmKey);
				actEmKey->Edit();
				return TRUE;
			}
		}
	}
	else if (s.Search("VFX_RESETKEY")!=-1) 
	{
		actFX->actKey->SetDefaultByFX(actFX);
		msg = "act key reseted";
		return TRUE;
	}
	else if (s.Search("VFX_RESETALL")!=-1) 
	{
		actFX->SetupEmitterKeysByVisual();
		msg = "all keys reseted";
		return TRUE;
	}
	else if (s.Search("VFX_SETDRAWBBOX")!=-1) 
	{
		drawBBox = !drawBBox;
		if (drawBBox) msg = "enabled drawing fx bounding boxes";
		else		  msg = "disabled drawing fx bounding boxes";
		return TRUE;
	}
	else if ( s.Search("VFX_SETDRAWTRJ" ) !=-1 )
	{
		drawTrj = !drawTrj;
		if (drawTrj) msg = "enabled drawing fx trajectory";
		else		 msg = "disabled drawing fx trajectory";
		return TRUE;
	}
	else if ( s.Search("VFX_SHOWTARGET") !=-1)
	{
		showTarget = !showTarget;
		if (showTarget) msg = "bbox for vfx target activated";
		else		 msg = "bbox for vfx target deactivated";
		return TRUE;
	}
	else if ( s == "PLAY" ) 
	{
		if (actFX) actFX->Play(playTime);
	}
	else if ( s.Search("STOP" ) != -1)
	{
		if (actFX) 
		{ 
			actFX->Stop(); actFX = 0; 
		};

		msg = "stopped";
		return TRUE;
	}
	return FALSE;
}

void oCEmitterKey::SetDefaultByFX(oCVisualFX*fx) 
{
	if (fx->fxBackup) fx->UpdateFXByEmitterKey(fx->fxBackup);

	pfx_scTime					= 1;

	visName_S					= fx->visName_S;
	lightPresetName				= fx->lightPresetName;
	lightRange					= fx->light ? fx->light->GetRange() : 0;
	emFlyGravity				= fx->emFlyGravity;
	emSelfRotVel_S				= fx->emSelfRotVel_S;
	emTrjEaseVel				= fx->emTrjEaseVel;

	if (fx->GetVisual() && dynamic_cast<zCParticleFX*>(fx->GetVisual()) && ((zCParticleFX*)fx->GetVisual())->GetEmitter()) 
	{
		zCParticleEmitter* em		= ((zCParticleFX*)fx->GetVisual())->GetEmitter();
		visSizeScale				=   em->visSizeEndScale;
		pfx_ppsValue				=	em->ppsValue;	
		pfx_ppsIsSmoothChg			=	0;
		pfx_ppsIsLoopingChg			=	0;
		pfx_shpIsVolumeChg			=	0;
		pfx_shpDistribWalkSpeed		=	em->shpDistribWalkSpeed;
		pfx_velAvg					=	em->velAvg;
		pfx_lspPartAvg				=	em->lspPartAvg;				
		pfx_visAlphaStart			=	em->visAlphaStart;
		pfx_flyGravity_S			=	em->flyGravity_S;
		pfx_shpOffsetVec_S			=	em->shpOffsetVec_S;
		pfx_shpDistribType_S		=	em->shpDistribType_S;
		pfx_dirMode_S				=	em->dirMode_S;
		pfx_dirFOR_S				=	em->dirFOR_S;
		pfx_dirModeTargetFOR_S		=	em->dirModeTargetFOR_S;
		pfx_dirModeTargetPos_S		=	em->dirModeTargetPos_S;
		pfx_shpIsVolumeChg			=	em->shpIsVolume;
		pfx_shpScaleFPS				=   em->shpScaleFPS;
		pfx_shpDim_S				=   em->shpDim_S;
	}
	
	ParseStrings();

};

void oCVisualFX::SetupEmitterKeysByVisual()
{
	if ( GetVisual() || GetVisual()->GetVisualDied() ) return ;

	for (int i=0; i<emKeyList.GetNumInList(); i++) 
	{
		emKeyList[i]->SetDefaultByFX(this);
	}
	for (int j=0; j<fxList.GetNumInList(); j++) 
	{
		fxList[j]->SetupEmitterKeysByVisual();
	}
	for (j=0; j<childList.GetNumInList(); j++) 
	{
		childList[j]->SetupEmitterKeysByVisual();
	}
};


void oCVisualFX::ResetForEditing()
{
	zERR_MESSAGE(10,0,"C: VIS: Spell editing-reset: " + visName_S);

	if (light) light->RemoveVobFromWorld();
	if ( sfx && sfxHnd ) zsound->StopSound(sfxHnd);

	if (fxInvestOrigin)	fxInvestOrigin->ResetForEditing();
	if (fxInvestTarget) fxInvestTarget->ResetForEditing();

	// nun alle childs reseten 
	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->ResetForEditing();
	for (j=0; j<childList.GetNumInList(); j++)  childList[j]->ResetForEditing();

	// timer reseten
	collisionTime = 0;
	deleteTime	  = 0;
	nextLevelTime = 0;
	damageTime    = 0;
	easeTime	  = 0;
	trjUpdateTime = 0;
	levelTime	  = 0;
	lifeSpanTimer = 0;
	queueSetLevel = 0;
	
	fxState					= zVFXSTATE_UNDEF;
};


#endif