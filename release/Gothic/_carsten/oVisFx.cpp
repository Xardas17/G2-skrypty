// oVisFX.cpp
// Carsten Edenfeld

/****************************************************************************************************


Wishlist:
---------

	Acceleration
    Blitzeffekt/Polystripes
	Morphmeshes
	other trj-move/trj-ani modi
	timescale
	

TODO/Known-Bugs:
----------------
  
  Perf. Problem: Ein Child muss auch eine AI haben, da sonst ein connected PFX Visual wenn es sich selbst löscht,
  nicht die AI löscht, und die AI keine Möglichkeit hat festzustellen, ob es noch in der Welt ist.
  (Noch aktuell?)

  Snds pro Keys releasen/stoppen ? Muss das sein ? Nur für looped Sounds, oder ?

  Volumen Spells wieder funktionsfähig machen (Massdeath)
  5% aller Fälle keine FB Kollision
  Burning Kacke!

****************************************************************************************************/

#include "zcore.h"
#include "zWorld.h"
#include "zModel.h"
#include "zKBSplines.h"
#include "zDbgTools.h"
#include "oVisFX.h"
#include "oVisFX_Edit.h"
#include "zPolystrip.h"
#include "z3d.h"
#include "zEventMan.h"
#include "zMorphMesh.h"
#include "zcore.h"
#include "onpc.h"
#include "onpc_damage.h"
#include "oaishoot.h"
#include "ospell.h"
#include "zvobmisc.h"
//#include "oVisFX_Lightning.h"
#include "oVisFX_MultiTarget.h"
#include <oNpcMessages.h>
#include <ogame.h>
#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

#include <zAccount.h>

#define VFX_VERSION zSTRING("v0.5")

const float AUTODISPOSE_TIME		= 2.0f;
const float AUTODISPOSE_TIME_INV	= 1/AUTODISPOSE_TIME;
const int   zVFX_MAX_CONTINOUS_COLL = 20;
const int	zVFX_SOUNDSLOT_DEFAULT  = 7;

#ifndef _DUMMYVFX_

zCArray<oCVisualFX> s_worldVisFXList;
// -------------------------------------------------------------------------------------------------------
// STATICS
// -------------------------------------------------------------------------------------------------------
static zCArray<oCVisualFX*>homeLessFXList;					// for save games


zCParser*	oCVisualFX::fxParser	= 0;	


static zVEC3 String2Vec3 (const zSTRING& s)
{
	zVEC3 v;
	v[0] = s.PickWord (1, " ", " ").ToFloat();
	v[1] = s.PickWord (2, " ", " ").ToFloat();
	v[2] = s.PickWord (3, " ", " ").ToFloat();
	return v;
};

static zCOLOR String2Color(const zSTRING& s)
{
	zCOLOR v;
	int r = s.PickWord (1, " ", " ").ToInt();
	int g = s.PickWord (2, " ", " ").ToInt();
	int b = s.PickWord (3, " ", " ").ToInt();
	int a = s.PickWord (4, " ", " ").ToInt();
	v.SetRedByte	(r);
	v.SetGreenByte	(g);
	v.SetBlueByte	(b);
	v.SetAlphaByte  (a);
	return v;
};

static inline zPOINT3 CalcAziElevRange(const float &aziDeg,const float &elevDeg,const float &rng, const zMAT4 &trafoObjToWorld)
{
	const zREAL	FAK = float(M_PI * ((1.0) / 180.0));
    zREAL azi = (180-aziDeg)  * FAK;
    zREAL elev= (elevDeg+360) * FAK;

	zPOINT3 mid		= trafoObjToWorld.GetTranslation();
	zVEC3	at		= trafoObjToWorld.GetAtVector();
	zVEC3	right   = trafoObjToWorld.GetRightVector();
	zPOINT3 res		= mid - (10 * at);
	float	range   = rng * 100;
	//						  ->  ->           ->            ->
	// Setup circle in Space. x = m + r*cos(b)*u0 + r*sin(b)*v0
	zERR_ASSERT(at.Length()>0);

	zVEC3 u0 = at;
	zVEC3 v0 = right;

	if (zAbs(at[VY]) != 1)  u0[VY]=0.0F; v0[VY]=0.0F;  // hier nicht mehr nötig ?

	u0.Normalize(); v0.Normalize();

	// get new azimuth position on circle
	zREAL fcos, fsin;
	zSinCosApprox(azi, fsin, fcos);
	res =  mid +   (range * fcos) * u0 + 
		           (range * fsin) * v0 ;

	// find u0 and v0 for elevation circle 
	res[VY] = mid[VY];
	u0 = (res-mid).Normalize();

	// Get orthogonal up (=v0) vec. from new target at-vec.
	v0 = zPOINT3 (0,1,0);
	v0 = (v0 + (-(v0 * u0) * u0)).Normalize(); // nötig ???

	// get new elevation position on circle

	zSinCosApprox(elev, fsin, fcos);
	return  zPOINT3( mid + (range * fcos) * u0 + 
				           (range * fsin) * v0 );
}

static zBOOL ArraysEqual(const zCArray<zCVob*>&a1, const zCArray<zCVob*>&a2)
{
	if (a1.GetNumInList()!=a2.GetNumInList()) return FALSE;
	for (int i=0; i<a1.GetNumInList(); i++) if (a1[i]!=a2[i]) return FALSE;
	return TRUE;
}

// -------------------------------------------------------------------------------------------------------
// oCTrajectory
// -------------------------------------------------------------------------------------------------------
void  oCTrajectory :: Calc	()
{
	// initialize spline
	if (keyList.GetNumInList()<2) return;

	if (mode & EM_TRJ_SPLINE) 
	{
		assert(spl==0);
		spl = zNEW(zCKBSpline());

		zCPositionKey *first = zNEW( zCPositionKey() );
		zCPositionKey *last  = zNEW( zCPositionKey() );

		first->SetMat( keyList[0]->GetMat() );
		last ->SetMat( keyList[keyList.GetNumInList()-1]->GetMat() );

		keyList.InsertAtPos(first,0);
		keyList.InsertEnd  (last);

		for (int i=0; i<keyList.GetNumInList(); i++)
		{
			keyList[i]->SetTime((float)i);
		}

		spl->Initialize(keyList);

		length = spl->Length();
	} 
	else if (mode & EM_TRJ_LINE) 
	{
		for (int i=1; i<keyList.GetNumInList(); i++)
		{
			length += (keyList[i]->GetPosition() - keyList[i-1]->GetPosition()).Length();
		}
	}
	else if (mode & EM_TRJ_TARGET) 
	{
		length = (keyList[1]->GetPosition() - keyList[0]->GetPosition()).Length();
	}
}

void oCTrajectory :: Changed()
{
	if (spl) spl->Changed();
};

zMAT4 oCTrajectory :: Interpolate(const float dist)
{
	// FIXME: Da muss es auch bessere Methoden geben !
	res = Alg_Identity3D();

	if (mode & EM_TRJ_SPLINE) 
	{
		if (!spl) return res;
		spl->InterpolateN(dist/spl->Length(), res);
		lastKey = spl->GetLastKey();
		return res;
	};

	if (keyList.GetNumInList()==0) return res;
	
	if (dist >= length) 
	{
		res.SetTranslation(keyList[keyList.GetNumInList()-1]->GetPosition());
		return res;
	}

	float l = 0;

	for (int i=1; i< keyList.GetNumInList(); i++) 
	{
		float partial = (keyList[i]->GetPosition()-keyList[i-1]->GetPosition()).Length();

		if ( partial+l >= dist) 
		{
			zVEC3 at	= (keyList[i]->GetPosition()-keyList[i-1]->GetPosition() ).Normalize();
			zPOINT3 pp	= keyList[i-1]->GetPosition() + (dist-l) * at;
			res			= GetPoseOfHeading(pp,at);
			lastKey		= i-1;

			return res;
		}

		l += partial;
	}
	// savety. normally should be never here. cond. above does not operate correctly!  (if (partial >= dist) fails sometimes when dist ~ maximum dist )
	// (compiler bug ?)
	if (i>1) 
	{
		zVEC3 at	= (keyList[i-2]->GetPosition()-keyList[i-1]->GetPosition() ).Normalize();
		zPOINT3 pp	= keyList[i-2]->GetPosition() + (dist-l) * at;
		lastKey		= i-2;
		res			= GetPoseOfHeading(pp,at);

		return res;
	}

	return res; // never here!!
}

zMAT4 oCTrajectory :: InterpolateN(const float time)
{
	if (mode & EM_TRJ_SPLINE) 
	{
		if (!spl) return res;
		spl->InterpolateN(time, res);
		lastKey = spl->GetLastKey();
		return res;
	};

	res = Interpolate(time * Length());
	return res;
}

void oCTrajectory :: Draw()
{

	if (mode & EM_TRJ_SPLINE) 
	{
		spl->Draw(GFX_WHITE,1); 
	}
	else 
	{
		zPOINT3 p0,p1;
		int x0,x1,y0,y1;
		p1 = zCCamera::activeCam -> Transform (keyList[0]->p);

		for (int i=1; i<keyList.GetNumInList(); i++) 
		{
			p0 = p1;
			p1 = zCCamera::activeCam -> Transform (keyList[i]->p);
			Alg_ClipAtZ0(p0,p1);
			zCCamera::activeCam -> Project( &p0, x0, y0 );
			zCCamera::activeCam -> Project( &p1, x1, y1 );

			if (p0[VZ] >= 1 && p1[VZ] >= 1) 
			if (screen->ClipLine(x0,y0,x1,y1))  
			{
				zrenderer->DrawLineZ( (float)x0,(float)y0, (float)1/p0[VZ], (float)x1,(float)y1, (float)1/p1[VZ], GFX_WHITE);
			}
		}
	}
}

void  oCTrajectory :: Clear()	
{ 		
	if (spl) 
	{
		delete spl; spl = 0;
	} 
	else 
	{
		for (int i=0; i<keyList.GetNumInList(); i++) delete keyList[i];
	}

	keyList.DeleteList();

	length = 0;
};

zVEC3 oCTrajectory::RecalcByColl(const zPOINT3 &orgPos, const zVEC3 &inDir,const zVEC3 &collNormal, const int alignCollNormal)
{
	// FIXME: Funktioniert das mit Splines ? Macht das Sinn ?
	// FIXME: evtl. muss der Vob wieder in eine NOCOLLDET Position bei Meldung einer Collision gebracht werden,
	// denn wenn der Vob zu weit in einer Wand steckt, reicht evtl. nicht die Reflexion und im nächsten Frame gibts wieder
	// eine Collision -> ewiger Bounce Effekt mit Child FX an einer Wand entlang
	
	if (keyList.GetNumInList()<2) return -zVEC3(inDir);
	zPOINT3 collPos; 

	zMAT4 trafo; zVEC3 norm; 

	norm = collNormal;

	if (!alignCollNormal) 
	{
		zVEC3 dir = -inDir;
		norm= dir.Reflect (norm);
	}

	if (norm.Length() == 0) {
		zERR_WARNING("C: oCTrajectory::RecalcByColl(): collision normal is (0/0/0)");
		return zVEC3(0,1,0);
	}

	trafo = GetPoseOfHeading(orgPos,norm);

	zCPositionKey *clipped = zNEW( zCPositionKey );
	clipped -> SetMat(trafo);
	clipped -> SetTime( float(lastKey+1) );
	keyList.InsertAtPos(clipped,lastKey+1 );

	// times der folgenden Elemente um eins erhöhen
	for (int i=lastKey+2; i<keyList.GetNumInList(); i++) {
		keyList[i]->SetTime(keyList[i]->GetTime()+1);
	}

	// Die nachfolgende Position entweder an der Polynormalen oder mit Einfallswinkel = Ausfallswinkel ausrichten
	zPOINT3 last	 = keyList[lastKey+2]->GetPosition(); 
	float   lastDist = (last-orgPos).Length();

	keyList[lastKey+2]->SetMat( GetPoseOfHeading(orgPos+norm*lastDist,norm) );

	if (spl) 
	{ 
		delete spl;
		spl = zNEW( zCKBSpline(keyList) );
	}

	return norm;
}

void  oCTrajectory:: ApplyGrav(const float &g)
{
	if (g==0) return;
	for (int i=0; i<keyList.GetNumInList(); i++) 
	{
		keyList[i]->SetPosition( keyList[i]->GetPosition()+zVEC3(0,g,0) );
	}

	if (spl) spl->Changed(); 
}

void  oCTrajectory:: SetByList(const zCArray<zCVob *> vobList)
{
	Clear();

	for (int i=0; i<vobList.GetNumInList(); i++) 
	{
		zCPositionKey *key = zNEW(zCPositionKey);
		key->SetMat(vobList[i]->trafoObjToWorld);
		keyList.InsertEnd(key);
	}

	if (spl) spl->Changed(); 
}

int oCTrajectory::VobCross(const zCVob *vob)
{
	for (int i=1; i<keyList.GetNumInList(); i++) 
	{
		if (vob->GetHomeWorld()->TraceRayFirstHit(keyList[i-1]->GetPosition(), keyList[i]->GetPosition()-keyList[i-1]->GetPosition(),(zCVob*) 0, zTRACERAY_VOB_BBOX)) {
			if (vob->GetHomeWorld()->traceRayReport.foundVob == vob) return i;
		}
	}
	return -1;
};


// -------------------------------------------------------------------------------------------------------
// oCEmitterKey
// -------------------------------------------------------------------------------------------------------
oCEmitterKey :: oCEmitterKey()
{
	visSizeScale				= 0;
	scaleDuration				= 1;
	pfx_ppsValue				= 0;
	pfx_ppsIsSmoothChg			= 0;
	pfx_ppsIsLoopingChg			= 0;
	pfx_scTime					= 0;
	pfx_shpDistribWalkSpeed		= 0;
	pfx_velAvg					= 0;
	pfx_lspPartAvg				= 0;
	pfx_visAlphaStart			= 0;
	pfx_shpIsVolumeChg			= 0;
	pfx_shpScaleFPS				= 0;
	lightRange					= 0;
	emTrjEaseVel				= 0;
	emFlyGravity				= 0;
	vob							= 0;
	targetPos					= zVEC3(0,0,0);
	sfx							= 0;
	sfxHnd						= 0;
	sfxIsAmbient				= FALSE;
	emCheckCollision			= 0;
	pfx_flyGravity				= 0;
	pfx_shpDistribType			= zPFX_EMITTER_DISTRIBTYPE_RAND;
	pfx_dirMode					= zPFX_EMITTER_DIRMODE_DIR;
	pfx_dirFOR					= zPFX_FOR_WORLD;
	pfx_dirModeTargetFOR		= zPFX_FOR_WORLD;
	pfx_shpOffsetVec			= zVEC3(0,0,0);
	pfx_dirModeTargetPos		= zVEC3(0,0,0);
	emSelfRotVel				= zVEC3(0,0,0);
	pfx_shpDistribType			= zPFX_EMITTER_DISTRIBTYPE_RAND;
	pfx_dirMode					= zPFX_EMITTER_DIRMODE_NONE;
	pfx_dirFOR					= zPFX_FOR_WORLD;
	pfx_dirModeTargetFOR		= zPFX_FOR_WORLD;
	emTrjMode					= 0;
	emFXLifeSpan				= 0;
};

oCEmitterKey::~oCEmitterKey() 
{
	// FIXME: Wann den Vob löschen ??
	//if (vob) delete vob; 
	if (sfx) 
	{
		if (sfxHnd && zsound->IsSoundActive(sfxHnd)) zsound->StopSound(sfxHnd);

        zCSoundFX *dummy = sfx;   // [Moos] Diesen Umweg muss man gehen, sonst Release-Rekursion => Crash.
        sfx = NULL;
		zRELEASE_ACCT_NONULL(dummy);         // [Moos] Doooch, das muss drin sein. Wenns Probleme macht, mir sagen!
	}
}
	

void oCEmitterKey::SetByScript(const zSTRING &id)
{
	zSTRING ID(id);
	ID.Upper();
	if (!oCVisualFX::fxParser->GetSymbol(ID)) 
	{
		zERR_FAULT("C:oVisFX.cpp(oCEmitterKey::SetByScript):Unknown ID: "+ id);
		ParseStrings();
		SetName(ID);
		return;
	};
	oCVisualFX::fxParser->CreateInstance(ID,this);
	ParseStrings();
	SetName(ID);

	if (sfxID != "") sfx = zsound -> LoadSoundFXScript(sfxID);
};

void oCEmitterKey::ParseStrings()
{
	emTrjMode = EM_TRJ_UNDEF;
	pfx_flyGravity		=	String2Vec3(pfx_flyGravity_S);
	pfx_shpOffsetVec	=   String2Vec3(pfx_shpOffsetVec_S);

	pfx_dirMode_S.Upper();
	if (pfx_dirMode_S.Search("DIR")!=-1)	pfx_dirMode	= zPFX_EMITTER_DIRMODE_DIR;		else
	if (pfx_dirMode_S.Search("TARGET")!=-1)	pfx_dirMode	= zPFX_EMITTER_DIRMODE_TARGET;	else
	if (pfx_dirMode_S.Search("MESH")!=-1)   pfx_dirMode = zPFX_EMITTER_DIRMODE_MESH; 	else
	pfx_dirMode = zPFX_EMITTER_DIRMODE_NONE;

	if ((pfx_dirModeTargetFOR_S[0]=='o') || (pfx_dirModeTargetFOR_S[0]=='O')) pfx_dirModeTargetFOR = zPFX_FOR_OBJECT;
	else																	  pfx_dirModeTargetFOR = zPFX_FOR_WORLD;

	pfx_dirModeTargetPos = String2Vec3 (pfx_dirModeTargetPos_S);

	emSelfRotVel = String2Vec3(emSelfRotVel_S);

	emTrjMode_S.Upper();
	if (emTrjMode_S.Search("FIXED") != -1)	emTrjMode			|= EM_TRJ_FIXED;	
	if (emTrjMode_S.Search("TARGET")!= -1)	emTrjMode			|= EM_TRJ_TARGET;	
	if (emTrjMode_S.Search("LINE")  != -1)	emTrjMode			|= EM_TRJ_LINE;		
	if (emTrjMode_S.Search("SPLINE")!= -1)	emTrjMode			|= EM_TRJ_SPLINE;	
	if (emTrjMode_S.Search("RANDOM")!= -1)	emTrjMode			|= EM_TRJ_RANDOM;	
	if (emTrjMode_S.Search("FOLLOW")!= -1)	emTrjMode			|= EM_TRJ_FOLLOW;	
	if (emTrjMode_S.Search("MISSILE")!= -1)	
	{
		if (zRandF()>0.7f) emTrjMode	|= EM_TRJ_MISSILE;	
		else			   emTrjMode	|= EM_TRJ_TARGET;	
	};

};

void oCVisualFX::SetupAIForAllFXInWorld()
{
	const float zEFFECT_CULL_AI_DISTANCE	= 6000 * 6000;
	const float zEFFECT_CULL_AI_SLEEP_TIMER	= 5.0f;

	if (!zCCamera::activeCam) return;

	zCClassDef *def = oCVisualFX::GetStaticClassDef();

	for (int i=0; i<def->GetNumObjects(); i++) 
	{
		oCVisualFX* fx = zDYNAMIC_CAST<oCVisualFX>(def->GetObjectByIndex(i));

		if (fx->emTrjMode & EM_TRJ_FIXED)
		{
			// [EDENFELD] Addon - AI von FX ohne Position am leben erhalten
			zPOINT3 fxPos = fx->GetPositionWorld();
			if ( (fxPos == zPOINT3(0,0,0)) || ((fxPos - zCCamera::activeCam->activeCamPos).Length2()<zEFFECT_CULL_AI_DISTANCE)) 
			{
				fx->SetSleepingMode(zVOB_AWAKE);
				fx->SetSleepTimer(-1);
			}
			else
			{
				if (fx->GetSleepTimer()==-1)	 fx->SetSleepTimer	(zEFFECT_CULL_AI_SLEEP_TIMER);
				else if (fx->GetSleepTimer()<=0) fx->SetSleepingMode(zVOB_SLEEPING);
			}
		}
		else 
		{
			fx->SetSleepingMode(zVOB_AWAKE);
			fx->SetSleepTimer(-1);
		}
	}

};

