// spcCParticleControl
// Andre Schrieber
// 17.12.1998

#include "zengine.h"

#include "spcCParticleControl.h"
#include "zParser.h"
#include "zWorld.h"
#include "zview.h"
#include "zInput_Win32.h"


spcCParticleControl::spcCParticleControl()
: pfxName("a.pfx"), pfxVobID(-1)
{
	partFX=0;
	pfxVob=0;
	rnd_world=0;
	IsInEditMode = false;
}

spcCParticleControl::spcCParticleControl(zCWorld* theWorld)
: pfxName("a.pfx"), pfxVobID(-1)
{
	partFX=0;
	pfxVob=0;
	rnd_world=theWorld;
	IsInEditMode = false;
}

spcCParticleControl::~spcCParticleControl()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//		START	-	Partikel-Effekt Krempel		START	
////////////////////////////////////////////////////////////////////////////////////////////////////////

zCVob* spcCParticleControl::GetPFXVob () {
	if (rnd_world) {
	pfxVob = rnd_world->SearchVobByID (pfxVobID);
	return pfxVob;
	} else return 0;
};


// ANDRE WUP
void spcCParticleControl::SelectActivePFX() {

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
			Cdtp_item :: GetInput();
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
		while (zinput->KeyPressed(KEY_PAD_MUL) || zinput->KeyToggled(KEY_BSLASH) || zinput->KeyToggled(KEY_ENTER)) {
			zCView :: GetInput();
//			sysEvent();
		};
	};
};

void spcCParticleControl::EditActivePFX()
{
	if (!GetPFXVob()) return;
	// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
/*	while (kbPressed(KEY_G)) {
		Cdtp_item :: GetInput();
		sysEvent();
	};*/
	if (!zCParticleFX::s_pfxParser) return;
	// Instanz "pfxName" durch Parser-Console editieren
	// zCParticleFX::pfxParser->EditInstance	(pfxName, partFX->emitter);
	// dumme Schleife, damit die Editerungen auf der Console sichtbar werden
	while (1) { 
//		sysEvent();
		zCView :: GetInput();
		screen		->DrawItems();
		zrenderer	->Vid_Blit();
		if (zinput->KeyPressed(KEY_ESC) || zinput->KeyPressed(KEY_BSLASH)) break; 
	};
	// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
	while (zinput->KeyPressed(KEY_ESC) || zinput->KeyPressed(KEY_BSLASH)) {
		zCView :: GetInput();
//		sysEvent();
	};
	// Preset raussuchen, von dem "pfxName" eine Instanz ist
	zCParticleEmitter *preset = zCParticleFX::SearchParticleEmitter (pfxName);
	// Die nun aktuellere Instanz "pfxName" in den Preset zurueckkopieren
	*(preset) = *(partFX->GetEmitter());  
	// Nun die abhängigen Variablen innerhalb der Instanz und des Presets updaten
	preset->UpdateInternals();
	partFX->GetEmitter()->UpdateInternals();
};

void spcCParticleControl::StartActivePFX() {
	if (!rnd_world) return;
	if (!GetPFXVob()) {
		partFX = new zCParticleFX();
		pfxVob = new zCVob(); 
		pfxVob->SetVobName				("Particle_Test_Vob");
		pfxVob->SetCollDet				(FALSE);
		pfxVob->Move					(0,150,0);
		rnd_world->AddVob				(pfxVob);
		zRELEASE(pfxVob);

		pfxVobID = pfxVob->GetVobID();
	};
	pfxVob->SetVisual			(partFX);
	partFX->SetAndStartEmitter	(pfxName);
}; 

void spcCParticleControl::CreateNewPFX(zSTRING& newPFXName)
{
	// Rename ??
	/*
	newPFXName.Upper();
	zoptions->ChangeDir(DIR_SCRIPTS);

	zFILE* file = zfactory->CreateZFile("System\\Pfx\\PfxInst.d");
	file->Open	();
	file->Append	();
	file->Write	(zSTRING("\nINSTANCE "+newPFXName+"(C_PARTICLEFX)\n"));
	file->Write	(zSTRING("{\n"));
	file->Write	(zSTRING("};\n"));
	file->Close	();
	delete file;

	zCParticleFX::ParseParticleFXScript();*/
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
//		ENDE -	Partikel-Effekt Krempel		ENDE	
////////////////////////////////////////////////////////////////////////////////////////////////////////

// neue Methoden CHANGES ANDRE
//void SetPFXName(zSTRING& newPFXName)
void spcCParticleControl::SetPFXName(zSTRING& newPFXName)
{
	pfxName = newPFXName;
}

void spcCParticleControl::SetWorld(zCWorld* theWorld)
{
	if (GetPFXVob()) 
	{ 
		rnd_world->RemoveVob(GetPFXVob()); 
		zCVob* vob = GetPFXVob();
		zRELEASE(vob);
		pfxVob=0;
	};

	rnd_world = theWorld;
}

void spcCParticleControl::BeginEditActive()
{
	if (!GetPFXVob()) return;
	// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
	if (!zCParticleFX::s_pfxParser) return;
	// Instanz "pfxName" durch Parser-Console editieren
	// FIXME:
	//zCParticleFX::pfxParser->EditInstance	(pfxName, partFX->emitter);
}

void spcCParticleControl::EndEditActive()
{
	// Preset raussuchen, von dem "pfxName" eine Instanz ist
	zCParticleEmitter *preset = zCParticleFX::SearchParticleEmitter (pfxName);
	// Die nun aktuellere Instanz "pfxName" in den Preset zurueckkopieren
	*(preset) = *(partFX->GetEmitter());  
	// Nun die abhängigen Variablen innerhalb der Instanz und des Presets updaten
	preset->UpdateInternals();
	partFX->GetEmitter()->UpdateInternals();
}