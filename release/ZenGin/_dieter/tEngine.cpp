
//   
// File: "tEngine.cpp" 
// 
// kaesiges engine test-programm.

// CLOUDSHADOWS

//#define ZDIETER_MODEL
//#define ZDIETER_MODEL_FACE
//#define ZDIETER_MODEL2
//#define ZDIETER_MODEL_WEAPON 
//#define ZDIETER_NET_TEST 
//#define ZDIETER_TRACERAY 
//#define ZDIETER_PICK_VOB
//#define ZDIETER_POLYSTRIP
//#define ZDIETER_QUADMARK 
//#define ZDIETER_PROGMESH

//
#include <Crtdbg.h>
#include <malloc.h>

//
#include <zEngine.h> 

//
#include <zWin32.h>
#include <zInput_Win32.h>
#include <zVideo_Win32.h>

// 
#include <fstream.h>
#include <iostream>

//
#include <zMoving.h>

//
#include <zParticle.h>
#include <zArchiver.h>
#include <zAIPlayer.h>
#include <zTypes3D.h>
#include <zBVolume.h>
#include <zRenderManager.h>

#include <zWayNet.h>
#include <zBuffer.h>

#include <zEventMan.h>
#include <zVobMisc.h>

#include <zPolyStrip.h>
#include <zProgMesh.h>
#include <zThread.h>
#include <zViewProgressBar.h>

#include <zRndD3D.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

#include <zRenderLightContainer.h>

#ifdef DEBUG_HILDEBRANDT
	#include <zAIArrow.h>
#endif
 
#pragma warning( disable : 4305 )  

zBOOL			LOAD_MATLIB				= FALSE;
zBOOL			SAVE_AFTER_COMPILE		= TRUE;
zREAL			BSP_OPTIMIZE			= 0.2F;
zBOOL			DEFAULT_TEXTURING		= FALSE;
zBOOL			QUAKE_BSP_READ_LIGHTS	= FALSE;

zSTRING			pfxName("");
zSTRING			BASE_NAME; 

zVEC3			freelookOffset			(00,80,-300);

//extern zDWORD bspCollectCtr;
extern int tr_numLeafs;
extern int tr_numLeafPolys;
extern int tr_numLeafVobs;
extern int tr_numLeafVobsSkip;
zREAL foundHeight = 0;

// =======================================================================================================================

//TRING worldMeshName= "world.zen";						zTBspTreeMode bspTreeMode = zBSP_MODE_OUTDOOR;
//zSTRING worldMeshName = "spacer_checklist\\spacer_checklist_outdoor_new.zen"; zTBspTreeMode bspTreeMode = zBSP_MODE_OUTDOOR;
zSTRING worldMeshName = "newworld\\newworld.zen"; zTBspTreeMode bspTreeMode = zBSP_MODE_OUTDOOR;
//zSTRING worldMeshName = "testlevel\\testlevel.zen"; zTBspTreeMode bspTreeMode = zBSP_MODE_INDOOR;
//zSTRING worldMeshName = "newworld_part_city_01.zen"; zTBspTreeMode bspTreeMode = zBSP_MODE_OUTDOOR;
//zSTRING worldMeshName = "wassertestlevel.zen"; zTBspTreeMode bspTreeMode = zBSP_MODE_OUTDOOR;

//zSTRING worldMeshName = "surface.zen"; zTBspTreeMode bspTreeMode = zBSP_MODE_OUTDOOR;


// =======================================================================================================================

#ifdef ZDIETER_PICK_VOB
	// PickVob 
	zCVob		*pickVob=0,*tmpVob=0;
	zCPolygon	*pickedPoly=0, *oldPoly = 0;
	zCMaterial	*oldMat=0;
	zCMaterial *markerMat= 0;
#endif

// =======================================================================================================================

class zCAITest : public zCAIBaseSound {
//class zCAITest : public zCAIBase {
	zCVob *aiVob;
	void	DoAI					(zCVob* vob, zBOOL& vobDeleted) { 
//		return;
		aiVob= vob;
		CheckSlideSound(aiVob);
		screen->Print (0,5000, "NIUB"); 
/*		if (vob->GetGroundPoly()) {
			zCMaterial *mat = vob->GetGroundPoly()->GetMaterial();
			screen->Print (0,5200, zSTRING(int(mat->GetBspSectorFront())) +", "+zSTRING(int(mat->GetBspSectorBack()))+
				", leafs: "+zSTRING(int(vob->vobLeafList.GetNumInList()))); 
		};*/
//		if (vob->GetVelocity().Length2()<(50*50)) {
		if (!vob->GetPhysicsEnabled()) {
			// ai abschalten, wenn Objekt fast im Stillstand
			vob->SetAI			(0); 
			vob->SetSleeping	(TRUE);
			return;
		};
	};
	void ReportCollisionToAI (const zCCollisionReport& collisionReport) {
		StartDefaultCollisionSound(aiVob, collisionReport);
	};
public:
	zCAITest() {aiVob=0;};
protected:
	~zCAITest() {};
};


void GameLoop();



int MainProg(VOID)
{

	zCEngine *zengine = zNEW(zCEngine);
	
	zengine->Init(&(zTSystemContextHandle(hWndApp)));

	//
	if (zinput->KeyPressed(KEY_LCTRL)) 
	{
		zerr.Message ("D: ..silent..");
//		zerr.SetOutputLevel (zERR_WARN);
	};

	GameLoop						();
									
	zerr.ShowSpy					(FALSE); 
	zengine->Shutdown				();
	delete zengine; zengine=0;

//	file.close();
 	return(1);
} 
 

extern int			vobsConsidered;
extern int			vobsAdded;

static int			minPacketSize = 9999999;
static int			maxPacketSize =-9999999;

//zBOOL				usrWantQuit		= FALSE;
zCParticleFX		*partFX=0;

zBOOL				followCam		= FALSE;
zBOOL				showEngineStats	= FALSE;

zCModelPrototype	*modelProto = 0;
zCModel				*model		= 0;
zCModel				*model2		= 0;
zCMorphMesh			*face		= 0;

zCMoveRecorder		zrecorder;
zCCamera			*camera	= 0; 
zCWorld				*world	= 0;
zCVob				*vob	= 0;
zCVob				*vobm2	= 0;
//zCVob				*vobm2	= 0;
zCVob				*vobm1	= 0;
zCVob				*vobm0	= 0;
zCVob				*pfxVob	= 0;
zCVob				*moveVob;  
zCVob				*camVob;
zCView				*textv;
int					showInfo = 1;
zCVob				*levelVob;
CMov_Movement		*mov	= 0;
zCPolygon			*poly;
zCVobLight			*light; 
zCTrigger			*trigger=0;
zCMover				*mover=0;

zCVob				*vobSubtree	= 0;

//zCVobLight		*playerLight;
zCAIPlayer			*playerAI	= 0;
//zCAIDummy			*dummyAI	= zNEW(zCAIDummy); 
					
zREAL				timeStep	= -1;
zBOOL				singleStep	= FALSE;

zCPolyStrip			*streak			= 0;
zCVob				*vobStreak		= 0;
zCLightning			*lightning		= 0;
zCVob				*vobLightning	= 0;
#ifdef ZDIETER_PROGMESH
zCProgMeshProto		*pmProto		= 0;
#endif

class zCVobCallback_StatsCounter : public zCVobCallback {
public:
	 zCVobCallback_StatsCounter() { numVobsWithParent=numVobsWithName=numVobsTotal=numParentsMax=numParentsSum=0; };
	~zCVobCallback_StatsCounter() { };

	int		numVobsWithParent;
	int		numVobsWithName;
	int		numVobsTotal;

	int		numParentsMax;
	int		numParentsSum;

	virtual void HandleVob(zCVob* vob, void *callbackData) 
	{
		numVobsTotal++;
		if (vob->HasParentVob())				numVobsWithParent++;
		if (vob->GetObjectName().IsEmpty())		numVobsWithName++;

		zCVob	*testVob		= vob;
		int		numParents		= 0;
		while (testVob->HasParentVob())
		{
			numParents++;
			testVob	= testVob->globalVobTreeNode->parent->data;
		};
		if (numParents>4)
		{
			zERR_MESSAGE (3, 0, "D: numParents>4: "+vob->GetVobName());
		};
		numParentsSum	+= numParents;
		numParentsMax	= zMax (numParentsMax, numParents);
	};
};

static void Freelook (zCVob* camVob, zCVob* moveVob) 
{
	static zBOOL freelookEnabled = FALSE;
	
	const float X_SCALE = 2;
	const float Y_SCALE = 2;
	
	if (zinput->KeyToggled(KEY_F))	
	{
		freelookEnabled				= !freelookEnabled;
		zinput->SetDeviceEnabled	(zINPUT_MOUSE, freelookEnabled);
	};
	if (!freelookEnabled)			return;

 	zREAL dx, dy, dz;
	zinput->GetMousePos (dx, dy, dz);

	if ((camVob!=moveVob) && (model)) {
		// Model Movement Freelook
		if (dx) moveVob->RotateWorld	(0,1,0, float(dx)/X_SCALE);

		//
		camVob->BeginMovement();
		if (dy) camVob->RotateLocalX	(float(dy)/Y_SCALE);

		zREAL freelookLen		= freelookOffset.Length();
		zVEC3 ray				= (camVob->GetPositionWorld() - moveVob->GetPositionWorld()).Normalize();
		ray						= ray * freelookLen;
		zBOOL hit				= world->TraceRayNearestHit (moveVob->GetPositionWorld(), ray, (zCVob*)0, zTRACERAY_VOB_IGNORE);
		ray.Normalize			();
		if (hit) {
			zREAL len					= (world->traceRayReport.foundIntersection - moveVob->GetPositionWorld()).Length();
			len							= (len-10.0F) / freelookLen;
			camVob->SetPositionWorld	(moveVob->GetPositionWorld());
			camVob->MoveLocal			(freelookOffset * len);
		} else {
			camVob->SetPositionWorld	(moveVob->GetPositionWorld());
			camVob->MoveLocal			(freelookOffset);
		};
		camVob->EndMovement();
	} else {
		if (dx) camVob->RotateWorld		(0,1,0, float(dx)/X_SCALE);
		if (dy) camVob->RotateLocalX	(float(dy)/Y_SCALE);
	};
};


static void InsertModel (zPOINT3 pos) {
	zCVob		*newVob		= zNEW(zCVob);
	zCModel		*newModel;
	zCAITest	*ai			= zNEW(zCAITest);
	newVob->SetAI			(ai);
	newVob->SetPositionLocal(pos);
	//newVob->SetVisual		("humanS.mds");	newVob->SetSleeping (FALSE); 
	newVob->SetVisual		("dragon.mds");	newVob->SetSleeping (FALSE); 
	newVob->SetCollDet		(FALSE);
//	newVob->SetAICallback	(playerAI);
	newModel				= (zCModel*)(newVob->GetVisual());
//	newModel->SetModelMesh	("Skeleton");
	world->AddVobRelease	(newVob);
//	newVob->SetSleepingMode	(zVOB_AWAKE_DOAI_ONLY);
//	newVob->SetSleeping		(FALSE);
	newVob->SetSleepingMode	(zVOB_AWAKE);
	zRELEASE (ai);
};

static void PushVob (zCVob *vob) {
	vob->SetSleeping						(FALSE);
	vob->SetPhysicsEnabled					(TRUE);
	vob->GetRigidBody()->SetGravityEnabled	(TRUE); 
	vob->GetRigidBody()->ApplyForceCM		(moveVob->GetAtVectorWorld()*1000); 
};
 
static void ThrowVob() 
{
#ifdef DEBUG_HILDEBRANDT
	zCAIArrow	*aiArrow	= zNEW(zCAIArrow);
	zCVob		*shootVob	= moveVob;
//	zCVobLight	*vob		= zNEW(zCVobLight);
	zCVob		*vob		= zNEW(zCVob);
	vob->SetVisual					("ITAM_ARROW_01.3DS");	  
	vob->SetAICallback				(aiArrow);
//	vob->SetCollisionClass			(zCCollObjectPoint::S_GetCollObjClass());
	vob->SetCollisionClass			(zCCollObjectProjectile::S_GetCollObjClass());

	vob->SetVobName					("Throwed-Vob");
//	vob->SetDrawBBox3D				(TRUE);
//	vob->SetPositionWorld			(shootVob->GetPositionWorld());
//	vob->SetRange					(1000);
//	vob->SetColor					(100,100,255);
	world->AddVobRelease			(vob);

	aiArrow->SetupAIVob				(vob, shootVob);

	vob->SetSleeping				(FALSE);
	vob->SetCollDetStat				(TRUE);
	vob->SetCollDetDyn				(TRUE);
#endif
};

static void ThrowVob2() {
	zCVob		*shootVob	= moveVob;
	zCVob		*vob		= zNEW(zCVob);
	zCAITest	*testAI		= zNEW(zCAITest);
	vob->SetAICallback					(testAI);
//	vob->SetVisual						("OC_LOB_BOWTRAIN.3DS");	  
//	zerr.Message ("D: volume: "+zSTRING(vob->GetBBox3DLocal().GetVolume()));
//	vob->SetVisual						("kugel2m.3ds");	  
//	vob->SetVisual						("sword.3ds");	 
//	vob->SetVisual						("_dieter\\VobBox.3ds");	 
//	vob->SetVisual						("IT_W_2HA_GREATAXE.3DS");
	vob->SetVisual						("nw_nature_bush_25p.3DS");

	
//	vob->SetVisual						("campfire.3ds");	 
//	vob->SetVisual						("tree.3ds");	 
	vob->GetRigidBody()->SetMass		(15);
//	zerr.Message ("D: volume: "+zSTRING(vob->GetBBox3DLocal().GetVolume()));

	vob->SetVobName						("Throwed-Vob-2");
//	vob->SetDrawBBox3D					(TRUE);
//	vob->SetPositionWorld				(shootVob->GetPositionWorld());
	world->AddVobRelease				(vob);

/*
	vob->SetSleeping					(FALSE);
	vob->SetPhysicsEnabled				(TRUE);
	vob->SetTrafoObjToWorld				(shootVob->trafoObjToWorld);
	vob->SetPositionWorld				(shootVob->GetPositionWorld() + shootVob->GetAtVectorWorld()*100);
//	vob->trafo.SetAtVector				(shootVob->GetAtVectorWorld());
//	vob->trafo.MakeOrthonormal			();
	zVEC3 force	=						shootVob->GetAtVectorWorld();
//	zVEC3 force	=						(shootVob->GetAtVectorWorld() + 0.7F*shootVob->GetUpVectorWorld()).Normalize();
//	zVEC3 force	=						zVEC3(1,0,0);
//	vob->RigidBody()->ApplyForceCM		(3000*force);
	vob->RigidBody()->SetVelocity		(500*force);
	vob->SetCollDetStat					(TRUE);
	vob->SetCollDetDyn					(TRUE);
*/

    // 6) Ausgangsposition herstellen
	zCVob *inVob = vob;
    inVob->SetCollDet               (FALSE);
    inVob->ResetRotationsWorld		();
    inVob->SetPositionWorld			(shootVob->GetPositionWorld() + shootVob->GetAtVectorWorld()*100);
    inVob->SetCollDet               (TRUE);
    inVob->SetSleeping              (FALSE);
    
    // 7) Geschwindigkeit einsetzen
	zREAL angle = 0;
    zMATRIX4 trafo          = shootVob->trafoObjToWorld * Alg_Rotation3DN ( zVEC3(1,0,0), -angle);
    zVEC3    direction      = trafo.GetAtVector() + zVEC3(0,1.5F,0);
	direction.Normalize();
    
    inVob->SetPhysicsEnabled					(TRUE);
    inVob->GetRigidBody()->SetGravityEnabled	(TRUE);
    inVob->GetRigidBody()->SetVelocity			(direction * 500.0F);

	//
	zRELEASE (testAI);
};

static void ThrowVob (zSTRING vis, zREAL mass, zCCollisionObjectDef *collObjDef=0) {
	zCVob		*shootVob	= moveVob;
	zCVob		*vob		= zNEW(zCVob);
	zCAITest	*testAI		= zNEW(zCAITest);
	vob->SetAICallback					(testAI);
//	vob->SetVisual						("_dieter\\kugel1m.3ds");	 
//	vob->SetVisual						("sml_table.3ds");
//	vob->SetVisual						("barrel_2.3ds");	 
	vob->SetVisual						(vis);	 
	vob->GetRigidBody()->SetMass		(mass); 
	if (collObjDef)
		vob->SetCollisionClass			(collObjDef);
	else
		vob->SetCollisionClass			(zCCollObjectComplex::S_GetCollObjClass());

	vob->SetVobName						("Throwed-Vob-3: "+vis);
//	vob->SetDrawBBox3D					(TRUE);
//	vob->SetPositionWorld				(shootVob->GetPositionWorld());
	world->AddVobRelease				(vob);

	vob->SetSleeping					(FALSE);
	vob->SetPhysicsEnabled				(TRUE);
	vob->SetTrafoObjToWorld				(shootVob->trafoObjToWorld);
	vob->SetPositionWorld				(shootVob->GetPositionWorld() + shootVob->GetAtVectorWorld()*300);
	zVEC3 force	=						shootVob->GetAtVectorWorld();
//	vob->GetRigidBody()->SetVelocity	(500*force);
	vob->GetRigidBody()->SetVelocity	(200*force);
	vob->SetCollDetStat					(TRUE);
	vob->SetCollDetDyn					(TRUE);

	zRELEASE (testAI);
};