void oCVisualFX::RemoveInstancesOfClass  (zCClassDef &classDefinition, const zBOOL destroyAllObjects)
{
	for (int i=0; i<classDefinition.GetNumObjects(); i++) 
	{
		zCVob* fx = zDYNAMIC_CAST<zCVob>(classDefinition.GetObjectByIndex(i));
//		oCVisualFX* fx = zDYNAMIC_CAST<oCVisualFX>(classDefinition.GetObjectByIndex(i));
		zERR_ASSERT(fx);

		if (fx->GetHomeWorld())
		{
/*			if (fx->light) 
			{	
				if (!destroyAllObjects) zADDREF_ACCT(fx->light);
				fx->light->RemoveVobFromWorld();
			}
			if (fx->earthQuake)
			{
				if (!destroyAllObjects) zADDREF_ACCT(fx->earthQuake);
				fx->earthQuake->RemoveVobFromWorld();
			}
			if (fx->screenFX)
			{
				if (!destroyAllObjects) zADDREF_ACCT(fx->screenFX);
				fx->screenFX->RemoveVobFromWorld();
			}
*/
			//if (!destroyAllObjects) zADDREF_ACCT(fx);
			fx->RemoveVobFromWorld();
			zRELEASE(fx);
			//if (!destroyAllObjects) homeLessFXList.InsertEnd(fx);
		}
	}
};

void oCVisualFX::PreSaveGameProcessing(const zBOOL destroyAllObjects)
{
	// wird nicht mehr benötigt. statt dessen wird alles über SetDontWriteIntoArchive(TRUE) 
	// behandelt
};

void oCVisualFX::PostSaveGameProcessing()
{
};


oCVisualFX::oCVisualFX()		   
{
	zERR_MESSAGE(10,0,"C: VIS: construct new oCVisualFX");

	InitValues();
	SetAI(ai);
}; 

oCVisualFX :: ~oCVisualFX() 
{
	//zERR_MESSAGE(10,0,"C: VIS: delete "+visName_S);
	zERR_MESSAGE(10,0,"C: VIS: Spell delete: " + visName_S + " ,ptr: " + zSTRING(int(this)) );

	// [EDENFELD] Addon: sicherheitshalber alle effekte beenden
	EndEffect(FALSE);

	assert(origin!=this);
	assert(target!=this);
 
    int i;

	ReleasePFXMesh();

    // emitter keys können ptr. auf Sounds beinhalten. die wieder "this" referenzieren
	for (i=0; i<emKeyList.GetNumInList(); i++) delete emKeyList[i];
	emKeyList.DeleteList();

	if (showTarget && target) target->SetDrawBBox3D(FALSE);

	DisposeHierachy();

	// alte Collision Kandidaten dereferenzieren und entfernen
	for (i=0; i<allowedCollisionVobList.GetNum(); i++) zRELEASE_ACCT_NONULL(allowedCollisionVobList[i]);
	allowedCollisionVobList.DeleteList();

	for (    i=0; i<collidedVobs.GetNum(); i++) zRELEASE_ACCT_NONULL(collidedVobs[i]);
	collidedVobs.DeleteList();

	for (	 i=0; i<queuedCollisions.GetNum(); i++) zRELEASE(queuedCollisions[i].foundVob);
	queuedCollisions.DeleteList();

	zCVob *delVob;
	for (    i=ignoreVobList.GetNum()-1; i>=0; i--)
	{
		delVob = ignoreVobList[i];
		ignoreVobList.RemoveIndex(i);
		zRELEASE(delVob);
	};

	for (    i=vobList.GetNum()-1; i>=0; i--)
	{
		delVob = vobList[i];
		vobList.RemoveIndex(i);
		zRELEASE(delVob);
	};


	if ( fxBackup )	
	{
		delete fxBackup;
		fxBackup = 0;
	}

	CleanUpCriticalFX();

	StopInvestFX();

	if ( origin && origin->GetVobName()=="_VFX" && origin->GetHomeWorld() )	// FIXME: warum nötig ? -> Firestorm 
	{
		origin->RemoveVobFromWorld();
	}

    SetTarget(NULL, FALSE);
    SetInflictor(NULL);
    SetOrigin(NULL, FALSE);


	// editor
	if ( actFX == this ) actFX = 0;

	zRELEASE(ai);

	// emitter keys können ptr. auf Sounds beinhalten. die wieder "thjs" referenzieren
	for (	i=0; i<emKeyList.GetNumInList(); i++) delete emKeyList[i];
	emKeyList.DeleteList();


};

void oCVisualFX::CleanUpCriticalFX()
{
	if (light) 
	{
		light->RemoveVobFromWorld();
		zRELEASE(light);
	};

	if (earthQuake) 
	{
		if (zCCamera::activeCam) earthQuake->OnUntrigger(0,0);
		earthQuake->RemoveVobFromWorld();
		zRELEASE(earthQuake);
	}

	if(screenFX)
	{
		zERR_MESSAGE(10,0,"C: VIS: deleting blend effect");
//		zREAL	fovDeg		   = userString[2].ToFloat();
		screenFX->StartEffect_BlendFadeOut(0,zCOLOR(0,0,0,0));
		//if (fovDeg > 0) screenFX->StartEffect_FOVMorph(0,0.1);
		screenFX->RemoveVobFromWorld();
		zRELEASE(screenFX);
	}

	// sounds löschen
	if ( sfx )	
	{
		zRELEASE_ACCT_NONULL(sfx);
		if (sfxHnd) zsound->StopSound(sfxHnd);
		sfx = 0;
	}
};

void oCVisualFX::CreateHierachy()
{
	// alle fx durchparsen

	if ( !emFXCreate_S.IsEmpty() )
	{
		emFXCreate_S.Upper();
		if (fxParser->GetSymbol(emFXCreate_S)) 
		{
			oCVisualFX *newFX = zNEW(oCVisualFX());
			newFX->root  = root;

			newFX->SetSpellType	(GetSpellType());
			newFX->SetSpellCat	(GetSpellCat ());
			newFX->SetDamage	(GetDamage() );
			newFX->SetDamageType(GetDamageType());
			newFX->SetLevel		(GetLevel());
			newFX->SetInflictor	(GetInflictor());

			if (emFXCreatedOwnTrj) 
			{
				newFX->parent= newFX;
				newFX->SetByScript(emFXCreate_S);

				newFX->parent= root;
				root -> fxList.Insert(newFX);
			}
			else 
			{
				newFX->parent= parent;
				newFX->SetIsChild(TRUE);
				newFX->SetByScript(emFXCreate_S);
				parent -> childList.Insert(newFX);
			}

		}
	}
}

void oCVisualFX::DisposeHierachy()
{
	// uargh
	for (int i=childList.GetNumInList()-1; i>=0;	  i--)	
	{
		childList[i]->parent = 0; // Inform childs of this parents death
		if (childList[i]->root==this) childList[i]->root = 0; 
        zRELEASE_ACCT_NONULL(childList[i]); // [Moos] Leakfix
	}
    childList.DeleteList();      // [Moos] Leakfix

	if (root == this) 
	{
		for (    i=fxList.GetNumInList()-1; i>=0; i--)	 
		{
			fxList[i]->root  = 0; // Inform childs of this parents death
			fxList[i]->parent= 0; // Inform childs of this parents death
			for (int j=fxList[i]->childList.GetNumInList()-1; j>=0; j--) 
			{
				fxList[i]->childList[j]->root  = 0;
                zRELEASE_ACCT_NONULL(fxList[i]->childList[j]);  // [Moos] Leakfix
			}
            fxList[i]->childList.DeleteList();       // [Moos] Leakfix
            zRELEASE_ACCT_NONULL(fxList[i]);         // [Moos] Leakfix
		}
        fxList.DeleteList();                         // [Moos] Leakfix
	}

	if ( parent ) 
	{
		if ( isChild )	parent->childList.Remove(this);
		else			parent->fxList	 .Remove(this); 
	};
}

void oCVisualFX::SetSendsAssessMagic(const zBOOL a_bSendAssessMagic)
{
	sendAssessMagic = a_bSendAssessMagic;

	for (int i=childList.GetNumInList()-1; i>=0;	  i--)	
	{
		childList[i]->sendAssessMagic = a_bSendAssessMagic;
	}

	if (root == this) 
	{
		for (    i=fxList.GetNumInList()-1; i>=0; i--)	 
		{
			fxList[i]->sendAssessMagic = a_bSendAssessMagic; 
			for (int j=fxList[i]->childList.GetNumInList()-1; j>=0; j--) 
			{
				fxList[i]->childList[j]->sendAssessMagic = a_bSendAssessMagic;
			}
		}
	}
}

zBOOL oCVisualFX::GetSendsAssessMagic()
{

	if (sendAssessMagic) return TRUE;

	for (int i=childList.GetNumInList()-1; i>=0;	  i--)	
	{
		if (childList[i]->sendAssessMagic) return TRUE;
	}

	if (root == this) 
	{
		for (    i=fxList.GetNumInList()-1; i>=0; i--)	 
		{
			if (fxList[i]->sendAssessMagic) return TRUE;
			for (int j=fxList[i]->childList.GetNumInList()-1; j>=0; j--) 
			{
				if (fxList[i]->childList[j]->sendAssessMagic) return TRUE;
			}
		}
	}

	return FALSE;
}



void oCVisualFX::InitParser() 
{
#ifdef COMPILING_SPACER
	if (fxParser != 0) return;	// im spacer nicht doppelt parsen
#endif
	if (!fxParser) 
	{
		zerr.Message("C: *** Visual FX Implementation "+VFX_VERSION);
		fxParser = zNEW(zCParser());
	}
	else  		   fxParser->Reset();

	zBOOL reparse	= zCParser::GetEnableParsing();
	zBOOL reparsevis= zoptions->Parm("REPARSEVIS");

	zCParser::SetEnableParsing(reparse||reparsevis);

	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "VisualEffects");
	if (filename.IsEmpty())
		filename = "System\\VisualFx";
	zERR_MESSAGE(4, 0, "N: VFX: Loading file " + filename + ".src or .dat");

	fxParser->Parse			(filename + ".src");
	fxParser->CreatePCode	();
	fxParser->CheckClassSize(zSTRING("C_PARTICLEFXEMITKEY"),oCEmitterKey::GetScriptClassSize());
	fxParser->CheckClassSize(zSTRING("CFX_BASE"),oCVisualFX::GetScriptClassSize());

	zCParser::SetEnableParsing(reparse);
};

/* ----------------------------------------------------------------------
	
    oCVisualFX::ExitParser()	

	25.08.2000	[Moos]	
                neu erstellt

   ---------------------------------------------------------------------- */

void oCVisualFX::ExitParser() 
{
    delete fxParser;
    fxParser = NULL;
};

 
void oCVisualFX::InitValues() 
{
	// TODO: Performance optimieren. Diese ganzen Calls durch presetListe vermeiden
 
	visAlphaBlendFunc_S		= "ADD";
	visTexAniFPS			= 0;
	visTexAniIsLooping		= FALSE;
	shouldDelete			= FALSE;
	deleteTime				= 0;
	emTrjNumKeys			= 1;
	origin					= 0;
	target					= 0;
	inflictor				= 0;
	light					= 0;
	level					= 1;
	actKey					= 0;
	lastSetKey				= 0;
	emCheckCollision		= 0;
	emAdjustShpToOrigin		= 0;
	emInvestNextKeyDuration	= 0;
	emTrjEaseVel			= 0;
	sfx						= 0;
	sfxHnd					= 0;
	sfxIsAmbient			= FALSE;
	fxBackup				= 0;
	nextLevelTime			= 0;
	emFlyGravity			= 0;
	emTrjNumKeysVar			= 0;
	emTrjAngleElevVar		= 0;
	emTrjAngleHeadVar		= 0;
	emTrjKeyDistVar			= 0;
	emTrjDist				= 0;
	trjSign					= 1;
	easeTime				= 0;
	lightning				= FALSE;
	targetPos				= zVEC3(0,0,0);
	queueSetLevel			= -1;

	emTrjDynUpdateDelay		= 0.1F;
	emTrjDynUpdateTargetOnly= 0;
	emFXTriggerDelay			= 0;
	emFXLifeSpan			= VFX_LIFESPAN_FOREVER;
	emFXCreatedOwnTrj		= 0;

	emActionCollStat		= 0;
	emActionCollDyn			= 0;
	emTrjTargetRange		= 5;
	emTrjTargetAzi			= 0;
	emTrjTargetElev			= 0;
	lightRange				= 0;
	fxInvestStopped			= FALSE;
	fovMorph				= FALSE;
	fxStartTime				= 0;
	root					= this;
	parent					= this;
	isDeleted				= FALSE;
	isChild					= FALSE;
	collisionOccured		= FALSE;
	collisionCtr			= 0;
	initialized				= FALSE;
	age						= 0;
	trjUpdateTime			= 0;
	showVisual				= 0;
	visAlpha				= 1;
	levelTime				= 0;
	damageTime				= 0;
	lifeSpanTimer			= 0;
	fxInvestOrigin			= 0;
	fxInvestTarget			= 0;
	fxInvestTargetInitialized= FALSE;
	fxInvestOriginInitialized= FALSE;
	visSize					= zVEC3(0,0,0);
	emTrjMode				= EM_TRJ_FIXED;
	emActionCollDyn			= TACTION_COLL_NONE;
	emActionCollStat		= TACTION_COLL_NONE;
	emSelfRotVel			= zVEC3(0,0,0);
	emTrjEaseFunc			= TEASEFUNC_LINEAR;
	emTrjLoopMode			= TRJ_LOOP_NONE;
	orgNode					= 0;
	targetNode				= 0;
	lastTrjDir				= zVEC3(0,0,0);
	keySize					= zVEC3(0,0,0);
	actSize					= zVEC3(0,0,0);
	castEndSize				= zVEC3(0,0,0);

	lastSetVisual			= NULL;

	damage					= 0;
	damageType				= 1;
	spellType				= 0;
	spellCat				= 0;
	spellTargetTypes		= TARGET_FLAG_ALL;
	sendAssessMagic			= 0;
	ringPos					= -1;
	emTrjFollowHitLastCheck = FALSE;
	earthQuake				= NULL;
	screenFX				= NULL;
	screenFXTime			= 0;
	screenFXDir				= 0;
	secsPerDamage			= -1;
	damageTime				= 0;
	bIsProjectile			= FALSE;
	bPfxMeshSetByVisualFX	= FALSE;
	timeScaled				= FALSE;	
 
	fxState					= zVFXSTATE_UNDEF;

	ai						= zNEW(oCVisualFXAI);

	if (!fxParser) InitParser();

	this->SetDontWriteIntoArchive(TRUE);
	m_bAllowMovement = TRUE;

	SetSleepTimer(-1);
};

void oCVisualFX::ParseStrings()
{
	emTrjMode = EM_TRJ_UNDEF;

	emTrjMode_S.Upper();
	if (emTrjMode_S.Search("FIXED") != -1)	emTrjMode			|= EM_TRJ_FIXED;	
	if (emTrjMode_S.Search("TARGET")!= -1)	emTrjMode			|= EM_TRJ_TARGET;	
	
	// [EDENFELD] 2.30c Splines waren durch fehlenden else Fall auch immer Lines -> ARGH
	if (emTrjMode_S.Search("SPLINE")!= -1)	emTrjMode			|= EM_TRJ_SPLINE;	else
	if (emTrjMode_S.Search("LINE")  != -1)	emTrjMode			|= EM_TRJ_LINE;		

	if (emTrjMode_S.Search("RANDOM")!= -1)	emTrjMode			|= EM_TRJ_RANDOM;	
	if (emTrjMode_S.Search("FOLLOW")!= -1)	emTrjMode			|= EM_TRJ_FOLLOW;	
	if (emTrjMode_S.Search("MISSILE")!= -1)	
	{
		if (zRandF()>0.7f) emTrjMode	|= EM_TRJ_MISSILE;	
		else			   emTrjMode	|= EM_TRJ_TARGET;	
	}

	emTrjLoopMode_S.Upper();
	if (emTrjLoopMode_S.Search("RESTART")!=-1)	emTrjLoopMode	= TRJ_LOOP_RESTART; else
	if (emTrjLoopMode_S.Search("PINGPONG_ONCE")!=-1) emTrjLoopMode	= TRJ_LOOP_PINGPONG_ONCE;else 
	if (emTrjLoopMode_S.Search("PINGPONG")!=-1) emTrjLoopMode	= TRJ_LOOP_PINGPONG;else 
	if (emTrjLoopMode_S.Search("HALT")!=-1)		emTrjLoopMode	= TRJ_LOOP_HALT;    else 
												emTrjLoopMode	= TRJ_LOOP_NONE;	
	emTrjEaseFunc_S.Upper();
	if (emTrjEaseFunc_S.Search("LINEAR")!=-1)	emTrjEaseFunc   = TEASEFUNC_LINEAR;	else
	if (emTrjEaseFunc_S.Search("SINE")!=-1)		emTrjEaseFunc   = TEASEFUNC_SINE;	else
	if (emTrjEaseFunc_S.Search("EXP")!=-1)		emTrjEaseFunc   = TEASEFUNC_EXP;	

	emActionCollStat_S.Upper();
	emActionCollDyn_S.Upper();

	if (emActionCollStat_S.Search("BOUNCE")!=-1)	emActionCollStat  = TACTION_COLL_BOUNCE; 
	if (emActionCollStat_S.Search("CREATE")!=-1)	emActionCollStat |= TACTION_COLL_CREATE; 
	if (emActionCollStat_S.Search("COLLIDE")!=-1)	emActionCollStat |= TACTION_COLL_COLLIDE; 
	//if (emActionCollStat_S.Search("NORESP")!=-1)	emActionCollStat |= TACTION_COLL_NORESP; 
	if (emActionCollStat_S.Search("CREATEQUAD")!=-1)emActionCollStat |= TACTION_COLL_CREATE_QUAD; 

	if (emActionCollDyn_S.Search("BOUNCE")!=-1) emActionCollDyn  = TACTION_COLL_BOUNCE; 

	if (emActionCollDyn_S.Search("CREATEONCE")!=-1) emActionCollDyn  |= TACTION_COLL_CREATE_ONCE; else
	if (emActionCollDyn_S.Search("CREATE")!=-1) emActionCollDyn  |= TACTION_COLL_CREATE; 
	
	if (emActionCollDyn_S.Search("COLLIDE")!=-1) emActionCollDyn |= TACTION_COLL_COLLIDE; 
	//if (emActionCollDyn_S.Search("NORESP")!=-1) emActionCollDyn |= TACTION_COLL_NORESP; 

	emFXCollStat_S.Upper();
	emFXCollDyn_S.Upper();
	emFXCollDynPerc_S.Upper();
	emFXCollStatAlign_S.Upper();;			// TRAJECTORY, COLLISIONNORMAL
	emFXCollDynAlign_S.Upper();;

	emSelfRotVel = String2Vec3(emSelfRotVel_S);
	visSize		 = keySize = actSize =  String2Vec3(visSize_S);
};


