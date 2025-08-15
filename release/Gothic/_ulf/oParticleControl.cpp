/******************************************************************************** 
 
     $Workfile:: oParticleControl.cpp $                $Date:: 18.10.00 16:35   $
     $Revision:: 8                    $             $Modtime:: 18.10.00 16:35   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oParticleControl.cpp $
 * 
 * 8     18.10.00 16:35 Edenfeld
 * 
 * 7     2.08.00 14:25 Wohlers
 * 
 * 6     21.07.00 15:35 Wohlers
 * 
 * 5     21.07.00 14:43 Wohlers
 * 
 * 4     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 7     24.02.00 23:32 Wohlers
 * Fixes
 * 
 * 6     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 5     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 4     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     20.12.99 20:39 Wohlers
 * ParticleControl angepasst
 * Ani-Probs (Jump/Climb) gefixed
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/
// oCParticleControl
// Andre Schrieber
// 17.12.1998

#include "zCore.h"

#include "oParticleControl.h"
#include "zParser.h"
#include "zConsole.h"
#include "zOption.h"
#include "zModel.h"
#include "zWorld.h"
#include "zWin32.h"
#include "zInput_Win32.h"
#include "zParticle.h"


oCParticleControl::oCParticleControl()
: pfxName("a.pfx"), pfxVobID(-1)
{
	partFX		= NULL;
	pfxVob		= NULL;
	pfxVobID	= 0;
	startpos	= zVEC3(0,0,0);
	IsInEditMode= FALSE;
	rnd_world	= NULL;
	part_edit	= NULL;;
}

oCParticleControl::oCParticleControl(zCWorld* theWorld)
: pfxName("a.pfx"), pfxVobID(-1)
{
	partFX		= NULL;
	pfxVob		= NULL;
	pfxVobID	= 0;
	startpos	= zVEC3(0,0,0);
	IsInEditMode= FALSE;
	rnd_world	= NULL;
	part_edit	= NULL;;

	partFX = zNEW( zCParticleFX() );
	pfxVob = zNEW( zCVob() ); 
	pfxVob -> SetVobName("Particle_Test_Vob");
	pfxVob -> SetCollDet(FALSE);
	rnd_world = theWorld;
	rnd_world->AddVob(pfxVob);
}

oCParticleControl::~oCParticleControl()
{
	if (part_edit) delete(part_edit); part_edit = NULL;
	partFX		= NULL;
	pfxVob		= NULL;
	rnd_world	= NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//		START	-	Partikel-Effekt Krempel		START	
////////////////////////////////////////////////////////////////////////////////////////////////////////

zCVob* oCParticleControl::GetPFXVob () {
	return pfxVob;
};


// ANDRE WUP
void oCParticleControl::SelectActivePFX() {

	// Die "zCParticleFX::emitterPresetList" wird auf dem Bildschirm ausgegeben.
	// Der User wählt die Nummer eines Presets
	// output: "pfxName", der Name des gewählten PFX-Presets

	// beide Frame-Buffer loeschen (front & back)
	zCOLOR col (0,0,0,255);
	zrenderer ->Vid_Clear	(col); 
	zrenderer ->Vid_Blit	();
	zrenderer ->Vid_Clear	(col); 
	zrenderer ->Vid_Blit	();
	{
/*		while (kbPressed(KEY_G)) {
			zCView :: GetInput();
			sysEvent();
		};*/

		int xpos=0;
		int ypos=0;
		for (int i=0; i<zCParticleFX::s_emitterPresetList.GetNumInList(); i++) {
			screen->Print (xpos   , ypos, zSTRING(i)+":");
			screen->Print (xpos+220, ypos, (zCParticleFX::s_emitterPresetList[i])->GetParticleFXName());
			ypos += 200;
			if ((i % 36)==35) {
				xpos += (8192 / 4);
				ypos  = 0;
			};
		};
		int index;
		do {
			zSTRING res = screen->Input			(0,7900, 2000, zSTRING(""));
//			zSTRING res = screen->InputNumber (0, 30);
			index = res.ToInt();
		} while ((index<0) || (index>=zCParticleFX::s_emitterPresetList.GetNumInList()));
		pfxName = zCParticleFX::s_emitterPresetList[index]->GetParticleFXName();

		// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
		while (zinput->KeyPressed(KEY_PAD_MUL) || zinput->KeyPressed(KEY_BSLASH) || zinput->KeyPressed(KEY_ENTER)) {
			zCView :: GetInput();
			sysEvent();
		};
	};
};

void oCParticleControl::EditActivePFX()
{
	if (!GetPFXVob()) return;
	// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
/*	while (kbPressed(KEY_G)) {
		zCView :: GetInput();
		sysEvent();
	};*/
	if (!zCParticleFX::s_pfxParser) return;
	// Instanz "pfxName" durch Parser-Console editiere
	if (part_edit) delete(part_edit);
	part_edit = zNEW( zCConsole() );
	part_edit -> SetParser(zCParticleFX::s_pfxParser);
	part_edit -> SetPos(0,0);
	part_edit -> EditInstance (pfxName, partFX->GetEmitter());
	// Preset raussuchen, von dem "pfxName" eine Instanz ist
	zCParticleEmitter *preset = zCParticleFX::SearchParticleEmitter (pfxName);
	// Die nun aktuellere Instanz "pfxName" in den Preset zurueckkopieren
	*(preset) = *(partFX->GetEmitter());  
	// Nun die abhängigen Variablen innerhalb der Instanz und des Presets updaten
	preset->UpdateInternals();
	partFX->GetEmitter()->UpdateInternals();
};