static void CreateLight () 
{
//	zCVob		*shootVob	= moveVob;
	zCVobLight	*light		= zNEW(zCVobLight);
	light->SetVobName					("created_light");
//
	if (zinput->KeyPressed (KEY_LALT))
	{
		light->SetLightType					(zVOBLIGHT_TYPE_SPOT);
		light->lightData.SetSpotConeAngle	(20.0F);
	};
	if (zinput->KeyPressed(KEY_LSHIFT))	light->SetRange	(3000);
	else								light->SetRange	(1500);
	light->SetColor						(255,255,255);
	light->SetIsStatic					(TRUE);
//	light->lightData.rangeAniScaleList.Insert (1.00);
//	light->lightData.rangeAniScaleList.Insert (0.99); 
//	light->SetRangeAniSmooth			(FALSE);
//	light->SetRangeAniFPS				(1);
	light->SetPositionLocal				(camVob->GetPositionWorld());
	light->SetTrafoObjToWorld			(camVob->trafoObjToWorld);
	world->AddVobRelease				(light);

//	light->SetRange (10);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
//		START	-	Partikel-Effekt Krempel		START	
////////////////////////////////////////////////////////////////////////////////////////////////////////

zCVob* GetPFXVob () {
	return pfxVob;
};

void SelectActivePFX() {
	if (zCParticleFX::s_emitterPresetList.GetNum()<=0) return;

	// Die "zCParticleFX::s_emitterPresetList" wird auf dem Bildschirm ausgegeben.
	// Der User w�hlt die Nummer eines Presets
	// output: "pfxName", der Name des gew�hlten PFX-Presets

	if (pfxVob) {
		pfxVob->RemoveVobFromWorld	();
		zRELEASE (pfxVob);
	};

	pfxName = "ZWATERRING.PFX";
	return;

	// beide Frame-Buffer loeschen (front & back)
	{
		zinput->ClearKeyBuffer	();
		for (int i=0; i<2; i++) 
		{
			zCOLOR col (0,0,0,255);
			zrenderer->Vid_Clear			(col); 
			zrenderer->Vid_BeginLfbAccess	();						
//			screen->SetFont (zSTRING("font_Roman8.fon"));
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
			zrenderer->Vid_EndLfbAccess	(); 
			zrenderer->Vid_Blit			();
		};
		int index;
		do {
			zSTRING res = screen->Input			(0,7500, 2000, zSTRING(""));
			index		= res.ToInt();
//			zrenderer ->Vid_Blit	();
		} while ((index<0) || (index>=zCParticleFX::s_emitterPresetList.GetNumInList()));
		pfxName = zCParticleFX::s_emitterPresetList[index]->GetParticleFXName();

		// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
		zinput->ClearKeyBuffer	();
//		screen->SetFont (zSTRING("font_0.fon"));
	};
};

void EditActivePFX()
{
	if (!GetPFXVob()) return;
	// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
	zinput->ClearKeyBuffer	();
	if (!zCParticleFX::s_pfxParser) return;
	// Instanz "pfxName" durch Parser-Console editieren

	{
//		zCParticleFX::pfxParser->EditInstance	(pfxName, partFX->emitter);
		zCConsole *edit_con = zNEW(zCConsole);
		edit_con -> SetPos		(0,0);
		edit_con -> SetParser	(zCParticleFX::s_pfxParser);
		edit_con -> EditInstance( pfxName, partFX->GetEmitter() );
//		edit_con -> SetChangedFunc ( cf );  // Wenn n�tig
//		edit_con -> AddEvalFunc ( ef ); // Wenn n�tig

	};

	// dumme Schleife, damit die Editerungen auf der Console sichtbar werden
	while (1) { 
		sysEvent();
		zCView :: GetInput();
		zrenderer	->Vid_BeginLfbAccess();						
		screen		->DrawItems			();
		zrenderer	->Vid_EndLfbAccess	();						
		zrenderer	->Vid_Blit			();
		if (zinput->KeyPressed(KEY_ESC) || zinput->KeyPressed(KEY_BSLASH)) break; 
	};
	// sichergehen, dass folgende Tasten auch wieder losgelassen wurden...
	while (zinput->KeyPressed(KEY_ESC) || zinput->KeyPressed(KEY_BSLASH)) {
		zCView :: GetInput();
		sysEvent();
	};
	// Preset raussuchen, von dem "pfxName" eine Instanz ist
	zCParticleEmitter *preset = zCParticleFX::SearchParticleEmitter (pfxName);
	// Die nun aktuellere Instanz "pfxName" in den Preset zurueckkopieren
	*(preset) = *(partFX->GetEmitter());  
	// Nun die abh�ngigen Variablen innerhalb der Instanz und des Presets updaten
	preset->UpdateInternals();
	partFX->GetEmitter()->UpdateInternals();
};

void StartActivePFX() {
	if (!GetPFXVob()) {
		partFX = zNEW(zCParticleFX);
		pfxVob = zNEW(zCTouchDamage); 
		pfxVob->SetVobName				("Particle_Test_Vob");
		pfxVob->SetCollDet				(FALSE);
		pfxVob->Move					(0,150,0);
		world->AddVob					(pfxVob);

		{
			zCTouchDamage *dam			= (zCTouchDamage*)pfxVob;
			dam->SetDamage				(10);
			dam->SetDamageType			(1);
			dam->SetDamageCollType		(zCTouchDamage::CT_BOX);
			dam->SetDamageVolDownScale	(0.5F);
			dam->SetDamageRepeatDelaySec(1.0F);
		};

	};
	if (pfxVob->GetHomeWorld()!=world) {
		world->AddVob (pfxVob);
	};
//	pfxVob->SetPositionWorld	(intro->hotSpot()+zVEC3(0,0,0));
	pfxVob->SetPositionWorld	(zVEC3(0,100,0));

	pfxVob->SetVisual			(partFX);
	partFX->SetDontKillPFXWhenDone	(TRUE);
	partFX->SetAndStartEmitter	(pfxName);
}; 

void CreateNewPFX(zSTRING& newPFXName)
{
/*	// Rename ??
	newPFXName.Upper();
	zoptions->ChangeDir(DIR_SCRIPTS);

	zFILE file("System\\Pfx\\PfxInst.d",zDSK_BIN);
	file.Open	();
	file.Append	();
	file.Write	(zSTRING("\nINSTANCE "+newPFXName+"(C_PARTICLEFX)\n"));
	file.Write	(zSTRING("{\n"));
	file.Write	(zSTRING("};\n"));
	file.Close	();

	zCParticleFX::ParseParticleFXScript();
*/
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
//		ENDE -	Partikel-Effekt Krempel		ENDE	
////////////////////////////////////////////////////////////////////////////////////////////////////////

int MOVE = 50;

static void GetInput(zCVob& invob, CMov_Movement* mov) 
{
	//
	mov->Movement	();
	mov->vob			= &invob;

	// Single Step
	{
		if (zinput->KeyToggled(KEY_F9)) {
			singleStep = !singleStep;
			timeStep = 0.0;
		};
		if (singleStep) {
			timeStep = 0;
			if (zinput->KeyToggled(KEY_F12)) timeStep = (1.0F / 25.0F);
			if (zinput->KeyToggled(KEY_F11))  {
				timeStep = (1.0F / 25.0F);
				zerr.Message ("D: step");
			};
		} else
			timeStep = -1;
	};

	// Ani transition tests
	{ 
		if (zinput->KeyToggled(KEY_F10)) {
			static int	   iActAni = 0;
			static zSTRING anis[4];

			if (anis[0].IsEmpty())
			{
				anis[0] = "S_RUN";
				anis[1] = "S_WALK";
				anis[2] = "S_SNEAK";
				anis[3] = "S_SWIM";
			}
			zCModel *moveModel = (zCModel*)vobm2->GetVisual();
			//moveModel->StopAni(moveModel->GetAniFromAniName(anis[iActAni]));
			iActAni++; if (iActAni>=4) iActAni=0;

			moveModel->StartAni(moveModel->GetAniFromAniName(anis[iActAni]));
		};
	}
	if (zinput->KeyToggled(KEY_O)) {
//		zREAL radius = zREAL(500.0F);
//		camera->AddTremor (moveVob->GetPositionWorld(), radius*radius, 2000.0F, zVEC3(0,120,0));
//		zCBspLeaf *leaf = world->GetBspTree()->FindLeaf (camVob->GetPositionWorld());
//		camVob->SetPositionWorld (leaf->bbox3D.GetCenter());

/*		zCVobCallback_StatsCounter statsCounter;
		world->TraverseVobTree (statsCounter);
		zerr.Message ("D: *********************************************************");
		zerr.Message ("D: numVobsTotal: "+zSTRING(statsCounter.numVobsTotal));
		zerr.Message ("D: numVobsWithName: "+zSTRING(float(((float)statsCounter.numVobsWithName)/(float)statsCounter.numVobsTotal),2));
		zerr.Message ("D: numVobsWithParent: "+zSTRING(float((float)statsCounter.numVobsWithParent/(float)statsCounter.numVobsTotal),2));
		zerr.Message ("D: numParentsMax: "+zSTRING(statsCounter.numParentsMax));
		zerr.Message ("D: numParentsAvgPerVob: "+zSTRING(float((float)statsCounter.numParentsSum/(float)statsCounter.numVobsTotal),2));
		zerr.Message ("D: *********************************************************");
*/
//		zCProgMeshProto::SetAutoSubdivEnabled(!zCProgMeshProto::GetAutoSubdivEnabled());

		{
			zCModelConvertFileHandler		modelConvert;
			zCMorphMeshConvertFileHandler	morphMeshConvert;
			zCProgMeshConvertFileHandler	pmeshConvert;

			dirScanner.RegisterFileHandler	(&modelConvert		, "zCModel");
//			dirScanner.RegisterFileHandler	(&morphMeshConvert	, "zCMorphMesh");
//			dirScanner.RegisterFileHandler	(&pmeshConvert		, "zCProgMeshProto");

//			dirScanner.Scan					(zoptions->GetDirString(DIR_MESHES));
			dirScanner.Scan					(zoptions->GetDirString(DIR_ANIMS));
//			dirScanner.Scan					(zoptions->GetDirString(DIR_DATA));
		};

	};

	// 
	if (zinput->KeyPressed(KEY_Z)) {
#if 0
		if (mover) {
			if (zinput->KeyPressed(KEY_LSHIFT)) {
				static int index = 0;
				mover->SetToKeyframe	((zREAL)index,+0);
				zerr.Message			("D: Set to keyframe: "+zSTRING(index));
				index++;
				if (index>=mover->keyframeList.GetNum()) index=0;
			} else
			if (zinput->KeyPressed(KEY_LCTRL)) {
//				mover->SetSleeping	(!mover->GetSleeping());
				
				mover->OnTrigger	(0);

/*				if (model) {
					vobm2->SetSleeping (FALSE);
					static zBOOL t=FALSE;
					if (t)		model->StartAni (zSTRING("T_OPEN_2_CLOSED"));
					else		model->StartAni (zSTRING("T_CLOSED_2_OPEN"));
					t = !t;
				};
*/
			}
			else {
				zerr.Message ("D: added keyframe, num: "+zSTRING(mover->keyframeList.GetNum()));
				zCMover::zTMov_Keyframe key;
				key = mover->GetKeyframe	(mover);
				mover->keyframeList.Insert	(key);
			};
		};
#endif

	};
 
	// MOVEMENT
	if (zinput->KeyPressed(KEY_ESC))	usrWantQuit = TRUE; 
	if (zinput->KeyToggled(KEY_I))		showInfo = (showInfo+1)%3;

	if (zinput->KeyToggled(KEY_R))		
	{
		if (!zinput->KeyToggled(KEY_LSHIFT))		
		{
			invob.ResetXZRotationsWorld();
		}
		else
		{
			invob.ResetXZRotationsLocal();
		};
	};

	if (zinput->KeyToggled(KEY_J)) 
	{
//		zCVob *vob = world->MergeVobSubtree (zSTRING("FIRETREE_SMALL.ZEN"), 0, zCWorld::zWLD_LOAD_MERGE_ADD);
//		vob->SetPositionWorld (camVob->GetPositionWorld());
		zREAL strength = zCProgMeshProto::GetLODParamStrengthModifier ();
		const zREAL D= zREAL(0.01F);
		if (zinput->KeyPressed(KEY_LSHIFT)) 
		{
			strength	-= D;
		} else
		{
			strength	+= D;
		};
		zCProgMeshProto::SetLODParamStrengthModifier (strength);
		zERR_MESSAGE (1, 0, "D: LOD modifier: "+zSTRING(strength,3));
	};

	if (zinput->KeyToggled(KEY_F1))	{
		zcon.Toggle();
	};

	if (zinput->KeyToggled(KEY_F2))	{
		zCWorld::SetFadeOutFarVertices(!zCWorld::GetFadeOutFarVertices());
	};

	
	if (zinput->KeyToggled(KEY_T))
	{
		if (zinput->KeyPressed(KEY_LSHIFT))		
			showEngineStats = !showEngineStats;
		else {
			zCRenderManager::SetUseRendererTNL (!zCRenderManager::GetUseRendererTNL());
			zERR_MESSAGE (0,0, "D: TNL enabled: "+zSTRING(zCRenderManager::GetUseRendererTNL()));
//			zCProgMeshProto::SetAutoSubdivEnabled(!zCProgMeshProto::GetAutoSubdivEnabled());
//			zCRenderManager::S_SetDetailTexturesEnabled (!zCRenderManager::S_GetDetailTexturesEnabled());
		};
	};

	if (zinput->KeyToggled(KEY_N))		{
		world->SetDrawVobBBox3D (!world->GetDrawVobBBox3D());
		if (!world->GetDrawVobBBox3D ())	zCVobLight::SetRenderLightVisuals (FALSE);
		else
		if (zinput->KeyPressed(KEY_LSHIFT))		
			zCVobLight::SetRenderLightVisuals (TRUE);

//		zCVobLight::SetRenderLightVisuals (!zCVobLight::GetRenderLightVisuals());
	};

	if (zinput->KeyPressed(KEY_LSHIFT)) 
	if (zinput->KeyPressed(KEY_S)) {
//		world->SaveWorld (BASE_NAME+"_SAVE.zen", zCWorld::zWLD_SAVE_EDITOR_UNCOMPILED);
		world->SaveWorld (BASE_NAME+"_SAVE.zen", zCWorld::zWLD_SAVE_EDITOR_COMPILED, TRUE);	// binary!
//		world->SaveWorld ("oldcamp_NoVob.zen", zCWorld::zWLD_SAVE_COMPILED_ONLY, FALSE);	// ASCII
	};

		if (zinput->KeyPressed(KEY_GREYPLUS)) 
		{
			playerLightInt += 100; 
			zerr.Message ("D: LightInt: "+zSTRING(playerLightInt));
		} else
		if (zinput->KeyPressed(KEY_GREYMINUS)) 
		{
			playerLightInt -= 100; 
			zerr.Message ("D: LightInt: "+zSTRING(playerLightInt));
		};



	/*if (zinput->KeyPressed(KEY_LSHIFT)) 
	{
		if (zinput->KeyToggled(KEY_GREYPLUS)) 
		{
			world->GetActiveSkyControler()->SetFarZScalability(world->GetActiveSkyControler()->GetFarZScalability()+0.01F);
		} else
		if (zinput->KeyToggled(KEY_GREYMINUS)) 
		{
			world->GetActiveSkyControler()->SetFarZScalability (world->GetActiveSkyControler()->GetFarZScalability()-0.01F);
		};
	} else 
	{
		if (zinput->KeyPressed(KEY_GREYPLUS)) 
		{
			playerLightInt += 100; 
			zerr.Message ("D: LightInt: "+zSTRING(playerLightInt));
		} else
		if (zinput->KeyPressed(KEY_GREYMINUS)) 
		{
			playerLightInt -= 100; 
			zerr.Message ("D: LightInt: "+zSTRING(playerLightInt));
		};
	};*/

	if (zinput->KeyPressed(KEY_0)) { 
		zBOOL f1,f2;
		if (zinput->KeyPressed(KEY_LSHIFT)) {
			if (camVob!=vobm0) {
				f1 = camVob->GetCollDetStat();	f2 = camVob->GetCollDetDyn();
				camVob->SetPositionWorld	((vobm0->GetPositionWorld()));
				camVob->SetHeadingAtWorld	(vobm0->GetAtVectorWorld());
				camVob->SetCollDetStat		(f1);	camVob->SetCollDetDyn (f2);
			};
		}
		else {
			f1 = vobm2->GetCollDetStat();	f2 = vobm2->GetCollDetDyn();
			vobm2->SetCollDet		(FALSE);
			vobm2->SetPositionWorld	(camVob->GetPositionWorld());
			vobm2->SetHeadingAtWorld(camVob->GetAtVectorWorld());
			vobm2->SetCollDetStat	(f1);	vobm2->SetCollDetDyn (f2);
		};
	};

	////////////

	// Load/Save Vob Positions
	{
		if (zinput->KeyToggled(KEY_8)) 
		{
			zoptions->ChangeDir (DIR_DATA);
			if (zinput->KeyPressed(KEY_LSHIFT)) 
			{
				zerr.Message						("D: Saving Model-Vob...");
				zCArchiver *arc						= zarcFactory.CreateArchiverWrite ("moveVob.zen", zARC_MODE_ASCII);
				arc->WriteObject					(vobm2);
				arc->Close							();
				zRELEASE							(arc);
			} else {
				zCVob::SetIgnoreVisuals				(TRUE);
				zerr.Message						("D: Loading Model-Vob...");
				zCArchiver *arc						= zarcFactory.CreateArchiverRead ("moveVob.zen");
				if (arc) {
					arc->ReadObject						(vobm2);
					vobm2->GetRigidBody()->StopTransRot	();
					vobm2->SetPhysicsEnabled			(FALSE);
					if (vobm2->GetVisualClass()==zCModel::GetStaticClassDef())
						((zCModel*)vobm2->GetVisual())->StartAni ("S_RUN");
					zCVob::SetIgnoreVisuals				(FALSE);
					arc->Close							();
					zRELEASE							(arc);
				};
			};
		};
		if (zinput->KeyToggled(KEY_9)) { 
			zoptions->ChangeDir (DIR_DATA);
			if (zinput->KeyPressed(KEY_LSHIFT)) 
			{
				zerr.Message						("D: Saving Camera-Vob...");
				zCArchiver *arc						= zarcFactory.CreateArchiverWrite ("camVob.zen", zARC_MODE_ASCII);
				arc->WriteObject					(vob);
				arc->Close							();
				zRELEASE							(arc);
			} else {
				zerr.Message						("D: Loading Camera-Vob...");
				zCArchiver *arc						= zarcFactory.CreateArchiverRead ("camVob.zen");
				if (arc) {
					arc->ReadObject						(vob);
					arc->Close							();
					zRELEASE							(arc);
				};
			};
		};
	};

	// Switch active cam/move-Vob
	{
		if (zinput->KeyToggled(KEY_ENTER)) {
			if (camVob==vob)	camVob = vobm0; 
			else				camVob = vob;
			camera->SetVob (camVob);
			if (zinput->KeyPressed(KEY_LSHIFT)) followCam=TRUE; else followCam=FALSE;
		};
		if (zinput->KeyToggled(KEY_SPACE)) { 
			if (zinput->KeyPressed(KEY_LSHIFT)) {
				if (GetPFXVob()) {
					if (moveVob==pfxVob)	moveVob=vob;
					else					moveVob=pfxVob;
				};
			} else {
				if (moveVob == vob) {
					moveVob = vobm2; 
					if (model) vobm2->SetAICallback (playerAI);
				} else {
					moveVob = vob;
					if (model) vobm2->SetAICallback (0);
				};
			};
			zerr.Message ("D: Changed Vob for movement: "+moveVob->GetVobName());
		};
	};
	{
		if (zinput->KeyToggled(KEY_F3)) {
			static zBOOL f = (zrenderer->Vid_GetScreenMode()==zRND_SCRMODE_FULLSCREEN);
			f = !f;
			if (f)	zrenderer->Vid_SetScreenMode (zRND_SCRMODE_FULLSCREEN);
			else	zrenderer->Vid_SetScreenMode (zRND_SCRMODE_WINDOWED);
		} 
	};

	// pfx
	{
		if (zinput->KeyPressed(KEY_PAD_DIV)) {
			// start
			StartActivePFX();
		};
		if (zinput->KeyPressed(KEY_PAD_MUL)) {
			if (zinput->KeyPressed(KEY_LSHIFT)) {
				// select
				SelectActivePFX	();
				StartActivePFX	();
			} else
				// edit
				EditActivePFX	();
		};
	};

/*	if (zinput->KeyPressed(KEY_S)) {
		world->PrintStatus();
		if (zinput->KeyPressed(KEY_LSHIFT))
			world->PrintGlobalVobTree();
	};*/

	// Camera-Overrides: drawMode
	if (zinput->KeyPressed(KEY_1)) {
		zrenderer->SetPolyDrawMode (zRND_DRAW_MATERIAL);
	};
	if (zinput->KeyPressed(KEY_2)) {
		zrenderer->SetPolyDrawMode (zRND_DRAW_FLAT);
	};
	if (zinput->KeyPressed(KEY_3)) {
		zrenderer->SetPolyDrawMode (zRND_DRAW_WIRE);
	};
	if (zinput->KeyPressed(KEY_4)) {
		zrenderer->SetPolyDrawMode (zRND_DRAW_MATERIAL_WIRE);
	};
	if (zinput->KeyToggled(KEY_5)) {
		zCVob::SetShowHelperVisuals (!zCVob::GetShowHelperVisuals());
	};
	if (zinput->KeyPressed(KEY_6)) {
		zrenderer->SetFog	(TRUE);
	};
	if (zinput->KeyPressed(KEY_7)) {
		zrenderer->SetFog	(FALSE);
	};

	if (zinput->KeyToggled(KEY_H)) 
	{ 
		world->GetBspTree()->CalcStaticLeafLightData();
/*		vobm2->BeginMovement();
		zVEC3 dir								= vobm2->GetAtVectorWorld() + zVEC3(0,1,0);
		vobm2->MoveWorld						(zVEC3(0,150,0));
		vobm2->SetPhysicsEnabled				(TRUE);
		vobm2->GetRigidBody()->ApplyImpulse		(dir*100000, vobm2->GetPositionWorld());
		vobm2->GetRigidBody()->SetMode			(zPHY_RBMODE_FLY);
		vobm2->GetRigidBody()->SetGravityEnabled(TRUE);
//		playerAI->StartFallDownAni				();
		model->StartAni							("S_FALL");
//		Print ("Bounce");
		vobm2->EndMovement();
*/
	};

	if (zinput->KeyToggled(KEY_L)) { 
		CreateLight();
	};
	if (zinput->KeyToggled(KEY_K))  
	{  
		if (world->GetWorldRenderMode()==zWLD_RENDER_MODE_VERT_LIGHT)
		{
			world->SetWorldRenderMode(zWLD_RENDER_MODE_LIGHTMAPS);
			zERR_MESSAGE (1, 0, "D: LightingMode: lightmaps");
		}
		else
		{
			world->SetWorldRenderMode(zWLD_RENDER_MODE_VERT_LIGHT);
			zERR_MESSAGE (1, 0, "D: LightingMode: vertLight");
		};
		vobm1->MoveWorld (zVEC3(10,0,0));
		vobm1->RotateLocalX (10);
	};
	if (zinput->KeyToggled(KEY_E)) {
		zREAL radius	= 2000.0F;
		zTBBox3D box;
		box.Init		();
		box.AddPoint	(camVob->GetPositionWorld());
		box.AddPoint	(camVob->GetPositionWorld() + radius*zVEC3(1,1,1));
		box.AddPoint	(camVob->GetPositionWorld() - radius*zVEC3(1,1,1));
		if (zinput->KeyPressed(KEY_LSHIFT)) {
//			world->GenerateLightmaps (zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_LOW_QUAL); 
//			world->GenerateLightmaps (zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_HI_QUAL, &box); 
			world->GenerateLightmaps (zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_HI_QUAL); 
		} else 
		if (zinput->KeyPressed(KEY_LCTRL)) {
			world->GenerateStaticVertexLighting	();
		} else {
//			world->GenerateStaticVertexLighting	();
			world->GenerateLightmaps (zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_LOW_QUAL); 
//			world->GenerateLightmaps (zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_HI_QUAL); 
		};
	};

	// screenshot
	if (zinput->KeyPressed(KEY_F12)) {
	};

	if (zinput->KeyToggled(KEY_Q)) {
		if (zinput->KeyPressed(KEY_LALT)) 
		{
//			ThrowVob ("OC_BARREL_V1.3DS", 30, zCCollObjectPoint::S_GetCollObjClass());
			ThrowVob ("ow_forest_tree_v4.3DS", 30, zCCollObjectPoint::S_GetCollObjClass());
		} else {
			if (zinput->KeyPressed(KEY_LSHIFT)) ThrowVob2(); 
			else								ThrowVob();
		};
	};

	if (zinput->KeyToggled(KEY_W)) {
		// chest, rack, barrel_2
		if (zinput->KeyPressed(KEY_LALT)) {
			ThrowVob ("BEDHIGH_1_OC.ASC"		 , 30, zCCollObjectComplex::S_GetCollObjClass());
//			ThrowVob ("OC_BARRELS_STRUBBELIG.3DS", 30, zCCollObjectComplex::S_GetCollObjClass());
		} else {
			
			if (zinput->KeyPressed(KEY_LSHIFT))  ThrowVob ("OW_LOB_TREE_V2.3DS", 30);
			else					 			 ThrowVob ("NC_OREHEAP_FENCE.3DS", 30);
//				if (zinput->KeyPressed(KEY_LSHIFT))  ThrowVob ("bed.3ds", 30);
//				else						ThrowVob ("apple.3ds", 30);
//				else						ThrowVob ("MEATBUG.MDS", 30);
//				else						ThrowVob ("bush_1.3ds", 30);
		};
	};

	//
	if (zinput->KeyToggled(KEY_P)) {
		zPOINT3 pos = camVob->GetPositionWorld();
		zerr.Message ("D: Position ("+zSTRING(pos.n[VX])+", "+zSTRING(pos.n[VY])+", "+zSTRING(pos.n[VZ])+")");
	};
};

void ModelInfo() {
	if (!model) return;
	screen->Print (0,7600, "physics: "+zSTRING(vobm2->GetPhysicsEnabled())+", phyMode: "+zSTRING((int)vobm2->GetRigidBody()->GetMode())+", sleeping: "+zSTRING(vobm2->GetSleeping()));
	screen->Print (0,7800, "cd-stat: "+zSTRING(vobm2->GetCollDetStat())+", cd-dyn: "+zSTRING(vobm2->GetCollDetDyn()));
};


void Info (zCView *viewport) 
{
	if (showInfo==0) return;

	static zDWORD time;
	zSTRING s,t,u,v;
	// time 
	time= sysGetTime() - time;
	s	= int(vidGetFPSRate());
	t	= int(time);
	s	= s + zSTRING(" fps   ");
	viewport->Print (0,0, s.ToChar());

	s	= "height:" + zSTRING(foundHeight);
	viewport->Print (7000,7000, s.ToChar());

//screen->Print (0,2000, zSTRING(ztimer.GetTotalTimeF() / 1000.0F, 3));

//screen->Print (0,2000, zSTRING(bspCollectCtr));

	if (singleStep)			viewport->Print (6000,0, "single-step");
	if (showEngineStats)	zengineStats.PrintScreen();
	if (showInfo<=1)		return;
	
	//
	screen->Print		(0,2000, "l: "+zSTRING(tr_numLeafs)+", p: "+zSTRING(tr_numLeafPolys)+", v:"+zSTRING(tr_numLeafVobs)+" skip:"+zSTRING(float(tr_numLeafVobsSkip)/float(tr_numLeafVobs),4));
	if (tr_numLeafs>0) {
		screen->Print	(0,2200, "p/l: "+zSTRING(float(tr_numLeafPolys) / float(tr_numLeafs),4)+", v/l: "+zSTRING(float(tr_numLeafVobs) / float(tr_numLeafs),4));
		screen->Print	(0,2200, "p/l: "+zSTRING(float(tr_numLeafPolys) / float(tr_numLeafs),4)+", v/l: "+zSTRING(float(tr_numLeafVobs) / float(tr_numLeafs),4));
	};

	tr_numLeafs=0;
	tr_numLeafPolys=0;
	tr_numLeafVobs=0;
	tr_numLeafVobsSkip=0;

	//
	ModelInfo();

	//
	zTRnd_Stats rndStats;
	zrenderer->GetStatistics(rndStats);

	s = 
		zSTRING(rndStats.numTrisRendered)		+ (" tris, " )+ 
		zSTRING(rndStats.numPolysRendered)		+ (" polys, ")+ 
//		zSTRING(zCWorld::s_vertsTransformed)	+ (" verts, ")+
		zSTRING(vidGetFPSRate() * rndStats.numTrisRendered)+" tps";
/*	s = zSTRING(zCWorld::s_polysRendered)		+ (" polys, ")+ 
		zSTRING(zCWorld::s_trisRendered)		+ (" tris, " )+ 
		zSTRING(zCWorld::s_vertsTransformed)	+ (" verts, ")+
		zSTRING(vidGetFPSRate() * zCWorld::s_trisRendered)+" tps";*/
	viewport->Print (0,200, (s+" ").ToChar());
	
	// Position
	zPOINT3 pos = camVob->GetPositionWorld();
	viewport->Print (0	 ,400, zSTRING(pos[0],8));
	viewport->Print (1000,400, zSTRING(pos[1],8));
	viewport->Print (2000,400, zSTRING(pos[2],8));

	// BSP
	s = "leafs: " + zSTRING(world->GetBspTree()->leafsRendered) +
		" vobs: " + zSTRING(world->GetBspTree()->vobsRendered);
	viewport->Print (0,800, (s).ToChar());

	viewport->Print (0	 , 1200 + (0*viewport->FontY()), "rndAlphaPolys: "+zSTRING(rndStats.numAlphaPolys));
	viewport->Print (0	 , 1200 + (1*viewport->FontY()), "rndAlphaPolyBatches: "+zSTRING(rndStats.numAlphaPolyBatches));

	viewport->Print (0	 , 1200 + (2*viewport->FontY()), "farclipz: "     +zSTRING(zCCamera::activeCam->GetFarClipZ()));
	viewport->Print (0	 , 1200 + (3*viewport->FontY()), "userFogFar: "   +zSTRING(zCCamera::activeCam->GetVob()->GetHomeWorld()->GetActiveSkyControler()->GetFarZ()));
	viewport->Print (0	 , 1200 + (4*viewport->FontY()), "userFogFarScale: "   +zSTRING(zCCamera::activeCam->GetVob()->GetHomeWorld()->GetActiveSkyControler()->GetFarZScalability()));

	// finde leaf, in dem sich das Camera-Vob befindet
//	zCBspLeaf *leaf = world->GetBspTree()->GetRoot()->FindLeaf (camVob->GetPositionWorld());
	zCBspLeaf *leaf = world->GetBspTree()->GetRoot()->FindLeaf (moveVob->GetPositionWorld());
	if (!leaf) {  
		screen->Print (00,7000, "Cam not in leaf !");
	} else {
		int numDLights =0;
		int numSLights =0;
		for (int i=0; i<leaf->lightVobList.GetNum(); i++)
		{
			if (leaf->lightVobList[i]->GetIsStatic())	numSLights++;
			else										numDLights++;

		};
		screen->Print (00,7000, "leaf, p:"	+ zSTRING(leaf->numPolys)+
									", vobs: "	+ zSTRING(int(leaf->leafVobList.GetNumInList()))+
									", sLight: "	+ zSTRING(numSLights)+
									", dLight: "	+ zSTRING(numDLights)
									);
/*		camera.Activate(); 
		leaf->bbox3D.Draw();
		zTBBox3D box = world->GetBspTree()->CalcLeafRealBBox3D(moveVob->GetPositionWorld());
		box.Draw (GFX_GREEN);*/
	}; 


	//
//	screen->Print (0,6000, zSTRING(vobsAdded)+", "+zSTRING(vobsConsidered));
//	vobsConsidered = vobsAdded = 0; 

	//
	if (showInfo==2) { if (model) { model->PrintStatus(); model->ShowAniList (6000); }; };
//	if (showInfo) { if (model2) model2->PrintStatus(0,3000); };
#ifdef ZDIETER_MODEL_FACE
	if (showInfo==2) { if (face) face->PrintStatus(0,4000); };
#endif
}

void LoadMatLib () {
	if (!LOAD_MATLIB) return;
/*
	zoptions->ChangeDir (DIR_TEX_MATLIBS);
	zFILE file("ow.pmf",zDSK_TEXT);
	if (!file.Exists()) {
		zerr.Message ("D: Matlib not found !");
		return;
	};
	zerr.Message ("D: Loading Matlib ...");
	file.Open();
	while (zCMaterial::LoadMaterial(file)!=0) {};
	file.Close();
*/
};

void SetDefaultTextures (zCMesh *mesh) {
	if (!DEFAULT_TEXTURING) return;

	for (int i=0; i<zCMaterial::GetStaticClassDef()->GetNumObjects(); i++)
	{
		zCMaterial *mat = static_cast<zCMaterial*>(zCMaterial::GetStaticClassDef()->GetObjectByIndex(i));
//		if (mat->GetName().Search("BODEN")!=-1)	mat->SetTexture(zSTRING("sqarbod.tga"));
		if (mat->GetName().Search("DACH" )!=-1)	mat->SetTexture(zSTRING("DACH.TGA"));
		if (mat->GetName().Search("DECKE")!=-1)	mat->SetTexture(zSTRING("ATW1_PUTZONLY.TGA"));
		if (mat->GetName().Search("WAND" )!=-1)	mat->SetTexture(zSTRING("ATW1_NOPUTZ.TGA"));
		if (mat->GetName().Search("TUER" )!=-1)	mat->SetTexture(zSTRING("WALNUTH.TGA"));
		if (mat->GetName().Search("ERDE" )!=-1)	mat->SetTexture(zSTRING("HOF1_DIRT.TGA"));
		if (mat->GetName().Search("FELS" )!=-1)	mat->SetTexture(zSTRING("HOW3_CANYON_MID4.TGA"));
		if (mat->GetName().Search("BLD"  )!=-1)	mat->SetTexture(zSTRING("GRASS4.TGA"));
		if (mat->GetName().Search("WALD" )!=-1)	mat->SetTexture(zSTRING("GRASS4.TGA"));
		if (mat->GetName().Search("BERG" )!=-1)	mat->SetTexture(zSTRING("HOW3_CANYON_MID4.TGA"));
//		if (mat->GetName().Search("P:"	 )!=-1)	mat->SetTexture(zSTRING("vob.tga"));
		if ((mat->GetName().Search("DEFAULT")!=-1) || (mat->GetName().Search("BODEN")!=-1)) {
			mat->SetSmooth			(TRUE);
			mat->SetSmoothAngle		(90);
			mat->SetTexture			(zSTRING("GRASS2.TGA"));
		};
//		if (mat->color.b>180) 
		if (mat->GetName().Search("WATER" )!=-1)	
		{
			mat->SetMatGroup		(zMAT_GROUP_WATER);
			mat->SetTexture			(zSTRING("WAT_A0.TGA"));
			mat->SetAlpha			(150);
			mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);
			mat->texAniCtrl.SetAniFPS (5);
		};
		if (mat->GetName().Search("WAT" )!=-1)	
		{
			mat->SetMatGroup		(zMAT_GROUP_WATER);
			mat->SetTexture			(zSTRING("WAT_A0.TGA"));
			mat->SetAlpha			(150);
			mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);
			mat->texAniCtrl.SetAniFPS (5);
		};
		if (mat->GetName().Search(".BSPMAT1")!=-1)	mat->SetTexture(zSTRING("ATW2_MIDWAND")); 
		if (mat->GetName().Search(".BSPMAT2")!=-1)	mat->SetTexture(zSTRING("ATW1_PUTZONLY"));
		if (mat->GetName().Search(".BSPMAT3")!=-1)	mat->SetTexture(zSTRING("ATW1_NOPUTZ")); 
		if (mat->GetName().Search("P:")!=-1) {
			if (mat->GetTexture()==0)
//			mat->SetTexture (zSTRING("BAUMKRONE_AB.TGA"));
			mat->SetTexture (zSTRING("BAUM_SSP.TGA"));
		};
//		mat->SetTexture			(zSTRING("Sk_Arm1_S0_D0.tga"));
	};

	if (0)
	if (bspTreeMode==zBSP_MODE_OUTDOOR) 
	{
		mesh->PolyList()[0]->GetMaterial()->SetColor		(50,255,50); 
//		mesh->polyList[0]->GetMaterial()->SetSmooth		(TRUE);
		mesh->PolyList()[0]->GetMaterial()->SetSmoothAngle(179); 
		mesh->SetDefaultPlanarMapping (5.0, 5.0);
	};
};