void oCVisualFX::SetVisualByString(const zSTRING &name)
{
	zCDecal *dc;
	zPATH path;

	zSTRING realName;

	if (!GetHomeWorld())										return;

	// emitter key visual ist gleich dem main fx visual
	if (visName_S == name && 
		(GetVisual()!=NULL && GetVisual() == lastSetVisual))	return;			

	if (age<emFXTriggerDelay) return;
		
	visName_S = name; 

	if (visName_S.Search(".")==-1) 
	{
		// must be pfx
		realName = visName_S.PickWord(1,".",".")+"_L" + zSTRING(level);

		if (zCParticleFX::SearchParticleEmitter(realName) == 0) 
		{ 
			realName = visName_S;
			if (zCParticleFX::SearchParticleEmitter(realName) == 0) return;
		}


		zCParticleFX* pfx = zNEW(zCParticleFX);

		zCVob::SetVisual(pfx); 

		pfx -> SetDontKillPFXWhenDone	(TRUE);

		// item effekte dürfen nicht jeden frame geupdated werden -> performance killer
		// UPDATE: doch, müssen sie leider, andere Optimierung für oCVisualfX Objekte dafür in
		// zCParticleFX::UpdateParticleFX()
		// magie effekte müssen leider jeden frame geupdated werden
		/*if (!zDYNAMIC_CAST<oCItem>(origin))*/ pfx -> SetForceEveryFrameUpdate (TRUE);

		pfx -> SetAndStartEmitter		(realName, TRUE);

		CalcPFXMesh();

		// FIXME!!!
		if (!zrenderer->GetAlphaLimitReached())
		{
			int ctr = 0;
			while( pfx->CalcIsDead() )
			{
				if (ctr++ == 10) 
				{
					zERR_WARNING("C: magic-pfx could not be started: " + visName_S);
					break;
				}
				pfx -> CreateParticles();
			}
		}

		if (pfx->GetEmitter())
		{	
			savePpsValue		= pfx->GetEmitter()->ppsValue;
			saveVisSizeStart	= pfx->GetEmitter()->visSizeStart;
		}

		zRELEASE(pfx);

		// FIXME[ALT?]: Partikel Effekte werden hier nicht gerendert, wenn SetVisualAlphaEnabled(TRUE);
		if (visAlpha < 1) 
		{
			SetVisualAlphaEnabled(TRUE);
			SetVisualAlpha(visAlpha);
		}
		else SetVisualAlphaEnabled(FALSE);

	}
	else if (visName_S.Search(".TGA")!=-1) 
	{
		// decal
		zCVob::SetVisual(visName_S);

		SetVisualCamAlign(zVISUAL_CAMALIGN_FULL);

		dc = static_cast<zCDecal*>(GetVisual());

		dc->SetDecalDim			(visSize[VX],visSize[VY]);
		dc->SetDecal2Sided		(TRUE);
		//dc->SetIsOnTop			(TRUE);
		dc->SetIgnoreDayLight	(TRUE);

		// transparenz setzen
		dc->decalMaterial->SetAlphaBlendFunc(zrenderer->AlphaBlendFuncStringToType(visAlphaBlendFunc_S));
		dc->decalMaterial->SetAlpha			( zBYTE(visAlpha*255) );

		// ani infos setzen
		dc->decalMaterial->texAniCtrl.SetAniFPS	   (visTexAniFPS);
		dc->decalMaterial->texAniCtrl.SetOneShotAni(!visTexAniIsLooping);

		//if (visAlpha == 1) SetVisualAlphaEnabled(FALSE); // Ja ?
	}
	else if (visName_S.Search(".3DS")!=-1 || visName_S.Search(".MDS")!=-1) 
	{

		zCVob::SetVisual(visName_S);

		if (zDYNAMIC_CAST<zCProgMeshProto>(GetVisual()))
		{
			zCProgMeshProto *progMesh = static_cast<zCProgMeshProto*>(GetVisual());

			for (int i=0; i<progMesh->GetNumMaterial(); i++) 
			{
				progMesh -> GetMaterialByIndex(i) -> SetAlphaBlendFunc		   (zrenderer->AlphaBlendFuncStringToType(visAlphaBlendFunc_S));
				progMesh -> GetMaterialByIndex(i) -> texAniCtrl.SetAniFPS	   (visTexAniFPS);
				progMesh -> GetMaterialByIndex(i) -> texAniCtrl.SetOneShotAni  (!visTexAniIsLooping);
				progMesh -> GetMaterialByIndex(i) -> SetAlpha				   ( zBYTE(visAlpha*255) );
			}
		}
		
		if (visAlpha < 1) 
		{
			SetVisualAlphaEnabled	(TRUE);
			SetVisualAlpha			(visAlpha);
		}
		else SetVisualAlphaEnabled(FALSE);

	}
	else if (visName_S.Search(".TRL")!=-1) 
	{
		// polyStripe trails
		zCPolyStrip	*polyStrip;
		polyStrip		= zNEW(zCPolyStrip);
		polyStrip->SetCamAlign			(zCPolyStrip::zCAM_ALIGN_STRIP);
		zCVob::SetVisual(polyStrip);

		polyStrip->SetAlphaFadeSpeed	(userString[0].ToFloat());
		polyStrip->material->SetAlphaBlendFunc		   (zrenderer->AlphaBlendFuncStringToType(visAlphaBlendFunc_S));
		polyStrip->material->SetTexture				   (visName_S.PickWord(1,".")+".TGA");
		polyStrip->material->texAniCtrl.SetAniFPS	   (visTexAniFPS);
		polyStrip->material->texAniCtrl.SetOneShotAni  (!visTexAniIsLooping);
		polyStrip->material->SetAlpha				   ( zBYTE(visAlpha*255) );

		polyStrip->AllocateResources	(128);
		
		//
		zRELEASE (polyStrip);
	}
	else if (visName_S.Search(".LTN")!=-1) 
	{
		// polyStripe trails
		zCPolyStrip	*polyStrip;
		polyStrip		= zNEW(zCPolyStrip);
		zCVob::SetVisual(polyStrip);

		polyStrip->SetAlphaFadeSpeed	(userString[0].ToFloat());
		polyStrip->SetCamAlign			(zCPolyStrip::zCAM_ALIGN_POLY);
		polyStrip->material->SetAlphaBlendFunc		   (zrenderer->AlphaBlendFuncStringToType(visAlphaBlendFunc_S));
		polyStrip->material->SetTexture				   (visName_S.PickWord(1,".")+".TGA");
		polyStrip->material->texAniCtrl.SetAniFPS	   (visTexAniFPS);
		polyStrip->material->texAniCtrl.SetOneShotAni  (!visTexAniIsLooping);
		polyStrip->material->SetAlpha				   ( zBYTE(visAlpha*255) );

		polyStrip->AllocateResources	(128);

		lightning = TRUE;
		
		//
		zRELEASE (polyStrip);
	}
	else if (visName_S.Search(".EQK")!=-1) 
	{
		// earthquake
		earthQuake = zNEW(zCEarthquake);
		zVEC3 radius3	= String2Vec3(userString[0]);
		zVEC3 timeSec3	= String2Vec3(userString[1]);
		zVEC3 amp3		= String2Vec3(userString[2]);
		earthQuake->SetProperties(radius3[VX], timeSec3[VX], amp3);
		earthQuake->SetPositionWorld(GetPositionWorld());
		earthQuake->SetDontWriteIntoArchive(TRUE);
		GetHomeWorld()->AddVob(earthQuake);
		return;
	}
	else if (visName_S.Search(".FOV")!=-1) 
	{
		// screen blends / fov morphs
		fovMorph = TRUE;
		zCCamera::activeCam->GetFOV (oldFovX,oldFovY);
		zsound->SetGlobalOcclusion (0.5F);
		return;
	}
	else if (visName_S.Search(".SCX")!=-1) 
	{
		// screen blends / fov morphs
		screenFX = zNEW(zCVobScreenFX);
		screenFX ->SetPositionWorld(GetPositionWorld());
		GetHomeWorld()->AddVob(screenFX);
		if (visName_S.Search("REVERSE")!=-1) this->screenFXDir=1;
		screenFX->SetDontWriteIntoArchive(TRUE);
		return;
	}
	else if (visName_S.Search(".MMS")!=-1) 
	{
		// morph meshes
		zCMorphMesh *mms = zCMorphMesh::Load(visName_S);

		if (!mms) 
		{
			zERR_FAULT("C: oCVisualFX::SetVisualByString(): MorphMesh not found: " + visName_S);
			return;
		}
		else {
		
			for (int i=0; i<mms->GetMorphMesh()->GetNumMaterial(); i++) 
			{
				mms->GetMorphMesh()->GetMaterialByIndex(i)->SetAlphaBlendFunc		   (zrenderer->AlphaBlendFuncStringToType(visAlphaBlendFunc_S));
				mms->GetMorphMesh()->GetMaterialByIndex(i)->texAniCtrl.SetAniFPS	   (visTexAniFPS);
				mms->GetMorphMesh()->GetMaterialByIndex(i)->texAniCtrl.SetOneShotAni (!visTexAniIsLooping);
				mms->GetMorphMesh()->GetMaterialByIndex(i)->SetAlpha				   ( zBYTE(visAlpha*255) );
			}

			mms->StartAni(mms->GetAnyAnimation());
		}
		
		zCVob::SetVisual(mms);
		zRELEASE(mms);
	}
	else if (visName_S.Search(".SLW")!=-1) 
	{
		zREAL timeScaleGlobal = userString[0].ToFloat();
		ztimer.SetMotionFactor(timeScaleGlobal);

		if (origin && zDYNAMIC_CAST<zCModel>(origin->GetVisual()))
		{
			static_cast<zCModel*>(origin->GetVisual())->SetTimeScale(userString[1].ToFloat()/ztimer.GetMotionFactor());
		}

		timeScaled = TRUE;
	}
	else if (visName_S.IsEmpty()) 
	{
		zCVob::SetVisual(0);		// nothing
	}

	lastSetVisual = GetVisual();
//	if (visAlpha > 0) zCVobSetShowVisual(TRUE);
//	else zCVob::SetShowVisual(FALSE);
	zCVob::SetShowVisual(visAlpha>0);
}

void oCVisualFX::SetCollisionEnabled(const zBOOL en)
{
	// If Collision was enabled previous, no disabling is allowed
	if ( GetCollDetDyn() || GetCollDetStat() ) 
	{
		emCheckCollision = TRUE;
		return;
	}

//	if (en==emCheckCollision) return;

	emCheckCollision = en;

	SetCollDetStat(en && (emActionCollStat != TACTION_COLL_NONE));
	SetCollDetDyn (en && (emActionCollDyn  != TACTION_COLL_NONE));

	if (!GetVisual())		return;
	if (!emCheckCollision)	return;

	// Argh, hier wird gesondert der Collisionstyp der einzelnen Spells gesetzt
	// FIXME: hier ist nicht der richtige Ort dafür. Besser wäre es, wenn das auf Skriptebene gelegt werden
	// könnte
	// UPDATE: AUF JEDEN FALL MACHEN: GROSSE FEHLERQUELLE!!!

	if (GetIsProjectile()) 
	{
		SetCollisionClass (zCCollObjectProjectile::S_GetCollObjClass());  
		return;
	}

	switch(GetSpellType())
	{
		// projektil geschosse:
	case SPL_FIRESTORM:
	case SPL_PYROKINESIS:
	case SPL_SKULL:				// FireStorm
		if (visName_S.Search("_SPREAD")!=-1)	SetCollisionClass (zCCollObjectBoxPassThrough::S_GetCollObjClass()); 
		else									SetCollisionClass (zCCollObjectProjectile::S_GetCollObjClass());  
	break;
	case SPL_LIGHTNINGFLASH:
	case SPL_GEYSER:
	case SPL_BREATHOFDEATH:
	case SPL_WINDFIST:
	case SPL_WATERFIST:
	case SPL_CHARGEFIREBALL:
	case SPL_INSTANTFIREBALL:
	case SPL_PALDESTROYEVIL:
	case SPL_FIREBOLT:
	case SPL_ICEBOLT:
	case SPL_ICELANCE:
	case SPL_PALHOLYBOLT:
	case SPL_THUNDERBALL:
	case SPL_ICECUBE:
	case SPL_WHIRLWIND:
	case SPL_GREENTENTACLE:
	case SPL_DESTROYUNDEAD:
	case SPL_MASTEROFDESASTER:
	case SPL_DEATHBOLT:
	case SPL_DEATHBALL:
	case SPL_CONCUSSIONBOLT:
	case SPL_PALREPELEVIL:
	case SPL_ZAP:
	case SPL_BELIARSRAGE:
	case SPL_SUCKENERGY:
	case SPL_PLAGUE:
	case SPL_SUMMONSWARM:
	case SPL_RESERVED_64:
	case SPL_RESERVED_65:
	case SPL_RESERVED_66:
	case SPL_RESERVED_67:
	case SPL_RESERVED_68:
	case SPL_RESERVED_69:
	case SPL_RESERVED_77:
	case SPL_RESERVED_78:
	case SPL_RESERVED_79:
	case SPL_RESERVED_89:
	case SPL_RESERVED_90:
	case SPL_RESERVED_91:
	case SPL_RESERVED_92:
	case SPL_RESERVED_93:
	case SPL_RESERVED_94:
	case SPL_RESERVED_95:
	case SPL_RESERVED_96:
	case SPL_RESERVED_97:
	case SPL_RESERVED_98:
	case SPL_RESERVED_99:
		SetCollisionClass (zCCollObjectProjectile::S_GetCollObjClass());  
		break;
	default:
//		SetCollisionClass (zCCollObjectComplex::S_GetCollObjClass());
		SetCollisionClass (zCCollObjectBoxPassThrough::S_GetCollObjClass());  // [Moos] 20.12.00 Anpassung an Vob-Änderung
		break;
	}
}


void oCVisualFX::SetByScript(const zSTRING &id )
{
	zSTRING ID(id);
	ID.Upper();

	if (!fxParser->GetSymbol(ID)) 
	{
		zERR_FAULT("C:oSpellVis.h(oCVisualFX::SetByScript):Unknown ID: "+ id);
		fxName = ID;
		return;
	};

	fxParser->CreateInstance(ID,(zBYTE*)&visName_S);
	ParseStrings();

	fxName = ID;

	zERR_MESSAGE(10,0,"C: VIS: Loading Visual FX Instance: " + ID);

	// init keys
	// first Emitterkey is being used always if particle vars are being modified at time key positions
	zSTRING newid = GetName() + "_KEY_OPEN";
	if (fxParser->GetSymbol(newid)) 
	{
		oCEmitterKey	*k = zNEW(oCEmitterKey);
		k->SetByScript(newid) ;
		emKeyList.Insert(k);
	}
	
	newid = GetName() + "_KEY_INIT";
	if (fxParser->GetSymbol(newid)) 
	{
		oCEmitterKey	*k = zNEW(oCEmitterKey);
		k->SetByScript(newid) ;
		emKeyList.Insert(k);
	}
	
	newid = GetName() + "_KEY_CAST";
	if (fxParser->GetSymbol(newid)) 
	{
		oCEmitterKey	*k = zNEW(oCEmitterKey);
		k->SetByScript(newid) ;
		emKeyList.Insert(k);
	}
	
	newid = GetName() + "_KEY_STOP";
	if (fxParser->GetSymbol(newid)) 
	{
		oCEmitterKey	*k = zNEW(oCEmitterKey);
		k->SetByScript(newid) ;
		emKeyList.Insert(k);
	}
	newid = GetName() + "_KEY_INVEST_";

	int key = 1;
	while (fxParser->GetSymbol(newid+zSTRING(key))) 
	{
		oCEmitterKey	*k = zNEW(oCEmitterKey);
		k->SetByScript(newid+zSTRING(key++)) ;
		emKeyList.Insert(k);
	}
	visName_S.Upper();

	// collision key may be there in both fx control modes
	zSTRING myd(GetName() + "_KEY_COLLIDE");

	if (fxParser->GetSymbol(myd)) 
	{
		oCEmitterKey	*k = zNEW(oCEmitterKey);
		k->SetByScript(myd) ;
		emKeyList.Insert(k);
	}

	if ( !lightPresetName.IsEmpty() ) 
	{
		lightPresetName.Upper();
		light = zNEW(zCVobLight);
		light->SetDontWriteIntoArchive(TRUE);
		if (!light->SetByPreset(lightPresetName))
		{
			zERR_FAULT("C: oCVisualFX::SetByScript(): lightpresetName " + lightPresetName + " unknown");
		}
		light->SetCanMove(TRUE);
		lightRange = light->GetRange();
	};

	if ( !sfxID.IsEmpty() ) sfx = zsound -> LoadSoundFXScript(sfxID);

	CreateHierachy();
	CreateInvestFX();

	if (GetNumKeys()>0) CreateBackup();
};


void oCVisualFX::UpdateFXByEmitterKey(oCEmitterKey *key)
{
	if ( lastSetKey == key ) return;
	if ( key == 0) return;

	keySize = actSize;

	if ( fxBackup == 0 ) CreateBackup();
	
	key->visName_S.Upper();

	if (!key->visName_S.IsEmpty()) SetVisualByString(key->visName_S);

	if ( zDYNAMIC_CAST<zCParticleFX>(GetVisual()) && (static_cast<zCParticleFX*>(GetVisual())->GetEmitter()) ) 
	{

		zCParticleEmitter *em = static_cast<zCParticleFX*>(GetVisual())->GetEmitter();
		zVEC3 v				  = String2Vec3 (key->pfx_shpDim_S);
		float f				  = key->pfx_shpDim_S.ToFloat();

		if (key->pfx_ppsValue)				em->ppsValue=savePpsValue		=	key->pfx_ppsValue;
		if (key->pfx_dirMode)				em->dirMode						=	key->pfx_dirMode;
		if (key->pfx_dirFOR)				em->dirFOR						=	key->pfx_dirFOR;
		if (key->pfx_shpDistribType)		em->shpDistribType				=	key->pfx_shpDistribType;
		if (key->pfx_dirModeTargetFOR)		em->dirModeTargetFOR			=	key->pfx_dirModeTargetFOR;
		if (key->pfx_shpDistribWalkSpeed)	em->shpDistribWalkSpeed			=   key->pfx_shpDistribWalkSpeed;
		if (key->pfx_shpScaleFPS)			em->shpScaleFPS					=   key->pfx_shpScaleFPS;
		if (key->pfx_velAvg)				em->velAvg						=	key->pfx_velAvg;
		if (key->pfx_lspPartAvg)			em->lspPartAvg					=	key->pfx_lspPartAvg;
		if (key->pfx_visAlphaStart)			em->visAlphaStart				=	key->pfx_visAlphaStart;
		if (key->visSizeScale)				em->visSizeEndScale				=	key->visSizeScale;
		if (v!=zVEC3(0,0,0))				em->shpLineBoxDim				=	v;
		if (f)								em->shpCircleSphereRadius		=	f;

		if (key->pfx_flyGravity		  != zVEC3(0,0,0))	em->flyGravity					=	key->pfx_flyGravity;
		if (key->pfx_shpOffsetVec	  != zVEC3(0,0,0))	em->shpOffsetVec				=	key->pfx_shpOffsetVec;
		if (key->pfx_dirModeTargetPos != zVEC3(0,0,0))	em->dirModeTargetPos			=   key->pfx_dirModeTargetPos;

		if (key->pfx_scTime) static_cast<zCParticleFX*>(GetVisual())->SetTimeScale(key->pfx_scTime);

		if (key->pfx_shpIsVolumeChg)  em->shpIsVolume			=	!em->shpIsVolume;
		if (key->pfx_ppsIsSmoothChg)  em->ppsIsSmooth			=	!em->ppsIsSmooth;
		if (key->pfx_ppsIsLoopingChg) 
		{
			if (em->ppsIsLooping) static_cast<zCParticleFX*>(GetVisual())->StopEmitterOutput();
			em->ppsIsLooping			=	!em->ppsIsLooping;
		}
		saveVisSizeStart				=	em->visSizeStart;
	}

	if (light && light->GetHomeWorld()) 
	{
		if (key->lightPresetName != lightPresetName && !key->lightPresetName.IsEmpty() ) 
		{
			// lichter tauschen, nun denn
			if (light) 
			{
				light->GetHomeWorld()->RemoveVob(light);
				zRELEASE(light);
			}

			light = zNEW(zCVobLight);
			light->SetDontWriteIntoArchive(TRUE);
			key  ->lightPresetName.Upper();
			if (!light->SetByPreset(key->lightPresetName)) 
			{
				zERR_FAULT("C: oCVisualFX::UpdateFXByEmitterKey(): lightpresetName " + key->lightPresetName + " unknown");
			}
			light->SetCanMove(TRUE);
			light->SetPositionWorld(GetPositionWorld());
			GetHomeWorld()->AddVobAsChild(light,this);
		}

		if (light && key->lightRange)  
		{
			light->SetRange(key->lightRange);
			lightRange = light->GetRange();
		}
	}
	if (key->sfx && !zsound->IsSoundActive(key->sfxHnd) ) 
	{
		zCSoundSystem::zTSound3DParams params;
		params.SetDefaults();
		params.isAmbient3D = key->sfxIsAmbient;
		key->sfxHnd = zsound->PlaySound3D(key->sfx,this,zVFX_SOUNDSLOT_DEFAULT,&params);
	}

	SetCollisionEnabled(key->emCheckCollision);

	if (key->emFlyGravity != 0 )			emFlyGravity = key->emFlyGravity;
	if (key->emSelfRotVel != zVEC3(0,0,0) ) emSelfRotVel = key->emSelfRotVel;
	if (key->emTrjEaseVel)					emTrjEaseVel = key->emTrjEaseVel;
	if ( !key->emTrjMode_S.IsEmpty() )		emTrjMode    = key->emTrjMode;
	if (key->emFXLifeSpan)					emFXLifeSpan = key->emFXLifeSpan;

	if (!isChild) CalcTrajectory(emTrjDynUpdateTargetOnly);

	// ACHTUNG: sonderfall: wenn this von einem anderem objekt bewegt wird, hat das origin
	// evtl. keine homeworld und dann wird "this" übergeben
	oCVisualFX *fx = NULL;
	if ( !this->GetAllowMovement() && (!origin || !origin->GetHomeWorld())) fx = CreateAndCastFX(key->emCreateFXID,this);
	else																	fx = CreateAndCastFX(key->emCreateFXID,origin);

	if (fx) fx->SetInflictor(inflictor);
	zRELEASE(fx); // [Moos] leakfix

	lastSetKey = key;
	actKey	   = key;
};

