#include "zcore.h"
#include "zsound.h"
#include "zinput.h"
#include "zvob.h"
#include "zworld.h"
#include "zparticle.h"

//#define CHASE_DEBUG

#ifdef CHASE_DEBUG

//#define TEST_SOUND
//#define TEST_POLYSTRIP
//#define TEST_LIGHTNING

#ifdef TEST_LIGHTNING
#include "zpolystrip.h"
#endif
 
#ifdef TEST_POLYSTRIP
#include "zpolystrip.h"
#endif

#ifdef COMPILING_GOTHIC
#include "oNpc.h"
#endif

void zLocal_Startup()
{
};

void zLocal_Shutdown()
{
};




void zLocal_PerFrame()
{


#ifdef TEST_SOUND

	static zCArray<zCSoundFX*>							sndList;
	static zCArray<zCVob*>								sndVobList;
	static zCArray<zTSoundHandle>						sndHandleList;
	static zCArray<zCSoundSystem::zTSound3DParams>		sndParamsList;

	if (zinput->KeyPressed(KEY_LALT) && zinput->KeyPressed(KEY_S))
	{
		sysIdle(100);

		zCSoundSystem::zTSound3DParams params;
		zCSoundFX *snd = zNEW(zCSoundFX);

		params.SetDefaults();

		if (zinput->KeyPressed(KEY_LSHIFT))	snd = zsound->LoadSoundFX("testadpcm.WAV");
		else								snd = zsound->LoadSoundFX("test.WAV"	 );
		snd->SetLooping(TRUE);

   		zCVob *vob = zNEW(zCVob);
		vob->SetVisual					("invisible_zCVobSound.3ds");	  
		vob->SetShowVisual				(TRUE);
		vob->SetVobName					("Sound-Vob " + zSTRING(sndList.GetNumInList()+1));
		vob->SetDrawBBox3D				(TRUE);
		vob->SetPositionWorld			(zCCamera::activeCam->GetVob()->GetPositionWorld());

		zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVobRelease(vob);

		vob->SetSleeping				(FALSE);
		vob->SetCollDetStat				(FALSE);
		vob->SetCollDetDyn				(FALSE);
		vob->SetIgnoredByTraceRay		(TRUE);

		zTSoundHandle hnd = zsound->PlaySound3D(snd,vob,zSND_SLOT_NONE,&params);

		if (hnd) 
		{
			sndList			.InsertEnd(snd);
			sndHandleList	.InsertEnd(hnd);
			sndVobList		.InsertEnd(vob);
			sndParamsList	.InsertEnd(params);
		}
		else 
		{ 
			int brk = 0;
		}

	}
	else if (zinput->KeyPressed(KEY_LALT) && zinput->KeyPressed(KEY_D))
	{
		sysIdle(100);
		if (sndList.GetNum()>0) {
			int lastEle = sndList.GetNum()-1;
			zCSoundFX *snd = sndList[lastEle];
			zsound->StopSound(sndHandleList[lastEle]);
			snd->Release();
			sndVobList[lastEle]->RemoveVobFromWorld();

			sndList			.RemoveIndex(lastEle);
			sndVobList		.RemoveIndex(lastEle);
			sndHandleList	.RemoveIndex(lastEle);
			sndParamsList	.RemoveIndex(lastEle);
		}
	}

	for (int i=0; i<sndList.GetNum(); i++)
	{

		zPOINT3 cp = zCCamera::activeCam->GetVob()->GetPositionWorld();
		zPOINT3 vp = sndVobList[i]->GetPositionWorld();
		zCWorld *world = zCCamera::activeCam->GetVob()->GetHomeWorld();
		
		// calc obstruction 

		if (world->TraceRayFirstHit(vp,cp-vp,(zCVob*)0,zTRACERAY_STAT_POLY)) sndParamsList[i].obstruction+= 0.01F;
		else sndParamsList[i].obstruction-= 0.01F;

		zClamp01(sndParamsList[i].obstruction);

		zsound->UpdateSound3D(sndHandleList[i],&sndParamsList[i]);

//		zERR_MESSAGE(5,0,"C: LocalPerFrame: dist to cam: " + zSTRING( (cp-vp).Length() ));
	}

#endif


#ifdef TEST_MAGIC
#endif


#ifdef TEST_LIGHTNING
	if (zinput->KeyPressed(KEY_LALT) && zinput->KeyPressed(KEY_L))
	{

		zCVob *vob = new zCVob;
		zCLightning *lightning = new zCLightning;
		
		zPOINT3 cp = zCCamera::activeCam->GetVob()->GetPositionWorld();

		vob->SetPositionWorld			( cp + 400 * zCCamera::activeCam->GetVob()->GetAtVectorWorld() );

		zPOINT3 vp = vob->GetPositionWorld();

		lightning->Generate(cp,vp);
		lightning->rootBolt.material->SetTexture(zSTRING("lightning_a1.tga"));
		for (int i=0; i<lightning->rootBolt.childList.GetNum(); i++)
		{
			lightning->rootBolt.childList[i]->material->SetTexture(zSTRING("lightning_a1.tga"));
		}

		vob->SetVisual					(lightning);	  
		vob->SetShowVisual				(TRUE);
		vob->SetVobName					("Lightning-Vob");
		vob->SetDrawBBox3D				(TRUE);

		zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVobRelease(vob);

		vob->SetSleeping				(FALSE);
		vob->SetCollDetStat				(FALSE);
		vob->SetCollDetDyn				(FALSE);
	}

#endif

#ifdef TEST_POLYSTRIP
#ifdef COMPILING_GOTHIC

	static zCPolyStrip* polyStrip = 0;
	static zCVob*		weaponTrailVob;

	if (!polyStrip)
	{
		polyStrip		= zNEW(zCPolyStrip);
		weaponTrailVob	= zNEW(zCVob);
		weaponTrailVob	->SetDontWriteIntoArchive(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
		weaponTrailVob	->SetCollDet			(FALSE);
		weaponTrailVob	->BeginMovement			();
		weaponTrailVob	->SetPositionWorld		(oCNpc::player->GetPositionWorld());
		weaponTrailVob	->SetVisual				(polyStrip);

		oCNpc::player->GetHomeWorld()->AddVob(weaponTrailVob);
		weaponTrailVob	->EndMovement			();

		//
		polyStrip->SetAlphaFadeSpeed	(0.1F);
//		polyStrip->SetAlphaFadeSpeed	(1.3F);
		polyStrip->material->SetTexture	(zSTRING("ZWEAPONTRAIL.TGA"));
		polyStrip->AllocateResources	(128);
		zERR_ASSERT (polyStrip->material);
		polyStrip->material->SetAlpha	(135);

		//
		polyStrip->Release();
	};
	polyStrip->AddSegment(oCNpc::player->GetPositionWorld()+zVEC3(0,150,0), oCNpc::player->GetPositionWorld());
	polyStrip->CalcBBox3D	();					// FIXME !!!!

#endif
#endif

	if (zinput->KeyPressed(KEY_LALT) && 
		zinput->KeyPressed(KEY_B) )
	{
		static int breaked = FALSE;
		if (!breaked) {	
			__asm { int 3 }; 
			breaked = TRUE; 
		};
	}

};

#else

void zLocal_Startup()
{
};

void zLocal_Shutdown()
{
};

void zLocal_PerFrame()
{
};

#endif