void LoadLevel() {
	zCMesh *mesh=0;


/*	{
		mesh = zNEW(zCMesh);
		zSTRING mesh1= "newworld2.3ds";
		{
			zCFile3DS file3DS;
			zoptions->ChangeDir	(DIR_MESHES);
			file3DS.Load3DS (mesh1, mesh); 
		};
		{
			zCFile3DS file3DS;
			zoptions->ChangeDir (DIR_MESHES);
			file3DS.Save3DS	("newworld2.3ds", mesh);
		};
		zerr.Report (zERR_FATAL, 1000, "D: STOP !, verts: "+zSTRING(mesh->numVert)+", polys:"+zSTRING(mesh->numPoly));
		mesh->Release();
		mesh=0;
		return;
	};*/

	// MERGE !
/*	{
		mesh = zNEW(zCMesh);
//		zSTRING mesh1= "_wald2\\surfacev47.3ds";
//		zSTRING mesh2= "_wald2\\forest01.3ds";
		zSTRING mesh1= "level\\surface\\surface.3ds";
		zSTRING mesh2= "level\\oldcamp\\oldcamp.3ds";
		zSTRING mesh3= "level\\psicamp\\psicamp.3ds";
		zSTRING mesh4= "level\\newcamp\\newcamp.3ds";
		{
			zCFile3DS file3DS;
			zoptions->ChangeDir	(DIR_MESHES);
			file3DS.Load3DS (mesh1, mesh); 
		};
		{
			zCFile3DS file3DS;
			zoptions->ChangeDir	(DIR_MESHES);
			file3DS.Load3DS (mesh2, mesh);
		};
		{
			zCFile3DS file3DS;
			zoptions->ChangeDir	(DIR_MESHES);
			file3DS.Load3DS (mesh3, mesh);
		};
		{
			zCFile3DS file3DS;
			zoptions->ChangeDir	(DIR_MESHES);
			file3DS.Load3DS (mesh4, mesh);
		};

		if (1)
		{
			zCFile3DS file3DS;
			zoptions->ChangeDir (DIR_MESHES);
			file3DS.Save3DS	("world_complete.3ds", mesh);
			zerr.Report (zERR_FATAL, 1000, "D: STOP !, verts: "+zSTRING(mesh->numVert)+", polys:"+zSTRING(mesh->numPoly));
			mesh->Release();
			mesh=0;
		};
		return;
	};
*/

	worldMeshName.Upper();
	zPATH path(worldMeshName);
	BASE_NAME = path.GetFilename();

	//
	zCViewProgressBar *progressBar = zNEW(zCViewProgressBar(0,0,4000,4000));
//	progressBar->InsertBack		(zSTRING("DEFAULT.TGA"));
	progressBar->SetMinimumStep (5);
	screen->InsertItem			(progressBar);
	world->SetProgressBar		(progressBar);

	{
		if (worldMeshName.Search(".ZEN")!=-1) {
			world->LoadWorld		(worldMeshName, zCWorld::zWLD_LOAD_GAME_STARTUP);
//			world->LoadWorld		(worldMeshName, zCWorld::zWLD_LOAD_EDITOR_COMPILED);
//			world->SaveWorld		("oldcamp_bin.zen", zCWorld::zWLD_SAVE_EDITOR_COMPILED, TRUE);
		} else {
			if (QUAKE_BSP_READ_LIGHTS) {
				if (worldMeshName.Search(".BSP")!=-1) {
					levelVob = zNEW(zCVobLevelCompo);
					levelVob->SetVobName			("Level-Vob");
					zCFileQuakeBSP meshFile;
					mesh = zNEW(zCMesh);
					meshFile.LoadQuakeBSP			(worldMeshName, mesh, world);
					levelVob->SetVisual				(mesh);
					world->AddVobRelease			(levelVob);

					goto ready;
				};
			};

			// .3ds, .bsp
			// Doch bereits schon compiliert worden ?
			zoptions->ChangeDir	(DIR_WORLD);
			zFILE* file = zfactory->CreateZFile(BASE_NAME+"zen");
			if (file->Exists()) {
				world->LoadWorld		(BASE_NAME+".zen", zCWorld::zWLD_LOAD_GAME_STARTUP);
//				world->LoadWorld		(BASE_NAME+".zen", zCWorld::zWLD_LOAD_EDITOR_COMPILED);
				mesh = world->GetBspTree()->mesh;
			} else
			{
				zFILE* file2 = zfactory->CreateZFile(BASE_NAME+".zen");
				if (file2->Exists()) {
					world->LoadWorld		(BASE_NAME+".zen", zCWorld::zWLD_LOAD_GAME_STARTUP);
					mesh = world->GetBspTree()->mesh;
				} else {

					//
//worldMeshName = "box_small.3ds";
					levelVob = zNEW(zCVobLevelCompo);
					levelVob->SetVobName			("Level-Vob");
					levelVob->SetVisual				(worldMeshName);
					world->AddVobRelease			(levelVob);

/*					mesh = ((zCMesh*)(levelVob->GetVisual ()));
					{
						zCVobLevelCompo *levelVob = zNEW(zCVobLevelCompo);
						levelVob->SetVobName			("Level-Vob2");
						levelVob->SetVisual				(zSTRING("MAGICFRONTIER.3DS"));
						world->AddVobRelease			(levelVob);
					};*/
/*					if (worldMeshName.Search ("_3DS")==-1)
					{
						zCFile3DS file3ds;
						zoptions->ChangeDir	(DIR_MESHES);
						file3ds.Save3DS (zSTRING("_tmp\\")+BASE_NAME+zSTRING("_3DS.3ds"), mesh);
						zERR_FATAL ("D: READY");
						return;
					};
*/
/*				//
				worldMeshName= "out_small.3ds";
					levelVob = zNEW(zCVobLevelCompo);
					levelVob->SetVobName			("Level-Vob2");
					levelVob->SetVisual				(worldMeshName);
					world->AddVobRelease			(levelVob);
					mesh = ((zCMesh*)(levelVob->GetVisual ()));
					mesh->SetDefaultPlanarMapping(1.0F,1.0F);
					{
						zCFile3DS file3ds;
						zoptions->ChangeDir	(DIR_MESHES);
						file3ds.Save3DS (zSTRING("vonMario\\")+worldMeshName, mesh);
					};
*/					

	/*				// ghostoccluder
					levelVob = zNEW(zCVob);
					levelVob->SetVobName			("Level-Vob2");
					levelVob->LoadLevelComponent	("1trilarge.3ds");
					zCMesh *mesh2 = ((zCMesh*)(levelVob->GetVisual ()));
					mesh2->Scale		(10, 10, 10);
					mesh2->CalcNormals	();
					mesh2->polyList[0]->GetMaterial()->SetName ("GHOSTOCCLUDER"); 
					world->AddVobRelease			(levelVob);
	*/
				};
				delete file2;
			};
			delete file;
		};
	}
/*	else {
		// ZSP
		world->LoadBspTree (worldMeshName);
		mesh = world->GetBspTree()->mesh;
	};
*/
ready:;
	if (mesh)  
		SetDefaultTextures (mesh);

	//
	world->SetProgressBar	(0);
	screen->RemoveItem		(progressBar);
	delete progressBar;


	if (1)
	{
		for (int i=0; i<zCMaterial::GetStaticClassDef()->GetNumObjects(); i++)
		{
			zCMaterial	*mat	= static_cast<zCMaterial*>(zCMaterial::GetStaticClassDef()->GetObjectByIndex(i));
			zSTRING		texName = mat->GetTextureName();
			if (
//				    (mat->GetName().Search("WASSER")!=-1)
//			     || (mat->GetName().Search("WATER")!=-1) ||
			        (mat->GetName().Search("OWODWATSTAND")!=-1)
			     || (mat->GetName().Search("OWODWATSTOP")!=-1)
			     || (mat->GetName().Search("OC_F_WATER")!=-1)
			     || (texName.Search("MAGBA_A0.TGA")!=-1)
//				 || (texName.Search("WATER")!=-1)
//				 || (texName.Search("WASSER")!=-1)
				) { 
//				zrenderer->SetBilerpFilterEnabled (FALSE);
//				mat->SetTexture			(zSTRING("DEFAULT.TGA"));
				mat->color.alpha		= 210;
				mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND); 	
				mat->SetMatGroup		(zMAT_GROUP_WATER); 
				mat->SetNoCollDet		(FALSE);
				mat->SetTexAniMapping	(TRUE);
				mat->SetTexAniMappingDir(zVEC2( 0.00000F,-0.00009F));
//				mat->SetTexAniMappingDir(zVEC2(+0.00020F,+0.00000F));
				mat->texAniCtrl.SetAniFPS (5);

			};
//			mat->SetSmooth			(TRUE);
//			mat->SetSmoothAngle		(90);
		};
	};

	//
	if (mesh) {
		int size =	(mesh->numPoly  )*((int)sizeof(zCPolygon)) +
					(mesh->numVert  )*((int)sizeof(zCVertex)) +
					(mesh->numPoly*3)*((int)sizeof(zCVertFeature));  
		zerr.Message ("D: LevelMesh mem: "+zSTRING(size));
	};
};