void oCVisualFX::CreateBackup()
{
	return; 
#if 0
	// folgender Code wird für Gothic nicht gebraucht.  und wird aus Performance Gründen auskommentiert
	// damit zu erreichendes Feature: Der Ursprungszustand eines Effektes kann von einer Investphase zur nächsten
	// nach einer gegebenen Zeit wiederhergestellt werden
	fxBackup = zNEW(oCEmitterKey);	

	if ( zDYNAMIC_CAST<zCParticleFX>(GetVisual()) && static_cast<zCParticleFX*>(GetVisual())->GetEmitter() ) 
	{
		zCParticleEmitter *em = static_cast<zCParticleFX*>(GetVisual())->GetEmitter();

		fxBackup -> pfx_ppsValue				=	em->ppsValue ;
		fxBackup -> pfx_shpScaleFPS				=   em->shpScaleFPS;
		fxBackup -> pfx_shpDistribWalkSpeed		=   em->shpDistribWalkSpeed;
		fxBackup -> pfx_velAvg					=	em->velAvg;
		fxBackup -> pfx_lspPartAvg				=	em->lspPartAvg;
		fxBackup -> pfx_visAlphaStart			=	em->visAlphaStart;
		fxBackup -> visSizeScale				=	em->visSizeEndScale;

		fxBackup -> pfx_flyGravity				=	em->flyGravity;
		fxBackup -> pfx_shpOffsetVec			=	em->shpOffsetVec;	
		fxBackup -> pfx_shpDistribType			=	em->shpDistribType;
		fxBackup -> pfx_dirMode					=	em->dirMode;
		fxBackup -> pfx_dirFOR					=	em->dirFOR;
		fxBackup -> pfx_dirModeTargetFOR		=	em->dirModeTargetFOR;
		fxBackup -> pfx_dirModeTargetPos		=	em->dirModeTargetPos;
		fxBackup -> pfx_scTime					=	1;
	}

	fxBackup -> visName_S						=   visName_S;
	fxBackup -> emTrjEaseVel					=	emTrjEaseVel;
	fxBackup ->	emFlyGravity					=   emFlyGravity;
	fxBackup ->	emSelfRotVel					=	emSelfRotVel;
	fxBackup -> lightPresetName					=   lightPresetName;

	if (light) fxBackup->lightRange = light->GetRange();
#endif
};

int oCVisualFX::FindKey(const zSTRING &id)
{
	zSTRING sub = "_KEY_" + zSTRING(id);

	for (int i=0; i<GetNumKeys(); i++)
	{
		if ( emKeyList[i]->GetName().Search(sub) != -1 ) return i;
	}
	return -1;
};

oCVisualFX* oCVisualFX::CreateAndPlay(const zSTRING &id,const zCVob *org, const zCVob *target, const int lvl, const float dam, const int damType,const zBOOL isProjectile)
{
	zSTRING ID(id);
	ID.Upper();
	if ( !ID.IsEmpty() )
	{
		if (fxParser->GetSymbol(ID)) 
		{
			oCVisualFX *newFX = zNEW(oCVisualFX());
			newFX->SetIsProjectile(isProjectile);
			// ein wenig kompliziert: hier wird die hierachie festgelegt
			// da es ein einfacher solo effekt ist, ist root == parent == der erzeugte fx
			newFX->root		= newFX;
			newFX->parent	= newFX;

			zSTRING levelID = ID + "_L" + zSTRING(lvl);
			if (fxParser->GetSymbol(levelID)) ID = levelID;

			newFX->SetByScript	( ID );
			newFX->SetDamage	(dam);
			newFX->SetDamageType(damType);
			newFX->SetLevel		(lvl);
			newFX->Init			( org, target );		// FIXME: wo wird der effekt erstmalig in die welt eingefügt ?
			newFX->Cast();  
			return newFX;
		}
		else zERR_WARNING("C: oCVisualFX::CreateAndPlay(): VisualFX ID " + id + " not found in visualfxinst.d");
	}
	return 0;

};

oCVisualFX* oCVisualFX::CreateAndPlay(const zSTRING &id,const zPOINT3 &orgPos, const zCVob *target, const int lvl, const float dam, const int damType,const zBOOL isProjectile)
{
	zSTRING ID(id);
	ID.Upper();
	if ( !ID.IsEmpty() )
	{
		if (fxParser->GetSymbol(ID)) 
		{
			oCVisualFX *newFX = zNEW(oCVisualFX());
			newFX->SetIsProjectile(isProjectile);
			// ein wenig kompliziert: hier wird die hierachie festgelegt
			// da es ein einfacher solo effekt ist, ist root == parent == der erzeugte fx
			newFX->root		= newFX;
			newFX->parent	= newFX;

			zSTRING levelID = ID + "_L" + zSTRING(lvl);
			if (fxParser->GetSymbol(levelID)) ID = levelID;

			// origin vob neu erzeugen
			zCVob *vob = zNEW(zCVob);
			vob->SetVobName("_VFX");
			vob->SetPositionWorld(orgPos);
			vob->SetSleeping(TRUE);
			vob->SetDontWriteIntoArchive(TRUE);
			if ( zCCamera::activeCam && zCCamera::activeCam->GetVob() && zCCamera::activeCam->GetVob()->GetHomeWorld() )
			{
				zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVob(vob);
			}

			newFX->SetByScript	( ID );
			newFX->SetDamage	(dam);
			newFX->SetDamageType(damType);
			newFX->SetLevel		(lvl);
			newFX->Init			( vob, target );

			newFX->Cast();  
			return newFX;
		}
		else zERR_WARNING("C: oCVisualFX::CreateAndPlay(): VisualFX ID " + id + " not found in visualfxinst.d");
	}
	return 0;

};


oCVisualFX* oCVisualFX::CreateAndCastFX(const zSTRING &id,const zCVob *org, const zCVob *inflictor)
{
	// FIXME: Hierfür was anderes überlegen. Man muss die Position & Homeworld festlegen 
	// können, da der parent Vob jederzeit gelöscht werden kann
	// einzige temp. Lösung: Mit dieser Methode erschaffene FX sind immer Childs 
	// diese keyFX sollten auch schon im Speicher sein -> Performance
	zSTRING ID(id);
	ID.Upper();
	if ( !ID.IsEmpty() )
	{
		if (fxParser->GetSymbol(ID)) 
		{
			oCVisualFX *newFX = zNEW(oCVisualFX());

			// ein wenig kompliziert: hier wird die hierachie festgelegt
			// da es ein einfacher solo effekt ist, ist root == parent == der erzeugte fx
			newFX->root		= newFX;
			newFX->parent	= newFX;

			zSTRING levelID = ID + "_L" + zSTRING(GetLevel());
			if (fxParser->GetSymbol(levelID)) ID = levelID;

			newFX->SetSpellType	(GetSpellType());
			newFX->SetSpellCat  (GetSpellCat ());
			newFX->SetDamage	(GetDamage()   );
			newFX->SetDamageType(GetDamageType());
			newFX->SetLevel		(GetLevel());
			newFX->SetByScript	( ID );	
			newFX->Init			( org, target, inflictor );

			newFX->Cast();  

			return newFX;
		}
		else zERR_WARNING("C: oCVisualFX::CreateAndCastFX(): VisualFX ID " + id + " not found in visualfxinst.d");
	}

	return 0;
};

oCVisualFX* oCVisualFX::CreateAndCastFX(const zSTRING &id,const zMAT4 &orgMat)
{
	// FIXME: Hierfür was anderes überlegen. Man muss die Position & Homeworld festlegen 
	// können, da der parent Vob jederzeit gelöscht werden kann
	// einzige temp. Lösung: Mit dieser Methode erschaffene FX sind immer Childs 
	zSTRING ID(id);
	ID.Upper();
	if ( !ID.IsEmpty() )
	{
		if (fxParser->GetSymbol(ID)) 
		{
			oCVisualFX *newFX = zNEW(oCVisualFX());
			newFX->root		= newFX;
			newFX->parent	= newFX;

			zSTRING levelID = ID + "_L" + zSTRING(GetLevel());
			if (fxParser->GetSymbol(levelID)) ID = levelID;

			newFX->SetSpellType	(GetSpellType());
			newFX->SetSpellCat  (GetSpellCat());
			newFX->SetDamage	(GetDamage() );
			newFX->SetDamageType(GetDamageType());
			newFX->SetLevel		(GetLevel());
			newFX->SetByScript(ID);

			// origin vob neu erzeugen
			zCVob *vob = zNEW(zCVob);
			vob->SetVobName	("_VFX");
			vob->SetTrafoObjToWorld(orgMat);
			vob->SetSleeping(TRUE);
			GetHomeWorld()->AddVob(vob);
			
			// [EDENFELD] 2.30c vob ist ein Dummy Vob -> keine Persistenz 
			vob->SetDontWriteIntoArchive(TRUE);

			newFX->Init(vob,(zCVob*)0,inflictor);  

			newFX->Cast();  

			return newFX;
		}
		else zERR_WARNING("C: oCVisualFX::CreateAndCastFX(): VisualFX ID " + id + " not found in visualfxinst.d");
	}
	return 0;
};

void oCVisualFX::CalcTrajectory(const zBOOL &updateTargetOnly )
{
	zMAT4 trgtTrafo = Alg_Identity3D();

	if (updateTargetOnly) 
	{
		if (target) 
		{
			if (targetNode) trgtTrafo = target->GetTrafoModelNodeToWorld(targetNode);
			else			trgtTrafo = target->trafoObjToWorld;
		}
		else if (targetPos !=zVEC3(0,0,0)) trgtTrafo.SetTranslation(targetPos);

		if (trajectory.GetNumKeys() != 0) 
		{
			trajectory.SetKey(trajectory.GetNumKeys()-1,trgtTrafo);
			trajectory.Changed();
		}

		return;
	}

	trajectory.Clear();

	if (!origin) return;
	zMAT4 orgTrafo	= Alg_Identity3D();
	zMAT4 trafo		= Alg_Identity3D();

	if ( orgNode ) 		orgTrafo = origin->GetTrafoModelNodeToWorld(orgNode);
	else				orgTrafo = origin -> trafoObjToWorld;

	if ( (emTrjMode & EM_TRJ_FOLLOW) && (ringPos == -1) )
	{
		for (int i=0; i<VFX_MAX_POS_SAMPLES; i++) transRing[i] = orgTrafo.GetTranslation();
		ringPos = 0;
	}

	if (vobList.GetNumInList() == 1) 
	{
		orgTrafo = vobList[0]->trafoObjToWorld;
		trajectory.InsertKey(vobList[0]->trafoObjToWorld);

		return;
	} 
	else if (vobList.GetNumInList() != 0) 
	{
		orgTrafo = vobList[0]->trafoObjToWorld;
		zCVob *lastVob = vobList[0];
		for (int i=1; i<vobList.GetNumInList(); i++)
		{
			trajectory.InsertKey( GetPoseOfHeading(lastVob->GetPositionWorld(),(vobList[i]->GetPositionWorld()-lastVob->GetPositionWorld()).Normalize()) );
			lastVob = vobList[i];
		}
		trajectory.InsertKey( vobList[i-1]->trafoObjToWorld );
		
		return;
	}


	if (target) 
	{
		if (targetNode) trgtTrafo = target->GetTrafoModelNodeToWorld(targetNode);
		else			trgtTrafo = target->trafoObjToWorld;
	}
	else if (targetPos !=zVEC3(0,0,0)) 
	{
		trgtTrafo.SetTranslation(targetPos);
	}
	else 
	{
		zPOINT3 tPos;
		if (emTrjTargetRange==0) 
		{
			tPos	  = orgTrafo.GetTranslation();
			trgtTrafo = orgTrafo;
		}
		else
		{
			zMAT4 flippedTrafo = orgTrafo;
			flippedTrafo.SetAtVector(-flippedTrafo.GetAtVector());
			tPos	  = CalcAziElevRange(emTrjTargetAzi,emTrjTargetElev,emTrjTargetRange,flippedTrafo);
			trgtTrafo = GetPoseOfHeading(tPos, (flippedTrafo.GetTranslation()-tPos).Normalize());
		}
	}

	if (GetIsProjectile() || GetCollisionClass()==zCCollObjectProjectile::S_GetCollObjClass())
	{
		if (origin != target)
		if ( target && (trgtTrafo.GetTranslation() != orgTrafo.GetTranslation()) ) trgtTrafo.SetTranslation(trgtTrafo.GetTranslation() + 50*(trgtTrafo.GetTranslation()-orgTrafo.GetTranslation()).Normalize());
	}

	if ( (emTrjMode & EM_TRJ_TARGET) && (emTrjMode & EM_TRJ_RANDOM) ) 
	{
		const float KEYNUM_REFERENCE_DIST = 100.0f;						// emTrjNumKeys gilt für 1 m distanz und wird höher skaliert bei bedarf.
		
		// first key at origin
		zPOINT3 org			= orgTrafo.GetTranslation();

		int numKeys = (int)(emTrjNumKeys + zRandF() * emTrjNumKeysVar)+1;
		zREAL realDist = (trgtTrafo.GetTranslation()-org).LengthApprox();

		// Spezialbehandlung für Blitz
		if (emTrjMode & EM_TRJ_LINE)
		if (realDist>100) 
		{
			zClamp(realDist, 100.0f, 4000.0f); // maximum 40m
			numKeys *= zFloat2Int(realDist/KEYNUM_REFERENCE_DIST);
		}

		zVEC3	at			= (trgtTrafo.GetTranslation()-org).Normalize();
		float   dist2		= (org - trgtTrafo.GetTranslation()).Length2();
		zMAT4	flippedTrafo= GetPoseOfHeading(org,-at);
		float	stepDist	= (org - trgtTrafo.GetTranslation()).LengthApprox()/numKeys;  // grobe Schätzung der Schrittweite
		zPOINT3 lastKey		= org;
		zPOINT3 lastStep	= org;

		// FIXME: Optimize heavily!!
		for (int i=0; i<numKeys; i++)
		{
			float	nextStep	= stepDist + zRandF() * emTrjKeyDistVar;

			zPOINT3 newKey		= CalcAziElevRange(	2*(zRandF()-0.5F) * emTrjAngleHeadVar, 
							 						2*(zRandF()-0.5F) * emTrjAngleElevVar, 
													nextStep*0.01F, 
													flippedTrafo );

			lastStep += nextStep * at;
			if ( (lastStep-org).Length2() >= dist2 ) break;

			flippedTrafo.SetTranslation(lastStep);
			trajectory.InsertKey( GetPoseOfHeading( lastKey, (newKey - lastKey).Normalize() ) );
			lastKey = newKey;
		}
		if (trgtTrafo.GetTranslation() != lastKey) trafo = GetPoseOfHeading(trgtTrafo.GetTranslation(), (trgtTrafo.GetTranslation()-lastKey).Normalize());
		else trafo = trgtTrafo;

		trajectory.InsertKey(trafo);

	}
	else if (emTrjMode & EM_TRJ_TARGET) 
	{
		trajectory.InsertKey(orgTrafo);
		if (trgtTrafo.GetTranslation()!=orgTrafo.GetTranslation()) {
			trafo = GetPoseOfHeading(trgtTrafo.GetTranslation(), (trgtTrafo.GetTranslation()-orgTrafo.GetTranslation()).Normalize());
		}
		else trafo = trgtTrafo;

		trajectory.InsertKey(trafo);
	}
	else trajectory.InsertKey(orgTrafo);

	trajectory.SetMode(emTrjMode);
	trajectory.Calc();

	if (lightning && zDYNAMIC_CAST<zCPolyStrip>(GetVisual()))
	{
		zCPolyStrip *trl = static_cast<zCPolyStrip*>(GetVisual());

		trl->FreeResources();
		trl->AllocateResources	(128);

		for (int i=0; i<trajectory.GetNumKeys(); i++) 
		{
			zPOINT3 p1 = trajectory.GetKey(i).GetTranslation();
			trl->AddSegment	(p1-emTrjEaseVel*float(GetLevel())*GetUpVectorWorld(), p1+emTrjEaseVel*float(GetLevel())*GetUpVectorWorld());
		}
	}

	const float SC_LSPPART_DIST = 1;

	// Update dirModeTargetPos if visual is a particle
	if ( zDYNAMIC_CAST<zCParticleFX>(GetVisual()) && static_cast<zCParticleFX*>(GetVisual())->GetEmitter() ) 
	{
		zCParticleEmitter *em = static_cast<zCParticleFX*>(GetVisual())->GetEmitter();

		if (em->dirMode			 == zPFX_EMITTER_DIRMODE_TARGET && 
			em->dirModeTargetFOR == zPFX_FOR_WORLD && 
			em->dirFOR			 == zPFX_FOR_WORLD
		    ) 
		{
			em->dirModeTargetPos = trgtTrafo.GetTranslation();
//			em->dirModeTargetPos = target->GetPositionWorld();
			float dist = (orgTrafo.GetTranslation()-trgtTrafo.GetTranslation()).LengthApprox();
			em->lspPartAvg = (SC_LSPPART_DIST * dist) / em->velAvg;
		}
	}
}

void oCVisualFX::SetOrigin		( zCVob *orgVob, const zBOOL recalcTrj ) 
{
	if (origin == orgVob) return;
	
	if (origin && origin != this) 
	{
		zRELEASE(origin);
	}

	origin = orgVob;

	// folgendes ist sicherer, falls ein Effekt auf einem Vob läuft, und der origin deleted wird
	if ( origin && this != origin ) 
	{
		if (timeScaled)
		if (zDYNAMIC_CAST<zCModel>(origin->GetVisual()))
		{
			static_cast<zCModel*>(origin->GetVisual())->SetTimeScale(userString[1].ToFloat()/ztimer.GetMotionFactor());
		}

		zADDREF_ACCT(origin);

	}

	if (recalcTrj) CalcTrajectory();

	// step through fx child list, init those
	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->SetOrigin(orgVob);
	for (j=0; j<childList.GetNumInList(); j++) 	childList[j]->SetOrigin(orgVob);

}

void oCVisualFX::SetInflictor		( zCVob *inflictorVob ) 
{
	if (inflictor == inflictorVob) return;
	if (inflictor && inflictor != this) zRELEASE(inflictor);
	inflictor = inflictorVob;

	// folgendes ist sicherer, falls ein Effekt auf einem Vob läuft, und der origin deleted wird
	if (inflictor && this != inflictor ) zADDREF_ACCT(inflictor);

	// step through fx child list, init those
	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->SetInflictor(inflictorVob);
	for (j=0; j<childList.GetNumInList(); j++) 	childList[j]->SetInflictor(inflictorVob);


}

void oCVisualFX::SetTarget		( zCVob *targetVob, const zBOOL recalcTrj ) 
{
	if (target == targetVob) return;
	if (target) 
	{
		if ( showTarget ) target->SetDrawBBox3D(FALSE);
		if (target != this) zRELEASE(target);
	}
	target = targetVob;

	if (target) 
	{
		// folgendes ist sicherer, falls ein Effekt auf einem Vob läuft, und der target deleted wird
		if ( this!=target ) zADDREF_ACCT(target);

		targetPos = target->GetPositionWorld();

		if (zDYNAMIC_CAST<zCModel>(target -> GetVisual()) && !emTrjTargetNode_S.IsEmpty()) 
		{
			emTrjTargetNode_S.Upper();
			targetNode = static_cast<zCModel*>(target->GetVisual())->SearchNode(emTrjTargetNode_S);
		}
	}

	if (recalcTrj) CalcTrajectory();

	// step through fx child list, init those
	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->SetTarget(targetVob);
	for (j=0; j<childList.GetNumInList(); j++) 	childList[j]->SetTarget(targetVob);

}

void oCVisualFX::SetTarget		( zPOINT3 &pos, const zBOOL recalcTrj )
{
	targetPos = pos;
	if (target && target != this) zRELEASE(target);
	if (recalcTrj)  CalcTrajectory();

	// step through fx child list, init those
	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->SetTarget(pos);
	for (j=0; j<childList.GetNumInList(); j++) 	childList[j]->SetTarget(pos);

}
			
void oCVisualFX::CreateInvestFX()
{
	if ( !fxInvestOrigin )
	if ( !emFXInvestOrigin_S.IsEmpty() )
	{
		emFXInvestOrigin_S.Upper();
		if (fxParser->GetSymbol(emFXInvestOrigin_S)) 
		{
			fxInvestOrigin = zNEW(oCVisualFX());
			fxInvestOrigin->root  = fxInvestOrigin;

			fxInvestOrigin->parent= fxInvestOrigin;
			fxInvestOrigin->SetByScript(emFXInvestOrigin_S);
			fxInvestOrigin->parent= fxInvestOrigin;
		}
	}
	
	if ( !fxInvestTarget )
	if ( !emFXInvestTarget_S.IsEmpty() )
	{
		emFXInvestTarget_S.Upper();
		if (fxParser->GetSymbol(emFXInvestTarget_S)) 
		{
			fxInvestTarget = zNEW(oCVisualFX());
			fxInvestTarget->root  = fxInvestTarget;

			fxInvestTarget->parent= fxInvestTarget;
			fxInvestTarget->SetByScript(emFXInvestTarget_S);
			fxInvestTarget->parent= fxInvestTarget;
		}
	}
};

