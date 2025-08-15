/***************************************************************************
*									
* Projekt-Mitglied bezogene Texte und Hinweise, StartUp/CleanUp-Code (Header)
* Datei         : ooCarsten.h
* Projekt       : Gothic
* Autor         : Carsten Edenfeld
* Version       : 0.00
* last modified : 14.11.98
* erstellt      : 14.11.98
*									
****************************************************************************/

#ifndef __OOCARSTEN_H__
#define __OOCARSTEN_H__

#include "windows.h"

extern zBOOL	freeLook;

extern void oCarsten_StartUp ();
extern void oCarsten_ShutDown();
extern void oCarsten_PerFrame();
extern void TestKeys_Carsten (int key);


#endif