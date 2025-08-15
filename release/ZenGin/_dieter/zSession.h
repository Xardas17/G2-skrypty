/******************************************************************************** 
 
     $Workfile:: zSession.h           $                $Date:: 30.01.01 15:19   $
     $Revision:: 8                    $             $Modtime:: 30.01.01 15:05   $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Dieter/zSession.h $
 * 
 * 8     30.01.01 15:19 Speckels
 * 
 * 7     4.12.00 17:48 Hildebrandt
 * 
 * 6     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 5     31.07.00 19:18 Speckels
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 2     22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 1     15.03.00 23:50 Hildebrandt
 *********************************************************************************/


#ifndef __ZSESSION_H__
#define __ZSESSION_H__

#ifndef __ZVIEW_H__
#include <zView.h>
#endif

#ifndef __ZWORLD_H__
#include <zWorld.h>
#endif

class zCViewProgressBar;
class zCView;
class zCCamera;
class zCAICamera;
class zCVob;
class zCCSManager;


/*	------------------------------------------------------------------

	class zCSession

	26.07.00	[Speckels]
				csplayer entfernt und csManager hinzugefuegt. 
				Neue bzw. umbenannte Methoden GetCutsceneManager und CutsceneSystemInit
				Reihenfolge der Deinitialisierung (zRELEASE: csManager nach World) geaendert				
				Methode SetWorld hinzugefuegt (protected)
				Methode GetViewport hinzugefuegt

	------------------------------------------------------------------ */

class zCSession : public zCInputCallback 
{
public:

	zCSession											();
	virtual ~zCSession									();
	
	// Engine :
	virtual void			Init						();			
	virtual void			Done						();
	virtual void			Render						();
	virtual void			RenderBlit					();

	// Note : Kameraverwaltung ist noch sehr undurchsichtig, auf Engine vereinheitlichen ?
	// Wer erzeugt wo welche Vobs, wer entfernt diese, was passiert bei Kamerafahrten...
	virtual void			CamInit						();
	virtual void			CamInit						(zCVob* camera_vob, zCCamera* cam);
	virtual	void			SetCamera					(zCCamera *cam) { camera = cam;		};
	virtual zCCamera*		GetCamera					() const		{ return camera;	};
	virtual zCAICamera*		GetCameraAI					() const		{ return aiCam;		};
	virtual zCVob*			GetCameraVob				() const		{ return camVob;	};
	virtual	zCView*			GetViewport					() const		{ return viewport;  };
	
	// Aktive Welt zurückliefern 	
	virtual zCWorld*		GetWorld					();

 	virtual void			SaveWorld					(const zSTRING& levelpath, zCWorld::zTWorldSaveMode savemode, BOOL savemesh = FALSE, BOOL saveBinary=TRUE);
	virtual	zBOOL			LoadWorld					(const zSTRING& fileName, const zCWorld::zTWorldLoadMode loadMode);

	virtual zCCSManager*	GetCutsceneManager			() { return csMan; };

	//
//	virtual void			Pause						();
//	virtual void			Unpause						();
	
	// Time
	virtual void			SetTime						(int  day, int  hour, int  min);
	virtual void			GetTime						(int& day, int& hour, int& min);

protected:

	virtual void			SetWorld					(zCWorld* _world);

	virtual void			DesktopInit					();
	virtual void			CutsceneSystemInit			();

private:	

	zCCSManager				*csMan;
	zCWorld					*world;
	zCCamera				*camera;
	zCAICamera				*aiCam;
	zCVob					*camVob;
	zCView					*viewport;
};

#endif
 