void oCVisualFX::InitInvestFX()
{
	if (fxInvestOrigin && !fxInvestOriginInitialized)
	{
		fxInvestOrigin->SetDamage(GetDamage());
		fxInvestOrigin->SetDamageType(GetDamageType());
		fxInvestOrigin->SetSpellType(GetSpellType());
		fxInvestOrigin->SetSpellCat (GetSpellCat());
		fxInvestOrigin->Init(origin,target,inflictor);
		fxInvestOriginInitialized = TRUE;
	}
	if (fxInvestTarget && !fxInvestTargetInitialized && target) 
	{
		fxInvestTarget->SetDamage(GetDamage());
		fxInvestTarget->SetDamageType(GetDamageType());
		fxInvestTarget->SetSpellType(GetSpellType());
		fxInvestTarget->SetSpellCat (GetSpellCat());
		fxInvestTarget->Init(target,origin,origin);
		fxInvestTargetInitialized = TRUE;
	}
};
 
void oCVisualFX::StopInvestFX	( )	
{

	if (fxInvestStopped || GetState() < zVFXSTATE_INVESTNEXT) return;
	if (fxInvestOrigin)
	{ 
		fxInvestOrigin->Stop();
        zRELEASE(fxInvestOrigin); // [Moos] Leakfix
	}
	if (fxInvestTarget) 
	{
		fxInvestTarget->Stop();
        zRELEASE(fxInvestTarget); // [Moos] Leakfix
	}

	fxInvestStopped = TRUE;
};

// ab hier: die einzelnen logischen phasen der visualisierungen.
// in den meisten fällen wird ein visualfx cycle so aussehen
// open->init->investnext->investnext->...->cast->[collide]->stop
// oder
// open->init->setlevel->cast->[collide]->stop
// oder
// init->cast
// oder
// init->investnext->investnext->...->stop			(aufrechterhaltungszauber)
void oCVisualFX::Open ()
{
	int stateLevel = static_cast<int>(fxState);

	if ( stateLevel >= zVFXSTATE_OPEN ) return;

	//zERR_MESSAGE(10,0,"C: VIS: Spell open:  " + visName_S);

	zERR_MESSAGE(10,0,"C: VIS: Spell open: " + visName_S + " ,ptr: " + zSTRING(int(this)) );

	InitEffect();

	int index = FindKey("OPEN");
	if (index != -1) {
		actKey	= emKeyList[index];
		UpdateFXByEmitterKey(actKey);
	}

	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->Open();
	for (j=0; j<childList.GetNumInList(); j++)  childList[j]->Open();

	fxState = zVFXSTATE_OPEN;
};

void oCVisualFX::Reset()
{
	zERR_MESSAGE(10,0,"C: VIS: Spell reset: " + visName_S);

	initialized = FALSE;

	if (light) light->RemoveVobFromWorld();
	if ( sfx && sfxHnd ) zsound->StopSound(sfxHnd);

	if (fxInvestOrigin)	fxInvestOrigin->Reset();
	if (fxInvestTarget) fxInvestTarget->Reset();

	SetTarget(NULL);
    SetOrigin(NULL);
    SetInflictor(NULL);

	// nun alle childs reseten 
	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->Reset();
	for (j=0; j<childList.GetNumInList(); j++)  childList[j]->Reset();

	// timer reseten
	collisionTime = 0;
	deleteTime	  = 0;
	nextLevelTime = 0;
	damageTime    = 0;
	easeTime	  = 0;
	trjUpdateTime = 0;
	levelTime	  = 0;
	lifeSpanTimer = 0;
	fxInvestTargetInitialized= FALSE;
	fxInvestOriginInitialized= FALSE;
	queueSetLevel = -1;
	
	fxState					= zVFXSTATE_UNDEF;
};

void oCVisualFX::Init	( const zCVob *orgVob , const zPOINT3 &trgtPos )
{
	if ( static_cast<int>(fxState) > zVFXSTATE_INIT ) return;		// already casted (trajectory update w/init allowed)
	
	zERR_MESSAGE(10,0,"C: VIS: Spell init with position as target " + visName_S);

	SetTarget(NULL);
	targetPos = trgtPos;

	Init(orgVob,(zCVob*)0,orgVob);
}; 

void oCVisualFX::Init	( const zCVob *orgVob , const zCVob *trgtVob, const zCVob *inflictorVob )
{	
	if ( static_cast<int>(fxState) >= zVFXSTATE_CAST ) return;		// already casted (trajectory update w/init allowed)

	zBOOL alreadyInitialized = (fxState >= zVFXSTATE_INIT);

	zERR_MESSAGE(10,0,"C: Spell init with vob as target " + visName_S);

	// wenn bereits initialisiert wurde, müssen evtl. bereits vorher stattgefundene AddRefs auf origin/target
	// vobs wieder gelöst werden
	if ( target && target!=this ) 
	{
		if ( showTarget ) target->SetDrawBBox3D(FALSE);
	}

//	SetOrigin(NULL);
//  SetInflictor(NULL);
//  SetTarget(NULL);

	if (alreadyInitialized) 
	{
//		if ( origin    && inflictor!=this ) zRELEASE(inflictor);
//		if ( inflictor && origin!=this )	zRELEASE(origin);

//        if (origin!=this) zRELEASE(origin); // [Moos]

		// und etwaige invest effekte am target löschen
		if (fxInvestTarget) 
		{
			fxInvestTarget->Stop();
			zRELEASE(fxInvestTarget);
			CreateInvestFX();
		}
	}

	SetOrigin   ((zCVob*)orgVob, FALSE);  
	SetTarget   ((zCVob*)trgtVob, FALSE);
	SetInflictor(inflictorVob ? (zCVob*)inflictorVob : (zCVob*)origin);


	if ( origin && zDYNAMIC_CAST<zCModel>(origin -> GetVisual()) && !emTrjOriginNode_S.IsEmpty() ) 
	{
		emTrjOriginNode_S.Upper();
		orgNode = static_cast<zCModel*>(origin->GetVisual())->SearchNode(emTrjOriginNode_S);
	}

	if (target && zDYNAMIC_CAST<zCModel>(target -> GetVisual()) && !emTrjTargetNode_S.IsEmpty()) 
	{
		emTrjTargetNode_S.Upper();
		targetNode = static_cast<zCModel*>(target->GetVisual())->SearchNode(emTrjTargetNode_S);
		if (showTarget) target->SetDrawBBox3D(TRUE);
	}

	InitEffect();

	// origin vob neu erzeugen falls keins übergeben
	if (origin == NULL)
	{
		// kann man auch als feature durchgehen lassen, aber erst mal sicherheitshalber ne 
		// warnung rausballern!
		zERR_WARNING("C: oCVisualFX::Init() origin vob is NULL");
		zCVob *vob = zNEW(zCVob);
		vob->SetVobName("_VFX");
		vob->SetPositionWorld(GetPositionWorld());
		vob->SetSleeping(TRUE);
		GetHomeWorld()->AddVob(vob);
		vob->SetDontWriteIntoArchive(TRUE);
		SetOrigin(vob);
	}

	for (int i=0; i<GetNumKeys(); i++) 
	{
		emKeyList[i]->vob		= this;
		emKeyList[i]->targetPos	= targetPos;
	}

	if (!alreadyInitialized) 
	{
		int index = FindKey("INIT");
		if (index != -1) 
		{
			actKey	= emKeyList[index];
			UpdateFXByEmitterKey(actKey);
		}
		if (age>=emFXTriggerDelay) 
		if (sfx) 
		{
			zCSoundSystem::zTSound3DParams params;
			params.SetDefaults();
			params.isAmbient3D = sfxIsAmbient;
			sfxHnd = zsound->PlaySound3D(sfx,this,zVFX_SOUNDSLOT_DEFAULT,&params);
		}
		level	= 1;

		fxState = zVFXSTATE_INIT;
	}

	if (!isChild) 
	{
		CalcTrajectory();
		SetTrafoObjToWorld(trajectory.Interpolate(0));
	}
	else SetTrafoObjToWorld(parent->trafoObjToWorld);

	// falls der effekt auf einem npc abgespielt wird, sende eine
	// AssessMagic Wahrnehmung an diesen.
	
	
	if (origin && zDYNAMIC_CAST<oCNpc>(origin) && sendAssessMagic )
	{
		
		oCNpc *inflictorNpc = zDYNAMIC_CAST<oCNpc>(inflictor);
		if (origin != inflictorNpc)
		{
			oCNpc* orgNpc = static_cast<oCNpc*>(origin);
			orgNpc->SetLastHitSpellID (GetSpellType());
			orgNpc->SetLastHitSpellCat(GetSpellCat ());
			orgNpc->AssessMagic_S(inflictorNpc,GetSpellType());
		}
	}

	AdjustShapeToOrigin	   ();

	// step through fx child list, init those
	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->Init(orgVob,trgtVob,inflictorVob);
	for (j=0; j<childList.GetNumInList(); j++) 	childList[j]->Init(orgVob,trgtVob, inflictorVob );

}; 

void oCVisualFX::Init	( const zCArray <zCVob *> &trj )	
{
	// FIXME: ist das nötig
	if (initialized) return; 

	if (ArraysEqual(trj,vobList)) return;

	zCVob *delVob;
	for (int i=vobList.GetNum()-1; i>=0; i--)
	{
		delVob = vobList[i];
		vobList.RemoveIndex(i);
		zRELEASE(delVob);
	};
		
	vobList = trj;

	for (i=0; i<vobList.GetNum(); i++) zADDREF_ACCT(vobList[i]);

	if (trj.GetNumInList()>=1) SetOrigin(trj[0]);
	else					   SetOrigin(NULL);

	vobList = trj;

	if (trj.GetNumInList()>1) Init(trj[0],trj[1]);
	else					  Init(trj[0]);
}; 

void oCVisualFX::InvestNext()
{	
	if ( static_cast<int>(fxState) > zVFXSTATE_INVESTNEXT ) return;		// already casted ? -> exit

	// Problem: Falls hier noch keine Homeworld vorliegt, werden hier evtl. 
	// Effekte durch die zCCamera::activeCam->GetVob()->GetHomeWorld() inserted,
	// was dazu führt, das kurzzeitig ein Effekt in der Mitte des Screens aufblinkt
	// in diesem Fall wird das SetLevel()/InvestNext() erst ausgeführt, wenn
	// InitEffect() beendet wurde
	if (!GetHomeWorld()) 
	{
		queueSetLevel = -2;
		return;
	}

	level++; 
	levelTime = 0;

	if (level>MAX_SPL_LEVEL) level = MAX_SPL_LEVEL;

	zERR_MESSAGE(10,0,"C: VIS: Spell invest next level:" + zSTRING(level) + " : "+visName_S);
	
	InitInvestFX();

	if (fxInvestTarget) fxInvestTarget->InvestNext();
	if (fxInvestOrigin) fxInvestOrigin->InvestNext();

	int index = FindKey("INVEST_" + zSTRING(level));
	if (index != -1) 
	{
		actKey	= emKeyList[index];
		UpdateFXByEmitterKey(actKey);
	}

	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->InvestNext();
	for (j=0; j<childList.GetNumInList(); j++) 	childList[j]->InvestNext();

	fxState = zVFXSTATE_INVESTNEXT;

};

void oCVisualFX::SetLevel( int l, zBOOL force )
{	
	if (l==0) return;
	if ( static_cast<int>(fxState) > zVFXSTATE_INVESTNEXT && !force) return;		// already casted (trajectory update w/init allowed)	

	// Problem: Falls hier noch keine Homeworld vorliegt, werden hier evtl. 
	// Effekte durch die zCCamera::activeCam->GetVob()->GetHomeWorld() inserted,
	// was dazu führt, das kurzzeitig ein Effekt in der Mitte des Screens aufblinkt
	// in diesem Fall wird das SetLevel()/InvestNext() erst ausgeführt, wenn
	// InitEffect() beendet wurde
	if (!GetHomeWorld()) 
	{
		queueSetLevel = l;
		return;
	}

	level	  = l; 
	levelTime = 0;

	if (level>MAX_SPL_LEVEL) level = MAX_SPL_LEVEL;

	zERR_MESSAGE(10,0,"C: VIS: Spell invest next level:" + zSTRING(level) + " : "+visName_S);

	InitInvestFX();

	if (fxInvestTarget) fxInvestTarget->SetLevel(l);
	if (fxInvestOrigin) fxInvestOrigin->SetLevel(l);

	int index = FindKey("INVEST_" + zSTRING(level));
	if (index != -1) 
	{
		actKey	= emKeyList[index];
		UpdateFXByEmitterKey(actKey);
	}

	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->SetLevel(l);
	for (j=0; j<childList.GetNumInList(); j++) 	childList[j]->SetLevel(l);

	if (!force) fxState = zVFXSTATE_INVESTNEXT;
};

int oCVisualFX::GetLevel() const
{
	return level;
};

void oCVisualFX::Cast	(const zBOOL killAfterDone)											
{
	if ( static_cast<int>(fxState) >= zVFXSTATE_CAST ) return;		// already casted ? -> exit

	zERR_MESSAGE(10,0,"C: VIS: Spell cast " + visName_S + " ,ptr: " + zSTRING(int(this)) );

	InitEffect();

	int index = FindKey("CAST");
	if (index != -1) 
	{
		actKey	= emKeyList[index];
		UpdateFXByEmitterKey(actKey);
	}

	for (int j=0; j<fxList.GetNumInList(); j++) fxList[j]->Cast();
	for (j=0; j<childList.GetNumInList();  j++) childList[j]->Cast();

	levelTime = 0;
	keySize   = actSize;
	
	if (actKey) castEndSize = actSize * actKey->visSizeScale;
	
	if (age>=emFXTriggerDelay) 
	{
		if (earthQuake) earthQuake->OnTrigger(0,0);

		if (screenFX)   
		{
			zERR_MESSAGE(10,0,"C: VIS: starting blend effect");
			zCOLOR	fxColor		   = String2Color(userString[1]);
//			zREAL	fovDeg		   = userString[2].ToFloat();			
			screenFX->StartEffect_BlendFadeIn	(userString[2].ToFloat(),fxColor, userString[3], userString[4].ToFloat(), zrenderer->AlphaBlendFuncStringToType(visAlphaBlendFunc_S) );
			//if (fovDeg > 0) screenFX->StartEffect_FOVMorph		(fxLoopDuration,0.1);
		}
	}

	StopInvestFX();

	fxState = zVFXSTATE_CAST;

}; 

void oCVisualFX::Collide( const zBOOL killAfterDone )	
{

	for (int j=0; j<childList.GetNumInList(); j++) 
	{
		int numChilds = childList.GetNumInList();
		childList[j]->Collide(killAfterDone);
		if (childList.GetNumInList() != numChilds) j=-1;  // Evtl. Restart nötig, da ein Stop() die FX/Child Liste des Parents ändert
	};

	int index = FindKey("COLLIDE");
	if (index != -1) 
	{
		actKey	= emKeyList[index];
		UpdateFXByEmitterKey(actKey);
	}
	
	fxState = zVFXSTATE_COLLIDE;

	EndEffect(killAfterDone);
};

void oCVisualFX::Stop	( const zBOOL killAfterDone )	
{

	if ( static_cast<int>(fxState) >= zVFXSTATE_STOP ) return;		// already stopped ? -> exit

//	zERR_MESSAGE(10,0,"C: VIS: Spell stop " + visName_S);
	zERR_MESSAGE(10,0,"C: VIS: Spell stop: " + visName_S + " ,ptr: " + zSTRING(int(this)) );

	for (int j=0; j<childList.GetNumInList(); j++) 
	{
		int numChilds = childList.GetNumInList();
		childList[j]->Stop(killAfterDone);

		if (childList.GetNumInList() != numChilds) j=-1;  // Evtl. Restart nötig, da ein Stop() die FX/Child Liste des Parents ändert
	}

	for (j=0; j<fxList.GetNumInList(); j++) 
	{
		int numFX = fxList.GetNumInList();
		fxList[j]->Stop(killAfterDone);

		if (fxList.GetNumInList() != numFX) j=-1;
	};

	int index = FindKey("STOP");
	if (index != -1) 
	{
		actKey	= emKeyList[index];
		UpdateFXByEmitterKey(actKey);
	}

	StopInvestFX();

	fxState = zVFXSTATE_STOP;

	EndEffect(TRUE);

};

void oCVisualFX::Kill()	
{
	zERR_MESSAGE(10,0,"C: VIS: Spell kill: " + visName_S + " ,ptr: " + zSTRING(int(this)) );

	for (int j=0; j<childList.GetNumInList(); j++) 
	{
		int numChilds = childList.GetNumInList();
		oCVisualFX *nextChild = childList[j];
		int numRefBeforeKill= nextChild->GetRefCtr();
		nextChild->Kill();
		// [EDENFELD] Release() nur durchführen, wenn RefCtr mindestens 1 vorm Killen war
		// (es gab hier ein unnötiges Release beim Equippen einer Firerain Rune, obwohl diese nur ein RefCtr von 1 hatte -> Crash)
		if (numRefBeforeKill>1) zRELEASE_ACCT_NONULL(nextChild);
		if (childList.GetNumInList() != numChilds) j=-1;  // Evtl. Restart nötig, da ein Stop() die FX/Child Liste des Parents ändert
	}

	for (j=0; j<fxList.GetNumInList(); j++) 
	{
		int numFX			= fxList.GetNumInList();
		oCVisualFX *nextFX	= fxList[j];
		int numRefBeforeKill= nextFX->GetRefCtr();
		nextFX->Kill();
		// [EDENFELD] Release() nur durchführen, wenn RefCtr mindestens 1 vorm Killen war
		// (es gab hier ein unnötiges Release beim Equippen einer Firerain Rune, obwohl diese nur ein RefCtr von 1 hatte -> Crash)
		if (numRefBeforeKill>1) zRELEASE_ACCT_NONULL(nextFX);
		if (fxList.GetNumInList() != numFX) j=-1;
	};

    fxList.DeleteList();
    childList.DeleteList(); // [Moos] die Kill()s oben entsprechen ->Releases(); ohne diese beiden Zeilen wird es in DisposeHirarchy() wiederholt.

	if (fxInvestOrigin) 
	{
		int numRefBeforeKill= fxInvestOrigin->GetRefCtr();
		fxInvestOrigin->Kill();
		// [EDENFELD] Release() nur durchführen, wenn RefCtr mindestens 1 vorm Killen war
		// (es gab hier ein unnötiges Release beim Equippen einer Firerain Rune, obwohl diese nur ein RefCtr von 1 hatte -> Crash)
		if (numRefBeforeKill>1)	zRELEASE_ACCT_NONULL(fxInvestOrigin);
	}
	if (fxInvestTarget) 
	{
		int numRefBeforeKill= fxInvestTarget->GetRefCtr();
		fxInvestTarget->Kill();
		// [EDENFELD] Release() nur durchführen, wenn RefCtr mindestens 1 vorm Killen war
		// (es gab hier ein unnötiges Release beim Equippen einer Firerain Rune, obwohl diese nur ein RefCtr von 1 hatte -> Crash)
		if (numRefBeforeKill>1)	zRELEASE_ACCT_NONULL(fxInvestTarget);
	}

	shouldDelete = TRUE;
	CheckDeletion();

	CleanUpCriticalFX();

	this->RemoveVobFromWorld();
	zERR_ASSERT(GetRefCtr()>=1);
	
	// neu: Release is up to caller -> safety
	//zRELEASE_ACCT_NONULL(this);
};

zBOOL oCVisualFX::CanBeDeleted()
{
	if (!shouldDelete) return FALSE;
	for (int i=0; i<fxList.GetNum(); i++) if (!fxList[i]->shouldDelete) return FALSE;
	return TRUE;
};

zBOOL oCVisualFX::IsFinished()
{ 
	if (isDeleted || shouldDelete) return TRUE;

	if (!GetVisual() && visName_S.IsEmpty() && !earthQuake && !screenFX) return TRUE;

	if (zDYNAMIC_CAST<zCParticleFX>(GetVisual())) return static_cast<zCParticleFX*>(GetVisual())->CalcIsDead();
	else if (GetVisual()) return GetVisual()->GetVisualDied(); 

	return FALSE;
};

zBOOL oCVisualFX::IsLooping()
{ 
	if (IsFinished()) return FALSE;
	if (zDYNAMIC_CAST<zCParticleFX>(GetVisual()) && static_cast<zCParticleFX*>(GetVisual())->GetIsOneShotFX()) return FALSE;
	if (this->emFXLifeSpan != VFX_LIFESPAN_FOREVER) return FALSE;
	return TRUE;
};