void SetupFog () 
{
	//
	zCOLOR	fogCol;
	zREAL	farz;
	if (bspTreeMode==zBSP_MODE_INDOOR) {
		farz				= 2000;
//		farz				= 10000;
//		farz				= 0;
		playerLightInt		= (int)farz; 
//		playerLightInt		= 1000; 
		fogCol.SetRGB		(00,00,00);
		zrenderer->SetFog	(FALSE);
	} else {
		farz				= 60000;
//		playerLightInt		= (int)farz; 
		playerLightInt		= 0;
		fogCol.SetRGB		(100,100,100);
		mov->IncreaseSpeed	(900);
	};
//	camera->SetFarClipZ		(zVALUE_MAX);
	camera->SetFarClipZ		(farz);
	zrenderer->SetFog		(TRUE);
	zrenderer->SetFogRange	(farz*0.25F, camera->GetFarClipZ(), zRND_FOG_FALLOFF_LINEAR);
	zrenderer->SetFogColor	(fogCol);
};

void CreateCamMoveVobs () {

	if (vob) return;
	// vobids werden zur Zeit bei jedem Level-Neu Load reseted
	// sollten ids im Constructor oder beim einfuegen in den Level vergeben werden ??

	// Startpunkt im Level enthalten ?
	zPOINT3 startPoint(0);
	zCArray<zCVob*> vobList;
	world->SearchVobListByClass (zCVobStartpoint::GetStaticClassDef(), vobList);
	if (vobList.GetNum()>0) {
		startPoint = vobList[0]->GetPositionWorld();
	};

	//
	vob		= zNEW(zCVob);
//	vob		= new zCVobLight; ((zCVobLight*)vob)->SetRange (1000.0F); ((zCVobLight*)vob)->SetWhiteLight (255);

	//
	vobm0	= zNEW(zCVob);
//	vobm0	= zNEW(zCTrigger);

	//
	vobm1	= zNEW(zCVob);
//	vobm1	= zNEW(zCVobChar);
//	vobm1	= zNEW(zCTouchAnimate);
//	vobm1	= zNEW(zCVobAnimate);
//	vobm1	= zNEW(zCVobLensFlare);	((zCVobLensFlare*)vobm1)->SetLensFlareFXByName ("TEMPLEFX01");

	//
//	vobm2	= zNEW(zCVob);	
//	vobm2	= zNEW(zCMover);
//	vobm2	= zNEW(zCTrigger);
#ifdef ZDIETER_MODEL
	vobm2	= zNEW(zCVobChar);
#else
	vobm2	= zNEW(zCVob);
//	vobm2	= zNEW(zCPFXControler);
//	vobm2	= zNEW(zCZoneZFog);
//	vobm2	= zNEW(zCZoneVobFarPlane);
#endif

	// ****************************************

	// 
	// ### !1 ###
	//
#ifdef ZDIETER_PROGMESH
if (1)
	{
		zCMaterial::SetUsageDefault	(zCMaterial::zMAT_USAGE_LEVEL);
//		zCMesh				*mesh	 = zCMesh::Load ("1tri.3ds"); 
//		zCMesh				*mesh	 = zCMesh::Load ("2tris.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("2tri_2mat.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("vobbox1_2my.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("kugel2m_2mat.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("duck.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("globe.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("troll.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("gobbo.3ds");

//		zCMesh				*mesh	 = zCMesh::Load ("buf.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("MIN_LOB_SOLDIERSHUT.3DS");
//		zCMesh				*mesh	 = zCMesh::Load ("OC_LOB_BOWTRAIN.3DS");
//		zCMesh				*mesh	 = zCMesh::Load ("ORC_VASE_V1.3DS");
//		zCMesh				*mesh	 = zCMesh::Load ("modelMesh2.3ds");
		zCMesh				*mesh	 = zCMesh::Load ("CR_DI_OPENEGG.3DS");
//		zCMesh				*mesh	 = zCMesh::Load ("OW_MUSHROOM_V2.3DS");
//		zCMesh				*mesh	 = zCMesh::Load ("OC_WEAPON_SHELF_NEW_V1.3DS");

//		zCMesh				*mesh	 = zCMesh::Load ("OC_BARREL_V1.3ds");
//		zCMesh				*mesh	 = zCMesh::Load ("OW_LOB_RUIN_1.3DS");
//		zCMesh				*mesh	 = zCMesh::Load ("OW_LOB_TREE_V2.3DS");
//		zCMesh				*mesh	 = zCMesh::Load ("OW_LOB_BUSH_V4.3DS");
//		zCMesh				*mesh	 = zCMesh::Load ("TPL_ORCSTATUE.3DS");

//		mesh->Scale(10,10,10);
//		mesh->CalcNormals();
		zCProgMeshBuilder	*pmBuild = zNEW(zCProgMeshBuilder);
		pmProto						 = zNEW(zCProgMeshProto);
//		pmBuild->BuildProgMeshProto (mesh, pmProto, 0, zPM_BUILD_FLAG_NO_LOD);
		pmBuild->BuildProgMeshProto (mesh, pmProto);
		vobm2->SetVisual			(pmProto);
	};
#endif
/*
	zCZoneVobFarPlaneDefault* defFog = zNEW(zCZoneVobFarPlaneDefault);
	defFog->SetFarZ			(50000.0F);
	world->AddVobRelease	(defFog);
*/


/*	{
		// ReverbZone
		zTBBox3D box;
		zREAL dim = 800;
		box.mins = zVEC3(-dim,-dim,-dim);
		box.maxs = zVEC3(+dim,+dim,+dim);
		zCZoneReverb* reverbZone = zNEW(zCZoneReverb);
		reverbZone->SetReverbPresetNr	(3);
		reverbZone->SetReverbWeight		(1);
		reverbZone->SetBBox3DLocal		(box);
		world->AddVobRelease			(reverbZone);
	};
*/
/*	{
		// SoundZone
//		zCVobSound* sound = zNEW(zCVobSound);
		zCVobSoundDaytime* sound = zNEW(zCVobSoundDaytime);
		sound->SetVobName			("sound");
		sound->SetSound				("lute_1.wav");
		sound->SetSound2			("boiling_pot.wav");
//		sound->SetSound				("BOW_FIRE_01.WAV");
//		sound->SetHasObstruction	(TRUE);
		
		sound->Move					(0,30,0);
		sound->SetSoundRadius		(1500.0F);
		world->AddVobRelease		(sound);
	};
*/
	vobm2->SetCollDet		(FALSE);
//	vobm2->SetVisual		("_dieter\\VobBox2.3ds");	 
//	vobm2->SetVisual		("torch_dieter2.3ds");	  
//	vobm2->SetVisual		("zsun1.tga");	  
//	vobm2->SetVisual		("_intern\\spot.3ds");
//	vobm2->SetVisual		("_intern\\STARTPOINT.3DS");
	
//	vobm2->SetVisual		("PC_CRYSTALLIGHT_02.3DS");	  
//	vobm2->SetVisual		("ITMW2HAXE01.3DS");	  
//	vobm2->SetVisual		("WATERPLANT_1.MMS");
//	vobm2->SetVisual		("CHAIR_3_OC.ASC");
//	vobm2->SetVisual		("invisible_camera.3ds");
//	vobm2->SetVisual		("OW_LOB_BUSH_V5.3DS");
//	vobm2->SetVisual		("INVISIBLE_ZCVOBSPOT.3DS");

//	vobm2->SetVisual		("ITMISWORDBLADE.3DS");
//	vobm2->SetVisual		("MFX_DESTROYUNDEAD_CAST.PFX");

//	vobm2->SetVisual		("OC_DECOROOF_V2.3DS");
//	vobm2->SetVisual		("kugel2m.3ds");
//	vobm2->SetVisual		("CR_DI_OPENEGG.3DS");
//	vobm2->SetVisual		("4tris.3ds");
//	vobm2->SetVisual		("BSANVIL_OC.MDS");
//	vobm2->SetVisual		("BOOK_BLUE.MDS");
//	vobm2->SetVisual		("nw_nature_bush_25p.3DS");
	vobm2->SetVisual		("nw_nature_tanne_100p.3DS");

	
//	vobm2->SetVisual		("_intern\\waypoint.3ds");	  
#ifdef ZDIETER_QUADMARK 
	zCQuadMark *quadMark	= zNEW(zCQuadMark);
//	quadMark->SetTexture	(zSTRING("ZBLOODPOOL2.TGA"));
//	quadMark->SetTexture	(zSTRING("BREASTPLATE.TGA"));
	quadMark->SetTexture	(zSTRING("ZBLOODSPLAT2.TGA"));
	vobm2->SetVisual		(quadMark);
#endif

/*	vobm2->SetVisual		("kugel1m.3ds");
zCMesh *m = (zCMesh*)vobm2->GetVisual();
m->polyList[0]->GetMaterial()->SetTexture (zSTRING("CHROMIC.TGA"));
m->SetDefaultPlanarMapping	(5.0F,5.0F);*/
//	vobm2->SetVisual		(zSTRING("TESTFONT.TGA"));
	vobm2->SetVobName		("Vobm2");
	vobm2->SetPositionWorld	(startPoint);
	vobm2->Move				(+0,+50,00);
	vobm2->RotateWorld		(zVEC3(0,1,0), 180);
	vobm2->SetDontWriteIntoArchive (TRUE);

/*	zVEC3 cent(50327, -2527, -11829);
	vobm2->Move				(cent);
	zTBBox3D vbox;
	vbox.mins = cent + zVEC3(-1,-1,-1)*30000;
	vbox.maxs = cent + zVEC3(+1,+1,+1)*30000;
	vobm2->SetBBox3DWorld	(vbox);
	((zCZoneVobFarPlane*)vobm2)->SetFarZ (5000.0F);
*/
//	world->AddVobRelease	(vobm2);

	// ---------
	// ### 1 ###
	// ---------

//	vobm1->SetVisual			("fireball.tga");
//	vobm1->SetVisual			("sml_table.3ds");	 
//	vobm1->SetVisual			("CHESTBIG_OC.MDS");	 
//	vobm1->SetVisual			("net3.tga");	  
//	vobm1->SetVisual			("globe.3ds");
//	vobm1->SetVisual			("MIN_LOB_BRIDGE_ANGEL_4m01.3DS");
//	vobm1->SetVisual			("MIN_LOB_BRIDGE_ANGEL_4m.3DS");
//	vobm1->SetVisual			("modelMesh5.3ds");	  
//	vobm1->SetVisual			("PILLAR_ORC.mds");	  

//	vobm1->SetVisual			("Bush_01.mms");
	vobm1->SetVobName			("Vobm1");
//	vobm1->MoveLocal			(0,20,+100);
//	vobm1->Move					(-270,90,150);
	vobm1->SetPositionWorld		(startPoint);
	vobm1->Move					(-00,+0,-200);
	world->AddVobRelease		(vobm1);
	vobm1->SetDrawBBox3D		(FALSE);
	vobm1->SetCollDetStat		(FALSE);
	vobm1->SetCollDetDyn		(TRUE);
//	vobm1->SetCollType			(zVOB_COLL_TYPE_BIG_OBJECT);
//	vobm1->SetIgnoredByTraceRay	(FALSE);

	world->AddVobAsChild		(vobm2, vobm1);
	vobm2->Release();

	// ---------
	// ### 0 ###
	// ---------

/*	vobm0->SetRange			(10000);
	vobm0->SetColor			(240,50,50);
	vobm0->SetIsStatic		(FALSE);
	vobm0->lightData.rangeAniScaleList.Insert (0.96);
	vobm0->lightData.rangeAniScaleList.Insert (0.95);
	vobm0->SetRangeAniSmooth	(FALSE);
	vobm0->SetRangeAniFPS		(10);
*/

	vobm0->SetTrafoObjToWorld(vobm2->trafoObjToWorld);
	world->AddVobAsChildRelease	(vobm0, vobm2);
	vobm0->MoveLocal		(0,120,-350);
//	vobm0->RotateLocalX		(90);
//	vobm0->MoveLocal		(zVEC3(0,0,-200));
	vobm0->SetVobName		("vobm0_child_Cam_Vob");

	// ---------
	// ### . ###
	// ---------

//	vob->SetVisual			("spot.3ds");
	vob->SetVobName			("CameraVob");
//	vob->SetRange			(10);
//	vob->SetWhiteLight		(255);
//	vob->SetColor			(240,50,50);
	vob->SetPositionWorld	(startPoint);
//	vob->Move				(00,120+150, 240);
	vob->Move				(00,200, 0);
	vob->RotateWorld		(0,1,0, 180);
	vob->SetCollDetStat		(FALSE);
	vob->SetCollDetDyn		(FALSE);
	world->AddVobRelease	(vob);
//	world->AddVobAsChild (vob, vobm2);

	// Light
	if (0) {
		light = zNEW(zCVobLight);
	//	light->SetRange			(900);
	//	light->SetColor			(255,255,255);
		light->SetByPreset		("FX_LIGHT1");
		light->SetIsStatic		(FALSE);
	/*	light->lightData.rangeAniScaleList.Insert (1.00);
		light->lightData.rangeAniScaleList.Insert (0.99); 
		light->SetRangeAniSmooth	(FALSE);
		light->SetRangeAniFPS		(1);*/
	//	light->SetPosition		(600,-100,600);
	//	light->SetPosition		(-1000,-900,950);
	//	world->AddVobAsChild	(light,vob);
		world->AddVobRelease	(light);
	};
	
//	light->AddThisToPresetList	("standardLight");
//	zCVobLight::SaveLightPresets();

	// Sound
/*	zCVobSound *sound = zNEW(zCVobSound);
	zTBBox3D	box;
	box.mins					= -zVEC3(100,100,100);
	box.maxs					=  zVEC3(100,100,100);
	sound->SetVobName			("SOUND");
	sound->SetBBox3DLocal		(box);
	sound->SetPositionWorld		(zVEC3(0,200,0));
	sound->SetSound				("ZFAN.WAV");
//	sound->SetSound				("zexplode.wav");
	world->AddVobRelease		(sound);
*/

/*	//
	trigger = zNEW(zCTrigger);
//	trigger = zNEW(zCTriggerJumper);
	zTBBox3D	box;
	box.mins	= -zVEC3(100,100,100);
	box.maxs	=  zVEC3(100,100,100);
	trigger->SetVobName			("trigger");
	trigger->SetTriggerTarget	("MOVER");
//	trigger->SetTriggerTarget	("QUAKE");
	trigger->SetPositionWorld	(zVEC3(-00,100,0));
	trigger->SetBBox3DLocal		(box);
	world->AddVobRelease		(trigger);

	// Earthquake
	zCEarthquake *earthquake	= zNEW(zCEarthquake);
	earthquake->SetVobName		("quake");
	earthquake->SetPositionWorld(zVEC3(-00,100,0));
	earthquake->SetProperties	(700, 1, zVEC3(1,15,1));
	world->AddVobRelease		(earthquake);

	//
//	mover	= zNEW(zCMover);
	mover	= (zCMover*)vobm2;
//	mover->SetVisual			("OC_MOB_TABLE_NORMAL.3ds");
	((zCVob*)mover)->SetVisual	(zSTRING("straw.3ds"));
//	((zCVob*)mover)->SetVisual	("chest_small.mds");
	mover->SetVobName			(zSTRING("MOVER"));
	mover->SetPositionWorld		(zVEC3(+100,100,-200));
	mover->SetTriggerTarget		("MOVER2");
//	world->AddVobRelease		(mover);

	//
	zCMover *mover2	= zNEW(zCMover);
	((zCVob*)mover2)->SetVisual	("chest_small.mds");
//	((zCModel*)mover2->GetVisual())->SetModelMesh ("Chest_small_mesh");
//	((zCVob*)mover)->SetVisual	(zSTRING("bucket.3ds"));
	mover2->SetVobName			("MOVER2");
	mover2->SetPositionWorld	(zVEC3(+100,100,-400));
	mover2->SetShowVisual		(TRUE);
	world->AddVobRelease		(mover2);
*/
	//
	camVob	= vob;
//	moveVob = vobm2;
	moveVob = vob;
//	moveVob->SetCollDetDyn (TRUE);
//	camVob ->SetCollDetDyn (TRUE);

};

