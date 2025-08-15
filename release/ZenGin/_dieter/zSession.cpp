/******************************************************************************** 
 
     $Workfile:: zSession.cpp        $                 $Date:: 16.03.01 15:36   $
     $Revision:: 15                  $              $Modtime:: 16.03.01 15:35   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH

   Description::
   Session

 * $Log: /current_work/ZenGin/_Dieter/zSession.cpp $
 * 
 * 15    16.03.01 15:36 Speckels
 * 
 * 14    15.03.01 14:01 Speckels
 * 
 * 13    7.02.01 12:53 Moos
 * 
 * 12    30.01.01 15:19 Speckels
 * 
 * 11    15.01.01 18:40 Moos
 * 
 * 10    12.01.01 16:53 Edenfeld
 * 
 * 9     31.08.00 17:04 Hildebrandt
 * 
 * 8     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 7     15.08.00 17:43 Speckels
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 6     31.07.00 19:18 Speckels
 * 
 * 5     21.07.00 14:28 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 2     22.03.00 2:59 Hildebrandt
 * zenGin 088a
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 15 $ ($Modtime: 16.03.01 15:35 $)

#include <zCore.h>
#include <zSession.h>
#include <zConsole.h>
#include <zParser.h>
#include <zCCSManager.h>
#include <zaicamera.h>

#include <zAccount.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

///////////////////////////////////////////////////////////////


zCSession::zCSession()
{	
	world		= 0;		
	aiCam		= 0;	
	camVob		= 0;
	viewport	= 0;
	csMan		= 0;
	camera		= 0;
}

zCSession::~zCSession()
{
	Done();
}

void zCSession::Done()
{	
	zRELEASE(world);		
	zRELEASE(aiCam);

    if (camVob)    
        camVob->SetAI(NULL); // [Moos] Leakfix: zirkuläre Referenzen

	zRELEASE(camVob);	
	zRELEASE(csMan);	// nicht bevor die Welt released wurde		
	delete camera;		camera	= 0;
	delete viewport;	viewport= 0;	
};

void zCSession::Init()
{	
	DesktopInit			();		

	// Konsole
	zcon.SetWorld		(world);
	zcon.SetParser		(&parser);	
	
	sysEvent();

	// initialisiere den cutscene-player
	CutsceneSystemInit	();

	sysEvent();
}

void zCSession::DesktopInit()
{
	// ...Setting up the viewport....
	viewport=  zNEW(zCView			(0,0,8191,8191,VIEW_VIEWPORT));
	screen	-> InsertItem			(viewport);
	viewport-> SetFont				(0);
}

void zCSession::CutsceneSystemInit()
{
	// ***************
	// Cutscene-Player
	// ***************
	if (!csMan) csMan = zfactory->CreateCSManager();

//	#ifdef NDEBUG
	csMan->LibForceToLoad();
//	#endif

	// hier KEIN Language-Setup
}

void zCSession::Render ()
{
	// Tageszeit
//	sky  = world -> GetActiveSkyControler();
//	sky -> SetTime (wldTimer -> GetSkyTime());

	// Rendering wird durchgeführt
	world->Render					(*camera);	

	// Views auf dem Viewport updaten
	zrenderer->Vid_BeginLfbAccess	();
	screen	 ->DrawItems			();		
	zrenderer->Vid_EndLfbAccess		();

	zrenderer->Vid_Unlock			();			// Video freigeben

//	world->AdvanceClock				(timeStep);
}

void zCSession::RenderBlit()
{
	zrenderer->Vid_Blit();
}

void zCSession::CamInit()
{
	// ********************
	// Camera - Init
	// ********************
	
	delete camera;
	camera  = zNEW(zCCamera);
	camera -> SetRenderTarget	(viewport);

	// ********************
	// Camera - AI - Init
	// ********************

	zRELEASE (aiCam);
	if (camVob) camVob->SetAICallback(0);
	zRELEASE (camVob);
	aiCam	=  zCAICamera::Create();
	camVob	=  zNEW(zCVob		());
	camVob->SetObjectName("ZCAICAMERA");
	if (!camVob->GetHomeWorld()) world ->AddVob(camVob); 
	aiCam	-> SetVob			(camVob);

	camVob  ->SetCollDet		(FALSE);
	camVob  ->SetAICallback		(aiCam);
	camVob	->SetSleeping		(FALSE);
	camVob  ->SetPhysicsEnabled	(FALSE);	
	camera  ->SetVob			(camVob);
	zsound -> SetListener		(camVob);
}

void zCSession::CamInit(zCVob* camera_vob, zCCamera* cam)
{
	// ********************
	// Camera - Init
	// ********************
	
	camera = cam;
	camera->SetRenderTarget		(viewport);

	// ********************
	// Camera - AI - Init
	// ********************
	
	camVob = camera_vob;
	world	->AddVob			(camVob);
	camVob  ->SetCollDet		(FALSE);
	camVob	->SetSleeping		(FALSE);
	camVob  ->SetPhysicsEnabled	(FALSE);	
	camera  ->SetVob			(camVob);
	zsound -> SetListener		(camVob);
}

zCWorld* zCSession::GetWorld() 
{
	return world;
};			

void zCSession::SaveWorld(const zSTRING& levelpath, zCWorld::zTWorldSaveMode savemode, BOOL savemesh, BOOL saveBinary)
{

};

zBOOL zCSession::LoadWorld(const zSTRING& fileName, const zCWorld::zTWorldLoadMode loadMode)
{
	return FALSE;
};

// Time
//	virtual void			Pause						();
//	virtual void			Unpause						();

void zCSession::SetTime (int  day, int  hour, int  min)
{
};

void zCSession::GetTime	(int& day, int& hour, int& min)
{
	
};

void zCSession::SetWorld(zCWorld* _world)
{
	world = _world;
	world->SetOwnerSession(this);
};


#pragma warning ( default:4244 )