void oCVisualFX :: InitEffect()
{
	if (GetSleeping()) SetSleeping(FALSE);
	if (initialized) return;

	if (!GetHomeWorld()) 
	{		
		if (origin && origin->GetHomeWorld())
		{
			if (zDYNAMIC_CAST<zCDecal>(GetVisual()))
			{
				zMAT4 newTrafo = this->trafoObjToWorld;
				newTrafo.SetTranslation(newTrafo.GetTranslation() + zVEC3(0,10,0) + (50 * newTrafo.GetAtVector()));
				newTrafo.SetAtVector((zCCamera::activeCamPos-newTrafo.GetTranslation()).Normalize());
				zVEC3 up = (zCCamera::activeCam->GetVob()->GetUpVectorWorld());
				
				zVEC3 right = newTrafo.GetAtVector()^up;
				right[VY]=0;
				right.NormalizeSafe();
				newTrafo.SetRightVector(right);
				newTrafo.SetUpVector   (newTrafo.GetAtVector()^right);
				SetTrafoObjToWorld(newTrafo);
			}
			else if ( orgNode ) SetTrafoObjToWorld(origin->GetTrafoModelNodeToWorld(orgNode));
			else 				
			{
				if (origin->HasParentVob())	
				{
					zCVob *parentVob					= origin->globalVobTreeNode->GetParent()->GetData();
					SetTrafo(parentVob->trafoObjToWorld * origin->trafoObjToWorld);
				}
				else
				{
					SetTrafo(origin->trafoObjToWorld);
				}
			}
			origin->GetHomeWorld()->AddVob(this);
		}
		else if (parent && parent->GetHomeWorld()) 
		{
			SetTrafoObjToWorld(parent->trafoObjToWorld);
			parent->GetHomeWorld()->AddVob(this);
		}
		else if (root && root->GetHomeWorld()) 
		{
			SetTrafoObjToWorld(root->trafoObjToWorld);
			root->GetHomeWorld()->AddVob(this);
		}
		else if ( zCCamera::activeCam && zCCamera::activeCam->GetVob() && zCCamera::activeCam->GetVob()->GetHomeWorld() )
		{
			zERR_WARNING("C: oCVisualFX :: InitEffect(): vob not in world!");
			zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVob(this);
			SetPositionWorld	( zCCamera::activeCam->GetVob()->GetPositionWorld() - 300 * zCCamera::activeCam->GetVob()->GetAtVectorWorld() );
		}
		else if (ogame->GetWorld())
		{
			if (origin) 
			{
				if ( orgNode ) SetTrafoObjToWorld(origin->GetTrafoModelNodeToWorld(orgNode));
				else
				{
					if (origin->HasParentVob())	
					{
						zCVob *parentVob					= origin->globalVobTreeNode->GetParent()->GetData();
						SetTrafo(parentVob->trafoObjToWorld * origin->trafoObjToWorld);
					}
					else
					{
						SetTrafo(origin->trafoObjToWorld);
					}
				}
			}
			ogame->GetWorld()->AddVob(this);
		}
		else zERR_FATAL("C: oVisFX.cpp(oCVisualFX::Open): vob not in world");
	}

	SetVobName			(fxName + " Vob");
	SetSleepingMode		(zVOB_AWAKE);
	SetPhysicsEnabled	(FALSE);
	SetVisualByString	(visName_S);

	if (light) 
	{
		light->SetPositionWorld(GetPositionWorld());
		GetHomeWorld()->AddVobAsChild(light,this);
	}

	initialized = TRUE;

	switch(GetSpellType())
	{
		// projektil geschosse festlegen: FIXME: besser woanders
	case SPL_FIRESTORM:
	case SPL_SKULL:				// FIXME
		if (visName_S.Search("_SPREAD")==-1) SetIsProjectile(TRUE);
		break;
	case SPL_BREATHOFDEATH:
	case SPL_WINDFIST:
	case SPL_WATERFIST:
	case SPL_CHARGEFIREBALL:
	case SPL_INSTANTFIREBALL:
	case SPL_PALDESTROYEVIL:
	case SPL_FIREBOLT:
	case SPL_ICEBOLT:
	case SPL_ICELANCE:
	case SPL_PALHOLYBOLT:
	case SPL_THUNDERBALL:
	case SPL_ICECUBE:
	case SPL_WHIRLWIND:
	case SPL_GREENTENTACLE:
	case SPL_DESTROYUNDEAD:
	case SPL_SUCKENERGY:
	case SPL_PLAGUE:
	case SPL_SUMMONSWARM:
		SetIsProjectile(TRUE);
		break;
	default:
		break;
	}

	SetCollisionEnabled(emCheckCollision);

	if (queueSetLevel != -1)
	{
		if (queueSetLevel == -2) oCVisualFX::InvestNext(); 
		else					 oCVisualFX::SetLevel(queueSetLevel); 

		queueSetLevel = -1;
	}

	fxStartTime = ztimer.GetTotalTimeF()/ztimer.GetMotionFactor();
};


void oCVisualFX :: EndEffect(const zBOOL killAfterDone)
{
	// here check other visuals, e.g. one shot tex decal anis
	if (timeScaled)
	{
		ztimer.SetMotionFactor(1);
		if (origin && zDYNAMIC_CAST<zCModel>(origin->GetVisual()))
		{
			static_cast<zCModel*>(origin->GetVisual())->SetTimeScale(1);
		}
	}

	SetCollDet(FALSE);
	if (killAfterDone) 
	{
		// Wenn der Vob schläft, löschen wir ihn sofort
		// ansonsten wird der effekt smooth ausgeblendet 
		if ( GetSleeping() ) 
		{
			RemoveVobFromWorld();
			return;
		} 
		else{
            isDeleted = TRUE;
        }
	}
	else SetShowVisual(FALSE);
};

void oCVisualFX::ReportCollision(const zCCollisionReport& collisionReport)
{
	if (!parent || !root) return;

	if ( static_cast<int>(fxState) <= zVFXSTATE_INVESTNEXT ) {
		zERR_WARNING(" C: oCVisualFX::ReportCollision(): collision before INVESTNEXT state (Name:" + visName_S + " )!!");
	}
	
	// weitere kollision 0 bis zum Ende dieser Methode vermeiden
	zBOOL doCollide= FALSE;

	//SetCollDet(FALSE);

	if (parent != root || isChild ) 
	{
		parent->ReportCollision(collisionReport); // recursive collision message
		lastTrjDir = parent->GetLastTrjDir();
		collisionCtr = parent->collisionCtr;
	}
		
	collisionOccured = TRUE;

	// achtung: ohne TACTION_COLL_BOUNCE findet keine Coll Resp. statt, und ein erzeugen eines neuen 
	// effektes findet evtl. an einer nicht freien Stelle statt
	
	zERR_ASSERT(collisionReport.m_poCollObject1);

	// das richtige Ziel Collision Objekt rauspicken 

	zCCollisionObject *collidedObject;
	zVEC3			   collNormal;

	if ( GetCollisionObject() == collisionReport.m_poCollObject0 )
	{
		collidedObject = collisionReport.m_poCollObject1;
		collNormal	   = collisionReport.m_oCollNormal1;
	}
	else
	{
		collidedObject = collisionReport.m_poCollObject0;
		collNormal	   = collisionReport.m_oCollNormal0;
	}
		
	// dynamische kollision
	if (collidedObject->GetCollObjClass()!=zCCollObjectLevelPolys::S_GetCollObjClass()) 
	{
		zSVisualFXColl newColl;
		zCVob *vobHit = static_cast<zCVob*>(collidedObject->GetClientData());
		zERR_ASSERT(vobHit);

		newColl.foundVob			= vobHit;
		newColl.foundContactPoint	= collisionReport.m_oContactPoint;
		newColl.foundNormal			= collNormal;
		
		if (vobHit->GetInMovement())
		{
			zERR_MESSAGE(10,0,"C: VIS: queueing vob collision..." + visName_S);
			zADDREF_ACCT(vobHit);
			queuedCollisions.InsertEnd(newColl);
		}
		else doCollide = ProcessCollision(newColl);
	}
	else 
	{
		zERR_MESSAGE(10,0,"C: VIS: collision (level)" + visName_S);
		zBOOL alignToNormal = (emFXCollStatAlign_S == "COLLISIONNORMAL");

		if	    ( emActionCollStat & TACTION_COLL_BOUNCE )   CollisionResponse(collNormal,alignToNormal);
		else if ( emActionCollStat & TACTION_COLL_COLLIDE)   
		{
			ResetToOldMovementState();
			doCollide = TRUE;
		}

		if (emActionCollStat & TACTION_COLL_CREATE_QUAD)
		{
			zCQuadMark *quadMark = zNEW(zCQuadMark);
			zCQuadMark::zTEffectParams	aniEffects;
			aniEffects.alphaFadeSpeed  = 0.01f;
			aniEffects.texAniScaleStart= 0.2f;
			aniEffects.texAniSpeed	   = 0.2F;
			aniEffects.texAniType	   = zCQuadMark::zTEXANI_SCALEUP_GRAV;

			quadMark->SetTexture		(userString[0]);
			quadMark->SetAlphaFadeSpeed	(0.015F);
			quadMark->GetDefaultMaterial().SetAlphaBlendFunc(zrenderer->AlphaBlendFuncStringToType(userString[2]));

			zCVob *quadVob = zNEW(zCVob);
			quadVob -> SetVobName("_VFX_Quad");
			quadVob -> SetPositionWorld(GetPositionWorld());
			quadVob -> SetVisual(quadMark);
			quadVob -> SetDontWriteIntoArchive(TRUE);
			GetHomeWorld()->AddVobRelease(quadVob);
			zVEC3 userVec3 = String2Vec3(userString[1]);
			zVEC2 quadDim(userVec3[VX],userVec3[VY]);
			zVEC3 at;
			if (origin) at = (GetPositionWorld() - origin->GetPositionWorld()).NormalizeApprox();
			else		at = GetAtVectorWorld();
//			quadMark->CreateQuadMark(GetPositionWorld()-10*at,at*100,quadDim,&aniEffects);
			quadMark->CreateQuadMark(GetPositionWorld()-10*at,at*100,quadDim);

            zRELEASE(quadMark); // [Moos] Leakfix; die Welt kümmert sich ab jetzt um das Ding.
		}
		
		if (collisionCtr < 2) // emergency: bei statischer welt kollision wird nur maximal einmal ein child fx am kollisionspunkt erzeugt
		if      ((emActionCollStat & TACTION_COLL_CREATE ) && (!emFXCollStat_S.IsEmpty()) ) 
		{
			if ( !(emActionCollStat & TACTION_COLL_BOUNCE) ) ResetToOldMovementState();

			zMAT4 trafo;
			if (alignToNormal) trafo = GetPoseOfHeading( GetPositionWorld(), collNormal);
			else			   trafo = GetPoseOfHeading( GetPositionWorld(), this->GetAtVectorWorld() );

			oCVisualFX *fx = CreateAndCastFX(emFXCollStat_S,trafo);
			if (fx)
			{
				if (fx->IsLooping()) 
				{
					zERR_WARNING("C: oCVisualFX::ReportCollision(), created (stat) collision fx " + emFXCollStat_S + " has infinite duration");
					fx->SetDuration(1000);
				}
			}
			zRELEASE(fx);
		}
	}

	// und wieder alten koll zustand herstellen (nur falls nicht gelöscht)

	if (doCollide) Collide(TRUE);		
	// ACHTUNG: this kann ab hier ungültig sein!
};

zBOOL oCVisualFX::ProcessQueuedCollisions()
{
//	zERR_ASSERT(!isChild);

	zBOOL doCollide = FALSE;

	for (int i=0; i<queuedCollisions.GetNum(); i++)
	{
		doCollide |= ProcessCollision(queuedCollisions[i]);
		zRELEASE(queuedCollisions[i].foundVob);
	} 

	queuedCollisions.DeleteList();

	if (doCollide) Collide(TRUE);		
	return doCollide;
};

zBOOL oCVisualFX::ProcessCollision		(zSVisualFXColl &coll)
{
	// FIXME: das ist ein hack für Defect #1805 , der dafür sorgt das nicht der Spieler getroffen wird
	// zusammen mit CREATE_ONCE dürfte nur noch ein Vob in der Umgebung anfangen zu brennen
	// Idee: es gibt zwei CollisionFX. Ein One Shot FX, der _kein_ AssessMagic sendet, und ein FX, der es tut, aber
	// nur wenn eine vorher aufgerufene Skript Funktion dies erlaubt (C_CanSpellCollideWith). Wenn ja, dann wird tatsächlich
	// von dem "statetrigger-fx" das assessmagic, bzw. assessstopmagic getriggert.
	// C_CanSpellCollideWith(int spellID, self, inflictor). 
	// liefert false: nur ambient collision fx abspielen (kein damage)
	// liefert true : ambient collision fx abspielen, und zweiten coll fx übers OnDamage interface starten, dieser hat ein sendassessmagic!

	zCVob *vobHit	=	coll.foundVob;
	zBOOL doCollide =	FALSE;

	zERR_ASSERT(vobHit);

	if (origin != vobHit) 
	{		
		zERR_MESSAGE(10,0,"C: VIS: collision (vob) " + visName_S + " with vob:" + vobHit->GetVobName() );

		if	    ( emActionCollDyn & TACTION_COLL_BOUNCE )   CollisionResponse(coll.foundNormal,(emFXCollDynAlign_S == "COLLISIONNORMAL"));		
		// Damage an alle Vobs weiterreichen

		zBOOL collStat, collDyn;

		if (!collidedVobs.IsInList(vobHit))
		{
			collidedVobs.InsertEnd(vobHit);
			zADDREF_ACCT(vobHit);
		}

		// Achtung: Hier muss die Kollision des getroffenen Vobs kurzzeitig ausgeschaltet
		// werden, ansonsten gibt es eine Endlosschleife beim OnDamage (NSC meldet Coll an die Spell AI-> kommt hier wieder rein, usw...)
		collStat = vobHit->GetCollDetStat();
		collDyn  = vobHit->GetCollDetDyn ();

		vobHit->SetCollDet(FALSE);

		// wenn nur einmal collidieren soll, in die ignore liste eintragen
		if ( (emActionCollDyn & TACTION_COLL_CREATE_ONCE) ) 
		{
			zADDREF_ACCT(vobHit);
			ignoreVobList.Insert(vobHit);
		}

		// 1. den normalen emFXCollDyn_S FX starten (ACHTUNG: hier darf kein sendAssessMagic aktiv sein)
		//
		oCVisualFX* hitFX = oCVisualFX::CreateAndPlay(this->emFXCollDyn_S, vobHit, origin, GetLevel(), GetDamage(), GetDamageType());
		if (hitFX) hitFX->SetInflictor(inflictor);
		zRELEASE(hitFX);

		// 2. Skript Funktion aufrufen, die checkt ob ein emFXCollDynPers_S auf dem Target gestartet werden soll
		// [1.21] aber nur, wenn das target auch ein NPC ist.
		oCNpc *targetNPC = zDYNAMIC_CAST<oCNpc>(target);

		//
		const int COLL_DONOTHING			= 0;
		const int COLL_DOEVERYTHING			= 1<<0;
	//	const int COLL_APPLYDAMAGE			= 1<<1;
		const int COLL_APPLYHALVEDAMAGE		= 1<<2;
		const int COLL_APPLYDOUBLEDAMAGE	= 1<<3;
		const int COLL_APPLYVICTIMSTATE		= 1<<4;
		const int COLL_DONTKILL				= 1<<5;


		int collideState = COLL_DOEVERYTHING;

		if (targetNPC)
		{
			parser.SetInstance("SELF"	,targetNPC);
			parser.SetInstance("OTHER"	,zDYNAMIC_CAST<oCNpc>(origin));
			int index = parser.GetIndex("C_CANNPCCOLLIDEWITHSPELL");
			if (index>0) collideState = *(int*)parser.CallFunc(index,GetSpellType());
			else zERR_WARNING("C: Skript Func C_CANNPCCOLLIDEWITHSPELL unknown!");
		}

		// 3. liefert die Skript Funktion was gültiges zurück, kollidieren, und in "B_ASSESSMAGIC" dann die ZS etc. starten
		if ( collideState != COLL_DONOTHING )
		{
			zBOOL createOnItem = TRUE;
			oCNpc *vobHitNpc = zDYNAMIC_CAST<oCNpc>(vobHit);
			if (vobHitNpc && vobHitNpc->IsConditionValid())
			{
				zREAL logicDamageScale = 1.0f;
				if	(collideState & COLL_APPLYHALVEDAMAGE)	logicDamageScale = 0.5F; else
				if	(collideState & COLL_APPLYDOUBLEDAMAGE) logicDamageScale = 2.0F; 

				oCNpc::oSDamageDescriptor desc;
				//oCNpc::oEDescDamageFlags  flags;
				//desc.dwFieldsValid = oEDamageDescFlag_Attacker |
				//					 oEDamageDescFlag_Attacker

				zBOOL bBurning = (GetDamageType() & oEDamageType_Fire);
									
				desc.fDamageTotal  = GetDamage	  () * GetLevel() * logicDamageScale;
				desc.enuModeDamage = GetDamageType();
				desc.nSpellID	   = GetSpellType ();
				desc.nSpellCat	   = GetSpellCat  ();
				desc.nSpellLevel   = GetLevel	  ();
				desc.pVobAttacker  = inflictor;
				desc.pNpcAttacker  = zDYNAMIC_CAST<oCNpc>(inflictor);
				desc.pVobHit	   = vobHit;
				desc.vecLocationHit= coll.foundContactPoint;
				desc.bDamageDontKill= collideState & COLL_DONTKILL;

				if ( (collideState & COLL_DOEVERYTHING) || (collideState & COLL_APPLYVICTIMSTATE))
				{
					desc.strVisualFX   = bBurning ? "" : emFXCollDynPerc_S;
					desc.SetFXHit       (this);
				}
				else desc.strVisualFX.Clear();

				//	zADDREF_ACCT(this); // [Moos] ist im Aufruf von SetFXHit schon drin.

				//	hier schon mal den schaden entsprechend des schadens-typs aufspalten
				//	(noetig, falls der caster ein monster ist, da sonst bei nicht angegebenen einzel-schaeden seine staerke verwendet wuerde)
				if (emCheckCollision!=2)
				{
					int nDamageTotal = (int) (desc.fDamageTotal);
					::ApplyDamages( desc.enuModeDamage, (int*) desc.aryDamage, nDamageTotal );
					oCMsgDamage* pMsgDamage = zNEW(oCMsgDamage(oCMsgDamage::EV_DAMAGE_ONCE,desc));

					vobHitNpc->GetEM()->OnMessage(pMsgDamage, NULL);
				}

				// ein zweiter effekt muss auf dem NPC als Item Effekt gestartet werden, wenn sowohl
				// fire damage UND ein child effekt angegeben wurde
				createOnItem = ( (!emFXCollDynPerc_S.IsEmpty()) && bBurning);
			}
			if (createOnItem)
			{	// alle anderen vobs über das engine interface
				oCVisualFX *fx = CreateAndCastFX(emFXCollDynPerc_S,vobHit,origin); 
				if (fx)
				{
					if (fx->IsLooping())
					{
						int nTicksPerDamagePoint = 1000;
						zCPar_Symbol  *pSymbol = ::parser.GetSymbol( "NPC_BURN_TICKS_PER_DAMAGE_POINT" );
						if ( pSymbol ) pSymbol->GetValue( nTicksPerDamagePoint );

						float fTimeDuration		= float(nTicksPerDamagePoint * this->GetDamage())/1000;
						fx->SetDuration(fTimeDuration);
					};
					zRELEASE(fx);
				}
				#if 0
				if (!vobHitNpc) vobHit->GetEM()->OnDamage	( this, origin, damage*GetLevel(), damageType,coll.foundContactPoint);
				#endif
			}
		}
		vobHit->SetCollDetDyn	(collDyn);
		vobHit->SetCollDetStat	(collStat);

		if ( emActionCollDyn & TACTION_COLL_COLLIDE)   doCollide = TRUE;
	}

	return doCollide;
};


void oCVisualFX::CollisionResponse(const zVEC3 &collisionNormal, zBOOL alignCollNormal )
{
	zVEC3 dir;

	if (isChild) return; // children haben keine collision response
		
	collisionCtr++;

	//if (collisionCtr >1) zERR_WARNING("C: collisionCtr: " + zSTRING(collisionCtr) );
	// auf die Position vor dem BeginMovement setzen. Diese Position darf niemals kollidieren!
	ResetToOldMovementState();

	// fand mehrmals hintereinander eine collision response statt, wird eine varianz
	// auf den richtungvector aufgerechnet
	if ( collisionCtr > zVFX_MAX_CONTINOUS_COLL ) 
	{
		// emergency: Kollision fand zu oft hintereinander statt, ohne das der Vob freigekommen
		// ist. Falls der Vob schon gecasted wurde, wird er jetzt einfach gestoppt
		if ( fxState >= zVFXSTATE_CAST ) {
			zERR_WARNING("C: Emergency Stop: " + zSTRING(collisionCtr) );
			Stop();
		}
		else {
			zERR_WARNING("C: collisionCtr > zVFX_MAX_CONTINOUS_COLL, reset! " );
			collisionCtr = 0;
		}
	}

	if ( collisionCtr > 2 ) dir = (GetLastTrjDir() + zVEC3(zRandF(0.1F),zRandF(0.1F),zRandF(0.1F))).Normalize();
	else					dir = GetLastTrjDir();

	// nun die trajectory anpassen
	lastTrjDir = trajectory.RecalcByColl( GetPositionWorld(),dir,collisionNormal,alignCollNormal );

	// falls das visual ein polystripe ist und die trajectory pro frame angezeigt werden soll, ist
	// auch hier eine anpassung nötig
	if (lightning && zDYNAMIC_CAST<zCPolyStrip>(GetVisual()))
	{
		zCPolyStrip *trl = static_cast<zCPolyStrip*>(GetVisual());
		trl->FreeResources();
		trl->AllocateResources	(128);

		for (int i=0; i<trajectory.GetNumKeys(); i++) 
		{
			zPOINT3 p1 = trajectory.GetKey(i).GetTranslation();
			trl->AddSegment	(p1-emTrjEaseVel*float(MAX(1.0f,level))*GetUpVectorWorld(), p1+emTrjEaseVel*float(MAX(1.0f,level))*GetUpVectorWorld());
		}
	}

	collisionOccured = FALSE;
}