void TestCode () {
/*	zCModel *piep=0;
	if (piep->aniChannels[0]==0) {
		piep->numActiveAnis=1;
		return;
	};
*/
/*
	{
		//
		long int color1;
		long int color2;
		long int result;

		color1 = (long int)c1;
		color2 = (long int)c2;

		result  = ((color1 & 0x00FF00FF) + (color2 & 0x00FF00FF)) & 0x00FF00FF;
		result += ((color1 & 0xFF00FF00) + (color2 & 0xFF00FF00)) & 0xFF00FF00;

		zCOLOR resCol2;
		resCol2.r	= (result & 0x000000FF)>>0;
		resCol2.g	= (result & 0x0000FF00)>>8;
		resCol2.b	= (result & 0x00FF0000)>>16;
		resCol2.alpha= (result & 0xFF000000)>>24;

		return;
	};
*/
/*	{ 
		zerr.Message			("D: start..");
		zoptions->ChangeDir			(DIR_SCRIPTS);
		zCChecksum check;
		check.BeginChecksum		();
		check.CalcFileChecksum	("test.txt");
		check.EndChecksum		();
		zerr.Message			("D: checksum: "+zSTRING(int(check.GetChecksum())));
	};
*/
/*	{
		float maxDist=-1; 
		for (int i=1; i<5000000; i++) {
			float f = float(i);
			float a = float(1) / sqrt(f);
			float b = Alg_SqrtInvApprox (f);
			float d = fabs(a-b);
			if (d>maxDist) maxDist=d;
		};
		zerr.Message (zSTRING(maxDist, 5));
	};
	return;*/

/*	{
		zMAT4 mat;
		mat.MakeIdentity();

		mat = Alg_Translation3D (zVEC3(1,2,3)) * Alg_Rotation3D(zVEC3(12,-1,3), 32);
		mat = mat.Inverse();
		mat = Alg_Scaling3D (zVEC3(4,-5,6)) * mat;
		mat = mat.Inverse();
	};
*/
	{
		zerr.Message ("D: Poly	     : "+zSTRING((int)sizeof(zCPolygon)));
		zerr.Message ("D: Vert	     : "+zSTRING((int)sizeof(zCVertex))); 
		zerr.Message ("D: Feat	     : "+zSTRING((int)sizeof(zCVertFeature)));
		zerr.Message ("D: bspNode      : "+zSTRING((int)sizeof(zCBspNode)));
		zerr.Message ("D: bspLeaf      : "+zSTRING((int)sizeof(zCBspLeaf))); 
		zerr.Message ("D: Portal       : "+zSTRING((int)sizeof(zCPortal)));
		zerr.Message ("D: zCOLOR       : "+zSTRING((int)sizeof(zCOLOR)));
		zerr.Message ("D: Vob          : "+zSTRING((int)sizeof(zCVob)));
		zerr.Message ("D: Model        : "+zSTRING((int)sizeof(zCModel)));
		zerr.Message ("D: ModelNode    : "+zSTRING((int)sizeof(zCModelNode)));
		zerr.Message ("D: ModelAni     : "+zSTRING((int)sizeof(zCModelAni)));
		zerr.Message ("D: ModelAniAct  : "+zSTRING((int)sizeof(zCModelAniActive)));
		zerr.Message ("D: ModelNodeInst: "+zSTRING((int)sizeof(zCModelNodeInst)));
		zerr.Message ("D: zSTRING      : "+zSTRING((int)sizeof(zSTRING)));
		zerr.Message ("D: zCCollObjectChar: "+zSTRING((int)sizeof(zCCollObjectCharacter)));
		zerr.Message ("D: zCMaterial: "+zSTRING((int)sizeof(zCMaterial)));
		zerr.Message ("D: zCShader: "+zSTRING((int)sizeof(zCShader)));
		zerr.Message ("D: zCShaderStage: "+zSTRING((int)sizeof(zCShaderStage)));
		zerr.Message ("D: zD3D_alphaPoly: "+zSTRING((int)sizeof(zD3D_alphaPoly)));
	};

/*	zPOINT3 origin, up, right;
	zTPlane plane;

	zVALUE	dot;
	zPOINT3 n = zPOINT3 (0.0F, 0.0F, 1.0F);
 
	// vorn
	plane.normal	= zPOINT3 (0.0F, 0.0F, -1.0F);
	plane.distance	= +100;
	plane.GetOriginUpRight (origin, up, right);
	zerr.Message ("D: Or, Up, Right: "+zSTRING(
		"("+zSTRING(origin.n[VX])+", "+zSTRING(origin.n[VY])+", "+zSTRING(origin.n[VZ])+") "+
		"("+zSTRING(up.n[VX])+", "+zSTRING(up.n[VY])+", "+zSTRING(up.n[VZ])+") "+
		"("+zSTRING(right.n[VX])+", "+zSTRING(right.n[VY])+", "+zSTRING(right.n[VZ])+")"));
	dot = plane.normal * n;
	zerr.Message ("Dot: "+zSTRING(dot));

	// hinten
	plane.normal	= zPOINT3 (0.0F, 0.0F, +1.0F);
	plane.distance	= -100;
	plane.GetOriginUpRight (origin, up, right);
	zerr.Message ("D: Or, Up, Right: "+zSTRING(
		"("+zSTRING(origin.n[VX])+", "+zSTRING(origin.n[VY])+", "+zSTRING(origin.n[VZ])+") "+
		"("+zSTRING(up.n[VX])+", "+zSTRING(up.n[VY])+", "+zSTRING(up.n[VZ])+") "+
		"("+zSTRING(right.n[VX])+", "+zSTRING(right.n[VY])+", "+zSTRING(right.n[VZ])+")"));
	dot = plane.normal * n;
	zerr.Message ("Dot: "+zSTRING(dot));

	// links
	plane.normal	= zPOINT3 (0.0F, +1.0F, 0.0F);
	plane.distance	= -100;
	dot = plane.normal * n;
	zerr.Message ("Dot: "+zSTRING(dot));

	// rechts
	plane.normal	= zPOINT3 (0.0F, -1.0F, 0.0F);
	plane.distance	= +100;
	dot = plane.normal * n;
	zerr.Message ("Dot: "+zSTRING(dot));
*/
};

void InstallModelFace ();

void SetupModel () 
{ 
	//
#ifdef ZDIETER_MODEL
	playerAI = zNEW(zCAIPlayer);
	{
	zSTRING mds, modelMesh;
	
//	mds = ("humanS.mds");		modelMesh = "HUM_BODY_NAKED0"; 
//	mds = ("humanS.mds");		modelMesh = "Hum_TPLM_ARMOR.ASC"; 
//	mds = ("humanS.mds");		modelMesh = "Hum_NOVS_ARMOR.ASC"; 
// 	mds = ("humans.mds");		modelMesh = "dragon_ice_body.ASC"; 
	mds = ("humanS.mds");		modelMesh = "HUM_BODY_NAKED0.ASC"; 
//	mds = ("humanS.mds");		modelMesh = "HUM_GURM_ARMOR.ASC"; 
//	mds = ("humanS.mds");		modelMesh = "HUM_EBRM_ARMOR.ASC"; 
//	mds = ("humanS.mds");		modelMesh = "SKE_BODY.ASC"; 
//	mds = ("babe.mds");			modelMesh = "BAB_BODY_U01"; 

//	mds = ("bloodfly.mds");		modelMesh	= "BLO_BODY.ASC";
//	mds = ("crawler.mds");
//	mds = ("crwqueen.mds");		
//	mds = ("demon.mds");		modelMesh	= "DEM_BODY.ASC";
//	mds = ("gobbo.mds");		modelMesh	= "GOB_BODY.ASC";
//	mds = ("golem.mds");		modelMesh	= "GOL_BODY.ASC	";
//	mds = ("lurker.mds");		modelMesh	= "LUR_BODY.ASC";
//	mds = ("meatbug.mds");		modelMesh	= "MBG_BODY.ASC";
//	mds = ("molerat.mds");		modelMesh	= "MOL_BODY.ASC";
//	mds = ("orc.mds");			modelMesh	= "ORC_BODY.ASC";
//	mds = ("scavenger.mds");	modelMesh	= "SCA_BODY.ASC";
//	mds = ("shadow.mds");		modelMesh	= "SHA_BODY.ASC";
//	mds = ("sleeper.mds");		
//	mds = ("snapper.mds");		modelMesh	= "SNA_BODY.ASC";	
//	mds = ("swampshark.mds");	modelMesh	= "SWA_BODY.ASC";
//	mds = ("troll.mds");		modelMesh	= "TRO_BODY.ASC";
//	mds = ("waran.mds");		modelMesh	= "WAR_BODY.ASC";
//	mds = ("wolf.mds");			modelMesh	= "WOL_BODY.ASC";
//	mds = ("zombie.mds");

	vobm2->SetVisual				(mds);
	vobm2->SetSleeping				(FALSE);
	vobm2->SetCollisionClass		(zCCollObjectCharacter::S_GetCollObjClass());
//	vobm2->SetSleeping				(TRUE);
	model							= (zCModel*)(vobm2->GetVisual());
	if (model) 
	{
//	model->SetModelMesh ("ShadowSS_V01"); 
//	model->SetNodeShadowEnabled (TRUE);
	
	model->ApplyMeshLib			(modelMesh);
//	model->ApplyMeshLib			("Hum_VLKM_ARMOR");
//	model->ApplyMeshLib			("HUM_ARMOR_ORG_T58521");
//	model->ApplyMeshLib			("hum_armor_nov_t7");
//	model->SetMeshLibTexture	(modelMesh, 0, 2);
//	model->SetMeshLibTexture	(modelMesh, 1, 0);

//	model->SetModelMesh			("skelet_multi");
//	model->SetModelMesh			("skelet_einfach");
	modelProto					= model->GetModelProto();
//	model->SetModelMesh			("HUM_ARMOR_NOV_T1");
	model->SetFatness			(0.0F);

/*	zerr.Message ("D: A");
	for (int i=0; i<300; i++) 
	{
		zCModel *model = zNEW(zCModel(modelProto));
	};
	zerr.Message ("D: B");
*/
	// dummy
	zCModelNodeInst *node = model -> SearchNode("ZS_RIGHTHAND");
	if (node) model -> SetNodeVisual(node,NULL);

//	model->ApplyModelProtoOverlay	("human_drunken.mds");
//	model->ApplyModelProtoOverlay	("hum_wounded.mds");
//	model->ApplyModelProtoOverlay	("human_mad.mds");
//	model->ApplyModelProtoOverlay	("humans_sprint.mds");

//	zCModelPrototype *proto = zCModelPrototype::Load (zSTRING("HUMANS_ACROBATIC.MDS"));

	if (0)
	{
		for (int x=0; x<8; x++)
		{
			for (int y=0; y<8; y++)
			{
				zCVob *vob = zNEW(zCVob);
				vob->SetVisual (zSTRING("humanS.mds"));
				zCModel *model = dynamic_cast<zCModel*>(vob->GetVisual());
				if (model)
				{
					model->ApplyMeshLib (zSTRING("Hum_SLDL_ARMOR.ASC"));
				};
				zVEC3 left  = zVEC3(0,0,200);
				zVEC3 right = zVEC3(200,0,0);
				vob->SetPositionWorld (vobm2->GetPositionWorld() + zREAL(x) * left + zREAL(y) * right);
				world->AddVob (vob);
			};
		};
	};

	if (0)
	{
//		zVEC3 scale = zVEC3(0.7F,0.6F,0.8F);
//		zVEC3 scale = zVEC3(1.0F,2.0F,1.0F);
		zVEC3 scale = zVEC3(0.3F,0.3F,0.3F);
//		zVEC3 scale = zVEC3(1,1,1);
		model->SetModelScale (scale);
//		vobm2->SetTrafo (vobm2->trafo * Alg_Scaling3D (scale));
	};
	if (0)
	if (moveVob==vobm2)
	if (model ) { 
		vobm2->SetAICallback	(playerAI); 
		vobm2->SetPhysicsEnabled(FALSE); 
		playerAI->Release		();
	};
	};
	};
#endif

#ifdef ZDIETER_MODEL2
	{
		zSTRING mds, modelMesh;

// 		mds = ("humanS.mds");		modelMesh = "HUM_ORGM_ARMOR.ASC"; 
// 		mds = ("humanS.mds");		modelMesh = "SKE_BODY.ASC"; 
		
//		mds = ("bloodfly.mds");		modelMesh	= "BLO_BODY.ASC";
//		mds = ("crawler.mds");
//		mds = ("crwqueen.mds");		
//		mds = ("demon.mds");		modelMesh	= "DEM_BODY.ASC";
//		mds = ("gobbo.mds");		modelMesh	= "GOB_BODY.ASC";
//		mds = ("golem.mds");		
//		mds = ("lurker.mds");		modelMesh	= "LUR_BODY.ASC";
//		mds = ("meatbug.mds");		modelMesh	= "MBG_BODY.ASC";
//		mds = ("molerat.mds");		modelMesh	= "MOL_BODY.ASC";
//		mds = ("orc.mds");			modelMesh	= "ORC_BODY.ASC";
//		mds = ("scavenger.mds");	modelMesh	= "SCA_BODY.ASC";
//		mds = ("shadow.mds");		modelMesh	= "SHA_BODY.ASC";
//		mds = ("sleeper.mds");		
		mds = ("snapper.mds");		modelMesh	= "SNA_BODY.ASC";	
//		mds = ("swampshark.mds");	modelMesh	= "SWA_BODY.ASC";
//		mds = ("troll.mds");		
//		mds = ("waran.mds");		modelMesh	= "WAR_BODY.ASC";
//		mds = ("wolf.mds");			modelMesh	= "WOL_BODY.ASC";
//		mds = ("zombie.mds");

		vobm1->SetVisual				(mds);
		vobm1->SetSleeping				(TRUE);
		vobm1->SetCollisionClass		(zCCollObjectCharacter::S_GetCollObjClass());
		model2							= (zCModel*)(vobm1->GetVisual());
		if (model2) 
		{
			model2->ApplyMeshLib		(modelMesh);
//			model2->ApplyModelProtoOverlay	("humans_sprint.mds");
		};

//		zCAIPlayer *ai2 = zNEW(zCAIPlayer());
//		ai2->SetIgnoreKeyboard		(TRUE);
//		vobm1->SetAI				(ai2); 
		vobm1->SetCollDet			(TRUE);
		vobm1->SetPhysicsEnabled	(FALSE); 
	};
#endif
/*	if (model)
	{
		zCDecal *humanDecal = zNEW(zCDecal());
		humanDecal	->SetTexture				(zSTRING("human_decal_a0.tga"));
		humanDecal	->SetDecalDim				(100*0.5F,180*0.5F);
		model		->AddNextLODVisual			(humanDecal);
		model		->SetLODFarDistance			(2000);
		model		->SetLODNearFadeOutDistance	(zVALUE_MAX);
		humanDecal	->SetLODFarDistance			(6000);
		humanDecal	->SetLODNearFadeOutDistance	(5500);
	};
*/
/*	if (model)
	{  
		zCModelAni*	ani			= model->SearchAni ("S_RUN");
		
		zCModelAni* rand1		= model->SearchAni ("T_LEGSHAKE");
		zCModelAni* rand2		= model->SearchAni ("T_SCRATCHLSHOULDER");
		zCModelAni* rand3		= model->SearchAni ("T_SCRATCHRSHOULDER");
		model->InsertRandAni	(ani->GetAniID(), rand1->GetAniID());
		model->InsertRandAni	(ani->GetAniID(), rand2->GetAniID());
		model->InsertRandAni	(ani->GetAniID(), rand3->GetAniID());
		model->SetRandAniFreq	(ani->GetAniID(), 8.0F);

//		model->ApplyModelProtoOverlay	("dieter_overlay.mds");
//		model->ApplyModelProtoOverlay	("dieter_overlay2.mds");
	};
*/
//	modelProto->DescribeTree ();
//	vobm1->SetVisual ("dieter.mds");
//	if (model->SearchNode ("ZS_HELMET")!=0) zerr.Message ("zs_helm found");

//	model->SetModelMesh ("Mesh_Guard");
//	model->SetModelMesh ("PlayerMesh_Robe");

	// Waffe ziehen
//	zCVob *waffe = zNEW(zCVob);
//	zCMesh *w;
//	waffe->SetVisual	("items\\melee_weapons\\1_hand\\sword.3ds");
//	waffe->Move			(100,0,0);
//	world->AddVobRelease	(waffe);
//	w = (zCMesh*)waffe->GetVisual();
//	vobm2->SetVisual (waffe->GetVisual());
#ifdef ZDIETER_MODEL_WEAPON
	if (model) 
	{
		zCModelNodeInst *slot; 
		zCVisual *visual	= zCVisual::LoadVisual ("ITMW_2H_AXE_HEAVY_04.3DS");
		slot				= model->SearchNode		("ZS_RIGHTHAND");
		if (!slot)	zerr.Message ("!!");
		else		model->SetNodeVisual	(slot, visual);
		visual->Release	();
	};
#endif 

	InstallModelFace();

};

