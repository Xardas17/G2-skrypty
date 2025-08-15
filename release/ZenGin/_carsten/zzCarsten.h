/***************************************************************************
*									
* Projekt-Mitglied bezogene Texte und Hinweise, StartUp/CleanUp-Code (Header)
* Datei         : zzCarsten.h
* Projekt       : Engine
* Autor         : Carsten Edenfeld
* Version       : 0.01
* last modified : 20.12.98
* erstellt      : 20.12.98
*									
****************************************************************************/

#ifndef __ZZCARSTEN_H__
#define __ZZCARSTEN_H__

#ifndef __ZMUSIC_H__
#include "zmusic.h"
#endif

#ifndef __ZMUSIC_DM_H__
#include "zmusic_dm.h"
#endif

extern void zCarsten_StartUp(zTSystemContextHandle* initContextHandle);
extern void zCarsten_ShutDown();
extern void zCarsten_ShutDown_Fast();

#endif
