/******************************************************************************** 
 
     $Workfile:: zMoving.h            $                $Date:: 4.12.00 17:45    $
     $Revision:: 9                    $             $Modtime:: 4.12.00 17:44    $
        Author:: Hildebrandt                                                          
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:

 * $Log: /current_work/zengin_work/_Dieter/zMoving.h $
 * 
 * 9     4.12.00 17:45 Hildebrandt
 * 
 * 8     20.09.00 22:31 Rueve
 * typedef
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 6     22.07.00 2:06 Hildebrandt
 * 
 * 5     21.07.00 15:11 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 4     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 9 $ ($Modtime: 4.12.00 17:44 $)

#ifndef __ZMOVING_H__
#define __ZMOVING_H__


#ifndef __Z3D_H__
#include "z3D.h"
#endif

#ifndef __ZOPTION_H__
#include "zoption.h"
#endif

#ifndef __ZVOB_H__
#include "zVob.h"
#endif

#ifndef __ZDISK_H__
#include <zDisk.h>
#endif

// ======================================================================================================================

class zENGINE_API zCMoveRecorder {
public:
	enum { DEF_NUM_SAMPLES=256 };
	enum { MOR_IDLE=0, MOR_PLAYBACK=1, MOR_RECORD=2 };
	struct zTMOR_Sample {
		zMATRIX4	trafoObjToWorld;
//		zPOINT3		positionWorld;
	};
	zSTRING					name;
	zCVob					*vob;
	zCArray<zTMOR_Sample>	samples;
	int						state;
	int						ctr;
	zBOOL					looping;
	zREAL					startTime;

	zCMoveRecorder() : samples (DEF_NUM_SAMPLES) {
		looping = FALSE;
		ctr		= 0;
		state	= MOR_IDLE;
	};
	void PrintTime() {
		zREAL absTime = (ztimer.GetTotalTimeF() - startTime) / zREAL(1000.F);
		zerr.Message ("D: MOR: time: "+zSTRING(absTime,4)+" sec, frames: "+zSTRING(samples.GetNumInList())+
			", fps: "+zSTRING(zREAL(samples.GetNumInList())/absTime,4));
	};
	void	StartRecord(zCVob *inVob, const zSTRING& fileName="DEFAULT") {
		name	= fileName;
		vob		= inVob;
		state	= MOR_RECORD;
		samples.EmptyList();
		zerr.Message ("D: MOR: Start Recording...");
		startTime = ztimer.GetTotalTimeF();
	};
	void	StopRecording	() { 
		zerr.Message ("D: MOR: ...Stop Recording");
		PrintTime();
		if (state==MOR_RECORD) {
			zoptions->ChangeDir (DIR_DATA);
//			zFILE file(name+".MOR");
			zFILE* file = zfactory->CreateZFile(name+".MOR");
			file->Create();
			for (int i=0; i<samples.GetNumInList(); i++) {
				file->Write (&(samples[i]), sizeof(samples[i]));
			};
			file->Close();
			delete file;
		};
		state=MOR_IDLE; 
	};
	void	StartPlayback	(zCVob *inVob, zBOOL loop=FALSE, const zSTRING& fileName="DEFAULT") {
		name = fileName;
		zoptions->ChangeDir (DIR_DATA);
//		zFILE file(fileName+".MOR");
		zFILE* file = zfactory->CreateZFile(fileName+".MOR");
		file->Open();
		if (!file->Exists()) {
			zerr.Message ("D: MOR: File not found: "+fileName);
			return;
		};

		int num				= file->Size() / sizeof(zTMOR_Sample);
		samples.EmptyList	();
		samples.AllocAbs	(num);

		zTMOR_Sample sample;
		for (int i=0; i<num; i++) {
			file->Read (&(sample), sizeof(sample));
			samples.InsertEnd (sample);
		};
		file->Close();
		delete file;

		ctr		= 0;
		state	= MOR_PLAYBACK;
		looping = loop;
		vob		= inVob;
		zerr.Message ("D: MOR: Start Playback...");
		startTime = ztimer.GetTotalTimeF();
	};
	void	StopPlayback	() { 
		state=MOR_IDLE; 
		zerr.Message ("D: MOR: ...Stop Playback");
		PrintTime();
	};

	void	DoUpdate		() {
		if (state==MOR_RECORD) {
			zTMOR_Sample sample;
			sample.trafoObjToWorld	= vob->trafoObjToWorld;
//			sample.positionWorld	= vob->GetPositionWorld();
			samples.Insert (sample);
		} else
		if (state==MOR_PLAYBACK) {
			if (ctr>=samples.GetNumInList()) {
				if (!looping) state = MOR_IDLE;
				ctr=0;
				PrintTime();
				startTime = ztimer.GetTotalTimeF();
			};
			vob->SetTrafoObjToWorld (samples[ctr].trafoObjToWorld);
//			vob->SetPositionWorld	(samples[ctr].positionWorld);
			ctr++;
		};
	};
	zBOOL IsRecording	() const { return state==MOR_RECORD; };
	zBOOL IsPlayingBack	() const { return state==MOR_PLAYBACK; };
};

// ======================================================================================================================

typedef double mov_typ;

class zENGINE_API CMov_Movement {
	// Time Correction
	zDWORD   oldtime,now;
	mov_typ time_corr;
public:	
	// Vob to move
	zCVob *vob;
public:
	mov_typ force_x,force_y,force_z,force_rot;
	mov_typ xspeed,yspeed,zspeed,rotspeed;
	
	CMov_Movement ( zCVob *vob );

	// Normale Bewegung ( Gehen )
	void Movement ();
	void IncreaseSpeed (mov_typ d);
};

// ======================================================================================================================

#endif