void oCVisualFX::SetCollisionCandidates(zCArray <zCVob *> collisionVobs)
{
	// alte Kandidaten dereferenzieren und entfernen
	for (int i=allowedCollisionVobList.GetNum()-1; i>=0; i--) 
	{
		zCVob* delVob = allowedCollisionVobList[i];
		allowedCollisionVobList.RemoveIndex(i);
		zRELEASE(delVob);
	}

	allowedCollisionVobList.DeleteList();

	allowedCollisionVobList = collisionVobs;
	for (    i=0; i<allowedCollisionVobList.GetNum(); i++) zADDREF_ACCT(allowedCollisionVobList[i]);

}

zBOOL oCVisualFX::GetCollidedCandidates	(zCArray <zCVob *> &resCollVobList)
{
	if (collidedVobs.GetNum() == 0) return FALSE;
	resCollVobList = collidedVobs;
	return TRUE;
};

zBOOL oCVisualFX::CanThisCollideWith		(zCVob* vob)	
{ 
	//SetPhysicsEnabled(TRUE);
	assert(vob);
	if (!emCheckCollision)	return FALSE;
	
	if (!vob->GetVisual())	return FALSE;
	
	if (vob == origin)		return FALSE;
	if (vob == inflictor)	return FALSE;			// hab ich den spruch selber verursacht -> kein treffer
	if (vob == this   )		return FALSE;

	// schon mal kollidiert ?(CREATEONCE) -> raus hier
	if ( ignoreVobList.IsInList(vob) )  return FALSE;

	if ( allowedCollisionVobList.GetNum() > 0 )
	{
		// spezialfall: nur die vobs, die gewünscht sind, collidieren lassen
		if ( allowedCollisionVobList.IsInList(vob) ) return TRUE; 
		else									     return FALSE;		
	}
	else if (!oCSpell::IsTargetTypeValid(vob,spellTargetTypes)) return FALSE;

	// inter visfx collision explicitly disabled
	if ( zDYNAMIC_CAST<oCVisualFX>(vob) || vob->GetVobName()=="_VFX"  ) return FALSE;	

	// collision with arrows disabled
	if ( zDYNAMIC_CAST<oCItem>(vob) && zDYNAMIC_CAST<oCAIArrow>(vob->GetAI()) )	return FALSE;

	// folgende abfrage für #2690 (Magie-NSCs treffen andere NSCs)
	if ( allowedCollisionVobList.GetNum() == 0 &&		// kein massenvernichtsungspruch
		 inflictor != oCNpc::player		   &&		// caster ist nicht der sc 
		 zDYNAMIC_CAST<oCNpc>(target)!= NULL  &&		// es gibt ein target nsc
		 target != vob						   &&		// der getroffene vob ist nicht das target auf das gezielt wurde
		 zDYNAMIC_CAST<oCNpc>(vob)			   &&		// der getroffene vob ist ein nsc
		 !static_cast<oCNpc*>(vob)->IsMonster() )		// getroffenes target ist kein monster
	{
		 return FALSE;
	}

	// vereinbarung: wenn der spieler den effekt selber gecasted hat, darf er nicht getroffen werden
	if ( inflictor == oCNpc::player && vob == oCNpc::player )			return FALSE;	

	// wenn einer der childs nicht mit dem collision vob kollidieren darf, darf this auch nicht collidieren
	for (int i=0; i<childList.GetNumInList(); i++) {
		if (childList[i]->emCheckCollision)				// nimmt das child an der kollision teil ?
		if (!childList[i]->CanThisCollideWith(vob)) return FALSE;
	}
	for (i=0; i<fxList.GetNumInList(); i++) {
		// nimmt das child an der kollision teil ?
		if (fxList[i]->emCheckCollision)
		if (!fxList[i]->CanThisCollideWith(vob)) return FALSE;
	}
	
	return TRUE;

};


zBOOL oCVisualFX :: CheckDeletion()
{
	// endgültig löschen -> ai davon in Kenntnis setzen
	if ( shouldDelete )
	{ 
		// Dieser Effekt soll in DOAI gelöscht werden falls ausserhalb dieses Scopes keine Referenzen mehr auf "This" existieren, daher werden hier alle Module, die Referenzen auf "This"
		// haben können (Sounds / NPCs) vom beenden dieses Effektes informiert

		// ggfs. AssessStopMagic senden
		
		if (origin && zDYNAMIC_CAST<oCNpc>(origin) && sendAssessMagic )
		{
			oCNpc *inflictorNpc = static_cast<oCNpc*>(inflictor);
			if (origin != inflictorNpc)
			static_cast<oCNpc*>(origin)->AssessStopMagic_S(inflictorNpc,GetSpellType());
		}

		// sounds löschen
		if ( sfx )	
		{
			zRELEASE_ACCT_NONULL(sfx);
			if (sfxHnd) zsound->StopSound(sfxHnd);
			sfx = 0;
		}

		// emitter keys können ptr. auf Sounds beinhalten. die wieder "thjs" referenzieren
		for (int i=0; i<emKeyList.GetNumInList(); i++) delete emKeyList[i];
		emKeyList.DeleteList();

		// Falls nun keine Referenzen ausserhalb dieses Scopes existieren, darf "this" im nächsten Frame 
		// in oCVisualFXAI::DoAI gelöscht werden
		ai->RequestDeletion();
		return TRUE;
	}

	// soll gelöscht werden, wenn bereits gecasted UND: 
	// a) visual tot oder
	// b) oCVisualFX::Stop() aufgerufen wurde oder
	// c) oCVisualFX::Collide() aufgerufen wurde oder
	// c) emFXLifeSpan abgelaufen ist 
	if ( !isDeleted )
	if ( IsFinished() )
	{
		if (fxState < zVFXSTATE_CAST) {
			zERR_WARNING("C: VIS: (oCVisualFX :: CheckDeletion()): Visual died before spell was casted. Name:" + visName_S);
		} else 
		{
			//IsFinished();  
			// FIXME: manchmal ist hier finished, obwohl es nicht sein dürfte!
			// (pfx->firstPart ist NULL, obwohl pfx noch nicht gestartet
			// workaround (?) bis Problem geklärt: solange CreateParticles() in oCVisualFX::SetVisualByName()
			// aufrufen, bis PFX nicht mehr tot ist. 
			isDeleted = TRUE;
		};
	}

	if (emFXLifeSpan != -1)		// lifespan set by visual lifespan ?
	{
		// no, custom set lifespan
		lifeSpanTimer += frameTime;
		if (lifeSpanTimer >= emFXLifeSpan) 
		{
			emFXLifeSpan = -1;
			isDeleted	 = TRUE;
		}
	}

	if (!isDeleted) return FALSE;

	if (zDYNAMIC_CAST<zCDecal>(GetVisual())) 
	{
		shouldDelete = TRUE;
		return TRUE;
	}

	if (deleteTime == 0) 
	{
		// here: make pfx one shot
		if ( zDYNAMIC_CAST<zCParticleFX>(GetVisual()) && static_cast<zCParticleFX*>(GetVisual())->GetEmitter() )
		{
			zCParticleFX *pfx = static_cast<zCParticleFX*>(GetVisual());

			pfx->StopEmitterOutput();
			pfx->GetEmitter()->ppsIsLooping = FALSE;

			zCParticleEmitter *em = pfx->GetEmitter()->ppsCreateEmitter;
			while (em) 
			{
				if ( em->ppsIsLooping )
				{
					 em->isOneShotFX  = TRUE;
					 em->ppsIsLooping = FALSE;				
				}
				em = em->ppsCreateEmitter;
			}
		}

		if (screenFX) 
		{
			zCOLOR	fxColor		   = String2Color(userString[1]);
			screenFX->StartEffect_BlendFadeOut(userString[2].ToFloat(),fxColor);
		}

		if (timeScaled)
		{
			ztimer.SetMotionFactor(1);
			if (origin && zDYNAMIC_CAST<zCModel>(origin->GetVisual()))
			{
				static_cast<zCModel*>(origin->GetVisual())->SetTimeScale(1);
			}
		}

		deleteTime = .000001F;
	}

	// Der Effekt wurde gestoppt (d.h. von aussen wurde ein isDeleted = TRUE forciert,
	// damit dann das ausblenden aber korrekt abläuft, und der pfx nicht wegpoppt, warten wir hier
	// bis der PFX wirklich gestorben ist
	if ( zDYNAMIC_CAST<zCParticleFX>(GetVisual()) && !static_cast<zCParticleFX*>(GetVisual())->CalcIsDead())   return FALSE;

	deleteTime += frameTime;

	if (deleteTime >= AUTODISPOSE_TIME) 
	{
		deleteTime = AUTODISPOSE_TIME;
		for (int i=0; i<childList.GetNumInList(); i++) childList[i]->Stop();

		shouldDelete = TRUE;
	}

	// lichter und sounds ausblenden
	if (light) {
		light->SetRange( (1-zSinusEase( deleteTime*AUTODISPOSE_TIME_INV )) * lightRange );
	}

	if (fovMorph)
	{
		
		zREAL t = zSinusEase( deleteTime*AUTODISPOSE_TIME_INV );
		zREAL fovx, fovy;
		zCCamera::activeCam->GetFOV(fovx, fovy);
		zsound->SetGlobalOcclusion (0.5f*(1-t));	

		zCCamera::activeCam->SetFOV		( zLerp(t, fovx, oldFovX), zLerp(t,fovy, oldFovY));
		zCCamera::activeCam->Activate	();					// FIXME: ugly, => Die Camera muss FOV abh. internals setzen..
	}

	if ( sfxHnd ) // sound geladen ?
	{
		zCSoundSystem::zTSound3DParams params;
		if ( zsound->GetSound3DProps(sfxHnd,params) ) // sound aktiv ?
		{
			params.volume = 1-zSinusEase( deleteTime*AUTODISPOSE_TIME_INV );

			zsound->UpdateSound3D(sfxHnd,&params);
		}
	}

	if ( GetVisual() /*&& !dynamic_cast<zCParticleFX*>(GetVisual()) */&& (visAlpha != 0) )
	{
		this->SetVisualAlphaEnabled(TRUE);
		this->SetVisualAlpha(1-zSinusEase( deleteTime*AUTODISPOSE_TIME_INV ));
	}

	return FALSE;
};


void oCVisualFX :: UpdateActKey()
{
	if (actKey) 
	{ 
		zBOOL casted = ( static_cast<int>(fxState) >= zVFXSTATE_CAST );

		if (!casted || (casted && actKey->visSizeScale != 0)) 
		if (zDYNAMIC_CAST<zCDecal>(GetVisual())) 
		{
			float s = MIN(1,levelTime/actKey->scaleDuration);

			// beim Cast Key wird die letze Grösse zugrunde gelegt und skaliert...

			//if (casted) thisSize = actSize; else thisSize = visSize;

			if (!casted) actSize = Lerp( s , keySize,visSize * actKey->visSizeScale);
			else		 actSize = Lerp( s , keySize,castEndSize				   );

//			zERR_MESSAGE(10,0,"C: oCVisualFX :: UpdateActKey for : " + visName_S);

			static_cast<zCDecal*>(GetVisual())->SetDecalDim(actSize[VX],actSize[VY]);
		}
		
		if (actKey->sfx && actKey->sfxHnd) zsound->UpdateSound3D(actKey->sfxHnd);

		// in der invest phase kann nach einer zeitdauer wieder der alte zustand der letzen
		// logischen visualfx phase hergestellt werden, (TODO: Performance?)
		// VORSICHT: Ist die logische INVEST PHASEN Länge der Magiesprüche kürzer als die
		// in den visualisierungs skripten, so wird der Backupzustand nicht wieder hergestellt

		if ( (emInvestNextKeyDuration != 0) && (fxState == zVFXSTATE_INVESTNEXT) ) 
		{
			nextLevelTime += frameTime;

			if (nextLevelTime > emInvestNextKeyDuration) 
			{ 
				UpdateFXByEmitterKey(fxBackup);
				nextLevelTime = 0; 
			};
		} 
	}
};

void oCVisualFX::DoMovements()
{

	lastTrjPos		= GetPositionWorld();	


	// Vereinbarung: Wenn das Origin Vob keine homeWorld hat kümmert sich jemand anders
	// um die Bewegung
	zBOOL shouldStop  = FALSE;

	if ( (NULL!=origin) && (NULL!=origin->GetHomeWorld()) && GetAllowMovement() ) 
	{
		BeginMovement();

		zBOOL rotateLocal = (emSelfRotVel != zVEC3(0,0,0)) || zDYNAMIC_CAST<zCDecal>(GetVisual());

		// Bei Partikel Emittern mit folgenden Eigenschaften darf der Emitter Vob nicht rotiert werden
		zCParticleFX *pfx = zDYNAMIC_CAST<zCParticleFX>(GetVisual());
		if (pfx && pfx->GetEmitter()->dirFOR == zPFX_FOR_OBJECT && pfx->GetEmitter()->dirMode== zPFX_EMITTER_DIRMODE_TARGET) rotateLocal = TRUE;
		

		if (isChild) 
		{
			if (parent != 0)			   SetPositionWorld(parent->trafoObjToWorld.GetTranslation()); else
			if (emTrjMode == EM_TRJ_UNDEF) Move(emFlyGravity * frameTime);     
		}
		else 
		{
			if (emTrjMode & EM_TRJ_FIXED) 
			{
				if (origin) 
				{
					zMATRIX4 trafoFxToWorld = Alg_Identity3D();
					if ( orgNode ) trafoFxToWorld = origin->GetTrafoModelNodeToWorld(orgNode);
					else  		   trafoFxToWorld = origin->GetNewTrafoObjToWorld();

					if (rotateLocal) SetPositionWorld	(trafoFxToWorld.GetTranslation());
					else			 SetTrafoObjToWorld	(trafoFxToWorld);	
				}
			}
			else if (emTrjMode == EM_TRJ_UNDEF) 
			{
				Move(zVEC3(0,emFlyGravity * frameTime,0));
			}
			else if (emTrjMode & EM_TRJ_MISSILE) 
			{
				zVEC3 newFlyVec;
				trajectory.ApplyGrav(emFlyGravity*frameTime);
				if (target) targetPos = target->GetPositionWorld();
				else		
				{
					if (targetPos==zVEC3(0,0,0) || (emTrjMode & EM_TRJ_FOLLOW))
					{
						zMAT4 flippedTrafo = origin->trafoObjToWorld;
						flippedTrafo.SetAtVector(-flippedTrafo.GetAtVector());
						targetPos = CalcAziElevRange(emTrjTargetAzi,emTrjTargetElev,emTrjTargetRange,flippedTrafo);
					}
				}
				newFlyVec  = (targetPos-GetPositionWorld()).Normalize()*emTrjEaseVel*frameTime*trjSign;

				SetPositionWorld(GetPositionWorld()+newFlyVec);

				if ( (origin->GetPositionWorld()-GetPositionWorld()).Length2()>=(targetPos-origin->GetPositionWorld()).Length2() )
				{
					if (emTrjLoopMode == TRJ_LOOP_RESTART)						SetPositionWorld(trajectory.GetKey(0).GetTranslation()); else
					if (emTrjLoopMode == TRJ_LOOP_PINGPONG)						trjSign		= -trjSign; else
					if (emTrjLoopMode == TRJ_LOOP_PINGPONG_ONCE && trjSign>0)	trjSign		= -trjSign; else
					if (emTrjLoopMode != TRJ_LOOP_HALT)							shouldStop	= TRUE;
				}
			}
			else 
			{ 
				trajectory.ApplyGrav(emFlyGravity*frameTime);

				if (emTrjEaseFunc == TEASEFUNC_LINEAR) 
				{
					float actVelo = emTrjEaseVel; 

					emTrjDist  += trjSign * actVelo * frameTime;
					if (emTrjDist > trajectory.Length() || emTrjDist < 0) {
						zClamp(emTrjDist, zVALUE(0), zVALUE(trajectory.Length()));
						if (emTrjLoopMode == TRJ_LOOP_RESTART)						emTrjDist	= 0;		else
						if (emTrjLoopMode == TRJ_LOOP_PINGPONG)						trjSign		= -trjSign; else
						if (emTrjLoopMode == TRJ_LOOP_PINGPONG_ONCE && trjSign>0)	trjSign		= -trjSign; else
						if (emTrjLoopMode != TRJ_LOOP_HALT)							shouldStop	= TRUE;
					}
					
					if (rotateLocal) SetPositionWorld	( trajectory.Interpolate( emTrjDist ).GetTranslation() );
					else			 SetTrafoObjToWorld	( trajectory.Interpolate( emTrjDist ) );

				}
				else if (emTrjEaseFunc == TEASEFUNC_SINE)  
				{
					
					easeTime += trjSign * frameTime/emTrjEaseVel;
					
					if (easeTime > 1 || easeTime < 0) 
					{
						zClamp(easeTime, zVALUE(0), zVALUE(1));

						if (emTrjLoopMode == TRJ_LOOP_RESTART)						easeTime	= 0;		else
						if (emTrjLoopMode == TRJ_LOOP_PINGPONG)						trjSign		= -trjSign; else
						if (emTrjLoopMode == TRJ_LOOP_PINGPONG_ONCE && trjSign>0)	trjSign		= -trjSign; else
						if (emTrjLoopMode != TRJ_LOOP_HALT)							shouldStop	= TRUE;
					}
				
					if (rotateLocal) SetPositionWorld	( trajectory.InterpolateN( zSinusEase(easeTime) ).GetTranslation() );
					else			 SetTrafoObjToWorld	( trajectory.InterpolateN( zSinusEase(easeTime) ) );
				}
			}
		}

		if (emTrjMode & EM_TRJ_FOLLOW)
		{
			zPOINT3 idealPos;
			if (!emTrjFollowHitLastCheck) idealPos = GetNewTrafoObjToWorld().GetTranslation();
			else						  idealPos = transRing[ringPos];

			if ( GetHomeWorld()->GetMasterFrameCtr() % 3 ) 
			{
				zPOINT3 p0 = trajectory.Interpolate(0).GetTranslation();

				if (GetHomeWorld()->TraceRayNearestHit( p0 , idealPos-p0, origin, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_POLY_IGNORE_TRANSP|zTRACERAY_VOB_IGNORE_NO_CD_DYN))
				{
					idealPos = p0 + 0.6F* (GetHomeWorld()->traceRayReport.foundIntersection-p0);
					emTrjFollowHitLastCheck = TRUE;
				} 
				else emTrjFollowHitLastCheck = FALSE;
			}
		
			transRing[ringPos++] = idealPos;

			if (ringPos==VFX_MAX_POS_SAMPLES) ringPos = 0;

			idealPos = zVEC3(0,0,0);

			for (int i=0; i<VFX_MAX_POS_SAMPLES; i++) idealPos += transRing[i];

			SetPositionWorld(idealPos/VFX_MAX_POS_SAMPLES);
		}


		trjUpdateTime += frameTime;

		if ( drawTrj || (lightning && !zDYNAMIC_CAST<zCPolyStrip>(GetVisual())) ) trajectory.Draw();

		SetDrawBBox3D(drawBBox);

		if (rotateLocal) 
		{  
			RotateLocalX(emSelfRotVel[VX]*frameTime);
			RotateLocalY(emSelfRotVel[VY]*frameTime);
			RotateLocalZ(emSelfRotVel[VZ]*frameTime);
		}

		if (zDYNAMIC_CAST<zCDecal>(GetVisual()))
		{
			zMAT4 newTrafo = this->GetNewTrafoObjToWorld();
			newTrafo.SetTranslation(newTrafo.GetTranslation() + zVEC3(0,10,0) + (50 * newTrafo.GetAtVector()));
			newTrafo.SetAtVector((zCCamera::activeCamPos-newTrafo.GetTranslation()).Normalize());
			zVEC3 up = (zCCamera::activeCam->GetVob()->GetUpVectorWorld());
			
			zVEC3 right = newTrafo.GetAtVector()^up;
			right[VY]=0;
			right.NormalizeSafe();
			newTrafo.SetRightVector(right);
			newTrafo.SetUpVector   (newTrafo.GetAtVector()^right);
			SetTrafoObjToWorld(newTrafo);
		};

		//SetPositionWorld(zCCamera::activeCam->GetVob()->GetPositionWorld() + 200*zCCamera::activeCam->GetVob()->GetAtVectorWorld());

		EndMovement();
	}

	if (earthQuake) earthQuake->SetPositionWorld(GetPositionWorld());
	if (screenFX)	screenFX  ->SetPositionWorld(GetPositionWorld());

	if (!collisionOccured) lastTrjDir = (GetPositionWorld() - lastTrjPos).NormalizeSafe();
	if (shouldStop) Stop(TRUE);
}