// ======================================================================================================================

void CompileSaveWorld() 
{
	if (!world->IsCompiled()) 
	{

//		world->CompileWorld					(bspTreeMode, BSP_OPTIMIZE, TRUE);				// GAME
		world->CompileWorld					(bspTreeMode, BSP_OPTIMIZE, FALSE, FALSE);		// EDITOR
//		world->CompileWorld					(bspTreeMode, BSP_OPTIMIZE, FALSE, TRUE);		// EDITOR, editor-moed
//		world->SaveBspTreeMesh3DS	(zSTRING("orcGraceYard_test.3ds"));
		world->GenerateStaticWorldLighting	(zCWorld::zWLD_LIGHT_VERTLIGHT_ONLY); 
//		world->GenerateStaticWorldLighting	(zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL); 
		if (SAVE_AFTER_COMPILE) {
			if (QUAKE_BSP_READ_LIGHTS) {
				world->SaveWorld				(BASE_NAME+".zen", zCWorld::zWLD_SAVE_EDITOR_COMPILED);
			} else {
//				world->SaveWorld				(BASE_NAME+".zen", zCWorld::zWLD_SAVE_COMPILED_ONLY);
				world->SaveWorld				(BASE_NAME+".zen", zCWorld::zWLD_SAVE_EDITOR_COMPILED);
//				world->SaveWorld				(BASE_NAME+".zen", zCWorld::zWLD_SAVE_COMPILED_ONLY, FALSE);	// ASCII
//				world->SaveWorld				(BASE_NAME+"_bin.zen", zCWorld::zWLD_SAVE_COMPILED_ONLY, TRUE);	// BINARY
			};
		};
	};
};

// ======================================================================================================================

void TestCodeGameLoop() {
#ifdef ZDIETER_MODEL_FACE
		if (face) {
			if (zinput->KeyPressed(KEY_F5))	{
				if (face->IsAniActive("V_TALK"))	face->FadeOutAni("V_TALK");
				else								face->StartAni	("V_TALK", zRandF()*0.0F + 1.0F);
			};
			if (zinput->KeyPressed(KEY_F6))	face->StartAni ("S_FRIGHTENED");
			if (zinput->KeyPressed(KEY_F7))	face->StartAni ("S_HOSTILE");
			if (zinput->KeyPressed(KEY_F8))	face->StartAni ("S_ANGRY");
//			if (zinput->KeyPressed(KEY_F8))	face->StartAni ("S_FRIENDLY");
//			if (zinput->KeyPressed(KEY_F8))	face->StartAni ("S_ANGRY");
//			if (zinput->KeyPressed(KEY_F9))	face->StartAni ("NEUTRAL");
			// H_Mutant
		};
#endif

		// Streak
#ifdef ZDIETER_POLYSTRIP
//		if (model) 
		if (0)
		{
//			zCTree<zCModelNodeInst> *node	= model->SearchNodeTree (zSTRING("BIP01 R FOREARM"));
/*			zCModelNodeInst *node			= model->SearchNode (zSTRING("ZS_RIGHTHAND"));
			if (node && node->nodeVisual) {
				zMATRIX4			trafoNodeToWorld	= vobm2->trafoObjToWorld * model->GetTrafoNodeToModel(node);
				zCOBBox3D			*obb				= node->nodeVisual->GetOBBox3D();
				zPOINT3				pos1				= obb->center + obb->axis[0]*obb->extent[0];
				zPOINT3				pos2				= obb->center - obb->axis[0]*obb->extent[0];
				pos1 = trafoNodeToWorld * pos1;
				pos2 = trafoNodeToWorld * pos2;
				streak->AddSegment (pos1, pos2);
			};*/
		} else {

			static zREAL t0 = 0.2F;
			static zREAL t1 = 0.8F;

			t0 += ztimer.GetFrameTimeF() / 7000.0F;
			t1 += ztimer.GetFrameTimeF() / 7000.0F;

/*			static zREAL t0 = 0.0F;
			static zREAL t1 = 0.0F;

//			t0 += ztimer.GetFrameTimeF() / 7000.0F;
			t1 += ztimer.GetFrameTimeF() / 3000.0F;
*/
			streak->SetVisibleSegments (t0,t1);

			if (zinput->KeyPressed(KEY_J)) 
			{ 
//				t0 = 0;
//				t1 = 0;
				zTBSphere3D streakSphere;
				streakSphere.center = vobLightning->GetPositionWorld();
				streakSphere.radius	= 2000;

				zTBSphere3D sphere;
				sphere.center			= 150.0F;
				sphere.radius			= 150.0F;
				zVEC3		startPos	= zVEC3(150.0F,150.0F,0);
				zVEC3		startDir	= zVEC3(1.0F,0,0);
				startDir = zVEC3(zRandF2(), zRandF2(), zRandF2());
				startDir.Normalize();
				streak->material->SetTexture		(zSTRING("ZBEAM1.TGA"));
				streak->SetAlphaFadeSpeed			(0.1F);
//				streak->SetCamAlign					(zCPolyStrip::zCAM_ALIGN_NONE);
				streak->SetCamAlign					(zCPolyStrip::zCAM_ALIGN_STRIP);
				streak->GenerateCircle				(sphere, startPos, startDir);
//				streak->GenerateCPLightning0		(zVEC3(0,150,0), zVEC3(-600, 100, -600));
				streak->SetVisibleSegments			(t0,t1);

/*				streak->material.SetTexture			(zSTRING("LIGHTNING_A0.TGA"));
				streak->SetCamAlign					(zCPolyStrip::zCAM_ALIGN_STRIP);
				streak->GenerateCPLightning0		(zVEC3(0,150,0), zVEC3(-600, 100, -600),0.3F);
*/
//				streak->AddSegment (vobm2->GetPositionWorld(), vobm2->GetPositionWorld()+vobm2->GetUpVectorWorld()*100); 
//				streak->GenerateCPLightning0		(zVEC3(0,150,0), zVEC3(-600, 100, -600));
/*
				zVEC3 p1	= zVEC3(zRandF2(), zRandF()*0.5F+0.5F, zRandF2());		
				zVEC3 p2	= zVEC3(zRandF2(), 0, zRandF2());		
//				zVEC3 p1(00,100,+600);
//				zVEC3 p2(00,100,-600);
				p1.Normalize();
				p2.Normalize();
				p1 = streakSphere.center + p1*streakSphere.radius;
				p2 = streakSphere.center + p2*streakSphere.radius;
				streak->GenerateCP		(p1,p2);
				streak->ProjectToSphere	(streakSphere);

				p1 = zVEC3(0,2000,0);
				p2 = zVEC3(0,0000,0)+zRandF2()*zVEC3(400,0,400);
				p1 += vobLightning->GetPositionWorld();
				p2 += vobLightning->GetPositionWorld();

				lightning->SetProjectionSphere	(streakSphere);
				lightning->Generate				(p1, p2);
*/
			};
		};
#endif

#ifdef ZDIETER_QUADMARK
		// Quadmark / Blood Test
		if (zinput->KeyToggled(KEY_U)) 
		{
			if (dynamic_cast<zCQuadMark*>(vobm2->GetVisual())) 
			{
				zCQuadMark *quadMark = dynamic_cast<zCQuadMark*>(vobm2->GetVisual());
				zVEC2 size(zRandF()*100, zRandF()*100);
				zREAL dim = zRandF()*120 + 20;
				size = zVEC2(dim*1.0F,dim);
				zCQuadMark::zTEffectParams aniEffects;
//				aniEffects.texAniType		= zCQuadMark::zTEXANI_SCALEUP;
				aniEffects.texAniType		= zCQuadMark::zTEXANI_SCALEUP_AUTO;
				aniEffects.texAniSpeed		= 1.0F;
				aniEffects.texAniScaleStart	= 0.5F;
//				quadMark->CreateQuadMark	(camVob->GetPositionWorld(), camVob->GetAtVectorWorld()*500, size, &aniEffects);
				quadMark->CreateQuadMark	(camVob->GetPositionWorld(), camVob->GetAtVectorWorld()*500, size);
			};
		};
#endif
		// Follow-Cam
		if (followCam)
			if (moveVob!=camVob)  camVob->SetHeadingWorld (moveVob);
};

// ======================================================================================================================

