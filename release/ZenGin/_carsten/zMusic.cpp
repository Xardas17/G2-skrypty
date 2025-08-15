// zMusic.cpp
// Carsten Edenfeld

#include "zcore.h"
#include "zmusic.h"

zCMusicSystem *zmusic = 0;

zBOOL zCMusicSystem::s_musicSystemDisabled = FALSE;

/***********************************************************
 zCMusicSystem::DisableMusicSystem

 30.01.2000 Speckels
			Methode eingefuehrt
 ***********************************************************/
void zCMusicSystem::DisableMusicSystem(zBOOL disable)
{ 
	s_musicSystemDisabled = disable;
	if (s_musicSystemDisabled)
	{
		if (zmusic) zmusic->Stop();
	}	
};