zBOOL oCVisualFX::CheckDelayedTrigger()
{
	age		  += frameTime;
	
	if (!emFXTriggerDelay) return TRUE;

	if (age >= emFXTriggerDelay)
	{
		SetVisualByString(visName_S);

		if (fxState>=zVFXSTATE_INIT)
		{
			if (sfx) 
			{
				zCSoundSystem::zTSound3DParams params;
				params.SetDefaults();
				params.isAmbient3D = sfxIsAmbient;
				sfxHnd = zsound->PlaySound3D(sfx,this,zVFX_SOUNDSLOT_DEFAULT,&params);
			}
		}

		if (fxState>=zVFXSTATE_CAST)
		{
			if (earthQuake) earthQuake->OnTrigger(0,0);

			if (screenFX)   
			{
				zERR_MESSAGE(10,0,"C: VIS: starting blend effect");
				zCOLOR	fxColor		   = String2Color(userString[1]);
				screenFX->StartEffect_BlendFadeIn	(userString[2].ToFloat(),fxColor, userString[3], userString[4].ToFloat(), zrenderer->AlphaBlendFuncStringToType(visAlphaBlendFunc_S) );
				// zREAL	fovDeg		   = userString[2].ToFloat();
				// if (fovDeg > 0) screenFX->StartEffect_FOVMorph		(fxLoopDuration,0.1);
			}
		}
		emFXTriggerDelay =  0;
		return TRUE;
	}

	return FALSE;
}

void oCVisualFX::AdjustShapeToOrigin()
{
	if (emAdjustShpToOrigin) 
	{
		if (origin) 
		{
			if (GetVisual()) 
			{
				if ( zDYNAMIC_CAST<zCParticleFX>(GetVisual()) && origin->GetVisual() ) 
				{
					zPOINT3 mins = origin->GetVisual()->GetBBox3D().mins;
					zPOINT3 maxs = origin->GetVisual()->GetBBox3D().maxs;
					zVEC3 boxdim(zAbs(mins[VX]-maxs[VX]),zAbs(mins[VY]-maxs[VY]),zAbs(mins[VZ]-maxs[VZ]));
					zCParticleEmitter *em = static_cast<zCParticleFX*>(GetVisual())->GetEmitter();
					zVEC3 origDim					=   String2Vec3(em->shpDim_S);
					zREAL dimScale = 1;
					if (em->shpType == zPFX_EMITTER_SHAPE_BOX   ) dimScale = MIN(5,boxdim.LengthApprox()/origDim.LengthApprox());	else 
					if (em->shpType == zPFX_EMITTER_SHAPE_SPHERE) dimScale = MIN(5,origin->GetVisual()->GetBBox3D().GetSphere3D().radius/origDim[VX]); else

					em->shpLineBoxDim				=	boxdim;
					em->shpCircleSphereRadius		=	origin->GetVisual()->GetBBox3D().GetSphere3D().radius;

					//em->ppsValue					=	dimScale * savePpsValue;
					em->visSizeStart				=	dimScale * saveVisSizeStart;
				}
				else if (zDYNAMIC_CAST<zCDecal>(GetVisual()) && origin->GetVisual())
				{
					if (zDYNAMIC_CAST<zCModel>(origin->GetVisual()))
					{
						zCModel *model = static_cast<zCModel*>(origin->GetVisual());
						zTBBox3D box = model->GetBBox3DLocalFixed();
						box.Scale(zVEC3(1,0.6F,1));
						zCDecal *decal = static_cast<zCDecal*>(GetVisual());
						decal->SetDecalDim( MIN(350,zAbs(box.maxs[VX]-box.mins[VX])), zAbs(box.maxs[VY]-box.mins[VY]) );
					}
					else
					{
						zTBBox3D box = origin->GetBBox3DWorld();
						box.Scale(zVEC3(1,0.8F,1));
						zCDecal *decal = static_cast<zCDecal*>(GetVisual());
						decal->SetDecalDim(zAbs(box.maxs[VX]-box.mins[VX]), zAbs(box.maxs[VY]-box.mins[VY]));
					};
				}
			}
		}
	}
};

void oCVisualFX::UpdateEffects()
{
	
	if (sfx && sfxHnd) zsound->UpdateSound3D(sfxHnd);

	if (isDeleted) return;

	if ( !isChild && (trjUpdateTime > emTrjDynUpdateDelay) ) 
	{
		trjUpdateTime = 0;
		CalcTrajectory(emTrjDynUpdateTargetOnly);

	}

	if ( zDYNAMIC_CAST<zCPolyStrip>(GetVisual()) && !lightning)
	{
		zCPolyStrip *trl = static_cast<zCPolyStrip*>(GetVisual()) ;
		trl->AddSegment	(GetPositionWorld()-20*float(MAX(1.0f,level))*GetUpVectorWorld(), GetPositionWorld()+20*float(MAX(1.0f,level))*GetUpVectorWorld());
		trl->CalcBBox3D	();					// FIXME !!!!
	}

	if (screenFX)
	{
		zREAL   fxLoopDuration		= userString[0].ToFloat();

		screenFXTime += frameTime;
		if (screenFXTime>=fxLoopDuration)
		{
			screenFXTime = 0;
			zCOLOR	fxColor		   = String2Color(userString[1]);

			if (screenFXDir == 0)
			{
				screenFXDir = 1;
				screenFX->StartEffect_BlendFadeOut(userString[2].ToFloat(),fxColor);
				//	zREAL	fovDeg		   = userString[2].ToFloat();
				//if (fovDeg > 0) screenFX->StartEffect_FOVMorph(fxLoopDuration,0.1);
			}
			else 
			{
				screenFXDir = 0;
				screenFX->StartEffect_BlendFadeIn	(userString[2].ToFloat(),fxColor, userString[3], userString[4].ToFloat(), zrenderer->AlphaBlendFuncStringToType(visAlphaBlendFunc_S) );
				//	zREAL	fovDeg		   = userString[2].ToFloat();
				//if (fovDeg > 0) screenFX->StartEffect_FOVMorph		(fxLoopDuration,0.1);
			}

		}
	}

	if (fovMorph)
	{
		//
		zREAL timeDelta	= (ztimer.GetTotalTimeF()/ztimer.GetMotionFactor()) - fxStartTime;
		zREAL t			= 1.0F - ((timeDelta) / 2000.0F);
		if (t<0) t=0;
		t = zSinusEase(t);
		// smooth einblenden den dreck
		zREAL tBlendIn = timeDelta/	3500.0f; 
		if (tBlendIn>1) tBlendIn = 1;
		tBlendIn = zSinusEase(tBlendIn);

		zREAL newBaseFovX = oldFovX;
		zREAL newBaseFovY = oldFovY;

		if (!userString[2].IsEmpty()) newBaseFovX = userString[2].ToFloat();
		if (!userString[3].IsEmpty()) newBaseFovY = userString[3].ToFloat();

		zREAL amp		= tBlendIn * (zREAL(5.00F) + t * zREAL(48.0F));
		zREAL speed		= zREAL(1.05F) + t * zREAL(1.0F);

		speed		   *= userString[0].ToFloat();
		amp			   *= userString[1].ToFloat();

		zREAL fovX		= zLerp(tBlendIn,oldFovX, newBaseFovX) + zSin (speed * (timeDelta * 0.0010F + (float(M_PI) * 1.0f))) * (amp);
		zREAL fovY		= zLerp(tBlendIn,oldFovY, newBaseFovY) + zSin (speed * (timeDelta * 0.0006F + (float(M_PI) * 1.5f))) * (amp * 0.75F);

		zCCamera::activeCam->SetFOV		(fovX, fovY);
		zCCamera::activeCam->Activate	();					// FIXME: ugly, => Die Camera muss FOV abh. internals setzen..
	}

};

void oCVisualFX:: OnTick()
{
	frameTime		= ztimer.GetFrameTimeF()/1000;
	
	if (m_fSleepTimer>0) 
	{
		m_fSleepTimer-=frameTime;
		if (m_fSleepTimer<0) m_fSleepTimer=0;
	}

	if (ProcessQueuedCollisions()) return;

	if ( CheckDeletion() ) return;	

	if (!CheckDelayedTrigger()) return;

	AdjustShapeToOrigin	   ();

	levelTime += frameTime;

	if ( secsPerDamage != -1 )
	if ( origin && zDYNAMIC_CAST<oCNpc>(origin) )
	{
		damageTime += frameTime;
		if (damageTime >= secsPerDamage)
		{
			static_cast<oCNpc*>(origin)->ChangeAttribute(NPC_ATR_HITPOINTS,-1);
			damageTime = 0;
		}
	};

	UpdateActKey ();
	UpdateEffects();


	DoMovements			   ();

	// wenn vorher Kollision stattgefunden hat, kurz checken, ob jetzt Vob frei, wenn ja Coll wieder anschmeissen
	// siehe auch Kommentar in oCTrajectory::RecalcByColl()
	// evtl. kann dieses CodeFragment raus, da in ReportCollision nach einer Collision mit ResetToOldMovementState()
	// der vob in den letzen bekannten nicht-kollidiert Zustand zurückversetzt wird
	// nachteile dieses einfachen collision response systems ist, das bei langsamer frame rate der abstand vom
	// kollisionspunkt zur letzen bekannten freien position grösser wird. besser wäre es, den exakten
 	// ort zu kennen, an dem der vob gerade nicht mehr kollidiert (ähnliche funktionsweise wie das zCAICamera::AdjustCenterSphere)
	// das könnte aber für effekte viel zu langsam sein
	// noch ein problem: die einfache collision response führt dazu, das durch ein simples "auf die letzte gültige position zurücksetzen"
	// die jetzt eigentliche darzustellende position übersprungen wird. durch das weiterlaufen der frametime
	// ist aber zumindest ein zeitlich korrektes verhalten gewährleistet
	// d.h. je langsamer die framerate ist, desto weniger wird das system "physikalisch korrekt"

/*	if (emCheckCollision && collisionOccured) 
	{
		SetCollisionEnabled(TRUE);

		if ( DetectCollision() ) 
		{
			SetCollisionEnabled(FALSE);
		}
		else 
		{
			collisionOccured = FALSE; 
		}
	} */
/*	else if (collisionCtr > 0 && emCheckCollision && !collisionOccured) 
	{
		// erstmalig keine folge collisionen mehr, alle parents davon informieren
		oCVisualFX *ptr = this;
		while ( ptr && ptr->parent != ptr ) 
		{
			ptr->collisionCtr = 0;
			ptr = ptr->parent;
		}
		collisionCtr = 0;
	}*/
};
 

void oCVisualFX::Archive	(zCArchiver &arc)
{
	zCEffect::Archive (arc);
};

void oCVisualFX::Unarchive	(zCArchiver &arc)
{
	zCEffect::Unarchive (arc);
};


void oCVisualFX::CalcPFXMesh()
{
	
	zCParticleFX* pfx = zDYNAMIC_CAST<zCParticleFX>(GetVisual());
	if (!pfx) return;
	
	// falls der partikeleffekt ein mesh als shp-type besitzt, dieses aber nicht initialisiert hat,
	// und emAdjustShpToOrigin auf true steht, übernimmt das oCVisualFX System die Kontrolle über das PFX Mesh Visual
	// dem partikeleffekt das richtige shape mitgeben, falls nötig
	if ( (this->emAdjustShpToOrigin) && (NULL!=origin) && (zPFX_EMITTER_SHAPE_MESH==pfx->GetEmitter()->shpType))
	{
		bPfxMeshSetByVisualFX = TRUE;

		ReleasePFXMesh();

		zCMesh*				orgMesh		= zDYNAMIC_CAST<zCMesh>			(origin->GetVisual());
		zCProgMeshProto*	orgProgMesh = zDYNAMIC_CAST<zCProgMeshProto>(origin->GetVisual());
		zCModel*			orgModel	= zDYNAMIC_CAST<zCModel>		(origin->GetVisual());
		zCMorphMesh*		orgMorph	= zDYNAMIC_CAST<zCMorphMesh>	(origin->GetVisual());

		if (orgMesh)
		{
			static_cast<zCParticleFX*>(GetVisual())->GetEmitter()->shpMesh = orgMesh;
			orgMesh->AddRef();
		}
		else if (orgProgMesh)
		{
			static_cast<zCParticleFX*>(GetVisual())->GetEmitter()->shpProgMesh = orgProgMesh;
			orgProgMesh->AddRef();
		}
		else if (orgModel)
		{
			static_cast<zCParticleFX*>(GetVisual())->GetEmitter()->shpModel = orgModel;
			orgModel->AddRef();
		}
		else if (orgMorph)
		{
			static_cast<zCParticleFX*>(GetVisual())->GetEmitter()->shpProgMesh = orgMorph->GetMorphMesh();
			if (orgMorph->GetMorphMesh()) orgMorph->GetMorphMesh()->AddRef();
		}
	}
};

void oCVisualFX::ReleasePFXMesh()
{

	if (emAdjustShpToOrigin && bPfxMeshSetByVisualFX && zDYNAMIC_CAST<zCParticleFX>(GetVisual())) 
	{
		zCParticleEmitter *emitter = static_cast<zCParticleFX*>(GetVisual())->GetEmitter();
		zRELEASE(emitter->shpMesh);
		zRELEASE(emitter->shpProgMesh);
		zRELEASE(emitter->shpModel);
	};
}


void oCVisualFX::SetPFXShapeVisual(zCVisual* a_pVisual, const zBOOL a_bForceChangeMesh)
{
	zCParticleFX* pfx = zDYNAMIC_CAST<zCParticleFX>(GetVisual());
	if (!pfx) return;
	zCMorphMesh* morph = zDYNAMIC_CAST<zCMorphMesh>(a_pVisual);

	if ( (a_bForceChangeMesh || emAdjustShpToOrigin) && bPfxMeshSetByVisualFX ) 
	{
		zCParticleEmitter *emitter = pfx->GetEmitter();
		
		if (emitter->shpMesh==a_pVisual || emitter->shpProgMesh==a_pVisual || emitter->shpModel==a_pVisual || (morph && morph->GetMorphMesh()==emitter->shpProgMesh))
		{
			return;
		}
		zRELEASE(emitter->shpMesh);
		zRELEASE(emitter->shpProgMesh);
		zRELEASE(emitter->shpModel);

		zCMesh*				orgMesh		= zDYNAMIC_CAST<zCMesh>			(a_pVisual);
		zCProgMeshProto*	orgProgMesh = zDYNAMIC_CAST<zCProgMeshProto>(a_pVisual);
		zCModel*			orgModel	= zDYNAMIC_CAST<zCModel>		(a_pVisual);
		zCMorphMesh*		orgMorph	= zDYNAMIC_CAST<zCMorphMesh>	(a_pVisual);

		if (orgMesh)
		{
			static_cast<zCParticleFX*>(GetVisual())->GetEmitter()->shpMesh = orgMesh;
			orgMesh->AddRef();
		}
		else if (orgProgMesh)
		{
			static_cast<zCParticleFX*>(GetVisual())->GetEmitter()->shpProgMesh = orgProgMesh;
			orgProgMesh->AddRef();
		}
		else if (orgModel)
		{
			static_cast<zCParticleFX*>(GetVisual())->GetEmitter()->shpModel = orgModel;
			orgModel->AddRef();
		}
		else if (orgMorph)
		{
			static_cast<zCParticleFX*>(GetVisual())->GetEmitter()->shpProgMesh = orgMorph->GetMorphMesh();
			if (orgMorph->GetMorphMesh()) orgMorph->GetMorphMesh()->AddRef();
		}
	};
};

void oCVisualFXAI::DoAI(zCVob*vob,zBOOL &vobDeleted)
{ 
    // [Moos] nach dieser Funktion gibt es noch zwei pointer auf vob: von der Welt und lokal von vob->DoFrameActivity(). 

//	if ( delete_it && vob->GetRefCtr()>2 )
  //      vob->Release();		// vob wird sonst nur aus der welt entfernt, und nicht gelöscht
	if ( delete_it )  
	{
		zERR_ASSERT(vob->GetRefCtr()>=2);
	//	vob->Release();		// vob wird sonst nur aus der welt entfernt, und nicht gelöscht
	}
	vobDeleted = delete_it;	
    
};

#else 

// --------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------

zBOOL oCVisualFX::FxConsole_EvalFunc (const zSTRING &in, zSTRING &msg)
{
	return FALSE;
};

void oCVisualFX::InitParser()
{
};

oCVisualFX::oCVisualFX()		   
{
	zERR_MESSAGE(8,0,"C: VIS: constructed");
}; 

oCVisualFX :: ~oCVisualFX() 
{
	zERR_MESSAGE(8,0,"C: VIS: destructed");
};



void oCVisualFX::OnTick			()
{
	zERR_MESSAGE(8,0,"C: VIS: OnTick");
};

	// init, inserts fx vobs into world, initializes AI Callbacks per frame etc.
void oCVisualFX::	Open			()
{
	zERR_MESSAGE(8,0,"C: VIS: Open");

	SetVisual("invisible_zCVobLight.3ds"); 
	SetDrawBBox3D(TRUE);

	zCWorld *world = zCCamera::activeCam->GetVob()->GetHomeWorld();
	world -> AddVob(this);

};

void oCVisualFX::   SetOrigin		( zCVob *orgVob )
{
	zERR_MESSAGE(8,0,"C: VIS: SetOrigin");
};

void oCVisualFX::   SetTarget		( zCVob *targetVob )
{
	zERR_MESSAGE(8,0,"C: VIS: SetTarget");
};

void oCVisualFX::SetTarget		( zPOINT3 &targetPos )
{
	zERR_MESSAGE(8,0,"C: VIS: SetTarget (pos)");
};

void oCVisualFX::Init			( zCVob *orgVob, zPOINT3 &targetPos		)
{
	zERR_MESSAGE(8,0,"C: VIS: Init (pos) ");
};

void oCVisualFX::Init			( zCVob *orgVob , zCVob *trgtVob  )
{
	zERR_MESSAGE(8,0,"C: VIS: Init");
};

void oCVisualFX::Init			( zCArray <zCVob *> trajectoryVobs		)
{
	zERR_MESSAGE(8,0,"C: VIS: Init (array) ");
};

void oCVisualFX::InvestNext		()
{
	zERR_MESSAGE(8,0,"C: VIS: InvestNext");
};

void oCVisualFX::SetLevel		( int level )
{
	zERR_MESSAGE( 8,0,"C: VIS: SetLevel:" + zSTRING(level) );
};

void oCVisualFX::Cast			( const zBOOL killAfterDone )
{
	zERR_MESSAGE(8,0,"C: VIS: Cast");

	this->RemoveVobFromWorld();
	zRELEASE_ACCT_NONULL(this);

};

void oCVisualFX::Stop			( const zBOOL killAfterDone )
{
	zERR_MESSAGE(8,0,"C: VIS: Stop");

	this->RemoveVobFromWorld();
	zRELEASE_ACCT_NONULL(this);
};

zBOOL oCVisualFX::IsFinished		()
{
	return FALSE;
};

zBOOL oCVisualFX::IsLooping		()											
{ 
	return FALSE; 
};

void oCVisualFX::SetByScript		( const zSTRING &id )
{
	zERR_MESSAGE(8,0,"C: VIS: SetByScript");
};

void oCVisualFX::SetCollDetStat  ( const zBOOL b )
{
};

void oCVisualFX::ReportCollision			(const zTVobCollisionReport& collisionReport)
{
	zERR_MESSAGE(8,0,"C: VIS: ReportCollision");
};

void oCVisualFX::SetCollisionEnabled		(const zBOOL en)
{
};

zBOOL oCVisualFX::CanThisCollideWith		(zCVob* vob)
{
	return TRUE;
};


// Damage Types

void oCVisualFX::SetDamage		( const float dam     )						
{ 	
};

void oCVisualFX::SetDamageType	( const int   damType )						
{ 
};

float oCVisualFX::GetDamage		() const									
{ 
	return 10;
};

int	oCVisualFX::GetDamageType	() const									
{ 
	return 1;
};

void	oCVisualFX::Archive			(zCArchiver &)
{
};

void	oCVisualFX::Unarchive		(zCArchiver &)
{
};



#endif


zCLASS_DEFINITION			(oCVisualFX,		zCEffect,	zCLASS_FLAG_SHARED_OBJECTS,	1)