void TestCodeGameLoopLFB ()
{
#ifdef ZDIETER_TRACERAY
	// Trace-Ray Test
	camera->Activate();
	int		rayFlags= zTRACERAY_STAT_POLY | zTRACERAY_POLY_NORMAL | zTRACERAY_POLY_TEST_WATER;
	if (zCVob::GetShowHelperVisuals())
		rayFlags |= zTRACERAY_VOB_TEST_HELPER_VISUALS;
	zVEC3	inters(0,0,0), point2;
	zREAL	RAY_LEN	= zREAL(1500.0F);

//	zPOINT3 rayOrg  = zPOINT3(0,0,-50);
//	zVEC3	ray		= zVEC3(0,0,1)*7000; 

	zPOINT3 rayOrg  = moveVob->GetPositionWorld();
	zVEC3	ray		= moveVob->GetAtVectorWorld() * RAY_LEN;
//	world->bspTree.GetRoot()->RayIntersection (vobm2->GetPositionWorld(), vobm2->GetPositionWorld()-vobm2->trafo.GetUpVector()*500, inters);
//	world->TraceRayFirstHit		(rayOrg, ray, moveVob, rayFlags);
	world->TraceRayNearestHit	(rayOrg, ray, moveVob, rayFlags);
//	world->PickScene			(*camera, 320, 200, RAY_LEN);
	if (world->traceRayReport.foundHit) {
		// foundIntersection, foundPolyNormal
		zlineCache.Line3D (world->traceRayReport.foundIntersection, 
						   world->traceRayReport.foundIntersection + world->traceRayReport.foundPolyNormal*zREAL(20.0F), GFX_RED);
		zlineCache.Line3D (world->traceRayReport.foundIntersection, 
						   world->traceRayReport.foundIntersection + zVEC3(0,10,0) + world->traceRayReport.foundPolyNormal*zREAL(20.0F), GFX_RED);
		if (world->traceRayReport.foundPoly==0) screen->Print (0,6000, "no poly !");
		else {
			zCPolygon *poly = world->traceRayReport.foundPoly;
			zCMaterial *mat = poly->GetMaterial();

//			poly->DrawWire	();

			zSTRING  s = "mat: \""+mat->GetName()+"\"";
			s += ", in=>out: "+zSTRING(int(poly->GetPortalIndoorOutdoorFlag()))+
							", f: "+zSTRING(int(mat->GetBspSectorFront()))+
							", b: "+zSTRING(int(mat->GetBspSectorBack ()))+
//							", sec: "+zSTRING(int(poly->GetSectorFlag()))+
							", secInd: "+zSTRING(int(poly->GetSectorIndex()))+
							", prt: "+zSTRING(int(poly->GetPortalType()))+
							", verts: "+zSTRING(int(poly->polyNumVert))+
							", occl: "+zSTRING(int(poly->GetOccluder()))+
							", go: "+zSTRING(int(poly->GetGhostOccluder()))+
							", noCD: "+zSTRING(int(mat->GetNoCollDet()));
			screen->Print (0,6000, s);
			screen->Print (0,6200, "area: "+zSTRING(poly->GetArea(),4)+", norm: "+poly->GetNormal().GetString());
			screen->Print (0,6400, "mat, alpha: "+zrenderer->AlphaBlendFuncTypeToString(poly->GetMaterial()->GetAlphaBlendFunc())
				+", lightStat: "+poly->GetLightStatAtPos	(world->traceRayReport.foundIntersection).GetString());
			if (poly->GetLightmap()) 
			{
				zCTexture *lm = poly->GetLightmap()->Texture();
				int xdim, ydim;
				lm->GetPixelSize (xdim, ydim);
				zREAL sc,tc;
				poly->GetLightmap()->GetLightmapTexCoords (world->traceRayReport.foundIntersection, sc,tc);
				sc = (sc)*float(xdim);
				tc = (tc)*float(ydim);
				s = "size: "+zSTRING(xdim)+"/"+zSTRING(ydim)+", s/t: "+zSTRING(int(sc))+"/"+zSTRING(int(tc))+
					", lm: "+zSTRING(int(lm)); 
				screen->Print (0,6600, s);
			};

			{
				int xscr, yscr;
				zPOINT3 pos;
				zCCamera::activeCam->Activate();
				s.Clear();
				for (int i=0; i<poly->polyNumVert; i++) 
				{
					pos = zCCamera::activeCam->Transform(poly->vertex[i]->position);
					if (pos[VZ]>0) 
					if (pos[VZ]<800) 
					{
						zCCamera::activeCam->Project		(&pos, xscr, yscr);
						s = zSTRING(poly->feature[i]->texu,2)+":"+zSTRING(poly->feature[i]->texv,2);
						screen->Print						(screen->anx(xscr),screen->any(yscr), s);
					};
					
//					s += zSTRING(poly->feature[i]->texu,2)+":"+zSTRING(poly->feature[i]->texv,2)+" -- ";
				};
//				screen->Print (0,6800, s);
			};

			if (zinput->KeyPressed(KEY_6)) {
				zVEC2 uvCenter = zVEC2(0);
				for (int i=0; i<poly->polyNumVert; i++) 
					uvCenter += zVEC2(poly->feature[i]->texu, poly->feature[i]->texv);
				uvCenter = uvCenter / float(poly->polyNumVert);
				poly->TexRotate		(uvCenter, 1.0F);
/*				poly->TexCorrectUV ();
				for (int i=0; i<poly->polyNumVert; i++) 
					zerr.Message ("D: "+zSTRING(i)+": "+zSTRING(poly->feature[i]->texu,4)+", "+zSTRING(poly->feature[i]->texv,4));
				zCArray<zCPolygon*> polyList;
				polyList.Insert (poly);
				zCPolygon::AlignPolyListToAvgPlane (polyList);*/
			};
		};
		if (world->traceRayReport.foundVob) 
		{
			zCVob	*vob	= world->traceRayReport.foundVob;
			zSTRING visName = (vob->GetVisual()) ? vob->GetVisual()->GetVisualName() : "%";
			screen->Print	(0,7000, "VOB, vis: "+visName+", cdDyn: "+zSTRING(vob->GetCollDetDyn())+", cdStat: "+zSTRING(vob->GetCollDetDyn()));
//			vob->SetDrawBBox3D (!vob->GetDrawBBox3D());
		};
//		if (world->traceRayReport.foundVob!=0) zerr.Message (world->traceRayReport.foundVob->GetVobName());
		inters = world->traceRayReport.foundIntersection;
		point2 = rayOrg;
//		if (moveVob!=camVob) zlineCache.Line3D (inters, point2, GFX_WHITE);
	};
#endif


#ifdef ZDIETER_PICK_VOB
			// PickVob
			{
//				camera.SetPixel (320,240,GFX_RED);
//				camera.SetPixel (320,241,GFX_RED);
//				zCVob	*ivob	= vobm2; 
				zCVob	*ivob	= camVob; 
				zPOINT3 rayOrg  = ivob->GetPositionWorld();
				zVEC3	ray		= ivob->GetAtVectorWorld()*10000;
				if (world->PickVob (*camera, 320, 240)) {
//				if (world->TraceRayNearestHit (rayOrg, ray, ivob, zTRACERAY_STAT_POLY)) { 
//				if (world->TraceRayNearestHit (rayOrg, ray, ivob)) {
//					zlineCache.Line3D (rayOrg, world->traceRayReport.foundIntersection, GFX_WHITE);
					zSTRING vobInfo;
					if (world->traceRayReport.foundVob) {
//						vobName = world->traceRayReport.foundVob->GetVobName();
//						if (vobName=="") vobName = "!";
						vobInfo = world->traceRayReport.foundVob->GetVobInfo();
					};
					screen->Print (0,7000, "found hit, poly:"+zSTRING((int)world->traceRayReport.foundPoly)+
											", vobInfo: "+vobInfo);
				};
				pickVob		= world->traceRayReport.foundVob;
				pickedPoly	= world->traceRayReport.foundPoly;
	//			world->PickVob (moveVob->GetPositionWorld(), zPOINT3(0,-10000,0), tmpVob, pickedPoly, inters);
//				zCMesh *level = (zCMesh*)world->bspTree.mesh;
//				pickedPoly = level->PickPolygon (moveVob->GetPositionWorld(), zPOINT3(0,-10000,0), inters);
//				if (pickedPoly==0) zerr.Message ("no poly!");
				if (oldPoly!=pickedPoly) {
					if (oldPoly!=0) {
						oldPoly->SetMaterial (oldMat);
					};
					if (pickedPoly!=0) {
						oldMat = pickedPoly->GetMaterial();
						pickedPoly->SetMaterial (markerMat);
						if (pickedPoly->polyNumVert>4) zerr.Message (zSTRING(pickedPoly->polyNumVert));
	//						if (poly) {
	//							zCList<zCPolygon> outList;
	//							((zCMesh*)levelVob->GetVisual())->GetAdjacentPolysOnPlane (poly, outList, FALSE, 0.01F);
	//							zerr.Message ("OnPlane Polys: "+zSTRING(outList.GetNumInList()));
	//						};
					};
					oldPoly = pickedPoly;
				};
				if (tmpVob!=pickVob) {
//					if (tmpVob==0) zerr.Message ("D: Lost Vob"); else {
//						zerr.Message ("D: New Vob: "+zSTRING(int(tmpVob))+" ID: "+zSTRING((int)tmpVob->GetVobID()));
//					}
					pickVob = tmpVob;
				};
				if (pickVob) {
					zCVob *vob = world->traceRayReport.foundVob;
					vob->SetDrawBBox3D (!vob->GetDrawBBox3D());
				};
				poly = pickedPoly;
			};
#endif	
/*		
		{
			static zVEC3 vel	= zVEC3(0,0,1);
			zVEC3 normal= zVEC3(0,1,0); normal.Normalize();
			zVEC3 res;
			zVEC3 tmp;

			res =  vel^normal;
			res =-(res^normal);
	//		res = zVEC3(0,1,0)^normal;
	//		res = res^normal;
	//		if (res[VY]>0) res = -res;

	//		res = normal * (normal * vel);

	//		vel.Normalize();
	//		res = (zVEC3(0,1,0)^normal);
	//		res.Normalize();

	//		screen->Print (3000,3000, zSTRING(Alg_Rad2Deg (Alg_AngleRad (normal, vel))));

	// -1	0	1	2	3
	// -180	-90	0	90	180		(- => rechts)
	zVEC3 a,b;
	a = zVEC3(0,0,1);
	b = vel;
	b.Normalize();
	zREAL	dot		= a * b;
	zVEC3	cross	= a^b;
	int		i;
	if (cross[0]!=0)	i=0; else
	if (cross[1]!=0)	i=1; else
						i=2;
	if (cross[i]<0)		dot = -(dot-1)+1;
	screen->Print (0,5000, zSTRING(dot,3));
	zlineCache.Line3D (0, normal*100, GFX_RED);
	zlineCache.Line3D (0, a*50, GFX_YELLOW);
	zlineCache.Line3D (0, b*50, GFX_GREEN);
	zlineCache.Line3D (0, cross*120, GFX_BLUE);

			vel.Normalize();
//			screen->Print (3000,3000, zSTRING(vel*normal));
//			screen->Print (3000,4000, zSTRING(Alg_Rad2Deg(Alg_AngleUnitRad(vel,normal))));
//			zlineCache.Line3D (0, normal*100, GFX_RED);
//			zlineCache.Line3D (0, vel*50, GFX_YELLOW);
//			zlineCache.Line3D (0, res*50, GFX_GREEN);

			const zVALUE D = 0.1;
			if (zinput->KeyPressed(KEY_HOME)) vel[VZ] += D;
			if (zinput->KeyPressed(KEY_END )) vel[VZ] -= D;
			if (zinput->KeyPressed(KEY_DEL )) vel[VX] += D;
			if (zinput->KeyPressed(KEY_PGDN)) vel[VX] -= D;
			if (zinput->KeyPressed(KEY_5 ))	 vel[VY] += D;
			if (zinput->KeyPressed(KEY_6))    vel[VY] -= D;
		}
*/
/*
		if (zinput->KeyPressed(KEY_F8)) {
			zCQuat	q1,q2,q3,qd;
			zMAT4	m1,m2,m3;
			m1 = Alg_Rotation3D (zVEC3(0,1,0), 134);
			m2 = Alg_Rotation3D (zVEC3(0,1,0), 179);
			q1.Matrix4ToQuat	(m1);
			q2.Matrix4ToQuat	(m2);

//			q3 = q1 - q2;
			qd = q1.Inverse() * q2;
			qd = q2 * q1.Inverse();
			q3 = q1 * qd;
			q3 = qd;

			q3.Unit();
			
			q3.QuatToMatrix4	(vobm2->trafo);
			q3.QuatToMatrix4	(vobm2->trafoObjToWorld);
		};
*/

/*		{
			zMAT4 trafo, newTrafo, view;
			zVEC3 right, at, up; 

			view		= camVob->trafo;
			view		= trafo.Inverse() * view;
			trafo		= vobm2->trafo;
			newTrafo	= trafo;

			view	= view.Inverse();
			right	= view.GetRightVector	();
			up		= view.GetUpVector		();
//			right	= zVEC3(1,0,00);
			at		= -(camVob->GetPositionWorld() - vobm2->GetPositionWorld());
			at[VY]	= 0;
			at.Normalize();

//			newTrafo.SetRightVector (right); 
//			newTrafo.SetUpVector	(up);
			newTrafo.SetAtVector	(at);
			newTrafo.MakeOrthonormal(); 

			vobm2->SetTrafo (newTrafo);
		};
*/

		// Fackel in die Hand legen
/*		{
			if (model) 
			if (vobSubtree)
			{
				zMATRIX4 mat = vobm2->GetTrafoModelNodeToWorld("ZS_LEFTHAND");
				vobSubtree->SetTrafoObjToWorld (mat);
			};
		};
*/
/*		if (zinput->KeyPressed(KEY_M)) {
			vobSubtree->SetSleeping			(FALSE); 
			vobSubtree->SetPhysicsEnabled	(TRUE);
			zVEC3 force	=						vobSubtree->GetAtVectorWorld(); 
			vobSubtree->RigidBody()->SetVelocity		(500*force);
			if (!vobSubtree->GetAICallback()) {;
				zCAITest	*testAI		= zNEW(zCAITest);
				vobSubtree->SetAICallback				(testAI);
			};
		};
*/

#ifndef ZDIETER_MODEL_FACE
/*		if (zinput->KeyPressed(KEY_F5))
		{
			if (zinput->KeyPressed(KEY_LCTRL)) {
				if (model) {
					model->SetModelMesh ("Mage");
				};
			} else
			if (vobm2->GetVisualType()!=zVISUAL_MODEL) {
				vobm2->SetVisual ("humanS.mds");	vobm2->SetSleeping (FALSE); 
				model		= (zCModel*)(vobm2->GetVisual());
				vobm2->SetAICallback	(playerAI);
				model->SetModelMesh		("HuS_Body_Naked0_U01");
//				model->SetDynLightMode	(zCModel::zMDL_DYNLIGHT_EXACT); 
			};
		};
		if (zinput->KeyPressed(KEY_LSHIFT)) 
		if (zinput->KeyPressed(KEY_F5)) {
			InsertModel (camVob->GetPositionWorld());
		};
*/
#endif

};

// ======================================================================================================================

void TestCodeGameLoopNetTest () 
{
#ifdef ZDIETER_NET_TEST
		// Netz-Model
		if (model2 && model)
		{
			const  int		TIME_STEP = 200;
			static zREAL	t=999999;
			static zCQuat	rot0, rot1, rot2;	// Zeitpunkte -1,0 (jetzt), 1
			static zPOINT3	pos0, pos1, pos2;
			t += ztimer.GetFrameTimeF();
			if (t>=TIME_STEP) {
				screen->Print (7920,7900, "P");
				t = 0;

				zCBuffer buffer (1024);
				int		size;
				buffer.SetPosBegin();	model ->PackStateBinary		(buffer);	size = buffer.GetSize();
				buffer.SetPosBegin();	model2->UnpackStateBinary	(buffer);

				minPacketSize = zMin		(minPacketSize, size);
				maxPacketSize = zMax		(maxPacketSize, size);

				vobm2->SetCollDet			(FALSE);
				vobm1->SetCollDet			(FALSE);
				buffer.SetPosBegin();	vobm2->PackStateBinary		(buffer);
				buffer.SetPosBegin();	vobm1->UnpackStateBinary	(buffer);

				// abstellen, dass das Model durch dessen Ani bewegt wird (X,Y,Z getrennt steuerbar)
				// (waere nur 1x noetig, falls man die Position lerpen will)
//				model2->SetAniTransScale	(zVEC3(0,0,0)); 
//				model2->SetAniTransScale	(zVEC3(1,0,1)); // nur Y abstellen

				// ACHTUNG: es wird davon ausgegangen, dass die Zeit zw. 2 Updates konstant ist !!

				// Rotation
				rot0 = rot1;
				rot1.Matrix4ToQuat (vobm2->trafo);
				rot2 = rot1 * (rot0.InverseUnit() * rot1);

				// Pos
//				pos0 = pos1;
//				pos1 = vobm2->GetPositionWorld();
//				pos2 = pos1 + (pos1-pos0);
				//
				vobm1->Move (150,0,0);		// HACK, damit das remote-Model neben dem master-model laueft
//				vobm2->SetShowVisual (FALSE);
			} else {
				zREAL	w		= zREAL(t) / zREAL(TIME_STEP);
				vobm1->BeginMovement();

				// Rot
				zCQuat	lerp;
				zMAT4	matrix	= vobm1->trafo;
				lerp.Slerp				(w, rot1, rot2);
				lerp.QuatToMatrix4		(matrix);
				vobm1->SetTrafo			(matrix);
				// pos
//				vobm1->SetPositionWorld (pos1 + w*(pos2-pos1));
//				vobm1->Move (150,0,0);	// HACK 
				// pos - nur Y 
//				zPOINT3 newPos	= vobm1->GetPositionWorld ();
//				newPos[VY]		= pos1[VY] + w*(pos2[VY]-pos1[VY]);
//				vobm1->SetPositionWorld (newPos);
				//
				vobm1->EndMovement();
			};
			if (showInfo) { if (model2) model2->PrintStatus(0,3000); };
		};
#endif
};

// ======================================================================================================================

void TestCodeMoveRecorder ()
{
	if (zinput->KeyPressed(KEY_R)) {
		if (zinput->KeyPressed(KEY_LALT)) {
			if (zrecorder.IsRecording())	zrecorder.StopRecording	();
			else							zrecorder.StartRecord	(moveVob);
		};
		if (zinput->KeyPressed(KEY_LSHIFT)) {
			if (zrecorder.IsPlayingBack())	zrecorder.StopPlayback	();
			else							zrecorder.StartPlayback	(moveVob, (zinput->KeyPressed(KEY_LCTRL)));
		};
	};
	zrecorder.DoUpdate();
};

// ======================================================================================================================

void TestCodePreGameLoop () 
{
#ifdef ZDIETER_PICK_VOB
	// PickVob
	markerMat= zNEW(zCMaterial(".BSP Dummy aterial1 Wall1"));
	markerMat->color.r = markerMat->color.g = markerMat->color.b = 10;
	markerMat->color.b = 100;
#endif
//	zCVob *nearestVob = 0;
	
	//
	// AI - Player
	//
	vobm2->SetCollDet			(FALSE); 
//	vobm1->SetCollDet			(TRUE); 

/*	vobm1->SetVisual (0);
//	vobSubtree = world->MergeVobSubtree (zSTRING("torchDieter.pwf"), vobm1, zCWorld::zWLD_LOAD_MERGE_ADD); 
	vobSubtree = world->MergeVobSubtree (zSTRING("torchUlf.pwf"), vobm1, zCWorld::zWLD_LOAD_MERGE_ADD); 
	world->RemoveVobSubtree	(vobm1);
	world->AddVob			(vobm1);
	*/
	
/*	// FACKEL
	vobSubtree = world->MergeVobSubtree (zSTRING("torch.pwf"), 0, zCWorld::zWLD_LOAD_MERGE_ADD); 
//	vobSubtree = world->MergeVobSubtree (zSTRING("torchDieter.pwf"), 0, zCWorld::zWLD_LOAD_MERGE_ADD); 
//	vobSubtree->Move			(50,50,50);
//	vobSubtree->SetCollDet		(TRUE);
//	vobm2 = vobSubtree;
*/


//	vobSubtree->Move (0,0,200);
/*	vobm2= world->MergeVobSubtree (zSTRING("torch2.pwf"), vobm1, zCWorld::zWLD_LOAD_MERGE_ADD); 
	vobm2->Move (0,0,200);
	zCVob *v=world->FindVobName ("TORCHFIRE");
	if (v) {
		v->CorrectTrafoObjToWorld (); 
		v->UpdateVisualDependencies(); 
	};
*/

/*	// Fackel 2
//	zCVob *torch = world->MergeVobSubtree		("VOBTREES\\TORCH_BURN2.ZEN", vobm2, zCWorld::zWLD_LOAD_MERGE_REPLACE_ROOT_VISUAL);
//	zCVob *torch = world->MergeVobSubtree		("VOBTREES\\TORCH_BURN2.ZEN", vobm2, zCWorld::zWLD_LOAD_MERGE_ADD);
	zCVob *torch = world->MergeVobSubtree		("TREE.ZEN", vobm2, zCWorld::zWLD_LOAD_MERGE_ADD);
	torch->AddRefVobSubtree	();
//	world->RemoveVob		(torch);
	world->RemoveVobSubtree	(torch);
	world->AddVob			(torch);
	torch->SetPositionWorld (0,100,0);
*/

	// PolyStrip
#ifdef ZDIETER_POLYSTRIP
	{
//		zVEC3 POS(-16000, 643, -3200);
		zVEC3 POS(0);
		streak		= zNEW(zCPolyStrip);
		vobStreak	= zNEW(zCVob);
		streak->AllocateResources	(33);
		vobStreak->SetCollDet		(FALSE);
		vobStreak->SetVisual		(streak);
		vobStreak->SetPositionWorld	(POS);
		world->AddVob				(vobStreak);
//		streak->AddSegment (zVEC3(0,150,0), zVEC3(0,150,0)+zVEC3(0,10,0)); 
//		streak->AddSegment (zVEC3(-600, 100, -600), zVEC3(-600, 100, -600)+zVEC3(0,10,0));

		lightning			= zNEW(zCLightning);
		vobLightning		= zNEW(zCVob);
		vobLightning->SetCollDet		(FALSE);
		vobLightning->SetVisual			(lightning);
		vobLightning->SetPositionWorld	(POS);
		lightning->SetLODFarDistance	(9999999);
		world->AddVob				(vobLightning);
	};
#endif

/*	{
//		camVob->SetPositionWorld (-15845,-1022,2386);
		camVob->SetPositionWorld (0,100,0);
		for (int i=0; i<199; i++) {
			InsertModel (camVob->GetPositionWorld()+zVEC3((zRandF()*2-1)*400,0,-50+(-float(i)*20)));
		};
	};
*/


//	zsndMan->StartHitSound			(vob, zCSoundManager::zSND_MAN_MEDIUM_ITEM, zCSoundManager::zSND_MAN_MEDIUM_ITEM, 0,0,0);
//	zsndMan->StartHitSound			(vob, zCSoundManager::zSND_MAN_MEDIUM_ITEM, zCSoundManager::zSND_MAN_MEDIUM_MODEL, 0,0);
//	zsndMan->StartHitSound			(vob, zCSoundManager::zSND_MAN_MEDIUM_MODEL, zCSoundManager::zSND_MAN_MEDIUM_LEVEL, 0,2);
//	zsndMan->StartHitSound			(vob, zCSoundManager::zSND_MAN_MEDIUM_MODEL, zCSoundManager::zSND_MAN_MEDIUM_LEVEL, 0,2);
//	zsndMan->StartAttackSound		(vob, zCSoundManager::zSND_MAN_MEDIUM_ITEM, zCSoundManager::zSND_MAN_MEDIUM_MODEL, 1,0);
//	zsndMan->StartDestructionSound	(vob, 2);

	if (0)
	{
		world->GetBspTree()->mesh->CalcBBox3D();
		camVob->SetPositionWorld (world->GetBspTree()->mesh->GetBBox3D().GetCenter());
	};
};

void InstallModelFace ()
{
#ifdef ZDIETER_MODEL_FACE
	if (1)
	{
		face = zCMorphMesh::Load("Hum_Head_Thief.mms");
//		face = zCMorphMesh::Load("Hum_Head_Std_Hair.mms");
//		face = zCMorphMesh::Load("Hum_Head_MA_Ponytail.mms");

		face->SetTextureVar		(0, 0);
		face->AddRandAni		(face->SearchAni("R_EYESBLINK"), 0.15F, 0.1F, 3.8F, 1.0F, 0.2F);
		face->StartAni			("H_NEUTRAL");
		if (model)	model->SetNodeVisual(model->SearchNode("BIP01 HEAD"), face, FALSE);
		else		{
			vobm2->SetVisual		(face); 
//			vobm2->RotateLocalY		(180);
			vobm2->RotateLocalZ		(90);
			vobm2->RotateLocalX		(180);
			vobm2->Move				(+0,+100,100);
		};
		face->Release();
	};
#endif
};

