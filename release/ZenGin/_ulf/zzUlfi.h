/******************************************************************************** 
 
     $Workfile:: ZzUlfi.h             $                $Date:: 4.12.00 18:23    $
     $Revision:: 5                    $             $Modtime:: 4.12.00 17:13    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/ZzUlfi.h $
 * 
 * 5     4.12.00 18:23 Moos
 * 
 * 4     22.05.00 18:46 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

 /***************************************************************************
*									
* Projekt-Mitglied bezogene Texte und Hinweise, StartUp/CleanUp-Code (Header)
* Datei         : zzUlfi.h
* Projekt       : Engine
* Autor         : Ulfi
* Version       : 0.00
* last modified : 10.03.97
* erstellt      : 01.03.97
*									
****************************************************************************/

/*
- INHALT -
1. Letzte Hinweise
2. Kommentare
3. Arbeits-Pläne
4. File-Liste
5. Basis-Typen
6. Worklog
7. Startup/Cleanup - Code

****************************
** 1. Letzte Hinweise     **
****************************

	* 10.3.97 *
	
	- Grade 97.041 (!) -> Bei älteren Grade Versionen entstehen Farb-Fehler in 16Bit Modis.
    - WICHTIG : Aus dem Mainfile das Init der Datenstruktur "vidinfo" und die Funktion
				"CFUNC vmodeEnumerator(DWORD Size)" entfernen ! 
	- Zum Ein/Umschalten des Grafikmode im Programm nicht die Grade-Funktion verwenden, sondern
	  immer View_SetMode(int x,int y,int bpp);
	- Vor dem Zugriff auf ein Desktop-Item dieses ab sofort immer erst in den Vater einfügen.
	  z.B. screen->Insert(View). Erst danach Grafikzugriffe auf "View" durchführen.
	- Auf vielfachen Wunsch sind alle Print-Befehle jetzt "printf"-kompatibel.
	  Bislang unterstützt :	"%d" -> integer
							"%s" -> char *
							"%S" -> zSTRING *
	- Main Test File: "Orph.cpp".

****************************
** 2. Kommentare          **
****************************

  - Idee: bei zCView: print-Sachen als _Stream_ implementieren !? 
    Ich arbeite dran ! Siehe 1.

****************************
** 3. Arbeits-Pläne       **
****************************


****************************
** 4. File-Liste          **
****************************

	Header-File	C++ File		Erläuterung
-------------------------------------------------------------------------------
	zzUlfi.h					Dieses File
	zGrafix.h	zGrafix.cpp		Grafik-Verwaltungs-Modul 
	zDisk.h		zDisk.cpp		Basic File-Handling
	zview.h	zDesktop.cpp	Oberflaechen-Baukasten

	oNpc.h		oNpc.cpp		NPC-Klasse (temp)
	oInfo.h		oInfo.cpp		Informations-Klasse (Infopool)
	oMission.h	oMission.cpp	Mission-Klasse 
	oDialog.h	oDialog.cpp		Dialog-System

				tPath.cpp		Pfadsuch-Algo-Testprogramm (A*)

****************************
** 5. Basis-Typen         **
****************************

	Typ			Definition in File		Erlaeuterung
-------------------------------------------------------------------------------
	zFILE		zDisk.cpp				Basis-File-Klasse

****************************
** 6. Worklog             **
****************************

****************************
** 7. StartUp/CleanUp     **
****************************

*/

#ifndef __ZZULFI_H__
#define __ZZULFI_H__

extern void zUlfi_StartUp();
extern void zUlfi_ShutDown();

#endif