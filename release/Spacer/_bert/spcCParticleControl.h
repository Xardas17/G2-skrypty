// spcCParticleControl.h: interface .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPCCPARTICLECONTROL_H__F7F40944_2D1E_11D2_88A8_0080AD209698__INCLUDED_)
#define AFX_SPCCPARTICLECONTROL_H__F7F40944_2D1E_11D2_88A8_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <zTypes3D.h>
#include <zParticle.h>
#include <zVob.h>

class spcCParticleControl
{
private:
	zCParticleFX* partFX;
	zCVob* pfxVob;
	zTVobID	pfxVobID;
	zSTRING pfxName;

	zCWorld*	rnd_world;
public:
	spcCParticleControl();
	spcCParticleControl(zCWorld* theWorld);
	~spcCParticleControl();

	zCVob* GetPFXVob ();
	void SelectActivePFX();
	void EditActivePFX();
	void StartActivePFX();
	void CreateNewPFX(zSTRING& newPFXName);

	void SetPFXName(zSTRING& newPFXName);
	void SetWorld(zCWorld* theWorld);
	void BeginEditActive();
	void EndEditActive();

	bool IsInEditMode;
};


#endif