void oCParticleControl::SetStartPos(zVEC3 &pos) {
	startpos = pos;
}

void oCParticleControl::StartActivePFX(zCVob *homeVob, zSTRING &node) 
{
	if (!rnd_world) return;

	DeleteLastPFX();

	zCModel *model = (zCModel*)homeVob->GetVisual();
	zCModelNodeInst *mnode = model->SearchNode(node);
	if (mnode) {
		partFX = zNEW( zCParticleFX() );
		pfxVob = zNEW( zCVob() ); 
		pfxVob->SetVobName			("Particle_Test_Vob");
		pfxVob->SetCollDet			(FALSE);
		rnd_world->AddVob			(pfxVob);
		// attach to node
//		zCTree<zCVob> *vobNode = homeVob->GetHomeWorld()->AddVobAsChild (pfxVob, homeVob);
//		model -> AttachChildVobToNode	(vobNode, mnode);
		model -> AttachChildVobToNode	(pfxVob, mnode);
		model -> UpdateAttachedVobs		();
		pfxVob-> SetVisual				(partFX);
		partFX-> SetAndStartEmitter		(pfxName);
		partFX-> SetDontKillPFXWhenDone	(TRUE);
//		pfxVobID = pfxVob->GetVobID		();
	}
}

void oCParticleControl::StartActivePFX() 
{
	if (!rnd_world) return;
	
	DeleteLastPFX();
	
	partFX = zNEW( zCParticleFX() );
	pfxVob = zNEW( zCVob() ); 
	pfxVob->SetVobName			("Particle_Test_Vob");
	pfxVob->SetCollDet			(FALSE);
	pfxVob->Move				(startpos);
	rnd_world->AddVob			(pfxVob);
	pfxVob->SetVisual			(partFX);
	partFX->SetAndStartEmitter	(pfxName);
	partFX->SetDontKillPFXWhenDone	(TRUE);
//	pfxVobID = pfxVob->GetVobID	();
}; 

void oCParticleControl::CreateNewPFX(zSTRING& newPFXName)
{
	// Rename ??
	newPFXName.Upper();
	zoptions->ChangeDir(DIR_SCRIPTS);

	zFILE *file = zfactory->CreateZFile("System\\Pfx\\PfxInst.d");
	file->Open	();
	file->Append	();
	file->Write	(zSTRING("\nINSTANCE "+newPFXName+"(C_PARTICLEFX)\n"));
	file->Write	(zSTRING("{\n"));
	file->Write	(zSTRING("};\n"));
	file->Close	();
	delete (file);

	zCParticleFX::ParseParticleFXScript();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
//		ENDE -	Partikel-Effekt Krempel		ENDE	
////////////////////////////////////////////////////////////////////////////////////////////////////////

// neue Methoden CHANGES ANDRE
//void SetPFXName(zSTRING& newPFXName)
void oCParticleControl::SetPFXName(zSTRING& newPFXName)
{
	pfxName = newPFXName;
	if (partFX) {
		partFX->SetEmitter( zCParticleFX::SearchParticleEmitter (pfxName) );
	}
}

void oCParticleControl::SetWorld(zCWorld* theWorld)
{
	if (GetPFXVob()) { 
		rnd_world->RemoveVob(GetPFXVob()); 
		GetPFXVob()->Release();
		pfxVob=0; 
	};
	rnd_world = theWorld;
}

void oCParticleControl::BeginEditActive(void(*cf)(const zSTRING &s))
{
	if (!GetPFXVob()) return;
	// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
	if (!zCParticleFX::s_pfxParser) return;
	// Instanz "pfxName" durch Parser-Console editieren
	if (part_edit) delete(part_edit);
	part_edit = zNEW( zCConsole() );
	part_edit -> SetParser(zCParticleFX::s_pfxParser);
	part_edit -> SetPos(0,0);
	part_edit -> EditInstance(pfxName, partFX->GetEmitter());
	part_edit -> SetChangedFunc(cf);
}

void oCParticleControl::DeleteLastPFX()
{
	if (pfxVob && pfxVob->GetHomeWorld()) {
		// RefCtr ???!
		if (pfxVob->GetRefCtr()>=2) pfxVob -> GetHomeWorld() -> RemoveVob(pfxVob);
		pfxVob -> Release();
		pfxVob = zNEW( zCVob() );
		partFX = zNEW( zCParticleFX() );
	}
}

void oCParticleControl::UpdateInternals()
{
	// Nun die abhängigen Variablen innerhalb der Instanz und des Presets updaten
	if (partFX) partFX->GetEmitter()->UpdateInternals();
}

void oCParticleControl::EndEditActive()
{
	// Preset raussuchen, von dem "pfxName" eine Instanz ist
	zCParticleEmitter *preset = zCParticleFX::SearchParticleEmitter (pfxName);
	// Die nun aktuellere Instanz "pfxName" in den Preset zurueckkopieren
	*(preset) = *(partFX->GetEmitter());  
	// Nun die abhängigen Variablen innerhalb der Instanz und des Presets updaten
	preset->UpdateInternals();
	partFX->GetEmitter()->UpdateInternals();
}