// ======================================================================================================================
// fuer Andre..
#if 0
zMAT4 CalcMatrixFromPoly (zCPolygon *poly)
{
	zCVertex*	v1			= 0;
	zCVertex*	v2			= 0;
	zREAL		bestDist	= zREAL_MAX;

	// 2 Vertices rauspicken
	for (int i=0; i<poly->polyNumVert; i++) {
		zCVertex *_v1 = poly->vertex[i];
		zCVertex *_v2 = poly->vertex[(i+1) % poly->polyNumVert]; 
		zREAL dist = (_v1->position-_v2->position).Length();
		if (dist < bestDist) {
			bestDist= dist;
			v1		= _v1;
			v2		= _v2;
		};
	};

	// Matrix berechenen
	zVEC3	right, up, at;
	up		= poly->GetNormal();
	right	= (v2->position - v1->position);
	right.Normalize();
	at		= up ^ right;

	// Matrix setzen
	zMAT4 mat			= Alg_Identity3D();
	mat.SetAtVector		(at);
	mat.SetUpVector		(up);
	mat.SetRightVector	(right);
	mat.SetTranslation	(v1->position);

	return mat;
};

void CalcMatrixDifference (zMAT4& mat1, zMAT4& mat2, zMAT4& res)
{
	res = Alg_Identity3D();

	// Testen, ob Matrizen �berhaupt verschieden sind
	zBOOL diff = FALSE;
	if (!mat1.GetAtVector()   .IsEqualEps (mat2.GetAtVector())	 )	diff = TRUE;
	if (!mat1.GetUpVector()   .IsEqualEps (mat2.GetUpVector())	 )	diff = TRUE;
	if (!mat1.GetRightVector().IsEqualEps (mat2.GetRightVector()))	diff = TRUE;
	zREAL trans = (mat2.GetTranslation()-mat1.GetTranslation()).Length();
	if (trans>0.1F)	diff = TRUE;		// 1mm

	if (!diff) {
		// keine Nennenswerte Differenz zw. den beiden Matrizen
		// => alle Vobs UNBERUEHRT lassen !
		return;
	};

	// Matrix Differenz berechnen
	res = mat2 * mat1.Inverse();
/*	{
		zCPolygon	*poly1 = world->GetBspTree()->mesh->polyList[0];
		zCPolygon	*poly2 = world->GetBspTree()->mesh->polyList[100];
		zMAT4		mat1, mat2, res;

		mat1 = CalcMatrixFromPoly	(poly1);
		mat2 = CalcMatrixFromPoly	(poly2);
		CalcMatrixDifference		(mat1, mat2, res);
		zVEC3 v = poly1->vertex[0]->position;
		v = res * v;
		zerr.Message ("D: padjf");
	};*/
};
#endif

// ======================================================================================================================

#if 0

class zCClassA {
public:
	void*					operator new		(size_t size)	
	{ 
		void* ptr = ::operator new (size); 
		return ptr; 
	};
	inline void* operator new	(unsigned int size, const char *file, int line)
	{
		void* ptr = ::operator new (size); 
		return ptr; 
	};
/*	inline void* operator new[]	(unsigned int size, const char *file, int line)
	{
//		void* ptr = ::operator new[] (size); 
		void* ptr = malloc (size); 
		return ptr; 
	}*/
	void					operator delete		(void* ptr)		
	{ 
		::operator delete (ptr); 
	};
/*	inline void operator delete[]( void* ptr )
	{
//		::operator delete[] (ptr); 
		free (ptr);
	}*/
};

class zCClassB : public zCClassA {
public:
	void*					operator new		(size_t size)	
	{ 
		void* ptr = ::operator new (size); 
		return ptr; 
	};
	inline void* operator new (unsigned int size, const char *file, int line)
	{
		void* ptr = ::operator new (size); 
		return ptr; 
	};
	void					operator delete		(void* ptr)		
	{ 
		::operator delete (ptr); 
	};
};

#ifdef _DEBUG
	inline void* operator new (unsigned int size, const char *file, int line)
	{
		   void *ptr = (void *)malloc(size);
		   return(ptr);
	};
	inline void operator delete(void *p)
	{
		   free(p);
	};
#endif

#ifdef _DEBUG
	#define DEBUG_NEW new(__FILE__, __LINE__)
#else
	#define DEBUG_NEW new
#endif

#define new DEBUG_NEW

#endif


	#define zzNEW( className )					 new(#className, __FILE__,__LINE__) className 
	#define zzNEW_ARRAY( className, count )		{ new className(__FILE__,__LINE__)[count]; }


void GameLoop () 
{
	//
	TestCode					();

	// Welt erzeugen
	camera						= zNEW(zCCamera);
	world						= zNEW(zCWorld);
	zcon.SetWorld				(world);

	//
	zCView *viewport			= zNEW(zCView(0,0,8191,8191,VIEW_VIEWPORT));
	screen->InsertItem			(viewport);
	camera->SetRenderTarget		(viewport); 

	// install Movement			 
/*	CreateCamMoveVobs			(); 
	camVob						= vob;
	moveVob						= vob;
*/
	mov							= zNEW(CMov_Movement(moveVob));
	mov->vob					= moveVob;
	camera->SetVob				(camVob);
	camera->Activate			();			// tmp (fuer LOD-Debug)
	zCCamera::activeCam			= camera;

	LoadMatLib					();  
	LoadLevel					();

	CompileSaveWorld			();
	CreateCamMoveVobs			(); 
								
	SetupFog					(); 
	camera->SetVob				(camVob);
	zsound->SetListener			(camVob);
								
	//							
	SetupModel					();
	TestCodePreGameLoop			();

	//
	camVob->SetCollDet			(FALSE);
	vobm2->SetCollDetStat		(TRUE);
	vobm2->SetCollDetDyn		(TRUE); 

	//							
//	zerr.SetOutputLevel			(zERR_INFO);
	zerr.Message				("D: .. Ready !");

//	zsound->SetGlobalReverbPreset (2, 1);
 
/*	zrenderer->Vid_SetScreenMode (zRND_SCRMODE_FULLSCREEN);
	zCVobScreenFX *screenFX = zNEW(zCVobScreenFX);
	world->AddVob (screenFX);
//	screenFX->StartEffect_BlendFadeIn   (10, zCOLOR(0,0,0,255));
	screenFX->StartEffect_CinemaFadeOut	(2, zCOLOR(0,0,0,255));
//	screenFX->StartEffect_FOVMorph		(10, 150);
*/


//	world->SetVobFarClipZ		(170000.0F);

	{
		int num=0;
		for (int i=0; i<zCTexture::GetStaticClassDef()->GetNumObjects(); i++)
			if (static_cast<zCTexture*>(zCTexture::GetStaticClassDef()->GetObjectByIndex(i))->GetCacheState()==zRES_CACHED_IN) num++;

		zERR_MESSAGE (0,0,"D: tex, numLiving objects: "+zSTRING(zCTexture::GetStaticClassDef()->GetNumLivingObjects()));
		zERR_MESSAGE (0,0,"D: tex, numObjectList    : "+zSTRING(zCTexture::GetStaticClassDef()->GetNumObjects()));
		zERR_MESSAGE (0,0,"D: tex, numCachedIn      : "+zSTRING(num));
	};
//world->SetVobFarClipZ (5000.0F);
//world->SetVobFarClipZ (30000.0F);
world->GetActiveSkyControler()->SetFarZ (30000.0F);
//world->GetActiveSkyControler()->SetFarZ (3000.0F);

//world->GetActiveSkyControler()->SetFillBackground (FALSE);
//zrenderer->SetPolyDrawMode (zRND_DRAW_WIRE);

	// -----------------------------------------------------------------------------------------------------------------

	// !ML
	do {  

/*		static int toggle=0;
		if (zinput->KeyPressed (KEY_1)) {
			if (toggle==0) {
				toggle=1;
//	screenFX->StartEffect_FOVMorph		(10, 0);
				vobm2->SetSleeping (FALSE);
				model = (zCModel*)(vobm2->GetVisual());
//				model->StartAni ("T_S1_2_S2");
				model->StartAni ("T_DEAD");
//				model->StartAni ("S_CHAIR_S1");

				if (zinput->KeyPressed (KEY_LSHIFT)) {
					static int reverb = 0;
					reverb++;
					reverb = reverb % zsound->GetNumReverbPresets();
					zsound->SetGlobalReverbPreset (reverb, 1);
					if (zsound->GetReverbPresetName(reverb))
						zerr.Message ("D: reverbPreset: "+zSTRING(reverb)+", "+(*(zsound->GetReverbPresetName(reverb))));

				} else 
				if (zinput->KeyPressed (KEY_LCTRL)) {
					static float perc = 0;
					perc += 0.05F;
					if (perc>1.0F) perc = 0;
					zsound->SetGlobalOcclusion (perc);
					zerr.Message ("D: occlusion: "+zSTRING(perc));
				} else 
				{
					static zCSoundFX *sfx=0;
					if (!sfx) {
						sfx = zsound->LoadSoundFX ("pch_0_q2.wav");
					}
					{
						zCSoundSystem::zTSound3DParams	params;
						params.SetDefaults	();
						zsound->PlaySound3D (sfx, vobm2, 1, &params);
					};
				};
			};
		} else toggle=0;
*/
		//
		TestCodeGameLoop				();

		//
        sysEvent						();	
		//camera.Activate				();		// temp

		zrenderer->BeginFrame			();
		world->Render					(*camera);
		world->TraceRayFirstHit(zCCamera::activeCamPos,zVEC3(0,-100000,0),(zCVob*)0,zTRACERAY_STAT_POLY | zTRACERAY_POLY_TEST_WATER);
		foundHeight = 0;
		if (world->traceRayReport.foundHit)
		{
			foundHeight = (zCCamera::activeCamPos-world->traceRayReport.foundIntersection).Length();
		}


	if (0)
	{
		static zREAL xpos=0;
		static zREAL ypos=0;
		static zCTexture *tile=0;
		if (!tile)
//			tile = zCTexture::Load (zSTRING("testFont.TGA"), zTEX_LOAD_FLAG_TILE);
//			tile = zCTexture::Load (zSTRING("surfacetest.TGA"), zTEX_LOAD_FLAG_TILE);
//			tile = zCTexture::Load (zSTRING("inv-bg.TGA"), zTEX_LOAD_FLAG_TILE);
//			tile = zCTexture::Load (zSTRING("LOADING_16BIT.TGA"), zTEX_LOAD_FLAG_TILE);
			tile = zCTexture::Load (zSTRING("LOADING.TGA"), zTEX_LOAD_FLAG_TILE);
//			tile = zCTexture::Load (zSTRING("TESTFONT.TGA"), zTEX_LOAD_FLAG_TILE);
//			tile = zCTexture::Load (zSTRING("map_ow.tga"), zTEX_LOAD_FLAG_TILE);
//			tile = zCTexture::Load (zSTRING("map_ow3.tga"), zTEX_LOAD_FLAG_TILE);
//			tile = zCTexture::Load (zSTRING("GOTHIC LOGO 804_16BIT.TGA"), zTEX_LOAD_FLAG_TILE);
//			tile = zCTexture::Load (zSTRING("BLUEBEAM.TGA"), zTEX_LOAD_FLAG_TILE);
//		zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_ALWAYS);
//		zrenderer->SetBilerpFilterEnabled	(FALSE);
		zREAL S = 1.0F;
		zREAL xdim	= (zREAL)tile->GetTextureInfo().refSizeX;
		zREAL ydim	= (zREAL)tile->GetTextureInfo().refSizeY;
		xdim	= 639;
		ydim	= 479;
		zrenderer->DrawTile (	tile,
								zVEC2(xpos,ypos),
								zVEC2(xpos+xdim*S,ypos+ydim*S),
								1.0F,
//								zVEC2(0.5039,0.1601),
//								zVEC2(0.6,0.230),
								zVEC2(0.0,0.0),
								zVEC2(1.0,1.0),
								zCOLOR(255,255,255,255)
								);
//		zrenderer->SetBilerpFilterEnabled	(TRUE);
//		zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_LESS);
		zREAL step = 2.0F;
		if (zinput->KeyPressed(KEY_LSHIFT))
		{
			if (zinput->KeyPressed(KEY_LEFT))	xpos -= step;
			if (zinput->KeyPressed(KEY_RIGHT))	xpos += step;
			if (zinput->KeyPressed(KEY_UP))		ypos -= step;
			if (zinput->KeyPressed(KEY_DOWN))	ypos += step;
		};
	};

		zCView::GetInput				();
		if (!zcon.IsVisible())
		{
			GetInput					(*moveVob, mov);
		};

		Freelook						(camVob, moveVob);

		TestCodeGameLoopLFB				();
		TestCodeGameLoopNetTest			();
		screen->DrawItems				();
		zrenderer->Vid_Unlock			();

		Info							(viewport);

		zrenderer->EndFrame				();
		zrenderer->Vid_Blit				();

		world->AdvanceClock				(timeStep);

		TestCodeMoveRecorder			();
/*		{
			static zVEC4 fadeCol(255,255,255,255);
			zREAL t			= zREAL(zSin(ztimer.GetTotalTimeF() / 1000.0F)+1) * 0.5F;
			zVEC4 resCol	= fadeCol * zREAL(t);
	//		camera->SetRenderCinemaScope	(zCOLOR (0,0,0,255));
			zCOLOR col;
			col.SetRGBA	(int(resCol[0]), int(resCol[1]), int(resCol[2]), int(resCol[3]));
			camera->SetRenderScreenFade		(col);
//			camera->SetRenderScreenFade		(zCOLOR (0,100,100,10));
	//		zrenderer->Vid_SetGammaCorrection (0.5F);
		};
*/

/*		if (model)
		if (zinput->KeyPressed(KEY_LSHIFT))
		{ 
			static int body_v	= 0;
			static int body_c	= 0;
			static int armor_v	= 0;
			if (zinput->KeyPressed(KEY_LEFT))	body_v	= (body_v+1)  % 3;
			if (zinput->KeyPressed(KEY_RIGHT))	body_c	= (body_c+1)  % 3;
			if (zinput->KeyPressed(KEY_UP))		armor_v = (armor_v+1) % 3;

			zerr.Message ("D: "+zSTRING(body_v)+zSTRING(body_c)+zSTRING(armor_v));
			zSTRING meshLib ("HUM_GURM_ARMOR");
			model->SetMeshLibTexture 	(meshLib, 0, body_v , &zSTRING("BODY"));		// skin tex variation
			model->SetMeshLibTexture 	(meshLib, 1, body_c , &zSTRING("BODY"));		// skin tex color
			model->SetMeshLibTexture 	(meshLib, 0, armor_v, &zSTRING("ARMOR"));	// armor tex variation
		}; */

/*		if (face)
		if (zinput->KeyPressed(KEY_LSHIFT))
		{ 
			const int NUM = 2;
			static int channel		= 0;
			static int channelVar[NUM];

			if (zinput->KeyToggled(KEY_LEFT))	channel = (channel+1) % NUM;
			if (zinput->KeyToggled(KEY_RIGHT))	channel = (channel-1) % NUM;
			zClamp (channel, 0, NUM);
			if (zinput->KeyToggled(KEY_UP))		channelVar[channel]= (channelVar[channel]+1) % 20;
			if (zinput->KeyToggled(KEY_DOWN))	channelVar[channel]= (channelVar[channel]-1) % 20;
			zClamp (channelVar[channel], 0, 30);

			zerr.Message ("D: "+zSTRING(channel)+","+zSTRING(channelVar[0])+","+zSTRING(channelVar[1]));
			face->SetTextureVar			(channel, channelVar[channel]);
		}; */

/*
#ifdef ZDIETER_PROGMESH
		if (pmProto)
		if (zinput->KeyPressed(KEY_Z))
		{
//			if (zinput->KeyPressed(KEY_LSHIFT))	pmProto->maxVert	= zMax (0, pmProto->maxVert-1);
//			else								pmProto->maxVert++;
			zREAL D = 0.005F;
			if (zinput->KeyPressed(KEY_LSHIFT))	pmProto->actVertPerc	-= D;
			else								pmProto->actVertPerc	+= D;
//			zerr.Message ("D: maxVert: "+zSTRING(pmProto->maxVert));
		};
#endif
*/
		{
			zREAL xpos, ypos, zpos;
			zinput->GetMousePos (xpos, ypos, zpos);

//			zERR_MESSAGE (1, 0, "D: Pos: "+zSTRING(xpos,2)+" / "+zSTRING(ypos,2));
			if (zinput->KeyPressed (KEY_LCTRL))
			{
				zERR_MESSAGE (1, 0, "D: Control");
			};
			if (zinput->KeyPressed (KEY_LALT))
			{
				zERR_MESSAGE (1, 0, "D: Alt");
			};
		};
	} while (!usrWantQuit); 

	// -----------------------------------------------------------------------------------------------------------------
	zcon.Hide();
	assert(_CrtCheckMemory());

#ifdef ZDIETER_NET_TEST
	zerr.Message ("D: Packet-Size, min: "+zSTRING(minPacketSize)+", max: "+zSTRING(maxPacketSize));
#endif

	// Cleanup
	// hier um den Code zu testen und keine Leaks zurueckzulassen ...
	delete		viewport;
	zRELEASE	(world);
	delete		camera;
	zRELEASE	(playerAI);
}
/*

__int16 a;

  ATHLON

void _m_prefetch( void* p );
Loads a 32-byte cache line into L1 data cache and sets the cache line state to exclusive. If the line is already in the cache or if a memory fault is detected, then the intrinsic function has no effect. The variable p specifies the address of the cache line to be loaded.

void _m_prefetchw( void* p );
Loads a 32-byte cache line into L1 data cache and sets the cache line state to modified. If the line is already in the cache or if a memory fault is detected, then the intrinsic function has no effect. The variable p specifies the address of the cache line to be loaded.

  SSE

void _mm_prefetch(char * p , int i );
PREFETCH
Loads one cache line of data from address p to a location closer to the processor. The value i specifies the type of prefetch operation: the constants _MM_HINT_T0, _MM_HINT_T1, _MM_HINT_T2, and _MM_HINT_NTA, corresponding to the type of prefetch instruction, should be used.


	Transforming normals using a non-orthonormal (so with scaling/shearing) transformation matrix is done properly by transforming using the transposed version of inversed matrix. 

	Note that when to matrix is orthonormal, the transposed inverse of the matrix is just the matrix itself. 

	Plane.Constant += Plane.Normal.Dot(InverseMatrix.Translation); 
	Plane.Normal = InverseMatrix.Transposed().Rotate(Plane.Normal); 

	// As scaling may have been applied, the normal has to be normalized again. 
	// We also need to "normalize" the plane constant by this. 
	float ooscale = 1.0f / fsqrt(Plane.Normal.SquareLength()); 
	Plane.Normal *= ooscale; 
	Plane.Constant *= ooscale;


*/

